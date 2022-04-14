/* Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.3.0"
%defines
%define api.parser.class {EvalParser}
%define api.prefix {eval}
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
// Tokens in an order which makes sense and related to the intended use.
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
  RELAY6 "relay6"
  MEMBER "member"
  PEERADDR "peeraddr"
  LINKADDR "linkaddr"
  LBRACKET "["
  RBRACKET "]"
  DOT "."
  TEXT "text"
  HEX "hex"
  EXISTS "exists"
  PKT "pkt"
  IFACE "iface"
  SRC "src"
  DST "dst"
  LEN "len"
  PKT4 "pkt4"
  CHADDR "mac"
  HLEN "hlen"
  HTYPE "htype"
  CIADDR "ciaddr"
  GIADDR "giaddr"
  YIADDR "yiaddr"
  SIADDR "siaddr"
  SUBSTRING "substring"
  SPLIT "split"
  ALL "all"
  COMA ","
  CONCAT "concat"
  PLUS "+"
  IFELSE "ifelse"
  TOHEXSTRING "hexstring"
  ADDRTOTEXT "addrtotext"
  INT8TOTEXT "int8totext"
  INT16TOTEXT "int16totext"
  INT32TOTEXT "int32totext"
  UINT8TOTEXT "uint8totext"
  UINT16TOTEXT "uint16totext"
  UINT32TOTEXT "uint32totext"
  PKT6 "pkt6"
  MSGTYPE "msgtype"
  TRANSID "transid"
  VENDOR_CLASS "vendor-class"
  VENDOR "vendor"
  ANY "*"
  DATA "data"
  ENTERPRISE "enterprise"

  TOPLEVEL_BOOL "top-level bool"
  TOPLEVEL_STRING "top-level string"
;

%token <std::string> STRING "constant string"
%token <std::string> INTEGER "integer"
%token <std::string> HEXSTRING "constant hexstring"
%token <std::string> OPTION_NAME "option name"
%token <std::string> IP_ADDRESS "ip address"

%type <uint16_t> option_code
%type <uint16_t> sub_option_code
%type <uint32_t> enterprise_id
%type <uint32_t> integer_expr
%type <TokenOption::RepresentationType> option_repr_type
%type <TokenRelay6Field::FieldType> relay6_field
%type <int8_t> nest_level
%type <TokenPkt::MetadataType> pkt_metadata
%type <TokenPkt4::FieldType> pkt4_field
%type <TokenPkt6::FieldType> pkt6_field

%left PLUS
%left OR
%left AND
%precedence NOT

%printer { yyoutput << $$; } <*>;

%%

// The whole grammar starts with a 'start' symbol...
%start start;

// ... that expects either TOPLEVEL_BOOL or TOPLEVEL_STRING. Depending on which
// token appears first, it will determine what is allowed and what it not.
start: TOPLEVEL_BOOL expression
     | TOPLEVEL_STRING string_expr
;

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
          | OPTION "[" option_code "]" "." OPTION "[" sub_option_code "]" "." EXISTS
                {
                    TokenPtr opt(new TokenSubOption($3, $8, TokenOption::EXISTS));
                    ctx.expression.push_back(opt);
                }
          | RELAY4 "[" sub_option_code "]" "." EXISTS
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
          | RELAY6 "[" nest_level "]" "." OPTION "[" sub_option_code "]" "." EXISTS
                {
                    switch (ctx.getUniverse()) {
                    case Option::V6:
                    {
                        TokenPtr opt(new TokenRelay6Option($3, $8, TokenOption::EXISTS));
                        ctx.expression.push_back(opt);
                        break;
                    }
                    case Option::V4:
                        // For now we only use relay6 in DHCPv6.
                        error(@1, "relay6 can only be used in DHCPv6.");
                    }
                }
          | VENDOR_CLASS "[" enterprise_id "]" "." EXISTS
              {
                  // Expression: vendor-class[1234].exists
                  //
                  // This token will find option 124 (DHCPv4) or 16 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendorClass(ctx.getUniverse(), $3, TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
          | VENDOR "[" enterprise_id "]" "." EXISTS
              {
                  // Expression: vendor[1234].exists
                  //
                  // This token will find option 125 (DHCPv4) or 17 (DHCPv6),
                  // and will check if enterprise-id equals specified value.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), $3, TokenOption::EXISTS));
                  ctx.expression.push_back(exist);
              }
          | VENDOR "[" enterprise_id "]" "." OPTION "[" sub_option_code "]" "." EXISTS
              {
                  // Expression vendor[1234].option[123].exists
                  //
                  // This token will check if specified vendor option
                  // exists, has specified enterprise-id and if has
                  // specified suboption.
                  TokenPtr exist(new TokenVendor(ctx.getUniverse(), $3, TokenOption::EXISTS, $8));
                  ctx.expression.push_back(exist);
               }
          | MEMBER "(" STRING ")"
              {
                  // Expression member('foo')
                  //
                  // This token will check if the packet is a member of
                  // the specified client class.
                  // To avoid loops at evaluation only already defined and
                  // built-in classes are allowed.
                  std::string cc = $3;
                  if (!ctx.isClientClassDefined(cc)) {
                      error(@3, "Not defined client class '" + cc + "'");
                  }
                  TokenPtr member(new TokenMember(cc));
                  ctx.expression.push_back(member);
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
            | IP_ADDRESS
                  {
                      TokenPtr ip(new TokenIpAddress($1));
                      ctx.expression.push_back(ip);
                  }
            | OPTION "[" option_code "]" "." option_repr_type
                  {
                      TokenPtr opt(new TokenOption($3, $6));
                      ctx.expression.push_back(opt);
                  }
            | OPTION "[" option_code "]" "." OPTION "[" sub_option_code "]" "." option_repr_type
                  {
                      TokenPtr opt(new TokenSubOption($3, $8, $11));
                      ctx.expression.push_back(opt);
                  }
            | RELAY4 "[" sub_option_code "]" "." option_repr_type
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

            | RELAY6 "[" nest_level "]" "." OPTION "[" sub_option_code "]" "." option_repr_type
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr opt(new TokenRelay6Option($3, $8, $11));
                         ctx.expression.push_back(opt);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(@1, "relay6 can only be used in DHCPv6.");
                     }
                  }

            | PKT "." pkt_metadata
                  {
                      TokenPtr pkt_metadata(new TokenPkt($3));
                      ctx.expression.push_back(pkt_metadata);
                  }
            | PKT4 "." pkt4_field
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V4:
                     {
                         TokenPtr pkt4_field(new TokenPkt4($3));
                         ctx.expression.push_back(pkt4_field);
                         break;
                     }
                     case Option::V6:
                         // For now we only use pkt4 in DHCPv4.
                         error(@1, "pkt4 can only be used in DHCPv4.");
                     }
                  }
            | PKT6 "." pkt6_field
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr pkt6_field(new TokenPkt6($3));
                         ctx.expression.push_back(pkt6_field);
                         break;
                     }
                     case Option::V4:
                         // For now we only use pkt6 in DHCPv6.
                         error(@1, "pkt6 can only be used in DHCPv6.");
                     }
                  }
            | RELAY6 "[" nest_level "]" "." relay6_field
                  {
                     switch (ctx.getUniverse()) {
                     case Option::V6:
                     {
                         TokenPtr relay6field(new TokenRelay6Field($3, $6));
                         ctx.expression.push_back(relay6field);
                         break;
                     }
                     case Option::V4:
                         // For now we only use relay6 in DHCPv6.
                         error(@1, "relay6 can only be used in DHCPv6.");
                     }
                  }

            | SUBSTRING "(" string_expr "," start_expr "," length_expr ")"
                  {
                      TokenPtr sub(new TokenSubstring());
                      ctx.expression.push_back(sub);
                  }
            | SPLIT "(" string_expr "," string_expr "," int_expr ")"
                  {
                      TokenPtr split(new TokenSplit());
                      ctx.expression.push_back(split);
                  }
            | CONCAT "(" string_expr "," string_expr ")"
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
            | string_expr PLUS string_expr
                  {
                      TokenPtr conc(new TokenConcat());
                      ctx.expression.push_back(conc);
                  }
            | IFELSE "(" bool_expr "," string_expr "," string_expr ")"
                  {
                      TokenPtr cond(new TokenIfElse());
                      ctx.expression.push_back(cond);
                  }
            | TOHEXSTRING "(" string_expr "," string_expr ")"
                  {
                      TokenPtr tohex(new TokenToHexString());
                      ctx.expression.push_back(tohex);
                  }
            | ADDRTOTEXT "(" string_expr ")"
                  {
                      TokenPtr addrtotext(new TokenIpAddressToText());
                      ctx.expression.push_back(addrtotext);
                  }
            | INT8TOTEXT "(" string_expr ")"
                  {
                      TokenPtr int8totext(new TokenInt8ToText());
                      ctx.expression.push_back(int8totext);
                  }
            | INT16TOTEXT "(" string_expr ")"
                  {
                      TokenPtr int16totext(new TokenInt16ToText());
                      ctx.expression.push_back(int16totext);
                  }
            | INT32TOTEXT "(" string_expr ")"
                  {
                      TokenPtr int32totext(new TokenInt32ToText());
                      ctx.expression.push_back(int32totext);
                  }
            | UINT8TOTEXT "(" string_expr ")"
                  {
                      TokenPtr uint8totext(new TokenUInt8ToText());
                      ctx.expression.push_back(uint8totext);
                  }
            | UINT16TOTEXT "(" string_expr ")"
                  {
                      TokenPtr uint16totext(new TokenUInt16ToText());
                      ctx.expression.push_back(uint16totext);
                  }
            | UINT32TOTEXT "(" string_expr ")"
                  {
                      TokenPtr uint32totext(new TokenUInt32ToText());
                      ctx.expression.push_back(uint32totext);
                  }
            | VENDOR "." ENTERPRISE
                {
                    // expression: vendor.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor option.
                    TokenPtr vendor(new TokenVendor(ctx.getUniverse(), 0, TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
            | VENDOR_CLASS "." ENTERPRISE
                {
                    // expression: vendor-class.enterprise
                    //
                    // This token will return enterprise-id number of
                    // received vendor class option.
                    TokenPtr vendor(new TokenVendorClass(ctx.getUniverse(), 0,
                                                         TokenVendor::ENTERPRISE_ID));
                    ctx.expression.push_back(vendor);
                }
            | VENDOR "[" enterprise_id "]" "." OPTION "[" sub_option_code "]" "." option_repr_type
                {
                    // This token will search for vendor option with
                    // specified enterprise-id.  If found, will search
                    // for specified suboption and finally will return
                    // its content.
                    TokenPtr opt(new TokenVendor(ctx.getUniverse(), $3, $11, $8));
                    ctx.expression.push_back(opt);
                }
            | VENDOR_CLASS "[" enterprise_id "]" "." DATA
                {
                    // expression: vendor-class[1234].data
                    //
                    // Vendor class option does not have suboptions,
                    // but chunks of data (typically 1, but the option
                    // structure allows multiple of them). If chunk
                    // offset is not specified, we assume the first (0th)
                    // is requested.
                    TokenPtr vendor_class(new TokenVendorClass(ctx.getUniverse(), $3,
                                                               TokenVendor::DATA, 0));
                    ctx.expression.push_back(vendor_class);
                }
            | VENDOR_CLASS "[" enterprise_id "]" "." DATA "[" INTEGER "]"
                {
                    // expression: vendor-class[1234].data[5]
                    //
                    // Vendor class option does not have suboptions,
                    // but chunks of data (typically 1, but the option
                    // structure allows multiple of them). This syntax
                    // specifies which data chunk (tuple) we want.
                    uint8_t index = ctx.convertUint8($8, @8);
                    TokenPtr vendor_class(new TokenVendorClass(ctx.getUniverse(), $3,
                                                               TokenVendor::DATA, index));
                    ctx.expression.push_back(vendor_class);
                }
            | integer_expr
                {
                    TokenPtr integer(new TokenInteger($1));
                    ctx.expression.push_back(integer);
                }
            | "(" string_expr ")"
            ;

integer_expr : INTEGER
                 {
                     $$ = ctx.convertUint32($1, @1);
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

sub_option_code : INTEGER
                 {
                     $$ = ctx.convertOptionCode($1, @1);
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

nest_level : INTEGER
                 {
                     $$ = ctx.convertNestLevelNumber($1, @1);
                 }
                 // Eventually we may add strings to handle different
                 // ways of choosing from which relay we want to extract
                 // an option or field.
           ;

pkt_metadata : IFACE
                  {
                      $$ = TokenPkt::IFACE;
                  }
             | SRC
                  {
                      $$ = TokenPkt::SRC;
                  }
             | DST
                  {
                      $$ = TokenPkt::DST;
                  }
             | LEN
                  {
                      $$ = TokenPkt::LEN;
                  }
             ;

enterprise_id : INTEGER
                   {
                       $$ = ctx.convertUint32($1, @1);
                   }
              | "*"
                   {
                       $$ = 0;
                   }
              ;

pkt4_field : CHADDR
                {
                    $$ = TokenPkt4::CHADDR;
                }
           | HLEN
                {
                    $$ = TokenPkt4::HLEN;
                }
           | HTYPE
                {
                    $$ = TokenPkt4::HTYPE;
                }
           | CIADDR
                {
                    $$ = TokenPkt4::CIADDR;
                }
           | GIADDR
                {
                    $$ = TokenPkt4::GIADDR;
                }
           | YIADDR
                {
                    $$ = TokenPkt4::YIADDR;
                }
           | SIADDR
                {
                    $$ = TokenPkt4::SIADDR;
                }
           | MSGTYPE
                 {
                    $$ = TokenPkt4::MSGTYPE;
                 }
           | TRANSID
                 {
                    $$ = TokenPkt4::TRANSID;
                 }
           ;

pkt6_field : MSGTYPE
                 {
                     $$ = TokenPkt6::MSGTYPE;
                 }
           | TRANSID
                 {
                     $$ = TokenPkt6::TRANSID;
                 }
           ;

relay6_field : PEERADDR
                   {
                       $$ = TokenRelay6Field::PEERADDR;
                   }
             | LINKADDR
                   {
                       $$ = TokenRelay6Field::LINKADDR;
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
int_expr : INTEGER
                 {
                     TokenPtr str(new TokenString($1));
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
