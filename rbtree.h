#pragma once
#include "node.h"
#define leaf rbNode<k, v>

template<class k, class v> class redBlackTree{
	leaf *root = nullptr;
	int nodeCount = 0;
	function<int(k, k)> compare; //key comparator

	//searches tree for key
	//if found, returns node
	//if not found, returns nullptr
	leaf *searchRec(k key, leaf *node);

	//recursively adds elements based on natural ordering
	leaf *addHelper(k key, v value, leaf *node);

	//called when a node is added
	//checks for a double red and fixes if true
	void dblRed(leaf *node);

	//removes node and readjusts tree
	leaf *removeHelper(leaf *node);

	//called if a node is removed and a double-black situation results
	void dblBlack(leaf *node);
public:
	//create tree with natural ordering
	redBlackTree();
	
	//create tree with custom comparator
	redBlackTree(function<int(k, k)> comp);
	
	//create new node with given key + value
	//root is always black
	//subsequent children are added as red
	void add(k key, v value);

	//add given node to tree
	void add(leaf o);
	
	//remove node belonging to given key
	//if node not found, no removal
	void remove(k key);
	
	//returns size of tree
	int size() const;
	
	//if root == nullptr, tree is empty
	bool empty() const;
};

#include "rbtree.cpp"
