/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:43:34 by lgrisel           #+#    #+#             */
/*   Updated: 2025/10/20 11:49:24 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Usage: ./PmergeMe <sequence>" << std::endl;
		return (EXIT_FAILURE);
	}

	try
	{
		PmergeMe	sorter;
		sorter.parseArgs(av + 1, ac - 1);
		sorter.sortAndMesure();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
