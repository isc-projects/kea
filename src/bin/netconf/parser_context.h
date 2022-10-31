// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETCONF_PARSER_CONTEXT_H
#define NETCONF_PARSER_CONTEXT_H
#include <string>
#include <map>
#include <vector>
#include <netconf/netconf_parser.h>
#include <netconf/parser_context_decl.h>
#include <cc/dhcp_config_error.h>
#include <exceptions/exceptions.h>

// Tell Flex the lexer's prototype ...
#define YY_DECL isc::netconf::NetconfParser::symbol_type netconf_lex (ParserContext& driver)

// ... and declare it for the parser's sake.
YY_DECL;

namespace isc {
namespace netconf {

/// @brief Parser context is a wrapper around flex/bison instances dedicated to
///        Netconf-agent config file parser.
///
/// It follows the same principle as other components. The primary interface
/// are @ref parseString and @ref parseFile methods. All other methods are
/// public for testing purposes only. This interface allows parsing the
/// whole configuration with syntactic checking (which is by far the most
/// frequent use), but it also allows parsing input as generic JSON or
/// parse only content of the Netconf-agent object, which is a subset
/// of full grammar (this will be very useful for unit-tests to not duplicate
/// unnecessary parts of the config file).
class ParserContext
{
public:

    /// @brief Defines currently supported scopes
    ///
    /// NetconfParser is able to parse several types of scope. Usually,
    /// when it parses a config file, it expects the data to have a map
    /// with Netconf-agent in it and all the parameters within that map.
    /// However, sometimes the parser is expected to parse only a subset
    /// of that information.
    typedef enum {
        /// This parser will parse the content as generic JSON.
        PARSER_JSON,

        /// This parser will expect the content as Netconf config wrapped
        /// in a map (that's the regular config file)
        PARSER_NETCONF,

        /// This parser will expect only the content of Netconf.
        PARSER_SUB_NETCONF
    } ParserType;

    /// @brief Default constructor.
    ParserContext();

    /// @brief destructor
    virtual ~ParserContext();

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
    /// @param parser_type specifies expected content (usually NETCONF or generic JSON)
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
    /// @param parser_type specifies expected content (usually PARSER_NETCONF
    ///                                                or PARSER_JSON)
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
    /// @throw ParseError
    void error(const isc::netconf::location& loc,
               const std::string& what,
               size_t pos = 0);

    /// @brief Error handler
    ///
    /// This is a simplified error reporting tool for possible future
    /// cases when the NetconfParser is not able to handle the packet.
    ///
    /// @param what string explaining the nature of the error.
    /// @throw ParseError
    void error(const std::string& what);

    /// @brief Fatal error handler
    ///
    /// This is for should not happen but fatal errors.
    /// Used by YY_FATAL_ERROR macro so required to be static.
    ///
    /// @param what string explaining the nature of the error.
    /// @throw ParseError
    static void fatal(const std::string& what);

    /// @brief Converts bison's position to one understandable by isc::data::Element
    ///
    /// Convert a bison location into an element position
    /// (take the begin, the end is lost)
    ///
    /// @param loc location in bison format
    /// @return Position in format accepted by Element
    isc::data::Element::Position loc2pos(isc::netconf::location& loc);

    /// @brief Check if a required parameter is present
    ///
    /// Check if a required parameter is present in the map at the top
    /// of the stack and raise an error when it is not.
    ///
    /// @param name name of the parameter to check
    /// @param open_loc location of the opening curly bracket
    /// @param close_loc location of the closing curly bracket
    /// @throw ParseError
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
    /// @throw ParseError
    void unique(const std::string& name,
                isc::data::Element::Position loc);

    /// @brief Warning handler
    ///
    /// @param loc location within the parsed file where the problem was experienced
    /// @param what string explaining the nature of the error
    ///
    /// @throw ParseError
    void warning(const isc::netconf::location& loc, const std::string& what);

    /// @brief Warning for extra commas
    ///
    /// @param loc location within the parsed file of the extra comma
    ///
    /// @throw ParseError
    void warnAboutExtraCommas(const isc::netconf::location& loc);

    /// @brief Defines syntactic contexts for lexical tie-ins
    typedef enum {
        ///< This one is used in pure JSON mode.
        NO_KEYWORDS,

        ///< Used while parsing top level (that contains Netconf)
        CONFIG,

        ///< Used while parsing content of Netconf.
        NETCONF,

        /// Used while parsing Netconf/managed-servers.
        MANAGED_SERVERS,

        ///< Used while parsing Netconf/managed-servers/*.
        SERVER,

        ///< Used while parsing Netconf/manages-servers/*/control-socket
        CONTROL_SOCKET,

        ///< Used while parsing Netconf/managed-servers/*/control-socket/socket-type.
        SOCKET_TYPE,

        ///< Used while parsing Netconf/hooks-libraries.
        HOOKS_LIBRARIES,

        ///< Used while parsing Netconf/loggers structures.
        LOGGERS,

        ///< Used while parsing Netconf/loggers/output_options structures.
        OUTPUT_OPTIONS

    } LexerContext;

    /// @brief File name
    std::string file_;

    /// @brief File name stack
    std::vector<std::string> files_;

    /// @brief Location of the current token
    ///
    /// The lexer will keep updating it. This variable will be useful
    /// for logging errors.
    isc::netconf::location loc_;

    /// @brief Location stack
    std::vector<isc::netconf::location> locs_;

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
    LexerContext ctx_;

    /// @brief Enter a new syntactic context
    ///
    /// Entering a new syntactic context is useful in several ways.
    /// First, it allows the parser to avoid conflicts. Second, it
    /// allows the lexer to return different tokens depending on
    /// context (e.g. if "renew-timer" string is detected, the lexer
    /// will return STRING token if in JSON mode or RENEW_TIMER if
    /// in DHCP6 mode. Finally, the syntactic context allows the
    /// error message to be more descriptive if the input string
    /// does not parse properly. Netconf Agent parser uses simplified
    /// contexts: either it recognizes keywords (value set to KEYWORDS)
    /// or not (value set to NO_KEYWORDS).
    ///
    /// Make sure to call @ref leave() once the parsing of your
    /// context is complete.
    ///
    /// @param ctx the syntactic context to enter into
    void enter(const LexerContext& ctx);

    /// @brief Leave a syntactic context
    ///
    /// @ref enter() must be called before (when entering a new scope
    /// or context). Once you complete the parsing, this method
    /// should be called.
    ///
    /// @throw isc::Unexpected if unbalanced (more leave() than enter() calls)
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
    std::vector<LexerContext> cstack_;

    /// @brief Common part of parseXXX
    ///
    /// @return Element structure representing parsed text.
    isc::data::ElementPtr parseCommon();
};  // ParserContext

}  // namespace netconf
}  // namespace isc

#endif
