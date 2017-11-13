#ifndef SIMPLESTATEMACHINE_H
#define SIMPLESTATEMACHINE_H

#include <StandardCplusplus.h>
#include <map>

#include "statemachine.h"

typedef State<bool> SimpleState;

class SimpleStateMachine
{
  friend StateMachine<bool>;
public:
  SimpleStateMachine();

  void execute();

  const SimpleState* addState(void (*executeFunction)() = 0);
  void addTransition(const SimpleState* fromState, const SimpleState* toState,
                     bool (*triggerFunction)(), void (*executeFunction)() = 0);

private:
  static void stateExecutor(const bool* globalState);
  static void transitionExecutor(const bool* globalState);
  static void transitionTrigger(const bool* globalState);

  static StateMachine<bool> _sm;
  static std::map<const SimpleState*, void (*)()> _stateExecuteFunctionMap;
  static std::map<const Transition<bool>*, void (*)()> _transitionExecuteFunctionMap;
  static std::map<const Transition<bool>*, void (*)()> _transitionTriggerFunctionMap;
};

#endif
