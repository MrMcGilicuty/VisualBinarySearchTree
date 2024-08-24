#include <chrono>
#include <iostream>
#include <memory>
#include <queue>
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

bool TreeContainer::find(int num, shared_ptr<Node> node) {

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

std::vector<int> TreeContainer::deepSearch(std::shared_ptr<Node> head_, int lv)
{
	std::vector<int> treeList;
	if (head_ == nullptr) {
		return treeList; // Return empty if the tree is empty
	}

	std::queue<std::pair<std::shared_ptr<Node>, int>> Bqueue;
	Bqueue.push({ head_, 0 });

	while (!Bqueue.empty()) {
		// Getting current node and the depth.
		std::shared_ptr<Node> node = Bqueue.front().first;
		int                  depth = Bqueue.front().second;
		Bqueue.pop();

		// If we are at desired depth on the node, then add it to the queue.
		if (depth == lv) 
			treeList.push_back(node ? node->key : -1);

		// If the depth is less than the desired depth, enqueue children
		if (depth < lv) {
			if (node->left) {
				Bqueue.push({ node->left, depth + 1 });
			}
			else {
				Bqueue.push({ nullptr, depth + 1 });
			}
			if (node->right) {
				Bqueue.push({ node->right, depth + 1 });
			}
			else {
				Bqueue.push({ nullptr, depth + 1 });
			}
		}
	}

	return treeList;
}
