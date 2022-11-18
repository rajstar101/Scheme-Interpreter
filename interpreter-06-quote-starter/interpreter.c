#include "linkedlist.h"
#include "parser.h"
#include "talloc.h"
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>

void evaulationError(){
    printf("Evaluation error\n");
    texit(0);
}

Frame *newFrame(Value *bindings, Frame *parent){
    Frame *newFrame = talloc(sizeof(Frame));
    newFrame->parent = parent;
    newFrame->bindings = bindings;
    return newFrame;
}

Value *lookUpSymbol(Value *tree, Frame *frame){ //find bindings
    Frame *currFrame = frame;
    Value *currBindings;
    char *currSymbo = tree->s;
    while(currFrame != NULL){
        currBindings = currFrame->bindings;
        while(!isNull(currBindings)){
            if(strcmp(currSymbo, car(car(currBindings))->s)==0){
                return car(cdr(car(currBindings)));
            }
            currBindings = cdr(currBindings); //am I checking through bindings right?
        }
        currFrame = currFrame->parent;
    }
    evaulationError();
    return tree; //what else do we return
}

Value *eval(Value *tree, Frame *frame) {
    switch (tree->type)  {
        case INT_TYPE: {
            return tree;
            break;
        }
        case DOUBLE_TYPE: {
            return tree;
            break;
        }
        case STR_TYPE: {
            return tree;
            break;
        }
        case BOOL_TYPE: {
            return tree;
            break;
        }
        case SYMBOL_TYPE: {
            Value *symbo = lookUpSymbol(tree, frame);
            return eval(lookUpSymbol(tree, frame), frame);
            break;
        }  
        case CONS_TYPE: {
            Value *first = car(tree);
            Value *args = cdr(tree);

        // Sanity and error checking on first...

            if (!strcmp(first->s,"if")) { //if it is a if statement
                if(!isNull(args)){
                    if(!isNull(cdr(args))){
                        if(!isNull(cdr(cdr(args)))){
                            ;
                        } else {
                            evaulationError();
                        }
                    } else {
                        evaulationError();
                    }
                } else {
                    evaulationError();
                }
                Value *tUf = eval(car(args), frame);
                args = cdr(args);
                Value *ifState;
                if(strcmp(tUf->s, "#F") == 0 || strcmp(tUf->s, "#f") == 0){
                    ifState = car(cdr(args));
                } else {
                    ifState = car(args);
                };
                Value *ifResult = eval(ifState, frame);
                return ifResult;
            }
            else if (!strcmp(first->s, "let")){
                Value *oldBindings = car(args);
                Value *newBindings = makeNull(); //transferred the defininion list
                Value *newVariable;
                if(isNull(car(oldBindings))){
                    newBindings = makeNull();
                } else {
                    if(isNull(car(car(oldBindings)))){
                        evaulationError();
                    }
                    while(!isNull(oldBindings)){//car(args) is the new bindings
                        newVariable = makeNull();
                        newVariable = cons(car(car(oldBindings)), newVariable);
                        newVariable = cons(eval(car(cdr(car(oldBindings))), frame), newVariable);
                        newVariable = reverse(newVariable);
                        newBindings = cons(newVariable, newBindings);
                        oldBindings = cdr(oldBindings);
                    }
                }
                newBindings = reverse(newBindings);
                if(isNull(cdr(args))){
                    evaulationError();
                }
                Frame *letFrame = newFrame(newBindings, frame);
                Value *letReturn = eval(car(cdr(args)), letFrame); // you aint done here
                return letReturn;
            }
            else if (!strcmp(first->s, "quote")){
                Value *bitchDetector = makeBitch();
                Value *quoteNode = cons(bitchDetector, args);
                return quoteNode;
            }
        // .. future special forms here...
            else { // not a recognized special form
                evaulationError();
            }
            break;
        }
        default: {
            evaulationError();
        }
    }
    Value *useless;
    return useless;
}

void interpret(Value *tree){
    Frame *frame = talloc(sizeof(Frame));
    frame->parent = NULL;
    frame->bindings = makeNull();
    Value *curNode;
    while(!isNull(tree)){
        curNode = eval(car(tree), frame);
        if(car(curNode)->type == BITCH_TYPE){
            printTree(cdr(curNode));
            printf("\n");
        } else {
            if(curNode->type == INT_TYPE){
                printf("%i\n", curNode->i);
            } else if(curNode->type == DOUBLE_TYPE){
                printf("%f\n", curNode->d);
            } else {
                printf("%s\n", curNode->s);
            } 
        }
        tree = cdr(tree);
    }
}