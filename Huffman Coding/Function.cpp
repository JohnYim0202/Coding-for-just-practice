#include "Header.h"

/* When you put a root of the tree to this function,
   it assigns a code word to each leaf. It is implemented
   by recursive function. */
void code_assign(class Tree* root)
{
	if (root->ptr_0)
	{
		(root->ptr_0)->code = (root->code) + "0";
		(root->ptr_1)->code = (root->code) + "1";
		code_assign(root->ptr_0);
		code_assign(root->ptr_1);
	}
}

/* This function prints the symbol and code words
	of the tree structure using recursive function. */
void print_tree(class Tree* root)
{
	if (root->ptr_0)
	{
		print_tree(root->ptr_0);
		print_tree(root->ptr_1);
	}
	else
	{
		cout << root->symbol << "->  ";
		printf("Frequency: %3d, Code word: ", root->sum);
		cout << root->code << endl;
	}
}

void search_code(string symbol, class Tree* root, string& code)
{
	if (root->ptr_0)
	{
		search_code(symbol, root->ptr_0, code);
		search_code(symbol, root->ptr_1, code);
	}
	else
	{
		if (symbol.compare(root->symbol) == 0)
			code = root->code;
	}
}

