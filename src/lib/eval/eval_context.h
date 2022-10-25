// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EVAL_CONTEXT_H
#define EVAL_CONTEXT_H
#include <string>
#include <map>
#include <eval/parser.h>
#include <eval/eval_context_decl.h>
#include <exceptions/exceptions.h>

// Tell Flex the lexer's prototype ...
#define YY_DECL \
    isc::eval::EvalParser::symbol_type evallex (EvalContext& driver)

// ... and declare it for the parser's sake.
YY_DECL;

namespace isc {
namespace eval {

/// @brief Evaluation error exception raised when trying to parse an exceptions.
class EvalParseError : public isc::Exception {
public:
    EvalParseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Evaluation context, an interface to the expression evaluation.
class EvalContext {
public:

    /// @brief Specifies what type of expression the parser is expected to see
    typedef enum {
        PARSER_BOOL,  ///< expression is expected to evaluate to bool
        PARSER_STRING ///< expression is expected to evaluate to string
    } ParserType;

    /// @brief Type of the check defined function.
    typedef std::function<bool(const ClientClass&)> CheckDefined;

    /// @brief Default constructor.
    ///
    /// @param option_universe Option universe: DHCPv4 or DHCPv6. This is used
    /// by the parser to determine which option definitions set should be used
    /// to map option names to option codes.
    /// @param check_defined A function called to check if a client class
    /// used for membership is already defined. If it is not the parser
    /// will fail: only backward or built-in references are accepted.
    EvalContext(const Option::Universe& option_universe,
                CheckDefined check_defined = acceptAll);

    /// @brief destructor
    virtual ~EvalContext();

    /// @brief Accept all client class names
    ///
    /// @param client_class (unused)
    /// @return true
    static bool acceptAll(const ClientClass& client_class);

    /// @brief Parsed expression (output tokens are stored here)
    isc::dhcp::Expression expression;

    /// @brief Method called before scanning starts on a string.
    ///
    /// @param type specifies type of the expression to be parsed
    void scanStringBegin(ParserType type);

    /// @brief Method called after the last tokens are scanned from a string.
    void scanStringEnd();

    /// @brief Run the parser on the string specified.
    ///
    /// @param str string to be parsed
    /// @param type type of the expression expected/parser type to be created
    /// @return true on success.
    bool parseString(const std::string& str, ParserType type = PARSER_BOOL);

    /// @brief The name of the file being parsed.
    /// Used later to pass the file name to the location tracker.
    std::string file_;

    /// @brief The string being parsed.
    std::string string_;

    /// @brief Error handler
    ///
    /// @param loc location within the parsed file where the problem was experienced.
    /// @param what string explaining the nature of the error.
    static void error(const isc::eval::location& loc, const std::string& what);

    /// @brief Error handler
    ///
    /// This is a simplified error reporting tool for possible future
    /// cases when the EvalParser is not able to handle the packet.
    static void error(const std::string& what);

    /// @brief Fatal error handler
    ///
    /// This is for should not happen but fatal errors
    static void fatal(const std::string& what);

    /// @brief Option code conversion
    ///
    /// @param option_code a string representing the integer code
    /// @param loc the location of the token
    /// @result the option code
    /// @throw calls the syntax error function if the value is not in
    ///        the range 0..255 or 0..65535
    uint16_t convertOptionCode(const std::string& option_code,
                               const isc::eval::location& loc);

    /// @brief Option name conversion
    ///
    /// @param option_name the option name
    /// @param loc the location of the token
    /// @return the option code
    /// @throw calls the syntax error function if the name cannot be resolved
    uint16_t convertOptionName(const std::string& option_name,
                               const isc::eval::location& loc);

    /// @brief Attempts to convert string to unsigned 32bit integer
    ///
    /// For reverse conversion, see @ref fromUint32
    ///
    /// @param number string to be converted
    /// @param loc the location of the token
    /// @return the integer value
    /// @throw EvalParseError if conversion fails or the value is out of range.
    static uint32_t convertUint32(const std::string& number,
                                  const isc::eval::location& loc);

    /// @brief Attempts to convert string to signed 32bit integer
    ///
    /// @param number string to be converted
    /// @param loc the location of the token
    /// @return the integer value
    /// @throw EvalParseError if conversion fails or the value is out of range.
    static int32_t convertInt32(const std::string& number,
                                const isc::eval::location& loc);

    /// @brief Attempts to convert string to unsigned 16bit integer
    ///
    /// For reverse conversion, see @ref fromUint16
    ///
    /// @param number string to be converted
    /// @param loc the location of the token
    /// @return the integer value
    /// @throw EvalParseError if conversion fails or the value is out of range.
    static uint16_t convertUint16(const std::string& number,
                                  const isc::eval::location& loc);

    /// @brief Attempts to convert string to signed 16bit integer
    ///
    /// @param number string to be converted
    /// @param loc the location of the token
    /// @return the integer value
    /// @throw EvalParseError if conversion fails or the value is out of range.
    static int16_t convertInt16(const std::string& number,
                                const isc::eval::location& loc);

    /// @brief Attempts to convert string to unsigned 8bit integer
    ///
    /// @param number string to be converted
    /// @param loc the location of the token
    /// @return the integer value
    /// @throw EvalParseError if conversion fails or the value is out of range.
    static uint8_t convertUint8(const std::string& number,
                                const isc::eval::location& loc);

    /// @brief Attempts to convert string to signed 8bit integer
    ///
    /// @param number string to be converted
    /// @param loc the location of the token
    /// @return the integer value
    /// @throw EvalParseError if conversion fails or the value is out of range.
    static int8_t convertInt8(const std::string& number,
                              const isc::eval::location& loc);

    /// @brief Nest level conversion
    ///
    /// @param nest_level a string representing the integer nesting level
    /// @param loc the location of the token
    /// @return the nesting level
    /// @throw calls the syntax error function if the value is not in
    ///        the range -32..31
    int8_t convertNestLevelNumber(const std::string& nest_level,
                                  const isc::eval::location& loc);

    /// @brief Converts unsigned 32bit integer to string representation
    ///
    /// The integer is coded as a 4 byte long string in network order, e.g.
    /// 6 is represented as 00000006. For reverse conversion, see
    /// @ref convertUint32.
    ///
    /// @param integer value to be converted
    /// @return 4 byte long string that encodes the value.
    static std::string fromUint32(const uint32_t integer);

    /// @brief Converts unsigned 16bit integer to string representation
    ///
    /// The integer is coded as a 2 byte long string in network order, e.g.
    /// 6 is represented as 0006. For reverse conversion, see
    /// @ref convertUint16.
    ///
    /// @param integer value to be converted
    /// @return 2 byte long string that encodes the value.
    static std::string fromUint16(const uint16_t integer);

    /// @brief Returns the universe (v4 or v6)
    ///
    /// @return universe
    Option::Universe getUniverse() {
        return (option_universe_);
    }

    /// @brief Check if a client class is already defined
    ///
    /// @param client_class the client class name to check
    /// @return true if the client class is defined, false if not
    bool isClientClassDefined(const ClientClass& client_class);

private:
    /// @brief Flag determining scanner debugging.
    bool trace_scanning_;

    /// @brief Flag determining parser debugging.
    bool trace_parsing_;

    /// @brief Option universe: DHCPv4 or DHCPv6.
    ///
    /// This is used by the parser to determine which option definitions
    /// set should be used to map option name to option code.
    Option::Universe option_universe_;

    /// @brief Function to check if a client class is already defined.
    CheckDefined check_defined_;

};

} // end of isc::eval namespace
} // end of isc namespace

#endif
