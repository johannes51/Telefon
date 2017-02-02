// header include
#include "mobile.h"
// lib includes
#include "Sim800l.cpp"

/*!
* \brief Check for phone ringing.
 * \return Wether the phone is currently ringing (true) or not (false).
 */
bool Mobile::isRinging()
{
  Sim800l sim;
  return false;
}

/*!
 * \brief Check for an active call.
 * \return Wether the phone currently has an active call.
 */
bool Mobile::isCalling()
{
  return false;
}

bool Mobile::startCall()
{
  return false;
}

void Mobile::setDialtone(bool tone)
{

}

void Mobile::setHangupTone(bool tone)
{

}

/*!
 * \brief Have the phone dial a number.
 * \param Number Number as a null-terminated string.
 * \return Wether the command was successful.
 */
bool Mobile::startCall(const std::string& Number)
{
  return false;
}

/*!
 * \brief Have the phone hang up.
 * \return Wether the command was successful.
 */
bool Mobile::hangUp()
{
  return true;
}
