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

#define FILENAME "res/image/input/indian.jpeg"
#define OUTPUT_FILE "res/image/output/output.txt"
#define INPUT_FILE "res/image/input/input.txt"

typedef cv::Mat Img;

std::vector<std::vector<cn> > make_2d_array();
void display_csv(std::vector<std::vector<cn> > matrix);

#endif
