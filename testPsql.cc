#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>
int main()
{
    try
    {
        pqxx::connection C("dbname = postgres user = postgres hostaddr = 127.0.0.1 port = 5432" );
        std::cout << "Connected to " << C.dbname() << std::endl;
        pqxx::work W{C};

        pqxx::result R{W.exec("SELECT *  FROM vector_arithmatic")};

        std::cout << "Found " << R.size() << "rows:\n";
        for (pqxx::row row: R){
          //std::vector<std::string> v = (std::vector<std::string>) row[4];  
	  std::vector<std::string> v( row[4].as_array());
		std::cout << row[4].c_str() << '\n';
	}

        //std::cout << "Doubling all employees' salaries...\n";
        //W.exec0("UPDATE employee SET salary = salary*2");

        //std::cout << "Making changes definite: ";
        //W.commit();
        std::cout << "OK.\n";
    }
    catch (std::exception const &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
