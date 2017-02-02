#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <StandardCplusplus.h>
#include <vector>
#include <memory>

#include "transition.h"

class SimpleStateMachine;

template <class GlobalState>
class StateMachine
{
  friend SimpleStateMachine;
public:
  StateMachine();
  StateMachine(GlobalState globalState);

  void execute();

  const State<GlobalState>* addState(void (*executeFunction)(GlobalState*) = 0);
  void addTransition(const State<GlobalState>* fromState, const State<GlobalState>* toState,
                     bool (*triggerFunction)(GlobalState*), void (*executeFunction)(GlobalState*) = 0);

protected:
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
        _state = const_cast<State<GlobalState>*>(_transitions.at(i).toState());
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
  return &_states.back();
}

template <class GlobalState>
void StateMachine<GlobalState>::addTransition(const State<GlobalState>* fromState, const State<GlobalState>* toState,
                   bool (*triggerFunction)(GlobalState*), void (*executeFunction)(GlobalState*))
{
  _transitions.push_back(Transition<GlobalState>(fromState, toState, triggerFunction, executeFunction));
}


#endif
