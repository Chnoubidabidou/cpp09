/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:46:01 by calleaum          #+#    #+#             */
/*   Updated: 2025/11/24 11:45:44 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::parseArgs(char **av, int ac)
{
	for (int i = 0; i < ac; ++i)
	{
		// Convert each argument to an integer
		std::istringstream iss(av[i]);
		int num;
		// Check: valid number non negative and nothing extra after the number
		if (!(iss >> num) || num < 0 || !iss.eof())
		{
			throw std::invalid_argument("Invalid input: " + std::string(av[i]));
		}
		// Store in vector and deque
		_vec.push_back(num);
		_deq.push_back(num);
	}
}

template <typename T>
void PmergeMe::printContainer(const T &container, const std::string &prefix)
{
	std::cout << prefix;
	for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template <typename T>
bool isSorted(const T &container)
{
	if (container.size() < 2)
		return (true);
	typename T::const_iterator it = container.begin();
	typename T::const_iterator next = it;
	++next;

	// Check each pair
	while (next != container.end())
	{
		if (*it > *next)
			return (false);
		++it;
		++next;
	}
	return (true);
}

std::vector<size_t> PmergeMe::generateJacobsthalSequence(size_t size) const
{
	std::vector<size_t> seq;
	seq.push_back(1);
	while (seq.back() < size)
	{
		size_t n = seq.size();
		size_t next = (n == 1) ? 3 : seq[n - 1] + 2 * seq[n - 2];
		if (next < size)
			seq.push_back(next);
		else
			break;
	}
	std::vector<size_t> full;
	std::vector<bool> used(size, false);
	for (size_t i = 0; i < seq.size(); ++i)
	{
		full.push_back(seq[i]);
		used[seq[i]] = true;
	}
	for (size_t i = 0; i < size; ++i)
		if (!used[i])
			full.push_back(i);
	return (full);
}

std::deque<size_t> PmergeMe::generateJacobsthalSequenceDeque(size_t size)
{
    std::deque<size_t> seq;
    seq.push_back(1);
    
    while (seq.back() < size)
    {
        size_t n = seq.size();
        size_t next = (n == 1) ? 3 : seq[n - 1] + 2 * seq[n - 2];
        if (next < size)
            seq.push_back(next);
        else
            break;
    }
    std::deque<size_t> full;
    std::deque<bool> used(size, false);
    for (size_t i = 0; i < seq.size(); ++i)
    {
        full.push_back(seq[i]);
        used[seq[i]] = true;
    }
    for (size_t i = 0; i < size; ++i)
        if (!used[i])
            full.push_back(i);
    return (full);
}

void PmergeMe::sortAndMesure()
{
	printContainer(_vec, "Before: ");

	// Sort vector + measure time
	std::vector<int> vecCopy = _vec;
	clock_t start1 = clock();
	sortVector(vecCopy);
	clock_t end1 = clock();

	// Sort deque + measure time
	std::deque<int> deqCopy = _deq;
	clock_t start2 = clock();
	sortDeque(deqCopy);
	clock_t end2 = clock();

	// Print result
	printContainer(vecCopy, "After: ");
	printContainer(deqCopy, "After: ");

	std::cout << "Vector sort " << (isSorted(vecCopy) ? "OK" : "KO") << std::endl;
	std::cout << "Deque sort " << (isSorted(deqCopy) ? "OK" : "KO") << std::endl;

	// Compute time in microseconds
	double durationVec = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1e6;
	double durationDeq = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1e6;

	// Print timing results
	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector : " << durationVec
			  << "μs" << std::endl;

	std::cout << "Time to process a range of " << _deq.size()
			  << " elements with std::deque : " << durationDeq
			  << "μs" << std::endl;
}

void PmergeMe::sortVector(std::vector<int> &input)
{
	if (input.size() <= 1)
		return;
	std::vector<int> mainChain;
	std::vector<int> pendings;

	// Split into pairs (a, b) with a ≤ b
	size_t i = 0;
	while (i + 1 < input.size())
	{
		int a = input[i];
		int b = input[i + 1];
		if (a > b)
			std::swap(a, b);
		pendings.push_back(a);
		mainChain.push_back(b);
		i += 2;
	}

	// Handle last lone element
	bool hasOdd = (input.size() % 2 != 0);
	int lastElement = hasOdd ? input.back() : 0;

	// Sort the bigger elements
	std::sort(mainChain.begin(), mainChain.end());

	// Insert smaller elements following Jacobsthal order
	std::vector<size_t> order = generateJacobsthalSequence(pendings.size());
	for (std::vector<size_t>::iterator it = order.begin(); it != order.end(); ++it)
	{
		if (*it >= pendings.size())
			continue;
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), pendings[*it]);
		mainChain.insert(pos, pendings[*it]);
	}

	// Insert last odd element
	if (hasOdd)
	{
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), lastElement);
		mainChain.insert(pos, lastElement);
	}

	// Replace input with sorted chain
	input = mainChain;
}

void PmergeMe::sortDeque(std::deque<int> &input)
{
	if (input.size() <= 1)
		return;
	std::deque<int> mainChain;
	std::deque<int> pendings;

	// Split into pairs (a, b)
	size_t i = 0;
	while (i + 1 < input.size())
	{
		int a = input[i];
		int b = input[i + 1];
		if (a > b)
			std::swap(a, b);
		pendings.push_back(a);
		mainChain.push_back(b);
		i += 2;
	}

	// Handle last lone element
	bool hasOdd = (input.size() % 2 != 0);
	int lastElement = hasOdd ? input.back() : 0;

	// Sort the bigger elements
	std::sort(mainChain.begin(), mainChain.end());

	// Insert smaller elements following Jacobsthal order
	std::deque<size_t> order = generateJacobsthalSequenceDeque(pendings.size());
	for (std::deque<size_t>::iterator it = order.begin(); it != order.end(); ++it)
	{
		if (*it >= pendings.size())
			continue;
		std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), pendings[*it]);
		mainChain.insert(pos, pendings[*it]);
	}

	// Insert last odd element
	if (hasOdd)
	{
		std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), lastElement);
		mainChain.insert(pos, lastElement);
	}

	// Replace input with sorted chain
	input = mainChain;
}
