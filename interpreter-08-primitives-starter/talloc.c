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
        return;
    } else {
        tfree_h(node->c.cdr);
        free(node->c.car->p);
        free(node->c.car);
        free(node); //its based on the idea that we will need to finish this function first before we continue to the free()
        return;
    }
}

void tfree(){
    tfree_h(Head); //I called the helper funciton
    Head = NULL;
    
}

void texit(int status){
    tfree();
    exit(status);
}