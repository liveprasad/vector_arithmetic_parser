#ifndef __PARSER_H
#define __PARSER_H
#include "common.hpp"
#include "data.hpp"
#include <stdio.h>
#include <string>
#include "data_cache.hpp"
#include "data_loader.hpp"
extern int yylex();
//extern yy_buffer_state;
typedef struct  yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE);
extern void  yyerror(const char *);
extern int yyparse();
int flag = 0;
//extern void yyparse();
class Parser{
    private:
      //std::map<std::string,DataHolder*> *sTable;
      int errorCode;
      DataLoader *loader;
      DataCache *cache;
    public:
      Parser();
      Parser(DataLoader* loader);
      ~Parser();
      int evaluate(const char * str);
      void add(std::string id1,std::string id2);
      void sub(std::string id1,std::string id2);
      void bitwiseOr(std::string id1,std::string id2);
      void biwiseAnd(std::string id1,std::string id2);
      DataCache* getCache();
};
#endif
