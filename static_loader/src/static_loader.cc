#include "static_loader.hpp"
static const uint8_t DEFINED_SIZE = 5;
StaticLoader::StaticLoader(std::string path){
  FILE * pFile;
  long lSize;
  char * buffer;
  size_t result;
 
  printf("\nfile reading stated\n");
  pFile = fopen ( path.c_str() , "r" );
  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);
  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // copy the file into the buffer:
  
  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
  printf("file size is %lu \n",lSize);

  /* whole file is now loaded in the memory buffer. */
  
  inMemoryDatabase = new std::map<std::string,std::vector<std::string>*>;

  printf("%s\n",buffer);
  char * pch;
  std::vector<std::string> *v = new std::vector<std::string>; 
  pch = strtok (buffer," \n");
  int i =0;
  while(pch != NULL) {
      std::string s= std::string(strdup(pch));
      v->push_back(s);
      if(v->size() == DEFINED_SIZE){
	//inMemoryDatabase->
	inMemoryDatabase->insert(std::make_pair(v->at(1), v));
	v =  new std::vector<std::string>;
      }
      pch = strtok (NULL," \n");
  }
  printf("file read is successful : %lu \n",inMemoryDatabase->size());
  fflush(stdin);

  fclose (pFile);
  free (buffer);
}

DataHolder* StaticLoader::getData(std::string code) {
  #ifdef  DEB
     if(inMemoryDatabase->find(code)==inMemoryDatabase->end()){
	//need to return the error code
	
        printf("not finding the key \"%s\" in DB\n", code.c_str());
        return NULL;
     }
  #endif

  std::vector<std::string> *v =inMemoryDatabase->at(code);
  fflush(stdin); 
  std::stringstream iss(v->at(4));
  std::string token;
  std::vector<std::string> *measurements =new std::vector<std::string>;
  while(getline(iss,token,',')){
    measurements->push_back(token);
  }
  DataHolder * d;
  DataType::Type data_type = DataType::_from_string(v->at(3));
  fflush(stdin);
  return transformVector(v,data_type,measurements);
}
void StaticLoader::insertData(DataHolder* data) {
   //not need to implement this;
}

DataHolder* StaticLoader:: transformVector(std::vector<std::string> *v,DataType::Type data_type,std::vector<std::string> * vectorMeasurementsString){
  //std::vector<T> * measurements = new std::vector<T>;
  #ifdef DEB
    std::cout<<"started the tranforamtion : " << vectorMeasurementsString->size()<< std::endl; 
  #endif
  switch(data_type){
    case DataType::Type::INT:
      {
	std::vector<int>* measurements =new std::vector<int>;
        std::transform(vectorMeasurementsString->begin(), vectorMeasurementsString->end(), std::back_inserter(*measurements), [](std::string str) { return std::stoi(str); });
        delete vectorMeasurementsString;
        /*#ifdef DEB
	  std::for_each(measurements->begin(), measurements->end(), [](int val){ std::cout<<val<<" ";});
        #endif*/
	return new Data<int>(v->at(0),v->at(1),v->at(2) ,data_type,measurements);
      }
    case DataType::Type::DOUBLE:
      {
	std::vector<double>* measurementDouble =new std::vector<double>;
        std::transform(vectorMeasurementsString->begin(), vectorMeasurementsString->end(), std::back_inserter(*measurementDouble), [](std::string str) {  
	    return std::stod(str); 
	 });
        delete vectorMeasurementsString;
        /*#ifdef DEB
	  std::for_each(measurementDouble->begin(), measurementDouble->end(), [](double val){ std::cout<<val<<" ";});
        #endif*/
        return new Data<double>(v->at(0),v->at(1),v->at(2) ,data_type,measurementDouble);
      }
    case DataType::Type::BIT:
      {
	std::vector<bool>* measurementBool =new std::vector<bool>;
        std::transform(vectorMeasurementsString->begin(), vectorMeasurementsString->end(), std::back_inserter(*measurementBool), [](std::string str) {  return str != "0" ;});
        delete vectorMeasurementsString;
        /*#ifdef DEB
	  std::for_each(measurementBool->begin(), measurementBool->end(), [](bool val){ std::cout<<val<<" ";});
        #endif*/
        return new Data<bool>(v->at(0),v->at(1),v->at(2) ,data_type,measurementBool);
      } 
    case DataType::Type::STRING:
      //vectorMeasurements =(std::vector<T>*)  vectorMeasurementsString;
     {
        #ifdef DEB
	  std::for_each(vectorMeasurementsString->begin(), vectorMeasurementsString->end(), [](std::string val){ std::cout<<val<<" ";});
        #endif
        return new DataString(v->at(0),v->at(1),v->at(2),vectorMeasurementsString);
     }
    default:
      printf("no macthing");
  }
  #ifdef DEB
    std::cout<<"Error with  the tranforamtion";
  #endif
  return NULL;
}

