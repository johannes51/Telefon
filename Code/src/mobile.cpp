// header include
#include "mobile.h"

Mobile::Mobile()
{
  _sim800.begin();
  _sim800.sendCommand(AT_AT, true);
  _sim800.sendCommand(AT_AT, true);
  _sim800.sendCommand(AT_RINGER_OFF, true);
}

Mobile::Mobile(const Mobile& lhs)
{
  Serial.print("Mobile(const Mobile& lhs)");
}

/*!
* \brief Check for phone ringing.
 * \return Wether the phone is currently ringing (true) or not (false).
 */
bool Mobile::isRinging()
{
  int cs =_sim800.getCallStatus();
  Serial.print("callStatus ");
  Serial.println(cs);
  return cs == 3;
}

/*!
 * \brief Check for an active call.
 * \return Wether the phone currently has an active call.
 */
bool Mobile::isCalling()
{
  return _sim800.getCallStatus() == 4;
}

bool Mobile::startCall()
{
  return _sim800.answerCall();
}

/*!
 * \brief Have the phone dial a number.
 * \param Number Number as a null-terminated string.
 * \return Wether the command was successful.
 */
bool Mobile::startCall(const String& Number)
{
  //if (Number == "4")
    return _sim800.callNumber(Number.c_str());
  //else return false;
}

/*!
 * \brief Have the phone hang up.
 * \return Wether the command was successful.
 */
bool Mobile::hangUp()
{
  return _sim800.hangoffCall();
}

void Mobile::setDialtone(bool tone)
{
  String duration = tone ? "15300000" : "10";
  _sim800.sendCommand(String(String(AT_TONE) += duration).c_str());
}

void Mobile::setHangupTone(bool tone)
{
}
