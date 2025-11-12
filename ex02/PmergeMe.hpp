/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:44:58 by lgrisel           #+#    #+#             */
/*   Updated: 2025/11/12 11:37:07 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <algorithm>

class PmergeMe
{
	private:
		std::vector<int>	_vec;
		std::deque<int>		_deq;

		void	sortVector(std::vector<int> &input);
		void	sortDeque(std::deque<int> &input);

		template	<typename T>
		void	printContainer(const T &container, const std::string &prefix);
		std::vector<size_t>	generateJacobsthalSequence(size_t size) const;
		std::deque<size_t>	generateJacobsthalSequenceDeque(size_t size);

		public:
		PmergeMe();
		~PmergeMe();

		void	parseArgs(char **av, int ac);
		void	sortAndMesure();
};
