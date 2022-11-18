#include <stdlib.h>
#include "value.h"
#include <stdio.h>

Value *Head = NULL; //should I make the type = nulltype instead of the node

void talloc_connector(Value *prevNode, Value *newNode){ //add new node to list
    if(Head == NULL){
        Head = newNode;
        return;
    }
    Value *lastNode = prevNode;
    while(lastNode->c.cdr != NULL){
        lastNode = lastNode->c.cdr;
    }
    lastNode->c.cdr = newNode; //why I don't need to derefrence?
    return;
}

void *talloc(size_t size){
    Value *node = malloc(sizeof(Value)); //we are making a new node
    void *malloced_return = malloc(size);
    node->type = CONS_TYPE;
    node->c.car = malloc(sizeof(Value));
    node->c.car->type = PTR_TYPE;
    node->c.car->p = malloced_return;
    node->c.cdr = NULL;
    talloc_connector(Head, node);
    return malloced_return; // I FORGOT WHY I ADDED return MALLOCED_RETURN
}

void tfree_h(Value *node){
    if(node == NULL){
        printf("we made it");
        return;
    } else {
        tfree_h(node->c.cdr);
        free(node->c.car);
        free(node); //its based on the idea that we will need to finish this function first before we continue to the free()
        return;
    }
}

void tfree(){
    tfree_h(Head); //I called the helper funciton
}

void texit(int status){
    tfree();
    exit(status);
}

/*
After talking with Chisom I know that I was adding nodes to my linked list in a
weird way so while I wait for my line in the queue for office hours, I'll write
an alternative for talloc that would add nodes to the front of the list which
would make my code alot easier to read.

alternative talloc functions:

Value *talloc_cons(Value *newCar, Value *newCdr){
    Value *value = talloc(sizeof(Value));
    value->type = CONS_TYPE;
    value->c.car = newCar;
    value->c.cdr = newCdr;
    return value;
}

void *talloc(size_t size){
    void *malloced_return = malloc(size); 
    Value *token = malloc(sizeof(Value));
    token->type = PTR_TYPE;
    token->p = malloced_return;
    *Head = talloc_cons(node, Head); //do I not need to pointer here
    return malloced_return;
}
*/