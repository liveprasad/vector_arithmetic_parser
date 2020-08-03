#ifndef __DATA_H
#define __DATA_H
#include <functional>
#include "common.hpp"
#include <uuid/uuid.h>
#include <string>
#include <vector>
#include <iterator>
#include <stddef.h>
#include <cmath>
#include <sstream>
class DataHolder{
  protected:
    std::string uuid;
    std::string defination;
    std::string id;
    DataType::Type data_type;
    std::vector<std::string> * vectorMeasurementsString = NULL;
  public:   
    DataHolder();
    virtual ~DataHolder()= 0;
    virtual std::vector<std::string>* transformVectorToString() = 0;
    std::string getUuid();
    std::string getDefination();
    std::string getId();
    DataType::Type getType();
    void setId(std::string id);
    void setDefination(std::string);
    virtual DataHolder* operator+(DataHolder *  ) = 0;
    virtual DataHolder* operator*(DataHolder *  ) = 0;
    virtual DataHolder* operator-(DataHolder *  ) = 0;
    virtual DataHolder* operator/(DataHolder *  ) = 0;
    virtual DataHolder* operator%(DataHolder *  ) = 0;
    //copy contstructor DataHolder(const DataHolder& other);
    virtual DataHolder* operator|(DataHolder *  ) = 0;
    virtual DataHolder* operator&(DataHolder *  ) = 0;
    virtual DataHolder* operator!( ) = 0;
    virtual DataHolder* operator-( ) = 0;//conflicting with binary - operations and hence not enabled to be invoked directly by using dataholder reference
    virtual DataHolder* operator==(std::string s) = 0;
};

template<class T>
class Data:public DataHolder{
  private:
    std::vector<T>* vectorMeasurements;
    //std::vector<std::string> *vectorMeasurementsString;
  public:
    //Data();
    Data(std::string uuid, std::string id,std::string defination,DataType::Type  data_type , std::vector<T> *v);
    Data(DataType::Type data_type , std::string defination, std::string id,std::vector<T> *v);
    ~Data();
    std::vector<T>* getMeasurements();
    //all operations which are invoked directly by using the reference to dataholders 
    //arthmatic operators
    DataHolder* operator+(DataHolder *);
    DataHolder* operator-(DataHolder *);//implemented using binary + and unary - operator
    DataHolder* operator*(DataHolder *);
    DataHolder* operator/(DataHolder *);
    DataHolder* operator%(DataHolder *);
    //logical operators
    DataHolder* operator|(DataHolder *  ) ;
    DataHolder* operator&(DataHolder *  ) ;

    //actual implementations of operators for which second argument is casted in S type Data
    //all binary operators
    //arthmatic opetators
    template<typename S>
    DataHolder* operator+(Data<S>* );
    template<typename S>
    DataHolder* operator*(Data<S>* );
    template<typename S>
    DataHolder* operator/(Data<S>* );
    template<typename S>
    DataHolder* operator%(Data<S>* );
    
    //logical operators
    template<typename S>
    DataHolder* operator|(Data<S>* );
    template<typename S>
    DataHolder* operator&(Data<S>* );
    
    //comparision operators
    DataHolder* operator==(std::string s);
    //unary operators
    //arithmatic operators
    Data<T>* operator-( );
    Data<T>* reciprocal( );
    //unary opatator 
    Data<T>* operator!();
    //string tranformations 
    std::vector<std::string>* transformVectorToString();
    //copy constructor Data(const Data<T>& other);
};

class DataString : public DataHolder{
  private:
    std::vector<std::string>* vectorMeasurements;
  public:
    DataString(std::string uuid,std::string id,std::string defination,std::vector<std::string>* vectorMeasurements);
    DataHolder* operator+(DataHolder *  ) {return NULL;}
    DataHolder* operator*(DataHolder *  ) {return NULL;}
    DataHolder* operator-(DataHolder *  ) {return NULL;}
    DataHolder* operator/(DataHolder *  ) {return NULL;}
    DataHolder* operator%(DataHolder *  ) {return NULL;}
    //copy contstructor DataHolder(const DataHolder& other);
    
    //comparision operators
    DataHolder* operator==(std::string match);
    //logical operators
    DataHolder* operator|(DataHolder *  ) {return NULL;}
    DataHolder* operator&(DataHolder *  ) {return NULL;}
    DataHolder* operator!( ) {return NULL;}
    DataHolder* operator-( ) {return NULL;} //conflicting with binary - operations and hence not enabled to be invoked directly by using dataholder reference
    std::vector<std::string>* transformVectorToString(){
	return vectorMeasurements;
    };
};

#endif
