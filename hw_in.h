

class HardwareInputs
{
public:
  void setup()
  {
    pinMode(pinDebug, INPUT);

    digitalWrite(pinDebug, HIGH);

    _vl53.init();
    _vl53.setTimeout(500);
    _vl53.startContinuous();

    intDistance = _vl53.readRangeContinuousMillimeters();

    if (intDistance < 0)
    {
      state.Put(State_ERROR, 100, 53, "LV");

      boDistEnabled = false;
    }

    _timerVL53.Interval(0);
    _timerVL53.Start();

    _scinLeft.ConfigIn(0, 1023);
    _scinRight.ConfigIn(0, 1023);

    _scinLeft.ConfigOut(settings.aLeft.dblOffset, settings.aLeft.dblMin, settings.aLeft.dblMax);
    //_scinFront.ConfigOut(settings.aFront.dblOffset, settings.aFront.dblMin, settings.aFront.dblMax);
    _scinRight.ConfigOut(settings.aRight.dblOffset, settings.aRight.dblMin, settings.aRight.dblMax);
    //_scinBack.ConfigOut(settings.aBack.dblOffset, settings.aBack.dblMin, settings.aBack.dblMax);
  }

  void loop()
  {
    //boDebugger = digitalRead(pinDebug);

    dblLeft = _scinLeft.value(analogRead(pinLineLeft)); // 300us
    _avgLeft.Put(dblLeft);

    dblLeft = _avgLeft.value();
    //dblLeft = _thresLeft.value(dblLeft, 3.0);

    dblRight = _scinRight.value(analogRead(pinLineRight));
    _avgRight.Put(dblRight);

    dblRight = _avgRight.value();
    //dblRight = _thresRight.value(dblRight, 3.0);

    if (boDistEnabled)
    {
      if (_timerVL53.elapsed())
      {
        if (_vl53.timeoutOccurred() == false)
        {
          intDistance = _vl53.readRangeContinuousMillimeters();

          if (intDistance < 0)
          {
            state.Put(State_ERROR, 100, 153, "LV");
          }
        }
        else
        {
          intDistance = 9999;
        }

        if (checkRange(intDistance, 0.0, 500.0) == false)
        {
          intDistance = 9999;
        }
      }
    }
    else
    {
      intDistance = 9999;
    }
  }

private:
  Timer _timerVL53 = Timer();

  VL53L0X _vl53;

  ScaleIn _scinLeft = ScaleIn();
  ScaleIn _scinFront = ScaleIn();
  ScaleIn _scinRight = ScaleIn();
  ScaleIn _scinBack = ScaleIn();

  TimedAverage _avgLeft = TimedAverage(5, 100);
  TimedAverage _avgRight = TimedAverage(5, 100);

  Threshold _thresLeft = Threshold();
  Threshold _thresRight = Threshold();
};
