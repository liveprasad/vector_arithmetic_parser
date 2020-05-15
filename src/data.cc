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


template<class T> template <typename S >
DataHolder*  Data<T>::operator+(Data<S> &op2 ){
    
    if(data_type > op2->getType()){
        Data<T>* val = new Data<T>(data_type,NULL,NULL,new std::vector<T>(vectorMeasurements));
	switch(val->DataType){
	    case DataType::Type::INT:
	        std::transform(val->getMeasurements()->begin(),val->getMeasurements()->end(),op2.getMeasurements()->begin(),op2.getMeasurements()->end(),std::plus<int>());
	    case DataType::Type::DOUBLE:
		std::transform(val->getMeasurements()->begin(),val->getMeasurements()->end(),op2.getMeasurements()->begin(),op2.getMeasurements()->end(),std::plus<double>());
	    default:
		printf("Error");
	}
	return val;
    }

    return op2 + this;
} 

template<class T>
Data<T>:: Data(std::string uuid, std::string id,std::string defination,std::string data_type , std::vector<std::string> *v){
  this->uuid = uuid;
  this->data_type = DataType::_from_string(data_type);
  this->defination = defination;
  this->id = id;
  this->vectorMeasurementsString = v;
  vectorMeasurements = transformVector();
  
}
template<class T>
Data<T>::Data(DataType::Type data_type , std::string defination, std::string id,std::vector<T> *v){
  this->data_type = data_type;
  this->defination = defination;
  this->vectorMeasurements = v;
  this->code = NULL;  //no identification required for the intermediate expression calculation
  //genrate the uuid for this expression  
  uuid_t binuuid;
  uuid_generate_random(binuuid);
  uuid_unparse(binuuid, uuid);
  
}
template<class T>
Data<T>:: ~Data(){
  delete vectorMeasurements;
  delete vectorMeasurementsString;
}

template<class T>
std::vector<std::string>* Data<T>:: transformVectorToString(){
  if(this->vectorMeasurementsString == NULL){
    this->vectorMeasurementsString = new std::vector<std::string>;
    for(T s: *vectorMeasurements){
        vectorMeasurementsString->push_back(s.to_string());
    }
  }
  return vectorMeasurementsString;
}

template<class T>
 std::vector<T> * Data<T>::transformVector(){
    if(this->vectorMeasurements == NULL){	
	    std::vector<T> * vectorMeasurements = new std::vector<T>;
	    switch(data_type){
	       case DataType::Type::INT:
		 std::transform(vectorMeasurementsString->begin(), vectorMeasurementsString->end(), std::back_inserter(vectorMeasurements->begin()), [](std::string str) { return std::stoi(str); });
		 
	       case DataType::Type::BIT:
		 std::transform(vectorMeasurementsString->begin(), vectorMeasurementsString->end(), std::back_inserter(vectorMeasurements->begin()), [](std::string str) { return str != "0" ; });
		 
	       case DataType::Type::DOUBLE:
		 std::transform(vectorMeasurementsString->begin(), vectorMeasurementsString->end(), std::back_inserter(vectorMeasurements->begin()), [](std::string str) { return std::stod(str); });
		 
	       default:
		 printf("no macthing");
	    }
	    return vectorMeasurements;
    }
    return vectorMeasurements;
}
template<class T>
std::vector<T>* Data<T>::getMeasurements(){
    return vectorMeasurements;
}
