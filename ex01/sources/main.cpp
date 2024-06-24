/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:52 by agan              #+#    #+#             */
/*   Updated: 2024/06/24 17:02:53 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void arg_checker(int argc, char **argv)
{
	const std::string valid_chars = "0123456789 +-/*";
	if (argc != 2)
		throw std::invalid_argument("Error: ./RPN [values]");
	std::string input = argv[1];
	size_t invalid_check = input.find_first_not_of(valid_chars);
	if (invalid_check != std::string::npos)
		throw std::invalid_argument("Error: invalid argument");
}

std::string get_next_token(const std::string &str)
{
	if (str.size() == 0)
		return "";
	size_t index = str.find(" ");
	if (index != std::string::npos)
		return str.substr(0, index + 1);
	else
		return str.substr(0, str.length());
}

token_type get_token_type(std::string token)
{
	std::stringstream ss(token);

	int tmp;
	if (ss >> tmp)
		return DIGIT;
	else
		return OPERATOR;
}

int get_digit(std::string token)
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
if size != 1, invalid */
void ft_rpn(std::string input, RPN &rpn)
{
	while (!input.empty())
	{
		std::string token = get_next_token(input);
		input.erase(0, token.length());
		if (get_token_type(token) == DIGIT)
			rpn.push(get_digit(token));
		else
			rpn.operation(token, rpn);
	}
	if (rpn.size() == 1)
		std::cout << rpn.pop() << std::endl;
	else
		throw std::runtime_error("Error: invalid expression");
}

void printInfinity() 
{
	std::cout << CYAN;
	std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
	std::cout << "⠀⠀⠀⠀⣀⣤⣴⣶⣶⣦⣄⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣶⣶⣦⣤⡀⠀⠀⠀⠀" << std::endl;
	std::cout << "⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀" << std::endl;
	std::cout << "⠀⠀⣾⣿⠟⠋⠉⠀⠀⠉⠙⠻⣿⣷⡀⣰⣿⣿⣿⠟⠉⠀⠀⠀⠈⠙⣿⣷⠀⠀" << std::endl;
	std::cout << "⠀⢸⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠸⣿⡇⠀" << std::endl;
	std::cout << "⠀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀" << std::endl;
	std::cout << "⠀⢸⣿⡆⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⡇⠀" << std::endl;
	std::cout << "⠀⠀⢿⣿⣄⡀⠀⠀⠀⢀⣴⣿⣿⣿⠟⠘⢿⣿⣦⣀⡀⠀⠀⢀⣀⣴⣿⡿⠀⠀" << std::endl;
	std::cout << "⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠙⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀" << std::endl;
	std::cout << "⠀⠀⠀⠀⠈⠛⠻⠿⠿⠿⠛⠁⠀⠀⠀⠀⠀⠀⠈⠙⠻⠿⠿⠿⠛⠉⠀⠀⠀⠀" << std::endl;
	std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << RESET << std::endl;
}

int main(int argc, char **argv)
{
	RPN rpn;
	try 
	{
		arg_checker(argc, argv);
		std::string input = argv[1];
		ft_rpn(input, rpn);
	}
	catch (RPN::InfinityException)
	{
		printInfinity();
	}
	catch (std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
}
