#include    <string.h>
#include    <malloc.h>

#include    "prnttree.h"
#include	"CodeGenerator.h"
#include    "token.h"
#include    "gram_parser.cpp.h"
#include    "symtab.h"
#include    "dsm_extension.h"
#include    "globals.h"

int  ptline, ptpos;

#ifdef    DEBUG
#define    FPUTS(X,Y)     do { if (debug_print_on) fputs((X),(Y)); } while(0)
#else
#define    FPUTS(X,Y)    /* Nop */
#endif

int fopt_mode=0;
int fdepth = 0;
int fcount = 0;
int thisstate =0;
typedef struct state_stack {
    int state;
    struct state_stack *next;
} state_stack;


state_stack *ststack= (state_stack *)NULL;

int debug_print_on;

/*  ###############################################################  */
static int decl_cnt = 0;
static int just_left_blk = 0;
static int enum_list_cnt = 0;

static void show_if(if_node *ifn, int tabs, FILE *fp);
static void show_for(for_node *forn, int tabs, FILE *fp);
static void show_any(treenode *child, int tabs, FILE *fp);
static void show_node(treenode *node, int tabs, FILE *fp);

/*  ###############################################################  */
int is_function(treenode *node)
{
    if (node->hdr.which == LEAF_T)
    {
        leafnode *leaf = (leafnode*) node;

        if ((leaf->hdr.type == TN_IDENT) && leaf->syment)
        {
            /* Need to check symbol table for the entry. */
            treenode *def = leaf->syment->node;

            if (def)
            {
                return (def->hdr.type == TN_FUNC_DEF);
            }
        } 
    }

    return 0;
}

/*  ###############################################################  */
/*  indent - 2 spaces per level */
void indent(int levels, FILE *fp)
{
    int j;
#ifdef    DEBUG
    if (debug_print_on && (levels != 0))
      fprintf(fp,"\n<indent %d>",levels);
    else
#endif
    for (j=levels; j > 0; j--)
      fputs("  ",fp);
}

/*  ###############################################################  */
/* Print a char, converting chars to escape sequences. */
void fputs_metachr(char c, int in_str, FILE *fp)
{
    switch (c) {
      case '\'':
        if (in_str) 
          fputs("'",fp);
        else
          fputs("\\'",fp);
        break;
      case '"':
        if (in_str) 
          fputs("\\\"",fp);
        else
          fputs("\"",fp);
        break;
      case '\0':
        fputs("\\0",fp);
        break;
      case '\\':
        fputs("\\\\",fp);
        break;
      case '\n':
        fputs("\\n",fp);
        break;
      case '\t':
        fputs("\\t",fp);
        break;
      case '\r':
        fputs("\\r",fp);
        break;
      case '\f':
        fputs("\\f",fp);
        break;
      case '\b':
        fputs("\\b",fp);
        break;
      case '\v':
        fputs("\\v",fp);
        break;
      case '\a':
        fputs("\\a",fp);
        break;
      default:
        fputc(c,fp);
    }
}

/*  ###############################################################  */
/* Print a string, converting chars to escape sequences. */
void fputs_metastr(char *str, FILE *fp)
{
  while (*str) {
    fputs_metachr(*str,1,fp);
    str++;
  }
}

/*  ###############################################################  */
char* print_ptr(void *ptr)
{
    static char buf[32];

#if defined(__STDC__) || defined(__cplusplus)
    sprintf( buf, "%p", ptr );
#else
    sprintf( buf, "0x%0x", (unsigned int) ptr );
#endif

    return buf;
}

treenode *lastfor=NULL,*currfor=NULL;
int forflag=0;
/*  ###############################################################  */
treenode *new_make_node(tn_t type, context_t *contxt)
{
    treenode *tmp_node;

    tmp_node = (treenode *) malloc(sizeof(treenode));

    if (tmp_node == NULL)
    {
        fputs("Error: Out of memory in new_make_node.\n",stderr);
        exit(1);
    }
    tmp_node->hdr.which = NODE_T;
    tmp_node->hdr.type  = type;

    tmp_node->lnode = (treenode *) NULL;
    tmp_node->rnode = (treenode *) NULL;

        tmp_node->hdr.c_contxt = malloc(sizeof(context_t));
        tmp_node->hdr.c_contxt->labels = malloc(sizeof(symtab_t));
        *(tmp_node->hdr.c_contxt->labels) = *(contxt->labels);
        tmp_node->hdr.c_contxt->syms = malloc(sizeof(symtab_t));
        *(tmp_node->hdr.c_contxt->syms) = *(contxt->syms);
        tmp_node->hdr.c_contxt->tags = malloc(sizeof(symtab_t));
        *(tmp_node->hdr.c_contxt->tags) = *(contxt->tags);

    return tmp_node;
}

void opt_try_tree(treenode *root)
{
    for_node *tfr;

    if_node  *ifn;
    for_node *forn;
    treenode *t;
    //switch (root->hdr.which){
    //case LEAF_T: printf(" LEAF_T %d\n",root->hdr.which); break;
    //case NODE_T: printf(" NODE_T %d\n",root->hdr.which); break;
    //case IF_T: printf(" IF_T %d\n",root->hdr.which); break;
    //case FOR_T: printf(" FOR_T %d\n",root->hdr.which); break;
    //case NONE_T: printf(" NONE_T %d\n",root->hdr.which); break;
    //default:
         //printf(" UNKNOWN_T %d\n",root->hdr.which); break;
    //}
    if (!root)
        return;


    switch (root->hdr.which){
    case LEAF_T:
        break;
    case NODE_T:
        if(root->lnode != NULL) opt_try_tree(root->lnode);
        if(root->rnode != NULL) opt_try_tree(root->rnode);
        break;

    case IF_T:
        ifn = (if_node *) root;
        if(ifn->cond != NULL) opt_try_tree(ifn->cond);
        if(ifn->then_n != NULL) opt_try_tree(ifn->then_n);
        if(ifn->else_n != NULL) opt_try_tree(ifn->else_n);
        break;

    case FOR_T:
        forn = (for_node *) root;
        lastfor = currfor;
        currfor = root;

        if(forn->init != NULL) opt_try_tree(forn->init);
        if(forn->test != NULL) opt_try_tree(forn->test);
        if(forn->incr != NULL) opt_try_tree(forn->incr);
            forflag = 0;
        if(forn->stemnt != NULL) opt_try_tree(forn->stemnt);
            if(forflag == 0 && lastfor != NULL){
                    tfr = (for_node *) lastfor;
                    if(tfr->test != NULL){
                             //printf("inside forflag then %d %d %d\n",tfr->test,tfr->test->hdr.type,tfr->test->hdr.c_contxt);
                             t = new_make_node(tfr->test->hdr.type, root->hdr.c_contxt);
                    } else { 
                       t = new_make_node(root->hdr.type, root->hdr.c_contxt);
                    }
                    t->hdr.type = TN_EXPR;
                    t->hdr.tok = OR;
                    t->lnode = tfr->test;
                    t->rnode = forn->test;
                    tfr->test = t;
            }
            forflag = 1;
        break;
    case NONE_T:
        break ;
    default:
         printf(" UNKNOWN_T %d\n",root->hdr.which); 
        break ;
    }
    return;
}
/*  ###############################################################  */
treenode *add_initstate(context_t *contxt)
{
treenode *tass;
leafnode *ln, *rn;
    // the assignment state = newstate;
    tass = new_make_node(TN_ASSIGN, contxt);
    tass->hdr.which = NODE_T;
    tass->hdr.tok  = EQ;
    tass->hdr.type  = TN_ASSIGN;
    ln =  (leafnode *) new_make_node(TN_IDENT,contxt);
    ln->data.sval = (str_t *)malloc(sizeof(str_t));
    ln->data.sval->str = (char *)malloc(40);
    strcpy(ln->data.sval->str,"int s_tate");
    ln->hdr.which = LEAF_T;
    ln->hdr.type  = TN_IDENT;
    ln->hdr.tok  = IDENT;
    tass->lnode = (treenode *) ln;
    rn = (leafnode *) new_make_node(TN_INT,contxt);
    rn->data.ival = 0;
    rn->hdr.which = LEAF_T;
    rn->hdr.type  = TN_INT;
    rn->hdr.tok  = INUM;
    tass->rnode = (treenode *) rn;
    return(tass);
}

treenode *add_state_is(context_t *contxt, int newstate)
{
treenode *tass;
leafnode *ln, *rn;
    // the assignment state = newstate;
    tass = new_make_node(TN_ASSIGN, contxt);
    tass->hdr.which = NODE_T;
    tass->hdr.tok  = EQ;
    tass->hdr.type  = TN_ASSIGN;
    ln =  (leafnode *) new_make_node(TN_IDENT,contxt);
    ln->data.sval = (str_t *)malloc(sizeof(str_t));
    ln->data.sval->str = (char *)malloc(40);
    strcpy(ln->data.sval->str,"s_tate");
    ln->hdr.which = LEAF_T;
    ln->hdr.type  = TN_IDENT;
    ln->hdr.tok  = IDENT;
    tass->lnode = (treenode *) ln;
    rn = (leafnode *) new_make_node(TN_INT,contxt);
    rn->data.ival = newstate;
    rn->hdr.which = LEAF_T;
    rn->hdr.type  = TN_INT;
    rn->hdr.tok  = INUM;
    tass->rnode = (treenode *) rn;
    return(tass);
}

treenode *cond_state(context_t *contxt, int st)
{
	treenode *cstate;
	leafnode  *ln,*rn;
    cstate = new_make_node(TN_EXPR, contxt);
    cstate->hdr.which = NODE_T;
    cstate->hdr.tok  = EQUAL;

    ln =  (leafnode *) new_make_node(TN_IDENT,contxt);
    ln->data.sval = (str_t *)malloc(sizeof(str_t));
    ln->data.sval->str = (char *)malloc(40);
    strcpy(ln->data.sval->str,"s_tate");
    ln->hdr.which = LEAF_T;
    ln->hdr.type  = TN_IDENT;
    ln->hdr.tok  = IDENT;
    cstate->lnode = (treenode *) ln;

    rn = (leafnode *) new_make_node(TN_INT,contxt);
    rn->data.ival = st;
    rn->hdr.which = LEAF_T;
    rn->hdr.type  = TN_INT;
    rn->hdr.tok  = INUM;
    cstate->rnode = (treenode *) rn;
    return(cstate);
}

if_node *add_if(context_t *contxt, treenode *root, int st)
{
if_node *ifn;
leafnode *ln,*rn,*llp;

    // if(state == fcount) root
    ifn = (if_node *)  new_make_node(IF_T, contxt);
    ifn->hdr.which = IF_T;
    ifn->hdr.type  = TN_IF;
    ifn->then_n = root;
    ifn->else_n = (treenode *) NULL;
    ifn->cond = cond_state(contxt,st);
    return ifn;
}

treenode *add_block(context_t *contxt, treenode *st1, treenode *st2, treenode *st3)
// the block { st1; st2; st3; }
{
treenode *sblock,*slist,*klist;
if(st3 == NULL)
{
    slist = new_make_node(TN_STEMNT_LIST, contxt);
    slist->hdr.which = NODE_T;
    slist->hdr.tok  = SEMICOLON;
    slist->hdr.type  = TN_STEMNT_LIST;
    slist->lnode = (treenode *) st1;
    slist->rnode = (treenode *) st2;
} else {
    klist = new_make_node(TN_STEMNT_LIST, contxt);
    klist->hdr.which = NODE_T;
    klist->hdr.tok  = SEMICOLON;
    klist->hdr.type  = TN_STEMNT_LIST;
    klist->lnode = (treenode *) st2;
    klist->rnode = (treenode *) st3;
    slist = new_make_node(TN_STEMNT_LIST, contxt);
    slist->hdr.which = NODE_T;
    slist->hdr.tok  = SEMICOLON;
    slist->hdr.type  = TN_STEMNT_LIST;
    slist->lnode = (treenode *) st1;
    slist->rnode = (treenode *) klist;

}
    sblock = new_make_node(TN_BLOCK, contxt);
    sblock->hdr.which = NODE_T;
    sblock->hdr.tok  = SEMICOLON;
    sblock->hdr.type  = TN_BLOCK;
    sblock->lnode = (treenode *) NULL;
    sblock->rnode = (treenode *) slist;
return(sblock);
}

treenode *add_while(context_t *contxt, treenode *test, treenode *stemnt,
                 int thisst, int nextst, int prevst)
// building:
//{ if(state == N1) { state = N2; j=0; }
//        if(state == N2) y=y*A[j];
// if(state == N2) if( j < A[i]) {state = N2; j++;  } else state = N1; }
{
if_node *ifn,*ifa,*ifb;
leafnode *ln,*rn,*llp;
treenode  *tass,*slist,*s1,*s2;
treenode *flatf,*fexit;

    // the assignment state = N2
    tass = add_state_is(contxt, thisst);
    //if(state == N1) { state = N2; j=0; }
    ifb = (if_node *)  new_make_node(IF_T, contxt);
    ifb->hdr.which = IF_T;
    ifb->hdr.type  = TN_IF;
    ifb->cond = cond_state(contxt, prevst);
    //the list { state = N2;}
    ifb->then_n = tass;
    ifb->else_n = (treenode *) NULL;


    // if( j < A[i]) {state = N2; j++;  } else state = N1; 
    ifa = (if_node *)  new_make_node(IF_T, contxt);
    ifa->hdr.which = IF_T;
    ifa->hdr.type  = TN_IF;
    ifa->cond = test;
    s1 = add_state_is(contxt, thisst);
    //the block { state = N2; j++; }
    //ifa->then_n = add_block(contxt,s1,incr,NULL);
    ifa->then_n = NULL;
    ifa->else_n = (treenode *) add_state_is(contxt, nextst);

// { if(state == N2) if( j < A[i]) {state = N2; j++;  } else state = N1; }
    ifn = (if_node *)  new_make_node(IF_T, contxt);
    ifn->hdr.which = IF_T;
    ifn->hdr.type  = TN_IF;
    ifn->cond = cond_state(contxt, thisst);
    ifn->then_n = (treenode *) ifa;
    ifn->else_n = (treenode *) NULL;

    flatf = add_block(contxt, (treenode*)ifb, (treenode*)stemnt, (treenode*)ifn);
    return flatf;
}

treenode *add_for(context_t *contxt, treenode *init, treenode *test, treenode *incr,treenode *stemnt,
                 int thisst, int nextst, int prevst)
// building:
//{ if(state == N1) { state = N2; j=0; }
//        if(state == N2) y=y*A[j];
// if(state == N2) if( j < A[i]) {state = N2; j++;  } else state = N1; }
{
if_node *ifn,*ifa,*ifb;
leafnode *ln,*rn,*llp;
treenode  *tass,*slist,*s1,*s2;
treenode *flatf,*fexit;

    // the assignment state = N2
    tass = add_state_is(contxt, thisst);
    //if(state == N1) { state = N2; j=0; }
    ifb = (if_node *)  new_make_node(IF_T, contxt);
    ifb->hdr.which = IF_T;
    ifb->hdr.type  = TN_IF;
    ifb->cond = cond_state(contxt, prevst);
    //the list { state = N2; j=0; }
    ifb->then_n = add_block(contxt,tass,init,NULL);
    ifb->else_n = (treenode *) NULL;


    // if( j < A[i]) {state = N2; j++;  } else state = N1; 
    ifa = (if_node *)  new_make_node(IF_T, contxt);
    ifa->hdr.which = IF_T;
    ifa->hdr.type  = TN_IF;
    ifa->cond = test;
    s1 = add_state_is(contxt, thisst);
    //the block { state = N2; j++; }
    //ifa->then_n = add_block(contxt,s1,incr,NULL);
    ifa->then_n = incr;
    ifa->else_n = (treenode *) add_state_is(contxt, nextst);

// { if(state == N2) if( j < A[i]) {state = N2; j++;  } else state = N1; }
    ifn = (if_node *)  new_make_node(IF_T, contxt);
    ifn->hdr.which = IF_T;
    ifn->hdr.type  = TN_IF;
    ifn->cond = cond_state(contxt, thisst);
    ifn->then_n = (treenode *) ifa;
    ifn->else_n = (treenode *) NULL;

    flatf = add_block(contxt, (treenode*)ifb, (treenode*)stemnt, (treenode*)ifn);
    return flatf;
}

treenode *add_firstfor(context_t *contxt, treenode *init, treenode *test, treenode *incr,treenode *stemnt, 
                 int thisst, int nextst, int prevst)
{
treenode *tass,*slist,*flatf;
if_node *ifb;
    // the assignment state = N2
    //tass = add_state_is(contxt, prevst);
    //the list { state = N2; j=0; }
    //slist = add_block(contxt,tass,incr,NULL);
    //if(state == N2) { state = N1; i++; }
    ifb = (if_node *)  new_make_node(IF_T, contxt);
    ifb->hdr.which = IF_T;
    ifb->hdr.type  = TN_IF;
    ifb->cond = cond_state(contxt, thisst);
    ifb->then_n = incr;
    ifb->else_n = (treenode *) NULL;

    //{ stemnt; if(state == N2) { state = N1; i++; } }
    flatf = add_block(contxt, (treenode*)stemnt, (treenode*)ifb,NULL);
	return(flatf);
}

treenode *add_thenelse(context_t *contxt,treenode *cond, treenode *then_n, treenode *else_n, 
             int thenst, int elsest, int prevst)
{
treenode *then_part,*else_part,*flatf;
if_node *ifa,*ifb,*ifc;
    ifc = (if_node *)  new_make_node(IF_T, contxt);
    ifc->hdr.which = IF_T;
    ifc->hdr.type  = TN_IF;
    ifc->cond = cond_state(contxt, (int)cond);
    ifc->then_n = add_state_is(contxt, thenst);
    if(elsest != -1){ ifc->else_n = add_state_is(contxt, elsest);} else ifc->else_n = NULL; 
    //if(state == thenst) { then_n; state = prevst }
    ifa = (if_node *)  new_make_node(IF_T, contxt);
    ifa->hdr.which = IF_T;
    ifa->hdr.type  = TN_IF;
    ifa->cond = cond_state(contxt, thenst);
    ifa->then_n = add_state_is(contxt, prevst);
    ifa->else_n = (treenode *) NULL;
    then_part = add_block(contxt, (treenode*)then_n, (treenode*)ifa,NULL);
    if(elsest != -1) {
    //if(state == thenst) { then_n; state = prevst }
    ifb = (if_node *)  new_make_node(IF_T, contxt);
    ifb->hdr.which = IF_T;
    ifb->hdr.type  = TN_IF;
    ifb->cond = cond_state(contxt, elsest);
    ifb->then_n = add_state_is(contxt, prevst);
    ifb->else_n = (treenode *) NULL;
    else_part = add_block(contxt, (treenode*)else_n, (treenode*)ifb,NULL);
    flatf = add_block(contxt, (treenode*)ifc, (treenode*)then_part, (treenode*)else_part);
    } else flatf = add_block(contxt, (treenode*)ifc, (treenode*)then_part,NULL);
	return(flatf);
}

int  flat_recur(treenode *root,treenode **parrent)
{
    if_node  *ifn;
    for_node *forn;
    leafnode *leaf;

    if (!root)
        return(0);

    just_left_blk = 0;

    switch (root->hdr.which){
   
    default:
    case NONE_T:
        return 0;

    case LEAF_T:
        leaf = (leafnode *) root;
        switch (leaf->hdr.type) {

        case TN_LABEL:
            break;

        case TN_IDENT:
            break;

        case TN_COMMENT:
            break;

        case TN_ELLIPSIS:
            break;

        case TN_STRING:
            break;

        case TN_TYPE:
            break;

        case TN_INT:
            break;

        case TN_REAL:
            break;

        default:
            break;
        }
        break;

    case IF_T:
        ifn = (if_node *) root;
        switch (ifn->hdr.type) {

        case TN_IF:
            if(fopt_mode == 1) 
            { int then_state=-1, else_state=-1, thisst;
              if(ifn->then_n != NULL && ifn->else_n != NULL)
              { 
               //push then state
               thisst = ststack-> state;
               state_stack *stp;
               stp = (state_stack *) malloc(sizeof(state_stack));
               if(stp == NULL) printf("stp allocation error\n");
               stp->state = fcount;
               stp->next = ststack;
               ststack = stp;
               then_state = fcount;
               fcount++; 
               stp = (state_stack *) malloc(sizeof(state_stack));
               if(stp == NULL) printf("stp allocation error\n");
               stp->state = fcount;
               stp->next = ststack;
               ststack = stp;
               else_state = fcount;
               fcount++; 
               fdepth++;
               flat_recur(ifn->then_n,&(ifn->then_n));
               flat_recur(ifn->else_n,&(ifn->else_n));
               if(ststack->next == NULL) printf("WHATTT ststate->next == NULL\n");
               *parrent = add_thenelse(ifn->hdr.c_contxt,ifn->cond, ifn->then_n, ifn->else_n, then_state, else_state, thisst); 

                   fdepth--;
              //pop the two states 
              if(ststack == NULL) printf("ERR STSTAE=NULL\n");
              stp = ststack;
              ststack= ststack->next;
              free(stp);
              if(ststack != NULL) thisstate = ststack->state; else { thisstate =0; fcount=0; }
              if(ststack == NULL) printf("ERR STSTAE=NULL\n");
              stp = ststack;
              ststack= ststack->next;
              free(stp);
              if(ststack != NULL) thisstate = ststack->state; else { thisstate =0; fcount=0; }
              }
              else if(ifn->then_n != NULL && ifn->else_n == NULL)
              {
               //push then state
               thisst = ststack-> state;
               state_stack *stp;
               stp = (state_stack *) malloc(sizeof(state_stack));
               if(stp == NULL) printf("stp allocation error\n");
               stp->state = fcount;
               stp->next = ststack;
               ststack = stp;
               then_state = fcount;
               fcount++; 
               flat_recur(ifn->then_n,&(ifn->then_n));
               if(ststack->next == NULL) printf("WHATTT ststate->next == NULL\n");
               *parrent = add_thenelse(root->hdr.c_contxt,ifn->cond, ifn->then_n, ifn->else_n, then_state, else_state, thisst); 

                   fdepth--;
              //pop the two states 
              if(ststack == NULL) printf("ERR STSTAE=NULL\n");
              stp = ststack;
              ststack= ststack->next;
              free(stp);
              if(ststack != NULL) thisstate = ststack->state; else { thisstate =0; fcount=0; }
              }

            } else {
            flat_recur(ifn->cond,&(ifn->cond));
            flat_recur(ifn->then_n,&(ifn->then_n));
            flat_recur(ifn->else_n,&(ifn->else_n));
            }
            return(0);

        case TN_COND_EXPR:
            flat_recur(ifn->cond,&(ifn->cond));
            flat_recur(ifn->then_n,&(ifn->then_n));
            flat_recur(ifn->else_n,&(ifn->else_n));
            break;

        default:
            break;
        }
        break;

    case FOR_T:
        forn = (for_node *) root;
        switch (forn->hdr.type) {

        case TN_FUNC_DEF:
            flat_recur(forn->init,&(forn->init));
            flat_recur(forn->test,&(forn->test));
            if (forn->test->hdr.which == LEAF_T)
            flat_recur(forn->incr,&(forn->incr));
            flat_recur(forn->stemnt,&(forn->stemnt));
            break;

        case TN_FOR:
            if(fopt_mode == 1) 
            {
               //push new state
               state_stack *stp;
               stp = (state_stack *) malloc(sizeof(state_stack));
               if(stp == NULL) printf("stp allocation error\n");
               stp->state = fcount;
               stp->next = ststack;
               ststack = stp;
               thisstate = fcount;
               fcount++; 
               if(ststack->next != NULL){
                   fdepth++;
                   flat_recur(forn->stemnt,&(forn->stemnt));
                   if(ststack->next == NULL) printf("WHATTT ststate->next == NULL\n");
                   *parrent = add_for(root->hdr.c_contxt, forn->init, forn->test, forn->incr,forn->stemnt,
                   ststack->state,ststack->next->state,ststack->next->state);
                   fdepth--;
               } else {
                   fdepth++;
                   flat_recur(forn->stemnt,&(forn->stemnt));
                   forn->stemnt = add_firstfor(root->hdr.c_contxt, forn->init, forn->test, forn->incr,forn->stemnt,
                   ststack->state,thisstate,thisstate);
                   forn->incr = NULL;
                   fdepth--;
              }
              //pop state
              if(ststack == NULL) printf("ERR STSTAE=NULL\n");
              stp = ststack;
              ststack= ststack->next;
              free(stp);
              if(ststack != NULL) thisstate = ststack->state; else { thisstate =0; fcount=0; }
            } else {
                   flat_recur(forn->init,&(forn->init));
                   flat_recur(forn->test,&(forn->test));
                   flat_recur(forn->incr,&(forn->incr));
                   flat_recur(forn->stemnt,&(forn->stemnt));
            }
            return 0;

        default:
            printf(" UNKNOWN \n");
            break;
        }
        break;

    case NODE_T:
        switch (root->hdr.type) {
			// start of Parc extension
	case TN_PARBLOCK:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
		break;
	case TN_PARBLOCK_EMPTY:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
		break;
	// end of Parc extension

        case TN_TRANS_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_FUNC_DECL:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_FUNC_CALL:
            /* Only true functions are printed without parens. */
            if(ststack != NULL) *parrent = (treenode*)add_if(root->hdr.c_contxt, root,ststack->state);
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_BLOCK:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            return(0);

        case TN_ARRAY_DECL:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_EXPR_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_NAME_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_ENUM_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_FIELD_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_PARAM_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_IDENT_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_TYPE_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_DECL:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_DECL_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_DECLS:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_STEMNT_LIST:
            flat_recur(root->lnode,&(root->lnode));
            if (root->rnode != NULL) {
                flat_recur(root->rnode,&(root->rnode));
                }
            break;

        case TN_STEMNT:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_COMP_DECL:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_BIT_FIELD:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_PNTR:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_TYPE_NME:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_INIT_LIST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_INIT_BLK:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_OBJ_DEF:
            leaf = (leafnode *) root;
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_OBJ_REF:
            leaf = (leafnode *) root;
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_CAST:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_JUMP:
            if (root->hdr.tok == FOPT)
            {
                if(fopt_mode == 0){ printf("FOPT SET\n"); fopt_mode = 1; fdepth=0; fcount=0;}
                *parrent = add_initstate(root->hdr.c_contxt);
            }
            if ((root->hdr.tok == RETURN) || (root->hdr.tok == GOTO))
            {
                flat_recur(root->lnode,&(root->lnode));
            }
            break;

        case TN_SWITCH:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_INDEX:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_DEREF:
            flat_recur(root->lnode,&(root->lnode));
            if (root->rnode && (root->rnode->hdr.type == TN_IDENT))
              flat_recur(root->rnode,&(root->rnode));
            else {
              flat_recur(root->rnode,&(root->rnode));
            }
            break;

        case TN_SELECT:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_ASSIGN:
           { leafnode *llp;
             llp = (leafnode *) root->lnode;
            if(ststack != NULL) *parrent = (treenode*)add_if(root->hdr.c_contxt, root,ststack->state);
            //printf(" ==> %s %d %d \n",toksym(root->hdr.tok,1),root->hdr.type,root->hdr.tok);
            //flat_recur(root->lnode,&(root->lnode));
            //flat_recur(root->rnode,&(root->rnode));
           }
            break;

        case TN_EXPR:
            switch (root->hdr.tok) {
              case CASE:
                flat_recur(root->lnode,&(root->lnode));
                flat_recur(root->rnode,&(root->rnode));
                break;

              case SIZEOF:
                flat_recur(root->lnode,&(root->lnode));
                flat_recur(root->rnode,&(root->rnode));
                break;

              case INCR:
              case DECR:
                if(ststack != NULL) *parrent = (treenode*)add_if(root->hdr.c_contxt, root,ststack->state);
                //flat_recur(root->lnode,&(root->lnode));
                //flat_recur(root->rnode,&(root->rnode));
                break;

              case B_AND:
                 if(root->lnode == NULL)
                  flat_recur(root->rnode,&(root->rnode));
                  break;

              default:
                flat_recur(root->lnode,&(root->lnode));
                flat_recur(root->rnode,&(root->rnode));
                break;
            }
            break;

        case TN_WHILE:
            if(fopt_mode == 1) 
            {
               //push new state
               state_stack *stp;
               stp = (state_stack *) malloc(sizeof(state_stack));
               if(stp == NULL) printf("stp allocation error\n");
               stp->state = fcount;
               stp->next = ststack;
               ststack = stp;
               thisstate = fcount;
               fcount++; 
                   fdepth++;
                   flat_recur(root->rnode,&(root->rnode));
                   printf("DOING FLAT WHILE\n");
                   if(ststack->next == NULL) printf("WHATTT ststate->next == NULL\n");
                   *parrent = add_while(root->hdr.c_contxt, root->lnode, root->rnode,
                   ststack->state,ststack->next->state,ststack->next->state);
                   fdepth--;
              //pop state
              if(ststack == NULL) printf("ERR STSTAE=NULL\n");
              stp = ststack;
              ststack= ststack->next;
              free(stp);
              if(ststack != NULL) thisstate = ststack->state; else { thisstate =0; fcount=0; }
            } else {
                     flat_recur(root->lnode,&(root->lnode));
                     flat_recur(root->rnode,&(root->rnode));
            }
            return(0);

        case TN_DOWHILE:
            flat_recur(root->rnode,&(root->rnode));
            flat_recur(root->lnode,&(root->lnode));
            break;

        case TN_LABEL:
            flat_recur(root->lnode,&(root->lnode));
            flat_recur(root->rnode,&(root->rnode));
            break;

        case TN_EMPTY:
        default:
            printf("ERR 0\n");
            return 0;
        }
        break;
    }

    return(1);
}

void flat_tree(treenode *root, treenode **parrent)
{
    leafnode *leaf;
    if_node  *ifn;
    for_node *forn;

    if (!root)
        return;

    switch (root->hdr.which){
    case LEAF_T: printf(" > LEAF_T %d\n",root->hdr.type); break;
    case NODE_T: printf(" > NODE_T %d\n",root->hdr.type); break;
    case IF_T: printf(" > IF_T %d\n",root->hdr.type); break;
    case FOR_T: printf(" > FOR_T %d\n",root->hdr.type); break;
    case NONE_T: printf(" > NONE_T %d\n",root->hdr.type); break;
    default:
         printf(" > UNKNOWN_T %d\n",root->hdr.which); break;
    }

    switch (root->hdr.which){
    case LEAF_T:
        return;
        break;
    case NODE_T:
      /*
        if(root->hdr.tok == TN_ASSIGN){
                printf("FOUND ASSIGN\n");
                *parrent = add_if(root->hdr.c_contxt, root,fdepth);
        }
      */
        if(root->lnode != NULL) flat_tree(root->lnode,&root);
        if(root->rnode != NULL) flat_tree(root->rnode,&root);
        return;
        break;

    case IF_T:
        ifn = (if_node *) root;
        if(ifn->cond != NULL) flat_tree(ifn->cond,&root);
        if(ifn->then_n != NULL) flat_tree(ifn->then_n,&root);
        if(ifn->else_n != NULL) flat_tree(ifn->else_n,&root);
        break;

    case FOR_T:
        forn = (for_node *) root;
        lastfor = currfor;
        currfor = root;

        if(forn->init != NULL) flat_tree(forn->init,&root);
        if(forn->test != NULL) flat_tree(forn->test,&root);
        if(forn->incr != NULL) flat_tree(forn->incr,&root);
        forflag = 1;
        return;
        break;
    default:
    case NONE_T:
         printf(" UNKNOWN_T %d\n",root->hdr.which); 
         return;
    }
}
/*  ###############################################################  */
int  print_recur(treenode *root, int level, FILE *fp)
{
    if_node  *ifn;
    for_node *forn;
    leafnode *leaf;

    if (!root)
        return(0);

    just_left_blk = 0;

    switch (root->hdr.which){
   
    default:
    case NONE_T:
        fputs("\nERROR: Node with no type.\n", fp);
        return 0;

    case LEAF_T:
        leaf = (leafnode *) root;
        switch (leaf->hdr.type) {

        case TN_LABEL:
            FPUTS("[TN_LABEL]", fp);
            if (leaf->hdr.tok == DEFLT)
              fputs("default",fp);
            else
              fputs(leaf->data.sval->str,fp);
            fputs(":\n",fp);
            FPUTS("{TN_LABEL}", fp);
            break;

        case TN_IDENT:
            FPUTS("[TN_IDENT]", fp);
            fputs(leaf->data.sval->str,fp);
            FPUTS("{TN_IDENT}", fp);
            break;

        case TN_COMMENT:
            fputs("\n",fp);
            fputs(leaf->data.str, fp);
            fputs("\n",fp);
            break;

        case TN_ELLIPSIS:
            FPUTS("[TN_ELLIPSIS]", fp);
            fputs("...",fp);
            FPUTS("{TN_ELLIPSIS}", fp);
            break;

        case TN_STRING:
            fputs("\"", fp);
            fputs_metastr(leaf->data.str,fp);
            fputs("\"", fp);
            break;

        case TN_TYPE:
            FPUTS("[TN_TYPE]", fp);
            if (leaf->hdr.tok != TYPEDEF_NAME)
              fputs(toksym(leaf->hdr.tok,1), fp);
            else {
              fputs(leaf->data.sval->str,fp);
              fputs(" ", fp);
            }
            FPUTS("{TN_TYPE}", fp);
            break;

        case TN_INT:
            if (leaf->hdr.tok == CHAR_CONST) {
              fputs("'",fp);
              fputs_metachr((char) leaf->data.ival, 0, fp);
              fputs("'",fp);
            } else
              fprintf(fp, "%d", leaf->data.ival);
            break;

        case TN_REAL:
            fprintf(fp, "%f", leaf->data.dval);
            break;

        default:
            fprintf(fp, "Unknown leaf value\n" );
            break;
        }
        break;

    case IF_T:
        ifn = (if_node *) root;
        switch (ifn->hdr.type) {

        case TN_IF:
            FPUTS("[TN_IF]", fp);
            fputs("if (", fp);
            print_recur(ifn->cond, level, fp);
            fputs(")", fp);
            print_recur(ifn->then_n, level+1, fp);
            if (ifn->else_n) {
                if (just_left_blk) {
                  indent(level,fp);
                  fputs("else\n", fp);
                } else {
                  fputs(";\n",fp);
                  indent(level,fp);
                  fputs("else\n", fp);
                }
                print_recur(ifn->else_n, level+1, fp);
            }
            FPUTS("{TN_IF}", fp);
            return(0);

        case TN_COND_EXPR:
            FPUTS("[TN_COND_EXPR]", fp);
            fputs("(", fp);
            print_recur(ifn->cond, level, fp);
            fputs(") ? (", fp);
            print_recur(ifn->then_n, level, fp);
            fputs(") : (", fp);
            print_recur(ifn->else_n, level, fp);
            fputs(")", fp);
            FPUTS("{TN_COND_EXPR}", fp);
            break;

        default:
            fprintf(fp, "Unknown type of if node.\n");
            break;
        }
        break;

    case FOR_T:
        forn = (for_node *) root;
        switch (forn->hdr.type) {

        case TN_FUNC_DEF:
            FPUTS("[TN_FUNC_DEF]", fp);
            print_recur(forn->init, level, fp);
            print_recur(forn->test, level, fp);
            if (forn->test->hdr.which == LEAF_T)
                fputs("()", fp);
            print_recur(forn->incr, level, fp);
            fputs("\n", fp);
            print_recur(forn->stemnt, level, fp);
            fputs("\n", fp);
            FPUTS("{TN_FUNC_DEF}", fp);
            break;

        case TN_FOR:
            FPUTS("[TN_FOR]", fp);
            fputs("for (", fp);
            print_recur(forn->init, level, fp);
            fputs("; ", fp);
            print_recur(forn->test, level, fp);
            fputs("; ", fp);
            print_recur(forn->incr, level, fp);
            fputs(")\n", fp);
            print_recur(forn->stemnt, level+1, fp);
            FPUTS("{TN_FOR}", fp);
            return 0;

        default:
            fprintf(fp, "Unknown type of for node.\n");
            break;
        }
        break;

    case NODE_T:
        switch (root->hdr.type) {
			// start of Parc extension
		case TN_PARBLOCK:
            FPUTS("[TN_PARBLOCK]", fp);
			fprintf(fp, "parblock\n");
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_PARBLOCK}", fp);
			break;
		case TN_PARBLOCK_EMPTY:
            FPUTS("[TN_PARBLOCK_EMPTY]", fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_PARBLOCK_EMPTY}", fp);
			break;
			// end of Parc extension

        case TN_TRANS_LIST:
            FPUTS("[TN_TRANS_LIST]", fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_TRANS_LIST}", fp);
            break;

        case TN_FUNC_DECL:
            FPUTS("[TN_FUNC_DECL]", fp);
            decl_cnt++;
            if (root->lnode && (root->lnode->hdr.type == TN_IDENT))
                print_recur(root->lnode, level, fp);
            else {
                fputs("(",fp);
                print_recur(root->lnode, level, fp);
                fputs(")",fp);
            }
            fputs("(",fp);
            print_recur(root->rnode, level, fp);
            fputs(")",fp);
            decl_cnt--;
            FPUTS("{TN_FUNC_DECL}", fp);
            break;

        case TN_FUNC_CALL:
            FPUTS("[TN_FUNC_CALL]", fp);

            /* Only true functions are printed without parens. */
            if (is_function(root->lnode))
            {
                print_recur(root->lnode, level, fp);
            }
            else
            {
                fputs("(", fp);
                print_recur(root->lnode, level, fp);
                fputs(")", fp);
            }

            fputs("(", fp);
            print_recur(root->rnode, level, fp);
            fputs(")", fp);
            FPUTS("{TN_FUNC_CALL}", fp);
            break;

        case TN_BLOCK:
            FPUTS("[TN_BLOCK]", fp);
            fputs("{\n", fp);
            print_recur(root->lnode, level+1, fp);
            print_recur(root->rnode, level+1, fp);
            indent(level,fp);
            fputs("}\n", fp);
            just_left_blk = 1;
            FPUTS("{TN_BLOCK}", fp);
            return(0);

        case TN_ARRAY_DECL:
            FPUTS("[TN_ARRAY_DECL]", fp);
            print_recur(root->lnode, level, fp);
            fputs("[", fp);
            print_recur(root->rnode, level, fp);
            fputs("]", fp);
            FPUTS("{TN_ARRAY_DECL}", fp);
            break;

        case TN_EXPR_LIST:
            FPUTS("[TN_EXPR_LIST]", fp);
            print_recur(root->lnode, level, fp);
            if (root->rnode)
              fputs(",", fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_EXPR_LIST}", fp);
            break;

        case TN_NAME_LIST:
            FPUTS("[TN_NAME_LIST]", fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_NAME_LIST}", fp);
            break;

        case TN_ENUM_LIST:
            FPUTS("[TN_ENUM_LIST]", fp);
            if (root->lnode
                  && (root->lnode->hdr.type != TN_ENUM_LIST))
              indent(level,fp);
            enum_list_cnt++;
            print_recur(root->lnode, level, fp);
            if (root->rnode)
              fputs(",\n",fp);
            indent(level,fp);
            print_recur(root->rnode, level, fp);
            if (--enum_list_cnt == 0)
              fputs("\n",fp);
            FPUTS("{TN_ENUM_LIST}", fp);
            break;

        case TN_FIELD_LIST:
            FPUTS("[TN_FIELD_LIST]", fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_FIELD_LIST}", fp);
            break;

        case TN_PARAM_LIST:
            FPUTS("[TN_PARAM_LIST]", fp);
            print_recur(root->lnode, level, fp);
            if (root->rnode)
              fputs(",",fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_PARAM_LIST}", fp);
            break;

        case TN_IDENT_LIST:
            FPUTS("[TN_IDENT_LIST]", fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_IDENT_LIST}", fp);
            break;

        case TN_TYPE_LIST:
            FPUTS("[TN_TYPE_LIST]", fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_TYPE_LIST}", fp);
            break;

        case TN_DECL:
            FPUTS("[TN_DECL]", fp);
//            if (decl_cnt == 0)
//              indent(level,fp);
//            decl_cnt++;
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
//            if (--decl_cnt == 0)
//              fputs(";\n",fp);
            FPUTS("{TN_DECL}", fp);
            break;

        case TN_DECL_LIST:
            FPUTS("[TN_DECL_LIST]", fp);
            print_recur(root->lnode, level, fp);
            if ((root->rnode && (root->rnode->hdr.type == TN_IDENT))
                 || (root->rnode->lnode
                     && ((root->rnode->lnode->hdr.type == TN_IDENT)
                         || (root->rnode->lnode->hdr.type == TN_PNTR))) )
              fputs(",",fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_DECL_LIST}", fp);
            break;

        case TN_DECLS:
            FPUTS("[TN_DECLS]", fp);
            print_recur(root->lnode, level, fp);
            if ((root->rnode && (root->rnode->hdr.type == TN_IDENT))
                 || (root->rnode->lnode
                     && ((root->rnode->lnode->hdr.type == TN_IDENT)
                         || (root->rnode->lnode->hdr.type == TN_PNTR))) )
              fputs(",",fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_DECLS}", fp);
            break;

        case TN_STEMNT_LIST:
            FPUTS("[TN_STEMNT_LIST]", fp);
            print_recur(root->lnode, level, fp);
            if (root->lnode
                    && (!just_left_blk)
                    && (root->lnode->hdr.type != TN_STEMNT_LIST)) {
                fputs(";\n", fp);
            }

            if (root->rnode != NULL) {
                print_recur(root->rnode, level, fp);
                if (!just_left_blk) {
                    fputs(";\n", fp);
                }
            }
            FPUTS("{TN_STEMNT_LIST}", fp);
            break;

        case TN_STEMNT:
            FPUTS("[TN_STEMNT]", fp);
            if (root->rnode && (root->rnode->hdr.type == TN_LABEL))
              indent(level-1,fp);
            else
              indent(level,fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_STEMNT}", fp);
            break;

        case TN_COMP_DECL:
            FPUTS("[TN_COMP_DECL]", fp);
            indent(level,fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            fputs(";\n",fp);
            FPUTS("{TN_COMP_DECL}", fp);
            break;

        case TN_BIT_FIELD:
            FPUTS("[TN_BIT_FIELD]", fp);
            print_recur(root->lnode, level, fp);
            fputs(":",fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_BIT_FIELD}", fp);
            break;

        case TN_PNTR:
            FPUTS("[TN_PNTR]", fp);
            fputs("*", fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_PNTR}", fp);
            break;

        case TN_TYPE_NME:
            FPUTS("[TN_TYPE_NME]", fp);
            print_recur(root->lnode, level, fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_TYPE_NME}", fp);
            break;

        case TN_INIT_LIST:
            FPUTS("[TN_INIT_LIST]", fp);
            print_recur(root->lnode, level, fp);
            fputs(",",fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_INIT_LIST}", fp);
            break;

        case TN_INIT_BLK:
            FPUTS("[TN_INIT_BLK]", fp);
            fputs("{", fp);
            print_recur(root->lnode, level, fp);
            fputs(",", fp);
            print_recur(root->rnode, level, fp);
            fputs("}", fp);
            FPUTS("{TN_INIT_BLK}", fp);
            break;

        case TN_OBJ_DEF:
            FPUTS("[TN_OBJ_DEF]", fp);
            leaf = (leafnode *) root;
            fputs(toksym(leaf->hdr.tok,1), fp);
            print_recur(root->lnode, level, fp);
            fputs(" {\n",fp);
            print_recur(root->rnode, level+1, fp);
            fputs("}",fp);
            FPUTS("{TN_OBJ_DEF}", fp);
            break;

        case TN_OBJ_REF:
            FPUTS("[TN_OBJ_REF]", fp);
            leaf = (leafnode *) root;
            fputs(toksym(leaf->hdr.tok,1), fp);
            print_recur(root->lnode, level, fp);
            fputs(" ",fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_OBJ_REF}", fp);
            break;

        case TN_CAST:
            FPUTS("[TN_CAST]", fp);
            decl_cnt++;    /* Not really, it's a hack. */
            fputs("(",fp);
            print_recur(root->lnode, level, fp);
            fputs(")",fp);
            decl_cnt--;
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_CAST}", fp);
            break;

        case TN_JUMP:
            FPUTS("[TN_JUMP]", fp);
            fputs(toksym(root->hdr.tok,1), fp);
            if ((root->hdr.tok == RETURN) || (root->hdr.tok == GOTO))
            {
                /*  fputs("(",fp);  */
                print_recur(root->lnode, level, fp);
                /*  fputs(")",fp);  */
            }
            FPUTS("{TN_JUMP}", fp);
            break;

        case TN_SWITCH:
            FPUTS("[TN_SWITCH]", fp);
            fputs("switch (", fp);
            print_recur(root->lnode, level, fp);
            fputs(")\n", fp);
            print_recur(root->rnode, level+1, fp);
            FPUTS("{TN_SWITCH}", fp);
            break;

        case TN_INDEX:
            FPUTS("[TN_INDEX]", fp);
            print_recur(root->lnode, level, fp);
            fputs("[",fp);
            print_recur(root->rnode, level, fp);
            fputs("]",fp);
            FPUTS("{TN_INDEX}", fp);
            break;

        case TN_DEREF:
            FPUTS("[TN_DEREF]", fp);
            fputs("*",fp);
            print_recur(root->lnode, level, fp);
            if (root->rnode && (root->rnode->hdr.type == TN_IDENT))
              print_recur(root->rnode, level, fp);
            else {
              fputs("(",fp);
              print_recur(root->rnode, level, fp);
              fputs(")",fp);
            }
            FPUTS("{TN_DEREF}", fp);
            break;

        case TN_SELECT:
            FPUTS("[TN_SELECT]", fp);
            print_recur(root->lnode, level, fp);

            if (root->hdr.tok == ARROW)
                fputs("->",fp);
            else
                fputs(".",fp);

            print_recur(root->rnode, level, fp);
            FPUTS("{TN_SELECT}", fp);
            break;

        case TN_ASSIGN:
            FPUTS("[TN_ASSIGN]", fp);
            print_recur(root->lnode, level, fp);
            fputs(toksym(root->hdr.tok,1), fp);
            //printf(" printing ==> %s %d %d \n",toksym(root->hdr.tok,1),root->hdr.type,root->hdr.tok);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_ASSIGN}", fp);
            break;

        case TN_EXPR:
            FPUTS("[TN_EXPR]", fp);
            switch (root->hdr.tok) {
              case CASE:
                fputs(toksym(root->hdr.tok,1), fp);
                print_recur(root->lnode, level, fp);
                print_recur(root->rnode, level, fp);
                break;

              case SIZEOF:
                fputs(toksym(root->hdr.tok,0), fp);
                fputs("(", fp);
                print_recur(root->lnode, level, fp);
                print_recur(root->rnode, level, fp);
                fputs(")", fp);
                break;

              case INCR:
              case DECR:
                print_recur(root->lnode, level, fp);
                fputs(toksym(root->hdr.tok,1), fp);
                print_recur(root->rnode, level, fp);
                break;

              case B_AND:
                if (root->lnode == NULL) {
                  fputs(toksym(root->hdr.tok,1), fp);
                  fputs("(", fp);
                  print_recur(root->rnode, level, fp);
                  fputs(")", fp);
                  break;
                }

              default:
                fputs("(", fp);
                print_recur(root->lnode, level, fp);
                fputs(toksym(root->hdr.tok,1), fp);
                print_recur(root->rnode, level, fp);
                fputs(")", fp);
                break;
            }
            FPUTS("{TN_EXPR}", fp);
            break;

        case TN_WHILE:
            FPUTS("[TN_WHILE]", fp);
            fputs("while (", fp);
            print_recur(root->lnode, level, fp);
            fputs(")\n", fp);
            print_recur(root->rnode, level+1, fp);
            FPUTS("{TN_WHILE}", fp);
            return(0);

        case TN_DOWHILE:
            FPUTS("[TN_DOWHILE]", fp);
            fputs("do\n", fp);
            print_recur(root->rnode, level+1, fp);
            if ((root->rnode->hdr.type == TN_STEMNT)
                    && (root->rnode->rnode->hdr.type != TN_BLOCK))
                fputs(";", fp);
            fputs("\n",fp);
            indent(level,fp);
            fputs("while (", fp);
            print_recur(root->lnode, level, fp);
            fputs(")", fp);
            FPUTS("{TN_DOWHILE}", fp);
            break;

        case TN_LABEL:
            FPUTS("[TN_LABEL 2]", fp);
            print_recur(root->lnode, level, fp);
            if (root->lnode && (root->lnode->hdr.type != TN_LABEL))
              fputs(":\n",fp);
            print_recur(root->rnode, level, fp);
            FPUTS("{TN_LABEL 2}", fp);
            break;

        case TN_EMPTY:
        default:
            fprintf(fp, "Unknown type of tree node (%d).\n", root->hdr.type);
            return 0;
        }
        break;
    }

    return(1);
}
/*  ###############################################################  */

#define print_recur   print_dsm_recur 

int  print_recur(treenode *root, int level, FILE *fp, FILE *h_fp)
{
    if_node  *ifn;
    for_node *forn;
    leafnode *leaf;
	static unsigned int selector_counter = 0;
	static int global = 1;
	treenode_list *list;

    if (!root)
        return(0);

    just_left_blk = 0;

    switch (root->hdr.which){
   
    default:
    case NONE_T:
        fputs("\nERROR: Node with no type.\n", fp);
        return 0;

    case LEAF_T:
        leaf = (leafnode *) root;
        switch (leaf->hdr.type) {

        case TN_LABEL:
            FPUTS("[TN_LABEL]", fp);
            if (leaf->hdr.tok == DEFLT)
              fputs("default",fp);
            else
              fputs(leaf->data.sval->str,fp);
            fputs(":\n",fp);
            FPUTS("{TN_LABEL}", fp);
            break;

        case TN_IDENT:
            FPUTS("[TN_IDENT]", fp);
            fputs(leaf->data.sval->str,fp);
            FPUTS("{TN_IDENT}", fp);
            break;

        case TN_COMMENT:
            fputs("\n",fp);
            fputs(leaf->data.str, fp);
            fputs("\n",fp);
            break;

        case TN_ELLIPSIS:
            FPUTS("[TN_ELLIPSIS]", fp);
            fputs("...",fp);
            FPUTS("{TN_ELLIPSIS}", fp);
            break;

        case TN_STRING:
            fputs("\"", fp);
            fputs_metastr(leaf->data.str,fp);
            fputs("\"", fp);
            break;

        case TN_TYPE:
            FPUTS("[TN_TYPE]", fp);
            if (leaf->hdr.tok != TYPEDEF_NAME)
              fputs(toksym(leaf->hdr.tok,1), fp);
            else {
              fputs(leaf->data.sval->str,fp);
              fputs(" ", fp);
            }
            FPUTS("{TN_TYPE}", fp);
            break;

        case TN_INT:
            if (leaf->hdr.tok == CHAR_CONST) {
              fputs("'",fp);
              fputs_metachr((char) leaf->data.ival, 0, fp);
              fputs("'",fp);
            } else
              fprintf(fp, "%d", leaf->data.ival);
            break;

        case TN_REAL:
            fprintf(fp, "%f", leaf->data.dval);
            break;

        default:
            fprintf(fp, "Unknown leaf value\n" );
            break;
        }
        break;

    case IF_T:
        ifn = (if_node *) root;
        switch (ifn->hdr.type) {

        case TN_IF:
            FPUTS("[TN_IF]", fp);
            fputs("if (", fp);
            print_recur(ifn->cond, level, fp, h_fp);
            fputs(")\n", fp);
            print_recur(ifn->then_n, level+1, fp, h_fp);
            if (ifn->else_n) {
                if (just_left_blk) {
                  indent(level,fp);
                  fputs("else\n", fp);
                } else {
                  fputs(";\n",fp);
                  indent(level,fp);
                  fputs("else\n", fp);
                }
                print_recur(ifn->else_n, level+1, fp, h_fp);
            }
            FPUTS("{TN_IF}", fp);
            return(0);

        case TN_COND_EXPR:
            FPUTS("[TN_COND_EXPR]", fp);
            fputs("(", fp);
            print_recur(ifn->cond, level, fp, h_fp);
            fputs(") ? (", fp);
            print_recur(ifn->then_n, level, fp, h_fp);
            fputs(") : (", fp);
            print_recur(ifn->else_n, level, fp, h_fp);
            fputs(")", fp);
            FPUTS("{TN_COND_EXPR}", fp);
            break;

        default:
            fprintf(fp, "Unknown type of if node.\n");
            break;
        }
        break;

    case FOR_T:
        forn = (for_node *) root;
        switch (forn->hdr.type) {

        case TN_FUNC_DEF:
			global = 0;
            FPUTS("[TN_FUNC_DEF]", fp);
			list = get_vars_list(forn->stemnt, 2);
			printf("\n");
            print_recur(forn->init, level, h_fp, fp); // puts function declaration in the h file
            print_recur(forn->test, level, h_fp, fp); // puts function declaration in the h file
            fputs(";\n", h_fp);

            print_recur(forn->init, level, fp, h_fp);
			fputs("CActivity::", fp);
            print_recur(forn->test, level, fp, h_fp);

            if (forn->test->hdr.which == LEAF_T)
                fputs("()", fp);
            print_recur(forn->incr, level, fp, h_fp);
            fputs("\n", fp);
            print_recur(forn->stemnt, level, fp, h_fp);
            fputs("\n", fp);
            FPUTS("{TN_FUNC_DEF}", fp);
			global = 1;
            break;

        case TN_FOR:
            FPUTS("[TN_FOR]", fp);
            fputs("for (", fp);
            print_recur(forn->init, level, fp, h_fp);
            fputs("; ", fp);
            print_recur(forn->test, level, fp, h_fp);
            fputs("; ", fp);
            print_recur(forn->incr, level, fp, h_fp);
            fputs(")\n", fp);
            print_recur(forn->stemnt, level+1, fp, h_fp);
            FPUTS("{TN_FOR}", fp);
            return 0;

        default:
            fprintf(fp, "Unknown type of for node.\n");
            break;
        }
        break;

    case NODE_T:
        switch (root->hdr.type) {
			// start of Parc extension
		case TN_PARBLOCK:
            FPUTS("[TN_PARBLOCK]", fp);
			fputs("parblock\n", fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_PARBLOCK}", fp);
			break;
		case TN_PARBLOCK_EMPTY:
            FPUTS("[TN_PARBLOCK_EMPTY]", fp);
			fprintf(h_fp, "    void __Selector%d(CActivationRecord *__spRec %s);\n", selector_counter++, "\0");
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
			list = get_vars_list(root->lnode, root->hdr.c_contxt->syms->clevel);
			printf("    void __Selector%d : ", selector_counter-1 );
//			print_list(list);
			printf("\n");
            FPUTS("{TN_PARBLOCK_EMPTY}", fp);
			break;
			// end of Parc extension

        case TN_TRANS_LIST:
            FPUTS("[TN_TRANS_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_TRANS_LIST}", fp);
            break;

        case TN_FUNC_DECL:
            FPUTS("[TN_FUNC_DECL]", fp);
            decl_cnt++;
            if (root->lnode && (root->lnode->hdr.type == TN_IDENT))
                print_recur(root->lnode, level, fp, h_fp);
            else {
                fputs("(",fp);
                print_recur(root->lnode, level, fp, h_fp);
                fputs(")",fp);
            }
            fputs("(",fp);
            print_recur(root->rnode, level, fp, h_fp);
            fputs(")",fp);
            decl_cnt--;
            FPUTS("{TN_FUNC_DECL}", fp);
            break;

        case TN_FUNC_CALL:
            FPUTS("[TN_FUNC_CALL]", fp);

            /* Only true functions are printed without parens. */
            if (is_function(root->lnode))
            {
                print_recur(root->lnode, level, fp, h_fp);
            }
            else
            {
                fputs("(", fp);
                print_recur(root->lnode, level, fp, h_fp);
                fputs(")", fp);
            }

            fputs("(", fp);
            print_recur(root->rnode, level, fp, h_fp);
            fputs(")", fp);
            FPUTS("{TN_FUNC_CALL}", fp);
            break;

        case TN_BLOCK:
            FPUTS("[TN_BLOCK]", fp);
            fputs("{\n", fp);
            print_recur(root->lnode, level+1, fp, h_fp);
            print_recur(root->rnode, level+1, fp, h_fp);
            indent(level,fp);
            fputs("}\n", fp);
            just_left_blk = 1;
            FPUTS("{TN_BLOCK}", fp);
            return(0);

        case TN_ARRAY_DECL:
            FPUTS("[TN_ARRAY_DECL]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs("[", fp);
            print_recur(root->rnode, level, fp, h_fp);
            fputs("]", fp);
            FPUTS("{TN_ARRAY_DECL}", fp);
            break;

        case TN_EXPR_LIST:
            FPUTS("[TN_EXPR_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            if (root->rnode)
              fputs(",", fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_EXPR_LIST}", fp);
            break;

        case TN_NAME_LIST:
            FPUTS("[TN_NAME_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_NAME_LIST}", fp);
            break;

        case TN_ENUM_LIST:
            FPUTS("[TN_ENUM_LIST]", fp);
            if (root->lnode
                  && (root->lnode->hdr.type != TN_ENUM_LIST))
              indent(level,fp);
            enum_list_cnt++;
            print_recur(root->lnode, level, fp, h_fp);
            if (root->rnode)
              fputs(",\n",fp);
            indent(level,fp);
            print_recur(root->rnode, level, fp, h_fp);
            if (--enum_list_cnt == 0)
              fputs("\n",fp);
            FPUTS("{TN_ENUM_LIST}", fp);
            break;

        case TN_FIELD_LIST:
            FPUTS("[TN_FIELD_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_FIELD_LIST}", fp);
            break;

        case TN_PARAM_LIST:
            FPUTS("[TN_PARAM_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            if (root->rnode)
              fputs(",",fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_PARAM_LIST}", fp);
            break;

        case TN_IDENT_LIST:
            FPUTS("[TN_IDENT_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_IDENT_LIST}", fp);
            break;

        case TN_TYPE_LIST:
            FPUTS("[TN_TYPE_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_TYPE_LIST}", fp);
            break;

        case TN_DECL:
            FPUTS("[TN_DECL]", fp);
            if (decl_cnt == 0)
              indent(level,fp);
            decl_cnt++;
			if (global) //  global variable, has to be in the h file.
			{
				print_recur(root->lnode, level, h_fp, fp);
				print_recur(root->rnode, level, h_fp, fp);
				if (--decl_cnt == 0)
					fputs(";\n",h_fp);
			}
			else
			{
				print_recur(root->lnode, level, fp, h_fp);
				print_recur(root->rnode, level, fp, h_fp);
				if (--decl_cnt == 0)
					fputs(";\n",fp);
			}
            FPUTS("{TN_DECL}", fp);
            break;

        case TN_DECL_LIST:
            FPUTS("[TN_DECL_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            if ((root->rnode && (root->rnode->hdr.type == TN_IDENT))
                 || (root->rnode->lnode
                     && ((root->rnode->lnode->hdr.type == TN_IDENT)
                         || (root->rnode->lnode->hdr.type == TN_PNTR))) )
              fputs(",",fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_DECL_LIST}", fp);
            break;

        case TN_DECLS:
            FPUTS("[TN_DECLS]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            if ((root->rnode && (root->rnode->hdr.type == TN_IDENT))
                 || (root->rnode->lnode
                     && ((root->rnode->lnode->hdr.type == TN_IDENT)
                         || (root->rnode->lnode->hdr.type == TN_PNTR))) )
              fputs(",",fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_DECLS}", fp);
            break;

        case TN_STEMNT_LIST:
            FPUTS("[TN_STEMNT_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            if (root->lnode
                    && (!just_left_blk)
                    && (root->lnode->hdr.type != TN_STEMNT_LIST)) {
                fputs(";\n", fp);
            }

            if (root->rnode != NULL) {
                print_recur(root->rnode, level, fp, h_fp);
                if (!just_left_blk) {
                    fputs(";\n", fp);
                }
            }
            FPUTS("{TN_STEMNT_LIST}", fp);
            break;

        case TN_STEMNT:
            FPUTS("[TN_STEMNT]", fp);
            if (root->rnode && (root->rnode->hdr.type == TN_LABEL))
              indent(level-1,fp);
            else
              indent(level,fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_STEMNT}", fp);
            break;

        case TN_COMP_DECL:
            FPUTS("[TN_COMP_DECL]", fp);
            indent(level,fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            fputs(";\n",fp);
            FPUTS("{TN_COMP_DECL}", fp);
            break;

        case TN_BIT_FIELD:
            FPUTS("[TN_BIT_FIELD]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(":",fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_BIT_FIELD}", fp);
            break;

        case TN_PNTR:
            FPUTS("[TN_PNTR]", fp);
            fputs("*", fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_PNTR}", fp);
            break;

        case TN_TYPE_NME:
            FPUTS("[TN_TYPE_NME]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_TYPE_NME}", fp);
            break;

        case TN_INIT_LIST:
            FPUTS("[TN_INIT_LIST]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(",",fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_INIT_LIST}", fp);
            break;

        case TN_INIT_BLK:
            FPUTS("[TN_INIT_BLK]", fp);
            fputs("{", fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(",", fp);
            print_recur(root->rnode, level, fp, h_fp);
            fputs("}", fp);
            FPUTS("{TN_INIT_BLK}", fp);
            break;

        case TN_OBJ_DEF:
            FPUTS("[TN_OBJ_DEF]", fp);
            leaf = (leafnode *) root;
            fputs(toksym(leaf->hdr.tok,1), fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(" {\n",fp);
            print_recur(root->rnode, level+1, fp, h_fp);
            fputs("}",fp);
            FPUTS("{TN_OBJ_DEF}", fp);
            break;

        case TN_OBJ_REF:
            FPUTS("[TN_OBJ_REF]", fp);
            leaf = (leafnode *) root;
            fputs(toksym(leaf->hdr.tok,1), fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(" ",fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_OBJ_REF}", fp);
            break;

        case TN_CAST:
            FPUTS("[TN_CAST]", fp);
            decl_cnt++;    /* Not really, it's a hack. */
            fputs("(",fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(")",fp);
            decl_cnt--;
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_CAST}", fp);
            break;

        case TN_JUMP:
            FPUTS("[TN_JUMP]", fp);
            fputs(toksym(root->hdr.tok,1), fp);
            if ((root->hdr.tok == RETURN) || (root->hdr.tok == GOTO))
            {
                /*  fputs("(",fp);  */
                print_recur(root->lnode, level, fp, h_fp);
                /*  fputs(")",fp);  */
            }
            FPUTS("{TN_JUMP}", fp);
            break;

        case TN_SWITCH:
            FPUTS("[TN_SWITCH]", fp);
            fputs("switch (", fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(")\n", fp);
            print_recur(root->rnode, level+1, fp, h_fp);
            FPUTS("{TN_SWITCH}", fp);
            break;

        case TN_INDEX:
            FPUTS("[TN_INDEX]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs("[",fp);
            print_recur(root->rnode, level, fp, h_fp);
            fputs("]",fp);
            FPUTS("{TN_INDEX}", fp);
            break;

        case TN_DEREF:
            FPUTS("[TN_DEREF]", fp);
            fputs("*",fp);
            print_recur(root->lnode, level, fp, h_fp);
            if (root->rnode && (root->rnode->hdr.type == TN_IDENT))
              print_recur(root->rnode, level, fp, h_fp);
            else {
              fputs("(",fp);
              print_recur(root->rnode, level, fp, h_fp);
              fputs(")",fp);
            }
            FPUTS("{TN_DEREF}", fp);
            break;

        case TN_SELECT:
            FPUTS("[TN_SELECT]", fp);
            print_recur(root->lnode, level, fp, h_fp);

            if (root->hdr.tok == ARROW)
                fputs("->",fp);
            else
                fputs(".",fp);

            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_SELECT}", fp);
            break;

        case TN_ASSIGN:
            FPUTS("[TN_ASSIGN]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(toksym(root->hdr.tok,1), fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_ASSIGN}", fp);
            break;

        case TN_EXPR:
            FPUTS("[TN_EXPR]", fp);
            switch (root->hdr.tok) {
              case CASE:
                fputs(toksym(root->hdr.tok,1), fp);
                print_recur(root->lnode, level, fp, h_fp);
                print_recur(root->rnode, level, fp, h_fp);
                break;

              case SIZEOF:
                fputs(toksym(root->hdr.tok,0), fp);
                fputs("(", fp);
                print_recur(root->lnode, level, fp, h_fp);
                print_recur(root->rnode, level, fp, h_fp);
                fputs(")", fp);
                break;

              case INCR:
              case DECR:
                print_recur(root->lnode, level, fp, h_fp);
                fputs(toksym(root->hdr.tok,1), fp);
                print_recur(root->rnode, level, fp, h_fp);
                break;

              case B_AND:
                if (root->lnode == NULL) {
                  fputs(toksym(root->hdr.tok,1), fp);
                  fputs("(", fp);
                  print_recur(root->rnode, level, fp, h_fp);
                  fputs(")", fp);
                  break;
                }

              default:
                fputs("(", fp);
                print_recur(root->lnode, level, fp, h_fp);
                fputs(toksym(root->hdr.tok,1), fp);
                print_recur(root->rnode, level, fp, h_fp);
                fputs(")", fp);
                break;
            }
            FPUTS("{TN_EXPR}", fp);
            break;

        case TN_WHILE:
            FPUTS("[TN_WHILE]", fp);
            fputs("while (", fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(")\n", fp);
            print_recur(root->rnode, level+1, fp, h_fp);
            FPUTS("{TN_WHILE}", fp);
            return(0);

        case TN_DOWHILE:
            FPUTS("[TN_DOWHILE]", fp);
            fputs("do\n", fp);
            print_recur(root->rnode, level+1, fp, h_fp);
            if ((root->rnode->hdr.type == TN_STEMNT)
                    && (root->rnode->rnode->hdr.type != TN_BLOCK))
                fputs(";", fp);
            fputs("\n",fp);
            indent(level,fp);
            fputs("while (", fp);
            print_recur(root->lnode, level, fp, h_fp);
            fputs(")", fp);
            FPUTS("{TN_DOWHILE}", fp);
            break;

        case TN_LABEL:
            FPUTS("[TN_LABEL 2]", fp);
            print_recur(root->lnode, level, fp, h_fp);
            if (root->lnode && (root->lnode->hdr.type != TN_LABEL))
              fputs(":\n",fp);
            print_recur(root->rnode, level, fp, h_fp);
            FPUTS("{TN_LABEL 2}", fp);
            break;

        case TN_EMPTY:
        default:
            fprintf(fp, "Unknown type of tree node (%d).\n", root->hdr.type);
            return 0;
        }
        break;
    }

    return(1);
}

#undef print_recur


void build_start(treenode *root, FILE *cpp_file, FILE *h_file, FILE *spawn_file)
{

	fprintf(h_file, "#ifndef __ACTIVITY_GEN_H__\n");
	fprintf(h_file, "#define __ACTIVITY_GEN_H__\n");
	fprintf(h_file, "#include <windows.h>\n");
	fprintf(h_file, "#include \"consistency_api.h\"\n");
	fprintf(h_file, "#include \"activation_record.h\"\n");
	fprintf(h_file, "\n\nenum ActivityTypes {ParForType = 0, ParBlockType = 1,ParMainType = 2};\n");
	fprintf(h_file, "enum CSWTypes {CSWMaster = 0, CSWSlave, CSWBoth,CSWNone};\n");
	fprintf(h_file, "extern __declspec(thread) unsigned long __CSCounter;\n");
	fprintf(h_file, "extern CRITICAL_SECTION DSM_STACK_CS;\n\n\n");
	fprintf(h_file, "class CActivity\n{\n");
	fprintf(h_file, "	char __Dummy[PAGE_SIZE];\n");
	fprintf(h_file, "	static int *stack;\n");
	fprintf(h_file, "	static int my_esp;\n");
	fprintf(h_file, "	void Finalize(CActivationRecord *, unsigned long &);\n");
	fprintf(h_file, "	void csw(CActivationRecord *&);\n");

	fprintf(h_file, "	void __RunParBlock(CActivationRecord &, unsigned long );\n");
	fprintf(h_file, "	void __RunParBlock(int, int, ...);\n");
	fprintf(h_file, "	void __RunInPlaceParBlock(CActivationRecord *, int, int, ...);\n");
	fprintf(h_file, "	void __RunParFor(int , int , int , int , int , ...);\n");
	fprintf(h_file, "	void __RunInPlaceParFor(CActivationRecord *, int , int , int , int , int , ...);\n");
	fprintf(h_file, "	public :\n");
	fprintf(h_file, "	CActivity();\n");
	fprintf(h_file, "	void Run(CActivationRecord *);\n");
//	fprintf(h_file, "	unsigned long __CSCounter;\n");
	fprintf(h_file, "	void CheckEsp(){}\n");
	fprintf(h_file, "	void InitGlobals(unsigned int stack_size)\n");
	fprintf(h_file, "	{\n");
	fprintf(h_file, "		InitializeCriticalSection(&DSM_STACK_CS);\n");
	fprintf(h_file, "		stack = (int *) dsm_malloc(stack_size);\n");
	fprintf(h_file, "	}\n");
	fprintf(h_file, "	void Init()\n    {\n        __CSCounter = 0;\n    }\n");
	fprintf(h_file, "	void __SpawnParConstruct(CActivationRecord *);\n");
	print_declaration(root, 0, h_file, 0);

	fprintf(cpp_file, "#include <stdio.h>\n");
	fprintf(cpp_file, "#include \"activity_gen.h\"\n");
	fprintf(cpp_file, "#include \"consistency_api.h\"\n");
	fprintf(cpp_file, "__declspec(thread) unsigned long __CSCounter = 0;\n");
	fprintf(cpp_file, "__declspec(thread) unsigned long __CSHapenned = 0;\n");
	fprintf(cpp_file, "CRITICAL_SECTION DSM_STACK_CS;\n");
	fprintf(cpp_file, "__declspec(thread) int *old_esp;\n");
	fprintf(cpp_file, "int *CActivity::stack = (int *) 0;\n");
	fprintf(cpp_file, "int CActivity::my_esp = 0xffff;\n");
	fprintf(cpp_file, "__declspec(thread) unsigned long childs_number = 0;\n");
	fprintf(cpp_file, "__declspec(thread) BOOL msg_sent = FALSE;\n");
	fprintf(cpp_file, "__declspec(thread) unsigned long parfor_start = 0;\n");
	fprintf(cpp_file, "__declspec(thread) unsigned long parfor_end  = 0;\n");
	fprintf(cpp_file, "__declspec(thread) unsigned long parfor_step = 0;\n");
	fprintf(cpp_file, "extern BOOL exit_system;\n");
	fprintf(cpp_file, "#pragma check_stack(off)\n");
	fprintf(cpp_file, "\n\n\n\n");

	fprintf(spawn_file, "#include \"activity_gen.h\"\n");
	fprintf(spawn_file, "\n\nvoid CActivity::__SpawnParConstruct(CActivationRecord *__spRec)\n{\n");
	fprintf(spawn_file, "if (__spRec->GetSize() == 0)\n");
	fprintf(spawn_file, "	return;\n");
	fprintf(spawn_file, "va_list __p  = __spRec->GetParams(0);\n");
	fprintf(spawn_file, "unsigned long sel_number = __spRec->GetSelNumber(0);\n");
	fprintf(spawn_file, "__spRec->RemoveActivity(0);\n");
	fprintf(spawn_file, "	switch(sel_number) {\n");
	fprintf(spawn_file, "	case 0: \n");
	fprintf(spawn_file, "		main(__spRec);\n");
	fprintf(spawn_file, "		break;\n");
}

void build_end(treenode *root, FILE *cpp_file, FILE *h_file, FILE *spawn_file)
{
	fprintf(h_file, "};\n\n#endif\n");
	fprintf(spawn_file, "	\n}\n}\n");
}

void build_middle(treenode *root, FILE *cpp_file, FILE *h_file, FILE *spawn_file)
{
	print_main_part(root, 0, cpp_file, h_file, spawn_file, 0, 0);
	print_main_part(root, 0, cpp_file, h_file, spawn_file, 1, 0);
	print_main_part(root, 0, cpp_file, h_file, spawn_file, 2, 0);
	print_main_part(root, 0, cpp_file, h_file, spawn_file, 3, 0);
	print_main_part(root, 0, cpp_file, h_file, spawn_file, 4, 0);

	return;
}

/*  ###############################################################  */
/* Print the tree back out (as dsm code )                            */
void  print_tree_as_dsm_code(treenode *root, char *in_file_name)
{
	int i;
	char *out_dir = malloc(sizeof(char) * strlen(in_file_name));
	char h_name[] = "activity_gen.h";
	char cpp_name[] = "activity_gen.cpp";
	char spawn_name[] = "activity_gen_spawn.cpp";
	char *h_file_name;
	char *cpp_file_name;
	char *spawn_file_name;
	FILE *h_file, *cpp_file, *spawn_file;
	strcpy(out_dir, in_file_name);
	for (i = strlen(in_file_name); i > 0;i --)
	{
		if (out_dir[i] == '\\')
		{
			out_dir[i+1] = '\0';
			break;
		}
	}
	h_file_name = malloc(sizeof(char) * (strlen(out_dir) + strlen(h_name) + 1));
	strcpy(h_file_name, out_dir);
	strcat(h_file_name, h_name);
	h_file = fopen(h_file_name, "w");

	cpp_file_name = malloc(sizeof(char) * (strlen(out_dir) + strlen(cpp_name) + 1));
	strcpy(cpp_file_name, out_dir);
	strcat(cpp_file_name, cpp_name);
	cpp_file = fopen(cpp_file_name, "w");

	spawn_file_name = malloc(sizeof(char) * (strlen(out_dir) + strlen(spawn_name) + 1));
	strcpy(spawn_file_name, out_dir);
	strcat(spawn_file_name, spawn_name);
	spawn_file = fopen(spawn_file_name, "w");

	build_start(root, cpp_file, h_file, spawn_file);
	build_middle(root, cpp_file, h_file, spawn_file);
	build_end(root, cpp_file, h_file, spawn_file);
//	build_h_file(root, h_file);
//	build_cpp_file(root, cpp_file);
//	build_static_start(h_file, cpp_file);
//    print_dsm_recur(root,0,cpp_file, h_file);
//	build_static_end(h_file, cpp_file);

}
/*  ###############################################################  */
/* Print the tree back out (as code - or close) */
void  print_tree(treenode *root, FILE *fp)
{
    flat_recur(root,&root);
    print_recur(root,0,fp);
}

/*  ###############################################################  */
void print_pcode(treenode *root, FILE *fp) {
     code_recur(root);
}
/*  ###############################################################  */
void  print_frag(treenode *root, FILE *fp)
{
  if (root && (root->hdr.type == TN_FUNC_DEF))
      decl_cnt = 0;
  else
      decl_cnt = 1;

  print_recur(root,0,fp);

#ifdef  SHOW_TYPES
  if (root && (root->hdr.type == TN_DECL)) {
    treenode *typetree, *typenode;
    typetree = root->lnode;
    fputs("\nType: ",fp);

    while (typetree && (typetree->hdr.type == TN_TYPE_LIST)) {
      typenode = typetree->lnode;
      typetree = typetree->rnode;

      if (typenode && (typenode->hdr.type == TN_TYPE)) {
        print_recur(typenode,0,fp);
      }
    }
  }
#endif
  decl_cnt = 0;
}

/*  ###############################################################  */
void  print_type(treenode *root, FILE *fp)
{
  decl_cnt = 1;

  if (root && (root->hdr.type == TN_DECL)) {
    treenode *typetree, *typenode;
    typetree = root->lnode;
    while (typetree && (typetree->hdr.type == TN_TYPE_LIST)) {
      typenode = typetree->lnode;
      typetree = typetree->rnode;

      if (typenode && (typenode->hdr.type == TN_TYPE)) {
        print_recur(typenode,0,fp);
      }
    }
  }

  decl_cnt = 0;
}

/*  ###############################################################  */
void show_leaf(leafnode *leaf, int tabs, FILE *fp)
{
    indent(tabs,fp);
    fprintf(fp, "%d,%d Leaf node %s: ", leaf->hdr.line, leaf->hdr.col,
            print_ptr(leaf));

    if (leaf == NULL){
        return;
    }

    switch(leaf->hdr.type){

    case TN_IDENT:
        fprintf(fp,"Identifier %s\n", nmestr(leaf->data.sval));
        break;

    case TN_TYPE:
        if (leaf->hdr.tok == TYPEDEF_NAME)
            fprintf(fp,"Type %s %s\n",
                toksym(leaf->hdr.tok,0),nmestr(leaf->data.sval));
        else
            fprintf(fp,"Type %s\n", toksym(leaf->hdr.tok,0));
        break;

    case TN_INT:
        fprintf(fp,"Integer %d\n", leaf->data.ival);
        break;

    case TN_REAL:
        fprintf(fp,"Real %g\n", leaf->data.dval);
        break;

    case TN_STRING:
        fprintf(fp,"String \"%s\"\n", leaf->data.str);
        break;

    case TN_ELLIPSIS:
        fprintf(fp,"Ellipsis\n");
        break;

    default:
        fprintf(fp,"Internal Error: Unknown type %d\n",
            leaf->hdr.type);
        break;
    }
}

/*  ###############################################################  */
static void show_node(treenode *node, int tabs, FILE *fp)
{
    indent(tabs,fp);

    if (node == NULL){
        fprintf(fp, "NULL node pointer 0x0\n");
        return;
    }

    fprintf(fp, "%d,%d ", node->hdr.line, node->hdr.col);
    switch(node->hdr.type){

    case TN_EMPTY:
        fprintf(fp, "Empty node %s; Token = \"%s\"\n",
                print_ptr(node), toksym(node->hdr.tok,0)); 
        break;

    case TN_FUNC_DEF:
        fprintf(fp, "Function Definition node %s:\n",
                print_ptr(node));
        break;

    case TN_FUNC_DECL:
        fprintf(fp, "Function Declaration node %s:\n",
                print_ptr(node));
        break;

    case TN_FUNC_CALL:
        fprintf(fp, "Function Call node %s:\n",
                print_ptr(node));
        break;

    case TN_BLOCK:
        fprintf(fp, "Block Node %s:\n", print_ptr(node));
        break;

    case TN_DECL:
        fprintf(fp, "Declaration node %s:\n",
                print_ptr(node));
        break;

    case TN_ARRAY_DECL:
        fprintf(fp, "Array Declaration node %s:\n",
                print_ptr(node));
        break;

    case TN_STEMNT_LIST:
        fprintf(fp, "Statement List Node %s:\n", print_ptr(node));
        break;

    case TN_TRANS_LIST:
        fprintf(fp, "TN_TRANS_LIST node %s:\n",
                print_ptr(node));
        break;

    case TN_DECL_LIST:
        fprintf(fp, "TN_DECL_LIST node %s:\n",
                print_ptr(node));
        break;

    case TN_DECLS:
        fprintf(fp, "TN_DECLS node %s:\n",
                print_ptr(node));
        break;

    case TN_EXPR_LIST:
        fprintf(fp, "Expr list node %s:\n",
                print_ptr(node));
        break;

    case TN_NAME_LIST:
        fprintf(fp, "Name list node %s:\n",
                print_ptr(node));
        break;

    case TN_ENUM_LIST:
        fprintf(fp, "Enum list node %s:\n",
                print_ptr(node));
        break;

    case TN_FIELD_LIST:
        fprintf(fp, "Field list node %s:\n",
                print_ptr(node));
        break;

    case TN_PARAM_LIST:
        fprintf(fp, "Parameter list node %s:\n",
                print_ptr(node));
        break;

    case TN_IDENT_LIST:
        fprintf(fp, "Identifier list node %s:\n",
                print_ptr(node));
        break;

    case TN_COMP_DECL:
        fprintf(fp, "Component declarator node %s:\n",
                print_ptr(node));
        break;

    case TN_BIT_FIELD:
        fprintf(fp, "Bitfield node %s:\n",
                print_ptr(node));
        break;

    case TN_PNTR:
        fprintf(fp, "Pointer node %s:\n",
                print_ptr(node));
        break;

    /* Stores a list of type specifiers/qualifiers (int:const:etc) */
    case TN_TYPE_LIST:
        fprintf(fp, "Type list node %s:\n",
                print_ptr(node));
        break;

    case TN_TYPE_NME:
        fprintf(fp, "Type name node %s:\n",
                print_ptr(node));
        break;

            /* Stores initial values for arrays */
    case TN_INIT_LIST:
        fprintf(fp, "Initializer list node %s:\n",
                print_ptr(node));
        break;

    case TN_INIT_BLK:
        fprintf(fp, "Initializer block node %s:\n",
                print_ptr(node));
        break;

    case TN_OBJ_DEF:    /* Definition of struct: union: or enum */
        fprintf(fp, "Struct/Union/Enum definition node %s:\n",
                print_ptr(node));
        break;

    case TN_OBJ_REF:    /* Reference to struct: union: or enum */
        fprintf(fp, "Struct/Union/Enum reference node %s:\n",
                print_ptr(node));
        break;

    case TN_CAST:
        fprintf(fp, "Cast node %s:\n",
                print_ptr(node));
        break;

    case TN_IF:
        fprintf(fp, "If node %s:\n",
                print_ptr(node));
        break;

    case TN_ASSIGN:
        fprintf(fp,"Assignment node %s: (%s)\n", print_ptr(node),
                toksym(node->hdr.tok,0));
        break;

    case TN_JUMP:
        fprintf(fp,"Jump node %s: %s\n", print_ptr(node),
                toksym(node->hdr.tok,0));
        break;

    case TN_FOR:
        fprintf(fp,"For node %s: %s\n", print_ptr(node),
                toksym(node->hdr.tok,0)); 
        break;

    case TN_WHILE:
        fprintf(fp,"While node %s: %s\n", print_ptr(node),
                toksym(node->hdr.tok,0)); 
        break;

    case TN_DOWHILE:
        fprintf(fp,"Do-while node %s: %s\n", print_ptr(node),
                toksym(node->hdr.tok,0)); 
        break;

    case TN_SWITCH:
        fprintf(fp, "Switch node %s:\n",
                print_ptr(node));
        break;

    case TN_ELLIPSIS:
        fprintf(fp, "Ellipsis node %s:\n",
                print_ptr(node));
        break;

    case TN_LABEL:
        fprintf(fp, "Label node %s:\n",
                print_ptr(node));
        break;

    case TN_STEMNT:
        fprintf(fp, "Statement node %s:\n",
                print_ptr(node));
        break;

    case TN_INDEX:     /* Index with [] */
        fprintf(fp, "Array index node %s:\n",
                print_ptr(node));
        break;

    case TN_DEREF:     /* Dereference with * */
        fprintf(fp, "Dereference node %s:\n",
                print_ptr(node));
        break;

    case TN_SELECT:    /* -> and . */
        fprintf(fp, "Struct selector node %s:\n",
                print_ptr(node));
        break;

    case TN_EXPR:
        fprintf(fp,"Expression node %s: (%s)\n", print_ptr(node),
                toksym(node->hdr.tok,0));
        break;

    case TN_COND_EXPR:
        fprintf(fp,"Conditional expression node %s: (%s)\n",
                print_ptr(node), toksym(node->hdr.tok,0));
        break;

    case TN_IDENT:
        fprintf(fp,"Unexpected identifier node %s\n",
                print_ptr(node));
        break;

    case TN_TYPE:
        fprintf(fp,"TN_TYPE node %s; Token is: %s\n",
                print_ptr(node), toksym(node->hdr.tok,0)); 
        break;

    case TN_STRING:
        fprintf(fp,"Unexpected string node %s\n", print_ptr(node));
        break;

    case TN_INT:
        fprintf(fp,"Unexpected integer node %s\n",
                print_ptr(node));
        break;

    case TN_REAL:
        fprintf(fp,"Unexpected real node %s\n", print_ptr(node));
        break;

    default:
        fprintf(fp,"Unknown node %s; internal error (type=%d)\n",
            print_ptr(node), node->hdr.type);
        break;
    }

    indent(tabs,fp);
    fprintf(fp, "Left Child %s:\n", print_ptr(node->lnode)); 
    show_any(node->lnode,tabs+1,fp);

    indent(tabs,fp);
    fprintf(fp, "Right Child %s:\n", print_ptr(node->rnode)); 
    show_any(node->rnode,tabs+1,fp);
}

/*  ###############################################################  */
static void show_if(if_node *ifn, int tabs, FILE *fp)
{
    int indx = 0;
    static char *heads[2][3] = {
        { "Test-expr %s:\n",
          "Then-statement %s:\n", "Else-statement %s:\n" },
        { "Conditional-expr %s:\n",
          "True-expr %s:\n", "False-expr %s:\n" }
    };

    indent(tabs,fp);

    if (ifn == NULL){
        fprintf(fp, "Unexpected Null If-node pointer 0x0\n");
        return;
    }

    if (ifn->hdr.tok == QUESTMARK)
        indx = 1;

    fprintf(fp, "%d,%d ", ifn->hdr.line, ifn->hdr.col);
    fprintf(fp, heads[indx][0], print_ptr(ifn));
    show_any(ifn->cond,tabs+1,fp);

    indent(tabs,fp);
    fprintf(fp, heads[indx][1], print_ptr(ifn));
    show_any(ifn->then_n,tabs+1,fp);

    indent(tabs,fp);
    fprintf(fp, heads[indx][2], print_ptr(ifn));
    show_any(ifn->else_n,tabs+1,fp);
}

/*  ###############################################################  */
static void show_for(for_node *forn, int tabs, FILE *fp)
{
    int indx = 0;
    static char *heads[2][4] = {
        {	//for case
			"Initializer %s:\n", 
			"Test %s:\n", 
			"Incrementer %s:\n", 
			"Statement %s:\n" 
		},
        
		{	//function case
			"Function Type %s:\n", 
			"Function Decl %s:\n",
			"Function Optional Decls (K&R) %s:\n", 
			"Statement %s:\n" 
		}
    };

    if (forn == NULL){
        fprintf(fp, "Unexpected Null For-node pointer 0x0\n");
        return;
    }

    if (forn->hdr.type == TN_FUNC_DEF)
        indx = 1;

	indent(tabs, fp);
    fprintf(fp, "%d,%d ", forn->hdr.line, forn->hdr.col);
    fprintf(fp, heads[indx][0], print_ptr(forn));
    show_any(forn->init,tabs+1,fp);

	indent(tabs,fp);
    fprintf(fp, heads[indx][1], print_ptr(forn));
    show_any(forn->test,tabs+1,fp);

	indent(tabs,fp);
    fprintf(fp, heads[indx][2], print_ptr(forn));
    show_any(forn->incr,tabs+1,fp);

	indent(tabs,fp);
    fprintf(fp, heads[indx][3], print_ptr(forn));
    show_any(forn->stemnt,tabs+1,fp);
}

/*  ###############################################################  */
static void show_any(treenode *child, int tabs, FILE *fp)
{
    if (!child){
        indent(tabs,fp);
        fputs("NULL node pointer 0x0\n",fp);
    } else {

        switch (child->hdr.which){
        case LEAF_T:
            show_leaf((leafnode *) child, tabs,fp);
            break;
     
        case NODE_T:
            show_node(child,tabs,fp);
            break;
        
        case IF_T:
            show_if((if_node *) child, tabs,fp);
            break;
        
        case FOR_T:
            show_for((for_node *) child, tabs,fp);
            break;
        
        case NONE_T:
            fprintf(fp, "Node %s: no-type\n", print_ptr(child));
            break;

        default:
            fprintf(stderr,
                    "Node %s internal error: unknown which-type %d\n",
                    print_ptr(child), child->hdr.which);
            break;
        }
    }
}

/*  ###############################################################  */
void show_tree(treenode *root, FILE *fp)
{
    fprintf(fp, "\nShowing parse tree %s:\n", print_ptr(root));
    show_any(root,1,fp);
}

/*  ###############################################################  */
void show_int_ntype(treenode *root, FILE *fp)
{
  switch (root->hdr.type) {
    default:
      fputs("<Unknown node type>\n", fp);
      break;

    case TN_EMPTY:
      fputs("TN_EMPTY\n",fp);
      break;

    case TN_FUNC_DEF:
      fputs("TN_FUNC_DEF\n",fp);
      break;

    case TN_FUNC_DECL:
      fputs("TN_FUNC_DECL\n",fp);
      break;

    case TN_FUNC_CALL:
      fputs("TN_FUNC_CALL\n",fp);
      break;

    case TN_BLOCK:
      fputs("TN_BLOCK\n",fp);
      break;

    case TN_DECL:
      fputs("TN_DECL\n",fp);
      break;

    case TN_ARRAY_DECL:
      fputs("TN_ARRAY_DECL\n",fp);
      break;

    case TN_TRANS_LIST:
      fputs("TN_TRANS_LIST\n",fp);
      break;

    case TN_DECL_LIST:
      fputs("TN_DECL_LIST\n",fp);
      break;

    case TN_DECLS:
      fputs("TN_DECLS\n",fp);
      break;

    case TN_STEMNT_LIST:
      fputs("TN_STEMNT_LIST\n",fp);
      break;

    case TN_EXPR_LIST:
      fputs("TN_EXPR_LIST\n",fp);
      break;

    case TN_NAME_LIST:
      fputs("TN_NAME_LIST\n",fp);
      break;

    case TN_ENUM_LIST:
      fputs("TN_ENUM_LIST\n",fp);
      break;

    case TN_FIELD_LIST:
      fputs("TN_FIELD_LIST\n",fp);
      break;

    case TN_PARAM_LIST:
      fputs("TN_PARAM_LIST\n",fp);
      break;

    case TN_IDENT_LIST:
      fputs("TN_IDENT_LIST\n",fp);
      break;

    case TN_COMP_DECL:
      fputs("TN_COMP_DECL\n",fp);
      break;

    case TN_BIT_FIELD:
      fputs("TN_BIT_FIELD\n",fp);
      break;

    case TN_PNTR:
      fputs("TN_PNTR\n",fp);
      break;

    case TN_TYPE_LIST:
      fputs("TN_TYPE_LIST\n",fp);
      break;

    case TN_TYPE_NME:
      fputs("TN_TYPE_NME\n",fp);
      break;

    case TN_INIT_LIST:
      fputs("TN_INIT_LIST\n",fp);
      break;

    case TN_INIT_BLK:
      fputs("TN_INIT_BLK\n",fp);
      break;

    case TN_OBJ_DEF:
      fputs("TN_OBJ_DEF\n",fp);
      break;

    case TN_OBJ_REF:
      fputs("TN_OBJ_REF\n",fp);
      break;

    case TN_CAST:
      fputs("TN_CAST\n",fp);
      break;

    case TN_IF:
      fputs("TN_IF\n",fp);
      break;

    case TN_ASSIGN:
      fputs("TN_ASSIGN\n",fp);
      break;

    case TN_JUMP:
      fputs("TN_JUMP\n",fp);
      break;

    case TN_FOR:
      fputs("TN_FOR\n",fp);
      break;

    case TN_WHILE:
      fputs("TN_WHILE\n",fp);
      break;

    case TN_DOWHILE:
      fputs("TN_DOWHILE\n",fp);
      break;

    case TN_SWITCH:
      fputs("TN_SWITCH\n",fp);
      break;

    case TN_LABEL:
      fputs("TN_LABEL\n",fp);
      break;

    case TN_STEMNT:
      fputs("TN_STEMNT\n",fp);
      break;

    case TN_INDEX:
      fputs("TN_INDEX\n",fp);
      break;

    case TN_DEREF:
      fputs("TN_DEREF\n",fp);
      break;

    case TN_SELECT:
      fputs("TN_SELECT\n",fp);
      break;

    case TN_EXPR:
      fputs("TN_EXPR\n",fp);
      break;

    case TN_COND_EXPR:
      fputs("TN_COND_EXPR\n",fp);
      break;

    case TN_IDENT:
      fputs("TN_IDENT\n",fp);
      break;

    case TN_TYPE:
      fputs("TN_TYPE\n",fp);
      break;

    case TN_STRING:
      fputs("TN_STRING\n",fp);
      break;

    case TN_INT:
      fputs("TN_INT\n",fp);
      break;

    case TN_REAL:
      fputs("TN_REAL\n",fp);
      break;

    case TN_ELLIPSIS:
      fputs("TN_ELLIPSIS\n",fp);
      break;
  }
}

/*  ###############################################################  */
