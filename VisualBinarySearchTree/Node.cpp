#include <memory>
#include "Node.h"

Node::Node(int num) {
	this->key = num;
}

int Node::balance() {

	// Performs a few checks then simply subtracts the height of the right from the left
	if (this->right == nullptr && this->left == nullptr) {
		return 0;
	}
	else if (this->left == nullptr) {
		return -this->right->height();
	}
	else if (this->right == nullptr) {
		return this->left->height();
	}
	else {
		return this->left->height() - this->right->height();
	}
}

void Node::insert(std::shared_ptr<Node> node) {
	// Default Cases.

	if (this->left == nullptr && this->key > node->key) {
		this->left = node;
		return;
	}
	else if (this->right == nullptr && this->key <= node->key) {
		this->right = node;
		return;
	}
	// If new node needs to be moved left.
	else if (this->key > node->key) {
		this->left->insert(node);

		// Check for balance issues.
		int bal = this->left->balance();
		if (bal > 1) {
			this->shiftRight(1);
		}
		else if (bal < -1) {
			this->shiftLeft(1);
		}
	}
	// If new node needs to be moved right.
	else if (this->key < node->key) {
		this->right->insert(node);

		// Check for balance issues.
		int bal = this->right->balance();
		if (bal > 1) {
			this->shiftRight(0);
		}
		else if (bal < -1) {
			this->shiftLeft(0);
		}
	}
}

void Node::shiftRight(bool left) {
	// Shifts Right.
	std::shared_ptr<Node> transferNode;
	if (left)
		transferNode = this->left;
	else {
		transferNode = this->right;
	}
	std::shared_ptr<Node> child = transferNode->left;
	std::shared_ptr<Node> gChild = nullptr;

	this->left = child;
	if (child->right != nullptr) {
		gChild = child->right;
	}
	transferNode->left = gChild;
	child->right = transferNode;
}

void Node::shiftLeft(bool left) {
	// Shifts Left.
	std::shared_ptr<Node> transferNode;
	if (left)
		transferNode = this->left;
	else {
		transferNode = this->right;
	}
	std::shared_ptr<Node> child = transferNode->right;
	std::shared_ptr<Node> gChild = nullptr;

	this->right = child;
	if (child->left != nullptr) {
		gChild = child->left;
	}
	transferNode->right = gChild;
	child->left = transferNode;
}

int Node::height() {

	// Recursively finds the height of each child node, returns the height of this node.
	// Default Case
	if (this->left == nullptr && this->right == nullptr) {
		return 1;
	}
	else if (this->right == nullptr) {
		// If you go deeper in the tree increase height
		return this->left->height() + 1;
	}
	else if (this->left == nullptr) {
		// If you go deeper in the tree increase height
		return this->right->height() + 1;
	}
	else {
		int depthL = this->left->height();
		int depthR = this->right->height();

		// If you go deeper in the tree increase height
		return depthL <= depthR ? depthR + 1 : depthL + 1;
	}
}

