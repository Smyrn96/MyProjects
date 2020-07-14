/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

	#include "targetCodeLib.h"

	#define YY_DECL int alpha_yylex (void* ylval) 

	int yyerror (char* yaccProvidedMessage);
	int yylex(void);
	int dollar_counter = 0;
	char * buffer;
	struct stack * functionLocalsStack;
	struct stack * loopcounterstack;
	struct stack * funcjumpstack;
	struct stacklist * breakstacklist;
	struct stacklist * contstacklist;
	struct stmt * breaklist_head;
	struct stmt * contlist_head;
	struct stacklist * returnstacklist;
	struct stmt * returnlist_head;
	symrec_t * tmp_rec;
	
	extern int yylineno;
	extern char * yytext;
	extern FILE * yyin;
	extern FILE * yyout;


#line 97 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    FOR = 261,
    FUNCTION = 262,
    RETURN = 263,
    BREAK = 264,
    CONTINUE = 265,
    AND = 266,
    NOT = 267,
    OR = 268,
    LOCAL = 269,
    TRUE = 270,
    FALSE = 271,
    NIL = 272,
    ASSIGN = 273,
    ADD = 274,
    MINUS = 275,
    MULTIPLICATION = 276,
    DIVISION = 277,
    MODULO = 278,
    EQUAL = 279,
    INEQUAL = 280,
    INCREMENT = 281,
    DECREMENT = 282,
    GREATER = 283,
    GREATER_EQUAL = 284,
    LESS = 285,
    LESS_EQUAL = 286,
    LEFT_CURLY_BRACKET = 287,
    RIGHT_CURLY_BRACKET = 288,
    LEFT_SQUARE_BRACKET = 289,
    RIGHT_SQUARE_BRACKET = 290,
    LEFT_PARENTHESIS = 291,
    RIGHT_PARENTHESIS = 292,
    SEMICOLON = 293,
    COMMA = 294,
    COLON = 295,
    DOUBLE_COLON = 296,
    DOT = 297,
    DOUBLE_DOT = 298,
    SINGLE_LINE_COMMENT = 299,
    OTHERCHAR = 300,
    IDENT = 301,
    INTEGER = 302,
    REAL = 303,
    STRINGCONST = 304,
    UMINUS = 305
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define AND 266
#define NOT 267
#define OR 268
#define LOCAL 269
#define TRUE 270
#define FALSE 271
#define NIL 272
#define ASSIGN 273
#define ADD 274
#define MINUS 275
#define MULTIPLICATION 276
#define DIVISION 277
#define MODULO 278
#define EQUAL 279
#define INEQUAL 280
#define INCREMENT 281
#define DECREMENT 282
#define GREATER 283
#define GREATER_EQUAL 284
#define LESS 285
#define LESS_EQUAL 286
#define LEFT_CURLY_BRACKET 287
#define RIGHT_CURLY_BRACKET 288
#define LEFT_SQUARE_BRACKET 289
#define RIGHT_SQUARE_BRACKET 290
#define LEFT_PARENTHESIS 291
#define RIGHT_PARENTHESIS 292
#define SEMICOLON 293
#define COMMA 294
#define COLON 295
#define DOUBLE_COLON 296
#define DOT 297
#define DOUBLE_DOT 298
#define SINGLE_LINE_COMMENT 299
#define OTHERCHAR 300
#define IDENT 301
#define INTEGER 302
#define REAL 303
#define STRINGCONST 304
#define UMINUS 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 30 "parser.y"

	char*	stringValue;
	int		intValue;
	double	doubleValue;
	struct expr* node;
	struct forVar* forpref;
	struct stmt* stmt_node;

#line 258 "parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   565

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  207

#define YYUNDEFTOK  2
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   143,   143,   146,   147,   148,   149,   150,   156,   156,
     159,   159,   162,   163,   164,   167,   167,   168,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   188,   189,   190,   191,   203,   215,   227,
     239,   242,   261,   242,   275,   302,   303,   304,   305,   314,
     367,   387,   394,   397,   398,   399,   400,   404,   405,   416,
     423,   424,   427,   427,   435,   435,   444,   445,   448,   449,
     452,   463,   475,   478,   479,   482,   482,   485,   485,   486,
     489,   489,   509,   509,   489,   524,   540,   540,   524,   556,
     557,   558,   559,   560,   561,   564,   564,   574,   577,   577,
     587,   590,   595,   597,   598,   601,   604,   604,   613,   624,
     626,   628,   636,   636,   655,   655,   659,   659
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE",
  "FALSE", "NIL", "ASSIGN", "ADD", "MINUS", "MULTIPLICATION", "DIVISION",
  "MODULO", "EQUAL", "INEQUAL", "INCREMENT", "DECREMENT", "GREATER",
  "GREATER_EQUAL", "LESS", "LESS_EQUAL", "LEFT_CURLY_BRACKET",
  "RIGHT_CURLY_BRACKET", "LEFT_SQUARE_BRACKET", "RIGHT_SQUARE_BRACKET",
  "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "SEMICOLON", "COMMA", "COLON",
  "DOUBLE_COLON", "DOT", "DOUBLE_DOT", "SINGLE_LINE_COMMENT", "OTHERCHAR",
  "IDENT", "INTEGER", "REAL", "STRINGCONST", "UMINUS", "$accept",
  "program", "stmt", "$@1", "$@2", "stmt_list", "$@3", "expr", "term",
  "assignexpr", "$@4", "$@5", "primary", "lvalue", "member", "call",
  "callsuffix", "normcall", "$@6", "methodcall", "$@7", "elist",
  "elist_expressions", "objectdef", "indexed", "indexedelem_list",
  "indexedelem", "$@8", "block", "$@9", "funcdef", "$@10", "@11", "$@12",
  "$@13", "@14", "$@15", "$@16", "const", "idlist", "$@17", "idlist_list",
  "$@18", "ifprefix", "elseprefix", "ifstmt", "whilestart", "whilecond",
  "$@19", "whilestmt", "N", "M", "forprefix", "forstmt", "$@20",
  "returnstmt", "$@21", "$@22", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF (-190)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-117)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     167,   -25,  -190,   -21,   -19,    -7,  -190,  -190,   243,   -12,
    -190,  -190,  -190,   243,   -11,   -11,     3,   205,   101,  -190,
      -9,  -190,  -190,  -190,  -190,    40,  -190,  -190,   317,  -190,
    -190,  -190,   -14,  -190,   -15,  -190,  -190,  -190,  -190,   167,
    -190,    14,  -190,  -190,  -190,  -190,   243,   243,     5,    17,
     243,    16,    18,    20,  -190,  -190,    22,    52,   -10,   -15,
     -10,  -190,   167,   243,   296,    25,    26,    23,   380,    27,
    -190,  -190,   167,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,  -190,  -190,  -190,   243,
    -190,    36,    37,    45,  -190,  -190,  -190,   243,   243,    38,
      74,  -190,   167,   243,   401,    42,  -190,  -190,   338,  -190,
    -190,  -190,    48,    53,   274,   243,  -190,  -190,  -190,    55,
    -190,  -190,    57,  -190,    81,   521,    22,    22,  -190,  -190,
    -190,   534,   534,   245,   245,   245,   245,   443,   243,  -190,
      58,  -190,   464,    51,  -190,  -190,   167,   243,  -190,    54,
    -190,  -190,    60,    73,  -190,    57,  -190,  -190,   296,    23,
     243,  -190,    61,  -190,   243,  -190,  -190,  -190,   422,  -190,
     243,  -190,  -190,    62,   243,  -190,  -190,    83,  -190,   243,
     506,  -190,  -190,   359,    73,    85,  -190,   485,  -190,    88,
     167,  -190,    89,    76,  -190,    65,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,    65,    85,  -190,  -190
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      17,     0,   105,     0,    80,   114,     8,    10,     0,     0,
      93,    94,    92,     0,     0,     0,    77,    67,     0,    14,
       0,    49,    89,    90,    91,     0,    15,     2,     0,    32,
      18,    40,    44,    52,    45,    46,    12,    13,    48,     0,
       4,     0,     5,   109,     6,     7,     0,    67,     0,     0,
       0,     0,     0,     0,    35,    50,    34,     0,    36,     0,
      38,    79,    17,     0,    69,     0,     0,    74,     0,     0,
      51,     1,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,    37,    39,     0,
      62,     0,     0,     0,    58,    60,    61,     0,    67,     0,
     103,   106,     0,    67,     0,     0,    81,    86,     0,   117,
       9,    11,     0,     0,     0,     0,    66,    70,    71,     0,
      72,    33,    47,    16,    30,    31,    19,    20,    21,    22,
      23,    28,    29,    24,    25,    26,    27,     0,    67,    53,
       0,    42,     0,     0,    55,   102,     0,     0,   108,     0,
     101,   110,     0,    97,   115,     0,    78,    75,    69,    74,
      67,    54,     0,    64,     0,    56,    57,   104,     0,   112,
       0,    82,    95,     0,     0,    68,    73,     0,    63,    67,
      43,   107,   109,     0,    97,   100,    87,     0,    59,     0,
       0,   111,     0,     0,    96,     0,    76,    65,   109,    83,
      98,    88,   113,     0,   100,    84,    99
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -190,  -190,   -23,  -190,  -190,   -54,  -190,    -8,  -190,  -190,
    -190,  -190,  -190,    32,  -190,    34,  -190,  -190,  -190,  -190,
    -190,   -46,   -29,  -190,  -190,   -28,    13,  -190,  -189,  -190,
     -16,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,   -50,
    -190,   -68,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -175,  -190,  -190,  -190,  -190,  -190,  -190,  -190
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    52,    53,    27,    72,    28,    29,    30,
      93,   164,    31,    32,    33,    34,    94,    95,   138,    96,
     179,    65,   116,    35,    66,   120,    67,   174,    36,    62,
      37,    48,   152,   184,   203,    49,   153,   195,    38,   173,
     185,   194,   204,    39,   146,    40,    41,   102,   147,    42,
     103,   170,    43,    44,   182,    45,    50,    51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,   105,    69,     9,   -41,    56,   201,   190,   113,    64,
      68,    46,    87,    88,   205,    47,   100,   -85,   123,    97,
      89,    98,    90,   202,    89,    57,    90,    99,    91,    92,
      20,  -116,    91,    92,    55,    21,    61,    70,   104,    64,
      71,   112,   108,    77,    78,    79,    58,    60,    59,    59,
     101,   106,   143,   107,   109,   114,   110,   149,   111,     4,
     117,   118,   119,   141,   122,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   145,   148,
     151,   137,   139,   140,   144,   155,   156,    63,   166,   142,
      64,   169,   162,   160,   163,    64,   171,    16,   178,   186,
      75,    76,    77,    78,    79,    80,    81,   158,     4,    82,
      83,    84,    85,     8,   177,     9,    10,    11,    12,   172,
     188,    13,   200,   167,   193,   197,   199,    14,    15,   175,
      64,   176,   159,   189,   192,    17,   206,    18,     0,   168,
       0,     0,    20,     0,     0,     0,     0,    21,    22,    23,
      24,     0,    64,     0,     0,     0,   180,     0,     0,     0,
       0,     0,   183,     0,     0,     0,   187,   198,     0,     0,
       1,    64,     2,     3,     4,     5,     6,     7,     0,     8,
       0,     9,    10,    11,    12,     0,     0,    13,     0,     0,
       0,     0,     0,    14,    15,     0,     0,     0,     0,    16,
       0,    17,     0,    18,     0,    19,     0,     0,    20,     0,
       0,     0,     0,    21,    22,    23,    24,     8,     0,     9,
      10,    11,    12,     0,     0,    13,     0,     0,     0,     0,
       0,    14,    15,     0,     0,     0,     0,    63,     0,    17,
       0,    18,     0,     0,     0,     0,    20,     0,     0,     0,
       0,    21,    22,    23,    24,     8,     0,     9,    10,    11,
      12,     0,     0,    13,    75,    76,    77,    78,    79,    14,
      15,     0,     0,  -117,  -117,  -117,  -117,    17,     0,    18,
       0,     0,     0,     0,    20,    73,     0,    74,     0,    21,
      22,    23,    24,    75,    76,    77,    78,    79,    80,    81,
       0,     0,    82,    83,    84,    85,     0,    73,     0,    74,
       0,     0,     0,     0,   157,    75,    76,    77,    78,    79,
      80,    81,     0,     0,    82,    83,    84,    85,    73,     0,
      74,     0,     0,     0,     0,   115,    75,    76,    77,    78,
      79,    80,    81,     0,     0,    82,    83,    84,    85,    73,
       0,    74,     0,     0,     0,    86,     0,    75,    76,    77,
      78,    79,    80,    81,     0,     0,    82,    83,    84,    85,
      73,     0,    74,     0,     0,     0,   154,     0,    75,    76,
      77,    78,    79,    80,    81,     0,     0,    82,    83,    84,
      85,    73,     0,    74,     0,     0,     0,   191,     0,    75,
      76,    77,    78,    79,    80,    81,     0,     0,    82,    83,
      84,    85,    73,     0,    74,     0,     0,   121,     0,     0,
      75,    76,    77,    78,    79,    80,    81,     0,     0,    82,
      83,    84,    85,    73,     0,    74,     0,     0,   150,     0,
       0,    75,    76,    77,    78,    79,    80,    81,     0,     0,
      82,    83,    84,    85,    73,     0,    74,     0,     0,   181,
       0,     0,    75,    76,    77,    78,    79,    80,    81,     0,
       0,    82,    83,    84,    85,    73,     0,    74,   161,     0,
       0,     0,     0,    75,    76,    77,    78,    79,    80,    81,
       0,     0,    82,    83,    84,    85,    73,     0,    74,   165,
       0,     0,     0,     0,    75,    76,    77,    78,    79,    80,
      81,     0,     0,    82,    83,    84,    85,    73,   196,    74,
       0,     0,     0,     0,     0,    75,    76,    77,    78,    79,
      80,    81,    73,     0,    82,    83,    84,    85,     0,     0,
      75,    76,    77,    78,    79,    80,    81,     0,     0,    82,
      83,    84,    85,    75,    76,    77,    78,    79,  -117,  -117,
       0,     0,    82,    83,    84,    85
};

static const yytype_int16 yycheck[] =
{
       8,    47,    18,    14,    18,    13,   195,   182,    62,    17,
      18,    36,    26,    27,   203,    36,    39,    36,    72,    34,
      34,    36,    36,   198,    34,    36,    36,    42,    42,    43,
      41,    38,    42,    43,    46,    46,    33,    46,    46,    47,
       0,    57,    50,    21,    22,    23,    14,    15,    14,    15,
      36,    46,    98,    36,    38,    63,    38,   103,    38,     7,
      35,    35,    39,    18,    37,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,     4,   102,
      38,    89,    46,    46,    46,    37,    33,    32,    37,    97,
      98,    37,   138,    36,    36,   103,    36,    32,    37,    37,
      19,    20,    21,    22,    23,    24,    25,   115,     7,    28,
      29,    30,    31,    12,   160,    14,    15,    16,    17,    46,
      37,    20,    46,   146,    39,    37,    37,    26,    27,   158,
     138,   159,   119,   179,   184,    34,   204,    36,    -1,   147,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    -1,   160,    -1,    -1,    -1,   164,    -1,    -1,    -1,
      -1,    -1,   170,    -1,    -1,    -1,   174,   190,    -1,    -1,
       3,   179,     5,     6,     7,     8,     9,    10,    -1,    12,
      -1,    14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    32,
      -1,    34,    -1,    36,    -1,    38,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    12,    -1,    14,
      15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    27,    -1,    -1,    -1,    -1,    32,    -1,    34,
      -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    12,    -1,    14,    15,    16,
      17,    -1,    -1,    20,    19,    20,    21,    22,    23,    26,
      27,    -1,    -1,    28,    29,    30,    31,    34,    -1,    36,
      -1,    -1,    -1,    -1,    41,    11,    -1,    13,    -1,    46,
      47,    48,    49,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    11,    -1,    13,
      -1,    -1,    -1,    -1,    40,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    11,    -1,
      13,    -1,    -1,    -1,    -1,    39,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    11,
      -1,    13,    -1,    -1,    -1,    38,    -1,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      11,    -1,    13,    -1,    -1,    -1,    38,    -1,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    11,    -1,    13,    -1,    -1,    -1,    38,    -1,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    11,    -1,    13,    -1,    -1,    37,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    11,    -1,    13,    -1,    -1,    37,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    11,    -1,    13,    -1,    -1,    37,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    11,    -1,    13,    35,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    11,    -1,    13,    35,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    11,    33,    13,
      -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    11,    -1,    28,    29,    30,    31,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     7,     8,     9,    10,    12,    14,
      15,    16,    17,    20,    26,    27,    32,    34,    36,    38,
      41,    46,    47,    48,    49,    52,    53,    56,    58,    59,
      60,    63,    64,    65,    66,    74,    79,    81,    89,    94,
      96,    97,   100,   103,   104,   106,    36,    36,    82,    86,
     107,   108,    54,    55,    58,    46,    58,    36,    64,    66,
      64,    33,    80,    32,    58,    72,    75,    77,    58,    81,
      46,     0,    57,    11,    13,    19,    20,    21,    22,    23,
      24,    25,    28,    29,    30,    31,    38,    26,    27,    34,
      36,    42,    43,    61,    67,    68,    70,    34,    36,    42,
      53,    36,    98,   101,    58,    72,    46,    36,    58,    38,
      38,    38,    81,    56,    58,    39,    73,    35,    35,    39,
      76,    37,    37,    56,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    69,    46,
      46,    18,    58,    72,    46,     4,    95,    99,    53,    72,
      37,    38,    83,    87,    38,    37,    33,    40,    58,    77,
      36,    35,    72,    36,    62,    35,    37,    53,    58,    37,
     102,    36,    46,    90,    78,    73,    76,    72,    37,    71,
      58,    37,   105,    58,    84,    91,    37,    58,    37,    72,
     101,    38,    90,    39,    92,    88,    33,    37,    53,    37,
      46,    79,   101,    85,    93,    79,    92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    53,    53,    53,    54,    53,
      55,    53,    53,    53,    53,    57,    56,    56,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    59,    59,    59,    59,    59,    59,    59,
      59,    61,    62,    60,    63,    63,    63,    63,    63,    64,
      64,    64,    64,    65,    65,    65,    65,    66,    66,    66,
      67,    67,    69,    68,    71,    70,    72,    72,    73,    73,
      74,    74,    75,    76,    76,    78,    77,    80,    79,    79,
      82,    83,    84,    85,    81,    86,    87,    88,    81,    89,
      89,    89,    89,    89,    89,    91,    90,    90,    93,    92,
      92,    94,    95,    96,    96,    97,    99,    98,   100,   101,
     102,   103,   105,   104,   107,   106,   108,   106
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     0,     3,
       0,     3,     1,     1,     1,     0,     3,     0,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     2,     2,     2,     2,     2,     2,
       1,     0,     0,     5,     1,     1,     1,     3,     1,     1,
       2,     2,     1,     3,     4,     3,     4,     4,     2,     6,
       1,     1,     0,     4,     0,     6,     2,     0,     3,     0,
       3,     3,     2,     3,     0,     0,     6,     0,     4,     2,
       0,     0,     0,     0,    10,     0,     0,     0,     8,     1,
       1,     1,     1,     1,     1,     0,     3,     0,     0,     4,
       0,     4,     1,     2,     4,     1,     0,     4,     3,     0,
       0,     7,     0,     8,     0,     4,     0,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 3:
#line 146 "parser.y"
                               {tempcounter=0; (yyval.stmt_node) = NULL;}
#line 1661 "parser.c"
    break;

  case 4:
#line 147 "parser.y"
                                {tempcounter=0; (yyval.stmt_node) = NULL;}
#line 1667 "parser.c"
    break;

  case 5:
#line 148 "parser.y"
                                  {tempcounter=0; (yyval.stmt_node) = NULL;}
#line 1673 "parser.c"
    break;

  case 6:
#line 149 "parser.y"
                                {tempcounter=0; (yyval.stmt_node) = NULL;}
#line 1679 "parser.c"
    break;

  case 7:
#line 150 "parser.y"
                                   {tempcounter=0; (yyval.stmt_node) = NULL;
							stmt * tempstmt = newstmt(nextquadlabel());
							tempstmt->next = topstacklist(returnstacklist)->next;
							topstacklist(returnstacklist)->next = tempstmt;
							emit(jump, newexpr_constnum(0), (expr *) 0, (expr *) 0,currQuad, yylineno);
					   }
#line 1690 "parser.c"
    break;

  case 8:
#line 156 "parser.y"
                              {if(!loopcounter){yyerror("Use of 'break' while not in a loop");}}
#line 1696 "parser.c"
    break;

  case 9:
#line 156 "parser.y"
                                                                                                          {tempcounter=0; (yyval.stmt_node) = newstmt(nextquadlabel()); 
												(yyval.stmt_node)->next = topstacklist(breakstacklist)->next; topstacklist(breakstacklist)->next = (yyval.stmt_node);
												emit(jump, newexpr_constnum(0), (expr *)0, (expr *)0, currQuad, yylineno);}
#line 1704 "parser.c"
    break;

  case 10:
#line 159 "parser.y"
                                 {if(!loopcounter){yyerror("Use of 'return' while not in a loop");}}
#line 1710 "parser.c"
    break;

  case 11:
#line 159 "parser.y"
                                                                                                              {tempcounter=0; (yyval.stmt_node) = newstmt(nextquadlabel());
												(yyval.stmt_node)->next = topstacklist(contstacklist)->next; topstacklist(contstacklist)->next = (yyval.stmt_node);
												emit(jump, newexpr_constnum(0), (expr *)0, (expr *)0, currQuad, yylineno);}
#line 1718 "parser.c"
    break;

  case 12:
#line 162 "parser.y"
                              {tempcounter=0; (yyval.stmt_node) = NULL;}
#line 1724 "parser.c"
    break;

  case 13:
#line 163 "parser.y"
                                {tempcounter=0; (yyval.stmt_node) = NULL;}
#line 1730 "parser.c"
    break;

  case 14:
#line 164 "parser.y"
                                  {tempcounter=0; (yyval.stmt_node) = NULL;}
#line 1736 "parser.c"
    break;

  case 15:
#line 167 "parser.y"
                    { first_cmd_stmt = 1; }
#line 1742 "parser.c"
    break;

  case 16:
#line 167 "parser.y"
                                                      { (yyval.stmt_node) = (yyvsp[-2].stmt_node);}
#line 1748 "parser.c"
    break;

  case 17:
#line 168 "parser.y"
                         {(yyval.stmt_node) = NULL;}
#line 1754 "parser.c"
    break;

  case 18:
#line 171 "parser.y"
                           {(yyval.node)=(yyvsp[0].node);}
#line 1760 "parser.c"
    break;

  case 19:
#line 172 "parser.y"
                                       { if(validtype((yyvsp[-2].node), (yyvsp[0].node))){ (yyval.node) = newexpr(arithexpr_e); (yyval.node)->type = returnType((yyval.node),(yyvsp[-2].node),(yyvsp[0].node)); (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emit(add, (yyval.node), (yyvsp[-2].node), (yyvsp[0].node), currQuad, yylineno);} }
#line 1766 "parser.c"
    break;

  case 20:
#line 173 "parser.y"
                                         {if(validtype((yyvsp[-2].node), (yyvsp[0].node))){ (yyval.node) = newexpr(arithexpr_e); (yyval.node)->type = returnType((yyval.node),(yyvsp[-2].node),(yyvsp[0].node));  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emit(sub, (yyval.node), (yyvsp[-2].node), (yyvsp[0].node), currQuad, yylineno);} }
#line 1772 "parser.c"
    break;

  case 21:
#line 174 "parser.y"
                                                  {if(validtype((yyvsp[-2].node), (yyvsp[0].node))){ (yyval.node) = newexpr(arithexpr_e); (yyval.node)->type = returnType((yyval.node),(yyvsp[-2].node),(yyvsp[0].node));  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emit(mul, (yyval.node), (yyvsp[-2].node), (yyvsp[0].node), currQuad, yylineno);} }
#line 1778 "parser.c"
    break;

  case 22:
#line 175 "parser.y"
                                            {if(validtype((yyvsp[-2].node), (yyvsp[0].node))){ (yyval.node) = newexpr(arithexpr_e); (yyval.node)->type = returnType((yyval.node),(yyvsp[-2].node),(yyvsp[0].node));  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emit(div_, (yyval.node), (yyvsp[-2].node), (yyvsp[0].node), currQuad, yylineno);} }
#line 1784 "parser.c"
    break;

  case 23:
#line 176 "parser.y"
                                          {if(validtype((yyvsp[-2].node), (yyvsp[0].node))){ (yyval.node) = newexpr(arithexpr_e); (yyval.node)->type = returnType((yyval.node),(yyvsp[-2].node),(yyvsp[0].node));  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emit(mod, (yyval.node), (yyvsp[-2].node), (yyvsp[0].node), currQuad, yylineno);} }
#line 1790 "parser.c"
    break;

  case 24:
#line 177 "parser.y"
                                           {(yyval.node) = newexpr(boolexpr_e);  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emitRelop((yyval.node), (yyvsp[-2].node), (yyvsp[0].node), if_greater, yylineno); }
#line 1796 "parser.c"
    break;

  case 25:
#line 178 "parser.y"
                                                 {(yyval.node) = newexpr(boolexpr_e);  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emitRelop((yyval.node), (yyvsp[-2].node), (yyvsp[0].node), if_greatereq, yylineno); }
#line 1802 "parser.c"
    break;

  case 26:
#line 179 "parser.y"
                                        {(yyval.node) = newexpr(boolexpr_e);  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emitRelop((yyval.node), (yyvsp[-2].node), (yyvsp[0].node), if_less, yylineno); }
#line 1808 "parser.c"
    break;

  case 27:
#line 180 "parser.y"
                                              {(yyval.node) = newexpr(boolexpr_e);  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emitRelop((yyval.node), (yyvsp[-2].node), (yyvsp[0].node), if_lesseq, yylineno); }
#line 1814 "parser.c"
    break;

  case 28:
#line 181 "parser.y"
                                         {(yyval.node) = newexpr(boolexpr_e);  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emitRelop((yyval.node), (yyvsp[-2].node), (yyvsp[0].node), if_eq, yylineno); }
#line 1820 "parser.c"
    break;

  case 29:
#line 182 "parser.y"
                                           {(yyval.node) = newexpr(boolexpr_e);  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emitRelop((yyval.node), (yyvsp[-2].node), (yyvsp[0].node), if_noteq, yylineno); }
#line 1826 "parser.c"
    break;

  case 30:
#line 183 "parser.y"
                                       {(yyval.node) = newexpr(boolexpr_e);  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emit(and, (yyval.node) , (yyvsp[-2].node), (yyvsp[0].node), currQuad, yylineno); }
#line 1832 "parser.c"
    break;

  case 31:
#line 184 "parser.y"
                                      {(yyval.node) = newexpr(boolexpr_e);  (yyval.node)->sym = returnTempName((yyvsp[-2].node),(yyvsp[0].node)); emit(or, (yyval.node) , (yyvsp[-2].node), (yyvsp[0].node), currQuad, yylineno); }
#line 1838 "parser.c"
    break;

  case 32:
#line 185 "parser.y"
                              {(yyval.node)=(yyvsp[0].node);}
#line 1844 "parser.c"
    break;

  case 33:
#line 188 "parser.y"
                                                        {(yyval.node)=(yyvsp[-1].node);}
#line 1850 "parser.c"
    break;

  case 34:
#line 189 "parser.y"
                                    {checkuminus((yyvsp[0].node)); (yyval.node)=newexpr(arithexpr_e); (yyval.node)->sym = newtemp(); emit(uminus, (yyval.node), (yyvsp[0].node), (expr *) 0, currQuad, yylineno);}
#line 1856 "parser.c"
    break;

  case 35:
#line 190 "parser.y"
                                  {(yyval.node)=newexpr(boolexpr_e); (yyval.node)->sym = newtemp(); emit(not, (yyval.node), (yyvsp[0].node), (expr *) 0, currQuad, yylineno);}
#line 1862 "parser.c"
    break;

  case 36:
#line 191 "parser.y"
                                          {if(token_is_func){yyerror("cannot increment function value"); token_is_func = 0;} 
								if((yyvsp[0].node)->type == tableitem_e){
									(yyval.node) = emit_iftableitem((yyvsp[0].node));
									emit(add, (yyval.node), (yyval.node), newexpr_constnum(1), currQuad, yylineno);
									emit(tablesetelem, (yyval.node), (yyvsp[0].node), (yyvsp[0].node)->index, currQuad, yylineno);
								}else{
									emit(add, (yyvsp[0].node), (yyvsp[0].node), newexpr_constnum(1), currQuad, yylineno);
									(yyval.node) = newexpr(arithexpr_e);
									(yyval.node)->sym = newtemp();
									emit(assign, (yyval.node), (yyvsp[0].node), (expr*) 0, currQuad, yylineno);
								}
							}
#line 1879 "parser.c"
    break;

  case 37:
#line 203 "parser.y"
                                          {if(token_is_func){yyerror("cannot increment function value"); token_is_func = 0;}
								(yyval.node) = newexpr(var_e); (yyval.node)->sym = newtemp();
								if((yyvsp[-1].node)->type == tableitem_e){
									expr * value = emit_iftableitem((yyvsp[-1].node));
									emit(assign, (yyval.node), value, (expr*) 0, currQuad, yylineno);
									emit(add, value, value, newexpr_constnum(1), currQuad, yylineno);
									emit(tablesetelem, value, (yyvsp[-1].node), (yyvsp[-1].node)->index, currQuad, yylineno);
								}else{
									emit(assign, (yyval.node), (yyvsp[-1].node), (expr*) 0, currQuad, yylineno);
									emit(add, (yyvsp[-1].node), (yyvsp[-1].node), newexpr_constnum(1), currQuad, yylineno);
								}
							}
#line 1896 "parser.c"
    break;

  case 38:
#line 215 "parser.y"
                                          {if(token_is_func){yyerror("cannot decrement function value"); token_is_func = 0;} 
								if((yyvsp[0].node)->type == tableitem_e){
									(yyval.node) = emit_iftableitem((yyvsp[0].node));
									emit(sub, (yyval.node), (yyval.node), newexpr_constnum(1), currQuad, yylineno);
									emit(tablesetelem, (yyval.node), (yyvsp[0].node), (yyvsp[0].node)->index, currQuad, yylineno);
								}else{
									emit(sub, (yyvsp[0].node), (yyvsp[0].node), newexpr_constnum(1), currQuad, yylineno);
									(yyval.node) = newexpr(arithexpr_e);
									(yyval.node)->sym = newtemp();
									emit(assign, (yyval.node), (yyvsp[0].node), (expr*) 0, currQuad, yylineno);
								}
							}
#line 1913 "parser.c"
    break;

  case 39:
#line 227 "parser.y"
                                          {if(token_is_func){yyerror("cannot decrement function value"); token_is_func = 0;} 
								(yyval.node) = newexpr(var_e); (yyval.node)->sym = newtemp();
								if((yyvsp[-1].node)->type == tableitem_e){
									expr * value = emit_iftableitem((yyvsp[-1].node));
									emit(assign, (yyval.node), value, (expr*) 0, currQuad, yylineno);
									emit(sub, value, value, newexpr_constnum(1), currQuad, yylineno);
									emit(tablesetelem, value, (yyvsp[-1].node), (yyvsp[-1].node)->index, currQuad, yylineno);
								}else{
									emit(assign, (yyval.node), (yyvsp[-1].node), (expr*) 0, currQuad, yylineno);
									emit(sub, (yyvsp[-1].node), (yyvsp[-1].node), newexpr_constnum(1), currQuad, yylineno);
								}
							}
#line 1930 "parser.c"
    break;

  case 40:
#line 239 "parser.y"
                                 {(yyval.node) = (yyvsp[0].node);}
#line 1936 "parser.c"
    break;

  case 41:
#line 242 "parser.y"
                      {		
						if((yyvsp[0].node) != NULL && (yyvsp[0].node)->sym->type == LIBFUNC){
							yyerror("Invalid insertion,0 trying to shadow LIBFUNC, before"); 
						}
						if((yyvsp[0].node) != NULL && (yyvsp[0].node)->sym->type == USERFUNC ){
							yyerror("variable already defined as function");
						}
						if(assignInRow){
							if(scope){
								tmp_rec = insert(scope, yylineno, LOCALVAR, yylval.stringValue);
								extraSets(tmp_rec);
							}else{
								tmp_rec = insert(scope, yylineno, GLOBAL, yylval.stringValue);
								extraSets(tmp_rec);
							}
							assignInRow = 0;
							(yyvsp[0].node) = lvalue_expr(tmp_rec);
						}
						
				}
#line 1961 "parser.c"
    break;

  case 42:
#line 261 "parser.y"
                                        {afterAssign = 1; }
#line 1967 "parser.c"
    break;

  case 43:
#line 261 "parser.y"
                                                                 { afterAssign = 0; 
													if((yyvsp[-4].node) != NULL && (yyvsp[-4].node)->type == tableitem_e){
														emit(tablesetelem, (yyvsp[0].node), (yyvsp[-4].node), (yyvsp[-4].node)->index, currQuad, yylineno);
														(yyval.node) = emit_iftableitem((yyvsp[-4].node));
														(yyval.node)->type = assignexpr_e;
													}else{
														emit(assign, (yyvsp[-4].node), (yyvsp[0].node), (expr*)0, currQuad, yylineno); 
														(yyval.node) = newexpr(assignexpr_e); 
														(yyval.node)->sym = returnTempName((yyvsp[0].node),(expr*)0); 
														emit(assign, (yyval.node), (yyvsp[-4].node), (expr*)0, currQuad, yylineno); 
													}
												}
#line 1984 "parser.c"
    break;

  case 44:
#line 275 "parser.y"
                       { 
					if(assignInRow){
						if(scope == 0){
							tmp_rec = insert(scope, yylineno, GLOBAL, yylval.stringValue);
							extraSets(tmp_rec);
						}else{
							tmp_rec = insert(scope, yylineno, LOCALVAR, yylval.stringValue);
							extraSets(tmp_rec);
						}
						assignInRow = 0;
						(yyvsp[0].node) = lvalue_expr(tmp_rec);
						
					}
					
					if(islibfunc){
						if(global_LIB_use){
							yyerror("Invalid insertion,1 trying to shadow LIBFUNC, before"); 
							global_LIB_use = 0;
						}
						islibfunc = 0;
					}else if(not_accessible && afterAssign && !call_depth){
						yyerror("Invalid insertion, before");
						not_accessible = 0;
						afterAssign = 0;
					}
					(yyval.node) = emit_iftableitem((yyvsp[0].node));
			}
#line 2016 "parser.c"
    break;

  case 45:
#line 302 "parser.y"
                              {global_LIB_use = 0; (yyval.node) = (yyvsp[0].node);}
#line 2022 "parser.c"
    break;

  case 46:
#line 303 "parser.y"
                                   {(yyval.node) = (yyvsp[0].node);}
#line 2028 "parser.c"
    break;

  case 47:
#line 304 "parser.y"
                                                                   { (yyval.node) = (yyvsp[-1].node); }
#line 2034 "parser.c"
    break;

  case 48:
#line 305 "parser.y"
                              {
				if(islibfunc && !call_depth && !inReturn){ 
						yyerror("Invalid insertion,3 trying to shadow LIBFUNC, before"); 
						islibfunc = 0;
				}
				(yyval.node) = (yyvsp[0].node);
			}
#line 2046 "parser.c"
    break;

  case 49:
#line 314 "parser.y"
                     {	
					if((tmp_rec = lookupLIBFUNCTs(yylval.stringValue))!= NULL){
						if(scope){
							global_LIB_use = 1;
						}else{
							global_LIB_use = 0;
						}
						islibfunc = 1;
					}else if( (tmp_rec = lookup(yylval.stringValue, scope)) != NULL){
						not_accessible = 0;
						islibfunc = 0;
					}else if( (tmp_rec = lookupFormal(yylval.stringValue, scope)) != NULL){
						not_accessible = 0;
						islibfunc = 0;
					}else if( (tmp_rec = lookupAbove(yylval.stringValue, scope)) != NULL){
						if(infunc && tmp_rec->type != USERFUNC && tmp_rec->func_scope < infunc){ /*an vrw parapanw variable kai eimai mesa se funct ->error*/
							yyerror("variable is not accesible in function");
						}
						not_accessible = 1;
						islibfunc = 0;
					}else if( (tmp_rec = lookup(yylval.stringValue, 0)) != NULL){
						glo_bal = 1;
						not_accessible = 0;
						islibfunc = 0;
					}else if(afterAssign){
						assignInRow = 1;
						afterAssign = 0;
						islibfunc = 0;
					}else{
						islibfunc =0;
								if(scope == 0){
									tmp_rec = insert(scope, yylineno, GLOBAL, yylval.stringValue);
									extraSets(tmp_rec);
								}else{
									tmp_rec = insert(scope, yylineno, LOCALVAR, yylval.stringValue);
									extraSets(tmp_rec);
								}
						
					}
					/* i parakatw if einai gia increment decrement error checking for functions*/
					
					if(tmp_rec != NULL && (tmp_rec->type == USERFUNC || tmp_rec->type == LIBFUNC)){
						token_is_func = 1;
					}else{
						token_is_func = 0;
					}
					if(tmp_rec == NULL){
						(yyval.node) = NULL;
					}else{
						(yyval.node) = lvalue_expr(tmp_rec);
					}
					
				}
#line 2104 "parser.c"
    break;

  case 50:
#line 367 "parser.y"
                                    {
							if(scope && ((tmp_rec = lookupLIBFUNCTs(yylval.stringValue)) !=NULL)){
								yyerror("Invalid insertion,4 trying to shadow LIBFUNC");
							}else if((tmp_rec = lookup(yylval.stringValue, scope)) != NULL){
								
							}else{
								if(scope == 0){
									tmp_rec = insert(scope, yylineno, GLOBAL, yylval.stringValue);
									extraSets(tmp_rec);
								}else{
									tmp_rec = insert(scope, yylineno, LOCALVAR, yylval.stringValue);
									extraSets(tmp_rec);
								}
							}
							if(tmp_rec == NULL){
								(yyval.node) = NULL;
							}else{
								(yyval.node) = lvalue_expr(tmp_rec);
							}
						}
#line 2129 "parser.c"
    break;

  case 51:
#line 387 "parser.y"
                                            {
						if((tmp_rec = lookup(yylval.stringValue, 0)) == NULL){
							yyerror("undefined global variable");
						}else{
							(yyval.node) = lvalue_expr(tmp_rec);
						}
				}
#line 2141 "parser.c"
    break;

  case 52:
#line 394 "parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 2147 "parser.c"
    break;

  case 53:
#line 397 "parser.y"
                                 { if((yyvsp[-2].node) != NULL){ (yyval.node) = member_item((yyvsp[-2].node), (yyvsp[0].stringValue)); } }
#line 2153 "parser.c"
    break;

  case 54:
#line 398 "parser.y"
                                                                              { (yyvsp[-3].node) = emit_iftableitem((yyvsp[-3].node)); (yyval.node) = newexpr(tableitem_e); (yyval.node)->sym = (yyvsp[-3].node)->sym; (yyval.node)->index = (yyvsp[-1].node); }
#line 2159 "parser.c"
    break;

  case 55:
#line 399 "parser.y"
                                        {islibfunc = 0; (yyval.node) = NULL;}
#line 2165 "parser.c"
    break;

  case 56:
#line 400 "parser.y"
                                                                            {(yyval.node) = NULL;}
#line 2171 "parser.c"
    break;

  case 57:
#line 404 "parser.y"
                                                                          {(yyval.node) = make_call((yyvsp[-3].node), (yyvsp[-1].node), yylineno);}
#line 2177 "parser.c"
    break;

  case 58:
#line 405 "parser.y"
                                           {
									if((yyvsp[0].node)->boolConst == '1'){
										expr * self = (yyvsp[-1].node);
										
										(yyvsp[-1].node) = emit_iftableitem(member_item(self, (yyvsp[0].node)->charConst));
										
										self->next = (yyvsp[0].node)->next; /*add self front*/
										(yyvsp[0].node) = self;
									}
									(yyval.node) = make_call((yyvsp[-1].node), (yyvsp[0].node), yylineno);
								}
#line 2193 "parser.c"
    break;

  case 59:
#line 416 "parser.y"
                                                                                                            {
																			expr* func = newexpr(programfunc_e);
																			func->sym = (yyvsp[-4].node)->sym;
																			(yyval.node) = make_call(func, (yyvsp[-1].node), yylineno);
																		}
#line 2203 "parser.c"
    break;

  case 60:
#line 423 "parser.y"
                        {(yyval.node) = (yyvsp[0].node);}
#line 2209 "parser.c"
    break;

  case 61:
#line 424 "parser.y"
                                   {(yyval.node) = (yyvsp[0].node);}
#line 2215 "parser.c"
    break;

  case 62:
#line 427 "parser.y"
                                {call_depth++; }
#line 2221 "parser.c"
    break;

  case 63:
#line 427 "parser.y"
                                                                         {	call_depth--;
																		(yyval.node) = newexpr(nil_e);
																		(yyval.node)->next = (yyvsp[-1].node);
																		(yyval.node)->charConst = NULL;
																		(yyval.node)->boolConst = '0';
																	}
#line 2232 "parser.c"
    break;

  case 64:
#line 435 "parser.y"
                                                 {call_depth++; methodcall_flag = 1;}
#line 2238 "parser.c"
    break;

  case 65:
#line 435 "parser.y"
                                                                                                             {
																		call_depth--;
																		(yyval.node) = newexpr(tableitem_e);
																		(yyval.node)->next = (yyvsp[-1].node);
																		(yyval.node)->charConst = (yyvsp[-4].stringValue);
																		(yyval.node)->boolConst = '1';
																	}
#line 2250 "parser.c"
    break;

  case 66:
#line 444 "parser.y"
                                      {(yyval.node) = (yyvsp[-1].node); (yyval.node)->next=(yyvsp[0].node);}
#line 2256 "parser.c"
    break;

  case 67:
#line 445 "parser.y"
                         {(yyval.node) = NULL;}
#line 2262 "parser.c"
    break;

  case 68:
#line 448 "parser.y"
                                               { (yyval.node)=(yyvsp[-1].node); (yyval.node)->next=(yyvsp[0].node);}
#line 2268 "parser.c"
    break;

  case 69:
#line 449 "parser.y"
                                         {(yyval.node)=NULL;}
#line 2274 "parser.c"
    break;

  case 70:
#line 452 "parser.y"
                                                              {
													int i = 0;
													expr* t = newexpr(newtable_e);
													t->sym = newtemp();
													emit(tablecreate, t, (expr*) 0, (expr*) 0, currQuad, yylineno);
													while((yyvsp[-1].node) != NULL){
														emit(tablesetelem, (yyvsp[-1].node), t, newexpr_constnum(i++), currQuad, yylineno);
														(yyvsp[-1].node) = (yyvsp[-1].node)->next;
													}
													(yyval.node) = t;
												}
#line 2290 "parser.c"
    break;

  case 71:
#line 463 "parser.y"
                                                                          {
													expr* t = newexpr(newtable_e);
													t->sym = newtemp();
													emit(tablecreate, t, (expr*) 0, (expr*) 0, currQuad, yylineno);
													while((yyvsp[-1].node)!=NULL){
														emit(tablesetelem, (yyvsp[-1].node), t, (yyvsp[-1].node)->index, currQuad, yylineno);
														(yyvsp[-1].node) = (yyvsp[-1].node)->next;
													}
													(yyval.node) = t;		
												}
#line 2305 "parser.c"
    break;

  case 72:
#line 475 "parser.y"
                                             {(yyval.node) = (yyvsp[-1].node); (yyval.node)->next = (yyvsp[0].node);}
#line 2311 "parser.c"
    break;

  case 73:
#line 478 "parser.y"
                                                           {(yyval.node) = (yyvsp[-1].node); (yyval.node)->next = (yyvsp[0].node);}
#line 2317 "parser.c"
    break;

  case 74:
#line 479 "parser.y"
                                          {(yyval.node) = NULL;}
#line 2323 "parser.c"
    break;

  case 75:
#line 482 "parser.y"
                                         {afterAssign = 0;}
#line 2329 "parser.c"
    break;

  case 76:
#line 482 "parser.y"
                                                                                     {(yyval.node) = (yyvsp[-1].node); (yyval.node)->index = (yyvsp[-4].node); afterAssign = 1;}
#line 2335 "parser.c"
    break;

  case 77:
#line 485 "parser.y"
                                  {scope++;}
#line 2341 "parser.c"
    break;

  case 78:
#line 485 "parser.y"
                                                                           {hide_scope(scope); scope--;}
#line 2347 "parser.c"
    break;

  case 80:
#line 489 "parser.y"
                        {infunc++;}
#line 2353 "parser.c"
    break;

  case 81:
#line 489 "parser.y"
                                         { 
							if(lookupLIBFUNCTs(yylval.stringValue)){
								yyerror("Invalid insertion, trying to shadow LIBFUNC");
							}else if(lookup(yylval.stringValue, scope) != NULL){
								yyerror("Invalid function name, defined");
							}else if(lookupFormal(yylval.stringValue, scope) != NULL){
								yyerror("Invalid function name, defined as formal argument");
							}else{
								(yyval.node) = lvalue_expr(insert(scope, yylineno, USERFUNC, yylval.stringValue));
								(yyval.node)->sym->iaddress = nextquadlabel();
								//function_jumplabel = currQuad; label of jump to patch
								push(funcjumpstack,currQuad);
								emit(jump,newexpr_constnum(0),(expr *) 0,(expr *) 0,currQuad,yylineno); 
								emit(funcstart, (yyval.node), (expr *) 0, (expr *) 0, currQuad, yylineno);
								push(functionLocalsStack, functionLocalOffset);
								tmp_expr = (yyval.node);
							}
							returnlist_head = newstmt(-1);
							pushstacklist(returnstacklist,returnlist_head);
							resetformalargsoffset();
						}
#line 2379 "parser.c"
    break;

  case 82:
#line 509 "parser.y"
                                                                  {scope++; enterscopespace();}
#line 2385 "parser.c"
    break;

  case 83:
#line 509 "parser.y"
                                                                                                                        {printf("Scopespace: %d\n\n\n",scopeSpaceCounter);scope--; enterscopespace(); resetfunctionlocalsoffset(); push(loopcounterstack, loopcounter); loopcounter = 0;}
#line 2391 "parser.c"
    break;

  case 84:
#line 510 "parser.y"
                                                      {
								infunc--; exitscopecounter(); exitscopecounter();
								(yyval.node) = tmp_expr;
								(yyval.node)->sym->totallocals = functionLocalOffset;
								functionLocalOffset = pop(functionLocalsStack);

								/* backpatch return list */
								patchBreakContinue(returnstacklist,nextquadlabel());
								emit(funcend, (yyval.node), (expr *) 0, (expr *) 0, currQuad, yylineno);
								patchlabel(pop(funcjumpstack),currQuad);
								
								loopcounter = pop(loopcounterstack);
								popstacklist(returnstacklist);
						}
#line 2410 "parser.c"
    break;

  case 85:
#line 524 "parser.y"
                                 {	
						infunc++;
						buffer = malloc(sizeof(char*));
						sprintf(buffer, "$%d", dollar_counter);
						buffer = strndup(buffer, sizeof(char*));
						(yyval.node) = lvalue_expr(insert(scope, yylineno, USERFUNC, buffer));
						//function_jumplabel = currQuad;  label of jump to patch 
						push(funcjumpstack,currQuad);
						emit(jump,newexpr_constnum(0),(expr *) 0,(expr *) 0,currQuad,yylineno); 
						emit(funcstart, (yyval.node), (expr *) 0, (expr *) 0, currQuad, yylineno);
						push(functionLocalsStack, functionLocalOffset);
						tmp_expr = (yyval.node);
						dollar_counter++;
						returnlist_head = newstmt(-1);
						pushstacklist(returnstacklist,returnlist_head);
						resetformalargsoffset();
					}
#line 2432 "parser.c"
    break;

  case 86:
#line 540 "parser.y"
                                                         {scope++; enterscopespace();}
#line 2438 "parser.c"
    break;

  case 87:
#line 540 "parser.y"
                                                                                                               {scope--; enterscopespace();}
#line 2444 "parser.c"
    break;

  case 88:
#line 540 "parser.y"
                                                                                                                                                   {
																			infunc--;
																			exitscopecounter(); exitscopecounter();
																			(yyval.node) = tmp_expr; 
																			(yyval.node)->sym->totallocals = functionLocalOffset;
																			functionLocalOffset = pop(functionLocalsStack);

																			/* backpatch return list */
																			patchBreakContinue(returnstacklist,nextquadlabel());
																			emit(funcend, (yyval.node), (expr *) 0, (expr *) 0, currQuad, yylineno);
																			patchlabel(pop(funcjumpstack),currQuad);

																			popstacklist(returnstacklist);
																		}
#line 2463 "parser.c"
    break;

  case 89:
#line 556 "parser.y"
                        { (yyval.node) = newexpr_constnum(yylval.intValue); }
#line 2469 "parser.c"
    break;

  case 90:
#line 557 "parser.y"
                               { (yyval.node) = newexpr_constnum(yylval.doubleValue); }
#line 2475 "parser.c"
    break;

  case 91:
#line 558 "parser.y"
                                      { (yyval.node) = newexpr_conststring(yylval.stringValue); }
#line 2481 "parser.c"
    break;

  case 92:
#line 559 "parser.y"
                              {afterAssign = 0; (yyval.node) = newexpr(nil_e);}
#line 2487 "parser.c"
    break;

  case 93:
#line 560 "parser.y"
                               {afterAssign = 0; (yyval.node) = newexpr_constbool('1');}
#line 2493 "parser.c"
    break;

  case 94:
#line 561 "parser.y"
                                {afterAssign = 0; (yyval.node) = newexpr_constbool('0');}
#line 2499 "parser.c"
    break;

  case 95:
#line 564 "parser.y"
                     {	formalArgOffset++;
				if(lookupLIBFUNCTs(yylval.stringValue)){
					yyerror("Invalid insertion, trying to shadow LIBFUNC");
				}else if(lookupFormal(yylval.stringValue, scope) != NULL){
					yyerror("duplicate formal names");
				}else{
					tmp_rec = insert(scope, yylineno, FORMAL, yylval.stringValue);
					extraSets(tmp_rec);
				}
			}
#line 2514 "parser.c"
    break;

  case 98:
#line 577 "parser.y"
                        {	formalArgOffset++;
				if(lookupLIBFUNCTs(yylval.stringValue)){
					yyerror("Invalid insertion, trying to shadow LIBFUNC");
				}else if(lookupFormal(yylval.stringValue, scope) != NULL){
					yyerror("duplicate formal names");
				}else{
					tmp_rec = insert(scope, yylineno, FORMAL, yylval.stringValue);
					extraSets(tmp_rec);
				}
			}
#line 2529 "parser.c"
    break;

  case 101:
#line 590 "parser.y"
                                                    { emit(if_eq, newexpr_constnum(nextquadlabel()+2), (yyvsp[-1].node), newexpr_constbool('1'), currQuad, yylineno); 
									(yyval.node) = newexpr(var_e); (yyval.node)->numConst = nextquadlabel(); 
									emit(jump, newexpr_constnum(0), (expr *)0, (expr *)0, currQuad, yylineno);
									first_cmd_stmt = 1;
									}
#line 2539 "parser.c"
    break;

  case 102:
#line 595 "parser.y"
                { (yyval.node) = newexpr(var_e); (yyval.node)->numConst = nextquadlabel(); emit(jump, newexpr_constnum(0), (expr *)0, (expr *)0, currQuad, yylineno); }
#line 2545 "parser.c"
    break;

  case 103:
#line 597 "parser.y"
                              {patchlabel((int)((yyvsp[-1].node)->numConst), nextquadlabel());}
#line 2551 "parser.c"
    break;

  case 104:
#line 598 "parser.y"
                                                       {patchlabel((int)((yyvsp[-3].node)->numConst), (int)((yyvsp[-1].node)->numConst) + 1); patchlabel((int)((yyvsp[-1].node)->numConst), nextquadlabel()); }
#line 2557 "parser.c"
    break;

  case 105:
#line 601 "parser.y"
                 {(yyval.node) = newexpr_constnum(nextquadlabel());}
#line 2563 "parser.c"
    break;

  case 106:
#line 604 "parser.y"
                                {/*call_depth++;*/}
#line 2569 "parser.c"
    break;

  case 107:
#line 604 "parser.y"
                                                                          {/*call_depth--;*/ ++loopcounter; 
										breaklist_head = newstmt(-1); contlist_head = newstmt(-1);
										pushstacklist(breakstacklist, breaklist_head); pushstacklist(contstacklist, contlist_head); 
										emit(if_eq, newexpr_constnum(nextquadlabel()+2), (yyvsp[-1].node), newexpr_constbool('1'), currQuad, yylineno); 
										(yyval.intValue) = nextquadlabel();   emit(jump, newexpr_constnum(0), (expr *)0, (expr *)0, currQuad, yylineno);
										first_cmd_stmt = 1;
										}
#line 2581 "parser.c"
    break;

  case 108:
#line 613 "parser.y"
                                         { --loopcounter;	
				emit(jump, (yyvsp[-2].node), (expr *)0, (expr *)0, currQuad, yylineno);   
				patchlabel((yyvsp[-1].intValue), nextquadlabel());   

				patchBreakContinue(breakstacklist, nextquadlabel());
				popstacklist(breakstacklist);
				patchBreakContinue(contstacklist, (int)((yyvsp[-2].node)->numConst));
				popstacklist(contstacklist);
			}
#line 2595 "parser.c"
    break;

  case 109:
#line 624 "parser.y"
                        { (yyval.intValue) = nextquadlabel();  emit(jump, newexpr_constnum(0), (expr *)0, (expr *)0, currQuad, yylineno);  }
#line 2601 "parser.c"
    break;

  case 110:
#line 626 "parser.y"
                        {  (yyval.intValue) = nextquadlabel(); }
#line 2607 "parser.c"
    break;

  case 111:
#line 628 "parser.y"
                                                                  {	
				(yyval.forpref) = malloc(sizeof(struct forVar));
				(yyval.forpref)->test = (yyvsp[-2].intValue); (yyval.forpref)->enter = nextquadlabel(); 
				emit(if_eq, newexpr_constnum(1), (yyvsp[-1].node), newexpr_constbool('1'), currQuad, yylineno);
				first_cmd_stmt = 1;
			}
#line 2618 "parser.c"
    break;

  case 112:
#line 636 "parser.y"
                                                   { prev = infunc; infunc = 0; ++loopcounter;
					breaklist_head = newstmt(-1); contlist_head = newstmt(-1);
					pushstacklist(breakstacklist, breaklist_head); pushstacklist(contstacklist, contlist_head);
					
					first_cmd_stmt = 1;
			}
#line 2629 "parser.c"
    break;

  case 113:
#line 641 "parser.y"
                                   {
				--loopcounter; infunc = prev;
				patchlabel((yyvsp[-7].forpref)->enter, (yyvsp[-2].intValue)+1);
				patchlabel((yyvsp[-6].intValue), nextquadlabel());
				patchlabel((yyvsp[-2].intValue), (yyvsp[-7].forpref)->test);
				patchlabel((yyvsp[0].intValue), (yyvsp[-6].intValue)+1);

				patchBreakContinue(breakstacklist, nextquadlabel());
				popstacklist(breakstacklist);
				patchBreakContinue(contstacklist, (yyvsp[-6].intValue)+1);
				popstacklist(contstacklist);
			}
#line 2646 "parser.c"
    break;

  case 114:
#line 655 "parser.y"
                  {afterAssign = 0; inReturn = 1; if(!infunc){yyerror("Use of 'return' while not in a function");}}
#line 2652 "parser.c"
    break;

  case 115:
#line 655 "parser.y"
                                                                                                                                    { 
																														inReturn = 1; 
																														emit(ret, (yyvsp[-1].node), (expr *) 0, (expr *) 0,currQuad, yylineno);
																													 }
#line 2661 "parser.c"
    break;

  case 116:
#line 659 "parser.y"
                                {if(!infunc){yyerror("Use of 'return' while not in a function");}}
#line 2667 "parser.c"
    break;

  case 117:
#line 659 "parser.y"
                                                                                                             {
																						emit(ret, (expr *) 0, (expr *) 0, (expr *) 0,currQuad, yylineno);
																					}
#line 2675 "parser.c"
    break;


#line 2679 "parser.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 664 "parser.y"


int yyerror (char* yaccProvideMessage){
	printIntermediate = 1;
	fprintf(stderr, "ERROR, %s token: %s, at line %d\n",yaccProvideMessage, yytext, yylineno);
}

int main(int argc, char** argv) {
	FILE *f = fopen("IntermediateCodefile.txt", "w");
	FILE *bf = fopen("TargetCodeFile.abc", "wb");
	tmp_expr = newexpr(var_e);
	functionLocalsStack = malloc(sizeof(struct stack));
	functionLocalsStack->top = -1;
	loopcounterstack = malloc(sizeof(struct stack));
	loopcounterstack->top = -1;
	funcjumpstack = malloc(sizeof(struct stack));
	funcjumpstack->top = -1;
	breakstacklist = malloc(sizeof(struct stacklist));
	breakstacklist->top = -1;
	contstacklist = malloc(sizeof(struct stacklist));
	contstacklist->top = -1;
	returnstacklist = malloc(sizeof(struct stacklist));
	returnstacklist->top = -1;
	
	

	myHashTable = newHashTable();
	insert_LIBFUNCTs();
	if(argc > 1){
		if(!(yyin = fopen(argv[1], "r"))){
			fprintf(stderr, "Cannot read file: %s\n", argv[1]);
			return 1;
		}
	}else{
		yyin = stdin;
	}
	
	yyparse();

	print_results();
	if (f == NULL || bf == NULL){
    	printf("\nERROR, cannot open output file!\n");
	}

	if(!printIntermediate){
		printQuads(f);
		generate_all();
		printInstructions();
		//printBinaryInstructions(bf);
	}else{
		printf("\nERROR at compile time!\n");
	}

	if(!avmbinaryfile(bf)){
		printf("ERROR, binary file parsing failed!\n");
	}

	fclose(f);
	fclose(bf);



	return 0;
}
