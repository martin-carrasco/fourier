#include "../include/fft.h"
#include <cmath>
#include <exception>

using namespace std;

vector<cn> recursive_fft(const vector<cn>& a)
{
    int n;
    double rad;

    n = a.size();
    if (not(n && !(n & (n - 1))))
        throw std::runtime_error("Not a power of 2\n");
    if (n == 1)
        return a;

    vector<cn> a0(n / 2), a1(n / 2);
    vector<cn> y0(n / 2), y1(n / 2);
    vector<cn> y(n);

    for (int i = 0; i < n / 2; ++i) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    y0 = recursive_fft(a0);
    y1 = recursive_fft(a1);

    rad = 2 * M_PI / n;
    cn w(1), wn(cos(rad), sin(rad));

    for (int k = 0; k <= n / 2 - 1; ++k) {
        y[k] = y0[k] + w * y1[k];
        y[k + (n / 2)] = y0[k] - w * y1[k];
        w = w * wn;
    }
    return y;
}
