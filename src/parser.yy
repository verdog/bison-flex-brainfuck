%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.2"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  class Driver;
  #include "brainfuckprog.hpp"
}

// The parsing context.
%param { Driver& drv }

%define parse.trace true
%define parse.error verbose

%code {
#include <string>
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
program: symbol_list {

}

symbol_list: symbol_list symbol {
    drv.add_symbol($2);
    drv.run();
}
| symbol {
    drv.add_symbol($1);
    drv.run();
}

%type <bf::pnode::Base*> symbol;
symbol: 
  ">" {
    $$ = new bf::pnode::Right(drv, drv.memory);
}
| "<" {
    $$ = new bf::pnode::Left(drv, drv.memory);
}
| "+" {
    $$ = new bf::pnode::Add(drv, drv.memory);
}
| "-" {
    $$ = new bf::pnode::Subtract(drv, drv.memory);
}
| "." {
    $$ = new bf::pnode::Output(drv, drv.memory);
}
| "," {
    $$ = new bf::pnode::Input(drv, drv.memory);
}
| "[" {
    $$ = new bf::pnode::OpenLoop(drv, drv.memory);
}
| "]" {
    $$ = new bf::pnode::CloseLoop(drv, drv.memory);
}
%%

void yy::parser::error (const std::string& m) {
    std::cerr << m << '\n';
}
