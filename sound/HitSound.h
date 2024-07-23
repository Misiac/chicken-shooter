class HitSound {
private:
  static int hitBeepFrequency;
  static int hitBeepDuration;

  HitSound() {}

public:
  static void play(Buzzer& buzzer) {
    buzzer.turnOnWithFrequency(hitBeepFrequency);
    delay(hitBeepDuration);
    buzzer.turnOff();
  }
};

int HitSound::hitBeepFrequency = 1400;
int HitSound::hitBeepDuration = 100;