%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "node_utils.h"
    #include "lex.yy.c"
    extern int yylineno;
    void myerror(char *msg);
    extern Node* Head;
    extern int errorNum;
    int yyerror(char const *msg);
%}

%union {
    struct Syntax_Tree* node;
}

//terminal token
%token <node> INT FLOAT ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV 
%token <node> AND OR DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

//association
%right ASSIGNOP  
%left OR 
%left AND 
%left RELOP
%left PLUS MINUS 
%left STAR DIV
%right NOT
%left DOT LB RB LP RP

//noassociation
%nonassoc LOWER_THAN_ELSE 
%nonassoc ELSE

//non-terminal type
%type <node> Program ExtDefList ExtDef ExtDecList Specifier
%type <node> StructSpecifier OptTag Tag VarDec FunDec VarList
%type <node> ParamDec CompSt StmtList Stmt DefList Def DecList
%type <node> Dec Exp Args



%%

//High-level Definitions

Program     : ExtDefList        
            {
                $$=Create_Node("Program","");
                Insert_Child(1, $$, $1);Head=$$;
            }
            ;

ExtDefList  : ExtDef ExtDefList     
            {
                $$=Create_Node("ExtDefList","");
                Insert_Child(2, $$, $1, $2);
            }
            |  /* empty*/           
            {
                $$=NULL;
            }
            ;
                
ExtDef      : Specifier ExtDecList SEMI     
            {
                $$=Create_Node("ExtDef","");
                Insert_Child(3, $$, $1, $2, $3);
            }
            | Specifier SEMI                
            {
                $$=Create_Node("ExtDef","");
                Insert_Child(2, $$, $1, $2);
            }    
            | Specifier FunDec CompSt       
            {
                $$=Create_Node("ExtDef","");
                Insert_Child(3, $$, $1, $2, $3);
            }
            | Specifier FunDec SEMI	    
            {
                errorNum++;
                myerror("Syntax error, near \';\'");
            }
            | Specifier error               
            {
                errorNum++;
                myerror("Syntax error, near \'}\'");
            }
            ;
ExtDecList  : VarDec                        
            {
                $$=Create_Node("ExtDecList","");
                Insert_Child(1, $$, $1);
            }
            | VarDec COMMA ExtDecList       
            {
                $$=Create_Node("ExtDecList","");
                Insert_Child(3, $$, $1, $2, $3);
            }
            ;

            

//Specifiers

Specifier   : TYPE                  
            {
                $$=Create_Node("Specifier","");
                Insert_Child(1, $$, $1);
            }
            | StructSpecifier       
            {
                $$=Create_Node("Specifier","");
                Insert_Child(1, $$, $1);
            }
            ;
            
StructSpecifier : STRUCT OptTag LC DefList RC   
            {
                $$=Create_Node("StructSpecifier","");
                Insert_Child(5, $$, $1, $2, $3, $4, $5);
            }
            | STRUCT Tag                    
            {
                $$=Create_Node("StructSpecifier","");
                Insert_Child(2, $$, $1, $2);
            }
            //| error Tag{errorNum++; myerror("Syntax error, missing \'struct\'");}在一些情况下会和缺少;冲突
            ;
            
OptTag  : ID                
            {
                $$=Create_Node("OptTag","");
                Insert_Child(1, $$, $1);
            }
        | /* empty*/        
            {
                $$=NULL;
            }
        ;
        
Tag     : ID                
            {
                $$=Create_Node("Tag","");
                Insert_Child(1, $$, $1);
            }
        ;


//4.Declarators

VarDec      : ID                            
            {
                $$=Create_Node("VarDec","");
                Insert_Child(1, $$, $1);
            }
            | VarDec LB INT RB              
            {
                $$=Create_Node("VarDec","");
                Insert_Child(4, $$, $1, $2, $3, $4);
            }
            | VarDec LB error RB	    
            {
                errorNum++; 
                myerror("Syntax error, near \']\'");
            }
            ;
            
FunDec      : ID LP VarList RP              
            {
                $$=Create_Node("FunDec","");
                Insert_Child(4, $$, $1, $2, $3, $4);
            }
            | ID LP RP                      
            {
                $$=Create_Node("FunDec","");
                Insert_Child(3, $$, $1, $2, $3);
            }
            ;
            
VarList     : ParamDec COMMA VarList        
            {
                $$=Create_Node("VarList","");
                Insert_Child(3, $$, $1, $2, $3);
            }
            | ParamDec                      
            {
                $$=Create_Node("VarList","");
                Insert_Child(1, $$, $1);
            }
            ;
            
ParamDec    : Specifier VarDec              
            {
                $$=Create_Node("ParamDec","");
                Insert_Child(2, $$, $1, $2);
            }
            ;

            
//Statements

CompSt      : LC DefList StmtList RC        
            {
                $$=Create_Node("CompSt","");
                Insert_Child(4, $$, $1, $2, $3, $4);
            }
            | LC DefList StmtList error     
            {
                errorNum++;
                myerror("missing \'}\'");
            }
            ;
            
StmtList    : Stmt StmtList                 
            {
                $$=Create_Node("StmtList","");
                Insert_Child(2, $$, $1, $2);
            }
            | /*empty*/                     
            {
                $$=NULL;
            }
            ;
            
Stmt    : Exp SEMI                                      
            {
                $$=Create_Node("Stmt","");
                Insert_Child(2, $$, $1, $2);
            }
        | CompSt                                        
            {
                $$=Create_Node("Stmt","");
                Insert_Child(1, $$, $1);
            }
        | RETURN Exp SEMI                               
            {
                $$=Create_Node("Stmt","");
                Insert_Child(3, $$, $1, $2, $3);
            }
	    | RETURN error SEMI				
            {
                errorNum++;
                myerror("Syntax error, after return");
            }
        | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE       
            {
                $$=Create_Node("Stmt","");
                Insert_Child(5, $$, $1, $2, $3, $4, $5);
            }
        | IF LP Exp RP Stmt ELSE Stmt                   
            {
                $$=Create_Node("Stmt","");
                Insert_Child(7, $$, $1, $2, $3, $4, $5, $6, $7);
            }
        | IF LP Exp RP error ELSE Stmt                  
            {
                errorNum++;
                myerror("Missing \";\""); 
            }
        | WHILE LP Exp RP Stmt                          
            {
                $$=Create_Node("Stmt","");
                Insert_Child(5, $$, $1, $2, $3, $4, $5);
            }
	    | Exp error					
            {
                errorNum++;
                myerror("Syntax error, before \'}\'");
            }
        ;


//Local Definitions

DefList : Def DefList               
            {
                $$=Create_Node("DefList","");
                Insert_Child(2, $$, $1, $2);
            }
        | /*empty*/                 
            {
                $$=NULL;
            }
        ;
        
Def     : Specifier DecList SEMI    
            {
                $$=Create_Node("Def","");
                Insert_Child(3, $$, $1, $2, $3);
            }
	    | Specifier error SEMI	    
            {
                errorNum++;
                myerror("Syntax error, near \';\'");
            }
        ;

DecList : Dec                       
            {
                $$=Create_Node("DecList","");
                Insert_Child(1, $$, $1);
            }
        | Dec COMMA DecList         
            {
                $$=Create_Node("DecList","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        ;
        
Dec     : VarDec                    
            {
                $$=Create_Node("Dec","");
                Insert_Child(1, $$, $1);
            }
        | VarDec ASSIGNOP Exp       
            {
                $$=Create_Node("Dec","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        ;
            
            
//Expressions
Exp     : Exp ASSIGNOP Exp      
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | Exp AND Exp           
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | Exp OR Exp            
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | Exp RELOP Exp         
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | Exp PLUS Exp          
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | Exp MINUS Exp         
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | Exp STAR Exp          
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | Exp DIV Exp           
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | LP Exp RP             
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | MINUS Exp             
            {
                $$=Create_Node("Exp","");
                Insert_Child(2, $$, $1, $2);
            }
        | NOT Exp               
            {
                $$=Create_Node("Exp","");
                Insert_Child(2, $$, $1, $2);
            }
        | ID LP Args RP         
            {
                $$=Create_Node("Exp","");
                Insert_Child(4, $$, $1, $2, $3, $4);
            }
	    | ID LP error		    
            {
                errorNum++;
                myerror("Syntax error, after \'(\'");
            }
        | ID LP RP              
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | Exp LB Exp RB         
            {
                $$=Create_Node("Exp","");
                Insert_Child(4, $$, $1, $2, $3, $4);
            }
        | Exp LB error 	       
            {
                errorNum++;
                myerror("Syntax error, near \'[\'");
            }
        | Exp DOT ID            
            {
                $$=Create_Node("Exp","");
                Insert_Child(3, $$, $1, $2, $3);
            }
        | ID                    
            {
                $$=Create_Node("Exp","");
                Insert_Child(1, $$, $1);
            }
        | INT                   
            {
                $$=Create_Node("Exp","");
                Insert_Child(1, $$, $1);
            }
        | FLOAT                 
            {
                $$=Create_Node("Exp","");
                Insert_Child(1, $$, $1);
            }
        ;
    
Args        : Exp COMMA Args        
            {
                $$=Create_Node("Args","");
                Insert_Child(3, $$, $1, $2, $3);
            }
            | Exp                   
            {
                $$=Create_Node("Args","");
                Insert_Child(1, $$, $1);
            }
            ;

%%

int yyerror(char const *msg){
    //printf("Error type B at line %d: %s\n", yylineno, msg);
}