#include "AtCommand.h"

AtCommand::AtCommand(String command)
: sent_(false)
, done_(false)
, command_(command)
{
}

const bool& AtCommand::done() const
{
  return done_;
}

void AtCommand::setResponse(String response)
{
  if (!done_) {
  	Serial.println("resp: " + response);
    response_ = response;
    done_ = true;
  }
}

const String& AtCommand::command() const
{
  return command_;
}

const String& AtCommand::response() const
{
  return response_;
}

bool& AtCommand::sent()
{
  return sent_;
}
