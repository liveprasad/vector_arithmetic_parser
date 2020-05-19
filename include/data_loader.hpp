#ifndef __DATA_LOADER_H
#define __DATA_LOADER_H
#include "data.hpp"
#include <string>

class DataLoader{
  private:
    
  public:
    //DataLoader();
    //~DataLoader();
    virtual DataHolder* getData(std::string code) = 0;
    virtual void insertData(DataHolder* data) = 0;
    
};
#endif
