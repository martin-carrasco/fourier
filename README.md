# Fourier Transform

## Instructions

```zsh
cd code

# To build image containing OpenCV and other dependencies (only run it one time)
./script/pre_build

# To compile project
./script/build

# To execute project
./script/run
```

## Useful resources

+ [3blue1brown. _But, what is a Fourier Transform?_](https://www.youtube.com/watch?v=spUNpyF58BY)
    + For an intuition of Fourier Transforms (recommended by dgcnz).
+ [Osgood, Brad. _The Fourier Transform and its Applications_](https://see.stanford.edu/materials/lsoftaee261/book-fall-07.pdf)
    + Tremendously comprehensive lecture notes from MIT's Brad Osgood.
+ [Math.StackExchange. _How is the Fourier Transform Linear?_](https://math.stackexchange.com/questions/140788/how-is-the-fourier-transform-linear)
    + For a discussion on what it means to be a linear transform and how can a Fourier Transform be considered one.
    + Spoiler alert: If it satisfies two conditions, namely, additivity (addition) and homogeneity (multiplication by scalar).
+ [Charles Van Loan. _Computational Frameworks for the Fast Fourier Transform_, 1992.](https://dl.acm.org/citation.cfm?id=130635)
    + For understanding of FFT and the mathematics of multidimensional FFTs (recommended by CLRS).
+ [Alan V. Oppenheim and Ronald W. Schafe, with John R. Buck. _Discrete-Time Signal Processing_, 1997.](https://dl.acm.org/citation.cfm?id=1795494)
    + For an introduction to signal processing and handling case when `n` is not power of 2 (recommended by CLRS).
+ [Rafael C. Gonzalez and Richard E. Woods. _Digital Image Processing_, 1992](https://dl.acm.org/citation.cfm?id=573607)
    + For a discussion in multidimensional Fourier Transforms and their use in image processing (recommended by CLRS).
+ [Brilliant.org. _Roots of unity_](https://brilliant.org/wiki/roots-of-unity/)
    + Useful intuition for FFT key concept.

## Literature

```txt
├── dgcnz
│   ├── graphs
│   │   ├── Are There Approximate Fast Fourier Transforms On Graphs? - Magorau - 2016.pdf
│   │   ├── Big Data Analysis with Signal Processing on Graphs - Sandryhaila - 2014.pdf
│   │   └── The Emerging Field of Signal Processing on Graphs - Shuman - 2013.pdf
│   ├── misc
│   │   └── Some Topics in Analysis of Boolean Functions - O'donell - 2008.pdf
│   ├── music
│   │   ├── Applications of Fourier Analysis to Audio Signal Processing: An Investigation of Chord Detection Algorithms - Lensen - 2013.pdf
│   │   ├── Design and Evaluation of a Simple Chord Detection Algorithm - Hausner - 2014 [Thesis].pdf
│   │   └── ON THE MATHEMATICS OF MUSIC: FROM CHORDS TO FOURIER ANALYSIS - Lensen - 2013.pdf
│   ├── theoretical
│   │   ├── Fourier Transforms and the Fast Fourier Transform (FFT) Algorithm - Heckbert - 1995.pdf
│   │   └── Recent Developments in the Sparse Fourier Transform: A compressed Fourier transform for big data - Gilbert - 2014.pdf
│   └── voice
│       └── Mathematical Methods for Voice Transformation - Lilla - 2017.pdf
├── jotarios
│   ├── books
│   │   └── Digital Image Processing for Medical Applications - See at page 232 onwards - 2009.pdf
│   ├── papers
│   │   ├── fft
│   │   │   ├── A Sparse Multi-Dimensional Fast Fourier Transform with Stability to Noise in the Context of Image Processing and Change Detection - 2016.pdf
│   │   │   ├── An Algorithm for the Machine Calculation of Complex Fourier Series - Cooley Tukey - 1965.pdf
│   │   │   ├── Fast Fourier transform using matrix decomposition - 2014.pdf
│   │   │   ├── Reduction of speckle in digital holography by discrete fourier filtering - 2007.pdf
│   │   │   ├── applications
│   │   │   │   ├── Diagnosis of Epilepsy in Patients Based on the Classification of EEG Signals Using Fast Fourier Transform - 2015.pdf
│   │   │   │   ├── Fast Fourier Transform for Feature Extraction And Neural Network for Classification of Electrocardiogram Signals - 2015.pdf
│   │   │   │   └── The Fast Fourier Transform and Its Applications - 1968.pdf
│   │   │   └── parallel-gpu
│   │   │       └── cusFFT: A High-Performance Sparse Fast Fourier Transform Algorithm on GPUs - 2016.pdf
│   │   ├── noise reduction - audio
│   │   │   └── Suppression of Acoustic Noise in Speech Using Spectral Subtraction - 1979.pdf
│   │   └── noise reduction - image
│   │       ├── Fourier Transform based Windowed Adaptive Switching Minimum Filter for Reducing Periodic Noise from Digital Images - 2015.pdf
│   │       └── Noise reduction algorithms using Fibonacci Fourier transforms - 2008.pdf
│   └── parts in books
│       └── Fast Fourier Transform (FFT) on GPUs - Chapter 16 - 2014.pdf
│
│
│
├── martin-carrasco
│	├── fft
│		├── An Omega((n log n)R) Lower Bound for Fourier Transform Computation.pdf
│		├── On Computing the FFT.pdf
|		|
│		└── Sparse Fourier Transform in Any Constant Dimension with Nearly-Optimal Sample Complexity in Sublinear Time.pdf
│	└── images
│		├── An Accurate Nonuniform Fourier Transform for SPRITE Magnetic Resonance Imaging Data.pdf
│		├── Determining Image Orientation using the Hough and Fourier Transforms.pdf
│		├── High-quality Motion Deblurring from a Single Image.pdf
│		├── Image Motion Estimation from Motion Smear -  A New Computational Model (1996).pdf
|		|
│		└── With J Fast Fourier Transforms and Removing Motion Blur.pdf
│
└── ramirez
    ├── FrationalFourierTransform.pdf
    ├── FrationalFourierTransform.pdfNoise removal in speech signal using fractional fourier transform-2017 .pdf
    ├── HarmonicAnalysus-1978.pdf
    └── paper.md
```
