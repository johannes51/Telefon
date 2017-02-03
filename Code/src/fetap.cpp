// header include
#include "fetap.h"

const unsigned long MaxDigitDelay = 6000;
const unsigned short CradlePin = 6;
const unsigned short NsaPin = 7;
const unsigned short NsiPin = 8;
const unsigned short RingerPin = 3;
unsigned long DebounceDelay = 20;

Fetap::Fetap()
: _ringing(false)
, _tone()
{
  pinMode(CradlePin, INPUT_PULLUP);
  pinMode(NsaPin, INPUT_PULLUP);
  pinMode(NsiPin, INPUT_PULLUP);
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

String Fetap::commenceDialing()
{
  _lastDigitMillis = millis();
  String result;
  while (isUnhooked() && !isDoneDialing()) {
    if (isTurned()) {
      Serial.println("isturned");
      result += (char)('0' + listenForDigit());
      _lastDigitMillis = millis();
    }
  }
  return result;
}

int Fetap::listenForDigit()
{
  int result = 0;
  unsigned long lastDebounceTime = 0;
  int buttonState = HIGH;
  delay(10);
  while (isTurned()) {
    int reading = digitalRead(NsiPin);
    if (lastDebounceTime + DebounceDelay < millis())
      if (reading != buttonState) {
        lastDebounceTime = millis();
        buttonState = reading;
        if (buttonState == HIGH)
          ++result;
      }
  }
  Serial.println(result);
  if (result == 10)
    result = 0;
  else if (result < 1 || result > 10)
    result = -1;
  return result;
}

bool Fetap::isDoneDialing()
{
  return (millis() > _lastDigitMillis + MaxDigitDelay);
}

bool Fetap::isTurned()
{
  return digitalRead(NsaPin) == LOW;
}
