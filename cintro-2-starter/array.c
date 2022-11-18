/* Program demonstrating arrays in C. */

#include <stdio.h>

int main() {
    int x = 0;
    int array_stack[10];

    //Write some numbers to the array on the stack
    for (int i = 0; i < 10; i++) {
        array_stack[i] = i;
    }

    // Writing past the array results in weirdness.
    printf("x value before writing to array_stack[10]: %i\n", x);
    //array_stack[10] = 5;
    printf("x value after writing to array_stack[10]: %i\n", x); //the memory is being relocated when you uncomment the line

}