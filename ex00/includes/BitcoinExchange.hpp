/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:32:22 by agan              #+#    #+#             */
/*   Updated: 2024/06/21 14:32:23 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BITCOINEXCHANGE_HPP__
#define __BITCOINEXCHANGE_HPP__

#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>

// Colors
# define BROWN "\033[1;33m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE	"\033[1;34m"
# define CYAN	"\033[1;36m"
# define RESET "\033[0m"

# define BROWN_R "\033[33m"
# define RED_R "\033[31m"
# define GREEN_R "\033[32m"
# define BLUE_R	"\033[34m"
# define CYAN_R	"\033[36m"

class BitcoinExchange {
	private:
		std::map<std::string, double> _exchangeRates;

		bool		is_valid_date(const std::string &str);
		std::string parseDate(const std::string &str);
		int			getExchangeRates();
		double		strToDouble(const std::string &str);
		std::string	splitString(bool date, char delimiter, std::string row);
		double		parseValue(const std::string row, const std::string date);

	public:
		// Constructors
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);

		// Destructor
		~BitcoinExchange();

		// Assignment operator
		BitcoinExchange &operator=(const BitcoinExchange &copy);

		void		getExchangeValues(std::ifstream &input);
};

#endif