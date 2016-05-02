//header include
#include "uart.h"
// AVR includes
#include <avr/io.h>
#include <avr/interrupt.h>
#define BAUD 19200
#include <util/setbaud.h>
// std includes
#include <string.h>

#define UART_MAXSTRLEN 128
volatile uint8_t uart_str_complete = 0;  // 1 .. String komplett empfangen
volatile uint8_t uart_str_count = 0;
volatile uint8_t uart_string_length = 0;
volatile char uart_string[UART_MAXSTRLEN + 1] = "";

ISR(USART_RXC_vect)
{
  unsigned char nextChar;

  // Daten aus dem Puffer lesen
  nextChar = UDR;
  if( uart_str_complete == 0 ) /* wenn uart_string noch nicht gelesen, neues Zeichen verwerfen */
  {
    if ( uart_str_count < UART_MAXSTRLEN )
    {
      uart_string[uart_str_count] = nextChar;
      ++uart_str_count;
    }
    else {
      uart_string[uart_str_count] = '\0';
      uart_string_length = uart_str_count;
      uart_str_count = 0;
      uart_str_complete = 1;
    }
    if (nextChar == '\r')
    {
      char temp_string[UART_MAXSTRLEN + 1];
      for (uint8_t offset = 0; offset < UART_MAXSTRLEN + 1; ++offset)
      {
        temp_string[offset] = uart_string[offset];
      }
      if ( strncmp(temp_string + uart_str_count - 3, "OK", 2) == 0 ||
           strncmp(temp_string + uart_str_count - 6, "ERROR", 5) == 0
         )
      {
        uart_string[uart_str_count] = '\0';
        uart_string_length = uart_str_count;
        uart_str_count = 0;
        uart_str_complete = 1;
      }
    }
  }
}

/* ATmega16 */
int uart_putc(unsigned char c)
{
  while (!(UCSRA & (1<<UDRE)))  /* warten bis Senden moeglich */
  {
  }

  UDR = c; /* sende Zeichen */
  return 0;
}

/* puts ist unabhaengig vom Controllertyp */
void uart_puts(char* s)
{
  while (*s)
  {   /* so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)" */
    uart_putc(*s);
    s++;
  }
}

void uart_init()
{
  UBRRH = UBRRH_VALUE;
  UBRRL = UBRRL_VALUE;
  UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
  // Frame Format: Asynchron 8N1
  UCSRC = (1 << URSEL) | (3 << UCSZ0);
  uart_puts("ATE0\r");
  uart_puts("ATV1\r");
}
