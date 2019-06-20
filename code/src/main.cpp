#include "../include/fft.h"
#include "../include/types.h"
#include <iostream>

using namespace std;

int main(void)
{
    vector<cn> x = { 0.24200326, 0.96688159, 0.87782714, 0.8408777 };
    vector<cn> y = recursive_fft(x);
    vector<cn> xp = recursive_ifft(y);

    cout << "Originally in time domain:\n";
    for (auto i : x) {
        cout << i << " ";
    }
    cout << endl;

    cout << "In frequency domain:\n";
    for (auto i : y) {
        cout << i << " ";
    }
    cout << endl;

    cout << "Again in time domain:\n";
    for (auto i : xp) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
