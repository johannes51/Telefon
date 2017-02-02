#ifndef STATE_H
#define STATE_H

template <class GlobalState>
class State
{
public:
  State(void (*executeFunction)(GlobalState*));

  void execute(GlobalState* globalState);
private:
    void (*_executeFunction)(GlobalState*);
};

template <class GlobalState>
State<GlobalState>::State(void (*executeFunction)(GlobalState*))
: _executeFunction(executeFunction)
{
}

template <class GlobalState>
void State<GlobalState>::execute(GlobalState* globalState)
{
  if (_executeFunction != 0)
    _executeFunction(globalState);
}

#endif
