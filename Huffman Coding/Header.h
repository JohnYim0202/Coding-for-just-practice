#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <iomanip>
#include <string>	  // for string class
#include <cmath>	  // for ceil, floor
#include <vector>	  // for vector
#include <algorithm>  // for std:find
#include <numeric>    // for acumulate
#include <functional> // for greater

#define MAX_LIMIT 3000

using namespace std;

class Tree {
public:
	Tree()
	{
		this->ptr_0 = NULL;
		this->ptr_1 = NULL;
		this->label_0 = 0;
		this->label_1 = 0;
		this->sum = 0;
	}
	class Tree* ptr_0;
	class Tree* ptr_1;
	int label_0;
	int label_1;
	int sum;
	string symbol;
	string code;
};

void code_assign(class Tree* root);
void print_tree(class Tree* root);
void search_code(string symbol, class Tree* root, string &code);

class Code
{
public:
	Code()// A constructor
	{
		this->Codestring = "a";	
	}
		
	void setstring(string input, int unit) 
	{	
		this->Codestring = input;
		cout << "Length of input string: " << input.length() << endl;

		int remainder = input.length() % unit;

		// Make sure that the length of (this->Codestring) be int. mult of (unit).
		if (remainder != 0)
			(this->Codestring).append(unit - remainder, '.');
	}
	
	void initialize(void)
	{
		Codestring.clear();
		Decodestring.clear();
		string_chunked.clear();
		symbol_list.clear();
		code_list.clear();
		code_length.clear();
		symbol_freq.clear();
	}

	void symbolanalyze(int unit) 
	// Cut the string into chunks with length of "unit". 
	{
		int list_counter = 0;
		double length = this->Codestring.length();

		// Update symbol list and symbol freq. list.
		for (int i = 0; i < ceil(length/unit); ++i)
		{
			string symbol = Codestring.substr(i*unit, unit);
			string_chunked.push_back(symbol);
			
			std::vector<string>::iterator it;
			it = std::find(symbol_list.begin(), symbol_list.end(), symbol);

			if ( it == symbol_list.end() ) // If the symbol is new,
			{ 
				symbol_list.push_back(symbol);
				symbol_freq.push_back(1);
			}
			else // If the symbol already exits,
			{ 
				int idx = it - symbol_list.begin();
				symbol_freq[idx] += 1;
			}
			
		}
	}

	// Order the symbol prob. list and assign code word, and save the bitstream.
	void encode(int unit)
	{
		cout << "Below is the freq. table of symbols before sorting." << endl;
		for (int i = 0; i < symbol_list.size(); ++i)
		{
			printf("[%02d] %4d ", i, symbol_freq[i]);
			cout << symbol_list[i] << endl;
		}  

		// Sort the symbol and freq. list. (Bubble sorting)
		for (int i = 0; i < symbol_list.size() - 1; ++i)
		{
			for (int j = symbol_list.size() - 1; j > i; --j)
			{
				if (symbol_freq[j-1] < symbol_freq[j])
				{
					int    tmp_i = symbol_freq[j - 1];
					string tmp_s = symbol_list[j - 1];

					symbol_freq[j - 1] = symbol_freq[j];
					symbol_list[j - 1] = symbol_list[j];

					symbol_freq[j] = tmp_i;
					symbol_list[j] = tmp_s;
				}
			}
		}
		
		cout << "Below is the freq. table of symbols after sorting." << endl;
		for (int i = 0; i < symbol_list.size(); ++i)
		{
			printf("[%02d] %4d ", i, symbol_freq[i]);
			cout << symbol_list[i] << endl;
		}

		// Prepare the leaf layer of the tree structure.
		for (int i = 0; i < symbol_list.size(); ++i)
		{
			class Tree* ptr = new class Tree();
			ptr->sum = symbol_freq[i];
			ptr->symbol = symbol_list[i];
			tree_layer.push_back(ptr);
		}

		// Prepare the whole tree structure.
		tree_struct.push_back(tree_layer);
		vector <class Tree*> temp = tree_layer;
		while (temp.size() > 1)
		{	
			temp = tree_struct.back();
			// Create New node and delete two smallest nodes from the vector.
			class Tree* ptr = new class Tree();
			ptr->label_0 = (temp.back())->sum;
			ptr->ptr_0 = temp.back();
			temp.pop_back();

			ptr->label_1 = (temp.back())->sum;
			ptr->ptr_1 = temp.back();
			temp.pop_back();

			ptr->sum = ptr->label_0 + ptr->label_1;
			temp.push_back(ptr);

			// Sort the nodes.
			for (int i = 0; i < temp.size() - 1; ++i)
			{
				for (int j = temp.size() - 1; j > i; --j)
				{
					if ((temp[j - 1]->sum) < (temp[j]->sum))
					{
						std::swap(temp[j - 1], temp[j]);
					}
				}
			}

			// Show the tree layer.
			/*cout << "================================" << endl;
			for (int i = 0; i < temp.size(); ++i)
			{
				printf("(%03d) %3d\n", i, (temp[i])->sum);
			}*/
			tree_struct.push_back(temp);
		} 

		// Assign code word.
		cout << "Code word is assigned." << endl;
		root = (tree_struct.back()).back();  // "root" is a member variable of the class "Code".
		code_assign(root);
		print_tree(root);

		// Prepare code word vector.
		for (int i = 0; i < symbol_list.size(); ++i)
		{
			string symbol = symbol_list[i];
			string code;
			// Now, "code" is a codeword corresponding to "symbol".
			search_code(symbol, root, code);
			code_list.push_back(code);
			code_length.push_back(code.length());
		}

		// Now, encoding.
		for (int i = 0; i < string_chunked.size(); ++i)
		{
			string symbol = string_chunked[i];

			std::vector<string>::iterator it;
			it = std::find(symbol_list.begin(), symbol_list.end(), symbol);
			
			// Find a index of a given "symbol" in a symbol_list.
			int idx = it - symbol_list.begin();
			string code = code_list[idx];
			Bitstream.append(code);
		}
		cout << "We have a bitstream : " << this->Bitstream << endl;
		cout << "Length of bitstream : " << this->Bitstream.length() << endl;
	}

	// Convert the bitstream back to the string.
	void decode(void)
	{
		string tempstream = this->Bitstream;
		while(tempstream.length() >= 1)
		{
			for (int i = 0; i < code_list.size(); ++i)
			{
				int criterion = (code_list[i]).compare(tempstream.substr(0, (code_list[i]).length()));
				if (!criterion)
				{
					(this->Decodestring).append(symbol_list[i]);
					tempstream.erase(0, (code_list[i]).length());
				}
			}
		}
		cout << "Decoded string: " << this->Decodestring << endl;
	}

private:
	string Bitstream;
	string Codestring;
	string Decodestring;

	vector <string> string_chunked;
	vector <string> symbol_list;
	vector <string> code_list;
	vector <int> code_length;

	vector <int>    symbol_freq;

	vector <class Tree *> tree_layer;
	vector <vector <class Tree*>> tree_struct;

	class Tree* root;
	
};


#else
#endif