#include "value.h"
// #include "linkedlist.h"
#include "talloc.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

Value *car(Value *list){
    assert(list->type == CONS_TYPE);
    return list->c.car;
}

Value *cdr(Value *list){
    assert(list->type == CONS_TYPE);
    return list->c.cdr;
}

bool isNull(Value *value){
    if(value->type == NULL_TYPE){
        return 1;
    }else{
        return 0;
    }
}

Value *makeNull(){
    Value *value = talloc(sizeof(Value));
    value->type = NULL_TYPE;
    return value;
}

Value *cons(Value *newCar, Value *newCdr){
    Value *value = talloc(sizeof(Value));
    value->type = CONS_TYPE;
    value->c.car = newCar;
    value->c.cdr = newCdr;
    return value;
}

void display(Value *list){
    while(list->type != NULL_TYPE){
        if(list->c.car->type == INT_TYPE){
            printf("%i,", list->c.car->i);
        } else if (list->c.car->type == DOUBLE_TYPE){
            printf("%f,", list->c.car->d);
        } else {
            printf("%s,", list->c.car->s);
        }
        list = cdr(list);
    }
    printf("\n");
}  


int lengthH(Value *value, int lengthlist){
    if(isNull(value)==1){
        return lengthlist;
    }else{
        lengthlist = lengthlist + 1;
        return lengthH(cdr(value), lengthlist);
    }
}

int length(Value *value){
    int lengthlist = 0;
    lengthlist = lengthH(value, lengthlist);
    return lengthlist;
}

Value *returnNode(Value *list, int tracker){
    if(tracker == 0){
        return list;
    } else {
        return returnNode(list->c.cdr, tracker - 1);
    }
}

Value *reverse(Value *list){
    Value *newHead = makeNull();
    for(int i = 0; i < length(list); i++){
        Value *tempNode = returnNode(list, i);
        newHead = cons(tempNode->c.car, newHead);
    }
    return newHead;
}


int main() {
    Value *head = makeNull();
    int correctLength = 0;
    display(head);

    Value *val1 = talloc(sizeof(Value));
    val1->type = INT_TYPE;
    val1->i = 7;
    head = cons(val1,head);
    correctLength++;
    display(head);

    Value *val2 = talloc(sizeof(Value));
    val2->type = DOUBLE_TYPE;
    val2->d = 6.00;
    head = cons(val2,head);
    correctLength++;
    display(head);

    Value *val3 = talloc(sizeof(Value));
    val3->type = STR_TYPE;
    char *text = "5.0s";
    val3->s = talloc(sizeof(char)*(strlen(text) + 1));
    strcpy(val3->s,text);
    head = cons(val3,head);
    correctLength++;
    display(head);


    Value *val4 = talloc(sizeof(Value));
    val4->type = DOUBLE_TYPE;
    val4->d = 4.00000;
    head = cons(val4,head);
    correctLength++;
    display(head);

    Value *reverseHead = reverse(head);
    display(reverseHead);

    tfree();
    display(reverseHead);
    display(head);
}