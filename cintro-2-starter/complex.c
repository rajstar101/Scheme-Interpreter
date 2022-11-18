#include <stdio.h>
#include <stdlib.h>

struct Complex {
    double real;
    double imaginary;
};

void multiply_in_place(struct Complex *num1, struct Complex *num2){
    double realio = num1->real * num2->real - num1->imaginary * num2->imaginary;
    double imaginaryio = num1->real * num2->imaginary + num2->real * num1->imaginary;
    num1->real = realio, num2->real = realio;
    num1->imaginary = imaginaryio, num2->imaginary = imaginaryio;
}

void print_complex(struct Complex num, char label[3]) {
    printf("%s %10.2f + %10.2f i\n", label, num.real, num.imaginary);
}

int main(){
    struct Complex *e1 = malloc(sizeof(struct Complex));
    struct Complex *e2 = malloc(sizeof(struct Complex));
    printf("Enter real part of c1: ");
    scanf("%lf", &e1->real);
    printf("Enter imaginary part of c1: ");
    scanf("%lf", &e1->imaginary);
    printf("Enter real part of c2: ");
    scanf("%lf", &e2->real);
    printf("Enter imaginary part of c2: ");
    scanf("%lf", &e2->imaginary);
    printf("Before multiplication:\n");
    print_complex(*e1, "c1:");
    print_complex(*e2, "c2:");
    multiply_in_place(e1, e2);
    printf("After multiplication:\n");
    print_complex(*e1, "c1:");
    print_complex(*e2, "c2:");
    free(e1);
    free(e2);
}