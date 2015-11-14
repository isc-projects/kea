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
  ALL "all"
  COMA ","
  LPAREN  "("
  RPAREN  ")"
  LBRACKET "["
  RBRACKET "]"
;

%token <std::string> STRING "constant string"
%token <std::string> INTEGER "integer"
%token <std::string> HEXSTRING "constant hexstring"
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
            | OPTION "[" INTEGER "]"
                  {
                      int n;
                      try {
                          n  = boost::lexical_cast<int>($3);
                      } catch (const boost::bad_lexical_cast &) {
                          // This can't happen...
                          ctx.error(@3,
                                    "Option code has invalid value in " + $3);
                      }
                      if (n < 0 || n > 65535) {
                          ctx.error(@3,
                                    "Option code has invalid value in "
                                    + $3 + ". Allowed range: 0..65535");
                      }
                      TokenPtr opt(new TokenOption(static_cast<uint16_t>(n)));
                      ctx.expression.push_back(opt);
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
