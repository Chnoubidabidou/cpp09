/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:41:55 by lgrisel           #+#    #+#             */
/*   Updated: 2025/10/14 16:25:09 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>

class	BitcoinExchange
{
	class	FileException : public std::exception
	{
		public:
			const char	*what() const throw();
	};

	protected:
		std::map<time_t, float>	data;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		~BitcoinExchange();
		BitcoinExchange	&operator=(const BitcoinExchange &copy);

		void	setData(const std::string	&filename);
		void	exchange(const std::string	&filename) const;
};
