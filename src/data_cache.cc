#include "data_cache.hpp"
#include <iostream>
DataCache::DataCache( DataLoader *loader){
  this->cache = new std::map<std::string,DataHolder*>;
  this->loader = loader;
}
DataCache::~DataCache(){
  std::map<std::string, DataHolder*>::iterator it = cache->begin();
  while(it != cache->end()){
    DataHolder *val = it->second;
    if(val)
       delete (val);
    it++;
  }

  #ifdef DEB
    printf("gracefully deleted the cache");
    fflush(stdin);
  #endif
}
DataHolder *DataCache::getData(std::string id){

  if(cache->find(id) == cache->end()){
    cache->insert(std::make_pair(id,this->loadFromLoader(id)));
  }
  return this->cache->at(id);

}
DataHolder* DataCache::loadFromLoader(std::string id){
  return loader->getData(id);
}
void DataCache::insertData(DataHolder* data){
  cache->insert(std::make_pair(data->getId(), data));
}
