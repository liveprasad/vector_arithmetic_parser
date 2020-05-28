#include <string>
#include <iostream>
#include "connection_factory.hpp"
#include "data_loader.hpp"
class PlsqlLoader: public DataLoader{
  private:
    std::string table_name;
  public:
    PlsqlLoader(std::string );
    ~PlsqlLoader();
    DataHolder* getData(std::string code);
    void insertData(DataHolder* data);
    DataHolder* transformVector(std::vector<std::string> *v,DataType::Type data_type,std::vector<std::string> * vectorMeasurementsString);
    std::string tranformToString(DataHolder *holder);
};
