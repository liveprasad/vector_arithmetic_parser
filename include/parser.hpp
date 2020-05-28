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
extern YY_BUFFER_STATE yy_scan_string(const char *expression );
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
      Parser(DataLoader* );
      std::string expressionId;
      static Parser* INSTANCE ;
    public:
      Parser(Parser &other)= delete;
      ~Parser();
      static Parser *initialize(DataLoader *loader);
      static Parser *getInstance();
      int evaluate(const char* table_name ,const char * expression,const char * expressionId);
      std::string getExpressionId();
      std::string add(std::string id1,std::string id2);
      std::string sub(std::string id1,std::string id2);
      std::string div(std::string id1,std::string id2);
      std::string mul(std::string id1,std::string id2);
      std::string mod(std::string id1,std::string id2);
      std::string match(std::string id,std::string match);
      std::string uMinus(std::string id);
      std::string bitwiseOr(std::string id1,std::string id2);
      std::string bitwiseAnd(std::string id1,std::string id2);
      std::string bitwiseNot(std::string id);
      DataCache* getCache();
};

#endif
