/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:43:35 by lgrisel           #+#    #+#             */
/*   Updated: 2025/10/20 11:30:08 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &copy) : stack(copy.stack)
{
}

RPN::~RPN()
{
}

RPN &RPN::operator=(const RPN &copy)
{
	if (this != &copy)
		this->stack = copy.stack;
	return (*this);
}

static size_t skipSpace(const std::string &str, size_t start)
{
	size_t len = 0;
	while (start + len < str.size() && std::isspace(static_cast<unsigned char>(str[start + len])))
		len++;
	return (len);
}

static bool isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

size_t RPN::parseValue(const std::string &str, size_t start)
{
	const char *cstr = str.c_str() + start;
	char *end = NULL;
	
	errno = 0;
	double value = std::strtod(cstr, &end);
	
	if (errno == ERANGE)
	{
		if (value == HUGE_VAL || value == -HUGE_VAL)
			throw std::overflow_error("overflow value");
		throw std::underflow_error("underflow value");
	}
	if (end == cstr)
		throw std::runtime_error("syntax error");
	this->stack.push(value);
	return (static_cast<size_t>(end - cstr));
}

size_t RPN::parseOp(const std::string &str, size_t start)
{
	size_t len = skipSpace(str, start);
	
	if (start + len >= str.size() || !isOperator(str[start + len]))
		throw std::runtime_error("syntax error");
	this->doOp(str[start + len]);
	return (len + 1);
}

void RPN::doOp(char op)
{
	if (this->stack.size() < 2)
		throw std::logic_error("insufficient operands");
	
	double b = this->stack.top();
	this->stack.pop();
	double a = this->stack.top();
	this->stack.pop();

	double result;
	switch (op)
	{
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			result = a / b;
			break;
		default:
			throw std::invalid_argument("invalid operation");
	}
	this->stack.push(result);
}

double RPN::compute(const std::string &str)
{
	size_t len = 0;
	
	while (len < str.size())
	{
		len += skipSpace(str, len);
		if (len >= str.size())
			break;
		
		try
		{
			len += this->parseValue(str, len);
		}
		catch (const std::runtime_error &)
		{
			len += this->parseOp(str, len);
		}
	}
	if (this->stack.size() > 1)
		throw std::logic_error("too many operands");
	if (this->stack.empty())
		throw std::logic_error("empty expression");
	double res = this->stack.top();
	this->stack.pop();
	return (res);
}
