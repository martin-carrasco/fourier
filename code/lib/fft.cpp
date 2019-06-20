#include "../include/fft.h"
#include <cmath>
#include <exception>

using namespace std;

vector<cn> _recursive_fft(const vector<cn>& a, bool inverse)
{
    int n;
    double rad;

    n = a.size();
    vector<cn> y(n);

    if (not(n && !(n & (n - 1))))
        throw std::runtime_error("Not a power of 2\n");
    if (n == 1)
        return (y = a);

    vector<cn> a0(n / 2), a1(n / 2);
    vector<cn> y0(n / 2), y1(n / 2);

    for (int i = 0; i < n / 2; ++i) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    y0 = _recursive_fft(a0, inverse);
    y1 = _recursive_fft(a1, inverse);

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
