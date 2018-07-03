#ifndef TRANSITION_H
#define TRANSITION_H

template <class GlobalState>
class State;

template <class GlobalState>
class Transition
{
public:
  Transition(const State<GlobalState>* fromState, const State<GlobalState>* toState,
             bool (*triggerFunction)(GlobalState*), void (*executeFunction)(GlobalState*));

  void execute(GlobalState* globalState);
  bool isTriggered(GlobalState* globalState);

  const State<GlobalState>* fromState();
  const State<GlobalState>* toState();
private:
  void (*_executeFunction)(GlobalState*);
  bool (*_triggerFunction)(GlobalState*);
  const State<GlobalState>* _fromState;
  const State<GlobalState>* _toState;
};

template <class GlobalState>
Transition<GlobalState>::Transition(const State<GlobalState>* fromState, const State<GlobalState>* toState,
           bool (*triggerFunction)(GlobalState*), void (*executeFunction)(GlobalState*))
: _executeFunction(executeFunction)
, _triggerFunction(triggerFunction)
, _fromState(fromState)
, _toState(toState)
{
}

template <class GlobalState>
void Transition<GlobalState>::execute(GlobalState* globalState)
{
  if (_executeFunction != nullptr)
    _executeFunction(globalState);
}

template <class GlobalState>
bool Transition<GlobalState>::isTriggered(GlobalState* globalState)
{
  if (_triggerFunction == nullptr) {
    return true;
  } else {
    return _triggerFunction(globalState);
  }
}

template <class GlobalState>
const State<GlobalState>* Transition<GlobalState>::fromState()
{
  return _fromState;
}

template <class GlobalState>
const State<GlobalState>* Transition<GlobalState>::toState()
{
  return _toState;
}

#endif
