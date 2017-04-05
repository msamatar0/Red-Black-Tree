#pragma once
#include <iostream>
#include <string>
#include <functional>
using namespace std;
enum nodeColor{RED, BLACK};

template<class k, class v> struct rbNode{
private:
	//
	nodeColor color;
public:
	k key;
	v value;
	rbNode<k, v> *parent = nullptr,
		*left = nullptr,
		*right = nullptr;

	//Create node
	//nodes are by default red
	rbNode(k k, v val, nodeColor c = RED);

	//Change node to red/black
	void setColor(nodeColor c);

	//Returns true if node has no children
	bool isExternal() const;

	//Returns true if node is black, false if red
	bool isBlack() const;
	
	//Return sibling of node, whether it is a left or right child
	rbNode<k, v> sibling() const;

	//Print contents of a node
	template<class k, class v> friend ostream &operator<<(ostream &nout, const rbNode<k, v> &n);
};

typedef rbNode<int, string> kvpair;

#include "node.cpp"