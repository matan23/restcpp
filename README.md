#Building and installing

##DEBUG
just ./MyRestSql

##OSX
1. make re
2. make osx_install
3. enjoy
4. scripts/osx_restsql.rc status|start|stop|restart

##UNIX
1. make re
2. make install
3. service restsql.rc start
4. enjoy
5. service restsql.rc status|start|stop|restart


#Protocol Example

##Create Table
URL: /table
METHOD: POST
PAYLOAD:
{
    "name" "fruits",
    "columns": {
        "color":"text"
        "juiciness":"int",

    }
}

##INSERT ROW / UPDATE ROW
URL: /fruits
METHOD: POST/PUT
PAYLOAD:
{
    "myColumnName":"value",
    "myColumnName":"value"
}

#NC Examples
DELETE /boy/1 Host: http://localhost Connection: Close | nc localhost 8080