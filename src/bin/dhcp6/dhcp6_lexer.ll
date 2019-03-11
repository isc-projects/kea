/* Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")

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
#include <dhcp6/parser_context.h>
#include <asiolink/io_address.h>
#include <boost/lexical_cast.hpp>
#include <exceptions/exceptions.h>

/* Please avoid C++ style comments (// ... eol) as they break flex 2.6.2 */

/* Work around an incompatibility in flex (at least versions
   2.5.31 through 2.5.33): it generates code that does
   not conform to C89.  See Debian bug 333231
   <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>. */
# undef yywrap
# define yywrap() 1

namespace {

bool start_token_flag = false;

isc::dhcp::Parser6Context::ParserType start_token_value;
unsigned int comment_start_line = 0;

using namespace isc::dhcp;

};

/* To avoid the call to exit... oops! */
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

/* avoid to get static global variables to remain with C++. */
/* in last resort %option reentrant */

/* Enables debug mode. To see the debug messages, one needs to also set
   yy_flex_debug to 1, then the debug messages will be printed on stderr. */
%option debug

/* I have no idea what this option does, except it was specified in the bison
   examples and Postgres folks added it to remove gcc 4.3 warnings. Let's
   be on the safe side and keep it. */
%option noinput

%x COMMENT
%x DIR_ENTER DIR_INCLUDE DIR_EXIT

/* These are not token expressions yet, just convenience expressions that
   can be used during actual token definitions. Note some can match
   incorrect inputs (e.g., IP addresses) which must be checked. */
int   \-?[0-9]+
blank [ \t\r]

UnicodeEscapeSequence           u[0-9A-Fa-f]{4}
JSONEscapeCharacter             ["\\/bfnrt]
JSONEscapeSequence              {JSONEscapeCharacter}|{UnicodeEscapeSequence}
JSONStandardCharacter           [^\x00-\x1f"\\]
JSONStringCharacter             {JSONStandardCharacter}|\\{JSONEscapeSequence}
JSONString                      \"{JSONStringCharacter}*\"

/* for errors */

BadUnicodeEscapeSequence        u[0-9A-Fa-f]{0,3}[^0-9A-Fa-f]
BadJSONEscapeSequence           [^"\\/bfnrtu]|{BadUnicodeEscapeSequence}
ControlCharacter                [\x00-\x1f]
ControlCharacterFill            [^"\\]|\\{JSONEscapeSequence}

%{
/* This code run each time a pattern is matched. It updates the location
   by moving it ahead by yyleng bytes. yyleng specifies the length of the
   currently matched token. */
#define YY_USER_ACTION  driver.loc_.columns(yyleng);
%}

%%

%{
    /* This part of the code is copied over to the verbatim to the top
       of the generated yylex function. Explanation:
       http://www.gnu.org/software/bison/manual/html_node/Multiple-start_002dsymbols.html */

    /* Code run each time yylex is called. */
    driver.loc_.step();

    if (start_token_flag) {
        start_token_flag = false;
        switch (start_token_value) {
        case Parser6Context::PARSER_JSON:
        default:
            return isc::dhcp::Dhcp6Parser::make_TOPLEVEL_JSON(driver.loc_);
        case Parser6Context::PARSER_DHCP6:
            return isc::dhcp::Dhcp6Parser::make_TOPLEVEL_DHCP6(driver.loc_);
        case Parser6Context::SUBPARSER_DHCP6:
            return isc::dhcp::Dhcp6Parser::make_SUB_DHCP6(driver.loc_);
        case Parser6Context::PARSER_INTERFACES:
            return isc::dhcp::Dhcp6Parser::make_SUB_INTERFACES6(driver.loc_);
        case Parser6Context::PARSER_SUBNET6:
            return isc::dhcp::Dhcp6Parser::make_SUB_SUBNET6(driver.loc_);
        case Parser6Context::PARSER_POOL6:
            return isc::dhcp::Dhcp6Parser::make_SUB_POOL6(driver.loc_);
        case Parser6Context::PARSER_PD_POOL:
            return isc::dhcp::Dhcp6Parser::make_SUB_PD_POOL(driver.loc_);
        case Parser6Context::PARSER_HOST_RESERVATION:
            return isc::dhcp::Dhcp6Parser::make_SUB_RESERVATION(driver.loc_);
        case Parser6Context::PARSER_OPTION_DEFS:
            return isc::dhcp::Dhcp6Parser::make_SUB_OPTION_DEFS(driver.loc_);
        case Parser6Context::PARSER_OPTION_DEF:
            return isc::dhcp::Dhcp6Parser::make_SUB_OPTION_DEF(driver.loc_);
        case Parser6Context::PARSER_OPTION_DATA:
            return isc::dhcp::Dhcp6Parser::make_SUB_OPTION_DATA(driver.loc_);
        case Parser6Context::PARSER_HOOKS_LIBRARY:
            return isc::dhcp::Dhcp6Parser::make_SUB_HOOKS_LIBRARY(driver.loc_);
        case Parser6Context::PARSER_DHCP_DDNS:
            return isc::dhcp::Dhcp6Parser::make_SUB_DHCP_DDNS(driver.loc_);
        case Parser6Context::PARSER_CONFIG_CONTROL:
            return isc::dhcp::Dhcp6Parser::make_SUB_CONFIG_CONTROL(driver.loc_);
        case Parser6Context::PARSER_LOGGING:
            return isc::dhcp::Dhcp6Parser::make_SUB_LOGGING(driver.loc_);
        }
    }
%}

#.* ;

"//"(.*) ;

"/*" {
  BEGIN(COMMENT);
  comment_start_line = driver.loc_.end.line;;
}

<COMMENT>"*/" BEGIN(INITIAL);
<COMMENT>. ;
<COMMENT><<EOF>> {
    isc_throw(Dhcp6ParseError, "Comment not closed. (/* in line " << comment_start_line);
}

"<?" BEGIN(DIR_ENTER);
<DIR_ENTER>"include" BEGIN(DIR_INCLUDE);
<DIR_INCLUDE>\"([^\"\n])+\" {
    /* Include directive. */

    /* Extract the filename. */
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);

    driver.includeFile(tmp);
}
<DIR_ENTER,DIR_INCLUDE,DIR_EXIT><<EOF>> {
    isc_throw(Dhcp6ParseError, "Directive not closed.");
}
<DIR_EXIT>"?>" BEGIN(INITIAL);


<*>{blank}+   {
    /* Ok, we found a with space. Let's ignore it and update loc variable. */
    driver.loc_.step();
}

<*>[\n]+      {
    /* Newline found. Let's update the location and continue. */
    driver.loc_.lines(yyleng);
    driver.loc_.step();
}


\"enable-updates\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_ENABLE_UPDATES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("enable-updates", driver.loc_);
    }
}

\"qualifying-suffix\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_QUALIFYING_SUFFIX(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("qualifying-suffix", driver.loc_);
    }
}

\"server-ip\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_SERVER_IP(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("server-ip", driver.loc_);
    }
}

\"server-port\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_SERVER_PORT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("server-port", driver.loc_);
    }
}

\"sender-ip\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_SENDER_IP(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("sender-ip", driver.loc_);
    }
}

\"sender-port\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_SENDER_PORT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("sender-port", driver.loc_);
    }
}

\"max-queue-size\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_MAX_QUEUE_SIZE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("max-queue-size", driver.loc_);
    }
}

\"ncr-protocol\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_NCR_PROTOCOL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("ncr-protocol", driver.loc_);
    }
}

\"ncr-format\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_NCR_FORMAT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("ncr-format", driver.loc_);
    }
}

\"override-no-update\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_OVERRIDE_NO_UPDATE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("override-no-update", driver.loc_);
    }
}

\"override-client-update\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_OVERRIDE_CLIENT_UPDATE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("override-client-update", driver.loc_);
    }
}

\"replace-client-name\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_REPLACE_CLIENT_NAME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("replace-client-name", driver.loc_);
    }
}

\"generated-prefix\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_GENERATED_PREFIX(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("generated-prefix", driver.loc_);
    }
}

\"hostname-char-set\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_HOSTNAME_CHAR_SET(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hostname-char-set", driver.loc_);
    }
}

\"hostname-char-replacement\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_HOSTNAME_CHAR_REPLACEMENT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hostname-char-replacement", driver.loc_);
    }
}

(?i:\"UDP\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::dhcp::Parser6Context::NCR_PROTOCOL) {
        return isc::dhcp::Dhcp6Parser::make_UDP(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, driver.loc_);
}

(?i:\"TCP\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::dhcp::Parser6Context::NCR_PROTOCOL) {
        return isc::dhcp::Dhcp6Parser::make_TCP(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, driver.loc_);
}

(?i:\"JSON\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::dhcp::Parser6Context::NCR_FORMAT) {
        return isc::dhcp::Dhcp6Parser::make_JSON(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, driver.loc_);
}

(?i:\"when-present\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::dhcp::Parser6Context::REPLACE_CLIENT_NAME) {
        return isc::dhcp::Dhcp6Parser::make_WHEN_PRESENT(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, driver.loc_);
}

(?i:\"true\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::dhcp::Parser6Context::REPLACE_CLIENT_NAME) {
        return isc::dhcp::Dhcp6Parser::make_WHEN_PRESENT(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, driver.loc_);
}

\"never\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::REPLACE_CLIENT_NAME:
        return isc::dhcp::Dhcp6Parser::make_NEVER(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("never", driver.loc_);
    }
}

(?i:\"never\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::dhcp::Parser6Context::REPLACE_CLIENT_NAME) {
        return isc::dhcp::Dhcp6Parser::make_NEVER(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, driver.loc_);
}

(?i:\"false\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::dhcp::Parser6Context::REPLACE_CLIENT_NAME) {
        return isc::dhcp::Dhcp6Parser::make_NEVER(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, driver.loc_);
}

(?i:\"always\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::dhcp::Parser6Context::REPLACE_CLIENT_NAME) {
        return isc::dhcp::Dhcp6Parser::make_ALWAYS(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, driver.loc_);
}

(?i:\"when-not-present\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::dhcp::Parser6Context::REPLACE_CLIENT_NAME) {
        return isc::dhcp::Dhcp6Parser::make_WHEN_NOT_PRESENT(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::dhcp::Dhcp6Parser::make_STRING(tmp, driver.loc_);
}

\"Dhcp6\"  {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONFIG:
        return isc::dhcp::Dhcp6Parser::make_DHCP6(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("Dhcp6", driver.loc_);
    }
}

\"data-directory\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return  isc::dhcp::Dhcp6Parser::make_DATA_DIRECTORY(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("data-directory", driver.loc_);
    }
}

\"interfaces-config\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return  isc::dhcp::Dhcp6Parser::make_INTERFACES_CONFIG(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("interfaces-config", driver.loc_);
    }
}

\"interfaces\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::INTERFACES_CONFIG:
        return  isc::dhcp::Dhcp6Parser::make_INTERFACES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("interfaces", driver.loc_);
    }
}

\"re-detect\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::INTERFACES_CONFIG:
        return  isc::dhcp::Dhcp6Parser::make_RE_DETECT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("re-detect", driver.loc_);
    }
}

\"sanity-checks\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return  isc::dhcp::Dhcp6Parser::make_SANITY_CHECKS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("sanity-checks", driver.loc_);
    }
}

\"lease-checks\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SANITY_CHECKS:
        return  isc::dhcp::Dhcp6Parser::make_LEASE_CHECKS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("lease-checks", driver.loc_);
    }
}

\"lease-database\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_LEASE_DATABASE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("lease-database", driver.loc_);
    }
}

\"hosts-database\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_HOSTS_DATABASE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hosts-database", driver.loc_);
    }
}

\"hosts-databases\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_HOSTS_DATABASES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hosts-databases", driver.loc_);
    }
}

\"config-control\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_CONFIG_CONTROL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("config-control", driver.loc_);
    }
}

\"config-databases\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONFIG_CONTROL:
        return isc::dhcp::Dhcp6Parser::make_CONFIG_DATABASES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("config-databases", driver.loc_);
    }
}


\"readonly\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_READONLY(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("readonly", driver.loc_);
    }
}

\"type\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::OPTION_DEF:
    case isc::dhcp::Parser6Context::SERVER_ID:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_TYPE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("type", driver.loc_);
    }
}

\"memfile\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE_TYPE:
        return isc::dhcp::Dhcp6Parser::make_MEMFILE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("memfile", driver.loc_);
    }
}

\"mysql\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE_TYPE:
        return isc::dhcp::Dhcp6Parser::make_MYSQL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("mysql", driver.loc_);
    }
}

\"postgresql\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE_TYPE:
        return isc::dhcp::Dhcp6Parser::make_POSTGRESQL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("postgresql", driver.loc_);
    }
}

\"cql\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DATABASE_TYPE:
        return isc::dhcp::Dhcp6Parser::make_CQL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("cql", driver.loc_);
    }
}

\"user\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_USER(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("user", driver.loc_);
    }
}

\"password\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_PASSWORD(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("password", driver.loc_);
    }
}

\"host\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_HOST(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("host", driver.loc_);
    }
}

\"port\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_PORT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("port", driver.loc_);
    }
}

\"persist\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::SERVER_ID:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_PERSIST(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("persist", driver.loc_);
    }
}

\"lfc-interval\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_LFC_INTERVAL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("lfc-interval", driver.loc_);
    }
}

\"connect-timeout\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_CONNECT_TIMEOUT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("connect-timeout", driver.loc_);
    }
}

\"keyspace\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_KEYSPACE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("keyspace", driver.loc_);
    }
}

\"consistency\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_CONSISTENCY(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("consistency", driver.loc_);
    }
}

\"serial-consistency\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_SERIAL_CONSISTENCY(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("serial-consistency", driver.loc_);
    }
}

\"reconnect-wait-time\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_RECONNECT_WAIT_TIME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("reconnect-wait-time", driver.loc_);
    }
}

\"request-timeout\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_REQUEST_TIMEOUT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("request-timeout", driver.loc_);
    }
}

\"tcp-keepalive\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_TCP_KEEPALIVE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("tcp-keepalive", driver.loc_);
    }
}

\"tcp-nodelay\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_TCP_NODELAY(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("tcp-nodelay", driver.loc_);
    }
}

\"contact-points\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_CONTACT_POINTS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("contact-points", driver.loc_);
    }
}

\"max-reconnect-tries\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_MAX_RECONNECT_TRIES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("max-reconnect-tries", driver.loc_);
    }
}

\"preferred-lifetime\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_PREFERRED_LIFETIME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("preferred-lifetime", driver.loc_);
    }
}

\"valid-lifetime\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_VALID_LIFETIME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("valid-lifetime", driver.loc_);
    }
}

\"renew-timer\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_RENEW_TIMER(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("renew-timer", driver.loc_);
    }
}

\"rebind-timer\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_REBIND_TIMER(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("rebind-timer", driver.loc_);
    }
}

\"decline-probation-period\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_DECLINE_PROBATION_PERIOD(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("decline-probation-period", driver.loc_);
    }
}

\"server-tag\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_SERVER_TAG(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("server-tag", driver.loc_);
    }
}

\"subnet6\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_SUBNET6(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("subnet6", driver.loc_);
    }
}

\"shared-networks\" {
    switch (driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return Dhcp6Parser::make_SHARED_NETWORKS(driver.loc_);
    default:
        return Dhcp6Parser::make_STRING("shared-networks", driver.loc_);
    }
}

\"option-def\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_OPTION_DEF(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("option-def", driver.loc_);
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
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_OPTION_DATA(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("option-data", driver.loc_);
    }
}

\"name\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LEASE_DATABASE:
    case isc::dhcp::Parser6Context::HOSTS_DATABASE:
    case isc::dhcp::Parser6Context::OPTION_DEF:
    case isc::dhcp::Parser6Context::OPTION_DATA:
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
    case isc::dhcp::Parser6Context::LOGGERS:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
    case isc::dhcp::Parser6Context::CONFIG_DATABASE:
        return isc::dhcp::Dhcp6Parser::make_NAME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("name", driver.loc_);
    }
}

\"data\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DATA:
        return isc::dhcp::Dhcp6Parser::make_DATA(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("data", driver.loc_);
    }
}

\"always-send\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DATA:
        return isc::dhcp::Dhcp6Parser::make_ALWAYS_SEND(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("always-send", driver.loc_);
    }
}

\"pools\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_POOLS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("pools", driver.loc_);
    }
}

\"pd-pools\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_PD_POOLS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("pd-pools", driver.loc_);
    }
}

\"prefix\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::PD_POOLS:
        return isc::dhcp::Dhcp6Parser::make_PREFIX(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("prefix", driver.loc_);
    }
}

\"prefix-len\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::PD_POOLS:
        return isc::dhcp::Dhcp6Parser::make_PREFIX_LEN(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("prefix-len", driver.loc_);
    }
}

\"excluded-prefix\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::PD_POOLS:
        return isc::dhcp::Dhcp6Parser::make_EXCLUDED_PREFIX(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("excluded-prefix", driver.loc_);
    }
}

\"excluded-prefix-len\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::PD_POOLS:
        return isc::dhcp::Dhcp6Parser::make_EXCLUDED_PREFIX_LEN(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("excluded-prefix-len", driver.loc_);
    }
}

\"delegated-len\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::PD_POOLS:
        return isc::dhcp::Dhcp6Parser::make_DELEGATED_LEN(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("delegated-len", driver.loc_);
    }
}

\"pool\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::POOLS:
        return isc::dhcp::Dhcp6Parser::make_POOL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("pool", driver.loc_);
    }
}

\"user-context\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::INTERFACES_CONFIG:
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
    case isc::dhcp::Parser6Context::OPTION_DEF:
    case isc::dhcp::Parser6Context::OPTION_DATA:
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
    case isc::dhcp::Parser6Context::SERVER_ID:
    case isc::dhcp::Parser6Context::CONTROL_SOCKET:
    case isc::dhcp::Parser6Context::POOLS:
    case isc::dhcp::Parser6Context::PD_POOLS:
    case isc::dhcp::Parser6Context::RESERVATIONS:
    case isc::dhcp::Parser6Context::LOGGERS:
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_USER_CONTEXT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("user-context", driver.loc_);
    }
}

\"comment\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::INTERFACES_CONFIG:
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
    case isc::dhcp::Parser6Context::OPTION_DEF:
    case isc::dhcp::Parser6Context::OPTION_DATA:
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
    case isc::dhcp::Parser6Context::SERVER_ID:
    case isc::dhcp::Parser6Context::CONTROL_SOCKET:
    case isc::dhcp::Parser6Context::POOLS:
    case isc::dhcp::Parser6Context::PD_POOLS:
    case isc::dhcp::Parser6Context::RESERVATIONS:
    case isc::dhcp::Parser6Context::LOGGERS:
    case isc::dhcp::Parser6Context::DHCP_DDNS:
        return isc::dhcp::Dhcp6Parser::make_COMMENT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("comment", driver.loc_);
    }
}

\"subnet\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_SUBNET(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("subnet", driver.loc_);
    }
}

\"interface\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_INTERFACE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("interface", driver.loc_);
    }
}

\"interface-id\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_INTERFACE_ID(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("interface-id", driver.loc_);
    }
}

\"id\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_ID(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("id", driver.loc_);
    }
}

\"rapid-commit\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_RAPID_COMMIT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("rapid-commit", driver.loc_);
    }
}

\"reservation-mode\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_RESERVATION_MODE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("reservation-mode", driver.loc_);
    }
}

\"disabled\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATION_MODE:
        return isc::dhcp::Dhcp6Parser::make_DISABLED(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("disabled", driver.loc_);
    }
}

\"off\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATION_MODE:
        return isc::dhcp::Dhcp6Parser::make_DISABLED(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("off", driver.loc_);
    }
}

\"out-of-pool\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATION_MODE:
        return isc::dhcp::Dhcp6Parser::make_OUT_OF_POOL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("out-of-pool", driver.loc_);
    }
}

\"global\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATION_MODE:
        return isc::dhcp::Dhcp6Parser::make_GLOBAL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("global", driver.loc_);
    }
}

\"all\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATION_MODE:
        return isc::dhcp::Dhcp6Parser::make_ALL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("all", driver.loc_);
    }
}

\"code\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DEF:
    case isc::dhcp::Parser6Context::OPTION_DATA:
        return isc::dhcp::Dhcp6Parser::make_CODE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("code", driver.loc_);
    }
}

\"mac-sources\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_MAC_SOURCES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("mac-sources", driver.loc_);
    }
}

\"relay-supplied-options\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_RELAY_SUPPLIED_OPTIONS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("relay-supplied-options", driver.loc_);
    }
}

\"host-reservation-identifiers\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_HOST_RESERVATION_IDENTIFIERS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("host-reservation-identifiers", driver.loc_);
    }
}

\"Logging\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONFIG:
        return isc::dhcp::Dhcp6Parser::make_LOGGING(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("Logging", driver.loc_);
    }
}

\"loggers\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LOGGING:
        return isc::dhcp::Dhcp6Parser::make_LOGGERS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("loggers", driver.loc_);
    }
}

\"output_options\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LOGGERS:
        return isc::dhcp::Dhcp6Parser::make_OUTPUT_OPTIONS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("output_options", driver.loc_);
    }
}

\"output\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OUTPUT_OPTIONS:
        return isc::dhcp::Dhcp6Parser::make_OUTPUT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("output", driver.loc_);
    }
}

\"flush\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OUTPUT_OPTIONS:
        return isc::dhcp::Dhcp6Parser::make_FLUSH(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("flush", driver.loc_);
    }
}

\"maxsize\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OUTPUT_OPTIONS:
        return isc::dhcp::Dhcp6Parser::make_MAXSIZE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("maxsize", driver.loc_);
    }
}

\"maxver\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OUTPUT_OPTIONS:
        return isc::dhcp::Dhcp6Parser::make_MAXVER(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("maxver", driver.loc_);
    }
}


\"debuglevel\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LOGGERS:
        return isc::dhcp::Dhcp6Parser::make_DEBUGLEVEL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("debuglevel", driver.loc_);
    }
}

\"severity\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::LOGGERS:
        return isc::dhcp::Dhcp6Parser::make_SEVERITY(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("severity", driver.loc_);
    }
}

\"client-classes\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_CLIENT_CLASSES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("client-classes", driver.loc_);
    }
}

\"require-client-classes\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::POOLS:
    case isc::dhcp::Parser6Context::PD_POOLS:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_REQUIRE_CLIENT_CLASSES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("require-client-classes", driver.loc_);
    }
}

\"client-class\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::POOLS:
    case isc::dhcp::Parser6Context::PD_POOLS:
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_CLIENT_CLASS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("client-class", driver.loc_);
    }
}

\"test\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
        return isc::dhcp::Dhcp6Parser::make_TEST(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("test", driver.loc_);
    }
}

\"only-if-required\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CLIENT_CLASSES:
        return isc::dhcp::Dhcp6Parser::make_ONLY_IF_REQUIRED(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("only-if-required", driver.loc_);
    }
}

\"reservations\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
    case isc::dhcp::Parser6Context::SUBNET6:
        return isc::dhcp::Dhcp6Parser::make_RESERVATIONS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("reservations", driver.loc_);
    }
}

\"ip-addresses\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATIONS:
    case isc::dhcp::Parser6Context::RELAY:
        return isc::dhcp::Dhcp6Parser::make_IP_ADDRESSES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("ip-addresses", driver.loc_);
    }
}

\"prefixes\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_PREFIXES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("prefixes", driver.loc_);
    }
}

\"duid\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::MAC_SOURCES:
    case isc::dhcp::Parser6Context::HOST_RESERVATION_IDENTIFIERS:
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_DUID(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("duid", driver.loc_);
    }
}

\"hw-address\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::HOST_RESERVATION_IDENTIFIERS:
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_HW_ADDRESS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hw-address", driver.loc_);
    }
}

\"hostname\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_HOSTNAME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hostname", driver.loc_);
    }
}

\"flex-id\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::HOST_RESERVATION_IDENTIFIERS:
    case isc::dhcp::Parser6Context::RESERVATIONS:
        return isc::dhcp::Dhcp6Parser::make_FLEX_ID(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("flex-id", driver.loc_);
    }
}

\"space\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DEF:
    case isc::dhcp::Parser6Context::OPTION_DATA:
        return isc::dhcp::Dhcp6Parser::make_SPACE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("space", driver.loc_);
    }
}

\"csv-format\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DATA:
        return isc::dhcp::Dhcp6Parser::make_CSV_FORMAT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("csv-format", driver.loc_);
    }
}

\"record-types\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DEF:
        return isc::dhcp::Dhcp6Parser::make_RECORD_TYPES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("record-types", driver.loc_);
    }
}

\"encapsulate\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DEF:
        return isc::dhcp::Dhcp6Parser::make_ENCAPSULATE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("encapsulate", driver.loc_);
    }
}

\"array\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::OPTION_DEF:
        return isc::dhcp::Dhcp6Parser::make_ARRAY(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("array", driver.loc_);
    }
}

\"relay\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SUBNET6:
    case isc::dhcp::Parser6Context::SHARED_NETWORK:
        return isc::dhcp::Dhcp6Parser::make_RELAY(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("relay", driver.loc_);
    }
}

\"ip-address\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::RELAY:
        return isc::dhcp::Dhcp6Parser::make_IP_ADDRESS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("ip-address", driver.loc_);
    }
}

\"hooks-libraries\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_HOOKS_LIBRARIES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hooks-libraries", driver.loc_);
    }
}


\"parameters\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::HOOKS_LIBRARIES:
        return isc::dhcp::Dhcp6Parser::make_PARAMETERS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("parameters", driver.loc_);
    }
}

\"library\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::HOOKS_LIBRARIES:
        return isc::dhcp::Dhcp6Parser::make_LIBRARY(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("library", driver.loc_);
    }
}

\"server-id\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_SERVER_ID(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("server-id", driver.loc_);
    }
}

\"LLT\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DUID_TYPE:
        return isc::dhcp::Dhcp6Parser::make_LLT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("LLT", driver.loc_);
    }
}

\"EN\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DUID_TYPE:
        return isc::dhcp::Dhcp6Parser::make_EN(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("EN", driver.loc_);
    }
}

\"LL\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DUID_TYPE:
        return isc::dhcp::Dhcp6Parser::make_LL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("LL", driver.loc_);
    }
}

\"identifier\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_IDENTIFIER(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("identifier", driver.loc_);
    }
}

\"htype\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_HTYPE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("htype", driver.loc_);
    }
}

\"time\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_TIME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("time", driver.loc_);
    }
}

\"enterprise-id\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::SERVER_ID:
        return isc::dhcp::Dhcp6Parser::make_ENTERPRISE_ID(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("enterprise-id", driver.loc_);
    }
}

\"expired-leases-processing\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_EXPIRED_LEASES_PROCESSING(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("expired-leases-processing", driver.loc_);
    }
}

\"reclaim-timer-wait-time\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::EXPIRED_LEASES_PROCESSING:
        return isc::dhcp::Dhcp6Parser::make_RECLAIM_TIMER_WAIT_TIME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("reclaim-timer-wait-time", driver.loc_);
    }
}

\"flush-reclaimed-timer-wait-time\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::EXPIRED_LEASES_PROCESSING:
        return isc::dhcp::Dhcp6Parser::make_FLUSH_RECLAIMED_TIMER_WAIT_TIME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("flush-reclaimed-timer-wait-time", driver.loc_);
    }
}

\"hold-reclaimed-time\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::EXPIRED_LEASES_PROCESSING:
        return isc::dhcp::Dhcp6Parser::make_HOLD_RECLAIMED_TIME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("hold-reclaimed-time", driver.loc_);
    }
}

\"max-reclaim-leases\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::EXPIRED_LEASES_PROCESSING:
        return isc::dhcp::Dhcp6Parser::make_MAX_RECLAIM_LEASES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("max-reclaim-leases", driver.loc_);
    }
}

\"max-reclaim-time\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::EXPIRED_LEASES_PROCESSING:
        return isc::dhcp::Dhcp6Parser::make_MAX_RECLAIM_TIME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("max-reclaim-time", driver.loc_);
    }
}

\"unwarned-reclaim-cycles\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::EXPIRED_LEASES_PROCESSING:
        return isc::dhcp::Dhcp6Parser::make_UNWARNED_RECLAIM_CYCLES(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("unwarned-reclaim-cycles", driver.loc_);
    }
}

\"dhcp4o6-port\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_DHCP4O6_PORT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("dhcp4o6-port", driver.loc_);
    }
}

\"control-socket\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_CONTROL_SOCKET(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("control-socket", driver.loc_);
    }
}

\"socket-type\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONTROL_SOCKET:
        return isc::dhcp::Dhcp6Parser::make_SOCKET_TYPE(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("socket-type", driver.loc_);
    }
}

\"socket-name\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONTROL_SOCKET:
        return isc::dhcp::Dhcp6Parser::make_SOCKET_NAME(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("socket-name", driver.loc_);
    }
}

\"dhcp-queue-control\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_DHCP_QUEUE_CONTROL(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("dhcp-queue-control", driver.loc_);
    }
}

\"dhcp-ddns\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::DHCP6:
        return isc::dhcp::Dhcp6Parser::make_DHCP_DDNS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("dhcp-ddns", driver.loc_);
    }
}

\"Dhcp4\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONFIG:
        return isc::dhcp::Dhcp6Parser::make_DHCP4(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("Dhcp4", driver.loc_);
    }
}

\"DhcpDdns\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONFIG:
        return isc::dhcp::Dhcp6Parser::make_DHCPDDNS(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("DhcpDdns", driver.loc_);
    }
}

\"Control-agent\" {
    switch(driver.ctx_) {
    case isc::dhcp::Parser6Context::CONFIG:
        return isc::dhcp::Dhcp6Parser::make_CONTROL_AGENT(driver.loc_);
    default:
        return isc::dhcp::Dhcp6Parser::make_STRING("Control-agent", driver.loc_);
    }
}


{JSONString} {
    /* A string has been matched. It contains the actual string and single quotes.
       We need to get those quotes out of the way and just use its content, e.g.
       for 'foo' we should get foo */
    std::string raw(yytext+1);
    size_t len = raw.size() - 1;
    raw.resize(len);
    std::string decoded;
    decoded.reserve(len);
    for (size_t pos = 0; pos < len; ++pos) {
        int b = 0;
        char c = raw[pos];
        switch (c) {
        case '"':
            /* impossible condition */
            driver.error(driver.loc_, "Bad quote in \"" + raw + "\"");
            break;
        case '\\':
            ++pos;
            if (pos >= len) {
                /* impossible condition */
                driver.error(driver.loc_, "Overflow escape in \"" + raw + "\"");
            }
            c = raw[pos];
            switch (c) {
            case '"':
            case '\\':
            case '/':
                decoded.push_back(c);
                break;
            case 'b':
                decoded.push_back('\b');
                break;
            case 'f':
                decoded.push_back('\f');
                break;
            case 'n':
                decoded.push_back('\n');
                break;
            case 'r':
                decoded.push_back('\r');
                break;
            case 't':
                decoded.push_back('\t');
                break;
            case 'u':
                /* support only \u0000 to \u00ff */
                ++pos;
                if (pos + 4 > len) {
                    /* impossible condition */
                    driver.error(driver.loc_,
                                 "Overflow unicode escape in \"" + raw + "\"");
                }
                if ((raw[pos] != '0') || (raw[pos + 1] != '0')) {
                    driver.error(driver.loc_, "Unsupported unicode escape in \"" + raw + "\"");
                }
                pos += 2;
                c = raw[pos];
                if ((c >= '0') && (c <= '9')) {
                    b = (c - '0') << 4;
                } else if ((c >= 'A') && (c <= 'F')) {
                    b = (c - 'A' + 10) << 4;
                } else if ((c >= 'a') && (c <= 'f')) {
                    b = (c - 'a' + 10) << 4;
                } else {
                    /* impossible condition */
                    driver.error(driver.loc_, "Not hexadecimal in unicode escape in \"" + raw + "\"");
                }
                pos++;
                c = raw[pos];
                if ((c >= '0') && (c <= '9')) {
                    b |= c - '0';
                } else if ((c >= 'A') && (c <= 'F')) {
                    b |= c - 'A' + 10;
                } else if ((c >= 'a') && (c <= 'f')) {
                    b |= c - 'a' + 10;
                } else {
                    /* impossible condition */
                    driver.error(driver.loc_, "Not hexadecimal in unicode escape in \"" + raw + "\"");
                }
                decoded.push_back(static_cast<char>(b & 0xff));
                break;
            default:
                /* impossible condition */
                driver.error(driver.loc_, "Bad escape in \"" + raw + "\"");
            }
            break;
        default:
            if ((c >= 0) && (c < 0x20)) {
                /* impossible condition */
                driver.error(driver.loc_, "Invalid control in \"" + raw + "\"");
            }
            decoded.push_back(c);
        }
    }

    return isc::dhcp::Dhcp6Parser::make_STRING(decoded, driver.loc_);
}

\"{JSONStringCharacter}*{ControlCharacter}{ControlCharacterFill}*\" {
    /* Bad string with a forbidden control character inside */
    driver.error(driver.loc_, "Invalid control in " + std::string(yytext));
}

\"{JSONStringCharacter}*\\{BadJSONEscapeSequence}[^\x00-\x1f"]*\" {
    /* Bad string with a bad escape inside */
    driver.error(driver.loc_, "Bad escape in " + std::string(yytext));
}

\"{JSONStringCharacter}*\\\" {
    /* Bad string with an open escape at the end */
    driver.error(driver.loc_, "Overflow escape in " + std::string(yytext));
}

"["    { return isc::dhcp::Dhcp6Parser::make_LSQUARE_BRACKET(driver.loc_); }
"]"    { return isc::dhcp::Dhcp6Parser::make_RSQUARE_BRACKET(driver.loc_); }
"{"    { return isc::dhcp::Dhcp6Parser::make_LCURLY_BRACKET(driver.loc_); }
"}"    { return isc::dhcp::Dhcp6Parser::make_RCURLY_BRACKET(driver.loc_); }
","    { return isc::dhcp::Dhcp6Parser::make_COMMA(driver.loc_); }
":"    { return isc::dhcp::Dhcp6Parser::make_COLON(driver.loc_); }

{int} {
    /* An integer was found. */
    std::string tmp(yytext);
    int64_t integer = 0;
    try {
        /* In substring we want to use negative values (e.g. -1).
           In enterprise-id we need to use values up to 0xffffffff.
           To cover both of those use cases, we need at least
           int64_t. */
        integer = boost::lexical_cast<int64_t>(tmp);
    } catch (const boost::bad_lexical_cast &) {
        driver.error(driver.loc_, "Failed to convert " + tmp + " to an integer.");
    }

    /* The parser needs the string form as double conversion is no lossless */
    return isc::dhcp::Dhcp6Parser::make_INTEGER(integer, driver.loc_);
}

[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)? {
    /* A floating point was found. */
    std::string tmp(yytext);
    double fp = 0.0;
    try {
        fp = boost::lexical_cast<double>(tmp);
    } catch (const boost::bad_lexical_cast &) {
        driver.error(driver.loc_, "Failed to convert " + tmp + " to a floating point.");
    }

    return isc::dhcp::Dhcp6Parser::make_FLOAT(fp, driver.loc_);
}

true|false {
    string tmp(yytext);
    return isc::dhcp::Dhcp6Parser::make_BOOLEAN(tmp == "true", driver.loc_);
}

null {
   return isc::dhcp::Dhcp6Parser::make_NULL_TYPE(driver.loc_);
}

(?i:true) driver.error (driver.loc_, "JSON true reserved keyword is lower case only");

(?i:false) driver.error (driver.loc_, "JSON false reserved keyword is lower case only");

(?i:null) driver.error (driver.loc_, "JSON null reserved keyword is lower case only");

<*>.   driver.error (driver.loc_, "Invalid character: " + std::string(yytext));

<<EOF>> {
    if (driver.states_.empty()) {
        return isc::dhcp::Dhcp6Parser::make_END(driver.loc_);
    }
    driver.loc_ = driver.locs_.back();
    driver.locs_.pop_back();
    driver.file_ = driver.files_.back();
    driver.files_.pop_back();
    if (driver.sfile_) {
        fclose(driver.sfile_);
        driver.sfile_ = 0;
    }
    if (!driver.sfiles_.empty()) {
        driver.sfile_ = driver.sfiles_.back();
        driver.sfiles_.pop_back();
    }
    parser6__delete_buffer(YY_CURRENT_BUFFER);
    parser6__switch_to_buffer(driver.states_.back());
    driver.states_.pop_back();

    BEGIN(DIR_EXIT);
}

%%

using namespace isc::dhcp;

void
Parser6Context::scanStringBegin(const std::string& str, ParserType parser_type)
{
    start_token_flag = true;
    start_token_value = parser_type;

    file_ = "<string>";
    sfile_ = 0;
    loc_.initialize(&file_);
    yy_flex_debug = trace_scanning_;
    YY_BUFFER_STATE buffer;
    buffer = parser6__scan_bytes(str.c_str(), str.size());
    if (!buffer) {
        fatal("cannot scan string");
        /* fatal() throws an exception so this can't be reached */
    }
}

void
Parser6Context::scanFileBegin(FILE * f,
                              const std::string& filename,
                              ParserType parser_type)
{
    start_token_flag = true;
    start_token_value = parser_type;

    file_ = filename;
    sfile_ = f;
    loc_.initialize(&file_);
    yy_flex_debug = trace_scanning_;
    YY_BUFFER_STATE buffer;

    /* See dhcp6_lexer.cc header for available definitions */
    buffer = parser6__create_buffer(f, 65536 /*buffer size*/);
    if (!buffer) {
        fatal("cannot scan file " + filename);
    }
    parser6__switch_to_buffer(buffer);
}

void
Parser6Context::scanEnd() {
    if (sfile_)
        fclose(sfile_);
    sfile_ = 0;
    static_cast<void>(parser6_lex_destroy());
    /* Close files */
    while (!sfiles_.empty()) {
        FILE* f = sfiles_.back();
        if (f) {
            fclose(f);
        }
        sfiles_.pop_back();
    }
    /* Delete states */
    while (!states_.empty()) {
        parser6__delete_buffer(states_.back());
        states_.pop_back();
    }
}

void
Parser6Context::includeFile(const std::string& filename) {
    if (states_.size() > 10) {
        fatal("Too many nested include.");
    }

    FILE* f = fopen(filename.c_str(), "r");
    if (!f) {
        fatal("Can't open include file " + filename);
    }
    if (sfile_) {
        sfiles_.push_back(sfile_);
    }
    sfile_ = f;
    states_.push_back(YY_CURRENT_BUFFER);
    YY_BUFFER_STATE buffer;
    buffer = parser6__create_buffer(f, 65536 /*buffer size*/);
    if (!buffer) {
        fatal( "Can't scan include file " + filename);
    }
    parser6__switch_to_buffer(buffer);
    files_.push_back(file_);
    file_ = filename;
    locs_.push_back(loc_);
    loc_.initialize(&file_);

    BEGIN(INITIAL);
}

namespace {
/** To avoid unused function error */
class Dummy {
    /* cppcheck-suppress unusedPrivateFunction */
    void dummy() { yy_fatal_error("Fix me: how to disable its definition?"); }
};
}
#endif /* !__clang_analyzer__ */
