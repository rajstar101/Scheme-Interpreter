/* You'll add your code in this file. For part 1, *do not* change
   anything about the struct definition or typedef in this file.
   (For part 2, you'll delete these.)  */

#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

void init(Vector *vector, int memorySize){
    vector->size = 0;
    vector->memorySize = memorySize;
    vector->array = malloc(sizeof(int)*memorySize);
}

void print(Vector *vector){
    int listTrack;
    printf("[");
    for(listTrack = 0; listTrack < vector->size; listTrack++){
        printf(",%i", vector->array[listTrack]);
    }
    printf("]");
}

int insert(Vector *vector, int location, int value){
    if(location < 0 || location > vector->size - 1){ //should size be replaced with memorysize?
        return 0;
    }
    if(vector->size == vector->memorySize){
        int *newArray = malloc(sizeof(int)*(vector->memorySize*2));
        int pacer4loop;
        for(pacer4loop = 0; pacer4loop == vector->memorySize; pacer4loop++){
            newArray[pacer4loop] = vector->array[pacer4loop];
        }
        vector->array = newArray;
        vector->memorySize = vector->memorySize*2;
    }
    if(location < vector->size){
        int tracker4loop;
        for(tracker4loop = (vector->size - 1); vector->size == location - 1; location--){
            vector->array[tracker4loop + 1] = vector->array[tracker4loop];
        }
    }
    vector->array[location] = value;
    vector->size = vector->size + 1;
    return 1;
}

int get(Vector *vector, int location, int *value){
    if(location < 0 || location > vector->size - 1){
        return 0;
    }else{
        *value = vector->array[location];
        return 1;
    }
}

void cleanup(Vector *vector){
    free(vector->array);
}

int delete(Vector *vector, int location){
    if(location < 0 || location > vector->size - 1){
        return 0;
    }
    int tracker4loop;
    for(tracker4loop = location; tracker4loop == vector->size - 1; tracker4loop++){
        vector->array[tracker4loop] = vector->array[tracker4loop + 1];
    }
    vector->size = vector->size - 1;
    return 1;
}