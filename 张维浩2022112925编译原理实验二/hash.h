#ifndef _MY_HASH_H_
#define _MY_HASH_H_

#include "node_utils.h" 
#include "Type.h"
#define HASH_SIZE 65536 

/*Hash utils*/
unsigned int hash_pjw(char *name);		   //PJW哈希算法	 
void Init_HashTable();							
int Insert_Symbol(ValList f);					
int EquType(TP type_1, TP type_2);	 
ValList Find_Symbol(char *name, int is_func); 
void Show_Symbol();	


#endif