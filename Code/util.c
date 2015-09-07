//header include
#include "util.h"
// AVR includes
#include <avr/wdt.h>
#include <util/delay.h>

/*!
 * \brief Watchdog-Initialisierung.
 *
 * Initialisiert den Watchdog und stoppt ihn dann.
 */
void wdt_init()
{
  MCUCSR = 0;
  wdt_reset();
  wdt_disable();
}

/*!
 * \brief Setzt den uC zurück.
 *
 * Startet den Watchdog-Timer und wartet dann, um einen Reset des uC zu erzwingen.
 */
void uCReset()
{
  wdt_enable(WDTO_15MS);
  _delay_ms(1000);
}
