#pragma once
#include "node.h"

template<class k, class v> class redBlackTree{
	rbNode<k, v> *root = nullptr;
	int nodeCount = 0;
	function<int(k, k)> compare; //key comparator

	

	//searches tree for key
	//if found, returns node
	//if not found, returns nullptr
	rbNode<k, v> *searchRec(k key, rbNode<k, v> *node){
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
	rbNode<k, v> *addHelper(k key, v value, rbNode<k, v> *node){
		if(compare(node->key, key))
			if(node->left == nullptr){
				node->left = new rbNode<k, v>(key, value, RED);
				return node->left;
			}
			else
				addHelper(key, value, node->left);
		else
			if(node->right == nullptr){
				node->right = new rbNode<k, v>(key, value, RED);
				return node->right;
			}
			else
				addHelper(key, value, node->right);
			return nullptr;
	}

	//called when a node is added
	//checks for a double red and fixes if true
	void dblRed(rbNode<k, v> *node){
		rbNode<k, v> *vNode = node->parent;

		if(vNode->isBlack())
			return;

		if(vNode->sibling()->isBlack()){
			vNode = trinode(node);
			vNode->setColor(BLACK);
			vNode->left->setColor(RED);
			vNode->right->setColor(RED);
		}
		else{
			vNode->setColor(BLACK);
			vNode->sibling()->setColor(BLACK);
			rbNode<k, v> *u = vNode->parent;
			if(u == root)
				return;
			u->setColor(RED);
			dblRed(u);
		}
	}

	//removes node and readjusts tree
	rbNode<k, v> *removeHelper(rbNode<k, v> *node){
		rbNode<k, v> *w;

		if(node->left->isExternal())
			w = node->left;
		else if(node->right->isExternal())
			w = node->right;
		else{
			w = node->right;
			do{
				w = w->left;
			}while(w->isExternal());
			rbNode<k, v> *u = w->parent;
			node->key = u->key;
			node->value = u->value;
		}

		rbNode<k, v> *a = w, p = w->parent, s = a->sibling();
		if(p == root){
			root == s;
			s->parent == nullptr;
		}
		else{
			rbNode<k, v> *gp = p->parent;
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
	void dblBlack(rbNode<k, v> *node){
		rbNode<k, v> *x = node->parent, *y = node->sibling();
		if(y->isBlack()){
			if(!y->left->isBlack() || !y->left->isBlack()){
				rbNode<k, v> *z = !y->left->isBlack()? y->left : y->right;
				nodeColor tcol = x->getColor();
				z = trinode(z);
				z->setColor(tcol);
				node->setColor(BLACK);
				z->left->setColor(BLACK);
				z->right->setColor(BLACK);
			}
			else{
				node->setColor(BLACK);
				y->setColor(BLACK);
				if(x->isBlack() && x != root)
					dblBlack(x);
				x->setColor(BLACK);
			}
		}
		else{
			rbNode<k, v> *z = y == x->right? y->right : y->left;
			trinode(z);
			y->setColor(BLACK);
			x->setColor(RED);
			dblBlack(node);
		}
	}

	rbNode<k, v> *trinode(rbNode<k, v> *node){
		return node;
	}

	//The following functions recursively traverse and print the tree based on postorder, inorder, and preorder
	void postorderRec(rbNode<k, v> *l, ostream &tout){
		if(l == nullptr)
			return;
		postorderRec(l->left, tout);
		postorderRec(l->right, tout);
		tout << l << ' ';
	}

	void inorderRec(rbNode<k, v> *l, ostream &tout){
		if(l == nullptr)
			return;
		inorderRec(l->left, tout);
		tout << l << ' ';
		inorderRec(l->right, tout);
	}

	void preorderRec(rbNode<k, v> *l, ostream &tout){
		if(l == nullptr)
			return;
		tout << l << ' ';
		preorderRec(l->left, tout);
		preorderRec(l->right, tout);
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
			root = new rbNode<k, v>(key, value, BLACK);
			nodeCount++;
			return;
		}

		rbNode<k, v> *node = addHelper(key, value, root);

		if(!node->parent->isBlack())
			dblRed(node);

		nodeCount++;
	}
	
	void add(rbNode<k, v> o){
		if(root == nullptr){
			root = new rbNode<k, v>(o.key, o.value, BLACK);
			nodeCount++;
			return;
		}

		rbNode<k, v> *node = addHelper(o.key, o.value, root);

		if(!node->parent->isBlack())
			dblRed(node);

		nodeCount++;
	}

	//remove node belonging to given key
	//if node not found, no removal
	void remove(k key){
		rbNode<k, v> *r = searchRec(key, root);

		if(r == nullptr)
			return;

		rbNode<k, v> *s = removeHelper(r);

		if(s == root || !s->isBlack() || !s->parent->isBlack())
			s->setColor(BLACK);
		else
			dblBlack(s);

		nodeCount--;
	}

	//Calls recursive traversal functions
	ostream &postorder(ostream &tout){
		tout << "Tree in postorder: ";
		postorderRec(root, tout);
		return tout;
	}
	
	ostream &inorder(ostream &tout){
		tout << "Tree in inorder: ";
		inorderRec(root, tout);
		return tout;
	}
	
	ostream &preorder(ostream &tout){
		tout << "Tree in preorder: ";
		preorderRec(root, tout);
		return tout;
	}

	//returns size of tree
	int size() const{
		return nodeCount;
	}
	
	//if root == nullptr, tree is empty
	bool empty() const{
		return root == nullptr;
	}

	friend ostream &operator<<<k, v>(ostream &tout, const redBlackTree<k, v> &rbt){
		redBlackTree<k, v> &r = const_cast<redBlackTree<k, v>&>(rbt);
		return r.postorder(tout) << endl;// << r.inorder(tout) << endl << r.preorder(tout);
	}
};
