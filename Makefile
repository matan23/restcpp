NAME    = MyRestSql

INSTALL_DIR = /usr/local/bin
LAUNCHD_FILE = com.mataejoon.restsql.plist
RC_FILE = restsql.rc
FILES_DIR = /etc/MyRestSql/
LOG_DIR = /var/log/restsql

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

CXXFLAGS  = -W -Wall -g3 -std=c++0x

# LFLAGS	= -pthread -lboost_system-mt -lboost_regex-mt -lboost_filesystem-mt

LFLAGS	= -l sqlite3 -lboost_unit_test_framework -pthread -lboost_system-mt -lboost_regex-mt -lboost_filesystem-mt

RM      = rm -f



all	:  $(OBJ)
	   $(CC) -o $(NAME) $(LFLAGS) main.cpp $(OBJ)	   

osx_install :
	  cp scripts/$(LAUNCHD_FILE) /Users/matan/Library/LaunchAgents/
	  scripts/osx_restsql.rc restart

osx_uninstall :
	  scripts/restsql.rc stop

install	:
	  mkdir -p $(INSTALL_DIR)
	  mkdir -p $(FILES_DIR)
	  mkdir -p $(LOG_DIR)
	  cp $(NAME) $(INSTALL_DIR)
	  cp $(RC_FILE) /etc/init.d/
	  insserv $(RC_FILE)
uninstall :
	insserv --remove $(RC_FILE)


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
