// header include
#include "fetap.h"

void cradleMoved()
{
}

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

Fetap::Fetap()
{
  pinMode(CradlePin, INPUT_PULLUP);
  attachInterrupt(CradlePin, cradleMoved, FALLING);
  pinMode(NsaPin, INPUT_PULLUP);
  pinMode(NsiPin, INPUT_PULLUP);

  stopState_ = ringer_.addState();
  auto stateRing1 = ringer_.addState();
  auto stateRing2 = ringer_.addState();
  auto statePause1 = ringer_.addState();
  auto statePause2 = ringer_.addState();

  ringer_.addTransition(stopState_, stateRing1, nullptr, startRinging);
  ringer_.addTransition(stateRing1, statePause1, finishedRinging, ringOff);
  ringer_.addTransition(statePause1, stateRing2, finishedPausing, ringOn);
  ringer_.addTransition(stateRing2, statePause2, finishedRinging, ringOff);
  ringer_.addTransition(statePause2, stateRing1, finishedPausing, startRinging);
}

Fetap::~Fetap()
{
  detachInterrupt(CradlePin);
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
