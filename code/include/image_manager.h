#ifndef __IMAGE_MANAGER_H__
#define __IMAGE_MANAGER_H__

#include "../include/2dfft.h"

#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

float dist_e(int cx, int cy, int px, int py);

std::vector<std::vector<cn>> low_pass_filter(int width, int height, int d0);

void save_img(std::vector< std::vector< cn > > vec);

std::vector<std::vector<cn>> load_img(std::string filename);

void img_transform(std::vector<std::vector<cn>> matrix);

#endif
