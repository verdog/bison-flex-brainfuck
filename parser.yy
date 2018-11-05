%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.2"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  class Driver;
}

// The parsing context.
%param { Driver& drv }

%define parse.trace
%define parse.error verbose

%code {
#include "driver.hpp"
}

%define api.token.prefix {TOK_}
%token
  END  0        "end of file"
  RIGHT         ">"
  LEFT          "<"
  PLUS          "+"
  MINUS         "-"
  OUTPUT        "."
  REPLACE       ","
  OPENBRACKET   "["
  CLOSEBRACKET  "]"
;

%%
%start program;
program: symbols {
    //
}

symbols: %empty {
    //
} 
| symbols symbol {
    //
}

symbol: 
  ">" {
    drv.do_right();
    drv.memory.report(std::cout);
}
| "<" {
    drv.do_left();
    drv.memory.report(std::cout);
}
| "+" {
    drv.do_plus();
    drv.memory.report(std::cout);
}
| "-" {
    drv.do_minus();
    drv.memory.report(std::cout);
}
| "." {
    drv.do_output();
    drv.memory.report(std::cout);
}
| "," {
    drv.do_replace();
    drv.memory.report(std::cout);
}
| "[" {
    drv.do_openbracket();
    drv.memory.report(std::cout);
}
| "]" {
    drv.do_closebracket();
    drv.memory.report(std::cout);
}
%%

void
yy::parser::error (const std::string& m)
{
  std::cerr << m << '\n';
}
