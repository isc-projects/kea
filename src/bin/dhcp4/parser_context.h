// Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PARSER_CONTEXT_H
#define PARSER_CONTEXT_H
#include <string>
#include <map>
#include <vector>
#include <dhcp4/dhcp4_parser.h>
#include <dhcp4/parser_context_decl.h>
#include <exceptions/exceptions.h>

// Tell Flex the lexer's prototype ...
#define YY_DECL isc::dhcp::Dhcp4Parser::symbol_type parser4_lex (Parser4Context& driver)

// ... and declare it for the parser's sake.
YY_DECL;

namespace isc {
namespace dhcp {

/// @brief Evaluation error exception raised when trying to parse.
///
/// @todo: This probably should be common for Dhcp4 and Dhcp6.
class Dhcp4ParseError : public isc::Exception {
public:
    Dhcp4ParseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Evaluation context, an interface to the expression evaluation.
class Parser4Context
{
public:

    /// @brief Defines currently supported scopes
    ///
    /// Dhcp4Parser is able to parse several types of scope. Usually,
    /// when it parses a config file, it expects the data to have a map
    /// with Dhcp4 in it and all the parameters within that Dhcp4 map.
    /// However, sometimes the parser is expected to parse only a subset
    /// of that information. For example, it may be asked to parse
    /// a structure that is host-reservation only, without the global
    /// 'Dhcp4' or 'reservations' around it. In such case the parser
    /// is being told to start parsing as PARSER_HOST_RESERVATION4.
    typedef enum {
        /// This parser will parse the content as generic JSON.
        PARSER_JSON,

        /// This parser will parse the content as Dhcp4 config wrapped in a map
        /// (that's the regular config file)
        PARSER_DHCP4,

        /// This parser will parse the content of Dhcp4 (without outer { } and
        /// without "Dhcp4"). It is mostly used in unit-tests as most of the
        /// unit-tests do not define the outer map and Dhcp4 entity, just the
        /// contents of it.
        SUBPARSER_DHCP4,

        /// This will parse the input as interfaces content.
        PARSER_INTERFACES,

        /// This will parse the input as Subnet4 content.
        PARSER_SUBNET4,

        /// This will parse the input as pool4 content.
        PARSER_POOL4,

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

        /// This will parse the input as dhcp-ddns.
        PARSER_DHCP_DDNS,

        /// This will parse the input as config-control.
        PARSER_CONFIG_CONTROL,
    } ParserType;

    /// @brief Default constructor.
    Parser4Context();

    /// @brief destructor
    virtual ~Parser4Context();

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
    /// @param parser_type specifies expected content (usually DHCP4 or generic JSON)
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
    /// @param parser_type specifies expected content (usually DHCP4 or generic JSON)
    /// @return Element structure representing parsed text.
    isc::data::ElementPtr parseFile(const std::string& filename,
                                    ParserType parser_type);

    /// @brief Error handler
    ///
    /// @note The optional position for an error in a string begins by 1
    /// so the caller should add 1 to the position of the C++ string.
    ///
    /// @param loc location within the parsed file where the problem was experienced.
    /// @param what string explaining the nature of the error.
    /// @param pos optional position for in string errors.
    /// @throw Dhcp4ParseError
    void error(const isc::dhcp::location& loc,
               const std::string& what,
               size_t pos = 0);

    /// @brief Error handler
    ///
    /// This is a simplified error reporting tool for possible future
    /// cases when the Dhcp4Parser is not able to handle the packet.
    ///
    /// @param what string explaining the nature of the error.
    /// @throw Dhcp4ParseError
    void error(const std::string& what);

    /// @brief Fatal error handler
    ///
    /// This is for should not happen but fatal errors.
    /// Used by YY_FATAL_ERROR macro so required to be static.
    ///
    /// @param what string explaining the nature of the error.
    /// @throw Dhcp4ParseError
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
    /// @param name name of the parameter to check
    /// @param open_loc location of the opening curly bracket
    /// @param close_loc location of the closing curly bracket
    /// @throw Dhcp4ParseError
    void require(const std::string& name,
                 isc::data::Element::Position open_loc,
                 isc::data::Element::Position close_loc);

    /// @brief Check if a parameter is already present
    ///
    /// Check if a parameter is already present in the map at the top
    /// of the stack and raise an error when it is.
    ///
    /// @param name name of the parameter to check
    /// @param loc location of the current parameter
    /// @throw Dhcp4ParseError
    void unique(const std::string& name,
                isc::data::Element::Position loc);

    /// @brief Warning handler
    ///
    /// @param loc location within the parsed file where the problem was experienced
    /// @param what string explaining the nature of the error
    ///
    /// @throw ParseError
    void warning(const isc::dhcp::location& loc, const std::string& what);

    /// @brief Warning for extra commas
    ///
    /// @param loc location within the parsed file of the extra comma
    ///
    /// @throw ParseError
    void warnAboutExtraCommas(const isc::dhcp::location& loc);

    /// @brief Defines syntactic contexts for lexical tie-ins
    typedef enum {
        ///< This one is used in pure JSON mode.
        NO_KEYWORD,

        ///< Used while parsing top level (that contains Dhcp4)
        CONFIG,

        ///< Used while parsing content of Dhcp4.
        DHCP4,

        /// Used while parsing Dhcp4/interfaces structures.
        INTERFACES_CONFIG,

        /// Sanity checks.
        SANITY_CHECKS,

        /// Used while parsing Dhcp4/interfaces/dhcp-socket-type structures.
        DHCP_SOCKET_TYPE,

        /// Used while parsing Dhcp4/interfaces/outbound-interface structures.
        OUTBOUND_INTERFACE,

        /// Used while parsing Dhcp4/lease-database structures.
        LEASE_DATABASE,

        /// Used while parsing Dhcp4/hosts-database[s] structures.
        HOSTS_DATABASE,

        /// Used while parsing Dhcp4/*-database/type.
        DATABASE_TYPE,

        /// Used while parsing Dhcp4/*-database/on-fail.
        DATABASE_ON_FAIL,

        /// Used while parsing Dhcp4/host-reservation-identifiers.
        HOST_RESERVATION_IDENTIFIERS,

        /// Used while parsing Dhcp4/hooks-libraries.
        HOOKS_LIBRARIES,

        /// Used while parsing Dhcp4/Subnet4 structures.
        SUBNET4,

        /// Used while parsing shared-networks structures.
        SHARED_NETWORK,

        /// Used while parsing Dhcp4/reservation-mode.
        RESERVATION_MODE,

        /// Used while parsing Dhcp4/option-def structures.
        OPTION_DEF,

        /// Used while parsing Dhcp4/option-data, Dhcp4/subnet4/option-data
        /// or anywhere option-data is present (client classes, host
        /// reservations and possibly others).
        OPTION_DATA,

        /// Used while parsing Dhcp4/client-classes structures.
        CLIENT_CLASSES,

        /// Used while parsing Dhcp4/expired-leases-processing.
        EXPIRED_LEASES_PROCESSING,

        /// Used while parsing Dhcp4/server-id structures.
        SERVER_ID,

        /// Used while parsing Dhcp4/control-socket structures.
        CONTROL_SOCKET,

        /// Used while parsing Dhcp4/dhcp-queue-control structures.
        DHCP_QUEUE_CONTROL,

        /// Used while parsing Dhcp4/multi-threading structures.
        DHCP_MULTI_THREADING,

        /// Used while parsing Dhcp4/subnet4/pools structures.
        POOLS,

        /// Used while parsing Dhcp4/reservations structures.
        RESERVATIONS,

        /// Used while parsing Dhcp4/subnet4relay structures.
        RELAY,

        /// Used while parsing Dhcp4/loggers structures.
        LOGGERS,

        /// Used while parsing Dhcp4/loggers/output_options structures.
        OUTPUT_OPTIONS,

        /// Used while parsing Dhcp4/dhcp-ddns.
        DHCP_DDNS,

        /// Used while parsing Dhcp4/dhcp-ddns/ncr-protocol
        NCR_PROTOCOL,

        /// Used while parsing Dhcp4/dhcp-ddns/ncr-format
        NCR_FORMAT,

        /// Used while parsing Dhcp4/dhcp-ddns/replace-client-name.
        REPLACE_CLIENT_NAME,

        /// Used while parsing Dhcp4/config-control
        CONFIG_CONTROL,

        /// Used while parsing config-control/config-databases
        CONFIG_DATABASE,

        /// Used while parsing compatibility parameters
        COMPATIBILITY,

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
    /// in DHCP4 mode. Finally, the syntactic context allows the
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
