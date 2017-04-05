#pragma once
#include <iostream>
#include <string>
#include <functional>
using namespace std;
enum nodeColor{RED, BLACK};

template<class k, class v> struct rbNode{
private:
	nodeColor color;
public:
	k key;
	v value;
	rbNode<k, v> *parent = nullptr,
		*left = nullptr,
		*right = nullptr;

	rbNode(k k, v val, nodeColor c = RED): key(k), value(val), color(c){}

	void setColor(nodeColor c){
		color = c;
	}

	nodeColor getColor() const{
		return color;
	}

	bool isExternal() const{
		return left == nullptr && right == nullptr;
	}

	bool isBlack() const{
		return color == BLACK;
	}

	rbNode<k, v> *sibling() const{
		return this == parent->left? parent->left : this == parent->right? parent->right : nullptr;
	}

	friend ostream &operator<<(ostream &nout, const rbNode<k, v> &n){
		return nout << "(" << n.key << ", " << n.value << ")";
	}
};

	typedef rbNode<int, string> kvpair;