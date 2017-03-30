#pragma once
#include "node.h"
#define leaf rbNode<k, v>

template<class k, class v> class redBlackTree{
	leaf *root = nullptr;
	int nodeCount = 0;
	function<int(k, k)> compare; //key comparator

	//recursively adds elements based on natural ordering
	leaf *addRec(k key, v value, leaf *l){
		if(compare(l->key, key))
			if(l->left == nullptr){
				l->left = new leaf(key, value);
				return l->left;
			}
			else
				addRec(key, value, l->left);
		else
			if(l->right == nullptr){
				l->right = new leaf(key, value);
				return l->right;
			}
			else
				addRec(key, value, l->right);
	}
	//called when a node is added
	//checks for a double red and fixes if true
	void dblRed(leaf *node){
		leaf *v = node->parent;
		if(v->isBlack())
			return;
	}
public:
	//create tree with natural ordering
	redBlackTree(): compare([](k a, k b){ return a - b; }){}
	//create tree with custom comparator
	redBlackTree(function<int(k, k)> comp): compare(comp){}
	//add new node
	//root is always black
	//subsequent children are added as red
	void add(k key, v value){
		if(root == nullptr){
			root = new leaf(key, value, BLACK);
			nodeCount++;
			return;
		}
		leaf *node = addRec(key, value, root);
		if(node->parent->isRed())
			dblRed(node);
		nodeCount++;
	}
	//remove node belonging to given key
	//if node not found, no removal
	void remove(k key){
		nodeCount--;
	}
	//returns size of tree
	int size() const{
		return nodeCount;
	}
	//If root == nullptr, tree is empty
	bool empty(){
		return root == nullptr;
	}
};
