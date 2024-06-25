/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:29:13 by agan              #+#    #+#             */
/*   Updated: 2024/06/25 14:29:14 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {};

PmergeMe::PmergeMe(int *arr, container type, size_t size) : _size(size), _container(type)
{
	if (_container == VECTOR)
	{
		this->createVector(arr);
	}
	// else if (_container == LIST)
	// {
	// 	createList(int *arr);
	// }
	else
		throw std::runtime_error("Error: invalid container");
}

PmergeMe::~PmergeMe() {};

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	*this = copy;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
	(void)copy;
	return *this;
}

void PmergeMe::sort()
{
	if (this->_container == VECTOR)
		sortVectorPairs();
}

void PmergeMe::printContainer()
{
	if (_container == VECTOR)
	{
		std::vector<std::pair<int, int> >::iterator i;
		for (i = this->_vector.begin(); i != this->_vector.end(); i++)
		{
			std::cout << "pair: [" << i->first << "] [" << i->second << "]" << std::endl;
		}
	}
}

void PmergeMe::sortVectorPairs()
{
	std::vector<std::pair<int, int> >::iterator it;
	for (it = this->_vector.begin(); it != this->_vector.end(); it++)
	{
		if (it->first < it->second)
		{
			int tmp = it->first;
			it->first = it->second;
			it->second = tmp;
		}
	}
	printContainer();
}

void PmergeMe::createVector(int *arr)
{	
	size_t j = 0;
	bool straggler = (this->_size % 2);

	for (size_t i = 0; i < this->_size / 2; i++)
	{
		if (straggler && j == this->_size - 1)
			break ;
		std::pair<int, int> _pair;
		_pair.first = arr[j];
		_pair.second = arr[j + 1];
		this->_vector.push_back(_pair);
		j += 2;
	}
	if (straggler)
	{
		std::pair<int, int> _pair;
		_pair.first = arr[j];
		_pair.second = -1;
		this->_vector.push_back(_pair);
	}
	// printContainer();
}

// void PmergeMe::createList(int *arr)
// {
// }
