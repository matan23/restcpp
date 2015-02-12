#include "restsql.h"

bool isInteger(const std::string &s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

std::string parse_error(Json::Reader &reader) {
    std::string error = reader.getFormattedErrorMessages();
	  std::cout  << "Failed to parse configuration\n" << error;
return error;
}


bool jsonKeyIsSuppportedType(Json::Value &value) {
    return (value.isString() == true);
}

bool jsonValueIsSuppportedType(Json::Value &value) {
return (value.isString() == true ||
        value.isBool() == true ||
        value.isInt() == true ||
        value.isUInt() == true ||
        value.isDouble() == true ||
        value.isNumeric() == true);    
}
bool jsonIsSuppportedType(Json::ValueIterator &iterator) {
    Json::Value key = iterator.key();
    Json::Value value = *iterator;

    return (key.isString() == true && (
        value.isString() == true ||
        value.isBool() == true ||
        value.isInt() == true ||
        value.isUInt() == true ||
        value.isDouble() == true ||
        value.isNumeric() == true
        ));
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