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

void PmergeMe::mergeInsertionSort()
{
	if (this->_container == VECTOR)
	{
		sortVectorPairs();
		mergeSort(_vector, 0, _vector.size() - 1);
		std::cout << "after:" << std::endl;
		printContainer();
		createSequence();
		printSorted();
	}
	// else if (this->container == LIST)
	// 	mergeSort(_list);
}

int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

void PmergeMe::createJacobsthal(size_t n)
{
	std::vector<int> j_arr;

	int jacob_index = 3;
	while (jacobsthal(jacob_index) < n - 1)
	{
		j_arr.push_back(this->jacobsthal(jacob_index));
		jacob_index++;
	}
	return j_arr;
}

void PmergeMe::createSequence()
{
	std::vector<std::pair<int, int> >::iterator it;
	std::vector<int> pend;
	std::vector<int> jacobsthal;
	int straggler;

	straggler = -1;
	// Create sequence and pend
	for (it = this->_vector.begin(); it != this->_vector.end(); it++)
	{
		if (it->second == -1)
			straggler = it->first;
		else
		{
			_sVector.push_back(it->first);
			pend.push_back(it->second);	
		}
	}

	// Push first el in pend to sequence
	if (pend.empty())
		return;
	_sVector.insert(_sVector.begin(), pend.front());
	pend.erase(pend.begin());

	// Create jacobsthal
	jacobsthal = createJacobsthal(pend.size());

	// // Function to print pend
	// std::vector<int>::iterator i;
	// std::cout << "Printing pend" << std::endl;
	// for (i = pend.begin(); i != pend.end(); i++)
	// {
	// 	std::cout << "[" << *i << "]" << std::endl;
	// }
	// std::cout << "End pend" << std::endl;
}

void PmergeMe::merge(std::vector<std::pair<int, int> >&arr, int left, int mid, int right)
{
	int leftSize = (mid - left) + 1; 
	int rightSize = right - mid;
	// Create temp arrays
	std::vector<std::pair<int, int> > L(leftSize);
	std::vector<std::pair<int, int> > R(rightSize);
	// Copy data
	for (int i = 0; i < leftSize; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < rightSize; j++)
		R[j] = arr[mid + 1 + j];

	int leftIndex = 0;
	int rightIndex = 0;
	int arrIndex = left;
	// Merge temporary arrays back
	while (leftIndex < leftSize && rightIndex < rightSize)
	{
		if (L[leftIndex].first <= R[rightIndex].first)
		{
			arr[arrIndex] = L[leftIndex];
			leftIndex++;
		}
		else
		{
			arr[arrIndex] = R[rightIndex];
			rightIndex++;
		}
		arrIndex++;
	}
	// Copy remaining elements
	while (leftIndex < leftSize)
	{
		arr[arrIndex] = L[leftIndex];
		leftIndex++;
		arrIndex++;
	}
	while (rightIndex < rightSize)
	{
		arr[arrIndex] = R[rightIndex];
		rightIndex++;
		arrIndex++;
	}
}

// Merge sort for vectors
void PmergeMe::mergeSort(std::vector<std::pair<int, int> >&arr, int left, int right)
{
	if (left >= right)
		return ;
	int mid = left + (right - left) / 2;

	// Sort both halves
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);

	// Merge sorted halves
	merge(arr, left, mid, right);
}

// Merge sort for lists

void PmergeMe::printSorted()
{
	if (_container == VECTOR)
	{
		std::vector<int>::iterator i;
		for (i = this->_sVector.begin(); i != this->_sVector.end(); i++)
		{
			std::cout << "[" << *i << "]" << std::endl;
		}
	}
	// To add: list
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
	// To add: list
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
