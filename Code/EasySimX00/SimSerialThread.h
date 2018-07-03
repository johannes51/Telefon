#ifndef SIM_SERIAL_THREAD_H
#define SIM_SERIAL_THREAD_H

#include <SoftwareSerial.h>

#include <Thread.h>

class AtCommand;

class SimSerialThread : public Thread
{
public:
	SimSerialThread(AtCommand** command, uint8_t rxPin, uint8_t txPin);

	void run();

private:
	void sendCommand();

	SoftwareSerial SIM_;
	AtCommand** command_;
	String partialResponse_;
};

#endif // SIM_SERIAL_THREAD_H
