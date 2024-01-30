#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    signed int input;
    int realArray[32];
    char tempArray[32];
    int current;
    int q = 0;
    int y = 0;
    int f = 0;
    int value = 0;
    int track = 8;
    int everyFourth = 1;
    fscanf(fp, "%d", &input);

    // print bits; you will see this kind of for loop often in this assignment
    for ( int bit=sizeof(signed int)*8-1; 0<=bit; bit-- ) {
        size_t bit_val = ((1<<1)-1) & input>>bit*1; // shift and mask
        char character = bit_val ? '1' : '0';
        tempArray[q] = character;
        q++;
    }


    while(y < 32){
        realArray[y] = tempArray[y] - '0';
        y++;
    }

    while(f < 32){

        current = realArray[f];

        value = value + (current * track);

        track = track / 2;

        if(everyFourth % 4 == 0){

            if(everyFourth > 16){
                printf("%x", value);

            }
            value = 0;
            track = 8;
        }


        everyFourth++;
        f++;
    }
    printf("\n");

    return EXIT_SUCCESS;

}