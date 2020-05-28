
%{ 
   /* Definition section */
   #include "parser.hpp"
   Parser * Parser::INSTANCE = 0;
%} 
 
%union {
  char* str;
  //int int_val;
}
%start exp

%token ID MATCH 
 
%left '+' '-'
  
%left '*' '/' '%'
  
%left '(' ')' 

%left '=' '!'

%type<str> E ID exp MATCH
  
/* Rule Section */
%% 
  
exp: E{ 
  
         std::string s =(Parser::getInstance())->getExpressionId();
         //printf("\nResult=%s for %s \n",$$, s.c_str()); 
	 DataHolder * d =Parser::getInstance()->getCache()->getData(std::string($$));
         d->setId(s);
	 Parser::getInstance()->getCache()->insertData(d);
	 //fflush(stdin);
	 return 0; 
  
        }; 
 E:E'+'E{
             //$$ = std::string($1)+ std::string($2);
 	    $$ = strdup(Parser::getInstance()->add(std::string($1) , std::string($3)).c_str()) ;
	    //$$ = &s[0];
	} 
  
 |E'-'E {
 	    $$ = strdup(Parser::getInstance()->sub(std::string($1) , std::string($3)).c_str());
	    //$$ = &s[0];
	} 
  
 |E'*'E {
 	    $$ = strdup(Parser::getInstance()->mul(std::string($1) , std::string($3)).c_str());
        } 
  
 |E'/'E {
 	    $$ = strdup(Parser::getInstance()->div(std::string($1) , std::string($3)).c_str());
        }
 |'-'E  {
	    $$ = strdup(Parser::getInstance()->uMinus(std::string($2)).c_str());
        }
 |E'|'E {
  	    $$ = strdup(Parser::getInstance()->bitwiseOr(std::string($1),std::string($3)).c_str());
        }  
 |E'&'E {
            $$ = strdup(Parser::getInstance()->bitwiseAnd(std::string($1),std::string($3)).c_str());
	}
 |'!'E  {
 	    $$ = strdup(Parser::getInstance()->bitwiseNot(std::string($2)).c_str());
 
        }
 |E'%'E {
            $$ = strdup(Parser::getInstance()->mod(std::string($1),std::string($3)).c_str());
        } 
|E'='MATCH {
            $$ = strdup(Parser::getInstance()->match(std::string($1),std::string($3)).c_str());  
        }
  
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

int Parser::evaluate(const char* table_name, const char* expression,const char* expressionId) 
{ 
   //char *s=(char *) malloc(5000* sizeof(char));
 
   this->expressionId = std::string(expressionId);
   #ifdef DEB
     printf("provided expression is %s****\n",expression );
   #endif
    
   YY_BUFFER_STATE buffer = yy_scan_string(expression);
   int r = yyparse();
   yy_delete_buffer(buffer);
   DataHolder * d =cache->getData(expressionId);
   d->setDefination(std::string(expression));
   #ifdef DEB
      std::vector<std::string> *v =d->transformVectorToString();
      std::cout<<"\n final vector is "<<v->size() << std::endl;
      for_each(v->begin(),v->end(),[](std::string str){std::cout<<str <<" ";});
   #endif
   fflush(stdin);
   loader->insertData(d);
   return 0;
} 
void yyerror(const char* err) 
{ 
   printf("\nEntered arithmetic expression is Invalid\n\n"); 
   flag=1; 
}

//invoking binary operators
std::string Parser::add(std::string id1,std::string id2){
   std::cout<<"******" << id1 << '+'<< id2<<"******" <<std::endl; 
   DataHolder *result= *(cache->getData(id1)) + cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}

std::string Parser::sub(std::string id1, std::string id2){
   std::cout<<"******" << id1 << '-'<< id2<<"******"<<std::endl; 
   DataHolder *result= *(cache->getData(id1))-cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}

std::string Parser::mul(std::string id1,std::string id2){ 
   std::cout<<"******" << id1 << '*'<< id2 <<"******" <<std::endl; 
   DataHolder *result= *(cache->getData(id1))*cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}

std::string Parser::div(std::string id1,std::string id2){
   std::cout<<"******" << id1 << '/'<< id2<<"******" <<std::endl; 
   DataHolder *result= *(cache->getData(id1)) / cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}

std::string Parser::bitwiseOr(std::string id1,std::string id2){
   std::cout<<"******" << id1 << '|'<< id2<<"******" <<std::endl; 
   DataHolder *result= *(cache->getData(id1)) | cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}

std::string Parser::bitwiseAnd(std::string id1,std::string id2){
   std::cout<<"******" << id1 << '&'<< id2<<"******" <<std::endl; 
   DataHolder *result= *(cache->getData(id1)) & cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}

std::string Parser::mod(std::string id1,std::string id2){
   std::cout<<"******" << id1 << '%'<< id2<<"******" <<std::endl; 
   DataHolder *result= *(cache->getData(id1)) % cache->getData(id2);
   cache->insertData(result);
   return result->getId();
}

std::string Parser::match(std::string id,std::string match){
    match = match.substr(1,match.length()-2);
   std::cout<<"******" << id << '='<< match<<"******" <<std::endl; 
   DataHolder *result=(*(cache->getData(id)) == match);
   cache->insertData(result);
   return result->getId();
}

//invoking unary operations
std::string Parser::uMinus(std::string id){
   std::cout<<"******" <<  '-'<< id<<"******" <<std::endl; 
   DataHolder *result= -*(cache->getData(id));
   cache->insertData(result);
   return result->getId();
  
}

std::string Parser::bitwiseNot(std::string id){
   std::cout<<"******" <<  '!'<< id<<"******" <<std::endl; 
   DataHolder *result= !*(cache->getData(id));
   cache->insertData(result);
   return result->getId();
  
}

std::string Parser::getExpressionId(){
   return expressionId;
}
DataCache * Parser::getCache(){
   return cache;
}
