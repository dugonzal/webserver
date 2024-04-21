# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 02:17:20 by Dugonzal          #+#    #+#              #
#    Updated: 2024/04/21 13:05:09 by Dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	webserv

SHELL			:=	/bin/zsh

CXX				:= c++ -Wall -Werror -Wextra -pedantic -g3 -fsanitize=address -std=c++98

INC_DIR		:= inc/
INC_FILES += $(addprefix $(P_DIR),$(parser))
INC_FILES += $(addprefix $(S_DIR),$(server ))
INC_FILES += Signals Utils
INC 			:= $(addprefix $(I), $(INC_FILES))

SRC_DIR		:= src/

OBJ_DIR		:= obj/

P_DIR			:= parser/
parser		:= BaseParser Parser

S_DIR			:= server/
server		:= WebServer Server ServerManager \
							BaseServer Request Response Location Logger

SRC_FILES += $(addprefix $(P_DIR),$(parser))
SRC_FILES += $(addprefix $(S_DIR),$(server))

SRC_FILES += main Signals Utils 

SRC				:= $(addprefix ${SRC_DIR}, $(addsuffix .cpp, ${SRC_FILES}))

OBJ				:= $(addprefix ${OBJ_DIR}, $(addsuffix .o, ${SRC_FILES}))

.SILENT:

all: ${NAME} 

${NAME}: ${OBJ} ${I}
	${CXX} ${OBJ} -o ${NAME} && ./$@
	printf "compile done ->: [$@]\n"

#	make -C tests
#./webserv | cat -e > logs/parser_data.log

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp
	mkdir -p ${OBJ_DIR}
	mkdir -p ${OBJ_DIR}${P_DIR}
	mkdir -p ${OBJ_DIR}${S_DIR}
	${CXX} -c $? -o $@
	printf "compile ->: {$?}\n"

clean:
#		make clean -C ./tests
		rm -rf ${NAME}

fclean: clean
#		make fclean -C ./tests
		rm -rf	${OBJ_DIR}

re: fclean all

serv:
	sudo python3 -m http.server 80853

init:
	sudo python main.py

cleanPorts:
	sudo lsof -i | grep 'webserv' | awk '{print}' | sudo xargs kill -9

val:
	valgrind ./${NAME}
