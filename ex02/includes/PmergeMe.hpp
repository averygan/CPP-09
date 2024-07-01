/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:29:18 by agan              #+#    #+#             */
/*   Updated: 2024/06/25 14:29:19 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <list>
#include <sstream>
#include <ctime>
#include <iomanip>

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

enum container 
{
	VECTOR,
	LIST,
	INVALID
};

class PmergeMe {
	public:
		PmergeMe();
		PmergeMe(int *arr, container type, size_t size);
		~PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe &operator=(const PmergeMe &copy);

		void	mergeInsertionSort(int *arr);
		void	printDuration();
		void	printSorted();

	private:
		size_t		_size;
		container 	_container;
		/* ----------------------- Vector functions ----------------------- */
		std::vector<std::pair<int, int> > _vector;
		std::vector<int> _usVector;
		std::vector<int> _sVector;
		std::vector<int> _pend;
		std::vector<int> _index;
		std::clock_t _start;
		std::clock_t _end;

		// Create vector and pairs
		void	createVector(int *arr);
		void 	createVectorPairs(int *arr);
		void	sortVectorPairs();
		// Merge sort function to recursively sort pairs
		void	mergeSort(std::vector<std::pair<int, int> >&arr, int left, int right);
		void	merge(std::vector<std::pair<int, int> >&arr, int left, int mid, int right);
		// Function to create sequence
		void	createSequence();
		// Jacobsthal functions
		std::vector<int> createJacobsthal(size_t n);
		// Get index of pend elements to be inserted to main chain
		void	getIndex(std::vector<int> &jacob);
		int		binarySearch(int n);
		// Push to main chain
		void	pushToMainChain(int straggler);

		/* ----------------------- List functions ----------------------- */
		std::list<std::pair<int, int> > _list;
		std::list<int> _usList;
		std::list<int> _sList;
		std::list<int> _lpend;
		std::list<int> _lindex;
		
		// Create list and pairs
		void createList(int *arr);
		void createListPairs(int *arr);
		void sortListPairs();
		// Merge sort function
		void merge(std::list<std::pair<int, int> >::iterator left, \
				std::list<std::pair<int, int> >::iterator mid, \
				std::list<std::pair<int, int> >::iterator right);
		void mergeSort(std::list<std::pair<int, int> >& lst, \
				std::list<std::pair<int, int> >::iterator left, \
				std::list<std::pair<int, int> >::iterator right);
		// Function to create sequence
		void createListSequence();
		// Jacobsthal func
		std::list<int> createJacobsthalList(size_t n);
		// Get index of pend elements to be inserted to main chain
		void	getIndex(std::list<int> &jacob);
		int		binarySearchList(int n);
		void	pushToMainChainList(int straggler);

		/* Common functions */
		size_t	jacobsthal(int n);

		/* Validate sorted functions */
		bool	isSorted(const std::vector<int>vector);
		bool	isSorted(const std::list<int>list);

		// For testing
		void	printContainer();
		void	printVector(std::string name, std::vector<int> vector);
		void 	printList(std::string name, const std::list<int> list);
};

#endif