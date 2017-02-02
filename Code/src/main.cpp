// std includes
#include <string.h>
// lib include
#include <Arduino.h>
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
* \brief Das Mainfile!
*/

/*!
* \brief setup-Funktion
* Wird einmal zu Beginn ausgeführt.
*/

struct GlobalState
{
  std::string Number;
}
;
StateMachine<GlobalState> telefonMachine;
Mobile mob;
Fetap fep;

void startRingin(GlobalState*)
{
  fep.setRinger(true);
}

void stopRingin(GlobalState*)
{
  fep.setRinger(false);
}

bool isUnhooked(GlobalState*)
{
  return fep.isUnhooked();
}

bool isHooked(GlobalState*)
{
  return !fep.isUnhooked();
}

void startDialtone(GlobalState* globalState)
{
  mob.setDialtone(true);
}

void stopDialtone(GlobalState* globalState)
{
  mob.setDialtone(false);
}

void processOutboundCall(GlobalState* globalState)
{
  mob.setDialtone(false);
  mob.startCall(globalState->Number);
}

void processInboundCall(GlobalState* globalState)
{
  fep.setRinger(false);
  mob.startCall();
}

void checkCallState(GlobalState*)
{
  if (!mob.isCalling())
    mob.setHangupTone(true);
}

bool receiveInboundCall(GlobalState* globalState)
{
  return mob.isRinging();
}

bool noInboundCall(GlobalState* globalState)
{
  return !mob.isRinging();
}

void endCall(GlobalState* globalState)
{
  mob.setHangupTone(true);
  mob.hangUp();
}

void processDialing(GlobalState* globalState)
{
  globalState->Number = fep.commenceDialing();
}

void setup()
{
  const State<GlobalState>* stateIdle = telefonMachine.addState();
  const State<GlobalState>* stateRinging = telefonMachine.addState();
  const State<GlobalState>* stateDialing = telefonMachine.addState(processDialing);
  const State<GlobalState>* stateCall = telefonMachine.addState(checkCallState);
  telefonMachine.addTransition(stateIdle, stateRinging, receiveInboundCall, startRingin);
  telefonMachine.addTransition(stateRinging, stateIdle, noInboundCall, stopRingin);
  telefonMachine.addTransition(stateRinging, stateCall, isUnhooked, processInboundCall);
  telefonMachine.addTransition(stateIdle, stateDialing, isUnhooked, startDialtone);
  telefonMachine.addTransition(stateDialing, stateIdle, isHooked, stopDialtone);
  telefonMachine.addTransition(stateDialing, stateCall, isUnhooked, processOutboundCall);
  telefonMachine.addTransition(stateCall, stateIdle, isHooked, endCall);
}

/*!
 * \brief loop-Funktion
 * Haupt-Loop
 */
void loop()
{
  telefonMachine.execute();
}
