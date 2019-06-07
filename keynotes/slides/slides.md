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
### Fourier transform
Any continoun signal in the time domain could be represented by sum of sinusoids
![](/../images/FT1.jpg)

#### why sinusoids?
they are the only waveform that doesn't change shape when subject to a linear invariant system
![](/../images/FT1_3.png)
### Systems
Is any process that produces an output signal in response to an input signal.
__X[t] = Y[t]__
![](/../images/FT1_2.png)

### Linear time invariant system
LTI systems are those that are both linear and time-invariant.
#### Linear propiety
The output is linearly related to the input.

__X<sub>1</sub>[t] = y<sub>1</sub>[t]__
__X<sub>2</sub>[t] = y<sub>2</sub>[t]__ 

__(x<sub>1</sub>[t] + x<sub>2</sub>[t]) = (y<sub>1</sub>(t) + y<sub>2</sub>(t)__
__(a.x<sub>1</sub>[t] + b.x<sub>2</sub>(t)) = (a.y<sub>1</sub>(t) + b.y<sub>2</sub>(t)__ 

__T[a.x<sub>1</sub>[t] + b.x<sub>2</sub>(t)] = a.T[x<sub>1</sub>(t)] + b.T[x<sub>2</sub>(t)]__   

![](/../images/FT1_3.png)

Note: if an input is 0, the output is also 0.
#### Time propiety
Systems where the output for a particular input does not change deppending on when that input was applied.
### convolution sum
### Frequency domain



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

  



