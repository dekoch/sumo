

class Sumo
{
  public:
    void setup()
    {
      _Step(0, 0);

      _timerStep.Start();
    }


    void loop()
    {
      if (_timerStep.elapsed())
      {
        uintStep = _uintNextStep;

        switch (uintStep)
        {
          case 0:
            _NextStep(10000);
            break;

          case 10:
            moveSumo = FWD;

            _NextStep(5000);
            break;

          case 20:
            moveSumo = BWD;

            _NextStep(5000);
            break;

          case 30:
            moveSumo = BREAK;

            _NextStep(5000);
            break;

          case 40:
            moveSumo = LEFT;

            _NextStep(5000);
            break;

          case 50:
            moveSumo = SEARCHLEFT;

            _NextStep(5000);
            break;

          case 60:
            moveSumo = TURNLEFT;

            _NextStep(5000);
            break;

          case 70:
            moveSumo = BREAK;

            _NextStep(5000);
            break;

          case 80:
            moveSumo = RIGHT;

            _NextStep(5000);
            break;

          case 90:
            moveSumo = SEARCHRIGHT;

            _NextStep(5000);
            break;

          case 100:
            moveSumo = TURNRIGHT;

            _NextStep(5000);
            break;

          default:
          case 110:
            moveSumo = STOP;

            _Step(0, 0);
            break;
        }
      }
    }

  private:
    unsigned int _uintNextStep = 0;
    Timer _timerStep = Timer();

    void _NextStep(unsigned long time)
    {
      _uintNextStep += 10;
      _timerStep.Interval(time);
    }

    void _Step(unsigned int step, unsigned long time)
    {
      _uintNextStep = step;
      _timerStep.Interval(time);
    }

};


