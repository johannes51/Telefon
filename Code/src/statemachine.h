#ifndef STATEMACHINE_H
#define STATEMACHINE_H

// std includes
#include <StandardCplusplus.h>
#include <vector>
// project includes
#include "transition.h"
#include "state.h"

#include "Arduino.h"

template <class GlobalState>
class StateMachine
{
public:
  StateMachine();
  StateMachine(GlobalState globalState);

  void execute();

  const State<GlobalState>* addState(void (*executeFunction)(GlobalState*) = 0);
  void addTransition(const State<GlobalState>* fromState, const State<GlobalState>* toState,
                     bool (*triggerFunction)(GlobalState*), void (*executeFunction)(GlobalState*) = 0);

private:
  std::vector<State<GlobalState> > _states;
  State<GlobalState>* _state;
  std::vector<Transition<GlobalState> > _transitions;
  GlobalState _globalState;
};

template <class GlobalState>
StateMachine<GlobalState>::StateMachine()
: _state(0)
, _globalState()
{
}

template <class GlobalState>
StateMachine<GlobalState>::StateMachine(GlobalState globalState)
: _state(0)
, _globalState(globalState)
{
}

template <class GlobalState>
void StateMachine<GlobalState>::execute()
{
  for (unsigned int i = 0; i < _transitions.size(); ++i)
    if (_transitions.at(i).fromState() == _state && _transitions.at(i).isTriggered(&_globalState)) {
      Serial.print("from: ");
      Serial.print((unsigned int) _state);
      _state = _transitions.at(i).toState();
      Serial.print("to: ");
      Serial.print((unsigned int) _state);
      _transitions.at(i).execute(&_globalState);
    }
  _state->execute(&_globalState);
}

template <class GlobalState>
const State<GlobalState>* StateMachine<GlobalState>::addState(void (*executeFunction)(GlobalState*))
{
  _states.push_back(State<GlobalState>(executeFunction));
  if (_state == 0)
    _state = &_states.back();
  Serial.print("state: ");
  Serial.print((unsigned int) &_states.back());
  Serial.print(" exec: ");
  Serial.println((unsigned int) executeFunction);
  return &_states.back();
}

template <class GlobalState>
void StateMachine<GlobalState>::addTransition(const State<GlobalState>* fromState, const State<GlobalState>* toState,
                   bool (*triggerFunction)(GlobalState*), void (*executeFunction)(GlobalState*))
{
  Serial.print("trans: ");
  Serial.print((unsigned int) fromState);Serial.print(" ");
  Serial.print((unsigned int) toState);Serial.print(" ");
  _transitions.push_back(Transition<GlobalState>(fromState, toState, triggerFunction, executeFunction));
  Serial.println((unsigned int) &_transitions.back());
}

#endif
