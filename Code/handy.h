#ifndef HANDY_H
#define HANDY_H

/*!
 * \file handy.h
 * \brief Interface with the mobile phone.
 *
 * Functions for interfacing with the mobile phone through UART and serial connection.
*/

// STD includes
#include <stdbool.h>

bool isRinging();
bool isCalling();

bool startCall(char* Number);

#endif
