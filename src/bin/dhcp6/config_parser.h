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

#include <string>
#include <exceptions/exceptions.h>
#include <cc/data.h>

#ifndef DHCP6_CONFIG_PARSER_H
#define DHCP6_CONFIG_PARSER_H

namespace isc {
namespace dhcp {

class Dhcpv6Srv;

/// An exception that is thrown if an error occurs while configuring an
/// \c Dhcpv6Srv object.
class Dhcp6ConfigError : public isc::Exception {
public:
Dhcp6ConfigError(const char* file, size_t line, const char* what) :
    isc::Exception(file, line, what) {}
};

class Dhcp6ConfigParser {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private to make it explicit that this is a
    /// pure base class.
    //@{
private:
    Dhcp6ConfigParser(const Dhcp6ConfigParser& source);
    Dhcp6ConfigParser& operator=(const Dhcp6ConfigParser& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    Dhcp6ConfigParser() {}
public:
    /// The destructor.
    virtual ~Dhcp6ConfigParser() {}
    //@}

    /// Prepare configuration value.
    ///
    /// This method parses the "value part" of the configuration identifier
    /// that corresponds to this derived class and prepares a new value to
    /// apply to the server.
    /// In the above example, the derived class for the identifier "param1"
    /// would be passed an data \c Element storing an integer whose value
    /// is 10, and would record that value internally;
    /// the derived class for the identifier "param2" would be passed a
    /// map element and (after parsing) convert it into some internal
    /// data structure.
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
    /// This method is not expected to be called more than once.  Although
    /// multiple calls are not prohibited by the interface, the behavior
    /// is undefined.
    ///
    /// \param config_value The configuration value for the identifier
    /// corresponding to the derived class.
    virtual void build(isc::data::ConstElementPtr config_value) = 0;

    /// Apply the prepared configuration value to the server.
    ///
    /// This method is expected to be exception free, and, as a consequence,
    /// it should normally not involve resource allocation.
    /// Typically it would simply perform exception free assignment or swap
    /// operation on the value prepared in \c build().
    /// In some cases, however, it may be very difficult to meet this
    /// condition in a realistic way, while the failure case should really
    /// be very rare.  In such a case it may throw, and, if the parser is
    /// called via \c configureDhcp6Server(), the caller will convert the
    /// exception as a fatal error.
    ///
    /// This method is expected to be called after \c build(), and only once.
    /// The result is undefined otherwise.
    virtual void commit() = 0;
};

/// Configure an \c Dhcpv6Srv object with a set of configuration values.
///
/// This function parses configuration information stored in \c config_set
/// and configures the \c server by applying the configuration to it.
/// It provides the strong exception guarantee as long as the underlying
/// derived class implementations of \c Dhcp6ConfigParser meet the assumption,
/// that is, it ensures that either configuration is fully applied or the
/// state of the server is intact.
///
/// If a syntax or semantics level error happens during the configuration
/// (such as malformed configuration or invalid configuration parameter),
/// this function throws an exception of class \c Dhcp6ConfigError.
/// If the given configuration requires resource allocation and it fails,
/// a corresponding standard exception will be thrown.
/// Other exceptions may also be thrown, depending on the implementation of
/// the underlying derived class of \c Dhcp6ConfigError.
/// In any case the strong guarantee is provided as described above except
/// in the very rare cases where the \c commit() method of a parser throws
/// an exception.  If that happens this function converts the exception
/// into a \c FatalError exception and rethrows it.  This exception is
/// expected to be caught at the highest level of the application to terminate
/// the program gracefully.
///
/// \param server The \c Dhcpv6Srv object to be configured.
/// \param config_set A JSON style configuration to apply to \c server.
void configureDhcp6Server(Dhcpv6Srv& server,
                         isc::data::ConstElementPtr config_set);


/// Create a new \c Dhcp6ConfigParser object for a given configuration
/// identifier.
///
/// It internally identifies an appropriate derived class for the given
/// identifier and creates a new instance of that class.  The caller can
/// then configure the \c server regarding the identifier by calling
/// the \c build() and \c commit() methods of the returned object.
///
/// In practice, this function is only expected to be used as a backend of
/// \c configureDhcp6Server() and is not supposed to be called directly
/// by applications.  It is publicly available mainly for testing purposes.
/// When called directly, the created object must be deleted by the caller.
/// Note: this means if this module and the caller use incompatible sets of
/// new/delete, it may cause unexpected strange failure.  We could avoid that
/// by providing a separate deallocation function or by using a smart pointer,
/// but since the expected usage of this function is very limited (i.e. for
/// our own testing purposes) it would be an overkilling.  We therefore prefer
/// simplicity and keeping the interface intuitive.
///
/// If the resource allocation for the new object fails, a corresponding
/// standard exception will be thrown.  Otherwise this function is not
/// expected to throw an exception, unless the constructor of the underlying
/// derived class implementation (unexpectedly) throws.
///
/// \param server The \c Dhcpv6Srv object to be configured.
/// \param config_id The configuration identifier for which a parser object
/// is to be created.
/// \return A pointer to an \c Dhcp6ConfigParser object.
Dhcp6ConfigParser* createDhcp6ConfigParser(Dhcpv6Srv& server,
                                         const std::string& config_id);

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP6_CONFIG_PARSER_H
