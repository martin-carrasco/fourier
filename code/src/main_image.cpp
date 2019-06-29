#include "utility/image_manager.h"
#include "utility/opencv_manager.h"
#include <vector>

using namespace std;

int main(void) {
  vector<vector<cn>> img_matrix = make_2d_array();

  ImageTransform transformer(img_matrix);

  transformer.apply_lp(0.0);

  // save_img(img_matrix);
  display_csv(img_matrix);

  return 0;
}
