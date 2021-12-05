/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
    o+
    o+     File:         treestk.h
    o+
    o+     Programmer:   Shawn Flisakowski
    o+     Date:         Apr 7, 1995
    o+
    o+     Stacks of trees being parsed
    o+         (to parse included files, as soon as they're seen)
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#ifndef TREE_STK_H
#define TREE_STK_H

#include <stdio.h>

#include "config.h"
#include "heap.h"
#include "tree.h"
#include "symtab.h"

BEGIN_HEADER

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */

#define    YYBUFF_SIZE    4096

    /*  Redefinition - original provided by flex/lex */
#ifndef    YY_BUFFER_STATE_DEFD
typedef  struct yy_buffer_state  *YY_BUFFER_STATE;
#endif

#define    MX_NODE_1      max(LEAFNODE_SZE, TREENODE_SZE)
#define    MX_NODE_2      max(IFNODE_SZE, FORNODE_SZE)
#define    MX_NODE_SZE    max( MX_NODE_1 , MX_NODE_2 )

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */

typedef  struct stk_item {

    treenode          *parse_tree;  /* Pointer to the parse tree */
    Heap              *node_heap;   /* Allocated tree nodes */

    char              *filename;    /* The name of the file */
    FILE              *yyin;        /* A pointer to an open file */

    int                yylineno;    /* Line number */
    int                yycolno;     /* Column number */
    int                yynxtcol;    /* next Column number */

    YY_BUFFER_STATE    yybuff;      /* A buffer for the lexer */

    struct stk_item   *next;        /* Ptr to next item in the stack */

} Stk_Item;

#define    STK_ITEM_SZE    (sizeof(Stk_Item))

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */

typedef struct treestk {

    Stk_Item    *top;
    Stk_Item    *bottom;

    context_t   *contxt;

} TreeStack;

#define    TREESTK_SZE    (sizeof(TreeStack))

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */

TreeStack *new_treestk      ARGS((void));
void       delete_treestk   ARGS((TreeStack*));

Stk_Item  *new_stk_item     ARGS((FILE*, char*));
void       delete_stk_item  ARGS((Stk_Item*));

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */

void      push           ARGS((TreeStack*, Stk_Item*));
void      put_on_bottom  ARGS((TreeStack*, Stk_Item*));
Stk_Item *pop            ARGS((TreeStack*));
int       is_empty       ARGS((TreeStack*));

Stk_Item *top_of_stack   ARGS((TreeStack*));
FILE     *top_file       ARGS((TreeStack*));
char     *top_filename   ARGS((TreeStack*));

void      reset_position ARGS((TreeStack*));

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */

int  tree_parse        ARGS((TreeStack*, int parse_all));

void handle_new_file   ARGS((TreeStack*, FILE*, char*));
int  get_next_file     ARGS((TreeStack*));
void abort_file        ARGS((TreeStack*));
   
#ifdef    DEBUG 
void show_stack        ARGS((TreeStack*));
#endif

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */

END_HEADER

#endif    /* TREE_STK_H  */
