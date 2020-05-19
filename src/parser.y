
%{ 
   /* Definition section */
   #include "parser.hpp"
   Parser* Parser::INSTANCE=0;
    
%} 
 
%union {
  char* str;
  //int int_val;
}
%start exp

%token ID 
 
%left '+' '-'
  
%left '*' '/' '%'
  
%left '(' ')'

%type<str> E ID exp
  
/* Rule Section */
%% 
  
exp: E{ 
  
         printf("\nResult=%s\n",$$ ); 
  
         return 0; 
  
        }; 
 E:E'+'E{
             //$$ = std::string($1)+ std::string($2);
 	    std::string s = Parser::getInstance()->add(std::string($1) , std::string($3));
	    $$ = &s[0];
	} 
  
 |E'-'E {
 	    std::string s = Parser::getInstance()->sub(std::string($1) , std::string($3));
	    $$ = &s[0];
	} 
  
 |E'*'E {
 	    std::string s = Parser::getInstance()->mul(std::string($1) , std::string($3));
	    $$ = &s[0];
       } 
  
 |E'/'E {$$=$1;} 
  
 |E'%'E {$$=$1;} 
  
 |'('E')' {$$=$2;} 
  
 | ID {
        $$=$1;
        #ifdef DEB
           printf("%s  is the id \n", $1);
        #endif
 } 
  
 ; 
  
%% 
  
//driver code 
Parser* Parser:: initialize( DataLoader *loader){

  if(Parser::getInstance() == nullptr){
    Parser::INSTANCE = new Parser(loader);
  }
  return Parser::INSTANCE;
}

Parser* Parser::getInstance(){
  return Parser::INSTANCE;
}

Parser::Parser( DataLoader * loader){
  this->loader = loader;
  cache = new DataCache(loader);
}

Parser::~Parser(){
      delete cache;
}

int Parser::evaluate(const char* expression) 
{ 
   //char *s=(char *) malloc(5000* sizeof(char));
   #ifdef DEB
     printf("provided expression is %s****\n",expression );
   #endif
   YY_BUFFER_STATE buffer = yy_scan_string(expression);
   int r = yyparse();
   yy_delete_buffer(buffer);
   if(flag==0) 
     printf("\nEntered arithmetic expression is Valid\n\n"); 
   return 0;
} 

void yyerror(const char* err) 
{ 
   printf("\nEntered arithmetic expression is Invalid\n\n"); 
   flag=1; 
}

std::string Parser::add(std::string id1,std::string id2){
   DataHolder *result= *(cache->getData(id1)) + cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}

std::string Parser::sub(std::string id1, std::string id2){
   DataHolder *result= *(cache->getData(id1))-cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}

std::string Parser::mul(std::string id1,std::string id2){ 
   DataHolder *result= *(cache->getData(id1))*cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}
