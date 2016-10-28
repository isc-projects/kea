/* Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%{ /* -*- C++ -*- */
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <dhcp6/parser_context.h>
#include <asiolink/io_address.h>
#include <boost/lexical_cast.hpp>

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token. The lexer will keep updating it. This
// variable will be useful for logging errors.
static isc::dhcp::location loc;

// To avoid the call to exit... oops!
#define YY_FATAL_ERROR(msg) isc::dhcp::Parser6Context::fatal(msg)
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
   yy_flex_debug to 1, then the debug messages will be printed on stderr. */
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
blank [ \t]

UnicodeEscapeSequence                   u[0-9A-Fa-f]{4}
JSONEscapeCharacter                     ["\\/bfnrt]
JSONEscapeSequence                      {JSONEscapeCharacter}|{UnicodeEscapeSequence}
JSONStringCharacter                     [^"\\]|\\{JSONEscapeSequence}
JSONString                              \"{JSONStringCharacter}*\"


%{
// This code run each time a pattern is matched. It updates the location
// by moving it ahead by yyleng bytes. yyleng specifies the length of the
// currently matched token.
#define YY_USER_ACTION  loc.columns(yyleng);
%}

%%

%{
    // Code run each time yylex is called.
    loc.step();
%}

{blank}+   {
    // Ok, we found a with space. Let's ignore it and update loc variable.
    loc.step();
}
[\n]+      {
    // Newline found. Let's update the location and continue.
    loc.lines(yyleng);
    loc.step();
}


{JSONString} {
    // A string has been matched. It contains the actual string and single quotes.
    // We need to get those quotes out of the way and just use its content, e.g.
    // for 'foo' we should get foo
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);

    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, loc);
}

"["                                     { return isc::dhcp::Dhcp6Parser::make_LSQUARE_BRACKET(loc); }
"]"                                     { return isc::dhcp::Dhcp6Parser::make_RSQUARE_BRACKET(loc); }
"{"                                     { return isc::dhcp::Dhcp6Parser::make_LCURLY_BRACKET(loc); }
"}"                                     { return isc::dhcp::Dhcp6Parser::make_RCURLY_BRACKET(loc); }
","                                     { return isc::dhcp::Dhcp6Parser::make_COMMA(loc); }
":"                                     { return isc::dhcp::Dhcp6Parser::make_COLON(loc); }

{int} {
    // An integer was found.
    std::string tmp(yytext);
    int64_t integer = 0;
    try {
        // In substring we want to use negative values (e.g. -1).
        // In enterprise-id we need to use values up to 0xffffffff.
        // To cover both of those use cases, we need at least
        // int64_t.
        integer = boost::lexical_cast<int64_t>(tmp);
    } catch (const boost::bad_lexical_cast &) {
        driver.error(loc, "Failed to convert " + tmp + " to an integer.");
    }

    // The parser needs the string form as double conversion is no lossless
    return isc::dhcp::Dhcp6Parser::make_INTEGER(integer, loc);
}
[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)? {
    // A floating point was found.
    std::string tmp(yytext);
    double fp = 0.0;
    try {
        // In substring we want to use negative values (e.g. -1).
        // In enterprise-id we need to use values up to 0xffffffff.
        // To cover both of those use cases, we need at least
        // int64_t.
        fp = boost::lexical_cast<double>(tmp);
    } catch (const boost::bad_lexical_cast &) {
        driver.error(loc, "Failed to convert " + tmp + " to a floating point.");
    }

    return isc::dhcp::Dhcp6Parser::make_FLOAT(fp, loc);
}

true|false {
    string tmp(yytext);
    return isc::dhcp::Dhcp6Parser::make_BOOLEAN(tmp == "true", loc);
}

null {
   return isc::dhcp::Dhcp6Parser::make_NULL_TYPE(loc);
}

.          driver.error (loc, "Invalid character: " + std::string(yytext));
<<EOF>>    return isc::dhcp::Dhcp6Parser::make_END(loc);
%%

using namespace isc::dhcp;

void
Parser6Context::scanStringBegin()
{
    loc.initialize(&file_);
    yy_flex_debug = trace_scanning_;
    YY_BUFFER_STATE buffer;
    buffer = yy_scan_bytes(string_.c_str(), string_.size());
    if (!buffer) {
        fatal("cannot scan string");
        // fatal() throws an exception so this can't be reached
    }
}

void
Parser6Context::scanStringEnd()
{
    yy_delete_buffer(YY_CURRENT_BUFFER);
}

namespace {
/// To avoid unused function error
class Dummy {
    // cppcheck-suppress unusedPrivateFunction
    void dummy() { yy_fatal_error("Fix me: how to disable its definition?"); }
};
}
