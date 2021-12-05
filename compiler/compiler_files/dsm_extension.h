#ifndef __DSM_EXTENSION_H__
#define __DSM_EXTENSION_H__

#include "tree.h"

typedef struct _treenode_list
{
	treenode *node;
	struct _treenode_list *next;
} treenode_list;

typedef struct _char_list
{
	char *node;
	struct _char_list *next;
} char_list;

// this function returns list of variables used in block treenode *
// with scope biger than scope, but no global variables
extern treenode_list *get_vars_list(treenode *, int scope);

// this function prints list of variables to file
extern void print_list(treenode_list *, int , FILE *);

// this function builds header file.
extern void print_declaration(treenode *, int, FILE *, int);

extern void print_main_part(treenode *, int, FILE *, FILE *, FILE *,int, int);
extern void print_selectors(treenode *, int, FILE *, int );
#endif