NAME = containers
SRC = main.cpp
INC = vector.hpp map.hpp iterator.hpp

ifdef DEBUG
	CC=clang++
	ASAN_OPTIONS='detect_leaks=1'
	FLAGS = -Wall -Wextra -fsanitize=address -DDEBUG=1 -g -std=c++98 -pedantic -Wshadow -ferror-limit=1000 -O3
else
	CC=c++
	FLAGS = -Wall -Wextra -Werror -O3
endif

ifdef STD
	FLAGS := $(FLAGS) -DSTD=1
endif

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(INC)
	$(CC) $(FLAGS) -c $< -o $@

pretest:
	$(MAKE) re DEBUG=1
	./containers

test:
	$(MAKE) re DEBUG=1
	./containers > output
	$(MAKE) re STD=1
	./containers > std_output
	diff -a std_output output
	$(MAKE) -C ext #TODO remove
	#$(MAKE) re DEBUG=1 SRC=test_avl.cpp NAME=test_avl
	#./test_avl

fast:
	$(MAKE) -C ext #TODO remove

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
