/* Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.0"
%defines
%define parser_class_name {Dhcp6Parser}
%define api.prefix {parser6_}
%define api.token.constructor
%define api.value.type variant
%define api.namespace {isc::dhcp}
%define parse.assert
%code requires
{
#include <string>
#include <cc/data.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>
#include <dhcp6/parser_context_decl.h>

using namespace isc::dhcp;
using namespace isc::data;
using namespace std;
}
// The parsing context.
%param { isc::dhcp::Parser6Context& ctx }
%locations
%define parse.trace
%define parse.error verbose
%code
{
#include <dhcp6/parser_context.h>

}

%define api.token.prefix {TOKEN_}
// Tokens in an order which makes sense and related to the intented use.
%token
  END  0  "end of file"
  COMMA ","
  COLON ":"
  LSQUARE_BRACKET "["
  RSQUARE_BRACKET "]"
  LCURLY_BRACKET "{"
  RCURLY_BRACKET "}"
  NULL_TYPE "null"
;

%token <std::string> STRING "constant string"
%token <int64_t> INTEGER "integer"
%token <double> FLOAT "floating point"
%token <bool> BOOLEAN "boolean"

%type <ElementPtr> value

%printer { yyoutput << $$; } <*>;

%%
// The whole grammar starts with a map, because the config file
// constists of Dhcp, Logger and DhcpDdns entries in one big { }.
%start map;

// Values rule
value : INTEGER { $$ = ElementPtr(new IntElement($1)); }
     | FLOAT { $$ = ElementPtr(new DoubleElement($1)); }
     | BOOLEAN { $$ = ElementPtr(new BoolElement($1)); }
     | STRING { $$ = ElementPtr(new StringElement($1)); }
     | NULL_TYPE { $$ = ElementPtr(new NullElement()); }
     | map { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); }
     | list { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); }
    ;


map: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement());
    ctx.stack_.push_back(m);
} map_content RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
};

// Assignments rule
map_content:  { /* do nothing, it's an empty map */ }
    | STRING COLON value {
        // map containing a single entry
        ctx.stack_.back()->set($1, $3);
    }
    | map_content COMMA STRING COLON value {
        // map consisting of a shorter map followed by comma and string:value
        ctx.stack_.back()->set($3, $5);
    }
    ;

list: LSQUARE_BRACKET {
    // List parsing about to start
    ElementPtr l(new ListElement());
    ctx.stack_.push_back(l);
} list_content RSQUARE_BRACKET {
    // list parsing complete. Put any sanity checking here
};

list_content: { /* do nothing, it's an empty list */ }
    | value {
        // List consisting of a single element.
        ctx.stack_.back()->add($1);
    }
    | list_content COMMA value {
        // List ending with , and a value.
        ctx.stack_.back()->add($3);
    }
    ;

%%

void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
