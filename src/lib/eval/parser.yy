/* Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")

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
  LPAREN  "("
  RPAREN  ")"
  NOT "not"
  AND "and"
  OR "or"
  EQUAL "=="
  OPTION "option"
  RELAY4 "relay4"
  LBRACKET "["
  RBRACKET "]"
  DOT "."
  TEXT "text"
  HEX "hex"
  EXISTS "exists"
  SUBSTRING "substring"
  ALL "all"
  COMA ","
  CONCAT "concat"
;

%token <std::string> STRING "constant string"
%token <std::string> INTEGER "integer"
%token <std::string> HEXSTRING "constant hexstring"
%token <std::string> OPTION_NAME "option name"

%type <uint16_t> option_code
%type <TokenOption::RepresentationType> option_repr_type

%left OR
%left AND
%precedence NOT

%printer { yyoutput << $$; } <*>;

%%

// The whole grammar starts with an expression.
%start expression;

// Expression can either be a single token or a (something == something) expression

expression : bool_expr
           ;

bool_expr : "(" bool_expr ")"
          | NOT bool_expr
                {
                    TokenPtr neg(new TokenNot());
                    ctx.expression.push_back(neg);
                }
          | bool_expr AND bool_expr
                {
                    TokenPtr neg(new TokenAnd());
                    ctx.expression.push_back(neg);
                }
          | bool_expr OR bool_expr
                {
                    TokenPtr neg(new TokenOr());
                    ctx.expression.push_back(neg);
                }
          | string_expr EQUAL string_expr
                {
                    TokenPtr eq(new TokenEqual());
                    ctx.expression.push_back(eq);
                }
          | OPTION "[" option_code "]" "." EXISTS
                {
                    TokenPtr opt(new TokenOption($3, TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
          | RELAY4 "[" option_code "]" "." EXISTS
                {
                   switch (ctx.getUniverse()) {
                   case Option::V4:
                   {
                       TokenPtr opt(new TokenRelay4Option($3, TokenOption::EXISTS));
                       ctx.expression.push_back(opt);
                       break;
                   }
                   case Option::V6:
                       // We will have relay6[123] for the DHCPv6.
                       // In a very distant future we'll possibly be able
                       // to mix both if we have DHCPv4-over-DHCPv6, so it
                       // has some sense to make it explicit whether we
                       // talk about DHCPv4 relay or DHCPv6 relay. However,
                       // for the time being relay4 can be used in DHCPv4
                       // only.
                       error(@1, "relay4 can only be used in DHCPv4.");
                   }
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
            | RELAY4 "[" option_code "]" "." option_repr_type
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V4:
                     {
                         TokenPtr opt(new TokenRelay4Option($3, $6));
                         ctx.expression.push_back(opt);
                         break;
                     }
                     case Option::V6:
                         // We will have relay6[123] for the DHCPv6.
                         // In a very distant future we'll possibly be able
                         // to mix both if we have DHCPv4-over-DHCPv6, so it
                         // has some sense to make it explicit whether we
                         // talk about DHCPv4 relay or DHCPv6 relay. However,
                         // for the time being relay4 can be used in DHCPv4
                         // only.
                         error(@1, "relay4 can only be used in DHCPv4.");
                     }
                  }
            | SUBSTRING "(" string_expr "," start_expr "," length_expr ")"
                  {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
            | CONCAT "(" string_expr "," string_expr ")"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
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
