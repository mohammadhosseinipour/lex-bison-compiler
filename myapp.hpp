
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DOT = 258,
     SINGLE = 259,
     SC = 260,
     COMMA = 261,
     LETTER = 262,
     OPBRACE = 263,
     CLBRACE = 264,
     CONTINUE = 265,
     BREAK = 266,
     IF = 267,
     ELSE = 268,
     FOR = 269,
     WHILE = 270,
     POW = 271,
     OPEN = 272,
     CLOSE = 273,
     COMMENT = 274,
     SQ_OPEN = 275,
     SQ_CLOSE = 276,
     INT = 277,
     FLOAT = 278,
     CHAR = 279,
     ID = 280,
     NUM = 281,
     PLUS = 282,
     MINUS = 283,
     MULT = 284,
     DIV = 285,
     AND = 286,
     OR = 287,
     LESS = 288,
     GREAT = 289,
     LESEQ = 290,
     GRTEQ = 291,
     NOTEQ = 292,
     EQEQ = 293,
     ASSIGN = 294,
     SPLUS = 295,
     SMINUS = 296,
     SMULT = 297,
     SDIV = 298,
     INC = 299,
     DEC = 300,
     SWITCH = 301,
     MAIN = 302,
     RETURN = 303,
     DEFAULT = 304,
     CASE = 305,
     COLON = 306
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 559 "hisbison.y"
char* var_type; char* text; struct AST *node; struct attributes{
	char* code; 
	char* optimized_code;
	char* true1;
	char* false1;
	char* next_lab;
	char* next;
	char* addr;
	float val;
	int is_dig;
}A;


/* Line 1676 of yacc.c  */
#line 117 "myapp.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


