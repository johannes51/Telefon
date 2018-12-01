#ifndef MOBILE_H
#define MOBILE_H

#include <Arduino.h>

/*!
 * \file mobile.h
 * \brief Logic interface with the mobile phone.
 *
 * Functions for sending commands and receiving data from the phone */

const uint8_t ringPin = 2;
const uint8_t dtrPin = 7;

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
  unsigned long lastPoll_;

  // interrupt handling
  static void interrupted();
  static bool interruptedB;
};

#endif
