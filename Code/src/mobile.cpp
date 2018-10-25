// header include
#include "mobile.h"

#include <avr/power.h>
#include <SIM800.h>

/** Query for network status */
#define AT_DIAL_TONE "1,1,15300000"
#define AT_BUSY_TONE "1,3,15300000"
#define AT_NO_TONE "0"

bool Mobile::interruptedB = true;

Mobile::Mobile()
: sleepingBuffer_(true)
{
  pinMode(dtrPin, OUTPUT);
  wakeSim();
  SIM.alertMode(CmdType::SET, "1");
  SIM.slowClock(CmdType::SET, "1");
  pinMode(ringPin, INPUT);
}

Mobile::~Mobile()
{
  if (!interruptedB) {
    detachInterrupt(digitalPinToInterrupt(ringPin));
  }
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
  wakeSim();
  SIM.answerCall();
}

/*!
 * \brief Have the phone dial a number.
 * \param Number Number as a null-terminated string.
 * \return Wether the command was successful.
 */
void Mobile::startCall(String& Number)
{
  wakeSim();
  Number += ";";
  SIM.originCall(Number.c_str());
  Serial.print(F("Call reply: "));
  Serial.println(SIM.getBuffer());
}

/*!
 * \brief Have the phone hang up.
 * \return Wether the command was successful.
 */
 void Mobile::hangUp()
{
  wakeSim();
  do {
    SIM.endCall();
  } while (!SIM.reply("OK"));
}

void Mobile::setDialtone(bool tone)
{
  wakeSim();
  String params;
  if (tone) {
    params = AT_DIAL_TONE;
  } else {
    params = AT_NO_TONE;
  }
  do {
    SIM.stkPlayTone(CmdType::SET, params.c_str());
  } while (!SIM.reply("OK"));
  Serial.print(F("dial reply: "));
  Serial.println(SIM.getBuffer());
}

void Mobile::setHangupTone(bool tone)
{
  wakeSim();
  String params;
  if (tone) {
    params = AT_BUSY_TONE;
  } else {
    params = AT_NO_TONE;
  }
  do {
    SIM.stkPlayTone(CmdType::SET, params.c_str());
  } while (!SIM.reply("OK"));
  Serial.print(F("hangup reply: "));
  Serial.println(SIM.getBuffer());
}

void Mobile::sleepSim()
{
  if (!sleepingBuffer_) {
    Serial.println(F("sleepSim"));
    digitalWrite(dtrPin, HIGH);
    SIM.end();
    // power_usart0_disable(); once we use HW Serial
    attachInterrupt(digitalPinToInterrupt(2), interrupted, FALLING);
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
    digitalWrite(dtrPin, LOW);
    delay(50);
    SIM.begin();
    // power_usart0_enable(); once we use HW Serial
    do {
      SIM.test();
    } while (!SIM.reply("OK"));
    sleepingBuffer_ = false;
  }
}

void Mobile::interrupted()
{
  interruptedB = true;
  detachInterrupt(digitalPinToInterrupt(ringPin));
}
