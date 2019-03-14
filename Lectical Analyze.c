%{
#include <math.h>
%}
DIGIT [0-9]
ID [A-Za-z][A-Za-z0-9]*
%%
{DIGIT}+ {
  if (abs(atoi(yytext)) <= abs(32768)) {
    printf( "An integer: %s (%d)\n", yytext,atoi( yytext ) );
  }
  else {
    printf("Number %d is out of range.\n",atoi(yytext));
  }
}
{DIGIT}+"."{DIGIT}* {
  printf( "A float: %s (%g)\n", yytext,atof( yytext ) );
}
if|elif|while|exit|def|print|else|input|return {
  printf( "A keyword: %s\n", yytext );
}
and|or|not {
  printf( "A logical operator: %s\n", yytext );
}
{ID} printf( "An identifier: %s\n", yytext );
"+"|"-"|"*"|"/" printf( "An operator: %s\n", yytext );
"<"|">"|"="|"<="|"=>"|"<>" printf("A correlation operator: %s\n", yytext );
":=" printf( "Notation: %s\n", yytext );
"," printf( "Comma: %s\n", yytext );
"("|")" printf( "A parenthesis: %s\n", yytext );
"#" printf( "Comment symbol : %s\n", yytext );


"{"[\^{}}\n]*"}" /* eat up one-line comments */
[ \t\n]+ /* eat up whitespace */
. printf( "Unrecognized character: %s\n", yytext );
%%
main( argc, argv )
int argc;
char **argv;
{
  ++argv, --argc; /* skip over program name */
  if ( argc > 0 )
  yyin = fopen( argv[0], "r" );
  else
  yyin = stdin;
  yylex();
}
