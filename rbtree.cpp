#include "rbtree.h"

template<class k, class v> redBlackTree<k, v>::redBlackTree(): compare([](k a, k b){ return a - b; }){}

template<class k, class v> redBlackTree<k, v>::redBlackTree(function<int(k, k)> comp) : compare(comp){}

template<class k, class v> leaf *redBlackTree<k, v>::searchRec(k key, leaf *node){
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

template<class k, class v> leaf *redBlackTree<k, v>::addHelper(k key, v value, leaf *node){
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

template<class k, class v> void redBlackTree<k, v>::dblRed(leaf * node){
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

template<class k, class v> leaf *redBlackTree<k, v>::removeHelper(leaf *node){
	leaf *w;

	if(node->left->isExternal())
		w = node->left;
	else if(node->right->isExternal())
		w = node->right;
	else{
		w = node->right;
		do{
			w = w->left;
		} while(w->isExternal());
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

template<class k, class v> void redBlackTree<k, v>::dblBlack(leaf * node){
	;
}

template<class k, class v> void redBlackTree<k, v>::add(k key, v value){
	//if no root exists, create one
	if(root == nullptr){
		root = new leaf(key, value, BLACK);
		nodeCount++;
		return;
	}

	leaf *node = addHelper(key, value, root);

	if(!node->parent->isBlack())
		dblRed(node);

	nodeCount++;
}

template<class k, class v> void redBlackTree<k, v>::add(leaf o){
	//if no root exists, create one
	if(root == nullptr){
		root = new leaf(o.key, o.value, BLACK);
		nodeCount++;
		return;
	}

	leaf *node = addHelper(o.key, o.value, root);

	if(!node->parent->isBlack())
		dblRed(node);

	nodeCount++;
}

template<class k, class v> void redBlackTree<k, v>::remove(k key){
	leaf *r = searchRec(key, root);

	if(r == nullptr)
		return;

	leaf *s = removeHelper(r);

	if(s == root || !s->isBlack() || !s->parent->isBlack())
		s->setColor(BLACK);
	else
		dblBlack(s);

	nodeCount--;
}

template<class k, class v> int redBlackTree<k, v>::size() const{
	return nodeCount;
}

template<class k, class v> bool redBlackTree<k, v>::empty() const{
	return root == nullptr;
}
