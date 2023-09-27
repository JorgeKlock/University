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
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFICADOR = 258,
    TIPO_DATO_BASICO = 259,
    LISTA = 260,
    SI = 261,
    MIENTRAS = 262,
    PARA = 263,
    BAJANDO_HASTA = 264,
    HASTA = 265,
    HACER = 266,
    SALIDA = 267,
    ENTRADA = 268,
    SINO = 269,
    RETORNO = 270,
    PRINCIPAL = 271,
    VAR = 272,
    VAREND = 273,
    PIZQ = 274,
    PDCH = 275,
    CIZQ = 276,
    CDCH = 277,
    PUNTO = 278,
    COMA = 279,
    COMILLAS_DOBLES = 280,
    COR_ABRE = 281,
    COR_CIERRA = 282,
    COMIENZO_LISTA = 283,
    MOV_CURSOR = 284,
    ARROBA = 285,
    ALFABETICO = 286,
    NUMERICO = 287,
    BOOLEANO = 288,
    C_ESPE = 289,
    PYC = 290,
    OP_ASIGNACION = 291,
    ALFABETICOPRIO = 292,
    OP_BINARIO = 293,
    ADITIVO = 294,
    MULTIPLICATIVO = 295,
    ALMOHADILLA = 296,
    EXCLAINTER = 297,
    MASMAS = 298
  };
#endif
/* Tokens.  */
#define IDENTIFICADOR 258
#define TIPO_DATO_BASICO 259
#define LISTA 260
#define SI 261
#define MIENTRAS 262
#define PARA 263
#define BAJANDO_HASTA 264
#define HASTA 265
#define HACER 266
#define SALIDA 267
#define ENTRADA 268
#define SINO 269
#define RETORNO 270
#define PRINCIPAL 271
#define VAR 272
#define VAREND 273
#define PIZQ 274
#define PDCH 275
#define CIZQ 276
#define CDCH 277
#define PUNTO 278
#define COMA 279
#define COMILLAS_DOBLES 280
#define COR_ABRE 281
#define COR_CIERRA 282
#define COMIENZO_LISTA 283
#define MOV_CURSOR 284
#define ARROBA 285
#define ALFABETICO 286
#define NUMERICO 287
#define BOOLEANO 288
#define C_ESPE 289
#define PYC 290
#define OP_ASIGNACION 291
#define ALFABETICOPRIO 292
#define OP_BINARIO 293
#define ADITIVO 294
#define MULTIPLICATIVO 295
#define ALMOHADILLA 296
#define EXCLAINTER 297
#define MASMAS 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
