#include "hash.h"
#include "node_utils.h"

ValList HashTable[HASH_SIZE]; // 哈希表数组作为符号表


/*Hash utils*/
// 散列表-P. J. Weinberge-hash 函数
unsigned int hash_pjw(char *name)
{ 
    unsigned int val = 0, i;
    for (; *name; ++name)
    {                             // 遍历字符串名字
        val = (val << 2) + *name; // 更新哈希值
        if (i = val & ~0x3fff)//符号表的大小（即 16384)
        {                                     // 如果存在高位溢出
            val = (val ^ (i >> 12)) & 0x3fff; // 则进行一次异或操作
        }
        return val % HASH_SIZE; // 返回哈希值
    }
}

void Init_HashTable()// 初始化哈希表函数
{ 
    // printf("11\n");
    for (int i = 0; i < HASH_SIZE; i++)
    {                        
       HashTable[i] = NULL; 
    }
}

int Insert_Symbol(ValList f)// 插入符号表符号
{                                    
    if (f == NULL)                   
        return 0;                    
    if (f->name == NULL)             
        return 0;                    
    
    f->collision = 0;                
    unsigned int key;                // 哈希键
    
    if (f->type->kd == 3)          // 函数类型
        key = hash_pjw(1 + f->name); // 此举是为了将函数名与其他类型变量名区分开，避免同名符号在哈希表中冲突
    else
        key = hash_pjw(f->name); 
    
    if (HashTable[key] == NULL)
    {                       
        HashTable[key] = f; 
        return 1;           
    }

    while (1)//若哈希表冲突
    {                                   
        key = (++key) % HASH_SIZE;       
        f->collision = f->collision + 1; 
        if (HashTable[key] == NULL)
        {                       
            HashTable[key] = f; 
            return 1;           
        }
    }
    return 0; //插入失败
}

ValList Find_Symbol(char *name, int is_func)// 查找符号
{ 
    if (name == NULL)
    {                
        return NULL; 
    }
    
    unsigned int key;             // 哈希键
    
    if (is_func)                 
        key = hash_pjw(1 + name); // 根据固定哈希值查找
    else
        key = hash_pjw(name);     // 否则计算哈希键
    
    ValList p = HashTable[key]; // 从哈希表中获取对应位置的字段列表
    
    while (p != NULL)//若哈希表冲突往后面找
    {
        if (strcmp(name, p->name) == 0)
        {                                                       
            if (is_func && (p->type->kd == 3)) //单独提出函数类型
                return p;                                       
            if ((!is_func) && (p->type->kd != 3)) 
                return p;                                       
        }
        key = (++key) % HASH_SIZE; 
        p = HashTable[key];        
    }
    return NULL; 
}

void Show_Symbol()// 输出符号表中所有类型符号
{ 
    for (int i = 0; i < HASH_SIZE; i++)
    { // 遍历哈希表
        if (HashTable[i] != NULL)
        {                                                                                 // 如果哈希表当前位置不为空
            printf("name: %s, kind: %d\n", HashTable[i]->name, HashTable[i]->type->kd); // 打印字段名称和类型
        }
    }
}

int EquType(TP type_1, TP type_2)// 判断类型是否相等
{                                           
    if ((type_1 == NULL) || (type_2 == NULL)) 
        return 0;                           
    if (type_1->kd != type_2->kd)         
        return 0;                           
    else
        switch (type_1->kd)
        { 
        case BASIC:
        {                                           
            if (type_1->u.basic == type_2->u.basic) 
                return 1;                           
            else
                return 0; 
        }
        break;
        case ARRAY:
        {                                                                   
            if (EquType(type_1->u.arrbase.elem, type_2->u.arrbase.elem) == 1)   // 递归判断元素基类型
                return 1;                                                   
            else
                return 0; 
        }
        break;
        case STRUCTURE:
        {                                           
            ValList field_1 = type_1->u.structname; // 获取结构体字段域（直接用名相等其实就可以了）
            ValList field_2 = type_2->u.structname; 
            if ((field_1 != NULL) && (field_2 != NULL))
            { 
                while ((field_1 != NULL) && (field_2 != NULL))
                { 
                    if (EquType(field_1->type, field_2->type) == 0)
                    {             
                        return 0; 
                    }
                    field_1 = field_1->next; // 获取下一个域
                    field_2 = field_2->next; 
                }
                if ((field_1 == NULL) && (field_2 == NULL)) //直到均为空
                    return 1;                            
            }
            return 0; 
        }
        break;
        case FUNCTION:
        {                                                                   
            if (type_1->u.func.param_num != type_2->u.func.param_num) 
                return 0;                                                   
            ValList param_1 = type_1->u.func.params;                   
            ValList param_2 = type_2->u.func.params;                   
            for (int i = 0; i < type_1->u.func.param_num; i++)
            {                                                   
                if (EquType(param_1->type, param_2->type) == 0) 
                    return 0;                                   
                param_1 = param_1->next;                          
                param_2 = param_2->next;                          
            }
            return 1; 
        }
        break;
        default:
        {             
            return 0; 
        }
        break;
        }
}