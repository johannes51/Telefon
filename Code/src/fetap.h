#ifndef FETAP_H
#define FETAP_H

// lib includes
#include <Arduino.h>
#include <Tone.h>

#include "statemachine.h"

const unsigned long MaxDigitDelay = 6000;
const unsigned short CradlePin = 3;
const unsigned short NsaPin = 8;
const unsigned short NsiPin = 9;
const unsigned short RingerPin = 16;
const unsigned long NsiDebounceDelay = 20;

struct RingerState
{
  RingerState() { tone.begin(RingerPin); }
  uint8_t ringsPlayed = 0;
  unsigned long tranisitionTime;
  Tone tone;
};

/*!
 * \file fetap.h
 * \brief A class to interact with the analog telephone.
 *
 * Functions that read the state of the dial plate and hook, as well as activating the ringer.
*/

class Fetap
{
public:
  Fetap();
  ~Fetap();

  void ring();
  void stopRinging();
  bool isRinging();

  bool isUnhooked();

  String commenceDialing();
private:
  int listenForDigit();
  bool isDoneDialing();

  bool isTurned();

  unsigned long lastDigitMillis_;

  StateMachine<RingerState> ringer_;
  const State<RingerState>* stopState_;
};

#endif
