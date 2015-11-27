/* Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")

   Permission to use, copy, modify, and/or distribute this software for any
   purpose with or without fee is hereby granted, provided that the above
   copyright notice and this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
   REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
   AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
   INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
   OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
   PERFORMANCE OF THIS SOFTWARE. */

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
            | OPTION "[" INTEGER "]" DOT TEXT
                  {
                      uint16_t numeric_code = ctx.convert_option_code($3, @3);
                      TokenPtr opt(new TokenOption(numeric_code, TokenOption::TEXTUAL));
                      ctx.expression.push_back(opt);
                  }
            | OPTION "[" INTEGER "]" DOT HEX
                  {
                      uint16_t numeric_code = ctx.convert_option_code($3, @3);
                      TokenPtr opt(new TokenOption(numeric_code, TokenOption::HEXADECIMAL));
                      ctx.expression.push_back(opt);
                  }
            | OPTION "[" OPTION_NAME "]" DOT TEXT
                  {
                      try {
                          // This may result in exception if the specified
                          // name is unknown.
                          TokenPtr opt(new TokenOption($3,
                                                       ctx.option_universe_,
                                                       TokenOption::TEXTUAL));
                          ctx.expression.push_back(opt);

                      } catch (const isc::BadValue& ex) {
                          ctx.error(@3, ex.what());
                      }
                  }
            | OPTION "[" OPTION_NAME "]" DOT HEX
                  {
                      try {
                          // This may result in exception if the specified
                          // name is unknown.
                          TokenPtr opt(new TokenOption($3,
                                                       ctx.option_universe_,
                                                       TokenOption::HEXADECIMAL));
                          ctx.expression.push_back(opt);

                      } catch (const isc::BadValue& ex) {
                          ctx.error(@3, ex.what());
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
