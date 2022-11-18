#include <stdio.h> // required for printf

int main() {
  float f;
  printf("What is the temperature in degrees Fahrenheit: ");
  scanf("%f", &f);
  if (f > -459.67) {
  float c = (f - 32) * 5/9;
  printf("%f degrees Fahrenheit is %f degrees Celsius.", f, c);
  } else {
    printf("Invalid temperature.");
  }
}