#pragma once
#include <string>
#include <vector>

struct TreeNode {
	TreeNode* Parent;
	TreeNode* Left_child;
	TreeNode* Right_child;
	std::string value;
	std::string compiled_text;
	float result;
	TreeNode(std::string _value) : value(_value) { 
		Left_child = nullptr;
		Right_child = nullptr;
	};
};