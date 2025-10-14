/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:41:55 by lgrisel           #+#    #+#             */
/*   Updated: 2025/10/14 16:28:11 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "DataParser.hpp"

const char *BitcoinExchange::FileException::what() const throw()
{
	return ("Error: could not open file.");
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : data(copy.data)
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this != &copy)
		this->data = copy.data;
	return (*this);
}

void BitcoinExchange::setData(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file)
		throw (FileException());

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string dateStr, valueStr;

		if (std::getline(ss, dateStr, ',') && std::getline(ss, valueStr))
		{
			try
			{
				char	*end;
				time_t date = DataParser::strtot(dateStr);
				float value = std::strtof(valueStr.c_str(), &end);
				this->data[date] = value;
			}
			catch (std::exception &e)
			{
				std::cerr << "Warning: " << e.what() << " (" << line << ")" << std::endl;
			}
		}
	}
}

void BitcoinExchange::exchange(const std::string &filename) const
{
	std::ifstream file(filename.c_str());
	if (!file)
		throw (FileException());

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string dateStr, valueStr;

		if (std::getline(ss, dateStr, '|') && std::getline(ss, valueStr))
		{
			dateStr.erase(dateStr.find_last_not_of(" \t") + 1);
			dateStr.erase(0, dateStr.find_first_not_of(" \t"));
			valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
			valueStr.erase(0, valueStr.find_first_not_of(" \t"));

			try
			{
				time_t date = DataParser::strtot(dateStr);
				float value = DataParser::strtof(valueStr);

				std::map<time_t, float>::const_iterator it = data.upper_bound(date);
				if (it != data.begin())
					--it;
				else
				{
					std::cerr << "Error: no rate available before " << dateStr << std::endl;
					continue;
				}

				float rate = it->second;
				std::cout << dateStr << " => " << value << " = " << value * rate << std::endl;
			}
			catch (std::exception &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		else
			std::cerr << "Error: bad input => " << line << std::endl;
	}
}
