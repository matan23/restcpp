NAME    = MyRestSql

SRC     =	main.cpp \
create_table.cpp\
insert.cpp\
update.cpp\
delete.cpp\
select.cpp\
sqlite.cpp\
dispatcher.cpp\
post_method.cpp\
put_method.cpp\
delete_method.cpp\
patch_method.cpp\
get_method.cpp

OBJ	= $(SRC:.cpp=.o)

CC      = g++

CXXFLAGS  = -W -Wall -g3

# LFLAGS	= -pthread -lboost_system-mt -lboost_regex-mt -lboost_filesystem-mt

LFLAGS	= -l sqlite3 -lboost_unit_test_framework

RM      = rm -f


all	:  $(OBJ)
	   $(CC) -o $(NAME) $(LFLAGS) $(OBJ)


clean	:
	  find . -name "*~" -exec rm {} \;
	  find . -name "*.o" -exec rm {} \;
	  find . -name "dev.sqlite3" -exec rm {} \;

fclean	: clean
	  $(RM) $(NAME)

re	: clean all

.PHONY	: clean fclean ld re install