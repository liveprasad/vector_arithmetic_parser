#include "data_cache.hpp"
#include <iostream>
DataCache::DataCache( DataLoader *loader){
	this->cache = new std::map<std::string,DataHolder*>;
	this->loader = loader;
}
DataCache::~DataCache(){
	delete cache;
}
DataHolder *DataCache::getData(std::string id){
        
	if(cache->find(id) == cache->end()){
		cache->insert(std::make_pair(id,this->loadFromLoader(id)));
	}
        #ifdef DEB
        std::cout<<cache->size()<<"\t"<< id <<"\t " << cache->at(id)->getId();
        #endif
	return this->cache->at(id);

}
DataHolder* DataCache::loadFromLoader(std::string id){
	return loader->getData(id);
}
void DataCache::insertData(DataHolder* data){
	cache->insert( make_pair(data->getId(), data));
}


