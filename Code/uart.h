#ifndef UART_H
#define UART_H

/*!
 * \file uart.h
 * \brief Serial interface with the mobile phone.
 *
 * Functions for interfacing with the mobile phone through UART and serial connection.
*/

void uart_init();
void uart_puts(char* s);

#endif // UART_H
