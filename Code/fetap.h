#ifndef FETAP_H
#define FETAP_H

/*!
 * \file fetap.h
 * \brief A collection of functions to interact with the analog telephone.
 *
 * Functions that read the state of the dial plate and hook, as well as activating the ringer.
*/

#include <stdbool.h>

void fetap_setRinger(bool ring);
bool fetap_isRinging();

bool fetap_isUnhooked();

#endif
