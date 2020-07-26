#include "plsql_loader.hpp"

PlsqlLoader::PlsqlLoader(std::string table_name){
   this->table_name = table_name; 
}
PlsqlLoader::~PlsqlLoader(){

}

DataHolder* PlsqlLoader::getData(std::string code){
    
    try
    {
        pqxx::connection C= ConnectionFactory::getInstance()->getConnection();
	//  =("dbname = postgres user = postgres hostaddr = 127.0.0.1 port = 5432" );
#ifdef DEB
	std::cout << "Connected to " << C.dbname() << std::endl;
#endif
	pqxx::work work{C};

        pqxx::result R{work.exec("SELECT *  FROM "+table_name+" where code ='" + code+"'")};
#ifdef DEB
        std::cout << "Found " << R.size() << "rows:\n";
#endif
	pqxx::row row = R[0];
	std::vector<std::string> * v = new std::vector<std::string>();
	for (int i = 0; i < 4 ; i++){
          //std::vector<std::string> v = (std::vector<std::string>) row[4];  
	  v->push_back(std::string(row[i].c_str()));
	}
	pqxx::array_parser parser = R[0][4].as_array();
	std::vector<std::string> * vectorMeasurementsString = new std::vector<std::string>();
	//vectorMeasurementsString->reserve(parser.size());
	auto obj = parser.get_next();
	while (obj.first != pqxx::array_parser::juncture::done)
	{
	  if (obj.first == pqxx::array_parser::juncture::string_value)
	  {
	    vectorMeasurementsString->push_back(obj.second.c_str());
	  }
	  obj = parser.get_next();
	}

        //std::cout << "Doubling all employees' salaries...\n";
        //W.exec0("UPDATE employee SET salary = salary*2");

        //std::cout << "Making changes definite: ";
        //W.commit();

	return transformVector(v,DataType::_from_string(v->at(3)),vectorMeasurementsString);

    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << '\n';
        return NULL;
    }
}

void PlsqlLoader::insertData(DataHolder* data){
        
   pqxx::connection connection= ConnectionFactory::getInstance()->getConnection();
   pqxx:: work w{ connection};
   std::string sql = tranformToString(data);
#ifdef DEB
   std::cout<< sql << std::endl;
#endif
   w.exec0(sql);
   w.commit();
}

std::string PlsqlLoader::tranformToString(DataHolder *holder){
   std::vector<std::string> * vec= holder->transformVectorToString();
   std::ostringstream vts; 
  
   if (!vec->empty()) 
   { 
     // Convert all but the last element to avoid a trailing "," 
     std::copy(vec->begin(), vec->end()-1, 
	 std::ostream_iterator<std::string>(vts, ", ")); 

     // Now add the last element with no delimiter 
     vts << vec->back(); 
   }
   std::string str = vts.str();
   std::string sql= "INSERT INTO " +table_name+" values('"+holder->getUuid()+"'"+",'"+holder->getId()+"'"+",'"+holder->getDefination()+"'"+",'"+std::to_string(holder->getType())+"'"+",'{"+str+"}'"+")";
   return sql;
}

DataHolder* PlsqlLoader:: transformVector(std::vector<std::string> *v,DataType::Type data_type,std::vector<std::string> * vectorMeasurementsString){
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
