/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
    o+
    o+     File:         treestk.c
    o+
    o+     Programmer:   Shaun Flisakowski
    o+     Date:         Apr 7, 1995
    o+
    o+     Stacks of trees being parsed
    o+         (to parse included files, as soon as they're seen)
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#include <stdio.h>

#include "globals.h"
#include "treestk.h"

char what_version[] = "@(#) Ctree Version 0.09";

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */

extern FILE *yyin;

extern int yyparse(void);
extern YY_BUFFER_STATE yy_create_buffer( FILE *file, int size );
extern void            yy_switch_to_buffer( YY_BUFFER_STATE buff );
extern void            yy_delete_buffer( YY_BUFFER_STATE buff );

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
Stk_Item  *new_stk_item( FILE *fp, char *fname )
{
    Stk_Item *stk_item;

    if ((stk_item = malloc(STK_ITEM_SZE)) == NULL){
        return((Stk_Item *) NULL);
    }

    if ((stk_item->filename = malloc(strlen(fname)+1)) == NULL){
        free(stk_item);
        return((Stk_Item *) NULL);
    }
    strcpy(stk_item->filename, fname);

    if ((stk_item->yybuff = yy_create_buffer(fp, YYBUFF_SIZE )) == NULL){
        free(stk_item->filename);
        free(stk_item);
        return((Stk_Item *) NULL);
    }

    if ((stk_item->node_heap  = CreateHeap(MX_NODE_SZE, 0)) == NULL){
        free(stk_item->filename);
        yy_delete_buffer( stk_item->yybuff );
        free(stk_item);
        return((Stk_Item *) NULL);
    }

    stk_item->yyin     = fp;

    stk_item->yylineno = 1;
    stk_item->yycolno  = 0;
    stk_item->yynxtcol = 0;

    stk_item->parse_tree = (treenode *) NULL;

    stk_item->next = (Stk_Item *) NULL;

    return(stk_item);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
void delete_stk_item( Stk_Item *stk_item )
{
    if (! stk_item)
        return;

    if (stk_item->yyin)
        fclose(stk_item->yyin);

    if (stk_item->parse_tree)
        free_tree(stk_item->parse_tree);

    if (stk_item->filename)
        free(stk_item->filename);

    if (stk_item->yybuff)
        yy_delete_buffer(stk_item->yybuff);

    if (stk_item->node_heap)
        DestroyHeap(stk_item->node_heap);

    free(stk_item);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
TreeStack *new_treestk(void)
{
    TreeStack    *treestk;

    if ((treestk = malloc(TREESTK_SZE)) == NULL){
        return NULL;
    }

    treestk->top    = NULL;
    treestk->bottom = NULL;

    treestk->contxt = NULL;
    return treestk;
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
void delete_treestk(TreeStack *treestk)
{
    if (! treestk)
        return;

    while(! is_empty(treestk))
        delete_stk_item(pop(treestk));

    free(treestk);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
void push(TreeStack *treestk, Stk_Item *stk_item )
{
    if (! treestk || ! stk_item)
        return;

    stk_item->next = treestk->top;

    if (! treestk->top)
        treestk->bottom = stk_item;

    treestk->top = stk_item;
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
Stk_Item *pop(TreeStack *treestk)
{
    Stk_Item *stk_item, *nxt_item;

    if (is_empty(treestk))
        return((Stk_Item *) NULL);

    stk_item = treestk->top;
    nxt_item = treestk->top->next;

    if (! nxt_item)
        treestk->bottom = (Stk_Item *) NULL;

    treestk->top = nxt_item;

    return(stk_item);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
void put_on_bottom(TreeStack *treestk, Stk_Item *stk_item)
{
    if (! treestk || ! stk_item)
        return;

    if (treestk->bottom)
        treestk->bottom->next = stk_item;

    if (! treestk->top)
        treestk->top = stk_item;

    treestk->bottom = stk_item;
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
int is_empty(TreeStack *treestk)
{
    if (! treestk)
        return(1);

    return(treestk->top == NULL);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
Stk_Item *top_of_stack(TreeStack *treestk)
{
    if (is_empty(treestk))
        return((Stk_Item *) NULL);
    else
        return(treestk->top);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
FILE *top_file(TreeStack *treestk)
{
    if (is_empty(treestk))
        return((FILE *) NULL);
    else
        return(treestk->top->yyin);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
char *top_filename(TreeStack *treestk)
{
    if (is_empty(treestk))
        return((char *) NULL);
    else
        return(treestk->top->filename);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
void reset_position(TreeStack *treestk)
{
    if ( !(Parse_TOS = top_of_stack(treestk)))
        return;

    yy_switch_to_buffer(Parse_TOS->yybuff);
    yyin = top_file(treestk);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
int tree_parse(TreeStack *treestk, int parse_all)
{
    int cnt = 0;

    if (is_empty(treestk))
        return(0);

    do {
    
        while(yyparse())
            ;

        cnt++;
        get_next_file(treestk);

        if (is_empty(treestk))
            break;

    } while (parse_all);

    return(cnt);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
void handle_new_file(TreeStack *treestk, FILE *fp, char *fname)
{
    Stk_Item *stk_item;

    if ((stk_item = new_stk_item(fp, fname)) == NULL)
        return;

    push(treestk, stk_item);
    reset_position(treestk);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
int  get_next_file(TreeStack *treestk)
{
    if (is_empty(treestk)){
        Parse_TOS = (Stk_Item *) NULL;
        return(0);
    }

    if (DoneStack)
        push(DoneStack, pop(treestk));
    else {
        fputs("DoneStack was NULL.\n", stdout);
        delete_stk_item(pop(treestk));
    }

    reset_position(treestk);

    if (is_empty(treestk))
        return(0);

    return(1);
}

/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
void abort_file(TreeStack *treestk)
{
    if (is_empty(treestk)){
        Parse_TOS = (Stk_Item *) NULL;
        return;
    }

    delete_stk_item(pop(treestk));
    reset_position(treestk);
}
    
/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
#ifdef    DEBUG
void show_stack(TreeStack *treestk)
{
    Stk_Item *tmp;

    fputs("-----Showing Stack: \n",stderr);
    if (treestk && treestk->top){

        fputs("Starting at top (current item being Parsed).\n",stderr);
        for (tmp=treestk->top; tmp; tmp=tmp->next){
            if (tmp->filename)
                fprintf(stderr, "%s:\t", tmp->filename);
            else
                fputs("--no name--:\t", stderr);
            fprintf(stderr, "Line: %d  Column: %d\n", tmp->yylineno, 
                    tmp->yycolno );
        }

    } else
        fputs("Stack is Empty.\n",stderr);

    fputs("-----Done Showing Stack \n",stderr);
}

#endif
/* o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o */
