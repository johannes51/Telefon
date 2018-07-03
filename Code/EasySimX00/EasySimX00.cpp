#include "EasySimX00.h"

#include <Arduino.h>

#include "SimSerialThread.h"
#include "AtCommand.h"

EasySimX00::EasySimX00(uint8_t rxPin, uint8_t txPin, int8_t resetPin)
: currentCommand_(nullptr)
, synced_(false)
, callStatus_(Idle)
, resetPin_(resetPin)
{
	auto thread = new SimSerialThread(&currentCommand_, rxPin, txPin);
	thread->setInterval(5);
	control_.add(thread);
}

void EasySimX00::begin()
{
	while (!synced_) {
		if (unresolvedCommands_.empty() && resolvedCommands_.empty() && currentCommand_ == nullptr) {
			enqueue(new AtCommand(F("AT")), true);
		}
		execute();
		delay(10);
	}
}

void EasySimX00::answerCall()
{
	// enqueue(new AtCommand("ATA"), true);
}

void EasySimX00::callNumber(const char* number)
{
	// enqueue(new AtCommand("ATD" + String(number)), true);
}

CallStatus EasySimX00::getCallStatus()
{
  // SIM.print (F("AT+CPAS\r\n"));
	return callStatus_;
}

void EasySimX00::hangupCall()
{
		// enqueue(new AtCommand("ATH"), true);
}

void EasySimX00::enqueue(AtCommand* command, bool priority)
{
	if (priority) {
		unresolvedCommands_.push_front(command);
	} else {
		unresolvedCommands_.push_back(command);
	}
}

void EasySimX00::execute()
{
	if (currentCommand_ == nullptr) {
		if (!unresolvedCommands_.empty()) {
			currentCommand_ = unresolvedCommands_.front();
		}
	} else {
		if (currentCommand_->done()) {
				resolvedCommands_.push_back(currentCommand_);
				if (unresolvedCommands_.empty()) {
					currentCommand_ = nullptr;
				} else {
					currentCommand_ = unresolvedCommands_.front();
					unresolvedCommands_.pop_front();
				}
		}
	}
	if (!resolvedCommands_.empty()) {
		processResponse(resolvedCommands_.front());
		resolvedCommands_.pop_front();
	}
	control_.run();
}

void EasySimX00::processResponse(AtCommand* command)
{
	if (command->command() == F("AT")) {
		if (command->response().indexOf(F("OK")) != -1) {
			synced_ = true;
		}
	} else if (command->response().indexOf(F("+CPAS")) != -1) {
		int cs = command->response().substring(command->response().indexOf("+CPAS: ")+7,command->response().indexOf("+CPAS: ")+9).toInt();
	  switch (cs) {
			case 3:
				callStatus_ = Ringing;
				break;
			case 4:
				callStatus_ = Call;
				break;
			default:
				callStatus_ = Idle;
				break;
		}
	}
}

void EasySimX00::reset(){
  digitalWrite(resetPin_, 1);
  delay(1000);
  digitalWrite(resetPin_, 0);
  delay(1000);
  // resync
	synced_ = false;
  begin();
}
