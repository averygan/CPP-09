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
