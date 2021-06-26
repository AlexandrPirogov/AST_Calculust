#include "TreeNode.h"
#include "SimpleTree.h"
#include <iostream>
void SimpleTree::parse_to_tree()
{
	while (this->tokens.size() != 0){
	if (this->tokens[0].value == "(") {
		this->tokens.erase(this->tokens.begin(), this->tokens.begin() + 1);
		this->current->Left_child = new TreeNode("");
		this->current->Left_child->Parent = this->current;
		this->current = current->Left_child;
	} else if (this->tokens[0].value == ")") {
		this->tokens.erase(this->tokens.begin(), this->tokens.begin() + 1);
		this->current = current->Parent;
	} else if (this->tokens[0].type == 'n') {
		this->current->value = this->tokens[0].value;
		this->tokens.erase(this->tokens.begin(), this->tokens.begin() + 1);
		this->current = this->current->Parent;
	}
	else {
		this->current->value = this->tokens[0].value;
		this->tokens.erase(this->tokens.begin(), this->tokens.begin() + 1);
		this->current->Right_child = new TreeNode("");
		this->current->Right_child->Parent = this->current;
		this->current = current->Right_child;
	}
	}
}

void SimpleTree::show_tree(TreeNode* _startNode)
{
	std::cout << _startNode->value << "\n";
	if (_startNode->Left_child != nullptr)
		show_tree(_startNode->Left_child);
	if (_startNode->Right_child != nullptr)
		show_tree(_startNode->Right_child);
}
