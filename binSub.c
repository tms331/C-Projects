#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char buff;
    int y = 7;
    int realMinuend[8];
    int realSubtrahend[8];
    char minuend[8];

    for (int i = 7; 0 <= i; i--) {
        fscanf(fp, " %c", &buff);
        minuend[i] = buff;
    }

    // notice that you are reading two different lines; caution with reading
    char subtrahend[8];
    for (int i = 7; 0 <= i; i--) {
        fscanf(fp, " %c", &buff);
        subtrahend[i] = buff;
    }
    
    while(y >= 0){
        realMinuend[y] = minuend[y] - '0';
        y--;
    } 
    
    y = 7;
    while(y >= 0){
        realSubtrahend[y] = subtrahend[y] - '0';
        y--;
    } 

    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND
    // Negate the subtrahend
    // flip all bits
    
    int k = 7;
    while(k >= 0){
        
        if(realSubtrahend[k] == 0){
            realSubtrahend[k] = 1;

        }else if(realSubtrahend[k] == 1){
            realSubtrahend[k] = 0;

        }
        k--;
    }
    
    // add one
    bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    int difference[8];

    for (int i = 0; i < 8; i++) { // iterate from LSB to MSB (right to left)

    if(carry == false){

        if (realMinuend[i] == 1 && realSubtrahend[i] == 1){
            difference[i] = 0;
            carry = true;

        }else if((realMinuend[i] == 0 && realSubtrahend[i] == 1) || (realMinuend[i] == 1 && realSubtrahend[i] == 0)){
            difference[i] = 1;
            carry = false;

        }else if(realMinuend[i] == 0 && realSubtrahend[i] == 0){
            difference[i] = 0;
            carry = false;
        }

    }else{ //if carry == true;

        if (realMinuend[i] == 1 && realSubtrahend[i] == 1){
            difference[i] = 1;
            carry = true;

        }else if((realMinuend[i] == 0 && realSubtrahend[i] == 1) || (realMinuend[i] == 1 && realSubtrahend[i] == 0)){
            difference[i] = 0;
            carry = true;

        }else if(realMinuend[i] == 0 && realSubtrahend[i] == 0){
            difference[i] = 1;
            carry = false;
        }

    }

}

    // print the difference bit string
    for (int i = 7; 0 <= i; i--){
        printf("%d", difference[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}