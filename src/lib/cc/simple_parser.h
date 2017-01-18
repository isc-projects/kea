// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SIMPLE_PARSER_H
#define SIMPLE_PARSER_H

#include <cc/data.h>
#include <vector>
#include <string>
#include <stdint.h>
#include <limits>

namespace isc {
namespace data {

/// This array defines a single entry of default values
struct SimpleDefault {
    SimpleDefault(const char* name, isc::data::Element::types type, const char* value)
        :name_(name), type_(type), value_(value) {}
    std::string name_;
    const isc::data::Element::types type_;
    const char* value_;
};

/// This specifies all default values in a given scope (e.g. a subnet)
typedef std::vector<SimpleDefault> SimpleDefaults;

/// This defines a list of all parameters that are derived (or inherited) between
/// contexts
typedef std::vector<std::string> ParamsList;


/// @brief A simple parser
///
/// This class is intended to be a simpler replacement for @ref
/// isc::dhcp::DhcpConfigParser. This class has been initially created to
/// facilitate DHCPv4 and DHCPv6 servers' configuration parsing. Thus examples
/// provided herein are related to DHCP configuration. Nevertheless, this is a
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
    static size_t setListDefaults(isc::data::ElementPtr list,
                                  const SimpleDefaults& default_values);

    /// @brief Utility method that returns position of an element
    ///
    /// It's mostly useful for logging. When any necessary parameter is
    /// missing (either parent is null or it doesn't contain specified
    /// name) ZERO_POSITION is returned.
    ///
    /// @param name position of that element will be returned
    /// @param parent parent element (optional)
    /// @return position of the element specified.
    static const data::Element::Position&
    getPosition(const std::string& name, const data::ConstElementPtr parent);

 protected:

    /// @brief Returns a string parameter from a scope
    ///
    /// Unconditionally returns a parameter. If the parameter is not there or
    /// is not of appropriate type, BadValue exception is thrown.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a string value of the parameter
    static std::string getString(isc::data::ConstElementPtr scope,
                                 const std::string& name);

    /// @brief Returns an integer parameter from a scope
    ///
    /// Unconditionally returns a parameter. If the parameter is not there or
    /// is not of appropriate type, BadValue exception is thrown.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return an integer value of the parameter
    static int64_t getInteger(isc::data::ConstElementPtr scope,
                              const std::string& name);

    /// @brief Returns a boolean parameter from a scope
    ///
    /// Unconditionally returns a parameter. If the parameter is not there or
    /// is not of appropriate type, BadValue exception is thrown.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a boolean value of the parameter
    static bool getBoolean(isc::data::ConstElementPtr scope,
                           const std::string& name);

    /// @brief Returns an integer value with range checking
    ///
    /// This template should be instantied in parsers when useful
    ///
    /// @tparam int_type the integer type e.g. uint32_t
    /// @tparam out_of_range always @c isc::dhcp::DhcpConfigError
    /// @param name name of the parameter for error report
    /// @param value value of the parameter
    /// @throw isc::data::TypeError when the value is not an integer
    /// @throw out_of_range when the value does not fit in int_type
    template <typename int_type, class out_of_range> int_type
    extractInt(const std::string& name, ConstElementPtr value) const {
        int64_t val_int = value->intValue();
        if ((val_int < std::numeric_limits<int_type>::min()) ||
            (val_int > std::numeric_limits<int_type>::max())) {
            isc_throw(out_of_range, "out of range value (" << val_int
                  << ") specified for parameter '" << name
                      << "' (" << value->getPosition() << ")");
        }
        return (static_cast<int_type>(val_int));
    }
};

};
};

#endif
