#ifndef _MY_TYPE_H_
#define _MY_TYPE_H_

typedef enum KIND// 类型种类枚举体
{
	BASIC,//type:int/float
	ARRAY,
	STRUCTURE,
	FUNCTION 
} kind;

typedef struct TYPE *TP;		  // 类型指针
typedef struct VALLIST *ValList; // 域列表指针，Hash表数组基类型

typedef struct TYPE
{
	kind kd; 
	union
	{
		int basic;// 基本类型
		struct	  // 数组类型
		{
			int size;
			TP elem; // 元素类型指针
		} arrbase;
		ValList structname; // 域列表指针存结构体类型名(结构体中关键字)
		struct	  // 函数类型
		{
			ValList params; // 形参域列表
			TP func_type; // 函数返回值类型
			int param_num;	  
		} func;
	} u; 
} TYPE;

typedef struct VALLIST//类似链表，参数域
{
	char *name;		
	TP type;	
	ValList next;   // 下一个域
	int collision;	// 哈希冲突次数
} VALLIST;


#endif