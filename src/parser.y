
%{ 
   /* Definition section */
   #include "parser.hpp"
  
   //extern int yylex();
   //extern yy_buffer_state;
   //typedef struct  yy_buffer_state *YY_BUFFER_STATE;
   //extern YY_BUFFER_STATE yy_scan_string(const char * str);
   //extern void yy_delete_buffer(YY_BUFFER_STATE);
   //extern void  yyerror(const char *);
   //extern int yyparse();
   //int flag = 0;
   //extern YY_BUFFER_STATE yy_scan_buffer(char *, size_t);
%} 
  
%token NUMBER 
  
%left '+' '-'
  
%left '*' '/' '%'
  
%left '(' ')'
  
/* Rule Section */
%% 
  
ArithmeticExpression: E{ 
  
         printf("\nResult=%d\n", $$); 
  
         return 0; 
  
        }; 
 E:E'+'E {$$=$1+$3;} 
  
 |E'-'E {$$=$1-$3;} 
  
 |E'*'E {$$=$1*$3;} 
  
 |E'/'E {$$=$1/$3;} 
  
 |E'%'E {$$=$1%$3;} 
  
 |'('E')' {$$=$2;} 
  
 | NUMBER {$$=$1;} 
  
 ; 
  
%% 
  
//driver code 

Parser::Parser(){
}

Parser::~Parser(){
}

int Parser::evaluate(const char* expression) 
{ 
   //char *s=(char *) malloc(5000* sizeof(char));
   printf("provided expression is %s",expression );
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

void Parser::add(std::string id1,std::string id2){
  *(cache->getData(id1)) +*( cache->getData(id2));
}
