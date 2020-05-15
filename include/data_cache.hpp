#ifndef __DATA_CACHE_H
#define __DATA_CACHE_H
#include <string>
#include "data.hpp"
#include "data_loader.hpp"
#include <map>
class DataCache{
  private:
    DataLoader *loader;
    std::map<std::string,DataHolder*> *cache;
  public:
    DataCache(DataLoader *loader);
    ~DataCache();
    DataHolder *getData(std::string code);
    DataHolder *loadFromLoader(std::string code);
    void insertData(DataHolder *);
    
};
#endif
