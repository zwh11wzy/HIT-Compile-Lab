#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yylineno;
extern struct SYT *head;
extern int e; 

extern int yylex();
extern void yyrestart(FILE *input_file);
extern int yyparse(void);
extern void OutputSYT(struct SYT *nd, int depth);




int main(int argc, char **argv)
{
    if (argc <= 1) 
        return 1;
    
    FILE *f=fopen(argv[1], "r");
    
    if(!f)
    {
            perror(argv[1]);
            return 1;
    }
    
    yylineno = 1; 

    // while (yylex() != 0); // Bison automatically calls yylex() when needed,
    // but does not call yyparse() and yyrestart() itself.
    yyrestart(f);
    yyparse();
    
    if(e==0){
        OutputSYT(head, 0);
    }
    
    return 0;
}