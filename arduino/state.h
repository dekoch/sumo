

class BoardState
{
public:
  void setup()
  {
    pinMode(pinLED1, OUTPUT);
    pinMode(pinLED2, OUTPUT);

    digitalWrite(pinLED1, LOW);
    digitalWrite(pinLED2, LOW);

    _timerLED.Interval(200);
    _timerLED.Start();

    _timerInfo.Interval(500);
    _timerInfo.Start();
  }

  void loop()
  {
    if (stateBoard != _stateBoardOld)
    {
      _stateBoardOld = stateBoard;

      Serial.print("State:\t");

      switch (stateBoard)
      {
      case State_Starting:
        Serial.println("starting...");

        digitalWrite(pinLED1, HIGH);
        digitalWrite(pinLED2, LOW);

        delay(500);
        break;

      case State_Ready:
        Serial.println("ready");

        digitalWrite(pinLED1, HIGH);
        digitalWrite(pinLED2, HIGH);

        delay(500);

        digitalWrite(pinLED1, LOW);
        digitalWrite(pinLED2, LOW);

        delay(500);

        digitalWrite(pinLED1, HIGH);
        digitalWrite(pinLED2, HIGH);

        delay(1500);
        break;

      case State_Loop:
        Serial.println("loop");

        digitalWrite(pinLED1, LOW);
        digitalWrite(pinLED2, LOW);
        break;
      }
    }

    if (_timerLED.elapsed())
    {
      digitalWrite(pinLED2, !digitalRead(pinLED2));
    }

    if (_timerInfo.elapsed())
    {
      Serial.println("");

      Serial.print("Uptime:\t");
      Serial.println(millis());

      Serial.print("Cycle:\t");
      Serial.println(ulTimeCycle);

      Serial.print("Step:\t");
      Serial.println(uintStep);

      Serial.print("StepUp:\t");
      Serial.println(boStepUpEnabled);

      ShowMoveState();

      Serial.print("Distance:\t");
      Serial.println(intDistance);

      Serial.print(dblLeft);
      Serial.print("\t");
      Serial.print(dblFront);
      Serial.print("\t");
      Serial.print(dblRight);
      Serial.print("\t");
      Serial.println(dblBack);

      Serial.print("Line:\t");
      if (lineSensor == Line_NONE)
      {
        Serial.println("N");
      }
      else if (lineSensor == Line_LEFT)
      {
        Serial.println("L");
      }
      else if (lineSensor == Line_RIGHT)
      {
        Serial.println("R");
      }

      state.Write();
    }
  }

  void SetState(enumState s)
  {
    stateBoard = s;

    _timerInfo.Reset();

    loop();
  }

  void ShowMoveState()
  {
    Serial.print("Move:\t");

    switch (moveSumo)
    {
    default:
      Serial.println("undefined");
      break;

    case STOP:
      Serial.println("STOP");
      break;

    case FWD:
      Serial.println("FWD");
      break;

    case BWD:
      Serial.println("BWD");
      break;

    case BREAK:
      Serial.println("BREAK");
      break;

    case LEFT:
      Serial.println("LEFT");
      break;

    case SEARCHLEFT:
      Serial.println("SEARCHLEFT");
      break;

    case TURNLEFT:
      Serial.println("TURNLEFT");
      break;

    case RIGHT:
      Serial.println("RIGHT");
      break;

    case SEARCHRIGHT:
      Serial.println("SEARCHRIGHT");
      break;

    case TURNRIGHT:
      Serial.println("TURNRIGHT");
      break;
    }
  }

private:
  Timer _timerLED = Timer();
  Timer _timerInfo = Timer();
  enumState _stateBoardOld = State_Undefined;
};
