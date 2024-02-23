# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 02:17:20 by Dugonzal          #+#    #+#              #
#    Updated: 2024/02/20 19:40:21 by Dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	webserv

SHELL			:=	/bin/zsh

CXX					:= c++ -Wall -Werror -Wextra -pedantic -g3 -fsanitize=address -std=c++98

I					:= inc/*/*.hpp

SRC_DIR		:= src/

OBJ_DIR		:= obj/

P_DIR			:= parser/
parser		:= parser

S_DIR			:= server/
server		:= BaseServer Server config

SRC_FILES += main Signals utils 

SRC_FILES += $(addprefix $(P_DIR),$(parser))
SRC_FILES += $(addprefix $(S_DIR),$(server))

SRC				:= $(addprefix ${SRC_DIR}, $(addsuffix .cpp, ${SRC_FILES}))

OBJ				:= $(addprefix ${OBJ_DIR}, $(addsuffix .o, ${SRC_FILES}))

all: ${NAME}

${NAME}: ${OBJ} ${I}
	${CXX} ${OBJ} -o $@ && ./$@ 
# compile tests automatically
	cp -r webserv tests/bin/
#	make  re -C  tests/
	./webserv | cat -e > logs/parser_data.log 

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp

	mkdir -p ${OBJ_DIR}
	mkdir -p ${OBJ_DIR}${P_DIR}
	mkdir -p ${OBJ_DIR}${S_DIR}

	${CXX} -c $? -o $@ 

clean:
		rm -rf ${NAME}

fclean: clean
		make fclean -C  tests
		rm -rf	${OBJ_DIR}

tests:
	make re -C  ./tests/

re: fclean all tests 

	
serv:
	sudo python3 -m http.server 80853

init:
	sudo python main.py

cleanPorts:
	sudo lsof -i   | grep 'python' | awk '{print }'  | sudo xargs kill -9
