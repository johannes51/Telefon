// lib include
#include <Arduino.h>
#include <avr/power.h>
// project includes
#include "TelefonMachine.h"

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
  Serial.println(F(""));
  Serial.println(F("start setup"));
  power_adc_disable(); //should not do anything
  power_timer1_disable(); // this is probably not used
  // power_spi_disable(); // this might be used by the ISP, neccessary?
  power_twi_disable(); // used by noone, probably disable
  Serial.println(F("setup TelefonMachine"));
  setupTelefonMachine();
  Serial.println(F("setup done"));
}

/*!
 * \brief loop-Funktion
 * Haupt-Loop
 */
void loop()
{
  // Serial.println(F("1"));
  // telefonMachine->_globalState.fetap.setRinger(true);
  // Serial.println(F("2"));
  // delay(1000);
  // Serial.println(F("3"));
  // telefonMachine->_globalState.fetap.setRinger(false);
  // Serial.println(F("4"));
  // delay(1000);
  // Serial.println(F("5"));
  telefonMachine->execute();
}
