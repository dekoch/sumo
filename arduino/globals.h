

bool boDebugger = false;
State state = State();
bool boError = false;

unsigned int uintStep = 0;
bool boStepUpEnabled = false;
bool boDistEnabled = true;
bool boAnalogEnabled = true;
int intDistance = 9999;

int intTest = 0;

double dblLeft;
double dblFront;
double dblRight;
double dblBack;

bool boLoadSettings = false;
bool boSaveSettings = false;

enum enumLine
{
  Line_NONE,
  Line_FRONT,
  Line_LEFT,
  Line_RIGHT,
  Line_BACK
} lineSensor = Line_NONE;

enum enumMove
{
  STOP,
  FWD,
  BWD,
  BREAK,
  LEFT,
  SEARCHLEFT,
  TURNLEFT,
  RIGHT,
  SEARCHRIGHT,
  TURNRIGHT
} moveSumo = STOP;

enum enumState
{
  State_Undefined,
  State_Starting,
  State_Ready,
  State_Loop,
  State_Standbye
} stateBoard = State_Undefined;

Timer timerCycle = Timer(false, true);
unsigned long ulTimeCycle = 0;
