#pragma once

#include <complex>
#include <vector>

namespace Utils {

class Fourier {

private:
  static std::vector<std::complex<double>> dft(const std::vector<std::complex<double>> &samples) {
    const unsigned long N = samples.size();
    std::vector<std::complex<double>> spectrum(N);

    for (unsigned long k = 0; k < N; k++)
      for (unsigned long n = 0; n < N; n++)
        spectrum[k] += samples[n] * std::polar(1.0, -2.0 * M_PI * k * n / N);

    return spectrum;
  }

  static std::vector<std::complex<double>> fftN2(const std::vector<std::complex<double>> &samples) {
    const unsigned long N = samples.size();
    if (N == 1)
      return dft(samples);

    const unsigned long M = N / 2;
    std::vector<std::complex<double>> evenSamples(M);
    std::vector<std::complex<double>> oddSamples(M);

    for (unsigned long k = 0; k < M; k++) {
      evenSamples[k] = samples[2 * k];
      oddSamples[k] = samples[2 * k + 1];
    }

    evenSamples = fftN2(evenSamples);
    oddSamples = fftN2(oddSamples);

    std::vector<std::complex<double>> spectrum(N);
    for (unsigned long k = 0; k < M; k++) {
      spectrum[k] = evenSamples[k] + std::polar(1.0, -2.0 * M_PI * k / N) * oddSamples[k];
      spectrum[k + M] = evenSamples[k] - std::polar(1.0, -2.0 * M_PI * k / N) * oddSamples[k];
    }

    return spectrum;
  }

public:
  static unsigned long nextPow2(const unsigned long N) {
    unsigned long pow2 = 1;
    while (pow2 < N)
      pow2 <<= 1;
    return pow2;
  }

  static std::vector<double> fftA(const std::vector<int32_t> &samples) {
    const unsigned long N = nextPow2(samples.size());
    std::vector<std::complex<double>> spectrum(N);
    std::transform(samples.begin(), samples.end(), spectrum.begin(), [](const int32_t sample) {
      return std::complex<double>(sample, 0);
    });
    spectrum = fftN2(spectrum);
    std::vector<double> spectrumA(N);
    std::transform(spectrum.begin(), spectrum.end(), spectrumA.begin(), [](const std::complex<double> sample) {
      return sqrt(pow(sample.real(), 2) + pow(sample.imag(), 2));
    });
    return spectrumA;
  }
};

}
