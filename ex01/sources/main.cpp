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

int main(int argc, char **argv)
{
	// get next token
	// if token is digit, continue
	// if token is operator
		// if length < 2, invalid
		// if length > 2, perform operator pop * 2 and push results
	// if stack length > 1, invalid
	try 
	{
		arg_checker(argc, argv);
		std::string input = argv[1];
		while (!input.empty())
		{
			std::string token = get_next_token(input);
			std::cout << "token is " << token << std::endl;
			input.erase(0, token.length());
		}
	}
	catch (std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
}
