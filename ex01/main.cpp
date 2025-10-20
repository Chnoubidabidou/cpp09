/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:43:34 by lgrisel           #+#    #+#             */
/*   Updated: 2025/10/20 11:31:28 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char *argv[])
{
	RPN	rpn;

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
		return (EXIT_FAILURE);
	}

	if (argc > 2)
	{
		std::cerr << argv[0] << ": too many arguments" << std::endl;
		return (EXIT_FAILURE);
	}

	try
	{
		std::cout << rpn.compute(argv[1]) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << argv[0] << ": " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
