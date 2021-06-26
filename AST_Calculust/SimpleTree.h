#pragma once
#include <vector>
#include "Token.h"
#include "TreeNode.h"

class SimpleTree {
public:
	std::vector<Token> tokens;
	TreeNode* root;
	SimpleTree() { 
		this->root = new TreeNode("");
		this->current = this->root; 
	};
	
	//commands
	void parse_to_tree();

	//queries
	void show_tree(TreeNode* _startNode);
private:
	TreeNode* current;
};