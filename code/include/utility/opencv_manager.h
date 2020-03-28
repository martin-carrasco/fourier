#ifndef __OPENCV_MANAGER_H__
#define __OPENCV_MANAGER_H__

#include "types.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define OUTPUT_PATH "res/image/output/"
#define INPUT_PATH "res/image/input/"

typedef cv::Mat Img;

std::vector<std::vector<cn>> read_img(const std::string filename);
Img display_img(std::vector<std::vector<cn>> matrix, bool domain);
Img display_filter(std::vector<std::vector<cn>> matrix, bool domain);
void to_csv(std::string filename, const std::vector<std::vector<cn>>& matrix);
#endif
