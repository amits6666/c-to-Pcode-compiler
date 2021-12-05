/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
    o+
    o+     File:         symtab.c
    o+
    o+     Programmer:   Shaun Flisakowski
    o+     Date:         Jul 15, 1997
    o+
    o+     Implements a scoped symbol table.
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#include  <stdio.h>
#include  <stdlib.h>
#include  <assert.h>

#include  "symtab.h"
#include  "nmetab.h"

#include  "prnttree.h"

/*  #define  PRINT_LEVEL  */

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

static void po_deltabs(scopetab_t *that);
static int  child_insert(scopetab_t *mom, scopetab_t *kid);
static symentry_t *mk_generic(str_t *sym, treenode *tn, int knd);

static void show_symentry(symentry_t *that, FILE *fp);
static void show_hashtab(hashtab_t *that, FILE *fp);
static void show_scopetab(scopetab_t *that, FILE *fp);

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
void
free_symentry(symentry_t *that)
{
  free(that);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
static void
show_symentry(symentry_t *that, FILE *fp)
{
  fputs("Name: ", fp);
  fputs(that->nme->str,fp);

  fputs(":\n", fp);
  print_frag(that->node, fp);

  if (that->container)
  {
    fputs("Container:\n", fp);
    print_frag(that->container, fp);
  }
  fputs("\n-------------\n", fp);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
static symentry_t*
mk_generic(str_t *sym, treenode *tn, int knd)
{
  symentry_t *that = malloc(sizeof(symentry_t));

  if (that)
  {
    that->kind = knd;
    that->nme  = sym;
    that->node = tn;
    that->container = NULL;
  } 

  return that;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
mk_typedef(str_t *sym, treenode *tn)
{
  return mk_generic(sym,tn,TYPEDEF_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
mk_funcdef(str_t *sym, treenode *tn)
{
  return mk_generic(sym,tn,FUNCDEF_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
mk_vardecl(str_t *sym, treenode *tn)
{
  return mk_generic(sym,tn,VARDECL_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
mk_enum_const(str_t *sym, treenode *tn)
{
  return mk_generic(sym,tn,ENUM_CONST_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
mk_label(str_t *sym, treenode *tn)
{
  return mk_generic(sym,tn,LABEL_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
mk_tag(str_t *sym, treenode *tn)
{
  return mk_generic(sym,tn,TAG_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
mk_component(str_t *sym, treenode *tn, treenode *container)
{
  symentry_t *entry = mk_generic(sym,tn,COMP_ENTRY);

  entry->container = container;
  return entry;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
int   is_typedef(symentry_t *that)
{
  return that && (that->kind == TYPEDEF_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
int   is_funcdef(symentry_t *that)
{
  return that && (that->kind == FUNCDEF_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
int   is_vardecl(symentry_t *that)
{
  return that && (that->kind == VARDECL_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
int   is_enum_const(symentry_t *that)
{
  return that && (that->kind == ENUM_CONST_ENTRY);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
static void
free_symlist(symentry_t *list)
{
  symentry_t *curr, *prev = NULL;

  for (curr=list; curr; curr = curr->next)
    {
    free_symentry(prev);
    prev = curr;
    }
  free_symentry(prev);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
hashtab_t *
new_hashtab(void)
{
  int j;
  hashtab_t *that = malloc(sizeof(hashtab_t));

  if (that) 
    {
    that->nent = 0;
    that->tsize = INIT_HASHTAB_SIZE;
  
    that->tab = malloc( sizeof(symentry_t*) * that->tsize );
    if (! that->tab)
      {
      free(that);
      return NULL;
      }

    for (j=0; j < that->tsize; j++)
      that->tab[j] = NULL;
    }

  return that;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
void
free_hashtab(hashtab_t *that)
{
  int j;

  if (that)
    {
    for (j=0; j < that->tsize; j++)
      free_symlist(that->tab[j]);

    free(that->tab);
    free(that);
    }
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t *
hashtab_lookup(hashtab_t *that, str_t *nme)
{
  symentry_t *curr;
  int j = nme->hash % that->tsize;
  
  for (curr = that->tab[j]; curr; curr = curr->next)
    if (nme_equal(curr->nme,nme)) 
      return curr;

  return NULL;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
hashtab_insert(hashtab_t *that, symentry_t *entry)
{
  int j;
  symentry_t *ret;

  if ((ret=hashtab_lookup(that,entry->nme)))
    return ret;

  j = entry->nme->hash % that->tsize;
  entry->next = that->tab[j];
  that->tab[j] = entry;

  return entry;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
static void
show_hashtab(hashtab_t *that, FILE *fp)
{
  int j;
  symentry_t *list;

  fprintf(fp, "HashTab:  nent: %d  size: %d\n",
              that->nent, that->tsize );

  for (j=0; j < that->tsize; j++)
    {
    list = that->tab[j];
    if (list)
      {
      fprintf(fp, "[%d]: ", j);
      for (; list; list=list->next)
        show_symentry(list,fp);
      fputs("\n", fp);
      }
    }
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
scopetab_t*
new_scopetab(scopetab_t *mom)
{
  int j;
  scopetab_t *that = malloc(sizeof(scopetab_t));

  if (that)
    {
    that->htab = NULL;
    that->nchild = 0;
    that->size = INIT_CHILD_SIZE;
    that->children = malloc( sizeof(scopetab_t*) * that->size );

    if (!that->children)
      {
      free(that->children);
      free(that);
      return NULL;
      }

    for (j=0; j < that->size; j++)
      that->children[j] = NULL;

    that->nsyms = 0;
    that->parent = mom;
    if (mom)
      that->level = mom->level + 1;
    else
      that->level = EXTERN_SCOPE;
    }

  return that;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
void
free_scopetab(scopetab_t *that)
{
  if (that)
    {
    free_hashtab(that->htab);
    free(that->children);
    free(that);
    }
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
scopetab_lookup(scopetab_t *that, str_t *nme)
{
  symentry_t *ret = NULL;

  if (that && that->htab)
    ret = hashtab_lookup(that->htab, nme);

  return ret;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
scopetab_find(scopetab_t *that, str_t *nme)
{
  symentry_t *ret = NULL;

  if (that)
    {
#ifdef  PRINT_LEVEL
  fprintf(stdout, "Looking for '%s' in level %d (<entry>)\n",
              nme->str, that->level);
#endif

    if (that->htab)
      ret = hashtab_lookup(that->htab,nme);

    if (!ret)
      return scopetab_find(that->parent,nme);

#ifdef  PRINT_LEVEL
  fprintf(stdout, "Looking for '%s' in level %d (%s)\n",
              nme->str, that->level, (ret ? "found": "NOT found"));
#endif
    }

  return ret;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
scopetab_insert(scopetab_t *that, symentry_t *entry)
{
#ifdef  PRINT_LEVEL
  fprintf(stdout, "Inserting '%s' in level %d\n",
              entry->nme->str, that->level);
#endif
  if (! that->htab)
    {
    that->htab = new_hashtab();
    if (!that->htab)
      return 0;
    }

  return hashtab_insert(that->htab,entry);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
static void
po_deltabs(scopetab_t *that)
{
  int j;

  if (that)
    {
    for (j=0; j < that->nchild; j++)
      po_deltabs(that->children[j]);

    free_scopetab(that);
    }
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
static int
child_insert(scopetab_t *mom, scopetab_t *kid)
{
  int j;

  if (mom->nchild >= mom->size)
    {
    scopetab_t **oldkids = mom->children;
    mom->size += mom->size;
    mom->children = malloc( sizeof(scopetab_t*) * mom->size );

    if (!mom->children)
      return 0;

    for (j=0; j < mom->nchild; j++)
      mom->children[j] = oldkids[j];
    }

  mom->children[mom->nchild] = kid;
  (mom->nchild)++;

  return 1;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
static void
show_scopetab(scopetab_t *that, FILE *fp)
{
  int j;
  fprintf(fp,"\nScopeTab (%p): (parent: %p)\n", that, that->parent);

  fprintf(fp, "level: %d  nsyms: %d  nchild: %d\n",
          that->level, that->nsyms, that->nchild );

  if (that->htab)
    show_hashtab(that->htab, fp);
  else
    fputs("HashTab: NULL\n", fp);

  for (j=0; j < that->nchild; j++)
    show_scopetab(that->children[j], fp);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symtab_t*
new_symtab(void)
{
  symtab_t *that = malloc(sizeof(symtab_t));

  if (that)
    {
    that->root = new_scopetab(NULL);
    that->clevel = EXTERN_SCOPE;
    that->current = that->root;

    if (!that->root)
      {
      free(that);
      that = NULL;
      }
    }

  return that;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
void
free_symtab(symtab_t *that)
{
  if (that)
    {
    /* delete all scopetab's (post-order traversal). */ 
    po_deltabs(that->root);
    free(that);
    }
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
symtab_lookup(symtab_t *that, str_t *nme)
{
  symentry_t *ret = NULL;

  if (that->current)
    ret = scopetab_find(that->current,nme);

  return ret;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
symtab_lookup_at(symtab_t *that, str_t *nme, int level)
{
  scopetab_t *scp = that->current;

  while (scp && scp->level < level)
    scp = scp->parent;

  return scopetab_find(scp,nme);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
symentry_t*
symtab_insert(symtab_t *that, symentry_t *entry)
{
  while (that->clevel > that->current->level)
    {
    scopetab_t *child = new_scopetab(that->current);

    if (!child || !child_insert(that->current,child))
      return NULL;

    that->current = child;
    }

  return scopetab_insert(that->current,entry);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
int
symtab_insert_at(symtab_t *that, symentry_t *entry, int level)
{
  scopetab_t *scp;

#ifdef  PRINT_LEVEL
  fprintf(stderr, "scope level %d\n", that->current->level);
  fprintf(stderr, "Current level %d\n", that->clevel);
  fprintf(stderr, "request level %d\n", level);
#endif

  while ((that->clevel > that->current->level)
      && (that->clevel >= level))
    {
    scopetab_t *child = new_scopetab(that->current);

    if (!child || !child_insert(that->current,child))
      return 0;

    that->current = child;
    }

  scp = that->current;
  while (scp && (scp->level > level))
    scp = scp->parent;

  if (scp)
    return (scopetab_insert(scp,entry) != NULL);
  else
    return 0;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
int
st_enter_scope(symtab_t *that)
{
  return ++(that->clevel);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
void
st_exit_scope(symtab_t *that)
{
  (that->clevel)--;
  if (that->current->level > that->clevel)
    that->current = that->current->parent;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
void
show_symtab(symtab_t *that, FILE *fp)
{
  fputs("\n-------------\nSymbol Table:\n", fp);
 
  fprintf(fp, "current level: %d  (%p)  parent: (%p)\n",
               that->clevel, that->current, that->current->parent);
  show_scopetab(that->root, fp);

  fputs("\n-------------\n", fp);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
context_t*
new_context(void)
{
  context_t *that = malloc( sizeof(context_t) );

  if (that)
    {
    that->labels = new_symtab();
    that->tags   = new_symtab();
    that->syms   = new_symtab();

    if (!that->labels || !that->tags || !that->syms)
      {
      free_symtab(that->labels);
      free_symtab(that->tags);
      free_symtab(that->syms);
      free(that);
      that = NULL;
      }
    }

  return that;
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
void
free_context(context_t *that)
{
  free_symtab(that->labels);
  free_symtab(that->tags);
  free_symtab(that->syms);

  free(that);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
int
enter_scope(context_t *that)
{
#ifdef  PRINT_LEVEL
  fprintf(stdout, "Entering Scope: %d\n", that->syms->clevel + 1);
#endif
  st_enter_scope(that->labels);
  st_enter_scope(that->tags);
  return st_enter_scope(that->syms);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
void
exit_scope(context_t *that)
{
#ifdef  PRINT_LEVEL
  /*  fprintf(stdout, "Exiting Scope: %d\n", that->syms->clevel);  */
#endif
  st_exit_scope(that->labels);
  st_exit_scope(that->tags);
  st_exit_scope(that->syms);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
void
exit_scopes(context_t *that, int newlev)
{
  if (newlev < EXTERN_SCOPE)
    newlev = EXTERN_SCOPE;

  while (newlev < that->syms->current->level)
    exit_scope(that);
}

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */
