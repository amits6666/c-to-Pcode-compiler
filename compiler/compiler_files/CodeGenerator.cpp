#include <iostream>

using namespace std;

#include "CodeGenerator.h"

static int Stack_Address = 5;
const int MAX = 100;

int label_if = 0;
int label_ifelse = 0;
int label_for = 0;
int label_while = 0;
int label_cond = 0;
int label_doWhile = 0;
string breakJump = "";
int label_switch = 0;
int label_case = 0;



class Variable {
public:
	/* Think! what does a Variable contain? */
	string identifier, type;
	int address, size, pointerDepth, dimCount, typeSize;
	Variable *next;
	int* dimSizes;

	Variable() {
		next = NULL;
	}

	Variable(string key, string type, int address, int size, int pointerDepth = 0, int dimCount = 0, int* dimSizes = NULL, int typeSize = 1) {
		this->identifier = key;
		this->size = size;
		this->type = type;
		this->address = address;
		this->pointerDepth = pointerDepth;
		next = NULL;
		this->dimCount = dimCount;
		this->dimSizes = dimSizes;
		this->typeSize = typeSize;
	}

	friend class SymbolTable;
};

class SymbolTable {
	/* Think! what can you add to  symbol_table */
	Variable *head[MAX];

public:
	SymbolTable() {
		for (int i = 0; i < MAX; i++)
			head[i] = NULL;
	}

	// Function to find an identifier
	int find(string id) {
		int index = hashf(id);
		Variable *start = head[index];

		if (start == NULL)
			return -1;

		while (start != NULL) {

			if (start->identifier == id) {
				return start->address;
			}

			start = start->next;
		}

		return -1; // not found
	}

	Variable* GetVariable(string id){
		int index = hashf(id);
		Variable *start = head[index];

		if (start == NULL)
			return NULL;

		while (start != NULL) {

			if (start->identifier == id) {
				return start;
			}

			start = start->next;
		}

		return NULL; // not found
	}

	// Function to insert an identifier
	bool insert(string id, string type, int address, int size, int pointerDepth = 0, int dimCount = 0, int* dimSizes = NULL, int typeSize = 1) {
		int index = hashf(id);
		Variable *p = new Variable(id, type, address, size, pointerDepth, dimCount, dimSizes, typeSize);

		if (head[index] == NULL) {
			head[index] = p;
			return true;
		} else {
			Variable *start = head[index];
			while (start->next != NULL)
				start = start->next;
			start->next = p;
			return true;
		}

		return false;
	}

	int hashf(string id) {
		int asciiSum = 0;

		for (int i = 0; i < id.length(); i++) {
			asciiSum = asciiSum + id[i];
		}

		return (asciiSum % MAX);
	}
};

SymbolTable ST;

class TreeNode { //base class
public:
	/*you can add another son nodes */
	TreeNode *son1 = NULL;
	TreeNode *son2 = NULL;

	virtual ~TreeNode() {};

	TreeNode() {};

	/*recursive function to make Pcode*/
	virtual void gencode(string c_type = "coder") {
		if (son1 != NULL)
			son1->gencode(c_type);
		if (son2 != NULL)
			son2->gencode(c_type);
	};
};

/*
* you have to add functions/implement of gencode()... of derived classes
*/
class Assign : public TreeNode {
public:
	string op = "";

	Assign(string oper = ""){
		op = oper;
	}

	virtual void gencode(string c_type) {
		if (son1 != NULL)
			son1->gencode("codel");
		if (son2 != NULL)
			if(op == "")
				son2->gencode("coder");
			else{
				son1->gencode("coder");
				son2->gencode("coder");
				cout << op << endl;
			}
		cout << "sto " << endl;
	}
};

class Expression : public TreeNode {
public:
	string op;

	Expression(string oper) {
		op = oper;
	}

	virtual void gencode(string c_type) {
		if (son1 != NULL)
			son1->gencode("coder");

		if(op == "inc" || op == "dec"){
			TreeNode* varSon = (son2 == NULL)?son1:son2;
			varSon->gencode("codel");
			varSon->gencode("coder");
			cout << op << " 1" << endl;
			cout << "sto" << endl;
			if(son1 == NULL)
				son2->gencode("coder");
		}
		else{
			if (son2 != NULL)
				son2->gencode("coder");
			cout << op << endl;
		}
	}
};

class If : public TreeNode { //son1 - cond, son2 - then
public:
	TreeNode* elseNode = NULL;

	virtual void gencode(string c_type) {
		int label;
		if(elseNode == NULL)
			label = label_if++;
		else {
			label = label_ifelse++;
		}

		son1->gencode("coder");

		if(elseNode == NULL)
			cout << "fjp if_end" << label << endl;
		else
			cout << "fjp ifelse_else" << label << endl;

		son2->gencode();

		if(elseNode == NULL)
			cout << "if_end" << label << ":" << endl;
		else {
			cout << "ujp ifelse_end" << label << endl;
			cout << "ifelse_else" << label << ":" << endl;
			elseNode->gencode();
			cout << "ifelse_end" << label << ":" << endl;
		}
	}
};

class ConditionExpression : public TreeNode { //son1 - cond, son2 - then
public:
	TreeNode* elseNode = NULL;

	virtual void gencode(string c_type) {
		int label = label_cond++;

		son1->gencode("coder");

		cout << "fjp cond_else" << label << endl;

		son2->gencode();

		cout << "ujp condLabel_end" << label << endl;
		cout << "cond_else" << label << ":" << endl;
		elseNode->gencode();
		cout << "condLabel_end" << label << ":" << endl;

	}
};

class Break : public TreeNode {
public:
	virtual void gencode(string c_type) {
		cout << "ujp " << breakJump << endl;
	}
};

class For : public TreeNode { //son1 - statement, son2 - increment
public:
	TreeNode* init = NULL;
	TreeNode* test = NULL;

	virtual void gencode(string c_type) {
		int label = label_for++;
		string prevBreakJump = breakJump;
		breakJump = "for_end" + to_string(label);

		init->gencode("coder");

		cout << "for_loop" << label << ":" << endl;

		test->gencode("coder");

		cout << "fjp for_end" << label << endl;

		son1->gencode("coder");
		son2->gencode("coder");

		cout << "ujp for_loop" << label << endl;
		cout << "for_end" << label << ":" << endl;

		breakJump = prevBreakJump;
	}
};

class While : public TreeNode { //son1 - cond, son2 - statement
public:
	virtual void gencode(string c_type) {
		int label = label_while++;
		string prevBreakJump = breakJump;
		breakJump = "while_end" + to_string(label);

		cout << "while_loop" << label << ":" << endl;

		son1->gencode("coder");

		cout << "fjp while_end" << label << endl;

		son2->gencode();

		cout << "ujp while_loop" << label << endl;
		cout << "while_end" << label << ":" << endl;
		breakJump = prevBreakJump;
	}
};

class DoWhile :public TreeNode
{
public:
	virtual void gencode(string c_type){
		int label = label_doWhile++;
		string prevBreakJump = breakJump;
		breakJump = "doWhile_end" + to_string(label);
		cout << "doWhile_loop" << label << ":" << endl;
		if(son1) son1->gencode("coder");
		if(son2) son2->gencode("coder");
		cout << "fjp doWhile_end" << label << endl << "ujp doWhile_loop" << label  << endl << "doWhile_end" << label << ":" << endl;
		breakJump = prevBreakJump;
	}
};

class Switch : public TreeNode {
public:

	virtual void gencode(string c_type = "coder"){
		label_case = 0;
		string prevBreakJump = breakJump;
		breakJump = "switch_end" + to_string(label_switch);
		son1->gencode("coder");
		son2->gencode();
		cout << "switch" << label_switch << "_case" << label_case << ":" << endl;
		cout << "switch_end" << label_switch++ << ":" << endl;
		breakJump = prevBreakJump;
	}
};

class Case : public TreeNode {
public:

	virtual void gencode(string c_type = "coder"){
		cout << "switch" << label_switch << "_case" << label_case++ << ":" << endl;
		cout << "dpl" << endl;
		son1->gencode("coder");
		cout << "equ" << endl;
		cout << "fjp " << "switch" << label_switch << "_case" << label_case << endl;
		son2->gencode();
	}
};

class Id : public TreeNode {
public:
	string id_name;

	Id(string id_n) {
		id_name = id_n;
	}

	virtual void gencode(string c_type) {
		if (c_type == "codel") {
			cout << "ldc " << ST.find(id_name) << endl;
		}
		else if(c_type == "coder") {
			this->gencode("codel");
			cout << "ind" << endl;
		}
	}
};

class Declaration : public TreeNode {
public:
	treenode* typeNode;
	int pointerDepth = 0, dimCount = 0;
	int* dimSizes = NULL;

	virtual void gencode(string c_type) {
		int size, typeSize = 1;
		string typeString;
		switch (typeNode->hdr.tok)
		{
			case INT: {
				typeString = "int";
				typeSize = 1;
				break;
			}
			case FLOAT: {
				typeString = "float";
				typeSize = 1;
				break;
			}
			case DOUBLE: {
				typeString = "double";
				typeSize = 1;
				break;
			}
		}

		size = typeSize;
		for(int i = 0; i < dimCount; i++){
			size *= dimSizes[i];
		}

		if(pointerDepth != 0)
			size = 1;


		cout << "creating var " << static_cast<Id*>(son1)->id_name << " with address " << Stack_Address << endl;
		ST.insert(static_cast<Id*>(son1)->id_name, typeString, Stack_Address, size, pointerDepth, dimCount, dimSizes, typeSize); // you need to add the type and size according to declaration of identifier in AST
		Stack_Address += size;
	}
};

class PrintNode : public TreeNode {
public:
	virtual void gencode(string c_type = "coder"){
		son1->gencode("coder");
		cout << "print" << endl;
	}
};

template<typename T>
class Num : public TreeNode {
	T value;

public:
	T getValue() { return value; }

	Num(double number) { value = number; }

	virtual void gencode(string c_type) {
		cout << "ldc " << to_string(getValue()) << endl;
	}
};

class Dereference : public TreeNode {
public:
	int dereferenceDepth = 0;

	virtual void gencode(string c_type){
		son1->gencode(c_type);
		for(int i = 0; i < dereferenceDepth; i++){
			cout << "ind" << endl;
		}
	}

	string GetIdentifier(){
		return static_cast<Id*>(son1)->id_name;
	}
};

class ArrayAccess : public TreeNode {
public:
	int dimCount = 0;
	TreeNode** indicesNodes;
	TreeNode* id;
	string ident = "";
	virtual void gencode(string c_type){
		id->gencode("codel");

		//cout << "1" << endl;
		Variable arr = *ST.GetVariable(ident);
		//cout << "2" << endl;
		int accessShift = 0;
		int dimMul = arr.typeSize;
		//cout << "3" << endl;
		for(int i = 1; i < arr.dimCount; i++){
			dimMul *= arr.dimSizes[i];
		}
		//cout << "4" << endl;
		for(int i = 0; i < arr.dimCount; i++){
			indicesNodes[i]->gencode("coder");
			cout << "ixa " << dimMul << endl;
			if(i+1 != arr.dimCount)
				dimMul /= arr.dimSizes[i+1];
		}
		//cout << "5" << endl;
		if(c_type == "coder")
			cout << "ind" << endl;
	}
};



TreeNode *obj_tree(treenode *root);

/*
*	Input: Tree of objects 
*	Output: prints the Pcode on the console
*/
int code_recur(treenode *root) {
	TreeNode *tree_root = obj_tree(root);
	tree_root->gencode();
	return SUCCESS;
}

/*
*	This recursive function is the main method for Code Generation
*	Input: treenode (AST)
*	Output: Tree of objects 
*/
TreeNode *obj_tree(treenode *root) {
	if_node *ifn;
	for_node *forn;
	leafnode *leaf;
	if (!root) {
		return NULL;
	}

	switch (root->hdr.which) {
		case LEAF_T:
			leaf = (leafnode *) root;
			switch (leaf->hdr.type) {
				case TN_LABEL:
					/* Maybe you will use it later */
					break;

				case TN_IDENT:
					/* variable case */
					/*
							*	In order to get the identifier name you have to use:
							*	leaf->data.sval->str
							*/
				{
					Id *ident = new Id(leaf->data.sval->str);
					return ident;
				}

				case TN_COMMENT:
					/* Maybe you will use it later */
					break;

				case TN_ELLIPSIS:
					/* Maybe you will use it later */
					break;

				case TN_STRING:
					/* Maybe you will use it later */
					break;

				case TN_TYPE:
					/* Maybe you will use it later */
					break;

				case TN_INT:
					/* Constant case */
					/*
							*	In order to get the int value you have to use:
							*	leaf->data.ival
							*/
				{
					Num<int> *const_number = new Num<int>(leaf->data.ival);
					return const_number;
				}

				case TN_REAL:
					/* Constant case */
					/*
							*	In order to get the real value you have to use:
							*	leaf->data.dval
							*/
					Num<double> *const_number = new Num<double>(leaf->data.dval);
					return const_number;
			}
			break;

		case IF_T:
			ifn = (if_node *) root;
			switch (ifn->hdr.type) {

				case TN_IF:
					if (ifn->else_n == NULL) {
						/* if case (without else)*/
						If *if_obj = new If();
						if_obj->son1 = obj_tree(ifn->cond);
						if_obj->son2 = obj_tree(ifn->then_n);
						return if_obj;
					} else {
						/* if - else case*/
						If *if_obj = new If();
						if_obj->son1 = obj_tree(ifn->cond);
						if_obj->son2 = obj_tree(ifn->then_n);
						if_obj->elseNode = obj_tree(ifn->else_n);
						return if_obj;
					}
					break;

				case TN_COND_EXPR:
					/* (cond)?(exp):(exp); */
				{
					ConditionExpression* conditionExpression = new ConditionExpression();
					conditionExpression->son1 = obj_tree(ifn->cond);
					conditionExpression->son2 = obj_tree(ifn->then_n);
					conditionExpression->elseNode = obj_tree(ifn->else_n);
					return conditionExpression;
				}

				default:
					/* Maybe you will use it later */
					obj_tree(ifn->cond);
					obj_tree(ifn->then_n);
					obj_tree(ifn->else_n);
			}
			break;

		case FOR_T:
			forn = (for_node *) root;
			switch (forn->hdr.type) {

				case TN_FUNC_DEF:
					/* Function definition */
					/* e.g. int main(...) { ... } */
					/* Look at the output AST structure! */
					obj_tree(forn->init);
					obj_tree(forn->test);
					obj_tree(forn->incr);
					obj_tree(forn->stemnt);
					break;

				case TN_FOR:
					/* For case*/
					/* e.g. for(i=0;i<5;i++) { ... } */
					/* Look at the output AST structure! */
				{
					For *forNode = new For();
					forNode->init = obj_tree(forn->init);
					forNode->test = obj_tree(forn->test);
					forNode->son1 = obj_tree(forn->stemnt);
					forNode->son2 = obj_tree(forn->incr);
					return forNode;
				}

				default:
					/* Maybe you will use it later */
					obj_tree(forn->init);
					obj_tree(forn->test);
					obj_tree(forn->stemnt);
					obj_tree(forn->incr);
			}
			break;

		case NODE_T:
			switch (root->hdr.type) {
				case TN_PARBLOCK:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_PARBLOCK_EMPTY:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_TRANS_LIST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_FUNC_DECL:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_FUNC_CALL:
					/* Function call */
					if (strcmp(((leafnode *) root->lnode)->data.sval->str, "printf") == 0) {
						/* printf case */
						/* The expression that you need to print is located in */
						/* the currentNode->right->right sub tree */
						/* Look at the output AST structure! */
						PrintNode* printNode = new PrintNode();
						printNode->son1 = obj_tree(root->rnode->rnode);
						return printNode;
					} else {
						/* other function calls - for HW3 */
						obj_tree(root->lnode);
						obj_tree(root->rnode);
					}
					break;

				case TN_BLOCK:
					/* Maybe you will use it later */
					//TODO: i dont think this is right
				{
					cout << "reached block " << endl;
					TreeNode *block = new TreeNode();
					block->son1 = obj_tree(root->lnode);
					block->son2 = obj_tree(root->rnode);
					return block;
				}
				case TN_ARRAY_DECL:
					/* array declaration - for HW2 */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_EXPR_LIST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_NAME_LIST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_ENUM_LIST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_FIELD_LIST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_PARAM_LIST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_IDENT_LIST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_TYPE_LIST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_COMP_DECL:
					/* struct component declaration - for HW2 */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_DECL: {
					Declaration *declaration = new Declaration();
					if (root->rnode == NULL)
						break;
					else if(root->rnode->hdr.type == TN_IDENT)
						declaration->son1 = obj_tree(root->rnode);
					else if(root->rnode->hdr.type == TN_ARRAY_DECL) {
						treenode* p = root->rnode;
						while(p != NULL && p->hdr.type == TN_ARRAY_DECL) {
							declaration->dimCount++;
							p = p->lnode;
						}
						declaration->son1 = obj_tree(p);
						int dimCount = declaration->dimCount;
						declaration->dimSizes = new int[declaration->dimCount];
						p = root->rnode;
						while(p != NULL && p->hdr.type == TN_ARRAY_DECL) {
							declaration->dimSizes[--dimCount] = ((leafnode*)p->rnode)->data.ival;
							p = p->lnode;
						}
					}
					else if(root->rnode->lnode->hdr.type == TN_PNTR) {
						declaration->son1 = obj_tree(root->rnode->rnode);
						treenode* p = root->rnode->lnode;
						while(p != NULL && p->hdr.type == TN_PNTR) {
							declaration->pointerDepth++;
							p = p->rnode;
						}
					}
					
					declaration->typeNode = root->lnode->lnode;
					return declaration;
				}

				case TN_DECL_LIST:
					/* Maybe you will use it later */
				{
					TreeNode* decList = new TreeNode();
					decList->son1 = obj_tree(root->lnode);
					decList->son2 = obj_tree(root->rnode);
					return decList;
				}

				case TN_DECLS:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_STEMNT_LIST:
					/* Maybe you will use it later */
					//TODO: i dont think this is right
				{
					TreeNode *statementList = new TreeNode();
					statementList->son1 = obj_tree(root->lnode);
					statementList->son2 = obj_tree(root->rnode);
					return statementList;
				}
				case TN_STEMNT:
					/* Maybe you will use it later */
					//TODO: i dont think this is right
				{
					TreeNode *statement = new TreeNode();
					statement->son1 = obj_tree(root->lnode);
					statement->son2 = obj_tree(root->rnode);
					return statement;
				}
				case TN_BIT_FIELD:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_PNTR:
					/* pointer - for HW2! */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_TYPE_NME:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_INIT_LIST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_INIT_BLK:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_OBJ_DEF:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_OBJ_REF:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_CAST:
					/* Maybe you will use it later */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
					break;

				case TN_JUMP:
					if (root->hdr.tok == RETURN) {
						/* return jump - for HW2! */
						obj_tree(root->lnode);
						obj_tree(root->rnode);
					} else if (root->hdr.tok == BREAK) {
						/* break jump - for HW2! */
						Break *breakObj = new Break();
						return breakObj;
					} else if (root->hdr.tok == GOTO) {
						/* GOTO jump - for HW2! */
						obj_tree(root->lnode);
						obj_tree(root->rnode);
					}
					break;

				case TN_SWITCH:
				{
					/* Switch case - for HW2! */
					Switch* switchObj = new Switch();
					switchObj->son1 = obj_tree(root->lnode);
					switchObj->son2 = obj_tree(root->rnode);
					return switchObj;
				}
				case TN_INDEX: {
					/* call for array - for HW2! */
					ArrayAccess* arrayAccess = new ArrayAccess();
					treenode* p = root;
					while(p != NULL && p->hdr.type == TN_INDEX) {
						arrayAccess->dimCount++;
						p = p->lnode;
					}
					arrayAccess->id = obj_tree(p);
					if(p->hdr.type == TN_IDENT)
						arrayAccess->ident = static_cast<Id*>(arrayAccess->id)->id_name;
					else if(p->hdr.type == TN_DEREF)
						arrayAccess->ident = ((Dereference*)arrayAccess->id)->GetIdentifier();
					int dimCount = arrayAccess->dimCount;
					arrayAccess->indicesNodes = new TreeNode*[arrayAccess->dimCount];
					p = root;
					while(p != NULL && p->hdr.type == TN_INDEX) {
						arrayAccess->indicesNodes[--dimCount] = obj_tree(p->rnode);
						p = p->lnode;
					}
					return arrayAccess;
				}
				case TN_DEREF:
				{
					/* pointer derefrence - for HW2! */
					Dereference* dereference = new Dereference();
					treenode* p = root;
					while(p->hdr.type == TN_DEREF) {
						dereference->dereferenceDepth++;
						p = p->rnode;
					}
					dereference->son1 = obj_tree(p);
					return dereference;
				}
				case TN_SELECT:
					/* struct case - for HW2! */
					if (root->hdr.tok == ARROW) {
						/* Struct select case "->" */
						/* e.g. struct_variable->x; */
						obj_tree(root->lnode);
						obj_tree(root->rnode);
					} else {
						/* Struct select case "." */
						/* e.g. struct_variable.x; */
						obj_tree(root->lnode);
						obj_tree(root->rnode);
					}
					break;

				case TN_ASSIGN:
					if (root->hdr.tok == EQ) {
						/* Regular assignment "=" */
						/* e.g. x = 5; */
						Assign *ass_obj = new Assign();
						ass_obj->son1 = obj_tree(root->lnode);
						ass_obj->son2 = obj_tree(root->rnode);
						return ass_obj;
					} else if (root->hdr.tok == PLUS_EQ) {
						/* Plus equal assignment "+=" */
						/* e.g. x += 5; */
						Assign *ass_obj = new Assign("add");
						ass_obj->son1 = obj_tree(root->lnode);
						ass_obj->son2 = obj_tree(root->rnode);
						return ass_obj;
					} else if (root->hdr.tok == MINUS_EQ) {
						/* Minus equal assignment "-=" */
						/* e.g. x -= 5; */
						Assign *ass_obj = new Assign("sub");
						ass_obj->son1 = obj_tree(root->lnode);
						ass_obj->son2 = obj_tree(root->rnode);
						return ass_obj;
					} else if (root->hdr.tok == STAR_EQ) {
						/* Multiply equal assignment "*=" */
						/* e.g. x *= 5; */
						Assign *ass_obj = new Assign("mul");
						ass_obj->son1 = obj_tree(root->lnode);
						ass_obj->son2 = obj_tree(root->rnode);
						return ass_obj;
					} else if (root->hdr.tok == DIV_EQ) {
						/* Divide equal assignment "/=" */
						/* e.g. x /= 5; */
						Assign *ass_obj = new Assign("div");
						ass_obj->son1 = obj_tree(root->lnode);
						ass_obj->son2 = obj_tree(root->rnode);
						return ass_obj;
					}
					break;

				case TN_EXPR:
					switch (root->hdr.tok) {
						case CASE:
							/* you should not get here */
							obj_tree(root->lnode);
							obj_tree(root->rnode);
							break;

						case INCR:
							/* Increment token "++" */
						{
							Expression *expr_obj = new Expression("inc");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}

						case DECR:
							/* Decrement token "--" */
						{
							Expression *expr_obj = new Expression("dec");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case PLUS:
							/* Plus token "+" */
						{
							Expression *expr_obj = new Expression("add");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case MINUS:
							/* Minus token "-" */
						{
							Expression *expr_obj = new Expression("sub");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							if(expr_obj->son1 == NULL)
								expr_obj->op = "neg";
							return expr_obj;
						}
						case DIV:
							/* Divide token "/" */
						{
							Expression *expr_obj = new Expression("div");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case STAR:
							/* multiply token "*" */
						{
							Expression *expr_obj = new Expression("mul");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case AND:
							/* And token "&&" */
						{
							Expression *expr_obj = new Expression("and");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case OR:
							/* Or token "||" */
						{
							Expression *expr_obj = new Expression("or");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case NOT:
							/* Not token "!" */
						{
							Expression *expr_obj = new Expression("not");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case GRTR:
							/* Greater token ">" */
						{
							Expression *expr_obj = new Expression("grt");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case LESS:
							/* Less token "<" */
						{
							Expression *expr_obj = new Expression("les");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case EQUAL:
							/* Equal token "==" */
						{
							Expression *expr_obj = new Expression("equ");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case NOT_EQ:
							/* Not equal token "!=" */
						{
							Expression *expr_obj = new Expression("neq");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case LESS_EQ:
							/* Less or equal token "<=" */
						{
							Expression *expr_obj = new Expression("leq");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						case GRTR_EQ:
							/* Greater or equal token ">=" */
						{
							Expression *expr_obj = new Expression("geq");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							return expr_obj;
						}
						default:
							obj_tree(root->lnode);
							obj_tree(root->rnode);
							break;
					}
					break;

				case TN_WHILE:
					/* While case */
				{
					While* whileNode = new While();
					whileNode->son1 = obj_tree(root->lnode);
					whileNode->son2 = obj_tree(root->rnode);
					return whileNode;
				}

				case TN_DOWHILE:
					/* Do-While case */
				{
					DoWhile* doWhile = new DoWhile();
					doWhile->son1 = obj_tree(root->rnode);
					doWhile->son2 = obj_tree(root->lnode);
					return doWhile;
				}

				case TN_LABEL:
				{
					if(root->lnode->hdr.tok == CASE){
						Case* caseObj  = new Case();
						caseObj->son1 = obj_tree(root->lnode->rnode);
						caseObj->son2 = obj_tree(root->rnode);
						return caseObj;
					}
					break;
				}

				default:
					obj_tree(root->lnode);
					obj_tree(root->rnode);
			}
			break;

		case NONE_T:
			printf("Error: Unknown node type!\n");
			exit(FAILURE);
	}
}

/*
*	This function prints all the variables on your symbol table with their data
*	Input: treenode (AST)
*	Output: prints the Symbol Table on the console
*/
void print_symbol_table(treenode *root) {
	printf("---------------------------------------\n");
	printf("Showing the Symbol Table:\n");

	/*
	*	add your code here
	*/
}
