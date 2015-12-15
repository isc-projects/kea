// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP_CONFIG_PARSER_H
#define DHCP_CONFIG_PARSER_H

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <stdint.h>
#include <string>
#include <map>

namespace isc {
namespace dhcp {

/// An exception that is thrown if an error occurs while configuring
/// DHCP server.
class DhcpConfigError : public isc::Exception {
public:

    /// @brief constructor
    ///
    /// @param file name of the file, where exception occurred
    /// @param line line of the file, where exception occurred
    /// @param what text description of the issue that caused exception
    DhcpConfigError(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {}
};

/// @brief Forward declaration to DhcpConfigParser class.
///
/// It is only needed here to define types that are
/// based on this class before the class definition.
class DhcpConfigParser;

/// @brief a pointer to configuration parser
typedef boost::shared_ptr<DhcpConfigParser> ParserPtr;

/// @brief Collection of parsers.
///
/// This container is used to store pointer to parsers for a given scope.
typedef std::vector<ParserPtr> ParserCollection;

/// @brief Combination of parameter name and configuration contents
typedef std::pair<std::string, isc::data::ConstElementPtr> ConfigPair;

/// @brief Base abstract class for all DHCP parsers
///
/// Each instance of a class derived from this class parses one specific config
/// element. Sometimes elements are simple (e.g. a string) and sometimes quite
/// complex (e.g. a subnet). In such case, it is likely that a parser will
/// spawn child parsers to parse child elements in the configuration.
class DhcpConfigParser {
    ///
    /// @name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private to make it explicit that this is a
    /// pure base class.
    //@{
private:

    // Private constructor and assignment operator assures that nobody
    // will be able to copy or assign a parser. There are no defined
    // bodies for them.
    DhcpConfigParser(const DhcpConfigParser& source);
    DhcpConfigParser& operator=(const DhcpConfigParser& source);
protected:
    /// @brief The default constructor.
    ///
    /// This is intentionally defined as @c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    DhcpConfigParser() {}
public:
    /// The destructor.
    virtual ~DhcpConfigParser() {}
    //@}

    /// @brief Prepare configuration value.
    ///
    /// This method parses the "value part" of the configuration identifier
    /// that corresponds to this derived class and prepares a new value to
    /// apply to the server.
    ///
    /// This method must validate the given value both in terms of syntax
    /// and semantics of the configuration, so that the server will be
    /// validly configured at the time of @c commit().  Note: the given
    /// configuration value is normally syntactically validated, but the
    /// @c build() implementation must also expect invalid input.  If it
    /// detects an error it may throw an exception of a derived class
    /// of @c isc::Exception.
    ///
    /// Preparing a configuration value will often require resource
    /// allocation.  If it fails, it may throw a corresponding standard
    /// exception.
    ///
    /// This method is not expected to be called more than once in the
    /// life of the object. Although multiple calls are not prohibited
    /// by the interface, the behavior is undefined.
    ///
    /// @param config_value The configuration value for the identifier
    /// corresponding to the derived class.
    virtual void build(isc::data::ConstElementPtr config_value) = 0;

    /// @brief Apply the prepared configuration value to the server.
    ///
    /// This method is expected to be exception free, and, as a consequence,
    /// it should normally not involve resource allocation.
    /// Typically it would simply perform exception free assignment or swap
    /// operation on the value prepared in @c build().
    /// In some cases, however, it may be very difficult to meet this
    /// condition in a realistic way, while the failure case should really
    /// be very rare.  In such a case it may throw, and, if the parser is
    /// called via @c configureDhcp4Server(), the caller will convert the
    /// exception as a fatal error.
    ///
    /// This method is expected to be called after @c build(), and only once.
    /// The result is undefined otherwise.
    virtual void commit() = 0;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP_CONFIG_PARSER_H

