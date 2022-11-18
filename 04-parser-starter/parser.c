#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include <stdio.h>

Value *sub_parse(Value *tokens){
    Value *sub_parse_list = makeNull();
    *tokens = *cdr(tokens);
    if(car(tokens)->type == CLOSE_TYPE){
        sub_parse_list = cons(makeNull(), sub_parse_list);
        return sub_parse_list;
    }
    while(car(tokens)->type != CLOSE_TYPE || isNull(tokens)){
        if(car(tokens)->type == OPEN_TYPE){
            sub_parse_list = cons(sub_parse(tokens), sub_parse_list);
        } else {
            sub_parse_list = cons(car(tokens), sub_parse_list);
        }
        if(isNull(cdr(tokens))){
            printf("Syntax error: not enough close parentheses\n");
            texit(0);
        }
        *tokens = *cdr(tokens);
        }
    Value *reverse_sub_parse_list = reverse(sub_parse_list);
    return reverse_sub_parse_list;
}

Value *parse(Value *tokens){
    Value *parse_list = makeNull();
    while(!isNull(tokens)){
        if(car(tokens)->type == CLOSE_TYPE){
            printf("Syntax error: too many close parentheses\n");
            texit(0);
        }else if(car(tokens)->type == OPEN_TYPE){
            parse_list = cons(sub_parse(tokens), parse_list);
        }else if(isNull(tokens)){
            break;
        } else {
            parse_list = cons(car(tokens), parse_list);
        }
        if(isNull(cdr(tokens))){
            break;
        }
        tokens = cdr(tokens);
    }
    Value *reverse_list = reverse(parse_list);
    return reverse_list;
}

void printTree(Value *tree){
    while(!isNull(tree)){
        if(car(tree)->type == CONS_TYPE){
            printf("( ");
            printTree(car(tree));
            printf(") ");
        }else if(car(tree)->type == INT_TYPE){
            printf("%i ", car(tree)->i);
        }else if(car(tree)->type == DOUBLE_TYPE){
            printf("%f ", car(tree)->d);
        } else if(car(tree)->type == NULL_TYPE){
            printf(" ");
        } else {
            printf("%s ", car(tree)->s);
        }
        tree = cdr(tree);
    }
    return;
}