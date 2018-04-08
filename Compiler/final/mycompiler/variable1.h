#ifndef VARIABLE1_H
#define VARIABLE1_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct array_elem
{
	int low_bound;
	int up_bound;
};

struct symbol
{
	string name; //符号名称
	string var_type; //变量类型
	string array_type;
	//string ret_type; //函数返回值类型
	struct symbol* parameters; //参数链表
	struct symbol* members; //成员链表（记录类型） 
	int dimension; //维数 
	int line_num; //引用行 
	vector<struct array_elem> bounds;
	int isVariable;//0：自定义type；1：变量id
	struct symbol* next_symbol;// 下一个符号 
};
//函数表 
struct function
{
	string name; //函数名
	string ret_type; //返回值类型
	int const_start;
	int type_start;
	int type_num;
	int const_num;
	struct symbol* symbol_list; //函数内部符号表 
	struct function* next_function;
};

struct const_node
{
	string name;
	string const_type;
	string value;
};

struct type_node
{
	string name;
	string type;
};

class token
{
	public:
		int row_no;
		int col_no;
		string type;
		string value;
		bool is_var;
		token()
		{
			type = "";
			value = "";
			is_var = false;
		}
};

#define YYSTYPE token

#endif
