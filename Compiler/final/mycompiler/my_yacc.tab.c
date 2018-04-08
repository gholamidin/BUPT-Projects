/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "my_yacc.y" /* yacc.c:339  */
	
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

#line 129 "my_yacc.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "my_yacc.tab.h".  */
#ifndef YY_YY_MY_YACC_TAB_H_INCLUDED
# define YY_YY_MY_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 1,
    FUNCTION = 2,
    PROCEDURE = 3,
    INTEGER = 4,
    REAL = 5,
    BOOLEAN = 6,
    ARRAY = 7,
    RECORD = 8,
    VAR = 9,
    BEGIN1 = 10,
    END = 11,
    OF = 12,
    IF = 13,
    THEN = 14,
    ELSE = 15,
    WHILE = 16,
    DO = 17,
    NOT = 18,
    TRUE = 19,
    FALSE = 20,
    READ = 21,
    WRITE = 22,
    COMMA = 37,
    SEMICOLON = 38,
    COLON = 39,
    LEFTCUBE = 40,
    RIGHTCUBE = 41,
    LEFTCIRCLE = 42,
    RIGHTCIRCLE = 43,
    PROGRAMEND = 45,
    FLOAT = 46,
    INT = 47,
    ID = 48,
    RELOP = 49,
    ADDOP = 50,
    MULOP = 51,
    ASSIGNOP = 52,
    SYMBOL = 53,
    FOR = 54,
    TO = 55,
    CONST = 57,
    MINUSOP = 58,
    TYPE = 59,
    CHAR = 60,
    REPEAT = 61,
    UNTIL = 62,
    DOWNTO = 63,
    CASE = 64,
    LETTER = 65,
    WRITELN = 66,
    READLN = 67,
    IFX = 258
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MY_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 235 "my_yacc.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   370

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  272

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   258

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    25,    26,    27,
      28,    29,    30,    31,     2,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     2,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   138,   150,   155,   163,   171,   179,   189,
     203,   207,   214,   220,   231,   246,   251,   282,   317,   349,
     388,   393,   398,   403,   408,   413,   418,   423,   428,   433,
     440,   451,   466,   471,   503,   539,   545,   550,   556,   561,
     568,   573,   578,   583,   590,   595,   600,   604,   610,   620,
     629,   640,   655,   669,   756,   847,   886,   922,   927,   932,
     939,   944,   949,   957,   962,   967,   977,   991,  1005,  1009,
    1017,  1022,  1039,  1052,  1067,  1072,  1078,  1084,  1102,  1125,
    1129,  1138,  1142,  1149,  1155,  1167,  1182,  1197,  1201,  1205,
    1215,  1219,  1226,  1236,  1249,  1253,  1266,  1283,  1286,  1290,
    1296,  1303,  1308,  1313,  1320,  1326,  1334,  1364,  1371,  1376,
    1384,  1392,  1401,  1408,  1434,  1441,  1469,  1488,  1493,  1509,
    1514,  1521,  1526,  1531,  1538,  1576,  1589,  1605,  1610,  1661,
    1667,  1672,  1679,  1684,  1689,  1695,  1700,  1704,  1710,  1748,
    1759,  1772,  1776,  1782,  1803,  1832,  1864,  1896,  1917,  1923
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "FUNCTION", "PROCEDURE",
  "INTEGER", "REAL", "BOOLEAN", "ARRAY", "RECORD", "VAR", "BEGIN1", "END",
  "OF", "IF", "THEN", "ELSE", "WHILE", "DO", "NOT", "TRUE", "FALSE",
  "READ", "WRITE", "COMMA", "SEMICOLON", "COLON", "LEFTCUBE", "RIGHTCUBE",
  "LEFTCIRCLE", "RIGHTCIRCLE", "PROGRAMEND", "FLOAT", "INT", "ID", "RELOP",
  "ADDOP", "MULOP", "ASSIGNOP", "SYMBOL", "FOR", "TO", "CONST", "MINUSOP",
  "TYPE", "CHAR", "REPEAT", "UNTIL", "DOWNTO", "CASE", "LETTER", "WRITELN",
  "READLN", "IFX", "$accept", "program", "program_head", "program_body",
  "identifier_list", "const_declarations", "const_declaration",
  "const_variable", "type_declarations", "type_declaration", "R", "type",
  "standard_type", "record_body", "periods", "period", "var_declarations",
  "var_declaration", "subprogram_declarations", "subprogram_declaration",
  "subprogram_head", "M", "N", "formal_parameter", "parameter_lists",
  "parameter_list", "var_parameter", "value_parameter",
  "compound_statement", "statement_list", "statement", "T", "write",
  "read", "S", "expression", "simple_expression", "term", "factor",
  "unsigned_const_variable", "variable", "IDM", "id_varparts",
  "id_varpart", "variable_list", "else_part", "case_body", "branch_list",
  "branch", "const_list", "updown", "call_procedure_statement",
  "expression_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    37,    38,    39,    40,    41,
      42,    43,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,   258
};
# endif

#define YYPACT_NINF -132

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-132)))

#define YYTABLE_NINF -126

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      24,    40,    94,    60,    -9,  -132,    83,    97,    92,  -132,
      49,  -132,   127,   146,   121,  -132,   139,   144,   136,    61,
     155,   170,   154,   207,   207,   174,   159,   186,   183,  -132,
    -132,  -132,   196,  -132,  -132,  -132,  -132,  -132,  -132,   201,
     212,  -132,  -132,  -132,   180,   133,   188,   338,   203,   104,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,   207,   207,  -132,
    -132,  -132,   204,  -132,  -132,  -132,   183,  -132,  -132,   195,
     133,   183,   213,   218,   258,   229,    60,   169,   108,  -132,
    -132,  -132,   207,   246,   235,   133,  -132,   343,  -132,  -132,
     301,   301,   236,   241,    63,   237,   258,   301,   244,  -132,
     109,  -132,   238,  -132,  -132,   207,     5,  -132,  -132,  -132,
      92,   133,    14,    16,  -132,    41,    18,   135,  -132,  -132,
     183,  -132,   133,   173,   301,  -132,  -132,   248,   173,   173,
    -132,   259,   -14,   247,  -132,  -132,  -132,   202,   249,   301,
     281,  -132,    27,  -132,   163,   265,   301,  -132,   215,  -132,
     301,  -132,   270,   261,  -132,   -11,   250,   301,   301,   160,
     144,   262,   183,    28,   145,  -132,  -132,  -132,  -132,   133,
    -132,   133,   207,   264,   207,   276,  -132,  -132,   260,   289,
     247,   247,   258,   301,   173,   173,   173,   258,  -132,  -132,
    -132,    88,   100,  -132,   260,   120,   301,  -132,   258,   301,
    -132,   123,  -132,  -132,    21,  -132,   207,   207,   258,   301,
    -132,  -132,   301,   263,  -132,   282,  -132,  -132,   133,    14,
      25,  -132,   274,   277,  -132,   207,  -132,    31,  -132,  -132,
     132,   285,    68,   247,   247,  -132,  -132,   249,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,   301,  -132,  -132,  -132,
    -132,   148,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,   258,  -132,  -132,   245,  -132,  -132,   258,
    -132,  -132
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    15,     0,     1,     0,     3,    32,     8,
       0,    12,     0,     0,    14,     2,     0,    52,     0,     0,
       0,     0,     0,     0,     0,    13,     0,    31,     0,    58,
       7,     5,     0,    11,    10,     6,    25,    28,    22,     0,
       0,    29,    18,    19,     0,     0,    30,     0,    51,     0,
       4,    23,    26,    20,    24,    27,    21,     0,     0,    40,
      41,    42,     0,    35,    39,    43,    45,    34,    36,     0,
       0,    50,     0,     0,    97,     0,    15,    70,    70,     9,
      16,    17,     0,     0,    44,     0,    56,     0,    66,    67,
       0,     0,     0,     0,   143,     0,    97,     0,   103,    88,
       0,    83,     0,    98,    99,   135,     0,   127,    87,    57,
      32,     0,     0,     0,    64,     0,     0,     0,    47,    37,
       0,    33,     0,     0,     0,   121,   122,   125,     0,     0,
     123,     0,   107,   108,   114,   119,   120,    97,     0,     0,
       0,   149,     0,   100,     0,     0,     0,    79,    97,    82,
       0,   140,    91,   134,   137,     0,     0,     0,     0,   124,
      52,     0,     0,     0,     0,    73,    74,    75,    62,     0,
      63,     0,     0,     0,     0,     0,    53,   118,     0,     0,
     109,   110,    97,     0,     0,     0,     0,    97,    93,   125,
     131,     0,     0,   147,   149,   146,     0,   145,    97,     0,
     105,     0,    80,    81,     0,    90,     0,     0,    97,     0,
      85,    84,     0,     0,   126,     0,    61,    76,     0,     0,
       0,    68,     0,     0,    49,     0,    46,     0,   117,   116,
       0,   133,   106,   111,   112,   113,    92,     0,   104,   101,
     144,   148,    94,   102,   141,   142,     0,   136,   139,   138,
      86,     0,   129,    59,    77,    72,    69,    71,    60,    65,
      48,    38,   115,    97,    89,   130,    97,   128,   132,    97,
      96,    95
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -132,  -132,     3,   228,  -132,   -23,   197,  -132,
    -132,   -65,    79,  -132,  -132,   143,   153,   271,  -132,  -132,
    -132,  -132,  -132,   251,  -132,   -19,  -132,   165,   -45,   232,
     -97,  -132,  -132,  -132,  -132,   -79,   147,   -96,  -113,  -132,
     -72,  -132,  -132,  -132,  -132,  -132,  -132,  -132,   140,  -132,
    -132,  -132,  -131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,   163,     8,    14,   116,    17,    27,
      66,    67,    68,    83,   117,   118,    29,    48,    49,    75,
      76,    77,    78,   113,   164,   165,   166,   167,    99,   100,
     101,   102,   103,   104,   105,   141,   132,   133,   134,   135,
     136,   107,   159,   214,   191,   264,   152,   153,   154,   155,
     246,   108,   142
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    43,   106,   149,    79,    86,   156,    12,   192,   195,
     177,   131,   137,    19,   207,   201,   208,     9,   145,   172,
     121,    10,   183,   184,   106,   162,    11,     1,   106,    20,
     185,    47,   180,   181,    80,    81,   162,    59,    60,    61,
     188,   157,   168,   169,   158,   178,   161,   149,   230,    11,
     173,   203,   196,    21,   -78,   218,   256,   176,   197,   -78,
      11,   194,    20,   244,  -125,   106,   190,   170,   171,    47,
     245,   204,   106,   235,    87,     4,   106,    65,   210,   211,
      18,   251,   151,   123,    11,   231,    21,    31,   233,   234,
     236,  -125,    32,   140,     5,  -125,   125,   126,   127,  -125,
     128,   203,  -125,     6,   222,   184,   223,   129,    72,    73,
     106,   249,   185,   237,   130,   106,    74,   241,    13,   238,
     242,    74,   147,    87,    90,   196,   106,    91,    20,    15,
     250,   239,    92,    93,   114,   148,   106,    16,   112,    59,
      60,    61,    62,    63,    94,   196,   219,    25,   196,   224,
      95,   240,    21,   254,   243,    28,    96,   196,    22,    97,
     174,    98,    30,   262,   175,   265,   268,   266,    64,   270,
     253,   220,   271,   196,    26,    74,   221,   267,    90,    65,
      35,    91,    23,   151,   248,    24,    92,    93,   212,   198,
      33,   106,   213,   123,   106,    45,   111,   106,    94,   112,
     255,   257,   260,   124,    95,    34,   125,   126,   127,    44,
      96,   199,    46,    97,    74,    98,    57,    90,    11,    58,
      91,   187,    50,    69,   130,    92,    93,    74,   202,    71,
      90,    85,    82,    91,    51,    52,    53,    94,    92,    93,
      36,    37,    38,    95,    39,    54,    55,    56,    88,    96,
      94,    40,    97,    89,    98,   109,    95,    74,    41,   119,
      90,   120,    96,    91,   269,    97,   138,    98,    92,    93,
      74,   139,   143,    90,   146,   182,    91,   150,   179,   200,
      94,    92,    93,   205,   189,   186,    95,   206,   216,   209,
     227,   228,    96,    94,    74,    97,   225,    98,   252,    95,
     258,   123,   263,   259,   110,    96,   261,   160,    97,   123,
      98,   124,   193,   215,   125,   126,   127,   226,   128,   124,
     229,   123,   125,   126,   127,   129,   128,   217,   144,   115,
     232,   124,   130,   129,   125,   126,   127,    84,   128,    20,
     130,     0,   -55,   -55,    20,   129,   247,   -54,   -54,     0,
     -55,   -55,   130,     0,     0,   -54,   -54,     0,     0,     0,
       0,     0,     0,    21,   -55,    70,     0,     0,    21,   -54,
     122
};

static const yytype_int16 yycheck[] =
{
      23,    24,    74,   100,    49,    70,     1,     4,   139,   140,
     123,    90,    91,    10,    25,   146,    27,    26,    97,     1,
      85,    30,    36,    37,    96,    11,    35,     3,   100,     1,
      44,    28,   128,   129,    57,    58,    11,     6,     7,     8,
     137,    36,    26,    27,    39,   124,   111,   144,   179,    35,
      32,   148,    25,    25,    26,    27,    31,   122,    31,    31,
      35,   140,     1,    42,     1,   137,   138,    26,    27,    66,
      49,   150,   144,   186,    71,    35,   148,    46,   157,   158,
      31,   212,   105,    20,    35,   182,    25,    26,   184,   185,
     187,    28,    31,    30,     0,    32,    33,    34,    35,    36,
      37,   198,    39,    43,   169,    37,   171,    44,     4,     5,
     182,   208,    44,    25,    51,   187,    12,   196,    35,    31,
     199,    12,    13,   120,    15,    25,   198,    18,     1,    32,
     209,    31,    23,    24,    26,    26,   208,    45,    30,     6,
       7,     8,     9,    10,    35,    25,     1,    26,    25,   172,
      41,    31,    25,   218,    31,    11,    47,    25,    31,    50,
      25,    52,    26,    31,    29,   237,   263,   246,    35,   266,
     215,    26,   269,    25,    35,    12,    31,    29,    15,    46,
      26,    18,    36,   206,   207,    39,    23,    24,    28,    26,
      35,   263,    32,    20,   266,    36,    27,   269,    35,    30,
     219,   220,   225,    30,    41,    35,    33,    34,    35,    35,
      47,    48,    26,    50,    12,    52,    36,    15,    35,    39,
      18,    19,    26,    35,    51,    23,    24,    12,    13,    26,
      15,    36,    28,    18,    33,    34,    35,    35,    23,    24,
      33,    34,    35,    41,    37,    33,    34,    35,    35,    47,
      35,    44,    50,    35,    52,    26,    41,    12,    51,    13,
      15,    26,    47,    18,    19,    50,    30,    52,    23,    24,
      12,    30,    35,    15,    30,    16,    18,    39,    30,    14,
      35,    23,    24,    13,    35,    38,    41,    26,    26,    39,
      14,    31,    47,    35,    12,    50,    32,    52,    35,    41,
      26,    20,    17,    26,    76,    47,   227,   110,    50,    20,
      52,    30,    31,   160,    33,    34,    35,   174,    37,    30,
      31,    20,    33,    34,    35,    44,    37,   162,    96,    78,
     183,    30,    51,    44,    33,    34,    35,    66,    37,     1,
      51,    -1,     4,     5,     1,    44,   206,     4,     5,    -1,
      12,    13,    51,    -1,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    -1,    -1,    25,    26,
      27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    56,    57,    35,     0,    43,    58,    60,    26,
      30,    35,    59,    35,    61,    32,    45,    63,    31,    59,
       1,    25,    31,    36,    39,    26,    35,    64,    11,    71,
      26,    26,    31,    35,    35,    26,    33,    34,    35,    37,
      44,    51,    62,    62,    35,    36,    26,    59,    72,    73,
      26,    33,    34,    35,    33,    34,    35,    36,    39,     6,
       7,     8,     9,    10,    35,    46,    65,    66,    67,    35,
      27,    26,     4,     5,    12,    74,    75,    76,    77,    83,
      62,    62,    28,    68,    72,    36,    66,    59,    35,    35,
      15,    18,    23,    24,    35,    41,    47,    50,    52,    83,
      84,    85,    86,    87,    88,    89,    95,    96,   106,    26,
      60,    27,    30,    78,    26,    78,    62,    69,    70,    13,
      26,    66,    27,    20,    30,    33,    34,    35,    37,    44,
      51,    90,    91,    92,    93,    94,    95,    90,    30,    30,
      30,    90,   107,    35,    84,    90,    30,    13,    26,    85,
      39,    62,   101,   102,   103,   104,     1,    36,    39,    97,
      63,    66,    11,    59,    79,    80,    81,    82,    26,    27,
      26,    27,     1,    32,    25,    29,    66,    93,    90,    30,
      92,    92,    16,    36,    37,    44,    38,    19,    85,    35,
      95,    99,   107,    31,    90,   107,    25,    31,    26,    48,
      14,   107,    13,    85,    90,    13,    26,    25,    27,    39,
      90,    90,    28,    32,    98,    71,    26,    82,    27,     1,
      26,    31,    66,    66,    62,    32,    70,    14,    31,    31,
     107,    85,    91,    92,    92,    93,    85,    25,    31,    31,
      31,    90,    90,    31,    42,    49,   105,   103,    62,    85,
      90,   107,    35,    83,    66,    80,    31,    80,    26,    26,
      62,    67,    31,    17,   100,    95,    90,    29,    85,    19,
      85,    85
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    57,    57,    57,    57,    57,    58,
      59,    59,    59,    60,    60,    60,    61,    61,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      63,    63,    63,    64,    64,    65,    66,    66,    66,    66,
      67,    67,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    71,    71,    72,    72,    72,    72,    73,    73,    74,
      75,    75,    75,    75,    75,    75,    76,    77,    78,    78,
      78,    79,    79,    79,    80,    80,    81,    82,    82,    83,
      83,    84,    84,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      86,    87,    87,    87,    88,    89,    90,    90,    91,    91,
      91,    91,    91,    92,    92,    93,    93,    93,    93,    93,
      93,    94,    94,    94,    95,    96,    97,    97,    98,    98,
      99,    99,   100,   100,   101,   101,   102,   102,   103,   104,
     104,   105,   105,   106,   106,   106,   106,   106,   107,   107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     6,     5,     5,     5,     3,     5,
       3,     3,     1,     3,     2,     0,     5,     5,     3,     3,
       2,     2,     1,     2,     2,     1,     2,     2,     1,     1,
       3,     2,     0,     5,     3,     1,     1,     3,     6,     1,
       1,     1,     1,     1,     1,     0,     3,     1,     4,     3,
       3,     2,     0,     5,     3,     1,     3,     3,     0,     5,
       5,     4,     3,     3,     2,     5,     2,     2,     3,     4,
       0,     3,     3,     1,     1,     1,     2,     3,     1,     3,
       4,     3,     2,     1,     3,     3,     4,     1,     1,     5,
       3,     2,     4,     3,     4,     7,     6,     0,     1,     1,
       2,     4,     4,     1,     4,     3,     3,     1,     1,     2,
       2,     3,     3,     3,     1,     4,     3,     3,     2,     1,
       1,     1,     1,     1,     2,     1,     2,     0,     3,     2,
       3,     1,     2,     0,     1,     0,     3,     1,     3,     3,
       1,     1,     1,     1,     4,     3,     3,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 128 "my_yacc.y" /* yacc.c:1646  */
    {
								for (int i = 0; i < errors.size(); i ++)										//显示程序中所有出现的错误
								{
									cout << errors[i] << endl;
								}
								cout << "\n" << "\n";
								(yyval).value = "#include<stdio.h> \n" + (yyvsp[-1]).value;
								output << (yyval).value << endl;
								cout << (yyval).value << endl;
							}
#line 1539 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 139 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no+1) + " ";
								string error = "error message: expected symbol of the end of the program!";
								errors.push_back(line + error);
								cout << "\n" << "\n";
								(yyval).value = "#include<stdio.h> \n" + (yyvsp[0]).value;
								output << (yyval).value << endl;
								cout << (yyval).value << endl;
							}
#line 1553 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 151 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-4]).value;
								add_func((yyvsp[-4]).value,"void",func_cur_node);
							}
#line 1562 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 156 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no+1) + " ";
								string error = "error message: missing ) !";
								errors.push_back(line + error);
								(yyval).value = (yyvsp[-3]).value;
								add_func((yyvsp[-3]).value,"void",func_cur_node);
							}
#line 1574 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 164 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[-3]).row_no) + " column " + int2str((yyvsp[-3]).col_no+1) + " ";
								string error = "error message: missing ( !";
								errors.push_back(line + error);
								(yyval).value = (yyvsp[-3]).value;
								add_func((yyvsp[-3]).value,"void",func_cur_node);
							}
#line 1586 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 172 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
								string error = "error message: expected content in the circles!";
								errors.push_back(line + error);
								(yyval).value = (yyvsp[-3]).value;
								add_func((yyvsp[-3]).value,"void",func_cur_node);
							}
#line 1598 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 180 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
								string error = "error message: expected content in the circles!";
								errors.push_back(line + error);
								(yyval).value = (yyvsp[-1]).value;
								add_func((yyvsp[-1]).value,"void",func_cur_node);
							}
#line 1610 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 190 "my_yacc.y" /* yacc.c:1646  */
    {
								if (is_main == 1)
								{
									(yyval).value = (yyvsp[-4]).value + (yyvsp[-3]).value + (yyvsp[-2]).value + (yyvsp[-1]).value + "\nint main()\n{\n\t" + (yyvsp[0]).value + "\n\treturn 0;\n}";
								}
								else
								{
									(yyval).value = "\n{\n\t" + (yyvsp[-4]).value + (yyvsp[-3]).value + (yyvsp[-2]).value + (yyvsp[-1]).value + (yyvsp[0]).value + "\n}";
								}
								
							}
#line 1626 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 204 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + ", " + (yyvsp[0]).value;
							}
#line 1634 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 208 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no+1) + " ";
								string error = "error message: comma error!";
								errors.push_back(line + error);
								(yyval).value = (yyvsp[-2]).value + ", " + (yyvsp[0]).value;
							}
#line 1645 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 215 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 1653 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 221 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[-1]).value == "")
								{
									(yyval).value = "\n";
								}
								else
								{	
									(yyval).value = (yyvsp[-1]).value + ";\n";
								}	
							}
#line 1668 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 232 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no+1) + " ";
								string error = "error message: expected semicolon at the end of the declaration!";
								errors.push_back(line + error);
								if ((yyvsp[0]).value == "")
								{
									(yyval).value = "\n";
								}
								else
								{	
									(yyval).value = (yyvsp[0]).value + ";\n";
								}	
							}
#line 1686 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 246 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "";	
							}
#line 1694 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 252 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[0]).value == "not exist")																			//错误：常量值未找到或未定义
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: const_variable has not been defined!";
									errors.push_back(line + error);
									(yyval).value = (yyvsp[-4]).value;
								}
								else
								{
									if (check_repeat_definition((yyvsp[-2]).value) == 0)														//重定义检查：对已定义的函数名、参数名、const、type和变量名进行查重，有重复则删除id，返回值为0表示有重复，返回值为1表示无重复
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_const((yyvsp[-2]).value,(yyvsp[0]).value,(yyvsp[0]).type);														//查重后加入常量表
									}
									if ((yyvsp[-2]).value != "")
									{
										(yyval).value = (yyvsp[-4]).value + ";\nconst " + (yyvsp[0]).type + " " + (yyvsp[-2]).value + " = " + (yyvsp[0]).value;
									}
									else
									{
										(yyval).value = (yyvsp[-4]).value;
									}
								}	
							}
#line 1729 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 283 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
								string error = "error message: using assignop when defining const!";
								errors.push_back(line + error);
								
								if ((yyvsp[0]).value == "not exist")																			//错误：常量值未找到或未定义
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: const_variable has not been defined!";
									errors.push_back(line + error);																	//保存错误信息
									(yyval).value = (yyvsp[-4]).value;
								}
								else
								{
									if (check_repeat_definition((yyvsp[-2]).value) == 0)														//重定义检查：对已定义的函数名、参数名、const、type和变量名进行查重，有重复则删除id，返回值为0表示有重复，返回值为1表示无重复
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_const((yyvsp[-2]).value,(yyvsp[0]).value,(yyvsp[0]).type);														//查重后加入常量表
									}
									if ((yyvsp[-2]).value != "")
									{
										(yyval).value = (yyvsp[-4]).value + ";\nconst " + (yyvsp[0]).type + " " + (yyvsp[-2]).value + " = " + (yyvsp[0]).value;
									}
									else
									{
										(yyval).value = (yyvsp[-4]).value;
									}
								}	
							}
#line 1768 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 318 "my_yacc.y" /* yacc.c:1646  */
    {
								func_cur_node->const_start = const_cur_pos;
								if ((yyvsp[0]).value == "not exist")																			//错误：常量值未找到或未定义
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: const_variable has not been defined!";
									errors.push_back(line + error);
									(yyval).value = "";
								}
								else
								{
									if (check_repeat_definition((yyvsp[-2]).value) == 0)														//重定义检查：对已定义的函数名、参数名、const、type和变量名进行查重，有重复则删除id，返回值为0表示有重复，返回值为1表示无重复
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_const((yyvsp[-2]).value,(yyvsp[0]).value,(yyvsp[0]).type);														//查重后加入常量表
									}
									if ((yyvsp[-2]).value != "")
									{
										(yyval).value = "const " + (yyvsp[0]).type + " " + (yyvsp[-2]).value + " = " + (yyvsp[0]).value;
									}
									else
									{
										(yyval).value = "";
									}
								}
							}
#line 1804 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 350 "my_yacc.y" /* yacc.c:1646  */
    {
								func_cur_node->const_start = const_cur_pos;
								
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
								string error = "error message: using assignop when defining const!";
								errors.push_back(line + error);
								
								if ((yyvsp[0]).value == "not exist")
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: const_variable has not been defined!";
									errors.push_back(line + error);
									(yyval).value = "";
								}
								else
								{
									if (check_repeat_definition((yyvsp[-2]).value) == 0)
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_const((yyvsp[-2]).value,(yyvsp[0]).value,(yyvsp[0]).type);
									}
									if ((yyvsp[-2]).value != "")
									{
										(yyval).value = "const " + (yyvsp[0]).type + " " + (yyvsp[-2]).value + " = " + (yyvsp[0]).value;
									}
									else
									{
										(yyval).value = "";
									}
								}
							}
#line 1845 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 389 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = get_const_value((yyvsp[0]).value);
								(yyval).type = get_const_type((yyvsp[0]).value);
							}
#line 1854 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 394 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "-" + get_const_value((yyvsp[0]).value);
								(yyval).type = get_const_type((yyvsp[0]).value);
							}
#line 1863 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 399 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = get_const_value((yyvsp[0]).value);
								(yyval).type = get_const_type((yyvsp[0]).value);
							}
#line 1872 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 404 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = "float";
							}
#line 1881 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 409 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "-" + (yyvsp[0]).value;
								(yyval).type = "float";
							}
#line 1890 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 414 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = "float";
							}
#line 1899 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 419 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = "int";
							}
#line 1908 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 424 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "-" + (yyvsp[0]).value;
								(yyval).type = "int";
							}
#line 1917 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 429 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = "int";							
							}
#line 1926 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 434 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = "char";
							}
#line 1935 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 441 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[-1]).value == "")
								{
									(yyval).value = "\n";
								}
								else
								{	
									(yyval).value = (yyvsp[-1]).value + ";\n";
								}
							}
#line 1950 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 452 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no+1) + " ";
								string error = "error message: expected semicolon at the end of the declaration!";
								errors.push_back(line + error);
								if ((yyvsp[0]).value == "")
								{
									(yyval).value = "\n";
								}
								else
								{	
									(yyval).value = (yyvsp[0]).value + ";\n";
								}
							}
#line 1968 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 466 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "";
							}
#line 1976 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 472 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[0]).value == "not exist")																
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: the type has not been defined!";
									errors.push_back(line + error);
									(yyval).value = (yyvsp[-4]).value;
								}
								else
								{
									if (check_repeat_definition((yyvsp[-2]).value) == 0)
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_typedef((yyvsp[-2]).value,(yyvsp[0]).type);														//查重后加入类型表
									}
						
									if ((yyvsp[-2]).value != "")
									{		
										(yyval).value = (yyvsp[-4]).value + ";\ntypedef " + (yyvsp[0]).value + " " + (yyvsp[-2]).value;
									}
									else
									{
										(yyval).value = (yyvsp[-4]).value;
									}
								}				
							}
#line 2012 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 504 "my_yacc.y" /* yacc.c:1646  */
    {
								func_cur_node->type_start = type_cur_pos;
								
								if ((yyvsp[0]).value == "not exist")
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: the type has not been defined!";
									errors.push_back(line + error);
									(yyval).value = "";
								}
								else
								{
									if (check_repeat_definition((yyvsp[-2]).value) == 0)
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									else
									{
										add_typedef((yyvsp[-2]).value,(yyvsp[0]).value);														//查重后加入类型表
									}
								
									if ((yyvsp[-2]).value != "")
									{
										(yyval).value = "typedef " + (yyvsp[0]).value + " " + (yyvsp[-2]).value;
									}
									else
									{
										(yyval).value = "";
									}
								}
							}
#line 2050 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 540 "my_yacc.y" /* yacc.c:1646  */
    {
								in_record = 1;																				//在var_declaration处规约时识别在record内部
							}
#line 2058 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 546 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = (yyvsp[0]).type;
							}
#line 2067 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 551 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "struct{" + (yyvsp[-1]).value + "}";
								(yyval).type = "struct";
								in_record = 0;
							}
#line 2077 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 557 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "array" + (yyvsp[0]).value + "[" + (yyvsp[-3]).value + "]";
								(yyval).type = "array" + (yyvsp[0]).type;
							}
#line 2086 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 562 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).type = get_typedef_type((yyvsp[0]).value);
								(yyval).value = (yyval).type;
							}
#line 2095 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 569 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "int";
								(yyval).type = "int";
							}
#line 2104 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 574 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "float";
								(yyval).type = "float";
							}
#line 2113 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 579 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "bool";
								(yyval).type = "bool";
							}
#line 2122 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 584 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "char";
								(yyval).type = "char";
							}
#line 2131 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 591 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 2139 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 595 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "";
							}
#line 2147 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 601 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + "," + (yyvsp[0]).value;
							}
#line 2155 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 605 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 2163 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 611 "my_yacc.y" /* yacc.c:1646  */
    {
								if (atoi((yyvsp[-3]).value.c_str()) > atoi((yyvsp[0]).value.c_str()))
								{
									string line = "line " + int2str((yyvsp[-3]).row_no) + " column " + int2str((yyvsp[-3]).col_no) + " ";
									string error = "error message: low bound is greater than up bound!";
									errors.push_back(line + error);
								}
								(yyval).value = (yyvsp[-3]).value + "|" + (yyvsp[0]).value;
							}
#line 2177 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 621 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no-1) + " ";
								string error = "error message: error in the array!";
								errors.push_back(line + error);
								(yyval).value = (yyvsp[-2]).value + "|" + (yyvsp[0]).value;
							}
#line 2188 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 630 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[-1]).value == "")
								{	
									(yyval).value = "\n";
								}
								else
								{
									(yyval).value = (yyvsp[-1]).value + ";\n";
								}
							}
#line 2203 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 641 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no+1) + " ";
								string error = "error message: expected semicolon at the end of the declaration!";
								errors.push_back(line + error);
								if ((yyvsp[0]).value == "")
								{	
									(yyval).value = "\n";
								}
								else
								{
									(yyval).value = (yyvsp[0]).value + ";\n";
								}
							}
#line 2221 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 655 "my_yacc.y" /* yacc.c:1646  */
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
								(yyval).value = "\n";
							}
#line 2238 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 670 "my_yacc.y" /* yacc.c:1646  */
    {
								int repeat = 1;
								if (in_record == 1)
								{
									if (check_in_ids((yyvsp[-2]).value) == 0)
									{
										repeat = 0;
									}
									
									string former;
									int pos = (yyvsp[-4]).value.find(" ");
									former = (yyvsp[-4]).value.substr(pos+1);
									
									string new_list;
									vector<string> ids;
									if ((yyvsp[-2]).value != "")
									{
										new_list = del_space((yyvsp[-2]).value);
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
									
									(yyvsp[-2]).value = "";
									for (int i = 0; i < ids.size(); i ++)
									{
										(yyvsp[-2]).value = (yyvsp[-2]).value + ids[i] + ", ";
									}
									(yyvsp[-2]).value = (yyvsp[-2]).value.substr(0,(yyvsp[-2]).value.length() - 2);
									if (repeat == 0)
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									
								}
								else
								{
									if (check_in_ids((yyvsp[-2]).value) == 0 || check_repeat_definition((yyvsp[-2]).value) == 0)
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}	 
									if ((yyvsp[-2]).value != "")
									{
										add_symbol((yyvsp[-2]).value, (yyvsp[0]).value);
									}
								}
													
								if ((yyvsp[-2]).value == "")
								{
									if ((yyvsp[-4]).value == "")
									{
										(yyval).value = "";
									}
									else
									{
										(yyval).value = (yyvsp[-4]).value;
									}
								}
								else
								{
									if ((yyvsp[-4]).value == "")
									{
										(yyval).value = definition_trans((yyvsp[0]).value + ":" + (yyvsp[-2]).value,false);
									}
									else
									{
										(yyval).value = (yyvsp[-4]).value + ";" + definition_trans((yyvsp[0]).value + ":" + (yyvsp[-2]).value,false);
									}				
								}
							}
#line 2329 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 757 "my_yacc.y" /* yacc.c:1646  */
    {
								int repeat = 1;
								if (in_record == 1)
								{
									if (check_in_ids((yyvsp[0]).value) == 0)
									{
										repeat = 0;
									}	
									
									string former;
									int pos = (yyvsp[-2]).value.find(" ");
									former = (yyvsp[-2]).value.substr(pos+1);
									
									string new_list;
									vector<string> ids;
									if ((yyvsp[0]).value != "")
									{
										new_list = del_space((yyvsp[0]).value);
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
									
									(yyvsp[0]).value = "";
									for (int i = 0; i < ids.size(); i ++)
									{
										(yyvsp[0]).value = (yyvsp[0]).value + ids[i] + ", ";
									}
									(yyvsp[0]).value = (yyvsp[0]).value.substr(0,(yyvsp[0]).value.length() - 2);
									
									if (repeat == 0)
									{
										string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
									
								}
								else
								{
									if (check_in_ids((yyvsp[0]).value) == 0 || check_repeat_definition((yyvsp[0]).value) == 0)
									{
										string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}		
									if ((yyvsp[0]).value != "")
									{
										add_symbol((yyvsp[0]).value, "int");
									}
								}
								
								if ((yyvsp[0]).value == "")
								{
									if ((yyvsp[-2]).value == "")
									{
										(yyval).value = "";
									}
									else
									{
										(yyval).value = (yyvsp[-2]).value;
									}
								}
								else
								{
									if ((yyvsp[-2]).value == "")
									{
										(yyval).value = definition_trans("int:" + (yyvsp[0]).value,false);
									}
									else
									{
										(yyval).value = (yyvsp[-2]).value + ";" + definition_trans("int:" + (yyvsp[0]).value,false);
									}				
								}
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
								string error = "error message: variable type missing!";
								errors.push_back(line + error);
							}
#line 2424 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 848 "my_yacc.y" /* yacc.c:1646  */
    {
								string tmp = "int";
								if (is_main == 1)
								{
									if (func_cur_node == func_head_node && time_r == 1)
									{
										add_parameter("");
										time_r = 0;
									}	
									if (check_var_declaration((yyvsp[0]).value,tmp) == 0)
									{
										string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
								}
								else
								{
									if (check_var_declaration((yyvsp[0]).value,tmp) == 0)
									{
										string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
								}
								if ((yyvsp[0]).value == "")
								{
									(yyval).value = "";
								}
								else
								{
									(yyval).value = definition_trans("int:" + (yyvsp[0]).value,false);
								}
								
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
								string error = "error message: variable type missing!";
								errors.push_back(line + error);	
							}
#line 2467 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 887 "my_yacc.y" /* yacc.c:1646  */
    {
								if (is_main == 1)
								{
									if ( func_cur_node == func_head_node && time_r == 1)
									{
										add_parameter("");
										time_r = 0;
									}
									if (check_var_declaration((yyvsp[-2]).value,(yyvsp[0]).value) == 0)
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
								}
								else
								{
									if (check_var_declaration((yyvsp[-2]).value,(yyvsp[0]).value) == 0)
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error = "error message: redefine the variable!";
										errors.push_back(line + error);
									}
								}
								if ((yyvsp[-2]).value == "")
								{
									(yyval).value = "";
								}
								else
								{
									(yyval).value = definition_trans((yyvsp[0]).value + ":" + (yyvsp[-2]).value,false);
								}
							}
#line 2505 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 923 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + "\n" + (yyvsp[-1]).value;
							}
#line 2513 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 927 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "";
							}
#line 2521 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 933 "my_yacc.y" /* yacc.c:1646  */
    {
								is_main = 1;
								(yyval).value = (yyvsp[-4]).value + "\n{\n\t" + (yyvsp[-3]).value + (yyvsp[-2]).value + (yyvsp[-1]).value + (yyvsp[0]).value + "\n}\n";
							}
#line 2530 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 940 "my_yacc.y" /* yacc.c:1646  */
    {
								redefine_type((yyvsp[-1]).value);
								(yyval).value = (yyvsp[-1]).value + " " + (yyvsp[-4]).value + (yyvsp[-3]).value;				
							}
#line 2539 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 945 "my_yacc.y" /* yacc.c:1646  */
    {
								add_parameter("");
								(yyval).value = (yyvsp[-1]).value + " " +(yyvsp[-3]).value;
							}
#line 2548 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 950 "my_yacc.y" /* yacc.c:1646  */
    {
								redefine_type("int");
								(yyval).value = "int " + (yyvsp[-2]).value + (yyvsp[-1]).value;
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
								string error = "error message: function must have a return type!";
								errors.push_back(line + error);
							}
#line 2560 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 958 "my_yacc.y" /* yacc.c:1646  */
    {
								redefine_type("void");
								(yyval).value = "void " + (yyvsp[-2]).value + (yyvsp[-1]).value;
							}
#line 2569 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 963 "my_yacc.y" /* yacc.c:1646  */
    {
								add_parameter("");
								(yyval).value = "void " + (yyvsp[-1]).value;
							}
#line 2578 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 968 "my_yacc.y" /* yacc.c:1646  */
    {
								redefine_type("void");
								(yyval).value = "void " + (yyvsp[-4]).value + (yyvsp[-3]).value;
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
								string error = "error message: a procedure doesn't have a return type!";
								errors.push_back(line + error);
							}
#line 2590 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 978 "my_yacc.y" /* yacc.c:1646  */
    {
								if (check_repeat_func((yyvsp[0]).value) == 0)
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: the name of the function has been defined before!";
									errors.push_back(line + error);
								}
								add_func((yyvsp[0]).value,"integer",func_cur_node);
								(yyval).value = (yyvsp[0]).value;
								is_main = 0;
							}
#line 2606 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 992 "my_yacc.y" /* yacc.c:1646  */
    {
								if (check_repeat_func((yyvsp[0]).value) == 0)
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: the name of the procedure has been defined before!";
									errors.push_back(line + error);
								}
								add_func((yyvsp[0]).value,"integer",func_cur_node);
								(yyval).value = (yyvsp[0]).value;
								is_main = 0;
							}
#line 2622 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1006 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "(" + (yyvsp[-1]).value + ")";
							}
#line 2630 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1010 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
								string error = "error message: unexpected semicolon!";
								errors.push_back(line + error);
								(yyval).value = "(" + (yyvsp[-2]).value + ")";
							}
#line 2641 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1017 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "";
							}
#line 2649 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1023 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[0]).value != "")
								{
									string parm = (yyvsp[0]).value;
									if ( parm.find("var+") == 0 )
									{
										parm = parm.substr(4);
									}
									add_parameter(parm);
									(yyval).value = (yyvsp[-2]).value + ", " + definition_trans((yyvsp[0]).value,true);
								}
								else
								{
									(yyval).value = (yyvsp[-2]).value;
								}
							}
#line 2670 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1040 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + ";" + (yyvsp[0]).value;
								string parm = (yyvsp[0]).value;
								if ( parm.find("var+") == 0 )
								{
									parm = parm.substr(4);
								}
								add_parameter(parm);
								string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
								string error = "error message: semicolon missing, wrong separate symbol!";
								errors.push_back(line + error);			
							}
#line 2687 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1053 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[0]).value != "")
								{
									string parm = (yyvsp[0]).value;
									if ( parm.find("var+") == 0 )
									{
										parm = parm.substr(4);
									}
									add_parameter(parm);
									(yyval).value = definition_trans((yyvsp[0]).value,true);
								}		
							}
#line 2704 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1068 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).is_var = true;
							}
#line 2713 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1073 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 2721 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1079 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "var+" + (yyvsp[0]).value;
							}
#line 2729 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1085 "my_yacc.y" /* yacc.c:1646  */
    {
								if (check_in_ids((yyvsp[-2]).value) == 0 || check_repeat_definition((yyvsp[-2]).value) == 0)
								{
									string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
									string error = "error message: redefine the variable in parameters!";
									errors.push_back(line + error);
								}
								
								if ((yyvsp[-2]).value == "")
								{
									(yyval).value = "";
								}
								else
								{
									(yyval).value = (yyvsp[0]).value + ":" + (yyvsp[-2]).value;
								}
							}
#line 2751 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1103 "my_yacc.y" /* yacc.c:1646  */
    {	
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
								string error = "error message: type missing!";
								errors.push_back(line + error);
								if (check_in_ids((yyvsp[0]).value) == 0 || check_repeat_definition((yyvsp[0]).value) == 0)
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: redefine the variable in parameters!";
									errors.push_back(line + error);
								}
								
								if ((yyvsp[0]).value == "")
								{
									(yyval).value = "";
								}
								else
								{
									(yyval).value = "int:" + (yyvsp[0]).value;
								}
							}
#line 2776 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1126 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-1]).value + "\n";
							}
#line 2784 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1130 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
								string error = "error message: unexpected semicolon!";
								errors.push_back(line + error);
								(yyval).value = (yyvsp[-2]).value + "\n";
							}
#line 2795 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1139 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + "\n\t" + (yyvsp[0]).value;
							}
#line 2803 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1143 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-1]).value + "\n\t" + (yyvsp[0]).value;
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
								string error = "error message: semicolon missing, wrong separate symbol!";
								errors.push_back(line + error);
							}
#line 2814 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1150 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 2822 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1156 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[-2]).value == "return")
								{
									(yyval).value = "return " + (yyvsp[0]).value;
								}
								if ( (yyvsp[-2]).value != "return" )
								{
									(yyval).value = (yyvsp[-2]).value + "=" + (yyvsp[0]).value + ";";
								}
								check_type_error_output((yyvsp[-2]).type,(yyvsp[0]).type,(yyvsp[-2]).row_no,(yyvsp[-2]).col_no,(yyvsp[0]).row_no,(yyvsp[0]).col_no);
							}
#line 2838 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1168 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[-2]).value == "return")
								{
									(yyval).value = "return " + (yyvsp[0]).value;
								}
								if ( (yyvsp[-2]).value != "return" )
								{
									(yyval).value = (yyvsp[-2]).value + "=" + (yyvsp[0]).value + ";";
								}
								check_type_error_output((yyvsp[-2]).type, (yyvsp[0]).type, (yyvsp[-2]).row_no, (yyvsp[-2]).col_no, (yyvsp[0]).row_no, (yyvsp[0]).col_no);
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
								string error =  "error message: assignrelop is wrong!";
								errors.push_back(line + error);
							}
#line 2857 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1183 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[-3]).value == "return")
								{
									(yyval).value = "return " + (yyvsp[-1]).value;
								}
								else
								{
									(yyval).value = (yyvsp[-3]).value + "=" + (yyvsp[-1]).value + ";";
								}
								check_type_error_output((yyvsp[-3]).type, (yyvsp[-1]).type, (yyvsp[-3]).row_no, (yyvsp[-3]).col_no, (yyvsp[-1]).row_no, (yyvsp[-1]).col_no);
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
								string error =  "error message: too many symbols before '=' !";
								errors.push_back(line + error);
							}
#line 2876 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1198 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value + ";";
							}
#line 2884 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1202 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 2892 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1206 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "if(" + (yyvsp[-3]).value + ")" + "\n\t{\n\t\t" + (yyvsp[-1]).value  + "\n\t}\n" + (yyvsp[0]).value;
								if (!((yyvsp[-3]).type == "bool" || (yyvsp[-3]).type == "constbool"))
								{
									string line = "line " + int2str((yyvsp[-3]).row_no) + " column " + int2str((yyvsp[-3]).col_no) + " ";
									string error = "error message: the if expression is not bool!";
									errors.push_back(line + error);
								}
							}
#line 2906 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1216 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "switch(" + (yyvsp[-2]).value + "){\n" + (yyvsp[-1]).value + "}\n";
							}
#line 2914 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1220 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no+1) + " ";
								string error = "error message: end is missing here!";
								errors.push_back(line + error);
								(yyval).value = "switch(" + (yyvsp[-1]).value + "){\n" + (yyvsp[0]).value + "}\n";
							}
#line 2925 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1227 "my_yacc.y" /* yacc.c:1646  */
    {
								if (!((yyvsp[-2]).type == "bool" || (yyvsp[-2]).type == "constbool"))
								{
									string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
									string error = "error message: the while expression is not bool!";
									errors.push_back(line + error);
								}
								(yyval).value = (yyvsp[-3]).value + "(" + (yyvsp[-2]).value + ")\n\t{\n\t\t" + (yyvsp[0]).value + "\n\t}\n";
							}
#line 2939 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1237 "my_yacc.y" /* yacc.c:1646  */
    {
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
								string error =  "error message: must have a do in the while statement!";
								errors.push_back(line + error);
								if (!((yyvsp[-1]).type == "bool" || (yyvsp[-1]).type == "constbool"))
								{
									string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
									string error = "error message: the while expression is not bool!";
									errors.push_back(line + error);
								}
								(yyval).value = (yyvsp[-2]).value + "(" + (yyvsp[-1]).value + ")\n\t{\n\t\t" + (yyvsp[0]).value + "\n\t}\n";
							}
#line 2956 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1250 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "do{\n" + (yyvsp[-2]).value + "}while(" + (yyvsp[0]).value + ")\n";
							}
#line 2964 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1254 "my_yacc.y" /* yacc.c:1646  */
    {
								check_type_error_output((yyvsp[-5]).type, (yyvsp[-3]).type, (yyvsp[-5]).row_no, (yyvsp[-5]).col_no, (yyvsp[-3]).row_no, (yyvsp[-3]).col_no);
								check_type_error_output((yyvsp[-5]).type, (yyvsp[-1]).type, (yyvsp[-5]).row_no, (yyvsp[-5]).col_no, (yyvsp[-1]).row_no, (yyvsp[-1]).col_no);
								if((yyvsp[-3]).value == "to")
								{
									(yyval).value = "for(" + (yyvsp[-6]).value + "=" + (yyvsp[-4]).value + ";" + (yyvsp[-6]).value + "<=" + (yyvsp[-2]).value + ";" + (yyvsp[-6]).value + "++){\n" + (yyvsp[-1]).value + "}\n";
								}
                              	else
								{
									(yyval).value = "for(" + (yyvsp[-6]).value + "=" + (yyvsp[-4]).value + ";" + (yyvsp[-6]).value + ">=" + (yyvsp[-2]).value + ";" + (yyvsp[-6]).value + "--){\n" + (yyvsp[-1]).value + "}\n";
                                }
							}
#line 2981 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1267 "my_yacc.y" /* yacc.c:1646  */
    {
								check_type_error_output((yyvsp[-5]).type, (yyvsp[-3]).type, (yyvsp[-5]).row_no, (yyvsp[-5]).col_no, (yyvsp[-3]).row_no, (yyvsp[-3]).col_no);
								check_type_error_output((yyvsp[-5]).type, (yyvsp[-1]).type, (yyvsp[-5]).row_no, (yyvsp[-5]).col_no, (yyvsp[-1]).row_no, (yyvsp[-1]).col_no);
								string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no+1) + " ";
								string error =  "error message: must have do in the for statement!";
								errors.push_back(line + error);
								if((yyvsp[-2]).value == "to")
								{
									(yyval).value = "for(" + (yyvsp[-5]).value + "=" + (yyvsp[-3]).value + ";" + (yyvsp[-5]).value + "<=" + (yyvsp[-1]).value + ";" + (yyvsp[-5]).value + "++){\n" + (yyvsp[0]).value + "}\n";
								}
                              	else
								{
									(yyval).value = "for(" + (yyvsp[-5]).value + "=" + (yyvsp[-3]).value + ";" + (yyvsp[-5]).value + ">=" + (yyvsp[-1]).value + ";" + (yyvsp[-5]).value + "--){\n" + (yyvsp[0]).value + "}\n";
                                }
							}
#line 3001 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1283 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "";
							}
#line 3009 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1287 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 3017 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1291 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 3025 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1297 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = find_local_var_func_type((yyvsp[0]).value,"");
							}
#line 3034 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1304 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = write_trans((yyvsp[-1]).value,(yyvsp[-1]).type,(yyvsp[-1]).row_no,(yyvsp[-1]).col_no);
								dim = 0;
							}
#line 3043 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1309 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = writeln_trans((yyvsp[-1]).value,(yyvsp[-1]).type,(yyvsp[-1]).row_no,(yyvsp[-1]).col_no);
								dim = 0;
							}
#line 3052 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1314 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "printf(\"\\n\")";
							}
#line 3060 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1321 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = read_trans((yyvsp[-1]).value,(yyvsp[-1]).type,(yyvsp[-1]).row_no,(yyvsp[-1]).col_no);					
							}
#line 3068 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1327 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).type = (yyvsp[-1]).type;
								cur_case_type = (yyvsp[-1]).type;
								(yyval).value = (yyvsp[-1]).value;
							}
#line 3078 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1335 "my_yacc.y" /* yacc.c:1646  */
    {
								if ( (yyvsp[-2]).type == "float" && (yyvsp[0]).type == "float" || (yyvsp[-2]).type == "float" && (yyvsp[0]).type == "int" || (yyvsp[-2]).type == "int" && 
								     (yyvsp[0]).type == "int" || (yyvsp[-2]).type == "float" && (yyvsp[0]).type == "int" || (yyvsp[-2]).type == "char" && (yyvsp[0]).type == "char")
								{	
									(yyval).type = "bool";
								}
								else if ((yyvsp[-2]).type == "bool" && (yyvsp[0]).type == "bool")
								{
									if ((yyvsp[-1]).value == "=")
									{
										(yyval).type = "bool";
									}
									else
									{
										string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
										string error =  "error message: invalid relop between bools!";
										errors.push_back(line + error);
										(yyval).type = "NULL";
									}
								}
								else
								{
									string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
									string error =  "error message: invalid relop between expressions!";
									errors.push_back(line + error);
									(yyval).type = "NULL";
								}
								(yyval).value = (yyvsp[-2]).value + (yyvsp[-1]).value + (yyvsp[0]).value;
							}
#line 3112 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1365 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = (yyvsp[0]).type;
							}
#line 3121 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1372 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = (yyvsp[0]).type;
							}
#line 3130 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1377 "my_yacc.y" /* yacc.c:1646  */
    {
								if ( (yyvsp[0]).type == "int" || (yyvsp[0]).type == "float" )
									(yyval).type = (yyvsp[0]).type;
								else
									(yyval).type = "NULL";
								(yyval).value = (yyvsp[-1]).value + (yyvsp[0]).value;
							}
#line 3142 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1385 "my_yacc.y" /* yacc.c:1646  */
    {
								if ( (yyvsp[0]).type == "int" || (yyvsp[0]).type == "float" )
									(yyval).type = (yyvsp[0]).type;
								else
									(yyval).type = "NULL";
								(yyval).value = (yyvsp[-1]).value + (yyvsp[0]).value;
							}
#line 3154 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1393 "my_yacc.y" /* yacc.c:1646  */
    {
								if ( (yyvsp[-1]).value == "or" )
								{
									(yyvsp[-1]).value = "||";
								}
								(yyval).value = (yyvsp[-2]).value + (yyvsp[-1]).value + (yyvsp[0]).value;
								(yyval).type = combine_type((yyvsp[-2]).type, (yyvsp[0]).type);
							}
#line 3167 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1402 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + (yyvsp[-1]).value + (yyvsp[0]).value;
								(yyval).type = combine_type((yyvsp[-2]).type, (yyvsp[0]).type);
							}
#line 3176 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1409 "my_yacc.y" /* yacc.c:1646  */
    {
								if (((yyvsp[-1]).value == "/" || (yyvsp[-1]).value == "div" || (yyvsp[-1]).value == "mod")&& (yyvsp[0]).value == "0")
								{									
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: the divisor can not be 0";
									errors.push_back(line + error);
								}
								if ( (yyvsp[-1]).value == "and" )
								{
									if ( !((yyvsp[-2]).type == "bool" || (yyvsp[-2]).type == "constbool") && ( (yyvsp[0]).type == "bool" || (yyvsp[0]).type == "constbool") )
									{
										string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
										string error = "error message: type is not bool on either side of and operator";
										errors.push_back(line + error);
									}
								}
								if ( (yyvsp[-1]).value == "mod" )
									(yyvsp[-1]).value = "%";
								if ( (yyvsp[-1]).value == "and" )
									(yyvsp[-1]).value = "&&";
								if ( (yyvsp[-1]).value == "div" )
									(yyvsp[-1]).value = "/";
								(yyval).value = (yyvsp[-2]).value + (yyvsp[-1]).value + (yyvsp[0]).value;  
								(yyval).type = combine_type((yyvsp[-2]).type, (yyvsp[0]).type);
							}
#line 3206 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1435 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = (yyvsp[0]).type;
							}
#line 3215 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1442 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-3]).value + "(" + (yyvsp[-1]).value + ")";
								if ( param_type_check((yyvsp[-3]).value, (yyvsp[-1]).type) != 0 )
								{
									(yyval).type = find_func_type((yyvsp[-3]).value);
									if ( (yyval).type == "NULL" )
									{
										string line = "line " + int2str((yyvsp[-3]).row_no) + " column " + int2str((yyvsp[-3]).col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								else
								{
									string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
									string error =  "error message: check your parameter numbers or types!";
									errors.push_back(line + error);
									(yyval).type = find_func_type((yyvsp[-3]).value);
									if ( (yyval).type == "NULL" )
									{
										string line = "line " + int2str((yyvsp[-3]).row_no) + " column " + int2str((yyvsp[-3]).col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								dim = 0;
							}
#line 3247 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1470 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + "()";
								(yyval).type = find_func_type((yyvsp[-2]).value);
								if (call_procedure_id_check((yyvsp[-2]).value)->symbol_list->parameters == NULL)
								{
									string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no+1) + " ";
									string error = "error message: unexpected circles!";
									errors.push_back(line + error);
								}
								else
								{
									string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no+1) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
								}
								
								dim = 0;
							}
#line 3270 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1489 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "(" + (yyvsp[-1]).value + ")";
								(yyval).type = (yyvsp[-1]).type;
							}
#line 3279 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1494 "my_yacc.y" /* yacc.c:1646  */
    {
								if ( (yyvsp[0]).type == "bool" )
								{
									(yyval).value = "!" + (yyvsp[0]).value;
									(yyval).type = "bool";
								}
								else
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: factor not bool type";
									errors.push_back(line + error);
									(yyval).value = "!" + (yyvsp[0]).value;
									(yyval).type = "NULL";
								}
							}
#line 3299 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1510 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = (yyvsp[0]).type;
							}
#line 3308 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1515 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).type = (yyvsp[0]).type;
								(yyval).value = (yyvsp[0]).value;
							}
#line 3317 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1522 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = "float";
							}
#line 3326 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1527 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = "int";
							}
#line 3335 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1532 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = "char";
							}
#line 3344 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1539 "my_yacc.y" /* yacc.c:1646  */
    {
								string name = (yyvsp[-1]).value;
								if ( name.find("return") == 0 )
								{
									name = name.substr(6);
									(yyvsp[-1]).value = (yyvsp[-1]).value.substr(0, 6);
								}
								string result = "";
								if ( recover == 1 )
									(yyval).type = find_local_var_func_type(name, "array"+(yyvsp[0]).value);
								if ( recover == 2 )
									(yyval).type = find_local_var_func_type(name, "struct"+(yyvsp[0]).value);
								if ( recover == 0 )
									(yyval).type = find_local_var_func_type(name, (yyvsp[0]).value);
								recover = 0;	
								if ( (yyvsp[0]).value != "" )
								{
									if ( (yyvsp[0]).value.find("[") != -1 )
									{
										(yyvsp[0]).value = (yyvsp[0]).value.substr(1);
										(yyvsp[0]).value = (yyvsp[0]).value.substr(0,(yyvsp[0]).value.length() - 1);
										vector<string> cons = split((yyvsp[0]).value,",");

										for (int i = 0; i < cons.size(); i ++)
										{
											result = result + "[" + cons[i] + "]";
										}
									}
									else if ( (yyvsp[0]).value.find(".") != -1)
									{
										 result = (yyvsp[0]).value;
									}
								}
								(yyval).value = (yyvsp[-1]).value + result;
							}
#line 3384 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1577 "my_yacc.y" /* yacc.c:1646  */
    {
								if (func_cur_node->name == (yyvsp[0]).value)
								{
									(yyval).value = "return" + (yyvsp[0]).value;
								}
								else
								{
									(yyval).value = (yyvsp[0]).value;
								}
								array_id = (yyvsp[0]).value;
							}
#line 3400 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1590 "my_yacc.y" /* yacc.c:1646  */
    {
								if ((yyvsp[0]).value.find("array") == 0)
								{
									(yyvsp[0]).value = (yyvsp[0]).value.substr(5);
									recover = 1;
								}
								
								if ((yyvsp[0]).value.find("struct") == 0)
								{
									(yyvsp[0]).value = "." + (yyvsp[0]).value.substr(6);
									recover = 2;
								}
								(yyval).value = (yyvsp[-1]).value + (yyvsp[0]).value;		
							}
#line 3419 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1605 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "";
							}
#line 3427 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1611 "my_yacc.y" /* yacc.c:1646  */
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
									vector<string> nums = split((yyvsp[-1]).value, ",");
									
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
												string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
												string error =  "error message: out of bounds in the array!";
												errors.push_back(line + error);
											}
											newnums.push_back(int2str(num-low));
										}
									}
									if ( dim != dimns.size() ) valid = 0;
									if ( valid == 0 )
									{
										string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
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
								(yyval).value = "array[" + new_exp + "]";
								dim = 0;
							}
#line 3482 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1662 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "struct" + (yyvsp[0]).value;
							}
#line 3490 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1668 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + "," + (yyvsp[0]).value;
								(yyval).type = (yyvsp[-2]).type + "*" + (yyvsp[0]).type;
							}
#line 3499 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1673 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = (yyvsp[0]).type;
							}
#line 3508 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1680 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "\telse\n\t{\n\t\t" + (yyvsp[0]).value + "\n\t}\n";
							}
#line 3516 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1684 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "";
							}
#line 3524 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1690 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								branches.clear();
							}
#line 3533 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1695 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = "";
							}
#line 3541 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1701 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + (yyvsp[0]).value;
							}
#line 3549 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1705 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 3557 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1711 "my_yacc.y" /* yacc.c:1646  */
    {
								vector<string> cases;
								int error1 = 0;
								(yyval).value = "";
								cases = split((yyvsp[-2]).value,",");
								for ( int i = 0; i < cases.size(); i++ )
								{
									if( nums.size() == 0 && branches.size() == 0 )
									{
										nums.push_back(cases[i]);
										branches.push_back((yyvsp[0]).value);
										(yyval).value = (yyval).value + "case " + cases[i] + ":" + (yyvsp[0]).value + "break;\n";
									}
									else
									{
										for ( int j = 0; j < nums.size(); j++ )
										{
											if ( nums[j] == cases[i] )
											{
												string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
												string error =  "error message: branches conflict!";
												errors.push_back(line + error);
												error1 = 1;
											}
										}
										if ( error1 == 0 )
										{
											nums.push_back(cases[i]);
											branches.push_back((yyvsp[0]).value);
											(yyval).value = (yyval).value + "case " + cases[i] + ":" + (yyvsp[0]).value + "break;\n";
										}
									}
									error1 = 0;
								}
							}
#line 3597 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1749 "my_yacc.y" /* yacc.c:1646  */
    {
								int error = 0;
								if ( (yyvsp[0]).type != cur_case_type )
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error =  "error message: const type not matched with case type!";
									errors.push_back(line + error);
								}
								(yyval).value = (yyvsp[-2]).value + "," + (yyvsp[0]).value;
							}
#line 3612 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1760 "my_yacc.y" /* yacc.c:1646  */
    {
								int error = 0;
								if ( (yyvsp[0]).type != cur_case_type )
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error =  "error message: const type not matched with case type!";
									errors.push_back(line + error);
								}
								(yyval).value = (yyvsp[0]).value;
							}
#line 3627 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1773 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 3635 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1777 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
							}
#line 3643 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1783 "my_yacc.y" /* yacc.c:1646  */
    {
								if ( call_procedure_id_check((yyvsp[0]).value) != NULL )
								{
									(yyval).type = find_func_type((yyvsp[0]).value);
									if ( (yyval).type != "void")
									{
										string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
										string error =  "error message: can not call a function directly in a statement!";
										errors.push_back(line + error);
									}
								}
								else
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error =  "error message: the function is not found!";
									errors.push_back(line + error);
									(yyval).type = "NULL";
								}
								(yyval).value = (yyvsp[0]).value + "()";
							}
#line 3668 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1804 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-3]).value + "(" + (yyvsp[-1]).value + ")";
								if ( param_type_check((yyvsp[-3]).value, (yyvsp[-1]).type) == 1 )
								{
									(yyval).type = find_func_type((yyvsp[-3]).value);
									if ( (yyval).type == "NULL" )
									{
										string line = "line " + int2str((yyvsp[-3]).row_no) + " column " + int2str((yyvsp[-3]).col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								else if ( param_type_check((yyvsp[-3]).value, (yyvsp[-1]).type) == -1 ) 
								{
									string line = "line " + int2str((yyvsp[-3]).row_no) + " column " + int2str((yyvsp[-3]).col_no) + " ";
									string error =  "error message: the function does not found!";
									errors.push_back(line + error);
									(yyval).type = "NULL";
								}
								else
								{
									string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
									(yyval).type = "NULL";
								}
								dim = 0;
							}
#line 3701 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1833 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + "(" + (yyvsp[-1]).value + ")";
								if ( param_type_check((yyvsp[-2]).value, (yyvsp[0]).type) == 1 )
								{
									(yyval).type = find_func_type((yyvsp[-2]).value);
									if ( (yyval).type == "NULL" )
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								else if ( param_type_check((yyvsp[-2]).value, (yyvsp[0]).type) == -1 ) 
								{
									string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
									string error = "error message: the function does not found!";
									errors.push_back(line + error);
									(yyval).type = "NULL";
								}
								else
								{
									string line = "line " + int2str((yyvsp[-1]).row_no) + " column " + int2str((yyvsp[-1]).col_no) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
									(yyval).type = "NULL";
								}
								string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no+1) + " ";
								string error = "error message: leftcircle is missing!";
								errors.push_back(line + error);
								dim = 0;
							}
#line 3737 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1865 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + "(" + (yyvsp[0]).value + ")";
								if ( param_type_check((yyvsp[-2]).value, (yyvsp[0]).type) == 1 )
								{
									(yyval).type = find_func_type((yyvsp[-2]).value);
									if ( (yyval).type == "NULL" )
									{
										string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
										string error =  "error message: function name not valid in the context!";
										errors.push_back(line + error);
									}
								}
								else if ( param_type_check((yyvsp[-2]).value, (yyvsp[0]).type) == -1 ) 
								{
									string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no) + " ";
									string error = "error message: the function does not found!";
									errors.push_back(line + error);
									(yyval).type = "NULL";
								}
								else
								{
									string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
									(yyval).type = "NULL";
								}
								string line = "line " + int2str((yyvsp[0]).row_no) + " column " + int2str((yyvsp[0]).col_no+1) + " ";
								string error = "error message: rightcircle is missing!";
								errors.push_back(line + error);
								dim = 0;
							}
#line 3773 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1897 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + "()";
								if (call_procedure_id_check((yyvsp[-2]).value)->symbol_list->parameters == NULL)
								{
									string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no+1) + " ";
									string error = "error message: unexpected circles!";
									errors.push_back(line + error);
								}
								else
								{
									string line = "line " + int2str((yyvsp[-2]).row_no) + " column " + int2str((yyvsp[-2]).col_no+1) + " ";
									string error = "error message: the parameters unmatched!";
									errors.push_back(line + error);
								}
								
								dim = 0;
							}
#line 3795 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1918 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[-2]).value + "," + (yyvsp[0]).value;
								(yyval).type = (yyvsp[-2]).type + "*" + (yyvsp[0]).type;
								dim ++;
							}
#line 3805 "my_yacc.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1924 "my_yacc.y" /* yacc.c:1646  */
    {
								(yyval).value = (yyvsp[0]).value;
								(yyval).type = (yyvsp[0]).type;
								dim++;
							}
#line 3815 "my_yacc.tab.c" /* yacc.c:1646  */
    break;


#line 3819 "my_yacc.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1932 "my_yacc.y" /* yacc.c:1906  */

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
