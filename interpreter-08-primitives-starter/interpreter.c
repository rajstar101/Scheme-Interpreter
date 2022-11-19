#include "linkedlist.h"
#include "parser.h"
#include "talloc.h"
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>

void evaulationError(){
    printf("Evaulation error\n");
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
            currBindings = cdr(currBindings);
        }
        currFrame = currFrame->parent;
    }
    printf("line 33: ");
    evaulationError();
    return tree;
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
                            printf("LINE 77: ");
                            evaulationError();
                        }
                    } else {
                        printf("LINE 81: ");
                        evaulationError();
                    }
                } else {
                    printf("LINE 85: ");
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
                        printf("LINE 105: ");
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
                    printf("LINE 117: ");
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
            else {
                Value *elseNode = eval(first, frame);
                if(elseNode->type == CLOSURE_TYPE){
                    int argLength = length(args);
                    int paramLength = length(elseNode->cl.paramNames);
                    if(isNull(car(elseNode->cl.paramNames))){
                        paramLength = 0;
                    }
                    if(paramLength != argLength){
                        printf("line 155: ");
                        evaulationError();
                        return makeNull();
                    }else{
                        Value *params = elseNode->cl.paramNames;
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
                        Frame *lambFrame = newFrame(newBindings, elseNode->cl.frame);
                        Value *lambResult = eval(elseNode->cl.functionCode, lambFrame);
                        return lambResult;
                    }
                }
                if(elseNode->type == PRIMITIVE_TYPE){
                    Value *eval_tree = makeNull();
                    Value *prime_args = args;
                    int i = 0;
                    while(!isNull(prime_args)){
                        printf("%i\n", i);
                        eval_tree = cons(eval(car(prime_args), frame), eval_tree);
                        prime_args = cdr(prime_args);
                        i = i + 1;
                    }
                    eval_tree = reverse(eval_tree);
                    Value *results = elseNode->pf(eval_tree);
                    return results;
                }
            }
            break;
        }
        default: {
            printf("LINE 196: ");
            evaulationError();
        }
    }
    Value *useless;
    return useless;
}

Value *primeSum(Value *eval_tree){
    double currSum = 0;
    while(!isNull(eval_tree)){
        Value *eval_tree_car = eval_tree->c.car;
        if(eval_tree_car->type == INT_TYPE){
            currSum = currSum + eval_tree_car->i;
        } else if(eval_tree_car->type == DOUBLE_TYPE){
            currSum = currSum + eval_tree_car->d;
        } else {
            printf("error caused by eval_tree: %s", eval_tree->s);
            printf("LINE 212: ");
            evaulationError();
            Value *useless;
            return useless;
        }
        eval_tree = cdr(eval_tree);
    }
    Value *primeSum_node = talloc(sizeof(Value));
    primeSum_node->type = DOUBLE_TYPE;
    primeSum_node->d = currSum;
    return primeSum_node;
}

Value *primeNull(Value *eval_tree){
    printf("we in null");
    char *tUf;
    if(isNull(car(eval_tree))){
        tUf = "#t";
    } else {
        tUf = "#f";
    }
    Value *primeNull_node = talloc(sizeof(Value));
    primeNull_node->type = BOOL_TYPE;
    primeNull_node->s = tUf;
    return primeNull_node;
}

void oppPrimBind(char *opp, Value *(*function)(Value *), Frame *frame){
    Value *opp_bind = makeNull();
    Value *variable = talloc(sizeof(Value));
    variable->type = SYMBOL_TYPE;
    variable->s = opp;
    opp_bind = cons(variable, opp_bind);
    Value *opperation = talloc(sizeof(Value));
    opperation->type = PRIMITIVE_TYPE;
    opperation->pf = function;
    opp_bind = cons(opperation, opp_bind);
    opp_bind = reverse(opp_bind);
    frame->bindings = cons(opp_bind, frame->bindings);
}

void interpret(Value *tree){
    Frame *frame = talloc(sizeof(Frame));
    frame->parent = NULL;
    frame->bindings = makeNull();
    //initialize some primitives
    oppPrimBind("+", primeSum, frame);
    oppPrimBind("null?", primeNull, frame);
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