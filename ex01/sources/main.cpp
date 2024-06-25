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
		rpn.ft_rpn(input);
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
