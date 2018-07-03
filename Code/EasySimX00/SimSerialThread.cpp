#include "SimSerialThread.h"

#include "AtCommand.h"

SimSerialThread::SimSerialThread(AtCommand** command, uint8_t rxPin, uint8_t txPin)
: SIM_(rxPin, txPin)
, command_(command)
{
  if (command_ == nullptr) {
    Serial.println(F("AAAAAAAAAAAH"));
    Serial.println(F("AAAAAAAAAAAH"));
    Serial.println(F("AAAAAAAAAAAH"));
    Serial.println(F("AAAAAAAAAAAH"));
    Serial.println(F("AAAAAAAAAAAH"));
    while (true);
  }
  SIM_.begin(9600);
}

void SimSerialThread::run()
{
	if (*command_ != nullptr) {
 		if ((*command_)->sent()) {
			while (SIM_.available() > 0) {
        int nextByte = SIM_.read();
				partialResponse_.concat((char) nextByte);
        if (nextByte == 0) {
					(*command_)->setResponse(partialResponse_);
					partialResponse_ = F("");
					break;
				}
			}
		} else { // if not sent
			sendCommand();
		}
	}
	runned();
}

void SimSerialThread::sendCommand()
{
	if (*command_ != nullptr && !(*command_)->sent()) {
	  Serial.print("send command: ");
		Serial.println((*command_)->command());
	  SIM_.print((*command_)->command() + F("\r\n"));
		(*command_)->sent() = true;
	}
}
