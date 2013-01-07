// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <stdint.h>
#include <string>

#ifndef DHCP4_CONFIG_PARSER_H
#define DHCP4_CONFIG_PARSER_H

/// @todo: This header file and its .cc counterpart are very similar between
/// DHCPv4 and DHCPv6. They should be merged. A ticket #2355.

namespace isc {
namespace dhcp {

class Dhcpv4Srv;

/// @brief a collection of elements that store uint32 values (e.g. renew-timer = 900)
typedef std::map<std::string, uint32_t> Uint32Storage;

/// @brief a collection of elements that store string values
typedef std::map<std::string, std::string> StringStorage;

/// An exception that is thrown if an error occurs while configuring an
/// \c Dhcpv4Srv object.
class Dhcp4ConfigError : public isc::Exception {
public:

    /// @brief constructor
    ///
    /// @param file name of the file, where exception occurred
    /// @param line line of the file, where exception occurred
    /// @param what text description of the issue that caused exception
    Dhcp4ConfigError(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {}
};

/// @brief Base abstract class for all DHCPv4 parsers
///
/// Each instance of a class derived from this class parses one specific config
/// element. Sometimes elements are simple (e.g. a string) and sometimes quite
/// complex (e.g. a subnet). In such case, it is likely that a parser will
/// spawn child parsers to parse child elements in the configuration.
/// @todo: Merge this class with DhcpConfigParser in src/bin/dhcp6
class Dhcp4ConfigParser {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private to make it explicit that this is a
    /// pure base class.
    //@{
private:

    // Private construtor and assignment operator assures that nobody
    // will be able to copy or assign a parser. There are no defined
    // bodies for them.
    Dhcp4ConfigParser(const Dhcp4ConfigParser& source);
    Dhcp4ConfigParser& operator=(const Dhcp4ConfigParser& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    Dhcp4ConfigParser() {}
public:
    /// The destructor.
    virtual ~Dhcp4ConfigParser() {}
    //@}

    /// \brief Prepare configuration value.
    ///
    /// This method parses the "value part" of the configuration identifier
    /// that corresponds to this derived class and prepares a new value to
    /// apply to the server.
    ///
    /// This method must validate the given value both in terms of syntax
    /// and semantics of the configuration, so that the server will be
    /// validly configured at the time of \c commit().  Note: the given
    /// configuration value is normally syntactically validated, but the
    /// \c build() implementation must also expect invalid input.  If it
    /// detects an error it may throw an exception of a derived class
    /// of \c isc::Exception.
    ///
    /// Preparing a configuration value will often require resource
    /// allocation.  If it fails, it may throw a corresponding standard
    /// exception.
    ///
    /// This method is not expected to be called more than once in the
    /// life of the object. Although multiple calls are not prohibited
    /// by the interface, the behavior is undefined.
    ///
    /// \param config_value The configuration value for the identifier
    /// corresponding to the derived class.
    virtual void build(isc::data::ConstElementPtr config_value) = 0;

    /// \brief Apply the prepared configuration value to the server.
    ///
    /// This method is expected to be exception free, and, as a consequence,
    /// it should normally not involve resource allocation.
    /// Typically it would simply perform exception free assignment or swap
    /// operation on the value prepared in \c build().
    /// In some cases, however, it may be very difficult to meet this
    /// condition in a realistic way, while the failure case should really
    /// be very rare.  In such a case it may throw, and, if the parser is
    /// called via \c configureDhcp4Server(), the caller will convert the
    /// exception as a fatal error.
    ///
    /// This method is expected to be called after \c build(), and only once.
    /// The result is undefined otherwise.
    virtual void commit() = 0;
};

/// @brief a pointer to configuration parser
typedef boost::shared_ptr<Dhcp4ConfigParser> ParserPtr;

/// @brief a collection of parsers
///
/// This container is used to store pointer to parsers for a given scope.
typedef std::vector<ParserPtr> ParserCollection;


/// \brief Configure DHCPv4 server (\c Dhcpv4Srv) with a set of configuration values.
///
/// This function parses configuration information stored in \c config_set
/// and configures the \c server by applying the configuration to it.
/// It provides the strong exception guarantee as long as the underlying
/// derived class implementations of \c DhcpConfigParser meet the assumption,
/// that is, it ensures that either configuration is fully applied or the
/// state of the server is intact.
///
/// If a syntax or semantics level error happens during the configuration
/// (such as malformed configuration or invalid configuration parameter),
/// this function returns appropriate error code.
///
/// This function is called every time a new configuration is received. The extra
/// parameter is a reference to DHCPv4 server component. It is currently not used
/// and CfgMgr::instance() is accessed instead.
///
/// This method does not throw. It catches all exceptions and returns them as
/// reconfiguration statuses. It may return the following response codes:
/// 0 - configuration successful
/// 1 - malformed configuration (parsing failed)
/// 2 - logical error (parsing was successful, but the values are invalid)
///
/// @param config_set a new configuration (JSON) for DHCPv4 server
/// @return answer that contains result of reconfiguration
isc::data::ConstElementPtr
configureDhcp4Server(Dhcpv4Srv&,
                     isc::data::ConstElementPtr config_set);

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP4_CONFIG_PARSER_H
