#include "restsql.h"

std::string parse_error(Json::Reader &reader) {
    std::string error = reader.getFormattedErrorMessages();
	  std::cout  << "Failed to parse configuration\n" << error;
return error;
}

int getNumberOfRows(std::string table, int id) {  
    string database_name = string("dev");
    ITranslatable *getQuery = new Select(table, id);

    Sqlite *db =  new Sqlite(database_name, getQuery->translateToSqlQuery());
    cout << getQuery->translateToSqlQuery() << "\n";
    cout << db->exec() << "\n";

    return db->result.size();
}

void printJSONValue(const Json::Value &val)
{
    if( val.isString() ) {
        printf( "string(%s)", val.asString().c_str() ); 
    } else if( val.isBool() ) {
        printf( "bool(%d)", val.asBool() ); 
    } else if( val.isInt() ) {
        printf( "int(%d)", val.asInt() ); 
    } else if( val.isUInt() ) {
        printf( "uint(%u)", val.asUInt() ); 
    } else if( val.isDouble() ) {
        printf( "double(%f)", val.asDouble() ); 
    }
    else 
    {
        printf( "unknown type=[%d]", val.type() ); 
    }
}