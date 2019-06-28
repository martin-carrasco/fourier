#ifndef __OPENCV_MANAGER_H__
#define __OPENCV_MANAGER_H__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#define FILENAME "res/image/input/lena.png"
#define OUTPUT_FILE "res/image/output/output.txt"
#define INPUT_FILE "res/image/input/input.txt"

typedef cv::Mat Img;

void generate_csv();
void display_csv();

#endif
