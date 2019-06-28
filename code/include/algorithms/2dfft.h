#ifndef __2DFFT_H__
#define __2DFFT_H__

#include "algorithms/fft.h"
#include <iostream>

#define fft2d(matrix, m, n) _fft2d(matrix, m, n, 0)
#define ifft2d(matrix, m, n) _fft2d(matrix, m, n, 1)

void p(std::vector<std::vector<RGBA_Complex>> vec);

void _fft2d(std::vector<std::vector<RGBA_Complex>>& matrix, int m, int n, bool inverse);

#endif
