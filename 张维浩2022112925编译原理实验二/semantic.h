#ifndef _SEMANTIC_H_ 
#define _SEMANTIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node_utils.h"
#include "Type.h"

#define Type_INT 1
#define Type_FLOAT 2
#define Type_Struct 3
#define Type_Array 4
#define Type_Func 5							

void ExtDefList(Node *Head);			   // 外部定义（全局变量，结构体，函数）列表，递归出口 
TP Specifier(Node *Head);				   // 类型符说明 					 
ValList VarDec(Node *Head, TP basic_type); // 变量声明，递归调用Specifier获取基本类型
void CompSt(Node *Head, TP func_type);	   // 语句块 
void DefList(Node *Head);				   // 变量定义列表	 
void Stmt(Node *Head, TP func_type);	   // 语句 
TP Exp(Node *Head);						   // 表达式

#endif