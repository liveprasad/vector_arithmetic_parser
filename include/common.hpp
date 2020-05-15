#ifndef __COMMON_H
#define __COMMON_H
#include <string>

class DataType {
  public:
    enum Type { INT,BIT,STRING,DOUBLE };
    static Type _from_string(const std::string& str)
    {
	if(str == "INT") return INT;
	else if(str == "BIT") return BIT;
	else if(str == "STRING") return STRING;
	else if (str == "DOUBLE") return DOUBLE;
	return BIT;
    }
};
#endif
