#ifndef MOBILE_H
#define MOBILE_H

// lib includes
#include "Arduino.h"
#include "Sim800l.h"

/*!
 * \file mobile.h
 * \brief Logic interface with the mobile phone.
 *
 * Functions for sending commands and receiving data from the phone */

class Mobile
{
public:
  Mobile();
  Mobile(const Mobile& lhs);

  bool isRinging();
  bool isCalling();

  bool startCall();
  bool startCall(const String& Number);
  bool hangUp();

  void setDialtone(bool tone);
  void setHangupTone(bool tone);
private:
  Sim800l _sim800;
};

/** Query for network status */
#define AT_AT "AT"
#define AT_NETSTAT "AT+COPS"
#define AT_TONE "AT+STTONE=1,1,"
#define AT_RINGER_OFF "AT+CALM=1"

#endif
