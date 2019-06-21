#ifndef __OPENCV_MANAGER_H__
#define __OPENCV_MANAGER_H__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#define FILENAME "../input/lenna.png"
#define OUTPUT_FILE "../output/output.txt"
#define INPUT_FILE "../input/input.txt"

typedef cv::Mat Img;

void generate_csv();
void display_csv();

#endif
