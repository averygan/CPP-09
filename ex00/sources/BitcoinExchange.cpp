/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:32:18 by agan              #+#    #+#             */
/*   Updated: 2024/06/21 14:32:19 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool BitcoinExchange::is_valid_date(const std::string &str)
{
	// Check if date is valid
	int year = atoi(str.substr(0, 4).c_str());
	int month = atoi(str.substr(5, 2).c_str());
	int day = atoi(str.substr(8, 2).c_str());

	// Check valid ranges
	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	// Check days in month
	static const int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	// Check for leap year in February
	if (month == 2) 
	{
		bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (is_leap)
		{
			if (day > 29) return false;
		}
		else 
		{
			if (day > 28) return false;
		}
	} 
	if (day > days_in_month[month - 1]) 
		return false;
	return true;
}

std::string BitcoinExchange::parseDate(const std::string &str)
{
	std::string date;

	// Check syntax
	if (str.length() < 10)
		return NULL;
	if (str[4] != '-' || str[7] != '-') 
		return NULL;
	for (int i = 0; i < 10; ++i) 
	{
		if (!isdigit(date[i]) && i != 4 && i != 7)
			return NULL;
	}
	if (!is_valid_date(str))
		return NULL;
	return (str.substr(0, 10));
}

/* Read from db file and store exchange rates in container */
int	BitcoinExchange::getExchangeRates()
{
	std::ifstream	db;
	std::string		row;
	
	db.open("data.csv");
	if (db.fail())
		throw std::runtime_error("Error opening data.csv");
	std::getline(db, row);
	while (std::getline(db, row))
	{
		std::string key = splitString(true, ',', row);
		std::string val = splitString(false, ',', row);
		double value = strToDouble(val);
		this->_exchangeRates[key] = value;
	}

    // std::map<std::string, double>::iterator it;
    // for (it = _exchangeRates.begin(); it != _exchangeRates.end(); ++it) {
    //     std::cout << std::fixed << std::setprecision(2);
    //     std::cout << it->first << " -> " << it->second << std::endl;
    // }

	return 0;
}

void	BitcoinExchange::getExchangeValues(std::ifstream &input)
{
	std::string	row;

	std::getline(input, row);
	if (row != "date | value")
		throw std::runtime_error("Format error: input file not in date | value format");
	while (std::getline(input, row))
	{
		// parse year and check if valid, parse values and check if within 0 - 1000
		std::string date = parseDate(row);
		// match year to exchange rates
		// if valid, multiple value by exchange rate
		// if invalid, throw error
	}
}

double	BitcoinExchange::strToDouble(const std::string &str)
{
	char *end;

	float value = std::strtof(str.c_str(), &end);
	if (*end != '\0')
		throw std::runtime_error("Syntax error: value is not of type float");
	return static_cast<double>(value);
}


std::string	BitcoinExchange::splitString(bool date, char delimiter, std::string row)
{
	size_t pos;

	pos = row.find(delimiter);
	if (pos == std::string::npos)
		throw std::invalid_argument("Syntax error: invalid delimiter");
	return date ? row.substr(0, pos) : row.substr(pos + 1);
}

// Constructor
BitcoinExchange::BitcoinExchange()
{
	this->getExchangeRates();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	*this = copy;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this != &copy)
		this->_exchangeRates = copy._exchangeRates;
	return *this;
}