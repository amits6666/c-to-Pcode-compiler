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
