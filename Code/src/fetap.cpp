// header include
#include "fetap.h"

#include <avr/power.h>

#include "RingerMachine.h"

Fetap::Fetap()
{
  pinMode(CradlePin, INPUT_PULLUP);
  pinMode(NsaPin, INPUT_PULLUP);
  pinMode(NsiPin, INPUT_PULLUP);

  stopState_ = setupRingerMachine(ringer_);
}

/*!
* \brief Set the ringer status.
* \param Status to set it to (true for ringing, false for silent).
*/
void Fetap::ring() {
  ringer_.execute();
  digitalWrite(13, HIGH);
}

void Fetap::stopRinging(){
  ringer_.setState(stopState_);
  power_timer2_disable();
  digitalWrite(13, LOW);
}

/*!
 * \brief Read status of the ringer.
 * \return Wether the ringer is active.
 */
bool Fetap::isRinging()
{
  return ringer_.getState() != stopState_;
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
  lastDigitMillis_ = millis();
  String result;
  while (isUnhooked() && !isDoneDialing()) {
    if (isTurned()) {
      Serial.println("isturned");
      auto digit = listenForDigit();
      if (digit >= 0) {
        result += (char)('0' + digit);
      }
      lastDigitMillis_ = millis();
      Serial.print("Nummer: ");
      Serial.println(result);
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
    if (lastDebounceTime + NsiDebounceDelay < millis())
      if (reading != buttonState) {
        lastDebounceTime = millis();
        buttonState = reading;
        if (buttonState == HIGH)
          ++result;
      }
  }
  if (result == 10)
    result = 0;
  else if (result < 1 || result > 10)
    result = -1;
  return result;
}

bool Fetap::isDoneDialing()
{
  return (millis() > lastDigitMillis_ + MaxDigitDelay);
}

bool Fetap::isTurned()
{
  return digitalRead(NsaPin) == LOW;
}
