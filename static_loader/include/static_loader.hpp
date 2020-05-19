#ifndef __STATIC_LOADER_H
#define __STATIC_LOADER_H
#include <string>
#include <stdio.h>
#include "data.hpp"
#include "data_loader.hpp"
#include <vector>
#include <string.h>
#include <iostream>
#include <map>
#include <sstream>
class StaticLoader: public DataLoader{
  private:
    std::map<std::string,std::vector<std::string>*> *inMemoryDatabase;
  public:
    StaticLoader(std::string);
    ~StaticLoader();
    DataHolder* getData(std::string code) override;
    void insertData(DataHolder* data) override;
    DataHolder* transformVector(std::vector<std::string> *v,DataType::Type data_type,std::vector<std::string> * vectorMeasurementsString);
};
#endif
