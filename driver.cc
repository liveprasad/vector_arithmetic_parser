//#include <dlfcn.h>
#include "parser.hpp"
#include "static_loader.hpp"
#include "plsql_loader.hpp"
int main(int argc,char** argv){
  //std::string s ="t4est";
  //char * s = "check";
  int t = sizeof(argv);
  printf("%d , %lu , %lu , whole , %s , %s  is the size of the argv\n",t,sizeof(*argv[0]),sizeof(*argv[1]),argv[0],argv[1]);
  //std::string file = "files/sample_table.txt";
  //StaticLoader* loader= new StaticLoader(file);
  FactoryConf *conf = new FactoryConf(); 
  ConnectionFactory::initialize(conf);
  PlsqlLoader * loader = new PlsqlLoader(std::string(argv[1]));
  Parser::initialize(loader);
  Parser* p=Parser::getInstance();
  p->evaluate(argv[1],argv[2],argv[3]);
  return 0;
}
