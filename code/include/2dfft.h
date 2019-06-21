#ifndef __2DFFT_H__
#define __2DFFT_H__

#include "../include/fft.h"
#include "../include/types.h"
#include <iostream>

void p(std::vector<std::vector<cn>> vec);

void fft2d(std::vector<std::vector<cn>>& matrix, int m, int n, bool b);

std::vector<cn> cons(std::vector<double> v1, std::vector<double> v2, int n);

void ifft2d(std::vector<std::vector<cn>>& matrix, int m, int n);


#endif
