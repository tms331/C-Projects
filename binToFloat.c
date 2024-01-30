#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23


int main(int argc, char *argv[]) {

    char fullArray[32];
    int realArray[32];
    int fracArray[32];
    int expArray[10];

    char input;
    int track = 128;
    double baseTrack = 0.5;
    int k = 0;
    int i = 0;
    int sign;
    
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    while(k < 32){
        fscanf(fp, "%c", &input);
        fullArray[k] = input;
        k++;
    }

    while(i < 32){
        realArray[i] = fullArray[i] - '0';
        i++;
    }
    sign = realArray[0];


    k = 1;
    while(k < 9){
        expArray[k] = realArray[k];
        k++;
    }

    k = 9;
    while(k < 32){
        fracArray[k] = realArray[k];
        k++;
    }

    // float number = *(float *)&binary; // you are not allowed to do this.
    // sign = (-1)^s
    // bias = 2^(k-1) - 1    k = 8 for float

    // E, encoded in exp field, E = exp - bias
    
    k = 1;
    int current;
    int e = 0;

    while(k < 9){

        current = expArray[k]; // iterate through frac bits

        e = e + (current * track); // update m if bit 1 one

        track = track / 2; // update the value at each bit

        k++; // continue if we haven't been through all bits

    }
    e = e - 127;
    k = 9;
    int current2;
    double m = 1.0;

    while(k < 32){

        current2 = fracArray[k]; // iterate through frac bits

        m = m + (current2 * baseTrack); // update m if bit 1 one

        baseTrack = baseTrack / 2; // update the value at each bit

        k++; // continue if we haven't been through all bits

    }
    
    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    // sign * m * 2^e

    double number = ldexp ( m, e );
    number = sign ? -number : number;
    printf("%f\n", number);

    
    fclose(fp);    
    return EXIT_SUCCESS;

}