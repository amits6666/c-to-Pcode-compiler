#ifndef   PRNTTREE_H
#define   PRNTTREE_H

#include    <stdio.h>

#include    "config.h"
#include    "tree.h"

BEGIN_HEADER

/*  ###############################################################  */

    /*  External Declarations */
extern int debug_print_on;

   /*  indent - 2 spaces per level */
void  indent    ARGS((int levels, FILE *fp));

void  fputs_metachr    ARGS((char c, int in_str, FILE *fp));
   /* Print the string, converting chars to escape sequences. */
void  fputs_metastr    ARGS((char *str, FILE *fp));

   /* Return a string that represents the pointer. */
char *print_ptr     ARGS((void *ptr));

      /* Print the tree back out (as code - or close) */
void  print_tree_as_dsm_code  ARGS((treenode*, char *));
void  print_tree              ARGS((treenode*, FILE *fp));
void  print_pcode             ARGS((treenode*, FILE *fp));
void  print_frag              ARGS((treenode*, FILE *fp));
void  print_type              ARGS((treenode*, FILE *fp));

void  show_leaf               ARGS((leafnode*, int tabs, FILE *fp));
void  show_tree               ARGS((treenode*, FILE *fp));

void  show_int_ntype          ARGS((treenode*, FILE *fp));

/*  ###############################################################  */

END_HEADER

#endif    /* PRNTTREE_H */
