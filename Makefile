NAME = containers
NAMESUB = containerssub
SRC = main.cpp
SRCSUB = subjectmain.cpp
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
	$(MAKE) -C ext #TODO remove
	$(MAKE) re DEBUG=1
	./containers > output
	$(MAKE) re STD=1
	./containers > std_output
	diff -a std_output output
	$(MAKE) resub DEBUG=1
	./containerssub 100 > output
	$(MAKE) resub STD=1
	./containerssub 100 > std_output
	#$(MAKE) re DEBUG=1 SRC=test_avl.cpp NAME=test_avl
	#./test_avl

fast:
	$(MAKE) -C ext #TODO remove

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
