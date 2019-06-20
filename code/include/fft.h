#ifndef __FFT_H__
#define __FFT_H__

#include "../include/types.h"
#include <vector>

// Macros to define fourier transform and its inverse

#define recursive_fft(a) _recursive_fft(a, 0)
#define recursive_ifft(a) _recursive_fft(a, 1)

// Base function
std::vector<cn> _recursive_fft(const std::vector<cn>& a, bool inverse);

#endif
