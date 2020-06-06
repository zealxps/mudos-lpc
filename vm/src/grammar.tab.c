/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */



#include "std.h"
#include "compiler.h"
#include "lex.h"
#include "scratchpad.h"

#include "lpc_incl.h"
#include "simul_efun.h"
#include "generate.h"

#line 13 "grammar/grammar.y.pre"
/*
 * This is the grammar definition of LPC, and its parse tree generator.
 */

/* down to one global :)
   bits:
      SWITCH_CONTEXT     - we're inside a switch
      LOOP_CONTEXT       - we're inside a loop
      SWITCH_STRINGS     - a string case has been found
      SWITCH_NUMBERS     - a non-zero numeric case has been found
      SWITCH_RANGES      - a range has been found
      SWITCH_DEFAULT     - a default has been found
 */
int context;

/*
 * bison & yacc don't prototype this in y.tab.h
 */
int yyparse (void);




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
   by #include "y.tab.h".  */
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

/* Copy the second part of user declarations.  */



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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1771

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  246
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  452

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    73,    63,    56,     2,
      67,    68,    62,    60,    70,    61,     2,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    66,
      59,    52,     2,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    74,     2,    75,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,    54,    72,    65,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   204,   204,   208,   209,   213,   218,   223,   266,   274,
     283,   287,   295,   300,   308,   313,   321,   326,   331,   350,
     330,   402,   408,   409,   410,   413,   421,   432,   433,   436,
     438,   443,   442,   497,   517,   518,   522,   523,   541,   542,
     562,   566,   574,   583,   597,   602,   603,   617,   623,   634,
     638,   646,   655,   657,   664,   665,   669,   677,   718,   717,
     731,   731,   731,   735,   741,   740,   762,   769,   798,   810,
     837,   843,   855,   859,   866,   874,   879,   880,   881,   882,
     883,   884,   890,   895,   920,   931,   930,   954,   963,   962,
     978,   977,   993,   992,  1018,  1039,  1045,  1063,  1069,  1079,
    1078,  1100,  1104,  1108,  1114,  1124,  1123,  1157,  1164,  1172,
    1180,  1188,  1203,  1220,  1231,  1248,  1253,  1258,  1263,  1268,
    1273,  1282,  1287,  1292,  1297,  1302,  1307,  1312,  1317,  1322,
    1327,  1332,  1337,  1342,  1350,  1355,  1363,  1472,  1518,  1524,
    1549,  1556,  1563,  1570,  1575,  1599,  1622,  1637,  1682,  1720,
    1725,  1730,  1880,  1975,  2056,  2061,  2157,  2179,  2202,  2212,
    2224,  2249,  2272,  2294,  2326,  2327,  2328,  2329,  2330,  2334,
    2341,  2363,  2367,  2372,  2380,  2385,  2393,  2400,  2414,  2419,
    2424,  2432,  2443,  2462,  2469,  2470,  2539,  2556,  2562,  2561,
    2593,  2607,  2615,  2620,  2628,  2636,  2641,  2646,  2690,  2755,
    2756,  2761,  2764,  2763,  2773,  2778,  2782,  2787,  2796,  2795,
    2810,  2821,  2820,  2836,  2842,  2857,  2866,  2867,  2872,  2880,
    2881,  2890,  2894,  2905,  2911,  2921,  2926,  2957,  2975,  3061,
    3124,  3153,  3180,  3202,  3233,  3234,  3249,  3265,  3281,  3316,
    3321,  3330,  3349,  3348,  3360,  3365,  3364
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "L_STRING", "L_NUMBER", "L_REAL",
  "L_BASIC_TYPE", "L_TYPE_MODIFIER", "L_DEFINED_NAME", "L_IDENTIFIER",
  "L_DEFINED_CLASS", "L_EFUN", "L_INC", "L_DEC", "L_ASSIGN", "L_LAND",
  "L_LOR", "L_LSH", "L_RSH", "L_ORDER", "L_NOT", "L_IF", "L_ELSE",
  "L_SWITCH", "L_CASE", "L_DEFAULT", "L_RANGE", "L_DOT_DOT_DOT", "L_WHILE",
  "L_DO", "L_FOR", "L_FOREACH", "L_IN", "L_BREAK", "L_CONTINUE",
  "L_RETURN", "L_ARROW", "L_INHERIT", "L_COLON_COLON", "L_ARRAY_OPEN",
  "L_MAPPING_OPEN", "L_FUNCTION_OPEN", "L_NEW_FUNCTION_OPEN", "L_SSCANF",
  "L_CATCH", "L_TIME_EXPRESSION", "L_CLASS", "L_NEW", "L_PARAMETER",
  "L_DOT", "LOWER_THAN_ELSE", "LOWER_THAN_ASSIGN", "'='", "'?'", "'|'",
  "'^'", "'&'", "L_EQ", "L_NE", "'<'", "'+'", "'-'", "'*'", "'%'", "'/'",
  "'~'", "';'", "'('", "')'", "':'", "','", "'{'", "'}'", "'$'", "'['",
  "']'", "$accept", "all", "program", "possible_semi_colon", "inheritance",
  "real", "number", "optional_star", "block_or_semi", "identifier", "def",
  "$@1", "@2", "modifier_change", "member_name", "member_name_list",
  "member_list", "class_decl", "@3", "defined_class_decl", "type_decl",
  "new_local_name", "atomic_type", "basic_type", "new_arg", "argument",
  "argument_list", "type_modifier_list", "type", "opt_basic_type",
  "name_list", "new_name", "block", "$@4", "decl_block",
  "local_declarations", "$@5", "new_local_def", "single_new_local_def",
  "single_new_local_def_with_init", "local_name_list", "statements",
  "statement", "$@6", "block_or_statement", "while", "$@7", "do", "$@8",
  "for", "$@9", "foreach_var", "foreach_vars", "foreach", "$@10",
  "for_expr", "first_for_expr", "switch", "$@11", "switch_block", "case",
  "case_label", "constant", "comma_expr", "lvalue", "expr0", "return",
  "expr_list", "expr_list_node", "expr_list2", "expr_list3", "expr_list4",
  "assoc_pair", "expr4", "@12", "$@13", "expr_or_block", "catch", "@14",
  "sscanf", "time_expression", "@15", "lvalue_list", "string",
  "string_con1", "string_con2", "class_init", "opt_class_init",
  "function_call", "efun_override", "function_name", "cond",
  "optional_else_part", "base_statement", "def_function_block", "$@16",
  "new_function_value", "@17", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,    61,    63,   124,    94,    38,   307,   308,    60,
      43,    45,    42,    37,    47,   126,    59,    40,    41,    58,
      44,   123,   125,    36,    91,    93
};
# endif

#define YYPACT_NINF -332

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-332)))

#define YYTABLE_NINF -246

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -332,    30,    39,  -332,    41,  -332,   -24,  -332,  -332,  -332,
    -332,   112,    12,  -332,  -332,  -332,  -332,  -332,    16,   231,
    -332,  -332,  -332,  -332,  -332,   244,   -24,    54,  -332,    16,
       5,   154,  -332,  -332,   103,   109,    14,  -332,    12,    -1,
      16,  -332,  -332,  -332,  -332,  1492,    97,   244,  -332,  -332,
    -332,     1,  -332,   174,  -332,  -332,   156,   -13,   160,   181,
     197,   922,   922,  1492,   244,   169,  -332,  -332,   234,  -332,
    1492,  1492,   900,  -332,   225,   529,  -332,  -332,   258,   267,
    1660,   116,  -332,  -332,  -332,  -332,   154,  -332,   252,   260,
    -332,   176,   287,  -332,    35,    12,     7,  1492,   244,   261,
     974,   244,   244,  -332,    99,  -332,  -332,  -332,  1492,    71,
      71,   263,  -332,  -332,  1492,    73,  1660,  1048,  -332,  1685,
     254,  -332,   266,   244,  -332,  -332,  1492,  1492,  1492,  1492,
    1492,  1492,  1492,  1492,  1492,  1492,  1492,  1492,  1492,  1492,
    1492,  1492,  1492,  1492,   244,   974,  1122,   974,   974,  -332,
    -332,  -332,    12,  -332,   272,    -6,   244,   273,   269,  -332,
    1660,  -332,   176,   276,  -332,  -332,  1526,  1492,  -332,  -332,
    -332,  -332,   244,    86,  -332,  1492,  1576,   259,   278,  -332,
    1492,  -332,  -332,   294,  -332,  1660,   499,   424,   164,   164,
     340,  1602,  1088,   199,   214,  1241,  1241,   340,   227,   227,
    -332,  -332,  -332,   280,   282,  1492,    50,   283,   284,   313,
    -332,  -332,   176,  -332,    12,  -332,   285,  -332,  1492,    93,
     752,   291,  -332,   107,   289,  1660,  1492,  -332,  1196,   127,
    -332,  1492,   974,  -332,    90,   379,  -332,  -332,  -332,  -332,
       4,  -332,  -332,    69,  1552,  -332,     2,   -12,   181,   299,
     305,   307,  -332,   309,   310,   288,   312,   604,  -332,  -332,
    -332,  -332,  -332,   314,   752,  -332,  -332,  -332,  -332,  -332,
      89,  -332,  -332,  1492,  -332,   244,   974,  1660,  -332,  -332,
    1660,   311,   454,  -332,  1492,  -332,    44,  -332,  1492,  -332,
    -332,  -332,  -332,  -332,  -332,   922,   325,  -332,  1492,  1492,
    1492,   826,  1270,   277,  -332,  -332,  -332,    89,    12,  -332,
    -332,  -332,  1660,  -332,   326,  -332,  1492,  -332,    51,    57,
    -332,  1660,  -332,  1492,   327,  -332,   134,   152,   177,   370,
      12,   391,  -332,  -332,   345,   342,  -332,  -332,  -332,   343,
     382,  -332,   313,   348,  -332,  -332,    64,  -332,  -332,  -332,
    -332,   826,  -332,  -332,   349,   313,  1492,  1344,   277,  1492,
     401,    12,  -332,  -332,   397,   350,   826,  1492,  -332,  1660,
     354,  -332,  1631,  1492,  -332,   826,  -332,  -332,  -332,   245,
    1418,  -332,  1660,  -332,    27,   359,   360,   826,    46,   361,
    -332,   678,  -332,  -332,  -332,  -332,   425,   427,   428,    46,
       3,  1015,   373,  -332,    12,   678,   362,   678,   826,  -332,
    -332,  -332,   151,    46,  -332,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,  -332,
    -332,  -332,  -332,  -332,  -332,   366,   111,   248,   248,   346,
    1167,  1235,   940,  1306,  1306,   346,   262,   262,  -332,  -332,
    -332,  -332
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    49,     1,    49,    22,     6,    24,    34,    35,
      23,    53,    10,    50,     5,     3,    38,    39,     0,     0,
      25,    40,    52,    51,    11,     0,     6,    54,   219,     0,
       0,   216,    16,    17,     0,     0,    56,    21,    10,     0,
       0,     7,   220,    29,    31,     0,     0,     0,    55,   217,
     218,    49,    29,     0,     9,     8,   245,   185,   186,     0,
       0,     0,     0,     0,     0,     0,   208,   211,     0,   187,
       0,     0,     0,   202,     0,     0,   168,   167,     0,     0,
      57,   164,   201,   165,   166,   199,   215,   184,     0,     0,
     205,    44,    56,    33,    53,    10,    49,     0,     0,     0,
       0,     0,     0,   156,   136,   157,   158,   235,     0,     0,
       0,   227,   160,   159,     0,     0,   134,     0,   188,   174,
       0,   176,   172,     0,   161,   162,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      36,    43,    10,    47,     0,    45,     0,    27,     0,    32,
     138,   236,    44,     0,   163,   233,     0,     0,    58,   206,
     209,   212,   221,     0,   200,     0,     0,     0,   179,   181,
       0,   175,   204,     0,   237,   137,   141,   140,   149,   150,
     147,     0,   142,   143,   144,   145,   146,   148,   151,   152,
     153,   154,   155,   190,     0,     0,     0,     0,     0,    41,
      19,    46,     0,    26,    10,    30,     0,   228,     0,     0,
       0,     0,   223,     0,     0,   135,     0,   203,     0,     0,
     177,     0,     0,   230,     0,     0,   198,   225,   229,    42,
       0,    48,    28,     0,   213,   207,     0,    38,    39,     0,
       0,     0,    90,     0,     0,     0,     0,     0,    82,    58,
      85,    60,    81,     0,     0,    77,    78,    61,    62,    79,
       6,    80,    76,     0,   226,   221,     0,   183,   182,   189,
     139,     0,     0,   197,     0,   195,     0,    15,     0,    14,
      20,    13,   242,   244,   246,     0,     0,    74,     0,     0,
       0,     0,     0,     0,    83,    84,   169,     6,    10,    59,
      73,    75,   222,   224,     0,   231,     0,   196,     0,     0,
     191,   241,    12,     0,   213,   210,     0,     0,     0,     0,
      10,     0,   104,   103,     0,   102,    94,    96,    95,    97,
       0,   170,     0,    70,    86,   232,     0,   192,   194,   243,
     214,     0,   105,    88,     0,     0,     0,     0,     0,     0,
      66,    10,   193,    87,   239,     0,     0,     0,    68,    69,
       0,    98,     0,     0,    71,     0,   238,    63,    89,     0,
       0,    99,    67,   240,     0,     0,     0,     0,     0,     0,
      64,     0,    91,    92,   100,   130,     0,     0,     0,     0,
       0,   113,   114,   112,    10,     0,     0,     0,     0,   132,
     131,   133,     0,     0,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
     108,   106,   107,    93,   129,     0,     0,   122,   123,   120,
     115,   116,   117,   118,   119,   121,   124,   125,   126,   127,
     128,   111
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -332,  -332,  -332,   -19,  -332,  -332,  -332,    15,  -332,    98,
    -332,  -332,  -332,  -332,  -332,   222,   385,  -332,  -332,  -332,
    -332,  -205,  -332,    -9,   233,   286,  -332,   265,   445,  -332,
     411,  -332,   -92,  -332,  -332,  -332,  -332,  -332,   149,  -332,
    -318,   192,  -217,  -332,  -331,  -332,  -332,  -332,  -332,  -332,
    -332,   110,  -332,  -332,  -332,  -323,  -332,  -332,  -332,   -89,
      77,    56,  1335,   -34,   -52,   -39,  -332,   -85,   290,  -332,
    -332,  -332,   242,   -49,  -332,  -332,   365,  -332,  -332,  -332,
    -332,  -332,   147,  -332,   -17,   -18,   201,  -332,  -332,  -332,
    -332,  -332,  -332,   166,  -332,  -332,  -332,  -332
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    15,     5,    76,    77,   342,   290,    78,
       6,    46,   240,     7,   157,   158,    51,     8,    52,     9,
      10,   151,    21,   260,   153,   154,   155,    94,    95,    23,
      26,    27,   261,   220,   262,   384,   404,   343,   338,   332,
     344,   263,   363,   308,   405,   265,   366,   266,   301,   267,
     408,   339,   340,   268,   387,   333,   334,   269,   365,   406,
     407,   400,   401,   270,    79,   116,   271,   120,   121,   122,
     177,   178,   179,    81,   180,   117,   170,    82,   109,    83,
      84,   110,   296,    85,    39,    86,   222,   223,    87,    88,
      89,   272,   376,   322,   294,   323,    90,    99
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      31,    30,    22,   264,   239,   287,    80,    37,     4,   103,
     105,    31,   104,   104,     4,   163,    97,   169,   169,    28,
     364,   211,    31,    50,   106,   -16,    98,    25,    45,   413,
       3,   112,   113,    16,   370,   378,   119,    17,   115,    -2,
     288,    16,    14,   374,   383,    17,     4,   264,     4,    28,
     395,   388,   389,    47,   100,  -245,   394,   386,   160,    40,
     204,   119,   207,   208,   212,    40,   396,    49,   297,   166,
     289,    41,   414,    93,    24,   168,   235,   433,   176,   159,
     173,   -18,   152,    29,   329,    22,   429,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   292,   119,   397,   119,   119,
     156,   398,   206,   399,   175,   395,   282,    35,    16,   320,
     175,   175,    17,    36,    38,   236,   347,   175,  -136,  -136,
    -136,   396,   348,   219,   175,   144,   225,   360,   167,   362,
     168,   174,   168,   175,   119,    92,   229,   281,   291,    18,
     368,   293,   144,   152,   224,    14,   175,    42,    19,   175,
     175,   245,   107,   175,    91,   283,   145,   209,   415,   416,
     417,   234,   397,   146,    43,   274,   398,   275,   436,   244,
      44,    20,    16,   145,   149,   150,    17,   277,    97,   176,
     146,   314,   280,   119,    98,   279,   161,   175,   -17,   164,
     165,   286,   351,   152,   175,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   129,   130,   131,   434,
     352,   184,   175,   307,   139,   140,   141,   142,   143,   156,
     101,   129,   130,   131,   312,   102,   108,   119,   306,    32,
      33,    34,   203,   324,   111,   353,   104,   175,   318,   321,
     319,   311,    32,    33,   213,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   326,   327,   328,    11,   335,    13,
     221,   136,   137,   138,   139,   140,   141,   142,   143,   124,
     125,   126,   346,    16,   321,   336,   337,    17,   341,   141,
     142,   143,   118,   330,   330,    53,   123,    28,    54,    55,
      56,    45,    57,    58,    59,    60,    61,    62,   424,   425,
     426,   427,   428,   385,    63,   175,   430,   369,   432,   147,
     372,   149,   150,   335,   426,   427,   428,   148,   162,   182,
     172,   227,    64,   379,   382,   215,   183,    65,    66,    67,
     210,    68,    69,   214,   217,   355,   335,   232,   228,   330,
     233,   237,   238,   243,   304,    70,   276,   129,   130,    71,
     273,    72,  -173,   415,   416,    73,   298,    74,    75,  -173,
      31,   402,   299,   221,   300,   390,   302,   303,   305,   315,
      53,    31,    28,    54,    55,    56,   309,    57,    58,    59,
      60,    61,    62,   325,   345,    31,   402,   295,   354,    63,
     139,   140,   141,   142,   143,   356,   424,   425,   426,   427,
     428,   357,   175,   358,   359,   373,   367,    64,   361,   375,
     380,   377,    65,    66,    67,   392,    68,    69,   393,   409,
     403,   410,   411,    40,   431,   451,   242,    96,   284,   127,
      70,   129,   130,   131,    71,   241,    72,    12,   216,    48,
      73,   331,    74,    75,   285,    53,   310,    28,    54,    55,
      56,   391,    57,    58,    59,    60,    61,    62,   371,   435,
     278,   350,     0,   230,    63,   171,   313,     0,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   349,
       0,     0,    64,     0,     0,     0,     0,    65,    66,    67,
       0,    68,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   316,     0,    70,   129,   130,   131,    71,
       0,    72,     0,     0,     0,    73,     0,    74,    75,   317,
      53,     0,    28,    54,    55,    56,     0,    57,    58,    59,
      60,    61,    62,     0,     0,     0,     0,     0,     0,    63,
       0,     0,     0,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,     0,     0,     0,    64,     0,     0,
       0,     0,    65,    66,    67,     0,    68,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,    71,     0,    72,     0,     0,     0,
      73,     0,    74,    75,  -171,    53,     0,    28,    54,    55,
      56,     0,    57,    58,    59,    60,    61,    62,     0,     0,
       0,     0,     0,     0,    63,    -6,    -6,    -6,    -6,    -6,
       0,     0,    -6,    -6,    -6,    -6,     0,    -6,    -6,    -6,
       0,     0,    64,     0,     0,     0,     0,    65,    66,    67,
       0,    68,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,    71,
      14,    72,     0,     0,     0,    73,    -6,    74,    75,    53,
       0,    28,    54,    55,   247,     0,    57,    58,   248,    60,
      61,    62,     0,     0,     0,     0,     0,     0,    63,   249,
       0,   250,   388,   389,     0,     0,   251,   252,   253,   254,
       0,   255,   256,   257,     0,     0,    64,     0,     0,     0,
       0,    65,    66,    67,     0,    68,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    70,
       0,     0,     0,    71,   258,    72,     0,     0,     0,   259,
    -109,    74,    75,   246,     0,    28,    54,    55,   247,     0,
      57,    58,   248,    60,    61,    62,     0,     0,     0,     0,
       0,     0,    63,   249,     0,   250,     0,     0,     0,     0,
     251,   252,   253,   254,     0,   255,   256,   257,     0,     0,
      64,     0,     0,     0,     0,    65,    66,    67,     0,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,     0,     0,     0,    71,   258,    72,
       0,     0,     0,   259,   -72,    74,    75,    53,     0,    28,
      54,    55,   247,     0,    57,    58,   248,    60,    61,    62,
       0,     0,     0,     0,     0,     0,    63,   249,     0,   250,
       0,     0,     0,     0,   251,   252,   253,   254,     0,   255,
     256,   257,     0,     0,    64,     0,     0,     0,     0,    65,
      66,    67,     0,    68,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,    71,   258,    72,     0,     0,     0,   259,     0,    74,
      75,    53,     0,    28,    54,    55,    56,     0,    57,    58,
      59,    60,    61,    62,     0,     0,     0,     0,     0,     0,
      63,     0,     0,     0,     0,    28,     0,     0,    56,     0,
      57,    58,     0,    60,     0,     0,     0,     0,    64,     0,
       0,     0,     0,    65,    66,    67,     0,    68,    69,     0,
       0,     0,     0,     0,     0,     0,     0,   415,   416,   417,
      64,    70,   114,     0,     0,    71,    66,    72,     0,    68,
      69,    73,     0,    74,    75,    53,     0,    28,    54,    55,
      56,     0,    57,    58,    59,    60,    61,    62,     0,    72,
       0,     0,     0,    73,    63,    74,    75,   421,   422,   423,
     424,   425,   426,   427,   428,     0,     0,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,    65,    66,    67,
       0,    68,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   415,   416,   417,    70,     0,     0,     0,    71,
       0,    72,  -171,     0,     0,    73,     0,    74,    75,    53,
       0,    28,    54,    55,    56,     0,    57,    58,    59,    60,
      61,    62,     0,     0,     0,     0,     0,     0,    63,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
       0,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,    65,    66,    67,     0,    68,    69,     0,     0,     0,
       0,     0,     0,     0,     0,   129,   130,   131,     0,    70,
       0,     0,     0,    71,     0,    72,     0,     0,     0,    73,
    -178,    74,    75,    53,     0,    28,    54,    55,    56,     0,
      57,    58,    59,    60,    61,    62,     0,     0,     0,     0,
       0,     0,    63,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,     0,     0,     0,     0,     0,     0,     0,
      64,     0,     0,     0,     0,    65,    66,    67,     0,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   205,     0,    70,   415,   416,   417,    71,     0,    72,
       0,     0,     0,    73,     0,    74,    75,    53,     0,    28,
      54,    55,    56,     0,    57,    58,    59,    60,    61,    62,
       0,     0,     0,     0,     0,     0,    63,     0,     0,     0,
       0,     0,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,     0,     0,    64,     0,     0,     0,     0,    65,
      66,    67,     0,    68,    69,     0,     0,     0,     0,     0,
       0,     0,   415,   416,   417,     0,     0,    70,   129,   130,
     131,    71,     0,    72,     0,     0,     0,    73,  -180,    74,
      75,    53,     0,    28,    54,    55,   247,     0,    57,    58,
     248,    60,    61,    62,     0,     0,     0,     0,     0,     0,
      63,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     138,   139,   140,   141,   142,   143,     0,     0,    64,     0,
       0,     0,     0,    65,    66,    67,     0,    68,    69,     0,
       0,     0,     0,   415,   416,   417,     0,     0,     0,     0,
       0,    70,     0,     0,     0,    71,  -101,    72,     0,     0,
       0,    73,     0,    74,    75,    53,     0,    28,    54,    55,
      56,     0,    57,    58,    59,    60,    61,    62,     0,     0,
       0,     0,     0,     0,    63,   423,   424,   425,   426,   427,
     428,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,    65,    66,    67,
       0,    68,    69,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,    71,
    -101,    72,     0,     0,     0,    73,     0,    74,    75,    53,
       0,    28,    54,    55,    56,     0,    57,    58,    59,    60,
      61,    62,     0,     0,     0,     0,     0,     0,    63,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,    65,    66,    67,     0,    68,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    70,
       0,     0,     0,    71,     0,    72,  -101,     0,     0,    73,
       0,    74,    75,    53,     0,    28,    54,    55,    56,     0,
      57,    58,    59,    60,    61,    62,     0,     0,     0,     0,
       0,     0,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,     0,     0,     0,     0,    65,    66,    67,     0,    68,
      69,   127,   128,   129,   130,   131,     0,     0,     0,     0,
       0,     0,     0,    70,     0,     0,     0,    71,     0,    72,
       0,     0,     0,    73,     0,    74,    75,   127,   128,   129,
     130,   131,     0,     0,     0,     0,     0,     0,     0,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   127,   128,   129,   130,   131,   218,     0,     0,     0,
       0,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   127,   128,   129,
     130,   131,   295,     0,     0,     0,     0,     0,     0,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,     0,     0,     0,     0,   226,   127,   128,   129,   130,
     131,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,     0,     0,     0,
       0,   231,     0,     0,     0,   127,   128,   129,   130,   131,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,     0,     0,     0,   381,
     127,   128,   129,   130,   131,     0,     0,     0,     0,     0,
       0,     0,   181,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   412,     0,     0,     0,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,     0,     0,     0,     0,     0,     0,
       0,   412
};

static const yytype_int16 yycheck[] =
{
      18,    18,    11,   220,   209,     1,    45,    26,     7,    61,
      62,    29,    61,    62,     7,   100,    14,   109,   110,     3,
     351,    27,    40,    40,    63,    38,    38,    12,    14,    26,
       0,    70,    71,     6,   357,   366,    75,    10,    72,     0,
      36,     6,    66,   361,   375,    10,     7,   264,     7,     3,
       4,    24,    25,    38,    67,    67,   387,   380,    97,    60,
     145,   100,   147,   148,    70,    60,    20,    68,    66,   108,
      66,    66,    69,    72,    62,    71,    26,   408,   117,    72,
     114,    67,    91,    67,   301,    94,   404,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,    36,   145,    61,   147,   148,
      95,    65,   146,    67,    70,     4,    26,    19,     6,    75,
      70,    70,    10,    25,    70,    75,    75,    70,    12,    13,
      14,    20,    75,   167,    70,    36,   175,   342,    67,    75,
      71,    68,    71,    70,   183,    47,   180,   232,   240,    37,
     355,   243,    36,   162,    68,    66,    70,     3,    46,    70,
      70,    68,    64,    70,    67,    75,    67,   152,    17,    18,
      19,   205,    61,    74,    71,    68,    65,    70,    67,   218,
      71,    69,     6,    67,     8,     9,    10,   226,    14,   228,
      74,   276,   231,   232,    38,    68,    98,    70,    38,   101,
     102,   235,    68,   212,    70,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    17,    18,    19,    68,
      68,   123,    70,   257,    60,    61,    62,    63,    64,   214,
      49,    17,    18,    19,   273,    38,    67,   276,   257,     8,
       9,    10,   144,   295,    10,    68,   295,    70,   282,   288,
     284,   270,     8,     9,   156,    56,    57,    58,    59,    60,
      61,    62,    63,    64,   298,   299,   300,     2,   302,     4,
     172,    57,    58,    59,    60,    61,    62,    63,    64,    12,
      13,    14,   316,     6,   323,     8,     9,    10,   307,    62,
      63,    64,    67,   302,   303,     1,    38,     3,     4,     5,
       6,    14,     8,     9,    10,    11,    12,    13,    60,    61,
      62,    63,    64,    68,    20,    70,   405,   356,   407,    67,
     359,     8,     9,   357,    62,    63,    64,    67,    67,    75,
      67,    72,    38,   367,   373,    66,    70,    43,    44,    45,
      68,    47,    48,    70,    68,   330,   380,    67,    70,   358,
      68,    68,    68,    68,    66,    61,    67,    17,    18,    65,
      69,    67,    68,    17,    18,    71,    67,    73,    74,    75,
     388,   388,    67,   275,    67,   384,    67,    67,    66,    68,
       1,   399,     3,     4,     5,     6,    72,     8,     9,    10,
      11,    12,    13,    68,    68,   413,   413,    70,    28,    20,
      60,    61,    62,    63,    64,    14,    60,    61,    62,    63,
      64,    66,    70,    70,    32,    14,    67,    38,    70,    22,
      66,    71,    43,    44,    45,    66,    47,    48,    68,     4,
      69,     4,     4,    60,    72,    69,   214,    52,    59,    15,
      61,    17,    18,    19,    65,   212,    67,     2,   162,    38,
      71,   302,    73,    74,    75,     1,   264,     3,     4,     5,
       6,   384,     8,     9,    10,    11,    12,    13,   358,   413,
     228,   324,    -1,   183,    20,   110,   275,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,   323,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    -1,    61,    17,    18,    19,    65,
      -1,    67,    -1,    -1,    -1,    71,    -1,    73,    74,    75,
       1,    -1,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    65,    -1,    67,    -1,    -1,    -1,
      71,    -1,    73,    74,    75,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    33,    34,    35,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    73,    74,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,
      -1,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    43,    44,    45,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    71,
      72,    73,    74,     1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    21,    -1,    23,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    -1,    33,    34,    35,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    65,    66,    67,
      -1,    -1,    -1,    71,    72,    73,    74,     1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    23,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    -1,    33,
      34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    65,    66,    67,    -1,    -1,    -1,    71,    -1,    73,
      74,     1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,     3,    -1,    -1,     6,    -1,
       8,     9,    -1,    11,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      38,    61,    62,    -1,    -1,    65,    44,    67,    -1,    47,
      48,    71,    -1,    73,    74,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    10,    11,    12,    13,    -1,    67,
      -1,    -1,    -1,    71,    20,    73,    74,    57,    58,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    61,    -1,    -1,    -1,    65,
      -1,    67,    68,    -1,    -1,    71,    -1,    73,    74,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    43,    44,    45,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    -1,    61,
      -1,    -1,    -1,    65,    -1,    67,    -1,    -1,    -1,    71,
      72,    73,    74,     1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    -1,    61,    17,    18,    19,    65,    -1,    67,
      -1,    -1,    -1,    71,    -1,    73,    74,     1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    -1,    -1,    61,    17,    18,
      19,    65,    -1,    67,    -1,    -1,    -1,    71,    72,    73,
      74,     1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      59,    60,    61,    62,    63,    64,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    47,    48,    -1,
      -1,    -1,    -1,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    65,    66,    67,    -1,    -1,
      -1,    71,    -1,    73,    74,     1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    71,    -1,    73,    74,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    43,    44,    45,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    65,    -1,    67,    68,    -1,    -1,    71,
      -1,    73,    74,     1,    -1,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,
      48,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    65,    -1,    67,
      -1,    -1,    -1,    71,    -1,    73,    74,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    15,    16,    17,    18,    19,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    15,    16,    17,
      18,    19,    70,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    68,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   399,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   436
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    77,    78,     0,     7,    80,    86,    89,    93,    95,
      96,   103,   104,   103,    66,    79,     6,    10,    37,    46,
      69,    98,    99,   105,    62,    83,   106,   107,     3,    67,
     160,   161,     8,     9,    10,    85,    85,    79,    70,   160,
      60,    66,     3,    71,    71,    14,    87,    83,   106,    68,
     160,    92,    94,     1,     4,     5,     6,     8,     9,    10,
      11,    12,    13,    20,    38,    43,    44,    45,    47,    48,
      61,    65,    67,    71,    73,    74,    81,    82,    85,   140,
     141,   149,   153,   155,   156,   159,   161,   164,   165,   166,
     172,    67,    85,    72,   103,   104,    92,    14,    38,   173,
      67,    49,    38,   140,   149,   140,   141,    85,    67,   154,
     157,    10,   141,   141,    62,   139,   141,   151,    67,   141,
     143,   144,   145,    38,    12,    13,    14,    15,    16,    17,
      18,    19,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    36,    67,    74,    67,    67,     8,
       9,    97,    99,   100,   101,   102,    83,    90,    91,    72,
     141,    85,    67,   143,    85,    85,   141,    67,    71,   108,
     152,   152,    67,   139,    68,    70,   141,   146,   147,   148,
     150,    27,    75,    70,    85,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,    85,   143,    59,   139,   143,   143,    83,
      68,    27,    70,    85,    70,    66,   101,    68,    70,   139,
     109,    85,   162,   163,    68,   141,    69,    72,    70,   139,
     144,    69,    67,    68,   139,    26,    75,    68,    68,    97,
      88,   100,    91,    68,   141,    68,     1,     6,    10,    21,
      23,    28,    29,    30,    31,    33,    34,    35,    66,    71,
      99,   108,   110,   117,   118,   121,   123,   125,   129,   133,
     139,   142,   167,    69,    68,    70,    67,   141,   148,    68,
     141,   143,    26,    75,    59,    75,   139,     1,    36,    66,
      84,   108,    36,   108,   170,    70,   158,    66,    67,    67,
      67,   124,    67,    67,    66,    66,    79,   139,   119,    72,
     117,    79,   141,   162,   143,    68,    59,    75,   139,   139,
      75,   141,   169,   171,   140,    68,   139,   139,   139,   118,
      99,   114,   115,   131,   132,   139,     8,     9,   114,   127,
     128,    79,    83,   113,   116,    68,   139,    75,    75,   169,
     158,    68,    68,    68,    28,    83,    14,    66,    70,    32,
      97,    70,    75,   118,   120,   134,   122,    67,    97,   141,
     131,   127,   141,    14,   116,    22,   168,    71,   120,   139,
      66,    68,   141,   120,   111,    68,   131,   130,    24,    25,
      99,   136,    66,    68,   120,     4,    20,    61,    65,    67,
     137,   138,   160,    69,   112,   120,   135,   136,   126,     4,
       4,     4,   138,    26,    69,    17,    18,    19,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,   116,
     135,    72,   135,   120,    68,   137,    67,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    79,    79,    80,    81,    82,
      83,    83,    84,    84,    84,    84,    85,    85,    87,    88,
      86,    86,    86,    86,    86,    89,    90,    91,    91,    92,
      92,    94,    93,    95,    96,    96,    97,    97,    98,    98,
      99,   100,   100,   100,   101,   101,   101,   102,   102,   103,
     103,   104,   105,   105,   106,   106,   107,   107,   109,   108,
     110,   110,   110,   111,   112,   111,   113,   113,   114,   115,
     116,   116,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   119,   118,   120,   122,   121,
     124,   123,   126,   125,   127,   127,   127,   128,   128,   130,
     129,   131,   131,   132,   132,   134,   133,   135,   135,   135,
     136,   136,   136,   137,   137,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   139,   139,   140,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   142,
     142,   143,   143,   143,   144,   144,   145,   145,   146,   146,
     146,   147,   147,   148,   149,   149,   149,   149,   150,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   151,   149,   149,   149,   152,   152,   154,   153,
     155,   157,   156,   158,   158,   159,   160,   160,   160,   161,
     161,   162,   162,   163,   163,   164,   164,   164,   164,   164,
     164,   164,   164,   165,   166,   166,   166,   166,   167,   168,
     168,   169,   171,   170,   170,   173,   172
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     0,     1,     0,     4,     1,     1,
       0,     1,     2,     1,     1,     1,     1,     1,     0,     0,
       9,     3,     1,     1,     1,     2,     2,     1,     3,     0,
       4,     0,     7,     6,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     1,     0,     1,     2,     1,     3,     0,
       2,     2,     1,     0,     1,     3,     2,     4,     0,     4,
       1,     1,     1,     0,     0,     4,     2,     4,     3,     3,
       1,     3,     0,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     0,     3,     1,     0,     6,
       0,     8,     0,    10,     1,     1,     1,     1,     3,     0,
       8,     0,     1,     1,     1,     0,    10,     2,     2,     0,
       3,     5,     2,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     2,     2,     2,     1,     3,     1,     3,     3,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       2,     2,     2,     3,     1,     1,     1,     1,     1,     2,
       3,     0,     1,     2,     1,     2,     1,     3,     0,     1,
       2,     1,     3,     3,     1,     1,     1,     1,     0,     5,
       3,     6,     7,     8,     7,     5,     6,     5,     4,     1,
       3,     1,     0,     4,     3,     1,     1,     3,     0,     3,
       7,     0,     3,     0,     3,     1,     1,     3,     3,     1,
       2,     0,     3,     1,     3,     4,     5,     2,     4,     4,
       4,     6,     7,     3,     1,     2,     3,     3,     6,     0,
       2,     1,     0,     3,     1,     0,     6
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
        case 5:

    {
#line 218 "grammar/grammar.y.pre"
		 //yywarn("Extra ';'. Ignored.");
	 }

    break;

  case 7:

    {
#line 227 "grammar/grammar.y.pre"
		object_t *ob;
		inherit_t inherit;
		int initializer;

		(yyvsp[-3].type) |= global_modifiers;

		if (var_defined)
		    yyerror("Illegal to inherit after defining global variables.");
		ob = find_object2((yyvsp[-1].string));
		if (ob == 0) {
		    inherit_file = alloc_cstring((yyvsp[-1].string), "inherit");
		    /* Return back to load_object() */
		    YYACCEPT;
		}
		scratch_free((yyvsp[-1].string));
		inherit.prog = ob->prog;
		inherit.function_index_offset =
		      mem_block[A_RUNTIME_FUNCTIONS].current_size /
		      sizeof (runtime_function_u);
		inherit.variable_index_offset =
		      mem_block[A_VAR_TEMP].current_size /
		      sizeof (variable_t);
		inherit.type_mod = (yyvsp[-3].type);
		add_to_mem_block(A_INHERITS, (char *)&inherit, sizeof inherit);
		copy_variables(ob->prog, (yyvsp[-3].type));
		copy_structures(ob->prog);
		initializer = copy_functions(ob->prog, (yyvsp[-3].type));
		if (initializer >= 0) {
		    /* initializer is an index into the object we're
		       inheriting's function table; this finds the
		       appropriate entry in our table and generates
		       a call to it */
		    switch_to_block(A_INITIALIZER);
		    generate_inherited_init_call(mem_block[A_INHERITS].current_size/sizeof(inherit_t) - 1, initializer);
		    switch_to_block(A_PROGRAM);
		}
	    }

    break;

  case 8:

    {
#line 269 "grammar/grammar.y.pre"
		CREATE_REAL((yyval.node), (yyvsp[0].real));
	    }

    break;

  case 9:

    {
#line 276 "grammar/grammar.y.pre"
		CREATE_NUMBER((yyval.node), (yyvsp[0].number));
	    }

    break;

  case 10:

    {
#line 283 "grammar/grammar.y.pre"
		(yyval.type) = 0;
	    }

    break;

  case 11:

    {
#line 287 "grammar/grammar.y.pre"
		(yyval.type) = TYPE_MOD_ARRAY;
	    }

    break;

  case 12:

    {
#line 294 "grammar/grammar.y.pre"
		(yyval.node) = (yyvsp[0].node);
	}

    break;

  case 13:

    {
#line 298 "grammar/grammar.y.pre"
		(yyval.node) = (yyvsp[0].decl).node;
		if (!(yyval.node)) {
		    CREATE_RETURN((yyval.node), 0);
		}
	}

    break;

  case 14:

    {
#line 305 "grammar/grammar.y.pre"
		(yyval.node) = 0;
	    }

    break;

  case 15:

    {
#line 309 "grammar/grammar.y.pre"
		(yyval.node) = 0;
	}

    break;

  case 16:

    {
#line 316 "grammar/grammar.y.pre"
	      (yyval.string) = scratch_copy((yyvsp[0].ihe)->name);
	    }

    break;

  case 18:

    {
#line 324 "grammar/grammar.y.pre"
		(yyvsp[-2].type) |= global_modifiers;
		/* Handle type checking here so we know whether to typecheck
		   'argument' */
		if ((yyvsp[-2].type) & ~NAME_TYPE_MOD) {
	 		exact_types = (yyvsp[-2].type) | (yyvsp[-1].type);
	 	} else {
		    if (pragmas & PRAGMA_STRICT_TYPES) {
				if (strcmp((yyvsp[0].string), "create") != 0)
					yyerror("\"#pragma strict_types\" requires type of function");
				else
					exact_types = TYPE_VOID; /* default for create() */
		    } else {
				exact_types = 0;
			}
		}
	}

    break;

  case 19:

    {
#line 346 "grammar/grammar.y.pre"
		char *p = (yyvsp[-4].string);
		(yyvsp[-4].string) = make_shared_string((yyvsp[-4].string));
		scratch_free(p);

		/* If we had nested functions, we would need to check */
		/* here if we have enough space for locals */

		/*
		 * Define a prototype. If it is a real function, then the
		 * prototype will be replaced below.
		 */

		(yyval.number) = NAME_UNDEFINED | NAME_PROTOTYPE;
		if ((yyvsp[-1].argument).flags & ARG_IS_VARARGS) {
		    (yyval.number) |= NAME_TRUE_VARARGS;
		    (yyvsp[-6].type) |= NAME_VARARGS;
		}
		define_new_function((yyvsp[-4].string), (yyvsp[-1].argument).num_arg, 0, (yyval.number), (yyvsp[-6].type) | (yyvsp[-5].type));
		/* This is safe since it is guaranteed to be in the
		   function table, so it can't be dangling */
		free_string((yyvsp[-4].string));
		context = 0;
	}

    break;

  case 20:

    {
#line 371 "grammar/grammar.y.pre"
		/* Either a prototype or a block */
		int fun;
		if ((yyvsp[0].node)) {
		    (yyvsp[-1].number) &= ~(NAME_UNDEFINED | NAME_PROTOTYPE);
		    if ((yyvsp[0].node)->kind != NODE_RETURN &&
				((yyvsp[0].node)->kind != NODE_TWO_VALUES
				 || (yyvsp[0].node)->r.expr->kind != NODE_RETURN)) {
				parse_node_t *replacement;
				CREATE_STATEMENTS(replacement, (yyvsp[0].node), 0);
				CREATE_RETURN(replacement->r.expr, 0);
				(yyvsp[0].node) = replacement;
		    }
		    if ((yyvsp[-3].argument).flags & ARG_IS_PROTO) {
				yyerror("Missing name for function argument");
		    }
		    fun = define_new_function((yyvsp[-6].string), (yyvsp[-3].argument).num_arg,
									  max_num_locals - (yyvsp[-3].argument).num_arg,
									  (yyvsp[-1].number), (yyvsp[-8].type) | (yyvsp[-7].type));
		    if (fun != -1) {
				COMPILER_FUNC(fun)->address = generate_function(COMPILER_FUNC(fun), (yyvsp[0].node), max_num_locals);
			}
		}
		free_all_local_names();
	}

    break;

  case 21:

    {
#line 397 "grammar/grammar.y.pre"
			if (!(yyvsp[-2].type))
				yyerror("Missing type for global variable declaration");
	    }

    break;

  case 25:

    {
#line 407 "grammar/grammar.y.pre"
			global_modifiers = (yyvsp[-1].type);
	    }

    break;

  case 26:

    {
#line 414 "grammar/grammar.y.pre"
			if ((current_type & ~NAME_TYPE_MOD) == TYPE_VOID)
				yyerror("Illegal to declare class member of type void.");
			add_local_name((yyvsp[0].string), current_type | (yyvsp[-1].type));
			scratch_free((yyvsp[0].string));
	    }

    break;

  case 31:

    {
#line 434 "grammar/grammar.y.pre"
		  ident_hash_elem_t *ihe;

		  (yyval.number) = store_prog_string((yyvsp[-1].string));
		  ihe = find_or_add_ident(
								  PROG_STRING((yyval.number)),
								  FOA_GLOBAL_SCOPE);
		  if (ihe->dn.class_num == -1)
			  ihe->sem_value++;
		  else {
			  /* Possibly, this should check if the definitions are
				 consistent */
			  char buf[256];
			  char *end = EndOf(buf);
			  char *p;

			  p = strput(buf, end, "Illegal to redefine class ");
			  p = strput(p, end, (yyvsp[-1].string));
			  yyerror(buf);
		  }

		  int _class_num = mem_block[A_CLASS_DEF].current_size / sizeof(class_def_t);
		  if(_class_num > TYPE_MOD_ARRAY) {
			  yyerror("Defined too much classes");
		  }
		  ihe->dn.class_num = _class_num;

	  }

    break;

  case 32:

    {
#line 463 "grammar/grammar.y.pre"
		class_def_t *sd;
		class_member_entry_t *sme;
		int i;

		sd = (class_def_t *)allocate_in_mem_block(A_CLASS_DEF, sizeof(class_def_t));
		i = sd->size = current_number_of_locals;
		sd->index = mem_block[A_CLASS_MEMBER].current_size / sizeof(class_member_entry_t);
		sd->name = (yyvsp[-2].number);

		sme = (class_member_entry_t *)allocate_in_mem_block(A_CLASS_MEMBER, sizeof(class_member_entry_t) * current_number_of_locals);

		while (i--) {
		    sme[i].name = store_prog_string(locals_ptr[i]->name);
		    sme[i].type = type_of_locals_ptr[i];
		}

		free_all_local_names();
		scratch_free((yyvsp[-4].string));
	}

    break;

  case 33:

    {
#line 487 "grammar/grammar.y.pre"
// by chenyh 2016.9.12
// 对于已有定义的class, 如果基类已经定义，那么不做任何处理
        if (!lookup_inherit_class((yyvsp[-3].ihe)->name, locals_ptr, current_number_of_locals)) {
            char buf[256];
            char *end = EndOf(buf);
            char *p;

            p = strput(buf, end, "Illegal to redefine class ");
            p = strput(p, end, (yyvsp[-3].ihe)->name);
            yyerror(buf);
        }
		free_all_local_names();
    }

    break;

  case 37:

    {
#line 512 "grammar/grammar.y.pre"
		if ((yyvsp[0].ihe)->dn.local_num != -1) {
		    char buff[256];
		    char *end = EndOf(buff);
		    char *p;

		    p = strput(buff, end, "Illegal to redeclare local name '");
		    p = strput(p, end, (yyvsp[0].ihe)->name);
		    p = strput(p, end, "'");
		    yyerror(buff);
		}
		(yyval.string) = scratch_copy((yyvsp[0].ihe)->name);
	    }

    break;

  case 39:

    {
#line 530 "grammar/grammar.y.pre"
			if ((yyvsp[0].ihe)->dn.class_num == -1) {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Undefined class '");
				p = strput(p, end, (yyvsp[0].ihe)->name);
				p = strput(p, end, "'");
				yyerror(buf);
				(yyval.type) = TYPE_ANY;
			} else
				(yyval.type) = (yyvsp[0].ihe)->dn.class_num | TYPE_MOD_CLASS;
	    }

    break;

  case 41:

    {
#line 563 "grammar/grammar.y.pre"
		if ((yyvsp[-1].type) == TYPE_VOID)
		    yyerror("Illegal to declare argument of type void.");
                (yyval.number) = ARG_IS_PROTO;
                add_local_name("", (yyvsp[-1].type) | (yyvsp[0].type));
            }

    break;

  case 42:

    {
#line 570 "grammar/grammar.y.pre"
		  if ((yyvsp[-2].type) == TYPE_VOID)
			  yyerror("Illegal to declare argument of type void.");
		  add_local_name((yyvsp[0].string), (yyvsp[-2].type) | (yyvsp[-1].type));
		  scratch_free((yyvsp[0].string));
		  (yyval.number) = 0;
	  }

    break;

  case 43:

    {
#line 578 "grammar/grammar.y.pre"
		if (exact_types) {
		    yyerror("Missing type for argument");
		}
		add_local_name((yyvsp[0].string), TYPE_ANY);
		scratch_free((yyvsp[0].string));
		(yyval.number) = 0;
            }

    break;

  case 44:

    {
#line 590 "grammar/grammar.y.pre"
		(yyval.argument).num_arg = 0;
                (yyval.argument).flags = 0;
	    }

    break;

  case 46:

    {
#line 596 "grammar/grammar.y.pre"
		int x = type_of_locals_ptr[max_num_locals-1];

		(yyval.argument) = (yyvsp[-1].argument);
		(yyval.argument).flags |= ARG_IS_VARARGS;

		if (x != TYPE_ANY && !(x & TYPE_MOD_ARRAY))
		    yywarn("Variable to hold remainder of arguments should be an array.");
	    }

    break;

  case 47:

    {
#line 609 "grammar/grammar.y.pre"
		(yyval.argument).num_arg = 1;
                (yyval.argument).flags = (yyvsp[0].number);
	    }

    break;

  case 48:

    {
#line 614 "grammar/grammar.y.pre"
                (yyval.argument) = (yyvsp[-2].argument);
		(yyval.argument).num_arg++;
                (yyval.argument).flags |= (yyvsp[0].number);
	    }

    break;

  case 49:

    {
#line 623 "grammar/grammar.y.pre"
		(yyval.type) = 0;
	    }

    break;

  case 50:

    {
#line 627 "grammar/grammar.y.pre"
		(yyval.type) = (yyvsp[-1].type) | (yyvsp[0].type);
	    }

    break;

  case 51:

    {
#line 634 "grammar/grammar.y.pre"
		(yyval.type) = (yyvsp[-1].type) | (yyvsp[0].type);
		current_type = (yyval.type);
	    }

    break;

  case 53:

    {
#line 643 "grammar/grammar.y.pre"
		(yyval.type) = TYPE_UNKNOWN;
	    }

    break;

  case 56:

    {
#line 655 "grammar/grammar.y.pre"
		if ((current_type & ~NAME_TYPE_MOD) == TYPE_VOID)
	    yyerror("Illegal to declare global variable of type void.");
		define_new_variable((yyvsp[0].string), current_type | (yyvsp[-1].type) | global_modifiers);
		scratch_free((yyvsp[0].string));
	    }

    break;

  case 57:

    {
#line 662 "grammar/grammar.y.pre"
		parse_node_t *expr;
		int type = 0;

		if ((yyvsp[-1].number) != F_ASSIGN)
	    yyerror("Only '=' is legal in initializers.");

		/* ignore current_type == 0, which gets a missing type error
		   later anyway */
		if (current_type) {
		    type = (current_type | (yyvsp[-3].type) | global_modifiers) & ~NAME_TYPE_MOD;
		    if ((current_type & ~NAME_TYPE_MOD) == TYPE_VOID)
			yyerror("Illegal to declare global variable of type void.");
		    if (!compatible_types(type, (yyvsp[0].node)->type)) {
			char buff[256];
			char *end = EndOf(buff);
			char *p;

			p = strput(buff, end, "Type mismatch ");
			p = get_two_types(p, end, type, (yyvsp[0].node)->type);
			p = strput(p, end, " when initializing ");
			p = strput(p, end, (yyvsp[-2].string));
			yyerror(buff);
		    }
		}
		switch_to_block(A_INITIALIZER);
		(yyvsp[0].node) = do_promotions((yyvsp[0].node), type);

		CREATE_BINARY_OP(expr, F_VOID_ASSIGN, 0, (yyvsp[0].node), 0);
		CREATE_OPCODE_1(expr->r.expr, F_GLOBAL_LVALUE, 0,
				define_new_variable((yyvsp[-2].string), current_type | (yyvsp[-3].type) | global_modifiers));
		generate(expr);
		switch_to_block(A_PROGRAM);
		scratch_free((yyvsp[-2].string));
	    }

    break;

  case 58:

    {
#line 701 "grammar/grammar.y.pre"
		push_local_count();
	}

    break;

  case 59:

    {
#line 705 "grammar/grammar.y.pre"
		(yyval.decl).node = (yyvsp[-1].node);
		(yyval.decl).num = get_local_count();
		pop_local_count();
	}

    break;

  case 63:

    {
#line 716 "grammar/grammar.y.pre"
                (yyval.decl).node = 0;
                (yyval.decl).num = 0;
            }

    break;

  case 64:

    {
#line 721 "grammar/grammar.y.pre"
		if ((yyvsp[0].type) == TYPE_VOID)
		    yyerror("Illegal to declare local variable of type void.");
                /* can't do this in basic_type b/c local_name_list contains
                 * expr0 which contains cast which contains basic_type
                 */
                current_type = (yyvsp[0].type);
            }

    break;

  case 65:

    {
#line 730 "grammar/grammar.y.pre"
                if ((yyvsp[-3].decl).node && (yyvsp[0].decl).node) {
		    CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-3].decl).node, (yyvsp[0].decl).node);
                } else (yyval.decl).node = ((yyvsp[-3].decl).node ? (yyvsp[-3].decl).node : (yyvsp[0].decl).node);
                (yyval.decl).num = (yyvsp[-3].decl).num + (yyvsp[0].decl).num;
            }

    break;

  case 66:

    {
#line 741 "grammar/grammar.y.pre"
		add_local_name((yyvsp[0].string), current_type | (yyvsp[-1].type));
		scratch_free((yyvsp[0].string));
		(yyval.node) = 0;
	    }

    break;

  case 67:

    {
#line 747 "grammar/grammar.y.pre"
		int type = (current_type | (yyvsp[-3].type)) & ~NAME_TYPE_MOD;

		if ((yyvsp[-1].number) != F_ASSIGN)
		    yyerror("Only '=' is allowed in initializers.");
		if (!compatible_types((yyvsp[0].node)->type, type)) {
		    char buff[256];
		    char *end = EndOf(buff);
		    char *p;

		    p = strput(buff, end, "Type mismatch ");
		    p = get_two_types(p, end, type, (yyvsp[0].node)->type);
		    p = strput(p, end, " when initializing ");
		    p = strput(p, end, (yyvsp[-2].string));

		    yyerror(buff);
		}

		(yyvsp[0].node) = do_promotions((yyvsp[0].node), type);

		CREATE_UNARY_OP_1((yyval.node), F_VOID_ASSIGN_LOCAL, 0, (yyvsp[0].node),
						  add_local_name((yyvsp[-2].string), current_type | (yyvsp[-3].type)));
		scratch_free((yyvsp[-2].string));
	    }

    break;

  case 68:

    {
#line 775 "grammar/grammar.y.pre"
		if ((yyvsp[-2].type) == TYPE_VOID)
			yyerror(" Wrong declare local variable of type void.");

		(yyval.number) = add_local_name((yyvsp[0].string), (yyvsp[-2].type) | (yyvsp[-1].type));
		scratch_free((yyvsp[0].string));
	}

    break;

  case 69:

    {
#line 786 "grammar/grammar.y.pre"
		int type = type_of_locals_ptr[(yyvsp[-2].number)];
				
		if ((yyvsp[-1].number) != F_ASSIGN)
		    yyerror("Only '=' is allowed in initializers.");
		if (!compatible_types((yyvsp[0].node)->type, type)) {
		    char buff[256];
		    char *end = EndOf(buff);
		    char *p;
			
		    p = strput(buff, end, "Type mismatch ");
		    p = get_two_types(p, end, type, (yyvsp[0].node)->type);
		    p = strput(p, end, " when initializing.");
		    yyerror(buff);
		}
		
		(yyvsp[0].node) = do_promotions((yyvsp[0].node), type);
		
		/* this is an expression */
		CREATE_BINARY_OP((yyval.node), F_ASSIGN, 0, (yyvsp[0].node), 0);
		CREATE_OPCODE_1((yyval.node)->r.expr, F_LOCAL_LVALUE, 0, (yyvsp[-2].number));
	}

    break;

  case 70:

    {
#line 812 "grammar/grammar.y.pre"
                (yyval.decl).node = (yyvsp[0].node);
                (yyval.decl).num = 1;
            }

    break;

  case 71:

    {
#line 817 "grammar/grammar.y.pre"
                if ((yyvsp[-2].node) && (yyvsp[0].decl).node) {
		    CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-2].node), (yyvsp[0].decl).node);
                } else (yyval.decl).node = ((yyvsp[-2].node) ? (yyvsp[-2].node) : (yyvsp[0].decl).node);
                (yyval.decl).num = 1 + (yyvsp[0].decl).num;
            }

    break;

  case 72:

    {
#line 827 "grammar/grammar.y.pre"
			(yyval.node) = 0;
	    }

    break;

  case 73:

    {
#line 831 "grammar/grammar.y.pre"
				if ((yyvsp[-1].node) && (yyvsp[0].node)) {
					CREATE_STATEMENTS((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
				} else (yyval.node) = ((yyvsp[-1].node) ? (yyvsp[-1].node) : (yyvsp[0].node));
            }

    break;

  case 74:

    {
#line 837 "grammar/grammar.y.pre"
				(yyval.node) = 0;
            }

    break;

  case 75:

    {
#line 844 "grammar/grammar.y.pre"
		(yyval.node) = insert_pop_value((yyvsp[-1].node));
	}

    break;

  case 81:

    {
#line 853 "grammar/grammar.y.pre"
		(yyval.node) = (yyvsp[0].decl).node;
		pop_n_locals((yyvsp[0].decl).num);
	}

    break;

  case 82:

    {
#line 858 "grammar/grammar.y.pre"
		(yyval.node) = 0;
	}

    break;

  case 83:

    {
#line 862 "grammar/grammar.y.pre"
		if (context & SPECIAL_CONTEXT) {
			yyerror("Cannot break out of catch { } or time_expression { }");
			(yyval.node) = 0;
		} else {
			if (context & SWITCH_CONTEXT) {
				CREATE_CONTROL_JUMP((yyval.node), CJ_BREAK_SWITCH);
			} else {
				if (context & LOOP_CONTEXT) {
					CREATE_CONTROL_JUMP((yyval.node), CJ_BREAK);
					if (context & LOOP_FOREACH) {
						parse_node_t *replace;
						CREATE_STATEMENTS(replace, 0, (yyval.node));
						CREATE_OPCODE(replace->l.expr, F_EXIT_FOREACH, 0);
						(yyval.node) = replace;
					}
				} else {
					yyerror("break statement outside loop");
					(yyval.node) = 0;
				}
			}
		}
	}

    break;

  case 84:

    {
#line 886 "grammar/grammar.y.pre"
		if (context & SPECIAL_CONTEXT)
		    yyerror("Cannot continue out of catch { } or time_expression { }");
		else
		if (!(context & LOOP_CONTEXT))
		    yyerror("continue statement outside loop");
		CREATE_CONTROL_JUMP((yyval.node), CJ_CONTINUE);
	}

    break;

  case 85:

    {
#line 895 "grammar/grammar.y.pre"
		if ((yyvsp[0].type) == TYPE_VOID)
			yyerror("Illegal to declare local variable of type void.");
		/* can't do this in basic_type b/c local_name_list contains
		 * expr0 which contains cast which contains basic_type
		 */
		current_type = (yyvsp[0].type);
	}

    break;

  case 86:

    {
#line 904 "grammar/grammar.y.pre"
		(yyval.node) = (yyvsp[0].decl).node;
		add_local_count((yyvsp[0].decl).num);
	}

    break;

  case 87:

    {
#line 917 "grammar/grammar.y.pre"
			(yyval.node) = (yyvsp[0].node);
		}

    break;

  case 88:

    {
#line 924 "grammar/grammar.y.pre"
		(yyvsp[-3].number) = context;
		context = LOOP_CONTEXT;
	}

    break;

  case 89:

    {
#line 929 "grammar/grammar.y.pre"
		CREATE_LOOP((yyval.node), 1, (yyvsp[0].node), 0, optimize_loop_test((yyvsp[-3].node)));
		context = (yyvsp[-5].number);
	}

    break;

  case 90:

    {
#line 937 "grammar/grammar.y.pre"
		(yyvsp[0].number) = context;
		context = LOOP_CONTEXT;
	}

    break;

  case 91:

    {
#line 942 "grammar/grammar.y.pre"
		CREATE_LOOP((yyval.node), 0, (yyvsp[-5].node), 0, optimize_loop_test((yyvsp[-2].node)));
		context = (yyvsp[-7].number);
	}

    break;

  case 92:

    {
#line 950 "grammar/grammar.y.pre"
		(yyvsp[-7].number) = context;
		context = LOOP_CONTEXT;
	    }

    break;

  case 93:

    {
#line 955 "grammar/grammar.y.pre"
		(yyval.decl).num = (yyvsp[-7].decl).num; /* number of declarations (0/1) */

		(yyvsp[-7].decl).node = insert_pop_value((yyvsp[-7].decl).node);
		(yyvsp[-3].node) = insert_pop_value((yyvsp[-3].node));
		if ((yyvsp[-3].node) && IS_NODE((yyvsp[-3].node), NODE_UNARY_OP, F_INC)
		    && IS_NODE((yyvsp[-3].node)->r.expr, NODE_OPCODE_1, F_LOCAL_LVALUE)) {
		    int lvar = (yyvsp[-3].node)->r.expr->l.number;
		    CREATE_OPCODE_1((yyvsp[-3].node), F_LOOP_INCR, 0, lvar);
		}

		CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-7].decl).node, 0);
		CREATE_LOOP((yyval.decl).node->r.expr, 1, (yyvsp[0].node), (yyvsp[-3].node), optimize_loop_test((yyvsp[-5].node)));

		context = (yyvsp[-9].number);
	      }

    break;

  case 94:

    {
#line 974 "grammar/grammar.y.pre"
		if ((yyvsp[0].ihe)->dn.local_num != -1) {
		    CREATE_OPCODE_1((yyval.decl).node, F_LOCAL_LVALUE, 0, (yyvsp[0].ihe)->dn.local_num);
		} else
	        if ((yyvsp[0].ihe)->dn.global_num != -1) {
		    CREATE_OPCODE_1((yyval.decl).node, F_GLOBAL_LVALUE, 0, (yyvsp[0].ihe)->dn.global_num);
		} else {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "'");
		    p = strput(p, end, (yyvsp[0].ihe)->name);
		    p = strput(p, end, "' is not a local or a global variable.");
		    yyerror(buf);
		    CREATE_OPCODE_1((yyval.decl).node, F_GLOBAL_LVALUE, 0, 0);
		}
		(yyval.decl).num = 0;
            }

    break;

  case 95:

    {
#line 994 "grammar/grammar.y.pre"
                CREATE_OPCODE_1((yyval.decl).node, F_LOCAL_LVALUE, 0, (yyvsp[0].number));
		(yyval.decl).num = 1;
            }

    break;

  case 96:

    {
#line 999 "grammar/grammar.y.pre"
		char buf[256];
		char *end = EndOf(buf);
		char *p;

		p = strput(buf, end, "'");
		p = strput(p, end, (yyvsp[0].string));
		p = strput(p, end, "' is not a local or a global variable.");
		yyerror(buf);
		CREATE_OPCODE_1((yyval.decl).node, F_GLOBAL_LVALUE, 0, 0);
		scratch_free((yyvsp[0].string));
		(yyval.decl).num = 0;
	    }

    break;

  case 97:

    {
#line 1016 "grammar/grammar.y.pre"
		CREATE_FOREACH((yyval.decl).node, (yyvsp[0].decl).node, 0);
		(yyval.decl).num = (yyvsp[0].decl).num;
            }

    break;

  case 98:

    {
#line 1021 "grammar/grammar.y.pre"
		CREATE_FOREACH((yyval.decl).node, (yyvsp[-2].decl).node, (yyvsp[0].decl).node);
		(yyval.decl).num = (yyvsp[-2].decl).num + (yyvsp[0].decl).num;
            }

    break;

  case 99:

    {
#line 1029 "grammar/grammar.y.pre"
		(yyvsp[-3].decl).node->v.expr = (yyvsp[-1].node);
		(yyvsp[-5].number) = context;
		context = LOOP_CONTEXT | LOOP_FOREACH;
            }

    break;

  case 100:

    {
#line 1035 "grammar/grammar.y.pre"
		(yyval.decl).num = (yyvsp[-5].decl).num;

		CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-5].decl).node, 0);
		CREATE_LOOP((yyval.decl).node->r.expr, 2, (yyvsp[0].node), 0, 0);
		CREATE_OPCODE((yyval.decl).node->r.expr->r.expr, F_NEXT_FOREACH, 0);

		context = (yyvsp[-7].number);
	    }

    break;

  case 101:

    {
#line 1048 "grammar/grammar.y.pre"
		CREATE_NUMBER((yyval.node), 1);
	    }

    break;

  case 103:

    {
#line 1056 "grammar/grammar.y.pre"
	 	(yyval.decl).node = (yyvsp[0].node);
		(yyval.decl).num = 0;
	    }

    break;

  case 104:

    {
#line 1061 "grammar/grammar.y.pre"
		(yyval.decl).node = (yyvsp[0].node);
		(yyval.decl).num = 1;
	    }

    break;

  case 105:

    {
#line 1069 "grammar/grammar.y.pre"
                (yyvsp[-3].number) = context;
                context &= LOOP_CONTEXT;
                context |= SWITCH_CONTEXT;
                (yyvsp[-2].number) = mem_block[A_CASES].current_size;
            }

    break;

  case 106:

    {
#line 1076 "grammar/grammar.y.pre"
                parse_node_t *node1, *node2;

                if ((yyvsp[-1].node)) {
		    CREATE_STATEMENTS(node1, (yyvsp[-2].node), (yyvsp[-1].node));
                } else node1 = (yyvsp[-2].node);

                if (context & SWITCH_STRINGS) {
                    NODE_NO_LINE(node2, NODE_SWITCH_STRINGS);
                } else if (context & SWITCH_RANGES) {
		    NODE_NO_LINE(node2, NODE_SWITCH_RANGES);
		} else {
                    NODE_NO_LINE(node2, NODE_SWITCH_NUMBERS);
                }
                node2->l.expr = (yyvsp[-7].node);
                node2->r.expr = node1;
                prepare_cases(node2, (yyvsp[-8].number));
                context = (yyvsp[-9].number);
		(yyval.node) = node2;
		pop_n_locals((yyvsp[-3].decl).num);
            }

    break;

  case 107:

    {
#line 1101 "grammar/grammar.y.pre"
               if ((yyvsp[0].node)){
		   CREATE_STATEMENTS((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
               } else (yyval.node) = (yyvsp[-1].node);
           }

    break;

  case 108:

    {
#line 1107 "grammar/grammar.y.pre"
               if ((yyvsp[0].node)){
		   CREATE_STATEMENTS((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
               } else (yyval.node) = (yyvsp[-1].node);
           }

    break;

  case 109:

    {
#line 1113 "grammar/grammar.y.pre"
               (yyval.node) = 0;
           }

    break;

  case 110:

    {
#line 1121 "grammar/grammar.y.pre"
                (yyval.node) = (yyvsp[-1].node);
                (yyval.node)->v.expr = 0;

                add_to_mem_block(A_CASES, (char *)&((yyvsp[-1].node)), sizeof((yyvsp[-1].node)));
            }

    break;

  case 111:

    {
#line 1128 "grammar/grammar.y.pre"
                if ( (yyvsp[-3].node)->kind != NODE_CASE_NUMBER
                    || (yyvsp[-1].node)->kind != NODE_CASE_NUMBER )
                    yyerror("String case labels not allowed as range bounds");
                if ((yyvsp[-3].node)->r.number > (yyvsp[-1].node)->r.number) break;

		context |= SWITCH_RANGES;

                (yyval.node) = (yyvsp[-3].node);
                (yyval.node)->v.expr = (yyvsp[-1].node);

                add_to_mem_block(A_CASES, (char *)&((yyvsp[-3].node)), sizeof((yyvsp[-3].node)));
            }

    break;

  case 112:

    {
#line 1142 "grammar/grammar.y.pre"
                if (context & SWITCH_DEFAULT) {
                    yyerror("Duplicate default");
                    (yyval.node) = 0;
                    break;
                }
		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_DEFAULT;
                (yyval.node)->v.expr = 0;
                add_to_mem_block(A_CASES, (char *)&((yyval.node)), sizeof((yyval.node)));
                context |= SWITCH_DEFAULT;
            }

    break;

  case 113:

    {
#line 1158 "grammar/grammar.y.pre"
                if ((context & SWITCH_STRINGS) && (yyvsp[0].pointer_int))
                    yyerror("Mixed case label list not allowed");

                if ((yyvsp[0].pointer_int)) context |= SWITCH_NUMBERS;
		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_CASE_NUMBER;
                (yyval.node)->r.expr = (parse_node_t *)(yyvsp[0].pointer_int);
            }

    break;

  case 114:

    {
#line 1168 "grammar/grammar.y.pre"
		int str;

		str = store_prog_string((yyvsp[0].string));
                scratch_free((yyvsp[0].string));
                if (context & SWITCH_NUMBERS)
                    yyerror("Mixed case label list not allowed");
                context |= SWITCH_STRINGS;
		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_CASE_STRING;
                (yyval.node)->r.number = str;
            }

    break;

  case 115:

    {
#line 1184 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) | (yyvsp[0].pointer_int);
            }

    break;

  case 116:

    {
#line 1188 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) ^ (yyvsp[0].pointer_int);
            }

    break;

  case 117:

    {
#line 1192 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) & (yyvsp[0].pointer_int);
            }

    break;

  case 118:

    {
#line 1196 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) == (yyvsp[0].pointer_int);
            }

    break;

  case 119:

    {
#line 1200 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) != (yyvsp[0].pointer_int);
            }

    break;

  case 120:

    {
#line 1204 "grammar/grammar.y.pre"
                switch((yyvsp[-1].number)){
                    case F_GE: (yyval.pointer_int) = (yyvsp[-2].pointer_int) >= (yyvsp[0].pointer_int); break;
                    case F_LE: (yyval.pointer_int) = (yyvsp[-2].pointer_int) <= (yyvsp[0].pointer_int); break;
                    case F_GT: (yyval.pointer_int) = (yyvsp[-2].pointer_int) >  (yyvsp[0].pointer_int); break;
                }
            }

    break;

  case 121:

    {
#line 1212 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) < (yyvsp[0].pointer_int);
            }

    break;

  case 122:

    {
#line 1216 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) << (yyvsp[0].pointer_int);
            }

    break;

  case 123:

    {
#line 1220 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) >> (yyvsp[0].pointer_int);
            }

    break;

  case 124:

    {
#line 1224 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) + (yyvsp[0].pointer_int);
            }

    break;

  case 125:

    {
#line 1228 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) - (yyvsp[0].pointer_int);
            }

    break;

  case 126:

    {
#line 1232 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) * (yyvsp[0].pointer_int);
            }

    break;

  case 127:

    {
#line 1236 "grammar/grammar.y.pre"
                if ((yyvsp[0].pointer_int)) (yyval.pointer_int) = (yyvsp[-2].pointer_int) % (yyvsp[0].pointer_int); else yyerror("Modulo by zero");
            }

    break;

  case 128:

    {
#line 1240 "grammar/grammar.y.pre"
                if ((yyvsp[0].pointer_int)) (yyval.pointer_int) = (yyvsp[-2].pointer_int) / (yyvsp[0].pointer_int); else yyerror("Division by zero");
            }

    break;

  case 129:

    {
#line 1244 "grammar/grammar.y.pre"
                (yyval.pointer_int) = (yyvsp[-1].pointer_int);
            }

    break;

  case 130:

    {
#line 1248 "grammar/grammar.y.pre"
		(yyval.pointer_int) = (yyvsp[0].number);
	    }

    break;

  case 131:

    {
#line 1252 "grammar/grammar.y.pre"
                (yyval.pointer_int) = -(yyvsp[0].number);
            }

    break;

  case 132:

    {
#line 1256 "grammar/grammar.y.pre"
                (yyval.pointer_int) = !(yyvsp[0].number);
            }

    break;

  case 133:

    {
#line 1260 "grammar/grammar.y.pre"
                (yyval.pointer_int) = ~(yyvsp[0].number);
            }

    break;

  case 134:

    {
#line 1267 "grammar/grammar.y.pre"
		(yyval.node) = (yyvsp[0].node);
	}

    break;

  case 135:

    {
#line 1271 "grammar/grammar.y.pre"
		CREATE_TWO_VALUES((yyval.node), (yyvsp[0].node)->type, insert_pop_value((yyvsp[-2].node)), (yyvsp[0].node));
	}

    break;

  case 136:

    {
#line 1278 "grammar/grammar.y.pre"
#define LV_ILLEGAL 1
#define LV_RANGE 2
#define LV_INDEX 4
			/* Restrictive lvalues, but I think they make more sense :) */
			(yyval.node) = (yyvsp[0].node);
			switch((yyval.node)->kind) {
			default:
				yyerror("Illegal lvalue");
				break;
			case NODE_PARAMETER:
				(yyval.node)->kind = NODE_PARAMETER_LVALUE;
				break;
			case NODE_TERNARY_OP:
				(yyval.node)->v.number = (yyval.node)->r.expr->v.number;
			case NODE_OPCODE_1:
			case NODE_UNARY_OP_1:
			case NODE_BINARY_OP:
				if ((yyval.node)->v.number >= F_LOCAL && (yyval.node)->v.number <= F_MEMBER)
					(yyval.node)->v.number++; /* make it an lvalue */
				else if ((yyval.node)->v.number >= F_INDEX
						 && (yyval.node)->v.number <= F_RE_RANGE) {
					parse_node_t *node = (yyval.node);
					int flag = 0;
					do {
						switch(node->kind) {
						case NODE_PARAMETER:
							node->kind = NODE_PARAMETER_LVALUE;
							flag |= LV_ILLEGAL;
							break;
						case NODE_TERNARY_OP:
							node->v.number = node->r.expr->v.number;
						case NODE_OPCODE_1:
						case NODE_UNARY_OP_1:
						case NODE_BINARY_OP:
							if (node->v.number >= F_LOCAL
								&& node->v.number <= F_MEMBER) {
								node->v.number++;
								flag |= LV_ILLEGAL;
								break;
							} else if (node->v.number == F_INDEX ||
									   node->v.number == F_RINDEX) {
								node->v.number++;
								flag |= LV_INDEX;
								break;
							} else if (node->v.number >= F_ADD_EQ
									   && node->v.number <= F_ASSIGN) {
								if (!(flag & LV_INDEX)) {
									yyerror("Illegal lvalue, a possible lvalue is (x <assign> y)[a]");
								}
								if (node->r.expr->kind == NODE_BINARY_OP||
									node->r.expr->kind == NODE_TERNARY_OP){
									if (node->r.expr->v.number >= F_NN_RANGE_LVALUE && node->r.expr->v.number <= F_NR_RANGE_LVALUE)
										yyerror("Illegal to have (x[a..b] <assign> y) to be the beginning of an lvalue");
								}
								flag = LV_ILLEGAL;
								break;
							} else if (node->v.number >= F_NN_RANGE
									   && node->v.number <= F_RE_RANGE) {
								if (flag & LV_RANGE) {
									yyerror("Can't do range lvalue of range lvalue.");
									flag |= LV_ILLEGAL;
									break;
								}
								if (flag & LV_INDEX){
									yyerror("Can't do indexed lvalue of range lvalue.");
									flag |= LV_ILLEGAL;
									break;
								}
								if (node->v.number == F_NE_RANGE) {
									/* x[foo..] -> x[foo..<1] */
									parse_node_t *rchild = node->r.expr;
									node->kind = NODE_TERNARY_OP;
									CREATE_BINARY_OP(node->r.expr,
													 F_NR_RANGE_LVALUE,
													 0, 0, rchild);
									CREATE_NUMBER(node->r.expr->l.expr, 1);
								} else if (node->v.number == F_RE_RANGE) {
									/* x[<foo..] -> x[<foo..<1] */
									parse_node_t *rchild = node->r.expr;
									node->kind = NODE_TERNARY_OP;
									CREATE_BINARY_OP(node->r.expr,
													 F_RR_RANGE_LVALUE,
													 0, 0, rchild);
									CREATE_NUMBER(node->r.expr->l.expr, 1);
								} else
									node->r.expr->v.number++;
								flag |= LV_RANGE;
								node = node->r.expr->r.expr;
								continue;
							}
						default:
							yyerror("Illegal lvalue");
							flag = LV_ILLEGAL;
							break;
						}
						if ((flag & LV_ILLEGAL) || !(node = node->r.expr)) break;
					} while (1);
					break;
				} else
					yyerror("Illegal lvalue");
				break;
			}
		}

    break;

  case 137:

    {
#line 1386 "grammar/grammar.y.pre"
		parse_node_t *l = (yyvsp[-2].node), *r = (yyvsp[0].node);
		/* set this up here so we can change it below */

		CREATE_BINARY_OP((yyval.node), (yyvsp[-1].number), r->type, r, l);

		if (exact_types && !compatible_types(r->type, l->type) &&
			!((yyvsp[-1].number) == F_ADD_EQ
			  && r->type == TYPE_STRING &&
			  COMP_TYPE(l->type, TYPE_NUMBER))) {
			char buf[256];
			char *end = EndOf(buf);
			char *p;

			p = strput(buf, end, "Bad assignment");
			p = get_two_types(p, end, l->type, r->type);
			p = strput(p, end, ".");
			yyerror(buf);
		}

#ifdef DBVAR_NOASSIGN
		if (DBVAR_NODE_GET(l)) {
			char buf[256];
			char *end = EndOf(buf);
			char *p;

			p = strput(buf, end, "Bad dbvar assignment ");
			p = get_two_types(p, end, l->type, r->type);
			p = strput(p, end, ".");
			yyerror(buf);
		}
#endif
		/*
		  fix the bug of following:
		  int a = 10;
		  a *= 0.2;
		  then you get: a = 0

		  by onlyu 2012.6.27
		*/
		if ((yyvsp[-1].number) < F_ADD_EQ || (yyvsp[-1].number) > F_MOD_EQ) {
			(yyval.node)->l.expr = do_promotions(r, l->type);
		}
	}

    break;

  case 138:

    {
#line 1431 "grammar/grammar.y.pre"
		yyerror("Illegal LHS");
		CREATE_ERROR((yyval.node));
	}

    break;

  case 139:

    {
#line 1436 "grammar/grammar.y.pre"
		parse_node_t *p1 = (yyvsp[-2].node), *p2 = (yyvsp[0].node);

		if (exact_types && !compatible_types2(p1->type, p2->type)) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "Types in ?: do not match ");
		    p = get_two_types(p, end, p1->type, p2->type);
		    p = strput(p, end, ".");
		    yywarn(buf);
		}

		/* optimize if last expression did F_NOT */
		if (IS_NODE((yyvsp[-4].node), NODE_UNARY_OP, F_NOT)) {
		    /* !a ? b : c  --> a ? c : b */
		    CREATE_IF((yyval.node), (yyvsp[-4].node)->r.expr, p2, p1);
		} else {
		    CREATE_IF((yyval.node), (yyvsp[-4].node), p1, p2);
		}
		(yyval.node)->type = ((p1->type == p2->type) ? p1->type : TYPE_ANY);
	}

    break;

  case 140:

    {
#line 1460 "grammar/grammar.y.pre"
		CREATE_LAND_LOR((yyval.node), F_LOR, (yyvsp[-2].node), (yyvsp[0].node));
		if (IS_NODE((yyvsp[-2].node), NODE_LAND_LOR, F_LOR))
		    (yyvsp[-2].node)->kind = NODE_BRANCH_LINK;
	}

    break;

  case 141:

    {
#line 1466 "grammar/grammar.y.pre"
		CREATE_LAND_LOR((yyval.node), F_LAND, (yyvsp[-2].node), (yyvsp[0].node));
		if (IS_NODE((yyvsp[-2].node), NODE_LAND_LOR, F_LAND))
		    (yyvsp[-2].node)->kind = NODE_BRANCH_LINK;
	}

    break;

  case 142:

    {
#line 1472 "grammar/grammar.y.pre"
		if (is_boolean((yyvsp[-2].node)) && is_boolean((yyvsp[0].node)))
		    yywarn("bitwise operation on boolean values.");
		(yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_OR, "|");
	}

    break;

  case 143:

    {
#line 1478 "grammar/grammar.y.pre"
		(yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_XOR, "^");
	}

    break;

  case 144:

    {
#line 1482 "grammar/grammar.y.pre"
		int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;
		if (is_boolean((yyvsp[-2].node)) && is_boolean((yyvsp[0].node)))
		    yywarn("bitwise operation on boolean values.");
		if ((t1 & TYPE_MOD_ARRAY) || (t3 & TYPE_MOD_ARRAY)) {
		    if (t1 != t3) {
				if ((t1 != TYPE_ANY) && (t3 != TYPE_ANY) &&
					!(t1 & t3 & TYPE_MOD_ARRAY)) {
					char buf[256];
					char *end = EndOf(buf);
					char *p;

					p = strput(buf, end, "Incompatible types for & ");
					p = get_two_types(p, end, t1, t3);
					p = strput(p, end, ".");
					yyerror(buf);
				}
				t1 = TYPE_ANY | TYPE_MOD_ARRAY;
		    }
		    CREATE_BINARY_OP((yyval.node), F_AND, t1, (yyvsp[-2].node), (yyvsp[0].node));
		} else (yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_AND, "&");
	}

    break;

  case 145:

    {
#line 1505 "grammar/grammar.y.pre"
		if (exact_types && !compatible_types2((yyvsp[-2].node)->type, (yyvsp[0].node)->type)){
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "== always false because of incompatible types ");
		    p = get_two_types(p, end, (yyvsp[-2].node)->type, (yyvsp[0].node)->type);
		    p = strput(p, end, ".");
		    yyerror(buf);
		}
		/* x == 0 -> !x */
		if (IS_NODE((yyvsp[-2].node), NODE_NUMBER, 0)) {
		    CREATE_UNARY_OP((yyval.node), F_NOT, TYPE_NUMBER, (yyvsp[0].node));
		} else
			if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0)) {
				CREATE_UNARY_OP((yyval.node), F_NOT, TYPE_NUMBER, (yyvsp[-2].node));
			} else {
				CREATE_BINARY_OP((yyval.node), F_EQ, TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
			}
	}

    break;

  case 146:

    {
#line 1527 "grammar/grammar.y.pre"
		if (exact_types && !compatible_types2((yyvsp[-2].node)->type, (yyvsp[0].node)->type)){
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "!= always true because of incompatible types ");
		    p = get_two_types(p, end, (yyvsp[-2].node)->type, (yyvsp[0].node)->type);
		    p = strput(p, end, ".");
		    yyerror(buf);
		}
		CREATE_BINARY_OP((yyval.node), F_NE, TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
	}

    break;

  case 147:

    {
#line 1541 "grammar/grammar.y.pre"
		if (exact_types) {
		    int t1 = (yyvsp[-2].node)->type;
		    int t3 = (yyvsp[0].node)->type;

		    if (!COMP_TYPE(t1, TYPE_NUMBER)
				&& !COMP_TYPE(t1, TYPE_STRING)) {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Bad left argument to '");
				p = strput(p, end, get_f_name((yyvsp[-1].number)));
				p = strput(p, end, "' : \"");
				p = _get_type_name(p, end, t1);
				p = strput(p, end, "\"");
				yyerror(buf);
		    } else if (!COMP_TYPE(t3, TYPE_NUMBER)
					   && !COMP_TYPE(t3, TYPE_STRING)) {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Bad right argument to '");
				p = strput(p, end, get_f_name((yyvsp[-1].number)));
				p = strput(p, end, "' : \"");
				p = _get_type_name(p, end, t3);
				p = strput(p, end, "\"");
				yyerror(buf);
		    } else if (!compatible_types2(t1,t3)) {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Arguments to ");
				p = strput(p, end, get_f_name((yyvsp[-1].number)));
				p = strput(p, end, " do not have compatible types : ");
				p = get_two_types(p, end, t1, t3);
				yyerror(buf);
		    }
		}
		CREATE_BINARY_OP((yyval.node), (yyvsp[-1].number), TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
	}

    break;

  case 148:

    {
#line 1585 "grammar/grammar.y.pre"
		if (exact_types) {
			int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

			if (!COMP_TYPE(t1, TYPE_NUMBER)
				&& !COMP_TYPE(t1, TYPE_STRING)) {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Bad left argument to '<' : \"");
				p = _get_type_name(p, end, t1);
				p = strput(p, end, "\"");
				yyerror(buf);
			} else if (!COMP_TYPE(t3, TYPE_NUMBER)
					   && !COMP_TYPE(t3, TYPE_STRING)) {
				char buf[200];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Bad right argument to '<' : \"");
				p = _get_type_name(p, end, t3);
				p = strput(p, end, "\"");
				yyerror(buf);
			} else if (!compatible_types2(t1,t3)) {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Arguments to < do not have compatible types : ");
				p = get_two_types(p, end, t1, t3);
				yyerror(buf);
			}
		}
		CREATE_BINARY_OP((yyval.node), F_LT, TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
	}

    break;

  case 149:

    {
#line 1622 "grammar/grammar.y.pre"
		(yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_LSH, "<<");
	}

    break;

  case 150:

    {
#line 1626 "grammar/grammar.y.pre"
		(yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_RSH, ">>");
	}

    break;

  case 151:

    {
#line 1630 "grammar/grammar.y.pre"
		int result_type;

		if (exact_types) {
		    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

		    if (t1 == t3){
#ifdef CAST_CALL_OTHERS
				if (t1 == TYPE_UNKNOWN){
					yyerror("Bad arguments to '+' (unknown vs unknown)");
					result_type = TYPE_ANY;
				} else
#endif
					result_type = t1;
		    } else if (t1 == TYPE_ANY) {
				if (t3 == TYPE_FUNCTION) {
					yyerror("Bad right argument to '+' (function)");
					result_type = TYPE_ANY;
				} else {
					result_type = t3;
				}
		    } else if (t3 == TYPE_ANY) {
				if (t1 == TYPE_FUNCTION) {
					yyerror("Bad left argument to '+' (function)");
					result_type = TYPE_ANY;
				} else {
					result_type = t1;
				}
		    } else {
				switch(t1) {
			    case TYPE_STRING:
					if (t3 == TYPE_REAL || t3 == TYPE_NUMBER){
						result_type = TYPE_STRING;
					} else goto add_error;
					break;
			    case TYPE_NUMBER:
					if (t3 == TYPE_REAL || t3 == TYPE_STRING)
						result_type = t3;
					else goto add_error;
					break;
				case TYPE_REAL:
					if (t3 == TYPE_NUMBER) {
						result_type = TYPE_REAL;
					} else if (t3 == TYPE_STRING) {
						result_type = TYPE_STRING;
					}
					else goto add_error;
					break;
			    default:
					if (t1 & t3 & TYPE_MOD_ARRAY) {
						result_type = TYPE_ANY|TYPE_MOD_ARRAY;
						break;
					}
				add_error:
					{
						char buf[256];
						char *end = EndOf(buf);
						char *p;

						p = strput(buf, end, "Invalid argument types to '+' ");
						p = get_two_types(p, end, t1, t3);
						yyerror(buf);
						result_type = TYPE_ANY;
					}
				}
		    }
		} else
		    result_type = TYPE_ANY;

		switch ((yyvsp[-2].node)->kind) {
		case NODE_NUMBER:
		    /* 0 + X */
		    if ((yyvsp[-2].node)->v.number == 0 &&
				((yyvsp[0].node)->type == TYPE_NUMBER || (yyvsp[0].node)->type == TYPE_REAL)) {
				(yyval.node) = (yyvsp[0].node);
				break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.number += (yyvsp[0].node)->v.number;
				break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
				(yyval.node) = (yyvsp[0].node);
				(yyvsp[0].node)->v.real += (yyvsp[-2].node)->v.number;
				break;
		    }
		    /* swapping the nodes may help later constant folding */
		    if ((yyvsp[0].node)->type != TYPE_STRING && (yyvsp[0].node)->type != TYPE_ANY)
				CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[0].node), (yyvsp[-2].node));
		    else
				CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		case NODE_REAL:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.real += (yyvsp[0].node)->v.number;
				break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.real += (yyvsp[0].node)->v.real;
				break;
		    }
		    /* swapping the nodes may help later constant folding */
		    if ((yyvsp[0].node)->type != TYPE_STRING && (yyvsp[0].node)->type != TYPE_ANY)
				CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[0].node), (yyvsp[-2].node));
		    else
				CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		case NODE_STRING:
		    if ((yyvsp[0].node)->kind == NODE_STRING) {
				/* Combine strings */
				int n1, n2;
				char *new_, *s1, *s2;
				int l;

				n1 = (yyvsp[-2].node)->v.number;
				n2 = (yyvsp[0].node)->v.number;
				s1 = PROG_STRING(n1);
				s2 = PROG_STRING(n2);
				new_ = (char *)DXALLOC( (l = strlen(s1))+strlen(s2)+1, TAG_COMPILER, "combine string" );
				strcpy(new_, s1);
				strcat(new_ + l, s2);
				/* free old strings (ordering may help shrink table) */
				if (n1 > n2) {
					free_prog_string(n1); free_prog_string(n2);
				} else {
					free_prog_string(n2); free_prog_string(n1);
				}
				(yyval.node) = (yyvsp[-2].node);
				(yyval.node)->v.number = store_prog_string(new_);
				FREE(new_);
				break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		default:
		    /* X + 0 */
		    if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0) &&
				((yyvsp[-2].node)->type == TYPE_NUMBER || (yyvsp[-2].node)->type == TYPE_REAL)) {
				(yyval.node) = (yyvsp[-2].node);
				break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		}
	}

    break;

  case 152:

    {
#line 1779 "grammar/grammar.y.pre"
		int result_type;

		if (exact_types) {
		    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

		    if (t1 == t3){
				switch(t1){
			    case TYPE_ANY:
			    case TYPE_NUMBER:
			    case TYPE_REAL:
			        result_type = t1;
					break;
			    default:
					if (!(t1 & TYPE_MOD_ARRAY)){
						type_error("Bad argument number 1 to '-'", t1);
						result_type = TYPE_ANY;
					} else result_type = t1;
				}
		    } else if (t1 == TYPE_ANY){
				switch(t3){
			    case TYPE_REAL:
			    case TYPE_NUMBER:
			        result_type = t3;
					break;
			    default:
					if (!(t3 & TYPE_MOD_ARRAY)){
						type_error("Bad argument number 2 to '-'", t3);
						result_type = TYPE_ANY;
					} else result_type = t3;
				}
		    } else if (t3 == TYPE_ANY){
				switch(t1){
			    case TYPE_REAL:
			    case TYPE_NUMBER:
			        result_type = t1;
					break;
			    default:
					if (!(t1 & TYPE_MOD_ARRAY)){
						type_error("Bad argument number 1 to '-'", t1);
						result_type = TYPE_ANY;
					} else result_type = t1;
				}
		    } else if ((t1 == TYPE_REAL && t3 == TYPE_NUMBER) ||
					   (t3 == TYPE_REAL && t1 == TYPE_NUMBER)){
				result_type = TYPE_REAL;
		    } else if (t1 & t3 & TYPE_MOD_ARRAY){
				result_type = TYPE_MOD_ARRAY|TYPE_ANY;
		    } else {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Invalid types to '-' ");
				p = get_two_types(p, end, t1, t3);
				yyerror(buf);
				result_type = TYPE_ANY;
		    }
		} else result_type = TYPE_ANY;

		switch ((yyvsp[-2].node)->kind) {
		case NODE_NUMBER:
		    if ((yyvsp[-2].node)->v.number == 0) {
				CREATE_UNARY_OP((yyval.node), F_NEGATE, (yyvsp[0].node)->type, (yyvsp[0].node));
		    } else if ((yyvsp[0].node)->kind == NODE_NUMBER) {
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.number -= (yyvsp[0].node)->v.number;
		    } else if ((yyvsp[0].node)->kind == NODE_REAL) {
				(yyval.node) = (yyvsp[0].node);
				(yyvsp[0].node)->v.real = (yyvsp[-2].node)->v.number - (yyvsp[0].node)->v.real;
		    } else {
				CREATE_BINARY_OP((yyval.node), F_SUBTRACT, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    }
		    break;
		case NODE_REAL:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.real -= (yyvsp[0].node)->v.number;
		    } else if ((yyvsp[0].node)->kind == NODE_REAL) {
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.real -= (yyvsp[0].node)->v.real;
		    } else {
				CREATE_BINARY_OP((yyval.node), F_SUBTRACT, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    }
		    break;
		default:
		    /* optimize X-0 */
		    if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0)) {
				(yyval.node) = (yyvsp[-2].node);
		    }
		    CREATE_BINARY_OP((yyval.node), F_SUBTRACT, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		}
	}

    break;

  case 153:

    {
#line 1873 "grammar/grammar.y.pre"
		int result_type;

		if (exact_types){
		    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

		    if (t1 == t3){
				switch(t1){
			    case TYPE_MAPPING:
			    case TYPE_ANY:
			    case TYPE_NUMBER:
			    case TYPE_REAL:
			        result_type = t1;
					break;
				default:
					type_error("Bad argument number 1 to '*'", t1);
					result_type = TYPE_ANY;
				}
		    } else if (t1 == TYPE_ANY || t3 == TYPE_ANY){
				int t = (t1 == TYPE_ANY) ? t3 : t1;
				switch(t){
			    case TYPE_NUMBER:
			    case TYPE_REAL:
			    case TYPE_MAPPING:
			        result_type = t;
					break;
			    default:
					type_error((t1 == TYPE_ANY) ?
							   "Bad argument number 2 to '*'" :
							   "Bad argument number 1 to '*'",
							   t);
					result_type = TYPE_ANY;
				}
		    } else if ((t1 == TYPE_NUMBER && t3 == TYPE_REAL) ||
					   (t1 == TYPE_REAL && t3 == TYPE_NUMBER)){
				result_type = TYPE_REAL;
		    } else {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Invalid types to '*' ");
				p = get_two_types(p, end, t1, t3);
				yyerror(buf);
				result_type = TYPE_ANY;
		    }
		} else result_type = TYPE_ANY;

		switch ((yyvsp[-2].node)->kind) {
		case NODE_NUMBER:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
				(yyval.node) = (yyvsp[-2].node);
				(yyval.node)->v.number *= (yyvsp[0].node)->v.number;
				break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
				(yyval.node) = (yyvsp[0].node);
				(yyvsp[0].node)->v.real *= (yyvsp[-2].node)->v.number;
				break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_MULTIPLY, result_type, (yyvsp[0].node), (yyvsp[-2].node));
		    break;
		case NODE_REAL:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.real *= (yyvsp[0].node)->v.number;
				break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.real *= (yyvsp[0].node)->v.real;
				break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_MULTIPLY, result_type, (yyvsp[0].node), (yyvsp[-2].node));
		    break;
		default:
		    CREATE_BINARY_OP((yyval.node), F_MULTIPLY, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		}
	}

    break;

  case 154:

    {
#line 1953 "grammar/grammar.y.pre"
		(yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_MOD, "%");
	}

    break;

  case 155:

    {
#line 1957 "grammar/grammar.y.pre"
		int result_type;

		if (exact_types){
		    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

		    if (t1 == t3){
				switch(t1){
			    case TYPE_NUMBER:
			    case TYPE_REAL:
				case TYPE_ANY:
			        result_type = t1;
					break;
			    default:
					type_error("Bad argument 1 to '/'", t1);
					result_type = TYPE_ANY;
				}
		    } else if (t1 == TYPE_ANY || t3 == TYPE_ANY){
				int t = (t1 == TYPE_ANY) ? t3 : t1;
				if (t == TYPE_REAL || t == TYPE_NUMBER)
					result_type = t;
				else {
					type_error(t1 == TYPE_ANY ?
							   "Bad argument 2 to '/'" :
							   "Bad argument 1 to '/'", t);
					result_type = TYPE_ANY;
				}
		    } else if ((t1 == TYPE_NUMBER && t3 == TYPE_REAL) ||
					   (t1 == TYPE_REAL && t3 == TYPE_NUMBER)) {
				result_type = TYPE_REAL;
		    } else {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Invalid types to '/' ");
				p = get_two_types(p, end, t1, t3);
				yyerror(buf);
				result_type = TYPE_ANY;
		    }
		} else result_type = TYPE_ANY;

		/* constant expressions */
		switch ((yyvsp[-2].node)->kind) {
		case NODE_NUMBER:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
				if ((yyvsp[0].node)->v.number == 0) {
					yyerror("Divide by zero in constant");
					(yyval.node) = (yyvsp[-2].node);
					break;
				}
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.number /= (yyvsp[0].node)->v.number;
				break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
				if ((yyvsp[0].node)->v.real == 0.0) {
					yyerror("Divide by zero in constant");
					(yyval.node) = (yyvsp[-2].node);
					break;
				}
				(yyval.node) = (yyvsp[0].node);
				(yyvsp[0].node)->v.real = ((yyvsp[-2].node)->v.number / (yyvsp[0].node)->v.real);
				break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_DIVIDE, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		case NODE_REAL:
		    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
				if ((yyvsp[0].node)->v.number == 0) {
					yyerror("Divide by zero in constant");
					(yyval.node) = (yyvsp[-2].node);
					break;
				}
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.real /= (yyvsp[0].node)->v.number;
				break;
		    }
		    if ((yyvsp[0].node)->kind == NODE_REAL) {
				if ((yyvsp[0].node)->v.real == 0.0) {
					yyerror("Divide by zero in constant");
					(yyval.node) = (yyvsp[-2].node);
					break;
				}
				(yyval.node) = (yyvsp[-2].node);
				(yyvsp[-2].node)->v.real /= (yyvsp[0].node)->v.real;
				break;
		    }
		    CREATE_BINARY_OP((yyval.node), F_DIVIDE, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		    break;
		default:
		    CREATE_BINARY_OP((yyval.node), F_DIVIDE, result_type, (yyvsp[-2].node), (yyvsp[0].node));
		}
	}

    break;

  case 156:

    {
#line 2052 "grammar/grammar.y.pre"
		CREATE_UNARY_OP((yyval.node), F_PRE_INC, 0, (yyvsp[0].node));
		if (exact_types){
			switch((yyvsp[0].node)->type){
			case TYPE_NUMBER:
			case TYPE_ANY:
			case TYPE_REAL:
				{
					(yyval.node)->type = (yyvsp[0].node)->type;
					break;
				}

			default:
				{
					(yyval.node)->type = TYPE_ANY;
					type_error("Bad argument 1 to ++x", (yyvsp[0].node)->type);
				}
			}
		} else (yyval.node)->type = TYPE_ANY;
	}

    break;

  case 157:

    {
#line 2073 "grammar/grammar.y.pre"
		CREATE_UNARY_OP((yyval.node), F_PRE_DEC, 0, (yyvsp[0].node));
		if (exact_types){
			switch((yyvsp[0].node)->type){
			case TYPE_NUMBER:
			case TYPE_ANY:
			case TYPE_REAL:
				{
					(yyval.node)->type = (yyvsp[0].node)->type;
					break;
				}

			default:
				{
					(yyval.node)->type = TYPE_ANY;
					type_error("Bad argument 1 to --x", (yyvsp[0].node)->type);
				}
			}
		} else (yyval.node)->type = TYPE_ANY;

	}

    break;

  case 158:

    {
#line 2095 "grammar/grammar.y.pre"
		if ((yyvsp[0].node)->kind == NODE_NUMBER) {
		    (yyval.node) = (yyvsp[0].node);
		    (yyval.node)->v.number = !((yyval.node)->v.number);
		} else {
		    CREATE_UNARY_OP((yyval.node), F_NOT, TYPE_NUMBER, (yyvsp[0].node));
		}
	}

    break;

  case 159:

    {
#line 2104 "grammar/grammar.y.pre"
		if (exact_types && !IS_TYPE((yyvsp[0].node)->type, TYPE_NUMBER))
		    type_error("Bad argument to ~", (yyvsp[0].node)->type);
		if ((yyvsp[0].node)->kind == NODE_NUMBER) {
		    (yyval.node) = (yyvsp[0].node);
		    (yyval.node)->v.number = ~(yyval.node)->v.number;
		} else {
		    CREATE_UNARY_OP((yyval.node), F_COMPL, TYPE_NUMBER, (yyvsp[0].node));
		}
	}

    break;

  case 160:

    {
#line 2115 "grammar/grammar.y.pre"
		int result_type;
		if (exact_types){
		    int t = (yyvsp[0].node)->type;
		    if (!COMP_TYPE(t, TYPE_NUMBER)){
				type_error("Bad argument to unary '-'", t);
				result_type = TYPE_ANY;
		    } else result_type = t;
		} else result_type = TYPE_ANY;

		switch ((yyvsp[0].node)->kind) {
		case NODE_NUMBER:
		    (yyval.node) = (yyvsp[0].node);
		    (yyval.node)->v.number = -(yyval.node)->v.number;
		    break;
		case NODE_REAL:
		    (yyval.node) = (yyvsp[0].node);
		    (yyval.node)->v.real = -(yyval.node)->v.real;
		    break;
		default:
		    CREATE_UNARY_OP((yyval.node), F_NEGATE, result_type, (yyvsp[0].node));
		}
	}

    break;

  case 161:

    {
#line 2139 "grammar/grammar.y.pre"
		CREATE_UNARY_OP((yyval.node), F_POST_INC, 0, (yyvsp[-1].node));
		(yyval.node)->v.number = F_POST_INC;
		if (exact_types){
			switch((yyvsp[-1].node)->type){
			case TYPE_NUMBER:
		    case TYPE_ANY:
			case TYPE_REAL:
				{
					(yyval.node)->type = (yyvsp[-1].node)->type;
					break;
				}

			default:
				{
					(yyval.node)->type = TYPE_ANY;
					type_error("Bad argument 1 to x++", (yyvsp[-1].node)->type);
				}
			}
		} else (yyval.node)->type = TYPE_ANY;
	}

    break;

  case 162:

    {
#line 2161 "grammar/grammar.y.pre"
		CREATE_UNARY_OP((yyval.node), F_POST_DEC, 0, (yyvsp[-1].node));
                if (exact_types){
                    switch((yyvsp[-1].node)->type){
		    case TYPE_NUMBER:
		    case TYPE_ANY:
		    case TYPE_REAL:
		    {
			(yyval.node)->type = (yyvsp[-1].node)->type;
			break;
		    }

		    default:
		    {
			(yyval.node)->type = TYPE_ANY;
			type_error("Bad argument 1 to x--", (yyvsp[-1].node)->type);
		    }
                    }
                } else (yyval.node)->type = TYPE_ANY;
	    }

    break;

  case 163:

    {
#line 2182 "grammar/grammar.y.pre"
            /*
               add grammar sugar of class:
               first, declare class:
               class abc_t {
                    int a;
                    int b;
               }
               then u can use abc_t.a,abc_t.b as the index of the class instance;
               by chenyh 2016.09.01
             */
            if ((yyvsp[-2].ihe)->dn.class_num == -1) {
                char buf[256];
                char *end = EndOf(buf);
                char *p;

                p = strput(buf, end, "Undefined class '");
                p = strput(p, end, (yyvsp[-2].ihe)->name);
                p = strput(p, end, "'");
                yyerror(buf);
                CREATE_ERROR((yyval.node));
            } else {
                int type = (yyvsp[-2].ihe)->dn.class_num | TYPE_MOD_CLASS;
                int index = lookup_class_member(CLASS_IDX(type),
                        (yyvsp[0].string),
                        NULL);
                CREATE_NUMBER((yyval.node), index);
            }
            scratch_free((yyvsp[0].string));
        }

    break;

  case 169:

    {
#line 2221 "grammar/grammar.y.pre"
		if (exact_types && !IS_TYPE(exact_types, TYPE_VOID))
		    yywarn("Non-void functions must return a value.");
		CREATE_RETURN((yyval.node), 0);
	    }

    break;

  case 170:

    {
#line 2227 "grammar/grammar.y.pre"
		if (exact_types && !compatible_types((yyvsp[-1].node)->type, exact_types & ~NAME_TYPE_MOD)) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "Type of returned value doesn't match function return type ");
		    p = get_two_types(p, end, (yyvsp[-1].node)->type, exact_types & ~NAME_TYPE_MOD);
		    yyerror(buf);
		}
		if (IS_NODE((yyvsp[-1].node), NODE_NUMBER, 0)) {
		    CREATE_RETURN((yyval.node), 0);
		} else {
		    CREATE_RETURN((yyval.node), (yyvsp[-1].node));
		}
	    }

    break;

  case 171:

    {
#line 2247 "grammar/grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), 0);
	    }

    break;

  case 172:

    {
#line 2251 "grammar/grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), (yyvsp[0].node));
	}

    break;

  case 173:

    {
#line 2255 "grammar/grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), (yyvsp[-1].node));
	    }

    break;

  case 174:

    {
#line 2262 "grammar/grammar.y.pre"
			CREATE_EXPR_NODE((yyval.node), (yyvsp[0].node), 0);
	    }

    break;

  case 175:

    {
#line 2266 "grammar/grammar.y.pre"
		CREATE_EXPR_NODE((yyval.node), (yyvsp[-1].node), 1);
	}

    break;

  case 176:

    {
#line 2273 "grammar/grammar.y.pre"
		(yyvsp[0].node)->kind = 1;

		(yyval.node) = (yyvsp[0].node);
	    }

    break;

  case 177:

    {
#line 2279 "grammar/grammar.y.pre"
		(yyvsp[0].node)->kind = 0;

		(yyval.node) = (yyvsp[-2].node);
		(yyval.node)->kind++;
		(yyval.node)->l.expr->r.expr = (yyvsp[0].node);
		(yyval.node)->l.expr = (yyvsp[0].node);
	    }

    break;

  case 178:

    {
#line 2291 "grammar/grammar.y.pre"
		/* this is a dummy node */
		CREATE_EXPR_LIST((yyval.node), 0);
	    }

    break;

  case 179:

    {
#line 2296 "grammar/grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), (yyvsp[0].node));
	}

    break;

  case 180:

    {
#line 2300 "grammar/grammar.y.pre"
		CREATE_EXPR_LIST((yyval.node), (yyvsp[-1].node));
	    }

    break;

  case 181:

    {
#line 2307 "grammar/grammar.y.pre"
		(yyval.node) = new_node_no_line();
		(yyval.node)->kind = 2;
		(yyval.node)->v.expr = (yyvsp[0].node);
		(yyval.node)->r.expr = 0;
		(yyval.node)->type = 0;
		/* we keep track of the end of the chain in the left nodes */
		(yyval.node)->l.expr = (yyval.node);
            }

    break;

  case 182:

    {
#line 2317 "grammar/grammar.y.pre"
		parse_node_t *expr;

		expr = new_node_no_line();
		expr->kind = 0;
		expr->v.expr = (yyvsp[0].node);
		expr->r.expr = 0;
		expr->type = 0;

		(yyvsp[-2].node)->l.expr->r.expr = expr;
		(yyvsp[-2].node)->l.expr = expr;
		(yyvsp[-2].node)->kind += 2;
		(yyval.node) = (yyvsp[-2].node);
	    }

    break;

  case 183:

    {
#line 2335 "grammar/grammar.y.pre"
		CREATE_TWO_VALUES((yyval.node), 0, (yyvsp[-2].node), (yyvsp[0].node));
            }

    break;

  case 185:

    {
#line 2342 "grammar/grammar.y.pre"
		int i;
		if ((i = (yyvsp[0].ihe)->dn.local_num) != -1) {
			CREATE_OPCODE_1((yyval.node), F_LOCAL, type_of_locals_ptr[i],i & 0xff);
			if (current_function_context)
				current_function_context->num_locals++;
		} else if ((i = (yyvsp[0].ihe)->dn.global_num) != -1) {
			if (current_function_context)
				current_function_context->bindable = FP_NOT_BINDABLE;
			CREATE_OPCODE_1((yyval.node), F_GLOBAL,
							VAR_TEMP(i)->type & ~NAME_TYPE_MOD, i);
#ifdef DBVAR_NOASSIGN
			DBVAR_NODE_SET((yyval.node), VAR_TEMP(i)->type);
#endif
			if (VAR_TEMP(i)->type & NAME_HIDDEN) {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Illegal to use private variable '");
				p = strput(p, end, (yyvsp[0].ihe)->name);
				p = strput(p, end, "'");
				yyerror(buf);
			}
		} else {
			ident_hash_elem_t *ihe = lookup_ident((yyvsp[0].ihe)->name);
			if (ihe && ihe->dn.upvalue_num >=0) { // upvalue
				UpVal *uv = find_upvalue((yyvsp[0].ihe)->name);
				if (!uv) {
					uv = add_upvalue((yyvsp[0].ihe)->name, ihe->dn.upvalue_type);
				}
				if (uv)
					CREATE_OPCODE_1((yyval.node), F_UPVALUE, uv->type,uv->index & 0xff);
				else {
					char buf[256];
					sprintf(buf, "add upvalue failed name=%s, type=%s", (yyvsp[0].ihe)->name, get_type_name(ihe->dn.upvalue_type));
					yyerror(buf);

				}
				
			} else if (ihe && (ihe->dn.function_num >= 0 || ihe->dn.simul_num >= 0 || ihe->dn.efun_num >=0) ){
				(yyval.node) = new_node();
				(yyval.node)->kind = NODE_FUNCTION_CONSTRUCTOR;
				(yyval.node)->type = TYPE_FUNCTION;
				(yyval.node)->r.expr = 0;
				if (ihe->dn.function_num >= 0)
					(yyval.node)->v.number = (ihe->dn.function_num << 8) | FP_LOCAL;
				else if(ihe->dn.simul_num >= 0)
					(yyval.node)->v.number = (ihe->dn.simul_num << 8) | FP_SIMUL;
				else if (ihe->dn.efun_num >= 0)
					(yyval.node)->v.number = (ihe->dn.efun_num << 8) | FP_EFUN;
			} else {
				char buf[256];
				char *end = EndOf(buf);
				char *p;
					
				p = strput(buf, end, "Undefined variable (defined name) '");
				p = strput(p, end, (yyvsp[0].ihe)->name);
				p = strput(p, end, "'");
				if (current_number_of_locals < CFG_MAX_LOCAL_VARIABLES) {
					add_local_name((yyvsp[0].ihe)->name, TYPE_ANY);
				}
				CREATE_OPCODE_1((yyval.node), F_LOCAL, TYPE_ANY, 0);
				yyerror(buf);
			}
		}
	}

    break;

  case 186:

    {
#line 2410 "grammar/grammar.y.pre"
		char buf[256];
		char *end = EndOf(buf);
		char *p;

		p = strput(buf, end, "Undefined variable here'");
		p = strput(p, end, (yyvsp[0].string));
		p = strput(p, end, "'");
		if (current_number_of_locals < CFG_MAX_LOCAL_VARIABLES) {
			add_local_name((yyvsp[0].string), TYPE_ANY);
		}
		CREATE_OPCODE_1((yyval.node), F_LOCAL, TYPE_ANY, 0);
		yyerror(buf);
		scratch_free((yyvsp[0].string));
	}

    break;

  case 187:

    {
#line 2426 "grammar/grammar.y.pre"
		CREATE_PARAMETER((yyval.node), TYPE_ANY, (yyvsp[0].number));
	}

    break;

  case 188:

    {
#line 2430 "grammar/grammar.y.pre"
		(yyval.contextp) = current_function_context;
		/* already flagged as an error */
		if (current_function_context)
		    current_function_context = current_function_context->parent;
            }

    break;

  case 189:

    {
#line 2437 "grammar/grammar.y.pre"
		parse_node_t *node;

		current_function_context = (yyvsp[-2].contextp);

		if (!current_function_context || current_function_context->num_parameters == -2) {
		    /* This was illegal, and error'ed when the '$' token
		     * was returned.
		     */
		    CREATE_ERROR((yyval.node));
		} else {
		    CREATE_OPCODE_1((yyval.node), F_LOCAL, (yyvsp[-1].node)->type,
				    current_function_context->values_list->kind++);

		    node = new_node_no_line();
		    node->type = 0;
		    current_function_context->values_list->l.expr->r.expr = node;
		    current_function_context->values_list->l.expr = node;
		    node->r.expr = 0;
		    node->v.expr = (yyvsp[-1].node);
		}
	    }

    break;

  case 190:

    {
#line 2460 "grammar/grammar.y.pre"
		if (!IS_CLASS((yyvsp[-2].node)->type)) {
		    yyerror("Left argument of -> is not a class");
		    CREATE_ERROR((yyval.node));
		} else {
		    CREATE_UNARY_OP_1((yyval.node), F_MEMBER, 0, (yyvsp[-2].node), 0);
		    (yyval.node)->l.number = lookup_class_member(CLASS_IDX((yyvsp[-2].node)->type),
						       (yyvsp[0].string),
						       &((yyval.node)->type));
		}
		scratch_free((yyvsp[0].string));
            }

    break;

  case 191:

    {
#line 2473 "grammar/grammar.y.pre"
			if ((yyvsp[-5].node)->type != TYPE_MAPPING &&
               (yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number < 0)
		    yywarn("00 A negative constant as the second element of arr[x..y] no longer means indexing from the end.  Use arr[x..<y]");
                (yyval.node) = make_range_node(F_NN_RANGE, (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node));
            }

    break;

  case 192:

    {
#line 2482 "grammar/grammar.y.pre"
                (yyval.node) = make_range_node(F_RN_RANGE, (yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[-1].node));
            }

    break;

  case 193:

    {
#line 2486 "grammar/grammar.y.pre"
		if ((yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number <= 1)
		    (yyval.node) = make_range_node(F_RE_RANGE, (yyvsp[-7].node), (yyvsp[-4].node), 0);
		else
		    (yyval.node) = make_range_node(F_RR_RANGE, (yyvsp[-7].node), (yyvsp[-4].node), (yyvsp[-1].node));
            }

    break;

  case 194:

    {
#line 2493 "grammar/grammar.y.pre"
		if ((yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number <= 1)
		    (yyval.node) = make_range_node(F_NE_RANGE, (yyvsp[-6].node), (yyvsp[-4].node), 0);
		else
		    (yyval.node) = make_range_node(F_NR_RANGE, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
            }

    break;

  case 195:

    {
#line 2500 "grammar/grammar.y.pre"
                (yyval.node) = make_range_node(F_NE_RANGE, (yyvsp[-4].node), (yyvsp[-2].node), 0);
            }

    break;

  case 196:

    {
#line 2504 "grammar/grammar.y.pre"
                (yyval.node) = make_range_node(F_RE_RANGE, (yyvsp[-5].node), (yyvsp[-2].node), 0);
            }

    break;

  case 197:

    {
#line 2508 "grammar/grammar.y.pre"
                if (IS_NODE((yyvsp[-4].node), NODE_CALL, F_AGGREGATE)
		    && (yyvsp[-1].node)->kind == NODE_NUMBER) {
                    int i = (yyvsp[-1].node)->v.number;
                    if (i < 1 || i > (yyvsp[-4].node)->l.number)
                        yyerror("Illegal index to array constant.");
                    else {
                        parse_node_t *node = (yyvsp[-4].node)->r.expr;
                        i = (yyvsp[-4].node)->l.number - i;
                        while (i--)
                            node = node->r.expr;
                        (yyval.node) = node->v.expr;
                        break;
                    }
                }
		CREATE_BINARY_OP((yyval.node), F_RINDEX, 0, (yyvsp[-1].node), (yyvsp[-4].node));
                if (exact_types) {
		    switch((yyvsp[-4].node)->type) {
		    case TYPE_MAPPING:
			yyerror("Illegal index for mapping.");
		    case TYPE_ANY:
			(yyval.node)->type = TYPE_ANY;
			break;
		    case TYPE_STRING:
		    case TYPE_BUFFER:
			(yyval.node)->type = TYPE_NUMBER;
			if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
			    type_error("Bad type of index", (yyvsp[-1].node)->type);
			break;

		    default:
			if ((yyvsp[-4].node)->type & TYPE_MOD_ARRAY) {
			    (yyval.node)->type = (yyvsp[-4].node)->type & ~TYPE_MOD_ARRAY;
			    if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
				type_error("Bad type of index", (yyvsp[-1].node)->type);
			} else {
			    type_error("Value indexed has a bad type ", (yyvsp[-4].node)->type);
			    (yyval.node)->type = TYPE_ANY;
			}
		    }
		} else (yyval.node)->type = TYPE_ANY;
            }

    break;

  case 198:

    {
#line 2551 "grammar/grammar.y.pre"
		/* Something stupid like ({ 1, 2, 3 })[1]; we take the
		 * time to optimize this because people who don't understand
		 * the preprocessor often write things like:
		 *
		 * #define MY_ARRAY ["foo", "bar", "bazz"]
		 * ...
		 * ... MY_ARRAY[1] ...
		 *
		 * which of course expands to the above.
		 */
                if (IS_NODE((yyvsp[-3].node), NODE_CALL, F_AGGREGATE) && (yyvsp[-1].node)->kind == NODE_NUMBER) {
                    int i = (yyvsp[-1].node)->v.number;
                    if (i < 0 || i >= (yyvsp[-3].node)->l.number)
					yyerror("Illegal index to array constant.");
                    else {
                        parse_node_t *node = (yyvsp[-3].node)->r.expr;
                        while (i--)
                            node = node->r.expr;
                        (yyval.node) = node->v.expr;
                        break;
                    }
                }
			if ((yyvsp[-3].node)->type != TYPE_MAPPING && (yyvsp[-3].node)->type != TYPE_ANY &&
                (yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number < 0)
					yywarn("11 A negative constant in arr[x] no longer means indexing from the end.  Use arr[<x]");
                CREATE_BINARY_OP((yyval.node), F_INDEX, 0, (yyvsp[-1].node), (yyvsp[-3].node));
                if (exact_types) {
		    switch((yyvsp[-3].node)->type) {
		    case TYPE_MAPPING:
		    case TYPE_ANY:
			(yyval.node)->type = TYPE_ANY;
			break;
		    case TYPE_STRING:
		    case TYPE_BUFFER:
			(yyval.node)->type = TYPE_NUMBER;
			if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
			    type_error("Bad type of index", (yyvsp[-1].node)->type);
			break;

		    default:
			if ((yyvsp[-3].node)->type & TYPE_MOD_ARRAY) {
			    (yyval.node)->type = (yyvsp[-3].node)->type & ~TYPE_MOD_ARRAY;
			    if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
				type_error("Bad type of index", (yyvsp[-1].node)->type);
			} else if IS_CLASS((yyvsp[-3].node)->type) {
                /*
                   add grammar sugar of class:
                   when we declare a class instance:
                      abc_t ins = new abc_t(a:1, b:2);
                   we can use ins[abc_t.a] instead of using ins->a.
                   by chenyh 2016.09.01
                 */
			    (yyval.node)->type = TYPE_ANY;
			    if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
				type_error("Bad type of index", (yyvsp[-1].node)->type);
            } else {
			    type_error("Value indexed has a bad type ", (yyvsp[-3].node)->type);
			    (yyval.node)->type = TYPE_ANY;
			}
                    }
                } else (yyval.node)->type = TYPE_ANY;
            }

    break;

  case 200:

    {
#line 2618 "grammar/grammar.y.pre"
		(yyval.node) = (yyvsp[-1].node);
	    }

    break;

  case 202:

    {
#line 2624 "grammar/grammar.y.pre"
			;
		}

    break;

  case 203:

    {
#line 2628 "grammar/grammar.y.pre"
		CREATE_CALL((yyval.node), F_AGGREGATE_ASSOC, TYPE_MAPPING, (yyvsp[-1].node));
	    }

    break;

  case 204:

    {
#line 2632 "grammar/grammar.y.pre"
		CREATE_CALL((yyval.node), F_AGGREGATE, TYPE_ANY | TYPE_MOD_ARRAY, (yyvsp[-1].node));
	}

    break;

  case 206:

    {
#line 2640 "grammar/grammar.y.pre"
			(yyval.node) = (yyvsp[0].decl).node;
	    }

    break;

  case 207:

    {
#line 2644 "grammar/grammar.y.pre"
		(yyval.node) = insert_pop_value((yyvsp[-1].node));
	}

    break;

  case 208:

    {
#line 2651 "grammar/grammar.y.pre"
		(yyval.number) = context;
		context = SPECIAL_CONTEXT;
	}

    break;

  case 209:

    {
#line 2656 "grammar/grammar.y.pre"
		CREATE_CATCH((yyval.node), (yyvsp[0].node));
		context = (yyvsp[-1].number);
	}

    break;

  case 210:

    {
#line 2664 "grammar/grammar.y.pre"
		int p = (yyvsp[-1].node)->v.number;
		CREATE_LVALUE_EFUN((yyval.node), TYPE_NUMBER, (yyvsp[-1].node));
		CREATE_BINARY_OP_1((yyval.node)->l.expr, F_SSCANF, 0, (yyvsp[-4].node), (yyvsp[-2].node), p);
	    }

    break;

  case 211:

    {
#line 2673 "grammar/grammar.y.pre"
		(yyval.number) = context;
		context = SPECIAL_CONTEXT;
	}

    break;

  case 212:

    {
#line 2678 "grammar/grammar.y.pre"
		CREATE_TIME_EXPRESSION((yyval.node), (yyvsp[0].node));
		context = (yyvsp[-1].number);
	}

    break;

  case 213:

    {
#line 2686 "grammar/grammar.y.pre"
	        (yyval.node) = new_node_no_line();
		(yyval.node)->r.expr = 0;
	        (yyval.node)->v.number = 0;
	    }

    break;

  case 214:

    {
#line 2692 "grammar/grammar.y.pre"
		parse_node_t *insert;

		(yyval.node) = (yyvsp[0].node);
		insert = new_node_no_line();
		insert->r.expr = (yyvsp[0].node)->r.expr;
		insert->l.expr = (yyvsp[-1].node);
		(yyvsp[0].node)->r.expr = insert;
		(yyval.node)->v.number++;
	    }

    break;

  case 215:

    {
#line 2706 "grammar/grammar.y.pre"
		CREATE_STRING((yyval.node), (yyvsp[0].string));
		scratch_free((yyvsp[0].string));
	    }

    break;

  case 217:

    {
#line 2715 "grammar/grammar.y.pre"
		(yyval.string) = (yyvsp[-1].string);
	    }

    break;

  case 218:

    {
#line 2719 "grammar/grammar.y.pre"
		(yyval.string) = scratch_join((yyvsp[-2].string), (yyvsp[0].string));
	    }

    break;

  case 220:

    {
#line 2727 "grammar/grammar.y.pre"
		(yyval.string) = scratch_join((yyvsp[-1].string), (yyvsp[0].string));
	    }

    break;

  case 221:

    {
#line 2734 "grammar/grammar.y.pre"
		(yyval.node) = 0;
    }

    break;

  case 222:

    {
#line 2738 "grammar/grammar.y.pre"
		(yyval.node) = new_node();
		(yyval.node)->l.expr = (parse_node_t *)(yyvsp[-2].string);
		(yyval.node)->v.expr = (yyvsp[0].node);
		(yyval.node)->r.expr = 0;
    }

    break;

  case 223:

    {
#line 2749 "grammar/grammar.y.pre"
		(yyval.node) = (yyvsp[0].node);
    }

    break;

  case 224:

    {
#line 2753 "grammar/grammar.y.pre"
		(yyval.node) = (yyvsp[0].node);
		(yyval.node)->r.expr = (yyvsp[-2].node);
    }

    break;

  case 225:

    {
#line 2762 "grammar/grammar.y.pre"
		(yyval.node) = validate_efun_call((yyvsp[-3].number),(yyvsp[-1].node));
	}

    break;

  case 226:

    {
#line 2766 "grammar/grammar.y.pre"
		parse_node_t *node;

		if ((yyvsp[-3].ihe)->dn.class_num == -1) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "Undefined class '");
		    p = strput(p, end, (yyvsp[-3].ihe)->name);
		    p = strput(p, end, "'");
		    yyerror(buf);
		    CREATE_ERROR((yyval.node));
		    node = (yyvsp[-1].node);
		    while (node) {
				scratch_free((char *)node->l.expr);
				node = node->r.expr;
		    }
		} else {
		    int type = (yyvsp[-3].ihe)->dn.class_num | TYPE_MOD_CLASS;
		    if ((node = (yyvsp[-1].node))) {
				CREATE_TWO_VALUES((yyval.node), type, 0, 0);
				(yyval.node)->l.expr = reorder_class_values((yyvsp[-3].ihe)->dn.class_num,node);
				CREATE_OPCODE_1((yyval.node)->r.expr, F_NEW_CLASS, type, (yyvsp[-3].ihe)->dn.class_num);
		    } else {
				CREATE_OPCODE_1((yyval.node), F_NEW_EMPTY_CLASS, type, (yyvsp[-3].ihe)->dn.class_num);
		    }
		}
	}

    break;

  case 227:

    {
#line 2796 "grammar/grammar.y.pre"
		if ((yyvsp[0].ihe)->dn.class_num == -1) {
		    char buf[256];
		    char *end = EndOf(buf);
		    char *p;

		    p = strput(buf, end, "Undefined class '");
		    p = strput(p, end, (yyvsp[0].ihe)->name);
		    p = strput(p, end, "'");
		    yyerror(buf);
		    CREATE_ERROR((yyval.node));
		} else {
		    int type = (yyvsp[0].ihe)->dn.class_num | TYPE_MOD_CLASS;
			CREATE_OPCODE_1((yyval.node), F_NEW_EMPTY_CLASS, type, (yyvsp[0].ihe)->dn.class_num);
		}
	}

    break;

  case 228:

    {
#line 2813 "grammar/grammar.y.pre"
		int f;

		(yyval.node) = (yyvsp[-1].node);
		if ((f = (yyvsp[-3].ihe)->dn.function_num) != -1) {
			if (FUNCTION_FLAGS(f) & NAME_HIDDEN) {
				char buf[256];
				char *end = EndOf(buf);
				char *p;

				p = strput(buf, end, "Illegal to call private function '");
				p = strput(p, end, (yyvsp[-3].ihe)->name);
				p = strput(p, end, "'");
				yyerror(buf);
			}
			if (current_function_context)
				current_function_context->bindable = FP_NOT_BINDABLE;

			(yyval.node)->kind = NODE_CALL_1;
			(yyval.node)->v.number = F_CALL_FUNCTION_BY_ADDRESS;
			(yyval.node)->l.number = f;
			(yyval.node)->type = validate_function_call(f, (yyvsp[-1].node)->r.expr);
		} else if ((f=(yyvsp[-3].ihe)->dn.simul_num) != -1) {
				(yyval.node)->kind = NODE_CALL_1;
				(yyval.node)->v.number = F_SIMUL_EFUN;
				(yyval.node)->l.number = f;
				(yyval.node)->type = (SIMUL(f)->type) & ~NAME_TYPE_MOD;
		} else {
			if ((f=(yyvsp[-3].ihe)->dn.efun_num) != -1) {
				(yyval.node) = validate_efun_call(f, (yyvsp[-1].node));
			} else {
				ident_hash_elem_t *ihe = lookup_ident((yyvsp[-3].ihe)->name);

				if (!ihe) { // can not find the variable
					char buf[256];
					char *end = EndOf(buf);
					char *p;
					char *n = (yyvsp[-3].ihe)->name;
					if (*n == ':') n++;
					p = strput(buf, end, "Undefined function variable ");
					p = strput(p, end, n);
					yyerror(buf);
				}

				ident_hash_elem_t *eval = lookup_ident("evaluate"); // get the efun "evaluate"

				// get the local or global function
				parse_node_t *func_pn;
				int i;
				if ((i = ihe->dn.local_num) != -1) {
					CREATE_OPCODE_1(func_pn, F_LOCAL, type_of_locals_ptr[i],i & 0xff);
				} else if (ihe && ihe->dn.upvalue_num >=0) { // upvalue
					UpVal *uv = find_upvalue((yyvsp[-3].ihe)->name);
					if (!uv)
						uv = add_upvalue((yyvsp[-3].ihe)->name, ihe->dn.upvalue_type);
					CREATE_OPCODE_1(func_pn, F_UPVALUE, uv->type,uv->index & 0xff);
				} else if ((i = (yyvsp[-3].ihe)->dn.global_num) != -1) {
					CREATE_OPCODE_1(func_pn, F_GLOBAL, VAR_TEMP(i)->type & ~NAME_TYPE_MOD, i);
				}

				// push the local function into the font of arguments
				parse_node_t *expr_func;
				CREATE_EXPR_NODE(expr_func, func_pn, 0);

				parse_node_t *args = (yyvsp[-1].node)->r.expr;
				if (args) {
					expr_func->kind = args->kind + 1;
					args->kind = 0;
					expr_func->l.expr = args->l.expr;
					expr_func->r.expr = args;
				} else {
					expr_func->kind = 1;
					expr_func->l.expr = 0;
					expr_func->r.expr = 0;
				}

				parse_node_t *final_args;
				CREATE_EXPR_LIST(final_args, expr_func);
					
				// call evaluate(func, args...)
				(yyval.node) = validate_efun_call(eval->dn.efun_num, final_args);
			}
		}
	}

    break;

  case 229:

    {
#line 2898 "grammar/grammar.y.pre"
	      char *name = (yyvsp[-3].string);

	      (yyval.node) = (yyvsp[-1].node);

	      if (current_function_context)
			  current_function_context->bindable = FP_NOT_BINDABLE;

	      if (*name == ':') {
			  int f;

			  f = arrange_call_inherited(name + 1, (yyval.node));
		      /* Can't do this; f may not be the correct function
				 entry.  It might be overloaded.

				 validate_function_call(f, $$->r.expr)
		      */
	      } else {
			  int f;
			  ident_hash_elem_t *ihe;

			  f = (ihe = lookup_ident(name)) ? ihe->dn.function_num : -1;
			  (yyval.node)->kind = NODE_CALL_1;
			  (yyval.node)->v.number = F_CALL_FUNCTION_BY_ADDRESS;
			  if (f!=-1) {
				  /* The only way this can happen is if function_name
				   * below made the function name.  The lexer would
				   * return L_DEFINED_NAME instead.
				   */
				  (yyval.node)->type = validate_function_call(f, (yyvsp[-1].node)->r.expr);
			  } else {
				  f = define_new_function(name, 0, 0,
										  NAME_UNDEFINED | NAME_PROTOTYPE, 0);
				  f = COMPILER_FUNC(f)->runtime_index;
			  }
			  (yyval.node)->l.number = f;
			  /*
			   * Check if this function has been defined.
			   * But, don't complain yet about functions defined
			   * by inheritance.
			   */
			  if (exact_types && (FUNCTION_FLAGS(f) & NAME_UNDEFINED)) {
				  char buf[256];
				  char *end = EndOf(buf);
				  char *p;
				  char *n = (yyvsp[-3].string);
				  if (*n == ':') n++;
				  /* prevent some errors */
				  FUNCTION_FLAGS(f) &= ~NAME_UNDEFINED;
				  FUNCTION_FLAGS(f) |= (NAME_INHERITED | NAME_VARARGS);
				  p = strput(buf, end, "Undefined function ");
				  p = strput(p, end, n);
				  yyerror(buf);
			  }
			  if (!(FUNCTION_FLAGS(f) & NAME_UNDEFINED))
				  (yyval.node)->type = FUNCTION_DEF(f)->type;
			  else
				  (yyval.node)->type = TYPE_ANY;  /* Just a guess */
	      }
	      scratch_free(name);
	}

    break;

  case 230:

    {
#line 2960 "grammar/grammar.y.pre"
		ident_hash_elem_t *eval = lookup_ident("evaluate"); // get the efun "evaluate"

		// get the local or global function

		// push the local function into the font of arguments
		parse_node_t *expr_func;
		CREATE_EXPR_NODE(expr_func, (yyvsp[-3].node), 0);

		parse_node_t *args = (yyvsp[-1].node)->r.expr;
		if (args) {
			expr_func->kind = args->kind + 1;
			args->kind = 0;
			expr_func->l.expr = args->l.expr;
			expr_func->r.expr = args;
		} else {
			expr_func->kind = 1;
			expr_func->l.expr = 0;
			expr_func->r.expr = 0;
		}

		parse_node_t *final_args;
		CREATE_EXPR_LIST(final_args, expr_func);
					
		// call evaluate(func, args...)
		(yyval.node) = validate_efun_call(eval->dn.efun_num, final_args);
	}

    break;

  case 231:

    {
#line 2988 "grammar/grammar.y.pre"
		parse_node_t *expr, *expr2;
		(yyval.node) = (yyvsp[-1].node);
		(yyval.node)->kind = NODE_EFUN;
		(yyval.node)->l.number = (yyval.node)->v.number + 2;
		(yyval.node)->v.number = F_CALL_OTHER;
#ifdef CAST_CALL_OTHERS
		(yyval.node)->type = TYPE_UNKNOWN;
#else
                (yyval.node)->type = TYPE_ANY;
#endif
		expr = new_node_no_line();
		expr->type = 0;
		expr->v.expr = (yyvsp[-5].node);

		expr2 = new_node_no_line();
		expr2->type = 0;
		CREATE_STRING(expr2->v.expr, (yyvsp[-3].string));
		scratch_free((yyvsp[-3].string));

		/* insert the two nodes */
		expr2->r.expr = (yyval.node)->r.expr;
		expr->r.expr = expr2;
		(yyval.node)->r.expr = expr;
	    }

    break;

  case 232:

    {
#line 3014 "grammar/grammar.y.pre"
	        parse_node_t *expr;

		(yyval.node) = (yyvsp[-1].node);
		(yyval.node)->kind = NODE_EFUN;
		(yyval.node)->l.number = (yyval.node)->v.number + 1;
		(yyval.node)->v.number = F_EVALUATE;
#ifdef CAST_CALL_OTHERS
		(yyval.node)->type = TYPE_UNKNOWN;
#else
		(yyval.node)->type = TYPE_ANY;
#endif
		expr = new_node_no_line();
		expr->type = 0;
		expr->v.expr = (yyvsp[-4].node);
		expr->r.expr = (yyval.node)->r.expr;
		(yyval.node)->r.expr = expr;
	    }

    break;

  case 233:

    {
#line 3034 "grammar/grammar.y.pre"
	//svalue_t *res;
	ident_hash_elem_t *ihe;

	(yyval.number) = (ihe = lookup_ident((yyvsp[0].string))) ? ihe->dn.efun_num : -1;
	if ((yyval.number) == -1) {
	    char buf[256];
	    char *end = EndOf(buf);
	    char *p;

	    p = strput(buf, end, "Unknown efun: ");
	    p = strput(p, end, (yyvsp[0].string));
	    yyerror(buf);
	} else {
		/* // 去掉了override关于APPLY_*的判断， -- by canoe
	    push_malloced_string(the_file_name(current_file));
	    share_and_push_string($3);
	    push_malloced_string(add_slash(main_file_name()));
	    res = safe_apply_master_ob(APPLY_VALID_OVERRIDE, 3);
	    if (!MASTER_APPROVED(res)) {
		yyerror("Invalid simulated efunction override");
		$$ = -1;
	    }
		*/
	}
	scratch_free((yyvsp[0].string));
      }

    break;

  case 235:

    {
#line 3066 "grammar/grammar.y.pre"
		int l = strlen((yyvsp[0].string)) + 1;
		char *p;
		/* here we be a bit cute.  we put a : on the front so we
		 * don't have to strchr for it.  Here we do:
		 * "name" -> ":::name"
		 */
		(yyval.string) = scratch_realloc((yyvsp[0].string), l + 3);
		p = (yyval.string) + l;
		while (p--,l--)
		    *(p+3) = *p;
		strncpy((yyval.string), ":::", 3);
	    }

    break;

  case 236:

    {
#line 3080 "grammar/grammar.y.pre"
		int z, l = strlen((yyvsp[0].string)) + 1;
		char *p;
		/* <type> and "name" -> ":type::name" */
		z = strlen(compiler_type_names[(yyvsp[-2].type)]) + 3; /* length of :type:: */
		(yyval.string) = scratch_realloc((yyvsp[0].string), l + z);
		p = (yyval.string) + l;
		while (p--,l--)
		    *(p+z) = *p;
		(yyval.string)[0] = ':';
		strncpy((yyval.string) + 1, compiler_type_names[(yyvsp[-2].type)], z - 3);
		(yyval.string)[z-2] = ':';
		(yyval.string)[z-1] = ':';
	    }

    break;

  case 237:

    {
#line 3095 "grammar/grammar.y.pre"
		int l = strlen((yyvsp[-2].string));
		/* "ob" and "name" -> ":ob::name" */
		(yyval.string) = scratch_alloc(l + strlen((yyvsp[0].string)) + 4);
		*((yyval.string)) = ':';
		strcpy((yyval.string) + 1, (yyvsp[-2].string));
		strcpy((yyval.string) + l + 1, "::");
		strcpy((yyval.string) + l + 3, (yyvsp[0].string));
		scratch_free((yyvsp[-2].string));
		scratch_free((yyvsp[0].string));
	    }

    break;

  case 238:

    {
#line 3110 "grammar/grammar.y.pre"
		/* x != 0 -> x */
		if (IS_NODE((yyvsp[-3].node), NODE_BINARY_OP, F_NE)) {
		    if (IS_NODE((yyvsp[-3].node)->r.expr, NODE_NUMBER, 0))
			(yyvsp[-3].node) = (yyvsp[-3].node)->l.expr;
		    else if (IS_NODE((yyvsp[-3].node)->l.expr, NODE_NUMBER, 0))
			     (yyvsp[-3].node) = (yyvsp[-3].node)->r.expr;
		}

		/* TODO: should optimize if (0), if (1) here.
		 * Also generalize this.
		 */

		if ((yyvsp[-1].node) == 0) {
		    if ((yyvsp[0].node) == 0) {
			/* if (x) ; -> x; */
			(yyval.node) = insert_pop_value((yyvsp[-3].node));
			break;
		    } else {
			/* if (x) {} else y; -> if (!x) y; */
			parse_node_t *repl;

			CREATE_UNARY_OP(repl, F_NOT, TYPE_NUMBER, (yyvsp[-3].node));
			(yyvsp[-3].node) = repl;
			(yyvsp[-1].node) = (yyvsp[0].node);
			(yyvsp[0].node) = 0;
		    }
		}
		CREATE_IF((yyval.node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
	    }

    break;

  case 239:

    {
#line 3144 "grammar/grammar.y.pre"
		(yyval.node) = 0;
	    }

    break;

  case 240:

    {
#line 3148 "grammar/grammar.y.pre"
		(yyval.node) = (yyvsp[0].node);
	}

    break;

  case 241:

    {
#line 3156 "grammar/grammar.y.pre"
		if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0)) {
		    CREATE_RETURN((yyval.node), 0);
		} else {
		    CREATE_RETURN((yyval.node), (yyvsp[0].node));
		}
	}

    break;

  case 242:

    {
#line 3173 "grammar/grammar.y.pre"
		push_local_count();
	}

    break;

  case 243:

    {
#line 3177 "grammar/grammar.y.pre"
		(yyval.decl).node = (yyvsp[0].node);
		(yyval.decl).num = get_local_count();
		pop_local_count();
	}

    break;

  case 245:

    {
#line 3187 "grammar/grammar.y.pre"
		push_closure();
		if ((yyvsp[0].type) != TYPE_FUNCTION) yyerror("Reserved type name unexpected.");
		(yyval.func_block).num_local = current_number_of_locals;
		(yyval.func_block).max_num_locals = max_num_locals;
		(yyval.func_block).context = context;
		(yyval.func_block).save_current_type = current_type;
		(yyval.func_block).save_exact_types = exact_types;
		if (type_of_locals_ptr + max_num_locals + CFG_MAX_LOCAL_VARIABLES >= &type_of_locals[type_of_locals_size])
		    reallocate_locals();
		deactivate_current_locals();
		locals_ptr += current_number_of_locals;
		type_of_locals_ptr += max_num_locals;
		runtime_locals_ptr += current_number_of_locals;
		max_num_locals = current_number_of_locals = 0;
		push_function_context();
		current_function_context->num_parameters = -1;
		exact_types = TYPE_ANY;
		context = 0;
	}

    break;

  case 246:

    {
#line 3208 "grammar/grammar.y.pre"
		if ((yyvsp[-2].argument).flags & ARG_IS_PROTO) {
			yyerror("Missing name for function argument");
		}
		if ((yyvsp[-2].argument).flags & ARG_IS_VARARGS) {
		    yyerror("Anonymous varargs functions aren't implemented");
		}
		if (!(yyvsp[0].decl).node) {
		    CREATE_RETURN((yyval.node), 0);
		} else if ((yyvsp[0].decl).node->kind != NODE_RETURN &&
			   ((yyvsp[0].decl).node->kind != NODE_TWO_VALUES || (yyvsp[0].decl).node->r.expr->kind != NODE_RETURN)) {
		    parse_node_t *replacement;
		    CREATE_STATEMENTS(replacement, (yyvsp[0].decl).node, 0);
		    CREATE_RETURN(replacement->r.expr, 0);
		    (yyvsp[0].decl).node = replacement;
		}

		(yyval.node) = new_node();
		(yyval.node)->kind = NODE_ANON_FUNC;
		(yyval.node)->type = TYPE_FUNCTION;
		(yyval.node)->r.expr = (yyvsp[0].decl).node;

		// dear with upvalue
		
		//int local_num = (max_num_locals - $4.num_arg);
		// build expr_list
		parse_node_t *upvalue_list = 0, *upvalue_head = 0;
		Closure *c = current_closure();
		int i; 
		for (i = 0; i < c->upvalue_num; i++) {
			UpVal *uv = &(c->upvalues[i]);
			parse_node_t *upvalue_node;
			LocalVal *lv = find_local_in_parent_closure(c, uv->name);
			if (lv) { // in the parent closure
				CREATE_OPCODE_1(upvalue_node, F_LOCAL, lv->type, lv->index & 0xff);
			} else { // not in the parent closure, maybe in parent's parent
				UpVal *puv = find_upvalue_inclosure(parent_closure(c), uv->name);
				if (puv) {
					CREATE_OPCODE_1(upvalue_node, F_UPVALUE, puv->type, puv->index & 0xff);
				} else {
					char buf[256];
					sprintf(buf, "upvalue %s not find", uv->name);
					yyerror(buf);
				}
			}

			parse_node_t *upvalue_expr;
			CREATE_EXPR_NODE(upvalue_expr, upvalue_node, 0);
			upvalue_expr->kind = 0;
			// chan expr list
			if (upvalue_list) {
				upvalue_list->r.expr = upvalue_expr;
			}
			if (!upvalue_head) {
				upvalue_head = upvalue_expr;
			}
			upvalue_head->kind ++;
			upvalue_list = upvalue_expr;
		}
		(yyval.node)->l.expr = upvalue_head;
		// upvalue ended
		(yyval.node)->v.expr = new_node();
		(yyval.node)->v.expr->v.number = c->upvalue_num; // number upvalue
		(yyval.node)->v.expr->l.number = (max_num_locals - (yyvsp[-2].argument).num_arg); // number locals
		(yyval.node)->v.expr->r.number = (yyvsp[-2].argument).num_arg; // number argument

		/*
		char buf[256];
		sprintf(buf, "arg_num=%d, local_num=%d, upvalue_num=%d",
				$$->v.expr->r.number,
				$$->v.expr->l.number,
				$$->v.expr->v.number);
		yywarn(buf);
		*/
		if (current_function_context->bindable)
		    (yyval.node)->v.expr->r.number |= 0x10000;
		free_all_local_names();

		current_number_of_locals = (yyvsp[-4].func_block).num_local;
		max_num_locals = (yyvsp[-4].func_block).max_num_locals;
		context = (yyvsp[-4].func_block).context;
		current_type = (yyvsp[-4].func_block).save_current_type;
		exact_types = (yyvsp[-4].func_block).save_exact_types;
		pop_function_context();

		//current_function_context->num_locals += num_locals;

		locals_ptr -= current_number_of_locals;
		type_of_locals_ptr -= max_num_locals;
		runtime_locals_ptr -= current_number_of_locals;
		reactivate_current_locals();
		pop_closure();
	}

    break;



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




#line 3302 "grammar/grammar.y.pre"

