#include <iostream>
#include <vector>
#include "Token.h"
#include "SimpleTree.h"

using namespace std;

void parse_string(string& _str, int start, int end);
void make_brackets(string& _str, int start, int end);
void take_operation(string& _str, char sign, int start, int end);
void take_tokens(vector<Token>& vec, string& _str);

int searchRightEnd(string& _str, int start);
int searchLeftEnd(string& _str, int start);
int operations_count(string& _str, int start, int end);
int brackets_count(string& _str, int start, int end);
int get_left_term(string& _str, int start);
int get_right_term(string& _str, int start);

int main() {
	cout << "Input your expressions \n";
	cout << ">";
	string expression;
	expression = "(7+3*5-2)";
	//cin >> expression;
	parse_string(expression, 0, expression.length());
	cout << expression;
	vector<Token> tokens;
	take_tokens(tokens, expression);
	SimpleTree* tree = new SimpleTree();
	tree->tokens = tokens;
	tree->parse_to_tree();
	tree->show_tree(tree->root);
	return 0;
}


void parse_string(string& _str, int start, int end) {
	make_brackets(_str, 0, _str.length());
}

void make_brackets(string& _str, int start, int end)
{	
	take_operation(_str, '/', 0, _str.length());
	take_operation(_str, '*', 0, _str.length());
	take_operation(_str, '-', 0, _str.length());
	take_operation(_str, '+', 0, _str.length());
}

void take_operation(string& _str, char sign, int start, int end)
{
	for (int i = start; i < end; i++) {
		int check_op = operations_count(_str, start, end);
		int check_br = brackets_count(_str, start, end);
		if (check_op == check_br)break;
		if (_str[i] == sign) {
			int left_term = get_left_term(_str, i - 1);
			int right_term = get_right_term(_str, i + 1);
			if (_str[i - 1] == ')' && _str[i + 1] == '(') { //expression operand expression
				int _start = searchLeftEnd(_str, i - 1);
				int _end = searchRightEnd(_str, i + 1);
				int op_c = operations_count(_str, _start, i - 1);
				int bracket_count = brackets_count(_str, _start, i - 1);
				if (op_c != bracket_count) {
					take_operation(_str, sign, _start, i - 1);
				}

				 op_c = operations_count(_str, i + 1, _end);
				 bracket_count = brackets_count(_str, i + 1, _end);
				if (op_c != bracket_count) {
					take_operation(_str, sign, i+1, _end);
				}
				_start = searchLeftEnd(_str, i - 1);
				_end = searchRightEnd(_str, i + 1);
				_str = _str.substr(0, _start) + "(" + _str.substr(_start, _end - _start+1) + ")" + _str.substr(_end + 1);
				i = searchRightEnd(_str, i+1);
				end = _str.length() - 2;
			}
			else if (_str[i - 1] == ')' && _str[i + 1] != '(') {
				int _start = searchLeftEnd(_str, i);
				int op_c = operations_count(_str, _start, i - 1);
				int bracket_count = brackets_count(_str, _start, i - 1);
				if (op_c != bracket_count )
					take_operation(_str, sign, _start, i - 1);
				_str = _str.substr(0, _start) + "(" + _str.substr(_start, i-_start+right_term+1) + ")" + _str.substr(i + right_term + 1);
			}
			else if (_str[i - 1] != ')' && _str[i + 1] == '(') {
				int _end = searchRightEnd(_str, i + 1);
				int op_c = operations_count(_str, i + 1, _end);
				int bracket_count = brackets_count(_str, i + 1, _end);
				if (op_c != bracket_count) {
					take_operation(_str, sign, i + 1, _end);
				}
				_str = _str.substr(0, i-left_term) + "(" + _str.substr(i-left_term, _end-i+right_term+1) + ")" + _str.substr(_end-i+right_term+2);
				if (op_c == bracket_count) {
					i = _end - 1;
				}
			}
			else {
				int op_c = operations_count(_str, i - 2, i+2);
				int bracket_count = brackets_count(_str, i - 2, i+2);
				if (op_c != bracket_count)
					_str = _str.substr(0, i - left_term) + "(" + _str.substr(i - left_term, left_term+1+right_term) + ")" + _str.substr(i+right_term + 1);
			}
			end = _str.length();
			i++;
		}
	}
}

void take_tokens(vector<Token>& vec, string& _str)
{
	int size = _str.length();
	for (int i = 0; i < size; i++) {
		if (_str[i] == '(' || _str[i] == ')') {
			Token t('b', string(1,_str[i]));
			vec.push_back(t);
		}
		else if (_str[i] == '/' || _str[i] == '*' || _str[i] == '-' || _str[i] == '+') {
			Token t('o',string(1, _str[i]));
			vec.push_back(t);
		}
		else {
			int num_start = get_right_term(_str, i);
			string num = _str.substr(i, num_start);
			Token t('n', num);
			vec.push_back(t);
		}
	}
}

int searchRightEnd(string& _str, int start) {
	int open_br = 0;
	int close_br = 0;
	int index = 0;
	for (int i = start;! (open_br == close_br && open_br > 0 && close_br > 0) && i >= 0; i++) {
		index = i;
		if (_str[i] == '(')open_br++;
		if (_str[i] == ')')close_br++;
	}
	return index;
}

int searchLeftEnd(string& _str, int start) {
	int open_br = 0;
	int close_br = 0;
	int index = 0;
	for (int i = start;!( open_br == close_br && open_br > 0 && close_br > 0) && i >= 0; i--) {
		if (_str[i] == '(')open_br++;
		if (_str[i] == ')')close_br++;
		index = i;
	}
	return index;
}

int operations_count(string& _str, int start, int end)
{
	int sum = 0;
	for (int i = start; i < end; i++) {
		if (_str[i] == '/' || _str[i] == '*' || _str[i] == '+' || _str[i] == '-')
			sum++;
	}
	return sum;
}

int brackets_count(string& _str, int start, int end)
{

	int sum = 0;
	for (int i = start; i <= end; i++) {
		if (_str[i] == '(' || _str[i] == ')')
			sum++;
	}
	return sum/2;
}

int get_left_term(string& _str, int start)
{
	int summ = 0;
	while (start >= 0 && isdigit(_str[start])) {
		summ++;
		start--;
	}
	return summ;
}

int get_right_term(string& _str, int start)
{
	int summ = 0;
	while (start <= _str.length() && isdigit(_str[start])) {
		summ++;
		start++;
	}
	return summ;
}


