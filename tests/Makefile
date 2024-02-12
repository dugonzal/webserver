# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 12:46:49 by Dugonzal          #+#    #+#              #
#    Updated: 2024/02/12 13:18:13 by Dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := webserv_tests

CXX := c++ -Wall -Werror -Wextra -pedantic -g3 -fsanitize=address -std=c++11  -lcppunit

SRC_DIR := src/
OBJ_DIR := obj/
 
SRC_FILES := main suma

SRC				:= $(addprefix ${SRC_DIR}, $(addsuffix .cpp, ${SRC_FILES}))

OBJ				:= $(addprefix ${OBJ_DIR}, $(addsuffix .o, ${SRC_FILES}))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ && ./$@ 

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	echo $(OBJ)
	exit
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TEST_BIN)

re: fclean all
