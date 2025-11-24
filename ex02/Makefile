# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgrisel <lgrisel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 09:07:48 by calleaum          #+#    #+#              #
#    Updated: 2025/11/24 11:45:14 by lgrisel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	PmergeMe
SRC =	main.cpp	PmergeMe.cpp
OBJ = $(SRC:.cpp=.o)

C++ =  c++
C++_FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	$(C++) $(C++_FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(C++) $(C++_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re bonus
