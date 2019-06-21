#include "../include/2dfft.h"

using namespace std;

void p(vector<vector<cn>> vec)
{
    for (auto layer_1 : vec) {
        for (auto comp_num : layer_1)
            cout << comp_num << ", ";
        cout << endl;
    }
    cout << endl;
}

void _fft2d(vector<vector<cn>>& matrix, int m, int n, bool inverse)
{
    for (int r = 0; r < m; r++) {
        matrix[r] = _recursive_fft(matrix[r], inverse); // R * O(R log R)
    }

    vector<cn> t; //(Real, Complex) representation of the transform made on the columns

    for (int c = 0; c < n; c++) { //C

        for (int r = 0; r < m; r++) { //O(R)
            t.push_back(matrix[r][c]);
        }

        t = _recursive_fft(t, inverse); //O(C log C)

        for (int r = 0; r < m; r++) { //O(R)
            matrix[r][c] = t[r];
        }
        t.clear();
        // O(C log C) + O(C) + O(2R)
    }
}
