// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PARSER_CONTEXT_H
#define PARSER_CONTEXT_H
#include <string>
#include <map>
#include <vector>
#include <d2/d2_parser.h>
#include <d2/parser_context_decl.h>
#include <exceptions/exceptions.h>

// Tell Flex the lexer's prototype ...
#define YY_DECL isc::d2::D2Parser::symbol_type d2_parser_lex (D2ParserContext& driver)

// ... and declare it for the parser's sake.
YY_DECL;

namespace isc {
namespace d2 {

/// @brief Evaluation error exception raised when trying to parse.
///
/// @todo: This probably should be common for Dhcp4 and Dhcp6.
class D2ParseError : public isc::Exception {
public:
    D2ParseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Evaluation context, an interface to the expression evaluation.
class D2ParserContext
{
public:

    /// @brief Defines currently supported scopes
    ///
    /// D2Parser may eventually support multiple levels of parsing scope.
    /// Currently it supports only the D2 module scope which expects the data
    /// to be parsed to be a map containing the DhcpDdns element and its
    /// constituents.
    ///
    typedef enum {
        /// This parser will parse the content as generic JSON.
        PARSER_JSON,

        ///< Used for parsing top level (contains DhcpDdns)
        PARSER_DHCPDDNS,

        ///< Used for parsing content of DhcpDdns.
        PARSER_SUB_DHCPDDNS,

        ///< Used for parsing content of a TSIG key.
        PARSER_TSIG_KEY,

        ///< Used for parsing a list of TSIG Keys.
        PARSER_TSIG_KEYS,

        ///< Used for parsing content of a DDNS Domain.
        PARSER_DDNS_DOMAIN,

        ///< Used for parsing a list a DDNS Domains.
        PARSER_DDNS_DOMAINS,

        ///< Used for parsing content of a DNS Server.
        PARSER_DNS_SERVER,

        ///< Used for parsing a list of DNS servers.
        PARSER_DNS_SERVERS,

        ///< Used for parsing content of hooks libraries.
        PARSER_HOOKS_LIBRARY
    } ParserType;

    /// @brief Default constructor.
    D2ParserContext();

    /// @brief destructor.
    virtual ~D2ParserContext();

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
    /// @param parser_type specifies expected content
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
    /// @param parser_type specifies expected content
    /// @return Element structure representing parsed text.
    isc::data::ElementPtr parseFile(const std::string& filename,
                                    ParserType parser_type);

    /// @brief Error handler
    ///
    /// @note The optional position for an error in a string begins by 1
    /// so the caller should add 1 to the position of the C++ string.
    ///
    /// @param loc location within the parsed file when experienced a problem.
    /// @param what string explaining the nature of the error.
    /// @param pos optional position for in string errors.
    /// @throw D2ParseError
    void error(const isc::d2::location& loc,
               const std::string& what,
               size_t pos = 0);

    /// @brief Error handler
    ///
    /// This is a simplified error reporting tool for reporting
    /// parsing errors.
    ///
    /// @param what string explaining the nature of the error.
    /// @throw D2ParseError
    void error(const std::string& what);

    /// @brief Fatal error handler
    ///
    /// This is for should not happen but fatal errors.
    /// Used by YY_FATAL_ERROR macro so required to be static.
    ///
    /// @param what string explaining the nature of the error.
    /// @throw D2ParseError
    static void fatal(const std::string& what);

    /// @brief Converts bison's position to one understood by isc::data::Element
    ///
    /// Convert a bison location into an element position
    /// (take the begin, the end is lost)
    ///
    /// @param loc location in bison format
    /// @return Position in format accepted by Element
    isc::data::Element::Position loc2pos(isc::d2::location& loc);

    /// @brief Check if a required parameter is present
    ///
    /// Check if a required parameter is present in the map at the top
    /// of the stack and raise an error when it is not.
    ///
    /// @param name name of the parameter to check
    /// @param open_loc location of the opening curly bracket
    /// @param close_loc location of the closing curly bracket
    /// @throw D2ParseError
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
    /// @throw D2ParseError
    void unique(const std::string& name,
                isc::data::Element::Position loc);

    /// @brief Defines syntactic contexts for lexical tie-ins
    typedef enum {
        ///< This one is used in pure JSON mode.
        NO_KEYWORD,

        ///< Used while parsing top level (contains DhcpDdns).
        CONFIG,

        ///< Used while parsing content of DhcpDdns.
        DHCPDDNS,

        ///< Used while parsing content of a tsig-key
        TSIG_KEY,

        ///< Used while parsing a list of tsig-keys
        TSIG_KEYS,

        ///< Used while parsing content of DhcpDdns/tsig-keys/algorithm
        ALGORITHM,

        ///< Used while parsing content of DhcpDdns/tsig-keys/digest-bits
        DIGEST_BITS,

        ///< Used while parsing content of DhcpDdns/tsig-keys/secret
        SECRET,

        ///< Used while parsing content of DhcpDdns/forward-ddns
        FORWARD_DDNS,

        ///< Used while parsing content of DhcpDdns/reverse-ddns
        REVERSE_DDNS,

        ///< Used while parsing content of a ddns-domain
        DDNS_DOMAIN,

        ///< Used while parsing a list of ddns-domains
        DDNS_DOMAINS,

        ///< Used while parsing content of a dns-server
        DNS_SERVER,

        ///< Used while parsing content of list of dns-servers
        DNS_SERVERS,

        ///< Used while parsing content of a control-socket
        CONTROL_SOCKET,

        /// Used while parsing DhcpDdns/loggers structures.
        LOGGERS,

        /// Used while parsing DhcpDdns/loggers/output_options structures.
        OUTPUT_OPTIONS,

        /// Used while parsing DhcpDdns/ncr-protocol
        NCR_PROTOCOL,

        /// Used while parsing DhcpDdns/ncr-format
        NCR_FORMAT,

        /// Used while parsing DhcpDdns/hooks-libraries.
        HOOKS_LIBRARIES

    } ParserContext;

    /// @brief File name
    std::string file_;

    /// @brief File name stack
    std::vector<std::string> files_;

    /// @brief Location of the current token
    ///
    /// The lexer will keep updating it. This variable will be useful
    /// for logging errors.
    isc::d2::location loc_;

    /// @brief Location stack
    std::vector<isc::d2::location> locs_;

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
    /// context (e.g. if "name" string is detected, the lexer
    /// will return STRING token if in JSON mode or NAME if
    /// in TSIG_KEY mode. Finally, the syntactic context allows the
    /// error message to be more descriptive if the input string
    /// does not parse properly.
    ///
    /// @param ctx the syntactic context to enter into
    void enter(const ParserContext& ctx);

    /// @brief Leave a syntactic context
    ///
    /// @throw isc::Unexpected if unbalanced
    void leave();

    /// @brief Get the syntax context name
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

} // end of isc::eval namespace
} // end of isc namespace

#endif
