#include "node_utils.h"     
#include "semantic.h" 
#include "hash.h"
#include "Type.h"

/*构造语法树结点同时进行语义错误检测*/

// 遍历处理外部定义（全局变量，结构体，函数）列表，对全局变量和函数定义进行处理，
//包括添加符号表、检查重定义等操作。
void ExtDefList(Node *Head)
{
    // ExtDefList → ExtDef ExtDefList | e
    // ExtDef → Specifier ExtDecList SEMI | Specifier SEMI | Specifier FunDec CompSt
    Node *ExtDefList = Head; 
    while (ExtDefList->child_num != 0)
    {                                                    
        Node *ExtDef = ExtDefList->child[0];             
        TP basic_type = Specifier(ExtDef->child[0]); // 递归向下,Head=Specifier
        
        // 如果外部定义是外部变量定义（ExtDecList），则处理外部变量定义列表检查重定义，并将变量加入符号表。
        //ExtDecList → VarDec | VarDec COMMA ExtDecList       
        if (strcmp(ExtDef->child[1]->name, "ExtDecList") == 0)// 外部变量定义
        {                                  
            Node *temp = ExtDef->child[1]; // 获取外部变量定义列表节点temp=ExtDecList
            ValList val;
            while (temp->child_num == 3)//ExtDecList →VarDec COMMA ExtDecList 
            {                                                                                                     
                val = VarDec(temp->child[0], basic_type);    // 递归向下,Head=VarDec                                                    
                if (Find_Symbol(val->name, 0) != NULL)       // 如果在符号表中找到了同名的变量
                    printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", ExtDef->line_num, val->name); 
                    // 输出错误类型3：变量出现重复定义或变量与前面定义过的结构体名字重复。
                else
                    Insert_Symbol(val);
                temp = temp->child[2];   // 移动到下一个外部变量定义ExtDecList递归
            }
            
            val = VarDec(temp->child[0], basic_type);//最后一个ExtDecList                                                        
            
            if (Find_Symbol(val->name, 0) != NULL)                                                         
                printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", ExtDef->line_num, val->name); 
                // 输出错误类型3：变量出现重复定义或变量与前面定义过的结构体名字重复。
            else
                Insert_Symbol(val); 
        }
        
        // 如果外部定义是函数定义
        // ExtDef → Specifier FunDec CompSt
        /*
        FunDec → ID LP VarList RP | ID LP RP
        VarList → ParamDec COMMA VarList | ParamDec
        ParamDec → Specifier VarDec
        */
        else if (strcmp(ExtDef->child[1]->name, "FunDec") == 0)
        {                                                            
            ValList val = (ValList)malloc(sizeof(VALLIST));   //FunDec
            val->name = ExtDef->child[1]->child[0]->text;     // 获取函数名
            //初始化 函数 类型结构体指针
            TP typ = (TP)malloc(sizeof(TYPE));                       
            typ->kd = FUNCTION;                                     
            typ->u.func.func_type = basic_type;                   
            typ->u.func.param_num = 0;                           
            typ->u.func.params = NULL;                          

            if (strcmp(ExtDef->child[1]->child[2]->name, "VarList") == 0) // 如果有参数列表
            {                                              
                Node *VarList = ExtDef->child[1]->child[2]; 
                while (VarList->child_num != 1)//递归至最后一个params
                {                                                                                                         
                    TP temp_type = Specifier(VarList->child[0]->child[0]);  // 递归向下,Head=Specifier                                       
                    ValList temp_val = VarDec(VarList->child[0]->child[1], temp_type);//变量name与type                                  
                    if (Find_Symbol(temp_val->name, 0) != NULL)             // 如果在符号表中找到了同名的变量
                        printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", ExtDef->line_num, temp_val->name); 
                        // 输出错误类型3：变量出现重复定义或变量与前面定义过的结构体名字重复。
                    else
                        Insert_Symbol(temp_val);               
                    typ->u.func.param_num++;               
                    temp_val->next = typ->u.func.params; // 将读到的参数字段列表接到到参数列表链表后
                    typ->u.func.params = temp_val;       // 更新参数列表链首
                    VarList = VarList->child[2];         // 递归下一个VarList
                }
                TP temp_type = Specifier(VarList->child[0]->child[0]); // 递归向下,Head=Specifier                                            
                ValList temp_val = VarDec(VarList->child[0]->child[1], temp_type);                                  
                if (Find_Symbol(temp_val->name, 0) != NULL)                                                         
                    printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", ExtDef->line_num, temp_val->name); 
                    // 输出错误类型3：变量出现重复定义或变量与前面定义过的结构体名字重复。
                else
                    Insert_Symbol(temp_val);               
                typ->u.func.param_num++;               
                temp_val->next = typ->u.func.params; // 将读到的参数字段列表接到到参数列表链表后
                typ->u.func.params = temp_val;       // 更新参数列表链首
            }
            val->type = typ;                                                                                
            if (Find_Symbol(val->name, 1) != NULL)                                                         // 如果在符号表中找到了同名的函数
                printf("Error type 4 at Line %d: Redefined function \"%s\".\n", ExtDef->line_num, val->name);
                //错误类型4：函数出现重复定义（即同样的函数名被多次定义）。
            else
                Insert_Symbol(val); 

            CompSt(ExtDef->child[2], basic_type); // 处理函数体
        }
        
        else
        { // 如果是其他类型的定义，例如声明ExtDef → Specifier SEMI
          // do nothing
        }

        if (ExtDefList->child[1] == NULL) // 如果没有下一个外部定义节点 ExtDefList → e
            return;
        ExtDefList = ExtDefList->child[1]; // 移动到下一个外部定义节点(如多个int main) ExtDefList → ExtDef ExtDefList
    }
}


// 解析类型声明的语法树节点，并生成对应的类型信息，支持基本类型和结构体类型。
TP Specifier(Node *Head)
{
    // Specifier → TYPE
    TP spec = (TP)malloc(sizeof(TYPE)); 
    if (strcmp(Head->child[0]->name, "TYPE") == 0)
    {                                                
        spec->kd = BASIC;                            
        if (strcmp(Head->child[0]->text, "int") == 0) 
            spec->u.basic = Type_INT;                 // 设置基本类型为INT_TYPE
        else
            spec->u.basic = Type_FLOAT; // 设置基本类型为FLOAT_TYPE
        return spec;                     // 返回类型指针
    }
    
    // Specifier ->     
    /*
       StructSpecifier → STRUCT OptTag LC DefList RC | STRUCT Tag
       OptTag → ID | e
       Tag → ID
       */
    else
    {
        spec->kd = STRUCTURE; 
        if (Head->child[0]->child_num == 2)// StructSpecifier → STRUCT Tag
        {                                                       
            char *s = Head->child[0]->child[1]->child[0]->text; // 获取Tag节点的名称ID
            ValList val = Find_Symbol(s, 0);               // 在符号表中查找该名称对应的字段列表
            if (val == NULL)
            {                                                                                       
                printf("Error type 17 at Line %d: Undefined structure \"%s\".\n", Head->line_num, s); 
                //错误类型17：直接使用未定义过的结构体来定义变量。
                spec->u.structname = NULL;                                                          
                return spec;                                                                      
            }
            else if (val->type != NULL) 
                return val->type;      
            spec->u.structname = NULL;     // 设置结构体类型字段列表为空,因为无LC DefList RC
            return spec;                  
        }
        else //StructSpecifier → STRUCT OptTag LC DefList RC
        {                                               // 如果不存在OptTag节点，表示是匿名结构体，需要处理结构体定义列表
            Node *DefList = Head->child[0]->child[3];   // 获取DefList节点
            spec->u.structname = NULL;                  // 设置结构体类型字段列表为空
            
            // 在结构体内的DefList与外部函数体CompSt的不同，不能在义时对域进行初始化（例如 struct A { int a = O; ｝)
            /*
           DefList → Def DefList | e
           Def →Specifier DecList  SEMI
           DecList → Dec | Dec COMMA DecList
           Dec → VarDec | VarDec ASSIGNOP Exp
           */
            while (DefList != NULL) //直到 DefList → e
            {                                                 // 递归处理每个Def节点
                Node *Def = DefList->child[0];                
                TP basic_type = Specifier(Def->child[0]);     // 递归调用Specifier获取基本类型

                Node *DecList = Def->child[1]; // Def →Specifier DecList  SEMI
                while (DecList->child_num == 3) // DecList → Dec COMMA DecList
                {                                                                                                              
                    ValList val = VarDec(DecList->child[0]->child[0], basic_type); //Head=VarDec                                       
                    
                    if (DecList->child[0]->child_num != 1)   // 如果Dec节点的子节点数不为1，Dec →VarDec ASSIGNOP Exp
                        printf("Error type 15 at Line %d: Variable %s in struct is initialized.\n", Def->line_num, val->name); 
                        //错误类型 15:结构体中域名重复定义（指同一结构体中），或在定义时对域进行初始化（例如 struct A { int a = O; ｝)
                    
                    ValList temp = spec->u.structname;   //用于遍历结构体中关键字类型,spec->u.structname定义在if (temp == NULL)后                                                                    
                    
                    //Dec → VarDec
                    while (temp != NULL)// 循环检查是否存在重定义的字段
                    { 
                        if (strcmp(temp->name, val->name) == 0)
                        {                                                                                            
                            printf("Error type 15 at Line %d: Redefined field \"%s\".\n", Def->line_num, val->name); 
                            //错误类型 15:结构体中域名重复定义（指同一结构体中），或在定义时对域进行初始化（例如 struct A { int a = O; ｝)
                            break;                                                                                   
                        }
                        temp = temp->next; // 移动到下一个字段
                    }
                    
                    if (temp == NULL)//补充spec->u.structname定义
                    {                                                                                                  
                        if (Find_Symbol(val->name, 0) != NULL)                                                      
                            printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", Def->line_num, val->name); 
                        //错误类型 3: 变量出现重复定义或变址与前面定义过的结构体名字重复
                        else
                        {                                    
                            Insert_Symbol(val);             // 在符号表中插入字段列表
                            val->next = spec->u.structname; // 将字段列表加入到结构体类型的字段列表中
                            spec->u.structname = val;       // 更新结构体类型的字段列表链表
                        }
                    }
                    DecList = DecList->child[2]; // 获取下一个Dec节点
                }
                
                //DecList → Dec,最后一个Dec
                ValList val = VarDec(DecList->child[0]->child[0], basic_type); //Head=VarDec                                              
                if (DecList->child[0]->child_num != 1)                                                                          
                    printf("Error type 15 at Line %d: Variable \"%s\" in struct is initialized.\n", Def->line_num, val->name);
                    //错误类型 15:结构体中域名重复定义（指同一结构体中），或在定义时对域进行初始化（例如 struct A { int a = O; ｝)
                ValList temp = spec->u.structname;                                                                           
                while (temp != NULL)
                { // 循环检查是否存在重定义的字段
                    if (strcmp(temp->name, val->name) == 0)
                    {                                                                                            
                        printf("Error type 15 at Line %d: Redefined field \"%s\".\n", Def->line_num, val->name); 
                        //错误类型 15:结构体中域名重复定义（指同一结构体中），或在定义时对域进行初始化（例如 struct A { int a = O; ｝)
                        break;                                                                                  
                    }
                    temp = temp->next; // 移动到下一个字段
                }
                if (temp == NULL)
                {                                                                                                  
                    if (Find_Symbol(val->name, 0) != NULL)                                                      
                        printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", Def->line_num, val->name); 
                    //错误类型 3: 变量出现重复定义或变址与前面定义过的结构体名字重复
                    else
                    {                                    
                        Insert_Symbol(val);             
                        val->next = spec->u.structname; 
                        spec->u.structname = val;       
                    }
                }
                DefList = DefList->child[1]; // 递归下一个Def节点null
            }
            
            //若存在OptTag节点，Specifier -> StructSpecifier
            /*StructSpecifier → STRUCT OptTag LC DefList RC*/
            if (Head->child[0]->child[1] != NULL)//->child[1]?
            {                                                                                                 
                ValList val = (ValList)malloc(sizeof(VALLIST));                                      
                val->type = spec;                                                                            
                char *s = Head->child[0]->child[1]->child[0]->text; //OptTag->ID                                         
                val->name = s;                                                                             
                if (Find_Symbol(val->name, 0) != NULL)                                                     
                    printf("Error type 16 at Line %d: Duplicated name \"%s\".\n", Head->line_num, val->name); 
                //错误类型 16 结构体的名字与前面定义过的结构体或变址的名字重复
                else
                    Insert_Symbol(val); // 在符号表中插入字段列表
            }
            return spec; // 返回结构体类型指针
        }
    }
}

// 根据变量声明的语法树节点，构造变量的类型信息 支持基本类型、一维数组和二维数组的声明。
ValList VarDec(Node *Head, TP basic_type)
{
    Node *temp = Head; // 临时节点指针指向根节点VarDec
    int i = 0;         // 记录当前节点是在多少级别的嵌套下
    /*VarDec->ID
      VarDec->VarDec LB INT RB
      数组  */
    while (strcmp(temp->child[0]->name, "ID") != 0)
    {                          // 循环VarDec->VarDec LB INT RB直到找到ID节点
        temp = temp->child[0]; // 移动到第一个子节点
        i++;                   
    }
    char *s = temp->child[0]->text; // 获取ID节点的文本内容，即变量名

    ValList val = (ValList)malloc(sizeof(VALLIST)); 
    val->name = s;                                         

    if (strcmp(Head->child[0]->name, "ID") == 0)
    {                            
        val->type = basic_type; 
        return val;            // 返回字段列表
    }

    switch (i)
    { // 根据计数器值进行分支判断，最多允许二维数组
    case 1:
    {
        TP var_1 = (TP)malloc(sizeof(TYPE));    
        var_1->kd = ARRAY;                               
        var_1->u.arrbase.size = atoi(Head->child[2]->text); // VarDec->VarDec LB INT RB
        var_1->u.arrbase.elem = basic_type;                  
        val->type = var_1;                                  // 将字数组类型存入字段链表
        return val;                                     
    }
    break;
    case 2:
    {
        // 外层数组
        TP var_1 = (TP)malloc(sizeof(TYPE));              
        var_1->kd = ARRAY;                                         
        var_1->u.arrbase.size = atoi(Head->child[2]->text); // VarDec->VarDec LB INT RB
        var_1->u.arrbase.elem = basic_type;                            
       //内层数组
        TP var_2 = (TP)malloc(sizeof(TYPE));              
        var_2->kd = ARRAY;                                         // 设置类型种类为数组
        var_2->u.arrbase.size = atoi(Head->child[0]->child[2]->text); // VarDec->VarDec LB INT RB递归查二级数组大小
        var_2->u.arrbase.elem = basic_type;                  
        val->type = var_2;                                  // 将字数组类型存入字段链表
        return val;
    }
    break;
    default:
        printf("error in VarDec");
        break; // 默认情况下输出错误信息
        while(i>2){//删
                i--;
                goto case 2;
        }
    }
}

// 处理函数内部的复合语句，包括处理局部变量的声明和语句块内的语句
void CompSt(Node *Head, TP func_type)
{
    // CompSt → LC DefList StmtList RC
    // 直接非递归解析deflist
    // stmtlist直接无脑递归处理
    Node *CompSt = Head;               // CompSt = Head
    DefList(CompSt->child[1]);         // DefList = Head
    Node *StmtList = CompSt->child[2]; // 获取语句列表节点
    while (StmtList != NULL)
    { //StmtList->Stmt StmtList | e                                    
        Node *Stmt_ = StmtList->child[0]; 
        Stmt(Stmt_, func_type);            
        StmtList = StmtList->child[1];    // 递归下一个stmtlist
    }
}

// 处理局部变量的定义列表，包括添加符号表、检查重定义等操作，区别于结构体内的DefList
/*
    DefList → Def DefList | e
    Def → Specifier DecList SEMI
    DecList → Dec | Dec COMMA DecList
    Dec → VarDec | VarDec ASSIGNOP Exp
*/
void DefList(Node *Head)
{
    Node *DefList = Head; // DefList = Head
    while (DefList != NULL)
    {                                                 
        Node *Def = DefList->child[0];                
        TP basic_type = Specifier(Def->child[0]); 
        Node *DecList = Def->child[1];                // 获取声明列表节点
        while (DecList->child_num == 3)
        { 
            // DecList → Dec | Dec COMMA DecList
            // Dec → VarDec | VarDec ASSIGNOP Exp                                                                                                     // 循环处理每个声明
            ValList val = VarDec(DecList->child[0]->child[0], basic_type);                                  
            if (Find_Symbol(val->name, 0) != NULL)                                                          
                        printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", DecList->line_num, val->name); 
                    //错误类型 3: 变量出现重复定义或变址与前面定义过的结构体名字重复
            else
                Insert_Symbol(val);     // 在符号表中插入字段列表
            DecList = DecList->child[2]; // 递归到下一个DecList
        }
        
        // DecList → Dec
        ValList val = VarDec(DecList->child[0]->child[0], basic_type);     // 获取最后一个声明
        if (Find_Symbol(val->name, 0) != NULL)                                                          
                        printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", DecList->line_num, val->name); 
                    //错误类型 3: 变量出现重复定义或变址与前面定义过的结构体名字重复 
        else
            Insert_Symbol(val);       // 在符号表中插入字段列表
        
        //DefList → e
        if (DefList->child[1] == NULL) // 如果没有下一个定义节点
            return;
        //DefList → Def DefList
        DefList = DefList->child[1]; // 移动到下一个定义节点DefList
    }
}

// 根据语法树节点的类型，处理不同类型的语句，包括返回语句、表达式语句、复合语句、循环语句、条件语句等。
/*
   Stmt → Exp SEMI | CompSt | RETURN Exp SEMI | IF LP Exp RP Stmt | IF LP Exp RP Stmt ELSE Stmt | WHILE LP Exp RP Stmt
 */
void Stmt(Node *Head, TP func_type)
{
    Node *Stmt_ = Head;                                                                      // Stmt = Head
    // RETURN Exp SEMI
    if (strcmp(Stmt_->child[0]->name, "RETURN") == 0)                                       
    {                                                                                        // 如果是返回语句
        TP return_type = Exp(Stmt_->child[1]);                                               // 获取返回值类型
        if (EquType(func_type, return_type) == 0)                                            // 返回值类型与函数返回类型不匹配
            printf("Error type 8 at Line %d: Type mismatched for return.\n", Stmt_->line_num); 
            //错误类型 8: return 语句的返回类型与函数定义的返回类型不匹配
    }
    else if (strcmp(Stmt_->child[0]->name, "Exp") == 0) // Exp SEMI表达式
    {                                                   
        Exp(Stmt_->child[0]);                           // 处理表达式
    }
    else if (strcmp(Stmt_->child[0]->name, "CompSt") == 0) // CompSt复合语句块
    {                                                      
        CompSt(Stmt_->child[0], func_type);                 // 处理复合语句块
    }
    else if (strcmp(Stmt_->child[0]->name, "WHILE") == 0) // WHILE LP Exp RP Stmt
    {                                                                                                       
        TP typ = Exp(Stmt_->child[2]);                    // 获取判断条件的类型
        if (!((typ->kd == BASIC) && (typ->u.basic == Type_INT)))   // 如果判断条件不是INT类型
            printf("Error type 5 at Line %d: Only type INT could be used for judgement.\n", Stmt_->line_num); 
            //错误类型5 只有整数才能用于判断
        Stmt(Stmt_->child[4], func_type);                                                                    // 处理循环体
    }
    else if (Stmt_->child_num < 6)          //IF LP Exp RP Stmt
    {                                       // 如果是单独的IF语句
        TP typ = Exp(Stmt_->child[2]); // 获取判断条件的类型
        if (typ != NULL)//排除while
            if (!((typ->kd == BASIC) && (typ->u.basic == Type_INT)))                                         // 如果判断条件不是INT类型
                printf("Error type 5 at Line %d: Only type INT could be used for judgement.\n", Stmt_->line_num); 
                //错误类型5 只有整数才能用于判断
        Stmt(Stmt_->child[4], func_type);                                                                        // 处理IF语句的主体
    }
    else    //IF LP Exp RP Stmt ELSE Stmt,如果是带有ELSE的IF语句
    {                                                                                                       
        TP typ = Exp(Stmt_->child[2]);                                                                 
        if (!((typ->kd == BASIC) && (typ->u.basic == Type_INT)))                                         // 如果判断条件不是INT类型
                printf("Error type 5 at Line %d: Only type INT could be used for judgement.\n", Stmt_->line_num); 
                //错误类型5 只有整数才能用于判断
        Stmt(Stmt_->child[4], func_type);                                                                    // 处理IF语句的主体
        Stmt(Stmt_->child[6], func_type);                                                                    // 处理ELSE语句的主体
    }
}

// 根据语法树节点的类型，处理不同类型的表达式，包括变量、整数、浮点数、运算符、赋值语句、函数调用、结构体成员访问、数组访问等
TP Exp(Node *Head)
{
    
    if (Head == NULL)
        return NULL; // 如果节点为空，则返回空指针

    // Exp->ID，这应为已定义的变量
    else if ((strcmp(Head->child[0]->name, "ID") == 0) && (Head->child_num == 1))
    {                                                            // 如果是单个ID节点
        ValList val = Find_Symbol(Head->child[0]->text, 0); // 查找符号表中的变量
        if (val != NULL)
            return val->type; // 返回变量的类型
        else
        {
            printf("Error type 1 at Line %d: Undefined variable \"%s\".\n", Head->line_num, Head->child[0]->text); 
            //错误类型1 :变量在使用时未经定义
            return NULL;
        }
    }

    // Exp->INT
    else if (strcmp(Head->child[0]->name, "INT") == 0)
    {                                                 
        TP typ = (TP)malloc(sizeof(TYPE)); 
        typ->kd = BASIC;
        typ->u.basic = Type_INT;
        return typ; // 返回整数类型
    }

    // Exp->FLOAT
    else if (strcmp(Head->child[0]->name, "FLOAT") == 0)
    {                                                 
        TP typ = (TP)malloc(sizeof(TYPE)); 
        typ->kd = BASIC;
        typ->u.basic = Type_FLOAT;
        return typ; 
    }

    // Exp->MINUS Exp | NOT Exp | LP Exp RP
    else if ((strcmp(Head->child[0]->name, "LP") == 0) || (strcmp(Head->child[0]->name, "MINUS") == 0) || (strcmp(Head->child[0]->name, "NOT") == 0))
    {
        return Exp(Head->child[1]); // 如果是括号、负号或非运算符，则递归处理子表达式
    }

    // 以下是形如Exp OP Exp的产生式形式
    // 在语义分析看来它们没区别，只需要检查两边操作数类型是否是一致的INT/FLOAT即可
    // Exp STAR Exp
    // Exp DIV Exp
    // Exp PLUS Exp
    // Exp MINUS Exp
    else if ((strcmp(Head->child[1]->name, "PLUS") == 0) || (strcmp(Head->child[1]->name, "MINUS") == 0) || (strcmp(Head->child[1]->name, "STAR") == 0) || (strcmp(Head->child[1]->name, "DIV") == 0))
    {
        TP typ_1 = Exp(Head->child[0]); // 获取左操作数的类型结构体指针
        TP typ_2 = Exp(Head->child[2]); // 获取右操作数的类型结构体指针
        if (EquType(typ_1, typ_2) == 0)
        { // 如果左右操作数类型不匹配
            if ((typ_1 != NULL) && (typ_2 != NULL))
                printf("Error type 7 at Line %d: Type mismatched for operands.\n", Head->line_num); 
            // 错误类型7：操作数类型不匹配或操作数类型与操作符不匹配（例如整型变量与数组变量相加减 或数组（或结构体）变址与数组（或结构体）结构体变量相加减）
            return NULL;
        }
        else
            return typ_1; // 返回左操作数的类型
    }
    // Exp RELOP Exp
    // Exp AND Exp
    // Exp OR Exp
    else if ((strcmp(Head->child[1]->name, "AND") == 0) || (strcmp(Head->child[1]->name, "OR") == 0) || (strcmp(Head->child[1]->name, "RELOP") == 0))
    {
        TP typ_1 = Exp(Head->child[0]); // 获取左操作数的类型结构体指针
        TP typ_2 = Exp(Head->child[2]); // 获取右操作数的类型结构体指针
        if (EquType(typ_1, typ_2) == 0)
        { // 如果左右操作数类型不匹配
            if ((typ_1 != NULL) && (typ_2 != NULL))
                printf("Error type 7 at Line %d: Type mismatched for operands.\n", Head->line_num); 
            // 错误类型7：操作数类型不匹配或操作数类型与操作符不匹配（例如整型变量与数组变量相加减 或数组（或结构体）变址与数组（或结构体）结构体变量相加减）
            return NULL;
        }
        else
        {
            TP typ = (TP)malloc(sizeof(TYPE)); // 分配内存
            typ->kd = BASIC;
            typ->u.basic = Type_INT;
            return typ; // 返回类型
        }
    }

    // Exp = Exp，赋值
    else if (strcmp(Head->child[1]->name, "ASSIGNOP") == 0)
    {
        // 左边是变量，否则不能给他赋值
        if (Head->child[0]->child_num == 1)
        {
            if (!(strcmp(Head->child[0]->child[0]->name, "ID") == 0))//Exp = Exp,Exp->ID
            {
                printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", Head->line_num); 
                // 错误类型6: 赋值号左边出现一个只有右值的表达式
                return NULL;
            }
        }
        else if (Head->child[0]->child_num == 3)//Exp->Exp DOT ID结构体访问
        {
            if (!((strcmp(Head->child[0]->child[0]->name, "Exp") == 0) && (strcmp(Head->child[0]->child[1]->name, "DOT") == 0) && (strcmp(Head->child[0]->child[2]->name, "ID") == 0)))
            {
                printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", Head->line_num); 
                // 错误类型6: 赋值号左边出现一个只有右值的表达式
                return NULL;
            }
        }
        else if (Head->child[0]->child_num == 4)//Exp->Exp LB Exp RB结构体访问
        {
            if (!((strcmp(Head->child[0]->child[0]->name, "Exp") == 0) && (strcmp(Head->child[0]->child[1]->name, "LB") == 0) && (strcmp(Head->child[0]->child[2]->name, "Exp") == 0) && (strcmp(Head->child[0]->child[3]->name, "RB") == 0)))
            {
                printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", Head->line_num); 
                // 错误类型6: 赋值号左边出现一个只有右值的表达式
                return NULL;
            }
        }
        TP typ_1 = Exp(Head->child[0]); // 递归获取左操作数的类型结构体指针
        TP typ_2 = Exp(Head->child[2]); // 递归获取右操作数的类型结构体指针
        if (EquType(typ_1, typ_2) == 0)
        { // 如果左右操作数类型不匹配
            if ((typ_1 != NULL) && (typ_2 != NULL))
                printf("Error type 5 at Line %d: Type mismatched for assignment.\n", Head->line_num); 
            // 错误类型7：操作数类型不匹配或操作数类型与操作符不匹配（例如整型变量与数组变量相加减 或数组（或结构体）变址与数组（或结构体）结构体变量相加减）
            return NULL;
        }
        else
            return typ_1; // 返回左操作数的类型
    }

    // Exp -> ID LP RP | ID LP Args RP  函数调用
    else if (strcmp(Head->child[0]->name, "ID") == 0)
    {                                                          // 如果是ID节点
        ValList fie = Find_Symbol(Head->child[0]->text, 1); // 查找符号表中的函数，FunDec部分记录的
        
        if (fie == NULL)
        {
            ValList fie2 = Find_Symbol(Head->child[0]->text, 0);
            if (fie2 != NULL)
                printf("Error type 11 at Line %d: \"%s\" is not a function.\n", Head->line_num, Head->child[0]->text); 
            // 错误类型 11:对普通变量使用”(· .. )"或“()＂（函数调用）操作符
            else
                printf("Error type 2 at Line %d: Undefined function \"%s\".\n", Head->line_num, Head->child[0]->text); 
            // 错误类型2:函数在调用时未经定义
            return NULL;
        }
        
        TP defined_type = fie->type;

        TP typ = (TP)malloc(sizeof(TYPE)); 
        typ->kd = FUNCTION;
        typ->u.func.param_num = 0;
        typ->u.func.params = NULL;
        
        // Exp -> ID LP Args RP
        if (strcmp(Head->child[2]->name, "RP") != 0)
        { // 如果有参数
            Node *temp = Head->child[2];//Args
            while (temp->child_num != 1)//直到Args-> Exp
            {                                                            // 遍历参数列表
                TP temp_type = Exp(temp->child[0]);                      // 获取参数类型
                ValList temp_val = (ValList)malloc(sizeof(VALLIST));     // 分配内存
                temp_val->name = "no";                                   //任意，用于临时比较
                temp_val->type = temp_type;
                
                typ->u.func.param_num++;
                temp_val->next = typ->u.func.params;                     //建造typ链头形参列表
                typ->u.func.params = temp_val;

                temp = temp->child[2];//Args->Exp COMMA Args 
            }
            //直到Args-> Exp
            TP temp_type = Exp(temp->child[0]);                      // 获取最后一个参数的类型
            ValList temp_val = (ValList)malloc(sizeof(VALLIST));     // 分配内存
            temp_val->name = "no";                                   //任意，用于临时比较
            temp_val->type = temp_type;
            
            typ->u.func.param_num++;
            temp_val->next = typ->u.func.params;                     //建造typ链头形参列表(函数形参)Exp部分生成的
            typ->u.func.params = temp_val;
        }
        
        if (EquType(typ, defined_type) == 0)
        {
            printf("Error type 9 at Line %d: Params wrong in function \"%s\".\n", Head->line_num, Head->child[0]->text); 
            // 错误类型 9: 函数调用时实参与形参的数目或类型不匹配
            return NULL;
        }
        else
            return defined_type->u.func.func_type; // 返回函数返回值类型
    }

    // Exp DOT ID 结构体成员访问
    else if (strcmp(Head->child[1]->name, "DOT") == 0)
    {                                       // 如果是结构体成员访问节点
        TP typ_1 = Exp(Head->child[0]); // 获取结构体变量的类型
        
        if (typ_1->kd != STRUCTURE)
        {
            Node *temp = Head->child[0];
            char *s;
           
            switch (temp->child_num)
            {
            case 1://Exp -> ID
            {
                if (strcmp(temp->child[0]->name, "ID") == 0)
                    s = temp->child[0]->text; // 若结构体变量是一个标识符，则将其文本内容赋值给变量 s
            }
            break;
            case 3://Exp -> ID->ID
            {
                if (strcmp(temp->child[2]->name, "ID") == 0)
                    s = temp->child[0]->text; // 若结构体变量是通过指针访问，则将其文本内容赋值给变量 s
            }
            break;
            case 4://Exp ->Exp LB Exp RB
            {
                if (strcmp(temp->child[0]->name, "Exp") == 0)
                    if (strcmp(temp->child[0]->child[0]->name, "ID") == 0)
                        s = temp->child[0]->child[0]->text; // 若结构体变量是通过数组成员访问，则将其文本内容赋值给变量 s
            }
            break;
            default:
                s = "error"; // 若无法确定结构体变量类型，则将 s 设置为 "error"
                break;
            }
            
            if (Find_Symbol(s, 0) != NULL)//之前声明过该变量
                printf("Error type 13 at Line %d: Illegal use of \".\".\n", Head->line_num); 
            // 错误类型 13：对非结构体型变批使用”.“操作符
            return NULL;
        }
        
        char *s = Head->child[2]->text;      // 获取ID成员名
        ValList temp = typ_1->u.structname; // 遍历结构体成员列表
        
        while (temp != NULL)
        {
            if (strcmp(temp->name, s) == 0)
                return temp->type; // 根据name查找成员类型

            temp = temp->next;
        }

        printf("Error type 14 at Line %d: Non-existent field \"%s\".\n", Head->line_num, Head->child[2]->text); 
        // 错误类型14： 访问结构体中未定义过的域
        return NULL;
    }

    // Exp -> Exp LB Exp RB 数组访问
    else if (strcmp(Head->child[1]->name, "LB") == 0)
    {                                       // 如果是数组访问节点
        TP typ_1 = Exp(Head->child[0]); // 获取数组变量的类型
        
        if (typ_1->kd != ARRAY)
        {
            Node *temp = Head->child[0];
            char *s;
            
            switch (temp->child_num)//查数组名
            {
            case 1:
            {
                if (strcmp(temp->child[0]->name, "ID") == 0) // 标识符
                    s = temp->child[0]->text;
            }
            break;
            case 3://Exp -> ID->ID
            {
                if (strcmp(temp->child[2]->name, "ID") == 0) // 指针访问
                    s = temp->child[0]->text;
            }
            break;
            case 4://Exp ->Exp LB Exp RB,Exp -> ID
            {
                if (strcmp(temp->child[0]->name, "Exp") == 0)
                    if (strcmp(temp->child[0]->child[0]->name, "ID") == 0) // 数组成员访问
                        s = temp->child[0]->child[0]->text;
            }
            break;
            default:
                s = "error";
                break;
            }
            if (Find_Symbol(s, 0) != NULL)
                printf("Error type 10 at Line %d: \"%s\" is not an array.\n", Head->line_num, s); 
            // 错误类型 10: 对非数组型变量使用“ [...]＂（数组访问）操作符
            return NULL;
        }
        
        TP temp = Exp(Head->child[2]); // 获取数组索引的类型
        
        if (temp->kd != BASIC)
        {
            printf("Error type 12 at Line %d: there is not an integer between \"[\" and \"]\".\n", Head->line_num);
            // 错误类型 12: 数组访问操作符”[...]”中出现非整数（例如 a[1.5]）
            return NULL;
        }
        else if (temp->u.basic == Type_FLOAT)
        {
            printf("Error type 12 at Line %d: there is not an integer between \"[\" and \"]\".\n", Head->line_num);
            printf("%f is not an integer.\n", atof(Head->child[2]->child[0]->text)); 
            // 错误类型 12: 数组访问操作符”[...]”中出现非整数（例如 a[1.5]）
            return NULL;
        }
        
        // 无错误，返回数组元素类型
        return typ_1->u.arrbase.elem;//VarList中定义的
    }

    else
    {
        printf("in\n"); // 输出错误信息
        return NULL;    // 返回空指针
    }
}

