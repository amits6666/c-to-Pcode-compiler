#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <assert.h>

#define     DEFINE_GLOBALS
#include    "globals.h"
#undef      DEFINE_GLOBALS

#include    "ctree.h"
#include    "lexer.h"
#include    "token.h"
#include    "gram_parser.cpp.h"
#include    "tree.h"
#include    "prnttree.h"
#include    "CodeGenerator.h"


/*  ###############################################################  */

#define    VERSION    "C-Tree Version 0.14"

/*  extern FILE *yyin;  */
/*  extern int   yyparse();  */
char	*cur_file;
int		show_pcode = 0;
int		show_SymbolTable = 0;
int		show_AST = 0;

#ifdef  USE_CPP

#    ifdef    USE_GCC_4_CPP
#    define   LIB_CPP    "gcc -E "
#    endif

#    ifdef    USE_CAT_4_CPP
#    define   LIB_CPP    "cat "
#    endif

#    ifdef    USE_CPP_4_CPP
#    define   LIB_CPP    "/lib/cpp "
#    endif

#    ifndef   LIB_CPP
#    define   LIB_CPP    "/lib/cpp "
#    endif	

#endif	/* USE_CPP */

/*  ###############################################################  */

void Usage(char *prog)
{
    fprintf(stderr,"Usage: %s [options] [filename(s)]\n\n",prog);

    fprintf(stderr,"This program parses C code, builds a tree and generate Pcode.\n\n");

    fprintf(stderr,"Options:\n");
    fprintf(stderr,"\t-Pcode:\t\t Show the generated Pcode (code machine).\n");
    fprintf(stderr,"\t-AST:\t\t Show Abstract-syntax-tree (AST).\n");
    fprintf(stderr,"\t-SymTab:\t Show Symbol Table.\n");
    fprintf(stderr,"\t-version:\t Show ctree version (-V).\n");
    fprintf(stderr,"\t-help:\t\t Show usage (-h).\n");
    exit(0);
}

/*  ###############################################################  */

int processArgs( int argc, char **argv )
{
    int num_files = 0;
    char *arg;
    char *prog = argv[0];

    argc--; 
    argv++;

    while(argc-- > 0) {
        arg = *argv++;

		if (strcmp(arg, "-Pcode") == 0)
			show_pcode = 1;
		else if (strcmp(arg, "-AST") == 0)
			show_AST = 1;
		else if (strcmp(arg, "-SymTab") == 0)
			show_SymbolTable = 1;
        else if ((strcmp(arg,"-version") == 0)
              || (strcmp(arg,"-V") == 0))
          fprintf(stdout, VERSION "\n");
        else if ((strcmp(arg,"-help") == 0)
            || (strcmp(arg,"-h") == 0))
          Usage(prog);
        else
          file_list[num_files++] = arg;    
    }

    file_list[num_files] = NULL;
    return(num_files);
}

/*  ###############################################################  */

int main( int argc, char **argv )
{
int   i, nf;
FILE *fp;
#ifdef  USE_CPP
char  cpp_cmmd[500];
char  cpp_file[200];
#endif
treenode   *parse_tree;
context_t  *contxt;

    if ((nf = processArgs(argc,argv)) < 0)
        return -1;

    if (nf == 0)
        Usage(argv[0]);

    parse_tree = (treenode *) NULL;

    init_nmetab();
    ParseStack = new_treestk();
    DoneStack  = new_treestk();
    contxt = new_context();

    if (!ParseStack || !DoneStack || !contxt) {
        delete_treestk(ParseStack);
        delete_treestk(DoneStack);
        free_context(contxt);
        fputs("Out of memory.\n", stderr);
        exit(1);
    }
    ParseStack->contxt = contxt;
 
    for (i=0; i < nf; i++) {
#ifdef  USE_CPP
        char *end;
#endif
        cur_file = file_list[i];

#ifdef USE_CPP
        strcpy(cpp_file, file_list[i]);
        end = strrchr(cpp_file,'.');
        if (!end) {
          fprintf(stderr, "No '.' found in filename '%s'\n", cur_file);
          continue;
        }
 
        sprintf(end, "_pp");

/*
willey
need to redirect output to file if using GCC, not give target file as final
argument, as in cpp

*/

#ifdef  USE_GCC_4_CPP
        sprintf(cpp_cmmd,"%s -DCTREE %s > %s",LIB_CPP, file_list[i], cpp_file);

#elif defined(USE_CAT_4_CPP)

        sprintf(cpp_cmmd,"%s %s > %s", LIB_CPP, file_list[i], cpp_file);
#else
        sprintf(cpp_cmmd, "%s -DCTREE %s %s", LIB_CPP, file_list[i], cpp_file);
#endif

        /*
          willey
          debugging line to see what preprocessor is being called
        */
#ifdef  DEBUG
        fprintf(stderr,"%s\n",cpp_cmmd);
#endif

        system(cpp_cmmd);
 
        if ((fp = fopen(cpp_file,"r")) == NULL)
            return(1);
#else

        if ((fp = fopen(cur_file,"r")) == NULL)
            return(1);
#endif
		
        handle_new_file(ParseStack, fp, file_list[i]);
		enter_scope(contxt);
		tree_parse(ParseStack, 0);
        parse_tree = (top_of_stack(DoneStack))->parse_tree;
		
#ifdef USE_CPP
        if (remove(cpp_file)) {
          fprintf(stderr, "Remove of file '%s' failed.\n", cpp_file);
        }
#endif

        if (parse_tree) 
		{
            /* Show data */
			if(show_pcode)
				print_pcode(parse_tree,stdout);
            else if(show_AST)
				show_tree(parse_tree,stdout);
			else if (show_SymbolTable)
				print_symbol_table(parse_tree);

            parse_tree = (treenode *) NULL;
        } 
		else 
		{
            fputs(" parse_tree is NULL\n", stdout);
        }

        exit_scope(contxt);

        while (! is_empty(ParseStack))
            delete_stk_item(pop(ParseStack)); 

        while (! is_empty(DoneStack))
            delete_stk_item(Parse_TOS = pop(DoneStack)); 
    }

    delete_treestk(ParseStack);
    delete_treestk(DoneStack);
    free_context(contxt);
    free_nmetab();

    return(0);
}

/*  ###############################################################  */
