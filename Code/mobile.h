#ifndef MOBILE_H
#define MOBILE_H

/*!
 * \file mobile.h
 * \brief Logic interface with the mobile phone.
 *
 * Functions for sending commands and receiving data from the phone */
// STD includes
#include <stdbool.h>

bool mobile_isRinging();
bool mobile_isCalling();

bool mobile_startCall(char* Number);

/* Following are the defines for IO-Ports, AT command and such */

/** Naked AT command, used for autobauding */
#define AT_AT "AT"
/** Query for network status */
#define AT_NETSTAT "AT+COPS"

#endif
