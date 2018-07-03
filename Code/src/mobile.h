#ifndef MOBILE_H
#define MOBILE_H

#include <Arduino.h>

#define RX_PIN 19
#define TX_PIN 18

/*!
 * \file mobile.h
 * \brief Logic interface with the mobile phone.
 *
 * Functions for sending commands and receiving data from the phone */

class ThreadController;

class Mobile
{
public:
  enum class CallStatus {
    Idle,
    Ringing,
    Call,
  };

  Mobile();
  ~Mobile();

  bool isRinging();
  bool isCalling();
  bool isSleeping();

  void startCall();
  void startCall(String& Number);
  void hangUp();

  void setDialtone(bool tone);
  void setHangupTone(bool tone);

  void sleepSim();

private:
  CallStatus getCs();
  void wakeSim();

  CallStatus callStatus_;
  bool sleepingBuffer_; // use isSleeping()
};

/** Query for network status */
#define AT_DIAL_TONE "1,1,15300000"
#define AT_BUSY_TONE "1,2,15300000"
#define AT_NO_TONE "0"

#endif
