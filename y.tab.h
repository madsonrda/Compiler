/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    AND = 258,
    ATTRIB = 259,
    EQUALEQUAL = 260,
    END = 261,
    ELSE = 262,
    EQUALTIL = 263,
    GE = 264,
    GT = 265,
    IF = 266,
    LE = 267,
    LPAREN = 268,
    LT = 269,
    LOCAL = 270,
    MINUS = 271,
    NOT = 272,
    NOTEQUAL = 273,
    OR = 274,
    EQUAL = 275,
    PLUS = 276,
    RPAREN = 277,
    SEMICOLON = 278,
    SLASH = 279,
    STAR = 280,
    THEN = 281,
    WHILE = 282,
    VAR = 283,
    PRINT = 284,
    DO = 285,
    STMT = 286,
    DIGSEQ = 287,
    TRUE = 288,
    FALSE = 289,
    NIL = 290,
    CHARACTER_STRING = 291,
    IDENTIFIER = 292,
    IFX = 293,
    UMINUS = 294
  };
#endif
/* Tokens.  */
#define AND 258
#define ATTRIB 259
#define EQUALEQUAL 260
#define END 261
#define ELSE 262
#define EQUALTIL 263
#define GE 264
#define GT 265
#define IF 266
#define LE 267
#define LPAREN 268
#define LT 269
#define LOCAL 270
#define MINUS 271
#define NOT 272
#define NOTEQUAL 273
#define OR 274
#define EQUAL 275
#define PLUS 276
#define RPAREN 277
#define SEMICOLON 278
#define SLASH 279
#define STAR 280
#define THEN 281
#define WHILE 282
#define VAR 283
#define PRINT 284
#define DO 285
#define STMT 286
#define DIGSEQ 287
#define TRUE 288
#define FALSE 289
#define NIL 290
#define CHARACTER_STRING 291
#define IDENTIFIER 292
#define IFX 293
#define UMINUS 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 35 "parser.y" /* yacc.c:1909  */

    int inteiros;                 
    char identificadores[20];               
    astNode *ASTPonteiro;             

#line 138 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
