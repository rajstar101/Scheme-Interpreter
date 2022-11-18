#include <stdio.h>
#include <stdlib.h>


void addOdds(int arr[], int startIdx, int stopSz, int *totalSum){
    if(startIdx >= stopSz){
        printf("The sum of the numbers at odd indices in your array is %i check", &totalSum);
    } else {
        *totalSum = *totalSum + arr[startIdx];
        addOdds(arr, (startIdx + 2), stopSz, totalSum);
    }
}

void stacker(int arr[], int curNum, int startIdx, int stopSz, int *totalSum){ //start is always 0 and stop is index - 1, start is also the number we indexing with
    if(startIdx == stopSz){
        addOdds(arr, 0, stopSz, totalSum);
    } else {
        arr[startIdx] = curNum;
        printf("Next number: ");
        int curcur;
        scanf("%i", &curcur);
        stacker(arr, curcur, (startIdx + 1), stopSz, totalSum);
    }
}

int main(){
    int *totalSum = malloc(sizeof(int));
    *totalSum = 0;
    int arrCount;
    printf("How many numbers do you want to include? ");
    scanf("%i", &arrCount);
    int sumStack[arrCount];
    printf("What number do you want to start at? ");
    int curNum;
    scanf("%i", &curNum);
    stacker(sumStack, curNum, 0, (arrCount - 1), totalSum);
    free(totalSum);
}