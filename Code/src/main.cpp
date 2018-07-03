// std includes
//#include <string.h>
// lib include
#include <Arduino.h>
#include <LowPower.h>
// project includes
#include "statemachine.h"
#include "mobile.h"
#include "fetap.h"


/*!
* @mainpage Telefon
* Projekt zum Ansteuern eines Handys mittels einer Wählscheibe über einen AVR-uC
* @author Johannes Greul
*/

/*!
* \file main.c
*/

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

void wakeUpSim(GlobalState* globalState)
{
  Serial.println(F("halfsleep->idle"));
  globalState->tranisitionTime = millis();
}

void gotoSleep(GlobalState* globalState)
{
  Serial.println(F("halfsleep->sleep"));
  globalState->tranisitionTime = millis();
}

void wakeUp(GlobalState* globalState)
{
  Serial.print(F("slept for: "));
  Serial.println(millis() - globalState->tranisitionTime);
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

bool isSimNapTime(GlobalState* globalState)
{
  return (globalState->tranisitionTime + maxPhoneIdle < millis());
}

bool isSimWoken(GlobalState* globalState)
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

void sleep(GlobalState* globalState)
{
  // go to sleep here
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  // wakes up here (maybe after priming Mobile for a wakeup) and then instantly
  // leaves via the automatic transition to idle
}

/*!
* \brief setup-Funktion
* Wird einmal zu Beginn ausgeführt.
*/
void setup()
{
  Serial.begin(9600);
  Serial.println(F(""));
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
  telefonMachine->addTransition(stateIdle, stateHalfSleep, isSimNapTime, sleepSim);
  telefonMachine->addTransition(stateHalfSleep, stateSleep, isNapTime, gotoSleep);
  telefonMachine->addTransition(stateHalfSleep, stateIdle, isSimWoken, wakeUpSim);
  telefonMachine->addTransition(stateSleep, stateIdle, nullptr, wakeUp);

  Serial.println(F("setup done"));
}

/*!
 * \brief loop-Funktion
 * Haupt-Loop
 */
void loop()
{
  // Serial.println(F("1"));
  // telefonMachine->_globalState.fetap.setRinger(true);
  // Serial.println(F("2"));
  // delay(1000);
  // Serial.println(F("3"));
  // telefonMachine->_globalState.fetap.setRinger(false);
  // Serial.println(F("4"));
  // delay(1000);
  // Serial.println(F("5"));
  telefonMachine->execute();
}
