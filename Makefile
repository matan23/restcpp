NAME    = MyRestSql

INSTALL_DIR = /usr/local/bin
RC_FILE = restsql.rc
FILES_DIR = /etc/MyRestSql/

SRC     = create_table.cpp\
insert.cpp\
update.cpp\
delete.cpp\
select.cpp\
sqlite.cpp\
dispatcher.cpp\
get_method.cpp\
post_method.cpp\
put_method.cpp\
delete_method.cpp\
patch_method.cpp\
jsoncpp.cpp \
parser_helper.cpp \
parse_table.cpp\
parse_row.cpp\
server.cpp\
client_handler.cpp\
response.cpp

OBJ	= $(SRC:.cpp=.o)

CC      = g++

CXXFLAGS  = -W -Wall -g3

# LFLAGS	= -pthread -lboost_system-mt -lboost_regex-mt -lboost_filesystem-mt

LFLAGS	= -l sqlite3 -lboost_unit_test_framework -pthread -lboost_system-mt -lboost_regex-mt -lboost_filesystem-mt

RM      = rm -f



all	:  $(OBJ)
	   $(CC) -o $(NAME) $(LFLAGS) main.cpp $(OBJ)	   

install	:
	  mkdir -p $(INSTALL_DIR)
	  mkdir -p $(FILES_DIR)
	  cp $(NAME) $(INSTALL_DIR)
	  insserv $(RC_FILE)

test :	$(OBJ)
		g++ -otest $(LFLAGS) test.cpp $(OBJ)

clean	:
	  find . -name "*~" -exec rm {} \;
	  find . -name "*.o" -exec rm {} \;
	  find . -name "dev.sqlite3" -exec rm {} \;

fclean	: clean
	  $(RM) $(NAME)

re	: clean all

.PHONY	: clean fclean ld re install
