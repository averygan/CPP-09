/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:29:08 by agan              #+#    #+#             */
/*   Updated: 2024/06/25 14:29:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void arg_checker(int argc)
{
	if (argc == 1)
		throw std::invalid_argument("Error: ./PmergeMe [input] ...");
}

int *parse_args(int argc, char **argv)
{
	int *arr = new int[argc - 1];

	for (int i = 1; i < argc; i++)
	{
		std::stringstream ss(argv[i]);
		int num;
		ss >> num;

		if (ss.fail() || !ss.eof())
		{
			delete[] arr;
			throw std::invalid_argument("Error: invalid argument");
		}
		else
		{
			if (num < 0)
				throw std::invalid_argument("Error: non-positive integer");
			arr[i] = num;
		}
	}
	return arr;
}

void printBefore(int size, int *arr)
{
	std::cout << "Before: ";
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	try
	{
		arg_checker(argc);
		int *arr = parse_args(argc, argv);
		printBefore(argc - 1, arr);

		PmergeMe vector = PmergeMe(arr, VECTOR, argc - 1);
		PmergeMe list = PmergeMe(arr, LIST, argc - 1);
		vector.mergeInsertionSort(arr);
		list.mergeInsertionSort(arr);

		list.printSorted();
		vector.printDuration();
		list.printDuration();
		delete[] arr;
	}
	catch (std::exception &e)
	{
		std::cout << RED << e.what() << RESET << std::endl;
	}
}
