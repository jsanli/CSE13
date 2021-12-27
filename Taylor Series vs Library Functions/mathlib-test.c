#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctel"
#define M_PI    3.14159265358979323846

int main(int argc, char **argv) {
    // contains code from Eugene's labsection on 1/19/21
    int opt = 0;
    bool do_sin, do_cos, do_tan, do_exp, do_log;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            do_sin = true;
            do_cos = true;
            do_tan = true;
            do_exp = true;
            do_log = true;
            break;
        case 's': do_sin = true; break;
        case 'c': do_cos = true; break;
        case 't': do_tan = true; break;
        case 'e': do_exp = true; break;
        case 'l': do_log = true; break;
        default: fprintf(stderr, "Usage: %s -[asctel]\n", argv[0]);
        }
    }
    double y = -2.0 * M_PI;
    if (do_sin) {
        puts("  x            Sin              Library        Difference");
        puts("  -            ---              -------        ----------");
        while (y < 2.0 * M_PI) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", y, Sin(y), sin(y), Sin(y) - sin(y));
            y += 0.1;
        }
    }
    if (do_cos) {
        y = -2.0 * M_PI;
        puts("  x            Cos              Library        Difference");
        puts("  -            ---              -------        ----------");
        while (y < 2.0 * M_PI) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", y, Cos(y), cos(y), Cos(y) - cos(y));
            y += 0.1;
        }
    }
    if (do_tan) {
        y = -M_PI / 3.0;
        puts("  x            Tan              Library        Difference");
        puts("  -            ---              -------        ----------");
        while (y < M_PI / 3) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", y, Tan(y), tan(y), Tan(y) - tan(y));
            y += 0.1;
        }
    }
    if (do_exp) {
        y = 1.0;
        puts("  x            Exp              Library        Difference");
        puts("  -            ---              -------        ----------");
        while (y < 10.0) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", y, Exp(y), exp(y), Exp(y) - exp(y));
            y += 0.1;
        }
    }
    if (do_log) {
        y = 1.0;
        puts("  x            Log              Library        Difference");
        puts("  -            ---              -------        ----------");
        while (y < 10.0) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", y, Log(y), log(y), Log(y) - log(y));
            y += 0.1;
        }
    }

    return 0;
}
