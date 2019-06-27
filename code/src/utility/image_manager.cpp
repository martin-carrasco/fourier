#include <algorithm>
#include "../include/image_manager.h"

using namespace std;

float dist_e(int cx, int cy, int px, int py) {
  return sqrt(pow(cx - px, 2) + pow(cy - py, 2));

}
bool cmp_complex(cn a, cn b) { return real(a) < real(b); }

vector<vector<cn>> median_filter(vector<vector<cn>> vec, int width, int height,
                                 int d0) {
  vector<vector<cn>> rows = vec;

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

      sort(cuad.begin(), cuad.end(), cmp_complex);

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
vector<vector<cn>> low_pass_filter(int width, int height, int d0) {
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

      if (dist_e(cent_x, cent_y, x, y) <= d0) {
        rows[x][y] = 1;
      } else {
        rows[x][y] = 0;
      }
    }
  }
  return rows;
}
 
vector< vector<cn> > load_img(string filename)
{
    ifstream file(filename);
    string line;
    vector<vector<cn>> rows;

    while (getline(file, line)) {
        vector<cn> col;
        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss(line);

        int tmp_int;
        while (ss >> tmp_int) {
            col.push_back(tmp_int);
        }
        rows.push_back(col);
    }
    rows.push_back(col);
  }
  file.close();
  return rows;
}


void save_img(vector< vector<cn> > vec){
    ofstream f_out("../input/input.txt");
    for(auto row : vec){
        for(auto col : row){
            f_out << real(col) << ",";
        }
        cout << endl;
    }
    f_out << endl;
  }
  f_out.close();
}

vector<vector<cn>> img_transform(vector<vector<cn>> matrix) {
  
  int width = matrix.size();
  int height = matrix[0].size();

  int P = width * 2;
  int Q = height * 2;


    //Zero pad image for P = 2W, P = 2H so P x Q = IMG
    vector < vector<cn>> rows(P, vector<cn>(Q, 0));

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      rows[x][y] = matrix[x][y];
    }
  }


  // Multiply by (-1)^x+y to center it to u = P / 2 and v Q / 2 where u and v
  // are center coordinates
  for (int x = 0; x < P; x++) {
    for (int y = 0; y < Q; y++) {
      rows[x][y] = rows[x][y] * pow(-1, x + y);
    }
  }
    //2D FFT
    fft2d(rows, P, Q);

    //Make filter h(x, y) for P x Q
    vector<vector<cn>> filter_mask = low_pass_filter(P, Q, 3);

    //2D FFT to make H(x, y) from h(x, y)
    fft2d(filter_mask, P, Q);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      mask[x][y] = matrix[x][y];
    }
  }

  // Make filter h(x, y) for P x Q
  // vector<vector<cn>> filter_mask = low_pass_filter(P, Q, 3);
  vector<vector<cn>> filter_mask = low_pass_filter(P, Q, 3);

  // Center H(x, y) to (P/2, Q/2) - multiply by (-1)^x+y
  for (int x = 0; x < P; x++) {
    for (int y = 0; y < Q; y++) {
      filter_mask[x][y] = filter_mask[x][y] * pow(-1, x + y);
    }
  }

  // 2D FFT to make H(x, y) from h(x, y)
  fft2d(filter_mask, P, Q);

  // Apply the filter H(x, y) to F(x, y) (multiply)
  for (int x = 0; x < P; x++) {
    for (int y = 0; y < Q; y++) {
      rows[x][y] = rows[x][y] * filter_mask[x][y];
    }
  }

  // Inverse 2D FFT
  ifft2d(rows, P, Q);

    //Inverse 2D FFT
    ifft2d(rows, P, Q);

  return rows;
}
