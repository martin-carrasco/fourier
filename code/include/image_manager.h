#ifdef __IMAGE_MANAGER_H__
#define __IMAGE_MANAGER_H__

#include "../include/2dfft.h"

float dist_e(int cx, int cy, int px, int py);

int low_pass_filter(int width, int height, int d0);

std::vector<std::vector<cn>> load_img(std::string filename);

void img_transform(std::vector<std::vector<cn>> matrix);

#endif
