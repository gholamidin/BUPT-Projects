%{	
	#include "variable1.h"

	const char* sFile="file.txt";												//打开要读取的文本文件
	ofstream output("output.txt");
	int yydebug = 1;
	extern "C"
	{
		extern int yylex(void);
		void yyerror (char *s);
	}
	
	vector<string> split(string &str,string pattern);							//切分函数
	void add_parameter(string parameters);										//添加函数参数节点函数
	void add_symbol(string symbols, string type);								//添加符号节点函数（变量）
	void add_func(string name, string type, struct function *currentNode);		//添加函数节点函数
	void add_const(string id, string replace, string replace_type);				//添加常量函数
	void add_typedef(string id, string type);									//添加自定义类型
	void redefine_type(string type);											//函数返回类型写回函数
	void check_type_error_output(string type1, string type2, int rownum1, int colnum1, int rownum2, int colnum2);//错误信息输出函数
	int assign_type_check( string left_type, string right_type );				//赋值语句类型检查
	int check_in_ids(string &id_list);											//记号表中重定义检查
	int check_repeat_definition(string &id_list);								//全局重定义检查
	int check_var_declaration(string &id_list,string &type);					
	int check_repeat_func(string id);											//函数名重定义检查
	int param_type_check ( string id, string params );							//函数调用参数检查
	string del_space(string str);												//去空格函数
	string find_func_type ( string id );										//获取函数返回类型
	string combine_type( string type1, string type2 );							//表达式类型合并函数
	string find_local_var_func_type( string id, string id_varparts );			//局部变量或函数类型查找函数
	string find_global_var_type( string id, string id_varparts );				//全局变量类型查找函数
	string definition_trans(string para, bool is_para);							//声明语句翻译函数
	string write_trans(string exp_value,string exp_type,int row_no,int col_no);	//write语句翻译函数
	string writeln_trans(string exp_value,string exp_type,int row_no,int col_no);//writeln语句翻译函数
	string read_trans(string exp_value,string exp_type,int row_no,int col_no);	//read语句翻译函数
	string get_const_type(string id);											//常量类型获取函数
	string get_const_value(string id);											//常量名字获取函数
	string get_typedef_type(string id);											//自定义类型获取函数
	string get_typedef_value(string id);										//自定义类型名获取函数
	
	struct function* func_head_node = NULL;										//函数表头节点
	struct function* func_cur_node = NULL;										//当前最新函数表节点
	struct symbol* sym_head_node = NULL;										//变量头节点
	struct symbol* sym_cur_node = NULL;											//当前最新变量节点
	struct symbol* param_cur_node = NULL;										//当前最新参数节点
	struct function* call_procedure_id_check( string id );						//函数调用时对函数名的检查
	string int2str( int int_temp );												//整型转字符串函数		
	string cur_case_type = "";													//case类型
	vector<string> errors;														//错误信息存储缓冲区
	vector<string> nums;														//case分支的常量值记录区
	vector<string> branches;													//case分支的语句记录区
	vector<const_node> const_table;												//常量表
	vector<type_node> type_table;												//自定义类型表
	string array_id = "";
	int in_record = 0;															//是否在一个记录内部
	int recover = 0;															//恢复变量类型
	int const_cur_pos = 0;														//当前最新常量在常量表中的位置
	int type_cur_pos = 0;														//当前最新类型在自定义类型表中的位置
	int dim = 0;
	int is_main = 1;
	int time_r = 1;
%}

%token PROGRAM 1
%token FUNCTION 2
%token PROCEDURE 3 
%token INTEGER 4
%token REAL 5
%token BOOLEAN 6
%token ARRAY 7
%token RECORD 8
%token VAR 9
%token BEGIN1 10
%token END 11
%token OF 12
%token IF 13
%token THEN 14
%token ELSE 15
%token WHILE 16
%token DO 17
%token NOT 18
%token TRUE 19
%token FALSE 20
%token READ 21
%token WRITE 22
%token COMMA 37
%token SEMICOLON 38
%token COLON 39
%token LEFTCUBE 40
%token RIGHTCUBE 41
%token LEFTCIRCLE 42
%token RIGHTCIRCLE 43
%token PROGRAMEND 45
%token FLOAT 46
%token INT 47
%token ID 48
%token RELOP 49
%token ADDOP 50
%token MULOP 51
%token ASSIGNOP 52
%token SYMBOL 53
%token FOR 54
%token TO 55
%token CONST 57
%token MINUSOP 58
%token TYPE 59
%token CHAR 60
%token REPEAT 61
%token UNTIL 62
%token DOWNTO 63
%token CASE 64
%token LETTER 65
%token WRITELN 66
%token READLN 67
	
%left RELOP
%left ADDOP
%left MULOP
%right SYMBOL

%nonassoc IFX
%nonassoc ELSE


%%

program 					: program_head program_body PROGRAMEND												//完成对整个程序的分析和翻译
							{
								for (int i = 0; i < errors.size(); i ++)										//显示程序中所有出现的错误
								{
									cout << errors[i] << endl;
								}
								cout << "\n" << "\n";
								$$.value = "#include<stdio.h> \n" + $2.value;
								output << $$.value << endl;
								cout << $$.value << endl;
							}
							| program_head program_body															//错误：程序结尾丢失.符号
							{
								string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no+1) + " ";
								string error = "error message: expected symbol of the end of the program!";
								errors.push_back(line + error);
								cout << "\n" << "\n";
								$$.value = "#include<stdio.h> \n" + $2.value;
								output << $$.value << endl;
								cout << $$.value << endl;
							}
							;

program_head				: PROGRAM ID LEFTCIRCLE identifier_list RIGHTCIRCLE SEMICOLON						//完成程序头的分析和翻译
							{
								$$.value = $2.value;
								add_func($2.value,"void",func_cur_node);
							}
							| PROGRAM ID LEFTCIRCLE identifier_list SEMICOLON									//错误：丢失）
							{
								string line = "line " + int2str($4.row_no) + " column " + int2str($4.col_no+1) + " ";
								string error = "error message: missing ) !";
								errors.push_back(line + error);
								$$.value = $2.value;
								add_func($2.value,"void",func_cur_node);
							}
							| PROGRAM ID identifier_list RIGHTCIRCLE SEMICOLON									//错误：丢失（
							{
								string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no+1) + " ";
								string error = "error message: missing ( !";
								errors.push_back(line + error);
								$$.value = $2.value;
								add_func($2.value,"void",func_cur_node);
							}
							| PROGRAM ID LEFTCIRCLE RIGHTCIRCLE SEMICOLON										//错误：丢失程序参数
							{
								string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
								string error = "error message: expected content in the circles!";
								errors.push_back(line + error);
								$$.value = $2.value;
								add_func($2.value,"void",func_cur_node);
							}
							| PROGRAM ID SEMICOLON																//错误：丢失程序参数
							{
								string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
								string error = "error message: expected content in the circles!";
								errors.push_back(line + error);
								$$.value = $2.value;
								add_func($2.value,"void",func_cur_node);
							}
							;

program_body				: const_declarations type_declarations var_declarations subprogram_declarations compound_statement	//完成对程序体的分析和翻译
							{
								if (is_main == 1)
								{
									$$.value = $1.value + $2.value + $3.value + $4.value + "\nint main()\n{\n\t" + $5.value + "\n\treturn 0;\n}";
								}
								else
								{
									$$.value = "\n{\n\t" + $1.value + $2.value + $3.value + $4.value + $5.value + "\n}";
								}
								
							}
							;

identifier_list				: identifier_list COMMA ID																				//记号列表，在定义参数等地方用到
							{
								$$.value = $1.value + ", " + $3.value;
							}
							| identifier_list error ID																				//错误：记号之间的分隔符不恰当
							{
								string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no+1) + " ";
								string error = "error message: comma error!";
								errors.push_back(line + error);
								$$.value = $1.value + ", " + $3.value;
							}
							| ID
							{
								$$.value = $1.value;
							}
							;

const_declarations			: CONST const_declaration SEMICOLON																		//常量声明
							{
								if ($2.value == "")
								{
									$$.value = "\n";
								}
								else
								{	
									$$.value = $2.value + ";\n";
								}	
							}
							| CONST const_declaration																				//错误：缺少常量声明最后的分号
							{
								string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no+1) + " ";
								string error = "error message: expected semicolon at the end of the declaration!";
								errors.push_back(line + error);
								if ($2.value == "")
								{
									$$.value = "\n";
								}
								else
								{	
									$$.value = $2.value + ";\n";
								}	
							}
							|																										//无常量声明
							{
								$$.value = "";	
							}
							;

const_declaration 			: const_declaration SEMICOLON ID RELOP const_variable													//常量声明，const_variable为常量值
							{
								if ($5.value == "not exist")																			//错误：常量值未找到或未定义
								{
									string line = "line " + int2str($5.row_no) + " column " + int2str($5.col_no) + " ";
									string error = "error message: const_variable has not been defined!";
									errors.push_back(line + error);
									$$.value = $1.value;
								}
								else
								{
									if (check_repeat_definition($3.value) == 0)														//重定义检查：对已定义的函数名、参数名、const、type和变量名进行查重，有重复则删除id，返回值为0表示有重复，返回值为1表示无重复
									{
										string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_const($3.value,$5.value,$5.type);														//查重后加入常量表
									}
									if ($3.value != "")
									{
										$$.value = $1.value + ";\nconst " + $5.type + " " + $3.value + " = " + $5.value;
									}
									else
									{
										$$.value = $1.value;
									}
								}	
							}
							| const_declaration SEMICOLON ID ASSIGNOP const_variable												//错误：等号误用成赋值号
							{
								string line = "line " + int2str($4.row_no) + " column " + int2str($4.col_no) + " ";
								string error = "error message: using assignop when defining const!";
								errors.push_back(line + error);
								
								if ($5.value == "not exist")																			//错误：常量值未找到或未定义
								{
									string line = "line " + int2str($5.row_no) + " column " + int2str($5.col_no) + " ";
									string error = "error message: const_variable has not been defined!";
									errors.push_back(line + error);																	//保存错误信息
									$$.value = $1.value;
								}
								else
								{
									if (check_repeat_definition($3.value) == 0)														//重定义检查：对已定义的函数名、参数名、const、type和变量名进行查重，有重复则删除id，返回值为0表示有重复，返回值为1表示无重复
									{
										string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_const($3.value,$5.value,$5.type);														//查重后加入常量表
									}
									if ($3.value != "")
									{
										$$.value = $1.value + ";\nconst " + $5.type + " " + $3.value + " = " + $5.value;
									}
									else
									{
										$$.value = $1.value;
									}
								}	
							}
							| ID RELOP const_variable																				//常量声明
							{
								func_cur_node->const_start = const_cur_pos;
								if ($3.value == "not exist")																			//错误：常量值未找到或未定义
								{
									string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
									string error = "error message: const_variable has not been defined!";
									errors.push_back(line + error);
									$$.value = "";
								}
								else
								{
									if (check_repeat_definition($1.value) == 0)														//重定义检查：对已定义的函数名、参数名、const、type和变量名进行查重，有重复则删除id，返回值为0表示有重复，返回值为1表示无重复
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_const($1.value,$3.value,$3.type);														//查重后加入常量表
									}
									if ($1.value != "")
									{
										$$.value = "const " + $3.type + " " + $1.value + " = " + $3.value;
									}
									else
									{
										$$.value = "";
									}
								}
							}
							| ID ASSIGNOP const_variable																			//错误：等号误用成赋值号
							{
								func_cur_node->const_start = const_cur_pos;
								
								string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
								string error = "error message: using assignop when defining const!";
								errors.push_back(line + error);
								
								if ($3.value == "not exist")
								{
									string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
									string error = "error message: const_variable has not been defined!";
									errors.push_back(line + error);
									$$.value = "";
								}
								else
								{
									if (check_repeat_definition($1.value) == 0)
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_const($1.value,$3.value,$3.type);
									}
									if ($1.value != "")
									{
										$$.value = "const " + $3.type + " " + $1.value + " = " + $3.value;
									}
									else
									{
										$$.value = "";
									}
								}
							}
							;

const_variable				: ADDOP ID																						//常量类型：+id型
							{
								$$.value = get_const_value($2.value);
								$$.type = get_const_type($2.value);
							}
							| MINUSOP ID																					//常量类型：-id型
							{
								$$.value = "-" + get_const_value($2.value);
								$$.type = get_const_type($2.value);
							}
							| ID																							//常量类型：id型
							{
								$$.value = get_const_value($1.value);
								$$.type = get_const_type($1.value);
							}
							| ADDOP FLOAT																					//常量类型：+浮点型
							{
								$$.value = $2.value;
								$$.type = "float";
							}
							| MINUSOP FLOAT																					//常量类型：-浮点型
							{
								$$.value = "-" + $2.value;
								$$.type = "float";
							}
							| FLOAT																							//常量类型：浮点型
							{
								$$.value = $1.value;
								$$.type = "float";
							}
							| ADDOP INT																						//常量类型：+整型
							{
								$$.value = $2.value;
								$$.type = "int";
							}
							| MINUSOP INT																					//常量类型：-整型
							{
								$$.value = "-" + $2.value;
								$$.type = "int";
							}
							| INT																							//常量类型：整型
							{
								$$.value = $1.value;
								$$.type = "int";							
							}
							| LETTER																						//常量类型：字符型
							{
								$$.value = $1.value;
								$$.type = "char";
							}
							;

type_declarations			: TYPE type_declaration SEMICOLON																//类型声明
							{
								if ($2.value == "")
								{
									$$.value = "\n";
								}
								else
								{	
									$$.value = $2.value + ";\n";
								}
							}
							| TYPE type_declaration																			//错误：丢失末位分号
							{
								string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no+1) + " ";
								string error = "error message: expected semicolon at the end of the declaration!";
								errors.push_back(line + error);
								if ($2.value == "")
								{
									$$.value = "\n";
								}
								else
								{	
									$$.value = $2.value + ";\n";
								}
							}
							|																								//无类型声明
							{
								$$.value = "";
							}
							;

type_declaration 			: type_declaration SEMICOLON ID RELOP type														//类型声明
							{
								if ($5.value == "not exist")																
								{
									string line = "line " + int2str($5.row_no) + " column " + int2str($5.col_no) + " ";
									string error = "error message: the type has not been defined!";
									errors.push_back(line + error);
									$$.value = $1.value;
								}
								else
								{
									if (check_repeat_definition($3.value) == 0)
									{
										string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_typedef($3.value,$5.type);														//查重后加入类型表
									}
						
									if ($3.value != "")
									{		
										$$.value = $1.value + ";\ntypedef " + $5.value + " " + $3.value;
									}
									else
									{
										$$.value = $1.value;
									}
								}				
							}
							| ID RELOP type																					//类型声明
							{
								func_cur_node->type_start = type_cur_pos;
								
								if ($3.value == "not exist")
								{
									string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
									string error = "error message: the type has not been defined!";
									errors.push_back(line + error);
									$$.value = "";
								}
								else
								{
									if (check_repeat_definition($1.value) == 0)
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_typedef($1.value,$3.value);														//查重后加入类型表
									}
								
									if ($1.value != "")
									{
										$$.value = "typedef " + $3.value + " " + $1.value;
									}
									else
									{
										$$.value = "";
									}
								}
							}
							;
							
R							: RECORD
							{
								in_record = 1;																				//在var_declaration处规约时识别在record内部
							}
							;
							
type 						: standard_type																					//类型种类：标准类型
							{
								$$.value = $1.value;
								$$.type = $1.type;
							}
							| R record_body END																				//记录类型
							{
								$$.value = "struct{" + $2.value + "}";
								$$.type = "struct";
								in_record = 0;
							}
							| ARRAY LEFTCUBE periods RIGHTCUBE OF standard_type												//数组类型
							{
								$$.value = "array" + $6.value + "[" + $3.value + "]";
								$$.type = "array" + $6.type;
							}
							| ID																							//已经声明的自定义类型
							{
								$$.type = get_typedef_type($1.value);
								$$.value = $$.type;
							}
							;
							
standard_type 				: INTEGER																						//基本类型
							{
								$$.value = "int";
								$$.type = "int";
							}
							| REAL																							//浮点类型	
							{
								$$.value = "float";
								$$.type = "float";
							}
							| BOOLEAN																						//布尔类型
							{
								$$.value = "bool";
								$$.type = "bool";
							}
							| CHAR																							//字符型
							{
								$$.value = "char";
								$$.type = "char";
							}
							;

record_body					: var_declaration																				//记录类型的内容部分
							{
								$$.value = $1.value;
							}
							|
							{
								$$.value = "";
							}
							;

periods						: periods COMMA period																			//数组类型多个维度
							{
								$$.value = $1.value + "," + $3.value;
							}
							| period 
							{
								$$.value = $1.value;
							}
							;

period 						: const_variable PROGRAMEND PROGRAMEND const_variable											//数组类型每个维度的上下界
							{
								if (atoi($1.value.c_str()) > atoi($4.value.c_str()))
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
									string error = "error message: low bound is greater than up bound!";
									errors.push_back(line + error);
								}
								$$.value = $1.value + "|" + $4.value;
							}
							| const_variable error const_variable															//上下界之间的分隔符使用非法
							{
								string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no-1) + " ";
								string error = "error message: error in the array!";
								errors.push_back(line + error);
								$$.value = $1.value + "|" + $3.value;
							}
							;

var_declarations			: VAR var_declaration SEMICOLON																	//变量声明
							{
								if ($2.value == "")
								{	
									$$.value = "\n";
								}
								else
								{
									$$.value = $2.value + ";\n";
								}
							}
							| VAR var_declaration																			//变量声明最后缺少分号
							{
								string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no+1) + " ";
								string error = "error message: expected semicolon at the end of the declaration!";
								errors.push_back(line + error);
								if ($2.value == "")
								{	
									$$.value = "\n";
								}
								else
								{
									$$.value = $2.value + ";\n";
								}
							}
							|																								//无变量声明
							{
								if (is_main == 1)
								{
									add_parameter("");
									func_head_node -> symbol_list -> next_symbol = NULL;
								}
								else
								{
									func_cur_node -> symbol_list -> next_symbol = NULL;
								}
								$$.value = "\n";
							}
							;

var_declaration 			: var_declaration SEMICOLON identifier_list COLON type
							{
								int repeat = 1;
								if (in_record == 1)
								{
									if (check_in_ids($3.value) == 0)
									{
										repeat = 0;
									}
									
									string former;
									int pos = $1.value.find(" ");
									former = $1.value.substr(pos+1);
									
									string new_list;
									vector<string> ids;
									if ($3.value != "")
									{
										new_list = del_space($3.value);
									}
									else 
									{
										new_list = "";
									}
									ids = split(new_list,",");
									for (int i = 0; i < ids.size(); i ++)
									{
										vector<string>::iterator it;
										if (former.find(ids[i]) != -1)
										{
											it = ids.begin() + i;
											ids.erase(it);
											repeat = 0;
										}
									}
									
									$3.value = "";
									for (int i = 0; i < ids.size(); i ++)
									{
										$3.value = $3.value + ids[i] + ", ";
									}
									$3.value = $3.value.substr(0,$3.value.length() - 2);
									if (repeat == 0)
									{
										string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									
								}
								else
								{
									if (check_in_ids($3.value) == 0 || check_repeat_definition($3.value) == 0)
									{
										string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}	 
									if ($3.value != "")
									{
										add_symbol($3.value, $5.value);
									}
								}
													
								if ($3.value == "")
								{
									if ($1.value == "")
									{
										$$.value = "";
									}
									else
									{
										$$.value = $1.value;
									}
								}
								else
								{
									if ($1.value == "")
									{
										$$.value = definition_trans($5.value + ":" + $3.value,false);
									}
									else
									{
										$$.value = $1.value + ";" + definition_trans($5.value + ":" + $3.value,false);
									}				
								}
							}
							| var_declaration SEMICOLON identifier_list
							{
								int repeat = 1;
								if (in_record == 1)
								{
									if (check_in_ids($3.value) == 0)
									{
										repeat = 0;
									}	
									
									string former;
									int pos = $1.value.find(" ");
									former = $1.value.substr(pos+1);
									
									string new_list;
									vector<string> ids;
									if ($3.value != "")
									{
										new_list = del_space($3.value);
									}
									else 
									{
										new_list = "";
									}
									ids = split(new_list,",");
									for (int i = 0; i < ids.size(); i ++)
									{
										vector<string>::iterator it;
										if (former.find(ids[i]) != -1)
										{
											it = ids.begin() + i;
											ids.erase(it);
											repeat = 0;
										}
									}
									
									$3.value = "";
									for (int i = 0; i < ids.size(); i ++)
									{
										$3.value = $3.value + ids[i] + ", ";
									}
									$3.value = $3.value.substr(0,$3.value.length() - 2);
									
									if (repeat == 0)
									{
										string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									
								}
								else
								{
									if (check_in_ids($3.value) == 0 || check_repeat_definition($3.value) == 0)
									{
										string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}		
									if ($3.value != "")
									{
										add_symbol($3.value, "int");
									}
								}
								
								if ($3.value == "")
								{
									if ($1.value == "")
									{
										$$.value = "";
									}
									else
									{
										$$.value = $1.value;
									}
								}
								else
								{
									if ($1.value == "")
									{
										$$.value = definition_trans("int:" + $3.value,false);
									}
									else
									{
										$$.value = $1.value + ";" + definition_trans("int:" + $3.value,false);
									}				
								}
								string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
								string error = "error message: variable type missing!";
								errors.push_back(line + error);
							}
							| identifier_list
							{
								string tmp = "int";
								if (is_main == 1)
								{
									if (func_cur_node == func_head_node && time_r == 1)
									{
										add_parameter("");
										time_r = 0;
									}	
									if (check_var_declaration($1.value,tmp) == 0)
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
								}
								else
								{
									if (check_var_declaration($1.value,tmp) == 0)
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
								}
								if ($1.value == "")
								{
									$$.value = "";
								}
								else
								{
									$$.value = definition_trans("int:" + $1.value,false);
								}
								
								string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
								string error = "error message: variable type missing!";
								errors.push_back(line + error);	
							}
							| identifier_list COLON type//not conflict with the parameters of the function
							{
								if (is_main == 1)
								{
									if ( func_cur_node == func_head_node && time_r == 1)
									{
										add_parameter("");
										time_r = 0;
									}
									if (check_var_declaration($1.value,$3.value) == 0)
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
								}
								else
								{
									if (check_var_declaration($1.value,$3.value) == 0)
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
								}
								if ($1.value == "")
								{
									$$.value = "";
								}
								else
								{
									$$.value = definition_trans($3.value + ":" + $1.value,false);
								}
							}
							;

subprogram_declarations		: subprogram_declarations subprogram_declaration SEMICOLON
							{
								$$.value = $1.value + "\n" + $2.value;
							}
							|
							{
								$$.value = "";
							}
							;

subprogram_declaration 		: subprogram_head const_declarations type_declarations var_declarations compound_statement
							{
								is_main = 1;
								$$.value = $1.value + "\n{\n\t" + $2.value + $3.value + $4.value + $5.value + "\n}\n";
							}
							;

subprogram_head 			: M formal_parameter COLON type SEMICOLON
							{
								redefine_type($4.value);
								$$.value = $4.value + " " + $1.value + $2.value;				
							}
							| M COLON type SEMICOLON
							{
								add_parameter("");
								$$.value = $3.value + " " +$1.value;
							}
							| M formal_parameter SEMICOLON
							{
								redefine_type("int");
								$$.value = "int " + $1.value + $2.value;
								string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
								string error = "error message: function must have a return type!";
								errors.push_back(line + error);
							}
							| N formal_parameter SEMICOLON
							{
								redefine_type("void");
								$$.value = "void " + $1.value + $2.value;
							}
							| N SEMICOLON
						    {
								add_parameter("");
								$$.value = "void " + $1.value;
							}
							| N formal_parameter COLON type SEMICOLON
							{
								redefine_type("void");
								$$.value = "void " + $1.value + $2.value;
								string line = "line " + int2str($4.row_no) + " column " + int2str($4.col_no) + " ";
								string error = "error message: a procedure doesn't have a return type!";
								errors.push_back(line + error);
							}
							;
							
M							: FUNCTION ID
							{
								if (check_repeat_func($2.value) == 0)
								{
									string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
									string error = "error message: the name of the function has been defined before!";
									errors.push_back(line + error);
								}
								add_func($2.value,"integer",func_cur_node);
								$$.value = $2.value;
								is_main = 0;
							}
							;
							
N							: PROCEDURE ID
							{
								if (check_repeat_func($2.value) == 0)
								{
									string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
									string error = "error message: the name of the procedure has been defined before!";
									errors.push_back(line + error);
								}
								add_func($2.value,"integer",func_cur_node);
								$$.value = $2.value;
								is_main = 0;
							}
							;
							
formal_parameter			: LEFTCIRCLE parameter_lists RIGHTCIRCLE
							{
								$$.value = "(" + $2.value + ")";
							}
							| LEFTCIRCLE parameter_lists SEMICOLON RIGHTCIRCLE
							{
								string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
								string error = "error message: unexpected semicolon!";
								errors.push_back(line + error);
								$$.value = "(" + $2.value + ")";
							}
							|
							{
								$$.value = "";
							}
							;

parameter_lists 			: parameter_lists SEMICOLON parameter_list
							{
								if ($3.value != "")
								{
									string parm = $3.value;
									if ( parm.find("var+") == 0 )
									{
										parm = parm.substr(4);
									}
									add_parameter(parm);
									$$.value = $1.value + ", " + definition_trans($3.value,true);
								}
								else
								{
									$$.value = $1.value;
								}
							}
							| parameter_lists error parameter_list
							{
								$$.value = $1.value + ";" + $3.value;
								string parm = $3.value;
								if ( parm.find("var+") == 0 )
								{
									parm = parm.substr(4);
								}
								add_parameter(parm);
								string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
								string error = "error message: semicolon missing, wrong separate symbol!";
								errors.push_back(line + error);			
							}
							| parameter_list
							{
								if ($1.value != "")
								{
									string parm = $1.value;
									if ( parm.find("var+") == 0 )
									{
										parm = parm.substr(4);
									}
									add_parameter(parm);
									$$.value = definition_trans($1.value,true);
								}		
							}
							;

parameter_list 				: var_parameter
							{
								$$.value = $1.value;
								$$.is_var = true;
							}
							| value_parameter
							{
								$$.value = $1.value;
							}
							;

var_parameter				: VAR value_parameter
							{
								$$.value = "var+" + $2.value;
							}
							;

value_parameter				: identifier_list COLON type
							{
								if (check_in_ids($1.value) == 0 || check_repeat_definition($1.value) == 0)
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
									string error = "error message: redefine the variable in parameters!";
									errors.push_back(line + error);
								}
								
								if ($1.value == "")
								{
									$$.value = "";
								}
								else
								{
									$$.value = $3.value + ":" + $1.value;
								}
							}
							| identifier_list
							{	
								string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
								string error = "error message: type missing!";
								errors.push_back(line + error);
								if (check_in_ids($1.value) == 0 || check_repeat_definition($1.value) == 0)
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
									string error = "error message: redefine the variable in parameters!";
									errors.push_back(line + error);
								}
								
								if ($1.value == "")
								{
									$$.value = "";
								}
								else
								{
									$$.value = "int:" + $1.value;
								}
							}
							;
							
compound_statement			: BEGIN1 statement_list END
							{
								$$.value = $2.value + "\n";
							}
							| BEGIN1 statement_list SEMICOLON END
							{
								string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
								string error = "error message: unexpected semicolon!";
								errors.push_back(line + error);
								$$.value = $2.value + "\n";
							}
							;
							
statement_list				: statement_list SEMICOLON statement
							{
								$$.value = $1.value + "\n\t" + $3.value;
							}
							| statement_list statement
							{
								$$.value = $1.value + "\n\t" + $2.value;
								string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
								string error = "error message: semicolon missing, wrong separate symbol!";
								errors.push_back(line + error);
							}
							| statement
							{
								$$.value = $1.value;
							}
							;

statement 					: variable ASSIGNOP expression
							{
								if ($1.value == "return")
								{
									$$.value = "return " + $3.value;
								}
								if ( $1.value != "return" )
								{
									$$.value = $1.value + "=" + $3.value + ";";
								}
								check_type_error_output($1.type,$3.type,$1.row_no,$1.col_no,$3.row_no,$3.col_no);
							}
							| variable RELOP expression
							{
								if ($1.value == "return")
								{
									$$.value = "return " + $3.value;
								}
								if ( $1.value != "return" )
								{
									$$.value = $1.value + "=" + $3.value + ";";
								}
								check_type_error_output($1.type, $3.type, $1.row_no, $1.col_no, $3.row_no, $3.col_no);
								string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
								string error =  "error message: assignrelop is wrong!";
								errors.push_back(line + error);
							}
							| variable error ASSIGNOP expression
							{
								if ($1.value == "return")
								{
									$$.value = "return " + $3.value;
								}
								else
								{
									$$.value = $1.value + "=" + $3.value + ";";
								}
								check_type_error_output($1.type, $3.type, $1.row_no, $1.col_no, $3.row_no, $3.col_no);
								string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
								string error =  "error message: too many symbols before '=' !";
								errors.push_back(line + error);
							}
							| call_procedure_statement
							{
								$$.value = $1.value + ";";
							}
							| compound_statement
							{
								$$.value = $1.value;
							}
							| IF expression THEN statement else_part
							{
								$$.value = "if(" + $2.value + ")" + "\n\t{\n\t\t" + $4.value  + "\n\t}\n" + $5.value;
								if (!($2.type == "bool" || $2.type == "constbool"))
								{
									string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
									string error = "error message: the if expression is not bool!";
									errors.push_back(line + error);
								}
							}
							| S case_body END
							{
								$$.value = "switch(" + $1.value + "){\n" + $2.value + "}\n";
							}
							| S case_body
							{
								string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no+1) + " ";
								string error = "error message: end is missing here!";
								errors.push_back(line + error);
								$$.value = "switch(" + $1.value + "){\n" + $2.value + "}\n";
							}
							| WHILE expression DO statement
							{
								if (!($2.type == "bool" || $2.type == "constbool"))
								{
									string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
									string error = "error message: the while expression is not bool!";
									errors.push_back(line + error);
								}
								$$.value = $1.value + "(" + $2.value + ")\n\t{\n\t\t" + $4.value + "\n\t}\n";
							}
							| WHILE expression statement
							{
								string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
								string error =  "error message: must have a do in the while statement!";
								errors.push_back(line + error);
								if (!($2.type == "bool" || $2.type == "constbool"))
								{
									string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
									string error = "error message: the while expression is not bool!";
									errors.push_back(line + error);
								}
								$$.value = $1.value + "(" + $2.value + ")\n\t{\n\t\t" + $3.value + "\n\t}\n";
							}
							| REPEAT statement_list UNTIL expression
							{
								$$.value = "do{\n" + $2.value + "}while(" + $4.value + ")\n";
							}
							| T ASSIGNOP expression updown expression DO statement
							{
								check_type_error_output($2.type, $4.type, $2.row_no, $2.col_no, $4.row_no, $4.col_no);
								check_type_error_output($2.type, $6.type, $2.row_no, $2.col_no, $6.row_no, $6.col_no);
								if($4.value == "to")
								{
									$$.value = "for(" + $1.value + "=" + $3.value + ";" + $1.value + "<=" + $5.value + ";" + $1.value + "++){\n" + $6.value + "}\n";
								}
                              	else
								{
									$$.value = "for(" + $1.value + "=" + $3.value + ";" + $1.value + ">=" + $5.value + ";" + $1.value + "--){\n" + $6.value + "}\n";
                                }
							}
							| T ASSIGNOP expression updown expression statement
							{
								check_type_error_output($1.type, $3.type, $1.row_no, $1.col_no, $3.row_no, $3.col_no);
								check_type_error_output($1.type, $5.type, $1.row_no, $1.col_no, $5.row_no, $5.col_no);
								string line = "line " + int2str($5.row_no) + " column " + int2str($5.col_no+1) + " ";
								string error =  "error message: must have do in the for statement!";
								errors.push_back(line + error);
								if($4.value == "to")
								{
									$$.value = "for(" + $1.value + "=" + $3.value + ";" + $1.value + "<=" + $5.value + ";" + $1.value + "++){\n" + $6.value + "}\n";
								}
                              	else
								{
									$$.value = "for(" + $1.value + "=" + $3.value + ";" + $1.value + ">=" + $5.value + ";" + $1.value + "--){\n" + $6.value + "}\n";
                                }
							}
							|
							{
								$$.value = "";
							}
							| write
							{
								$$.value = $1.value;
							}
							| read
							{
								$$.value = $1.value;
							}
							;
		
T							: FOR ID
							{
								$$.value = $2.value;
								$$.type = find_local_var_func_type($2.value,"");
							}
							;
							
write						: WRITE LEFTCIRCLE expression_list RIGHTCIRCLE
							{
								$$.value = write_trans($3.value,$3.type,$3.row_no,$3.col_no);
								dim = 0;
							}
							| WRITELN LEFTCIRCLE expression_list RIGHTCIRCLE
							{
								$$.value = writeln_trans($3.value,$3.type,$3.row_no,$3.col_no);
								dim = 0;
							}
							| WRITELN
							{
								$$.value = "printf(\"\\n\")";
							}
							;


read						: READ LEFTCIRCLE variable_list RIGHTCIRCLE
							{
								$$.value = read_trans($3.value,$3.type,$3.row_no,$3.col_no);					
							}
							
							
S							: CASE expression OF
							{
								$$.type = $2.type;
								cur_case_type = $2.type;
								$$.value = $2.value;
							}
							;
							
expression 					: simple_expression RELOP simple_expression
							{
								if ( $1.type == "float" && $3.type == "float" || $1.type == "float" && $3.type == "int" || $1.type == "int" && 
								     $3.type == "int" || $1.type == "float" && $3.type == "int" || $1.type == "char" && $3.type == "char")
								{	
									$$.type = "bool";
								}
								else if ($1.type == "bool" && $3.type == "bool")
								{
									if ($2.value == "=")
									{
										$$.type = "bool";
									}
									else
									{
										string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
										string error =  "error message: invalid relop between bools!";
										errors.push_back(line + error);
										$$.type = "NULL";
									}
								}
								else
								{
									string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
									string error =  "error message: invalid relop between expressions!";
									errors.push_back(line + error);
									$$.type = "NULL";
								}
								$$.value = $1.value + $2.value + $3.value;
							}
							| simple_expression
							{
								$$.value = $1.value;
								$$.type = $1.type;
							}
							;

simple_expression			: term
							{
								$$.value = $1.value;
								$$.type = $1.type;
							}
							| ADDOP term
							{
								if ( $2.type == "int" || $2.type == "float" )
									$$.type = $2.type;
								else
									$$.type = "NULL";
								$$.value = $1.value + $2.value;
							}
							| MINUSOP term
							{
								if ( $2.type == "int" || $2.type == "float" )
									$$.type = $2.type;
								else
									$$.type = "NULL";
								$$.value = $1.value + $2.value;
							}
							| simple_expression ADDOP term
							{
								if ( $2.value == "or" )
								{
									$2.value = "||";
								}
								$$.value = $1.value + $2.value + $3.value;
								$$.type = combine_type($1.type, $3.type);
							}
							| simple_expression MINUSOP term
							{
								$$.value = $1.value + $2.value + $3.value;
								$$.type = combine_type($1.type, $3.type);
							}
							;

term						: term MULOP factor
							{
								if (($2.value == "/" || $2.value == "div" || $2.value == "mod")&& $3.value == "0")
								{									
									string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
									string error = "error message: the divisor can not be 0";
									errors.push_back(line + error);
								}
								if ( $2.value == "and" )
								{
									if ( !($1.type == "bool" || $1.type == "constbool") && ( $3.type == "bool" || $3.type == "constbool") )
									{
										string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
										string error = "error message: type is not bool on either side of and operator";
										errors.push_back(line + error);
									}
								}
								if ( $2.value == "mod" )
									$2.value = "%";
								if ( $2.value == "and" )
									$2.value = "&&";
								if ( $2.value == "div" )
									$2.value = "/";
								$$.value = $1.value + $2.value + $3.value;  
								$$.type = combine_type($1.type, $3.type);
							}							
							| factor
							{
								$$.value = $1.value;
								$$.type = $1.type;
							}
							;

factor   					: ID LEFTCIRCLE expression_list RIGHTCIRCLE
							{
								$$.value = $1.value + "(" + $3.value + ")";
								if ( param_type_check($1.value, $3.type) != 0 )
								{
									$$.type = find_func_type($1.value);
									if ( $$.type == "NULL" )
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								else
								{
									string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
									string error =  "error message: check your parameter numbers or types!";
									errors.push_back(line + error);
									$$.type = find_func_type($1.value);
									if ( $$.type == "NULL" )
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								dim = 0;
							}
							| ID LEFTCIRCLE RIGHTCIRCLE
							{
								$$.value = $1.value + "()";
								$$.type = find_func_type($1.value);
								if (call_procedure_id_check($1.value)->symbol_list->parameters == NULL)
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no+1) + " ";
									string error = "error message: unexpected circles!";
									errors.push_back(line + error);
								}
								else
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no+1) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
								}
								
								dim = 0;
							}
							| LEFTCIRCLE expression RIGHTCIRCLE
							{
								$$.value = "(" + $2.value + ")";
								$$.type = $2.type;
							}
							| NOT factor
							{
								if ( $2.type == "bool" )
								{
									$$.value = "!" + $2.value;
									$$.type = "bool";
								}
								else
								{
									string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
									string error = "error message: factor not bool type";
									errors.push_back(line + error);
									$$.value = "!" + $2.value;
									$$.type = "NULL";
								}
							}
							| unsigned_const_variable
							{
								$$.value = $1.value;
								$$.type = $1.type;
							}
							| variable
							{
								$$.type = $1.type;
								$$.value = $1.value;
							}
							;

unsigned_const_variable 	: FLOAT
							{
								$$.value = $1.value;
								$$.type = "float";
							}
							| INT
							{
								$$.value = $1.value;
								$$.type = "int";
							}
							| LETTER
							{
								$$.value = $1.value;
								$$.type = "char";
							}								
							;

variable 					: IDM id_varparts
							{
								string name = $1.value;
								if ( name.find("return") == 0 )
								{
									name = name.substr(6);
									$1.value = $1.value.substr(0, 6);
								}
								string result = "";
								if ( recover == 1 )
									$$.type = find_local_var_func_type(name, "array"+$2.value);
								if ( recover == 2 )
									$$.type = find_local_var_func_type(name, "struct"+$2.value);
								if ( recover == 0 )
									$$.type = find_local_var_func_type(name, $2.value);
								recover = 0;	
								if ( $2.value != "" )
								{
									if ( $2.value.find("[") != -1 )
									{
										$2.value = $2.value.substr(1);
										$2.value = $2.value.substr(0,$2.value.length() - 1);
										vector<string> cons = split($2.value,",");

										for (int i = 0; i < cons.size(); i ++)
										{
											result = result + "[" + cons[i] + "]";
										}
									}
									else if ( $2.value.find(".") != -1)
									{
										 result = $2.value;
									}
								}
								$$.value = $1.value + result;
							}
							;
			
IDM							: ID
							{
								if (func_cur_node->name == $1.value)
								{
									$$.value = "return" + $1.value;
								}
								else
								{
									$$.value = $1.value;
								}
								array_id = $1.value;
							}
							;
id_varparts					: id_varparts id_varpart
							{
								if ($2.value.find("array") == 0)
								{
									$2.value = $2.value.substr(5);
									recover = 1;
								}
								
								if ($2.value.find("struct") == 0)
								{
									$2.value = "." + $2.value.substr(6);
									recover = 2;
								}
								$$.value = $1.value + $2.value;		
							}
							| 
							{
								$$.value = "";
							}
							;

id_varpart					: LEFTCUBE expression_list RIGHTCUBE
							{
								int valid = 1;
								string type = find_local_var_func_type(array_id, "");
								vector<string> newnums;
								if ( type.find("array") == 0 )
								{
									int pos = type.find("[");
									type = type.substr(pos+1);
									type = type.erase(type.length()-1, 1);
									vector<string> dimns = split(type, ",");
									vector<string> nums = split($2.value, ",");
									
									if ( nums.size() == dimns.size() )
									{
										for ( int i = 0; i < dimns.size() && i < nums.size(); i++ )
										{
											vector<string> bounds = split(dimns[i],"|");
											int low = atoi(bounds[0].data());
											int up = atoi(bounds[1].data());
											int num = atoi(nums[i].data());
											if ( num < low || num > up )
											{
												string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
												string error =  "error message: out of bounds in the array!";
												errors.push_back(line + error);
											}
											newnums.push_back(int2str(num-low));
										}
									}
									if ( dim != dimns.size() ) valid = 0;
									if ( valid == 0 )
									{
										string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
										string error =  "error message: dimension errors in the array!";
										errors.push_back(line + error);
										for (int i = 0; i < nums.size(); i ++)
										{
											newnums.push_back(nums[i]);
										}
									}
								}
								string new_exp = "";
								for (int i = 0; i < newnums.size(); i ++)
								{
									new_exp = new_exp + newnums[i] + ",";
								}
								new_exp = new_exp.substr(0,new_exp.size() - 1);
								$$.value = "array[" + new_exp + "]";
								dim = 0;
							}
							| PROGRAMEND ID
							{
								$$.value = "struct" + $2.value;
							}
							;

variable_list				: variable_list COMMA variable
							{
								$$.value = $1.value + "," + $3.value;
								$$.type = $1.type + "*" + $3.type;
							}
							| variable
							{
								$$.value = $1.value;
								$$.type = $1.type;
							}
							;
							
else_part					: ELSE statement
							{
								$$.value = "\telse\n\t{\n\t\t" + $2.value + "\n\t}\n";
							}
							| 
							{
								$$.value = "";
							}
							;

case_body 					: branch_list
							{
								$$.value = $1.value;
								branches.clear();
							}
							|
							{
								$$.value = "";
							}
							;

branch_list					: branch_list SEMICOLON branch 
							{
								$$.value = $1.value + $3.value;
							}
							| branch
							{
								$$.value = $1.value;
							}
							;

branch 						: const_list COLON statement
							{
								vector<string> cases;
								int error1 = 0;
								$$.value = "";
								cases = split($1.value,",");
								for ( int i = 0; i < cases.size(); i++ )
								{
									if( nums.size() == 0 && branches.size() == 0 )
									{
										nums.push_back(cases[i]);
										branches.push_back($3.value);
										$$.value = $$.value + "case " + cases[i] + ":" + $3.value + "break;\n";
									}
									else
									{
										for ( int j = 0; j < nums.size(); j++ )
										{
											if ( nums[j] == cases[i] )
											{
												string line = "line " + int2str($1.row_no) + " column " + int2str($3.col_no) + " ";
												string error =  "error message: branches conflict!";
												errors.push_back(line + error);
												error1 = 1;
											}
										}
										if ( error1 == 0 )
										{
											nums.push_back(cases[i]);
											branches.push_back($3.value);
											$$.value = $$.value + "case " + cases[i] + ":" + $3.value + "break;\n";
										}
									}
									error1 = 0;
								}
							}
							;

const_list 					: const_list COMMA const_variable
							{
								int error = 0;
								if ( $3.type != cur_case_type )
								{
									string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
									string error =  "error message: const type not matched with case type!";
									errors.push_back(line + error);
								}
								$$.value = $1.value + "," + $3.value;
							}
							| const_variable
							{
								int error = 0;
								if ( $1.type != cur_case_type )
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
									string error =  "error message: const type not matched with case type!";
									errors.push_back(line + error);
								}
								$$.value = $1.value;
							}
							;

updown 						: TO
							{
								$$.value = $1.value;
							}
							| DOWNTO
							{
								$$.value = $1.value;
							}
							;

call_procedure_statement	: ID
							{
								if ( call_procedure_id_check($1.value) != NULL )
								{
									$$.type = find_func_type($1.value);
									if ( $$.type != "void")
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error =  "error message: can not call a function directly in a statement!";
										errors.push_back(line + error);
									}
								}
								else
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
									string error =  "error message: the function is not found!";
									errors.push_back(line + error);
									$$.type = "NULL";
								}
								$$.value = $1.value + "()";
							}
							| ID LEFTCIRCLE expression_list RIGHTCIRCLE
							{
								$$.value = $1.value + "(" + $3.value + ")";
								if ( param_type_check($1.value, $3.type) == 1 )
								{
									$$.type = find_func_type($1.value);
									if ( $$.type == "NULL" )
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								else if ( param_type_check($1.value, $3.type) == -1 ) 
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
									string error =  "error message: the function does not found!";
									errors.push_back(line + error);
									$$.type = "NULL";
								}
								else
								{
									string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
									$$.type = "NULL";
								}
								dim = 0;
							}
							| ID expression_list RIGHTCIRCLE
							{
								$$.value = $1.value + "(" + $2.value + ")";
								if ( param_type_check($1.value, $3.type) == 1 )
								{
									$$.type = find_func_type($1.value);
									if ( $$.type == "NULL" )
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								else if ( param_type_check($1.value, $3.type) == -1 ) 
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
									string error = "error message: the function does not found!";
									errors.push_back(line + error);
									$$.type = "NULL";
								}
								else
								{
									string line = "line " + int2str($2.row_no) + " column " + int2str($2.col_no) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
									$$.type = "NULL";
								}
								string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no+1) + " ";
								string error = "error message: leftcircle is missing!";
								errors.push_back(line + error);
								dim = 0;
							}
							| ID LEFTCIRCLE expression_list
							{
								$$.value = $1.value + "(" + $3.value + ")";
								if ( param_type_check($1.value, $3.type) == 1 )
								{
									$$.type = find_func_type($1.value);
									if ( $$.type == "NULL" )
									{
										string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								else if ( param_type_check($1.value, $3.type) == -1 ) 
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no) + " ";
									string error = "error message: the function does not found!";
									errors.push_back(line + error);
									$$.type = "NULL";
								}
								else
								{
									string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
									$$.type = "NULL";
								}
								string line = "line " + int2str($3.row_no) + " column " + int2str($3.col_no+1) + " ";
								string error = "error message: rightcircle is missing!";
								errors.push_back(line + error);
								dim = 0;
							}
							| ID LEFTCIRCLE RIGHTCIRCLE
							{
								$$.value = $1.value + "()";
								if (call_procedure_id_check($1.value)->symbol_list->parameters == NULL)
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no+1) + " ";
									string error = "error message: unexpected circles!";
									errors.push_back(line + error);
								}
								else
								{
									string line = "line " + int2str($1.row_no) + " column " + int2str($1.col_no+1) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
								}
								
								dim = 0;
							}
							;


expression_list				: expression_list COMMA expression
							{
								$$.value = $1.value + "," + $3.value;
								$$.type = $1.type + "*" + $3.type;
								dim ++;
							} 
							| expression
							{
								$$.value = $1.value;
								$$.type = $1.type;
								dim++;
							}
							;


%%
//赋值语句类型检查结果反馈
void check_type_error_output(string type1, string type2, int rownum1, int colnum1, int rownum2, int colnum2)
{
	string line;
	string error;
	if (assign_type_check(type1,type2) == 0)													//错误：赋值语句左边为常量
	{
		line = "line " + int2str(rownum1) + " column " + int2str(colnum1) + " ";
		error = "error message: the const variable can't be assigned!";
		errors.push_back(line + error); 
	}
	if (assign_type_check(type1,type2) == -1)													//错误：左部变量未定义或表达式类型无效
	{
		line = "line " + int2str(rownum1) + " column " + int2str(colnum1) + " ";
		error = "error message: the variable has not been defined!";
		errors.push_back(line + error);
	}
	else if (assign_type_check(type1,type2) == -2)												//错误：右部变量未定义或表达式类型无效					
	{
		line = "line " + int2str(rownum2) + " column " + int2str(colnum2) + " ";
		error = "error message: the variable has not been defined!";
		errors.push_back(line + error);
	}
	else if (assign_type_check(type1,type2) == -3)												//错误：两侧符号均未定义或表达式类型无效
	{
		line = "line " + int2str(rownum1) + " column " + int2str(colnum1) + " ";
		error = "error message: the variable has not been defined!";
		errors.push_back(line + error);
		line = "line " + int2str(colnum2) + " column " + int2str(colnum2) + " ";
		error = "error message: the variable has not been defined!";
		errors.push_back(line + error);
	}
	else if (assign_type_check(type1,type2) == -4)												//错误：左右表达式类型有效但不匹配
	{
		line = "line " + int2str(rownum2) + " column " + int2str(colnum2) + " ";
		error = "error message: type unmatched in the assignment!";
		error = error + "\nleft_type is " + type1 + " right_type is " + type2;
		errors.push_back(line + error);
	}
}
//write语句的翻译
string write_trans(string exp_value,string exp_type,int row_no,int col_no)
{
	vector<string> exp = split(exp_type, "*");
	vector<string> exp_list = split(exp_value, ",");
	vector<string>::iterator it;
	string str = "\"";

	for (int i = 0; i < exp.size(); i ++)
	{
		if (exp[i] != "NULL")
		{
			if (exp[i] == "int" || exp[i] == "constint")								//整型变量
			{
				str += "%d";
			}
			else if (exp[i] == "char" || exp[i] == "constchar")							//字符型
			{
				str += "%c";
			}
			else if (exp[i] == "float" || exp[i] == "constfloat")						//浮点型
			{
				str += "%f";
			}
			else if (exp[i] == "bool" || exp[i] == "constbool")							//布尔型变量
			{
				it = exp_list.begin() + i;
				exp_list.erase(it);
			}
		}
		else
		{
			it = exp_list.begin() + i;
			exp_list.erase(it);
		}
	}
	
	str += "\"";
	
	for (int i = 0; i < exp_list.size(); i ++)
	{
		str = str + "," + exp_list[i];
	}
	
	return "printf(" + str + ");";
}
//writeln语句的翻译
string writeln_trans(string exp_value,string exp_type,int row_no,int col_no)
{
	vector<string> exp = split(exp_type, "*");
	vector<string> exp_list = split(exp_value, ",");
	vector<string>::iterator it;
	string str = "\"";

	for (int i = 0; i < exp.size(); i ++)
	{
		if (exp[i] != "NULL")
		{
			if (exp[i] == "int" || exp[i] == "constint")
			{
				str += "%d";
			}
			else if (exp[i] == "char" || exp[i] == "constchar")
			{
				str += "%c";
			}
			else if (exp[i] == "float" || exp[i] == "constfloat")
			{
				str += "%f";
			}
			else if (exp[i] == "bool" || exp[i] == "constbool")
			{
				it = exp_list.begin() + i;
				exp_list.erase(it);
			}
		}
		else
		{
			it = exp_list.begin() + i;
			exp_list.erase(it);
		}
	}
	
	str += "\\n\"";
	
	for (int i = 0; i < exp_list.size(); i ++)
	{
		str = str + "," + exp_list[i];
	}
	
	return "printf(" + str + ");";
}
//read语句翻译
string read_trans(string exp_value,string exp_type,int row_no,int col_no)
{
	vector<string> exp = split(exp_type, "*");
	vector<string> exp_list = split(exp_value, ",");
	vector<string>::iterator it;
	string str = "\"";

	for (int i = 0; i < exp.size(); i ++)
	{
		if (exp[i] != "NULL")
		{
			if (exp[i] == "int")
			{
				str += "%d";
			}
			else if (exp[i] == "char")
			{
				str += "%c";
			}
			else if (exp[i] == "float")
			{
				str += "%f";
			}
			else
			{
				it = exp_list.begin() + i;
				exp_list.erase(it);
			}
		}
		else
		{
			it = exp_list.begin() + i;
			exp_list.erase(it);
		}
	}
	
	str += "\"";
	
	for (int i = 0; i < exp_list.size(); i ++)
	{
		str = str + ",&" + exp_list[i];
	}
	
	return "scanf(" + str + ");";
}
//发生无法恢复的错误时（没有产生式可以规约），调用yyerror函数报错
void yyerror(char *s) //当yacc遇到语法错误时，会回调yyerror函数，并且把错误信息放在参数s中  
{  
    cerr << s << endl;//直接输出错误信息  
} 
//向函数表中加入一个节点表示当前处理的（子）函数
void add_func(string name, string type, struct function *currentNode)
{
	struct function *funcNode;
	if (currentNode == NULL)																//主函数作为头结点
	{
		currentNode = new struct function;
		currentNode->next_function = NULL;
		func_head_node = currentNode;
	}
	else
	{
		funcNode = new struct function;
		currentNode->next_function = funcNode;
		currentNode = funcNode;
	}

	currentNode->name = name;
	currentNode->ret_type = type;
	currentNode->type_num = 0;
	currentNode->const_num = 0;
	currentNode->type_start = -1;
	currentNode->const_start = -1;
	currentNode->symbol_list = NULL;
	currentNode -> next_function = NULL;
	func_cur_node = currentNode;
}
//切分函数
vector<string> split(string &str,string pattern)
{
	int pos;
	vector<string> result;
	if (str == "")
	{
		return result;
	}
	str += pattern;
	int size = str.size();
	for (int i = 0; i < size; i ++)
	{
		pos = str.find(pattern,i);
		if (pos < size)
		{
			string tmp = str.substr(i,pos-i);
			result.push_back(tmp);
			i = pos + pattern.size() - 1;
		}
	}
	str = str.substr(0,size - pattern.length());
	return result;
}
//去空格函数
string del_space(string str)
{
	string result = "";
	for (int i = 0; i < str.size(); i ++)
	{
		if (str[i] != ' ')
		{
			result += str[i];
		}
	}
	return result;
}
//函数返回值回写函数，先创建函数表节点，参数确定后再回填其返回类型
void redefine_type( string type )
{
	func_cur_node -> ret_type = type;
}
//函数调用有效性检查函数
struct function* call_procedure_id_check( string id )
{
	struct function* func_node = func_head_node;
	if (is_main == 1)
	{
		while( func_node != NULL )
		{
			if ( func_node -> name == id )
			{
				return func_node;
			}
			func_node = func_node -> next_function;
		}
		return NULL;
	}
	else
	{
		while( func_node != NULL )
		{
			if ( func_node -> name == id && func_node != func_cur_node || func_node == func_cur_node )
			{
				return func_node;
			}
			func_node = func_node -> next_function;
		}
		return NULL;
	}
	
}

//调用函数时的参数检查，0：参数不匹配；1：参数匹配；-1：函数未找到
int param_type_check ( string id, string params )
//
{
	struct function* func_node;
	vector<string> param_type = split(params, "*");
	int i = 0;
	func_node = call_procedure_id_check(id);
	string type;
	if ( func_node == NULL )
	{
		return -1;
	}
	else if ( func_node != NULL )
	{
		struct symbol* prms = func_node -> symbol_list -> parameters;
		if ( prms != NULL )
		{
			while ( prms-> name != "" && params != "" && i < param_type.size() )
			{
				if ( prms -> var_type == "struct" )
				{
					type = "";
					type = type + "struct" + "{";
					struct symbol*  members = prms -> members;
					while(members != NULL )
					{
						type += members -> name + ":" + members->var_type;
						if ( members -> next_symbol != NULL )
						{
							type += ";";
						}
						members = members -> next_symbol;
					}
					type += "}";
				}
				if ( prms -> var_type == "array" )
				{
					type = "";
					type = type + "array" + prms->array_type + "[";
					vector<struct array_elem> members(prms -> bounds);
					for ( int i = 0; i < members.size(); i++ )
					{
						string low_bound;
						string up_bound;
						low_bound = int2str(members[i].low_bound);
						up_bound = int2str(members[i].up_bound);
						type += low_bound + "|" + up_bound;
						if ( i != members.size() - 1 )
							type += ",";
					}
					type += "]";
				}
				if ( prms -> var_type == "int" || prms -> var_type == "float" || prms -> var_type == "char" || prms -> var_type == "bool")
				{
					type = prms -> var_type;
				}
				if ( param_type[i] != type )
					return 0;
				prms = prms -> next_symbol;
				i++;
			}
			if ( i != param_type.size() || prms -> name != "" )
				return 0;
			return 1;	
		}
		if ( prms == NULL && params == "" )
		{
			return 1;
		}
	}
	return 0;
}
//调用函数时获取函数的返回类型
string find_func_type ( string id )
{
	struct function* func_node = func_head_node;
	while( func_node != NULL )
	{
		if ( func_node->name == id )
		{
			return func_node -> ret_type;
		}
		func_node = func_node -> next_function;
	}
	return "NULL";
}
//向符号表的参数域增加参数
void add_parameter(string parameters)
{
	string new_para;
	string type;
	string paras;
	vector<string> para;
	vector<string> member_para;
	if ( func_cur_node -> symbol_list == NULL)								//当前函数表节点没有参数节点，则创建
	{
		func_cur_node->symbol_list = new struct symbol;
		func_cur_node->symbol_list->name = "";
		if ( parameters == "" )
			func_cur_node -> symbol_list -> parameters = NULL;
		else
		{
			func_cur_node -> symbol_list -> parameters = new struct symbol;
			param_cur_node = func_cur_node -> symbol_list -> parameters;
		}
	}
	
	if (parameters != "")													//参数不为空，则添加到该函数表节点的第一个符号表节点的parameter域
		new_para = del_space(parameters);
	else new_para = "";
	if ( new_para != "" )
	{
		int type_start = new_para.find(":");
		type = new_para.substr(0, type_start);
		if ( type_start != -1 )
		{
			paras = new_para.substr(type_start+1);
			para = split(paras, ",");
			if ( type.find("struct") == 0 )									//参数类型为记录类型
			{
				for ( int k = 0; k < para.size(); k++ )
				{
					param_cur_node -> name = para[k];
					param_cur_node -> var_type  = "struct";
					param_cur_node -> members = new struct symbol;
					struct symbol* pointer = param_cur_node -> members; 
					pointer-> next_symbol = NULL;
					string temp = type.substr(type.find("{")+1);
					string members = temp.erase(temp.find("}"));
					member_para = split(members,";");
					for ( int i = 0; i < member_para.size(); i++ )
					{
						vector<string> tmp = split(member_para[i],":");
						vector<string> vars = split(tmp[0],",");
						for ( int j = 0; j < vars.size(); j++ )				//存储每个成员的信息
						{
							pointer -> name = vars[j];
							pointer -> var_type = tmp[1];
							struct symbol *tmp = new struct symbol;
							if ( i == member_para.size()-1 && j == vars.size()-1 ){
								pointer -> next_symbol = NULL;
							}
							else{
								pointer -> next_symbol = tmp;
								pointer = tmp;
							}
						}
					}
					param_cur_node -> next_symbol = new struct symbol;
					param_cur_node = param_cur_node -> next_symbol;
					param_cur_node -> name == "";
				}
				
			}
			else if( type.find("array") == 0 )								//参数类型为数组类型
			{
				type = type.substr(5);
				for ( int k = 0; k < para.size(); k++ )
				{
					vector<string> bnds;
					param_cur_node -> name = para[k];
					param_cur_node -> var_type  = "array";
					param_cur_node -> array_type = type.substr(0, type.find("["));
					struct array_elem elem;
					string temp = type.substr(type.find("[")+1);
					string members = temp.erase(temp.find("]"), temp.size()-1 );
					bnds = split(members, ",");
					for ( int s = 0; s < bnds.size(); s ++ )
					{
						vector<string> bnd = split(bnds[s], "|");
						elem.low_bound = atoi(bnd[0].data());
						elem.up_bound = atoi(bnd[1].data());
						(param_cur_node -> bounds).push_back(elem);
					}
					param_cur_node -> next_symbol = new struct symbol;
					param_cur_node = param_cur_node -> next_symbol;
					param_cur_node -> name == "";
				}
			}
			else if( type.find("int") == 0 || type.find("float") == 0 || type.find("bool") == 0 || type.find("char") == 0)//参数类型为简单变量类型
			{
				for ( int k = 0; k < para.size(); k++ )
				{
					param_cur_node -> name = para[k];
					param_cur_node -> var_type  = type;
					param_cur_node -> next_symbol = new struct symbol;
					param_cur_node = param_cur_node -> next_symbol;
					param_cur_node -> name == "";
				}
			}
		}
	}
	sym_cur_node = func_cur_node->symbol_list;
	sym_cur_node -> next_symbol = NULL;
}

//向符号表中加入一个符号，记录其名字和类型，若为记录类型则要保存成员信息；若为数组类型需要保存上下界和维数
void add_symbol(string symbols, string type)
{
	string new_sym = del_space(symbols);
	vector<string> syms = split(new_sym, ",");
	struct symbol *symbol_cur = new struct symbol;
	vector<string> member_para;
		
	sym_cur_node->next_symbol = symbol_cur;
	symbol_cur -> parameters = NULL;
	symbol_cur->next_symbol = NULL;
	
	if ( func_head_node == func_cur_node && time_r == 1 )				//主函数中需要创建一个空的参数节点，因为主函数参数在转换中没有意义
	{
		add_parameter("");
		time_r = 0;
	}
	if ( type.find("struct") == 0 )										//增加记录类型的变量
	{
		for ( int k = 0; k < syms.size(); k++ )
		{
			symbol_cur -> name = syms[k];
			symbol_cur -> var_type  = "struct";
			symbol_cur -> members = new struct symbol;
			struct symbol* pointer = symbol_cur -> members; 
			pointer-> next_symbol = NULL;
			string temp = type.substr(type.find("{")+1);
			string members = temp.erase(temp.find("}"));
			member_para = split(members,";");
			for ( int i = 0; i < member_para.size(); i++ )				//保存成员信息
			{
				vector<string> tmp = split(member_para[i]," ");
				vector<string> vars = split(tmp[1],",");
				for ( int j = 0; j < vars.size(); j++ )
				{
					pointer -> name = vars[j];
					pointer -> var_type = tmp[0];
					struct symbol *tmp = new struct symbol;
					
					if ( i == member_para.size()-1 && j == vars.size()-1 ){
						pointer -> next_symbol = NULL;
					}
					else{
						pointer -> next_symbol = tmp;
						pointer = tmp;
					}
				}
			}
			if ( k == syms.size() - 1)
				symbol_cur -> next_symbol = NULL;
			else
			{
				symbol_cur -> next_symbol = new struct symbol;
				symbol_cur = symbol_cur -> next_symbol;
			}
		}
		
	}
	else if(type.find("array") == 0)									//增加数组变量
	{
		type = type.substr(5);
		for ( int k = 0; k < syms.size(); k++ )
		{
			vector<string> bnds;
			symbol_cur -> name = syms[k];
			symbol_cur -> var_type  = "array";
			
			symbol_cur -> array_type = type.substr(0, type.find("["));
			struct array_elem elem;
			string temp = type.substr(type.find("[")+1);
			string members = temp.erase(temp.find("]"), temp.size()-1 );
			bnds = split(members, ",");
			for ( int s = 0; s < bnds.size(); s ++ )//记录维数和上下界
			{
				vector<string> bnd = split(bnds[s], "|");
				elem.low_bound = atoi(bnd[0].data());
				elem.up_bound = atoi(bnd[1].data());
				symbol_cur -> bounds.push_back(elem);
			}
			if ( k == syms.size() - 1)
				symbol_cur -> next_symbol = NULL;
			else
			{
				symbol_cur -> next_symbol = new struct symbol;
				symbol_cur = symbol_cur -> next_symbol;
			}	
		}
	}
	else if (type.find("int") == 0 || type.find("float") == 0 || type.find("char") == 0 || type.find("bool") == 0)//保存普通类型变量
	{
		for ( int k = 0; k < syms.size(); k++ )
		{
			symbol_cur -> name = syms[k];
			symbol_cur -> var_type  = type;
			if ( k == syms.size() - 1)
				symbol_cur -> next_symbol = NULL;
			else{
				symbol_cur -> next_symbol = new struct symbol;
				symbol_cur = symbol_cur -> next_symbol;
			}
		}
	}

	sym_cur_node = symbol_cur;
}
//赋值类型检查
int assign_type_check( string left_type, string right_type )
{
	if ( left_type == "NULL" && right_type != "NULL") 
	{
		return -1;
	}
	else if (left_type != "NULL" && right_type == "NULL")
	{
		return -2;
	}
	else if (left_type == "NULL" && right_type == "NULL")
	{
		return -3;
	}
	else if ( left_type.find("const") == 0 )
	{
		return 0;
	}
	else if ( left_type.find("int") == 0 && right_type.find("constint") == 0 || left_type.find("int") == 0 && right_type.find("int") == 0) 		 
	{
		return 1;
	}
	else if ( left_type.find("array") != -1 && right_type.find("array") != -1 && left_type == right_type )
	{
		return 1;
	}
	else if( left_type == "float" && right_type == "int" || left_type == "float" && right_type == "constint" 
		   || left_type.find("float") == 0 && right_type.find("constfloat") == 0)
	{
		return 1;
	}
	else if ( left_type == "char" && right_type == "char" || left_type.find("char") == 0 && right_type.find("constchar") == 0 )
	{
		return 1;
	}
	else if ( left_type.find("bool") == 0 && right_type.find("bool") == 0 || left_type.find("bool") == 0 && right_type.find("constbool") == 0 )
	{
		return 1;
	}
	else if ( left_type.find("struct") != -1 && right_type.find("struct") != -1 && left_type == right_type )
	{
		return 1;
	}
	else
	{
		return -4;
	}
}
//将运算符号两边的变量类型合并
string combine_type( string type1, string type2 )//only int and float
{
	if( type1 == "int" && type2 == "int" || type1 == "constint" && type2 == "int" 
	  	|| type2 == "constint" && type1 == "int" || type1 == "constint" && type2 == "constint")
	{
		return "int";
	}
	else if ( type1 == "char" && type2 == "char" || type1 == "constchar" && type2 == "char" 
		|| type1 == "char" && type2 == "constchar" || type1 == "constchar" && type2 == "constchar")
	{
		return "char";
	}
	else if ( type1 == "float" && type2 == "int" || type1 == "float" && type2 == "constint" 
		|| type1 == "float" && type2 == "float" || type1 == "float" && type2 == "constfloat"
		|| type1 == "constfloat" && type2 == "int" || type1 == "constfloat" && type2 == "constint" 
		|| type1 == "constfloat" && type2 == "float" || type1 == "constfloat" && type2 == "constfloat"
		|| type1 == "int" && type2 == "float" || type1 == "int" && type2 == "constfloat"
		|| type1 == "constint" && type2 == "float" || type1 == "constint" && type2 == "constfloat")
	{
		return "float";
	}
	else if ( type1 == "bool" && type2 == "bool" || type1 == "bool" && type2 == "constbool"
		|| type1 == "constbool" && type2 == "bool" || type1 == "constbool" && type2 == "constbool")
	{
		return "bool";
	}
	else
	{
		return "NULL";
	}
		
}
//整型转字符串函数
string int2str( int int_temp )  
{  
	string string_temp;
    stringstream stream;  
    stream<<int_temp;  
    string_temp=stream.str();   //此处也可以用 stream>>string_temp  
	return string_temp;
} 
//获得局部变量或者当前所在函数的类型
string find_local_var_func_type( string id, string id_varparts )//only parameter node
{
	struct symbol* sym_node;
	if ( is_main == 1 )
	{ 
		sym_node = func_head_node -> symbol_list;
	}
	else
	{
		sym_node = func_cur_node -> symbol_list;
	}
	if ( id == func_cur_node -> name )
		return func_cur_node -> ret_type;
	
	if ( id_varparts == "" )
	{
		int start = func_cur_node -> const_start;
		int num = func_cur_node -> const_num;
		if ( num != 0 )
		{
			for ( int i = start; i < start + num; i++ )
			{
				if ( const_table[i].name == id )
					return "const"+const_table[i].const_type;
			}
		}
	}
	
	while(sym_node != NULL) 
	{
		if( sym_node -> parameters != NULL )
		{
			struct symbol* param_node = sym_node -> parameters;
			while( param_node != NULL )
			{
				if( param_node -> name == id )
				{
					if ( id_varparts.find("array") != -1 )
					{
						return param_node -> array_type;
					}
					else if ( id_varparts.find("struct") != -1 )
					{
						string member = id_varparts.substr(7);
						struct symbol* mems = param_node -> members;
						while( mems != NULL )
						{
							if ( mems -> name == member )
							{
								return mems -> var_type;
							}
							mems = mems -> next_symbol;
						}
					}
					else if ( id_varparts == "" )
					{
						if( param_node -> var_type == "array" )
						{
							string arraytp = "";
							arraytp = arraytp + "array" + param_node -> array_type + "[";
							vector<struct array_elem> bnds(param_node -> bounds);
							for ( int i = 0; i < bnds.size(); i++ )
							{
								string low_bound;
								string up_bound;
								low_bound = int2str(bnds[i].low_bound);
								up_bound = int2str(bnds[i].up_bound);
								arraytp = arraytp + low_bound + "|" + up_bound;
								if ( i != bnds.size() - 1 )
									arraytp = arraytp + ",";
							}
							arraytp = arraytp + "]";
							return arraytp;
						}
						else if ( param_node -> var_type == "struct" )
						{
							string structtp = "";
							structtp = structtp + "struct" + "{";
							struct symbol*  members = param_node -> members;
							while(members != NULL )
							{
								structtp += members -> name + ":" + members->var_type;
								if ( members -> next_symbol != NULL )
								{
									structtp += ";";
								}
								members = members -> next_symbol;
							}
							structtp += "}";
							return structtp;
						}
					}
					return param_node -> var_type;
				}
				param_node = param_node -> next_symbol;
			}
		}
		struct symbol* cur_node = sym_node;
		if ( cur_node -> name == id )
		{
			if ( id_varparts.find("array") != -1 )
			{
				return cur_node -> array_type;
			}
			else if( id_varparts.find("struct") != -1 )
			{
				string member = id_varparts.substr(7);
				struct symbol* mems = cur_node -> members;
				while( mems != NULL )
				{
					if ( mems -> name == member )
					{
						return mems -> var_type;
					}
					mems = mems -> next_symbol;
				}
			}
			else if ( id_varparts == "" )
			{
				if( cur_node -> var_type == "array" )
				{
					string arraytp = "";
					arraytp = arraytp + "array" + cur_node -> array_type + "[";
					vector<struct array_elem> bnds(cur_node -> bounds);
					for ( int i = 0; i < bnds.size(); i++ )
					{
						string low_bound;
						string up_bound;
						low_bound = int2str(bnds[i].low_bound);
						up_bound = int2str(bnds[i].up_bound);
						arraytp = arraytp + low_bound + "|" + up_bound;
						if ( i != bnds.size() - 1 )
							arraytp = arraytp + ",";
					}
					arraytp = arraytp + "]";
					return arraytp;
				}
				else if ( cur_node -> var_type == "struct" )
				{
					string structtp = "";
					structtp = structtp + "struct" + "{";
					struct symbol*  members = cur_node -> members;
					while(members != NULL )
					{
						structtp += members -> name + ":" + members->var_type;
						if ( members -> next_symbol != NULL )
						{
							structtp += ";";
						}
						members = members -> next_symbol;
					}
					structtp += "}";
					return structtp;
				}
			}
			return cur_node -> var_type;
		}
		sym_node = sym_node -> next_symbol;
	}
	return find_global_var_type(id, id_varparts);
}
//获取全局变量类型
string find_global_var_type( string id, string id_varparts )
{
	struct symbol *sym_node = func_head_node -> symbol_list -> next_symbol;
	if ( id_varparts == "" )
	{
		int start = func_head_node -> const_start;
		int num = func_head_node -> const_num;
		if ( num != 0 )
		{
			for ( int i = start; i < start + num; i++ )
			{
				if ( const_table[i].name == id )
					return "const"+const_table[i].const_type;
			}
		}
		
	}
	
	while (sym_node != NULL)
	{
		if ( sym_node -> name == id )
		{
			if ( id_varparts.find("array") != -1 )
			{
				return sym_node -> array_type;
			}
			else if( id_varparts.find("struct") != -1 )
			{
				
				string member = id_varparts.substr(7);
				struct symbol* mems = sym_node -> members;
				while( mems != NULL )
				{
					if ( mems -> name == member )
					{
						return mems -> var_type;
					}
					mems = mems -> next_symbol;
				}
			}
			else if ( id_varparts == "" )
			{
				if( sym_node -> var_type == "array" )
				{
					string arraytp = "";
					arraytp = arraytp + "array" + sym_node -> array_type + "[";
					vector<struct array_elem> bnds(sym_node -> bounds);
					for ( int i = 0; i < bnds.size(); i++ )
					{
						string low_bound;
						string up_bound;
						low_bound = int2str(bnds[i].low_bound);
						up_bound = int2str(bnds[i].up_bound);
						arraytp = arraytp + low_bound + "|" + up_bound;
						if ( i != bnds.size() - 1 )
							arraytp = arraytp + ",";
					}
					arraytp = arraytp + "]";
					return arraytp;
				}
				else if ( sym_node -> var_type == "struct" )
				{
					string structtp = "";
					structtp = structtp + "struct" + "{";
					struct symbol*  members = sym_node -> members;
					while(members != NULL )
					{
						structtp += members -> name + ":" + members->var_type;
						if ( members -> next_symbol != NULL )
						{
							structtp += ";";
						}
						members = members -> next_symbol;
					}
					structtp += "}";
					return structtp;
				}
			}
			return sym_node -> var_type;
		}
		sym_node = sym_node -> next_symbol;
	}
	return "NULL";
}
//获取声明常量的类型
string get_const_type(string id)
{
	int start = func_cur_node->const_start;
	int num = func_cur_node->const_num;
	string result = "not exist";

	if (num == 0)
	{
		return result;
	}
	for (int i = start; i < start + num; i ++)
	{
		if (const_table[i].name == id)
		{
			result = const_table[i].const_type;
		}
	}
	start = func_head_node->const_start;
	num = func_head_node->const_num;
	for (int j = start; j < num + start; j ++)
	{
		if (const_table[j].name == id)
		{
			result = const_table[j].const_type;
		}
	}
	return result;
}
//获取声明常量的名字
string get_const_value(string id)
{
	int start = func_cur_node->const_start;
	int num = func_cur_node->const_num;
	string result = "not exist";
	if (num == 0)
	{
		return result;
	}
	for (int i = start; i < start + num; i ++)
	{
		if (const_table[i].name == id)
		{
			return const_table[i].name;
		}
	}
	start = func_head_node->const_start;
	num = func_head_node->const_num;
	for (int j = start; j < num + start; j ++)
	{
		if (const_table[j].name == id)
		{
			return const_table[j].name;
		}
	}
	return result;
}

//从type_table中获取type类型，找不到返回not exist
string get_typedef_type(string id)
{
	int start = func_cur_node->type_start;
	int num = func_cur_node->type_num;
	string result = "not exist";
	if (num == 0)
	{
		return result;
	}
	
	for (int i = start; i < num + start; i ++)
	{
		if (type_table[i].name == id)
		{
			return type_table[i].type;
		}
	}
	start = func_head_node->type_start;
	num = func_head_node->type_num;
	for (int j = start; j < num + start; j ++)
	{
		if (type_table[j].name == id)
		{
			return type_table[j].type;
		}
	}
	
	return result;
}

//从type_table中获取type名，找不到返回not exist
string get_typedef_value(string id)
{
	int start = func_cur_node->type_start;
	int num = func_cur_node->type_num;
	string result = "not exist";
	if (num == 0)
	{
		return result;
	}
	for (int i = start; i < num + start; i ++)
	{
		if (type_table[i].name == id)
		{
			result = type_table[i].name;
		}
	}
	start = func_head_node->type_start;
	num = func_head_node->type_num;
	
	for (int j = start; j < num + start; j ++)
	{
		if (type_table[j].name == id)
		{
			result = type_table[j].name;
		}
	} 
	return result;
}

//在id_list中直接进行重复检查，重复返回0，不重复返回1
int check_in_ids(string &id_list)
{
	string new_list;
	vector<string> ids;
	if (id_list != "")
	{
		new_list = del_space(id_list);
	}
	else 
	{
		new_list = "";
	}
	ids = split(new_list,",");
	int size1 = ids.size();
	sort(ids.begin(),ids.end());
	ids.erase( unique(ids.begin(),ids.end()), ids.end() );
	int size2 = ids.size();
	id_list = "";
	for (int i = 0; i < size2; i ++)
	{
		id_list = id_list + ids[i] + ", ";
	}
	id_list = id_list.substr(0,id_list.length() - 2);
	
	if (size2 < size1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//对已定义的函数名、参数名、const、type和变量名进行查重，有重复则删除id
//返回值为0表示函数名有重复，返回值为1函数名表示无重复
int check_repeat_func(string id)
{
	int result = 1;
	if (get_typedef_value(id) != "not exist" || get_const_value(id) != "not exist")
	{
		result = 0;
	}
	struct symbol* search_var;
	search_var = func_head_node->symbol_list->next_symbol;
	
	while (search_var != NULL)
	{
		if (search_var->name == id)
		{
			result = 0;
		}
		search_var = search_var->next_symbol;
	}
	
	struct function* search_func;
	search_func = func_head_node;
	while (search_func != NULL)
	{
		if (search_func->name == id)
		{
			result = 0;
		}
		search_func = search_func->next_function;
	}
	return result;
}

//对已定义的函数名、参数名、const、type和变量名进行查重，有重复则删除id
//返回值为0表示有重复，返回值为1表示无重复
int check_repeat_definition(string &id_list)
{
	int result = 1;
	string new_list;
	vector<string> ids;
	if (id_list != "")
	{
		new_list = del_space(id_list);
	}
	else 
	{
		new_list = "";
	}
	ids = split(new_list,",");

	//是否与当前函数名重复
	for (int i = 0; i < ids.size(); i ++)
	{
		vector<string>::iterator it;
		if (ids[i] == func_cur_node->name)
		{
			it = ids.begin() + i;
			ids.erase(it);
			result = 0;
		}
	}

	//是否与已定义参数名重复
	struct symbol* search_sym = func_cur_node->symbol_list;
	struct symbol* search_para = NULL;
	if (search_sym != NULL)
	{
		search_para = search_sym->parameters;
	}
	
	if (search_para != NULL)
	{
		while (search_para->name != "")
		{
			for (int i = 0; i < ids.size(); i ++)
			{	
					
				if (ids[i] == search_para->name)
				{
					vector<string>::iterator it;
					it = ids.begin() + i;
					ids.erase(it);
					result = 0;
				}
			}
			search_para = search_para->next_symbol;
		}
	}	

	for (int i = 0; i < ids.size(); i ++)
	{	
		vector<string>::iterator it;
		//是否与已定义const重复
		
		if (get_const_value(ids[i]) != "not exist")
		{
			it = ids.begin() + i;
			ids.erase(it);
			result = 0;
		}
		if (ids.size() == 0)
		{
			break;
		}
		//是否与已定义type重复
		if (get_typedef_value(ids[i]) != "not exist")
		{
			it = ids.begin() + i;
			ids.erase(it);
			result = 0;
		}
	}
	//是否与已定义变量名重复
	if (search_sym != NULL)
	{
		search_sym = func_cur_node->symbol_list->next_symbol;
	}
	while (search_sym != NULL)
	{
		for (int i = 0; i < ids.size(); i ++)
		{
			if (ids[i] == search_sym->name)
			{
				vector<string>::iterator it;
				it = ids.begin() + i;
				ids.erase(it);
				result = 0;
			}
		}
		search_sym = search_sym->next_symbol;
	}
	id_list = "";
	for (int i = 0; i < ids.size(); i ++)
	{
		id_list = id_list + ids[i] + ", ";
	}
	id_list = id_list.substr(0,id_list.length() - 2);
	
	return result;
}

//id_list自身内部查重与已定义变量,const,type的查重
int check_var_declaration(string &id_list,string &type)
{
	int ret = 1;
	if (in_record == 1)
	{
		if (check_in_ids(id_list) == 0)
		{
			ret = 0;
		}		
	}
	else
	{
		if (check_in_ids(id_list) == 0 || check_repeat_definition(id_list) == 0)
		{
			ret = 0;
		}
		if (id_list != "")
		{
			add_symbol(id_list, type);
		}
	}
	return ret;
}

//将const类型加入const_table中
void add_const(string id, string replace, string replace_type)
{
	struct const_node new_const;
	bool is_id = false;
	new_const.name = id;
	new_const.const_type = replace_type;
	new_const.value = replace;
	const_table.push_back(new_const);
	func_cur_node->const_num ++;
	const_cur_pos ++;
}

//将type类型加入type_table中
void add_typedef(string id, string type)
{
	struct type_node new_type;
	new_type.name = id;
	new_type.type = type;
	type_table.push_back(new_type);
	func_cur_node->type_num ++;
	type_cur_pos ++;
}

//翻译参数定义和变量定义
string definition_trans(string para, bool is_para)     
{
	bool is_var = false;
	//传引用的参数与传值参数翻译不同
	if (para.find("var+") != -1)
	{
		is_var = true;
		para = para.substr(4);
	}
	string result;
	string id_list;
	vector<string> ids;
	if (para.find("[") == -1 && para.find("{") == -1)
	//基本类型的翻译
	{
		int pos = para.find(":");
		id_list = para.substr(pos + 1);
		ids = split(id_list, ",");
		string type = para.substr(0, pos);
	
		if (is_para)
		{
			for (int i = 0; i < ids.size(); i++)
			{
				if (is_var)
				{
					result = result + type + " &" + ids[i] + ", ";
				}
				else
				{
					result = result + type + " " + ids[i] + ", ";
				}
			}
			result = result.substr(0, result.length() - 2);
		}
		else
		{
			result = type + " " + id_list;
		}
	}
	
	if (para.find("struct") == 0)
	//record类型的翻译
	{
		int pos = para.find("}");
		string type = para.substr(0, pos + 1);
		id_list = para.substr(pos + 2);
		ids = split(id_list, ",");
		if (is_para)
		{
			for (int i = 0; i < ids.size(); i++)
			{
				if (is_var)
				{
					result = result + type + " &" + ids[i] + ", ";
				}
				else
				{
					result = result + type + " " + ids[i] + ", ";
				}
			}
			result = result.substr(0, result.length() - 2);
		}
		else
		{
			result = type + " " + id_list;
		}
	}
	else if (para.find("[") != -1)
	//数组类型的翻译
	{
		para = para.substr(5);
		int pos = para.find(":");
		int pos1 = para.find("[");
		int pos2 = para.find("]");
		
		id_list = para.substr(pos + 1);
		ids = split(id_list, ",");
		string type = para.substr(0, pos1);
		string dimension = para.substr(pos1 + 1, pos2 - pos1 - 1);
		vector<string> dim_list = split(dimension, ",");
		string final_dim;
		
		for (int j = 0; j < dim_list.size(); j++)
		{
			int pos3 = dim_list[j].find("|");
			string low = dim_list[j].substr(0, pos3);
			string high = dim_list[j].substr(pos3 + 1);
			int range, low_bound, high_bound;
			low_bound = atoi(low.c_str());
			high_bound = atoi(high.c_str());
			range = high_bound - low_bound + 1;
			stringstream ss;
			ss << range;
			string s = ss.str();
			final_dim = final_dim + "[" + s + "]";
		}
		
		if (is_para)
		{
			for (int i = 0; i < ids.size(); i++)
			{
				if (is_var)
				{
					result = result + type + " &" + ids[i];
				}
				else
				{
					result = result + type + " " + ids[i];
				}

				result = result + final_dim + ", ";
			}
			result = result.substr(0, result.length() - 2);
		}
		else
		{
			result = result + type + " "; 
			for (int i = 0; i < ids.size(); i ++)
			{
				result = result + ids[i] + final_dim + ", ";
			}
			result = result.substr(0, result.length() - 2);
		}
	}
	return result;
}

int main()																//程序主函数，这个函数也可以放到其它.c, .cpp文件里
{
	
	FILE* fp1 = fopen(sFile, "r");
	if (fp1 == NULL)
	{
		printf("cannot open %s\n", sFile);
		return -1;
	}
	extern FILE* yyin,yyout;											//yyin和yyout都是FILE*类型
	yyin = fp1;															//yacc会从yyin读取输入，yyin默认是标准输入，这里改为磁盘文件。yacc默认向yyout输出，可修改yyout改变输出目的

	printf("-----begin parsing %s\n", sFile);
	yyparse();															//使yacc开始读取输入和解析，它会调用lex的yylex()读取记号
	puts("-----end parsing");

	fclose(fp1);

	return 0;
}