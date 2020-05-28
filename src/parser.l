
%{ 
   /* Definition section */
  #include <stdio.h> 
  #include "y.tab.h" 
  //extern int yylval;
  //extern yyerror(const char*); 
%} 
  
/* Rule Section */
%% 
[a-zA-Z0-9_]+ { 
          yylval.str=strdup(yytext); 
          return ID; 
  
       }
\"(\\.|[^"\\])*\" {
          yylval.str=strdup(yytext);
	  return MATCH;
       }   
[ \t] ; 
  
[\n] return 0; 
  
. { return yytext[0] ;} 
  
%% 
  
int yywrap() 
{ 
 return 1; 
} 
