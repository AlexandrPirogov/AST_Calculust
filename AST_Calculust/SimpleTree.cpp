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

void SimpleTree::calculate(TreeNode* _startNode)
{
	this->current = _startNode;
	try {
		stoi(this->current->value);
		return;
	}
	catch (const std::exception& ex) {
		if (this->current->Left_child->value == "/" || this->current->Left_child->value == "*" ||
			this->current->Left_child->value == "-" || this->current->Left_child->value == "+")calculate(this->current->Left_child);
		if (this->current->Right_child->value == "/" || this->current->Right_child->value == "*" ||
			this->current->Right_child->value == "-" || this->current->Right_child->value == "+")calculate(this->current->Right_child);
		if (this->current->Left_child->Left_child == nullptr && this->current->Left_child->Right_child == nullptr
			&& this->current->Right_child->Left_child == nullptr && this->current->Right_child->Right_child == nullptr) {
			float result = solve(this->current);
			this->current->value = std::to_string(result);
			this->current->compiled_text = "(" + this->current->Left_child->value + this->current->value + this->current->Right_child->value + ")";
			this->current->Left_child = nullptr;
			this->current->Right_child = nullptr;
			this->current = this->current->Parent;
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

float SimpleTree::solve(TreeNode* _current)
{
	float result;
	std::string op = _current->value;
	if (op == "/") {
		result = stoi(_current->Left_child->value)/stoi(_current->Right_child->value);
	} else if (op == "*") {
		result = stoi(_current->Left_child->value) * stoi(_current->Right_child->value);
	}
	else if (op == "-") {
		result = stoi(_current->Left_child->value) - stoi(_current->Right_child->value);
	}
	else {
		result = stoi(_current->Left_child->value)+stoi(_current->Right_child->value);
	}
	return result;
}
