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
    L_STRING = 258,
    L_NUMBER = 259,
    L_REAL = 260,
    L_BASIC_TYPE = 261,
    L_TYPE_MODIFIER = 262,
    L_DEFINED_NAME = 263,
    L_IDENTIFIER = 264,
    L_DEFINED_CLASS = 265,
    L_EFUN = 266,
    L_INC = 267,
    L_DEC = 268,
    L_ASSIGN = 269,
    L_LAND = 270,
    L_LOR = 271,
    L_LSH = 272,
    L_RSH = 273,
    L_ORDER = 274,
    L_NOT = 275,
    L_IF = 276,
    L_ELSE = 277,
    L_SWITCH = 278,
    L_CASE = 279,
    L_DEFAULT = 280,
    L_RANGE = 281,
    L_DOT_DOT_DOT = 282,
    L_WHILE = 283,
    L_DO = 284,
    L_FOR = 285,
    L_FOREACH = 286,
    L_IN = 287,
    L_BREAK = 288,
    L_CONTINUE = 289,
    L_RETURN = 290,
    L_ARROW = 291,
    L_INHERIT = 292,
    L_COLON_COLON = 293,
    L_ARRAY_OPEN = 294,
    L_MAPPING_OPEN = 295,
    L_FUNCTION_OPEN = 296,
    L_NEW_FUNCTION_OPEN = 297,
    L_SSCANF = 298,
    L_CATCH = 299,
    L_TIME_EXPRESSION = 300,
    L_CLASS = 301,
    L_NEW = 302,
    L_PARAMETER = 303,
    L_DOT = 304,
    LOWER_THAN_ELSE = 305,
    LOWER_THAN_ASSIGN = 306,
    L_EQ = 307,
    L_NE = 308
  };
#endif
/* Tokens.  */
#define L_STRING 258
#define L_NUMBER 259
#define L_REAL 260
#define L_BASIC_TYPE 261
#define L_TYPE_MODIFIER 262
#define L_DEFINED_NAME 263
#define L_IDENTIFIER 264
#define L_DEFINED_CLASS 265
#define L_EFUN 266
#define L_INC 267
#define L_DEC 268
#define L_ASSIGN 269
#define L_LAND 270
#define L_LOR 271
#define L_LSH 272
#define L_RSH 273
#define L_ORDER 274
#define L_NOT 275
#define L_IF 276
#define L_ELSE 277
#define L_SWITCH 278
#define L_CASE 279
#define L_DEFAULT 280
#define L_RANGE 281
#define L_DOT_DOT_DOT 282
#define L_WHILE 283
#define L_DO 284
#define L_FOR 285
#define L_FOREACH 286
#define L_IN 287
#define L_BREAK 288
#define L_CONTINUE 289
#define L_RETURN 290
#define L_ARROW 291
#define L_INHERIT 292
#define L_COLON_COLON 293
#define L_ARRAY_OPEN 294
#define L_MAPPING_OPEN 295
#define L_FUNCTION_OPEN 296
#define L_NEW_FUNCTION_OPEN 297
#define L_SSCANF 298
#define L_CATCH 299
#define L_TIME_EXPRESSION 300
#define L_CLASS 301
#define L_NEW 302
#define L_PARAMETER 303
#define L_DOT 304
#define LOWER_THAN_ELSE 305
#define LOWER_THAN_ASSIGN 306
#define L_EQ 307
#define L_NE 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{


    POINTER_INT pointer_int;
    int number;
    float real;
    char *string;
    int type;
    struct { short num_arg; char flags; } argument;
    ident_hash_elem_t *ihe;
    parse_node_t *node;
    function_context_t *contextp;
    struct {
	parse_node_t *node;
        char num;
    } decl; /* 5 */
    struct {
	char num_local;
	char max_num_locals;
	short context;
	short save_current_type;
	short save_exact_types;
    } func_block; /* 8 */


};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
