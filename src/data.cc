#include "data.hpp"


/*template<class T, typename R>
  DataHolder* operator+(const DataHolder* lhs, const DataHolder*  rhs )
  {
  if(rhs->getType() > lhs->getType()) {

//result = new Data<R>(rhs->getType(),NULL,NULL,new std::vector<R>(rhs->getMeasurements()));
}
else
return rhs + lhs;
}*/

DataHolder::DataHolder(){
}

DataHolder::~DataHolder(){
}

std::string DataHolder:: getUuid(){
  return uuid;
}
std::string DataHolder::getDefination(){
  return defination;
}
std::string DataHolder:: getId(){
  return id;
}
DataType::Type DataHolder:: getType(){
  return data_type;
}

//copy constructor
/*template<class T>
  Data<T>* Data<T>::Data(Data<T> & other):DataHolder(other){
  this->vectorMeasurements = new vector<T>((other->getMeasurements());
  } */


template<class T>
DataHolder * Data<T>::operator+(DataHolder * op2){

  #ifdef DEB
     std::cout<<"+ onperator overloaded for DataHolder :" << getId() << "+" << op2->getId()<<std::endl; 
  #endif
  switch(op2->getType()){
    case DataType::Type::INT:
      return *((Data<int>* )op2) + this;
    case DataType::Type::DOUBLE:
      return *((Data<double>*)op2) + this;
    case DataType::Type::BIT:
      return NULL;
    case DataType::Type::STRING:
      return NULL;
  }
  //return this + op2;
}

template<class T> template <typename S >
DataHolder*  Data<T>::operator+(Data<S> * op2 ){
  #ifdef DEB
     std::cout<<"+ onperator overloaded for Data :" << getId() << "+" << op2->getId()<< "for vector size "<< vectorMeasurements->size()<<std::endl; 
  #endif

  if(data_type >= op2->getType()){
    std::vector<T> *result = new std::vector<T>;
    result->reserve(vectorMeasurements->size());
    std::cout << "vector size" << result->size() <<std::endl;
    Data<T>* val = new Data<T>(data_type,id+"+"+op2->getId(),id,result);
    switch(val->getType()){
      case DataType::Type::INT:
      case DataType::Type::DOUBLE:
      case DataType::Type::BIT:
	//result->reserve(getMeasurements()->size());
	if(op2->getType() != DataType::Type::STRING){
	  std::cout<<"starting addition of 2 vectors" << std::endl;
	  std::transform(vectorMeasurements->begin(),vectorMeasurements->end(),op2->getMeasurements()->begin(),back_inserter(*result),std::plus<T>());
          #ifdef DEB
	     std::cout<< "vector calculated for opration"<<val->getDefination()<< std::endl;
	     std::for_each(val->getMeasurements()->begin(),val->getMeasurements()->end(),[](T val){ std::cout<<val<<" ";} );
          #endif
	}
      case DataType::Type::STRING:

	//std::transform(val->getMeasurements()->begin(),val->getMeasurements()->end(),op2->getMeasurements()->begin(),op2->getMeasurements()->end(),std::plus<double>());
	//default:
	printf("Error");

    }
    return val;
  }
  return *op2 + this;
} 

template<class T>
DataHolder * Data<T>::operator-(DataHolder * op2){
  switch(op2->getType()){
    case DataType::Type::INT:
      return *((Data<int>* )op2) - this;
    case DataType::Type::DOUBLE:
      return *((Data<double>*)op2) - this;
    case DataType::Type::BIT:
      return NULL;
    case DataType::Type::STRING:
      return NULL;
  }
  //return this + op2;
}

template<class T> template <typename S >
DataHolder*  Data<T>::operator-(Data<S> * op2 ){
  if(data_type > op2->getType()){
    std::vector<T> *result = new std::vector<T>;
    Data<T>* val = new Data<T>(data_type,NULL,NULL,result);
    switch(val->getType()){
      case DataType::Type::INT:
      case DataType::Type::DOUBLE:
      case DataType::Type::BIT:
	//result->reserve(getMeasurements()->size());
	if(op2->getType() != DataType::Type::STRING){
	  std::transform(val->getMeasurements()->begin(),val->getMeasurements()->end(),op2->getMeasurements()->begin(),back_inserter(*result),std::minus<T>());
	}
      case DataType::Type::STRING:

	//std::transform(val->getMeasurements()->begin(),val->getMeasurements()->end(),op2->getMeasurements()->begin(),op2->getMeasurements()->end(),std::plus<double>());
	//default:
	printf("Error");

    }
    return val;
  }
  return *op2 - this;
} 

template<class T>
DataHolder * Data<T>::operator*(DataHolder * op2){
  switch(op2->getType()){
    case DataType::Type::INT:
      return *((Data<int>* )op2) * this;
    case DataType::Type::DOUBLE:
      return *((Data<double>*)op2) * this;
    case DataType::Type::BIT:
      return NULL;
    case DataType::Type::STRING:
      return NULL;
  }
  //return this + op2;
}

template<class T> template <typename S >
DataHolder*  Data<T>::operator*(Data<S> * op2 ){
  if(data_type > op2->getType()){
    std::vector<T> *result = new std::vector<T>;
    Data<T>* val = new Data<T>(data_type,defination,id,result);
    switch(val->getType()){
      case DataType::Type::INT:
      case DataType::Type::DOUBLE:
      case DataType::Type::BIT:
	//result->reserve(getMeasurements()->size());
	if(op2->getType() != DataType::Type::STRING){
	  std::transform(val->getMeasurements()->begin(),val->getMeasurements()->end(),op2->getMeasurements()->begin(),back_inserter(*result),std::multiplies<T>());
	}
      case DataType::Type::STRING:

	//std::transform(val->getMeasurements()->begin(),val->getMeasurements()->end(),op2->getMeasurements()->begin(),op2->getMeasurements()->end(),std::plus<double>());
	//default:
	printf("Error");

    }
    return val;
  }
  return *op2 * this;
} 
/*template<class T>
Data<T>::Data(){
}*/

template<class T>
Data<T>:: Data(std::string uuid, std::string id,std::string defination,DataType::Type data_type , std::vector<T> *v){
  this->uuid = uuid;
  this->data_type = data_type;
  this->defination = defination;
  this->id = id;
  //this->vectorMeasurementsString = v;
  this->vectorMeasurements = v; 
  #ifdef DEB
    printf("allocation of data with vector size %lu\n", v->size());
    fflush(stdin);
  #endif
}

template<class T>
Data<T>::Data(DataType::Type data_type , std::string defination, std::string id,std::vector<T> *v){
  #ifdef DEB
     printf("start allocating the data for intermediate operations:\n" );
     fflush(stdin);
  #endif 
 
  this->data_type = data_type;
  //this->defination 
  this->vectorMeasurements = v;
  //no identification required for the intermediate expression calculation
  //genrate the uuid for this expression  
  uuid_t binuuid;
  uuid_generate_random(binuuid);
  char* cuuid = (char *) malloc(sizeof(char)* 37);
  uuid_unparse(binuuid, cuuid);
  std::cout<< "generated new uuid" << cuuid << std::endl; 
  uuid = std::string(cuuid);
  std::cout<<uuid<<std::endl; 
  this->id = uuid; //use uuid as the code for the intermediate calculations;  
  #ifdef DEB
    printf("allocation of data with vector size %lu\n", v->size());
    fflush(stdin);
  #endif
}
template<class T>
Data<T>:: ~Data(){
  delete vectorMeasurements;
  //delete vectorMeasurementsString;
}

/*template<class T>
std::vector<std::string>* Data<T>:: transformVectorToString(){
  if(this->vectorMeasurementsString == NULL){
    this->vectorMeasurementsString = new std::vector<std::string>;
    for(T s: *vectorMeasurements){
        vectorMeasurementsString->push_back(std::to_string(s));
    }
  }
  return vectorMeasurementsString;
}*/

template<class T>
std::vector<T>* Data<T>::getMeasurements(){
    return vectorMeasurements;
}

template class Data<double>;
template class Data<int>;
//template class Data<std::string>;
template class Data<bool>;
