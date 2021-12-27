#include "mathlib.h"

#include <math.h>

#define EPSILON 1e-14

static inline double Abs(double x) {
    return x < 0 ? -x : x;
}

//Inspired by Eugene's Section on 1/19/21
double Sin(double x) {
    fmod(x, 2 * M_PI);
    double num = x;
    double den = 1.0;
    double sum = x / den;
    double term = x / den;
    for (double k = 3.0; Abs(term) > EPSILON; k += 2.0) {
        num *= -x * x;
        den *= (k - 1) * k;
        term = num / den;
        sum += term;
    }
    return sum;
}

double Cos(double x) {
    fmod(x, 2 * M_PI);
    double num = 1.0;
    double den = 1.0;
    double sum = num / den;
    double term = num / den;
    for (double k = 2.0; Abs(term) > EPSILON; k += 2.0) {
        num *= -x * x;
        den *= (k - 1) * k;
        term = num / den;
        sum += term;
    }
    return sum;
}

double Tan(double x) {
    return (Sin(x) / Cos(x));
}

//Inspired by Eugene's Section on 1/19/21
double Exp(double x) {
    double term = 1.0;
    double sum = term;
    for (double k = 1.0; Abs(term) > EPSILON; k += 1.0) {
        term *= (x / k);
        sum += term;
    }
    return sum;
}

//Inspired by Eugene's Section on 1/19/21
double Log(double x) {
    double y = 1.0;
    double p = Exp(y);
    while (Abs(p - x) > EPSILON) {
        y = y + (x - p) / p;
        p = Exp(y);
    }
    return y;
}
