class TimerMelody {
private:
  static int countdownBeepFrequency;
  static int countdownBeepDuration;
  static int startBeepFrequency;
  static int startBeepDuration;

  TimerMelody() {}

public:
  static void play(Buzzer& buzzer) {
    for (int i = 3; i > 0; i--) {
      buzzer.turnOnWithFrequency(countdownBeepFrequency);
      delay(countdownBeepDuration);
      buzzer.turnOff();
      delay(1000 - countdownBeepDuration);
    }

    buzzer.turnOnWithFrequency(startBeepFrequency);
    delay(startBeepDuration);
    buzzer.turnOff();
  }
};

int TimerMelody::countdownBeepFrequency = 1000;
int TimerMelody::countdownBeepDuration = 500;
int TimerMelody::startBeepFrequency = 2000;
int TimerMelody::startBeepDuration = 500;