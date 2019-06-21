#include "../include/2dfft.h"
#include "../include/types.h"
#include <iostream>

using namespace std;

int main(void)
{
    vector<vector<cn>> input_mat, nn;

    vector<cn> input_vec0 = { 0.24015828, -0.86474901, 6.70624768, -1.69587419 };
    vector<cn> input_vec1 = { 5.95275288, 4.54761255, 1.64295669, -2.16218665 };
    vector<cn> input_vec2 = { -0.18274577, -4.59299313, -9.39010456, -0.90969898 };
    vector<cn> input_vec3 = { 0.46954236, -3.14142204, -6.569748, -1.08002712 };

    input_mat.push_back(input_vec0);
    input_mat.push_back(input_vec1);
    input_mat.push_back(input_vec2);
    input_mat.push_back(input_vec3);

    cout << "Before transform: " << endl;
    p(input_mat);

    fft2d(input_mat, 4, 4, false);

    cout << "After transform: " << endl;
    p(input_mat);

    cout << "After inverse: " <<endl;

    cout<< endl;
    ifft2d(input_mat,4,4);
    p(input_mat);
    return 0;
}
