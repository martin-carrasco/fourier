#include "algorithms/fft.h"
#include <cassert>
#include <cmath>
#include <exception>

using namespace std;

bool is_prime(int num) {
    bool prime = true;
    for (int x = 2; x <= num / 2; x++) {
        if (num % x == 0) {
            prime = false;
            break;
        }
    }
    return prime;
}

vector<cn> ct_out_fft1d(const vector<cn>& a, bool inverse = false) {
    int n;
    double rad;

    n = a.size();
    vector<cn> y(n);

    if (not(n && !(n & (n - 1)))) throw runtime_error("Not a power of 2\n");
    if (n == 1) return (y = a);

    vector<cn> a0(n / 2), a1(n / 2);
    vector<cn> y0(n / 2), y1(n / 2);

    for (int i = 0; i < n / 2; ++i) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    y0 = ct_out_fft1d(a0, inverse);
    y1 = ct_out_fft1d(a1, inverse);

    rad = 2 * M_PI / n * (inverse ? -1 : 1);
    cn w(1), wn(cos(rad), sin(rad));

    for (int k = 0; k <= n / 2 - 1; ++k) {
        y[k] = y0[k] + w * y1[k];
        y[k + (n / 2)] = y0[k] - w * y1[k];
        if (inverse) {
            y[k] /= 2;
            y[k + n / 2] /= 2;
        }
        w = w * wn;
    }
    return y;
}

void ct_in_fft1d(vector<cn>& a, bool inverse = false) {
    int n = a.size();
    if (n == 1) return;

    vector<cn> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    ct_in_fft1d(a0, inverse);
    ct_in_fft1d(a1, inverse);

    double ang = 2 * acos(-1) / n * (inverse ? -1 : 1);
    cn w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (inverse) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

/*
void ct_inplace_fft(vector<cn>& ft, bool inverse) {
    if (not(n && !(n & (n - 1))))
        throw runtime_error("Not a power of 2\n");
    ct_fft_helper(ft.begin(), ft.end());
}

void ct_fft_inplace_helper(vector<cn>::iterator begin, vector<cn>::iterator end,
                   bool inverse) {
    int N = distance(begin, end);
    if (N == 1) return;
    ct_fft_helper(begin, begin + N / 2, inverse);
    ct_fft_helper(begin + N / 2, end, inverse);

    for (auto it = begin; it != begin + N / 2; ++it)
    {
    //TODO: multiplying by roots of unity
    }

    return y;
}
*/

void ct_in_fft2d(vector<vector<cn>>& matrix, bool inverse) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int r = 0; r < rows; r++)
        ct_in_fft1d(matrix[r], inverse);  // R * O(R log R)

    vector<cn> t;  //(Real, Complex) representation of the transform made on the
                   // columns

    for (int c = 0; c < cols; c++) {  // C

        for (int r = 0; r < rows; r++) {  // O(R)
            t.push_back(matrix[r][c]);
        }

        ct_in_fft1d(t, inverse);  // O(C log C)

        for (int r = 0; r < rows; r++) {  // O(R)
            matrix[r][c] = t[r];
        }
        t.clear();
        // O(C log C) + O(C) + O(2R)
    }
}

void shift_fft2d(vector<vector<cn>>& vec) {
    int height = vec.size();
    int width = vec[0].size();

    int half_width = width / 2;
    int half_height = height / 2;

    for (int i = 0; i < half_height; i++) {
        for (int j = 0; j < half_width; j++) {
            cn tmp_1_quad = vec[i][j];
            cn tmp_4_quad = vec[i + half_height][j + half_width];
            vec[i][j] = tmp_4_quad;
            vec[i + half_height][j + half_width] = tmp_1_quad;
        }

        for (int k = half_width; k < height; k++) {
            cn tmp_2_quad = vec[i][k];
            cn tmp_3_quad = vec[i + half_height][k - half_width];
            vec[i][k] = tmp_3_quad;
            vec[i + half_height][k - half_width] = tmp_2_quad;
        }
    }
}
void rad_in_fft1d(vector<cn>& vec, bool inverse) {
    assert(is_prime(vec.size()));
}
void win_in_fft1d(std::vector<cn>& vec, bool inverse) {}
