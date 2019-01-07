// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
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
    /// Dhcp6Parser is able to parse several types of scope. Usually,
    /// when it parses a config file, it expects the data to have a map
    /// with Dhcp6 in it and all the parameters within that Dhcp6 map.
    /// However, sometimes the parser is expected to parse only a subset
    /// of that information. For example, it may be asked to parse
    /// a structure that is host-reservation only, without the global
    /// 'Dhcp6' or 'reservations' around it. In such case the parser
    /// is being told to start parsing as PARSER_HOST_RESERVATION6.
    typedef enum {
        /// This parser will parse the content as generic JSON.
        PARSER_JSON,

        /// This parser will parse the content as Dhcp6 config wrapped in a map
        /// (that's the regular config file)
        PARSER_DHCP6,

        /// This parser will parse the content of Dhcp6 (without outer { } and
        /// without "Dhcp6"). It is mostly used in unit-tests as most of the
        /// unit-tests do not define the outer map and Dhcp6 entity, just the
        /// contents of it.
        SUBPARSER_DHCP6,

        /// This will parse the input as interfaces content.
        PARSER_INTERFACES,

        /// This will parse the input as Subnet6 content.
        PARSER_SUBNET6,

        /// This will parse the input as pool6 content.
        PARSER_POOL6,

        /// This will parse the input as pd-pool content.
        PARSER_PD_POOL,

        /// This will parse the input as host-reservation.
        PARSER_HOST_RESERVATION,

        /// This will parse the input option definitions (for tests).
        PARSER_OPTION_DEFS,

        /// This will parse the input as option definition.
        PARSER_OPTION_DEF,

        /// This will parse the input as option data.
        PARSER_OPTION_DATA,

        /// This will parse the input as hooks-library.
        PARSER_HOOKS_LIBRARY,

        /// This will parse the input as dhcp-ddns. (D2 client config)
        PARSER_DHCP_DDNS,

        /// This will parse the input as config-control.
        PARSER_CONFIG_CONTROL,

        /// This will parse the content of Logging.
        PARSER_LOGGING

    } ParserType;

    /// @brief Default constructor.
    Parser6Context();

    /// @brief destructor
    virtual ~Parser6Context();

    /// @brief JSON elements being parsed.
    std::vector<isc::data::ElementPtr> stack_;

    /// @brief Method called before scanning starts on a string.
    ///
    /// @param str string to be parsed
    /// @param type specifies expected content
    void scanStringBegin(const std::string& str, ParserType type);

    /// @brief Method called before scanning starts on a file.
    ///
    /// @param f stdio FILE pointer
    /// @param filename file to be parsed
    /// @param type specifies expected content
    void scanFileBegin(FILE* f, const std::string& filename, ParserType type);

    /// @brief Method called after the last tokens are scanned.
    void scanEnd();

    /// @brief Divert input to an include file.
    ///
    /// @param filename file to be included
    void includeFile(const std::string& filename);

    /// @brief Run the parser on the string specified.
    ///
    /// This method parses specified string. Depending on the value of
    /// parser_type, parser may either check only that the input is valid
    /// JSON, or may do more specific syntax checking. See @ref ParserType
    /// for supported syntax checkers.
    ///
    /// @param str string to be parsed
    /// @param parser_type specifies expected content (usually DHCP6 or generic JSON)
    /// @return Element structure representing parsed text.
    isc::data::ElementPtr parseString(const std::string& str,
                                      ParserType parser_type);

    /// @brief Run the parser on the file specified.
    ///
    /// This method parses specified file. Depending on the value of
    /// parser_type, parser may either check only that the input is valid
    /// JSON, or may do more specific syntax checking. See @ref ParserType
    /// for supported syntax checkers.
    ///
    /// @param filename file to be parsed
    /// @param parser_type specifies expected content (usually DHCP6 or generic JSON)
    /// @return Element structure representing parsed text.
    isc::data::ElementPtr parseFile(const std::string& filename,
                                    ParserType parser_type);

    /// @brief Error handler
    ///
    /// @param loc location within the parsed file when experienced a problem.
    /// @param what string explaining the nature of the error.
    /// @throw Dhcp6ParseError
    void error(const isc::dhcp::location& loc, const std::string& what);

    /// @brief Error handler
    ///
    /// This is a simplified error reporting tool for possible future
    /// cases when the Dhcp6Parser is not able to handle the packet.
    ///
    /// @param what string explaining the nature of the error.
    /// @throw Dhcp6ParseError
    void error(const std::string& what);

    /// @brief Fatal error handler
    ///
    /// This is for should not happen but fatal errors.
    /// Used by YY_FATAL_ERROR macro so required to be static.
    ///
    /// @param what string explaining the nature of the error.
    /// @throw Dhcp6ParseError
    static void fatal(const std::string& what);

    /// @brief Converts bison's position to one understandable by isc::data::Element
    ///
    /// Convert a bison location into an element position
    /// (take the begin, the end is lost)
    ///
    /// @param loc location in bison format
    /// @return Position in format accepted by Element
    isc::data::Element::Position loc2pos(isc::dhcp::location& loc);

    /// @brief Check if a required parameter is present
    ///
    /// Check if a required parameter is present in the map at the top
    /// of the stack and raise an error when it is not.
    ///
    /// @param name name of the parameter expected to be present
    /// @param open_loc location of the opening curly bracket
    /// @param close_loc ocation of the closing curly bracket
    /// @throw Dhcp6ParseError
    void require(const std::string& name,
                 isc::data::Element::Position open_loc,
                 isc::data::Element::Position close_loc);

    /// @brief Defines syntactic contexts for lexical tie-ins
    typedef enum {
        ///< This one is used in pure JSON mode.
        NO_KEYWORD,

        ///< Used while parsing top level (that contains Dhcp6, Logging and others)
        CONFIG,

        ///< Used while parsing content of Dhcp6.
        DHCP6,

        // not yet Dhcp4, DhcpDdns,

        ///< Used while parsing content of Logging
        LOGGING,

        /// Used while parsing Dhcp6/interfaces structures.
        INTERFACES_CONFIG,

        /// Sanity checks.
        SANITY_CHECKS,

        /// Used while parsing Dhcp6/lease-database structures.
        LEASE_DATABASE,

        /// Used while parsing Dhcp6/hosts-database[s] structures.
        HOSTS_DATABASE,

        /// Used while parsing Dhcp6/*-database/type.
        DATABASE_TYPE,

        /// Used while parsing Dhcp6/mac-sources structures.
        MAC_SOURCES,

        /// Used while parsing Dhcp6/host-reservation-identifiers.
        HOST_RESERVATION_IDENTIFIERS,

        /// Used while parsing Dhcp6/hooks-libraries.
        HOOKS_LIBRARIES,

        /// Used while parsing Dhcp6/Subnet6 structures.
        SUBNET6,

        /// Used while parsing shared-networks structures.
        SHARED_NETWORK,

        /// Used while parsing Dhcp6/reservation-mode.
        RESERVATION_MODE,

        /// Used while parsing Dhcp6/option-def structures.
        OPTION_DEF,

        /// Used while parsing Dhcp6/option-data, Dhcp6/subnet6/option-data
        /// or anywhere option-data is present (client classes, host
        /// reservations and possibly others).
        OPTION_DATA,

        /// Used while parsing Dhcp6/client-classes structures.
        CLIENT_CLASSES,

        /// Used while parsing Dhcp6/expired-leases-processing.
        EXPIRED_LEASES_PROCESSING,

        /// Used while parsing Dhcp6/server-id structures.
        SERVER_ID,

        /// Used while parsing Dhcp6/server-id/type structures.
        DUID_TYPE,

        /// Used while parsing Dhcp6/control-socket structures.
        CONTROL_SOCKET,

        /// Used while parsing Dhcp4/dhcp-queue-control structures.
        DHCP_QUEUE_CONTROL,

        /// Used while parsing Dhcp6/subnet6/pools structures.
        POOLS,

        /// Used while parsing Dhcp6/subnet6/pd-pools structures.
        PD_POOLS,

        /// Used while parsing Dhcp6/reservations structures.
        RESERVATIONS,

        /// Used while parsing Dhcp6/subnet6/relay structures.
        RELAY,

        /// Used while parsing Dhcp6/loggers structures.
        LOGGERS,

        /// Used while parsing Dhcp6/loggers/output_options structures.
        OUTPUT_OPTIONS,

        /// Used while parsing Dhcp6/dhcp-ddns.
        DHCP_DDNS,

        /// Used while parsing Dhcp6/dhcp-ddns/ncr-protocol
        NCR_PROTOCOL,

        /// Used while parsing Dhcp6/dhcp-ddns/ncr-format
        NCR_FORMAT,

        /// Used while parsing Dhcp6/dhcp-ddns/replace-client-name.
        REPLACE_CLIENT_NAME,

        /// Used while parsing Dhcp4/config-control
        CONFIG_CONTROL,

        /// Used while parsing config-control/config-databases
        CONFIG_DATABASE

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
    ///
    /// This is a stack of files. Typically there's only one file (the
    /// one being currently parsed), but there may be more if one
    /// file includes another.
    std::vector<FILE*> sfiles_;

    /// @brief Current syntactic context
    ParserContext ctx_;

    /// @brief Enter a new syntactic context
    ///
    /// Entering a new syntactic context is useful in several ways.
    /// First, it allows the parser to avoid conflicts. Second, it
    /// allows the lexer to return different tokens depending on
    /// context (e.g. if "renew-timer" string is detected, the lexer
    /// will return STRING token if in JSON mode or RENEW_TIMER if
    /// in DHCP6 mode. Finally, the syntactic context allows the
    /// error message to be more descriptive if the input string
    /// does not parse properly.
    ///
    /// @param ctx the syntactic context to enter into
    void enter(const ParserContext& ctx);

    /// @brief Leave a syntactic context
    ///
    /// @throw isc::Unexpected if unbalanced
    void leave();

    /// @brief Get the syntactic context name
    ///
    /// @return printable name of the context.
    const std::string contextName();

 private:
    /// @brief Flag determining scanner debugging.
    bool trace_scanning_;

    /// @brief Flag determining parser debugging.
    bool trace_parsing_;

    /// @brief Syntactic context stack
    std::vector<ParserContext> cstack_;

    /// @brief Common part of parseXXX
    ///
    /// @return Element structure representing parsed text.
    isc::data::ElementPtr parseCommon();
};

}; // end of isc::eval namespace
}; // end of isc namespace

#endif
