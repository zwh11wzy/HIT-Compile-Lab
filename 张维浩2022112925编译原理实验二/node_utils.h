#ifndef _MY_NODE_H_
#define _MY_NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define MAX_CHILD_NUM 7
extern int yylineno;

typedef struct Syntax_Tree{
    char name[32];                              
    char text[32];                              
    int line_num;                                 
    int child_num;                               
    struct Syntax_Tree *child[MAX_CHILD_NUM]; 
} Node;

Node *Create_Node(char *name, char *text);       
void Insert_Child(int child_num, Node *parent, ...); 
void Travel_Tree(Node *Head);
void Output_Tree(Node *parent, int blank);         


#endif