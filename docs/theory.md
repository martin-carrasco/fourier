# Fourier Transforms: Background theory

## Signal Processing

### Discrete-time signals

Discrete-time signals are represented as sequences of numbers $x$, in which the $n^{th}$ number in the sequence is denoted $x[n]$ is formally written as:

`Eq. 2.1`:
$$
x = \{x [n] \} \quad -\infty < n < \infty
$$

If such sequence arises from periodic sampling of an analog signal $x_a(t)$, the numeric value of the nth number in the sequence is equal to the value of the analog signal, $x_a(t)$, at time $nT$.

`Eq. 2.2`:
$$
x = x_a(nT) \quad -\infty < n < \infty
$$

The quantity $T$ is the _sampling period_, and its reciprical is the _sampling frequency_.

The _unit sample sequence_ is defined as the sequence:

`Eq. 2.3`:
$$
\partial[n] =
\begin{cases}
  0, & n \neq 0, \\
  1, & n =  0.
\end{cases}
$$

_Note_: the unit sample sequence plays the same role for discrete-time signals and systems that the unit impulse function (Dirac delta function) does for continuous-time ssignals and systens. The unit samples sequence is often referred as an _impulse_.

One important aspects of the impulse sequence is that and arbitrary sequence can be represented as a sum of scaled, delayed impulses.

`Eq. 2.5`:
$$
x[n] = \sum_{k=-\infty}^{\infty}x[k]\partial[n-k]
$$

The _unit step sequence_ is defined as:

`Eq. 2.6`:
$$
u[n] =
\begin{cases}
  1, & n \geq 0, \\
  0, & n <  0.
\end{cases}
$$

## Discrete-time systems

A discrete-time system is defined mathematically as a transformation or operator that maps an input sequence with values $x[n]$ into an output sequence with values $y[n]$.

`Eq. 2.19`
$$
y[n] = T{x[n]}
$$

## Linear Systems
The class of linear systems is defined by the principle of superposition. If $y_1[n]$ and $y_2[n]$ are the responses of a system when $x_1[n]$ and $x_2[n]$ are the respective inputs, then the system is linear iff it holds for the _additive property_ and the _homogeneity_ / _scaling property_.

The principle of superposition can be defined as:

`Eq. 2.24`
$$
T{ax_1[n] + bx_2[n]} = aT{x_1[n]} + bT{x_2[n]}
$$

## Time-Invariant systems

A time-invariant system (also, shift-invariant system) is a system for which a time shift or delay of the input sequence causes a corresponding shift in the output sequence.
## LTI systems (linear and time invariant)

+ Must abide linearity property (additivity and homogeneity principles)
+ If the linearity property is combined with the representation of a general sequence a s a linear combination of delayed impulses (`Eq. 2.5`), it follows that a linear system can be completely characterized by its impulse response.
+ Specifically, let $h_k[n]$ be the response of the system to the input $\partial[n-k]$, an impulse ocurring at $n = k$. Then, using `Eq. 2.5` to represent the input it follows that:

`Eq. 2.47`
$$
y[n] = T{ \sum_{k=-\infty}^{\infty} x[k]\partial[n - k] }
$$

and the principle of superposition in `Eq. 2.24`, we can write

`Eq. 2.48`
$$
y[n] = \sum_{k=-\infty}^{\infty} T{x[k]\partial[n - k]} = \sum_{k=-\infty}^{\infty} T{x[k]h_k[n]}
$$


