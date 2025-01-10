#include <vector>
#pragma once

#include "../MenuItem.h"
#include "../../utils/Fourier.h"

namespace Main {

class Spectroid : public MenuItem {

public:
  Spectroid()
    : MenuItem("Spectroid") {
  }

  void run() override {

    int height = 0;
    int offset = 3;
    int countOfSamples = stick->lcd.width();
    stick->lcd.fillScreen(BLACK);

    while (true) {

      std::vector<double> rawSpectrumA = Utils::Fourier::fftA(stick->mic.getSamples(512));
      std::vector<double> spectrumA(rawSpectrumA.begin() + offset, rawSpectrumA.begin() + countOfSamples + offset);
      double maxValue = *(std::max_element(std::begin(spectrumA), std::end(spectrumA)));

      for (int i = 0; i < countOfSamples; i++)
        stick->lcd.drawPixel(i, height, BLUE, spectrumA[i] / maxValue * 255, BLACK);
      height = (height + 1) % stick->lcd.height();
      stick->lcd.drawFastHLine(0, height, stick->lcd.width(), BLACK);

      tick();
      if (exitTrigger())
        return;
    }
  }
};

}
