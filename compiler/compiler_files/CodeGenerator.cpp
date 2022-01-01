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
string currentClassDeclaration = "";
bool switchCondConst = false;
double switchConstCondCaseVal = 0;



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

class Struct {
	Variable *head[MAX];
public:
	string identifier;
	int size;
	Struct *next;

	Struct() {
		next = NULL;
		for (int i = 0; i < MAX; i++)
			head[i] = NULL;
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
	bool insert(string id, string type, int size, int pointerDepth = 0, int dimCount = 0, int* dimSizes = NULL, int typeSize = 1) {
		int index = hashf(id);
		Variable *p = new Variable(id, type, this->size, size, pointerDepth, dimCount, dimSizes, typeSize);
		//cout << id << " at offset " << this->size << endl;
		this->size += size;

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

	Struct(string key, int size = 0) {
		this->identifier = key;
		this->size = size;
		next = NULL;
		for (int i = 0; i < MAX; i++)
			head[i] = NULL;
	}

	friend class StructTable;
};

class StructTable {
	Struct *head[MAX];
public:

	StructTable() {
		for (int i = 0; i < MAX; i++)
			head[i] = NULL;
	}

	Struct* GetStruct(string id){
		int index = hashf(id);
		Struct *start = head[index];
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
	bool insert(string id, int size = 0) {
		int index = hashf(id);
		Struct *p = new Struct(id, size);
		if (head[index] == NULL) {
			head[index] = p;
			return true;
		} else {
			Struct *start = head[index];
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

StructTable structTable;

int TypeToSize(string type, bool isPointer = false){
	if(isPointer || type == "int" || type == "double" || type == "float")
		return 1;
	else
		return structTable.GetStruct(type)->size;
}

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

class VarTreeNode : public TreeNode {
public:
	virtual string GetIdentifier(){
		cout << "this shouldn't happen 1" << endl;
		return "this shouldn't happen 1";
	}
	virtual string GetType(){
		cout << "this shouldn't happen 2" << endl;
		return "this shouldn't happen 2";
	}
	virtual int GetPointerDepth(){
		cout << "this shouldn't happen 3" << endl;
		return -1;
	}
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
	bool condConst = false;
	double condVal;

	virtual void gencode(string c_type) {
		int label;
		if(condConst){
			//cout << "if is const" << endl;
			if(condVal)
				son2->gencode();
			else if(elseNode != NULL)
				elseNode->gencode();
		}
		else {
			if (elseNode == NULL)
				label = label_if++;
			else {
				label = label_ifelse++;
			}

			son1->gencode("coder");

			if (elseNode == NULL)
				cout << "fjp if_end" << label << endl;
			else
				cout << "fjp ifelse_else" << label << endl;

			son2->gencode();

			if (elseNode == NULL)
				cout << "if_end" << label << ":" << endl;
			else {
				cout << "ujp ifelse_end" << label << endl;
				cout << "ifelse_else" << label << ":" << endl;
				elseNode->gencode();
				cout << "ifelse_end" << label << ":" << endl;
			}
		}
	}
};

class ConditionExpression : public TreeNode { //son1 - cond, son2 - then
public:
	TreeNode* elseNode = NULL;
	bool condConst = false;
	double condVal;

	virtual void gencode(string c_type) {
		if(condConst){
			if(condVal)
				son2->gencode();
			else
				elseNode->gencode();
		}
		else {
			int label = label_cond++;

			son1->gencode("coder");

			cout << "fjp cond_else" << label << endl;

			son2->gencode();

			cout << "ujp condLabel_end" << label << endl;
			cout << "cond_else" << label << ":" << endl;
			elseNode->gencode();
			cout << "condLabel_end" << label << ":" << endl;
		}
	}
};

class Break : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if(breakJump != "")
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
	bool condConst = false;
	double condVal;

	virtual void gencode(string c_type = "coder"){
		switchCondConst = condConst;
		if(!condConst) {
			label_case = 0;
			string prevBreakJump = breakJump;
			breakJump = "switch_end" + to_string(label_switch);
			son1->gencode("coder");
			son2->gencode();
			cout << "switch" << label_switch << "_case" << label_case << ":" << endl;
			cout << "switch_end" << label_switch++ << ":" << endl;
			breakJump = prevBreakJump;
		}
		else{
			switchConstCondCaseVal = condVal;
			son2->gencode();
		}
	}
};

class Case : public TreeNode {
public:
	double val;

	virtual void gencode(string c_type = "coder"){
		if(!switchCondConst) {
			cout << "switch" << label_switch << "_case" << label_case++ << ":" << endl;
			cout << "dpl" << endl;
			son1->gencode("coder");
			cout << "equ" << endl;
			cout << "fjp " << "switch" << label_switch << "_case" << label_case << endl;
			son2->gencode();
		}
		else if(val == switchConstCondCaseVal){
			son2->gencode();
		}
	}
};

class Id : public VarTreeNode {
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

	virtual string GetIdentifier(){
		return id_name;
	}
	virtual string GetType(){
		return ST.GetVariable(GetIdentifier())->type;
	}
	virtual int GetPointerDepth(){
		return ST.GetVariable(GetIdentifier())->pointerDepth;
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
		if(typeNode->hdr.type == TN_TYPE) {
			switch (typeNode->hdr.tok) {
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
		}
		else {
			typeString = ((leafnode*)(typeNode->lnode))->data.sval->str;
			typeSize = structTable.GetStruct(typeString)->size;
		}

		size = typeSize;
		for(int i = 0; i < dimCount; i++){
			size *= dimSizes[i];
		}

		if(pointerDepth != 0)
			size = 1;


		//cout << "creating var " << static_cast<Id*>(son1)->id_name << " with address " << Stack_Address << endl;
		ST.insert(static_cast<Id*>(son1)->id_name, typeString, Stack_Address, size, pointerDepth, dimCount, dimSizes, typeSize); // you need to add the type and size according to declaration of identifier in AST
		Stack_Address += size;
	}
};

class ClassDeclaration : public TreeNode {
public:
	virtual void gencode(string c_type) {
		structTable.insert(static_cast<VarTreeNode*>(son1)->GetIdentifier());
		currentClassDeclaration = static_cast<VarTreeNode*>(son1)->GetIdentifier();
		son2->gencode(c_type);
	}
};

class ClassComponentDeclaration : public TreeNode {
public:
	treenode* typeNode;
	int pointerDepth = 0, dimCount = 0;
	int* dimSizes = NULL;

	virtual void gencode(string c_type) {
		int size, typeSize = 1;
		string typeString;
		if(typeNode->hdr.type == TN_TYPE) {
			switch (typeNode->hdr.tok) {
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
		}
		else {
			typeString = ((leafnode*)(typeNode->lnode))->data.sval->str;
			typeSize = structTable.GetStruct(typeString)->size;
		}

		size = typeSize;
		for(int i = 0; i < dimCount; i++){
			size *= dimSizes[i];
		}

		if(pointerDepth != 0)
			size = 1;


		//cout << "creating component var " << static_cast<Id*>(son1)->id_name << endl;
		structTable.GetStruct(currentClassDeclaration)->insert(static_cast<Id*>(son1)->id_name, typeString, size, pointerDepth, dimCount, dimSizes, typeSize);
	}
};

class StructSelector : public VarTreeNode {
public:
	bool arrow;
	virtual void gencode(string c_type = "coder"){
		son1->gencode(arrow?"coder":"codel");
		cout << "inc " << structTable.GetStruct(static_cast<VarTreeNode*>(son1)->GetType())->GetVariable(static_cast<VarTreeNode*>(son2)->GetIdentifier())->address << endl;

		if(c_type == "coder") {
			cout << "ind" << endl;
		}
	}

	virtual string GetIdentifier(){
		return static_cast<VarTreeNode*>(son1)->GetIdentifier();
	}
	virtual string GetType(){
		return structTable.GetStruct(static_cast<VarTreeNode*>(son1)->GetType())->GetVariable(static_cast<VarTreeNode*>(son2)->GetIdentifier())->type;
	}
	virtual int GetPointerDepth(){
		return static_cast<VarTreeNode*>(son1)->GetPointerDepth();
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

class Dereference : public VarTreeNode {
public:
	int dereferenceDepth = 0;

	virtual void gencode(string c_type){
		son1->gencode(c_type);
		for(int i = 0; i < dereferenceDepth; i++){
			cout << "ind" << endl;
		}
	}

	virtual string GetIdentifier(){
		return static_cast<VarTreeNode*>(son1)->GetIdentifier();
	}
	virtual string GetType(){
		return static_cast<VarTreeNode*>(son1)->GetType();
	}
	virtual int GetPointerDepth(){
		return static_cast<VarTreeNode*>(son1)->GetPointerDepth() - dereferenceDepth;
	}
};

class ArrayAccess : public VarTreeNode {
public:
	int dimCount = 0;
	TreeNode** indicesNodes;
	TreeNode* id;
	string ident = "";
	virtual void gencode(string c_type){
		id->gencode("codel");

		Variable* arr = ST.GetVariable(ident);
		int dimMul = 1;
		if(arr) {
			dimMul = TypeToSize(GetType(), GetPointerDepth()>0);
			for (int i = 1; i < dimCount; i++) {
				dimMul *= arr->dimSizes[i];
			}
		}
		//cout << "arr dim count " << arr.dimCount << endl;
		for(int i = 0; i < dimCount; i++){
			indicesNodes[i]->gencode("coder");
			cout << "ixa " << dimMul << endl;
			if(i+1 != dimCount)
				dimMul /= arr->dimSizes[i+1];
		}
		if(dimCount == 0) {
			indicesNodes[0]->gencode("coder");
			cout << "ixa " << dimMul << endl;
		}
		if(c_type == "coder")
			cout << "ind" << endl;
	}

	virtual string GetIdentifier(){
		return static_cast<VarTreeNode*>(id)->GetIdentifier();
	}
	virtual string GetType(){
		return static_cast<VarTreeNode*>(id)->GetType();
	}
	virtual int GetPointerDepth(){
		return static_cast<VarTreeNode*>(id)->GetPointerDepth();
	}
};



TreeNode *obj_tree(treenode *root);
bool calculate_expression(treenode *root, double &ret);
bool search_case(treenode *root, double src);

/*
 * 	Input: Tree of expression and ret var
 * 	Output: returns is the expression constant, if it is then ret is set to its value
 */
bool calculate_expression(treenode *root, double &ret) {
	leafnode *leaf;
	if_node *ifn;
	if (!root) {
		return true;
	}
	//cout << "recur " << root->hdr.type << endl;

	switch (root->hdr.which) {
		case LEAF_T:
			leaf = (leafnode *) root;
			switch (leaf->hdr.type) {

				case TN_IDENT:
				{
					return false;
				}

				case TN_INT:
					/* Constant case */
					/*
							*	In order to get the int value you have to use:
							*	leaf->data.ival
							*/
				{
					ret = (leaf->data.ival);
					return true;
				}

				case TN_REAL: {
					/* Constant case */
					/*
							*	In order to get the real value you have to use:
							*	leaf->data.dval
							*/
					ret = (leaf->data.dval);
					return true;
				}
			}
			break;
		case IF_T:
			ifn = (if_node *) root;
			switch (ifn->hdr.type) {
				case TN_COND_EXPR:{
					double retCond;
					if(calculate_expression(ifn->cond, retCond)){
						if(retCond)
							return (calculate_expression(ifn->then_n, ret));
						else
							return (calculate_expression(ifn->else_n, ret));
					}
					return false;
				}
			}
		case NODE_T:
			switch (root->hdr.type) {
				case TN_EXPR:
					switch (root->hdr.tok) {
						case CASE:
							break;

						case INCR:
							/* Increment token "++" */
						{
							double returned;
							treenode* varSon = (root->rnode == NULL)?root->lnode:root->rnode;
							if (calculate_expression(varSon, returned)){
								ret = returned++;
								return true;
							}
							else
								return false;
						}

						case DECR:
							/* Decrement token "--" */
						{
							double returned;
							treenode* varSon = (root->rnode == NULL)?root->lnode:root->rnode;
							if (calculate_expression(varSon, returned)){
								ret = returned--;
								return true;
							}
							else
								return false;
						}
						case PLUS:
							/* Plus token "+" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(!(const1 && const2))
								return false;

							ret = ret1 + ret2;
							return true;
						}
						case MINUS:
							/* Minus token "-" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(!(const1 && const2))
								return false;

							ret = ret1 - ret2;
							return true;
						}
						case DIV:
							/* Divide token "/" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);
							//cout << "div: " << to_string(const1) << " | " << to_string(const2) << " | " << to_string(ret1) << " | " << to_string(ret2) << endl;
							if(const1 && const2)
								ret = ret1 / ret2;
							else if(const1 && ret1 == 0)
								ret = 0;
							else
								return false;

							return true;
						}
						case STAR:
							/* multiply token "*" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);
							//cout << "star: " << to_string(const1) << " | " << to_string(const2) << " | " << to_string(ret1) << " | " << to_string(ret2) << endl;
							if(const1 && const2)
								ret = ret1 * ret2;
							else if((const1 && (ret1 == 0)) || (const2 && (ret2 == 0)))
								ret = 0;
							else
								return false;

							return true;
						}
						case AND:
							/* And token "&&" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(const1 && const2)
								ret = ret1 && ret2;
							else if((const1 && ret1 == 0) || (const2 && ret2 == 0))
								ret = 0;
							else
								return false;

							return true;
						}
						case OR:
							/* Or token "||" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(const1 && const2)
								ret = ret1 || ret2;
							else if((const1 && ret1 != 0) || (const2 && ret2 != 0))
								ret = 1;
							else
								return false;

							return true;
						}
						case NOT:
							/* Not token "!" */
						{
							double ret1;
							bool const1;
							const1 = calculate_expression(root->lnode, ret1);

							if(!(const1))
								return false;

							ret = !ret1;
							return true;
						}
						case GRTR:
							/* Greater token ">" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(!(const1 && const2))
								return false;

							ret = ret1 > ret2;
							return true;
						}
						case LESS:
							/* Less token "<" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(!(const1 && const2))
								return false;

							ret = ret1 < ret2;
							return true;
						}
						case EQUAL:
							/* Equal token "==" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(!(const1 && const2))
								return false;

							ret = ret1 == ret2;
							return true;
						}
						case NOT_EQ:
							/* Not equal token "!=" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(!(const1 && const2))
								return false;

							ret = ret1 != ret2;
							return true;
						}
						case LESS_EQ:
							/* Less or equal token "<=" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(!(const1 && const2))
								return false;

							ret = ret1 <= ret2;
							return true;
						}
						case GRTR_EQ:
							/* Greater or equal token ">=" */
						{
							double ret1, ret2;
							bool const1, const2;
							const1 = calculate_expression(root->lnode, ret1);
							const2 = calculate_expression(root->rnode, ret2);

							if(!(const1 && const2))
								return false;

							ret = ret1 >= ret2;
							return true;
						}
						default:
							cout << "calculate_expression expression operation unrecognized" << endl;
							double ret;
							return calculate_expression(root->lnode, ret) && calculate_expression(root->rnode, ret);

					}
					break;

				default:
					cout << "calculate_expression node unrecognized" << endl;
					double ret;
					return calculate_expression(root->lnode, ret) && calculate_expression(root->rnode, ret);

			}
			break;

		case NONE_T:
			printf("Error: Unknown node type!\n");
			exit(FAILURE);

		default:
			//cout << "why" << endl;
			double ret;
			return calculate_expression(root->lnode, ret) && calculate_expression(root->rnode, ret);
	}
}

bool search_case(treenode *root, double src) {
	if (!root || root->hdr.which == LEAF_T) {
		return false;
	}

	if((root->hdr.which == NODE_T) && (root->hdr.type == TN_EXPR) && (root->hdr.tok == CASE)){
		double ret;
		return (calculate_expression(root->rnode, ret) && (ret == src));
	}

	return search_case(root->lnode, src) || search_case(root->rnode, src);
}

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
	//cout << "recur " << root->hdr.type << endl;

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
					//cout << "ident: " << leaf->data.sval->str << endl;
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
						double ret;
						//cout << "if " << endl;
						if(calculate_expression(ifn->cond, ret)){
							//cout << "(const) ret: " << to_string(ret) << endl;
							if_obj->condConst = true;
							if_obj->condVal = ret;
						}
						//cout << "if end" << endl;
						return if_obj;
					} else {
						/* if - else case*/
						If *if_obj = new If();
						if_obj->son1 = obj_tree(ifn->cond);
						if_obj->son2 = obj_tree(ifn->then_n);
						if_obj->elseNode = obj_tree(ifn->else_n);
						double ret;
						if(calculate_expression(ifn->cond, ret)){
							if_obj->condConst = true;
							if_obj->condVal = ret;
						}
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
					double ret;
					if(calculate_expression(ifn->cond, ret)){
						conditionExpression->condConst = true;
						conditionExpression->condVal = ret;
					}
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

				case TN_TRANS_LIST:{
					TreeNode *node = new TreeNode();
					node->son1 = obj_tree(root->lnode);
					node->son2 = obj_tree(root->rnode);
					return node;
				}

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
				{
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

				case TN_FIELD_LIST: {
					/* Maybe you will use it later */
					TreeNode *node = new TreeNode();
					node->son1 = obj_tree(root->lnode);
					node->son2 = obj_tree(root->rnode);
					return node;
				}
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

				case TN_TYPE_LIST: {
					TreeNode* node = new TreeNode();
					node->son1 = obj_tree(root->lnode);
					node->son2 = obj_tree(root->rnode);
					return node;
				}

				case TN_COMP_DECL: {
					ClassComponentDeclaration *declaration = new ClassComponentDeclaration();
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

				case TN_DECL: {
					if(root->lnode->lnode->hdr.type != TN_TYPE && root->lnode->lnode->hdr.type != TN_ARRAY_DECL && root->lnode->lnode->hdr.type != TN_OBJ_REF) {
						TreeNode* node = new TreeNode();
						node->son1 = obj_tree(root->lnode);
						node->son2 = obj_tree(root->rnode);
						return node;
					}
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
				{
					TreeNode *statementList = new TreeNode();
					statementList->son1 = obj_tree(root->lnode);
					statementList->son2 = obj_tree(root->rnode);
					return statementList;
				}
				case TN_STEMNT:
					/* Maybe you will use it later */
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

				case TN_OBJ_DEF: {
					ClassDeclaration* classDeclaration = new ClassDeclaration();
					classDeclaration->son1 = obj_tree(root->lnode);
					classDeclaration->son2 = obj_tree(root->rnode);
					return classDeclaration;
				}

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
					double ret;
					if(calculate_expression(root->lnode, ret)){
						switchObj->condConst = true;
						switchObj->condVal = ret;

					}
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
					arrayAccess->ident = static_cast<VarTreeNode*>(arrayAccess->id)->GetIdentifier();
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
				case TN_SELECT: {
					/* struct case - for HW2! */
					StructSelector* structSelector = new StructSelector();
					structSelector->son1 = obj_tree(root->lnode);
					structSelector->son2 = obj_tree(root->rnode);
					structSelector->arrow = (root->hdr.tok == ARROW);
					return structSelector;
				}
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
						double ret2;
						if(calculate_expression(root->rnode, ret2)) {
							if(ret2 == 0)
								return NULL;

							Assign *ass_obj = new Assign("add");
							ass_obj->son1 = obj_tree(root->lnode);
							ass_obj->son2 = new Num<double>(ret2);
							return ass_obj;
						}
						Assign *ass_obj = new Assign("add");
						ass_obj->son1 = obj_tree(root->lnode);
						ass_obj->son2 = obj_tree(root->rnode);
						return ass_obj;
					} else if (root->hdr.tok == MINUS_EQ) {
						/* Minus equal assignment "-=" */
						/* e.g. x -= 5; */
						double ret2;
						if(calculate_expression(root->rnode, ret2)) {
							if(ret2 == 0)
								return NULL;

							Assign *ass_obj = new Assign("sub");
							ass_obj->son1 = obj_tree(root->lnode);
							ass_obj->son2 = new Num<double>(ret2);
							return ass_obj;
						}
						Assign *ass_obj = new Assign("sub");
						ass_obj->son1 = obj_tree(root->lnode);
						ass_obj->son2 = obj_tree(root->rnode);
						return ass_obj;
					} else if (root->hdr.tok == STAR_EQ) {
						/* Multiply equal assignment "*=" */
						/* e.g. x *= 5; */
						double ret2;
						if(calculate_expression(root->rnode, ret2)) {
							if(ret2 == 1)
								return NULL;
							else if(ret2 == 0){
								Assign *ass_obj = new Assign();
								ass_obj->son1 = obj_tree(root->lnode);
								ass_obj->son2 = new Num<double>(0);
								return ass_obj;
							}
							else {
								Assign *ass_obj = new Assign("mul");
								ass_obj->son1 = obj_tree(root->lnode);
								ass_obj->son2 = new Num<double>(ret2);
								return ass_obj;
							}
						}
						Assign *ass_obj = new Assign("mul");
						ass_obj->son1 = obj_tree(root->lnode);
						ass_obj->son2 = obj_tree(root->rnode);
						return ass_obj;
					} else if (root->hdr.tok == DIV_EQ) {
						/* Divide equal assignment "/=" */
						/* e.g. x /= 5; */
						double ret2;
						if(calculate_expression(root->rnode, ret2)) {
							if(ret2 == 1)
								return NULL;
							else {
								Assign *ass_obj = new Assign("div");
								ass_obj->son1 = obj_tree(root->lnode);
								ass_obj->son2 = new Num<double>(ret2);
								return ass_obj;
							}
						}
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
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1)) {
									if (ret1 == 0)
										return obj_tree(root->rnode);
									else
										expr_obj->son1 = new Num<double>(ret1);
								}
								else if(calculate_expression(root->rnode, ret2)) {
									if (ret2 == 0)
										return obj_tree(root->lnode);
									else
										expr_obj->son2 = new Num<double>(ret2);
								}
							}

							return expr_obj;
						}
						case MINUS:
							/* Minus token "-" */
						{
							Expression *expr_obj = new Expression("sub");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1)) {
									if (ret1 == 0)
										expr_obj->son1 = NULL;
									else
										expr_obj->son1 = new Num<double>(ret1);
								}
								else if(calculate_expression(root->rnode, ret2)) {
									if (ret2 == 0)
										return obj_tree(root->lnode);
									else
										expr_obj->son2 = new Num<double>(ret2);
								}
							}

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
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1)) {
									expr_obj->son1 = new Num<double>(ret1);
								}
								else if(calculate_expression(root->rnode, ret2)) {
									if (ret2 == 1)
										return obj_tree(root->lnode);
									else
										expr_obj->son2 = new Num<double>(ret2);
								}
							}

							return expr_obj;
						}
						case STAR:
							/* multiply token "*" */
						{
							Expression *expr_obj = new Expression("mul");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1)) {
									if (ret1 == 1)
										return obj_tree(root->rnode);
									else
										expr_obj->son1 = new Num<double>(ret1);
								}
								else if(calculate_expression(root->rnode, ret2)) {
									if (ret2 == 1)
										return obj_tree(root->lnode);
									else
										expr_obj->son2 = new Num<double>(ret2);
								}
							}

							return expr_obj;
						}
						case AND:
							/* And token "&&" */
						{
							Expression *expr_obj = new Expression("and");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1)) {
									if (ret1 != 0)
										return obj_tree(root->rnode);
									else
										expr_obj->son1 = new Num<double>(ret1);
								}
								else if(calculate_expression(root->rnode, ret2)) {
									if (ret2 != 0)
										return obj_tree(root->lnode);
									else
										expr_obj->son2 = new Num<double>(ret2);
								}
							}

							return expr_obj;
						}
						case OR:
							/* Or token "||" */
						{
							Expression *expr_obj = new Expression("or");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1)) {
									if (ret1 == 0)
										return obj_tree(root->rnode);
									else
										expr_obj->son1 = new Num<double>(ret1);
								}
								else if(calculate_expression(root->rnode, ret2)) {
									if (ret2 == 0)
										return obj_tree(root->lnode);
									else
										expr_obj->son2 = new Num<double>(ret2);
								}
							}

							return expr_obj;
						}
						case NOT:
							/* Not token "!" */
						{
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(!ret);
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
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1))
									expr_obj->son1 = new Num<double>(ret1);
								else if(calculate_expression(root->rnode, ret2))
									expr_obj->son2 = new Num<double>(ret2);
							}

							return expr_obj;
						}
						case LESS:
							/* Less token "<" */
						{
							Expression *expr_obj = new Expression("les");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1))
									expr_obj->son1 = new Num<double>(ret1);
								else if(calculate_expression(root->rnode, ret2))
									expr_obj->son2 = new Num<double>(ret2);
							}

							return expr_obj;
						}
						case EQUAL:
							/* Equal token "==" */
						{
							Expression *expr_obj = new Expression("equ");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1))
									expr_obj->son1 = new Num<double>(ret1);
								else if(calculate_expression(root->rnode, ret2))
									expr_obj->son2 = new Num<double>(ret2);
							}

							return expr_obj;
						}
						case NOT_EQ:
							/* Not equal token "!=" */
						{
							Expression *expr_obj = new Expression("neq");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1))
									expr_obj->son1 = new Num<double>(ret1);
								else if(calculate_expression(root->rnode, ret2))
									expr_obj->son2 = new Num<double>(ret2);
							}

							return expr_obj;
						}
						case LESS_EQ:
							/* Less or equal token "<=" */
						{
							Expression *expr_obj = new Expression("leq");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1))
									expr_obj->son1 = new Num<double>(ret1);
								else if(calculate_expression(root->rnode, ret2))
									expr_obj->son2 = new Num<double>(ret2);
							}

							return expr_obj;
						}
						case GRTR_EQ:
							/* Greater or equal token ">=" */
						{
							Expression *expr_obj = new Expression("geq");
							expr_obj->son1 = obj_tree(root->lnode);
							expr_obj->son2 = obj_tree(root->rnode);
							double ret;
							if(calculate_expression(root, ret))
								return new Num<double>(ret);
							else{
								double ret1, ret2;
								if(calculate_expression(root->lnode, ret1))
									expr_obj->son1 = new Num<double>(ret1);
								else if(calculate_expression(root->rnode, ret2))
									expr_obj->son2 = new Num<double>(ret2);
							}

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
						double ret;
						if(calculate_expression(root->lnode->rnode, ret)) {
							caseObj->val = ret;
						}
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
