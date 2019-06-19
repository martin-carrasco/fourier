#include <fstream>
#include <sstream>

using namespace std;

float dist_e(int cx, int cy, int px, int py){
    return sqrt(
                pow(cx - px, 2)  + pow(cy - py, 2);
            );
}

int low_pass_filter(int width, int height, int d0){
    vector< vector<int> > rows(width, 0);
    for(auto row : rows){
        vector<cn> col(height, 0);
        rows.push_back(col);
    }

    for(int x = 0;x < width;x++){
        for(int y = 0;y < height;y++){
            int ncx, ncy, cx, cy, cent_x, cent_y;
            
            ncx = width / d0;
            ncy = height / d0;

            cx = width / ncx;
            cy = height / ncy;

            cent_x = floor(x / (width / ncx) ) * ncx + ceil( (width / ncx) / 2 );
            cent_y = floor(y / (height / ncy) ) * ncy + ceil( (height / ncy) / 2 );

            if(dist_e(cent_x, cent_y, x, y) <= d0){
                rows[x][y] = 1;
            }else{
                rows[x][y] = 0;
            }
            
        }
    }
    return rows; 
}

vector< vector< cn > > load_img(string filename){
    ifstream file(filename);
    string line;
    vector< vector< cn > > rows;

    while(getline(file, line)){
        vector<cn> col;
        stringstream ss(line);
        int tmp_int;

        while(ss >> tmp_int){
            col.push_back(tmp_int);
            if(ss.peek(","))
                ss.ignore();
        }
        rows.push_back(col);
    }
    return rows;
}

void img_transform(vector< vector< cn > > complex_mat){
    int width = matrix.size()
    int height = matrix[0].height();

    //vector< vector< cn > > complex_mat = convert_to_complex(matrix);

    //2D FFT
    2dfft(complex_mat, width, height);

    //Create a low pass mask for low frequency domain
    vector< vector< int > > low_pass_mask = low_pass_filter(width, height, 3);

    //Apply the low pass mask in the frequency domain
    for(int x = 0;x < width;x++){
        for(int y = 0;y < height;y++){
            complex_mat[x][y] = complex_mat[x][y]  * low_pass_mask[x][y]; 
        }
    }
    //Reverse 2D FFT

    //Save img
}
