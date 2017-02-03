// header include
#include "fetap.h"
// lib includes
#include "Arduino.h"

const unsigned long MaxDigitDelay = 4000;
const unsigned short CradlePin = 6;
const unsigned short NsaPin = 7;
const unsigned short NsiPin = 8;
const unsigned short RingerPin = 3;

Fetap::Fetap()
: _ringing(false)
{/*
  pinMode(CradlePin, INPUT);
  pinMode(NsaPin, INPUT);
  pinMode(NsiPin, INPUT);
  pinMode(RingerPin, OUTPUT);
  digitalWrite(RingerPin, LOW);*/
}

/*!
* \brief Set the ringer status.
* \param Status to set it to (true for ringing, false for silent).
*/
void Fetap::setRinger(bool ring)
{
  unsigned short level = ring ? HIGH : LOW;
  digitalWrite(RingerPin, level);
  digitalWrite(13, level);
  _ringing = ring;
}

/*!
 * \brief Read status of the ringer.
 * \return Wether the ringer is active.
 */
bool Fetap::isRinging()
{
  return _ringing;
}

/*!
 * \brief Read status of the hook switch.
 * \return Wether the switch is unhooked.
 */
bool Fetap::isUnhooked()
{
  return digitalRead(CradlePin) == LOW;
}

std::string Fetap::commenceDialing()
{
  _lastDigitMillis = millis();
  std::string result;
  while (isUnhooked() && !isDoneDialing()) {
    if (isTurned()) {
      result.push_back((char)('0' + listenForDigit()));
      _lastDigitMillis = millis();
    }
  }
  return result;
}

int Fetap::listenForDigit()
{
  // MEGA SCHEISSE!
  return 0;
}

bool Fetap::isDoneDialing()
{
  return (millis() > _lastDigitMillis + MaxDigitDelay);
}

bool Fetap::isTurned()
{
  return digitalRead(NsaPin) == LOW;
}
