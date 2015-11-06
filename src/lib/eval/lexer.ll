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

%{ /* -*- C++ -*- */
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <eval/eval_context.h>
#include <eval/parser.h>
#include <boost/lexical_cast.hpp>

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token. The lexer will keep updating it. This
// variable will be useful for logging errors.
static isc::eval::location loc;
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
   can be used during actual token definitions. */
int   [0-9]+
hex   [0-9a-fA-F]+
blank [ \t]
str   [a-zA-Z_0-9]*

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

\'{str}\' {
    // A string has been matched. It contains the actual string and single quotes.
    // We need to get those quotes out of the way and just use its content, e.g.
    // for 'foo' we should get foo
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);

    return isc::eval::EvalParser::make_STRING(tmp, loc);
}

0[xX]{hex} {
    // A hex string has been matched. It contains the '0x' or '0X' header
    // followed by at least one hexadecimal digit.
    return isc::eval::EvalParser::make_HEXSTRING(yytext, loc);
}

{int} {
    // A code (16 bit unsigned integer) was found.
    std::string tmp(yytext);

    int n;
    try {
        n = boost::lexical_cast<int>(tmp);
    } catch (const boost::bad_lexical_cast &) {
        driver.error(loc, "Failed to convert specified option code to "
                     "number in " + tmp + ".");
    }

    // 65535 is the maximum value of the option code in DHCPv6. We want the
    // code to be the same for v4 and v6, so let's ignore for a moment that
    // max. option code in DHCPv4 is 255.
    if (n < 0 || n > 65535) {
        driver.error(loc, "Option code has invalid value in " +
                     std::string(yytext) + ". Allowed range: 0..65535");
    }

    return isc::eval::EvalParser::make_CODE(static_cast<uint16_t>(n), loc);
}

"=="        return isc::eval::EvalParser::make_EQUAL(loc);
"option"    return isc::eval::EvalParser::make_OPTION(loc);
"substring" return isc::eval::EvalParser::make_SUBSTRING(loc);
"("         return isc::eval::EvalParser::make_LPAREN(loc);
")"         return isc::eval::EvalParser::make_RPAREN(loc);
"["         return isc::eval::EvalParser::make_LBRACKET(loc);
"]"         return isc::eval::EvalParser::make_RBRACKET(loc);
","         return isc::eval::EvalParser::make_COMA(loc);

.          driver.error (loc, "Invalid character: " + std::string(yytext));
<<EOF>>    return isc::eval::EvalParser::make_END(loc);
%%

using namespace isc::eval;

void
EvalContext::scanBegin()
{
    yy_flex_debug = trace_scanning_;
    if (file_.empty () || file_ == "-") {
        yyin = stdin;
    }
    else if (!(yyin = fopen(file_.c_str (), "r"))) {
        error("cannot open " + file_ + ": " + strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void
EvalContext::scanEnd()
{
    fclose(yyin);
}
