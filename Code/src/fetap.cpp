// header include
#include "fetap.h"

#include "Arduino.h"

const unsigned long MaxDigitDelay = 4000;

Fetap::Fetap()
: _ringing(false)
{
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
 * \brief Set the ringer status.
 * \param Status to set it to (true for ringing, false for silent).
 */
void Fetap::setRinger(bool ring)
{
  /* Hardware bal */
  _ringing = ring;
}

/*!
 * \brief Read status of the hook switch.
 * \return Wether the switch is unhooked.
 */
bool Fetap::isUnhooked()
{
  /* Hardware bla */
  return false;
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
