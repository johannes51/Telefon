#ifndef STATE_H
#define STATE_H

template <class GlobalState>
class State
{
public:
  State(void (*executeFunction)(GlobalState*));

  void execute(GlobalState* globalState);
  void (*_executeFunction)(GlobalState*);
private:
};

template <class GlobalState>
State<GlobalState>::State(void (*executeFunction)(GlobalState*))
: _executeFunction(executeFunction)
{
}

template <class GlobalState>
void State<GlobalState>::execute(GlobalState* globalState)
{
  if (_executeFunction != nullptr)
    _executeFunction(globalState);
}

#endif
