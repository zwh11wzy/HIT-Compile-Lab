CC = gcc                 # 定义C编译器
FLEX = flex              # 定义flex工具
BISON = bison            # 定义bison工具
CFLAGS = -std=c99        # 定义编译选项

CFILES = $(shell find ./ -name "*.c")      # 查找所有.c文件
OBJS = $(CFILES:.c=.o)                     # 将.c文件路径转换为.o文件路径
LFILE = $(shell find ./ -name "*.l")       # 查找所有.l文件(flex词法分析器)
YFILE = $(shell find ./ -name "*.y")       # 查找所有.y文件(bison语法分析器)
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)  # 生成flex输出文件名
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)  # 生成bison输出文件名
LFO = $(LFC:.c=.o)       # flex生成的C文件对应的目标文件
YFO = $(YFC:.c=.o)       # bison生成的C文件对应的目标文件

# 生成最终的parser可执行文件
parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) -lfl

# 编译由bison生成的语法分析器代码
syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

# 使用flex生成词法分析器的C代码
lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

# 使用bison生成语法分析器的C代码
syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))
# 包含了自动生成的依赖文件，实现了更精细的增量编译。
.PHONY: clean test
# 测试目标
test:
	./parser ./test1.cmm
	./parser ./test2.cmm
	./parser ./test3.cmm
	./parser ./test4.cmm
# 清理目标
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
