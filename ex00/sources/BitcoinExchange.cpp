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

/* Function to check if date is valid (inc leap year) */
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
		bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		return (is_leap ? (day <= 29) : (day <= 28));
	}
	else
	{
		if (day > days_in_month[month - 1])
			return false;
	}
	return true;
}

/* Function to parse date, return error for formatting, 
invalid date or 
date earlier than earliest date in _exchangeRates */
std::string BitcoinExchange::parseDate(const std::string &str, const BitcoinExchange &btc)
{
	std::string date;

	if (str.length() < 10 || str[4] != '-' || str[7] != '-')
		return "";
	for (int i = 0; i < 10; ++i) 
	{
		if (!isdigit(str[i]) && (i != 4 && i != 7))
			return "";
	}
	if (!is_valid_date(str))
		return "";
	std::string earliestDate = btc._exchangeRates.begin()->first;
	if (str.substr(0, 10) < earliestDate)
		return "";
	return (str.substr(0, 10));
}

/* Function to check for formatting and if value is valid float and positive int */
double BitcoinExchange::parseValue(const std::string row, const std::string date)
{
	char *end;

	if (row.length() < 13 || row.substr(10, 3) != " | ")
	{
		std::cout << "Error: bad input => " << row << std::endl;
		return -1;
	}
	else
	{
		float value = std::strtof(row.c_str() + 13, &end);
		if (*end != '\0')
			std::cout << "Error: invalid value => " << date << std::endl;
		else
		{
			double d_value = static_cast<double>(value);
			if (d_value < 0)
				std::cout << "Error: not a positive number." << std::endl;
			else if (d_value > 1000)
				std::cout << "Error: too large a number." << std::endl;
			else
			{
				std::cout << date << " => " << d_value << " = ";
				return d_value;
			}
		}
	}
	return -1;
}

/* Function to get rate based on matched date or earlier date from _exchangeRates map */
double BitcoinExchange::getRate(const std::string date, const BitcoinExchange &btc)
{
	std::map<std::string, double>::const_iterator it;
	double exchange_rate;

	for (it = btc._exchangeRates.begin(); it != btc._exchangeRates.end(); it++)
	{
		if (it->first <= date)
			exchange_rate = it->second;
		else
			break;
	}
	return exchange_rate;
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
	if (row != "date,exchange_rate")
		throw std::runtime_error("Error: data.csv not in 'date,exchange_rate' format");
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

    db.close();

	return 0;
}

/* Function to parse each line of input and print date + exchange values */
void	BitcoinExchange::getExchangeValues(std::ifstream &input, const BitcoinExchange &btc)
{
	std::string	row;

	std::getline(input, row);
	if (row != "date | value")
		throw std::runtime_error("Error: input file not in date | value format");
	while (std::getline(input, row))
	{
		// parse year and check if valid, parse values and check if within 0 - 1000
		std::string date = parseDate(row, btc);
		if (date.empty())
		{
			std::cout << "Error: bad input => " << row << std::endl;
			continue ;
		}
		double value = parseValue(row, date);
		if (value == -1)
			continue ;
		// match date to exchange rates -> print value * exchange rate
		std::cout << value * getRate(date, btc) << std::endl;
	}
}

/* Helper function to check if string is a valid float and parse to double */
double	BitcoinExchange::strToDouble(const std::string &str)
{
	char *end;

	float value = std::strtof(str.c_str(), &end);
	if (*end != '\0')
		throw std::runtime_error("Syntax error: value is not of type float");
	return static_cast<double>(value);
}

/* Function to split string based on delimiter */
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
	if (this->_exchangeRates.empty())
		throw std::runtime_error("Error: exchange rate data is empty");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	*this = copy;
}

// Destructor
BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this != &copy)
		this->_exchangeRates = copy._exchangeRates;
	return *this;
}