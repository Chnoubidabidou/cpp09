/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:41:52 by lgrisel           #+#    #+#             */
/*   Updated: 2025/10/14 16:35:26 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "DataParser.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./btc <file>" << std::endl;
		return (1);
	}

	try
	{
		BitcoinExchange btc;
		btc.setData("./data.csv");
		btc.exchange(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}
