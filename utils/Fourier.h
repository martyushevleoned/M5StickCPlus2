#pragma once

#include <complex>
#include <vector>

namespace Utils {

class Fourier {

private:
  static std::vector<std::complex<double>> fft(std::vector<std::complex<double>> &samples) {

    const int N = samples.size();
    if (N == 1)
      return samples;

    const int evenN = N / 2;
    const int oddN = N - evenN;

    std::vector<std::complex<double>> xEven(evenN);
    std::vector<std::complex<double>> xOdd(oddN);

    for (int i = 0; i < evenN; i++)
      xEven[i] = samples[i * 2];
    for (int i = 0; i < oddN; i++)
      xOdd[i] = samples[i * 2 + 1];

    const std::vector<std::complex<double>> fEven = fft(xEven);
    const std::vector<std::complex<double>> fOdd = fft(xOdd);

    std::vector<std::complex<double>> frequencyBins(N);
    for (int i = 0; i < N; i++)
      frequencyBins[i] = fEven[i % evenN] + std::polar(1.0, -2.0 * M_PI * i / N) * fOdd[i % oddN];

    return frequencyBins;
  }

public:
  static std::vector<std::complex<double>> fft(std::vector<int32_t> &samples) {
    std::vector<std::complex<double>> complexSamples(samples.size());
    std::transform(samples.begin(), samples.end(), complexSamples.begin(), [](const double sample) {
      return std::complex<double>(sample, 0);
    });
    complexSamples = fft(complexSamples);
    return complexSamples;
  }

  static std::vector<double> fftA(std::vector<int32_t> &samples) {
    std::vector<std::complex<double>> complexSamples = fft(samples);
    std::vector<double> samplesA(complexSamples.size());
    std::transform(complexSamples.begin(), complexSamples.end(), samplesA.begin(), [](const std::complex<double> complexSample) {
      return sqrt(pow(complexSample.real(), 2) + pow(complexSample.imag(), 2));
    });
    return samplesA;
  }
};
}
