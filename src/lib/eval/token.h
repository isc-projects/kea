// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef TOKEN_H
#define TOKEN_H

#include <exceptions/exceptions.h>
#include <dhcp/pkt.h>
#include <stack>

namespace isc {
namespace dhcp {

class Token;

/// @brief Pointer to a single Token
typedef boost::shared_ptr<Token> TokenPtr;

/// This is a structure that holds an expression converted to RPN
///
/// For example expression: option[123] == 'foo' will be converted to:
/// [0] = option[123] (TokenOption object)
/// [1] = 'foo' (TokenString object)
/// [2] = == operator (TokenEqual object)
typedef std::vector<TokenPtr> Expression;

/// Evaluated values are stored as a stack of strings
typedef std::stack<std::string> ValueStack;

/// @brief EvalStackError is thrown when more or less parameters are on the
///        stack than expected.
class EvalBadStack : public Exception {
public:
    EvalBadStack(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Base class for all tokens
///
/// It provides an interface for all tokens and storage for string representation
/// (all tokens evaluate to string).
///
/// This class represents a single token. Examples of a token are:
/// - "foo" (a constant string)
/// - option[123] (a token that extracts value of option 123)
/// - == (an operator that compares two other tokens)
/// - substring(a,b,c) (an operator that takes three arguments: a string,
///   first character and length)
class Token {
public:

    /// @brief This is a generic method for evaluating a packet.
    ///
    /// We need to pass the packet being evaluated and possibly previously
    /// evaluated values. Specific implementations may ignore the packet altogether
    /// and just put their own value on the stack (constant tokens), look at the
    /// packet and put some data extracted from it on the stack (option tokens),
    /// or pop arguments from the stack and put back the result (operators).
    ///
    /// The parameters passed will be:
    ///
    /// @param pkt - packet being classified
    /// @param values - stack of values with previously evaluated tokens
    virtual void evaluate(const Pkt& pkt, ValueStack& values) = 0;

    /// @brief Virtual destructor
    virtual ~Token() {}
};

/// @brief Token representing a constant string
///
/// This token holds value of a constant string, e.g. it represents
/// "MSFT" in expression option[vendor-class] == "MSFT"
class TokenString : public Token {
public:
    /// Value is set during token construction.
    ///
    /// @param str constant string to be represented.
    TokenString(const std::string& str)
        :value_(str){
    }

    /// @brief Token evaluation (puts value of the constant string on the stack)
    ///
    /// @param pkt (ignored)
    /// @param values (represented string will be pushed here)
    void evaluate(const Pkt& pkt, ValueStack& values);

protected:
    std::string value_; ///< Constant value
};

/// @brief Token representing a constant string in hexadecimal format
///
/// This token holds value of a constant string giving in an hexadecimal
/// format, for instance 0x666f6f is "foo"
class TokenHexString : public Token {
public:
    /// Value is set during token construction.
    ///
    /// @param str constant string to be represented
    /// (must be a string of hexadecimal digits or decoding will fail)
    TokenHexString(const std::string& str)
        :repr_(str){
    }

    /// @brief Token evaluation (puts value of the constant string on
    /// the stack after decoding or an empty string if decoding fails
    /// (note it should not if the parser is correct)
    ///
    /// @param pkt (ignored)
    /// @param values (represented string will be pushed here)
    void evaluate(const Pkt& pkt, ValueStack& values);

protected:
    std::string repr_; ///< Constant value
};

/// @brief Token that represents a value of an option
///
/// This represents a reference to a given option, e.g. in the expression
/// option[vendor-class] == "MSFT", it represents option[vendor-class]
///
/// During the evaluation it tries to extract the value of the specified
/// option. If the option is not found, an empty string ("") is returned.
class TokenOption : public Token {
public:
    /// @brief Constructor that takes an option code as a parameter
    /// @param option_code code of the option
    ///
    /// Note: There is no constructor that takes option_name, as it would
    /// introduce complex dependency of the libkea-eval on libdhcpsrv.
    ///
    /// @param option_code code of the option to be represented.
    TokenOption(uint16_t option_code)
        :option_code_(option_code) {}

    /// @brief Evaluates the values of the option
    ///
    /// This token represents a value of the option, so this method attempts
    /// to extract the option from the packet and put its value on the stack.
    /// If the option is not there, an empty string ("") is put on the stack.
    ///
    /// @param pkt specified option will be extracted from this packet (if present)
    /// @param values value of the option will be pushed here (or "")
    void evaluate(const Pkt& pkt, ValueStack& values);

private:
    uint16_t option_code_; ///< code of the option to be extracted
};

/// @brief Token that represents equality operator (compares two other tokens)
///
/// For example in the expression option[vendor-class] == "MSFT" this token
/// represents the equal (==) sign.
class TokenEqual : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenEqual() {}

    /// @brief Compare two values.
    ///
    /// Evaluation does not use packet information, but rather consumes the last
    /// two parameters. It does a simple string comparison and sets the value to
    /// either "true" or "false". It requires at least two parameters to be
    /// present on stack.
    ///
    /// @throw EvalBadStack if there are less than 2 values on stack
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (2 arguments will be popped, 1 result
    ///        will be pushed)
    void evaluate(const Pkt& pkt, ValueStack& values);
};

/// @brief Token that represents the substring operator (returns a portion
/// of the supplied string)
///
/// This token represents substring(str, start, len)  An operator that takes three
/// arguments: a string, the first character and the length.
class TokenSubstring : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenSubstring() {}

    /// @brief Extract a substring from a string
    ///
    /// Evaluation does not use packet information.  It requires at least
    /// three values to be present on the stack.  It will consume the top
    /// three values on the stack as parameters and push the resulting substring
    /// onto the stack.  From the top it expects the values on the stack as:
    /// -  len
    /// -  start
    /// -  str
    ///
    /// str is the string to extract a substring from.  If it is empty, an empty
    /// string is pushed onto the value stack.
    ///
    /// start is the postion from which the code starts extracting the substring.
    /// 0 is the first character and a negative number starts from the end, with
    /// -1 being the last character.  If the starting point is outside of the
    /// original string an empty string is pushed onto the value stack.
    ///
    /// length is the number of characters from the string to extract.
    /// "all" means all remaining characters from start to the end of string.
    /// A negative number means to go from start towards the beginning of
    /// the string, but doesn't include start.
    /// If length is longer than the remaining portion of string
    /// then the entire remaining portion is placed on the value stack.
    ///
    /// The following examples all use the base string "foobar", the first number
    /// is the starting position and the second is the length.  Note that
    /// a negative length only selects which characters to extract it does not
    /// indicate an attempt to reverse the string.
    /// -  0, all => "foobar"
    /// -  0,  6  => "foobar"
    /// -  0,  4  => "foob"
    /// -  2, all => "obar"
    /// -  2,  6  => "obar"
    /// - -1, all => "r"
    /// - -1, -4  => "ooba"
    ///
    /// @throw EvalBadStack if there are less than 3 values on stack
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (3 arguments will be popped, 1 result
    ///        will be pushed)
    void evaluate(const Pkt& pkt, ValueStack& values);
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
