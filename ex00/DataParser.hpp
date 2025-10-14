/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:24:32 by lgrisel           #+#    #+#             */
/*   Updated: 2025/10/14 16:25:40 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

class	DataParser
{
	class	InvalidDateException : public std::exception
	{
		private:
			std::string _message;

		public:
			InvalidDateException(const std::string &input);
			virtual	~InvalidDateException() throw();
			virtual char const	*what() const throw();
	};

	class	NumberTooLargeException : public std::exception
	{
		public:
			char const	*what() const throw();
	};

	class	NanException : public std::exception
	{
		public:
			char const	*what() const throw();
	};

	class	NotPositiveNumberException : public std::exception
	{
		public:
			char const	*what() const throw();
	};

	private:
		DataParser();
		DataParser(const DataParser &copy);
		DataParser	&operator=(const DataParser &copy);

	public:
		~DataParser();
		static	std::time_t	strtot(const std::string	&str);
		static	std::string	ttostr(const std::time_t	&time);

		static	float		strtof(const std::string	&str);
};
