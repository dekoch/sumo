

struct struAnalog
{
  double dblOffset;
  double dblMin;
  double dblMax;
};

struct struSettings
{
  byte bySpeedSlowLeft;
  byte bySpeedSlowRight;
  byte bySpeedMaxLeft;
  byte bySpeedMaxRight;

  struAnalog aLeft;
  struAnalog aFront;
  struAnalog aRight;
  struAnalog aBack;
} settings;


class Settings
{
  public:
    setup()
    {
      settings.bySpeedSlowLeft = 255;
      settings.bySpeedSlowRight = 255;
      settings.bySpeedMaxLeft = 255;
      settings.bySpeedMaxRight = 255;
      

      settings.aLeft.dblOffset = 0.0;
      settings.aLeft.dblMin = 0.0;
      settings.aLeft.dblMax = 100.0;

      settings.aFront.dblOffset = 0.0;
      settings.aFront.dblMin = 0.0;
      settings.aFront.dblMax = 100.0;

      settings.aRight.dblOffset = 0.0;
      settings.aRight.dblMin = 0.0;
      settings.aRight.dblMax = 100.0;

      settings.aBack.dblOffset = 0.0;
      settings.aBack.dblMin = 0.0;
      settings.aBack.dblMax = 100.0;
    }

    bool load()
    {
      Serial.println("load EE");
      
      int intConfig;
      int intEEConfig;

      // check overall config size
      intConfig = sizeof(settings)
                  + (sizeof(int) * 4); // 4x length checksum

      int intAddress = 0;

      // Config
      intConfig = sizeof(settings);

      EEPROM.get(intAddress, intEEConfig);
      intAddress += sizeof(int);

      if (intConfig != intEEConfig)
      {
        return false;
      }

      EEPROM.get(intAddress, settings);
      intAddress += sizeof(settings);
      // Config

      return true;
    }

    bool save()
    {
      Serial.println("save EE");
      
      int intConfig;

      // check overall config size
      intConfig = sizeof(settings)
                  + (sizeof(int) * 4); // 4x length checksum

      if (intConfig >= EEPROM.length())
      {
        return false;
      }

      int intAddress = 0;

      // Config
      intConfig = sizeof(settings);

      EEPROM.put(intAddress, intConfig);
      intAddress += sizeof(int);

      EEPROM.put(intAddress, settings);
      intAddress += sizeof(settings);
      // Config

      return true;
    }
};


