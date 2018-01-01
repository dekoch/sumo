
#define VERSION 1.0
#define BOARD_SUMO_1_1712
#define BOARD_SUMO_OPT_1_0

#include <EEPROM.h>
#include <Wire.h>
#include <VL53L0X.h> // https://github.com/pololu/vl53l0x-arduino

#include "arduino/config.h"
#include "arduino/boards.h"
#include "arduino/util.h"
#include "arduino/globals.h"
#include "arduino/state.h"
#include "arduino/hw_in.h"
#include "arduino/hw_out.h"
#include "arduino/background.h"
//#include "arduino/a_sumo.h"
#include "arduino/a_sumo_test.h"

Settings sett;
BoardState boardstate;
HardwareInputs hw_in;
HardwareOutputs hw_out;
Background bg;
Sumo sumo;

bool boState = false;

void setup()
{
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");

  boardstate.setup();
  boardstate.SetState(State_Starting);

  Wire.begin();

  sett.setup();

  if (boLoadSettings)
  {
    boLoadSettings = false;

    if (sett.load() == false)
    {
      while (true)
        ;
    }
  }

  hw_out.setup();
  hw_in.setup();
  bg.setup();
  sumo.setup();

  timerCycle.Interval(2000);
  timerCycle.Start();

  boardstate.SetState(State_Ready);
  boardstate.SetState(State_Loop);
}

void loop()
{
  timerCycle.Reset();

  hw_in.loop();

  bg.loop();

  if (boState)
  {
    boardstate.loop();
  }

  sumo.loop();

  hw_out.loop();

  // load/save settings
  if (boLoadSettings)
  {
    boLoadSettings = false;

    sett.load();
  }

  if (boSaveSettings)
  {
    boSaveSettings = false;

    sett.save();
  }

  // cycle time monitoring
  if (boState == false)
  {
    ulTimeCycle = timerCycle.elapsedTime();

    if (timerCycle.elapsed()) // 2ms
    {
      state.Put(State_WARNING, 1, 1, "Cyc");
    }
  }

  boState = !boState;

  digitalWrite(pinLED1, !digitalRead(pinLED1));
}
