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
	else if (_container == LIST)
	{
		this->createList(arr);
	}
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

/* ----------------------- Common functions ----------------------- */

void PmergeMe::mergeInsertionSort()
{
	if (this->_container == VECTOR)
	{
		sortVectorPairs();
		mergeSort(_vector, 0, _vector.size() - 1);
		createSequence();
		// printVector("sVector", this->_sVector);
	}
	else if (this->_container == LIST)
	{
		sortListPairs();
		mergeSort(_list, _list.begin(), _list.end());
		printContainer();
		createListSequence();
		printList("sorted list", this->_sList);
	}
}

size_t PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

/* ----------------------- Vector functions ----------------------- */

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
	// printContainer();
}

std::vector<int> PmergeMe::createJacobsthal(size_t n)
{
	std::vector<int> jacob;

	int jacob_index = 3;
	while (jacobsthal(jacob_index) < n - 1)
	{
		jacob.push_back(this->jacobsthal(jacob_index));
		jacob_index++;
	}

	return jacob;
}

void PmergeMe::getIndex(std::vector<int> &jacob)
{
	size_t val = 1;
	size_t prev_index = 1;
	size_t curr_index = 1;

	if (this->_pend.empty())
		return ;
	while (!jacob.empty())
	{
		val = jacob.front();
		this->_index.push_back(val);
		curr_index = val - 1;
		while (curr_index > prev_index)
		{
			this->_index.push_back(curr_index);
			curr_index--;
		}
		prev_index = val;
		jacob.erase(jacob.begin());
	}
	while (val++ < this->_pend.size())
		this->_index.push_back(val);
}

int PmergeMe::binarySearch(int n)
{
	int low = 0;
	int high = _sVector.size();

	while (low < high)
	{
		int mid = low + (high - low) / 2;

		if (n < _sVector.at(mid))
			high = mid;
		else
			low = mid + 1;
	}
	return low;
}

// Push to main chain based on indexed seq using binary search
void PmergeMe::pushToMainChain(int straggler)
{
	int element;
	int mainIndex;

	while (!this->_index.empty())
	{
		element = this->_pend.at(_index.front() - 1);
		_index.erase(_index.begin());
		mainIndex = binarySearch(element);
		_sVector.insert(_sVector.begin() + mainIndex, element);
	}
	if (straggler != -1)
	{
		mainIndex = binarySearch(straggler);
		_sVector.insert(_sVector.begin() + mainIndex, straggler);
	}
}

void PmergeMe::createSequence()
{
	std::vector<std::pair<int, int> >::iterator it;
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
			_pend.push_back(it->second);	
		}
	}

	// Push first el in pend to sequence
	if (_pend.empty())
		return;
	_sVector.insert(_sVector.begin(), _pend.front());

	// Create jacobsthal
	jacobsthal = createJacobsthal(_pend.size());
	// Get index based on jacobsthal sequence
	getIndex(jacobsthal);
	// printVector("sVector", this->_sVector);
	// printVector("pend", this->_pend);
	// printVector("index", this->_index);
	pushToMainChain(straggler);
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

/* ----------------------- List functions ----------------------- */

void PmergeMe::createList(int *arr)
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
		this->_list.push_back(_pair);
		j += 2;
	}
	if (straggler)
	{
		std::pair<int, int> _pair;
		_pair.first = arr[j];
		_pair.second = -1;
		this->_list.push_back(_pair);
	}
}

void PmergeMe::sortListPairs()
{
	std::list<std::pair<int, int> >::iterator it;
	for (it = this->_list.begin(); it != this->_list.end(); it++)
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

void PmergeMe::merge(std::list<std::pair<int, int> >::iterator left, \
	std::list<std::pair<int, int> >::iterator mid, \
	std::list<std::pair<int, int> >::iterator right)
{
	// Create tmp lists
	std::list<std::pair<int, int> > L(left, mid);
	std::list<std::pair<int, int> > R(mid, right);

    std::list<std::pair<int, int> >::iterator leftIter = L.begin();
    std::list<std::pair<int, int> >::iterator rightIter = R.begin();
    std::list<std::pair<int, int> >::iterator lstIter = left;

	// Merge temporary lists back into lst
	while (leftIter != L.end() && rightIter != R.end())
	{
		if (leftIter->first <= rightIter->first)
		{
			*lstIter = *leftIter;
			leftIter++;
		}
		else
		{
			*lstIter = *rightIter;
			rightIter++;
		}
		lstIter++;
	}
	// Copy remaining nodes
	while (leftIter != L.end())
	{
		*lstIter = *leftIter;
		leftIter++;
		lstIter++;
	}
	while (rightIter != R.end())
	{
		*lstIter = *rightIter;
		rightIter++;
		lstIter++;
	}
}

// Merge sort for vectors
void PmergeMe::mergeSort(std::list<std::pair<int, int> >& lst, \
		std::list<std::pair<int, int> >::iterator left, \
		std::list<std::pair<int, int> >::iterator right)
{
	if (std::distance(left, right) <= 1)
		return;

	std::list<std::pair<int, int> >::iterator mid = left;
	std::advance(mid, std::distance(left, right) / 2);

	// Sort both halves
	mergeSort(lst, left, mid);
	mergeSort(lst, mid, right);

	// Merge sorted halves
	merge(left, mid, right);
}

void PmergeMe::createListSequence()
{
	std::list<std::pair<int, int> >::iterator it;
	std::list<int> jacobsthal;
	int straggler;

	straggler = -1;
	// Create sequence and pend
	for (it = this->_list.begin(); it != this->_list.end(); it++)
	{
		if (it->second == -1)
			straggler = it->first;
		else
		{
			_sList.push_back(it->first);
			_lpend.push_back(it->second);	
		}
	}

	// Push first el in pend to sequence
	if (_lpend.empty())
		return;
	_sList.push_front(_lpend.front());

	// Create jacobsthal
	jacobsthal = createJacobsthalList(_lpend.size());
	// Get index based on jacobsthal sequence
	getIndex(jacobsthal);
	printList("_sList", this->_sList);
	printList("_lpend", this->_lpend);
	pushToMainChainList(straggler);
}

std::list<int> PmergeMe::createJacobsthalList(size_t n)
{
	std::list<int> jacob;

	int jacob_index = 3;
	while (jacobsthal(jacob_index) < n - 1)
	{
		jacob.push_back(this->jacobsthal(jacob_index));
		jacob_index++;
	}

	printList("jacobsthal", jacob);
	return jacob;
}

void PmergeMe::getIndex(std::list<int> &jacob)
{
	size_t val = 1;
	size_t prev_index = 1;
	size_t curr_index = 1;

	if (this->_lpend.empty())
		return ;
	while (!jacob.empty())
	{
		val = jacob.front();
		this->_lindex.push_back(val);
		curr_index = val - 1;
		while (curr_index > prev_index)
		{
			this->_lindex.push_back(curr_index);
			curr_index--;
		}
		prev_index = val;
		jacob.pop_front();
	}
	while (val++ < this->_lpend.size())
		this->_lindex.push_back(val);

	// printList("index", _lindex);
}

int PmergeMe::binarySearchList(int n)
{
	int low = 0;
	int high = _sList.size();

	std::list<int>::iterator itLow = _sList.begin();
	std::list<int>::iterator itHigh = _sList.end();

	while (low < high)
	{
		int mid = low + std::distance(itLow, itHigh) / 2;

		std::list<int>::iterator itMid = itLow;
		std::advance(itMid, mid);

		if (n < *itMid)
		{
			itHigh = itMid;
			high = mid;
		}
		else
		{
			itLow = ++itMid;
			low = mid + 1;
		}
	}
	return low;
}

// Push to main chain based on indexed seq using binary search
void PmergeMe::pushToMainChainList(int straggler)
{
	int element;
	int mainIndex;
	std::list<int>::iterator it;
	std::list<int>::iterator mainIt;

	while (!this->_lindex.empty())
	{
		// Get element from lpend
		it = _lpend.begin();
		std::advance(it, _lindex.front());
		element = *it;
		// Remote index from front of lindex
		_lindex.pop_front();
		// Search for insertion index in main chain
		mainIndex = binarySearchList(element);
		// Advance and insert
		mainIt = _sList.begin();
		std::advance(mainIt, mainIndex);
		_sList.insert(mainIt, element);
	}
	if (straggler != -1)
	{
		mainIndex = binarySearchList(straggler);
		std::cout << "mainindex is " << mainIndex << std::endl;
		mainIt = _sList.begin();
		std::advance(mainIt, mainIndex);
		_sList.insert(mainIt, straggler);
	}
}

/* ----------------------- Debugging functions ----------------------- */

void PmergeMe::printVector(std::string name, const std::vector<int> vector)
{
	std::cout << GREEN << "printing " << name << RESET << std::endl;
	std::vector<int>::const_iterator i;
	for (i = vector.begin(); i != vector.end(); i++)
	{
		std::cout << "[" << *i << "]";
	}
	std::cout << GREEN << std::endl << "end of " << name << RESET << std::endl;
}

void PmergeMe::printList(std::string name, const std::list<int> list)
{
	std::cout << GREEN << "printing " << name << RESET << std::endl;
	std::list<int>::const_iterator i;
	for (i = list.begin(); i != list.end(); i++)
	{
		std::cout << "[" << *i << "]";
	}
	std::cout << GREEN << std::endl << "end of " << name << RESET << std::endl;
}

void PmergeMe::printContainer()
{
	std::cout << CYAN << "printing container" << RESET << std::endl;
	if (_container == VECTOR)
	{
		std::vector<std::pair<int, int> >::iterator i;
		for (i = this->_vector.begin(); i != this->_vector.end(); i++)
		{
			std::cout << "pair: [" << i->first << "] [" << i->second << "]" << std::endl;
		}
	}
	else if (_container == LIST)
	{
		std::list<std::pair<int, int> >::iterator i;
		for (i = this->_list.begin(); i != this->_list.end(); i++)
		{
			std::cout << "pair: [" << i->first << "] [" << i->second << "]" << std::endl;
		}
	}
	std::cout << CYAN << "end of container" << RESET << std::endl;
}

