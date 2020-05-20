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

void DataHolder::setId(std::string id){
  this->id = id;
}
//copy constructor
/*template<class T>
  Data<T>* Data<T>::Data(Data<T> & other):DataHolder(other){
  this->vectorMeasurements = new vector<T>((other->getMeasurements());
  } */


template<class T>
DataHolder * Data<T>::operator+(DataHolder * op2){

  switch(op2->getType()){
    case DataType::Type::INT:
      return *this + ((Data<int>* )op2);
    case DataType::Type::DOUBLE:
      return *this + ((Data<double>*)op2);
    case DataType::Type::BIT:
      return *this + ((Data<bool>*)op2);
    case DataType::Type::STRING:
      return NULL;
  }
  //return this + op2;
}

template<class T> template <typename S >
DataHolder*  Data<T>::operator+(Data<S> * op2 ){
#ifdef DEB
  std::cout<<"+ operator overloaded for Data :" << defination << "+" << op2->getDefination()<< "for vector size "<< vectorMeasurements->size()<<std::endl; 
#endif

  if(data_type >= op2->getType()){
    std::vector<T> *result = new std::vector<T>;
    result->reserve(vectorMeasurements->size());
    Data<T>* val = new Data<T>(data_type,defination+"+"+op2->getDefination(),id,result);
#ifdef DEB
	  std::cout<<"starting addition of 2 vectors" << std::endl;
#endif
	  std::transform(vectorMeasurements->begin(),vectorMeasurements->end(),op2->getMeasurements()->begin(),back_inserter(*result),std::plus<T>());
#ifdef DEB
	  std::cout<< "vector calculated for operation:"<<val->getDefination()<< std::endl;
	  std::for_each(val->getMeasurements()->begin(),val->getMeasurements()->end(),[](T val){ std::cout<<val<<" ";} );
	  std::cout<<std::endl;
#endif
	  return val;
  }
  return *op2 + this;
} 

template<class T>
DataHolder * Data<T>::operator-(DataHolder * op2){
  switch(op2->getType()){
    case DataType::Type::INT:
      return (*this + -*((Data<int>* )op2));
    case DataType::Type::DOUBLE:
      return (*this + -*((Data<double>*)op2) );
    case DataType::Type::BIT:
      return (*this + -*((Data<bool>*)op2) );
    case DataType::Type::STRING:
      return NULL;
  }
  //return this + op2;
}

template<class T> 
Data<T>* Data<T>::operator-(){

#ifdef DEB
  std::cout<<"operation of negation for " << this->defination<< std::endl;
#endif
  std::vector<T> *result = new std::vector<T>();
  //result->reserve(vectorMeasurements->size());
  std::transform(vectorMeasurements->begin(),vectorMeasurements->end(),back_inserter(*result),[](T val){ return -val;});
  Data<T>* val = new Data<T>(data_type,"-"+defination,id,result); 
#ifdef DEB
  std::cout<<"negated vector " << this->defination<< std::endl;
  for_each(result->begin(),result->end(), [](T val){std::cout<<val<<" ";});
  std::cout<<std::endl;
#endif
  return val;
}

/*template<class T> template <typename S >
  DataHolder*  Data<T>::operator-(Data<S> * op2 ){
#ifdef DEB
std::cout<<"+ operator overloaded for Data :" << getId() << "+" << op2->getId()<< "for vector size "<< vectorMeasurements->size()<<std::endl; 
#endif

if(data_type >= op2->getType()){
std::vector<T> *result = new std::vector<T>;
result->reserve(vectorMeasurements->size());
Data<T>* val = new Data<T>(data_type,id+"+"+op2->getId(),id,result);
switch(val->getType()){
case DataType::Type::INT:
case DataType::Type::DOUBLE:
case DataType::Type::BIT:
//result->reserve(getMeasurements()->size());
if(op2->getType() != DataType::Type::STRING){
#ifdef DEB
std::cout<<"starting addition of 2 vectors" << std::endl;
#endif
std::transform(vectorMeasurements->begin(),vectorMeasurements->end(),op2->getMeasurements()->begin(),back_inserter(*result),std::minus<T>());
#ifdef DEB
std::cout<< "vector calculated for operation:"<<val->getDefination()<< std::endl;
std::for_each(val->getMeasurements()->begin(),val->getMeasurements()->end(),[](T val){ std::cout<<val<<" ";} );
#endif
return -(*val);
}
case DataType::Type::STRING:

//std::transform(val->getMeasurements()->begin(),val->getMeasurements()->end(),op2->getMeasurements()->begin(),op2->getMeasurements()->end(),std::plus<double>());
//default:
printf("Error");

}
}
return -(*((Data<S>*)(op2 - this)));
} */

template<class T>
DataHolder * Data<T>::operator/(DataHolder * op2){
  switch(op2->getType()){
    case DataType::Type::INT:
      return *this / ((Data<int>*)op2);
    case DataType::Type::DOUBLE:
      return *this / ((Data<double>*)op2) ;
    case DataType::Type::BIT:
      return *this / ((Data<bool>*)op2) ;
    case DataType::Type::STRING:
      return NULL;
  }
}

template<class T>
Data<T>* Data<T>::reciprocal(){
#ifdef DEB
  std::cout<<"operation of reciprocal for " << this->defination<< std::endl;
#endif
  std::vector<T> *result = new std::vector<T>();
  result->reserve(vectorMeasurements->size());
  std::transform(vectorMeasurements->begin(),vectorMeasurements->end(),result->begin(),[](T val){ return ((T)1)/val;});
  Data<T>* val = new Data<T>(data_type,"1/"+defination,id,result); 
#ifdef DEB
  std::cout<<"reciprocated vector " << this->defination<< std::endl;
  for_each(result->begin(),result->end(), [](T val){std::cout<<val<<" ";});
  std::cout<<std::endl;
#endif
  return val;
}

template<class T> template <typename S >
DataHolder*  Data<T>::operator/(Data<S> * op2 ){
#ifdef DEB
  std::cout<<"+ operator overloaded for Data :" << defination<< "/" << op2->getDefination()<< "for vector size "<< vectorMeasurements->size()<<std::endl; 
#endif

  if(data_type >= op2->getType()){
    std::vector<T> *result = new std::vector<T>;
    result->reserve(vectorMeasurements->size());
    Data<T>* val = new Data<T>(data_type,defination+"/"+op2->getDefination(),id,result);
#ifdef DEB
	  std::cout<<"starting divides of 2 vectors" << std::endl;
#endif
	  std::transform(vectorMeasurements->begin(),vectorMeasurements->end(),op2->getMeasurements()->begin(),back_inserter(*result),std::divides<T>());
#ifdef DEB
	  std::cout<< "vector calculated for operation:"<<val->getDefination()<< std::endl;
	  std::for_each(val->getMeasurements()->begin(),val->getMeasurements()->end(),[](T val){ std::cout<<val<<" ";} );
	  std::cout<<std::endl;
#endif
	  return val;
  }
  else{
     
    std::vector<S> *result = new std::vector<S>;
    result->reserve(vectorMeasurements->size());
    Data<S>* val = new Data<S>(data_type,defination+"/"+op2->getDefination(),id,result);
#ifdef DEB
	  std::cout<<"starting divides of 2 vectors in reverse" << std::endl;
#endif
	  std::transform(vectorMeasurements->begin(),vectorMeasurements->end(),op2->getMeasurements()->begin(),back_inserter(*result),std::divides<S>());
#ifdef DEB
	  std::cout<< "vector calculated for operation:"<<val->getDefination()<< std::endl;
	  std::for_each(val->getMeasurements()->begin(),val->getMeasurements()->end(),[](S val){ std::cout<<val<<" ";} );
	  std::cout<<std::endl;
#endif
	  return val;
  }

}

template<class T>
DataHolder * Data<T>::operator*(DataHolder * op2){
  switch(op2->getType()){
    case DataType::Type::INT:
      return *this * ((Data<int>*)op2);
    case DataType::Type::DOUBLE:
      return *this * ((Data<double>*)op2) ;
    case DataType::Type::BIT:
      return *this * ((Data<bool>*)op2) ;
    case DataType::Type::STRING:
      return NULL;
  }
}

template<class T> template <typename S >
DataHolder*  Data<T>::operator*(Data<S> * op2 ){
#ifdef DEB
  std::cout<<"+ operator overloaded for Data :" << defination<< "*" << op2->getDefination()<< "for vector size "<< vectorMeasurements->size()<<std::endl; 
#endif

  if(data_type >= op2->getType()){
    std::vector<T> *result = new std::vector<T>;
    result->reserve(vectorMeasurements->size());
    Data<T>* val = new Data<T>(data_type,defination+"*"+op2->getDefination(),id,result);
#ifdef DEB
	  std::cout<<"starting multiplication of 2 vectors" << std::endl;
#endif
	  std::transform(vectorMeasurements->begin(),vectorMeasurements->end(),op2->getMeasurements()->begin(),back_inserter(*result),std::multiplies<T>());
#ifdef DEB
	  std::cout<< "vector calculated for operation:"<<val->getDefination()<< std::endl;
	  std::for_each(val->getMeasurements()->begin(),val->getMeasurements()->end(),[](T val){ std::cout<<val<<" ";} );
	  std::cout<<std::endl;
#endif
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
  this->defination = defination; 
  this->vectorMeasurements = v;
  //no identification required for the intermediate expression calculation
  //genrate the uuid for this expression  
  uuid_t binuuid;
  uuid_generate_random(binuuid);
  char* cuuid = (char *) malloc(sizeof(char)* 37);
  uuid_unparse(binuuid, cuuid);
  uuid = std::string(cuuid);
  this->id = uuid; //use uuid as the code for the intermediate calculations;  
  std::replace(this->id.begin(),this->id.end(),'-','a');
#ifdef DEB
  std::cout<< "generated new id:" << this->id << std::endl; 
  fflush(stdin);
#endif
}
template<class T>
Data<T>:: ~Data(){
#ifdef DEB
  printf("calling the destructors of the data \n");
  fflush(stdin);
#endif
  delete vectorMeasurements;
  //delete vectorMeasurementsString;
}

template<class T>
std::vector<std::string>* Data<T>:: transformVectorToString(){
  std::vector<std::string> * vectorMeasurementsString;
  if(vectorMeasurementsString == NULL|| vectorMeasurementsString->size() == 0){
    vectorMeasurementsString = new std::vector<std::string>;
    for(T s: *vectorMeasurements){
      vectorMeasurementsString->push_back(std::to_string(s));
    }
  }
  return vectorMeasurementsString;
}

template<class T>
std::vector<T>* Data<T>::getMeasurements(){
  return vectorMeasurements;
} 

template class Data<double>;
template class Data<int>;
//template class Data<std::string>;
template class Data<bool>;
