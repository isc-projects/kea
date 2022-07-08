// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SIMPLE_PARSER_H
#define SIMPLE_PARSER_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <util/triplet.h>
#include <map>
#include <vector>
#include <string>
#include <stdint.h>
#include <limits>

namespace isc {
namespace data {

/// This array defines a single entry of default values.
struct SimpleDefault {
    SimpleDefault(const char* name, isc::data::Element::types type, const char* value)
        :name_(name), type_(type), value_(value) {}
    std::string name_;
    const isc::data::Element::types type_;
    const char* value_;
};

/// This specifies all required keywords.
typedef std::vector<std::string> SimpleRequiredKeywords;

/// This specifies all accepted keywords with their types.
typedef std::map<std::string, isc::data::Element::types> SimpleKeywords;

/// This specifies all default values in a given scope (e.g. a subnet).
typedef std::vector<SimpleDefault> SimpleDefaults;

/// This defines a list of all parameters that are derived (or inherited) between
/// contexts.
typedef std::vector<std::string> ParamsList;


/// @brief A simple parser
///
/// This class is intended to be a simpler replacement for DhcpConfigParser.
/// This class has been initially created to facilitate DHCPv4 and
/// DHCPv6 servers' configuration parsing. Thus examples provided
/// herein are related to DHCP configuration. Nevertheless, this is a
/// generic class to be used in other modules too.
///
/// The simplification comes from several factors:
/// - no build/commit nonsense. There's a single step:
///   CfgStorage parse(ConstElementPtr json)
///   that converts JSON configuration into an object and returns it.
/// - no state kept. This greatly simplifies the parsers (no contexts, no child
///   parsers list, no separate storage for uint32, strings etc. In fact,
///   this base class is purely static. However, some derived classes may store
///   some state. Implementors are advised to store as little state as possible.
/// - no optional parameters (all are mandatory). This simplifies the parser,
///   but introduces a new step before parsing where we insert the default
///   values into client configuration before parsing. This is actually a good
///   thing, because we now have a clear picture of the default parameters as
///   they're defined in a single place (the DhcpConfigParser had the defaults
///   spread out in multiple files in multiple directories).
class SimpleParser {
public:

    /// @brief Checks that all required keywords are present.
    ///
    /// This method throws an exception when a required
    /// entry is not present in the given scope.
    ///
    /// @param required Required keywords.
    /// @param scope Specified parameters which are checked.
    /// @throw DhcpConfigError if a required parameter is not present.
    static void checkRequired(const SimpleRequiredKeywords& required,
                              isc::data::ConstElementPtr scope);

    /// @brief Checks acceptable keywords with their expected type.
    ///
    /// This methods throws an exception when a not acceptable keyword
    /// is found or when an acceptable entry does not have the expected type.
    ///
    /// @param keywords The @c SimpleKeywords keywords and types map.
    /// @param scope Specified parameters which are checked.
    /// @throw DhcpConfigError if a not acceptable keyword is found.
    /// @throw DhcpConfigError if an acceptable entry does not have
    /// the expected type.
    static void checkKeywords(const SimpleKeywords& keywords,
                              isc::data::ConstElementPtr scope);

    /// @brief Derives (inherits) parameters from parent scope to a child
    ///
    /// This method derives parameters from the parent scope to the child,
    /// if there are no values specified in the child scope. For example,
    /// this method can be used to derive timers from global scope (e.g. for
    /// the whole DHCPv6 server) to a subnet scope. This method checks
    /// if the child scope doesn't have more specific values defined. If
    /// it doesn't, then the value from parent scope is copied over.
    ///
    /// @param parent scope to copy from (e.g. global)
    /// @param child scope to copy from (e.g. subnet)
    /// @param params names of the parameters to copy
    /// @return number of parameters copied
    static size_t deriveParams(isc::data::ConstElementPtr parent,
                               isc::data::ElementPtr child,
                               const ParamsList& params);

    /// @brief Sets the default values
    ///
    /// This method sets the default values for parameters that are not
    /// defined. The list of default values is specified by default_values.
    /// If not present, those will be inserted into the scope. If
    /// a parameter is already present, the default value will not
    /// be inserted.
    ///
    /// @param scope default values will be inserted here
    /// @param default_values list of default values
    /// @return number of parameters inserted
    static size_t setDefaults(isc::data::ElementPtr scope,
                              const SimpleDefaults& default_values);

    /// @brief Sets the default values for all entries in a list
    ///
    /// This is a simple utility method that iterates over all
    /// parameters in a list and calls setDefaults for each
    /// entry.
    ///
    /// @param list list to be iterated over
    /// @param default_values list of default values
    /// @return number of parameters inserted
    static size_t setListDefaults(isc::data::ConstElementPtr list,
                                  const SimpleDefaults& default_values);

    /// @brief Utility method that returns position of an element
    ///
    /// It's mostly useful for logging. If the element is missing
    /// the parent position is returned or ZERO_POSITION if parent
    /// is null.
    ///
    /// @param name position of that element will be returned
    /// @param parent parent element (optional)
    /// @return position of the element specified.
    static const data::Element::Position&
    getPosition(const std::string& name, const data::ConstElementPtr parent);

    /// @brief Returns a string parameter from a scope
    ///
    /// Unconditionally returns a parameter.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a string value of the parameter
    /// @throw DhcpConfigError if the parameter is not there or is not of
    /// appropriate type
    static std::string getString(isc::data::ConstElementPtr scope,
                                 const std::string& name);

    /// @brief Returns an integer parameter from a scope
    ///
    /// Unconditionally returns a parameter.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return an integer value of the parameter
    /// @throw DhcpConfigError if the parameter is not there or is not of
    /// appropriate type
    static int64_t getInteger(isc::data::ConstElementPtr scope,
                              const std::string& name);

    /// @brief Returns an integer parameter from a scope and checks its range
    ///
    /// Unconditionally returns a parameter. Checks that the value specified
    /// is in min =< X =< max range.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @param min minimum allowed value
    /// @param max maximum allowed value
    /// @return an integer value of the parameter
    /// @throw DhcpConfigError if the parameter is not there or is not of
    /// appropriate type.
    /// @throw OutOfRange if the parameter is out of range
    static int64_t getInteger(isc::data::ConstElementPtr scope,
                              const std::string& name,
                              int64_t min, int64_t max);

    /// @brief Returns a boolean parameter from a scope
    ///
    /// Unconditionally returns a parameter.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a boolean value of the parameter
    /// @throw DhcpConfigError if the parameter is not there or is not of
    /// appropriate type
    static bool getBoolean(isc::data::ConstElementPtr scope,
                           const std::string& name);


    /// @brief Returns a IOAddress parameter from a scope
    ///
    /// Unconditionally returns a parameter.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return an IOAddress representing the value of the parameter
    /// @throw DhcpConfigError if the parameter is not there or is not of
    /// appropriate type (or its conversion to IOAddress fails due to not
    /// being a proper address).
    static isc::asiolink::IOAddress
    getAddress(const ConstElementPtr& scope, const std::string& name);

    /// @brief Returns a floating point parameter from a scope
    ///
    /// Unconditionally returns a parameter.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a double value of the parameter
    /// @throw DhcpConfigError if the parameter is not there or is not
    /// an Element::real
    static double getDouble(const ConstElementPtr& scope,
                            const std::string& name);

protected:

    /// @brief Returns an integer value with range checking from a scope
    ///
    /// This template should be instantiated in parsers when useful
    ///
    /// @tparam int_type the integer type e.g. uint32_t
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter for error report
    /// @return a value of int_type
    /// @throw DhcpConfigError if the parameter is not there, is not of
    /// appropriate type or is out of type value range
    template <typename int_type> int_type
    getIntType(isc::data::ConstElementPtr scope,
               const std::string& name) {
        int64_t val_int = getInteger(scope, name);
        if ((val_int < std::numeric_limits<int_type>::min()) ||
            (val_int > std::numeric_limits<int_type>::max())) {
          isc_throw(isc::dhcp::DhcpConfigError,
                    "out of range value (" << val_int
                    << ") specified for parameter '" << name
                    << "' (" << getPosition(name, scope) << ")");
        }
        return (static_cast<int_type>(val_int));
    }

    /// @brief Returns a converted value from a scope
    ///
    /// This template should be instantiated in parsers when useful
    ///
    /// @tparam target_type the type of the result
    /// @tparam convert the conversion function std::string -> target_type
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter for error report
    /// @param type_name name of target_type for error report
    /// @return a converted value of target_type
    /// @throw DhcpConfigError if the parameter is not there, is not of
    /// appropriate type or can not be converted
    template <typename target_type,
              target_type convert(const std::string&)> target_type
    getAndConvert(isc::data::ConstElementPtr scope,
                  const std::string& name,
                  const std::string& type_name) {
        std::string str = getString(scope, name);
        try {
            return (convert(str));
        } catch (const std::exception&) {
            isc_throw(isc::dhcp::DhcpConfigError,
                      "invalid " << type_name << " (" << str
                      << ") specified for parameter '" << name
                      << "' (" << getPosition(name, scope) << ")");
        }
    }

public:
    /// @brief Returns a value converted to uint32_t
    ///
    /// Instantiation of getIntType() to uint32_t
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return an uint32_t value
    /// @throw isc::dhcp::DhcpConfigError when it is not an uint32_t
    uint32_t getUint32(isc::data::ConstElementPtr scope,
                       const std::string& name) {
        return (getIntType<uint32_t>(scope, name));
    }

    /// @brief Returns a value converted to uint16_t
    ///
    /// Instantiation of getIntType() to uint16_t
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return an uint16_t value
    /// @throw isc::dhcp::DhcpConfigError when it is not an uint16_t
    uint16_t getUint16(isc::data::ConstElementPtr scope,
                       const std::string& name) {
        return (getIntType<uint16_t>(scope, name));
    }

    /// @brief Get an uint8_t value
    ///
    /// Instantiation of getIntType() to uint8_t
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return uint8_t value
    /// @throw isc::dhcp::DhcpConfigError when it is not an uint8_t
    uint8_t getUint8(ConstElementPtr scope, const std::string& name) {
        return (getIntType<uint8_t>(scope, name));
    }

    /// @brief Parses an integer triplet
    ///
    /// Parses an integer triplet parameter of the form:
    ///
    ///    min-{name}, {name}, max-{name}
    ///
    /// @param scope Data element holding e.g. shared network configuration
    /// to be parsed.
    /// @param name Base name of the parameter.
    /// @return A triplet with the parsed value.
    const isc::util::Triplet<uint32_t> parseIntTriplet(const data::ConstElementPtr& scope,
                                                       const std::string& name);
};

}
}

#endif
