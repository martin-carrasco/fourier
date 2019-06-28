#ifndef __TYPES_H__
#define __TYPES_H__

#include <complex>
#include <iostream> 

typedef std::complex<double> cn;

struct RGBA_Complex {
    cn R, G, B, A; 


    RGBA_Complex(){
        R = G = B = A = 0;
    }
    RGBA_Complex(double real_val){
        R = real_val;
        G = real_val;
        B = real_val;
        A = real_val;
    }
    RGBA_Complex(double real_val, double complex_val){
        R = real_val;
        R.imag(complex_val);
        
        G = real_val;
        G.imag(complex_val);

        B = real_val;
        B.imag(complex_val);

        A = real_val;
        A.imag(complex_val);
    }
    RGBA_Complex operator*(const RGBA_Complex& channel){
        RGBA_Complex result;
        result.R = channel.R * R;
        result.G = channel.G * G;
        result.B = channel.B * B;
        result.A = channel.A * A;
        return result;
    }
    RGBA_Complex operator*(double num){
        RGBA_Complex result;
        result.R = R * num;
        result.G = G * num;
        result.B = B * num;
        result.A = A * num;

        return result;
    }
    RGBA_Complex operator+(const RGBA_Complex& channel){
        RGBA_Complex result;
        result.R = channel.R + R;
        result.G = channel.G + G;
        result.B = channel.B + B;
        result.A = channel.A + A;
        return result;
    }

    RGBA_Complex operator+(double num){
        RGBA_Complex result;
        result.R = R + num;
        result.G = G + num;
        result.B = B + num;
        result.A = A + num;
        return result;
    }

    RGBA_Complex operator-(const RGBA_Complex& channel){
        RGBA_Complex result;
        result.R = channel.R - R;
        result.G = channel.G - G;
        result.B = channel.B - B;
        result.A = channel.A - A;
        return result;
    }

    RGBA_Complex operator-(double num){
        RGBA_Complex result;
        result.R = R - num;
        result.G = G - num;
        result.B = B - num;
        result.A = A - num;
        return result;
    }

    RGBA_Complex operator/=(const RGBA_Complex& channel){
        RGBA_Complex result;
        result.R = channel.R / R;
        result.G = channel.G / G;
        result.B = channel.B / B;
        result.A = channel.A / A;
        return result;
    }

    RGBA_Complex operator/=(double num){
        RGBA_Complex result;
        result.R = R / num;
        result.G = G / num;
        result.B = B / num;
        result.A = A / num;
        return result;
    }
    friend std::ostream& operator <<(std::ostream &os, const RGBA_Complex& pixel){
        os << "( " << pixel.R << ", " << pixel.G << ", " << pixel.B << ", " << pixel.A << ")";  
        return os;
    }
};

#endif
