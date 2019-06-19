#include "../include/fft.h"
#include <iostream>

using namespace std;

void p(vector< vector<cn> > vec){
    for(auto layer_1 : vec){
        for(auto comp_num : layer_1)
            cout << comp_num << ", ";
        cout << endl;
    }
    cout << endl;
}
void fft2d(vector< vector<cn> > &matrix, int m, int n){
    for(int r = 0; r < m;r++){
        matrix[r] = recursive_fft(matrix[r]); // R * O(R log R)
    }

    vector<cn> t; //(Real, Complex) representation of the transform made on the columns

    for(int c = 0;c < n;c++){ //C

        for(int r = 0;r < m;r++){ //O(R)
            t.push_back(matrix[r][c]);
        }

        t = recursive_fft(t); //O(C log C) 
        
        for(int r = 0;r < m;r++){ //O(R)
            matrix[r][c] = t[r];
        }
        t.clear();
        // O(C log C) + O(C) + O(2R)
    }
}

int main(){
    vector< vector< cn > > input_mat;

    vector<cn> input_vec0 = {0.24015828, -0.86474901,  6.70624768, -1.69587419};
    vector<cn> input_vec1 = { 5.95275288,  4.54761255,  1.64295669, -2.16218665};
    vector<cn> input_vec2 = {-0.18274577, -4.59299313, -9.39010456, -0.90969898};
    vector<cn> input_vec3 = { 0.46954236, -3.14142204, -6.569748  , -1.08002712};

    input_mat.push_back(input_vec0);
    input_mat.push_back(input_vec1);
    input_mat.push_back(input_vec2);
    input_mat.push_back(input_vec3);
    
    cout << "Before transform: " << endl;
    p(input_mat);

    fft2d(input_mat, 4,  4);
    
    cout << "After transform: " << endl;
    p(input_mat);
    

}
