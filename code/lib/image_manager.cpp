#include "../include/image_manager.h"
#include <algorithm>

using namespace std;

float dist_e(int cx, int cy, int px, int py)
{
    return sqrt(
        pow(cx - px, 2) + pow(cy - py, 2));
}

vector<vector<cn>> low_pass_filter(int width, int height, int d0)
{
    vector<vector<cn>> rows(width, vector<cn>(height, 0));
    for (auto row : rows) {
        vector<cn> col(height, 0);
        rows.push_back(col);
    }

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
    f_out.close();
}

vector< vector<cn> > img_transform(vector<vector<cn>> matrix)
{
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

    //Multiply by (-1)^x+y to center it to u = P / 2 and v Q / 2 where u and v are center coordinates
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

    //Center H(x, y) to (P/2, Q/2) - multiply by (-1)^x+y
    for (int x = 0; x < P; x++) {
        for (int y = 0; y < Q; y++) {
            filter_mask[x][y] = filter_mask[x][y] * pow(-1, x + y);
        }
    }

    //Apply the filter H(x, y) to F(x, y) (multiply)
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            rows[x][y] = rows[x][y] * filter_mask[x][y];
        }
    }

    //Inverse 2D FFT
    ifft2d(rows, P, Q);

    //Crop back
    
    return rows;
}
