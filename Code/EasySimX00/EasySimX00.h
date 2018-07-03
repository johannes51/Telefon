#ifndef EASY_SIM_X00_H
#define EASY_SIM_X00_H

#include <list>

enum CallStatus {
	Idle,
	Ringing,
	Call
};

class AtCommand;

class EasySimX00
{
public:
	EasySimX00(uint8_t rxPin, uint8_t txPin, int8_t resetPin = -1);

	void begin();

	void hangupCall();
	void callNumber(const char* cmd);
	void answerCall();
	void reset();

	CallStatus getCallStatus();

	void execute();
private:
	void enqueue(AtCommand* command, bool priority);
	void processResponse(AtCommand* command);

	AtCommand* currentCommand_;
	std::list<AtCommand*> unresolvedCommands_;
	std::list<AtCommand*> resolvedCommands_;

	bool synced_;
	CallStatus callStatus_;
	int8_t resetPin_;
};

#endif // EASY_SIM_X00_H
