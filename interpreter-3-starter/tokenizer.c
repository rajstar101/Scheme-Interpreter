#include "value.h"
#include <stdio.h>
#include <wchar.h>
#include "talloc.h"
#include <stdarg.h>//supposed to be a header that allows a function to take  indefinite number of arguments
#include "linkedlist.h"
#include <string.h>


int endCheck(char chr){ //to detect if we at the end
    if(chr == ' '|| chr == '\n'|| chr == '('|| chr == ')'||chr == ';' || chr == '\r'){
        return 1;
    } else if (chr == EOF){
        return 2;
    } else {
        return 0;
    }
}

Value *openUcloseDtct(char chr){ //for parenthesis
    if(chr == '('){
        Value *valOpen = talloc(sizeof(Value));
        valOpen->type = OPEN_TYPE;
        char *str4Open = "(";
        valOpen->s = str4Open;
        return valOpen;
    } else if(chr == ')') {
        Value *valClose = talloc(sizeof(Value));
        valClose->type = CLOSE_TYPE;
        char *str4Close = ")";
        valClose->s = str4Close;
        return valClose;
    } else {
        printf("Syntax Error: Open and Close Error: character passed through check but not detect;");
        texit(0);
        Value *valUseless;
        return valUseless;
    }
}

Value *tUfDtct(char nxtChr){ //for bool
    if(nxtChr == 'f'){
        Value *valf = talloc(sizeof(Value));
        valf->type = BOOL_TYPE;
        char *str4f = "#f";
        valf->s = str4f;
        return valf;
    } else if(nxtChr == 't'){
        Value *valt = talloc(sizeof(Value));
        valt->type = BOOL_TYPE;
        char *str4t = "#t";
        valt->s = str4t;
        return valt;
    } else if(nxtChr == 'T'){
        Value *valT = talloc(sizeof(Value));
        valT->type = BOOL_TYPE;
        char *str4T = "#T";
        valT->s = str4T;
        return valT;
    } else if(nxtChr == 'F'){
        Value *valF = talloc(sizeof(Value));
        valF->type = BOOL_TYPE;
        char *str4F = "#F";
        valF->s = str4F;
        return valF;
    } else {
        printf("Syntax Error: Boolean Error: tried using a # with something other than T,t,F, or f\n");
        texit(0); //no clue what different numbers do
        Value *valUseless;
        return valUseless;
    }
}

int intdoubCheck(char chr){ //former name intdoubDtct
    if(chr >= '0' && chr <= '9'){ //a int returns 0
        return 1;
    } else if(chr == '.'){ //a decimal returns a 1
        return 2;
    } else { //everything else returns a 2
        return 0;
        }
}

Value *strDtct(char chr){
    char *str4str = talloc(sizeof(char)*300);
    str4str[0] = '"';
    char newchr = (char)fgetc(stdin);
    int x = 1;
    while(newchr != '"'){
        str4str[x] = newchr;
        x++;
        newchr = (char)fgetc(stdin);
        if(x == 299){
            printf("Syntax Error: String memory error\n");
            texit(0);
        }
    }
    str4str[x] = '"';
    str4str[x+1] = '\0';
    Value *val4str = talloc(sizeof(Value));
    val4str->type = STR_TYPE;
    val4str->s = str4str;
    return val4str;
}

int symbolCheck(char chr, int casetype){ // former name symDtct
    if(casetype == 0){
        if((chr >= 'A' && chr <= 'z')||chr == '!' ||chr == '$' ||chr == '%' ||chr == '&' ||chr == '*' ||chr == '/' ||chr == ':' ||chr == '<' ||chr == '=' ||chr == '>' ||chr == '?' ||chr == '~' ||chr == '_' ||chr == '^'){
            return 1;
        }else{
            return 0;
        }
    } else if (casetype == 1){
        if(symbolCheck(chr, 0) == 1 ||chr == '.' ||chr == '+' ||chr == '-' || intdoubCheck(chr) == 1){
            return 1;
        } else {
            return 0;
        }
    } else {
        printf("Syntax Error: Symbol Error: wrong casetype inserted into function symbolCheck\n");
        texit(0);
        return 0;
    }
}

Value *doubDtct(char *str4doubleDtct, int tracker){
    int x = tracker;
    char charRead = (char)fgetc(stdin);
    while(endCheck(charRead) == 0){
        if(intdoubCheck(charRead) == 2){
            printf("Syntax Error: Double Error: you can't have 2 decimals in one number\n");
            texit(0);
            Value *useless;
            return useless;
        }
        if(intdoubCheck(charRead) == 0){
            printf("Syntax Error: Double Error: you can't add strings to a number\n");
            texit(0);
        }
        str4doubleDtct[x] = charRead;
        x++;
        charRead = (char)fgetc(stdin);
    }
    ungetc(charRead, stdin);
    str4doubleDtct[x] = '\0';
    double doub4node = strtod(str4doubleDtct, NULL);
    Value *val1 = talloc(sizeof(Value));
    val1->type = DOUBLE_TYPE;
    val1->d = doub4node;
    return val1;
}

Value *intUdoub(char *str4intUdoub, int tracker){
    int x = tracker;
    char charRead = (char)fgetc(stdin);
    if(strcmp(str4intUdoub, " ") == 0){
        str4intUdoub = talloc(sizeof(char)*300);
    }
    while(endCheck(charRead) == 0){ //make an if statements that sends the whole thing to a double statement if . detected
        if(charRead == '.'){
            str4intUdoub[x] = charRead;
            return doubDtct(str4intUdoub, (x + 1));
        }
        if(intdoubCheck(charRead) == 0){
            printf("Syntax Error: Integer or Double Error: you can't add strings to a number\n");
            texit(0);
        }
        str4intUdoub[x] = charRead;

        x++;
        charRead = (char)fgetc(stdin);
    }
    ungetc(charRead, stdin);
    str4intUdoub[x] = '\0';
    char *useless;
    int int4node = strtol(str4intUdoub, &useless, 10);
    Value *val1 = talloc(sizeof(Value));
    val1->type = INT_TYPE;
    val1->i = int4node;
    return val1;
}

Value *plusUmin(char charRead){
    char *str4plusUmin = talloc(sizeof(char)*300);
    str4plusUmin[0] = charRead;
    charRead = (char)fgetc(stdin);
    if(intdoubCheck(charRead) > 0){
        str4plusUmin[1] = charRead;
        return intUdoub(str4plusUmin, 2);
    } else if (endCheck(charRead) == 1){
        ungetc(charRead, stdin);
        str4plusUmin[1] = '\0';
        Value *sym4node = talloc(sizeof(Value));
        sym4node->type = SYMBOL_TYPE;
        sym4node->s = str4plusUmin;
        return sym4node;
    } else {
        printf("Syntax Error: Plus or Minus Error: prefaced a string using a +/-\n");
        texit(0);
        Value *useless;
        return useless;
    }
}



Value *symDtct(){
    char charRead = (char)fgetc(stdin);
    if(symbolCheck(charRead, 0) == 0){
        if(charRead == EOF){
            printf("Syntax Error: you reached the end of the file but your program is treating this like a symbol");
        } else {
            printf("Syntax Error: Entry Error: not a valid entry in scheme R1: %c\n", charRead);
        }
        texit(0);
    }
    char *str4sym = talloc(sizeof(char)*300);
    str4sym[0] = charRead;
    charRead = (char)fgetc(stdin);
    int x = 1;
    while(endCheck(charRead) == 0){
        if(symbolCheck(charRead, 1) != 1){
            printf("Entry Error: not a valid entry in scheme R2: %c\n", charRead);
            texit(0);
        }
        str4sym[x] = charRead;
        x++;
        charRead = (char)fgetc(stdin);
    }
    str4sym[x] = '\0';
    ungetc(charRead, stdin);
    Value *val1 = talloc(sizeof(Value));
    val1->type = SYMBOL_TYPE;
    val1->s = str4sym;
    return val1;
}

Value *tokenize() {
    char charRead;
    Value *list = makeNull();
    charRead = (char)fgetc(stdin);

    while (charRead != EOF) {
        if(charRead == '\r' || charRead == '\n'){
            ;
        }else if(charRead == ' '){
            ;
        } else if(charRead == ';'){
            while(charRead != '\n' && charRead != EOF && charRead != '\r'){
                charRead = (char)fgetc(stdin);
                }
            if(charRead == EOF){
                break;
            }
            ungetc(charRead, stdin);
        } else if (charRead == '(' || charRead == ')') {
            list = cons(openUcloseDtct(charRead), list);
        } else if (charRead == '#'){
            charRead = (char)fgetc(stdin);
            list = cons(tUfDtct(charRead), list);
        } else if (charRead == '"'){
            list = cons(strDtct(charRead), list);
        } else if (charRead == '+'||charRead == '-'){ //if string starts with positive or negative sign
            list = cons(plusUmin(charRead), list);
        } else if (intdoubCheck(charRead) !=  0){
            ungetc(charRead, stdin);
            list = cons(intUdoub(" ", 0), list);
        } else {
            ungetc(charRead, stdin);
            list = cons(symDtct(), list);
        }
        charRead = (char)fgetc(stdin);
    }
    Value *revList = reverse(list);
    return revList;
}

void displayTokens(Value *list){
    while(list->type != NULL_TYPE){
        if(list->c.car->type == INT_TYPE){
            printf("%i:integer\n", list->c.car->i);
        } else if(list->c.car->type == DOUBLE_TYPE){
            printf("%f:double\n", list->c.car->d);
        } else if(list->c.car->type == STR_TYPE){
            printf("%s:string\n", list->c.car->s);
        } else if(list->c.car->type == OPEN_TYPE){
            printf("%s:open\n", list->c.car->s);
        } else if(list->c.car->type == CLOSE_TYPE){
            printf("%s:close\n", list->c.car->s);
        } else if(list->c.car->type == BOOL_TYPE){
            printf("%s:boolean\n", list->c.car->s);
        } else if(list->c.car->type == SYMBOL_TYPE){
            printf("%s:symbol\n", list->c.car->s);
        } else {
            printf("error reading\n");
        }
        list = list->c.cdr;
    }
} 