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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "gram.y" /* yacc.c:339  */

 /*
 ======================================================================
 CTREE Version 0.09
 Written by Shaun Flisakowski (1995)
 ======================================================================
  This program is provided free of charge on an "as is" basis without
  warranty of any kind, either express or implied.  Acceptance and use
  of this program constitutes the user's understanding that (s)he will
  have no recourse for any actual or consequential damages, including,
  but not limited to, lost profits or savings, arising out of the use
  of or inability to use this program.  
 ======================================================================
 */

/* grammar File for C - Shaun Flisakowski */
/* Grammar was constructed with the assistance of:
    "C - A Reference Manual" (Fourth Edition),
    by Samuel P Harbison, and Guy L Steele Jr. */



#include <malloc.h>
#include <stdio.h>
#include <errno.h>
#include <setjmp.h>

#include "lexer.h"
#include "tree.h"
#include "symtab.h"
#include "token.h"
#include "globals.h"


extern  void yyerror(char *);

extern  int errno;
extern  int err_cnt;
extern  int yylex(YYSTYPE *lvalp);
extern  int yyparse (void);

treenode *parse_include(char *filename);
static void insert_decl(leafnode *leaf, treenode *def, treenode*);
static void insert_typedef(leafnode *leaf, treenode *def, treenode*);
static void insert_component(leafnode *leaf, treenode *def,
                             treenode *container);

static void add_params_to_symtab(treenode *funcdecl);

/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1

/*  int  yydebug = 1;  */

/* ###################################################### */
#line 186 "gram.y" /* yacc.c:339  */

/* 1 if we explained undeclared var errors.  */
/*  static int undeclared_variable_notice = 0;  */

#line 127 "gram.c" /* yacc.c:339  */

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
   by #include "gram.h".  */
#ifndef YY_YY_GRAM_H_INCLUDED
# define YY_YY_GRAM_H_INCLUDED
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
    IDENT = 258,
    STRING = 259,
    FIELD_NAME = 260,
    TYPEDEF_NAME = 261,
    TAG = 262,
    CHAR_CONST = 263,
    INUM = 264,
    RNUM = 265,
    COMMENT = 266,
    PP_LINE = 267,
    PP_INCLUDE = 268,
    PP_DEFINE = 269,
    PP_UNDEF = 270,
    PP_ERROR = 271,
    PP_IF = 272,
    PP_IFDEF = 273,
    PP_IFNDEF = 274,
    PP_ELSE = 275,
    PP_ELIF = 276,
    PP_ENDIF = 277,
    PP_IDENT = 278,
    PP_PRAGMA = 279,
    INVALID = 280,
    AUTO = 281,
    BREAK = 282,
    CASE = 283,
    CHAR = 284,
    CONST = 285,
    CONT = 286,
    DEFLT = 287,
    DO = 288,
    DOUBLE = 289,
    ELSE = 290,
    ENUM = 291,
    EXTRN = 292,
    IF = 293,
    FOR = 294,
    PARFOR = 295,
    FLOAT = 296,
    GOTO = 297,
    INT = 298,
    LONG = 299,
    REGISTR = 300,
    RETURN = 301,
    SHORT = 302,
    SGNED = 303,
    STATIC = 304,
    STRUCT = 305,
    SWITCH = 306,
    TYPEDEF = 307,
    UNION = 308,
    UNSGNED = 309,
    VOID = 310,
    VOLATILE = 311,
    WHILE = 312,
    PLUS_EQ = 313,
    MINUS_EQ = 314,
    STAR_EQ = 315,
    DIV_EQ = 316,
    MOD_EQ = 317,
    B_NOT_EQ = 318,
    B_AND_EQ = 319,
    B_OR_EQ = 320,
    B_XOR_EQ = 321,
    L_SHIFT_EQ = 322,
    R_SHIFT_EQ = 323,
    EQUAL = 324,
    LESS_EQ = 325,
    GRTR_EQ = 326,
    NOT_EQ = 327,
    RPAREN = 328,
    RBRCKT = 329,
    LBRACE = 330,
    RBRACE = 331,
    SEMICOLON = 332,
    COMMA = 333,
    ELLIPSIS = 334,
    LB_SIGN = 335,
    DOUB_LB_SIGN = 336,
    BACKQUOTE = 337,
    AT = 338,
    DOLLAR = 339,
    CPP_INCLUDE = 340,
    CPP_DEFINE = 341,
    CPP_LINE = 342,
    PARBLOCK = 343,
    COMMA_OP = 344,
    EQ = 345,
    ASSIGN = 346,
    QUESTMARK = 347,
    COLON = 348,
    COMMA_SEP = 349,
    OR = 350,
    AND = 351,
    B_OR = 352,
    B_XOR = 353,
    B_AND = 354,
    COMP_EQ = 355,
    COMP_ARITH = 356,
    LESS = 357,
    GRTR = 358,
    L_SHIFT = 359,
    R_SHIFT = 360,
    PLUS = 361,
    MINUS = 362,
    STAR = 363,
    DIV = 364,
    MOD = 365,
    CAST = 366,
    UNARY = 367,
    NOT = 368,
    B_NOT = 369,
    SIZEOF = 370,
    INCR = 371,
    DECR = 372,
    HYPERUNARY = 373,
    ARROW = 374,
    DOT = 375,
    LPAREN = 376,
    LBRCKT = 377,
    FOPT = 378
  };
#endif

/* Value type.  */



int yyparse (void);

#endif /* !YY_YY_GRAM_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 296 "gram.c" /* yacc.c:358  */

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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  124
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  142
/* YYNRULES -- Number of rules.  */
#define YYNRULES  284
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  422

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   378

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   193,   193,   200,   210,   217,   218,   226,   231,   236,
     241,   247,   281,   285,   295,   308,   311,   314,   315,   323,
     332,   339,   342,   345,   352,   361,   367,   373,   379,   385,
     391,   398,   404,   410,   416,   422,   428,   435,   441,   447,
     454,   459,   468,   474,   479,   487,   488,   491,   492,   493,
     494,   497,   506,   512,   518,   524,   531,   538,   544,   554,
     566,   577,   586,   600,   615,   616,   617,   620,   621,   632,
     633,   641,   642,   650,   656,   657,   665,   666,   674,   675,
     683,   689,   690,   698,   699,   707,   708,   716,   717,   725,
     726,   734,   735,   743,   744,   745,   746,   747,   748,   749,
     750,   751,   752,   755,   762,   768,   774,   781,   787,   793,
     799,   805,   806,   815,   818,   821,   825,   828,   831,   834,
     835,   843,   847,   848,   853,   859,   866,   867,   868,   869,
     870,   871,   874,   883,   884,   887,   894,   902,   905,   908,
     909,   917,   928,   935,   938,   939,   942,   943,   944,   947,
     950,   953,   954,   957,   981,   987,   990,   996,   999,  1002,
    1009,  1016,  1025,  1032,  1042,  1045,  1048,  1049,  1058,  1061,
    1064,  1065,  1073,  1074,  1082,  1083,  1093,  1096,  1099,  1100,
    1110,  1113,  1116,  1117,  1118,  1119,  1120,  1123,  1124,  1125,
    1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,
    1138,  1139,  1142,  1143,  1146,  1151,  1152,  1156,  1159,  1162,
    1166,  1169,  1186,  1192,  1193,  1201,  1202,  1210,  1222,  1225,
    1231,  1250,  1256,  1275,  1281,  1282,  1290,  1298,  1299,  1307,
    1308,  1312,  1315,  1324,  1327,  1328,  1331,  1337,  1346,  1349,
    1352,  1359,  1362,  1363,  1369,  1370,  1378,  1386,  1395,  1403,
    1410,  1411,  1418,  1421,  1424,  1425,  1433,  1434,  1442,  1449,
    1456,  1463,  1467,  1476,  1479,  1480,  1483,  1492,  1493,  1499,
    1507,  1513,  1519,  1527,  1533,  1542,  1551,  1559,  1567,  1576,
    1577,  1580,  1581,  1582,  1583
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "STRING", "FIELD_NAME",
  "TYPEDEF_NAME", "TAG", "CHAR_CONST", "INUM", "RNUM", "COMMENT",
  "PP_LINE", "PP_INCLUDE", "PP_DEFINE", "PP_UNDEF", "PP_ERROR", "PP_IF",
  "PP_IFDEF", "PP_IFNDEF", "PP_ELSE", "PP_ELIF", "PP_ENDIF", "PP_IDENT",
  "PP_PRAGMA", "INVALID", "AUTO", "BREAK", "CASE", "CHAR", "CONST", "CONT",
  "DEFLT", "DO", "DOUBLE", "ELSE", "ENUM", "EXTRN", "IF", "FOR", "PARFOR",
  "FLOAT", "GOTO", "INT", "LONG", "REGISTR", "RETURN", "SHORT", "SGNED",
  "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION", "UNSGNED", "VOID",
  "VOLATILE", "WHILE", "PLUS_EQ", "MINUS_EQ", "STAR_EQ", "DIV_EQ",
  "MOD_EQ", "B_NOT_EQ", "B_AND_EQ", "B_OR_EQ", "B_XOR_EQ", "L_SHIFT_EQ",
  "R_SHIFT_EQ", "EQUAL", "LESS_EQ", "GRTR_EQ", "NOT_EQ", "RPAREN",
  "RBRCKT", "LBRACE", "RBRACE", "SEMICOLON", "COMMA", "ELLIPSIS",
  "LB_SIGN", "DOUB_LB_SIGN", "BACKQUOTE", "AT", "DOLLAR", "CPP_INCLUDE",
  "CPP_DEFINE", "CPP_LINE", "PARBLOCK", "COMMA_OP", "EQ", "ASSIGN",
  "QUESTMARK", "COLON", "COMMA_SEP", "OR", "AND", "B_OR", "B_XOR", "B_AND",
  "COMP_EQ", "COMP_ARITH", "LESS", "GRTR", "L_SHIFT", "R_SHIFT", "PLUS",
  "MINUS", "STAR", "DIV", "MOD", "CAST", "UNARY", "NOT", "B_NOT", "SIZEOF",
  "INCR", "DECR", "HYPERUNARY", "ARROW", "DOT", "LPAREN", "LBRCKT", "FOPT",
  "$accept", "program", "trans_unit", "top_level_decl", "func_def",
  "enter_scope", "func_spec", "opt_decl_list", "decl_list", "cmpnd_stemnt",
  "opt_stemnt_list", "stemnt_list", "stemnt", "parblock_stemnt",
  "parblock_body", "parblock_block", "expr_stemnt", "labeled_stemnt",
  "cond_stemnt", "iter_stemnt", "switch_stemnt", "break_stemnt",
  "continue_stemnt", "fopt_stemnt", "return_stemnt", "goto_stemnt",
  "null_stemnt", "if_stemnt", "if_else_stemnt", "do_stemnt",
  "while_stemnt", "for_stemnt", "parfor_stemnt", "label", "cond_expr",
  "log_or_expr", "log_and_expr", "log_neg_expr", "bitwise_or_expr",
  "bitwise_xor_expr", "bitwise_and_expr", "bitwise_neg_expr", "cast_expr",
  "equality_expr", "relational_expr", "shift_expr", "additive_expr",
  "mult_expr", "unary_expr", "sizeof_expr", "unary_minus_expr",
  "unary_plus_expr", "addr_expr", "indirection_expr", "preinc_expr",
  "predec_expr", "assign_expr", "opt_const_expr", "const_expr", "opt_expr",
  "expr", "comma_expr", "prim_expr", "paren_expr", "postfix_expr",
  "subscript_expr", "comp_select_expr", "postinc_expr", "postdec_expr",
  "opt_expr_list", "expr_list", "named_label", "case_label", "deflt_label",
  "add_op", "mult_op", "equality_op", "relation_op", "shift_op",
  "declaration", "opt_comment", "opt_decl_specs", "decl_specs",
  "comp_decl_specs", "opt_comp_decl_specs", "init_decl",
  "opt_init_decl_list", "init_decl_list", "initializer_list",
  "initializer", "opt_comma", "type_qual_list", "opt_type_qual_list",
  "storage_class", "type_spec", "enum_type_spec", "struct_type_spec",
  "typedef_name", "union_type_spec", "opt_tag", "tag", "enum_type_define",
  "enum_type_ref", "enum_def_list", "enum_const_def", "enum_constant",
  "opt_trailing_comma", "struct_type_define", "struct_type_ref",
  "union_type_define", "union_type_ref", "field_list", "comp_decl",
  "comp_decl_list", "comp_declarator", "simple_comp", "bit_field", "width",
  "type_qual", "type_name", "opt_declarator", "declarator",
  "direct_declarator", "simple_decl", "pointer_start", "pointer",
  "opt_param_type_list", "param_type_list", "param_list", "param_decl",
  "ident_list", "ident", "field_ident", "typename_as_ident", "abs_decl",
  "direct_abs_decl", "array_decl", "direct_comp_select",
  "indirect_comp_select", "func_call", "assign_op", "constant", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378
};
# endif

#define YYPACT_NINF -238

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-238)))

#define YYTABLE_NINF -240

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     564,    11,  -238,  -238,  -238,  -238,  -238,  -238,  -238,    49,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,    49,  -238,
      49,  -238,  -238,  -238,     0,    28,    46,   621,  -238,  -238,
      10,  -238,    28,  1143,  1143,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  1143,  1111,   -25,  -238,   -55,
      30,  -238,  -238,  -238,  -238,  -238,   -17,     6,  -238,     9,
       6,    42,     6,     0,  -238,  -238,    -4,  -238,    11,  -238,
      -1,  -238,  -238,  -238,    33,     8,   887,  -238,  -238,  -238,
    -238,  -238,  1111,  -238,    28,   996,   433,  -238,   -25,   109,
    -238,  -238,  -238,  -238,  -238,  1111,  -238,    28,   527,  -238,
    -238,    25,  -238,  -238,    31,    47,    48,  -238,   -28,  -238,
    -238,  -238,  -238,  -238,   433,   433,   433,   433,   433,   433,
     690,   764,   764,   678,  -238,   -38,    58,  -238,    36,    32,
      67,  -238,  -238,    73,    74,    -6,    34,   -31,    52,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,   106,  -238,  -238,
     105,  -238,  -238,   -27,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,   112,  -238,   103,  1172,  1172,   292,
    -238,   527,  -238,  -238,   710,   433,  -238,    35,  -238,    23,
    -238,   942,  -238,   192,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,   678,  -238,   245,  -238,  -238,   123,   124,   -73,   125,
     433,   433,   433,   433,   433,   433,  -238,   433,  -238,   433,
    -238,  -238,   433,  -238,  -238,   433,  -238,  -238,  -238,   433,
    -238,  -238,   433,  -238,   433,  -238,  -238,    56,    56,   433,
     433,   109,   126,   433,    28,  1172,  1029,  -238,  1172,  1060,
      92,   107,   122,   433,   127,  -238,   445,    82,    84,    85,
     192,   433,    86,    88,  -238,    10,   135,  -238,   137,   393,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,   121,
     140,  -238,  -238,  -238,   142,  -238,   148,  -238,   149,   150,
      23,  1143,   433,  -238,  -238,  -238,   153,  -238,  -238,   804,
      55,  -238,   433,   130,    58,    36,    32,    67,    73,    74,
      -6,    34,   -31,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,   154,   151,   158,  -238,  -238,  -238,    93,  -238,  -238,
    -238,   143,   144,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,   178,   433,   433,   433,   161,   162,  -238,
     433,   433,  -238,   147,  -238,  -238,  -238,  -238,   445,   230,
     527,   166,  -238,  -238,  -238,   170,   171,  -238,  -238,   433,
    -238,   433,  -238,  -238,    28,   433,   129,   174,   167,   175,
    -238,  -238,   184,   185,    10,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,   433,   445,   433,
     433,   445,   445,  -238,   186,   216,   187,   193,  -238,  -238,
     194,   445,   433,   433,  -238,  -238,   190,   196,   445,   445,
    -238,  -238
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     4,   248,   204,   154,   182,   192,   234,   197,   207,
     183,   196,   194,   195,   184,   193,   198,   185,   207,   186,
     207,   199,   191,   235,   180,     0,     0,     0,     5,     8,
       0,     7,   168,   157,   157,   187,   188,   189,   190,   200,
     201,   202,   203,   205,   206,   157,    15,   241,   242,   250,
       0,   244,    10,     9,   209,   266,     0,   212,   210,     0,
     221,     0,   223,   181,   249,   178,     0,     1,     0,     6,
       0,    12,    11,   170,     0,   169,    15,   159,   158,   160,
     161,    14,    16,    17,   168,     0,   113,   251,   240,     0,
      12,    12,   179,   243,    20,    15,   153,     0,     0,    13,
      18,   166,   263,   247,   260,     0,   254,   256,     0,   261,
     284,   283,   281,   282,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,    67,    69,    97,    71,    74,
      76,    98,    91,    78,    83,    85,    87,    89,    81,    94,
      95,    96,    99,   100,   101,   102,   119,     0,   114,   115,
     118,   126,   122,    93,   127,   128,   130,   131,   121,   133,
     134,   129,   123,   217,   218,   213,   215,     0,     0,     0,
     171,     0,   174,   167,   252,   113,   258,   267,   259,   268,
     245,     0,   246,     0,   107,    81,   106,   105,   108,    73,
      80,     0,   104,     0,   109,   110,     0,     0,   236,     0,
       0,     0,     0,     0,     0,     0,   149,     0,   150,     0,
     151,   152,     0,   144,   145,     0,   146,   147,   148,     0,
     279,   280,     0,   275,     0,   135,   136,     0,     0,   137,
       0,   219,     0,     0,   238,   164,     0,   224,   164,     0,
       0,   263,     0,     0,     0,   143,     0,     0,     0,     0,
       0,   116,     0,     0,    57,     0,     0,    27,     0,     0,
      23,    36,    25,    26,    28,    29,    30,    31,    32,    33,
      34,    35,    37,    45,    46,    47,    48,    49,    50,     0,
       0,    64,    65,    66,   176,   172,     0,   253,     0,     0,
     269,   252,   113,   255,   257,   262,     0,   125,   124,   252,
     267,   237,     0,     0,    70,    72,    75,    77,    79,    84,
      86,    88,    90,    92,   112,   120,   264,   277,   265,   276,
     139,     0,   138,     0,   214,   211,   216,     0,   227,   229,
     230,     0,   231,   165,   162,   220,   225,   163,   222,    38,
      52,   142,    53,     0,     0,   116,   116,     0,     0,   117,
       0,     0,    42,    39,    40,    54,    19,    24,     0,   155,
     177,     0,   273,   270,   271,     0,     0,   103,    82,     0,
     278,     0,   132,   226,   238,     0,     0,     0,     0,     0,
      56,    55,     0,     0,     0,    44,   156,    43,   173,   175,
     274,   272,    68,   140,   228,   233,   232,     0,     0,   116,
     116,     0,     0,    41,     0,    58,     0,     0,    51,    61,
       0,     0,   116,   116,    60,    59,     0,     0,     0,     0,
      62,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -238,  -238,  -238,   246,  -238,    94,  -238,   -44,  -238,   -30,
    -238,  -238,  -237,  -238,  -238,  -112,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,   -94,  -238,    76,  -238,    72,    75,
      77,  -238,   -91,    78,    79,    70,    80,    69,  -101,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,   -95,  -134,    39,  -221,
     -84,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,    40,
    -238,     2,    37,  -172,    50,   188,  -238,  -238,  -238,  -166,
    -238,  -238,  -238,  -238,    -5,  -238,  -238,  -238,  -238,    24,
      54,  -238,  -238,  -238,    59,  -238,  -238,  -238,  -238,  -238,
    -238,   119,  -171,  -238,   -85,  -238,  -238,  -238,   -20,   100,
    -238,   -24,   -40,   -41,  -238,   -43,     3,   212,  -238,   117,
    -238,   -78,    71,   -39,   -75,  -165,  -238,  -238,  -238,  -238,
    -238,  -238
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,    29,    95,    30,    81,    82,   257,
     258,   259,   260,   261,   353,   354,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   348,
     280,   150,   151,   152,   153,   154,   155,   156,   157,   321,
     322,   281,   282,   283,   215,   219,   207,   209,   212,    83,
     387,    77,   104,   234,   334,    73,    74,    75,   284,   173,
     361,    63,    64,    33,    34,    35,    36,    37,    38,    56,
      57,    39,    40,   164,   165,   166,   232,    41,    42,    43,
      44,   236,   237,   327,   328,   329,   330,   396,    45,   199,
     331,    46,    47,    48,    49,    50,   286,   287,   106,   107,
     108,   158,   317,    58,   288,   179,    51,   159,   160,   161,
     222,   162
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    66,   149,   172,    65,   285,    87,   109,    76,   343,
      88,    70,   290,   185,   185,   185,   185,   185,   185,   192,
     194,   195,   357,   184,   186,   187,   188,   189,   190,   178,
       7,     2,    99,     2,     2,    24,    79,    32,     2,   197,
      31,   289,    59,    92,    61,   182,    67,    80,   299,   175,
     183,   169,    54,    24,   200,    55,    23,   201,    89,     2,
     101,   177,    55,   333,    32,   336,   333,    31,   336,    93,
      78,    78,    60,   101,    62,    94,   172,   216,   217,   218,
     176,  -208,    78,    84,    90,    71,    97,    52,    53,   225,
     226,   149,   227,   228,   229,   230,    85,    86,   210,   211,
     185,   185,   185,   185,   185,   295,   185,   197,   185,   197,
      96,   185,   163,    84,   185,    98,   303,    91,   185,    84,
     180,   385,   100,   301,   378,   379,   181,   314,   313,   315,
     204,   177,    84,   203,   320,   290,    24,    88,   326,    24,
     213,   214,   220,   221,   291,   292,   323,   238,   238,    25,
      66,    25,   174,   175,   202,   300,   174,   175,   366,   149,
     198,   405,   235,   235,   408,   409,   205,   349,    94,   339,
     373,   374,   347,   206,   415,   208,   299,   175,   406,   407,
     223,   420,   421,   224,   167,   168,   316,   316,   318,   318,
     231,   416,   417,   233,   388,   102,   297,   298,   302,   340,
    -141,   185,   325,   344,   342,   345,   346,   350,   149,   351,
     332,   368,   355,   356,   358,   238,   238,   359,   238,   238,
     360,   362,   363,   369,   364,   352,   367,   370,   198,   371,
     235,   235,   372,   235,   235,   376,   375,  -239,   380,   381,
     384,   386,   389,   390,   399,   391,   196,   398,   102,   110,
     397,   411,   400,   111,   112,   113,   300,   401,   402,   410,
     377,   349,   349,   418,   412,   172,   382,   383,   185,   419,
     413,   414,   403,    69,   305,   392,   393,   304,   306,   310,
     395,   307,   341,   308,   312,   170,   309,   239,   337,   394,
     324,   296,   311,   240,   365,   241,   110,   105,   294,   319,
     111,   112,   113,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   404,     0,   349,   349,     0,     0,   242,
     243,     0,     0,   244,   245,   246,     0,     0,   349,   349,
     247,   248,   249,     0,   250,     0,     0,     0,   251,     0,
       0,     0,     0,   252,   114,     0,     0,     0,     0,   253,
     332,   115,   116,   117,   352,     0,     0,     0,   118,   119,
     120,   121,   122,     0,     0,     0,   123,    71,   -21,   254,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     255,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,     0,     0,   240,     0,   241,   110,   115,   116,
     117,   111,   112,   113,     0,   118,   119,   120,   121,   122,
       0,     0,     0,   123,     0,   256,     0,     0,     0,     0,
     242,   243,     0,     0,   244,   245,   246,     0,     0,     0,
       0,   247,   248,   249,     0,   250,   102,   110,     0,   251,
       0,   111,   112,   113,   252,     0,   240,     0,   241,   110,
     253,     0,     0,   111,   112,   113,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,   -22,
     254,     0,   242,   243,     0,     0,   244,   245,   246,     0,
       0,   255,     0,   247,   248,   249,     0,   250,     0,     0,
       0,   251,   114,     0,     0,     0,   252,     0,     0,   115,
     116,   117,   253,     0,     0,     0,   118,   119,   120,   121,
     122,     0,     0,     0,   123,     0,   256,     0,     0,     0,
      71,     0,   254,     0,     0,     0,     0,     0,     0,     0,
     102,   110,   114,   255,     0,   111,   112,   113,     0,   115,
     116,   117,     0,     0,   114,     0,   118,   119,   120,   121,
     122,   115,   116,   117,   123,     0,     0,     0,   118,   119,
     120,   121,   122,     0,    -2,     1,   123,     2,   256,     0,
       3,     0,     0,     0,     0,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     0,     0,     6,     7,     0,     0,     0,     8,     0,
       9,    10,   171,     0,     0,    11,     0,    12,    13,    14,
       0,    15,    16,    17,    18,     0,    19,    20,    21,    22,
      23,    -3,    68,     0,     2,     0,   114,     3,     0,     0,
       0,     0,     4,   115,   116,   117,     0,     0,     0,     0,
     118,   119,   120,   121,   122,     0,     0,     5,   123,     0,
       6,     7,     0,     0,     0,     8,     0,     9,    10,     0,
       0,     0,    11,     0,    12,    13,    14,     0,    15,    16,
      17,    18,    24,    19,    20,    21,    22,    23,     0,   196,
       0,   102,   110,     0,     3,    25,   111,   112,   113,     0,
       0,     0,     0,   102,   110,     0,     0,     0,   111,   112,
     113,     0,     0,     0,     5,     0,     0,     6,     7,     0,
       0,     0,     8,     2,     9,    10,     3,     0,     0,    11,
       0,    12,    13,    14,     0,    15,    16,    17,    18,    24,
      19,    20,    21,    22,    23,     0,     5,     0,     0,     6,
       7,     0,    25,     0,     8,     0,     9,    10,     0,     0,
       0,    11,     0,    12,    13,    14,     0,    15,    16,    17,
      18,     0,    19,    20,    21,    22,    23,   102,   110,     0,
       0,     0,   111,   112,   113,     0,     0,   114,     0,     0,
       0,     0,     0,     0,   115,   116,   117,     0,     0,   114,
       0,   118,   119,   120,   121,   122,   115,   116,   117,   123,
       0,     0,     0,   118,   119,   120,   121,   122,     0,     0,
       3,   191,     0,     0,     0,     0,     0,     0,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,   174,   175,     6,     7,     0,     0,     0,     8,     0,
       9,    10,     0,     0,     0,    11,     0,    12,    13,    14,
       0,    15,    16,    17,    18,     0,    19,    20,    21,    22,
      23,     0,     0,   114,     0,     0,     0,     0,     0,     0,
     115,   116,   117,     0,     0,     0,     0,   118,   119,   120,
     121,   122,     0,     0,     0,   193,     0,     0,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    24,     5,     0,     0,     6,     7,     0,     0,
       0,     8,     0,     9,    10,   299,   175,     0,    11,     0,
      12,    13,    14,     0,    15,    16,    17,    18,     0,    19,
      20,    21,    22,    23,     0,     0,     0,     0,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -166,  -166,     0,     0,     5,     0,
       0,     6,     7,     0,     0,     0,     8,    98,     9,    10,
       0,     0,     0,    11,     0,    12,    13,    14,     0,    15,
      16,    17,    18,     0,    19,    20,    21,    22,    23,   102,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   293,     5,     0,     0,     6,     7,     0,     0,     0,
       8,     0,     9,    10,     0,     3,     0,    11,     0,    12,
      13,    14,     0,    15,    16,    17,    18,     0,    19,    20,
      21,    22,    23,     0,     0,     0,     0,     0,     6,     7,
       0,     0,     0,     8,     0,     9,     3,     0,     0,   103,
      11,     0,    12,    13,     0,     0,    15,    16,     0,    18,
       0,     0,    20,    21,    22,    23,     0,     0,     0,     6,
       7,     0,     0,     0,     8,     0,     9,     0,     0,     0,
       0,    11,     0,    12,    13,   335,     0,    15,    16,     0,
      18,     0,     0,    20,    21,    22,    23,     3,     0,     0,
       0,     0,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   338,     5,     0,     0,
       6,     7,     0,     0,     0,     8,     0,     9,    10,     3,
       0,     0,    11,     0,    12,    13,    14,     0,    15,    16,
      17,    18,     0,    19,    20,    21,    22,    23,     0,     5,
       0,     0,     6,     7,     0,     0,     0,     8,     3,     9,
      10,     0,     0,     0,    11,     0,    12,    13,    14,     0,
      15,    16,    17,    18,     0,    19,    20,    21,    22,    23,
       0,     6,     7,     0,     0,     0,     8,     0,     9,     0,
       0,     0,     0,    11,     0,    12,    13,     0,     0,    15,
      16,     0,    18,     0,     0,    20,    21,    22,    23
};

static const yytype_int16 yycheck[] =
{
      30,    25,    86,    98,    24,   171,    49,    85,    32,   246,
      50,     1,   177,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   259,   114,   115,   116,   117,   118,   119,   104,
      30,     3,    76,     3,     3,   108,    34,     0,     3,   123,
       0,   175,    18,    63,    20,    73,     0,    45,   121,   122,
      78,    95,     3,   108,    92,     6,    56,    95,    75,     3,
      84,   104,     6,   235,    27,   236,   238,    27,   239,    73,
      33,    34,    18,    97,    20,    76,   171,   108,   109,   110,
     104,    75,    45,    46,    75,    75,    78,    76,    77,   116,
     117,   175,   119,   120,   121,   122,   121,   122,   104,   105,
     201,   202,   203,   204,   205,   183,   207,   191,   209,   193,
      77,   212,     3,    76,   215,    90,   200,    75,   219,    82,
      73,   358,    82,   198,   345,   346,    78,   222,   219,   224,
      98,   174,    95,    97,   229,   300,   108,   177,   233,   108,
     106,   107,    90,    91,   121,   122,   230,   167,   168,   121,
     174,   121,   121,   122,    96,   198,   121,   122,   292,   243,
     123,   398,   167,   168,   401,   402,    99,   251,    76,    77,
      77,    78,   250,   100,   411,   101,   121,   122,   399,   400,
      74,   418,   419,    78,    90,    91,   227,   228,   227,   228,
      78,   412,   413,    90,   360,     3,    73,    73,    73,    77,
      93,   302,    76,   121,    77,   121,   121,   121,   292,   121,
     234,   302,    77,    76,    93,   235,   236,    77,   238,   239,
      78,    73,    73,    93,    74,   255,    73,    73,   191,    78,
     235,   236,    74,   238,   239,    57,    93,    93,    77,    77,
      93,    11,    76,    73,    77,    74,     1,    73,     3,     4,
     121,    35,    77,     8,     9,    10,   299,    73,    73,    73,
     344,   345,   346,    73,    77,   360,   350,   351,   369,    73,
      77,    77,   384,    27,   202,   369,   371,   201,   203,   209,
     375,   204,   243,   205,   215,    97,   207,   168,   238,   374,
     231,   191,   212,     1,   291,     3,     4,    85,   181,   228,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   397,    -1,   399,   400,    -1,    -1,    27,
      28,    -1,    -1,    31,    32,    33,    -1,    -1,   412,   413,
      38,    39,    40,    -1,    42,    -1,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    51,    99,    -1,    -1,    -1,    -1,    57,
     374,   106,   107,   108,   384,    -1,    -1,    -1,   113,   114,
     115,   116,   117,    -1,    -1,    -1,   121,    75,    76,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    99,    -1,    -1,     1,    -1,     3,     4,   106,   107,
     108,     8,     9,    10,    -1,   113,   114,   115,   116,   117,
      -1,    -1,    -1,   121,    -1,   123,    -1,    -1,    -1,    -1,
      27,    28,    -1,    -1,    31,    32,    33,    -1,    -1,    -1,
      -1,    38,    39,    40,    -1,    42,     3,     4,    -1,    46,
      -1,     8,     9,    10,    51,    -1,     1,    -1,     3,     4,
      57,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    -1,    27,    28,    -1,    -1,    31,    32,    33,    -1,
      -1,    88,    -1,    38,    39,    40,    -1,    42,    -1,    -1,
      -1,    46,    99,    -1,    -1,    -1,    51,    -1,    -1,   106,
     107,   108,    57,    -1,    -1,    -1,   113,   114,   115,   116,
     117,    -1,    -1,    -1,   121,    -1,   123,    -1,    -1,    -1,
      75,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,    99,    88,    -1,     8,     9,    10,    -1,   106,
     107,   108,    -1,    -1,    99,    -1,   113,   114,   115,   116,
     117,   106,   107,   108,   121,    -1,    -1,    -1,   113,   114,
     115,   116,   117,    -1,     0,     1,   121,     3,   123,    -1,
       6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    29,    30,    -1,    -1,    -1,    34,    -1,
      36,    37,    75,    -1,    -1,    41,    -1,    43,    44,    45,
      -1,    47,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,     0,     1,    -1,     3,    -1,    99,     6,    -1,    -1,
      -1,    -1,    11,   106,   107,   108,    -1,    -1,    -1,    -1,
     113,   114,   115,   116,   117,    -1,    -1,    26,   121,    -1,
      29,    30,    -1,    -1,    -1,    34,    -1,    36,    37,    -1,
      -1,    -1,    41,    -1,    43,    44,    45,    -1,    47,    48,
      49,    50,   108,    52,    53,    54,    55,    56,    -1,     1,
      -1,     3,     4,    -1,     6,   121,     8,     9,    10,    -1,
      -1,    -1,    -1,     3,     4,    -1,    -1,    -1,     8,     9,
      10,    -1,    -1,    -1,    26,    -1,    -1,    29,    30,    -1,
      -1,    -1,    34,     3,    36,    37,     6,    -1,    -1,    41,
      -1,    43,    44,    45,    -1,    47,    48,    49,    50,   108,
      52,    53,    54,    55,    56,    -1,    26,    -1,    -1,    29,
      30,    -1,   121,    -1,    34,    -1,    36,    37,    -1,    -1,
      -1,    41,    -1,    43,    44,    45,    -1,    47,    48,    49,
      50,    -1,    52,    53,    54,    55,    56,     3,     4,    -1,
      -1,    -1,     8,     9,    10,    -1,    -1,    99,    -1,    -1,
      -1,    -1,    -1,    -1,   106,   107,   108,    -1,    -1,    99,
      -1,   113,   114,   115,   116,   117,   106,   107,   108,   121,
      -1,    -1,    -1,   113,   114,   115,   116,   117,    -1,    -1,
       6,   121,    -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      26,   121,   122,    29,    30,    -1,    -1,    -1,    34,    -1,
      36,    37,    -1,    -1,    -1,    41,    -1,    43,    44,    45,
      -1,    47,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,
     106,   107,   108,    -1,    -1,    -1,    -1,   113,   114,   115,
     116,   117,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,    26,    -1,    -1,    29,    30,    -1,    -1,
      -1,    34,    -1,    36,    37,   121,   122,    -1,    41,    -1,
      43,    44,    45,    -1,    47,    48,    49,    50,    -1,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    78,    -1,    -1,    26,    -1,
      -1,    29,    30,    -1,    -1,    -1,    34,    90,    36,    37,
      -1,    -1,    -1,    41,    -1,    43,    44,    45,    -1,    47,
      48,    49,    50,    -1,    52,    53,    54,    55,    56,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,
      34,    -1,    36,    37,    -1,     6,    -1,    41,    -1,    43,
      44,    45,    -1,    47,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    29,    30,
      -1,    -1,    -1,    34,    -1,    36,     6,    -1,    -1,    73,
      41,    -1,    43,    44,    -1,    -1,    47,    48,    -1,    50,
      -1,    -1,    53,    54,    55,    56,    -1,    -1,    -1,    29,
      30,    -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    -1,    43,    44,    76,    -1,    47,    48,    -1,
      50,    -1,    -1,    53,    54,    55,    56,     6,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    26,    -1,    -1,
      29,    30,    -1,    -1,    -1,    34,    -1,    36,    37,     6,
      -1,    -1,    41,    -1,    43,    44,    45,    -1,    47,    48,
      49,    50,    -1,    52,    53,    54,    55,    56,    -1,    26,
      -1,    -1,    29,    30,    -1,    -1,    -1,    34,     6,    36,
      37,    -1,    -1,    -1,    41,    -1,    43,    44,    45,    -1,
      47,    48,    49,    50,    -1,    52,    53,    54,    55,    56,
      -1,    29,    30,    -1,    -1,    -1,    34,    -1,    36,    -1,
      -1,    -1,    -1,    41,    -1,    43,    44,    -1,    -1,    47,
      48,    -1,    50,    -1,    -1,    53,    54,    55,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     3,     6,    11,    26,    29,    30,    34,    36,
      37,    41,    43,    44,    45,    47,    48,    49,    50,    52,
      53,    54,    55,    56,   108,   121,   125,   126,   127,   128,
     130,   203,   206,   217,   218,   219,   220,   221,   222,   225,
     226,   231,   232,   233,   234,   242,   245,   246,   247,   248,
     249,   260,    76,    77,     3,     6,   223,   224,   257,   223,
     224,   223,   224,   215,   216,   242,   245,     0,     1,   127,
       1,    75,   133,   209,   210,   211,   245,   205,   206,   205,
     205,   131,   132,   203,   206,   121,   122,   249,   246,    75,
      75,    75,   242,    73,    76,   129,    77,    78,    90,   131,
     203,   245,     3,    73,   206,   251,   252,   253,   254,   255,
       4,     8,     9,    10,    99,   106,   107,   108,   113,   114,
     115,   116,   117,   121,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   255,   261,
     262,   263,   265,     3,   227,   228,   229,   129,   129,   131,
     209,    75,   180,   213,   121,   122,   245,   249,   258,   259,
      73,    78,    73,    78,   166,   172,   166,   166,   166,   166,
     166,   121,   172,   121,   172,   172,     1,   184,   206,   243,
      92,    95,    96,    97,    98,    99,   100,   200,   101,   201,
     104,   105,   202,   106,   107,   198,   108,   109,   110,   199,
      90,    91,   264,    74,    78,   116,   117,   119,   120,   121,
     122,    78,   230,    90,   207,   218,   235,   236,   242,   235,
       1,     3,    27,    28,    31,    32,    33,    38,    39,    40,
      42,    46,    51,    57,    77,    88,   123,   133,   134,   135,
     136,   137,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     184,   195,   196,   197,   212,   213,   250,   251,   258,   181,
     259,   121,   122,    79,   253,   255,   243,    73,    73,   121,
     249,   258,    73,   184,   160,   162,   163,   164,   167,   168,
     169,   170,   171,   166,   180,   180,   247,   256,   257,   256,
     180,   193,   194,   184,   228,    76,   180,   237,   238,   239,
     240,   244,   245,   207,   208,    76,   236,   208,    76,    77,
      77,   182,    77,   136,   121,   121,   121,   255,   183,   184,
     121,   121,   133,   138,   139,    77,    76,   136,    93,    77,
      78,   214,    73,    73,    74,   250,   181,    73,   166,    93,
      73,    78,    74,    77,    78,    93,    57,   184,   183,   183,
      77,    77,   184,   184,    93,   136,    11,   204,   213,    76,
      73,    74,   158,   180,   238,   180,   241,   121,    73,    77,
      77,    73,    73,   139,   184,   136,   183,   183,   136,   136,
      73,    35,    77,    77,    77,   136,   183,   183,    73,    73,
     136,   136
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   124,   125,   125,   125,   126,   126,   127,   127,   127,
     127,   128,   129,   130,   130,   131,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   137,
     138,   138,   139,   140,   141,   142,   142,   143,   143,   143,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   157,   157,   158,   158,   159,
     159,   160,   160,   161,   162,   162,   163,   163,   164,   164,
     165,   166,   166,   167,   167,   168,   168,   169,   169,   170,
     170,   171,   171,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   173,   173,   174,   175,   176,   177,   178,
     179,   180,   180,   181,   181,   182,   183,   183,   184,   185,
     185,   186,   186,   186,   187,   187,   188,   188,   188,   188,
     188,   188,   189,   190,   190,   191,   192,   193,   193,   194,
     194,   195,   196,   197,   198,   198,   199,   199,   199,   200,
     201,   202,   202,   203,   203,   204,   204,   205,   205,   206,
     206,   206,   207,   207,   208,   208,   209,   209,   210,   210,
     211,   211,   212,   212,   213,   213,   214,   214,   215,   215,
     216,   216,   217,   217,   217,   217,   217,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     219,   219,   220,   220,   221,   222,   222,   223,   223,   224,
     224,   225,   226,   227,   227,   228,   228,   229,   230,   230,
     231,   232,   233,   234,   235,   235,   236,   237,   237,   238,
     238,   239,   240,   241,   242,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   246,   246,   246,   246,   247,   248,
     249,   249,   250,   250,   251,   251,   252,   252,   253,   253,
     253,   254,   254,   255,   256,   256,   257,   258,   258,   258,
     259,   259,   259,   259,   259,   260,   261,   262,   263,   264,
     264,   265,   265,   265,   265
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     1,     2,     1,     1,     2,
       2,     2,     0,     3,     2,     0,     1,     1,     2,     5,
       2,     0,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     5,     2,     2,     2,     3,     3,     1,     5,     7,
       7,     5,     9,     9,     1,     1,     1,     1,     5,     1,
       3,     1,     3,     2,     1,     3,     1,     3,     1,     3,
       2,     1,     4,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     2,     2,     2,     2,     2,     2,
       2,     1,     3,     0,     1,     1,     0,     1,     1,     1,
       3,     1,     1,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     4,     1,     1,     2,     2,     0,     1,     1,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     1,     0,     1,     2,
       2,     2,     2,     2,     0,     1,     1,     3,     0,     1,
       1,     3,     1,     3,     1,     4,     0,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     6,     2,     1,     3,     1,     3,     1,     0,     1,
       6,     2,     6,     2,     1,     2,     3,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     2,     0,     1,
       2,     1,     1,     3,     1,     4,     4,     3,     1,     2,
       1,     2,     0,     1,     1,     3,     1,     3,     2,     2,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     4,     3,     4,     4,     3,     3,     4,     1,
       1,     1,     1,     1,     1
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




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

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
      yychar = yylex (&yylval);
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
#line 193 "gram.y" /* yacc.c:1646  */
    {
            if (err_cnt == 0)
              fputs("Warning: ANSI/ISO C forbids an empty source file.\n",
                  stderr);
            Parse_TOS->parse_tree= (treenode *) NULL;
            (yyval.node) = (treenode *) NULL;
        }
#line 1927 "gram.c" /* yacc.c:1646  */
    break;

  case 3:
#line 201 "gram.y" /* yacc.c:1646  */
    {
            if (err_cnt) {
                fprintf(stderr,"%d Errors found.\n",err_cnt);
                Parse_TOS->parse_tree = (treenode *) NULL;
            } else {
                /*fputs("No Errors encountered.\n",stderr);*/
                Parse_TOS->parse_tree = (yyval.node);
            }
        }
#line 1941 "gram.c" /* yacc.c:1646  */
    break;

  case 4:
#line 211 "gram.y" /* yacc.c:1646  */
    {
            fputs("Errors - Aborting parse.\n",stderr);
            Parse_TOS->parse_tree= (treenode *) NULL;
            YYABORT;
        }
#line 1951 "gram.c" /* yacc.c:1646  */
    break;

  case 6:
#line 219 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_TRANS_LIST, ParseStack->contxt);
            tmp_node->lnode = (yyvsp[-1].node);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 1962 "gram.c" /* yacc.c:1646  */
    break;

  case 7:
#line 227 "gram.y" /* yacc.c:1646  */
    {
            /* Safety precaution. */
            exit_scopes(ParseStack->contxt, FILE_SCOPE);
        }
#line 1971 "gram.c" /* yacc.c:1646  */
    break;

  case 8:
#line 232 "gram.y" /* yacc.c:1646  */
    {
            /* Safety precaution. */
            exit_scopes(ParseStack->contxt, FILE_SCOPE);
        }
#line 1980 "gram.c" /* yacc.c:1646  */
    break;

  case 9:
#line 237 "gram.y" /* yacc.c:1646  */
    {
            free_tree((yyvsp[0].node));
            (yyval.node) = (treenode *) NULL;
        }
#line 1989 "gram.c" /* yacc.c:1646  */
    break;

  case 10:
#line 242 "gram.y" /* yacc.c:1646  */
    {
            free_tree((yyvsp[0].node));
            (yyval.node) = (treenode *) NULL;
        }
#line 1998 "gram.c" /* yacc.c:1646  */
    break;

  case 11:
#line 248 "gram.y" /* yacc.c:1646  */
    {
            leafnode *lm, *rm;
            for_node *tmpnode;
            tmpnode = (for_node *) (yyvsp[-1].node);
            tmpnode->stemnt = (yyvsp[0].node);

            if (ParseStack->contxt)
              {
              lm = leftmost((yyval.node));
              rm = find_func_name((yyval.node));

              if (rm)
                {
                if (lm && (lm->hdr.tok == STATIC))
                  {
                  if (! symtab_insert_at(ParseStack->contxt->syms,
                        mk_funcdef(rm->data.sval, (yyval.node)), FILE_SCOPE))
                    yyerr("Duplicate function.");
                  }
                else
                  {
                  if (! symtab_insert_at(ParseStack->contxt->syms,
                        mk_funcdef(rm->data.sval, (yyval.node)), EXTERN_SCOPE))
                    yyerr("Duplicate function.");
                  }
                }
              }

            /* This is the scope that starts in func_spec */
            exit_scope(ParseStack->contxt);
        }
#line 2034 "gram.c" /* yacc.c:1646  */
    break;

  case 12:
#line 281 "gram.y" /* yacc.c:1646  */
    {
            enter_scope(ParseStack->contxt);
        }
#line 2042 "gram.c" /* yacc.c:1646  */
    break;

  case 13:
#line 286 "gram.y" /* yacc.c:1646  */
    {
            for_node *tmp_node = make_for(TN_FUNC_DEF, ParseStack->contxt);

            tmp_node->init = (yyvsp[-2].node);
            tmp_node->test = (yyvsp[-1].node);
            tmp_node->incr = (yyvsp[0].node);
            add_params_to_symtab((yyvsp[-1].node));
            (yyval.node) = (treenode *) tmp_node;
        }
#line 2056 "gram.c" /* yacc.c:1646  */
    break;

  case 14:
#line 296 "gram.y" /* yacc.c:1646  */
    {
            /* return type defaults to int */
            for_node *tmp_node = make_for(TN_FUNC_DEF, ParseStack->contxt);

            tmp_node->init = (treenode *) NULL;
            tmp_node->test = (yyvsp[-1].node);
            tmp_node->incr = (yyvsp[0].node);
            add_params_to_symtab((yyvsp[-1].node));
            (yyval.node) = (treenode *) tmp_node;
        }
#line 2071 "gram.c" /* yacc.c:1646  */
    break;

  case 15:
#line 308 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (treenode *) NULL;
        }
#line 2079 "gram.c" /* yacc.c:1646  */
    break;

  case 18:
#line 316 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_DECL_LIST, ParseStack->contxt);
            tmp_node->lnode = (yyvsp[-1].node);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2090 "gram.c" /* yacc.c:1646  */
    break;

  case 19:
#line 325 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-4].node)->hdr.type = TN_BLOCK;
            (yyvsp[-4].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-4].node)->rnode = (yyvsp[-1].node);
            free_tree((yyvsp[0].node));
            exit_scope(ParseStack->contxt);
        }
#line 2102 "gram.c" /* yacc.c:1646  */
    break;

  case 20:
#line 333 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (treenode *) NULL;
            free_tree((yyvsp[0].node));
        }
#line 2111 "gram.c" /* yacc.c:1646  */
    break;

  case 21:
#line 339 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (treenode *) NULL;
        }
#line 2119 "gram.c" /* yacc.c:1646  */
    break;

  case 23:
#line 346 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT_LIST, ParseStack->contxt);
            tmp_node->lnode = (yyvsp[0].node);
            tmp_node->rnode = NULL;
            (yyval.node) = tmp_node;
        }
#line 2130 "gram.c" /* yacc.c:1646  */
    break;

  case 24:
#line 353 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT_LIST, ParseStack->contxt);
            tmp_node->lnode = (yyvsp[-1].node);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2141 "gram.c" /* yacc.c:1646  */
    break;

  case 25:
#line 362 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2151 "gram.c" /* yacc.c:1646  */
    break;

  case 26:
#line 368 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2161 "gram.c" /* yacc.c:1646  */
    break;

  case 27:
#line 374 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2171 "gram.c" /* yacc.c:1646  */
    break;

  case 28:
#line 380 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2181 "gram.c" /* yacc.c:1646  */
    break;

  case 29:
#line 386 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2191 "gram.c" /* yacc.c:1646  */
    break;

  case 30:
#line 392 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
			malloc(10);
            (yyval.node) = tmp_node;
        }
#line 2202 "gram.c" /* yacc.c:1646  */
    break;

  case 31:
#line 399 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2212 "gram.c" /* yacc.c:1646  */
    break;

  case 32:
#line 405 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2222 "gram.c" /* yacc.c:1646  */
    break;

  case 33:
#line 411 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2232 "gram.c" /* yacc.c:1646  */
    break;

  case 34:
#line 417 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2242 "gram.c" /* yacc.c:1646  */
    break;

  case 35:
#line 423 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2252 "gram.c" /* yacc.c:1646  */
    break;

  case 36:
#line 429 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_PARBLOCK, ParseStack->contxt);
            tmp_node->lnode = 0;
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
		}
#line 2263 "gram.c" /* yacc.c:1646  */
    break;

  case 37:
#line 436 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmp_node = make_node(TN_STEMNT, ParseStack->contxt);
            tmp_node->rnode = (yyvsp[0].node);
            (yyval.node) = tmp_node;
        }
#line 2273 "gram.c" /* yacc.c:1646  */
    break;

  case 38:
#line 442 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (treenode *) NULL;
            free_tree((yyvsp[0].node));
        }
#line 2282 "gram.c" /* yacc.c:1646  */
    break;

  case 39:
#line 448 "gram.y" /* yacc.c:1646  */
    {
		    (yyval.node) = (yyvsp[0].node);
			free_tree((yyvsp[-1].node));
		}
#line 2291 "gram.c" /* yacc.c:1646  */
    break;

  case 40:
#line 455 "gram.y" /* yacc.c:1646  */
    {
		    (yyval.node) = make_node(TN_PARBLOCK_EMPTY, ParseStack->contxt);
			(yyval.node)->lnode = (yyvsp[0].node);
		}
#line 2300 "gram.c" /* yacc.c:1646  */
    break;

  case 41:
#line 460 "gram.y" /* yacc.c:1646  */
    {
		    free_tree((yyvsp[-1].node));
		    (yyval.node) = make_node(TN_PARBLOCK_EMPTY, ParseStack->contxt);
			(yyval.node)->lnode = (yyvsp[0].node);
			(yyval.node)->rnode = (yyvsp[-2].node);
		}
#line 2311 "gram.c" /* yacc.c:1646  */
    break;

  case 42:
#line 469 "gram.y" /* yacc.c:1646  */
    {
		     (yyval.node) = (yyvsp[0].node);
		}
#line 2319 "gram.c" /* yacc.c:1646  */
    break;

  case 43:
#line 475 "gram.y" /* yacc.c:1646  */
    {
            free_tree((yyvsp[-1].node));
        }
#line 2327 "gram.c" /* yacc.c:1646  */
    break;

  case 44:
#line 480 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_LABEL;
            (yyvsp[-1].node)->lnode = (treenode *) (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2338 "gram.c" /* yacc.c:1646  */
    break;

  case 51:
#line 498 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-4].node)->hdr.type = TN_SWITCH;
            (yyvsp[-4].node)->lnode = (treenode *) (yyvsp[-2].node);
            (yyvsp[-4].node)->rnode = (treenode *) (yyvsp[0].node);
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
        }
#line 2350 "gram.c" /* yacc.c:1646  */
    break;

  case 52:
#line 507 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_JUMP;
            free_tree((yyvsp[0].node));
        }
#line 2359 "gram.c" /* yacc.c:1646  */
    break;

  case 53:
#line 513 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_JUMP;
            free_tree((yyvsp[0].node));
        }
#line 2368 "gram.c" /* yacc.c:1646  */
    break;

  case 54:
#line 519 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_JUMP;
            free_tree((yyvsp[0].node));
        }
#line 2377 "gram.c" /* yacc.c:1646  */
    break;

  case 55:
#line 525 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_JUMP;
            (yyvsp[-2].node)->lnode = (yyvsp[-1].node);
            free_tree((yyvsp[0].node));
        }
#line 2387 "gram.c" /* yacc.c:1646  */
    break;

  case 56:
#line 532 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_JUMP;
            (yyvsp[-2].node)->lnode = (treenode *) (yyvsp[-1].leaf);
            free_tree((yyvsp[0].node));
        }
#line 2397 "gram.c" /* yacc.c:1646  */
    break;

  case 57:
#line 539 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (treenode *) NULL;
            free_tree((yyvsp[0].node));
        }
#line 2406 "gram.c" /* yacc.c:1646  */
    break;

  case 58:
#line 545 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-4].ifn)->hdr.type = TN_IF;
            (yyvsp[-4].ifn)->cond = (yyvsp[-2].node);
            (yyvsp[-4].ifn)->then_n = (yyvsp[0].node);
            (yyval.node) = (treenode *) (yyvsp[-4].ifn);
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
        }
#line 2419 "gram.c" /* yacc.c:1646  */
    break;

  case 59:
#line 555 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-6].ifn)->hdr.type = TN_IF;
            (yyvsp[-6].ifn)->cond = (yyvsp[-4].node);
            (yyvsp[-6].ifn)->then_n = (yyvsp[-2].node);
            (yyvsp[-6].ifn)->else_n = (yyvsp[0].node);
            (yyval.node) = (treenode *) (yyvsp[-6].ifn);
            free_tree((yyvsp[-5].node));
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
        }
#line 2434 "gram.c" /* yacc.c:1646  */
    break;

  case 60:
#line 567 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-6].node)->hdr.type = TN_DOWHILE;
            (yyvsp[-6].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-6].node)->rnode = (yyvsp[-5].node);
            free_tree((yyvsp[-4].node));
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
            free_tree((yyvsp[0].node));
        }
#line 2448 "gram.c" /* yacc.c:1646  */
    break;

  case 61:
#line 578 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-4].node)->hdr.type = TN_WHILE;
            (yyvsp[-4].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-4].node)->rnode = (yyvsp[0].node);
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
        }
#line 2460 "gram.c" /* yacc.c:1646  */
    break;

  case 62:
#line 588 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-8].forn)->hdr.type = TN_FOR;
            (yyvsp[-8].forn)->init = (yyvsp[-6].node);
            (yyvsp[-8].forn)->test = (yyvsp[-4].node);
            (yyvsp[-8].forn)->incr = (yyvsp[-2].node);
            (yyvsp[-8].forn)->stemnt = (yyvsp[0].node);
            free_tree((yyvsp[-7].node));
            free_tree((yyvsp[-5].node));
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
        }
#line 2476 "gram.c" /* yacc.c:1646  */
    break;

  case 63:
#line 602 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-8].forn)->hdr.type = TN_FOR;
            (yyvsp[-8].forn)->init = (yyvsp[-6].node);
            (yyvsp[-8].forn)->test = (yyvsp[-4].node);
            (yyvsp[-8].forn)->incr = (yyvsp[-2].node);
            (yyvsp[-8].forn)->stemnt = (yyvsp[0].node);
            free_tree((yyvsp[-7].node));
            free_tree((yyvsp[-5].node));
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
        }
#line 2492 "gram.c" /* yacc.c:1646  */
    break;

  case 68:
#line 622 "gram.y" /* yacc.c:1646  */
    {
            if_node *tmpnode = make_if(TN_COND_EXPR, ParseStack->contxt);
            tmpnode->cond = (yyvsp[-4].node);
            tmpnode->then_n = (yyvsp[-2].node);
            tmpnode->else_n = (yyvsp[0].node);
            (yyval.node) = (treenode *) tmpnode;
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
        }
#line 2506 "gram.c" /* yacc.c:1646  */
    break;

  case 70:
#line 634 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2517 "gram.c" /* yacc.c:1646  */
    break;

  case 72:
#line 643 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2528 "gram.c" /* yacc.c:1646  */
    break;

  case 73:
#line 651 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
        }
#line 2537 "gram.c" /* yacc.c:1646  */
    break;

  case 75:
#line 658 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2548 "gram.c" /* yacc.c:1646  */
    break;

  case 77:
#line 667 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2559 "gram.c" /* yacc.c:1646  */
    break;

  case 79:
#line 676 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2570 "gram.c" /* yacc.c:1646  */
    break;

  case 80:
#line 684 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
        }
#line 2579 "gram.c" /* yacc.c:1646  */
    break;

  case 82:
#line 691 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-3].node)->hdr.type = TN_CAST;
            (yyvsp[-3].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-3].node)->rnode = (yyvsp[0].node);
            free_tree((yyvsp[-1].node));
        }
#line 2590 "gram.c" /* yacc.c:1646  */
    break;

  case 84:
#line 700 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2601 "gram.c" /* yacc.c:1646  */
    break;

  case 86:
#line 709 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2612 "gram.c" /* yacc.c:1646  */
    break;

  case 88:
#line 718 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2623 "gram.c" /* yacc.c:1646  */
    break;

  case 90:
#line 727 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2634 "gram.c" /* yacc.c:1646  */
    break;

  case 92:
#line 736 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2645 "gram.c" /* yacc.c:1646  */
    break;

  case 103:
#line 756 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-3].node)->hdr.type = TN_EXPR;
            (yyvsp[-3].node)->rnode = (yyvsp[-1].node);
            free_tree((yyvsp[-2].node));
            free_tree((yyvsp[0].node));
        }
#line 2656 "gram.c" /* yacc.c:1646  */
    break;

  case 104:
#line 763 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
        }
#line 2665 "gram.c" /* yacc.c:1646  */
    break;

  case 105:
#line 769 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
        }
#line 2674 "gram.c" /* yacc.c:1646  */
    break;

  case 106:
#line 775 "gram.y" /* yacc.c:1646  */
    {
            /* Unary plus is an ISO addition (for symmetry) - ignore it */
            (yyval.node) = (yyvsp[0].node);
            free_tree((yyvsp[-1].node));
        }
#line 2684 "gram.c" /* yacc.c:1646  */
    break;

  case 107:
#line 782 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
        }
#line 2693 "gram.c" /* yacc.c:1646  */
    break;

  case 108:
#line 788 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_DEREF;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
        }
#line 2702 "gram.c" /* yacc.c:1646  */
    break;

  case 109:
#line 794 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
        }
#line 2711 "gram.c" /* yacc.c:1646  */
    break;

  case 110:
#line 800 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
        }
#line 2720 "gram.c" /* yacc.c:1646  */
    break;

  case 112:
#line 807 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_ASSIGN;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2731 "gram.c" /* yacc.c:1646  */
    break;

  case 113:
#line 815 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (treenode *) NULL;
        }
#line 2739 "gram.c" /* yacc.c:1646  */
    break;

  case 116:
#line 825 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) NULL;
        }
#line 2747 "gram.c" /* yacc.c:1646  */
    break;

  case 120:
#line 836 "gram.y" /* yacc.c:1646  */
    {
           (yyvsp[-1].node)->hdr.type = TN_EXPR;
           (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
           (yyvsp[-1].node)->rnode = (yyvsp[0].node);
           (yyval.node) = (yyvsp[-1].node);
        }
#line 2758 "gram.c" /* yacc.c:1646  */
    break;

  case 121:
#line 844 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) (yyvsp[0].leaf);
        }
#line 2766 "gram.c" /* yacc.c:1646  */
    break;

  case 123:
#line 849 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) (yyvsp[0].leaf);
        }
#line 2774 "gram.c" /* yacc.c:1646  */
    break;

  case 124:
#line 854 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (yyvsp[-1].node);
           free_tree((yyvsp[-2].node));
           free_tree((yyvsp[0].node));
        }
#line 2784 "gram.c" /* yacc.c:1646  */
    break;

  case 125:
#line 860 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) NULL;
           free_tree((yyvsp[-2].node));
           free_tree((yyvsp[0].node));
        }
#line 2794 "gram.c" /* yacc.c:1646  */
    break;

  case 132:
#line 875 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_INDEX;
            (yyvsp[-2].node)->lnode = (yyvsp[-3].node);
            (yyvsp[-2].node)->rnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[-2].node);
            free_tree((yyvsp[0].node));
        }
#line 2806 "gram.c" /* yacc.c:1646  */
    break;

  case 135:
#line 888 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[0].node)->hdr.type = TN_EXPR;
            (yyvsp[0].node)->lnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[0].node);
        }
#line 2816 "gram.c" /* yacc.c:1646  */
    break;

  case 136:
#line 895 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[0].node)->hdr.type = TN_EXPR;
            (yyvsp[0].node)->lnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[0].node);
        }
#line 2826 "gram.c" /* yacc.c:1646  */
    break;

  case 137:
#line 902 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (treenode *) NULL;
        }
#line 2834 "gram.c" /* yacc.c:1646  */
    break;

  case 140:
#line 910 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR_LIST;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2845 "gram.c" /* yacc.c:1646  */
    break;

  case 141:
#line 918 "gram.y" /* yacc.c:1646  */
    {
        (yyval.node) = (treenode *) (yyvsp[0].leaf);
        if (ParseStack->contxt)
          {
          if (! symtab_insert_at(ParseStack->contxt->labels,
                mk_label((yyvsp[0].leaf)->data.sval, (yyval.node)), FUNCTION_SCOPE))
            yyerr("Duplicate label.");
          }
        }
#line 2859 "gram.c" /* yacc.c:1646  */
    break;

  case 142:
#line 929 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_EXPR;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (treenode *) (yyvsp[-1].node);
        }
#line 2869 "gram.c" /* yacc.c:1646  */
    break;

  case 153:
#line 958 "gram.y" /* yacc.c:1646  */
    {
            leafnode *lm;
            (yyvsp[0].node)->hdr.type = TN_DECL;
            (yyvsp[0].node)->lnode = (yyvsp[-2].node);
            (yyvsp[0].node)->rnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[0].node);

            lm = leftmost((yyval.node));
            if (lm)
            {
              if (lm->hdr.tok == TYPEDEF)
              {
                /* Decl is a typedef. Scan the subtree for the
                   ident naming the new type.  Don't use rightmost()
                   since it doesn't give the ident for complex
                   types (like arrays). */
                find_typedef_name((yyval.node),(yyval.node),insert_typedef);
              } else {
                /* Find the identifier for a normal declaration. */
                find_ident_name((yyval.node),(yyval.node),NULL,insert_decl);
              }
            }
        }
#line 2897 "gram.c" /* yacc.c:1646  */
    break;

  case 154:
#line 982 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) (yyvsp[0].leaf);
        }
#line 2905 "gram.c" /* yacc.c:1646  */
    break;

  case 155:
#line 987 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) NULL;
        }
#line 2913 "gram.c" /* yacc.c:1646  */
    break;

  case 156:
#line 991 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) (yyvsp[0].leaf);
        }
#line 2921 "gram.c" /* yacc.c:1646  */
    break;

  case 157:
#line 996 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) NULL;
        }
#line 2929 "gram.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1003 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_TYPE_LIST, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 2940 "gram.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1010 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_TYPE_LIST, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 2951 "gram.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1017 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_TYPE_LIST, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 2962 "gram.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1026 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_TYPE_LIST, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 2973 "gram.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1033 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_TYPE_LIST, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 2984 "gram.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1042 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) NULL;
        }
#line 2992 "gram.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1050 "gram.y" /* yacc.c:1646  */
    {
           (yyvsp[-1].node)->hdr.type = TN_ASSIGN;
           (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
           (yyvsp[-1].node)->rnode = (yyvsp[0].node);
           (yyval.node) = (yyvsp[-1].node);
        }
#line 3003 "gram.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1058 "gram.y" /* yacc.c:1646  */
    {
          (yyval.node) = (treenode *) NULL;
        }
#line 3011 "gram.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1066 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_DECLS;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3022 "gram.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1075 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_INIT_LIST;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3033 "gram.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1084 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_INIT_BLK;
            (yyval.node) = (yyvsp[-2].node);
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
            free_tree((yyvsp[0].node));
        }
#line 3045 "gram.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1093 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) NULL;
        }
#line 3053 "gram.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1101 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_TYPE_LIST, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 3064 "gram.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1110 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (treenode *) NULL;
        }
#line 3072 "gram.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1147 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) (yyvsp[0].leaf);
        }
#line 3080 "gram.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1156 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) NULL;
        }
#line 3088 "gram.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1163 "gram.y" /* yacc.c:1646  */
    {
          (yyval.node) = (treenode *) (yyvsp[0].leaf);
        }
#line 3096 "gram.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1170 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-5].node)->hdr.type = TN_OBJ_DEF;
            (yyvsp[-5].node)->lnode = (yyvsp[-4].node);
            (yyvsp[-5].node)->rnode = (yyvsp[-2].node);
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[-1].node));
            free_tree((yyvsp[0].node));
            if (ParseStack->contxt && (yyvsp[-4].node))
              {
              leafnode *leaf = (leafnode *) (yyvsp[-4].node);
              if (! symtab_insert(ParseStack->contxt->tags,
                    mk_tag(leaf->data.sval, (yyval.node))))
                yyerr("Duplicate tag.");
              }
        }
#line 3116 "gram.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1187 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_OBJ_REF;
            (yyvsp[-1].node)->lnode = (yyvsp[0].node);
        }
#line 3125 "gram.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1194 "gram.y" /* yacc.c:1646  */
    {
           (yyvsp[-1].node)->hdr.type = TN_ENUM_LIST;
           (yyvsp[-1].node)->lnode = (treenode *) (yyvsp[-2].node);
           (yyvsp[-1].node)->rnode = (yyvsp[0].node);
           (yyval.node) = (yyvsp[-1].node);
        }
#line 3136 "gram.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1203 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_ASSIGN;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3147 "gram.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1211 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) (yyvsp[0].leaf);
           if (ParseStack->contxt)
             {
             if (! symtab_insert(ParseStack->contxt->syms,
                                 mk_enum_const((yyvsp[0].leaf)->data.sval, (yyval.node))))
               yyerr("Duplicate enumeration constant.");
             }
        }
#line 3161 "gram.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1222 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (treenode *) NULL;
        }
#line 3169 "gram.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1226 "gram.y" /* yacc.c:1646  */
    {
          yywarn("Trailing comma in enum type definition.");
        }
#line 3177 "gram.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1232 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-5].node)->hdr.type = TN_OBJ_DEF;
            (yyvsp[-5].node)->lnode = (yyvsp[-4].node);
            (yyvsp[-5].node)->rnode = (yyvsp[-1].node);
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[0].node));
            if (ParseStack->contxt && (yyvsp[-4].node))
            {
              leafnode *leaf = (leafnode *) (yyvsp[-4].node);
              if (! symtab_insert(ParseStack->contxt->tags,
                    mk_tag(leaf->data.sval, (yyval.node))))
                yyerr("Duplicate tag.");
            }
    
            find_components((yyvsp[-1].node),(yyvsp[-5].node),(yyvsp[-5].node),insert_component);
            exit_scope(ParseStack->contxt);
        }
#line 3199 "gram.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1251 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_OBJ_REF;
            (yyvsp[-1].node)->lnode = (yyvsp[0].node);
        }
#line 3208 "gram.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1257 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-5].node)->hdr.type = TN_OBJ_DEF;
            (yyvsp[-5].node)->lnode = (yyvsp[-4].node);
            (yyvsp[-5].node)->rnode = (yyvsp[-1].node);
            free_tree((yyvsp[-3].node));
            free_tree((yyvsp[0].node));
            if (ParseStack->contxt && (yyvsp[-4].node))
            {
              leafnode *leaf = (leafnode *) (yyvsp[-4].node);
              if (! symtab_insert(ParseStack->contxt->tags,
                    mk_tag(leaf->data.sval, (yyval.node))))
                yyerr("Duplicate tag.");
            }

            find_components((yyvsp[-1].node),(yyvsp[-5].node),(yyvsp[-5].node),insert_component);
            exit_scope(ParseStack->contxt);
        }
#line 3230 "gram.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1276 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_OBJ_REF;
            (yyvsp[-1].node)->lnode = (yyvsp[0].node);
        }
#line 3239 "gram.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1283 "gram.y" /* yacc.c:1646  */
    {
           treenode *tmpnode = make_node(TN_FIELD_LIST, ParseStack->contxt);
           tmpnode->lnode = (yyvsp[-1].node);
           tmpnode->rnode = (yyvsp[0].node);
           (yyval.node) = tmpnode;
        }
#line 3250 "gram.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1291 "gram.y" /* yacc.c:1646  */
    {
          (yyvsp[0].node)->hdr.type = TN_COMP_DECL;
          (yyvsp[0].node)->lnode = (yyvsp[-2].node);
          (yyvsp[0].node)->rnode = (yyvsp[-1].node);
          (yyval.node) = (yyvsp[0].node);
        }
#line 3261 "gram.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1300 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_DECLS;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3272 "gram.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1316 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_BIT_FIELD;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3283 "gram.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1332 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_TYPE_NME, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 3293 "gram.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1338 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_TYPE_NME, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 3304 "gram.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1346 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) NULL;
        }
#line 3312 "gram.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1353 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_DECL, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 3323 "gram.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1364 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (yyvsp[-1].node);
            free_tree((yyvsp[-2].node));
            free_tree((yyvsp[0].node));
        }
#line 3333 "gram.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1371 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_FUNC_DECL;
            (yyvsp[-2].node)->lnode = (yyvsp[-3].node);
            (yyvsp[-2].node)->rnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[-2].node);
            free_tree((yyvsp[0].node));
        }
#line 3345 "gram.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1379 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_FUNC_DECL;
            (yyvsp[-2].node)->lnode = (yyvsp[-3].node);
            (yyvsp[-2].node)->rnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[-2].node);
            free_tree((yyvsp[0].node));
        }
#line 3357 "gram.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1387 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_FUNC_DECL;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyval.node) = (yyvsp[-1].node);
            free_tree((yyvsp[0].node));
        }
#line 3368 "gram.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1396 "gram.y" /* yacc.c:1646  */
    {
           /* NYI - Need error check code here */
           leafnode *ln;
           ln = (yyvsp[0].leaf);
           /*  fprintf(stdout,"Value: %s\n", nmestr(ln->data.sval));  */
        }
#line 3379 "gram.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1404 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_PNTR;
            (yyvsp[-1].node)->lnode = (yyvsp[0].node);
            (yyvsp[-1].node)->rnode = NULL;
        }
#line 3389 "gram.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1412 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_PNTR;
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
        }
#line 3398 "gram.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1418 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) NULL;
        }
#line 3406 "gram.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1426 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_PARAM_LIST;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3417 "gram.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1435 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_PARAM_LIST;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3428 "gram.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1443 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_DECL, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 3439 "gram.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1450 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_DECL, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 3450 "gram.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1457 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_DECL, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 3460 "gram.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1464 "gram.y" /* yacc.c:1646  */
    {
           (yyval.node) = (treenode *) (yyvsp[0].leaf);
        }
#line 3468 "gram.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1468 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_IDENT_LIST;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (treenode *) (yyvsp[0].leaf);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3479 "gram.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1484 "gram.y" /* yacc.c:1646  */
    {
            /* Convert a TYPEDEF_NAME back into a normal IDENT */
            (yyvsp[0].leaf)->hdr.type = TN_IDENT;
            (yyvsp[0].leaf)->hdr.tok  = IDENT;
            (yyval.node) = (treenode *) (yyvsp[0].leaf);
        }
#line 3490 "gram.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1494 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_DECL, ParseStack->contxt);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 3500 "gram.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1500 "gram.y" /* yacc.c:1646  */
    {
            treenode *tmpnode = make_node(TN_DECL, ParseStack->contxt);
            tmpnode->lnode = (yyvsp[-1].node);
            tmpnode->rnode = (yyvsp[0].node);
            (yyval.node) = tmpnode;
        }
#line 3511 "gram.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1508 "gram.y" /* yacc.c:1646  */
    {
            (yyval.node) = (yyvsp[-1].node);
            free_tree((yyvsp[-2].node));
            free_tree((yyvsp[0].node));
        }
#line 3521 "gram.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1514 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_ARRAY_DECL;
            (yyvsp[-2].node)->rnode = (yyvsp[-1].node);
            free_tree((yyvsp[0].node));
        }
#line 3531 "gram.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1520 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_ARRAY_DECL;
            (yyvsp[-2].node)->lnode = (yyvsp[-3].node);
            (yyvsp[-2].node)->rnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[-2].node);
            free_tree((yyvsp[0].node));
        }
#line 3543 "gram.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1528 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_FUNC_DECL;
            (yyvsp[-1].node)->rnode = (yyvsp[-1].node);
            free_tree((yyvsp[0].node));
        }
#line 3553 "gram.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1534 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_FUNC_DECL;
            (yyvsp[-2].node)->lnode = (yyvsp[-3].node);
            (yyvsp[-2].node)->rnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[-2].node);
            free_tree((yyvsp[0].node));
        }
#line 3565 "gram.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1543 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_ARRAY_DECL;
            (yyvsp[-2].node)->lnode = (yyvsp[-3].node);
            (yyvsp[-2].node)->rnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[-2].node);
            free_tree((yyvsp[0].node));
        }
#line 3577 "gram.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1552 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_SELECT;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (treenode *) (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3588 "gram.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1560 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-1].node)->hdr.type = TN_SELECT;
            (yyvsp[-1].node)->lnode = (yyvsp[-2].node);
            (yyvsp[-1].node)->rnode = (treenode *) (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
#line 3599 "gram.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1568 "gram.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].node)->hdr.type = TN_FUNC_CALL;
            (yyvsp[-2].node)->lnode = (yyvsp[-3].node);
            (yyvsp[-2].node)->rnode = (yyvsp[-1].node);
            (yyval.node) = (yyvsp[-2].node);
            free_tree((yyvsp[0].node));
        }
#line 3611 "gram.c" /* yacc.c:1646  */
    break;


#line 3615 "gram.c" /* yacc.c:1646  */
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
#line 1586 "gram.y" /* yacc.c:1906  */


/***********************************************************************/
static void        /*ARGSUSED*/
insert_decl(leafnode *leaf, treenode *def, treenode *container)
{
    if (leaf && (leaf->hdr.tok == IDENT))
      if (ParseStack->contxt)
      {
          symentry_t *entry = mk_vardecl(leaf->data.sval, def);
          leaf->syment = symtab_insert(ParseStack->contxt->syms, entry);
		  *(leaf->hdr.c_contxt->syms) = *(ParseStack->contxt->syms);
      }
}


static void        /*ARGSUSED*/
insert_typedef(leafnode *leaf, treenode *def, treenode *container)
{
    if (leaf && (leaf->hdr.tok == IDENT))
      if (ParseStack->contxt)
      {
          symentry_t *entry = mk_typedef(leaf->data.sval, def); 
          leaf->syment = symtab_insert(ParseStack->contxt->syms,entry);
		  *(leaf->hdr.c_contxt->syms) = *(ParseStack->contxt->syms);
      }
}

static void
insert_component(leafnode *leaf, treenode *def, treenode *container)
{
    if (leaf && (leaf->hdr.tok == IDENT))
      if (ParseStack->contxt)
      {
          symentry_t *entry = mk_component(leaf->data.sval, def, container);
          leaf->syment = symtab_insert(ParseStack->contxt->syms, entry);
		  *(leaf->hdr.c_contxt->syms) = *(ParseStack->contxt->syms);
      }
}

/***********************************************************************/
static void
add_params_to_symtab(treenode *funcdecl)
{
    /* Parameters are defined at prototype/function scope */
    enter_scope(ParseStack->contxt);

    find_params(funcdecl, insert_decl);
}

/***********************************************************************/
treenode *parse_include( char *filename )
{
FILE *fp;

    fprintf(stderr, "Request to parse included file %s\n", filename);

        /* Should really search around */
    if ((fp = fopen(filename,"r")) == NULL){
        fprintf(stderr, "Error: couldn't locate included file %s\n",filename);
        return(NULL);
    }
    
    handle_new_file(ParseStack, fp, filename);    

    tree_parse(ParseStack, 0);

    return( (top_of_stack(DoneStack))->parse_tree );
}

/***********************************************************************/
