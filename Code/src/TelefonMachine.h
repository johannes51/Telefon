#include <LowPower.h>

#include "statemachine.h"
#include "mobile.h"
#include "fetap.h"

const unsigned long maxIdleTime = 3000;
const unsigned long maxPhoneIdle = 1000;

// StateMachine setup
// global state for the StateMachine

struct GlobalState
{
  String number;
  Mobile mobile;
  Fetap fetap;
  unsigned long tranisitionTime;
};
StateMachine<GlobalState>* telefonMachine;

// transition functions

void startRinging(GlobalState* globalState)
{
  Serial.println(F("idle->ringing"));
}

void stopRinging(GlobalState* globalState)
{
  Serial.println(F("ringing->idle"));
  globalState->fetap.stopRinging();
}

void startDialtone(GlobalState* globalState)
{
  Serial.println(F("idle->dialing"));
  globalState->mobile.setDialtone(true);
}

void stopDialtone(GlobalState* globalState)
{
  Serial.println(F("dialing->idle"));
  globalState->mobile.setDialtone(false);
}

void processOutboundCall(GlobalState* globalState)
{
  globalState->mobile.setDialtone(false);
  Serial.println(F("dialing->call"));
  Serial.println(globalState->number);
  globalState->mobile.startCall(globalState->number);
}

void processInboundCall(GlobalState* globalState)
{
  Serial.println(F("idle->ringing"));
  globalState->fetap.stopRinging();
  globalState->mobile.startCall();
}

void endCall(GlobalState* globalState)
{
  Serial.println(F("call->idle"));
  globalState->mobile.setHangupTone(false);
  globalState->mobile.hangUp();
  globalState->tranisitionTime = millis();
}

void sleepSim(GlobalState* globalState)
{
  Serial.println(F("idle->halfsleep"));
  globalState->mobile.sleepSim();
  globalState->tranisitionTime = millis();
}

void wakeUpMobile(GlobalState* globalState)
{
  Serial.println(F("halfsleep->idle"));
  globalState->tranisitionTime = millis();
}

void gotoSleep(GlobalState* globalState)
{
  Serial.println(F("halfsleep->sleep"));
}

void wakeUp(GlobalState* globalState)
{
  Serial.println(F("sleep->idle"));
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

bool isMobileWoken(GlobalState* globalState)
{
  return !globalState->mobile.isSleeping();
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
  detachInterrupt(CradlePin);
}

void sleep(GlobalState* globalState)
{
  // go to sleep here
  attachInterrupt(digitalPinToInterrupt(CradlePin), cradleMoved, FALLING);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
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
  telefonMachine->addTransition(stateHalfSleep, stateIdle, isMobileWoken, wakeUpMobile);
  telefonMachine->addTransition(stateSleep, stateIdle, nullptr, wakeUp);
}
