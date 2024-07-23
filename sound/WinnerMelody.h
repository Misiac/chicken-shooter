class WinnerMelody {
private:
  static const int MELODY_LENGTH = 13;
  static int frequencies[MELODY_LENGTH];
  static int durations[MELODY_LENGTH];

  WinnerMelody() {}  // Private constructor to prevent instantiation

public:
  static void play(Buzzer& buzzer) {
    for (int i = 0; i < MELODY_LENGTH; i++) {
      if (frequencies[i] > 0) {
        buzzer.turnOnWithFrequency(frequencies[i]);
        delay(durations[i]);
        buzzer.turnOff();
      } else {
        delay(durations[i]);  // Rest
      }
      delay(30);  // Short pause between notes
    }
  }
};

// Define the melody (frequencies in Hz, 0 for rest)
int WinnerMelody::frequencies[MELODY_LENGTH] = {
  587, 587, 587, 784, 
  784, 698, 698, 659, 659, 
  587, 784, 698, 587
};

// Define note durations (in milliseconds)
int WinnerMelody::durations[MELODY_LENGTH] = {
  200, 200, 200, 400, 
  400, 200, 200, 200, 200, 
  400, 200, 200, 600
};