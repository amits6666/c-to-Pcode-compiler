/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
    o+
    o+     File:         symtab.c
    o+
    o+     Programmer:   Shaun Flisakowski
    o+     Date:         Jul 12, 1997
    o+
    o+     Implements a scoped symbol table.
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o 

    SymTab:  A tree of scope tables,
             one for each scope that declares something, or has a
             child scope that declares something:

         Level
           1              external
                         /        \
           2          file        file 
                      scope       scope 
                                /       \
           3              prototype    function
                            scope        scope
                                        /     \
           4                         block    block
                                     scope    scope    
                                                 \
           5                                     block
                                                 scope    
                                                    \
                                                   (etc.)

    At any particular point you can see all the symbols 
    (variables, types, functions, etc) declared above you in the tree.

    The scope tables are recreated in a lazy fashion, so entering
    and exiting scopes that don't declare new symbols is cheap.

    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
   
#ifndef   SYMTAB_H
#define   SYMTAB_H

#include  "config.h"
#include  "nmetab.h"
#include  "tree.h"

BEGIN_HEADER

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

/* Different kinds of entries in the symbol table. */

/* These things are all in the same namespace. */
#define    TYPEDEF_ENTRY      (1)    /* type definition. */
#define    FUNCDEF_ENTRY      (2)    /* function definition. */
#define    VARDECL_ENTRY      (3)    /* variable declaration. */
#define    ENUM_CONST_ENTRY   (4)    /* enum constants. */

/* These things are in seperate namespaces. */
#define    LABEL_ENTRY        (5)    /* label definition. */
#define    TAG_ENTRY          (6)    /* struct/union/enum tags. */

/* There is also a separate namespace for each struct/union. */
#define    COMP_ENTRY         (7)    /* components of struct/union. */

/* These might be convienent. */
#define    CURRENT_SCOPE   (0)    /* the default */
#define    EXTERN_SCOPE    (1)
#define    FILE_SCOPE      (2)
#define    FUNCTION_SCOPE  (3)
#define    BLOCK_SCOPE     (4)    /* really, 4 or more. */

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

typedef struct symentry {
    int          kind;   /* What kind of thing it is. */
    str_t       *nme;    /* The name of the thing. */
    treenode    *node;   /* ptr to it's definition/declaration. */

    /* For a struct/union component, this points to the definition
       of the container. */
    treenode    *container;

   /* This would probably be a good place to add some attributes, 
      but none come to mind at the moment. */

    struct symentry  *next;    /* For convienent storage in a hashtab_t. */
} symentry_t;

symentry_t *mk_typedef      ARGS((str_t *sym, treenode *));
symentry_t *mk_funcdef      ARGS((str_t *sym, treenode *));
symentry_t *mk_vardecl      ARGS((str_t *sym, treenode *));
symentry_t *mk_enum_const   ARGS((str_t *sym, treenode *));
symentry_t *mk_label        ARGS((str_t *sym, treenode *));
symentry_t *mk_tag          ARGS((str_t *sym, treenode *));
symentry_t *mk_component    ARGS((str_t *sym, treenode *, treenode*));

int   is_typedef       ARGS((symentry_t *));
int   is_funcdef       ARGS((symentry_t *));
int   is_vardecl       ARGS((symentry_t *));
int   is_enum_const    ARGS((symentry_t *));

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#define    INIT_HASHTAB_SIZE    (5)

typedef struct hashtab {
    int            tsize;     /* The current size of the table. */
    int            nent;      /* The number of entries being stored. */
    symentry_t   **tab;       /* The table. */
} hashtab_t;

hashtab_t  *new_hashtab       ARGS((void));
void        free_hashtab      ARGS((hashtab_t *));
symentry_t *hashtab_lookup    ARGS((hashtab_t *, str_t *nme));
symentry_t *hashtab_insert    ARGS((hashtab_t *, symentry_t *entry));

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#define    INIT_CHILD_SIZE     4

typedef struct scopetab {
    int               nsyms; /* The num of syms declared at this scope. */
    int               level; /* This scopetab's scoping level. */

    hashtab_t        *htab;  /* A hash table - to store the symbols. */

    struct scopetab  *parent; /* The scope enclosing us, if any. */

    /* A doubling array of scopes we enclose. */
    int               nchild;
    int               size;
    struct scopetab **children;
} scopetab_t;

scopetab_t *new_scopetab       ARGS((scopetab_t *mom));
void        free_scopetab      ARGS((scopetab_t *));
symentry_t *scopetab_lookup    ARGS((scopetab_t *, str_t *nme));
symentry_t *scopetab_find      ARGS((scopetab_t *, str_t *nme));
symentry_t *scopetab_insert    ARGS((scopetab_t *, symentry_t *entry));

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

typedef struct symtab {
    scopetab_t      *root;    /* The top scopetab - external scope. */

    int              clevel;  /* The current level. */
    scopetab_t      *current; /* The current scopetab, or one of its
                                 ancestors, if it doesn't exist yet. */
} symtab_t;

symtab_t   *new_symtab        ARGS((void));
void        free_symtab       ARGS((symtab_t *));

symentry_t *symtab_lookup     ARGS((symtab_t *, str_t *nme));
symentry_t *symtab_lookup_at  ARGS((symtab_t *, str_t *nme, int level));
symentry_t *symtab_insert     ARGS((symtab_t *, symentry_t *));
int         symtab_insert_at  ARGS((symtab_t *, symentry_t *, int level));

int         st_enter_scope    ARGS((symtab_t *));
void        st_exit_scope     ARGS((symtab_t *));
void        show_symtab       ARGS((symtab_t *, FILE *));

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

typedef struct context {

    symtab_t    *labels;    /* Statement labels. */
    symtab_t    *tags;      /* Struct/Union/Enum tags. */
    symtab_t    *syms;      /* Vars, Types, Functions, etc. */

} context_t;

context_t  *new_context    ARGS((void));
void        free_context   ARGS((context_t *));
int         enter_scope    ARGS((context_t *));
void        exit_scope     ARGS((context_t *));
void        exit_scopes    ARGS((context_t *, int newlev));

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
END_HEADER

#endif    /* SYMTAB_H */
