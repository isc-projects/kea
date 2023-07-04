// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
/// For example expression: option[123].text == 'foo' will be converted to:
/// [0] = option[123].text (TokenOption object)
/// [1] = 'foo' (TokenString object)
/// [2] = == operator (TokenEqual object)
typedef std::vector<TokenPtr> Expression;

typedef boost::shared_ptr<Expression> ExpressionPtr;

/// Evaluated values are stored as a stack of strings
typedef std::stack<std::string> ValueStack;

/// @brief EvalBadStack is thrown when more or less parameters are on the
///        stack than expected.
class EvalBadStack : public Exception {
public:
    EvalBadStack(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief EvalTypeError is thrown when a value on the stack has a content
///        with an unexpected type.
class EvalTypeError : public Exception {
public:
    EvalTypeError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Base class for all tokens
///
/// It provides an interface for all tokens and storage for string representation
/// (all tokens evaluate to string).
///
/// This class represents a single token. Examples of a token are:
/// - "foo" (a constant string)
/// - option[123].text (a token that extracts textual value of option 123)
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
    virtual void evaluate(Pkt& pkt, ValueStack& values) = 0;

    /// @brief Virtual destructor
    virtual ~Token() {}

    /// @brief Coverts a (string) value to a boolean
    ///
    /// Only "true" and "false" are expected.
    ///
    /// @param value the (string) value
    /// @return the boolean represented by the value
    /// @throw EvalTypeError when the value is not either "true" or "false".
    static inline bool toBool(std::string value) {
        if (value == "true") {
            return (true);
        } else if (value == "false") {
            return (false);
        } else {
            isc_throw(EvalTypeError, "Incorrect boolean. Expected exactly "
                      "\"false\" or \"true\", got \"" << value << "\"");
        }
    }
};

/// The order where Token subtypes are declared should be:
///  - literal terminals
///  - option & co
///  - pkt field & co
///  - ==
///  - substring & co
///  - not, and, or

/// @brief Token representing a constant string
///
/// This token holds value of a constant string, e.g. it represents
/// "MSFT" in expression option[vendor-class].text == "MSFT"
class TokenString : public Token {
public:
    /// Value is set during token construction.
    ///
    /// @param str constant string to be represented.
    TokenString(const std::string& str)
        : value_(str){
    }

    /// @brief Token evaluation (puts value of the constant string on the stack)
    ///
    /// @param pkt (ignored)
    /// @param values (represented string will be pushed here)
    void evaluate(Pkt& pkt, ValueStack& values);

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
    /// (must be "0x" or "0X" followed by a string of hexadecimal digits
    /// or decoding will fail)
    TokenHexString(const std::string& str);

    /// @brief Token evaluation (puts value of the constant string on
    /// the stack after decoding or an empty string if decoding fails
    /// (note it should not if the parser is correct)
    ///
    /// @param pkt (ignored)
    /// @param values (represented string will be pushed here)
    void evaluate(Pkt& pkt, ValueStack& values);

protected:
    std::string value_; ///< Constant value
};

/// @brief Token representing an unsigned 32 bit integer
///
/// For performance reasons, the constant integer value is converted to a string
/// just once (in the constructor). Afterwards, this effectively works as a constant
/// 4 byte long string. Hence this class is derived from TokenString and
/// does not even need its own evaluate() method.
class TokenInteger : public TokenString {
public:
    /// @brief Integer value set during construction.
    ///
    /// The value is converted to string and stored in value_ provided by the
    /// base class.
    ///
    /// @param value integer value to be stored.
    TokenInteger(const uint32_t value);

    /// @brief Returns integer value
    ///
    /// Used in tests only.
    ///
    /// @return integer value
    uint32_t getInteger() const {
        return (int_value_);
    }

protected:
    uint32_t int_value_; ///< value as integer (stored for testing only)
};

/// @brief Token representing an IP address as a constant string
///
/// This token holds the value of an IP address as a constant string,
/// for instance 10.0.0.1 is 0x10000001
class TokenIpAddress : public Token {
public:
    /// Value is set during token construction.
    ///
    /// @param addr IP address to be represented as a constant string
    TokenIpAddress(const std::string& addr);

    /// @brief Token evaluation (puts value of the constant string on
    /// the stack after decoding)
    ///
    /// @param pkt (ignored)
    /// @param values (represented IP address will be pushed here)
    void evaluate(Pkt& pkt, ValueStack& values);

protected:
    ///< Constant value (empty string if the IP address cannot be converted)
    std::string value_;
};

/// @brief Token representing an IP address as a string
///
/// This token holds the value of an IP address as a string, for instance
/// 10.0.0.1 is '10.0.0.1'
class TokenIpAddressToText : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenIpAddressToText() {}

    /// @brief Token evaluation (puts value of the string on the stack after
    /// decoding)
    ///
    /// @param pkt (ignored)
    /// @param values (represented IP address as a string will be pushed here)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token representing an 8 bit integer as a string
///
/// This token holds the value of an 8 bit integer as a string, for instance
/// 0xff is '-1'
class TokenInt8ToText : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenInt8ToText() {}

    /// @brief Token evaluation (puts value of the string on the stack after
    /// decoding)
    ///
    /// @param pkt (ignored)
    /// @param values (represented 8 bit integer as a string will be pushed
    /// here)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token representing a 16 bit integer as a string
///
/// This token holds the value of a 16 bit integer as a string, for instance
/// 0xffff is '-1'
class TokenInt16ToText : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenInt16ToText() {}

    /// @brief Token evaluation (puts value of the string on the stack after
    /// decoding)
    ///
    /// @param pkt (ignored)
    /// @param values (represented 16 bit integer as a string will be pushed
    /// here)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token representing a 32 bit integer as a string
///
/// This token holds the value of a 32 bit integer as a string, for instance
/// 0xffffffff is '-1'
class TokenInt32ToText : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenInt32ToText() {}

    /// @brief Token evaluation (puts value of the string on the stack after
    /// decoding)
    ///
    /// @param pkt (ignored)
    /// @param values (represented 32 bit integer as a string will be pushed
    /// here)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token representing an 8 bit unsigned integer as a string
///
/// This token holds the value of an 8 bit unsigned integer as a string, for
/// instance 0xff is '255'
class TokenUInt8ToText : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenUInt8ToText() {}

    /// @brief Token evaluation (puts value of the string on the stack after
    /// decoding)
    ///
    /// @param pkt (ignored)
    /// @param values (represented 8 bit unsigned integer as a string will be
    /// pushed here)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token representing a 16 bit unsigned integer as a string
///
/// This token holds the value of a 16 bit unsigned integer as a string, for
/// instance 0xffff is '65535'
class TokenUInt16ToText : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenUInt16ToText() {}

    /// @brief Token evaluation (puts value of the string on the stack after
    /// decoding)
    ///
    /// @param pkt (ignored)
    /// @param values (represented 16 bit unsigned integer as a string will be
    /// pushed here)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token representing a 32 bit unsigned integer as a string
///
/// This token holds the value of a 32 bit unsigned integer as a string, for
/// instance 0xffffffff is '4294967295'
class TokenUInt32ToText : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenUInt32ToText() {}

    /// @brief Token evaluation (puts value of the string on the stack after
    /// decoding)
    ///
    /// @param pkt (ignored)
    /// @param values (represented 32 bit unsigned integer as a string will be
    /// pushed here)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token that represents a value of an option
///
/// This represents a reference to a given option, e.g. in the expression
/// option[vendor-class].text == "MSFT", it represents
/// option[vendor-class].text
///
/// During the evaluation it tries to extract the value of the specified
/// option. If the option is not found, an empty string ("") is returned
/// (or "false" when the representation is EXISTS).
class TokenOption : public Token {
public:

    /// @brief Token representation type.
    ///
    /// There are many possible ways in which option can be presented.
    /// Currently the textual, hexadecimal and exists representations are
    /// supported. The type of representation is specified in the
    /// constructor and it affects the value generated by the
    /// @c TokenOption::evaluate function.
    enum RepresentationType {
        TEXTUAL,
        HEXADECIMAL,
        EXISTS
    };

    /// @brief Constructor that takes an option code as a parameter
    ///
    /// Note: There is no constructor that takes option_name, as it would
    /// introduce complex dependency of the libkea-eval on libdhcpsrv.
    ///
    /// @param option_code code of the option to be represented.
    /// @param rep_type Token representation type.
    TokenOption(const uint16_t option_code, const RepresentationType& rep_type)
        : option_code_(option_code), representation_type_(rep_type) {}

    /// @brief Evaluates the values of the option
    ///
    /// This token represents a value of the option, so this method attempts
    /// to extract the option from the packet and put its value on the stack.
    /// If the option is not there, an empty string ("") is put on the stack.
    ///
    /// @param pkt specified option will be extracted from this packet (if present)
    /// @param values value of the option will be pushed here (or "")
    void evaluate(Pkt& pkt, ValueStack& values);

    /// @brief Returns option-code
    ///
    /// This method is used in testing to determine if the parser had
    /// instantiated TokenOption with correct parameters.
    ///
    /// @return option-code of the option this token expects to extract.
    uint16_t getCode() const {
        return (option_code_);
    }

    /// @brief Returns representation-type
    ///
    /// This method is used in testing to determine if the parser had
    /// instantiated TokenOption with correct parameters.
    ///
    /// @return representation-type of the option this token expects to use.
    RepresentationType getRepresentation() const {
        return (representation_type_);
    }

protected:
    /// @brief Attempts to retrieve an option
    ///
    /// For this class it simply attempts to retrieve the option from the packet,
    /// but there may be derived classes that would attempt to extract it from
    /// other places (e.g. relay option, or as a suboption of other specific option).
    ///
    ///
    /// @param pkt the option will be retrieved from here
    /// @return option instance (or NULL if not found)
    virtual OptionPtr getOption(Pkt& pkt);

    /// @brief Auxiliary method that puts string representing a failure
    ///
    /// Depending on the representation type, this is either "" or "false".
    ///
    /// @param values a string representing failure will be pushed here.
    /// @return value pushed
    virtual std::string pushFailure(ValueStack& values);

    uint16_t option_code_; ///< Code of the option to be extracted
    RepresentationType representation_type_; ///< Representation type.
};

/// @brief Represents a sub-option inserted by the DHCPv4 relay.
///
/// DHCPv4 relays insert sub-options in option 82. This token attempts to extract
/// such sub-options. Note in DHCPv6 it is radically different (possibly
/// many encapsulation levels), thus there are separate classes for v4 and v6.
///
/// This token can represent the following expressions:
/// relay[13].text - Textual representation of sub-option 13 in RAI (option 82)
/// relay[13].hex  - Binary representation of sub-option 13 in RAI (option 82)
/// relay[vendor-class].text - Text representation of sub-option X in RAI (option 82)
/// relay[vendor-class].hex - Binary representation of sub-option X in RAI (option 82)
class TokenRelay4Option : public TokenOption {
public:

    /// @brief Constructor for extracting sub-option from RAI (option 82)
    ///
    /// @param option_code code of the requested sub-option
    /// @param rep_type code representation (currently .hex and .text are supported)
    TokenRelay4Option(const uint16_t option_code,
                      const RepresentationType& rep_type);

protected:
    /// @brief Attempts to obtain specified sub-option of option 82 from the packet
    /// @param pkt DHCPv4 packet (that hopefully contains option 82)
    /// @return found sub-option from option 82
    virtual OptionPtr getOption(Pkt& pkt);
};

/// @brief Token that represents a value of an option within a DHCPv6 relay
/// encapsulation
///
/// This represents a reference to a given option similar to TokenOption
/// but from within the information from a relay.  In the expression
/// relay6[nest-level].option[option-code], nest-level indicates which
/// of the relays to examine and option-code which option to extract.
///
/// During the evaluation it tries to extract the value of the specified
/// option from the requested relay block.  If the relay block doesn't
/// exist or the option is not found an empty string ("") is returned
/// (or "false" when the representation is EXISTS).
///
/// The nesting level can go from 0 (closest to the server) to 31,
/// or from -1 (closest to the client) to -32
class TokenRelay6Option : public TokenOption {
public:
    /// @brief Constructor that takes a nesting level and an option
    /// code as parameters.
    ///
    /// @param nest_level the nesting for which relay to examine.
    /// @param option_code code of the option.
    /// @param rep_type Token representation type.
    TokenRelay6Option(const int8_t nest_level, const uint16_t option_code,
                      const RepresentationType& rep_type)
        : TokenOption(option_code, rep_type), nest_level_(nest_level) {}

    /// @brief Returns nest-level
    ///
    /// This method is used in testing to determine if the parser has
    /// instantiated TokenRelay6Option with correct parameters.
    ///
    /// @return nest-level of the relay block this token expects to use
    /// for extraction.
    int8_t getNest() const {
        return (nest_level_);
    }

protected:
    /// @brief Attempts to obtain specified option from the specified relay block
    /// @param pkt DHCPv6 packet that hopefully contains the proper relay block
    /// @return option instance if available
    virtual OptionPtr getOption(Pkt& pkt);

    int8_t nest_level_; ///< nesting level of the relay block to use
};

/// @brief Token that represents meta data of a DHCP packet.
///
/// For example in the expression pkt.iface == 'eth0'
/// this token represents the pkt.iface expression.
///
/// Currently supported meta datas are:
/// - iface (incoming/outgoinginterface name)
/// - src   (source IP address, 4 or 16 octets)
/// - dst   (destination IP address, 4 or 16 octets)
/// - len   (length field in the UDP header, padded to 4 octets)
class TokenPkt : public Token {
public:

    /// @brief enum value that determines the field.
    enum MetadataType {
        IFACE, ///< interface name (string)
        SRC,   ///< source (IP address)
        DST,   ///< destination (IP address)
        LEN    ///< length (4 octets)
    };

    /// @brief Constructor (does nothing)
    TokenPkt(const MetadataType type)
        : type_(type) {}

    /// @brief Gets a value from the specified packet.
    ///
    /// Evaluation uses metadata available in the packet. It does not
    /// require any values to be present on the stack.
    ///
    /// @param pkt - metadata will be extracted from here
    /// @param values - stack of values (1 result will be pushed)
    void evaluate(Pkt& pkt, ValueStack& values);

    /// @brief Returns metadata type
    ///
    /// This method is used only in tests.
    /// @return type of the metadata.
    MetadataType getType() {
        return (type_);
    }

private:
    /// @brief Specifies metadata of the DHCP packet
    MetadataType type_;
};

/// @brief Token that represents fields of a DHCPv4 packet.
///
/// For example in the expression pkt4.chaddr == 0x0102030405
/// this token represents the pkt4.chaddr expression.
///
/// Currently supported fields are:
/// - chaddr (client hardware address, hlen [0..16] octets)
/// - giaddr (relay agent IP address, 4 octets)
/// - ciaddr (client IP address, 4 octets)
/// - yiaddr ('your' (client) IP address, 4 octets)
/// - siaddr (next server IP address, 4 octets)
/// - hlen   (hardware address length, padded to 4 octets)
/// - htype  (hardware address type, padded to 4 octets)
class TokenPkt4 : public Token {
public:

    /// @brief enum value that determines the field.
    enum FieldType {
        CHADDR, ///< chaddr field (up to 16 bytes link-layer address)
        GIADDR, ///< giaddr (IPv4 address)
        CIADDR, ///< ciaddr (IPv4 address)
        YIADDR, ///< yiaddr (IPv4 address)
        SIADDR, ///< siaddr (IPv4 address)
        HLEN,   ///< hlen (hardware address length)
        HTYPE,  ///< htype (hardware address type)
        MSGTYPE, ///< message type (not really a field, content of option 53)
        TRANSID, ///< transaction-id (xid)
    };

    /// @brief Constructor (does nothing)
    TokenPkt4(const FieldType type)
        : type_(type) {}

    /// @brief Gets a value from the specified packet.
    ///
    /// Evaluation uses fields available in the packet. It does not require
    /// any values to be present on the stack.
    ///
    /// @throw EvalTypeError when called for DHCPv6 packet
    ///
    /// @param pkt - fields will be extracted from here
    /// @param values - stack of values (1 result will be pushed)
    void evaluate(Pkt& pkt, ValueStack& values);

    /// @brief Returns field type
    ///
    /// This method is used only in tests.
    /// @return type of the field.
    FieldType getType() {
        return (type_);
    }

private:
    /// @brief Specifies field of the DHCPv4 packet
    FieldType type_;
};

/// @brief Token that represents fields of DHCPv6 packet.
///
/// For example in the expression pkt6.msgtype == 1
/// this token represents the message type of the DHCPv6 packet.
/// The integer values are placed on the value stack as 4 byte
/// strings.
///
/// Currently supported fields are:
/// - msgtype
/// - transid
class TokenPkt6 : public Token {
public:
    /// @brief enum value that determines the field.
    enum FieldType {
        MSGTYPE, ///< msg type
        TRANSID  ///< transaction id (integer but manipulated as a string)
    };

    /// @brief Constructor (does nothing)
    TokenPkt6(const FieldType type)
        : type_(type) {}

    /// @brief Gets a value of the specified packet.
    ///
    /// The evaluation uses fields that are available in the packet.  It does not
    /// require any values to be present on the stack.
    ///
    /// @throw EvalTypeError when called for a DHCPv4 packet
    ///
    /// @param pkt - packet from which to extract the fields
    /// @param values - stack of values, 1 result will be pushed
    void evaluate(Pkt& pkt, ValueStack& values);

    /// @brief Returns field type
    ///
    /// This method is used only in tests.
    /// @return type of the field.
    FieldType getType() {
        return (type_);
    }

private:
    /// @brief Specifies field of the DHCPv6 packet to get
    FieldType type_;
};

/// @brief Token that represents a value of a field within a DHCPv6 relay
/// encapsulation
///
/// This represents a reference to a field with a given DHCPv6 relay encapsulation.
/// In the expression relay6[nest-level].field-name, nest-level indicates which of
/// the relays to examine and field-name which of the fields to extract.
///
/// During the evaluation it tries to extract the value of the specified
/// field from the requested relay block.  If the relay block doesn't exist
/// an empty string ("") is returned.  If the relay block does exist the field
/// is always returned as a 16 byte IPv6 address.  As the relay may not have
/// set the field it may be 0s.
///
/// The nesting level can go from 0 (closest to the server) to 31,
/// or from -1 (closest to the client) to -32
class TokenRelay6Field : public Token {
public:

    /// @brief enum value that determines the field.
    enum FieldType {
        PEERADDR, ///< Peer address field (IPv6 address)
        LINKADDR  ///< Link address field (IPv6 address)
    };

    /// @brief Constructor that takes a nesting level and field type
    /// as parameters.
    ///
    /// @param nest_level the nesting level for which relay to examine.
    /// @param type which field to extract.
    TokenRelay6Field(const int8_t nest_level, const FieldType type)
        : nest_level_(nest_level), type_(type) {}

    /// @brief Extracts the specified field from the requested relay
    ///
    /// Evaluation uses fields available in the packet.  It does not require
    /// any values to be present on the stack.
    ///
    /// @param pkt fields will be extracted from here
    /// @param values - stack of values (1 result will be pushed)
    void evaluate(Pkt& pkt, ValueStack& values);

    /// @brief Returns nest-level
    ///
    /// This method is used in testing to determine if the parser has
    /// instantiated TokenRelay6Field with correct parameters.
    ///
    /// @return nest-level of the relay block this token expects to use
    /// for extraction.
    int8_t getNest() const {
        return (nest_level_);
    }

    /// @brief Returns field type
    ///
    /// This method is used only in testing to determine if the parser has
    /// instantiated TokenRelay6Field with correct parameters.
    ///
    /// @return type of the field.
    FieldType getType() {
        return (type_);
    }

protected:
    /// @brief Specifies field of the DHCPv6 relay option to get
    int8_t nest_level_; ///< nesting level of the relay block to use
    FieldType type_; ///< field to get
};

/// @brief Token that represents equality operator (compares two other tokens)
///
/// For example in the expression option[vendor-class].text == "MSFT"
/// this token represents the equal (==) sign.
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
    void evaluate(Pkt& pkt, ValueStack& values);
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
    /// start is the position from which the code starts extracting the substring.
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
    /// @throw EvalTypeError if start is not a number or length a number or
    ///        the special value "all".
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (3 arguments will be popped, 1 result
    ///        will be pushed)
    void evaluate(Pkt& pkt, ValueStack& values);
};

class TokenSplit : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenSplit() {}

    /// @brief Extract a field from a delimited string
    ///
    /// Evaluation does not use packet information.  It requires at least
    /// three values to be present on the stack.  It will consume the top
    /// three values on the stack as parameters and push the resulting substring
    /// onto the stack.  From the top it expects the values on the stack as:
    /// -  field
    /// -  delims
    /// -  str
    ///
    /// str is the string to split.  If it is empty, an empty
    /// string is pushed onto the value stack.
    /// delims is string of character delimiters by which to split str. If it is
    /// empty the entire value of str will be pushed on onto the value stack.
    /// field is the field number (starting at 1) of the desired field.  If it is
    /// out of range an empty string is pushed on the value stack.
    ///
    /// The following examples all use the base string "one.two..four" and shows
    /// the value returned for a given field:
    /// ```
    /// field => value
    /// --------------
    /// -  0  => ""
    /// -  1  => "one"
    /// -  2  => "two"
    /// -  3  => ""
    /// -  4  => "four"
    /// -  5  => ""
    /// ```
    ///
    /// @throw EvalBadStack if there are less than 3 values on stack
    /// @throw EvalTypeError if field is not a number
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (3 arguments will be popped, 1 result
    ///        will be pushed)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token that represents concat operator (concatenates two other tokens)
///
/// For example in the sub-expression "concat('foo','bar')" the result
/// of the evaluation is "foobar"
/// For user convenience the "'foo' + 'bar'" alternative does the same.
class TokenConcat : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenConcat() {}

    /// @brief Concatenate two values.
    ///
    /// Evaluation does not use packet information, but rather consumes the last
    /// two parameters. It does a simple string concatenation. It requires
    /// at least two parameters to be present on stack.
    ///
    /// @throw EvalBadStack if there are less than 2 values on stack
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (2 arguments will be popped, 1 result
    ///        will be pushed)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token that represents an alternative
///
/// For example in the sub-expression "ifelse(cond, iftrue, iffalse)"
/// the boolean "cond" expression is evaluated, if it is true then
/// the "iftrue" value is returned else the "iffalse" value is returned.
/// Please note that "iftrue" and "iffalse" must be plain string (vs. boolean)
/// expressions and they are always evaluated. If you want a similar
/// operator on boolean expressions it can be built from "and", "or" and
/// "not" boolean operators.
class TokenIfElse : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenIfElse() { }

    /// @brief Alternative.
    ///
    /// Evaluation does not use packet information, but rather consumes the
    /// last three results. It does a simple string comparison on the
    /// condition (third value on the stack) which is required to be
    /// either "true" or "false", and leaves the second and first
    /// value if the condition is "true" or "false".
    ///
    /// @throw EvalBadStack if there are less than 3 values on stack
    /// @throw EvalTypeError if the third value (the condition) is not
    ///        either "true" or "false"
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (two items are removed)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token that converts to hexadecimal string
///
/// For example in the sub-expression "hexstring(pkt4.mac, ':')"
/// the binary MAC address is converted to its usual hexadecimal
/// representation as a list of (6) pairs of hexadecimal digits
/// separated by colons (':').
/// Please note the token is named TokenToHexString when the syntax
/// use the hexstring name without a leading "to".
class TokenToHexString : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenToHexString() { }

    /// @brief Convert a binary value to its hexadecimal string representation
    ///
    /// Evaluation does not use packet information. It requires at least
    /// two values to be present on the stack. It will consume the top
    /// two values on the stack as parameters and push the resulting
    /// hexadecimal string onto the stack.
    /// From the top it expects the values on the stack as:
    /// - separator
    /// - binary
    ///
    /// binary is the binary value (note it can be any value, i.e.
    /// it is not checked to really be not printable).
    /// separator is literal for instance '-' or ':'. The empty separator
    /// means no separator.
    ///
    /// The following example use a binary MAC address 06:ce:8f:55:b3:33:
    /// - mac, '-' => "06-ce-8f-55-b3-33"
    ///
    /// @throw EvalBadStack if there are less than 2 values on stack
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (2 arguments will be popped, 1 result
    ///        will be pushed)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token that represents logical negation operator
///
/// For example in the expression "not(option[vendor-class].text == 'MSF')"
/// this token represents the leading "not"
class TokenNot : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenNot() {}

    /// @brief Logical negation.
    ///
    /// Evaluation does not use packet information, but rather consumes the last
    /// result. It does a simple string comparison and sets the value to
    /// either "true" or "false". It requires at least one value to be
    /// present on stack and to be either "true" or "false".
    ///
    /// @throw EvalBadStack if there are less than 1 value on stack
    /// @throw EvalTypeError if the top value on the stack is not either
    ///        "true" or "false"
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (logical top value negated)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token that represents logical and operator
///
/// For example "option[10].exists and option[11].exists"
class TokenAnd : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenAnd() {}

    /// @brief Logical and.
    ///
    /// Evaluation does not use packet information, but rather consumes the last
    /// two parameters. It returns "true" if and only if both are "true".
    /// It requires at least two logical (i.e., "true" or "false') values
    /// present on stack.
    ///
    /// @throw EvalBadStack if there are less than 2 values on stack
    /// @throw EvalTypeError if one of the 2 values on stack is not
    ///        "true" or "false"
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (2 arguments will be popped, 1 result
    ///        will be pushed)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token that represents logical or operator
///
/// For example "option[10].exists or option[11].exists"
class TokenOr : public Token {
public:
    /// @brief Constructor (does nothing)
    TokenOr() {}

    /// @brief Logical or.
    ///
    /// Evaluation does not use packet information, but rather consumes the last
    /// two parameters. It returns "false" if and only if both are "false".
    /// It requires at least two logical (i.e., "true" or "false') values
    /// present on stack.
    ///
    /// @throw EvalBadStack if there are less than 2 values on stack
    /// @throw EvalTypeError if one of the 2 values on stack is not
    ///        "true" or "false"
    ///
    /// @param pkt (unused)
    /// @param values - stack of values (2 arguments will be popped, 1 result
    ///        will be pushed)
    void evaluate(Pkt& pkt, ValueStack& values);
};

/// @brief Token that represents client class membership
///
/// For example "not member('foo')" is the complement of class foo
class TokenMember : public Token {
public:
    /// @brief Constructor
    ///
    /// @param client_class client class name
    TokenMember(const std::string& client_class)
        : client_class_(client_class){
    }

    /// @brief Token evaluation (check if client_class_ was added to
    /// packet client classes)
    ///
    /// @param pkt the class name will be check from this packet's client classes
    /// @param values true (if found) or false (if not found) will be pushed here
    void evaluate(Pkt& pkt, ValueStack& values);

    /// @brief Returns client class name
    ///
    /// This method is used in testing to determine if the parser had
    /// instantiated TokenMember with correct parameters.
    ///
    /// @return client class name the token expects to check membership.
    const ClientClass& getClientClass() const {
        return (client_class_);
    }

protected:
    /// @brief The client class name
    ClientClass client_class_;
};

/// @brief Token that represents vendor options in DHCPv4 and DHCPv6.
///
/// It covers vendor independent vendor information option (125, DHCPv4)
/// and vendor option (17, DHCPv6). Since both of those options may have
/// suboptions, this class is derived from TokenOption and leverages its
/// ability to operate on sub-options. It also adds additional capabilities.
/// In particular, it allows retrieving enterprise-id.
///
/// It can represent the following expressions:
/// vendor[4491].exists - if vendor option with enterprise-id = 4491 exists
/// vendor[*].exists - if any vendor option exists
/// vendor.enterprise - returns enterprise-id from vendor option
/// vendor[4491].option[1].exists - check if suboption 1 exists for vendor 4491
/// vendor[4491].option[1].hex - return content of suboption 1 for vendor 4491
class TokenVendor : public TokenOption {
public:

    /// @brief Specifies a field of the vendor option
    enum FieldType {
        SUBOPTION,     ///< If this token fetches a suboption, not a field.
        ENTERPRISE_ID, ///< enterprise-id field (vendor-info, vendor-class)
        EXISTS,        ///< vendor[123].exists
        DATA           ///< data chunk, used in derived vendor-class only
    };

    /// @brief Constructor used for accessing a field
    ///
    /// @param u universe (either V4 or V6)
    /// @param vendor_id specifies enterprise-id (0 means any)
    /// @param field specifies which field should be returned
    TokenVendor(Option::Universe u, uint32_t vendor_id, FieldType field);


    /// @brief Constructor used for accessing an option
    ///
    /// This constructor is used for accessing suboptions. In general
    /// option_code is mandatory, except when repr is EXISTS. For
    /// option_code = 0 and repr = EXISTS, the token will return true
    /// if the whole option exists, not suboptions.
    ///
    /// @param u universe (either V4 or V6)
    /// @param vendor_id specifies enterprise-id (0 means any)
    /// @param repr representation type (hex or exists)
    /// @param option_code sub-option code
    TokenVendor(Option::Universe u, uint32_t vendor_id, RepresentationType repr,
                uint16_t option_code = 0);

    /// @brief Returns enterprise-id
    ///
    /// Used in tests only.
    ///
    /// @return enterprise-id
    uint32_t getVendorId() const;

    /// @brief Returns field.
    ///
    /// Used in tests only.
    ///
    /// @return field type.
    FieldType getField() const;

    /// @brief This is a method for evaluating a packet.
    ///
    /// Depending on the value of vendor_id, field type, representation and
    /// option code, it will attempt to return specified characteristic of the
    /// vendor option
    ///
    /// If vendor-id is specified, check only option with that particular
    /// enterprise-id. If vendor-id is 0, check any vendor option, regardless
    /// of its enterprise-id value.
    ///
    /// If FieldType is NONE, get specified suboption represented by option_code
    /// and represent it as specified by repr.
    ///
    /// If FieldType is ENTERPRISE_ID, return value of the enterprise-id field
    /// or "" if there's no vendor option.
    ///
    /// @throw EvalTypeError for any other FieldType values.
    ///
    /// The parameters passed are:
    ///
    /// @param pkt - vendor options will be searched for here.
    /// @param values - the evaluated value will be pushed here.
    virtual void evaluate(Pkt& pkt, ValueStack& values);

protected:
    /// @brief Attempts to get a suboption.
    ///
    /// This method overrides behavior of TokenOption method. It attempts to retrieve
    /// the sub-option of the vendor option. Using derived method allows usage of
    /// TokenOption routines.
    ///
    /// @param pkt vendor option will be searched here.
    /// @return suboption of the vendor option (if exists)
    virtual OptionPtr getOption(Pkt& pkt);

    /// @brief Universe (V4 or V6)
    ///
    /// We need to remember it, because depending on the universe, the code needs
    /// to retrieve either option 125 (DHCPv4) or 17 (DHCPv6).
    Option::Universe universe_;

    /// @brief Enterprise-id value
    ///
    /// Yeah, I know it technically should be called enterprise-id, but that's
    /// too long and everyone calls it vendor-id.
    uint32_t vendor_id_;

    /// @brief Specifies which field should be accessed.
    FieldType field_;
};

/// @brief Token that represents vendor class options in DHCPv4 and DHCPv6.
///
/// It covers vendor independent vendor information option (124, DHCPv4)
/// and vendor option (16, DHCPv6). Contrary to vendor options, vendor class
/// options don't have suboptions, but have data chunks (tuples) instead.
/// Therefore they're not referenced by option codes, but by indexes.
/// The first data chunk is data[0], the second is data[1] etc.
///
/// This class is derived from OptionVendor to take advantage of the
/// enterprise handling field and field type.
///
/// It can represent the following expressions:
/// vendor-class[4491].exists
/// vendor-class[*].exists
/// vendor-class[*].enterprise
/// vendor-class[4491].data - content of the opaque-data of the first tuple
/// vendor-class[4491].data[3] - content of the opaque-data of the 4th tuple
class TokenVendorClass : public TokenVendor {
public:

    /// @brief This constructor is used to access fields.
    ///
    /// @param u universe (V4 or V6)
    /// @param vendor_id value of enterprise-id field (0 means any)
    /// @param repr representation type (EXISTS or HEX)
    TokenVendorClass(Option::Universe u, uint32_t vendor_id, RepresentationType repr);

    /// @brief This constructor is used to access data chunks.
    ///
    /// @param u universe (V4 or V6)
    /// @param vendor_id value of enterprise-id field (0 means any)
    /// @param field type of the field (usually DATA or ENTERPRISE)
    /// @param index specifies which data chunk to retrieve
    TokenVendorClass(Option::Universe u, uint32_t vendor_id, FieldType field,
                     uint16_t index = 0);

    /// @brief Returns data index.
    ///
    /// Used in testing.
    /// @return data index (specifies which data chunk to retrieve)
    uint16_t getDataIndex() const;

protected:

    /// @brief This is a method for evaluating a packet.
    ///
    /// Depending on the value of vendor_id, field type, representation and
    /// option code, it will attempt to return specified characteristic of the
    /// vendor option
    ///
    /// If vendor-id is specified, check only option with that particular
    /// enterprise-id. If vendor-id is 0, check any vendor option, regardless
    /// of its enterprise-id value.
    ///
    /// If FieldType is ENTERPRISE_ID, return value of the enterprise-id field
    /// or "" if there's no vendor option.
    ///
    /// If FieldType is DATA, get specified data chunk represented by index_.
    ///
    /// If FieldType is EXISTS, return true if vendor-id matches.
    ///
    /// @throw EvalTypeError for any other FieldType values.
    ///
    /// The parameters passed are:
    ///
    /// @param pkt - vendor options will be searched for here.
    /// @param values - the evaluated value will be pushed here.
    void evaluate(Pkt& pkt, ValueStack& values);

    /// @brief Data chunk index.
    uint16_t index_;
};

/// @brief Token that represents sub-options in DHCPv4 and DHCPv6.
///
/// It covers any options which encapsulate sub-options, for instance
/// dhcp-agent-options (82, DHCPv4) or rsoo (66, DHCPv6).
/// This class is derived from TokenOption and leverages its ability
/// to operate on sub-options. It also adds additional capabilities.
///
/// Note: @c TokenSubOption virtually derives @c TokenOption because both
/// classes are inherited together in more complex classes in other parts of
/// the code. This makes the base class @c TokenOption to exist only once in
/// such complex classes.
///
/// It can represent the following expressions:
/// option[149].exists - check if option 149 exists
/// option[149].option[1].exists - check if suboption 1 exists in the option 149
/// option[149].option[1].hex - return content of suboption 1 for option 149
class TokenSubOption : public virtual TokenOption {
public:

    /// @note Does not define its own representation type:
    /// simply use the @c TokenOption::RepresentationType

    /// @brief Constructor that takes an option and sub-option codes as parameter
    ///
    /// Note: There is no constructor that takes names.
    ///
    /// @param option_code code of the parent option.
    /// @param sub_option_code code of the sub-option to be represented.
    /// @param rep_type Token representation type.
    TokenSubOption(const uint16_t option_code,
                   const uint16_t sub_option_code,
                   const RepresentationType& rep_type)
        : TokenOption(option_code, rep_type), sub_option_code_(sub_option_code) {}

    /// @brief This is a method for evaluating a packet.
    ///
    /// This token represents a value of the sub-option, so this method
    /// attempts to extract the parent option from the packet and when
    /// it succeeds to extract the sub-option from the option and
    /// its value on the stack.
    /// If the parent option or the sub-option is not there, an empty
    /// string ("") is put on the stack.
    ///
    /// @param pkt specified parent option will be extracted from this packet
    /// @param values value of the sub-option will be pushed here (or "")
    virtual void evaluate(Pkt& pkt, ValueStack& values);

    /// @brief Returns sub-option-code
    ///
    /// This method is used in testing to determine if the parser had
    /// instantiated TokenSubOption with correct parameters.
    ///
    /// @return option-code of the sub-option this token expects to extract.
    uint16_t getSubCode() const {
        return (sub_option_code_);
    }

protected:
    /// @brief Attempts to retrieve a sub-option.
    ///
    /// @param parent the sub-option will be retrieved from here
    /// @return sub-option instance (or NULL if not found)
    virtual OptionPtr getSubOption(const OptionPtr& parent);

    uint16_t sub_option_code_; ///< Code of the sub-option to be extracted
};

} // end of isc::dhcp namespace
} // end of isc namespace

#endif
