#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <time.h>

double fabs (double value) {
    return value < 0.0 ? -value : value;
}

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    
    // The problem we are trying to solve is:
    // r^n = x
    // given n and x, find r.
    // n is a positive integer larger than 0.
    // x is a positive floating point value.
    // https://en.wikipedia.org/wiki/Nth_root
    // r needs to be found such that r is within the answer value specified by precision.

    double x;
    fscanf(fp, "%lf", &x);

    size_t n;
    fscanf(fp, "%ld", &n);

    double precision;
    fscanf(fp, "%lf", &precision);

    // The easiest way to solve this in C is to invoke the pow() function as follows.
    // Unfortunately, as part of this assignment we are not allowing importing math.h.
    // Even if you import math.h, that Makefile does not link the math library.
    // So, you will need to write a separate algorithm to find the n-th root.
    // printf("%f", pow(x, 1.0/n));

    // There are many algorithms that can find the n-th root (Newton-Raphson, etc.).
    // A straightfoward one for our purposes is a binary search along the number line.
    // You should review how the binary search algorithm works.

    srand(time(NULL));
    double guess_r_max = x < 1.0 ? 1.0 : x; // Think: why is this the maximum guess?
    double guess_r_min = 0.0;

    double guess_r = ( (double)rand() ) / RAND_MAX;
    double error = DBL_MAX;
    double estimate = 1;
    
    while ( precision < fabs(error) ) {
        estimate = 1;
        int tmp = 0;

        double randomNum = (double)rand() / RAND_MAX;
        double range = (guess_r_max - guess_r_min) * randomNum;
        guess_r = guess_r_min + range;

        while(tmp < n){
            estimate = estimate * guess_r;
            tmp++;
        }

        if(estimate > x){
            guess_r_max = guess_r;
            error = estimate - x;

        }else if(x > estimate){
            guess_r_min = guess_r;
            error = x - estimate;

        }else{
            error = estimate - x;
        }

    }

    printf("%f\n", guess_r);
    return EXIT_SUCCESS;

}