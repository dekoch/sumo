

struct struAnalog
{
  int intMin;
  int intMax;
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
    settings.bySpeedSlowLeft = 20;
    settings.bySpeedSlowRight = 20;
    settings.bySpeedMaxLeft = 50;
    settings.bySpeedMaxRight = 50;

    settings.aLeft.intMin = 180;
    settings.aLeft.intMax = 240;

    settings.aFront.intMin = 0;
    settings.aFront.intMax = 100;

    settings.aRight.intMin = 0;
    settings.aRight.intMax = 100;

    settings.aBack.intMin = 0;
    settings.aBack.intMax = 100;
  }

  bool load()
  {
    Serial.println("load EE");

    int intConfig;
    int intEEConfig;

    // check overall config size
    intConfig = sizeof(settings) + (sizeof(int) * 4); // 4x length checksum

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
    intConfig = sizeof(settings) + (sizeof(int) * 4); // 4x length checksum

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
