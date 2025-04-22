#include <stdlib.h>
#include <stdio.h>
#include "node_utils.h"
#include "semantic.h"
#include "hash.h"

extern void yyrestart(FILE *);
extern int yyparse();
extern int yylineo;

Node* Head = NULL;
int errorNum = 0;
int last_elineo1 = 0;

void myerror(char *msg){
    if(last_elineo1 != yylineno){
        printf("Error type B at line %d: %s\n", yylineno, msg);
        last_elineo1 = yylineno;
    }
}

int main(int argc, char** argv){

    if (argc <= 1){
        return 1; 
    } 
    FILE* fp = fopen(argv[1],"r");
    if (!fp){
        perror(argv[1]);
        return 1;
    }   

    yylineno=1;

    yyrestart(fp);
    yyparse();

    if(errorNum == 0){
        // printf("there is no error\n\n");
        Init_HashTable();
        Travel_Tree(Head);
        // Show_Symbol();
        // Output_Tree(Head,0);
    }

    return 0;
}