%locations // Enable lexical location tracking

%{

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

extern int yylineno; 
extern char* yytext; 
extern int yylex(); 

int e = 0;
int last_elineo = 0;

void yyerror(const char* s);

struct SYT { // Multi-way tree
    struct SYT* child;
    struct SYT* bro;
    int linenum;
    char attr[10]; // Used for matching when creating nodes
    int leaf; // Used to determine if it is a leaf node
    union { // Used for output during traversal
        int type_int;
        float type_float;
        char type_char[32];
    };
};

#define YYSTYPE struct SYT* 


struct SYT* head=NULL;  
struct SYT* Nodes(struct SYT* cd, char* s, int line);
void OutputSYT(struct SYT* nd, int depth); // Depth-first search, pre-order traversal
void prerror(char errorType, char* msg); 



%}

/* Tokens */

%token PLUS
%token MINUS
%token AND
%token OR
%token MUL
%token DIV
%token ASSIGNOP
%token NOT
%token SEMI
%token COMMA
%token DOT
%token LP
%token RP
%token LB
%token RB
%token LC
%token RC
%token STRUCT
%token RETURN
%token IF
%token ELSE
%token WHILE
%token TYPE
%token INT
%token INT8
%token INT16
%token FLOAT
%token ID
%token RELOP


%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left MUL DIV 

%right ASSIGNOP
%right LOWER_THAN_NOT NOT 
%right DOT LP LB RP RB 

%nonassoc LOWER_THAN_ELSE 
%nonassoc ELSE 


%% 

/* High-level Definitions */
//全局变量，结构体，函数定义

Program: ExtDefList{
    if($1->type_int==0){
        $$=Nodes($1,"Program\0",$1->linenum);//$1->linenum not used
    }else{
        $$=Nodes($1,"Program\0",@1.first_line);        
    }
}

ExtDefList: {
    $$ = Nodes(NULL,"ExtDefList\0",yylineno);//结束后返回行号
    $$->type_int = 0;
} | ExtDef ExtDefList {//递归
    $$ = Nodes($1,"ExtDefList\0",@1.first_line);
    $$->type_int = 2;//多个儿子
    $1->bro = $2;
}

ExtDef: Specifier ExtDecList SEMI{//多个全局变量定义
    $$ = Nodes($1,"ExtDef\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;    
} | Specifier SEMI{//单个无定义的结构体
    $$ = Nodes($1,"ExtDef\0",@1.first_line);
    $1->bro = $2;
} | Specifier FunDec CompSt{//函数头体
    $$ = Nodes($1,"ExtDef\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;     
} | Specifier error{
    e = 1;
    if(last_elineo != yylineno){//无一行出现多个error情况
        prerror('B',"Missing \";\"");
    }
}

ExtDecList: VarDec{//多个全局变量定义
    $$ = Nodes($1,"ExtDecList\0",@1.first_line);    
} | VarDec COMMA ExtDecList{
    $$ = Nodes($1,"ExtDecList\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;         
} | VarDec error ExtDecList{
    e = 1;
    if(last_elineo != yylineno){
        prerror('B',"text");
    }
}

/* Specifiers */
// 变量类型

Specifier: TYPE{
    $$ = Nodes($1,"Specifier\0",@1.first_line);    
} | StructSpecifier{
    $$ = Nodes($1,"Specifier\0",@1.first_line);     
}

StructSpecifier: STRUCT OptTag LC DefList RC{
    $$ = Nodes($1,"StructSpecifier\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;
    $3->bro = $4;
    $4->bro = $5;          
} | STRUCT Tag{
    $$ = Nodes($1,"StructSpecifier\0",@1.first_line);
    $1->bro = $2;    
}

OptTag: {
    $$ = Nodes(NULL,"OptTag\0",0);//yylineno?
    $$->type_int = 0;        
} | ID{
    $$ = Nodes($1,"OptTag\0",@1.first_line);    
}

Tag: ID{
    $$ = Nodes($1,"Tag\0",@1.first_line);    
}

/* Declarators */
//变量、函数定义
VarDec: ID{
    $$ = Nodes($1,"VarDec\0",@1.first_line);    
} | VarDec LB INT RB{//数组数字
    $$ = Nodes($1,"VarDec\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;
    $3->bro = $4;        
} | VarDec LB error RB{
    char msg[32];
    e = 1;
    sprintf(msg, "Syntax error near \'%c\'", yytext[0]);
    if(last_elineo != yylineno){
        prerror('B', msg);
    }
}

FunDec: ID LP VarList RP{//形参列表
    $$ = Nodes($1,"FunDec\0",@1.first_line); 
    $1->bro = $2;
    $2->bro = $3;
    $3->bro = $4;
} | ID LP RP{
    $$ = Nodes($1,"FunDec\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;        
} | ID LP error RP{
    e = 1;
    if(last_elineo != yylineno){
        prerror('B',"Syntax error between ()");
    }
}

VarList: ParamDec COMMA VarList{//对形参变量定义
    $$ = Nodes($1,"VarList\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;         
} | ParamDec{
    $$ = Nodes($1,"VarList\0",@1.first_line);    
}

ParamDec: Specifier VarDec{//描述符与变量定义
    $$ = Nodes($1,"ParamDec\0",@1.first_line);
    $1->bro = $2;       
}


/* Statements */
//语句
CompSt: LC DefList StmtList RC{//语句块，一系列变量定义，语句
//CompSt必须在每个语句块开头才能定义
    $$ = Nodes($1,"CompSt\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;
    $3->bro = $4;        
}

StmtList: {
    $$ = Nodes(NULL,"StmtList\0",0);
    $$->type_int = 0;        
} | Stmt StmtList{
    $$ = Nodes($1,"StmtList\0",@1.first_line);    
    $1->bro = $2;  
}

Stmt: Exp SEMI{//语句
    $$ = Nodes($1,"Stmt\0",@1.first_line);
    $1->bro = $2;    
} | CompSt{
    $$ = Nodes($1,"Stmt\0",@1.first_line);
} | RETURN Exp SEMI{
    $$ = Nodes($1,"Stmt\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;
} | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE{//避免报移入归约冲突
    $$ = Nodes($1,"Stmt\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;
    $3->bro = $4;
    $4->bro = $5;    
} | IF LP Exp RP Stmt ELSE Stmt{
    $$ = Nodes($1,"Stmt\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;
    $3->bro = $4;
    $4->bro = $5;
    $5->bro = $6;
    $6->bro = $7;  
} | WHILE LP Exp RP Stmt{
    $$ = Nodes($1,"Stmt\0",@1.first_line);
    $1->bro = $2;
    $2->bro = $3;
    $3->bro = $4;
    $4->bro = $5;
} | Exp error{
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Missing \";\"");
    }
}

/* Local Definitions */
//局部变量定义
DefList: {
    $$ = Nodes(NULL,"DefList\0",0);
    $$->type_int = 0;    
} | Def DefList{//一类变量定义
    $$ = Nodes($1,"DefList\0",@1.first_line);
    $1->bro = $2;    
}

Def: Specifier DecList SEMI{//e.g:int a,b,c;或int a, int b ,int c;
    $$ = Nodes($1,"Def\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;
} | Specifier error SEMI{
    char msg[32];
    e = 1;
    sprintf(msg, "Syntax error near \'%c\'", yytext[0]);
    if(last_elineo != yylineno){
        prerror('B', msg);
    }
} | Specifier DecList error{
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Missing \";\"");
    }    
}

DecList: Dec{
    $$ = Nodes($1,"DecList\0",@1.first_line);    
} | Dec COMMA DecList{
    $$ = Nodes($1,"DecList\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;         
}

Dec: VarDec{//单个变量定义，e.g:int a = 5;
    $$ = Nodes($1,"Dec\0",@1.first_line);        
} | VarDec ASSIGNOP Exp{
    $$ = Nodes($1,"Dec\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;    
}


/* Expressions */
//表达式

Exp: Exp ASSIGNOP Exp{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | Exp AND Exp{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | Exp OR Exp{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | Exp RELOP Exp{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | Exp PLUS Exp{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | Exp MINUS Exp{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | Exp MUL Exp{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | Exp DIV Exp{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | LP Exp RP{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | MINUS Exp %prec LOWER_THAN_NOT{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;        
} | NOT Exp{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;         
} | ID LP Args RP{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;
    $3->bro = $4;         
} | ID LP RP{
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | Exp LB Exp RB{// 数组访问
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;
    $3->bro = $4;     
} | Exp DOT ID{//结构体访问
    $$ = Nodes($1,"Exp\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | ID{
    $$ = Nodes($1,"Exp\0",@1.first_line);     
} | INT{
    $$ = Nodes($1,"Exp\0",@1.first_line);     
} | FLOAT{
    $$ = Nodes($1,"Exp\0",@1.first_line);     
} | Exp LB Exp error RB{
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Missing \"]\"");
    }     
} | ID LP error RP{
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Syntax error in Exp");
    }
} | LP error RP{
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Syntax error in Exp");
    }
} | Exp ASSIGNOP error{
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Syntax error in Exp");
    }
} | Exp LB error RB{
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Syntax error between \"[]\"");
    }
}     
     
Args: Exp COMMA Args{//实参列表
    $$ = Nodes($1,"Args\0",@1.first_line);
    $1->bro = $2;    
    $2->bro = $3;     
} | Exp{
    $$ = Nodes($1,"Args\0",@1.first_line);    
}
     

%%

#include "lex.yy.c"

struct SYT* Nodes(struct SYT* cd, char* s, int line){
    struct SYT* n = (struct SYT*)malloc(sizeof(struct SYT));
    n->leaf = 1; // Syntax unit
    n->child = cd;
    n->linenum = line;
    n->bro = NULL;
    n->type_int = 1;
    strcpy(n->attr,s);
    head = n;
    return n;
}


void OutputNodes(struct SYT* nd){
    if(nd->leaf==0){ // If it is a terminal
        if(!strcmp(nd->attr,"ID\0")){
            printf("ID: %s\n",nd->type_char);
        }else if(!strcmp(nd->attr,"TYPE\0")){
            printf("TYPE: %s\n",nd->type_char);
        }else if(!strcmp(nd->attr,"INT\0")){
            printf("INT: %u\n",nd->type_int);
        }else if(!strcmp(nd->attr,"FLOAT\0")){
            printf("FLOAT: %f\n",nd->type_float);
        } else {
            printf("%s\n", nd->attr); // Output information for other types of terminals
        }
    }else if(nd->type_int){// If it is a non-terminal
        printf("%s (%d)\n", nd->attr, nd->linenum);
    }
}


void OutputSYT(struct SYT* nd, int depth){
    int i;
    if(nd->leaf==0||nd->type_int){
        for(i=0;i<depth;i++)
        {
            printf("  ");
        }
        OutputNodes(nd);
    }
    if(nd->child!=NULL){
        OutputSYT(nd->child,depth+1);
    }
    if(nd->bro!=NULL){
        OutputSYT(nd->bro,depth);
    }
    return;
}


void prerror(char errorType, char* msg) {
    fprintf(stderr, "Error type %c at Line %d: %s.\n", errorType, yylineno, msg);
    last_elineo = yylineno; 
}

void yyerror(const char* s) {}