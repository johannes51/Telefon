#include "simplestatemachine.h"

StateMachine<bool> SimpleStateMachine::_sm;

SimpleStateMachine::SimpleStateMachine()
{
}

void SimpleStateMachine::execute()
{
  _sm.execute();
}

const SimpleState* SimpleStateMachine::addState(void (*executeFunction)())
{

  const SimpleState* newState = _sm.addState(&SimpleStateMachine::stateExecutor);
  _stateExecuteFunctionMap[newState] = executeFunction;
  return newState;
}

void SimpleStateMachine::addTransition(const SimpleState* fromState, const SimpleState* toState,
                   bool (*triggerFunction)(), void (*executeFunction)())
{
  _sm.addTransition(fromState, toState, triggerFunction, executeFunction);
}

void SimpleStateMachine::stateExecutor(const bool* globalState)
{
  void (*executeFunction)() = (_stateExecuteFunctionMap[_sm._state]);
  executeFunction();
}

void SimpleStateMachine::transitionExecutor(const bool* globalState)
{
  void (*executeFunction)() = (_stateExecuteFunctionMap[_sm._state]);
  executeFunction();
}

void SimpleStateMachine::transitionTrigger(const bool* globalState)
{
  void (*executeFunction)() = (_functionMap[_sm._state]);
  executeFunction();
}
