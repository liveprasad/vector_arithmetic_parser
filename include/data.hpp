#ifndef __DATA_H
#define __DATA_H

#include "common.hpp"
#include <uuid/uuid.h>
#include <string>
#include <vector>

class DataHolder{
  protected:
    std::string uuid;
    std::string defination;
    std::string id;
    DataType::Type data_type;
  public:   
    virtual std::vector<std::string>* transformVectorToString() = 0;
    std::string getUuid();
    std::string getDefination();
    std::string getId();
    DataType::Type getType();
    virtual DataHolder* operator+(DataHolder & ) = 0;
    //copy contstructor DataHolder(const DataHolder& other);
};

template<class T>
class Data:public DataHolder{
  private:
    std::vector<T>* vectorMeasurements;
    std::vector<std::string> *vectorMeasurementsString;
  public:
    Data(std::string uuid, std::string id,std::string defination,std::string data_type , std::vector<std::string> *v);
    Data(DataType::Type data_type , std::string defination, std::string id,std::vector<T> *v);
    ~Data();
    std::vector<T>* transformVector();
    virtual std::vector<std::string>* transformVectorToString () override;
    std::vector<T>* getMeasurements();
    template<typename S>
    DataHolder* operator+(Data<S>& );
    //copy constructor Data(const Data<T>& other);
    
};

#endif
