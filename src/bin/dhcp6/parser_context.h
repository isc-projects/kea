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

/// @brief Evaluation error exception raised when trying to parse.
///
/// @todo: This probably should be common for Dhcp4 and Dhcp6.
class Dhcp6ParseError : public isc::Exception {
public:
    Dhcp6ParseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Evaluation context, an interface to the expression evaluation.
class Parser6Context
{
public:

    /// @brief Defines currently supported scopes
    ///
    /// Dhcp6Parser is able to parse several types of scope. Usually, when it
    /// parses a config file, it expects the data to have a map with Dhcp6 in it
    /// and all the parameters within that Dhcp6 map. However, sometimes the
    /// parser is expected to parse only a subset of that information. For example,
    /// it may be asked to parse a structure that is host-reservation only, without
    /// the global 'Dhcp6' or 'reservations' around it. In such case the parser
    /// is being told to start parsing as SUBPARSER_HOST_RESERVATION6.
    typedef enum {
        /// This parser will parse the content as generic JSON.
        //PARSER_GENERIC_JSON,

        SUBPARSER_JSON,

        /// This parser will parse the content as Dhcp6 config wrapped in a map (that's
        /// the regular config file)
        PARSER_DHCP6,

        /// This parser will parse the content of Dhcp6. It is mostly used
        /// in unit-tests as most of the unit-tests do not define the outer
        /// map and Dhcp6 entity, just the contents of it.
        SUBPARSER_DHCP6,

        /// This will parse the conde as Subnet6 content.
        PARSER_SUBNET6,

        /// This parser will parse pool6 content.
        PARSER_POOL6,

        /// This parser will parse the interfaces content.
        PARSER_INTERFACES,

        /// This parser will parse the content as pd-pool.
        PARSER_PD_POOL,

        /// This parser will parse the content as host-reservation
        PARSER_HOST_RESERVATION,

        /// This parser will parse the content as option definition.
        PARSER_OPTION_DEF,

        /// This parser will parse the content as option data.
        PARSER_OPTION_DATA,

        /// This parser will parse the content as hooks-library
        PARSER_HOOKS_LIBRARY
    } ParserType;

    /// @brief Default constructor.
    Parser6Context();

    /// @brief destructor
    virtual ~Parser6Context();

    /// @brief JSON elements being parsed.
    std::vector<isc::data::ElementPtr> stack_;

    /// @brief Method called before scanning starts on a string.
    void scanStringBegin(const std::string& str, ParserType type);

    /// @brief Method called before scanning starts on a file.
    void scanFileBegin(FILE * f, const std::string& filename, ParserType type);

    /// @brief Method called after the last tokens are scanned.
    void scanEnd();

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
    /// cases when the Dhcp6Parser is not able to handle the packet.
    void error(const std::string& what);

    /// @brief Fatal error handler
    ///
    /// This is for should not happen but fatal errors.
    /// Used by YY_FATAL_ERROR macro so required to be static.
    static void fatal(const std::string& what);

    /// @brief Converts bison's position to one understandable by isc::data::Element
    ///
    /// Convert a bison location into an element position
    /// (take the begin, the end is lost)
    isc::data::Element::Position loc2pos(isc::dhcp::location& loc);

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
        LEASE_DATABASE,
        HOSTS_DATABASE,
        MAC_SOURCES,
        HOST_RESERVATION_IDENTIFIERS,
        HOOKS_LIBRARIES,
        SUBNET6,
        OPTION_DEF,
        OPTION_DATA,
        CLIENT_CLASSES,
        SERVER_ID,
        CONTROL_SOCKET,
        /// subnet6
        POOLS,
        PD_POOLS,
        RESERVATIONS,
        RELAY,
        /// client-classes
        CLIENT_CLASS,
        /// Logging
        LOGGERS,
        /// loggers
        OUTPUT_OPTIONS
    } ParserContext;    

    /// @brief File name
    std::string file_;

    /// @brief File name stack
    std::vector<std::string> files_;

    /// @brief Location of the current token
    ///
    /// The lexer will keep updating it. This variable will be useful
    /// for logging errors.
    isc::dhcp::location loc_;

    /// @brief Location stack
    std::vector<isc::dhcp::location> locs_;

    /// @brief Lexer state stack
    std::vector<struct yy_buffer_state*> states_;

    /// @brief sFile (aka FILE)
    FILE* sfile_;

    /// @brief sFile (aka FILE) stack
    std::vector<FILE*> sfiles_;

    /// @brief Current syntactic context
    ParserContext ctx_;

    /// @brief Enter a new syntactic context
    void enter(const ParserContext& ctx);

    /// @brief Leave a syntactic context
    /// @throw isc::Unexpected if unbalanced
    void leave();

    /// @brief Get the syntactix context name
    const std::string context_name();

 private:
    /// @brief Flag determining scanner debugging.
    bool trace_scanning_;

    /// @brief Flag determing parser debugging.
    bool trace_parsing_;

    /// @brief Syntactic context stack
    std::vector<ParserContext> cstack_;

    /// @brief Common part of parseXXX
    isc::data::ConstElementPtr parseCommon();
};

}; // end of isc::eval namespace
}; // end of isc namespace

#endif
