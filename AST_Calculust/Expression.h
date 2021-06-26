#pragma once
#include "Token.h"

struct Expression {
	Token l_operand;
	Expression* r_operand;
	char _operator;
};