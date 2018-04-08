/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
