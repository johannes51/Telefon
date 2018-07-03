// header include
#include "mobile.h"

#include <SIM800.h>

bool interruptedB;

void interrupted()
{
  interruptedB = true;
}

Mobile::Mobile()
: sleepingBuffer_(true)
{
  SIM.begin();
  wakeSim();
  SIM.alertMode(CmdType::SET, "1");
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), interrupted, FALLING);
}

Mobile::~Mobile()
{
  detachInterrupt(digitalPinToInterrupt(2));
}

/*!
* \brief Check for phone ringing.
 * \return Wether the phone is currently ringing (true) or not (false).
 */
bool Mobile::isRinging()
{
  return getCs() == CallStatus::Ringing;
}

/*!
 * \brief Check for an active call.
 * \return Wether the phone currently has an active call.
 */
bool Mobile::isCalling()
{
  return getCs() == CallStatus::Call;
}

void Mobile::startCall()
{
  if (isSleeping()) {
    wakeSim();
  }
  SIM.answerCall();
}

/*!
 * \brief Have the phone dial a number.
 * \param Number Number as a null-terminated string.
 * \return Wether the command was successful.
 */
void Mobile::startCall(String& Number)
{
  if (isSleeping()) {
    wakeSim();
  }
  Number += ";";
  SIM.originCall(Number.c_str());
  Serial.println(SIM.getBuffer());
}

/*!
 * \brief Have the phone hang up.
 * \return Wether the command was successful.
 */
 void Mobile::hangUp()
{
  if (isSleeping()) {
    wakeSim();
  }
  SIM.endCall();
}

void Mobile::setDialtone(bool tone)
{
  if (isSleeping()) {
    wakeSim();
  }
  String params;
  if (tone) {
    params = AT_DIAL_TONE;
  } else {
    params = AT_NO_TONE;
  }
  SIM.stkPlayTone(CmdType::SET, params.c_str());
}

void Mobile::setHangupTone(bool tone)
{
  if (isSleeping()) {
    wakeSim();
  }
  String params;
  if (tone) {
    params = AT_BUSY_TONE;
  } else {
    params = AT_NO_TONE;
  }
  SIM.stkPlayTone(CmdType::SET, params.c_str());
}

void Mobile::sleepSim()
{
  if (!sleepingBuffer_) {
    Serial.println(F("sleepSim"));
    // this is where we would send the commands to do that and then set
    sleepingBuffer_ = true;
  }
}

Mobile::CallStatus Mobile::getCs()
{
  if (!isSleeping()) {
    SIM.activity(CmdType::EXE);
    auto reply = String(SIM.getBuffer());
    auto cs = reply.substring(reply.indexOf("+CPAS: ") + 7,
                              reply.indexOf("+CPAS: ") + 9).toInt();
    switch (cs) {
      case 0:
      default:
        callStatus_ = CallStatus::Idle;
        break;
      case 3:
        callStatus_ = CallStatus::Ringing;
        break;
      case 4:
        callStatus_ = CallStatus::Call;
        break;
    }
    interruptedB = false;
  }
  return callStatus_;
}

bool Mobile::isSleeping()
{
  if (interruptedB) {
    wakeSim();
  }
  return sleepingBuffer_;
}

void Mobile::wakeSim()
{
  if (sleepingBuffer_) {
    do {
      SIM.test();
      while (SIM.reply("TIMEOUT")) {
        delay(10);
      }
    } while (!SIM.reply("OK"));
    sleepingBuffer_ = false;
    Serial.println(F("woke!"));
  }
}
