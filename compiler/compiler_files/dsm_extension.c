#include    "prnttree.h"
#include    "symtab.h"

#include "treestk.h"
#include "tree.h"
#include "gram_parser.cpp.h"
#include "dsm_extension.h"
#include "nmetab.h"
#include "token.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern TreeStack *ParseStack;
extern int is_function(treenode *node); // prntree.c

void combain_lists(treenode_list **dest, treenode_list **src)
{
	treenode_list *dest_tmp;
	if (!(*dest))
	{
		*dest = *src;
		*src = 0;
		return;
	}
	dest_tmp = *dest;
	while(dest_tmp && *src)
	{
		treenode_list *src_tmp;
		src_tmp = malloc(sizeof(treenode_list));
		src_tmp->next = *src;
		*src = src_tmp;
		while(src_tmp && src_tmp->next)
		{
			if (!strcmp(((leafnode *) (dest_tmp->node))->syment->nme->str, 
				        ((leafnode *) (src_tmp->next->node))->syment->nme->str))
			{
				treenode_list *tmp = src_tmp->next;
				src_tmp->next = src_tmp->next->next;
				free(tmp);
			}
			src_tmp = src_tmp->next;
		}
		src_tmp = *src;
		*src = (*src) ->next;
		free (src_tmp);
		dest_tmp = dest_tmp->next;
	}
	dest_tmp = *dest;
	while( dest_tmp->next) 
		dest_tmp = dest_tmp->next;
	dest_tmp->next = *src;
	*src = 0;
	return;
}

char in_list(char *name, char_list *list)
{
	while(list)
	{
		if (!strcmp(name, list->node))
			return 1;
		list = list->next;
	}
	return 0;
}

treenode_list *get_vars_list(treenode *tree, int scope)
{
    leafnode *leaf;
    if_node  *ifn;
    for_node *forn;
	treenode_list *ret_value = 0;
	treenode_list *left = 0, *right = 0;
	if (!tree)
		return 0;

	
    switch (tree->hdr.which)
	{
    default:
    case NONE_T:        
        return 0;
    case LEAF_T:
        leaf = (leafnode *) tree;
        switch (leaf->hdr.type) 
		{
        case TN_LABEL:
            break;
        case TN_IDENT:
			{
				symentry_t *m_symentry;
				leaf = (leafnode *) tree;
				m_symentry = symtab_lookup(leaf->hdr.c_contxt->syms, leaf->data.sval);
				if (m_symentry && 
					m_symentry->node->hdr.c_contxt->syms->clevel <= scope &&
					m_symentry->node->hdr.c_contxt->syms->clevel > 2)
				{
					ret_value = malloc(sizeof(treenode_list));
					ret_value->node = tree;
					ret_value->next = 0;
				}
			}
			return ret_value;
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
        ifn = (if_node *) tree;
        switch (ifn->hdr.type) 
		{
        case TN_IF:
			left = get_vars_list(ifn->cond, scope);
			right = get_vars_list(ifn->then_n, scope);
			combain_lists(&right, &left);
            if (ifn->else_n) 
			{
				left = get_vars_list(ifn->else_n, scope);
            }
            break;

        case TN_COND_EXPR:
			left = get_vars_list(ifn->cond, scope);
			right = get_vars_list(ifn->then_n, scope);
			combain_lists(&right, &left);
            left = get_vars_list(ifn->else_n, scope);
            break;

        default:
            break;
        }
        break;

    case FOR_T:
        forn = (for_node *) tree;
        switch (forn->hdr.type) 
		{
        case TN_FUNC_DEF:
            left = get_vars_list(forn->init, scope);
//            right = get_vars_list(forn->test);
			combain_lists(&right, &left);
            left = get_vars_list(forn->incr, scope);
			combain_lists(&right, &left);
            left = get_vars_list(forn->stemnt, scope);
            break;
        case TN_FOR:
			left = get_vars_list(forn->init, scope);
			right = get_vars_list(forn->test, scope);
			combain_lists(&right, &left);
			left = get_vars_list(forn->incr, scope);
			combain_lists(&right, &left);
			left = get_vars_list(forn->stemnt, scope);
            return 0;

        default:
            break;
        }
        break;

    case NODE_T:
        switch (tree->hdr.type) {
			// start of Parc extension
		case TN_PARBLOCK:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
			break;
		case TN_PARBLOCK_EMPTY:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
			break;
			// end of Parc extension
        case TN_TRANS_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;

        case TN_FUNC_DECL:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;

        case TN_FUNC_CALL:
/*			leaf = find_func_name(tree->lnode);
			if (!in_list(leaf->data.sval->str, func_name))
			{
				symentry_t *func_def;
				if (func_def = symtab_lookup(leaf->hdr.c_contxt->syms, leaf->data.sval))
				{
					char_list tmp;
					tmp.next = func_name;
					tmp.node = leaf->data.sval->str;
					left = get_vars_list(func_def->node, &tmp, 2);
					right = get_vars_list(tree->rnode, &tmp , 2);
				}
			}
*/			
			left = get_vars_list(tree->rnode, scope);
			break;
        case TN_BLOCK:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;

        case TN_ARRAY_DECL:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_EXPR_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_NAME_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_ENUM_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_FIELD_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_PARAM_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_IDENT_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_TYPE_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_DECL:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_DECL_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_DECLS:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_STEMNT_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_STEMNT:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_COMP_DECL:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_BIT_FIELD:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_PNTR:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_TYPE_NME:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_INIT_LIST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_INIT_BLK:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_OBJ_DEF:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_OBJ_REF:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_CAST:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_JUMP:
            if ((tree->hdr.tok == RETURN) || (tree->hdr.tok == GOTO))
            {
				left = get_vars_list(tree->lnode, scope);
            }
            break;

        case TN_SWITCH:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_INDEX:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_DEREF:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_SELECT:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_ASSIGN:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_EXPR:
            switch (tree->hdr.tok) 
			{
			case CASE:
				left = get_vars_list(tree->lnode, scope);
				right = get_vars_list(tree->rnode, scope);
                break;
              case SIZEOF:
				left = get_vars_list(tree->lnode, scope);
				right = get_vars_list(tree->rnode, scope);
                break;
              case INCR:
              case DECR:
				left = get_vars_list(tree->lnode, scope);
				right = get_vars_list(tree->rnode, scope);
                break;
              case B_AND:
              default:
				left = get_vars_list(tree->lnode, scope);
				right = get_vars_list(tree->rnode, scope);
                break;
            }
            break;
        case TN_WHILE:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
			break;
        case TN_DOWHILE:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_LABEL:
			left = get_vars_list(tree->lnode, scope);
			right = get_vars_list(tree->rnode, scope);
            break;
        case TN_EMPTY:
        default:
            return 0;
        }
        break;
    }	
	
/*	if (!left)
		return right;
	ret_value = left;
	while(ret_value->next)
		ret_value = ret_value->next;
	ret_value->next = right;*/
	combain_lists(&left, &right);
	return left;
}

extern int  print_recur(treenode *, int , FILE *);

void print_list(treenode_list *list, int mode, FILE *fp)
{
	leafnode *leaf;
	if (!list)
		return;
	leaf = (leafnode *) list->node;
//	printf("%s   ", leaf->data.sval->str);
	if (mode != 2)
		print_recur(leaf->syment->node->lnode, 0, fp);
	if (mode == 1)
		fputs("&", fp);
	if (mode == 0 || mode ==2 )
		fputs("*", fp);
	print_recur(leaf->syment->node->rnode, 0, fp);
	if (mode == 0)
	{
		fputs(" = (", fp);
		print_recur(leaf->syment->node->lnode, 0, fp);
		fputs("*) ((unsigned long ) va_arg(__p, ", fp);
		print_recur(leaf->syment->node->lnode, 0, fp);
		fputs("*)+ (unsigned long ) dsm_get_reserved_address());\n", fp);
	}
	if (list->next && (mode == 1 || mode == 2))
		fputs(" ,", fp);
	print_list(list->next, mode, fp);
}

void print_addresses(treenode_list *list, FILE *fp)
{
	treenode_list *tmp = list;
	int size = 0;
	while(tmp)
	{
		fprintf(fp, ", (unsigned long) &%s - (unsigned long ) dsm_get_reserved_address()", 
			        ((leafnode *) (tmp->node))->data.sval->str);
		tmp = tmp->next;
	}
}

void print_sizeof_list(treenode_list *list, FILE *fp)
{
	treenode_list *tmp = list;
	int size = 0;
	while(tmp)
	{
		size++;
		tmp = tmp->next;
	}
	fprintf(fp, "%d * sizeof(void *)", size);
}


void print_declaration(treenode *root, int level, FILE *fp, int declaration)
{
    if_node  *ifn;
    for_node *forn;
    leafnode *leaf;
	static unsigned int selector_counter = 1;
	static int global = 1;
	static treenode_list *list;
	static int just_left_blk  = 0;
	static int decl_cnt = 0;
	static int enum_list_cnt = 0;

    if (!root)
        return ;

    just_left_blk = 0;

    switch (root->hdr.which)
	{
    default:
    case NONE_T:
        fputs("\nERROR: Node with no type.\n", fp);
        return ;

    case LEAF_T:
		if (!declaration)
			return;
        leaf = (leafnode *) root;
        switch (leaf->hdr.type) 
		{
        case TN_LABEL:
            if (leaf->hdr.tok == DEFLT)
              fputs("default",fp);
            else
              fputs(leaf->data.sval->str,fp);
            fputs(":\n",fp);
            break;

        case TN_IDENT:
            fputs(leaf->data.sval->str,fp);
            break;

        case TN_COMMENT:
            fputs("\n",fp);
            fputs(leaf->data.str, fp);
            fputs("\n",fp);
            break;

        case TN_ELLIPSIS:
            fputs("...",fp);
            break;

        case TN_STRING:
            fputs("\"", fp);
            fputs_metastr(leaf->data.str,fp);
            fputs("\"", fp);
            break;

        case TN_TYPE:
            if (leaf->hdr.tok != TYPEDEF_NAME)
              fputs(toksym(leaf->hdr.tok,1), fp);
            else {
              fputs(leaf->data.sval->str,fp);
              fputs(" ", fp);
            }
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
            print_declaration(ifn->cond, level, fp, declaration);
            print_declaration(ifn->then_n, level+1, fp, declaration);
            if (ifn->else_n) 
			{
                print_declaration(ifn->else_n, level+1, fp, declaration);
            }
            return;

        case TN_COND_EXPR:
            print_declaration(ifn->cond, level, fp, declaration);
            print_declaration(ifn->then_n, level, fp, declaration);
            print_declaration(ifn->else_n, level, fp, declaration);
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
			list = get_vars_list(forn->stemnt, 2);
            print_declaration(forn->init, level, fp, 1);
            print_declaration(forn->test, level, fp, 1);
            fputs(";\n", fp);

            print_declaration(forn->stemnt, level, fp, 0);  //   for Selectors

			global = 1;
            break;

        case TN_FOR:
/*            fputs("for (", fp);
            print_declaration(forn->init, level, fp, declaration);
            fputs("; ", fp);
            print_declaration(forn->test, level, fp, declaration);
            fputs("; ", fp);
            print_declaration(forn->incr, level, fp, declaration);
            fputs(")\n", fp);*/
            print_declaration(forn->stemnt, level+1, fp, 0);
            return ;

        default:
            fprintf(fp, "Unknown type of for node.\n");
            break;
        }
        break;

    case NODE_T:
        switch (root->hdr.type) {
			// start of Parc extension
		case TN_PARBLOCK:
            print_declaration(root->lnode, level, fp, 0);
            print_declaration(root->rnode, level, fp, 0);
			break;
		case TN_PARBLOCK_EMPTY:
//			fprintf(fp, "    void __Selector%d(ActivationRecord *__spRec %s ", selector_counter++, "\0");
//			list = get_vars_list(root->lnode, root->hdr.c_contxt->syms->clevel);
//			if (list)
//				fprintf(fp, ",");
//			print_list(list, 1, fp);
//			fprintf(fp, ");\n");
			print_declaration(root->lnode, level, fp, 0);  //   body
            print_declaration(root->rnode, level, fp, 0);  // next block
			break;
			// end of Parc extension

        case TN_TRANS_LIST:
            print_declaration(root->lnode, level, fp, 0);
            print_declaration(root->rnode, level, fp, 0);
            break;

        case TN_FUNC_DECL:
            decl_cnt++;
            if (root->lnode && (root->lnode->hdr.type == TN_IDENT))
                print_declaration(root->lnode, level, fp, declaration);
            else {
                fputs("(",fp);
                print_declaration(root->lnode, level, fp, declaration);
                fputs(")",fp);
            }
            fputs("(",fp);
			global = 1;
			if (root->rnode)
				fprintf(fp, "CActivationRecord * ,");
			else
				fprintf(fp, "CActivationRecord * ");
            print_declaration(root->rnode, level, fp, declaration);
			global = 0;

			print_list(list, 1, fp);
			printf("\n");


			// end
            fputs(")",fp);
            decl_cnt--;
            break;

        case TN_FUNC_CALL:
            break;

        case TN_BLOCK:
            print_declaration(root->lnode, level+1, fp, 0);
            print_declaration(root->rnode, level+1, fp, 0);
            just_left_blk = 1;
            return;

        case TN_ARRAY_DECL:
            print_declaration(root->lnode, level, fp, 1);
            fputs("[", fp);
            print_declaration(root->rnode, level, fp, 1);
            fputs("]", fp);
            break;

        case TN_EXPR_LIST:
            print_declaration(root->lnode, level, fp, declaration);
            if (root->rnode)
              fputs(",", fp);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_NAME_LIST:
            print_declaration(root->lnode, level, fp, declaration);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_ENUM_LIST:
            if (root->lnode
                  && (root->lnode->hdr.type != TN_ENUM_LIST))
              indent(level,fp);
            enum_list_cnt++;
            print_declaration(root->lnode, level, fp, declaration);
            if (root->rnode && declaration)
              fputs(",\n",fp);
            indent(level,fp);
            print_declaration(root->rnode, level, fp, declaration);
            if (--enum_list_cnt == 0 && declaration)
              fputs("\n",fp);
            break;

        case TN_FIELD_LIST:
            print_declaration(root->lnode, level, fp, declaration);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_PARAM_LIST:
            print_declaration(root->lnode, level, fp, declaration);
            if (root->rnode)
              fputs(",",fp);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_IDENT_LIST:
            print_declaration(root->lnode, level, fp, declaration);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_TYPE_LIST:
            print_declaration(root->lnode, level, fp, declaration);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_DECL:
            if (decl_cnt == 0)
              indent(level,fp);
			if (global)
			{
				decl_cnt++;
				print_declaration(root->lnode, level, fp, 1);
				print_declaration(root->rnode, level, fp, 1);
				if (--decl_cnt == 0)
					fputs(";\n", fp);
			}
            break;

        case TN_DECL_LIST:
            print_declaration(root->lnode, level, fp, 1);
            if ((root->rnode && (root->rnode->hdr.type == TN_IDENT))
                 || (root->rnode->lnode
                     && ((root->rnode->lnode->hdr.type == TN_IDENT)
                         || (root->rnode->lnode->hdr.type == TN_PNTR))) )
              fputs(",",fp);
            print_declaration(root->rnode, level, fp, 1);
            break;

        case TN_DECLS:
            print_declaration(root->lnode, level, fp, 1);
            if ((root->rnode && (root->rnode->hdr.type == TN_IDENT))
                 || (root->rnode->lnode
                     && ((root->rnode->lnode->hdr.type == TN_IDENT)
                         || (root->rnode->lnode->hdr.type == TN_PNTR))) )
              fputs(",",fp);
            print_declaration(root->rnode, level, fp, 1);
            break;

        case TN_STEMNT_LIST:
            print_declaration(root->lnode, level, fp, declaration);
            if (root->lnode
                    && (!just_left_blk)
                    && (root->lnode->hdr.type != TN_STEMNT_LIST)) 
			{
				if (declaration)
					fputs(";\n", fp);
            }

            if (root->rnode != NULL) {
                print_declaration(root->rnode, level, fp, declaration);
                if (!just_left_blk) 
				{
					if (declaration)
						fputs(";\n", fp);
                }
            }
            break;

        case TN_STEMNT:
            if (root->rnode && (root->rnode->hdr.type == TN_LABEL))
              indent(level-1,fp);
            else
              indent(level,fp);
            print_declaration(root->lnode, level, fp, declaration);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_COMP_DECL:
            indent(level,fp);
            print_declaration(root->lnode, level, fp, 1);
            print_declaration(root->rnode, level, fp, 1);
            fputs(";\n",fp);
            break;

        case TN_BIT_FIELD:
            print_declaration(root->lnode, level, fp, declaration);
            if (declaration)
				fputs(":",fp);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_PNTR:
			if (declaration)
				fputs("*", fp);
            print_declaration(root->lnode, level, fp, declaration);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_TYPE_NME:
            print_declaration(root->lnode, level, fp, declaration);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_INIT_LIST:
            print_declaration(root->lnode, level, fp, declaration);
			if (declaration)
				fputs(",",fp);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_INIT_BLK:
			if (declaration)
				fputs("{", fp);
            print_declaration(root->lnode, level, fp, declaration);
			if (declaration)
				fputs(",", fp);
            print_declaration(root->rnode, level, fp, declaration);
            if (declaration)
				fputs("}", fp);
            break;

        case TN_OBJ_DEF:
            leaf = (leafnode *) root;
			if (declaration)
				fputs(toksym(leaf->hdr.tok,1), fp);
            print_declaration(root->lnode, level, fp, declaration);
			if (declaration)
				fputs(" {\n",fp);
            print_declaration(root->rnode, level+1, fp, declaration);
			if (declaration)
				fputs("}",fp);
            break;

        case TN_OBJ_REF:
            leaf = (leafnode *) root;
            if (declaration)
				fputs(toksym(leaf->hdr.tok,1), fp);
            print_declaration(root->lnode, level, fp, declaration);
            if (declaration)
				fputs(" ",fp);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_CAST:
            decl_cnt++;    /* Not really, it's a hack. */
            if(declaration)
				fputs("(",fp);
            print_declaration(root->lnode, level, fp, declaration);
            if(declaration)
				fputs(")",fp);
            decl_cnt--;
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_JUMP:
            if (declaration)
				fputs(toksym(root->hdr.tok,1), fp);
            if ((root->hdr.tok == RETURN) || (root->hdr.tok == GOTO))
            {
                /*  fputs("(",fp);  */
                print_declaration(root->lnode, level, fp, declaration);
                /*  fputs(")",fp);  */
            }
            break;

        case TN_SWITCH:
//            fputs("switch (", fp);
            print_declaration(root->lnode, level, fp, declaration);
//            fputs(")\n", fp);
            print_declaration(root->rnode, level+1, fp, declaration);
            break;

        case TN_INDEX:
            print_declaration(root->lnode, level, fp, declaration);
            if (declaration)
				fputs("[",fp);
            print_declaration(root->rnode, level, fp, declaration);
            if (declaration)
				fputs("]",fp);
            break;

        case TN_DEREF:
            if (declaration)
				fputs("*",fp);
            print_declaration(root->lnode, level, fp, declaration);
            if (root->rnode && (root->rnode->hdr.type == TN_IDENT))
              print_declaration(root->rnode, level, fp, declaration);
            else {
				if (declaration)
					fputs("(",fp);
				print_declaration(root->rnode, level, fp, declaration);
				if (declaration)
					fputs(")",fp);
            }
            break;

        case TN_SELECT:
            print_declaration(root->lnode, level, fp, declaration);

			if (declaration)
				if (root->hdr.tok == ARROW)
					fputs("->",fp);
				else
					fputs(".",fp);
			
			print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_ASSIGN:
            print_declaration(root->lnode, level, fp, declaration);
            if (declaration)
				fputs(toksym(root->hdr.tok,1), fp);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_EXPR:
            switch (root->hdr.tok) {
              case CASE:
                if (declaration)
					fputs(toksym(root->hdr.tok,1), fp);
                print_declaration(root->lnode, level, fp, declaration);
                print_declaration(root->rnode, level, fp, declaration);
                break;

              case SIZEOF:
                if (declaration)
				{
					fputs(toksym(root->hdr.tok,0), fp);
					fputs("(", fp);
				}
                print_declaration(root->lnode, level, fp, declaration);
                print_declaration(root->rnode, level, fp, declaration);
				if (declaration)
					fputs(")", fp);
                break;

              case INCR:
              case DECR:
                print_declaration(root->lnode, level, fp, declaration);
				if (declaration)
					fputs(toksym(root->hdr.tok,1), fp);
                print_declaration(root->rnode, level, fp, declaration);
                break;

              case B_AND:
                if (root->lnode == NULL) {
                  if (declaration)
				  {
					  fputs(toksym(root->hdr.tok,1), fp);
					  fputs("(", fp);
				  }
                  print_declaration(root->rnode, level, fp, declaration);
				  if (declaration)
					  fputs(")", fp);
                  break;
                }

              default:
                if (declaration)
					fputs("(", fp);
                print_declaration(root->lnode, level, fp, declaration);
				if (declaration)
					fputs(toksym(root->hdr.tok,1), fp);
                print_declaration(root->rnode, level, fp, declaration);
				if (declaration)
					fputs(")", fp);
                break;
            }
            break;

        case TN_WHILE:
//            fputs("while (", fp);
            print_declaration(root->lnode, level, fp, 0);
//            fputs(")\n", fp);
            print_declaration(root->rnode, level+1, fp, 0);
            return;

        case TN_DOWHILE:
//            fputs("do\n", fp);
            print_declaration(root->rnode, level+1, fp, 0);
//            if ((root->rnode->hdr.type == TN_STEMNT)
//                    && (root->rnode->rnode->hdr.type != TN_BLOCK))
//                fputs(";", fp);
//            fputs("\n",fp);
//            indent(level,fp);
//            fputs("while (", fp);
            print_declaration(root->lnode, level, fp, declaration);
//            fputs(")", fp);
            break;

        case TN_LABEL:
            print_declaration(root->lnode, level, fp, declaration);
            if (root->lnode && (root->lnode->hdr.type != TN_LABEL) && declaration)
              fputs(":\n",fp);
            print_declaration(root->rnode, level, fp, declaration);
            break;

        case TN_EMPTY:
        default:
            fprintf(fp, "Unknown type of tree node (%d).\n", root->hdr.type);
            return ;
        }
        break;
    }

    return;
}


//  cpp file

void print_main_part(treenode *root, int level , FILE *fp, FILE *h_fp, FILE *spawn_file, int parblock_level, int cur_parblock_level)
{
    if_node  *ifn;
    for_node *forn;
    leafnode *leaf;
	static unsigned int selector_counter_decl = 1;
	static unsigned int selector_counter_call = 1;
	static int global = 1;
	treenode_list *list;
	static int just_left_blk  = 0;
	static int decl_cnt = 0;
	static int enum_list_cnt = 0;


    if (!root)
        return;

    just_left_blk = 0;

    switch (root->hdr.which){
   
    default:
    case NONE_T:
        fputs("\nERROR: Node with no type.\n", fp);
        return;

    case LEAF_T:
        leaf = (leafnode *) root;
        switch (leaf->hdr.type) {

        case TN_LABEL:
            if (leaf->hdr.tok == DEFLT)
              if (cur_parblock_level == parblock_level) fputs("default",fp);
            else
				if (cur_parblock_level == parblock_level) fputs(leaf->data.sval->str,fp);
			if (cur_parblock_level == parblock_level) fputs(":\n",fp);
            break;

        case TN_IDENT:
            if (cur_parblock_level == parblock_level) fputs(leaf->data.sval->str,fp);
            break;

        case TN_COMMENT:
            if (cur_parblock_level == parblock_level) fputs("\n",fp);
            if (cur_parblock_level == parblock_level) fputs(leaf->data.str, fp);
            if (cur_parblock_level == parblock_level) fputs("\n",fp);
            break;

        case TN_ELLIPSIS:
            if (cur_parblock_level == parblock_level) fputs("...",fp);
            break;

        case TN_STRING:
            if (cur_parblock_level == parblock_level) fputs("\"", fp);
            if (cur_parblock_level == parblock_level) fputs_metastr(leaf->data.str,fp);
            if (cur_parblock_level == parblock_level) fputs("\"", fp);
            break;

        case TN_TYPE:
            if (leaf->hdr.tok != TYPEDEF_NAME)
              if (cur_parblock_level == parblock_level) fputs(toksym(leaf->hdr.tok,1), fp);
            else {
              if (cur_parblock_level == parblock_level) fputs(leaf->data.sval->str,fp);
              if (cur_parblock_level == parblock_level) fputs(" ", fp);
            }
            break;

        case TN_INT:
            if (leaf->hdr.tok == CHAR_CONST) {
              if (cur_parblock_level == parblock_level) fputs("'",fp);
              if (cur_parblock_level == parblock_level) fputs_metachr((char) leaf->data.ival, 0, fp);
              if (cur_parblock_level == parblock_level) fputs("'",fp);
            } else
              if (cur_parblock_level == parblock_level) fprintf(fp, "%d", leaf->data.ival);
            break;

        case TN_REAL:
            if (cur_parblock_level == parblock_level) fprintf(fp, "%f", leaf->data.dval);
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
            if (cur_parblock_level == parblock_level) fputs("if (", fp);
            print_main_part(ifn->cond, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(")\n", fp);
            print_main_part(ifn->then_n, level+1, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (ifn->else_n) {
                if (just_left_blk) {
                  indent(level,fp);
                  if (cur_parblock_level == parblock_level) fputs("else\n", fp);
                } else {
                  if (cur_parblock_level == parblock_level) fputs(";\n",fp);
                  if (cur_parblock_level == parblock_level) indent(level,fp);
                  if (cur_parblock_level == parblock_level) fputs("else\n", fp);
                }
                print_main_part(ifn->else_n, level+1, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            }
            return;

        case TN_COND_EXPR:
            if (cur_parblock_level == parblock_level) fputs("(", fp);
            print_main_part(ifn->cond, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(") ? (", fp);
            print_main_part(ifn->then_n, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(") : (", fp);
            print_main_part(ifn->else_n, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(")", fp);
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
			list = get_vars_list(forn->stemnt, 2);

            print_main_part(forn->init, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
			if (cur_parblock_level == parblock_level) fputs("CActivity::", fp);
            print_main_part(forn->test, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
			leaf = find_func_name(forn->test);

            if (forn->test->hdr.which == LEAF_T)
                if (cur_parblock_level == parblock_level) fputs("()", fp);
            print_main_part(forn->incr, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level)  fputs("\n{\n", fp);
            print_main_part(forn->stemnt, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) 
			{
				if (!strcmp(leaf->data.sval->str, "main"))
					fputs("exit_system = TRUE;", fp);
				fputs("\n}\n", fp);
			}
			global = 1;
            break;

        case TN_FOR:
            if (cur_parblock_level == parblock_level) fputs("for (", fp);
            print_main_part(forn->init, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs("; ", fp);
            print_main_part(forn->test, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs("; ", fp);
            print_main_part(forn->incr, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(")\n", fp);
            print_main_part(forn->stemnt, level+1, fp, spawn_file, h_fp, parblock_level, cur_parblock_level);
            return;

        default:
            fprintf(fp, "Unknown type of for node.\n");
            break;
        }
        break;

    case NODE_T:
        switch (root->hdr.type) {
			// start of Parc extension
		case TN_PARBLOCK:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
			if (cur_parblock_level == parblock_level) 
			{
				treenode *tmp = root->rnode;
				unsigned long size = 0;
				while(tmp)
				{
					size++;
					tmp = tmp->rnode;
				}
				fprintf(fp, "    CActivationRecord record(%d, ", size);
				tmp = root->rnode;
				while(tmp)
				{
					list = get_vars_list(tmp->lnode, tmp->hdr.c_contxt->syms->clevel);
					print_sizeof_list(list, fp);
					tmp = tmp->rnode;
					if (tmp)
						fprintf(fp, " + ");
				}
			}
			if (cur_parblock_level == parblock_level) fprintf(fp, ");\n");
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
			if (cur_parblock_level == parblock_level) fprintf(fp, "    record += *__spRec;\n");
			if (cur_parblock_level == parblock_level) fprintf(fp, "    __RunParBlock(record, __spRec->m_static_record->parent);\n");
			if (cur_parblock_level == parblock_level) fprintf(fp, "	 Finalize(__spRec,childs_number);\n");
			break;
		case TN_PARBLOCK_EMPTY:
			if (cur_parblock_level == parblock_level-1)
			{
				fprintf(fp, "\nvoid CActivity::__Selector%d(CActivationRecord *__spRec", selector_counter_decl, "\0");
				list = get_vars_list(root->lnode, root->hdr.c_contxt->syms->clevel);
				if (list)
					fprintf(fp, ",");
				print_list(list, 1, fp);
				fprintf(fp, ")\n");
				
				fprintf(h_fp, "    void __Selector%d(CActivationRecord *__spRec %s ", selector_counter_decl, "\0");
				if (list)
					fprintf(h_fp, ",");
				print_list(list, 1, h_fp);
				fprintf(h_fp, ");\n");

				fprintf(spawn_file, "\n     case %d: {\n", selector_counter_decl);
				print_list(list, 0, spawn_file);
				fprintf(spawn_file, "\n     __Selector%d(__spRec", selector_counter_decl);

				if (list)
					fprintf(spawn_file, ",");
				print_list(list, 2, spawn_file);
				fprintf(spawn_file, ");\n}\n");
				fprintf(spawn_file, "\n				 break;");
				selector_counter_decl++;
				fprintf(fp, "\n{\n");
				print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level+1);  //   body
				fprintf(fp, "__SpawnParConstruct(__spRec);\n");
				fprintf(fp, "Finalize(__spRec,childs_number);\n}\n");
				print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);  // next block
			}
			else if (cur_parblock_level == parblock_level)
			{
//				if (root->rnode)
					//fprintf(fp, "    __RunParBlock(%d, ", selector_counter_call++, "\0");
					fprintf(fp, "    record.AddActivity(%d, ", selector_counter_call++, "\0");
//				else
//					fprintf(fp, "    __RunInPlaceParBlock(__spRec, %d, ", selector_counter_call++, "\0");
				list = get_vars_list(root->lnode, root->hdr.c_contxt->syms->clevel);
				print_sizeof_list(list, fp);
				print_addresses(list, fp);
				fprintf(fp, ");\n");
//				if (!root->rnode)
//					fprintf(fp, "	 Finalize(__spRec,childs_number);\n");

				print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);  // next , block
			}
			else if (cur_parblock_level < parblock_level-1)
			{
				print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level+1);  //   body
				print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);  // next block
			}

			break;
			// end of Parc extension

        case TN_TRANS_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_FUNC_DECL:
            decl_cnt++;
            if (root->lnode && (root->lnode->hdr.type == TN_IDENT))
                print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            else {
                if (cur_parblock_level == parblock_level) fputs("(",fp);
                print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                if (cur_parblock_level == parblock_level) fputs(")",fp);
            }
            if (cur_parblock_level == parblock_level) fputs("(",fp);
			if (root->rnode)
			{
				if (cur_parblock_level == parblock_level) fprintf(fp, "CActivationRecord *__spRec,");
			}
			else
			{
				if (cur_parblock_level == parblock_level) fprintf(fp, "CActivationRecord *__spRec");
			}
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(")",fp);
            decl_cnt--;
            break;

        case TN_FUNC_CALL:

            /* Only true functions are printed without parens. */
            if (is_function(root->lnode))
            {
                print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            }
            else
            {
                if (cur_parblock_level == parblock_level) fputs("(", fp);
                print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                if (cur_parblock_level == parblock_level) fputs(")", fp);
            }
            if (cur_parblock_level == parblock_level) fputs("(", fp);
			if (root->rnode)
			{
				symentry_t *sym;
				leafnode *leaf = find_func_name(root->lnode);
				sym = scopetab_find(root->hdr.c_contxt->syms->current, leaf->data.sval);
				if (sym)
					if (cur_parblock_level == parblock_level) 
						fprintf(fp, "__spRec,");
			}
			else
			{
				if (cur_parblock_level == parblock_level) fprintf(fp, "__spRec");
			}

            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(")", fp);
            break;

        case TN_BLOCK:
            if (cur_parblock_level == parblock_level) fputs("{\n", fp);
            print_main_part(root->lnode, level+1, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level+1, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            indent(level,fp);
            if (cur_parblock_level == parblock_level) fputs("}\n", fp);
            just_left_blk = 1;
            return;

        case TN_ARRAY_DECL:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs("[", fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs("]", fp);
            break;

        case TN_EXPR_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (root->rnode)
              if (cur_parblock_level == parblock_level) fputs(",", fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_NAME_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_ENUM_LIST:
            if (root->lnode
                  && (root->lnode->hdr.type != TN_ENUM_LIST))
              indent(level,fp);
            enum_list_cnt++;
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (root->rnode)
              if (cur_parblock_level == parblock_level) fputs(",\n",fp);
            indent(level,fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (--enum_list_cnt == 0)
              if (cur_parblock_level == parblock_level) fputs("\n",fp);
            break;

        case TN_FIELD_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_PARAM_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (root->rnode)
              if (cur_parblock_level == parblock_level) fputs(",",fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_IDENT_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_TYPE_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_DECL:
            if (decl_cnt == 0)
              indent(level,fp);
			if (!global)
			{
				decl_cnt++;
				print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
				print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
				if (--decl_cnt == 0)
					if (cur_parblock_level == parblock_level) 
						fputs(";\n",fp);
			}
            break;

        case TN_DECL_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if ((root->rnode && (root->rnode->hdr.type == TN_IDENT))
                 || (root->rnode->lnode
                     && ((root->rnode->lnode->hdr.type == TN_IDENT)
                         || (root->rnode->lnode->hdr.type == TN_PNTR))) )
              if (cur_parblock_level == parblock_level) fputs(",",fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_DECLS:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if ((root->rnode && (root->rnode->hdr.type == TN_IDENT))
                 || (root->rnode->lnode
                     && ((root->rnode->lnode->hdr.type == TN_IDENT)
                         || (root->rnode->lnode->hdr.type == TN_PNTR))) )
              if (cur_parblock_level == parblock_level) fputs(",",fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_STEMNT_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (root->lnode
                    && (!just_left_blk)
                    && (root->lnode->hdr.type != TN_STEMNT_LIST)) {
                if (cur_parblock_level == parblock_level)
					fputs(";\n", fp);
            }

            if (root->rnode != NULL) {
                print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                if (!just_left_blk) {
                    if (cur_parblock_level == parblock_level)
						fputs(";\n", fp);
                }
            }
            break;

        case TN_STEMNT:
            if (root->rnode && (root->rnode->hdr.type == TN_LABEL))
              indent(level-1,fp);
            else
              indent(level,fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_COMP_DECL:
            indent(level,fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(";\n",fp);
            break;

        case TN_BIT_FIELD:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(":",fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_PNTR:
            if (cur_parblock_level == parblock_level) fputs("*", fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_TYPE_NME:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_INIT_LIST:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(",",fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_INIT_BLK:
            if (cur_parblock_level == parblock_level) fputs("{", fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(",", fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs("}", fp);
            break;

        case TN_OBJ_DEF:
            leaf = (leafnode *) root;
            if (cur_parblock_level == parblock_level) fputs(toksym(leaf->hdr.tok,1), fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(" {\n",fp);
            print_main_part(root->rnode, level+1, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs("}",fp);
            break;

        case TN_OBJ_REF:
            leaf = (leafnode *) root;
            if (cur_parblock_level == parblock_level) fputs(toksym(leaf->hdr.tok,1), fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(" ",fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_CAST:
            decl_cnt++;    /* Not really, it's a hack. */
            if (cur_parblock_level == parblock_level) fputs("(",fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(")",fp);
            decl_cnt--;
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_JUMP:
            if (cur_parblock_level == parblock_level) fputs(toksym(root->hdr.tok,1), fp);
            if ((root->hdr.tok == RETURN) || (root->hdr.tok == GOTO))
            {
                /*  fputs("(",fp);  */
                print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                /*  fputs(")",fp);  */
            }
            break;

        case TN_SWITCH:
            if (cur_parblock_level == parblock_level) fputs("switch (", fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(")\n", fp);
            print_main_part(root->rnode, level+1, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_INDEX:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs("[",fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs("]",fp);
            break;

        case TN_DEREF:
            if (cur_parblock_level == parblock_level) fputs("*",fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (root->rnode && (root->rnode->hdr.type == TN_IDENT))
              print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            else {
              if (cur_parblock_level == parblock_level) fputs("(",fp);
              print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
              if (cur_parblock_level == parblock_level) fputs(")",fp);
            }
            break;

        case TN_SELECT:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);

            if (root->hdr.tok == ARROW)
                if (cur_parblock_level == parblock_level) fputs("->",fp);
            else
                if (cur_parblock_level == parblock_level) fputs(".",fp);

            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_ASSIGN:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(toksym(root->hdr.tok,1), fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_EXPR:
            switch (root->hdr.tok) {
              case CASE:
                if (cur_parblock_level == parblock_level) fputs(toksym(root->hdr.tok,1), fp);
                print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                break;

              case SIZEOF:
                if (cur_parblock_level == parblock_level) fputs(toksym(root->hdr.tok,0), fp);
                if (cur_parblock_level == parblock_level) fputs("(", fp);
                print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                if (cur_parblock_level == parblock_level) fputs(")", fp);
                break;

              case INCR:
              case DECR:
                print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                if (cur_parblock_level == parblock_level) fputs(toksym(root->hdr.tok,1), fp);
                print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                break;

              case B_AND:
                if (root->lnode == NULL) {
                  if (cur_parblock_level == parblock_level) fputs(toksym(root->hdr.tok,1), fp);
                  if (cur_parblock_level == parblock_level) fputs("(", fp);
                  print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                  if (cur_parblock_level == parblock_level) fputs(")", fp);
                  break;
                }

              default:
                if (cur_parblock_level == parblock_level) fputs("(", fp);
                print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                if (cur_parblock_level == parblock_level) fputs(toksym(root->hdr.tok,1), fp);
                print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
                if (cur_parblock_level == parblock_level) fputs(")", fp);
                break;
            }
            break;

        case TN_WHILE:
            if (cur_parblock_level == parblock_level) fputs("while (", fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(")\n", fp);
            print_main_part(root->rnode, level+1, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            return;

        case TN_DOWHILE:
            if (cur_parblock_level == parblock_level) fputs("do\n", fp);
            print_main_part(root->rnode, level+1, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if ((root->rnode->hdr.type == TN_STEMNT)
                    && (root->rnode->rnode->hdr.type != TN_BLOCK))
                if (cur_parblock_level == parblock_level) fputs(";", fp);
            if (cur_parblock_level == parblock_level) fputs("\n",fp);
            indent(level,fp);
            if (cur_parblock_level == parblock_level) fputs("while (", fp);
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (cur_parblock_level == parblock_level) fputs(")", fp);
            break;

        case TN_LABEL:
            print_main_part(root->lnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            if (root->lnode && (root->lnode->hdr.type != TN_LABEL))
              if (cur_parblock_level == parblock_level) fputs(":\n",fp);
            print_main_part(root->rnode, level, fp, h_fp, spawn_file, parblock_level, cur_parblock_level);
            break;

        case TN_EMPTY:
        default:
            fprintf(fp, "Unknown type of tree node (%d).\n", root->hdr.type);
            return;
        }
        break;
    }

    return;
}



