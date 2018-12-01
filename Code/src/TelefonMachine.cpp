#include "TelefonMachine.h"

#include "log.h"

StateMachine<GlobalState>* telefonMachine;

// transition functions

void startRinging(GlobalState* globalState)
{
  logLn(F("idle->ringing"));
  globalState->tranisitionTime = millis();
}

void stopRinging(GlobalState* globalState)
{
  logLn(F("ringing->idle"));
  globalState->fetap.stopRinging();
  globalState->tranisitionTime = millis();
}

void startDialtone(GlobalState* globalState)
{
  logLn(F("idle->dialing"));
  globalState->mobile.setDialtone(true);
  globalState->tranisitionTime = millis();
}

void stopDialtone(GlobalState* globalState)
{
  logLn(F("dialing->idle"));
  globalState->mobile.setDialtone(false);
  globalState->tranisitionTime = millis();
}

void processOutboundCall(GlobalState* globalState)
{
  globalState->mobile.setDialtone(false);
  logLn(F("dialing->call"));
  logLn(globalState->number);
  globalState->mobile.startCall(globalState->number);
  globalState->tranisitionTime = millis();
}

void processInboundCall(GlobalState* globalState)
{
  logLn(F("idle->ringing"));
  globalState->fetap.stopRinging();
  globalState->mobile.startCall();
  globalState->tranisitionTime = millis();
}

void endCall(GlobalState* globalState)
{
  logLn(F("call->idle"));
  globalState->mobile.setHangupTone(false);
  globalState->mobile.hangUp();
  globalState->tranisitionTime = millis();
}

void sleepSim(GlobalState* globalState)
{
  logLn(F("idle->halfsleep"));
  globalState->mobile.sleepSim();
  globalState->tranisitionTime = millis();
}

void wakeUpMobile(GlobalState* globalState)
{
  logLn(F("halfsleep->idle"));
  globalState->tranisitionTime = millis();
}

void gotoSleep(GlobalState* globalState)
{
  logLn(F("halfsleep->sleep"));
  globalState->tranisitionTime = millis();
}

void wakeUp(GlobalState* globalState)
{
  logLn(F("sleep->idle"));
  globalState->tranisitionTime = millis();
}

// transition conditions

bool isUnhooked(GlobalState* globalState)
{
  return globalState->fetap.isUnhooked();
}

bool isHooked(GlobalState* globalState)
{
  return !globalState->fetap.isUnhooked();
}

bool receivingInboundCall(GlobalState* globalState)
{
  return globalState->mobile.isRinging();
}

bool noInboundCall(GlobalState* globalState)
{
  return !globalState->mobile.isRinging();
}

bool isNapTime(GlobalState* globalState)
{
  return (globalState->tranisitionTime + maxIdleTime < millis());
}

bool isSimMobileTime(GlobalState* globalState)
{
  return (globalState->tranisitionTime + maxPhoneIdle < millis());
}

bool isPhoneWoken(GlobalState* globalState)
{
  return !globalState->mobile.isSleeping() || globalState->fetap.isUnhooked();
}

// state Functions

void processDialing(GlobalState* globalState)
{
  globalState->number = globalState->fetap.commenceDialing();
}

void checkCallState(GlobalState* globalState)
{
  if (!globalState->mobile.isCalling()) {
    globalState->mobile.setHangupTone(true);
  }
}

void ring(GlobalState* globalState)
{
  globalState->fetap.ring();
}

void cradleMoved()
{
}

void sleep(GlobalState* globalState)
{
  // go to sleep here
  attachInterrupt(digitalPinToInterrupt(CradlePin), cradleMoved, FALLING);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  detachInterrupt(digitalPinToInterrupt(CradlePin));
  // wakes up here (maybe after priming Mobile for a wakeup) and then instantly
  // leaves via the automatic transition to idle
}

void setupTelefonMachine()
{
  telefonMachine = new StateMachine<GlobalState>();
  const State<GlobalState>* stateIdle = telefonMachine->addState();
  const State<GlobalState>* stateHalfSleep = telefonMachine->addState();
  const State<GlobalState>* stateSleep = telefonMachine->addState(sleep);
  const State<GlobalState>* stateRinging = telefonMachine->addState();
  const State<GlobalState>* stateDialing = telefonMachine->addState(processDialing);
  const State<GlobalState>* stateCall = telefonMachine->addState(checkCallState);
  telefonMachine->addTransition(stateIdle, stateRinging, receivingInboundCall, startRinging);
  telefonMachine->addTransition(stateRinging, stateIdle, noInboundCall, stopRinging);
  telefonMachine->addTransition(stateRinging, stateCall, isUnhooked, processInboundCall);
  telefonMachine->addTransition(stateIdle, stateDialing, isUnhooked, startDialtone);
  telefonMachine->addTransition(stateDialing, stateIdle, isHooked, stopDialtone);
  telefonMachine->addTransition(stateDialing, stateCall, isUnhooked, processOutboundCall);
  telefonMachine->addTransition(stateCall, stateIdle, isHooked, endCall);
  telefonMachine->addTransition(stateIdle, stateHalfSleep, isSimMobileTime, sleepSim);
  telefonMachine->addTransition(stateHalfSleep, stateSleep, isNapTime, gotoSleep);
  telefonMachine->addTransition(stateHalfSleep, stateIdle, isPhoneWoken, wakeUpMobile);
  telefonMachine->addTransition(stateSleep, stateIdle, nullptr, wakeUp);
}
