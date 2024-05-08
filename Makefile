# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 02:17:20 by Dugonzal          #+#    #+#              #
#    Updated: 2024/05/08 08:32:11 by jaizpuru         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	webserv

SHELL			:=	/bin/zsh

CXX				:= c++ -Wall -Werror -Wextra -pedantic -std=c++98 -O3

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
							BaseServer Request Response Location CGI

SRC_FILES += $(addprefix $(P_DIR),$(parser))
SRC_FILES += $(addprefix $(S_DIR),$(server))

SRC_FILES += main Signals Utils Logger

SRC				:= $(addprefix ${SRC_DIR}, $(addsuffix .cpp, ${SRC_FILES}))

OBJ				:= $(addprefix ${OBJ_DIR}, $(addsuffix .o, ${SRC_FILES}))

.SILENT:

all: ${NAME}

${NAME}: ${OBJ} ${I}
	${CXX} ${OBJ} -o ${NAME}
	printf "compile done ->: [$@]\n"

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp
	mkdir -p ${OBJ_DIR}
	mkdir -p ${OBJ_DIR}${P_DIR}
	mkdir -p ${OBJ_DIR}${S_DIR}
	${CXX} -c $? -o $@
	printf "compile ->: {$?}\n"

clean:
	rm -rf ${NAME}

fclean: clean
	rm -rf	${OBJ_DIR}

re: fclean all
