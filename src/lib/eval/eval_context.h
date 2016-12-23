// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
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
class EvalContext
{
public:
    /// @brief Default constructor.
    ///
    /// @param option_universe Option universe: DHCPv4 or DHCPv6. This is used
    /// by the parser to determine which option definitions set should be used
    /// to map option names to option codes.
    EvalContext(const Option::Universe& option_universe);

    /// @brief destructor
    virtual ~EvalContext();

    /// @brief Parsed expression (output tokens are stored here)
    isc::dhcp::Expression expression;

    /// @brief Method called before scanning starts on a string.
    void scanStringBegin();

    /// @brief Method called after the last tokens are scanned from a string.
    void scanStringEnd();

    /// @brief Run the parser on the string specified.
    ///
    /// @param str string to be written
    /// @return true on success.
    bool parseString(const std::string& str);

    /// @brief The name of the file being parsed.
    /// Used later to pass the file name to the location tracker.
    std::string file_;

    /// @brief The string being parsed.
    std::string string_;

    /// @brief Error handler
    ///
    /// @param loc location within the parsed file when experienced a problem.
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

    /// @brief Attempts to convert string to unsigned 8bit integer
    ///
    /// @param number string to be converted
    /// @param loc the location of the token
    /// @return the integer value
    /// @throw EvalParseError if conversion fails or the value is out of range.
    static uint8_t convertUint8(const std::string& number,
                                const isc::eval::location& loc);

    /// @brief Nest level conversion
    ///
    /// @param nest_level a string representing the integer nesting level
    /// @param loc the location of the token
    /// @return the nesting level
    /// @throw calls the syntax error function if the value is not in
    ///        the range 0..31
    uint8_t convertNestLevelNumber(const std::string& nest_level,
                                   const isc::eval::location& loc);

    /// @brief Converts integer to string representation
    ///
    /// The integer is coded as a 4 byte long string in network order, e.g.
    /// 6 is represented as 00000006. For reverse conversion, see
    /// @ref convertUint32.
    ///
    /// @param integer value to be converted
    /// @return 4 byte long string that encodes the value.
    static std::string fromUint32(const uint32_t integer);

    /// @brief Returns the universe (v4 or v6)
    ///
    /// @return universe
    Option::Universe getUniverse() {
        return (option_universe_);
    }

 private:
    /// @brief Flag determining scanner debugging.
    bool trace_scanning_;

    /// @brief Flag determening parser debugging.
    bool trace_parsing_;

    /// @brief Option universe: DHCPv4 or DHCPv6.
    ///
    /// This is used by the parser to determine which option definitions
    /// set should be used to map option name to option code.
    Option::Universe option_universe_;

};

}; // end of isc::eval namespace
}; // end of isc namespace

#endif
