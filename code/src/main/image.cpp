#include "utility/image_manager.h"
#include "utility/opencv_manager.h"
#include <vector>

using namespace std;

vector<vector<cn>> ft(vector<vector<cn>> vec);

int main(void) {
    vector<vector<cn>> img_matrix = read_img("indian.png");

    ImageTransform transformer(img_matrix);

    transformer.apply_lp(3.0);

    // save_img(img_matrix);

    img_matrix = transformer.get_matrix();
    display_img(img_matrix, false);

    return 0;
}
