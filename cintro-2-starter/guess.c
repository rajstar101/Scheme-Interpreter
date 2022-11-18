#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void numberGuesser (int guess, int right, int points){
    int newGuess;
    if(guess == right){
        printf("Correct! Total guesses = %i\n", points);
    } else if(guess < 1 || guess > 100) {
        printf("Your number is out of range!\nPick a number between 1-100: ");
        scanf("%i", &newGuess);
        numberGuesser(newGuess, right, points); //I didn't want to increase the number of turns it took if the user was genuienly confused thats why I didn't increase points by one like I did to the other recursive stuff
    } else if(guess > right){
        printf("Too high!");
        printf("\nGuess again: ");
        scanf("%i", &newGuess);
        numberGuesser(newGuess, right, (points + 1));
    } else {
        printf("Too low!");
        printf("\nGuess again: ");
        scanf("%i", &newGuess);
        numberGuesser(newGuess, right, (points + 1));
    }
}

int main (){
    unsigned int seed;
    printf("Enter a random seed: ");
    scanf("%u", &seed);
    srandom(seed);
    int numOfGuess = 1;
    int magicNum = (random() % 100) + 1;
    int guessNum;
    printf("Guess a number: ");
    scanf("%i", &guessNum);
    numberGuesser(guessNum, magicNum, numOfGuess);
}