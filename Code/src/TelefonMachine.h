#include <LowPower.h>

#include "statemachine.h"
#include "mobile.h"
#include "fetap.h"

struct GlobalState
{
  String number;
  Mobile mobile;
  Fetap fetap;
  unsigned long tranisitionTime;
};

extern StateMachine<GlobalState>* telefonMachine;

void setupTelefonMachine();

const unsigned long maxIdleTime = 3000;
const unsigned long maxPhoneIdle = 10000;

// StateMachine setup
// global state for the StateMachine
