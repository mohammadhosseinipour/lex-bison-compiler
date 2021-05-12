
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "hisbison.y"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdarg.h>
#include <ctype.h>
void yyerror(const char*);
int yylex();
int scope[100];
int scope_ctr;
int scope_ind;
int flag1 =1;

extern int yylineno;

int t=0;
int lab=0;
char stack[100][100];
int top=0;
int num_iter[10];
int iter_init[10];
int iter_top=0;
int number_of_iterations=0;
int return_flag=0;
typedef struct AST{
	char lexeme[100];
	int NumChild;
	struct AST **child;
}AST_node;
char typ[10]="nothing";
extern FILE *yyin;

/*
struct attributes{
	char* code; 
	struct attributes* true;
	struct attributes* false;
	struct attributes* next;
	char addr[20];
}; */

struct entry
{
	char name[30];
	char type[10];
	int width;
	int line_num;
	int scope;
};




struct entry sym_tab[100];
int ctr = 0;

void update_sym_tab(char* typ, char* nam, int line, int scope)
{
	strcpy(sym_tab[ctr].name,nam);

	if(strcmp(typ,"int")==0)
	{
		strcpy(sym_tab[ctr].type,typ);
		sym_tab[ctr].width=4;
	}

	else if(strcmp(typ,"float")==0)
	{
		strcpy(sym_tab[ctr].type,typ);
		sym_tab[ctr].width=8;
	}
	else if(strcmp(typ,"char")==0)
	{
		strcpy(sym_tab[ctr].type,typ);
		sym_tab[ctr].width=1;	
	}
	sym_tab[ctr].line_num=line;
	sym_tab[ctr].scope=scope;
	ctr++;
	//printf("%d\n",ctr);


}


void print_sym_tab()
{
	int i;
	printf("1   \n\nSymbol Table: \n");
	for(i=0;i<ctr;i++)
	{
		printf("2   <%s,%s,%d,%d, %d> \n",sym_tab[i].name, sym_tab[i].type, sym_tab[i].width,sym_tab[i].line_num,sym_tab[i].scope);
	}
}

int look_up_sym_tab(char* nam)
{
	int i; 
	for(i=0;i<ctr;i++)
	{
		if(strcmp(sym_tab[i].name,nam)==0)
		{
			int scop=sym_tab[i].scope;
			int flag=0;
			int zero_ctr=0;
			int j=scope_ind-1;
			while(j>=0)
			{
				if(scope[j]==0)
					zero_ctr++;
				else if(scope[j]!=0 && zero_ctr>0)
					zero_ctr--;
				else if(scope[j]!=0 && zero_ctr==0)
				{
					if(scope[j]==scop)
					{
						flag=1;
						return 1;
					}
				}
				j--;
			}
		}
	}
	return 0;
}
int is_int (char *nam, int scop)
{
	int i;
	for(i=0;i<ctr;i++)
	{
		if(strcmp(sym_tab[i].name,nam)==0 && scop==sym_tab[i].scope)
		{
			if(strcmp(sym_tab[i].type,"int")==0)
				return 1;
			else
				return 0;
		}
	}
	return 1;
}

int look_up_sym_tab_dec(char* nam, int scop)
{
	int i; 
	for(i=0;i<ctr;i++)
	{
		if(strcmp(sym_tab[i].name,nam)==0 && sym_tab[i].scope==scop)
		{
			return 1;
		}
	}
	return 0;
}

int get_scope()
{
	//printf("ind :%d\n",scope_ind);
	int i=scope_ind-1;
	int zero_ctr=0;
	int flag=1;
	while(flag && i>0)
	{
		if(scope[i]!=0)
			zero_ctr--;
		else
			zero_ctr++;
		if(zero_ctr==0)
		{
			i--;
			flag=0;
			break;
		}
		i--;
	}
	return scope[i];
}





void push(char* string)
{

	strcpy(stack[++top],string); 
	
	//printf("top: %s %d\n",stack[top],top);
}

void pop()
{
	//printf("top: %d",top);
	top--;
}

/*
struct entry sym_tab[100];
int ctr = 0;
void update_sym_tab(char* typ, char* nam)
{
	strcpy(sym_tab[ctr].name,nam);
	if(strcmp(typ,"int")==0)
	{
		strcpy(sym_tab[ctr].type,typ);
		sym_tab[ctr].width=4;
	}
	else if(strcmp(typ,"float")==0)
	{
		strcpy(sym_tab[ctr].type,typ);
		sym_tab[ctr].width=8;
	}
	else if(strcmp(typ,"char")==0)
	{
		strcpy(sym_tab[ctr].type,typ);
		sym_tab[ctr].width=1;	
	}
	ctr++;
	//printf("%d\n",ctr);
}
*/

int remove_spaces(char* text, char* blank)
{
	int p;
	FILE *fp = fopen("temp.txt", "w");
    if (fp != NULL)
    {
        fputs(text, fp);
        fclose(fp);
    }
    //printf("Here\n");
    fp=fopen("temp.txt","r");
    FILE* fp2=fopen("newfile.txt","w");  //all the content gets copied to this filename and blank lines are also removed from your file

            while((p=getc(fp))!=EOF)
            {
            	//printf("Here2\n");
                fputc(p,fp2);
                if (p==10)
                    {
                    	fputc(p,fp2);
                              while((p=getc(fp))==10)
                              {
                              	printf("3   %c\n",p);
                              }
                    fputc(p,fp2);
                    }
            }
printf("4   Here 3\n");
fclose(fp);
printf("5   Here 4\n");
fclose(fp2);
printf("6   Here 5\n");
fp=fopen("newfile.txt", "r");
printf("7   Here 6\n");


//struct stat buf;
//stat("speed",&buf);
        //char *str = (char*)malloc(buf.st_size);
        while(!feof(fp))
        {
                char *s=(char*)malloc(1024);
                fgets(s,1024,fp);
                s[strlen(s)-1]='\0';
                strcat(blank,s);
        }
        printf("8   File content:%s\n",blank);


return 1;
}

int remove_blank(char *text, char* blank)
{
	int c=0; int d=0;
       while (text[c] != '\0') {
      if (text[c] == ' ') {
         int temp = c + 1;
         if (text[temp] != '\0') {
            while (text[temp] == ' ' && text[temp] != '\0') {
               if (text[temp] == ' ') {
                  c++;
               }  
               temp++;
            }
         }
      }
      blank[d] = text[c];
      c++;
      d++;
   }
 
   blank[d] = '\0';
 
   //printf("Text after removing blanks\n%s\n", blank);
 
   return 0;
}

void remove_rest(char *text, char* blank)
{
	char *tok=strtok(text,"\n");
	while(tok!=NULL)
	{
		if(strlen(tok)>1)
		{
			/*
			if(strcmp(tok[0],"L")==0)
			{
				strcat(blank,tok);
				strcat(blank," ");
				tok=strtok(NULL,"\n");
				strcat(blank,tok);
				strcat(blank,"\n");
			}
			*/
			if(strcmp(tok," goto ")==0)
			{
				strcat(blank,"goto");
				strcat(blank," ");
				tok=strtok(NULL,"\n");
				strcat(blank,tok);
				strcat(blank,"\n");
			}
			//char tmp[100];
			//strcpy(tmp,tok);
			/*
			if(tmp[0]=='L')
			{
				strcat(blank,tok);
				strcat(blank," ");
				tok=strtok(NULL,"\n");
				char temp1[10];
				strcpy(temp1,tok);
				if(temp1[0]!='L')
				{
					strcat(blank,tok);
					strcat(blank,"\n");
				}
				else
				{
					strcat(blank,"\n");
					strcat(blank,tok);
					strcat(blank,"\n");
				}
			}*/
			else			
			{
				strcat(blank,tok);
				strcat(blank,"\n");
			}
		}
		tok=strtok(NULL,"\n");
	}
	/*
	char *temp=malloc(strlen(blank));
	strcpy(temp,blank);
	printf("9   -----------------------------------\n");
	printf("11  %s\n",temp);
	printf("10  -----------------------------------\n");
	strcpy(blank,"");
	char *tok1=strtok(temp,"\n");
	while(tok1!=NULL)
	{
		char tmp[100];
		strcpy(tmp,tok1);
		if(tmp[0]=='L')
		{
				strcat(blank,tok1);
				//strcat(blank," ");
				tok1=strtok(NULL,"\n");
				//strcat(blank,tok1);
				if(strcmp(tok1,": ")==0)
				{
					strcat(blank,tok1);
					//tok1=strtok(NULL,"\n");
					//strcat(blank," ");
					//strcat(blank,tok1);
				}
				strcat(blank,"\n");	
		}
		else			
		{
			//strcat(blank,tok1);
			//strcat(blank,"\n");	
			strcat(blank,tok1);
			strcat(blank,"\n");
		}
		tok1=strtok(NULL,"\n");
	}
	*/
}

int is_digit(char* tmp)
{
  int j=0;
  int isDigit = 1;
  while(j<strlen(tmp))
  {
  	if(isdigit(tmp[j])|| tmp[j]=='.')
  	{
  		j++;
  		continue;
  	}
  	else
  	{
  		isDigit = 0;
  		break;
  	}
  	j++;
  }
  return isDigit;
}

void print_IC(char* str)
{
	// Returns first token 
    char *token = strtok(str, "\n");
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        printf("12      %s\n", token);
        token = strtok(NULL, "\n");
    }
 
}


/*
void print_sym_tab()
{
	int i;
	printf("13  \n\nSymbol Table: \n");
	for(i=0;i<ctr;i++)
	{
		printf("14  <%s,%s,%d> \n",sym_tab[i].name, sym_tab[i].type, sym_tab[i].width);
	}
}
int look_up_sym_tab(char* nam)
{
	int i; 
	for(i=0;i<ctr;i++)
	{
		if(strcmp(sym_tab[i].name,nam)==0)
		{
			return 1;
		}
	}
	return 0;
}
*/


void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
 
char* new_temp()
{
	t++;
	char* num = (char*)malloc(sizeof(int));
	tostring(num,t);
	char* temp = (char*)malloc(sizeof(int));
	strcat(temp,"t");
	strcat(temp,num);
	return temp;
}


char* new_label()
{
	lab++;
	char* num = (char*)malloc(sizeof(int));
	tostring(num,lab);
	char* temp = (char*)malloc(sizeof(int));
	strcat(temp,"L");
	strcat(temp,num);
	return temp;
}

char* code_concatenate(int arg_count,...)
{
	//printf("\nConcatenating\n");
	int i;
	va_list ap;
	va_start(ap, arg_count);
	char* temp = (char*)malloc(1000);
	for (i = 1; i <= arg_count; i++)
    {   
     	char* a = va_arg(ap, char*);
     	temp = (char*)realloc(temp,(strlen(temp)+strlen(a)+10));
     	strcat(temp,"\n");
     	strcat(temp,a);
     }
     return temp;     
}


char* gen_addr(char* string)
{
	char* addr = (char*)malloc(sizeof(string));
	strcpy(addr, string);
	return addr;
}

char* code_gen(int arg_count,...)
{
	int i;
	va_list ap;
	va_start(ap, arg_count);
	char* temp = (char*)malloc(1000);
	for (i = 1; i <= arg_count; i++)
    {   
     	char* a = va_arg(ap, char*);
     	temp = (char*)realloc(temp,(strlen(temp)+strlen(a)+10));
     	strcat(temp,a);
    }
    strcat(temp,"   ");
     return temp;  
}


char* code_gen(int arg_count,...);
char* gen_addr(char* string);
char* new_temp();
char* code_concatenate(int arg_count,...);
char* new_label();
int is_int(char *,int);
void remove_rest(char *, char *);
char break_lab[20];
char switch_id[10];


/* Line 189 of yacc.c  */
#line 626 "myapp.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
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


/* Line 214 of yacc.c  */
#line 727 "myapp.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 739 "myapp.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   149

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNRULES -- Number of states.  */
#define YYNSTATES  136

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     9,    10,    15,    19,    22,    25,    26,
      27,    32,    33,    34,    39,    42,    45,    46,    47,    56,
      58,    61,    64,    69,    73,    75,    84,    87,    91,    93,
      95,    97,   101,   105,   107,   109,   111,   113,   115,   117,
     119,   121,   125,   128,   130,   132,   136,   138,   144,   149,
     155,   160,   164,   168,   170,   174,   178,   180,   182,   184,
     188,   190,   192,   196,   200,   206,   208,   210,   212,   214,
     217,   220,   223,   226,   229
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    22,    47,    17,    18,    54,    -1,    -1,
       8,    55,    56,     9,    -1,    79,     5,    56,    -1,    77,
      56,    -1,    54,    56,    -1,    -1,    -1,    57,    66,    58,
      56,    -1,    -1,    -1,    59,    67,    60,    56,    -1,    68,
      56,    -1,    74,    56,    -1,    -1,    -1,    46,    17,    25,
      18,     8,    62,    63,     9,    -1,    64,    -1,    64,    65,
      -1,    64,    63,    -1,    50,    26,    51,    56,    -1,    49,
      51,    56,    -1,    61,    -1,    14,    17,    74,    69,     5,
      79,    18,    54,    -1,    11,     5,    -1,    48,    79,     5,
      -1,    70,    -1,    71,    -1,    79,    -1,    79,    73,    79,
      -1,    79,    72,    79,    -1,    31,    -1,    32,    -1,    35,
      -1,    36,    -1,    37,    -1,    38,    -1,    33,    -1,    34,
      -1,    75,    76,     5,    -1,    75,    78,    -1,    22,    -1,
      23,    -1,    76,     6,    25,    -1,    25,    -1,    25,    39,
      79,     6,    77,    -1,    25,    39,    79,     5,    -1,    25,
      39,    79,     6,    78,    -1,    25,    39,    79,     5,    -1,
      79,    27,    80,    -1,    79,    28,    80,    -1,    80,    -1,
      80,    29,    81,    -1,    80,    30,    81,    -1,    81,    -1,
      25,    -1,    26,    -1,    17,    79,    18,    -1,    84,    -1,
      82,    -1,    25,    83,    25,    -1,    25,    83,    26,    -1,
      25,    83,    17,    79,    18,    -1,    40,    -1,    41,    -1,
      42,    -1,    43,    -1,    44,    25,    -1,    25,    44,    -1,
      45,    25,    -1,    25,    45,    -1,    28,    25,    -1,    28,
      26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   581,   581,   610,   610,   613,   614,   620,   621,   621,
     621,   624,   624,   624,   627,   628,   629,   634,   634,   644,
     645,   646,   649,   661,   668,   671,   710,   711,   714,   715,
     716,   720,   752,   755,   756,   759,   760,   761,   762,   763,
     764,   767,   768,   773,   774,   777,   782,   791,   827,   875,
     911,   956,   981,  1002,  1005,  1028,  1049,  1052,  1053,  1054,
    1055,  1056,  1059,  1066,  1072,  1080,  1081,  1082,  1083,  1086,
    1092,  1098,  1104,  1110,  1116
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DOT", "SINGLE", "SC", "COMMA", "LETTER",
  "OPBRACE", "CLBRACE", "CONTINUE", "BREAK", "IF", "ELSE", "FOR", "WHILE",
  "POW", "OPEN", "CLOSE", "COMMENT", "SQ_OPEN", "SQ_CLOSE", "INT", "FLOAT",
  "CHAR", "ID", "NUM", "PLUS", "MINUS", "MULT", "DIV", "AND", "OR", "LESS",
  "GREAT", "LESEQ", "GRTEQ", "NOTEQ", "EQEQ", "ASSIGN", "SPLUS", "SMINUS",
  "SMULT", "SDIV", "INC", "DEC", "SWITCH", "MAIN", "RETURN", "DEFAULT",
  "CASE", "COLON", "$accept", "start", "comp_stat", "$@1", "stat", "$@2",
  "$@3", "$@4", "$@5", "ST", "$@6", "B", "C", "D", "select_stat",
  "iter_stat", "jump_stat", "cond", "relexp", "logexp", "logOp", "relOp",
  "decl", "Type", "Varlist", "assign_expr", "assign_expr1", "E", "T", "F",
  "s_operation", "s_op", "unary_expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    55,    54,    56,    56,    56,    57,    58,
      56,    59,    60,    56,    56,    56,    56,    62,    61,    63,
      63,    63,    64,    65,    66,    67,    68,    68,    69,    69,
      69,    70,    71,    72,    72,    73,    73,    73,    73,    73,
      73,    74,    74,    75,    75,    76,    76,    77,    77,    78,
      78,    79,    79,    79,    80,    80,    80,    81,    81,    81,
      81,    81,    82,    82,    82,    83,    83,    83,    83,    84,
      84,    84,    84,    84,    84
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     4,     3,     2,     2,     0,     0,
       4,     0,     0,     4,     2,     2,     0,     0,     8,     1,
       2,     2,     4,     3,     1,     8,     2,     3,     1,     1,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     1,     3,     1,     5,     4,     5,
       4,     3,     3,     1,     3,     3,     1,     1,     1,     3,
       1,     1,     3,     3,     5,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     3,     2,     8,
       0,     0,    43,    44,    57,    58,     0,     0,     0,     0,
      16,     0,     0,     0,    16,    16,     0,    16,     0,    53,
      56,    61,    60,    26,    57,     0,     0,    65,    66,    67,
      68,    70,    72,     0,    73,    74,    69,    71,     0,     7,
       4,     0,    24,     9,     0,    12,    14,    15,    46,     0,
      42,     6,    16,     0,     0,     0,     0,    59,     0,     0,
      62,    63,    27,     0,    16,     0,    16,     0,    41,     0,
       5,    51,    52,    54,    55,    48,     0,     0,     0,    10,
       0,    13,     0,    45,     0,    47,    64,     0,     0,    28,
      29,    30,    50,     0,    17,     0,    33,    34,    39,    40,
      35,    36,    37,    38,     0,     0,     0,    49,     0,     0,
      32,    31,     0,     0,    19,     0,     0,    18,     0,    21,
      20,    25,    16,     8,    22,    23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    20,     9,    21,    22,    74,    23,    76,    52,
     118,   123,   124,   130,    53,    55,    24,    98,    99,   100,
     114,   115,    25,    26,    59,    27,    60,    28,    29,    30,
      31,    43,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -35
static const yytype_int16 yypact[] =
{
     -13,   -34,    21,    29,   -35,    49,    74,   -35,   -35,     3,
      82,   -10,   -35,   -35,    81,   -35,   -22,    65,    67,   -10,
      63,    86,    64,    98,    63,    63,    90,    63,    14,     9,
     -35,   -35,   -35,   -35,    87,    22,   -10,   -35,   -35,   -35,
     -35,   -35,   -35,     7,   -35,   -35,   -35,   -35,    25,   -35,
     -35,    99,   -35,   -35,   100,   -35,   -35,   -35,    79,    56,
     -35,   -35,    63,   -10,   -10,   -10,   -10,   -35,    17,   -10,
     -35,   -35,   -35,   108,    63,    47,    63,   -10,   -35,   109,
     -35,     9,     9,   -35,   -35,   -35,   110,    36,   118,   -35,
     -10,   -35,    31,   -35,   101,   -35,   -35,   129,   133,   -35,
     -35,    66,   -35,   114,   -35,   -10,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -10,   -10,    79,   -35,    91,    38,
      45,    45,   116,   134,    26,    74,    93,   -35,    94,   -35,
     -35,   -35,    63,     3,   -35,   -35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,    -6,   -35,   -19,   -35,   -35,   -35,   -35,   -35,
     -35,    23,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,    71,   -35,   -35,    62,    46,    -9,    15,    18,
     -35,   -35,   -35
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -17
static const yytype_int16 yytable[] =
{
       8,    49,    35,    44,    45,    56,    57,    11,    61,     1,
      48,     7,   -16,     3,    10,    34,    15,   -11,    16,    62,
      11,     4,    85,    86,    69,    12,    13,    68,    14,    15,
      72,    16,    70,    71,    17,    18,   102,   103,    65,    66,
      67,    63,    64,    80,    63,    64,     5,    17,    18,    63,
      64,    19,    63,    64,    96,    89,   125,    91,    63,    64,
      87,    78,    79,    63,    64,    63,    64,     6,    92,    12,
      13,     7,    63,    64,    10,   128,   122,   -11,    81,    82,
      11,   101,     7,    83,    84,    12,    13,    33,    14,    15,
      46,    16,    47,    63,    64,    50,   119,   106,   107,   108,
     109,   110,   111,   112,   113,   120,   121,    17,    18,    -8,
      51,    19,    54,   134,   135,    58,    73,    75,    77,   131,
      36,    37,    38,    39,    40,    41,    42,    37,    38,    39,
      40,    41,    42,    88,    93,    94,    97,   104,   105,   116,
      36,   122,   126,   127,   132,   133,    90,   129,    95,   117
};

static const yytype_uint8 yycheck[] =
{
       6,    20,    11,    25,    26,    24,    25,    17,    27,    22,
      19,     8,     9,    47,    11,    25,    26,    14,    28,     5,
      17,     0,     5,     6,    17,    22,    23,    36,    25,    26,
       5,    28,    25,    26,    44,    45,     5,     6,    29,    30,
      18,    27,    28,    62,    27,    28,    17,    44,    45,    27,
      28,    48,    27,    28,    18,    74,    18,    76,    27,    28,
      69,     5,     6,    27,    28,    27,    28,    18,    77,    22,
      23,     8,    27,    28,    11,    49,    50,    14,    63,    64,
      17,    90,     8,    65,    66,    22,    23,     5,    25,    26,
      25,    28,    25,    27,    28,     9,   105,    31,    32,    33,
      34,    35,    36,    37,    38,   114,   115,    44,    45,    46,
      46,    48,    14,   132,   133,    25,    17,    17,    39,   125,
      39,    40,    41,    42,    43,    44,    45,    40,    41,    42,
      43,    44,    45,    25,    25,    25,    18,     8,     5,    25,
      39,    50,    26,     9,    51,    51,    75,   124,    86,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    22,    53,    47,     0,    17,    18,     8,    54,    55,
      11,    17,    22,    23,    25,    26,    28,    44,    45,    48,
      54,    56,    57,    59,    68,    74,    75,    77,    79,    80,
      81,    82,    84,     5,    25,    79,    39,    40,    41,    42,
      43,    44,    45,    83,    25,    26,    25,    25,    79,    56,
       9,    46,    61,    66,    14,    67,    56,    56,    25,    76,
      78,    56,     5,    27,    28,    29,    30,    18,    79,    17,
      25,    26,     5,    17,    58,    17,    60,    39,     5,     6,
      56,    80,    80,    81,    81,     5,     6,    79,    25,    56,
      74,    56,    79,    25,    25,    77,    18,    18,    69,    70,
      71,    79,     5,     6,     8,     5,    31,    32,    33,    34,
      35,    36,    37,    38,    72,    73,    25,    78,    62,    79,
      79,    79,    50,    63,    64,    18,    26,     9,    49,    63,
      65,    54,    51,    51,    56,    56
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 581 "hisbison.y"
    {  //printf("Here\n");
										(yyval.A)=(yyvsp[(5) - (5)].A); print_sym_tab(); 
										if(return_flag)
										{	(yyval.A).code = code_concatenate(2,(yyval.A).code,"end: ");
											(yyval.A).optimized_code = code_concatenate(2,(yyval.A).optimized_code,"end: ");
										} 
										char* code1 = (char*)malloc(strlen((yyval.A).code)); 
										char* code2 = (char*)malloc(strlen((yyval.A).optimized_code));

										int a = remove_blank((yyval.A).code,code1); 
										a = remove_blank((yyval.A).optimized_code,code2);
										printf("15  \n IC: \n%s",code1);
										printf("16  \n OC: \n%s",code2);
										char* code3 = (char*)malloc(strlen(code1)); 
										char* code4 = (char*)malloc(strlen(code2));
										remove_rest(code1,code3);
										remove_rest(code2,code4);
										//printf("\n IC: \n%s",$$.code);  
										//printf("\n IC: \n%s",code1); 
										//printf("\n OC: \n%s",code2);
										//printf("\n\nOC: %s\n\n",$$.optimized_code);
										printf("17  \n\nIC\n\n");
										print_IC(code3);
										printf("18  \n\nOC\n\n");
										print_IC(code4);
										YYACCEPT;
										;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 610 "hisbison.y"
    {scope_ctr++;scope[scope_ind++]=scope_ctr;;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 610 "hisbison.y"
    {(yyval.A)=(yyvsp[(3) - (4)].A); scope[scope_ind++]=0; (yyval.A).optimized_code = (yyvsp[(3) - (4)].A).optimized_code;;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 613 "hisbison.y"
    {(yyval.A).code = code_concatenate(2,(yyvsp[(1) - (3)].A).code,(yyvsp[(3) - (3)].A).code); (yyval.A).optimized_code = code_concatenate(2,(yyvsp[(1) - (3)].A).optimized_code, (yyvsp[(3) - (3)].A).optimized_code);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 614 "hisbison.y"
    {(yyval.A).code = code_concatenate(2,(yyvsp[(1) - (2)].A).code,(yyvsp[(2) - (2)].A).code); 
    							//printf("$2 optimized code: %s\n\n", $2.optimized_code);
    							(yyval.A).optimized_code = code_concatenate(2,(yyvsp[(1) - (2)].A).optimized_code, (yyvsp[(2) - (2)].A).optimized_code); 
    							(yyval.A).is_dig=(yyvsp[(1) - (2)].A).is_dig;
    							//printf("ABC\n");
    						  ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 620 "hisbison.y"
    {(yyval.A).code = code_concatenate(2,(yyvsp[(1) - (2)].A).code,(yyvsp[(2) - (2)].A).code); (yyval.A).optimized_code = code_concatenate(2,(yyvsp[(1) - (2)].A).optimized_code, (yyvsp[(2) - (2)].A).optimized_code);;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 621 "hisbison.y"
    {char * lab = new_label(); push(lab);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 621 "hisbison.y"
    {pop();;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 621 "hisbison.y"
    {(yyval.A).code = code_concatenate(2,(yyvsp[(2) - (4)].A).code,(yyvsp[(4) - (4)].A).code); 
    																			(yyval.A).optimized_code = code_concatenate(2,(yyvsp[(2) - (4)].A).optimized_code, (yyvsp[(4) - (4)].A).optimized_code);
    																			;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 624 "hisbison.y"
    {char * lab = new_label(); push(lab);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 624 "hisbison.y"
    {pop();;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 624 "hisbison.y"
    {(yyval.A).code = code_concatenate(2,(yyvsp[(2) - (4)].A).code,(yyvsp[(4) - (4)].A).code); 
    																			(yyval.A).optimized_code = code_concatenate(2,(yyvsp[(2) - (4)].A).optimized_code, (yyvsp[(4) - (4)].A).optimized_code);
    																			;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 627 "hisbison.y"
    {(yyval.A).code = code_concatenate(2,(yyvsp[(1) - (2)].A).code,(yyvsp[(2) - (2)].A).code); (yyval.A).optimized_code = code_concatenate(2,(yyvsp[(1) - (2)].A).optimized_code, (yyvsp[(2) - (2)].A).optimized_code);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 628 "hisbison.y"
    {(yyval.A).code = code_concatenate(2,(yyvsp[(1) - (2)].A).code,(yyvsp[(2) - (2)].A).code); (yyval.A).optimized_code = code_concatenate(2,(yyvsp[(1) - (2)].A).optimized_code, (yyvsp[(2) - (2)].A).optimized_code);;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 629 "hisbison.y"
    {(yyval.A).code = strdup(" "); (yyval.A).optimized_code = (yyval.A).code;;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 634 "hisbison.y"
    {scope_ctr++;scope[scope_ind++]=scope_ctr;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 635 "hisbison.y"
    {
												scope[scope_ind++]=0;
												if(!look_up_sym_tab((yyvsp[(3) - (8)].text))){printf("19     Undeclared variable %s\n", (yyvsp[(3) - (8)].text)); YYERROR;}
												(yyval.A).code = code_concatenate(2, (yyvsp[(7) - (8)].A).code, code_gen(2,stack[top],": "));
												(yyval.A).optimized_code = code_concatenate(2, (yyvsp[(7) - (8)].A).optimized_code, code_gen(2,stack[top],": "));
											;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 644 "hisbison.y"
    {(yyval.A)=(yyvsp[(1) - (1)].A);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 645 "hisbison.y"
    {(yyval.A).code = code_concatenate(2,(yyvsp[(1) - (2)].A).code, (yyvsp[(2) - (2)].A).code); (yyval.A).optimized_code = code_concatenate(2,(yyvsp[(1) - (2)].A).optimized_code, (yyvsp[(2) - (2)].A).optimized_code);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 646 "hisbison.y"
    {(yyval.A).code = code_concatenate(2,(yyvsp[(1) - (2)].A).code, (yyvsp[(2) - (2)].A).code); (yyval.A).optimized_code = code_concatenate(2,(yyvsp[(1) - (2)].A).optimized_code, (yyvsp[(2) - (2)].A).optimized_code);;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 649 "hisbison.y"
    {char* lab1 = new_label();
								//printf("in switch\n"); 
								char* lab2 = new_label(); 
								//printf("in switch\n"); 
								(yyval.A).code = code_concatenate(6,code_gen(4,"if ",(yyvsp[(-2) - (4)].text)," == ",(yyvsp[(2) - (4)].text)," goto ", lab1), " goto ",lab2, code_gen(2,lab1,": "),(yyvsp[(4) - (4)].A).code, code_gen(2,lab2,": "));
								//printf("in switch\n"); 
								(yyval.A).optimized_code =code_concatenate(6,code_gen(6,"if ",(yyvsp[(-2) - (4)].text)," == ",(yyvsp[(2) - (4)].text)," goto ", lab1), " goto ",lab2, code_gen(2, lab1,": "),(yyvsp[(4) - (4)].A).optimized_code, code_gen(2,lab2,": "));
								//printf("%s\n",$4.optimized_code);
								;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 661 "hisbison.y"
    {char* lab = new_label(); (yyval.A).code = code_concatenate(1,(yyvsp[(3) - (3)].A).code); (yyval.A).optimized_code = (yyvsp[(3) - (3)].A).optimized_code;;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 668 "hisbison.y"
    {(yyval.A)=(yyvsp[(1) - (1)].A);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 671 "hisbison.y"
    {char* begin = new_label(); 
															(yyvsp[(3) - (8)].A).next = begin; 
															(yyvsp[(4) - (8)].A).true1 = new_label(); 
															
															(yyvsp[(8) - (8)].A).next = stack[top];
															//push($8.next);
															(yyvsp[(4) - (8)].A).false1 = (yyvsp[(8) - (8)].A).next;   
															//printf("here %s",break_lab);
															strcpy(break_lab,(yyvsp[(8) - (8)].A).next);
															//printf("here2 %s",break_lab);
															//$8.next = new_label();
															(yyvsp[(6) - (8)].A).next = begin;

															(yyval.A).code = code_concatenate(8,(yyvsp[(3) - (8)].A).code, code_gen(2,begin,": "),code_gen(4,"if ", (yyvsp[(4) - (8)].A).code, "goto ", (yyvsp[(4) - (8)].A).true1), 
															code_gen(2,"goto ", (yyvsp[(4) - (8)].A).false1), code_gen(2,(yyvsp[(4) - (8)].A).true1,": "),(yyvsp[(8) - (8)].A).code, code_gen(2,"goto ",begin),code_gen(2,(yyvsp[(8) - (8)].A).next,": \n"));

															if(num_iter)
															{
																//printf("HERE\n");
																(yyval.A).optimized_code = strdup(" ");
																(yyval.A).optimized_code = code_concatenate(2,(yyval.A).optimized_code,(yyvsp[(3) - (8)].A).optimized_code);
																
																
																
																//printf("number of iterations %d\n",number_of_iterations);
																int i;
																for(i=0;i<number_of_iterations;i++)
																{
																	(yyval.A).optimized_code = code_concatenate(2,(yyval.A).optimized_code,(yyvsp[(8) - (8)].A).optimized_code);
																}
																//printf("FOR OC%s\n",$$.optimized_code);
															}
															else
															{
																(yyval.A).optimized_code = (yyval.A).code;
															}
															;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 710 "hisbison.y"
    {(yyval.A).code = code_gen(2,"goto ",stack[top]); (yyval.A).optimized_code = (yyval.A).code;;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 711 "hisbison.y"
    {(yyval.A).code = code_gen(3,"return ",(yyvsp[(2) - (3)].A).addr,"\ngoto end\n");  (yyval.A).optimized_code = (yyval.A).code; return_flag=1;;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 714 "hisbison.y"
    {(yyval.A)=(yyvsp[(1) - (1)].A);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 715 "hisbison.y"
    {(yyval.A)=(yyvsp[(1) - (1)].A);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 716 "hisbison.y"
    {(yyval.A)=(yyvsp[(1) - (1)].A);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 720 "hisbison.y"
    {(yyval.A).code = code_gen(3,(yyvsp[(1) - (3)].A).code,(yyvsp[(3) - (3)].A).code,code_gen(3,(yyvsp[(1) - (3)].A).addr,(yyvsp[(2) - (3)].text),(yyvsp[(3) - (3)].A).addr)); 
					if(strcmp((yyvsp[(2) - (3)].text),"<")==0)
					{
						num_iter[iter_top++]=atoi((yyvsp[(3) - (3)].A).addr);
						//printf("TOP: %d\n",iter_top);
						number_of_iterations = num_iter[--iter_top]-iter_init[iter_top];
						//num_iter = atoi($3.addr);
						//printf("Number of iterations: %d\n",num_iter);
					}
					
					if(strcmp((yyvsp[(2) - (3)].text),"<=")==0)
					{
						num_iter[iter_top++]=atoi((yyvsp[(3) - (3)].A).addr);
						printf("20      TOP: %d\n",iter_top);
						number_of_iterations = num_iter[--iter_top]-iter_init[iter_top]+1;
					}
					if(strcmp((yyvsp[(2) - (3)].text),">")==0)
					{
						num_iter[iter_top++]=atoi((yyvsp[(3) - (3)].A).addr);
						printf("21      TOP: %d\n",iter_top);
						number_of_iterations = iter_init[--iter_top] - num_iter[iter_top];
					}
					if(strcmp((yyvsp[(2) - (3)].text),">=")==0)
					{
						num_iter[iter_top++]=atoi((yyvsp[(3) - (3)].A).addr);
						printf("22      TOP: %d\n",iter_top);
						number_of_iterations = iter_init[--iter_top] - num_iter[iter_top]+1;
					}
					
					;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 752 "hisbison.y"
    {(yyval.A).code = code_gen(3,(yyvsp[(1) - (3)].A).code,(yyvsp[(3) - (3)].A).code,code_gen(3,(yyvsp[(1) - (3)].A).addr,(yyvsp[(2) - (3)].text),(yyvsp[(3) - (3)].A).addr)); (yyval.A).optimized_code = (yyval.A).code;;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 755 "hisbison.y"
    {(yyval.text)=(yyvsp[(1) - (1)].text);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 756 "hisbison.y"
    {(yyval.text)=(yyvsp[(1) - (1)].text);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 759 "hisbison.y"
    {(yyval.text)=(yyvsp[(1) - (1)].text);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 760 "hisbison.y"
    {(yyval.text)=(yyvsp[(1) - (1)].text);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 761 "hisbison.y"
    {(yyval.text)=(yyvsp[(1) - (1)].text);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 762 "hisbison.y"
    {(yyval.text)=(yyvsp[(1) - (1)].text);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 763 "hisbison.y"
    {(yyval.text)=(yyvsp[(1) - (1)].text);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 764 "hisbison.y"
    {(yyval.text)=(yyvsp[(1) - (1)].text);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 767 "hisbison.y"
    {(yyval.A).code = code_gen(3,(yyvsp[(1) - (3)].var_type)," ",(yyvsp[(2) - (3)].A).code); (yyval.A).optimized_code = (yyval.A).code;;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 768 "hisbison.y"
    {(yyval.A).code = code_gen(1,(yyvsp[(2) - (2)].A).code); (yyval.A).optimized_code = (yyvsp[(2) - (2)].A).optimized_code; ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 773 "hisbison.y"
    { (yyval.var_type)=(yyvsp[(1) - (1)].var_type); strcpy(typ,(yyvsp[(1) - (1)].var_type));;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 774 "hisbison.y"
    {(yyval.var_type)=(yyvsp[(1) - (1)].var_type);strcpy(typ,(yyvsp[(1) - (1)].var_type));;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 777 "hisbison.y"
    {if(look_up_sym_tab_dec((yyvsp[(3) - (3)].text),scope[scope_ind-1])){ yyerror("Redeclaration\n");  YYERROR; } 
								if(scope[scope_ind-1]>0){update_sym_tab((yyvsp[(0) - (3)].var_type),(yyvsp[(3) - (3)].text),yylineno,scope[scope_ind-1]);}else{int scop=get_scope();update_sym_tab((yyvsp[(0) - (3)].var_type),(yyvsp[(3) - (3)].text),yylineno,scop);} 

								(yyval.A).code = code_gen(3,(yyvsp[(1) - (3)].A).code,", ",(yyvsp[(3) - (3)].text)); (yyval.A).optimized_code = code_gen(3,(yyvsp[(1) - (3)].A).optimized_code,", ",(yyvsp[(3) - (3)].text));
								;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 782 "hisbison.y"
    {(yyval.A).addr=gen_addr((yyvsp[(1) - (1)].text)); 
	   					if(look_up_sym_tab_dec((yyvsp[(1) - (1)].text),scope[scope_ind-1])){ yyerror("Redeclaration\n");  YYERROR; }
	   					if(scope[scope_ind-1]>0){update_sym_tab((yyvsp[(0) - (1)].var_type),(yyvsp[(1) - (1)].text),yylineno,scope[scope_ind-1]);}else{int scop=get_scope();update_sym_tab((yyvsp[(0) - (1)].var_type),(yyvsp[(1) - (1)].text),yylineno,scop);} 
	   					(yyval.A).code = (yyvsp[(1) - (1)].text); (yyval.A).optimized_code = (yyvsp[(1) - (1)].text);
	   					//printf("%s ID\n",$1);
	   					;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 791 "hisbison.y"
    {(yyval.A).addr = gen_addr((yyvsp[(1) - (5)].text));  
			   							(yyval.A).code = code_concatenate(3,(yyvsp[(3) - (5)].A).code,code_gen(3,(yyval.A).addr," = ",(yyvsp[(3) - (5)].A).addr),(yyvsp[(5) - (5)].A).code);
			   							char buf[10];
			   							int scop=get_scope();
			   							int ret=is_int((yyvsp[(1) - (5)].text),scop);
			   							if(ret)
			   							{
			   								if(is_digit((yyvsp[(3) - (5)].A).addr))
			   								{
			   									float val=atof((yyvsp[(3) - (5)].A).addr);
			   									int val1=(int)val;
			   									char buf1[10];
			   									gcvt(val1, 6, buf1);
			   									(yyval.A).code = code_concatenate(3,(yyvsp[(3) - (5)].A).code,code_gen(3,(yyval.A).addr," = ",buf1),(yyvsp[(5) - (5)].A).code);
			   								}
			   								else
			   									(yyval.A).code = code_concatenate(3,(yyvsp[(3) - (5)].A).code,code_gen(3,(yyval.A).addr," = ",(yyvsp[(3) - (5)].A).addr),(yyvsp[(5) - (5)].A).code);
			   							} 
			   							else
			   								(yyval.A).code = code_concatenate(3,(yyvsp[(3) - (5)].A).code,code_gen(3,(yyval.A).addr," = ",(yyvsp[(3) - (5)].A).addr),(yyvsp[(5) - (5)].A).code);
			   							//printf("%s\n",$1);
			   							
			   							if(ret)
			   							{
			   								int val=(int)(yyvsp[(3) - (5)].A).val;
			   								float f = val;
			   								gcvt(val, 6, buf);
			   							}
			   							else
											gcvt((yyvsp[(3) - (5)].A).val, 6, buf);
										if((yyvsp[(3) - (5)].A).is_dig)
			   							(yyval.A).optimized_code = code_concatenate(2,code_gen(3,(yyval.A).addr," = ",buf),(yyvsp[(5) - (5)].A).optimized_code);
			   							else
			   							(yyval.A).optimized_code = code_concatenate(3,(yyvsp[(3) - (5)].A).optimized_code,code_gen(3,(yyval.A).addr," = ",(yyvsp[(3) - (5)].A).addr),(yyvsp[(5) - (5)].A).optimized_code);
			   							if(!look_up_sym_tab((yyvsp[(1) - (5)].text))){printf("24     Undeclared variable %s\n", (yyvsp[(1) - (5)].text)); YYERROR;}flag1=1;
			   							;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 827 "hisbison.y"
    {
		  								(yyval.A).addr = gen_addr((yyvsp[(1) - (4)].text)); 
		  								int scop=get_scope(); 
		  								int ret=is_int((yyvsp[(1) - (4)].text),scop);
		  								if(ret)
			   							{
			   								if(is_digit((yyvsp[(3) - (4)].A).addr))
			   								{
			   									float val=atof((yyvsp[(3) - (4)].A).addr);
			   									int val1=(int)val;
			   									char buf1[10];
			   									gcvt(val1, 6, buf1);
			   									(yyval.A).code = code_concatenate(2,(yyvsp[(3) - (4)].A).code,code_gen(3,(yyval.A).addr," = ",buf1));
			   								}
			   								else
			   									(yyval.A).code = code_concatenate(2,(yyvsp[(3) - (4)].A).code,code_gen(3,(yyval.A).addr," = ",(yyvsp[(3) - (4)].A).addr));
			   							} 
			   							else
			   								(yyval.A).code = code_concatenate(2,(yyvsp[(3) - (4)].A).code,code_gen(3,(yyval.A).addr," = ",(yyvsp[(3) - (4)].A).addr));
			   							char buf[10];
			   							
										
			   							if(ret)
			   							{
			   								int val=(int)(yyvsp[(3) - (4)].A).val;
			   								float f = val;
			   								gcvt(val, 6, buf);
			   							}
			   							else
											gcvt((yyvsp[(3) - (4)].A).val, 6, buf);
										//printf("flag %d",flag1);
										if((yyvsp[(3) - (4)].A).is_dig)
										{
											//printf("Assign Here\n");
			   								(yyval.A).optimized_code = code_concatenate(1,code_gen(3,(yyval.A).addr," = ",buf)); 
			   								//printf("%s\n",$$.optimized_code);
			   							}
			   							else
			   							{
			   								(yyval.A).optimized_code = code_concatenate(2,(yyvsp[(3) - (4)].A).optimized_code,code_gen(3,(yyval.A).addr," = ",(yyvsp[(3) - (4)].A).addr)); 
			   								//flag1=1;
			   							}
			   							//printf("OC: %s\n",$$.optimized_code);
			   							if(!look_up_sym_tab((yyvsp[(1) - (4)].text))){printf("25     Undeclared variable %s\n", (yyvsp[(1) - (4)].text)); YYERROR;}
			   							flag1=1;												
			   							;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 875 "hisbison.y"
    {(yyval.A).addr = gen_addr((yyvsp[(1) - (5)].text));  
										
										if(strcmp(typ,"int")==0)
		   								{
		   									if(is_digit((yyvsp[(3) - (5)].A).addr))
		   									{
		   										float val=atof((yyvsp[(3) - (5)].A).addr);
		   										int val1=(int)val;
		   										char buf1[10];
		   										gcvt(val1, 6, buf1);
		   										(yyval.A).code = code_concatenate(3,(yyvsp[(3) - (5)].A).code,code_gen(5,typ," ",(yyval.A).addr," = ",buf1),(yyvsp[(5) - (5)].A).code); 
		   									}
		   									else
		   										(yyval.A).code = code_concatenate(3,(yyvsp[(3) - (5)].A).code,code_gen(5,typ," ",(yyval.A).addr," = ",(yyvsp[(3) - (5)].A).addr),(yyvsp[(5) - (5)].A).code); 

		   								}
		   								else
			   								(yyval.A).code = code_concatenate(3,(yyvsp[(3) - (5)].A).code,code_gen(5,typ," ",(yyval.A).addr," = ",(yyvsp[(3) - (5)].A).addr),(yyvsp[(5) - (5)].A).code); 
			   							
			   							char buf[10];
			   							if(strcmp(typ,"int")==0)
			   							{
			   								int val=(int)(yyvsp[(3) - (5)].A).val;
			   								float f = val;
			   								gcvt(val, 6, buf);
			   							}
										else
											gcvt((yyvsp[(3) - (5)].A).val, 6, buf);
										if((yyvsp[(3) - (5)].A).is_dig)
			   								(yyval.A).optimized_code = code_concatenate(2,code_gen(3,(yyval.A).addr," = ",buf),(yyvsp[(5) - (5)].A).optimized_code);
			   							else
			   								(yyval.A).optimized_code = code_concatenate(3,(yyvsp[(3) - (5)].A).optimized_code,code_gen(3,(yyval.A).addr," = ",(yyvsp[(3) - (5)].A).addr),(yyvsp[(5) - (5)].A).optimized_code);
			   							//$$.optimized_code = code_concatenate(2,code_gen(5,typ," ",$$.addr," = ",buf),$5.optimized_code);
			   							 if(look_up_sym_tab_dec((yyvsp[(1) - (5)].text),scope[scope_ind-1])){ yyerror("Redeclaration\n");  YYERROR;flag1=1; }
if(scope[scope_ind-1]>0){update_sym_tab(typ,(yyvsp[(1) - (5)].text),yylineno,scope[scope_ind-1]);}else{int scop=get_scope();update_sym_tab(typ,(yyvsp[(1) - (5)].text),yylineno,scop);}
			   							;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 911 "hisbison.y"
    {  (yyval.A).addr = gen_addr((yyvsp[(1) - (4)].text));  
		   								
		   								if(strcmp(typ,"int")==0)
		   								{
		   									if(is_digit((yyvsp[(3) - (4)].A).addr))
		   									{
		   										float val=atof((yyvsp[(3) - (4)].A).addr);
		   										int val1=(int)val;
		   										char buf1[10];
		   										gcvt(val1, 6, buf1);
		   										(yyval.A).code = code_concatenate(2,(yyvsp[(3) - (4)].A).code,code_gen(5,typ," ",(yyval.A).addr," = ",buf1)); 
		   									}
		   									else
		   										(yyval.A).code = code_concatenate(2,(yyvsp[(3) - (4)].A).code,code_gen(5,typ," ",(yyval.A).addr," = ",(yyvsp[(3) - (4)].A).addr)); 

		   								}
		   								else
			   								(yyval.A).code = code_concatenate(2,(yyvsp[(3) - (4)].A).code,code_gen(5,typ," ",(yyval.A).addr," = ",(yyvsp[(3) - (4)].A).addr)); 
			   							char buf[10];
			   							if(strcmp(typ,"int")==0)
			   							{
			   								int val=(int)(yyvsp[(3) - (4)].A).val;
			   								float f = val;
			   								gcvt(val, 6, buf);
			   							}
										else
											gcvt((yyvsp[(3) - (4)].A).val, 6, buf);
										if((yyvsp[(3) - (4)].A).is_dig)
										{
											//printf("Here\n");
			   								(yyval.A).optimized_code = code_concatenate(1,code_gen(3,(yyval.A).addr," = ",buf)); 
			   							}
			   							else
			   							{
			   								(yyval.A).optimized_code = code_concatenate(2,(yyvsp[(3) - (4)].A).optimized_code,code_gen(3,(yyval.A).addr," = ",(yyvsp[(3) - (4)].A).addr)); 
			   								//flag1=1;
			   							}
			   							//$$.optimized_code = code_concatenate(1,code_gen(5,typ," ",$$.addr," = ",buf)); 
			   							//printf("OC: %s\n",$$.optimized_code); 
			   							 if(look_up_sym_tab_dec((yyvsp[(1) - (4)].text),scope[scope_ind-1])){ yyerror("Redeclaration\n");  YYERROR; } if(scope[scope_ind-1]>0){update_sym_tab(typ,(yyvsp[(1) - (4)].text),yylineno,scope[scope_ind-1]);}else{int scop=get_scope();update_sym_tab(typ,(yyvsp[(1) - (4)].text),yylineno,scop);} 
			   							iter_init[iter_top]=atoi((yyvsp[(3) - (4)].A).addr);
			   							//printf("TOP: %d",iter_top);flag1=1;
			   						 ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 956 "hisbison.y"
    {(yyval.A).addr = new_temp(); (yyval.A).code = code_concatenate(3,(yyvsp[(1) - (3)].A).code,(yyvsp[(3) - (3)].A).code,code_gen(5,(yyval.A).addr," = ",(yyvsp[(1) - (3)].A).addr," + ",(yyvsp[(3) - (3)].A).addr)); 
				
				if(((yyvsp[(1) - (3)].A).is_dig) && ((yyvsp[(3) - (3)].A).is_dig))
				{
					(yyval.A).is_dig=1;
					//printf("HERE\n");
					//printf("Constant folding\n");
					//float temp = atof($1.addr) + atof($3.addr);
					float temp = (yyvsp[(1) - (3)].A).val+(yyvsp[(3) - (3)].A).val;
					char buf[10];
					gcvt(temp, 6, buf);
					(yyval.A).optimized_code = code_concatenate(3,(yyvsp[(1) - (3)].A).optimized_code,(yyvsp[(3) - (3)].A).optimized_code,code_gen(3,(yyval.A).addr," = ",buf));
					//printf("%s\n",$$.optimized_code);
					(yyval.A).val = temp;
					flag1 &= 1;
				}
				else
				{
					(yyval.A).is_dig=0;
					//printf("HERE\n");
					(yyval.A).optimized_code = (yyval.A).code;
					flag1=0;
				}
				
				;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 981 "hisbison.y"
    {(yyval.A).addr = new_temp(); (yyval.A).code = code_concatenate(3,(yyvsp[(1) - (3)].A).code,(yyvsp[(3) - (3)].A).code,code_gen(5,(yyval.A).addr," = ",(yyvsp[(1) - (3)].A).addr," - ",(yyvsp[(3) - (3)].A).addr));
 				if(((yyvsp[(1) - (3)].A).is_dig) && ((yyvsp[(3) - (3)].A).is_dig))
				{
					(yyval.A).is_dig=1;
					//printf("Constant folding\n");
					//float temp = atof($1.addr) - atof($3.addr);
					float temp = (yyvsp[(1) - (3)].A).val-(yyvsp[(3) - (3)].A).val;
					char buf[10];
					gcvt(temp, 6, buf);
					(yyval.A).optimized_code = code_concatenate(3,(yyvsp[(1) - (3)].A).optimized_code,(yyvsp[(3) - (3)].A).optimized_code,code_gen(3,(yyval.A).addr," = ",buf));
					//printf("%s\n",$$.optimized_code);
					(yyval.A).val = temp;
					flag1 &=1;
				}
				else
				{
					(yyval.A).is_dig=0;
					(yyval.A).optimized_code = (yyval.A).code;
					flag1=0;
				}
 				;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1002 "hisbison.y"
    {(yyval.A)=(yyvsp[(1) - (1)].A);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1005 "hisbison.y"
    {(yyval.A).addr = new_temp(); (yyval.A).code = code_concatenate(3,(yyvsp[(1) - (3)].A).code,(yyvsp[(3) - (3)].A).code,code_gen(5,(yyval.A).addr," = ",(yyvsp[(1) - (3)].A).addr," * ",(yyvsp[(3) - (3)].A).addr)); 
				if(((yyvsp[(1) - (3)].A).is_dig) && ((yyvsp[(3) - (3)].A).is_dig))
				{
					(yyval.A).is_dig=1;
					//printf("HERE MULT\n");
					//printf("Constant folding\n");
					//float temp = atof($1.addr) * atof($3.addr);
					float temp = (yyvsp[(1) - (3)].A).val*(yyvsp[(3) - (3)].A).val;
					char buf[10];
					gcvt(temp, 6, buf);
					(yyval.A).optimized_code = code_concatenate(3,(yyvsp[(1) - (3)].A).optimized_code,(yyvsp[(3) - (3)].A).optimized_code,code_gen(3,(yyval.A).addr," = ",buf));
					//printf("%s\n",$$.optimized_code);
					(yyval.A).val = temp;
					flag1 &=1;
				}

				else
				{
					(yyval.A).is_dig=0;
					(yyval.A).optimized_code = (yyval.A).code;
					flag1=0;
				}
				;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 1028 "hisbison.y"
    {(yyval.A).addr = new_temp(); (yyval.A).code = code_concatenate(3,(yyvsp[(1) - (3)].A).code,(yyvsp[(3) - (3)].A).code,code_gen(5,(yyval.A).addr," = ",(yyvsp[(1) - (3)].A).addr," / ",(yyvsp[(3) - (3)].A).addr)); 
 				if(((yyvsp[(1) - (3)].A).is_dig) && ((yyvsp[(3) - (3)].A).is_dig))
				{
					(yyval.A).is_dig=1;
					//printf("Constant folding\n");
					//float temp = atof($1.addr) / atof($3.addr);
					float temp = (yyvsp[(1) - (3)].A).val/(yyvsp[(3) - (3)].A).val;
					char buf[10];
					gcvt(temp, 6, buf);
					(yyval.A).optimized_code = code_concatenate(3,(yyvsp[(1) - (3)].A).optimized_code,(yyvsp[(3) - (3)].A).optimized_code,code_gen(3,(yyval.A).addr," = ",buf));
					//printf("%s\n",$$.optimized_code);
					(yyval.A).val = temp;
					flag1 &=1;
				}
				else
				{
					(yyval.A).is_dig=0;
					(yyval.A).optimized_code = (yyval.A).code;
					flag1=0;
				}
 				;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 1049 "hisbison.y"
    {(yyval.A).addr = (yyvsp[(1) - (1)].A).addr; (yyval.A).code = (yyvsp[(1) - (1)].A).code; (yyval.A).optimized_code = (yyvsp[(1) - (1)].A).optimized_code; (yyval.A).val = (yyvsp[(1) - (1)].A).val;(yyval.A).is_dig=(yyvsp[(1) - (1)].A).is_dig;;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 1052 "hisbison.y"
    {(yyval.A).addr = gen_addr((yyvsp[(1) - (1)].text)); (yyval.A).code = code_gen(1," ");if(!look_up_sym_tab((yyvsp[(1) - (1)].text))){printf("26        Undeclared variable %s\n", (yyvsp[(1) - (1)].text)); YYERROR;} (yyval.A).optimized_code = (yyval.A).code;(yyval.A).is_dig=0;;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 1053 "hisbison.y"
    {(yyval.A).addr = gen_addr((yyvsp[(1) - (1)].text)); (yyval.A).code = code_gen(1," ");(yyval.A).optimized_code = (yyval.A).code; (yyval.A).val = atof((yyvsp[(1) - (1)].text));(yyval.A).is_dig=1;;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1054 "hisbison.y"
    {(yyval.A)= (yyvsp[(2) - (3)].A);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1055 "hisbison.y"
    {(yyval.A)=(yyvsp[(1) - (1)].A);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1056 "hisbison.y"
    {(yyval.A)=(yyvsp[(1) - (1)].A);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1059 "hisbison.y"
    {(yyval.A).addr = new_temp(); 
								(yyval.A).code = code_concatenate(2,code_gen(5,(yyval.A).addr,"=",(yyvsp[(1) - (3)].text),(yyvsp[(2) - (3)].text),(yyvsp[(3) - (3)].text)), code_gen(3,(yyvsp[(1) - (3)].text),"=",(yyval.A).addr)); 
								if(!look_up_sym_tab((yyvsp[(1) - (3)].text))){printf("27     Undeclared variable %s\n", (yyvsp[(1) - (3)].text)); YYERROR;}
								if(!look_up_sym_tab((yyvsp[(3) - (3)].text))){printf("28     Undeclared variable %s\n", (yyvsp[(3) - (3)].text)); YYERROR;}
								(yyval.A).optimized_code = (yyval.A).code;
								(yyval.A).is_dig=0;
								;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1066 "hisbison.y"
    {(yyval.A).addr = new_temp(); 
								(yyval.A).code = code_concatenate(2,code_gen(5,(yyval.A).addr,"=",(yyvsp[(1) - (3)].text),(yyvsp[(2) - (3)].text),(yyvsp[(3) - (3)].text)), code_gen(3,(yyvsp[(1) - (3)].text),"=",(yyval.A).addr)); 
								if(!look_up_sym_tab((yyvsp[(1) - (3)].text))){printf("29     Undeclared variable %s\n", (yyvsp[(1) - (3)].text)); YYERROR;}
								(yyval.A).optimized_code = (yyval.A).code;
								(yyval.A).is_dig=0;
								;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1072 "hisbison.y"
    {(yyval.A).addr = new_temp(); 
								(yyval.A).code = code_concatenate(3,(yyvsp[(4) - (5)].A).code,code_gen(5,(yyval.A).addr,"=",(yyvsp[(1) - (5)].text),(yyvsp[(2) - (5)].text),(yyvsp[(4) - (5)].A).addr), code_gen(3,(yyvsp[(1) - (5)].text),"=",(yyval.A).addr)); 
								if(!look_up_sym_tab((yyvsp[(1) - (5)].text))){printf("30     Undeclared variable %s\n", (yyvsp[(1) - (5)].text)); YYERROR;}
								(yyval.A).optimized_code = (yyval.A).code;
								(yyval.A).is_dig=0;
								;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1080 "hisbison.y"
    {(yyval.text)=strdup("+");;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1081 "hisbison.y"
    {(yyval.text)=strdup("-");;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1082 "hisbison.y"
    {(yyval.text)=strdup("*");;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1083 "hisbison.y"
    {(yyval.text)=strdup("/");;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1086 "hisbison.y"
    { (yyval.A).addr = new_temp(); 
								(yyval.A).code = code_concatenate(2,code_gen(4,(yyval.A).addr,"=",(yyvsp[(2) - (2)].text),"+ 1"),code_gen(3,(yyvsp[(2) - (2)].text),"=",(yyval.A).addr)); 
								if(!look_up_sym_tab((yyvsp[(2) - (2)].text))){printf("31     Undeclared variable %s\n", (yyvsp[(2) - (2)].text)); YYERROR;}
								(yyval.A).optimized_code = (yyval.A).code;
								(yyval.A).is_dig=0;
							;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1092 "hisbison.y"
    { (yyval.A).addr = new_temp(); 
								(yyval.A).code = code_concatenate(2,code_gen(4,(yyval.A).addr,"=",(yyvsp[(1) - (2)].text),"+ 1"),code_gen(3,(yyvsp[(1) - (2)].text),"=",(yyval.A).addr));
								if(!look_up_sym_tab((yyvsp[(1) - (2)].text))){printf("32     Undeclared variable %s\n", (yyvsp[(1) - (2)].text)); YYERROR;}
								(yyval.A).optimized_code = (yyval.A).code;
								(yyval.A).is_dig=0;
							;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1098 "hisbison.y"
    {  (yyval.A).addr = new_temp(); 
								(yyval.A).code = code_concatenate(2,code_gen(4,(yyval.A).addr,"=",(yyvsp[(2) - (2)].text),"- 1"),code_gen(3,(yyvsp[(2) - (2)].text),"=",(yyval.A).addr));
								if(!look_up_sym_tab((yyvsp[(2) - (2)].text))){printf("33     Undeclared variable %s\n", (yyvsp[(2) - (2)].text)); YYERROR;}
								(yyval.A).optimized_code = (yyval.A).code;
								(yyval.A).is_dig=0;
							;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1104 "hisbison.y"
    {  (yyval.A).addr = new_temp(); 
								(yyval.A).code = code_concatenate(2,code_gen(4,(yyval.A).addr,"=",(yyvsp[(1) - (2)].text),"- 1"),code_gen(3,(yyvsp[(1) - (2)].text),"=",(yyval.A).addr));
								if(!look_up_sym_tab((yyvsp[(1) - (2)].text))){printf("34     Undeclared variable %s\n", (yyvsp[(1) - (2)].text)); YYERROR;}
								(yyval.A).optimized_code = (yyval.A).code;
								(yyval.A).is_dig=0;
							;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1110 "hisbison.y"
    {  (yyval.A).addr = new_temp(); 
								(yyval.A).code = code_gen(4,(yyval.A).addr,"=",(yyvsp[(1) - (2)].text),(yyvsp[(2) - (2)].text)); 
								if(!look_up_sym_tab((yyvsp[(1) - (2)].text))){printf("35     Undeclared variable %s\n", (yyvsp[(1) - (2)].text)); YYERROR;}
								(yyval.A).optimized_code = (yyval.A).code;
								(yyval.A).is_dig=0;
							;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1116 "hisbison.y"
    {  (yyval.A).addr = new_temp(); 
								(yyval.A).code = code_gen(4,(yyval.A).addr,"=",(yyvsp[(1) - (2)].text),(yyvsp[(2) - (2)].text)); 
								(yyval.A).optimized_code = (yyval.A).code;
								(yyval.A).is_dig=1;
							;}
    break;



/* Line 1455 of yacc.c  */
#line 2980 "myapp.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1122 "hisbison.y"

void yyerror(const char* arg)
{
	printf("36      %s\n",arg);
}



int main()
{
	printf("37      Enter a string\n");
	//yylex();
	yyin=fopen("test1.txt","r");
	if(!yyparse())
	{
		printf("38      \nSuccess\n");

	}
	else
		printf("39      Fail\n");
	/*
	int i;
	for(i=0;i<scope_ind;i++)
		printf("40      %d ",scope[i]);
	*/
	//printf("\n");
	//printf("%d\n",is_digit("2"));
}

