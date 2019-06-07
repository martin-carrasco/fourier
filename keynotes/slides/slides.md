# Fourier Transform

---

## Index

+ Theory
    + Basic mathematical background
    + Fourier Transform derivation
+ Application
    + Algorithm 1
    + Algorithm 2

---

## Theory



---

## Application

### Image processing

In terms of blurred images, if the motion blur on said image is shift-invariante then it's usually modeled as a convolution of that image. Meaning that the blurred image actually has 2 components:

- Latent image: The original image that has been affected by a blur kernel
- Motion blur: The blur kernel that applied to the image causes the blur

Now there are 2 methods for image deconvolution:

- _Non-blind Deconvolution_ :  In this method it is assumed that you already have the blur kernel and you just need to do the reverse operation

- _Blind Deconvolution_: In blind deconvolution there is also as an addictional task,, using some kind of modeling strategy, to find out the closes possible blur kernel to the original one.

  Some popular strategies for finding these motion deconvolutions ranged from proposing 2 consequente instances of an image in time, rotating the image, etc. However they all proved either inexact or had a high computational cost.

An easy iterative blind approach would be as follows:

 __L<sup>´</sup> = argmin<sub>L</sub> { ||B - K *  L  || + p<sub>L</sub>(L) }__

 __K<sup>´</sup> = argmin<sub>L</sub> { ||B - K *  L  || + p<sub>K</sub>(K }__



given that the motion blur equations is

~~~C
B= K * L + N
~~~

where the basic terms

~~~C
B = blurred image
K = motion kernel or PSF (point spread function)
L = current latent image
~~~



However we are going to be using FFT to speed up the process of the calculations. To do this we will devide the operations in 3 steps:



* Prediction: Here we will predict a base L value to be used in the next step. This will be a really simple blind approximation using Gaussian prior.

* Kernel Estimation: Using our base case L we will use FFT to accuratly approximate K as much as possible

* Deconvolution: Since we now have all the elements needed to produce the "clear" image we will again apply FFT to deconvolute.

  



