#pragma once
#include <memory>
#include <vector>
#include "Node.h"

class TreeContainer
{
public:

	// Adds a node to the tree.
	void add(std::shared_ptr<Node> node);

	// Searches for specific integer in tree.
	void search(int num);

	// Returns true if it found a specific number on the tree.
	/// <param name="num:"> Integer to search for. </param>
	/// <param name="node:"> Node from which you are commensing the search. </param>
	bool find(int num, std::shared_ptr<Node> node);

	// Returns a vector of every key in the tree, -1 means null or empty
	/// <param name="head:"> Will only generate a list downward from the head. </param>
	/// <param name="level:"> go this far down. </param>
	std::vector<int> deepSearch(std::shared_ptr<Node> head_, int lv);

	// The head of the list.
	std::shared_ptr<Node> head = nullptr;
};