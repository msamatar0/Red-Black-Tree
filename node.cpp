#include "node.h"

template<class k, class v> rbNode<k, v>::rbNode(k k, v val, nodeColor c): key(k), value(val), color(c){}

template<class k, class v> void rbNode<k, v>::setColor(nodeColor c){
	color = c;
}

template<class k, class v> bool rbNode<k, v>::isExternal() const{
	return left == nullptr && right == nullptr;
}

template<class k, class v> bool rbNode<k, v>::isBlack() const{
	return color == BLACK;
}

template<class k, class v> inline rbNode<k, v> rbNode<k, v>::sibling() const{
	return this == parent->left? parent->left : parent.right;
}

template<class k, class v> ostream &operator<<(ostream &nout, const rbNode<k, v> &n){
	return nout << "(" << n.key << ", " << n.value << ")";
}
