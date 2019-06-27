#ifndef __IMAGE_MANAGER_H__
#define __IMAGE_MANAGER_H__

#include "algorithms/2dfft.h"

#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

float dist_e(int cx, int cy, int px, int py);

bool cmp_complex(cn a, cn b);

std::vector<std::vector<cn>> low_pass_filter(int width, int height, int d0);

std::vector<std::vector<cn>> median_filter(std::vector<std::vector<cn>> vec,
                                           int width, int height, int d0);

void save_img(std::vector<std::vector<cn>> vec);

std::vector<std::vector<cn>> load_img(std::string filename);

std::vector<std::vector<cn>> img_transform(std::vector<std::vector<cn>> matrix);

#endif