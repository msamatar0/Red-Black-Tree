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
	leaf *searchRec(k key, leaf *node){
		if(node == nullptr)
			return node;

		int comp = compare(node->key, key);

		if(comp > 0)
			searchRec(key, node->left);
		else if(comp < 0)
			searchRec(key, node->right);
		else if(comp == 0)
			return node;
	}

	//recursively adds elements based on natural ordering
	leaf *addHelper(k key, v value, leaf *node){
		if(compare(node->key, key))
			if(node->left == nullptr){
				node->left = new leaf(key, value, RED);
				return node->left;
			}
			else
				addHelper(key, value, node->left);
		else
			if(node->right == nullptr){
				node->right = new leaf(key, value, RED);
				return node->right;
			}
			else
				addHelper(key, value, node->right);
	}

	//called when a node is added
	//checks for a double red and fixes if true
	void dblRed(leaf *node){
		leaf *v = node->parent;

		if(v->isBlack())
			return;

		if(v->sibling()->isBlack()){
			;
			v->setColor(BLACK);
			v->left->setColor(RED);
			v->right->setColor(RED);
		}
		else{
			v->setColor(BLACK);
			v->sibling()->setColor(BLACK);
			leaf *u = v->parent;
			if(u == root)
				return;
			u->setColor(RED);
			dblRed(u);
		}
	}

	//removes node and readjusts tree
	leaf *removeHelper(leaf *node){
		leaf *w;

		if(node->left->isExternal())
			w = node->left;
		else if(node->right->isExternal())
			w = node->right;
		else{
			w = node->right;
			do{
				w = w->left;
			}while(w->isExternal());
			leaf *u = w->parent;
			node->key = u->key;
			node->value = u->value;
		}

		leaf *a = w, p = w->parent, s = a->sibling();
		if(p == root){
			root == s;
			s->parent == nullptr;
		}
		else{
			leaf *gp = p->parent;
			if(p == gp->left)
				gp->left = s;
			else
				gp->right = s;
			s->parent = gp;
		}
		delete a;
		delete b;
		n -= 2;
		return s;
	}

	//called if a node is removed and a double-black situation results
	//
	void dblBlack(leaf *node){
		;
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

		leaf *node = addHelper(key, value, root);

		if(node->parent->isRed())
			dblRed(node);

		nodeCount++;
	}
	
	//remove node belonging to given key
	//if node not found, no removal
	void remove(k key){
		leaf *r = searchRec(key, root);

		if(r == nullptr)
			return;

		leaf *s = removeHelper(r);

		if(s == root || s->isRed() || s->parent->isRed())
			s->setColor(BLACK);
		else
			dblBlack(s);

		nodeCount--;
	}
	
	//returns size of tree
	int size() const{
		return nodeCount;
	}
	
	//if root == nullptr, tree is empty
	bool empty() const{
		return root == nullptr;
	}
};
