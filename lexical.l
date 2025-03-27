%{

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "syntax.tab.h"

int yycolumn = 1;
#define YY_USER_ACTION\
    yylloc.first_line=yylloc.last_line=yylineno;\
    yylloc.first_column=yycolumn;\
    yylloc.last_column=yycolumn+yyleng-1;\
    yycolumn+=yyleng;

struct SYT* Nodes_leaf(char* s){
    struct SYT* n = (struct SYT*)malloc(sizeof(struct SYT));
    n->leaf = 0; // lexical unit
    n->child = NULL;
    n->linenum = 0;//NOT print
    n->bro = NULL;
    strcpy(n->attr, s); 
    return n;
}
 



%}

%option yylineno


INT [1-9]+[0-9]{0,31}|0
INT8 0[0-9]{3}
INT16 0x[0-9A-Fa-f]{0,4}
FLOAT {INT}\.[0-9]+ 
ID [_a-zA-Z][_0-9_a-zA-Z]* 
RELOP >|<|>=|<=|==|!= 
TYPE int|float
DIGIT [0-9] 


IGNORE [\r \t] 
CHANGELINE [\n] 

%%

"+" {
    yylval = Nodes_leaf("PLUS\0");//yylval是Flex 的内部变量，表示当前词法单元所对应的属性值
    return PLUS;
}

"-" {
    yylval = Nodes_leaf("MINUS\0");
    return MINUS;
}

"&&" {
    yylval = Nodes_leaf("AND\0");
    return AND;
}

"||" {
    yylval = Nodes_leaf("OR\0");
    return OR;
}

"*" {
    yylval = Nodes_leaf("MUL\0");
    return MUL;
}

"/" {
    yylval = Nodes_leaf("DIV\0");
    return DIV;
}

"=" {
    yylval = Nodes_leaf("ASSIGNOP\0");
    return ASSIGNOP;
}

"!" {
    yylval = Nodes_leaf("NOT\0");
    return NOT;
}

";" {
    yylval = Nodes_leaf("SEMI\0");
    return SEMI; 
}

"," {
    yylval = Nodes_leaf("COMMA\0"); 
    return COMMA; 
}

"." {
    yylval = Nodes_leaf("DOT\0"); 
    return DOT; 
}

"(" {
    yylval = Nodes_leaf("LP\0"); 
    return LP; 
}

")" {
    yylval = Nodes_leaf("RP\0"); 
    return RP; 
}

"[" {
    yylval = Nodes_leaf("LB\0"); 
    return LB; 
}

"]" {
    yylval = Nodes_leaf("RB\0"); 
    return RB; 
}

"{" {
    yylval = Nodes_leaf("LC\0"); 
    return LC; 
}

"}" {
    yylval = Nodes_leaf("RC\0"); 
    return RC; 
}

"struct" {
    yylval = Nodes_leaf("STRUCT\0"); 
    return STRUCT; 
}

"return" {
    yylval = Nodes_leaf("RETURN\0"); 
    return RETURN; 
}

"if" {
    yylval = Nodes_leaf("IF\0"); 
    return IF; 
}

"else" {
    yylval = Nodes_leaf("ELSE\0"); 
    return ELSE; 
}

"while" {
    yylval = Nodes_leaf("WHILE\0"); 
    return WHILE; 
}

{RELOP} {
    yylval = Nodes_leaf("RELOP\0"); 
    return RELOP;
}

{TYPE} {
    yylval = Nodes_leaf("TYPE\0"); 
    strcpy(yylval->type_char, yytext);
    return TYPE;
}

{INT} {
    yylval = Nodes_leaf("INT\0");
    yylval->type_int = atoi(yytext); 
    return INT; 
}

{INT8} {
    yylval = Nodes_leaf("INT8\0");
    yylval->type_int = atoi(yytext);  
    return INT8;     
}

{INT16} {
    yylval = Nodes_leaf("INT16\0");
    yylval->type_int = atoi(yytext);  
    return INT16;
}

{FLOAT} {
    yylval = Nodes_leaf("FLOAT\0");
    yylval->type_float = atof(yytext);  
    return FLOAT; 
}

{ID} {
    yylval = Nodes_leaf("ID\0");
    strcpy(yylval->type_char, yytext); 
    return ID; 
}


{IGNORE} {} 

{CHANGELINE} {
    yycolumn = 1;
} 

. {
    char msg[32]; 
    sprintf(msg, "Mysterious character \"%s\"", yytext); 
    prerror('A', msg); 
    e = 1; 
}



%%
