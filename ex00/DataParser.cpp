/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:24:33 by lgrisel           #+#    #+#             */
/*   Updated: 2025/10/14 16:32:45 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DataParser.hpp"

std::time_t DataParser::strtot(const std::string &str)
{
	std::tm tm = {};
	std::istringstream ss(str);
	char dash1, dash2;

	ss >> tm.tm_year >> dash1 >> tm.tm_mon >> dash2 >> tm.tm_mday;

	if (ss.fail() || dash1 != '-' || dash2 != '-')
		throw (DataParser::InvalidDateException(str));

	int year = tm.tm_year;
	int month = tm.tm_mon;
	int day = tm.tm_mday;

	if (month < 1 || month > 12 || day < 1 || day > 31)
		throw (DataParser::InvalidDateException(str));

	int days_in_month[] = {31, 28, 31, 30, 31, 30,
							31, 31, 30, 31, 30, 31};

	bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	if (is_leap)
		days_in_month[1] = 29;

	if (day > days_in_month[month - 1])
		throw (DataParser::InvalidDateException(str));

	tm.tm_year -= 1900;
	tm.tm_mon -= 1;
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;

	std::time_t result = std::mktime(&tm);
	if (result == -1)
		throw (DataParser::InvalidDateException(str));

	return (result);
}

std::string DataParser::ttostr(const std::time_t &time)
{
	char buffer[20];
	std::tm *tm = std::localtime(&time);
	if (!tm || std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm) == 0)
		return ("Invalid date");
	return (std::string(buffer));
}

float DataParser::strtof(const std::string &valueStr)
{
	std::istringstream ss(valueStr);
	float value;

	ss >> value;

	if (ss.fail() || !ss.eof())
		throw (DataParser::NanException());

	if (value < 0.0f)
		throw (DataParser::NotPositiveNumberException());

	if (value > 1000.0f)
		throw (DataParser::NumberTooLargeException());

	return (value);
}

DataParser::InvalidDateException::InvalidDateException(const std::string &input) : _message("Error: bad input => " + input)
{
}

DataParser::InvalidDateException::~InvalidDateException() throw()
{
}

const char *DataParser::InvalidDateException::what() const throw()
{
	return this->_message.c_str();
}

const char *DataParser::NanException::what() const throw()
{
	return "Error: not a number.";
}

const char *DataParser::NotPositiveNumberException::what() const throw()
{
	return "Error: not a positive number.";
}

const char *DataParser::NumberTooLargeException::what() const throw()
{
	return "Error: too large a number.";
}
