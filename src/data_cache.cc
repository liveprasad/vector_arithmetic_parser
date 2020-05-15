#include "data_cache.hpp"

DataCache::DataCache(DataLoader *loader){
	this->cache = new std::map<std::string,DataHolder*>;
	this->loader = loader;


}
DataCache::~DataCache(){
	delete cache;
}
DataHolder *DataCache::getData(std::string id){
	if(cache->find(id) == cache->end()){
		cache->at(id) = this->loadFromLoader(id);
	}
	return this->cache->at(id);

}
DataHolder* DataCache::loadFromLoader(std::string id){
	return loader->getData(id);
}
void DataCache::insertData(DataHolder* data){
	cache->at(data->getId()) = data;
}


