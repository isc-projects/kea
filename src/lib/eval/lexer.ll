/* Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%{ /* -*- C++ -*- */

/* Generated files do not make clang static analyser so happy */
#ifndef __clang_analyzer__

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <eval/eval_context.h>
#include <eval/parser.h>
#include <asiolink/io_address.h>
#include <boost/lexical_cast.hpp>

/* Please avoid C++ style comments (// ... eol) as they break flex 2.6.2 */

/* Work around an incompatibility in flex (at least versions
   2.5.31 through 2.5.33): it generates code that does
   not conform to C89.  See Debian bug 333231
   <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>. */
# undef yywrap
# define yywrap() 1

/* The location of the current token. The lexer will keep updating it. This
   variable will be useful for logging errors. */
static isc::eval::location loc;

namespace {
    bool start_token_flag = false;
    isc::eval::EvalContext::ParserType start_token_value;
};

/* To avoid the call to exit... oops! */
#define YY_FATAL_ERROR(msg) isc::eval::EvalContext::fatal(msg)
%}

/* noyywrap disables automatic rewinding for the next file to parse. Since we
   always parse only a single string, there's no need to do any wraps. And
   using yywrap requires linking with -lfl, which provides the default yywrap
   implementation that always returns 1 anyway. */
%option noyywrap

/* nounput simplifies the lexer, by removing support for putting a character
   back into the input stream. We never use such capability anyway. */
%option nounput

/* batch means that we'll never use the generated lexer interactively. */
%option batch

/* Enables debug mode. To see the debug messages, one needs to also set
   eval_flex_debug to 1, then the debug messages will be printed on stderr. */
%option debug

/* I have no idea what this option does, except it was specified in the bison
   examples and Postgres folks added it to remove gcc 4.3 warnings. Let's
   be on the safe side and keep it. */
%option noinput

/* This line tells flex to track the line numbers. It's not really that
   useful for client classes, which typically are one-liners, but it may be
   useful in more complex cases. */
%option yylineno

/* These are not token expressions yet, just convenience expressions that
   can be used during actual token definitions. Note some can match
   incorrect inputs (e.g., IP addresses) which must be checked. */
int   \-?[0-9]+
hex   [0-9a-fA-F]+
blank [ \t]
addr4 [0-9]+\.[0-9]+\.[0-9]+\.[0-9]+
addr6 [0-9a-fA-F]*\:[0-9a-fA-F]*\:[0-9a-fA-F:.]*

%{
/* This code run each time a pattern is matched. It updates the location
   by moving it ahead by yyleng bytes. yyleng specifies the length of the
   currently matched token. */
#define YY_USER_ACTION  loc.columns(evalleng);
%}

%%

%{
    /* Code run each time evallex is called. */
    loc.step();

    if (start_token_flag) {
        start_token_flag = false;
        switch (start_token_value) {
        case EvalContext::PARSER_BOOL:
            return isc::eval::EvalParser::make_TOPLEVEL_BOOL(loc);
        default:
        case EvalContext::PARSER_STRING:
            return isc::eval::EvalParser::make_TOPLEVEL_STRING(loc);
        }
    }

%}

{blank}+   {
    /* Ok, we found a with space. Let's ignore it and update loc variable. */
    loc.step();
}

[\n]+      {
    /* Newline found. Let's update the location and continue. */
    loc.lines(evalleng);
    loc.step();
}

\'[^\'\n]*\' {
    /* A string has been matched. It contains the actual string and single quotes.
       We need to get those quotes out of the way and just use its content, e.g.
       for 'foo' we should get foo */
    std::string tmp(evaltext+1);
    tmp.resize(tmp.size() - 1);

    return isc::eval::EvalParser::make_STRING(tmp, loc);
}

0[xX]{hex} {
    /* A hex string has been matched. It contains the '0x' or '0X' header
       followed by at least one hexadecimal digit. */
    return isc::eval::EvalParser::make_HEXSTRING(evaltext, loc);
}

{int} {
    /* An integer was found. */
    std::string tmp(evaltext);

    try {
        /* In substring we want to use negative values (e.g. -1).
           In enterprise-id we need to use values up to 0xffffffff.
           To cover both of those use cases, we need at least
           int64_t. */
        static_cast<void>(boost::lexical_cast<int64_t>(tmp));
    } catch (const boost::bad_lexical_cast &) {
        driver.error(loc, "Failed to convert " + tmp + " to an integer.");
    }

    /* The parser needs the string form as double conversion is no lossless */
    return isc::eval::EvalParser::make_INTEGER(tmp, loc);
}

[A-Za-z]([-_A-Za-z0-9]*[A-Za-z0-9])?({blank}|\n)*/] {
    /* This string specifies option name starting with a letter
       and further containing letters, digits, hyphens and
       underscores and finishing by letters or digits. */
    /* Moved from a variable trailing context to C++ code as it was too slow */
    std::string tmp(evaltext);
    /* remove possible trailing blanks or newlines */
    while (tmp.size() > 1) {
        char last = tmp[tmp.size() - 1];
        if ((last != ' ') && (last != '\t') && (last != '\n')) {
            break;
        }
        if (last == '\n') {
            /* Take embedded newlines into account */
            /* Can make it more complex to handle spaces after the last
               newline but currently keep it simple... */
            loc.lines();
            loc.step();
        }
        tmp.resize(tmp.size() - 1);
    }
    return isc::eval::EvalParser::make_OPTION_NAME(tmp, loc);
}

{addr4}|{addr6} {
    /* IPv4 or IPv6 address */
    std::string tmp(evaltext);

    /* Some incorrect addresses can match so we have to check. */
    try {
        isc::asiolink::IOAddress ip(tmp);
    } catch (...) {
        driver.error(loc, "Failed to convert " + tmp + " to an IP address.");
    }

    return isc::eval::EvalParser::make_IP_ADDRESS(evaltext, loc);
}

"=="           return isc::eval::EvalParser::make_EQUAL(loc);
"option"       return isc::eval::EvalParser::make_OPTION(loc);
"relay4"       return isc::eval::EvalParser::make_RELAY4(loc);
"relay6"       return isc::eval::EvalParser::make_RELAY6(loc);
"peeraddr"     return isc::eval::EvalParser::make_PEERADDR(loc);
"linkaddr"     return isc::eval::EvalParser::make_LINKADDR(loc);
"text"         return isc::eval::EvalParser::make_TEXT(loc);
"hex"          return isc::eval::EvalParser::make_HEX(loc);
"exists"       return isc::eval::EvalParser::make_EXISTS(loc);
"pkt"          return isc::eval::EvalParser::make_PKT(loc);
"iface"        return isc::eval::EvalParser::make_IFACE(loc);
"src"          return isc::eval::EvalParser::make_SRC(loc);
"dst"          return isc::eval::EvalParser::make_DST(loc);
"len"          return isc::eval::EvalParser::make_LEN(loc);
"pkt4"         return isc::eval::EvalParser::make_PKT4(loc);
"mac"          return isc::eval::EvalParser::make_CHADDR(loc);
"hlen"         return isc::eval::EvalParser::make_HLEN(loc);
"htype"        return isc::eval::EvalParser::make_HTYPE(loc);
"ciaddr"       return isc::eval::EvalParser::make_CIADDR(loc);
"giaddr"       return isc::eval::EvalParser::make_GIADDR(loc);
"yiaddr"       return isc::eval::EvalParser::make_YIADDR(loc);
"siaddr"       return isc::eval::EvalParser::make_SIADDR(loc);
"pkt6"         return isc::eval::EvalParser::make_PKT6(loc);
"msgtype"      return isc::eval::EvalParser::make_MSGTYPE(loc);
"transid"      return isc::eval::EvalParser::make_TRANSID(loc);
"vendor"       return isc::eval::EvalParser::make_VENDOR(loc);
"vendor-class" return isc::eval::EvalParser::make_VENDOR_CLASS(loc);
"data"         return isc::eval::EvalParser::make_DATA(loc);
"enterprise"   return isc::eval::EvalParser::make_ENTERPRISE(loc);
"substring"    return isc::eval::EvalParser::make_SUBSTRING(loc);
"all"          return isc::eval::EvalParser::make_ALL(loc);
"concat"       return isc::eval::EvalParser::make_CONCAT(loc);
"ifelse"       return isc::eval::EvalParser::make_IFELSE(loc);
"hexstring"    return isc::eval::EvalParser::make_TOHEXSTRING(loc);
"addrtotext"   return isc::eval::EvalParser::make_ADDRTOTEXT(loc);
"int8totext"   return isc::eval::EvalParser::make_INT8TOTEXT(loc);
"int16totext"  return isc::eval::EvalParser::make_INT16TOTEXT(loc);
"int32totext"  return isc::eval::EvalParser::make_INT32TOTEXT(loc);
"uint8totext"  return isc::eval::EvalParser::make_UINT8TOTEXT(loc);
"uint16totext" return isc::eval::EvalParser::make_UINT16TOTEXT(loc);
"uint32totext" return isc::eval::EvalParser::make_UINT32TOTEXT(loc);
"not"          return isc::eval::EvalParser::make_NOT(loc);
"and"          return isc::eval::EvalParser::make_AND(loc);
"or"           return isc::eval::EvalParser::make_OR(loc);
"member"       return isc::eval::EvalParser::make_MEMBER(loc);
"."            return isc::eval::EvalParser::make_DOT(loc);
"("            return isc::eval::EvalParser::make_LPAREN(loc);
")"            return isc::eval::EvalParser::make_RPAREN(loc);
"["            return isc::eval::EvalParser::make_LBRACKET(loc);
"]"            return isc::eval::EvalParser::make_RBRACKET(loc);
","            return isc::eval::EvalParser::make_COMA(loc);
"*"            return isc::eval::EvalParser::make_ANY(loc);
"+"            return isc::eval::EvalParser::make_PLUS(loc);
.          driver.error (loc, "Invalid character: " + std::string(evaltext));
<<EOF>>    return isc::eval::EvalParser::make_END(loc);
%%

using namespace isc::eval;

void
EvalContext::scanStringBegin(ParserType type)
{
    start_token_flag = true;
    start_token_value = type;

    loc.initialize(&file_);
    eval_flex_debug = trace_scanning_;
    YY_BUFFER_STATE buffer;
    buffer = eval_scan_bytes(string_.c_str(), string_.size());
    if (!buffer) {
        fatal("cannot scan string");
        /* fatal() throws an exception so this can't be reached */
    }
}

void
EvalContext::scanStringEnd()
{
    eval_delete_buffer(YY_CURRENT_BUFFER);
}

namespace {
/** To avoid unused function error */
class Dummy {
    /* cppcheck-suppress unusedPrivateFunction */
    void dummy() { yy_fatal_error("Fix me: how to disable its definition?"); }
};
}
#endif /* !__clang_analyzer__ */
