#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "node_utils.h"     
#include "semantic.h" 

/*stdarg.h 头文件是 C 语言标准库的一部分，主要用于处理可变参数的函数。它提供了一组宏，使得函数能够接受不定数量的参数。
主要功能：
va_list：用于声明一个变量，该变量将用于访问可变参数。
va_start：初始化 va_list 变量，以便可以访问可变参数。
va_arg：用于访问可变参数中的下一个参数。
va_end：用于清理 va_list 变量，结束对可变参数的访问。本代码中Insert_Node函数用到*/

Node *Create_Node(char *name, char *text)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, name); 
    strcpy(p->text, text); 

    p->line_num = yylineno; 
    for (int i = 0; i < MAX_CHILD_NUM; i++)
    {
        p->child[i] = NULL;
    }
    p->child_num = 0;
    return p;
}

void Insert_Child(int child_num, Node *parent, ...)
{
    va_list ap;
    va_start(ap, parent);

    for (int i = 0; i < child_num; i++)
    {
        parent->child[i] = va_arg(ap, Node *);
    }
    parent->line_num = parent->child[0]->line_num; // 取第一个子节点的行号作为父节点行号
    parent->child_num = child_num;
    va_end(ap);
}

void Output_Tree(Node *parent, int blank)
{
    if (parent == NULL)
    {
        return;
    }
    for (int i = 0; i < blank; i++)
    {
        printf(" "); 
    }
    if (parent->child_num != 0)
    {
        printf("%s (%d)\n", parent->name, parent->line_num); //与语法分析中输出语法树一致
        for (int i = 0; i < parent->child_num; i++)
        {
            Output_Tree(parent->child[i], blank + 2); // 递归打印子节点
        }
    }
    else
    {
        if (strcmp(parent->name, "INT") == 0)
        {
            printf("%s: %d\n", parent->name, atoi(parent->text)); // 打印整型值
        }
        else if (strcmp(parent->name, "FLOAT") == 0)
        {
            printf("%s: %f\n", parent->name, atof(parent->text)); // 打印浮点数值
        }
        else if (strcmp(parent->name, "ID") == 0 || strcmp(parent->name, "TYPE") == 0)
        {
            printf("%s: %s\n", parent->name, parent->text); // 打印标识符或类型名
        }
        else
        {
            printf("%s\n", parent->name); // 打印其他节点
        }
    }
}


void Travel_Tree(Node *Head)
{
    if (Head == NULL)
        return;

    if (strcmp(Head->name, "ExtDefList") == 0)
    {
        ExtDefList(Head); // 在所有递归调用完成返回后对外部定义列表进行语义分析
        return;
    }

    if (Head->child_num != 0)
        for (int i = 0; i < Head->child_num; i++)
            Travel_Tree(Head->child[i]); // 递归遍历子节点
}
