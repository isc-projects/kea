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
#include <exceptions/exceptions.h>

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

namespace {

// The location of the current token. The lexer will keep updating it. This
// variable will be useful for logging errors.
isc::dhcp::location loc;

/// @brief Location stack.
std::vector<isc::dhcp::location> locs;

/// @brief File name.
std::string file;

/// @brief File name stack.
std::vector<std::string> files;

/// @brief State stack.
std::vector<struct yy_buffer_state*> states;

bool start_token_flag = false;

isc::dhcp::Parser6Context::ParserType start_token_value;
int comment_start_line = 0;

};

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

%x COMMENT
%x DIR_ENTER DIR_INCLUDE DIR_EXIT

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
    // This part of the code is copied over to the verbatim to the top
    // of the generated yylex function. Explanation:
    // http://www.gnu.org/software/bison/manual/html_node/Multiple-start_002dsymbols.html

    // Code run each time yylex is called.
    loc.step();

    if (start_token_flag) {
        start_token_flag = false;
        switch (start_token_value) {
        case Parser6Context::PARSER_DHCP6:
            return isc::dhcp::Dhcp6Parser::make_TOPLEVEL_DHCP6(loc);
        case Parser6Context::PARSER_GENERIC_JSON:
        default:
            return isc::dhcp::Dhcp6Parser::make_TOPLEVEL_GENERIC_JSON(loc);
        }
    }
%}

#.* ;

"//"(.*) ;

"/*" {
  BEGIN(COMMENT);
  comment_start_line = yylineno;
}

<COMMENT>"*/" BEGIN(INITIAL);
<COMMENT>. ;
<COMMENT><<EOF>> {
    isc_throw(isc::BadValue, "Comment not closed. (/* in line " << comment_start_line);
}

"<?" BEGIN(DIR_ENTER);
<DIR_ENTER>"include" BEGIN(DIR_INCLUDE);
<DIR_INCLUDE>\"([^\"\n])+\" {
    // Include directive.

    // Extract the filename.
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);

    driver.includeFile(tmp);
}
<DIR_EXIT>"?>" BEGIN(INITIAL);
    

{blank}+   {
    // Ok, we found a with space. Let's ignore it and update loc variable.
    loc.step();
}

[\n]+      {
    // Newline found. Let's update the location and continue.
    loc.lines(yyleng);
    loc.step();
}

\"Dhcp6\"  {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONFIG:
        return isc::dhcp::Dhcp6Parser::make_DHCP6(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("Dhcp6", loc);
    }
}

\"interfaces-config\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return  isc::dhcp::Dhcp6Parser::make_INTERFACES_CONFIG(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("interfaces-config", loc);
    }
}

\"interfaces\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::INTERFACES_CONFIG:
        return  isc::dhcp::Dhcp6Parser::make_INTERFACES(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("interfaces", loc);
    }
}

\"lease-database\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_LEASE_DATABASE(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("lease-database", loc);
    }
}

\"hosts-database\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_HOSTS_DATABASE(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hosts-database", loc);
    }
}

\"type\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE:
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_TYPE(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("type", loc);
    }
}

\"user\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE:
        return isc::dhcp::Dhcp6Parser::make_USER(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("user", loc);
    }
}

\"password\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE:
        return isc::dhcp::Dhcp6Parser::make_PASSWORD(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("password", loc);
    }
}

\"host\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE:
        return isc::dhcp::Dhcp6Parser::make_HOST(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("host", loc);
    }
}

\"persist\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE:
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_PERSIST(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("persist", loc);
    }
}

\"lfc-interval\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE:
        return isc::dhcp::Dhcp6Parser::make_LFC_INTERVAL(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("lfc-interval", loc);
    }
}

\"preferred-lifetime\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_PREFERRED_LIFETIME(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("preferred-lifetime", loc);
    }
}

\"valid-lifetime\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_VALID_LIFETIME(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("valid-lifetime", loc);
    }
}

\"renew-timer\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_RENEW_TIMER(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("renew-timer", loc);
    }
}

\"rebind-timer\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_REBIND_TIMER(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("rebind-timer", loc);
    }
}

\"subnet6\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_SUBNET6(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("subnet6", loc);
    }
}

\"option-data\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::POOLS:
    case isc::dhcp::Parser6Context::PD_POOLS:
    case isc::dhcp::Parser6Context::RESERVATIONS:
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
    case isc::dhcp::Parser6Context::CLIENT_CLASS:
        return isc::dhcp::Dhcp6Parser::make_OPTION_DATA(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("option-data", loc);
    }
}

\"name\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE:
    case isc::dhcp::Parser6Context::OPTION_DATA:
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
    case isc::dhcp::Parser6Context::CLIENT_CLASS:
    case isc::dhcp::Parser6Context::LOGGERS:
        return isc::dhcp::Dhcp6Parser::make_NAME(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("name", loc);
    }
}

\"data\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DATA:
        return isc::dhcp::Dhcp6Parser::make_DATA(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("data", loc);
    }
}

\"pools\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_POOLS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("pools", loc);
    }
}

\"pd-pools\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_PD_POOLS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("pd-pools", loc);
    }
}

\"prefix\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::PD_POOLS:
        return isc::dhcp::Dhcp6Parser::make_PREFIX(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("prefix", loc);
    }
}

\"prefix-len\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::PD_POOLS:
        return isc::dhcp::Dhcp6Parser::make_PREFIX_LEN(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("prefix-len", loc);
    }
}

\"delegated-len\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::PD_POOLS:
        return isc::dhcp::Dhcp6Parser::make_DELEGATED_LEN(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("delegated-len", loc);
    }
}

\"pool\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::POOLS:
        return isc::dhcp::Dhcp6Parser::make_POOL(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("pool", loc);
    }
}

\"subnet\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_SUBNET(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("subnet", loc);
    }
}

\"interface\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_INTERFACE(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("interface", loc);
    }
}

\"id\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_ID(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("id", loc);
    }
}

\"code\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DATA:
        return isc::dhcp::Dhcp6Parser::make_CODE(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("code", loc);
    }
}

\"mac-sources\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_MAC_SOURCES(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("mac-sources", loc);
    }
}

\"relay-supplied-options\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_RELAY_SUPPLIED_OPTIONS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("relay-supplied-options", loc);
    }
}

\"host-reservation-identifiers\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_HOST_RESERVATION_IDENTIFIERS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("host-reservation-identifiers", loc);
    }
}

\"Logging\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONFIG:
        return isc::dhcp::Dhcp6Parser::make_LOGGING(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("Logging", loc);
    }
}

\"loggers\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LOGGING:
        return isc::dhcp::Dhcp6Parser::make_LOGGERS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("loggers", loc);
    }
}

\"output_options\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LOGGERS:
        return isc::dhcp::Dhcp6Parser::make_OUTPUT_OPTIONS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("output_options", loc);
    }
}

\"output\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OUTPUT_OPTIONS:
        return isc::dhcp::Dhcp6Parser::make_OUTPUT(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("output", loc);
    }
}

\"debuglevel\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LOGGERS:
        return isc::dhcp::Dhcp6Parser::make_DEBUGLEVEL(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("debuglevel", loc);
    }
}

\"severity\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LOGGERS:
        return isc::dhcp::Dhcp6Parser::make_SEVERITY(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("severity", loc);
    }
}

\"client-classes\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_CLIENT_CLASSES(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("client-classes", loc);
    }
}

\"client-class\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
        return isc::dhcp::Dhcp6Parser::make_CLIENT_CLASS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("client-class", loc);
    }
}

\"test\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
    case isc::dhcp::Parser6Context::CLIENT_CLASS:
        return isc::dhcp::Dhcp6Parser::make_TEST(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("test", loc);
    }
}

\"reservations\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_RESERVATIONS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("reservations", loc);
    }
}

\"ip-addresses\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_IP_ADDRESSES(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("ip-addresses", loc);
    }
}

\"prefixes\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_PREFIXES(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("prefixes", loc);
    }
}

\"duid\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::MAC_SOURCES:
    case isc::dhcp::Parser6Context::HOST_RESERVATION_IDENTIFIERS:
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_DUID(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("duid", loc);
    }
}

\"hw-address\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::HOST_RESERVATION_IDENTIFIERS:
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_HW_ADDRESS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hw-address", loc);
    }
}

\"hostname\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_HOSTNAME(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hostname", loc);
    }
}

\"space\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DATA:
        return isc::dhcp::Dhcp6Parser::make_SPACE(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("space", loc);
    }
}

\"csv-format\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DATA:
        return isc::dhcp::Dhcp6Parser::make_CSV_FORMAT(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("csv-format", loc);
    }
}

\"hooks-libraries\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_HOOKS_LIBRARIES(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hooks-libraries", loc);
    }
}

\"library\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::HOOKS_LIBRARIES:
        return isc::dhcp::Dhcp6Parser::make_LIBRARY(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("library", loc);
    }
}

\"server-id\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_SERVER_ID(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("server-id", loc);
    }
}

\"identifier\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_IDENTIFIER(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("identifier", loc);
    }
}

\"htype\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_HTYPE(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("htype", loc);
    }
}

\"time\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_TIME(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("time", loc);
    }
}

\"enterprise-id\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_ENTERPRISE_ID(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("enterprise-id", loc);
    }
}

\"expired-leases-processing\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_EXPIRED_LEASES_PROCESSING(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("expired-leases-processing", loc);
    }
}

\"dhcp4o6-port\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_DHCP4O6_PORT(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("dhcp4o6-port", loc);
    }
}

\"dhcp-ddns\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_DHCP_DDNS(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("dhcp-ddns", loc);
    }
}

\"enable-updates\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_ENABLE_UPDATES(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("enable-updates", loc);
    }
}

\"qualifying-suffix\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_QUALIFYING_SUFFIX(loc);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("qualifying-suffix", loc);
    }
}


{JSONString} {
    // A string has been matched. It contains the actual string and single quotes.
    // We need to get those quotes out of the way and just use its content, e.g.
    // for 'foo' we should get foo
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);

    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, loc);
}

"["                  { return isc::dhcp::Dhcp6Parser::make_LSQUARE_BRACKET(loc); }
"]"                 { return isc::dhcp::Dhcp6Parser::make_RSQUARE_BRACKET(loc); }
"{"                  { return isc::dhcp::Dhcp6Parser::make_LCURLY_BRACKET(loc); }
"}"                     { return isc::dhcp::Dhcp6Parser::make_RCURLY_BRACKET(loc); }
","                   { return isc::dhcp::Dhcp6Parser::make_COMMA(loc); }
":"                     { return isc::dhcp::Dhcp6Parser::make_COLON(loc); }

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

<<EOF>>    {
    if (states.empty()) {
        return isc::dhcp::Dhcp6Parser::make_END(loc);
    }
    loc = locs.back();
    locs.pop_back();
    file = files.back();
    files.pop_back();
    parser6__delete_buffer(YY_CURRENT_BUFFER);
    parser6__switch_to_buffer(states.back());
    states.pop_back();

    BEGIN(DIR_EXIT);
}

%%

using namespace isc::dhcp;

void
Parser6Context::scanStringBegin(const std::string& str, ParserType parser_type)
{
    start_token_flag = true;
    start_token_value = parser_type;

    file = "<string>";
    loc.initialize(&file);
    yy_flex_debug = trace_scanning_;
    YY_BUFFER_STATE buffer;
    buffer = yy_scan_bytes(str.c_str(), str.size());
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

void
Parser6Context::scanFileBegin(FILE * f,
                              const std::string& filename,
                              ParserType parser_type) {

    start_token_flag = true;
    start_token_value = parser_type;

    file = filename;
    loc.initialize(&file);
    yy_flex_debug = trace_scanning_;
    YY_BUFFER_STATE buffer;

    // See dhcp6_lexer.cc header for available definitions
    buffer = parser6__create_buffer(f, 65536 /*buffer size*/);
    if (!buffer) {
        fatal("cannot scan file " + filename);
    }
    parser6__switch_to_buffer(buffer);
}

void
Parser6Context::scanFileEnd(FILE * f) {
    fclose(f);
    yy_delete_buffer(YY_CURRENT_BUFFER);
}

void
Parser6Context::includeFile(const std::string& filename) {
    if (states.size() > 10) {
        fatal("Too many nested include.");
    }

    FILE* f = fopen(filename.c_str(), "r");
    if (!f) {
        fatal("Can't open include file " + filename);
    }
    states.push_back(YY_CURRENT_BUFFER);
    YY_BUFFER_STATE buffer;
    buffer = parser6__create_buffer(f, 65536 /*buffer size*/);
    if (!buffer) {
        fatal( "Can't scan include file " + filename);
    }
    parser6__switch_to_buffer(buffer);
    files.push_back(file);
    file = filename;
    locs.push_back(loc);
    loc.initialize(&file);

    BEGIN(INITIAL);
}

namespace {
/// To avoid unused function error
class Dummy {
    // cppcheck-suppress unusedPrivateFunction
    void dummy() { yy_fatal_error("Fix me: how to disable its definition?"); }
};
}
