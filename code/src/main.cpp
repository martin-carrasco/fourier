#include "utility/image_manager.h"
#include "utility/opencv_manager.h"
#include <vector>

using namespace std;

int main(void) {
  vector<vector<cn>> img_matrix = make_2d_array();

  // display_csv(img_matrix);

  ImageTransform transformer(img_matrix);

  ImageLowFilter* filter = new ImageLowFilter();

  transformer.apply_transform(filter);

  vector<vector<cn>> trans_matrix = transformer.get_matrix();

  // save_img(img_matrix);
  display_csv(trans_matrix);

  return 0;
}
