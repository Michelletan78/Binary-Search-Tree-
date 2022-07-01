/*
This is a simple program to give the student experience writing code
for binary trees.  This is a CLASS implementation of the BST ADT.
*/
#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>
#include"bst.h"

using namespace std;
bst::bst()
{
	root = 0;
	ifstream myReadFile;
	myReadFile.open("county_data.txt");
	string output;
	cout << "Echo the input datafile to the screen from default constructor\n" << endl;

	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			getline(myReadFile, output);
			int separator =0;
			for (int i = output.length()-1; i >= 0; i--)
			{
				if (output[i] == ' ')
				{
					separator = i;
					break;
				}
			}
			string county = output.substr(0,separator);
			string num_s = output.substr(separator + 1, output.length()-1-separator);
			cout << left << setw(15) << county << setw(25) << right <<
				num_s << endl;
			double num_d = stod(num_s);
			this->insert(county, num_d);
		}
	}
	myReadFile.close();
	cout << endl;

}
bool bst::empty()
{
	return (root == 0);
}

void bst::insert(const string& item, const double& population)
{
	insert(root, item, population);
}

void bst::insert(treenode * &loc_ptr, const string & item, const double
		& population)
{
	if (loc_ptr == 0)
	{
		loc_ptr = new treenode;
		loc_ptr->lchild = loc_ptr->rchild = 0;
		loc_ptr->county_name = item;
		loc_ptr->population_size = population;
	}
	else if (loc_ptr->county_name > item)
	{
		insert(loc_ptr->lchild, item, population);
	}
	else if (loc_ptr->county_name < item) {
		insert(loc_ptr->rchild, item, population);
	}
	else
		cout << "the item is already in the tree\n";	
}

treenode* bst::search_tree(string item)
{
	return search_tree(root, item);
}

treenode* bst::search_tree(treenode* loc_ptr, string item)
{
	if (loc_ptr != 0)
	{
		if (loc_ptr->county_name == item)
			return loc_ptr;
		else if (loc_ptr->county_name > item)
			return search_tree(loc_ptr->lchild, item);
		else
			return search_tree(loc_ptr->rchild, item);
	}
	else
		return loc_ptr;
}

void bst::del_name(string item)
{
	del_name(root, item);
}

void bst::del_name(treenode*& loc_ptr, string item)
{
	if (loc_ptr == 0)
		cout << "item not in tree\n";

	else if (loc_ptr->county_name > item)
		del_name(loc_ptr->lchild, item);

	else if (loc_ptr->county_name < item)
		del_name(loc_ptr->rchild, item);

	else
	{
		if (loc_ptr == 0)
			cout << "item not in tree\n";
		else if (loc_ptr->county_name > item)
			del_name(loc_ptr->lchild, item);
		else if (loc_ptr->county_name < item)
			del_name(loc_ptr->rchild, item);
		else
		{
			treenode* ptr;
			if (loc_ptr->lchild == 0)
			{
				ptr = loc_ptr->rchild;
				delete loc_ptr;
				loc_ptr = ptr;
			}
			else if (loc_ptr->rchild == 0)
			{
				ptr = loc_ptr->lchild;
				delete loc_ptr;
				loc_ptr = ptr;
			}
			else
			{
				ptr = inorder_succ(loc_ptr);
				loc_ptr->county_name = ptr->county_name;
				del_name(loc_ptr->rchild, ptr->county_name);
			}
		}
	}
}

treenode* bst::inorder_succ(treenode * loc_ptr)
{
		treenode* ptr = loc_ptr->rchild;
		while (ptr->lchild != 0)
		{
			ptr = ptr->lchild;
		}
		return ptr;
}

void bst::print_tree()
{
	print_tree(root);
}

void bst::print_tree(treenode * node)
{
	cout.precision(20);    // fix the show size;
	if ( node!= NULL)
	{
		print_tree(node->lchild);  //print node left child;
		cout << node->county_name << " "
		<<std::noshowpoint
	    << node->population_size << endl;
		print_tree(node->rchild); // print node right child;
	}
}
bst::~bst()
{
	cout << "The Destructor called" << endl;
	empty_tree();
}
void bst::county_ranges(const string& min_name, const string& max_name)
{
	county_ranges(root, min_name, max_name);
}
void bst::county_ranges(treenode*& loc_ptr, const string& min_name, const string
	& max_name)
{
	if (loc_ptr == NULL)
	{
		return;
	}
	if (loc_ptr->county_name >= min_name && loc_ptr->county_name <= max_name)
	{
		county_ranges(loc_ptr->lchild, min_name, max_name);
		cout << loc_ptr->county_name << endl;
		county_ranges(loc_ptr->rchild, min_name, max_name);
	}
	else if (loc_ptr->county_name < min_name)
	{
		county_ranges(loc_ptr->rchild, min_name, max_name);
	}
	else if(loc_ptr->county_name > max_name)
	{
		county_ranges(loc_ptr->lchild, min_name, max_name);
	}
}

void bst::sorted_info()
{
	ofstream myfile;
	myfile.open("county_info.txt");
	sorted_info(myfile, root);
	myfile.close();
}

void bst::sorted_info(ostream& myfile, treenode*& loc_ptr)
{
	if (loc_ptr == NULL)
	{
		return;
	}
	sorted_info(myfile, loc_ptr->lchild);
	string county = loc_ptr->county_name;
	double pop = loc_ptr->population_size;
	myfile << left << setw(15) << county << setw(15) << right << pop << endl;
	sorted_info(myfile, loc_ptr->rchild);
}
void deleteTree(treenode * node) 
{
	if (node != NULL)
	{
		/* first delete both subtrees */
		deleteTree(node->lchild);
		deleteTree(node->rchild);
		/* then delete the node */
		delete node;
	}
}
void bst::empty_tree() 
{
	deleteTree(root);  //call deleteTree function to empty tree.
	root = NULL;   
}

