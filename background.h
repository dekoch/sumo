

class Background
{
  public:
    void setup()
    {
      _timerStandby.Interval(5000);
    }


    void loop()
    {
      boError = !state.noError();

      // auto turn off StepUp
      if (true == true)
      {
        if (moveSumo == STOP && _timerStandby.enabled() == false)
        {
          _timerStandby.Reset();
          _timerStandby.Start();
        }

        if (moveSumo != STOP)
        {
          _timerStandby.Stop();

          boStepUpEnabled = true;
        }

        if (_timerStandby.elapsed())
        {
          _timerStandby.Stop();

          boStepUpEnabled = false;
        }
      }

      // line detection
      if (true == true)
      {
        if (dblLeft < dblRight)
        {
          lineSensor = Line_LEFT;
        }
        else if (dblLeft > dblRight)
        {
          lineSensor = Line_RIGHT;
        }
        else
        {
          lineSensor = Line_NONE;
        }
      }

      // distance sensor control
      if (true == false)
      {
        if (moveSumo == SEARCHLEFT || moveSumo == SEARCHRIGHT)
        {
          boDistEnabled = true;
        }
        else
        {
          boDistEnabled = false;
        }
      }
    }

  private:
    Timer _timerStandby = Timer(false);

};


