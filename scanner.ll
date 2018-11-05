%{ /* -*- C++ -*- */
#include <string>
#include "driver.hh"
#include "parser.hh"
%}

%option noyywrap

WS [ \t\n]*

%%

{WS} {} // eat whitespace
\> return yy::parser::make_RIGHT();
\< return yy::parser::make_LEFT();
\+ return yy::parser::make_PLUS();
\- return yy::parser::make_MINUS();
\. return yy::parser::make_OUTPUT();
\, return yy::parser::make_REPLACE();
\[ return yy::parser::make_OPENBRACKET();
\] return yy::parser::make_CLOSEBRACKET();
<<EOF>> return yy::parser::make_END();

. {
    throw yy::parser::syntax_error("invalid character: " + std::string(yytext));
}

%%

void Driver::scan_begin() {
    yy_flex_debug = trace_scanning;
    if (file.empty() || file == "-")
        yyin = stdin;
    else if (!(yyin = fopen(file.c_str (), "r"))) {
        std::cerr << "cannot open " << file << ": " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }
}

void Driver::scan_end () {
    fclose (yyin);
}
