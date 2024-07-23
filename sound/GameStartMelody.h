class GameStartMelody {
private:
  static const int MELODY_LENGTH = 5;
  static int frequencies[MELODY_LENGTH];
  static int durations[MELODY_LENGTH];

  GameStartMelody() {}  // Private constructor to prevent instantiation

public:
  static void play(Buzzer& buzzer) {
    for (int i = 0; i < MELODY_LENGTH; i++) {
      buzzer.turnOnWithFrequency(frequencies[i]);
      delay(durations[i]);
      buzzer.turnOff();
      delay(50);
    }
  }
};

// Define the melody (frequencies in Hz)
int GameStartMelody::frequencies[MELODY_LENGTH] = {523, 659, 784, 659, 1047};

// Define note durations (in milliseconds)
int GameStartMelody::durations[MELODY_LENGTH] = {200, 200, 200, 200, 400};

