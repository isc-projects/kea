// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PARSER_CONTEXT_H
#define PARSER_CONTEXT_H
#include <string>
#include <map>
#include <vector>
#include <dhcp6/dhcp6_parser.h>
#include <dhcp6/parser_context_decl.h>
#include <exceptions/exceptions.h>

// Tell Flex the lexer's prototype ...
#define YY_DECL isc::dhcp::Dhcp6Parser::symbol_type parser6_lex (Parser6Context& driver)

// ... and declare it for the parser's sake.
YY_DECL;

namespace isc {
namespace dhcp {

/// @brief Evaluation error exception raised when trying to parse an axceptions.
class EvalParseError : public isc::Exception {
public:
    EvalParseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Evaluation context, an interface to the expression evaluation.
class Parser6Context
{
public:

    /// @brief Defines currently support the content supported
    typedef enum {
        PARSER_GENERIC_JSON, // This will parse the content as generic JSON
        PARSER_DHCP6 // This will parse the content as DHCP6 config
    } ParserType;

    /// @brief Default constructor.
    Parser6Context();

    /// @brief destructor
    virtual ~Parser6Context();

    /// @brief JSON elements being parsed.
    std::vector<isc::data::ElementPtr> stack_;

    /// @brief Method called before scanning starts on a string.
    void scanStringBegin(const std::string& str, ParserType type);

    /// @brief Method called after the last tokens are scanned from a string.
    void scanStringEnd();

    /// @brief Method called before scanning starts on a file.
    void scanFileBegin(FILE * f, const std::string& filename, ParserType type);

    /// @brief Method called after the last tokens are scanned from a file.
    void scanFileEnd(FILE * f);

    /// @brief Divert input to an include file.
    void includeFile(const std::string& filename);

    /// @brief Run the parser on the string specified.
    ///
    /// @param str string to be parsed
    /// @param parser_type specifies expected content (either DHCP6 or generic JSON)
    /// @return true on success.
    isc::data::ConstElementPtr parseString(const std::string& str,
                                           ParserType parser_type);

    /// @brief Run the parser on the file specified.
    isc::data::ConstElementPtr parseFile(const std::string& filename,
                                         ParserType parser_type);

    /// @brief Error handler
    ///
    /// @param loc location within the parsed file when experienced a problem.
    /// @param what string explaining the nature of the error.
    void error(const isc::dhcp::location& loc, const std::string& what);

    /// @brief Error handler
    ///
    /// This is a simplified error reporting tool for possible future
    /// cases when the EvalParser is not able to handle the packet.
    void error(const std::string& what);

    /// @brief Fatal error handler
    ///
    /// This is for should not happen but fatal errors.
    /// Used by YY_FATAL_ERROR macro so required to be static.
    static void fatal(const std::string& what);

    /// @brief Defines syntactic contexts for lexical tie-ins
    typedef enum {
        /// at toplevel
        NO_KEYWORD,
        CONFIG,
        /// in config
        DHCP6,
        // not yet DHCP4,
        // not yet DHCP_DDNS,
        LOGGING,
        /// Dhcp6
        INTERFACES_CONFIG,
        DATABASE,
        MAC_SOURCES,
        HOST_RESERVATION_IDENTIFIERS,
        HOOKS_LIBRARIES,
        SUBNET6,
        OPTION_DATA,
        CLIENT_CLASSES,
        SERVER_ID,
        DHCP_DDNS,
        /// subnet6
        POOLS,
        PD_POOLS,
        RESERVATIONS,
        /// client-classes
        CLIENT_CLASS,
        /// Logging
        LOGGERS,
        /// loggers
        OUTPUT_OPTIONS
    } ParserContext;    

    /// @brief Current syntactic context
    ParserContext ctx_;

    /// @brief Enter a new syntactic context
    void enter(const ParserContext& ctx);

    /// @brief Leave a syntactic context
    /// @throw isc::Unexpected if unbalanced
    void leave();

 private:
    /// @brief Flag determining scanner debugging.
    bool trace_scanning_;

    /// @brief Flag determing parser debugging.
    bool trace_parsing_;

    /// @brief Syntactic context stack
    std::vector<ParserContext> cstack_;
};

}; // end of isc::eval namespace
}; // end of isc namespace

#endif
