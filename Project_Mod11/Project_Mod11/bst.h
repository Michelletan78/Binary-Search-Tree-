#pragma once
#include<string>
#include<iomanip>
using namespace std;

#ifndef BST_H
#define BST_H

class treenode
{
public:
	string county_name;
	double population_size;
	treenode* lchild;
	treenode* rchild;//left and right children pointers
};

class bst
{
public:
	bst() ; //store the data file (“county_data.txt”) into initial bst.
	~bst();//de-allocates dynamic memory allocate for tree bool empty();
	bool empty();
	void insert(const string & item, const double& population);
	void insert(treenode*&, const string & item, const double & population);
	void del_name(string item);
	void del_name(treenode*& loc_ptr, string item);
	treenode* search_tree(string item);
	treenode* search_tree(treenode*, string item);
	treenode* inorder_succ(treenode*);
	void county_ranges(const string& min_name, const string & max_name);
	void county_ranges(treenode*&, const string & min_name, const string & max_name);
	void print_tree();
	void print_tree(treenode*);
	void sorted_info();
	void sorted_info(ostream&, treenode*&);
	void empty_tree();
private:
	treenode* root;

};
#endif