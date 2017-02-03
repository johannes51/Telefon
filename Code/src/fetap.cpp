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
, _tone()
{
  pinMode(CradlePin, INPUT_PULLUP);
  pinMode(NsaPin, INPUT);
  pinMode(NsiPin, INPUT);
  _tone.begin(RingerPin);
}

/*!
* \brief Set the ringer status.
* \param Status to set it to (true for ringing, false for silent).
*/
void Fetap::setRinger(bool ring)
{
  if (ring) {
    _tone.play(10);
    digitalWrite(13, HIGH);
  } else {
    _tone.play(10, 10);
    digitalWrite(13, LOW);
  }
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
      Serial.println("isturned");
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
