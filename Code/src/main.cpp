// lib include
#include <Arduino.h>
#include <avr/power.h>
// project includes
#include "TelefonMachine.h"
#include "log.h"

/*!
* @mainpage Telefon
* Projekt zum Ansteuern eines Handys mittels einer Wählscheibe über einen AVR-uC
* @author Johannes Greul
*/

/*!
* \file main.c
*/

/*!
* \brief setup-Funktion
* Wird einmal zu Beginn ausgeführt.
*/
void setup()
{
  Serial.begin(9600);
  logLn(F(""));
  logLn(F("start setup"));
  power_adc_disable(); //should not do anything
  power_timer1_disable(); // this is probably not used
  // power_spi_disable(); // this might be used by the ISP, neccessary?
  power_twi_disable(); // used by noone, probably disable
  logLn(F("setup TelefonMachine"));
  setupTelefonMachine();
  logLn(F("setup done"));
}

/*!
 * \brief loop-Funktion
 * Haupt-Loop
 */
void loop()
{
  // logLn(F("1"));
  // telefonMachine->_globalState.fetap.setRinger(true);
  // logLn(F("2"));
  // delay(1000);
  // logLn(F("3"));
  // telefonMachine->_globalState.fetap.setRinger(false);
  // logLn(F("4"));
  // delay(1000);
  // logLn(F("5"));
  telefonMachine->execute();
}
