#include <iostream>
#include <pqxx/pqxx> 
#include <string>

class FactoryConf{
  private: 
    std::string hostaddr;
    std::string dbname;
    std::string username;
    std::string pass;
    std::string port;
  public:
    ~FactoryConf();
    FactoryConf(std::string host="127.0.0.1",std::string dbname="postgres",std::string username="postgres",std::string pass="",std::string port="5432"):
    hostaddr(host),
    dbname(dbname),
    username(username),
    pass(pass),
    port(port)
    {}
    std::string getHostaddr();
    std::string getDbname();
    std::string getUserName();
    std::string getPass();
    std::string getPort();
};
class ConnectionFactory{
  private:
    FactoryConf *conf;
    static ConnectionFactory* INSTANCE;
    std::string connectionString ;
    ConnectionFactory();
    ConnectionFactory(FactoryConf * conf);
  public:
    ~ConnectionFactory();
    static ConnectionFactory* getInstance();
    static ConnectionFactory* initialize(FactoryConf *conf);
    pqxx::connection getConnection();
    void closeConnection();
    std::string getConnString();
    
};
