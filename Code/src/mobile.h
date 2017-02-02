#ifndef MOBILE_H
#define MOBILE_H

#include <string>

/*!
 * \file mobile.h
 * \brief Logic interface with the mobile phone.
 *
 * Functions for sending commands and receiving data from the phone */

class Mobile
{
public:
  bool isRinging();
  bool isCalling();

  bool startCall();
  bool startCall(const std::string& Number);
  bool hangUp();

  void setDialtone(bool tone);
  void setHangupTone(bool tone);
};

/** Naked AT command, used for autobauding */
#define AT_AT "AT"
/** Query for network status */
#define AT_NETSTAT "AT+COPS"

#endif
