//#include <dlfcn.h>
#include "parser.hpp"
#include "static_loader.hpp"
extern "C" int evaluate(const char * s );
int main(int c,char** argv){
  //std::string s ="t4est";
  //char * s = "check";
  int t = sizeof(argv);
  printf("%d , %lu , %lu , whole , %s , %s  is the size of the argv\n",t,sizeof(*argv[0]),sizeof(*argv[1]),argv[0],argv[1]);
  std::string file = "files/sample_table.txt";
  StaticLoader*  loader= new StaticLoader(file);
  
  Parser::initialize(loader);  
  Parser* p=Parser::getInstance();
  p->evaluate(argv[1]);
  return 0;
}
