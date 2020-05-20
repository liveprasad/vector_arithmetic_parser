#ifndef __COMMON_H
#define __COMMON_H
#include <string>
#include <iostream>
class DataType {
  public:
    enum Type { BIT,INT,STRING,DOUBLE };
    static Type _from_string(const std::string& str)
    {
	if(str == "int") return INT;
	else if(str == "bit") return BIT;
	else if(str == "string") return STRING;
	else if (str == "double") return DOUBLE;
	return BIT;
    }
};
#endif
