#include "algorithms/fft.h"
#include "utility/matplotlibcpp.h"
#include "utility/opencv_manager.h"
#include <cmath>
#include <filesystem>
#include <iostream>
#include <vector>
#define INPUT_PATH "res/image/input/"
#define OUTPUT_PATH "res/image/output/"

namespace plt = matplotlibcpp;
namespace fs = std::filesystem;

int main(int argc, const char* argv[]) {
    auto img = read_img("indian.png");
    display_img(img)
    return 0;
}
