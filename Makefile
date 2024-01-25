# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 02:17:20 by Dugonzal          #+#    #+#              #
#    Updated: 2024/01/25 10:26:02 by Dugonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	webserv

C					:= c++ -Wall -Werror -Wextra -g3 -fsanitize=address -std=c++98

SRC_DIR		:= src/

OBJ_DIR		:= obj/

SRC_FILES	:=  webserv server config 

I					:= inc/*.hpp

SRC				:= $(addprefix ${SRC_DIR}, $(addsuffix .cpp, ${SRC_FILES}))

OBJ				:= $(addprefix ${OBJ_DIR}, $(addsuffix .o, ${SRC_FILES}))

all: ${NAME}

${NAME}: ${OBJ} ${I}
	${C} ${OBJ} -o $@ 

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp

	mkdir -p ${OBJ_DIR}
	${C} -c $? -o $@ 

clean:
	
		rm -rf ${NAME}

fclean: clean
	
		rm -rf	${OBJ_DIR}

re: fclean all 

serv:
	
	sudo python3 -m http.server 80853

init:
	
	sudo python main.py

cleanPorts:
	
	sudo lsof -i   | grep 'python' | awk '{print }'  | sudo xargs kill -9
