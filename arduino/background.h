

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

    // StepUp control
    if (true == true)
    {
      // auto turn off StepUp
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

      if (boDebugger)
      {
        boStepUpEnabled = true;
      }
    }

    // analog sensor control
    if (true == false)
    {
      if (moveSumo != STOP)
      {
        boAnalogEnabled = true;
      }
      else
      {
        boAnalogEnabled = false;
      }
    }

    // line detection
    if (true == true)
    {
      lineSensor = Line_NONE;

      if (dblLeft > 50.0 && dblRight > 50.0)
      {
        if (dblLeft > dblRight)
        {
          lineSensor = Line_LEFT;
        }
        else
        {
          lineSensor = Line_RIGHT;
        }
      }
      else if (dblLeft > 50.0)
      {
        lineSensor = Line_LEFT;
      }
      else if (dblRight > 50.0)
      {
        lineSensor = Line_RIGHT;
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
