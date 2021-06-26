#pragma once

class Token {
public:
	char type;
	std::string value;
	Token(char _type, std::string _value) : type(_type), value(_value) { };
};