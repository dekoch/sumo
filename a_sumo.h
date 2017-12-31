

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
      if (lineSensor != Line_NONE)
      {
        if (uintStep >= 100 && uintStep < 199)
        {
          moveSumo = BREAK;

          _Step(0, 0);
        }
      }


      if (_timerStep.elapsed())
      {
        uintStep = _uintNextStep;

        switch (uintStep)
        {
          case 0:
            _NextStep(0);
            break;

          case 10:
            if (lineSensor == Line_NONE)
            {
              _Step(100, 0);
            }
            else
            {
              _Step(200, 0);
            }
            break;


          case 100:
            moveSumo = SEARCHRIGHT;

            _NextStep(0);
            break;

          case 110:
            if (intDistance < 200)
            {
              moveSumo = TURNLEFT;

              _NextStep(200);
            }
            break;

          case 120:
            moveSumo = FWD;
            break;


          case 200:
            moveSumo = BWD;

            _NextStep(0);
            break;

          case 210:
            if (lineSensor == Line_NONE)
            {
              _NextStep(1000);
            }
            break;

          case 220:
            moveSumo = BREAK;

            _NextStep(0);
            break;


          default:
          case 999:
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


