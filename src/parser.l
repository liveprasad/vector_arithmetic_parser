
%{ 
   /* Definition section */
  #include <stdio.h> 
  //#include <string>
  #include "y.tab.h" 
  extern int yylval;
  //extern yyerror(const char*); 
%} 
  
/* Rule Section */
%% 
[0-9]+ { 
          yylval=atoi(yytext); 
          return NUMBER; 
  
       } 
[\t] ; 
  
[\n] return 0; 
  
. return yytext[0]; 
  
%% 
  
int yywrap() 
{ 
 return 1; 
} 
