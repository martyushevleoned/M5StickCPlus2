#pragma once

#include "../MenuItem.h"
#include "../../utils/Fourier.h"

namespace Main {

class Tuner : public MenuItem {

public:
  Tuner()
    : MenuItem("Tuner") {
  }

  void run() override {

    int offset = 3;
    stick->lcd.setTextSize(3);

    while (true) {

      std::vector<double> spectrumA = Utils::Fourier::fftA(stick->mic.getSamples(SAMPLE_BUFFER_SIZE));
      int indexOfMaxFrequency = std::distance(std::begin(spectrumA), std::max_element(std::begin(spectrumA) + offset, std::begin(spectrumA) + SAMPLE_BUFFER_SIZE / 2));
      String output = String(SAMPLE_RATE * indexOfMaxFrequency / 512) + " Hz";

      stick->lcd.fillScreen(BLACK);
      stick->lcd.setWidthScaledTextSize(output);
      stick->lcd.printCenter(output);

      tick();
      if (exitTrigger())
        return;
    }
  }
};

}
