#ifndef STATEMACHINE_H
#define STATEMACHINE_H

// std includes
#include <StandardCplusplus.h>
#include <vector>
// lib includes
#include "Arduino.h"
// project includes
#include "transition.h"
#include "state.h"

template <class GlobalState>
class StateMachine
{
public:
  StateMachine();
  StateMachine(GlobalState globalState);

  void execute();

  const State<GlobalState>* getState() const;
  void setState(const State<GlobalState>*);

  const GlobalState& globalState() const;

  const State<GlobalState>* addState(void (*executeFunction)(GlobalState*) = nullptr);
  void addTransition(const State<GlobalState>* fromState,
                     const State<GlobalState>* toState,
                     bool (*triggerFunction)(GlobalState*) = nullptr,
                     void (*executeFunction)(GlobalState*) = nullptr);

private:
  GlobalState _globalState;

  std::vector<State<GlobalState> > _states;
  State<GlobalState>* _state;
  std::vector<Transition<GlobalState> > _transitions;
};

template <class GlobalState>
StateMachine<GlobalState>::StateMachine()
: _globalState()
, _state(0)
{
}

template <class GlobalState>
StateMachine<GlobalState>::StateMachine(GlobalState globalState)
: _globalState(globalState)
, _state(0)
{
}

template <class GlobalState>
void StateMachine<GlobalState>::execute()
{
  for (unsigned int i = 0; i < _transitions.size(); ++i){
    if (_transitions.at(i).fromState() == _state && _transitions.at(i).isTriggered(&_globalState)) {
      _state = const_cast<State<GlobalState>*>(_transitions.at(i).toState());
      _transitions.at(i).execute(&_globalState);
      break;
    }}
  _state->execute(&_globalState);
}

template <class GlobalState>
const State<GlobalState>* StateMachine<GlobalState>::getState() const
{
  return _state;
}

template <class GlobalState>
void StateMachine<GlobalState>::setState(const State<GlobalState>* newState)
{
  for (auto state : _states) {
    if (newState == &state) {
      _state = &state;
      break;
    }
  }
}

template <class GlobalState>
const State<GlobalState>* StateMachine<GlobalState>::addState(void (*executeFunction)(GlobalState*))
{
  _states.push_back(State<GlobalState>(executeFunction));
  if (_state == 0)
    _state = &_states.at(0);
  return &_states.back();
}

template <class GlobalState>
void StateMachine<GlobalState>::addTransition(const State<GlobalState>* fromState, const State<GlobalState>* toState,
                   bool (*triggerFunction)(GlobalState*), void (*executeFunction)(GlobalState*))
{
  _transitions.push_back(Transition<GlobalState>(fromState, toState, triggerFunction, executeFunction));
}

#endif
