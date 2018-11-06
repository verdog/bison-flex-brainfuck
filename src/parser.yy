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
program: expression_list {
}

expression_list: expression_list expression {
}
| expression {
}

expression: symbol {
}
| "[" expression_list "]" {
}
| %empty {
}

symbol: 
  ">" {
    drv.do_right();
}
| "<" {
    drv.do_left();
}
| "+" {
    drv.do_plus();
    drv.memory.report();
}
| "-" {
    drv.do_minus();
    drv.memory.report();
}
| "." {
    drv.do_output();
}
| "," {
    drv.do_replace();
}
%%

void yy::parser::error (const std::string& m) {
    std::cerr << m << '\n';
}
