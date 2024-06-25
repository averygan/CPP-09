/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:57 by agan              #+#    #+#             */
/*   Updated: 2024/06/24 17:02:57 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int		RPN::size()
{
	return this->_stack.size();
}

void	RPN::push(int n)
{
	this->_stack.push(n);
}

// Function to pop -> popping length <= 0 leads to undefined behavior
int		RPN::pop()
{
	int value;

	value = this->_stack.top();
	this->_stack.pop();
	return value;
}

const char *RPN::InfinityException::what() const throw()
{
	return ("Infinity");
}

void RPN::operation(std::string token)
{
	if (this->size() < 2)
		throw std::runtime_error("Error: invalid operation");
	int second = this->pop();
	int first = this->pop();
	int val;
	if (token == "+" || token == "+ ")
		val = first + second;
	if (token == "-" || token == "- ")
		val = first - second;
	if (token == "/" || token == "/ ")
	{
		if (second == 0)
			throw InfinityException();
		else
			val = first / second;
	}
	if (token == "*" || token == "* ")
		val = first * second;
	this->push(val);
}

std::string RPN::get_next_token(const std::string &str)
{
	if (str.size() == 0)
		return "";
	size_t index = str.find(" ");
	if (index != std::string::npos)
		return str.substr(0, index + 1);
	else
		return str.substr(0, str.length());
}

token_type RPN::get_token_type(std::string token)
{
	std::stringstream ss(token);

	int tmp;
	if (ss >> tmp)
		return DIGIT;
	else if (token == " ")
		return SPACE;
	else
		return OPERATOR;
}

int RPN::get_digit(std::string token)
{
	std::stringstream ss(token);

	int val;
	if (ss >> val)
		return val;
	else
		throw std::runtime_error("Error: invalid value");
}

/* Run through input string -> get next token -> erase token 
if digit, push to stack
if operator, perform operation
if space, do nothing
if size != 1, invalid */
void RPN::ft_rpn(std::string input)
{
	while (!input.empty())
	{
		std::string token = get_next_token(input);
		input.erase(0, token.length());
		if (get_token_type(token) == DIGIT)
			this->push(get_digit(token));
		else if (get_token_type(token) != SPACE)
			this->operation(token);
	}
	if (this->size() == 1)
		std::cout << this->pop() << std::endl;
	else
		throw std::runtime_error("Error: invalid expression");
}

RPN::RPN() {};

RPN::RPN(const RPN &copy)
{
	*this = copy;
}

RPN::~RPN() {};

RPN &RPN::operator=(const RPN &copy)
{
	if (this != &copy)
		this->_stack = copy._stack;
	return *this;
}
