

class HardwareOutputs
{
  public:
    void setup()
    {
      pinMode(pinSteUpEN, OUTPUT);

      digitalWrite(pinSteUpEN, HIGH);
    }


    void loop()
    {
      if (boError)
      {
        moveSumo = STOP;
      }
      
      if (boStepUpEnabled)
      {
        //digitalWrite(pinSteUpEN, HIGH);

        switch (moveSumo)
        {
          default:
          case STOP:
            _motorLeft.Dir(MotorDir_STOP);
            _motorRight.Dir(MotorDir_STOP);
            break;

          case  FWD:
            _motorLeft.Dir(MotorDir_FW, settings.bySpeedMaxLeft);
            _motorRight.Dir(MotorDir_FW, settings.bySpeedMaxRight);
            break;

          case  BWD:
            _motorLeft.Dir(MotorDir_BW, settings.bySpeedMaxLeft);
            _motorRight.Dir(MotorDir_BW, settings.bySpeedMaxRight);
            break;

          case  BREAK:
            _motorLeft.Dir(MotorDir_BREAK);
            _motorRight.Dir(MotorDir_BREAK);
            break;

          case  LEFT:
            _motorLeft.Dir(MotorDir_FW, settings.bySpeedSlowLeft);
            _motorRight.Dir(MotorDir_FW, settings.bySpeedMaxRight);
            break;

          case  SEARCHLEFT:
            _motorLeft.Dir(MotorDir_BW, settings.bySpeedSlowLeft);
            _motorRight.Dir(MotorDir_FW, settings.bySpeedSlowRight);
            break;
            
          case  TURNLEFT:
            _motorLeft.Dir(MotorDir_BW, settings.bySpeedMaxLeft);
            _motorRight.Dir(MotorDir_FW, settings.bySpeedMaxRight);
            break;

          case  RIGHT:
            _motorLeft.Dir(MotorDir_FW, settings.bySpeedMaxLeft);
            _motorRight.Dir(MotorDir_FW, settings.bySpeedSlowRight);
            break;

          case  SEARCHRIGHT:
            _motorLeft.Dir(MotorDir_FW, settings.bySpeedSlowLeft);
            _motorRight.Dir(MotorDir_BW, settings.bySpeedSlowRight);
            break;
            
          case  TURNRIGHT:
            _motorLeft.Dir(MotorDir_FW, settings.bySpeedMaxLeft);
            _motorRight.Dir(MotorDir_BW, settings.bySpeedMaxRight);
            break;
        }
      }
      else
      {
        //digitalWrite(pinSteUpEN, LOW);
      }
    }

  private:
    MotorH _motorLeft = MotorH(pinMotA1, pinMotA2, true);
    MotorH _motorRight = MotorH(pinMotB1, pinMotB2, true);
};


