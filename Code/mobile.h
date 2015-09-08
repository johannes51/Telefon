#ifndef MOBILE_H
#define MOBILE_H

/*!
 * \file mobile.h
 * \brief Interface with the mobile phone.
 *
 * Functions for interfacing with the mobile phone through UART and serial connection.
*/

// STD includes
#include <stdbool.h>

bool mobile_isRinging();
bool mobile_isCalling();

bool mobile_startCall(char* Number);

#endif
