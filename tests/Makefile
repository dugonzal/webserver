NAME 			:= webserv_tests

SHELL			:=	/bin/zsh

CXX 			:= c++ -Wall -Werror -Wextra -pedantic -g3 -fsanitize=address -std=c++11  -lcppunit

SRC_DIR 	:= src/
OBJ_DIR 	:= obj/

# deberia crear dos caarpetas de teeseo y meter los archivos de test en ellas
#  parsetTest y serverTest

SRC_FILES := main  Test

SRC				:= $(addprefix ${SRC_DIR}, $(addsuffix .cpp, ${SRC_FILES}))

OBJ				:= $(addprefix ${OBJ_DIR}, $(addsuffix .o, ${SRC_FILES}))

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	mkdir -p ${OBJ_DIR}
	rm -rf ../obj/main.o
	cp -r ../obj/*/*.o ../obj/*.o  obj/
	$(CXX) $(OBJ_DIR)*.o -o $@ && ./$@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c $< -o $@

clean:
	rm -f $(NAME)

fclean: clean
	rm -rf $(OBJ_DIR)

re: fclean all