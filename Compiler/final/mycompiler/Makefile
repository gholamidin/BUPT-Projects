LEX=flex
YACC=bison
CC=g++
OBJECT=compiler #生成的目标文件

$(OBJECT): lex.yy.o  my_yacc.tab.o
	$(CC) lex.yy.o my_yacc.tab.o -o $(OBJECT)
	@./$(OBJECT) #编译后立刻运行

lex.yy.o: lex.yy.c  my_yacc.tab.h variable1.h
	$(CC) -c lex.yy.c -ll -lfl

my_yacc.tab.o: my_yacc.tab.c
	$(CC) -c my_yacc.tab.c

my_yacc.tab.c  my_yacc.tab.h: my_yacc.y
# bison使用-d参数编译.y文件
	$(YACC) -d my_yacc.y

lex.yy.c: my_lex.l
	$(LEX) my_lex.l 

clean:
	@rm -f $(OBJECT)  *.o
