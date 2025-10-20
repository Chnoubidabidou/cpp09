/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:43:37 by lgrisel           #+#    #+#             */
/*   Updated: 2025/10/20 11:29:45 by lgrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <cmath>
#include <cerrno>
#include <string>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

class RPN
{
	protected:
		std::stack<double>	stack;

		size_t	parseValue(const std::string &str, size_t start);
		size_t	parseOp(const std::string &str, size_t start);
		void	doOp(char op);

	public:
		RPN();
		RPN(const RPN &copy);
		~RPN();
		RPN		&operator=(const RPN &copy);

		double	compute(const std::string &str);
};
