#ifndef   CODE_GENERATOR_H
#define   CODE_GENERATOR_H
#include    <stdio.h>
#include    <string.h>
#include    <malloc.h>
#include    "config.h"
#include    "tree.h"
#include    "prnttree.h"
#include    "token.h"
#include    "gram_parser.cpp.h"
#include    "symtab.h"
#include    "dsm_extension.h"
#include    "globals.h"

#define FAILURE 1
#define SUCCESS 0

BEGIN_HEADER
/*  ###############################################################  */
void	print_symbol_table	ARGS((treenode*));
int	code_recur			ARGS((treenode*));

/*  ###############################################################  */

END_HEADER

#endif   
