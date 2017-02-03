#ifndef FETAP_H
#define FETAP_H

#include <string>

#include "Tone.h"

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

  void setRinger(bool ring);
  bool isRinging();

  bool isUnhooked();

  std::string commenceDialing();
private:
  int listenForDigit();
  bool isDoneDialing();

  bool isTurned();

  unsigned long _lastDigitMillis;
  bool _ringing;
  Tone _tone;
};

#endif
