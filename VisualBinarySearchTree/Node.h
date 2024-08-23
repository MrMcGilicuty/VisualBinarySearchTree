#pragma once
#include <memory>
class Node {
public:
	// Number to set to the key.
	Node(int num);

	// Recursively finds where a node should be placed on the tree, then performs balances if needed.
	void insert(std::shared_ptr<Node> node);
	// Performs the necessary linkage changes to swap nodes right to self balance.
	void shiftRight(bool left);
	// Performs the necessary linkage changes to swap nodes left to self balance.
	void shiftLeft(bool left);
	// Returns Balance of this node (left child - right child).
	int balance();

	// Number it holds.
	int key;
	// Node to the down-left.
	std::shared_ptr<Node> left;
	// Node to the down-right.
	std::shared_ptr<Node> right;
	// (Relative)
	int height();
};

