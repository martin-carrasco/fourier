# Fourier FAQ

## General

+ What is the difference between Fourier Series and Fourier Transform?
    + A Fourier Transform is a way to move from one domain to another to simplify the calculations of an functions. While a Fourier Series is a way to divide a function in all of its sinusoidal components. Also a Fourier Transform is aperiodic while a Fourier Series is periodic (* 1 / T) 
+ What is the difference between multiplication and convolution?
    + Multiplication is term-by-term multiplication: $z[n] = x[n]y[n]$ for all $n$.
    + Convolution, for discrete-time sequences, is equivalent to polynomial multiplication which is not the same as the term-by-term multiplication. Convolution also requires a lot more calculation: typically $N^2$ multiplications for sequences of length $N$ instead of the $N$ multiplications of the term-by-term multiplication.
+ How does the Fourier Transform relate to polynomial multiplication (convolution)
    + The key point of Fourier analysis is that term-by-term multiplication in one domain is the same as convolution in the other domain. So, in order to calculate the results of a convolution, you can either do it directly, using $N^2$ multiplications, or transform to the other domain, do a term-by-term multiplication, and transform back. This requires two transformations to go from one domain to the other, $N$ multiplications in the other domain, and one inverse transformation to come back to the domain where the convolution result is needed. This more complicated process can, in fact, require less computation because the transformations can be done very efficiently via the Fast Fourier Transform (FFT) algorithm which requires about $NlogN$  multiplications. So, compare the computational effort in calculating the three transforms and doing the term-by-term multiplication to $N^2$ to see if the FFT gives you a more efficient method of computing a convolution.

## Some important quotes

### [McGill, Spectra.](https://www.music.mcgill.ca/~gary/307/week1/spectra.html)
+ DFT determines sinusoidal "weights" via the inner product of sinusoids and the signal.
+ The DFT can be interpreted as the sum of projectoions of `x[n]` onto a set of `k` samples complex sinusoids / sinusoidal basis functions at (normalized) radian frequencies given by `wk = 2 pi k / N`
+ The DFT coefficiets are complex values. To plot the magnitude response of a signals's spectrum,, we calculate the magnitude of each coefficient.

### [Spectral Audio Signal Processing](https://www.dsprelated.com/freebooks/sasp/Fourier_Transform_FT_Inverse.html)

+ Thus, the Fourier transform is defined for continuous time and continuous frequency, both unbounded. As a result, mathematical questions such as existence and invertibility are most difficult for this case. In fact, such questions fueled decades of confusion in the history of harmonic analysis (see Appendix G).

+ On the existence of the fourier transform: sufficient to be absolutely integrable or square integrable.

+ The need for spectral interpolation comes up in many situations. For example, we always use the DFT in practice, while conceptually we often prefer the DTFT. For time-limited signals, that is, signals which are zero outside some finite range, the DTFT can be computed from the DFT via spectral interpolation. Conversely, the DTFT of a time-limited signal can be sampled to obtain its DFT

