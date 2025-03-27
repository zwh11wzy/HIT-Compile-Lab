/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "./syntax.y"


# include <stdio.h>
# include <string.h>
# include <stdlib.h>

extern int yylineno; 
extern char* yytext; 
extern int yylex(); 

int e = 0;
int last_elineo = 0;

void yyerror(const char* s);

struct SYT { // Multi-way tree
    struct SYT* child;
    struct SYT* bro;
    int linenum;
    char attr[10]; // Used for matching when creating nodes
    int leaf; // Used to determine if it is a leaf node
    union { // Used for output during traversal
        int type_int;
        float type_float;
        char type_char[32];
    };
};

#define YYSTYPE struct SYT* 


struct SYT* head=NULL;  
struct SYT* Nodes(struct SYT* cd, char* s, int line);
void OutputSYT(struct SYT* nd, int depth); // Depth-first search, pre-order traversal
void prerror(char errorType, char* msg); 




#line 111 "./syntax.tab.c"

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

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PLUS = 3,                       /* PLUS  */
  YYSYMBOL_MINUS = 4,                      /* MINUS  */
  YYSYMBOL_AND = 5,                        /* AND  */
  YYSYMBOL_OR = 6,                         /* OR  */
  YYSYMBOL_MUL = 7,                        /* MUL  */
  YYSYMBOL_DIV = 8,                        /* DIV  */
  YYSYMBOL_ASSIGNOP = 9,                   /* ASSIGNOP  */
  YYSYMBOL_NOT = 10,                       /* NOT  */
  YYSYMBOL_SEMI = 11,                      /* SEMI  */
  YYSYMBOL_COMMA = 12,                     /* COMMA  */
  YYSYMBOL_DOT = 13,                       /* DOT  */
  YYSYMBOL_LP = 14,                        /* LP  */
  YYSYMBOL_RP = 15,                        /* RP  */
  YYSYMBOL_LB = 16,                        /* LB  */
  YYSYMBOL_RB = 17,                        /* RB  */
  YYSYMBOL_LC = 18,                        /* LC  */
  YYSYMBOL_RC = 19,                        /* RC  */
  YYSYMBOL_STRUCT = 20,                    /* STRUCT  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_IF = 22,                        /* IF  */
  YYSYMBOL_ELSE = 23,                      /* ELSE  */
  YYSYMBOL_WHILE = 24,                     /* WHILE  */
  YYSYMBOL_TYPE = 25,                      /* TYPE  */
  YYSYMBOL_INT = 26,                       /* INT  */
  YYSYMBOL_INT8 = 27,                      /* INT8  */
  YYSYMBOL_INT16 = 28,                     /* INT16  */
  YYSYMBOL_FLOAT = 29,                     /* FLOAT  */
  YYSYMBOL_ID = 30,                        /* ID  */
  YYSYMBOL_RELOP = 31,                     /* RELOP  */
  YYSYMBOL_LOWER_THAN_NOT = 32,            /* LOWER_THAN_NOT  */
  YYSYMBOL_LOWER_THAN_ELSE = 33,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_Program = 35,                   /* Program  */
  YYSYMBOL_ExtDefList = 36,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 37,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 38,                /* ExtDecList  */
  YYSYMBOL_Specifier = 39,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 40,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 41,                    /* OptTag  */
  YYSYMBOL_Tag = 42,                       /* Tag  */
  YYSYMBOL_VarDec = 43,                    /* VarDec  */
  YYSYMBOL_FunDec = 44,                    /* FunDec  */
  YYSYMBOL_VarList = 45,                   /* VarList  */
  YYSYMBOL_ParamDec = 46,                  /* ParamDec  */
  YYSYMBOL_CompSt = 47,                    /* CompSt  */
  YYSYMBOL_StmtList = 48,                  /* StmtList  */
  YYSYMBOL_Stmt = 49,                      /* Stmt  */
  YYSYMBOL_DefList = 50,                   /* DefList  */
  YYSYMBOL_Def = 51,                       /* Def  */
  YYSYMBOL_DecList = 52,                   /* DecList  */
  YYSYMBOL_Dec = 53,                       /* Dec  */
  YYSYMBOL_Exp = 54,                       /* Exp  */
  YYSYMBOL_Args = 55                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   287

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,    95,   103,   106,   112,   116,   119,   123,   130,
     132,   136,   146,   148,   152,   158,   163,   166,   170,   176,
     178,   183,   192,   197,   201,   208,   212,   216,   224,   232,
     235,   240,   243,   245,   249,   255,   263,   269,   278,   281,
     286,   290,   297,   304,   306,   312,   314,   324,   328,   332,
     336,   340,   344,   348,   352,   356,   360,   363,   366,   371,
     375,   380,   384,   386,   388,   390,   395,   400,   405,   410,
     417,   421
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PLUS", "MINUS", "AND",
  "OR", "MUL", "DIV", "ASSIGNOP", "NOT", "SEMI", "COMMA", "DOT", "LP",
  "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE", "WHILE",
  "TYPE", "INT", "INT8", "INT16", "FLOAT", "ID", "RELOP", "LOWER_THAN_NOT",
  "LOWER_THAN_ELSE", "$accept", "Program", "ExtDefList", "ExtDef",
  "ExtDecList", "Specifier", "StructSpecifier", "OptTag", "Tag", "VarDec",
  "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt", "DefList",
  "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-113)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-18)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,   -22,  -113,    21,  -113,    18,    12,  -113,    10,    11,
    -113,  -113,  -113,  -113,  -113,    23,    34,    99,    47,    18,
      74,  -113,    33,    33,    15,    18,  -113,    14,    60,    18,
      68,  -113,    33,    70,    80,  -113,  -113,  -113,    71,    84,
     237,    92,     2,     9,   102,  -113,  -113,  -113,    91,  -113,
      18,  -113,  -113,   214,   214,    83,   214,   107,   108,  -113,
    -113,   112,  -113,   109,   237,    45,  -113,   214,  -113,  -113,
      33,  -113,     6,     6,   122,   127,   143,   214,   214,    76,
    -113,  -113,  -113,   214,   214,   214,   214,   214,   214,    94,
    -113,    97,   115,   214,   204,  -113,  -113,  -113,  -113,   157,
     174,   123,  -113,   188,   124,   271,   271,   229,   218,    46,
      46,  -113,    46,  -113,   136,    65,   261,   237,   237,  -113,
     214,  -113,  -113,   138,  -113,   134,  -113,  -113,  -113,   237,
    -113
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    16,    12,     0,     2,     3,     0,    13,    18,     0,
      15,     1,     4,     8,     6,    19,     0,     0,     0,    38,
       0,     5,     0,     0,     0,    38,     7,     0,     0,    38,
       0,    23,     0,     0,    26,    19,    11,    10,     0,     0,
      29,     0,    45,     0,    43,    14,    39,    24,    27,    22,
       0,    21,    20,     0,     0,     0,     0,     0,     0,    63,
      64,    62,    32,     0,    29,     0,    41,     0,    42,    40,
       0,    25,    56,    57,     0,     0,     0,     0,     0,     0,
      28,    30,    37,     0,     0,     0,     0,     0,     0,     0,
      31,     0,     0,     0,    46,    44,    67,    55,    33,     0,
       0,     0,    59,    71,     0,    51,    52,    48,    49,    53,
      54,    68,    47,    61,     0,     0,    50,     0,     0,    66,
       0,    58,    69,     0,    60,    34,    36,    70,    65,     0,
      35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -113,  -113,   162,  -113,    95,     7,  -113,  -113,  -113,   -23,
    -113,   118,  -113,   151,   111,  -112,    35,  -113,   101,  -113,
     -53,    56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    16,    27,     7,     9,    10,    17,
      18,    33,    34,    62,    63,    64,    28,    29,    43,    44,
      65,   104
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    73,    75,    76,    42,   125,   126,     6,     8,    48,
      68,    67,     6,    13,    94,    41,    38,   130,    24,    91,
      69,    11,    92,    14,    99,   100,   103,    32,   -17,    19,
     105,   106,   107,   108,   109,   110,   112,    20,     1,   115,
     116,    39,    15,     2,    35,    21,    82,    42,    83,    84,
      85,    86,    87,    88,    89,    89,    90,    32,    91,    91,
      40,    92,    92,    35,    46,    25,   123,   103,    83,    84,
      85,    86,    87,    88,    89,    30,    93,   101,    91,    45,
      53,    92,   124,    47,    74,    49,    54,    53,    51,    31,
      55,   102,    50,    54,     1,   111,    93,    55,    53,     2,
      22,    52,    59,    66,    54,    60,    61,    24,    55,    59,
      -9,    23,    60,    61,    70,    24,   114,    36,    37,    53,
      59,    77,    78,    60,    61,    54,    79,   113,    80,    55,
      83,    84,    85,    86,    87,    88,    89,    96,   119,   121,
      91,    59,    97,    92,    60,    61,    83,    84,    85,    86,
      87,    88,    89,   122,    98,   128,    91,   129,    93,    92,
      83,    84,    85,    86,    87,    88,    89,    12,    71,    26,
      91,    95,   117,    92,    93,    81,   127,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,    91,    93,   118,
      92,    83,    84,    85,    86,    87,    88,    89,     0,     0,
     120,    91,     0,     0,    92,    93,     0,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,    91,    53,    93,
      92,    83,    84,    85,    54,    87,    88,    89,    55,     0,
       0,    91,    83,    84,    92,    93,    87,    88,    89,     0,
      59,    53,    91,    60,    61,    92,     0,    54,     0,    93,
       0,    55,     0,     0,     0,    25,     0,     0,    56,    57,
      93,    58,     0,    59,    83,    84,    60,    61,    87,    88,
      89,     0,     0,     0,    91,     0,     0,    92,    87,    88,
      89,     0,     0,     0,    91,     0,     0,    92
};

static const yytype_int16 yycheck[] =
{
      53,    54,    55,    56,    27,   117,   118,     0,    30,    32,
       1,     9,     5,     1,    67,     1,     1,   129,    16,    13,
      11,     0,    16,    11,    77,    78,    79,    20,    18,    18,
      83,    84,    85,    86,    87,    88,    89,    14,    20,    92,
      93,    26,    30,    25,    30,    11,     1,    70,     3,     4,
       5,     6,     7,     8,     9,     9,    11,    50,    13,    13,
      25,    16,    16,    30,    29,    18,     1,   120,     3,     4,
       5,     6,     7,     8,     9,     1,    31,     1,    13,    19,
       4,    16,    17,    15,     1,    15,    10,     4,    17,    15,
      14,    15,    12,    10,    20,     1,    31,    14,     4,    25,
       1,    17,    26,    11,    10,    29,    30,    16,    14,    26,
      11,    12,    29,    30,    12,    16,     1,    22,    23,     4,
      26,    14,    14,    29,    30,    10,    14,    30,    19,    14,
       3,     4,     5,     6,     7,     8,     9,    15,    15,    15,
      13,    26,    15,    16,    29,    30,     3,     4,     5,     6,
       7,     8,     9,    17,    11,    17,    13,    23,    31,    16,
       3,     4,     5,     6,     7,     8,     9,     5,    50,    18,
      13,    70,    15,    16,    31,    64,   120,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    13,    31,    15,
      16,     3,     4,     5,     6,     7,     8,     9,    -1,    -1,
      12,    13,    -1,    -1,    16,    31,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    13,     4,    31,
      16,     3,     4,     5,    10,     7,     8,     9,    14,    -1,
      -1,    13,     3,     4,    16,    31,     7,     8,     9,    -1,
      26,     4,    13,    29,    30,    16,    -1,    10,    -1,    31,
      -1,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,    22,
      31,    24,    -1,    26,     3,     4,    29,    30,     7,     8,
       9,    -1,    -1,    -1,    13,    -1,    -1,    16,     7,     8,
       9,    -1,    -1,    -1,    13,    -1,    -1,    16
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    25,    35,    36,    37,    39,    40,    30,    41,
      42,     0,    36,     1,    11,    30,    38,    43,    44,    18,
      14,    11,     1,    12,    16,    18,    47,    39,    50,    51,
       1,    15,    39,    45,    46,    30,    38,    38,     1,    26,
      50,     1,    43,    52,    53,    19,    50,    15,    43,    15,
      12,    17,    17,     4,    10,    14,    21,    22,    24,    26,
      29,    30,    47,    48,    49,    54,    11,     9,     1,    11,
      12,    45,    54,    54,     1,    54,    54,    14,    14,    14,
      19,    48,     1,     3,     4,     5,     6,     7,     8,     9,
      11,    13,    16,    31,    54,    52,    15,    15,    11,    54,
      54,     1,    15,    54,    55,    54,    54,    54,    54,    54,
      54,     1,    54,    30,     1,    54,    54,    15,    15,    15,
      12,    15,    17,     1,    17,    49,    49,    55,    17,    23,
      49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    37,    37,    38,
      38,    38,    39,    39,    40,    40,    41,    41,    42,    43,
      43,    43,    44,    44,    44,    45,    45,    46,    47,    48,
      48,    49,    49,    49,    49,    49,    49,    49,    50,    50,
      51,    51,    51,    52,    52,    53,    53,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     2,     1,
       3,     3,     1,     1,     5,     2,     0,     1,     1,     1,
       4,     4,     4,     3,     4,     3,     1,     2,     4,     0,
       2,     2,     1,     3,     5,     7,     5,     2,     0,     2,
       3,     3,     3,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     3,
       4,     3,     1,     1,     1,     5,     4,     3,     3,     4,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 95 "./syntax.y"
                   {
    if(yyvsp[0]->type_int==0){
        yyval=Nodes(yyvsp[0],"Program\0",yyvsp[0]->linenum);//$1->linenum not used
    }else{
        yyval=Nodes(yyvsp[0],"Program\0",(yylsp[0]).first_line);        
    }
}
#line 1390 "./syntax.tab.c"
    break;

  case 3: /* ExtDefList: %empty  */
#line 103 "./syntax.y"
            {
    yyval = Nodes(NULL,"ExtDefList\0",yylineno);//结束后返回行号
    yyval->type_int = 0;
}
#line 1399 "./syntax.tab.c"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 106 "./syntax.y"
                      {//递归
    yyval = Nodes(yyvsp[-1],"ExtDefList\0",(yylsp[-1]).first_line);
    yyval->type_int = 2;//多个儿子
    yyvsp[-1]->bro = yyvsp[0];
}
#line 1409 "./syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 112 "./syntax.y"
                                 {//多个全局变量定义
    yyval = Nodes(yyvsp[-2],"ExtDef\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];    
}
#line 1419 "./syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 116 "./syntax.y"
                  {//单个无定义的结构体
    yyval = Nodes(yyvsp[-1],"ExtDef\0",(yylsp[-1]).first_line);
    yyvsp[-1]->bro = yyvsp[0];
}
#line 1428 "./syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 119 "./syntax.y"
                           {//函数头体
    yyval = Nodes(yyvsp[-2],"ExtDef\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1438 "./syntax.tab.c"
    break;

  case 8: /* ExtDef: Specifier error  */
#line 123 "./syntax.y"
                   {
    e = 1;
    if(last_elineo != yylineno){//无一行出现多个error情况
        prerror('B',"Missing \";\"");
    }
}
#line 1449 "./syntax.tab.c"
    break;

  case 9: /* ExtDecList: VarDec  */
#line 130 "./syntax.y"
                  {//多个全局变量定义
    yyval = Nodes(yyvsp[0],"ExtDecList\0",(yylsp[0]).first_line);    
}
#line 1457 "./syntax.tab.c"
    break;

  case 10: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 132 "./syntax.y"
                           {
    yyval = Nodes(yyvsp[-2],"ExtDecList\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];         
}
#line 1467 "./syntax.tab.c"
    break;

  case 11: /* ExtDecList: VarDec error ExtDecList  */
#line 136 "./syntax.y"
                           {
    e = 1;
    if(last_elineo != yylineno){
        prerror('B',"text");
    }
}
#line 1478 "./syntax.tab.c"
    break;

  case 12: /* Specifier: TYPE  */
#line 146 "./syntax.y"
               {
    yyval = Nodes(yyvsp[0],"Specifier\0",(yylsp[0]).first_line);    
}
#line 1486 "./syntax.tab.c"
    break;

  case 13: /* Specifier: StructSpecifier  */
#line 148 "./syntax.y"
                   {
    yyval = Nodes(yyvsp[0],"Specifier\0",(yylsp[0]).first_line);     
}
#line 1494 "./syntax.tab.c"
    break;

  case 14: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 152 "./syntax.y"
                                            {
    yyval = Nodes(yyvsp[-4],"StructSpecifier\0",(yylsp[-4]).first_line);
    yyvsp[-4]->bro = yyvsp[-3];
    yyvsp[-3]->bro = yyvsp[-2];
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];          
}
#line 1506 "./syntax.tab.c"
    break;

  case 15: /* StructSpecifier: STRUCT Tag  */
#line 158 "./syntax.y"
              {
    yyval = Nodes(yyvsp[-1],"StructSpecifier\0",(yylsp[-1]).first_line);
    yyvsp[-1]->bro = yyvsp[0];    
}
#line 1515 "./syntax.tab.c"
    break;

  case 16: /* OptTag: %empty  */
#line 163 "./syntax.y"
        {
    yyval = Nodes(NULL,"OptTag\0",0);//yylineno?
    yyval->type_int = 0;        
}
#line 1524 "./syntax.tab.c"
    break;

  case 17: /* OptTag: ID  */
#line 166 "./syntax.y"
      {
    yyval = Nodes(yyvsp[0],"OptTag\0",(yylsp[0]).first_line);    
}
#line 1532 "./syntax.tab.c"
    break;

  case 18: /* Tag: ID  */
#line 170 "./syntax.y"
       {
    yyval = Nodes(yyvsp[0],"Tag\0",(yylsp[0]).first_line);    
}
#line 1540 "./syntax.tab.c"
    break;

  case 19: /* VarDec: ID  */
#line 176 "./syntax.y"
          {
    yyval = Nodes(yyvsp[0],"VarDec\0",(yylsp[0]).first_line);    
}
#line 1548 "./syntax.tab.c"
    break;

  case 20: /* VarDec: VarDec LB INT RB  */
#line 178 "./syntax.y"
                    {//数组数字
    yyval = Nodes(yyvsp[-3],"VarDec\0",(yylsp[-3]).first_line);
    yyvsp[-3]->bro = yyvsp[-2];
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];        
}
#line 1559 "./syntax.tab.c"
    break;

  case 21: /* VarDec: VarDec LB error RB  */
#line 183 "./syntax.y"
                      {
    char msg[32];
    e = 1;
    sprintf(msg, "Syntax error near \'%c\'", yytext[0]);
    if(last_elineo != yylineno){
        prerror('B', msg);
    }
}
#line 1572 "./syntax.tab.c"
    break;

  case 22: /* FunDec: ID LP VarList RP  */
#line 192 "./syntax.y"
                        {//形参列表
    yyval = Nodes(yyvsp[-3],"FunDec\0",(yylsp[-3]).first_line); 
    yyvsp[-3]->bro = yyvsp[-2];
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];
}
#line 1583 "./syntax.tab.c"
    break;

  case 23: /* FunDec: ID LP RP  */
#line 197 "./syntax.y"
            {
    yyval = Nodes(yyvsp[-2],"FunDec\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];        
}
#line 1593 "./syntax.tab.c"
    break;

  case 24: /* FunDec: ID LP error RP  */
#line 201 "./syntax.y"
                  {
    e = 1;
    if(last_elineo != yylineno){
        prerror('B',"Syntax error between ()");
    }
}
#line 1604 "./syntax.tab.c"
    break;

  case 25: /* VarList: ParamDec COMMA VarList  */
#line 208 "./syntax.y"
                               {//对形参变量定义
    yyval = Nodes(yyvsp[-2],"VarList\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];         
}
#line 1614 "./syntax.tab.c"
    break;

  case 26: /* VarList: ParamDec  */
#line 212 "./syntax.y"
            {
    yyval = Nodes(yyvsp[0],"VarList\0",(yylsp[0]).first_line);    
}
#line 1622 "./syntax.tab.c"
    break;

  case 27: /* ParamDec: Specifier VarDec  */
#line 216 "./syntax.y"
                          {//描述符与变量定义
    yyval = Nodes(yyvsp[-1],"ParamDec\0",(yylsp[-1]).first_line);
    yyvsp[-1]->bro = yyvsp[0];       
}
#line 1631 "./syntax.tab.c"
    break;

  case 28: /* CompSt: LC DefList StmtList RC  */
#line 224 "./syntax.y"
                              {//语句块，一系列变量定义，语句
//CompSt必须在每个语句块开头才能定义
    yyval = Nodes(yyvsp[-3],"CompSt\0",(yylsp[-3]).first_line);
    yyvsp[-3]->bro = yyvsp[-2];
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];        
}
#line 1643 "./syntax.tab.c"
    break;

  case 29: /* StmtList: %empty  */
#line 232 "./syntax.y"
          {
    yyval = Nodes(NULL,"StmtList\0",0);
    yyval->type_int = 0;        
}
#line 1652 "./syntax.tab.c"
    break;

  case 30: /* StmtList: Stmt StmtList  */
#line 235 "./syntax.y"
                 {
    yyval = Nodes(yyvsp[-1],"StmtList\0",(yylsp[-1]).first_line);    
    yyvsp[-1]->bro = yyvsp[0];  
}
#line 1661 "./syntax.tab.c"
    break;

  case 31: /* Stmt: Exp SEMI  */
#line 240 "./syntax.y"
              {//语句
    yyval = Nodes(yyvsp[-1],"Stmt\0",(yylsp[-1]).first_line);
    yyvsp[-1]->bro = yyvsp[0];    
}
#line 1670 "./syntax.tab.c"
    break;

  case 32: /* Stmt: CompSt  */
#line 243 "./syntax.y"
          {
    yyval = Nodes(yyvsp[0],"Stmt\0",(yylsp[0]).first_line);
}
#line 1678 "./syntax.tab.c"
    break;

  case 33: /* Stmt: RETURN Exp SEMI  */
#line 245 "./syntax.y"
                   {
    yyval = Nodes(yyvsp[-2],"Stmt\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];
}
#line 1688 "./syntax.tab.c"
    break;

  case 34: /* Stmt: IF LP Exp RP Stmt  */
#line 249 "./syntax.y"
                                           {//避免报移入归约冲突
    yyval = Nodes(yyvsp[-4],"Stmt\0",(yylsp[-4]).first_line);
    yyvsp[-4]->bro = yyvsp[-3];
    yyvsp[-3]->bro = yyvsp[-2];
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];    
}
#line 1700 "./syntax.tab.c"
    break;

  case 35: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 255 "./syntax.y"
                               {
    yyval = Nodes(yyvsp[-6],"Stmt\0",(yylsp[-6]).first_line);
    yyvsp[-6]->bro = yyvsp[-5];
    yyvsp[-5]->bro = yyvsp[-4];
    yyvsp[-4]->bro = yyvsp[-3];
    yyvsp[-3]->bro = yyvsp[-2];
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];  
}
#line 1714 "./syntax.tab.c"
    break;

  case 36: /* Stmt: WHILE LP Exp RP Stmt  */
#line 263 "./syntax.y"
                        {
    yyval = Nodes(yyvsp[-4],"Stmt\0",(yylsp[-4]).first_line);
    yyvsp[-4]->bro = yyvsp[-3];
    yyvsp[-3]->bro = yyvsp[-2];
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];
}
#line 1726 "./syntax.tab.c"
    break;

  case 37: /* Stmt: Exp error  */
#line 269 "./syntax.y"
             {
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Missing \";\"");
    }
}
#line 1737 "./syntax.tab.c"
    break;

  case 38: /* DefList: %empty  */
#line 278 "./syntax.y"
         {
    yyval = Nodes(NULL,"DefList\0",0);
    yyval->type_int = 0;    
}
#line 1746 "./syntax.tab.c"
    break;

  case 39: /* DefList: Def DefList  */
#line 281 "./syntax.y"
               {//一类变量定义
    yyval = Nodes(yyvsp[-1],"DefList\0",(yylsp[-1]).first_line);
    yyvsp[-1]->bro = yyvsp[0];    
}
#line 1755 "./syntax.tab.c"
    break;

  case 40: /* Def: Specifier DecList SEMI  */
#line 286 "./syntax.y"
                           {//e.g:int a,b,c;或int a, int b ,int c;
    yyval = Nodes(yyvsp[-2],"Def\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];
}
#line 1765 "./syntax.tab.c"
    break;

  case 41: /* Def: Specifier error SEMI  */
#line 290 "./syntax.y"
                        {
    char msg[32];
    e = 1;
    sprintf(msg, "Syntax error near \'%c\'", yytext[0]);
    if(last_elineo != yylineno){
        prerror('B', msg);
    }
}
#line 1778 "./syntax.tab.c"
    break;

  case 42: /* Def: Specifier DecList error  */
#line 297 "./syntax.y"
                           {
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Missing \";\"");
    }    
}
#line 1789 "./syntax.tab.c"
    break;

  case 43: /* DecList: Dec  */
#line 304 "./syntax.y"
            {
    yyval = Nodes(yyvsp[0],"DecList\0",(yylsp[0]).first_line);    
}
#line 1797 "./syntax.tab.c"
    break;

  case 44: /* DecList: Dec COMMA DecList  */
#line 306 "./syntax.y"
                     {
    yyval = Nodes(yyvsp[-2],"DecList\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];         
}
#line 1807 "./syntax.tab.c"
    break;

  case 45: /* Dec: VarDec  */
#line 312 "./syntax.y"
           {//单个变量定义，e.g:int a = 5;
    yyval = Nodes(yyvsp[0],"Dec\0",(yylsp[0]).first_line);        
}
#line 1815 "./syntax.tab.c"
    break;

  case 46: /* Dec: VarDec ASSIGNOP Exp  */
#line 314 "./syntax.y"
                       {
    yyval = Nodes(yyvsp[-2],"Dec\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];    
}
#line 1825 "./syntax.tab.c"
    break;

  case 47: /* Exp: Exp ASSIGNOP Exp  */
#line 324 "./syntax.y"
                     {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1835 "./syntax.tab.c"
    break;

  case 48: /* Exp: Exp AND Exp  */
#line 328 "./syntax.y"
               {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1845 "./syntax.tab.c"
    break;

  case 49: /* Exp: Exp OR Exp  */
#line 332 "./syntax.y"
              {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1855 "./syntax.tab.c"
    break;

  case 50: /* Exp: Exp RELOP Exp  */
#line 336 "./syntax.y"
                 {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1865 "./syntax.tab.c"
    break;

  case 51: /* Exp: Exp PLUS Exp  */
#line 340 "./syntax.y"
                {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1875 "./syntax.tab.c"
    break;

  case 52: /* Exp: Exp MINUS Exp  */
#line 344 "./syntax.y"
                 {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1885 "./syntax.tab.c"
    break;

  case 53: /* Exp: Exp MUL Exp  */
#line 348 "./syntax.y"
               {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1895 "./syntax.tab.c"
    break;

  case 54: /* Exp: Exp DIV Exp  */
#line 352 "./syntax.y"
               {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1905 "./syntax.tab.c"
    break;

  case 55: /* Exp: LP Exp RP  */
#line 356 "./syntax.y"
             {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1915 "./syntax.tab.c"
    break;

  case 56: /* Exp: MINUS Exp  */
#line 360 "./syntax.y"
                                  {
    yyval = Nodes(yyvsp[-1],"Exp\0",(yylsp[-1]).first_line);
    yyvsp[-1]->bro = yyvsp[0];        
}
#line 1924 "./syntax.tab.c"
    break;

  case 57: /* Exp: NOT Exp  */
#line 363 "./syntax.y"
           {
    yyval = Nodes(yyvsp[-1],"Exp\0",(yylsp[-1]).first_line);
    yyvsp[-1]->bro = yyvsp[0];         
}
#line 1933 "./syntax.tab.c"
    break;

  case 58: /* Exp: ID LP Args RP  */
#line 366 "./syntax.y"
                 {
    yyval = Nodes(yyvsp[-3],"Exp\0",(yylsp[-3]).first_line);
    yyvsp[-3]->bro = yyvsp[-2];    
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];         
}
#line 1944 "./syntax.tab.c"
    break;

  case 59: /* Exp: ID LP RP  */
#line 371 "./syntax.y"
            {
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1954 "./syntax.tab.c"
    break;

  case 60: /* Exp: Exp LB Exp RB  */
#line 375 "./syntax.y"
                 {// 数组访问
    yyval = Nodes(yyvsp[-3],"Exp\0",(yylsp[-3]).first_line);
    yyvsp[-3]->bro = yyvsp[-2];    
    yyvsp[-2]->bro = yyvsp[-1];
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1965 "./syntax.tab.c"
    break;

  case 61: /* Exp: Exp DOT ID  */
#line 380 "./syntax.y"
              {//结构体访问
    yyval = Nodes(yyvsp[-2],"Exp\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 1975 "./syntax.tab.c"
    break;

  case 62: /* Exp: ID  */
#line 384 "./syntax.y"
      {
    yyval = Nodes(yyvsp[0],"Exp\0",(yylsp[0]).first_line);     
}
#line 1983 "./syntax.tab.c"
    break;

  case 63: /* Exp: INT  */
#line 386 "./syntax.y"
       {
    yyval = Nodes(yyvsp[0],"Exp\0",(yylsp[0]).first_line);     
}
#line 1991 "./syntax.tab.c"
    break;

  case 64: /* Exp: FLOAT  */
#line 388 "./syntax.y"
         {
    yyval = Nodes(yyvsp[0],"Exp\0",(yylsp[0]).first_line);     
}
#line 1999 "./syntax.tab.c"
    break;

  case 65: /* Exp: Exp LB Exp error RB  */
#line 390 "./syntax.y"
                       {
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Missing \"]\"");
    }     
}
#line 2010 "./syntax.tab.c"
    break;

  case 66: /* Exp: ID LP error RP  */
#line 395 "./syntax.y"
                  {
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Syntax error in Exp");
    }
}
#line 2021 "./syntax.tab.c"
    break;

  case 67: /* Exp: LP error RP  */
#line 400 "./syntax.y"
               {
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Syntax error in Exp");
    }
}
#line 2032 "./syntax.tab.c"
    break;

  case 68: /* Exp: Exp ASSIGNOP error  */
#line 405 "./syntax.y"
                      {
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Syntax error in Exp");
    }
}
#line 2043 "./syntax.tab.c"
    break;

  case 69: /* Exp: Exp LB error RB  */
#line 410 "./syntax.y"
                   {
    e = 1;
    if(last_elineo != yylineno){
        prerror('B', "Syntax error between \"[]\"");
    }
}
#line 2054 "./syntax.tab.c"
    break;

  case 70: /* Args: Exp COMMA Args  */
#line 417 "./syntax.y"
                    {//实参列表
    yyval = Nodes(yyvsp[-2],"Args\0",(yylsp[-2]).first_line);
    yyvsp[-2]->bro = yyvsp[-1];    
    yyvsp[-1]->bro = yyvsp[0];     
}
#line 2064 "./syntax.tab.c"
    break;

  case 71: /* Args: Exp  */
#line 421 "./syntax.y"
       {
    yyval = Nodes(yyvsp[0],"Args\0",(yylsp[0]).first_line);    
}
#line 2072 "./syntax.tab.c"
    break;


#line 2076 "./syntax.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 426 "./syntax.y"


#include "lex.yy.c"

struct SYT* Nodes(struct SYT* cd, char* s, int line){
    struct SYT* n = (struct SYT*)malloc(sizeof(struct SYT));
    n->leaf = 1; // Syntax unit
    n->child = cd;
    n->linenum = line;
    n->bro = NULL;
    n->type_int = 1;
    strcpy(n->attr,s);
    head = n;
    return n;
}


void OutputNodes(struct SYT* nd){
    if(nd->leaf==0){ // If it is a terminal
        if(!strcmp(nd->attr,"ID\0")){
            printf("ID: %s\n",nd->type_char);
        }else if(!strcmp(nd->attr,"TYPE\0")){
            printf("TYPE: %s\n",nd->type_char);
        }else if(!strcmp(nd->attr,"INT\0")){
            printf("INT: %u\n",nd->type_int);
        }else if(!strcmp(nd->attr,"FLOAT\0")){
            printf("FLOAT: %f\n",nd->type_float);
        } else {
            printf("%s\n", nd->attr); // Output information for other types of terminals
        }
    }else if(nd->type_int){// If it is a non-terminal
        printf("%s (%d)\n", nd->attr, nd->linenum);
    }
}


void OutputSYT(struct SYT* nd, int depth){
    int i;
    if(nd->leaf==0||nd->type_int){
        for(i=0;i<depth;i++)
        {
            printf("  ");
        }
        OutputNodes(nd);
    }
    if(nd->child!=NULL){
        OutputSYT(nd->child,depth+1);
    }
    if(nd->bro!=NULL){
        OutputSYT(nd->bro,depth);
    }
    return;
}


void prerror(char errorType, char* msg) {
    fprintf(stderr, "Error type %c at Line %d: %s.\n", errorType, yylineno, msg);
    last_elineo = yylineno; 
}

void yyerror(const char* s) {}
