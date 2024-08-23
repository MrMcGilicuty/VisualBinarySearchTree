#include <chrono>
#include <iostream>
#include <memory>
#include "TreeContainer.h"
#include "Node.h"
using namespace std;

void TreeContainer::add(shared_ptr<Node> node) {

	// Creates Head
	if (head == nullptr) {
		head = node;
		return;
	}

	// Inserts node.
	head->insert(node);

	// If the head is unbalanced change it here.
	// Very similar to the shift functions

	int bal = head->balance();
	shared_ptr<Node> transferNode = head;
	shared_ptr<Node> gChild = nullptr;

	// Shift Right
	if (bal > 1) {
		shared_ptr<Node> child = transferNode->left;

		if (child->right != nullptr) {
			gChild = child->right;
		}
		head = child;
		transferNode->left = gChild;
		child->right = transferNode;
	}
	// Shift Left
	else if (bal < -1) {
		shared_ptr<Node> child = transferNode->right;

		if (child->left != nullptr) {
			gChild = child->left;
		}
		head = child;
		transferNode->right = gChild;
		child->left = transferNode;
	}
}

void TreeContainer::search(int num) {
	auto start = chrono::high_resolution_clock::now();

	bool found = find(num, head);

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::duration<double>>(end - start);

	if (found) {
		cout << "You found the number " << num << " in " << duration.count() << " Seconds.\n\n";
	}
	else {
		cout << "You did not find the number " << num << " in " << duration.count() << " Seconds.\n\n";
	}
}

bool TreeContainer::find(int num, shared_ptr<Node> node)
{

	if (num == node->key) {
		return 1;
	}
	else if (node->right == nullptr && node->left == nullptr) {
		return 0;
	}
	else if (node->right == nullptr) {
		return this->find(num, node->left);
	}
	else if (node->left == nullptr) {
		return this->find(num, node->right);
	}
	else {
		// if the root key is greater than the search key, result is guaranteed to be on the left, & vise versa.
		return node->key > num ? this->find(num, node->left) : this->find(num, node->right);
	}
}