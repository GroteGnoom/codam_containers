NAME = containers
SRC = main.cpp
INC = vector.hpp map.hpp iterator.hpp

ifdef DEBUG
	CC=clang++
	ASAN_OPTIONS='detect_leaks=1'
	FLAGS = -Wall -Wextra -fsanitize=address -DDEBUG=1 -g -std=c++98 -pedantic -Wshadow
else
	CC=c++
	FLAGS = -Wall -Wextra -Werror
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

test:
	$(MAKE) re STD=1
	./containers > std_output
	$(MAKE) re DEBUG=1
	./containers > output
	diff -a std_output output

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
