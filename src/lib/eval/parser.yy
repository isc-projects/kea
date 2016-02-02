/* Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.0"
%defines
%define parser_class_name {EvalParser}
%define api.token.constructor
%define api.value.type variant
%define api.namespace {isc::eval}
%define parse.assert
%code requires
{
#include <string>
#include <eval/token.h>
#include <eval/eval_context_decl.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>

using namespace isc::dhcp;
using namespace isc::eval;
}
// The parsing context.
%param { EvalContext& ctx }
%locations
%define parse.trace
%define parse.error verbose
%code
{
# include "eval_context.h"
}

%define api.token.prefix {TOKEN_}
%token
  END  0  "end of file"
  EQUAL "=="
  OPTION "option"
  SUBSTRING "substring"
  TEXT "text"
  RELAY "relay"
  HEX "hex"
  ALL "all"
  DOT "."
  COMA ","
  LPAREN  "("
  RPAREN  ")"
  LBRACKET "["
  RBRACKET "]"
;

%token <std::string> STRING "constant string"
%token <std::string> INTEGER "integer"
%token <std::string> HEXSTRING "constant hexstring"
%token <std::string> OPTION_NAME "option name"
%token <std::string> TOKEN

%type <uint16_t> option_code
%type <TokenOption::RepresentationType> option_repr_type

%printer { yyoutput << $$; } <*>;

%%

// The whole grammar starts with an expression.
%start expression;

// Expression can either be a single token or a (something == something) expression

expression : bool_expr
           ;

bool_expr : string_expr EQUAL string_expr
                {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
          ;

string_expr : STRING
                  {
                      TokenPtr str(new TokenString($1));
                      ctx.expression.push_back(str);
                  }
            | HEXSTRING
                  {
                      TokenPtr hex(new TokenHexString($1));
                      ctx.expression.push_back(hex);
                  }
            | OPTION "[" option_code "]" "." option_repr_type
                  {
                      TokenPtr opt(new TokenOption($3, $6));
                      ctx.expression.push_back(opt);
                  }
            | RELAY "[" option_code "]" "." option_repr_type
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V4:
                     {
                         TokenPtr opt(new TokenRelay4Option($3, $6));
                         ctx.expression.push_back(opt);
                         break;
                     }
                     case Option::V6:
                         error(@1, "relay support for v6 is not implemented");
                     }
                  }
            | SUBSTRING "(" string_expr "," start_expr "," length_expr ")"
                  {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
            | TOKEN
                // Temporary unused token to avoid explict but long errors
            ;

option_code : INTEGER
                 {
                     $$ = ctx.convertOptionCode($1, @1);
                 }
            | OPTION_NAME
                 {
                     $$ = ctx.convertOptionName($1, @1);
                 }
            ;

option_repr_type : TEXT
                      {
                          $$ = TokenOption::TEXTUAL;
                      }
                 | HEX
                      {
                          $$ = TokenOption::HEXADECIMAL;
                      }
                 ;

start_expr : INTEGER
                 {
                     TokenPtr str(new TokenString($1));
                     ctx.expression.push_back(str);
                 }
           ;

length_expr : INTEGER
                  {
                      TokenPtr str(new TokenString($1));
                      ctx.expression.push_back(str);
                  }
            | ALL
                 {
                     TokenPtr str(new TokenString("all"));
                     ctx.expression.push_back(str);
                 }
            ;

%%
void
isc::eval::EvalParser::error(const location_type& loc,
                             const std::string& what)
{
    ctx.error(loc, what);
}
