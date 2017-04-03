#pragma once
#include <iostream>
#include <string>
#include <utility>
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

	bool isExternal() const{
		return left == nullptr && right == nullptr;
	}

	bool isBlack() const{
		return color == BLACK;
	}

	bool isRed() const{
		return color == RED;
	}

	rbNode<k, v> sibling(){
		return this == parent->left? parent->left : parent.right;
	}

	friend ostream &operator<<(ostream &nout, const rbNode<k, v> &n){
		return nout << "(" << n.key << ", " << n.value << ")";
	}
};

typedef pair<int, string> kvpair;
