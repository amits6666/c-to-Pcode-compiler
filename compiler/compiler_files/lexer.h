/**************************************************************************
/    lexer.h
/ *************************************************************************/

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#include "config.h"
#include "tree.h"

BEGIN_HEADER

/**************************************************************************/

/* Maximum length for strings and identifiers */
#define MAX_STRING_LEN        512

/* If we allow a comment as a token, we need to let them be larger. */
#define MAX_TOKN_LEN        8192

/**************************************************************************/

typedef union {

    treenode *node;
    leafnode *leaf;

    if_node  *ifn;
    for_node *forn;

} tree_union;

/******************************************************/

/*    For Flex compatibility  */

#undef  YYSTYPE
#define YYSTYPE tree_union

/******************************************************/

void get_lineno (void);
void yywarn  (char *s);
//int  yyerror (char *s);
int  yyerr   (char *s);

/******************************************************/

END_HEADER

#endif  /* LEXER_H */
