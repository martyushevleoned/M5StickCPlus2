#pragma once

#include "../MenuItem.h"
#include "../../utils/Fourier.h"

namespace Main {

class Tuner : public MenuItem {

private:
  const float MAIN_TONE = 16.352;  // C0
  const float BASE = pow(2., 1. / 12.);
  const String NOTES[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

public:
  Tuner()
    : MenuItem("Tuner") {
  }

  void run() override {

    int offset = 5;
    int countOfSamples = 4048;
    stick->lcd.setTextSize(4);

    while (true) {

      std::vector<double> spectrumA = Utils::Fourier::fftA(stick->mic.getSamples(countOfSamples));
      int indexOfMaxFrequency = std::distance(std::begin(spectrumA), std::max_element(std::begin(spectrumA) + offset, std::begin(spectrumA) + countOfSamples / 2));

      float frequency = stick->mic.getSampleRate() * indexOfMaxFrequency / countOfSamples;
      float logValue = log(frequency / MAIN_TONE) / log(BASE);
      int roundedLogValue = round(logValue);

      int octave = roundedLogValue / 12;
      int note = roundedLogValue % 12;
      int cent = (int)(logValue * 100) - roundedLogValue * 100;

      stick->lcd.fillScreen(BLACK);
      stick->lcd.printCenter(NOTES[note] + String(octave), stick->lcd.width() / 2, stick->lcd.height() / 3);
      stick->lcd.printCenter(String(cent) + "c", stick->lcd.width() / 2, stick->lcd.height() * 2 / 3);

      tick();
      if (exitTrigger())
        return;
    }
  }
};

}
