#ifndef __DATA_H
#define __DATA_H
#include <functional>
#include "common.hpp"
#include <uuid/uuid.h>
#include <string>
#include <vector>
#include <iterator>
#include <stddef.h>
class DataHolder{
  protected:
    std::string uuid;
    std::string defination;
    std::string id;
    DataType::Type data_type;
  public:   
    DataHolder();
    virtual ~DataHolder()= 0;
    virtual std::vector<std::string>* transformVectorToString() = 0;
    std::string getUuid();
    std::string getDefination();
    std::string getId();
    DataType::Type getType();
    void setId(std::string id);
    virtual DataHolder* operator+(DataHolder *  ) = 0;
    virtual DataHolder* operator*(DataHolder *  ) = 0;
    virtual DataHolder* operator-(DataHolder *  ) = 0;
    virtual DataHolder* operator/(DataHolder *  ) = 0;
    //copy contstructor DataHolder(const DataHolder& other);
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
    DataHolder* operator+(DataHolder *);
    DataHolder* operator-(DataHolder *);
    DataHolder* operator*(DataHolder *);
    DataHolder* operator/(DataHolder *);
    template<typename S>
    DataHolder* operator+(Data<S>* );
    /*template<typename S>
    DataHolder* operator-(Data<S>* );*/
    template<typename S>
    DataHolder* operator*(Data<S>* );
    template<typename S>
    DataHolder* operator/(Data<S>* );
    Data<T>* operator-( );
    Data<T>* reciprocal( );
    std::vector<std::string>* transformVectorToString();
    //copy constructor Data(const Data<T>& other);
};
#endif
