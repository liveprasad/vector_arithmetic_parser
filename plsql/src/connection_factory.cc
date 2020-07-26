#include "connection_factory.hpp"
ConnectionFactory * ConnectionFactory::INSTANCE = 0;

std::string FactoryConf::getHostaddr(){
  return hostaddr;
}
std::string FactoryConf::getDbname(){
  return dbname;
}
std::string FactoryConf::getUserName(){
  return username;
}
std::string FactoryConf::getPass(){
  return pass;
}
std::string FactoryConf::getPort(){
  return port;
}

ConnectionFactory::ConnectionFactory(){
   conf = new FactoryConf();
}

ConnectionFactory::ConnectionFactory(FactoryConf* conf){
  this->conf = conf;
}

ConnectionFactory* ConnectionFactory::getInstance(){
  return INSTANCE;
} 

ConnectionFactory* ConnectionFactory::initialize(FactoryConf *conf){
  if(INSTANCE == NULL){
    if(conf == NULL)
      INSTANCE = new ConnectionFactory();
    else
      INSTANCE = new ConnectionFactory(conf);
  }
  return INSTANCE;
}

pqxx::connection ConnectionFactory::getConnection(){
   std::string connStr = getConnString();
#ifdef DEB
   printf("connection string : %s ", connStr.c_str() );
   fflush(stdin);
#endif
   pqxx::connection connection(connStr);
   return connection;
}

std::string ConnectionFactory::getConnString(){
   if(connectionString.empty())
       connectionString = (!conf->getDbname().empty() ? ("dbname=" + conf->getDbname() + " "): "") +
       (!conf->getHostaddr().empty() ? ("hostaddr="+ conf->getHostaddr()+" "):"")+
       (!conf->getUserName().empty() ? ("user="+ conf->getUserName()+" "):"")+
       (!conf->getPass().empty() ? ("password=" + conf->getPass()+" "):"") +
       (!conf->getPort().empty() ? ("port=" + conf->getPort()):"");
   return connectionString;
}
