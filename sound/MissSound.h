class MissSound {
private:
  static const int SOUND_LENGTH = 2;
  static int frequencies[SOUND_LENGTH];
  static int durations[SOUND_LENGTH];

  MissSound() {}  // Private constructor to prevent instantiation

public:
  static void play(Buzzer& buzzer) {
    for (int i = 0; i < SOUND_LENGTH; i++) {
      buzzer.turnOnWithFrequency(frequencies[i]);
      delay(durations[i]);
      buzzer.turnOff();
      if (i < SOUND_LENGTH - 1) {
        delay(50);  // Short pause between notes
      }
    }
  }
};

// Define the sound (frequencies in Hz)
int MissSound::frequencies[SOUND_LENGTH] = { 330, 220 };

// Define sound durations (in milliseconds)
int MissSound::durations[SOUND_LENGTH] = { 200, 400 };