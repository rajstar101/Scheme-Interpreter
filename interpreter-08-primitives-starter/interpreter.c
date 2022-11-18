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

Value *sumDoub(Value *tree, double currIntSum){
    
    ;//this for doub
}

Value *sumInt(Value *tree){
    float currSum = 0;
    while(!isNull(tree)){
        //add error checkers
        //needs to make a return statement here for doub
        currSum = currSum + tree->i;
        tree = cdr(tree); //I'm defrefrencing aint I
    }
    return currSum;
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
            return lookUpSymbol(tree, frame);
            break;
        }
        case CLOSURE_TYPE: {
            return makeNull();
            break;
        }
        case CONS_TYPE: {
            fflush(stdin);
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
                Value *bootyDetector = makeBooty();
                Value *quoteNode = cons(bootyDetector, args);
                return quoteNode;
            }
            else if (!strcmp(first->s, "define")){
                Value *oldBindings = frame->bindings;
                Value *var2bind = makeNull();
                var2bind = cons(eval(car(cdr(args)), frame), var2bind);
                var2bind = cons(car(args), var2bind);
                var2bind = cons(var2bind, oldBindings);
                frame->bindings = var2bind;
                return makeNull();
            }
            else if(!strcmp(first->s, "lambda")){
                Value *lambNode = talloc(sizeof(Value));
                lambNode->type = CLOSURE_TYPE;
                lambNode->cl.frame = frame;
                lambNode->cl.functionCode = car(cdr(args));
                lambNode->cl.paramNames = car(args);
                return lambNode;
            }
            else if(!strcmp(first->s, "+")){
                Value *lambNode = talloc(sizeof(Value));
                lambNode->type = PRIMITIVE_TYPE;
                lambNode->pf = %;
            }
            else {
                //check if its a lambda
                Value *lambNode = eval(first, frame);
                int argLength = length(args);
                int paramLength = length(lambNode->cl.paramNames);
                if(isNull(car(lambNode->cl.paramNames))){
                    paramLength = 0;
                }
                if(paramLength != argLength){
                    evaulationError();
                    return makeNull();
                }else{
                    Value *params = lambNode->cl.paramNames;
                    Value *values = args;
                    Value *newBindings = makeNull();
                    int x = length(args);
                    while(x>0){
                        Value *newVariables = makeNull();
                        newVariables = cons(eval(car(values), frame), newVariables);
                        newVariables = cons(car(params), newVariables);
                        newBindings = cons(newVariables, newBindings);
                        params = cdr(params);
                        values = cdr(values);
                        x = x - 1;
                    }
                    Frame *lambFrame = newFrame(newBindings, lambNode->cl.frame);
                    Value *lambResult = eval(lambNode->cl.functionCode, lambFrame);
                    return lambResult;
                }
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
        if(isNull(curNode)){
            ;
        }
        else if(curNode -> type == CONS_TYPE && car(curNode)->type == BOOTY_TYPE){
            ;
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