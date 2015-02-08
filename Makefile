NAME    = MyRestSql


SRC     =	main.cpp create_table.cpp insert.cpp select.cpp

OBJ	= $(SRC:.cpp=.o)

CC      = g++

CXXFLAGS  = -W -Wall -g3

# LFLAGS	= -pthread -lboost_system-mt -lboost_regex-mt -lboost_filesystem-mt

RM      = rm -f


all	:  $(OBJ)
	   $(CC) -o $(NAME) $(OBJ)


clean	:
	  find . -name "*~" -exec rm {} \;
	  find . -name "*.o" -exec rm {} \;

fclean	: clean
	  $(RM) $(NAME)

re	: clean all

.PHONY	: clean fclean ld re install