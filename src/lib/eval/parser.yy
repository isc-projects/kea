%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
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
class EvalContext;
}
// The parsing context.
%param { EvalContext& ctx }
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &ctx.file;
};
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
  SUBSTRING "substring"
  COMA ","
  LPAREN  "("
  RPAREN  ")"
;
%token <std::string> STRING "constant string"
%token <int> OPTION "option code"
%printer { yyoutput << $$; } <*>;
%%

// The whole grammar starts with an expression.
%start expression;

// Expression can either be a single token or a (something == something) expression
expression:
token EQUAL token
| token;

token:
STRING { /* push back TokenString */ }
| OPTION { /* push back TokenOption */ }
| SUBSTRING "(" token "," token "," token ")" {
    /* push back TokenSubstring */
  }

%%
void
isc::eval::EvalParser::error(const location_type& l,
                             const std::string& m)
{
    ctx.error(l, m);
}
