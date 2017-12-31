

/* v1.2 +class State
        +class ScaleIn
        +class Average
        +class TimedAverage
        +class Threshold
        +class RecordMinMax
        +MotorH enumDir
        +MotorH Speed()
        +Timer enabled()
        +Timer elapsedTime()

   v1.1 +class MotorH
        +class Timer

   v1.0
*/


#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

/*
  Timer MyTimer = Timer();
  MyTimer.Interval(1000);
  MyTimer.Start();

  if (MyTimer.elapsed())
  { }
*/
class Timer
{
  public:
    Timer()
    {
      Reset();
    }

    Timer(bool autoreset)
    {
      _boAutoReset = autoreset;

      Reset();
    }

    Timer(bool autoreset, bool usemicros)
    {
      _boAutoReset = autoreset;
      _boUseMicros = usemicros;

      Reset();
    }

    void Interval(unsigned long interval)
    {
      _ulInterval = interval;
    }

    void Start()
    {
      _boEnabled = true;
    }

    void Stop()
    {
      _boEnabled = false;
    }

    bool enabled()
    {
      return _boEnabled;
    }

    void Reset()
    {
      _ulStartTime = _time();
    }

    bool elapsed()
    {
      return elapsed(_ulInterval);
    }

    bool elapsed(unsigned long interval)
    {
      if (_boEnabled == false)
      {
        return false;
      }
      else
      {
        if ((_time() - _ulStartTime) < interval)
        {
          return false;
        }
        else
        {
          if (_boAutoReset)
          {
            Reset();
          }

          return true;
        }
      }
    }

    unsigned long elapsedTime()
    {
      return _time() - _ulStartTime;
    }

  private:
    bool _boAutoReset = true;
    bool _boUseMicros = false;
    bool _boEnabled = false;
    unsigned long _ulInterval;
    unsigned long _ulStartTime;

    unsigned long _time()
    {
      if (_boUseMicros)
      {
        return micros();
      }
      else
      {
        return millis();
      }
    }
};

// edge detection
/*
  Edge MyEdge = Edge();
  if (MyEdge.rising(digitalRead(0)))
  { }
*/
class Edge
{
  public:
    Edge()
    {
      _boRising = true;
    }

    Edge(bool rising)
    {
      _boRising = rising;
    }

    bool rising(bool state)
    {
      if (state != _boOldState)
      {
        _boOldState = state;

        if (state == true)
        {
          return true;
        }
      }

      return false;
    }

    bool falling(bool state)
    {
      if (state != _boOldState)
      {
        _boOldState = state;

        if (state == false)
        {
          return true;
        }
      }

      return false;
    }

    bool edge(bool state)
    {
      if (state != _boOldState)
      {
        _boOldState = state;

        if ((state == _boRising) || (!state == !_boRising))
        {
          return true;
        }
      }

      return false;
    }

  private:
    bool _boRising;
    bool _boOldState = false;
};


bool timeOut(unsigned long starttime, unsigned long timeOut)
{
  if (millis() < starttime)
  {
    //Serial.println("overflow");
    starttime = 4294967295 - starttime;
  }

  if ((millis() - starttime) < timeOut)
  {
    /*Print("TimeOut: ");
      Print(millis() - starttime);
      Print(" / ");
      Print(timeOut);
      Println("ms");*/
    return false;
  }
  else
  {
    return true;
  }
}


class PushButton
{
  public:
    PushButton(unsigned int pin, unsigned long debounce, bool high)
    {
      _uiPin = pin;
      _ulDebounce = debounce;

      pinMode(_uiPin, INPUT);
      digitalWrite(_uiPin, high);
    }

    bool state()
    {
      if (digitalRead(_uiPin))
      {
        _ulTime = millis();

        return true;
      }


      if (timeOut(_ulTime, _ulDebounce))
      {
        return false;
      }
      else
      {
        return true;
      }
    }

  private:
    unsigned int _uiPin;
    unsigned long _ulDebounce;
    unsigned long _ulTime;
};


class Threshold
{
  public:
    Threshold()
    {
      _dblLastValue = 0.0;
    }

    double value(double in, double thres)
    {
      double dblTempMin = _dblLastValue - thres;
      double dblTempMax = _dblLastValue + thres;

      if (in < dblTempMin)
      {
        /*Serial.println("");
          Serial.println(_dblLastValue);
          Serial.println(dblTempMin);
          Serial.println(in);*/

        _dblLastValue = in;
      }

      if (in > dblTempMax)
      {
        /*Serial.println("");
          Serial.println(_dblLastValue);
          Serial.println(dblTempMax);
          Serial.println(in);*/

        _dblLastValue = in;
      }

      return _dblLastValue;
    }

  private:
    double _dblLastValue;
};


enum enumMotorDir
{
  MotorDir_STOP,
  MotorDir_FW,
  MotorDir_BW,
  MotorDir_BREAK
};

class MotorH
{
  public:
    MotorH(int pin1, int pin2, bool pwmenabled)
    {
      _intPin1 = pin1;
      _intPin2 = pin2;
      _boPWMenabled = pwmenabled;
      _bySpeed = 0;

      pinMode(_intPin1, OUTPUT);
      digitalWrite(_intPin1, LOW);

      pinMode(_intPin2, OUTPUT);
      digitalWrite(_intPin2, LOW);
    }

    void Speed(byte speed)
    {
      _bySpeed = speed;
    }

    void Dir(enumMotorDir dir)
    {
      Dir(dir, _bySpeed);
    }

    void Dir(enumMotorDir dir, byte speed)
    {
      _bySpeed = speed;

      switch (dir)
      {
        default:
        case MotorDir_STOP:
          if (_boPWMenabled)
          {
            analogWrite(_intPin1, 0);
            analogWrite(_intPin2, 0);
          }
          else
          {
            digitalWrite(_intPin1, LOW);
            digitalWrite(_intPin2, LOW);
          }
          break;

        case MotorDir_FW:
          if (_boPWMenabled)
          {
            analogWrite(_intPin1, _bySpeed);
            analogWrite(_intPin2, 0);
          }
          else
          {
            digitalWrite(_intPin1, HIGH);
            digitalWrite(_intPin2, LOW);
          }
          break;

        case MotorDir_BW:
          if (_boPWMenabled)
          {
            analogWrite(_intPin1, 0);
            analogWrite(_intPin2, _bySpeed);
          }
          else
          {
            digitalWrite(_intPin1, LOW);
            digitalWrite(_intPin2, HIGH);
          }
          break;

        case MotorDir_BREAK:
          if (_boPWMenabled)
          {
            analogWrite(_intPin1, 255);
            analogWrite(_intPin2, 255);
          }
          else
          {
            digitalWrite(_intPin1, HIGH);
            digitalWrite(_intPin2, HIGH);
          }
          break;
      }
    }

  private:
    int _intPin1;
    int _intPin2;
    bool _boPWMenabled;
    byte _bySpeed;
};

// scale integer value to double
/*
  ScaleIn MyScaleIn = ScaleIn();
  MyScaleIn.ConfigIn(0, 1023);
  MyScaleIn.ConfigOut(0.0, 0.0, 100.0);

  double value = MyScaleIn.value(analogRead(A0));
*/
class ScaleIn
{
  public:
    ScaleIn()
    {}

    ConfigIn(int inmin, int inmax)
    {
      _intInMin = inmin;
      _intInMax = inmax;
    }

    ConfigOut(double outoffset, double outmin, double outmax)
    {
      _dblOutOffset = outoffset;
      _dblOutMin = outmin;
      _dblOutMax = outmax;
    }

    double value(int in)
    {
      // map IN to OUT
      double dblRet = map(in, _intInMin, _intInMax, _dblOutMin, _dblOutMax);
      // offset
      dblRet = map(dblRet, _dblOutMin - _dblOutOffset, _dblOutMax - _dblOutOffset, _dblOutMin, _dblOutMax);
      // check min/max range
      if (dblRet < 0.0)
      {
        dblRet = 0.0;
      }
      else if (dblRet > 100.0)
      {
        dblRet = 100.0;
      }

      return dblRet;
    }

  private:
    int _intInMin;
    int _intInMax;
    double _dblOutOffset;
    double _dblOutMin;
    double _dblOutMax;
};


class Average
{
  public:
    Average(int size)
    {
      _intSize = size;

      if (_intSize > 10)
      {
        _intSize = 10;
      }
    }

    void Put(double val)
    {
      for (int i = _intSize - 1; i >= 0; i -= 1)
      {
        _dblArray[i] = _dblArray[i - 1];
      }

      _dblArray[0] = val;
    }

    double value()
    {
      double dblRet = 0.0;

      for (int i = 0; i < _intSize; i += 1)
      {
        dblRet += _dblArray[i];
      }

      dblRet = dblRet / _intSize;

      /*Serial.println("");
        Serial.println(dblRet);*/

      return dblRet;
    }

  private:
    int _intSize;
    double _dblArray[10];
};


class TimedAverage
{
  public:
    TimedAverage(int size, unsigned int time)
    {
      _intSize = size;
      _uintTime = time;

      if (_intSize > 10)
      {
        _intSize = 10;
      }
    }

    void Put(double val)
    {
      for (int i = _intSize - 1; i >= 0; i -= 1)
      {
        _valuesArray[i] = _valuesArray[i - 1];
      }

      _valuesArray[0].dblValue = val;
      _valuesArray[0].uintTime = millis();
    }

    double value()
    {
      // replace old entries
      unsigned int uintNow = millis();

      for (int i = _intSize - 1; i >= 1; i -= 1)
      {
        if (_valuesArray[i].uintTime <= uintNow - _uintTime)
        {
          _valuesArray[i].dblValue = _valuesArray[i - 1].dblValue;
          _valuesArray[i].uintTime = uintNow;
        }
      }


      double dblRet = 0.0;

      for (int i = 0; i < _intSize; i += 1)
      {
        dblRet += _valuesArray[i].dblValue;
      }

      dblRet = dblRet / _intSize;

      return dblRet;
    }

  private:
    int _intSize;
    unsigned int _uintTime;

    struct struValues
    {
      double dblValue;
      unsigned int uintTime;
    } _valuesArray[10];
};


class RecordMinMax
{
  public:
    RecordMinMax()
    {
      _dblMin = 0.0;
      _dblMax = 0.0;
    }

    void Reset()
    {
      _dblMin = 0.0;
      _dblMax = 0.0;
    }

    void Put(double in)
    {
      if (in < _dblMin)
      {
        _dblMin = in;
      }

      if (in > _dblMax)
      {
        _dblMax = in;
      }
    }

    double minValue()
    {
      return _dblMin;
    }

    double maxValue()
    {
      return _dblMax;
    }

  private:
    double _dblMin;
    double _dblMax;
};


bool checkRange(double val, double minVal, double maxVal)
{
  if (val < minVal)
  {
    return false;
  }
  else if (val > maxVal)
  {
    return false;
  }
  else
  {
    return true;
  }
}


double mapd(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* Type:
 * Error = 0..49
 * Warning = 50..99
 * Info = 100
 * 
 * Sender:
 * Sensors = 100..149
 * 
 */

enum enumStates
{
  State_ERROR,
  State_WARNING,
  State_INFO
};

class State
{
  public:
    State()
    { }

    void Clear()
    {
      for (int i = 0; i < _cintArraySize; i += 1)
      {
        _stateArray[i].bySender = 0;
      }
    }

    void Put(byte type, byte sender, int id, char *str)
    {
      for (int i = _cintArraySize - 1; i >= 0; i -= 1)
      {
        _stateArray[i] = _stateArray[i - 1];
      }

      _stateArray[0].ulTime = millis();
      _stateArray[0].byType = type;
      _stateArray[0].bySender = sender;
      _stateArray[0].intID = id;
      _stateArray[0].str = str;
    }

    void Write()
    {
      for (int i = _cintArraySize - 1; i >= 0; i -= 1)
      {
        if (_stateArray[i].bySender != 0)
        {
          Serial.print("t: ");
          Serial.print(_stateArray[i].ulTime);
          Serial.print("\t");

          if (_stateArray[i].byType == State_ERROR)
          {
            Serial.print("E\t");
          }
          else if (_stateArray[i].byType == State_WARNING)
          {
            Serial.print("W\t");
          }
          else if (_stateArray[i].byType == State_INFO)
          {
            Serial.print("I\t");
          }
          else
          {
            Serial.print("\t");
          }

          Serial.print("s: ");
          Serial.print(_stateArray[i].bySender);
          Serial.print("\t");

          Serial.print("(");
          Serial.print(_stateArray[i].intID);
          Serial.print(") ");

          Serial.println(_stateArray[i].str);
        }
      }
    }

    bool noError()
    {
      for (int i = 0; i < _cintArraySize; i += 1)
      {
        if (_stateArray[i].bySender != 0)
        {
          if (_stateArray[i].byType == 0)
          {
            return false;
          }
        }
      }

      return true;
    }

  private:
    const int _cintArraySize = 3;

    struct struState
    {
      unsigned long ulTime;
      byte byType;
      byte bySender;
      int intID;
      char *str;
    } _stateArray[3];
};


// Calculate tilt compensated compass heading
// mag componentes and roll/pitch should be in APM2.0 axis reference (X front, Y right, Z down)
// In this function we used some optimizations based on dcm matrix
/*float heading(struMPU in, float mag_x, float mag_y, float mag_z, float declination)
  {
  float headX;
  float headY;
  float heading;
  float cos_pitch = sqrt(1 - (in.DCM[2][0] * in.DCM[2][0]));

  // Tilt compensated magnetic field X component:
  // headX = mag_x*cos_pitch + mag_y*sin_roll*sin_pitch + mag_z*cos_roll*sin_pitch;
  headX = mag_x * cos_pitch - mag_y * in.DCM[2][1] * in.DCM[2][0] / cos_pitch - mag_z * in.DCM[2][2] * in.DCM[2][0] / cos_pitch;

  // Tilt compensated magnetic field Y component:
  //headY = mag_y*cos_roll - mag_z*sin_roll;
  headY = mag_y * in.DCM[2][2] / cos_pitch - mag_z * in.DCM[2][1] / cos_pitch;

  // magnetic heading
  heading = 180.0 * atan2(headY, headX) / PI;
  if (headY >= 0.0)
    return heading;
  else
    return (360.0 + heading);

  // Declination correction (if supplied)
  // if(fabs(declination) > 0.0 ){
  //     heading = _normalize_angle(heading + declination);
  // }
  }*/

