#include <algorithm>
#include "utility/image_manager.h"

using namespace std;

ImageTransform::ImageTransform(void){}

ImageTransform::ImageTransform(vector< vector< cn > > matrix){
    this->complex_matrix = matrix;
}   
ImageTransform::ImageTransform(vector< vector< double > > matrix){
    //TODO Convert double matrix to complex matrix
}


void ImageTransform::apply_transform(ImageFilter* filter){

    int width = this->complex_matrix.size();
    int height = this->complex_matrix[0].size();

    int P = width * 2;
    int Q = height * 2;


    // Zero pad image for P = 2W, P = 2H so P x Q = IMG
    vector<vector<cn>> rows = ImageUtils::pad0_complex(this->complex_matrix, width, height);

    //Make zero padded copy of image and make filter
    vector< vector< cn > > image_filter = filter->make_filter(rows, P, Q, 3);
    

    //// Multiply by (-1)^x+y to center it to u = P / 2 and v Q / 2 where u and v
    //// are center coordinates
    //ImageUtils::center_matrix(image_filter);

    //// Multiply by (-1)^x+y to center it to u = P / 2 and v Q / 2 where u and v
    //// are center coordinates
    //ImageUtils::center_matrix(rows);

    // 2D FFT
    fft2d(rows, P, Q);

    //2D FFT on filter
    fft2d(image_filter, P, Q);

    // Apply the filter H(x, y) to F(x, y) (multiply)
    for (int x = 0; x < P; x++) {
        for (int y = 0; y < Q; y++) {
            rows[x][y] = rows[x][y] * image_filter[x][y];
        }
    }
    
    // Inverse 2D FFT
    ifft2d(rows, P, Q);


    //Crop back
    for(int x = 0;x < P;x++){
        for(int y = 0;y < Q;y++){
            this->complex_matrix[x][y] = rows[x][y];
        }
    } 
    
    this->complex_matrix = rows;
}

void ImageTransform::set_matrix(vector< vector< cn > > matrix){
    this->complex_matrix = matrix;
}
void ImageTransform::set_matrix(vector< vector< double > > matrix){
    //TODO Convert double to cn matrix 
}

vector< vector< cn > > ImageTransform::get_matrix(void){
    return this->complex_matrix;
}


vector< vector< cn > > ImageMedianFilter::make_filter(vector< vector< cn > > matrix, int width, int height, int d0){

  vector<vector<cn>> rows = matrix;

  int n_cuad_cols = height / d0;
  int n_cuad_rows = width / d0;

  cout << width << " " << height << " " << endl;
  for (int rc = 0; rc < n_cuad_rows;rc++) {
    for (int cc = 0; cc < n_cuad_cols; cc++) {
      int lc_y = rc * d0;
      int lc_x = cc * d0;

      vector<cn> cuad;
      for (int i = 0; i < d0 * d0; i++) {
        int x = lc_x + i % d0;
        int y = lc_y + i / d0;
        if (x >= width || y >= height) continue;

        cuad.push_back(rows[x][y]);
      }

      sort(cuad.begin(), cuad.end(), ImageUtils::cmp_rgba);

      if(cuad.empty())
          continue;
      cn mid = cuad[cuad.size() / 2];

      for (int i = 0; i < d0 * d0; i++) {
        int x = lc_x + i % d0;
        int y = lc_y + i / d0;

        if (x >= width || y >= height) continue;
        if (!(x == 0 || y == 0 || x == width - 1 || y == height - 1))
          rows[x][y] = mid;
      }
    }
  }
  return rows;
}

vector< vector< cn > > ImageLowFilter::make_filter(vector< vector< cn > > matrix, int width, int height, int d0){
  vector<vector<cn>> rows(width, vector<cn>(height, 0));

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int ncx, ncy, cx, cy, cent_x, cent_y;

      ncx = width / d0;
      ncy = height / d0;

      cx = width / ncx;
      cy = height / ncy;

      cent_x = floor(x / (width / ncx)) * ncx + ceil((width / ncx) / 2);
      cent_y = floor(y / (height / ncy)) * ncy + ceil((height / ncy) / 2);

      if (ImageUtils::dist_euclid(cent_x, cent_y, x, y) <= d0) {
        rows[x][y] = 1;
      } else {
        rows[x][y] = 0;
      }
    }
  }
  return rows;
}

//vector<vector<cn>> load_img(string filename) {
  //ifstream file(filename);
  //string line;
  //vector<vector<cn>> rows;

  //while (getline(file, line)) {
    //vector<cn> col;
    //replace(line.begin(), line.end(), ',', ' ');
    //stringstream ss(line);

    //int tmp_int;
    //while (ss >> tmp_int) {
      //col.push_back(tmp_int);
    //}
    //rows.push_back(col);
  //}
  //file.close();
  //return rows;
//}


