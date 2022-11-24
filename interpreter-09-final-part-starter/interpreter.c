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

Value *lookUpSymbol(Value *tree, Frame *frame){
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

void changeSymbol(Value *variable, Value *newValue, Frame *frame){
    Frame *currFrame = frame;
    Value *currBindings;
    char *currSymbo = car(variable)->s;
    int Check = 0;
    while(currFrame != NULL){
        currBindings = currFrame->bindings;
        Value *newBindings = makeNull();
        while(!isNull(currBindings)){
            if(strcmp(currSymbo, car(car(currBindings))->s)==0){
                Value *newBinding = makeNull();
                newBinding = cons(newValue, newBinding);
                newBinding = cons(car(variable), newBinding);
                newBindings = cons(newBinding, newBindings);
                Check = 1;
            } else {
                newBindings = cons(car(currBindings), newBindings);
            }
            currBindings = cdr(currBindings);
        }
        currFrame->bindings = newBindings;
        currFrame = currFrame->parent;
    }
    if(Check == 0){
        printf("line 59: ");
        evaulationError();
    }
}

Value *eval(Value *tree, Frame *frame) {
    Value *returnNode;
    while(!isNull(tree)){
        switch (tree->type)  {
            case INT_TYPE: {
                returnNode = tree;
                return returnNode;
                break;
            }
            case DOUBLE_TYPE: {
                returnNode = tree;
                return returnNode;
                break;
            }
            case STR_TYPE: {
                returnNode = tree;
                return returnNode;
                break;
            }
            case BOOL_TYPE: {
                returnNode = tree;
                return returnNode;
                break;
            }
            case SYMBOL_TYPE: {
                returnNode = lookUpSymbol(tree, frame);
                return returnNode;
                break;
            }
            case CLOSURE_TYPE: {
                returnNode = tree;
                return returnNode;
                break;
            }
            case CONS_TYPE: {
                fflush(stdin);
                Value *first = car(tree);
                Value *args = cdr(tree);

            // Sanity and error checking on first...
                if (!strcmp(first->s,"if")) { 
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
                    returnNode = eval(ifState, frame);
                    return returnNode;
                }
                else if (!strcmp(first->s, "let")){
                    Value *oldBindings = car(args);
                    Value *newBindings = makeNull();
                    Value *newVariable;
                    if(isNull(car(oldBindings))){
                        newBindings = makeNull();
                    } else {
                        if(isNull(car(car(oldBindings)))){
                            printf("LINE 105: ");
                            evaulationError();
                        }
                        while(!isNull(oldBindings)){
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
                    returnNode = eval(car(cdr(args)), letFrame);
                    return returnNode;
                }
                else if (!strcmp(first->s,"let*")){
                    Value *oldBindings = car(args);
                    Frame *currFrame = frame;
                    while(!isNull(oldBindings)){
                        Value *newBinding = makeNull();
                        newBinding = cons(car(car(oldBindings)), newBinding);
                        newBinding = cons(eval(car(cdr(car(oldBindings))), currFrame), newBinding);
                        newBinding = reverse(newBinding);
                        Value *newBindings = cons(newBinding, makeNull());
                        currFrame = newFrame(newBindings, currFrame);
                        oldBindings = cdr(oldBindings);
                    }
                    returnNode = eval(car(cdr(args)), currFrame);
                    return returnNode;
                }
                else if(!strcmp(first->s, "letrec")){
                    Value *oldBindings = car(args); //phase one: beginning
                    Value *newBindings = makeNull();
                    Value *newVariable;
                    if(isNull(car(oldBindings))){
                        newBindings = makeNull();
                    } else {
                        if(isNull(car(car(oldBindings)))){
                            printf("LINE 105: ");
                            evaulationError();
                        }
                        while(!isNull(oldBindings)){
                            newVariable = makeNull();
                            newVariable = cons(car(car(oldBindings)), newVariable);
                            newVariable = cons(car(cdr(car(oldBindings))), newVariable);
                            newVariable = reverse(newVariable);
                            newBindings = cons(newVariable, newBindings);
                            oldBindings = cdr(oldBindings);
                        }
                    }
                    newBindings = reverse(newBindings);
                    Frame *letrecFrame = newFrame(newBindings, frame); //new frame declared
                    Value *letrecFX = lookUpSymbol(car(car(cdr(args))), letrecFrame);
                    Value *eval_letrec = car(cdr(cdr(letrecFX)));
                    Value *newnewVariable = car(car(cdr(letrecFX)));
                    Value *newnewValue = eval(car(cdr(car(cdr(args)))), frame);
                    Value *newnewBindings = makeNull(); //new frame for actual evaluation
                    newnewBindings = cons(newnewValue, newnewBindings);
                    newnewBindings = cons(newnewVariable, newnewBindings);
                    newnewBindings = cons(newnewBindings, newBindings);
                    Frame *newnewFrame = newFrame(newnewBindings, frame);
                    printTree(newnewBindings);
                    printTree(eval_letrec);
                    returnNode = eval(eval_letrec, newnewFrame);
                    return returnNode;
                }
                else if (!strcmp(first->s, "quote")){
                    returnNode = args->c.car;
                    return returnNode;
                }
                else if (!strcmp(first->s, "define")){
                    Value *oldBindings = frame->bindings;
                    Value *var2bind = makeNull();
                    var2bind = cons(eval(car(cdr(args)), frame), var2bind);
                    var2bind = cons(car(args), var2bind);
                    var2bind = cons(var2bind, oldBindings);
                    frame->bindings = var2bind;
                    returnNode = makeNull();
                    return returnNode;
                }
                else if(!strcmp(first->s, "set!")){
                    changeSymbol(args, eval(car(cdr(args)), frame), frame);
                    returnNode = makeNull();
                    return returnNode;      
                }
                else if(!strcmp(first->s, "lambda")){
                    Value *lambNode = talloc(sizeof(Value));
                    lambNode->type = CLOSURE_TYPE;
                    lambNode->cl.frame = frame;
                    lambNode->cl.functionCode = car(cdr(args));
                    lambNode->cl.paramNames = car(args);
                    returnNode = lambNode;
                    return returnNode;
                } 
                else if(!strcmp(first->s, "begin")){
                    if(isNull(args)){
                        Value *emptyNode = talloc(sizeof(Value));
                        emptyNode->type = VOID_TYPE;
                        returnNode = emptyNode;
                        return returnNode;
                    }
                    while(!isNull(cdr(args))){
                        eval(car(args), frame);
                        args = cdr(args);
                    }
                    returnNode = eval(car(args), frame);
                    return returnNode;
                }
                else if(!strcmp(first->s, "and")){
                    while(!isNull(args)){
                        if(strcmp(eval(car(args), frame)->s, "#f")==0||strcmp(eval(car(args), frame)->s, "#F")==0){
                            Value *falseNode = talloc(sizeof(Value));
                            falseNode->type = BOOL_TYPE;
                            falseNode->s = "#f";
                            returnNode = falseNode;
                            return returnNode;
                        }
                        args = cdr(args);
                    }
                    Value *trueNode = talloc(sizeof(Value));
                    trueNode->type = BOOL_TYPE;
                    trueNode->s = "#t";
                    returnNode = trueNode;
                    return returnNode;
                }
                else if(!strcmp(first->s, "or")){
                    while(!isNull(args)){
                        if(strcmp(eval(car(args), frame)->s, "#t")==0||strcmp(eval(car(args), frame)->s, "#T")==0){
                            Value *trueNode = talloc(sizeof(Value));
                            trueNode->type = BOOL_TYPE;
                            trueNode->s = "#t";
                            return trueNode;
                        }
                        args = cdr(args);
                    }
                    Value *falseNode = talloc(sizeof(Value));
                    falseNode->type = BOOL_TYPE;
                    falseNode->s = "#f";
                    returnNode = falseNode;
                    return returnNode;
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
                            returnNode = lambResult;
                            return returnNode;
                        }
                    }
                    if(elseNode->type == PRIMITIVE_TYPE){
                        Value *eval_tree = makeNull();
                        Value *prime_args = args;
                        while(!isNull(prime_args)){
                            eval_tree = cons(eval(car(prime_args), frame), eval_tree);
                            prime_args = cdr(prime_args);
                        }
                        eval_tree = reverse(eval_tree);
                        Value *results = elseNode->pf(eval_tree);
                        returnNode = results;
                        return returnNode;
                    }
                }
                break;
            }
            default: {
                printf("LINE 196: ");
                evaulationError();
            }
        }
        tree = cdr(tree);
    }
    return returnNode;
}

Value *primeSum(Value *eval_tree){
    int currSum = 0;
    while(!isNull(eval_tree)){
        Value *eval_tree_car = eval_tree->c.car;
        if(eval_tree_car->type == INT_TYPE){
            currSum = currSum + eval_tree_car->i;
        } else if(eval_tree_car->type == DOUBLE_TYPE){
            double doub_currSum = 0 + currSum;
            while(!isNull(eval_tree)){
                Value *doub_eval_tree_car = eval_tree->c.car;
                if(doub_eval_tree_car->type == INT_TYPE){
                    doub_currSum = doub_currSum + doub_eval_tree_car->i;
                } else if (doub_eval_tree_car->type == DOUBLE_TYPE){
                    doub_currSum = doub_currSum + doub_eval_tree_car->d;
                } else {
                    printf("LINE 217: ");
                    evaulationError();
                    Value *useless;
                    return useless;
                }
                eval_tree = cdr(eval_tree);
            }
            Value *doub_primeSum_node = talloc(sizeof(Value));
            doub_primeSum_node->type = DOUBLE_TYPE;
            doub_primeSum_node->d = currSum;
            return doub_primeSum_node;
        } else {
            printf("LINE 212: ");
            evaulationError();
            Value *useless;
            return useless;
        }
        eval_tree = cdr(eval_tree);
    }
    Value *primeSum_node = talloc(sizeof(Value));
    primeSum_node->type = INT_TYPE;
    primeSum_node->i = currSum;
    return primeSum_node;
}

Value *primeNull(Value *eval_tree){
    char *tUf;
    if(isNull(car(eval_tree))){
        tUf = "#t";
    } else {
        tUf = "#f";
        if(strcmp(eval_tree->s, "(null)")==0){
            tUf = "#t";
        }
        if(car(eval_tree)->type == CONS_TYPE){
            if(isNull(car(car(eval_tree)))){
                tUf = "#t";
            } else {
                tUf = "#f";
            }
        }
    }
    Value *primeNull_node = talloc(sizeof(Value));
    primeNull_node->type = BOOL_TYPE;
    primeNull_node->s = tUf;
    return primeNull_node;
}

Value *primeCons(Value *eval_tree){
    Value *node = cons(car(eval_tree), car(cdr(eval_tree)));
    return node;
}

Value *primeCar(Value *eval_tree){
    Value *node = car(car(eval_tree));
    return node;
}

Value *primeCdr(Value *eval_tree){
    Value *node = cdr(car(eval_tree));
    return node;
}

Value *primeMinus(Value *eval_tree){
    int val2 = car(cdr(eval_tree))->i;
    int val1 = car(eval_tree)->i;
    Value *node = talloc(sizeof(Value));
    node->type = INT_TYPE;
    node->i = val1-val2;
    return node;
}

Value *primeLess(Value *eval_tree){
    int val2 = car(cdr(eval_tree))->i;
    int val1 = car(eval_tree)->i;
    Value *node = talloc(sizeof(Value));
    node->type = BOOL_TYPE;
    if(val1 < val2){
        node->s = "#t";
    } else {
        node->s = "#f";
    }
    return node;
}

Value *primeGreat(Value *eval_tree){
    int val2 = car(cdr(eval_tree))->i;
    int val1 = car(eval_tree)->i;
    Value *node = talloc(sizeof(Value));
    node->type = BOOL_TYPE;
    if(val1 > val2){
        node->s = "#t";
    } else {
        node->s = "#f";
    }
    return node;
}


Value *primeEqual(Value *eval_tree){
    int val2 = car(cdr(eval_tree))->i;
    int val1 = car(eval_tree)->i;
    Value *node = talloc(sizeof(Value));
    node->type = BOOL_TYPE;
    if(val1 == val2){
        node->s = "#t";
    } else {
        node->s = "#f";
    }
    return node;
}

void primBind(char *opp, Value *(*function)(Value *), Frame *frame){
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
    primBind("+", primeSum, frame);
    primBind("null?", primeNull, frame);
    primBind("cons", primeCons, frame);
    primBind("car", primeCar, frame);
    primBind("cdr", primeCdr, frame);
    primBind("+", primeSum, frame);
    primBind("null?", primeNull, frame);
    primBind("cons", primeCons, frame);
    primBind("car", primeCar, frame);
    primBind("cdr", primeCdr, frame);
    primBind("<", primeLess, frame);
    primBind(">", primeGreat, frame);
    primBind("=", primeEqual, frame);
    primBind("-", primeMinus, frame);
    Value *curNode;

    while(!isNull(tree)){
        curNode = eval(car(tree), frame);
        printTree(curNode);
        printf("\n");
        tree = cdr(tree);
    }
}