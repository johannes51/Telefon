#ifndef AT_COMMAND_H
#define AT_COMMAND_H

#include <Arduino.h>

class AtCommand {
public:
  AtCommand(String command);

  const bool& done() const;
  void setResponse(String response);
  const String& command() const;
  const String& response() const;
  bool& sent();

private:
  bool sent_;
  bool done_;
  String response_;
  String command_;
};

#endif // AT_COMMAND_H
