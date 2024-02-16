# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 12:46:49 by Dugonzal          #+#    #+#              #
#    Updated: 2024/02/13 04:08:09 by Dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := webserv_tests

SHELL			:=	/bin/zsh

CXX := c++ -Wall -Werror -Wextra -pedantic -g3 -fsanitize=address -std=c++11  -l cppunit

SRC_DIR := src/
OBJ_DIR := obj/

# deberia crear dos caarpetas de teeseo y meter los archivos de test en ellas
#  parsetTest y serverTest

SRC_FILES := main  Test

SRC				:= $(addprefix ${SRC_DIR}, $(addsuffix .cpp, ${SRC_FILES}))

OBJ				:= $(addprefix ${OBJ_DIR}, $(addsuffix .o, ${SRC_FILES}))

all: $(NAME)

$(NAME): $(OBJ)
	mkdir -p bin
	cp -r ../obj/*/* obj/
	$(CXX) $(OBJ_DIR)*.o -o $@ && ./$@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(NAME)

fclean: clean
	rm -rf $(OBJ_DIR)

re: fclean all
