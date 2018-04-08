%{
	//需要包括的头文件已经自定义的函数和变量的声明
	#include <stdio.h>
	#include <stdlib.h>
	#include<math.h>
	#include "variable1.h"
	#include "my_yacc.tab.h"
	int id_num=0;
	int num_num=0;
	int digit=0;
	int row_no = 1;
	int col_no = 1;
	char *curfilename;
	void wrong();
	void lex_return();
	string big2low(string bigstr);
	
	extern "C"
	{
		int yywrap(void);
		int yylex(void);
	}

%}

 /*正则表达式识别换行符、标识符、数字和字符等*/
delim				[\t]
ws					{delim}+
letter				[A-Za-z]
digit				[0-9]
digits				{digit}+
id					{letter}({letter}|{digit})*
num					{digits}(\.{digits})?(E[+\-]?{digits})?
newline				[\n]
%%

 /*关键字的识别*/
[Bb][Ee][Gg][Ii][Nn]				        {lex_return(); return(BEGIN1);}
[pP][rR][oO][gG][rR][aA][mM]				{lex_return(); return(PROGRAM);}
[vV][aA][rR]								{lex_return(); return(VAR);}
[aA][rR][rR][aA][yY]				        {lex_return(); return(ARRAY);}
[rR][eE][cC][oO][rR][dD]				    {lex_return(); return(RECORD);}
[eE][nN][dD]				                {lex_return(); return(END);}
[oO][fF]					                {lex_return(); return(OF);}
[iI][nN][tT][eE][gG][eE][rR]				{lex_return(); return(INTEGER);}
[rR][eE][aA][lL]							{lex_return(); return(REAL);}
[bB][oO][oO][lL][eE][aA][nN]				{lex_return(); return(BOOLEAN);}
[fF][uU][nN][cC][tT][iI][oO][nN]			{lex_return(); return(FUNCTION);}
[pP][rR][oO][cC][eE][dD][uU][rR][eE]	    {lex_return(); return(PROCEDURE);}
[iI][fF]									{lex_return(); return(IF);}
[tT][hH][eE][nN] 							{lex_return(); return(THEN);}
[eE][lL][sS][eE]							{lex_return(); return(ELSE);}
[wW][hH][iI][lL][eE]						{lex_return(); return(WHILE);}
[dD][oO]					                {lex_return(); return(DO);}
[rR][eE][aA][dD]							{lex_return(); return(READ);}
[wW][rR][iI][tT][eE]				        {lex_return(); return(WRITE);}
[nN][oO][tT]								{lex_return(); return(NOT);}
[tT][rR][uU][eE]							{lex_return(); return(TRUE);}
[fF][aA][lL][sS][eE]						{lex_return(); return(FALSE);}
[fF][oO][rR]					  			{lex_return(); return(FOR);}
[tT][oO]					                {lex_return(); return(TO);}
[cC][oO][nN][Ss][Tt] 						{lex_return(); return(CONST);}
[tT][Yy][Pp][Ee] 							{lex_return(); return(TYPE);}
[cC][hH][Aa][Rr] 							{lex_return(); return(CHAR);}
[Rr][Ee][Pp][Ee][Aa][Tt]				    {lex_return(); return(REPEAT);}
[Uu][Nn][Tt][Ii][Ll] 						{lex_return(); return(UNTIL);}
[Dd][Oo][Ww][Nn][Tt][Oo]      				{lex_return(); return(DOWNTO);}
[Cc][Aa][Ss][Ee]			 				{lex_return(); return(CASE);}
[Ww][Rr][Ii][Tt][Ee][Ll][Nn]				{lex_return(); return(WRITELN);}


"="					{lex_return();	return(RELOP);}
"<>"				{lex_return();	return(RELOP);}
"<"					{lex_return();	return(RELOP);}
">"					{lex_return();	return(RELOP);}
">="				{lex_return();	return(RELOP);}
"<="				{lex_return();	return(RELOP);}
"+"					{lex_return();	return(ADDOP);}
"-"					{lex_return();	return(MINUSOP);}
"*"					{lex_return();	return(MULOP);}
"/"					{lex_return();	return(MULOP);}
":="				{lex_return();	return(ASSIGNOP);}
","					{lex_return();	return(COMMA);}
";"					{lex_return();	return(SEMICOLON);}
":"					{lex_return();	return(COLON);}
"["					{lex_return();	return(LEFTCUBE);}
"]"					{lex_return();	return(RIGHTCUBE);}
"("					{lex_return();	return(LEFTCIRCLE);}
")"					{lex_return();	return(RIGHTCIRCLE);}
"."					{lex_return();	return(PROGRAMEND);}
or					{lex_return();	return(ADDOP);}
div					{lex_return();	return(MULOP);}
mod					{lex_return();	return(MULOP);}
and					{lex_return();	return(MULOP);}
[/']{letter}[/']	{lex_return();  return(LETTER);}
{id}				{id_num++;	lex_return();	return (ID);}
{digits}			{digit++;	lex_return();	return (INT);}	
{num}				{num_num++;	lex_return();	return (FLOAT);}	
{ws}				{col_no=col_no+yyleng;	}
{newline}			{row_no++;	col_no=1;}

 /*单行注释操作*/
"{"			{
				char c;
				c = yyinput();
				col_no++;
				while(c != '}')
				{
					if(c == '\n') {row_no++; col_no=1; wrong();break;}/*可能出现注释错误*/
					c = yyinput();
					col_no++;
				}
			}
			
 /*多行注释操作*/
"(*"		{
				printf("注释开始\n");
				char c;
				c = yyinput();
				col_no++;
				printf("%c",c);	
				while(1)
				{
					if(c=='*'){
						c = yyinput();
						printf("%c",c);
						if(c==')'){c = yyinput();printf("%c",c);break;}
					}
					else	{c = yyinput();
						printf("%c",c);
						if(c == '\n'){row_no++; col_no=1; }/*可以接受多行注释*/
					}
				}
				printf("\n注释结束啦！\n");
				row_no++;
			}
" "					{col_no=col_no+yyleng;}
"\r"				{col_no=col_no+yyleng;}
.                   {wrong();}

%%
/*错误信息输出*/
void wrong()
{
	cout << "line " << row_no << " column " << col_no << " error message: find illegal syntax!" << endl;
	return;
}

/*通过yytext将识别到的字符串送给yylval，其结构在variable.h中定义，默认为int*/
void lex_return()
{
	yylval.value = big2low(yytext);
	yylval.row_no = row_no;
	yylval.col_no = col_no;
	col_no=col_no+yyleng;
}

string big2low(string bigstr)
{
	string lowstr;
	for ( int i = 0; i < bigstr.length(); i ++)
	{
		if ( bigstr[i] >= 'A' && bigstr[i] <= 'Z')
			bigstr[i] = bigstr[i] + 32;
	}
	
	return bigstr;
}

int yywrap(void)
{
	return 1;
}
