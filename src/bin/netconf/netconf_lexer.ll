/* Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%{ /* -*- C++ -*- */

/* Generated files do not make clang static analyser so happy */
#ifndef __clang_analyzer__

#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <netconf/parser_context.h>
#include <asiolink/io_address.h>
#include <boost/lexical_cast.hpp>
#include <exceptions/exceptions.h>
#include <cc/dhcp_config_error.h>

/* Please avoid C++ style comments (// ... eol) as they break flex 2.6.2 */

/* Work around an incompatibility in flex (at least versions
   2.5.31 through 2.5.33): it generates code that does
   not conform to C89.  See Debian bug 333231
   <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>. */
# undef yywrap
# define yywrap() 1

namespace {

bool start_token_flag = false;

isc::netconf::ParserContext::ParserType start_token_value;
unsigned int comment_start_line = 0;

using namespace isc;
using isc::netconf::NetconfParser;

};

/* To avoid the call to exit... oops! */
#define YY_FATAL_ERROR(msg) isc::netconf::ParserContext::fatal(msg)
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

    /* We currently have 3 points of entries defined:
       START_JSON - which expects any valid JSON
       START_NETCONF - which expects full configuration (with outer map and Netconf
                     object in it.
       START_SUB_NETCONF - which expects only content of the Netconf, this is
                         primarily useful for testing. */
    if (start_token_flag) {
        start_token_flag = false;
        switch (start_token_value) {
        case ParserContext::PARSER_JSON:
        default:
            return NetconfParser::make_START_JSON(driver.loc_);
        case ParserContext::PARSER_NETCONF:
            return NetconfParser::make_START_NETCONF(driver.loc_);
        case ParserContext::PARSER_SUB_NETCONF:
            return NetconfParser::make_START_SUB_NETCONF(driver.loc_);
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
    isc_throw(ParseError, "Comment not closed. (/* in line " << comment_start_line);
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
    isc_throw(ParseError, "Directive not closed.");
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


\"Netconf\" {
    switch(driver.ctx_) {
    case ParserContext::CONFIG:
        return NetconfParser::make_NETCONF(driver.loc_);
    default:
        return NetconfParser::make_STRING("Netconf", driver.loc_);
    }
}

\"user-context\" {
    switch(driver.ctx_) {
    case ParserContext::NETCONF:
    case ParserContext::SERVER:
    case ParserContext::CONTROL_SOCKET:
    case ParserContext::LOGGERS:
        return NetconfParser::make_USER_CONTEXT(driver.loc_);
    default:
        return NetconfParser::make_STRING("user-context", driver.loc_);
    }
}

\"comment\" {
    switch(driver.ctx_) {
    case ParserContext::NETCONF:
    case ParserContext::SERVER:
    case ParserContext::CONTROL_SOCKET:
    case ParserContext::LOGGERS:
        return NetconfParser::make_COMMENT(driver.loc_);
    default:
        return NetconfParser::make_STRING("comment", driver.loc_);
    }
}

\"boot-update\" {
    switch(driver.ctx_) {
    case ParserContext::NETCONF:
    case ParserContext::SERVER:
        return NetconfParser::make_BOOT_UPDATE(driver.loc_);
    default:
        return NetconfParser::make_STRING("boot-update", driver.loc_);
    }
}

\"subscribe-changes\" {
    switch(driver.ctx_) {
    case ParserContext::NETCONF:
    case ParserContext::SERVER:
        return NetconfParser::make_SUBSCRIBE_CHANGES(driver.loc_);
    default:
        return NetconfParser::make_STRING("subscribe-changes", driver.loc_);
    }
}

\"validate-changes\" {
    switch(driver.ctx_) {
    case ParserContext::NETCONF:
    case ParserContext::SERVER:
        return NetconfParser::make_VALIDATE_CHANGES(driver.loc_);
    default:
        return NetconfParser::make_STRING("validate-changes", driver.loc_);
    }
}

\"managed-servers\" {
    switch(driver.ctx_) {
    case ParserContext::NETCONF:
        return NetconfParser::make_MANAGED_SERVERS(driver.loc_);
    default:
        return NetconfParser::make_STRING("managed-servers", driver.loc_);
    }
}

\"dhcp4\" {
    switch(driver.ctx_) {
    case ParserContext::MANAGED_SERVERS:
        return NetconfParser::make_DHCP4_SERVER(driver.loc_);
    default:
        return NetconfParser::make_STRING("dhcp4", driver.loc_);
    }
}

\"dhcp6\" {
    switch(driver.ctx_) {
    case ParserContext::MANAGED_SERVERS:
        return NetconfParser::make_DHCP6_SERVER(driver.loc_);
    default:
        return NetconfParser::make_STRING("dhcp6", driver.loc_);
    }
}

\"d2\" {
    switch(driver.ctx_) {
    case ParserContext::MANAGED_SERVERS:
        return NetconfParser::make_D2_SERVER(driver.loc_);
    default:
        return NetconfParser::make_STRING("d2", driver.loc_);
    }
}

\"ca\" {
    switch(driver.ctx_) {
    case ParserContext::MANAGED_SERVERS:
        return NetconfParser::make_CA_SERVER(driver.loc_);
    default:
        return NetconfParser::make_STRING("ca", driver.loc_);
    }
}

\"model\" {
    switch(driver.ctx_) {
    case ParserContext::SERVER:
        return NetconfParser::make_MODEL(driver.loc_);
    default:
        return NetconfParser::make_STRING("model", driver.loc_);
    }
}

\"control-socket\" {
    switch(driver.ctx_) {
    case ParserContext::SERVER:
        return NetconfParser::make_CONTROL_SOCKET(driver.loc_);
    default:
        return NetconfParser::make_STRING("control-socket", driver.loc_);
    }
}

\"unix\" {
    switch(driver.ctx_) {
    case ParserContext::SOCKET_TYPE:
        return NetconfParser::make_UNIX(driver.loc_);
    default:
        return NetconfParser::make_STRING("unix", driver.loc_);
    }
}

\"http\" {
    switch(driver.ctx_) {
    case ParserContext::SOCKET_TYPE:
        return NetconfParser::make_HTTP(driver.loc_);
    default:
        return NetconfParser::make_STRING("http", driver.loc_);
    }
}

\"stdout\" {
    switch(driver.ctx_) {
    case ParserContext::SOCKET_TYPE:
        return NetconfParser::make_STDOUT(driver.loc_);
    default:
        return NetconfParser::make_STRING("stdout", driver.loc_);
    }
}

\"socket-type\" {
    switch(driver.ctx_) {
    case ParserContext::CONTROL_SOCKET:
        return NetconfParser::make_SOCKET_TYPE(driver.loc_);
    default:
        return NetconfParser::make_STRING("socket-type", driver.loc_);
    }
}

\"socket-name\" {
    switch(driver.ctx_) {
    case ParserContext::CONTROL_SOCKET:
        return NetconfParser::make_SOCKET_NAME(driver.loc_);
    default:
        return NetconfParser::make_STRING("socket-name", driver.loc_);
    }
}

\"socket-url\" {
    switch(driver.ctx_) {
    case ParserContext::CONTROL_SOCKET:
        return NetconfParser::make_SOCKET_URL(driver.loc_);
    default:
        return NetconfParser::make_STRING("socket-url", driver.loc_);
    }
}

\"hooks-libraries\" {
    switch(driver.ctx_) {
    case ParserContext::NETCONF:
        return NetconfParser::make_HOOKS_LIBRARIES(driver.loc_);
    default:
        return NetconfParser::make_STRING("hooks-libraries", driver.loc_);
    }
}

\"library\" {
    switch(driver.ctx_) {
    case ParserContext::HOOKS_LIBRARIES:
        return NetconfParser::make_LIBRARY(driver.loc_);
    default:
        return NetconfParser::make_STRING("library", driver.loc_);
    }
}

\"parameters\" {
    switch(driver.ctx_) {
    case ParserContext::HOOKS_LIBRARIES:
        return NetconfParser::make_PARAMETERS(driver.loc_);
    default:
        return NetconfParser::make_STRING("parameters", driver.loc_);
    }
}

\"loggers\" {
    switch(driver.ctx_) {
    case ParserContext::NETCONF:
        return NetconfParser::make_LOGGERS(driver.loc_);
    default:
        return NetconfParser::make_STRING("loggers", driver.loc_);
    }
}

\"name\" {
    switch(driver.ctx_) {
    case ParserContext::LOGGERS:
        return NetconfParser::make_NAME(driver.loc_);
    default:
        return NetconfParser::make_STRING("name", driver.loc_);
    }
}

\"output_options\" {
    switch(driver.ctx_) {
    case ParserContext::LOGGERS:
        return NetconfParser::make_OUTPUT_OPTIONS(driver.loc_);
    default:
        return NetconfParser::make_STRING("output_options", driver.loc_);
    }
}

\"output\" {
    switch(driver.ctx_) {
    case ParserContext::OUTPUT_OPTIONS:
        return NetconfParser::make_OUTPUT(driver.loc_);
    default:
        return NetconfParser::make_STRING("output", driver.loc_);
    }
}

\"flush\" {
    switch(driver.ctx_) {
    case ParserContext::OUTPUT_OPTIONS:
        return NetconfParser::make_FLUSH(driver.loc_);
    default:
        return NetconfParser::make_STRING("flush", driver.loc_);
    }
}

\"maxsize\" {
    switch(driver.ctx_) {
    case ParserContext::OUTPUT_OPTIONS:
        return NetconfParser::make_MAXSIZE(driver.loc_);
    default:
        return NetconfParser::make_STRING("maxsize", driver.loc_);
    }
}

\"maxver\" {
    switch(driver.ctx_) {
    case ParserContext::OUTPUT_OPTIONS:
        return NetconfParser::make_MAXVER(driver.loc_);
    default:
        return NetconfParser::make_STRING("maxver", driver.loc_);
    }
}

\"pattern\" {
    switch(driver.ctx_) {
    case ParserContext::OUTPUT_OPTIONS:
        return NetconfParser::make_PATTERN(driver.loc_);
    default:
        return NetconfParser::make_STRING("pattern", driver.loc_);
    }
}

\"debuglevel\" {
    switch(driver.ctx_) {
    case ParserContext::LOGGERS:
        return NetconfParser::make_DEBUGLEVEL(driver.loc_);
    default:
        return NetconfParser::make_STRING("debuglevel", driver.loc_);
    }
}

\"severity\" {
    switch(driver.ctx_) {
    case ParserContext::LOGGERS:
        return NetconfParser::make_SEVERITY(driver.loc_);
    default:
        return NetconfParser::make_STRING("severity", driver.loc_);
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

    return NetconfParser::make_STRING(decoded, driver.loc_);
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

"["    { return NetconfParser::make_LSQUARE_BRACKET(driver.loc_); }
"]"    { return NetconfParser::make_RSQUARE_BRACKET(driver.loc_); }
"{"    { return NetconfParser::make_LCURLY_BRACKET(driver.loc_); }
"}"    { return NetconfParser::make_RCURLY_BRACKET(driver.loc_); }
","    { return NetconfParser::make_COMMA(driver.loc_); }
":"    { return NetconfParser::make_COLON(driver.loc_); }

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
    return NetconfParser::make_INTEGER(integer, driver.loc_);
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

    return NetconfParser::make_FLOAT(fp, driver.loc_);
}

true|false {
    string tmp(yytext);
    return NetconfParser::make_BOOLEAN(tmp == "true", driver.loc_);
}

null {
   return NetconfParser::make_NULL_TYPE(driver.loc_);
}

(?i:true) driver.error (driver.loc_, "JSON true reserved keyword is lower case only");

(?i:false) driver.error (driver.loc_, "JSON false reserved keyword is lower case only");

(?i:null) driver.error (driver.loc_, "JSON null reserved keyword is lower case only");

<*>.   driver.error (driver.loc_, "Invalid character: " + std::string(yytext));

<<EOF>> {
    if (driver.states_.empty()) {
        return NetconfParser::make_END(driver.loc_);
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
    netconf__delete_buffer(YY_CURRENT_BUFFER);
    netconf__switch_to_buffer(driver.states_.back());
    driver.states_.pop_back();

    BEGIN(DIR_EXIT);
}

%%

using namespace isc::dhcp;

void
ParserContext::scanStringBegin(const std::string& str, ParserType parser_type)
{
    start_token_flag = true;
    start_token_value = parser_type;

    file_ = "<string>";
    sfile_ = 0;
    loc_.initialize(&file_);
    yy_flex_debug = trace_scanning_;
    YY_BUFFER_STATE buffer;
    buffer = netconf__scan_bytes(str.c_str(), str.size());
    if (!buffer) {
        fatal("cannot scan string");
        /* fatal() throws an exception so this can't be reached */
    }
}

void
ParserContext::scanFileBegin(FILE * f,
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

    /* See netconf_lexer.cc header for available definitions */
    buffer = netconf__create_buffer(f, 65536 /*buffer size*/);
    if (!buffer) {
        fatal("cannot scan file " + filename);
    }
    netconf__switch_to_buffer(buffer);
}

void
ParserContext::scanEnd() {
    if (sfile_)
        fclose(sfile_);
    sfile_ = 0;
    static_cast<void>(netconf_lex_destroy());
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
        netconf__delete_buffer(states_.back());
        states_.pop_back();
    }
}

void
ParserContext::includeFile(const std::string& filename) {
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
    buffer = netconf__create_buffer(f, 65536 /*buffer size*/);
    if (!buffer) {
        fatal( "Can't scan include file " + filename);
    }
    netconf__switch_to_buffer(buffer);
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
