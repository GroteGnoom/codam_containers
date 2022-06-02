NAME = containers
NAMESUB = containerssub
SRC = main.cpp
SRCSUB = subjectmain.cpp
INC = vector.hpp map.hpp iterator.hpp stack.hpp node_iterator.hpp pair.hpp rest.hpp printing.hpp printing.hpp vector_iterator.hpp 

ifdef DEBUG
	CC=clang++
	ASAN_OPTIONS='detect_leaks=1'
	FLAGS = -Wall -Wextra -fsanitize=address -DDEBUG=1 -g -std=c++98 -pedantic -Wshadow -ferror-limit=1000  -O3
else
	CC=c++
	FLAGS = -Wall -Wextra -Werror -O3
endif

ifdef STD
	FLAGS := $(FLAGS) -DSTD=1
endif

OBJ = $(SRC:.cpp=.o)
OBJSUB = $(SRCSUB:.cpp=.o)

all: $(NAME)
allsub: $(NAMESUB)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(NAMESUB): $(OBJSUB)
	$(CC) $(FLAGS) $(OBJSUB) -o $(NAMESUB)

%.o: %.cpp $(INC)
	$(CC) $(FLAGS) -c $< -o $@

pretest:
	$(MAKE) re DEBUG=1
	./containers

test:
	#$(MAKE) -C ext
	$(MAKE) resub DEBUG=1
	time ./containerssub 100 > output
	$(MAKE) resub STD=1
	time ./containerssub 100 > std_output
	$(MAKE) re DEBUG=1
	./containers > output
	$(MAKE) re STD=1
	./containers > std_output
	diff -a std_output output
	#$(MAKE) re DEBUG=1 SRC=test_avl.cpp NAME=test_avl
	#./test_avl

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
cleansub:
	rm -f $(OBJSUB)

fcleansub: cleansub
	rm -f $(NAMESUB)

resub: fcleansub allsub
.PHONY: all clean fclean re
