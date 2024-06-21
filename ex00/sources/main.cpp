/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:32:08 by agan              #+#    #+#             */
/*   Updated: 2024/06/21 14:32:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void arg_checker(int argc, char **argv, std::ifstream &input)
{
	// Check for arg counts
	if (argc != 2)
		throw std::invalid_argument("Invalid arguments: ./btc [input]");
	// Check input file open
	input.open(argv[1]);
	if (input.fail())
    	throw std::runtime_error(std::string("Error opening ") + argv[1]);
}

int main(int argc, char **argv)
{
	std::ifstream	input;

	try
	{
		arg_checker(argc, argv, input);
		BitcoinExchange btc;
		btc.getExchangeValues(input);
		input.close();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
