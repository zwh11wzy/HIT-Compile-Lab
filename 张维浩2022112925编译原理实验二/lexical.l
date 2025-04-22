%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include "syntax.tab.h"
    #include "node_utils.h"
    extern int errorNum;
    int theSameLine2 = 0;
%}
%option yylineno

SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS "+"
MINUS "-"
STAR "*"
DIV "/"
AND "&&"
OR "||"
DOT "."
NOT "!"
TYPE int|float
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
SPACE [ \r\n\t]+
DECNUM ([1-9][0-9]*)|0
OCT 0[0-7]*
OCT_ERROR 0[0-9A-WYZa-wyz][0-9A-Za-z]*
HEX 0[Xx][0-9a-fA-F]*
HEX_ERROR [0][Xx][0-9A-Za-z]*
INT {DECNUM}|{OCT}|{HEX}
FLOAT [0-9]*[.][0-9]+f?
ID [A-Za-z_][A-Za-z_0-9]*
COMMENT "//"
OTHER .

%%

{SEMI}  {
    yylval.node=Create_Node("SEMI",yytext);
    return(SEMI);
}
{COMMA} {
    yylval.node=Create_Node("COMMA",yytext);
    return(COMMA);
}
{ASSIGNOP} {
    yylval.node=Create_Node("ASSIGNOP",yytext);
    return ASSIGNOP;
}


{RELOP}     {
    yylval.node=Create_Node("RELOP",yytext);
    return RELOP;
}

{PLUS}      {
    yylval.node=Create_Node("PLUS",yytext);
    return PLUS;
}
{MINUS}     {
    yylval.node=Create_Node("MINUS",yytext);
    return MINUS;
}
{STAR}      {
    yylval.node=Create_Node("STAR",yytext);
    return STAR;
}
{DIV}       {
    yylval.node=Create_Node("DIV",yytext);
    return DIV;
}
{AND}       {
    yylval.node=Create_Node("AND",yytext);
    return AND;
}
{OR}        {
    yylval.node=Create_Node("OR",yytext);
    return OR;
}
{DOT}       {
    yylval.node=Create_Node("DOT",yytext);
    return DOT;
}
{NOT}       {
    yylval.node=Create_Node("NOT",yytext);
    return NOT;
}
{TYPE}      {
    yylval.node=Create_Node("TYPE",yytext);
    return TYPE;
}
{LP}        {
    yylval.node=Create_Node("LP",yytext);
    return LP;
}
{RP}        {
    yylval.node=Create_Node("RP",yytext);
    return RP;
}
{LB}        {
    yylval.node=Create_Node("LB",yytext);
    return LB;
}
{RB}        {
    yylval.node=Create_Node("RB",yytext);
    return RB;
}
{LC}        {
    
    yylval.node=Create_Node("LC",yytext);
    return LC;
}
{RC}        {
    yylval.node=Create_Node("RC",yytext);
    return RC;
}
{STRUCT}    {
    yylval.node=Create_Node("STRUCT",yytext);
    return STRUCT;
}
{RETURN}    {
    yylval.node=Create_Node("RETURN",yytext);
    return RETURN;
}
{IF}        {
    yylval.node=Create_Node("IF",yytext);
    return IF;
}
{ELSE}      {
    yylval.node=Create_Node("ELSE",yytext);
    return ELSE;
}
{WHILE}     {
    yylval.node=Create_Node("WHILE",yytext);
    return WHILE;
}
{SPACE}     {}


{OCT}       {
    char *end = NULL;
    int l = (int)strtol(yytext, &end, 8);
    snprintf(yytext, 10,"%d",l);
    yylval.node=Create_Node("INT",yytext);
    return INT;
}
{OCT_ERROR} {
    errorNum++;
    printf("Error type A at Line %d: Illegal octal number '%s'\n", yylineno, yytext);
    return INT;
}
{HEX}       {
    char *end = NULL;
    int l = (int)strtol(yytext, &end, 16);
    snprintf(yytext, 10,"%d",l);
    yylval.node=Create_Node("INT",yytext);
    return INT;
}
{HEX_ERROR} {
    errorNum++;
    printf("Error type A at Line %d: Illegal hexadecimal number '%s'\n", yylineno, yytext);
    return INT;
}
{INT}       {
    yylval.node=Create_Node("INT",yytext);
    return INT;
}
{FLOAT}     {
    yylval.node=Create_Node("FLOAT",yytext);
    return FLOAT;
}

{ID}        {
    
    yylval.node=Create_Node("ID",yytext);
    return ID;
}

{OTHER} {
    errorNum++;
    if(theSameLine2 != yylineno){
        printf("Error type A at line %d: Mysterious character \"%s\".\n",yylineno,yytext);
        theSameLine2 = yylineno;
    }
    
}
{COMMENT} {
        printf("Error type A at line %d: Mysterious character \"%s\".\n",yylineno,yytext);
        theSameLine2 = yylineno;  
}


%%
//用于处理输入的结束。返回值 1 表示没有更多的输入文件需要处理，词法分析器可以结束。
//如果返回 0，则表示还有其他输入文件需要继续处理，词法分析器会尝试读取下一个输入文件。
int yywrap() {
    return 1;
}


  
