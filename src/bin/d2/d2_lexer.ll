/* Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%{ /* -*- C++ -*- */

/* Generated files do not make clang static analyser so happy */
#ifndef __clang_analyzer__

#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <d2/parser_context.h>
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

isc::d2::D2ParserContext::ParserType start_token_value;
unsigned int comment_start_line = 0;

};

/* To avoid the call to exit... oops! */
#define YY_FATAL_ERROR(msg) isc::d2::D2ParserContext::fatal(msg)
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

BadUnicodeEscapeSequence        u[0-9A-Fa-f]{0,3}[^0-9A-Fa-f"]
BadJSONEscapeSequence           [^"\\/bfnrtu]|{BadUnicodeEscapeSequence}
ControlCharacter                [\x00-\x1f]
ControlCharacterFill            [^"\\]|\\["\\/bfnrtu]

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
        case D2ParserContext::PARSER_JSON:
        default:
            return isc::d2::D2Parser::make_TOPLEVEL_JSON(driver.loc_);
        case D2ParserContext::PARSER_DHCPDDNS:
            return isc::d2::D2Parser::make_TOPLEVEL_DHCPDDNS(driver.loc_);
        case D2ParserContext::PARSER_SUB_DHCPDDNS:
            return isc::d2::D2Parser::make_SUB_DHCPDDNS(driver.loc_);
        case D2ParserContext::PARSER_TSIG_KEY:
            return isc::d2::D2Parser::make_SUB_TSIG_KEY(driver.loc_);
        case D2ParserContext::PARSER_TSIG_KEYS:
            return isc::d2::D2Parser::make_SUB_TSIG_KEYS(driver.loc_);
        case D2ParserContext::PARSER_DDNS_DOMAIN:
            return isc::d2::D2Parser::make_SUB_DDNS_DOMAIN(driver.loc_);
        case D2ParserContext::PARSER_DDNS_DOMAINS:
            return isc::d2::D2Parser::make_SUB_DDNS_DOMAINS(driver.loc_);
        case D2ParserContext::PARSER_DNS_SERVER:
            return isc::d2::D2Parser::make_SUB_DNS_SERVER(driver.loc_);
        case D2ParserContext::PARSER_HOOKS_LIBRARY:
            return isc::d2::D2Parser::make_SUB_HOOKS_LIBRARY(driver.loc_);
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
    isc_throw(D2ParseError, "Comment not closed. (/* in line " << comment_start_line);
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
    isc_throw(D2ParseError, "Directive not closed.");
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

\"DhcpDdns\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONFIG:
        return isc::d2::D2Parser::make_DHCPDDNS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("DhcpDdns", driver.loc_);
    }
}

\"ip-address\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
    case isc::d2::D2ParserContext::DNS_SERVER:
    case isc::d2::D2ParserContext::DNS_SERVERS:
        return isc::d2::D2Parser::make_IP_ADDRESS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("ip-address", driver.loc_);
    }
}

\"port\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
    case isc::d2::D2ParserContext::DNS_SERVER:
    case isc::d2::D2ParserContext::DNS_SERVERS:
        return isc::d2::D2Parser::make_PORT(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("port", driver.loc_);
    }
}

\"dns-server-timeout\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_DNS_SERVER_TIMEOUT(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("dns-server-timeout", driver.loc_);
    }
}

\"ncr-protocol\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_NCR_PROTOCOL(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("ncr-protocol", driver.loc_);
    }
}

\"ncr-format\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_NCR_FORMAT(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("ncr-format", driver.loc_);
    }
}

(?i:\"UDP\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::d2::D2ParserContext::NCR_PROTOCOL) {
        return isc::d2::D2Parser::make_UDP(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::d2::D2Parser::make_STRING(tmp, driver.loc_);
}

(?i:\"TCP\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::d2::D2ParserContext::NCR_PROTOCOL) {
        return isc::d2::D2Parser::make_TCP(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::d2::D2Parser::make_STRING(tmp, driver.loc_);
}

(?i:\"JSON\") {
    /* dhcp-ddns value keywords are case insensitive */
    if (driver.ctx_ == isc::d2::D2ParserContext::NCR_FORMAT) {
        return isc::d2::D2Parser::make_JSON(driver.loc_);
    }
    std::string tmp(yytext+1);
    tmp.resize(tmp.size() - 1);
    return isc::d2::D2Parser::make_STRING(tmp, driver.loc_);
}

\"user-context\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
    case isc::d2::D2ParserContext::DDNS_DOMAIN:
    case isc::d2::D2ParserContext::DDNS_DOMAINS:
    case isc::d2::D2ParserContext::DNS_SERVER:
    case isc::d2::D2ParserContext::DNS_SERVERS:
    case isc::d2::D2ParserContext::TSIG_KEY:
    case isc::d2::D2ParserContext::TSIG_KEYS:
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
    case isc::d2::D2ParserContext::AUTHENTICATION:
    case isc::d2::D2ParserContext::CLIENTS:
    case isc::d2::D2ParserContext::LOGGERS:
        return isc::d2::D2Parser::make_USER_CONTEXT(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("user-context", driver.loc_);
    }
}

\"comment\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
    case isc::d2::D2ParserContext::DDNS_DOMAIN:
    case isc::d2::D2ParserContext::DDNS_DOMAINS:
    case isc::d2::D2ParserContext::DNS_SERVER:
    case isc::d2::D2ParserContext::DNS_SERVERS:
    case isc::d2::D2ParserContext::TSIG_KEY:
    case isc::d2::D2ParserContext::TSIG_KEYS:
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
    case isc::d2::D2ParserContext::AUTHENTICATION:
    case isc::d2::D2ParserContext::CLIENTS:
    case isc::d2::D2ParserContext::LOGGERS:
        return isc::d2::D2Parser::make_COMMENT(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("comment", driver.loc_);
    }
}

\"forward-ddns\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_FORWARD_DDNS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("forward-ddns", driver.loc_);
    }
}

\"reverse-ddns\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_REVERSE_DDNS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("reverse-ddns", driver.loc_);
    }
}

\"ddns-domains\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::FORWARD_DDNS:
    case isc::d2::D2ParserContext::REVERSE_DDNS:
        return isc::d2::D2Parser::make_DDNS_DOMAINS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("ddns-domains", driver.loc_);
    }
}

\"key-name\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DDNS_DOMAIN:
    case isc::d2::D2ParserContext::DDNS_DOMAINS:
    case isc::d2::D2ParserContext::DNS_SERVER:
    case isc::d2::D2ParserContext::DNS_SERVERS:
        return isc::d2::D2Parser::make_KEY_NAME(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("key-name", driver.loc_);
    }
}

\"dns-servers\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DDNS_DOMAIN:
    case isc::d2::D2ParserContext::DDNS_DOMAINS:
        return isc::d2::D2Parser::make_DNS_SERVERS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("dns-servers", driver.loc_);
    }
}

\"hostname\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DNS_SERVER:
    case isc::d2::D2ParserContext::DNS_SERVERS:
        return isc::d2::D2Parser::make_HOSTNAME(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("hostname", driver.loc_);
    }
}


\"tsig-keys\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_TSIG_KEYS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("tsig-keys", driver.loc_);
    }
}

\"algorithm\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::TSIG_KEY:
    case isc::d2::D2ParserContext::TSIG_KEYS:
        return isc::d2::D2Parser::make_ALGORITHM(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("algorithm", driver.loc_);
    }
}

\"digest-bits\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::TSIG_KEY:
    case isc::d2::D2ParserContext::TSIG_KEYS:
        return isc::d2::D2Parser::make_DIGEST_BITS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("digest-bits", driver.loc_);
    }
}

\"secret\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::TSIG_KEY:
    case isc::d2::D2ParserContext::TSIG_KEYS:
        return isc::d2::D2Parser::make_SECRET(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("secret", driver.loc_);
    }
}

\"secret-file\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::TSIG_KEY:
    case isc::d2::D2ParserContext::TSIG_KEYS:
        return isc::d2::D2Parser::make_SECRET_FILE(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("secret-file", driver.loc_);
    }
}

\"control-socket\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_CONTROL_SOCKET(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("control-socket", driver.loc_);
    }
}

\"control-sockets\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_CONTROL_SOCKETS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("control-sockets", driver.loc_);
    }
}

\"socket-type\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
        return isc::d2::D2Parser::make_SOCKET_TYPE(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("socket-type", driver.loc_);
    }
}

\"unix\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET_TYPE:
        return isc::d2::D2Parser::make_UNIX(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("unix", driver.loc_);
    }
}

\"http\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET_TYPE:
        return isc::d2::D2Parser::make_HTTP(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("http", driver.loc_);
    }
}

\"https\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET_TYPE:
        return isc::d2::D2Parser::make_HTTPS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("https", driver.loc_);
    }
}

\"socket-name\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
        return isc::d2::D2Parser::make_SOCKET_NAME(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("socket-name", driver.loc_);
    }
}

\"socket-address\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
        return isc::d2::D2Parser::make_SOCKET_ADDRESS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("socket-address", driver.loc_);
    }
}

\"socket-port\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
        return isc::d2::D2Parser::make_SOCKET_PORT(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("socket-port", driver.loc_);
    }
}

\"authentication\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
        return isc::d2::D2Parser::make_AUTHENTICATION(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("authentication", driver.loc_);
    }
}

\"type\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::AUTHENTICATION:
        return isc::d2::D2Parser::make_TYPE(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("type", driver.loc_);
    }
}

\"basic\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::AUTH_TYPE:
        return isc::d2::D2Parser::make_BASIC(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("basic", driver.loc_);
    }
}

\"realm\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::AUTHENTICATION:
        return isc::d2::D2Parser::make_REALM(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("realm", driver.loc_);
    }
}

\"directory\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::AUTHENTICATION:
        return isc::d2::D2Parser::make_DIRECTORY(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("directory", driver.loc_);
    }
}

\"clients\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::AUTHENTICATION:
        return isc::d2::D2Parser::make_CLIENTS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("clients", driver.loc_);
    }
}

\"user\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CLIENTS:
        return isc::d2::D2Parser::make_USER(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("user", driver.loc_);
    }
}

\"user-file\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CLIENTS:
        return isc::d2::D2Parser::make_USER_FILE(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("user-file", driver.loc_);
    }
}

\"password\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CLIENTS:
        return isc::d2::D2Parser::make_PASSWORD(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("password", driver.loc_);
    }
}

\"password-file\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CLIENTS:
        return isc::d2::D2Parser::make_PASSWORD_FILE(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("password-file", driver.loc_);
    }
}

\"trust-anchor\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
        return isc::d2::D2Parser::make_TRUST_ANCHOR(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("trust-anchor", driver.loc_);
    }
}

\"cert-file\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
        return isc::d2::D2Parser::make_CERT_FILE(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("cert-file", driver.loc_);
    }
}

\"key-file\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
        return isc::d2::D2Parser::make_KEY_FILE(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("key-file", driver.loc_);
    }
}

\"cert-required\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::CONTROL_SOCKET:
        return isc::d2::D2Parser::make_CERT_REQUIRED(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("cert-required", driver.loc_);
    }
}

\"hooks-libraries\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_HOOKS_LIBRARIES(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("hooks-libraries", driver.loc_);
    }
}

\"parameters\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::HOOKS_LIBRARIES:
        return isc::d2::D2Parser::make_PARAMETERS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("parameters", driver.loc_);
    }
}

\"library\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::HOOKS_LIBRARIES:
        return isc::d2::D2Parser::make_LIBRARY(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("library", driver.loc_);
    }
}

\"loggers\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::DHCPDDNS:
        return isc::d2::D2Parser::make_LOGGERS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("loggers", driver.loc_);
    }
}

\"output_options\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::LOGGERS:
        return isc::d2::D2Parser::make_OUTPUT_OPTIONS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("output_options", driver.loc_);
    }
}

\"output-options\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::LOGGERS:
        return isc::d2::D2Parser::make_OUTPUT_OPTIONS(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("output-options", driver.loc_);
    }
}

\"output\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::OUTPUT_OPTIONS:
        return isc::d2::D2Parser::make_OUTPUT(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("output", driver.loc_);
    }
}

\"flush\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::OUTPUT_OPTIONS:
        return isc::d2::D2Parser::make_FLUSH(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("flush", driver.loc_);
    }
}

\"maxsize\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::OUTPUT_OPTIONS:
        return isc::d2::D2Parser::make_MAXSIZE(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("maxsize", driver.loc_);
    }
}

\"maxver\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::OUTPUT_OPTIONS:
        return isc::d2::D2Parser::make_MAXVER(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("maxver", driver.loc_);
    }
}

\"pattern\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::OUTPUT_OPTIONS:
        return isc::d2::D2Parser::make_PATTERN(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("pattern", driver.loc_);
    }
}

\"name\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::LOGGERS:
    case isc::d2::D2ParserContext::TSIG_KEY:
    case isc::d2::D2ParserContext::TSIG_KEYS:
    case isc::d2::D2ParserContext::DDNS_DOMAIN:
    case isc::d2::D2ParserContext::DDNS_DOMAINS:
        return isc::d2::D2Parser::make_NAME(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("name", driver.loc_);
    }
}

\"debuglevel\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::LOGGERS:
        return isc::d2::D2Parser::make_DEBUGLEVEL(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("debuglevel", driver.loc_);
    }
}

\"severity\" {
    switch(driver.ctx_) {
    case isc::d2::D2ParserContext::LOGGERS:
        return isc::d2::D2Parser::make_SEVERITY(driver.loc_);
    default:
        return isc::d2::D2Parser::make_STRING("severity", driver.loc_);
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
                    driver.error(driver.loc_,
                    "Unsupported unicode escape in \"" + raw + "\"",
                    pos + 1);
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

    return isc::d2::D2Parser::make_STRING(decoded, driver.loc_);
}

\"{JSONStringCharacter}*{ControlCharacter}{ControlCharacterFill}*\" {
    /* Bad string with a forbidden control character inside */
    std::string raw(yytext+1);
    size_t len = raw.size() - 1;
    size_t pos = 0;
    for (; pos < len; ++pos) {
        char c = raw[pos];
        if ((c >= 0) && (c < 0x20)) {
            break;
        }
    }
    driver.error(driver.loc_,
                 "Invalid control in " + std::string(yytext),
                 pos + 1);
}

\"{JSONStringCharacter}*\\{BadJSONEscapeSequence}[^"]*\" {
    /* Bad string with a bad escape inside */
    std::string raw(yytext+1);
    size_t len = raw.size() - 1;
    size_t pos = 0;
    bool found = false;
    for (; pos < len; ++pos) {
        if (found) {
            break;
        }
        char c = raw[pos];
        if (c == '\\') {
            ++pos;
            c = raw[pos];
            switch (c) {
            case '"':
            case '\\':
            case '/':
            case 'b':
            case 'f':
            case 'n':
            case 'r':
            case 't':
                break;
            case 'u':
                if ((pos + 4 > len) ||
                    !std::isxdigit(raw[pos + 1]) ||
                    !std::isxdigit(raw[pos + 2]) ||
                    !std::isxdigit(raw[pos + 3]) ||
                    !std::isxdigit(raw[pos + 4])) {
                    found = true;
                }
                break;
            default:
                found = true;
                break;
            }
        }
    }
    /* The rule stops on the first " including on \" so add ... in this case */
    std::string trailer = "";
    if (raw[len - 1] == '\\') {
        trailer = "...";
    }
    driver.error(driver.loc_,
                 "Bad escape in " + std::string(yytext) + trailer,
                 pos);
}

\"{JSONStringCharacter}*\\\" {
    /* Bad string with an open escape at the end */
    std::string raw(yytext+1);
    driver.error(driver.loc_,
                 "Overflow escape in " + std::string(yytext),
                 raw.size() + 1);
}

\"{JSONStringCharacter}*\\u[0-9A-Fa-f]{0,3}\" {
    /* Bad string with an open unicode escape at the end */
    std::string raw(yytext+1);
    size_t pos = raw.size() - 1;
    for (; pos > 0; --pos) {
        char c = raw[pos];
        if (c == 'u') {
            break;
        }
    }
    driver.error(driver.loc_,
                 "Overflow unicode escape in " + std::string(yytext),
                 pos + 1);
}

"["    { return isc::d2::D2Parser::make_LSQUARE_BRACKET(driver.loc_); }
"]"    { return isc::d2::D2Parser::make_RSQUARE_BRACKET(driver.loc_); }
"{"    { return isc::d2::D2Parser::make_LCURLY_BRACKET(driver.loc_); }
"}"    { return isc::d2::D2Parser::make_RCURLY_BRACKET(driver.loc_); }
","    { return isc::d2::D2Parser::make_COMMA(driver.loc_); }
":"    { return isc::d2::D2Parser::make_COLON(driver.loc_); }

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
    return isc::d2::D2Parser::make_INTEGER(integer, driver.loc_);
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

    return isc::d2::D2Parser::make_FLOAT(fp, driver.loc_);
}

true|false {
    string tmp(yytext);
    return isc::d2::D2Parser::make_BOOLEAN(tmp == "true", driver.loc_);
}

null {
   return isc::d2::D2Parser::make_NULL_TYPE(driver.loc_);
}

(?i:true) driver.error (driver.loc_, "JSON true reserved keyword is lower case only");

(?i:false) driver.error (driver.loc_, "JSON false reserved keyword is lower case only");

(?i:null) driver.error (driver.loc_, "JSON null reserved keyword is lower case only");

<*>.   driver.error (driver.loc_, "Invalid character: " + std::string(yytext));

<<EOF>> {
    if (driver.states_.empty()) {
        return isc::d2::D2Parser::make_END(driver.loc_);
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
    d2_parser__delete_buffer(YY_CURRENT_BUFFER);
    d2_parser__switch_to_buffer(driver.states_.back());
    driver.states_.pop_back();

    BEGIN(DIR_EXIT);
}

%%

using namespace isc::dhcp;

void
D2ParserContext::scanStringBegin(const std::string& str, ParserType parser_type)
{
    start_token_flag = true;
    start_token_value = parser_type;

    file_ = "<string>";
    sfile_ = 0;
    loc_.initialize(&file_);
    yy_flex_debug = trace_scanning_;
    YY_BUFFER_STATE buffer;
    buffer = d2_parser__scan_bytes(str.c_str(), str.size());
    if (!buffer) {
        fatal("cannot scan string");
        /* fatal() throws an exception so this can't be reached */
    }
}

void
D2ParserContext::scanFileBegin(FILE * f,
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

    /* See d2_lexer.cc header for available definitions */
    buffer = d2_parser__create_buffer(f, 65536 /*buffer size*/);
    if (!buffer) {
        fatal("cannot scan file " + filename);
    }
    d2_parser__switch_to_buffer(buffer);
}

void
D2ParserContext::scanEnd() {
    if (sfile_)
        fclose(sfile_);
    sfile_ = 0;
    static_cast<void>(d2_parser_lex_destroy());
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
        d2_parser__delete_buffer(states_.back());
        states_.pop_back();
    }
}

void
D2ParserContext::includeFile(const std::string& filename) {
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
    buffer = d2_parser__create_buffer(f, 65536 /*buffer size*/);
    if (!buffer) {
        fatal( "Can't scan include file " + filename);
    }
    d2_parser__switch_to_buffer(buffer);
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
