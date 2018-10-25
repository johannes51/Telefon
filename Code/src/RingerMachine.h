#ifndef RINGER_MACHINE_H
#define RINGER_MACHINE_H

#include "fetap.h"

#include <avr/power.h>

bool finishedRinging(RingerState* ringerState)
{
  unsigned long ringTime;
  switch (ringerState->ringsPlayed) {
    case 0:
      ringTime = 1000;
      break;
    case 1:
    default:
      ringTime = 300;
      break;
  }
  if (ringerState->tranisitionTime + ringTime < millis()) {
    ++ringerState->ringsPlayed;
    return true;
  } else {
    return false;
  }
}

bool finishedPausing(RingerState* ringerState)
{
  unsigned long pauseTime;
  switch (ringerState->ringsPlayed) {
    case 1:
      pauseTime = 250;
      break;
    case 2:
    default:
      pauseTime = 3000;
      break;
  }
  return (ringerState->tranisitionTime + pauseTime < millis());
}

void startRinging(RingerState* ringerState)
{
  power_timer2_enable();
  ringerState->tone.play(10);
  ringerState->ringsPlayed = 0;
}

void ringOn(RingerState* ringerState)
{
  ringerState->tone.play(10);
}

void ringOff(RingerState* ringerState)
{
  ringerState->tone.stop();
}

const State<RingerState>* setupRingerMachine(StateMachine<RingerState>& ringer)
{
  auto stopState = ringer.addState();
  auto stateRing1 = ringer.addState();
  auto stateRing2 = ringer.addState();
  auto statePause1 = ringer.addState();
  auto statePause2 = ringer.addState();

  ringer.addTransition(stopState, stateRing1, nullptr, startRinging);
  ringer.addTransition(stateRing1, statePause1, finishedRinging, ringOff);
  ringer.addTransition(statePause1, stateRing2, finishedPausing, ringOn);
  ringer.addTransition(stateRing2, statePause2, finishedRinging, ringOff);
  ringer.addTransition(statePause2, stateRing1, finishedPausing, startRinging);

  return stopState;
}

#endif // RINGER_MACHINE_H
