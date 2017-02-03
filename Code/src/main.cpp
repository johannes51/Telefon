// std includes
//#include <string.h>
// lib include
#include "Arduino.h"
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

struct GlobalState
{
  std::string number;
  Mobile mobile;
  Fetap fetap;
};
StateMachine<GlobalState> telefonMachine;

void startRinging(GlobalState* globalState)
{
  Serial.println("stateIdle->stateRinging");
  globalState->fetap.setRinger(true);
}

void stopRinging(GlobalState* globalState)
{
  Serial.println("stateRinging->stateIdle");
  globalState->fetap.setRinger(false);
}

bool isUnhooked(GlobalState* globalState)
{
  Serial.println("isUnhooked");
  return globalState->fetap.isUnhooked();
}

bool isHooked(GlobalState* globalState)
{
  Serial.println("isHooked");
  return !globalState->fetap.isUnhooked();
}

void startDialtone(GlobalState* globalState)
{
  Serial.println("stateIdle->stateDialing");
  globalState->mobile.setDialtone(true);
}

void stopDialtone(GlobalState* globalState)
{
  Serial.println("stateDialing->stateIdle");
  globalState->mobile.setDialtone(false);
}

void processOutboundCall(GlobalState* globalState)
{
  Serial.println("stateDialing->stateCall");
  globalState->mobile.setDialtone(false);
  globalState->mobile.startCall(globalState->number);
}

void processInboundCall(GlobalState* globalState)
{
  Serial.println("stateRinging->stateCall");
  globalState->fetap.setRinger(false);
  globalState->mobile.startCall();
}

bool receivingInboundCall(GlobalState* globalState)
{
  Serial.println("stateIdle?stateRinging");
  return globalState->mobile.isRinging();
}

bool noInboundCall(GlobalState* globalState)
{
  Serial.println("stateRinging?stateIdle");
  return !globalState->mobile.isRinging();
}

void endCall(GlobalState* globalState)
{
  Serial.println("stateCall->stateIdle");
  globalState->mobile.setHangupTone(true);
  globalState->mobile.hangUp();
}

void processDialing(GlobalState* globalState)
{
  Serial.println("stateDialing");
  globalState->number = globalState->fetap.commenceDialing();
  Serial.println("dialing done");
}

void checkCallState(GlobalState* globalState)
{
  Serial.println("stateCall");
  if (!globalState->mobile.isCalling())
    globalState->mobile.setHangupTone(true);
}

void si(GlobalState* globalState)
{
  Serial.println("stateIdle");
}

void sr(GlobalState* globalState)
{
  Serial.println("stateRinging");
}

/*!
* \brief setup-Funktion
* Wird einmal zu Beginn ausgeführt.
*/
void setup()
{
  Serial.begin(9600);
  Serial.println("setup");
  Serial.println("setup");
  const State<GlobalState>* stateIdle = telefonMachine.addState(si);
  const State<GlobalState>* stateRinging = telefonMachine.addState(sr);
  const State<GlobalState>* stateDialing = telefonMachine.addState(processDialing);
  const State<GlobalState>* stateCall = telefonMachine.addState(checkCallState);
  telefonMachine.addTransition(stateIdle, stateRinging, receivingInboundCall, startRinging);
  telefonMachine.addTransition(stateRinging, stateIdle, noInboundCall, stopRinging);
  telefonMachine.addTransition(stateRinging, stateCall, isUnhooked, processInboundCall);
  telefonMachine.addTransition(stateIdle, stateDialing, isUnhooked, startDialtone);
  telefonMachine.addTransition(stateDialing, stateIdle, isHooked, stopDialtone);
  telefonMachine.addTransition(stateDialing, stateCall, isUnhooked, processOutboundCall);
  telefonMachine.addTransition(stateCall, stateIdle, isHooked, endCall);
  Serial.println("setup done");
}

/*!
 * \brief loop-Funktion
 * Haupt-Loop
 */
void loop()
{
  Serial.println("mainloop");
  telefonMachine.execute();
}
