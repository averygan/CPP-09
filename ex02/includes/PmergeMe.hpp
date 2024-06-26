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

		void mergeInsertionSort();

	private:
		size_t		_size;
		container 	_container;
		// Containers of unsorted and sorted ints
		std::vector<std::pair<int, int> > _vector;
		std::vector<int> _sVector;
		std::list<std::pair<int, int> > _list;
		std::list<int> _sList;

		// Member functions for sorting vector
		void createVector(int *arr);
		void sortVectorPairs();
		void merge(std::vector<std::pair<int, int> >&arr, int left, int mid, int right);
		void createSequence();
		// Overloaded mergeSort
		void mergeSort(std::vector<std::pair<int, int> >&arr, int left, int right);
	
		// Member functions for sorting list

		// For testing
		void printContainer();
		void printSorted();
};

#endif