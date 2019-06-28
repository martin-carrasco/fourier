#ifndef __FFT_H__
#define __FFT_H__

#include "utility/types.h"
#include <vector>

// Macros to define fourier transform and its inverse

#define recursive_fft(a) _recursive_fft(a, 0)
#define recursive_ifft(a) _recursive_fft(a, 1)


// Base function
std::vector<RGBA_Complex> _recursive_fft(const std::vector<RGBA_Complex>& a, bool inverse);
void _fft2d(std::vector<std::vector<RGBA_Complex>>& matrix, int m, int n, bool inverse);


#endif
