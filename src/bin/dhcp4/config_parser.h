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

#ifndef DHCP4_CONFIG_PARSER_H
#define DHCP4_CONFIG_PARSER_H

namespace isc {
namespace dhcp {

class Dhcpv4Srv;

/// An exception that is thrown if an error occurs while configuring an
/// \c Dhcpv4Srv object.
class Dhcp4ConfigError : public isc::Exception {
public:

/// @brief constructor
///
/// @param file name of the file, where exception occurred
/// @param line line of the file, where exception occurred
/// @param what text description of the issue that caused exception
Dhcp4ConfigError(const char* file, size_t line, const char* what) :
    isc::Exception(file, line, what) {}
};

class DhcpConfigParser {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private to make it explicit that this is a
    /// pure base class.
    //@{
private:
    DhcpConfigParser(const DhcpConfigParser& source);
    DhcpConfigParser& operator=(const DhcpConfigParser& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    DhcpConfigParser() {}
public:
    /// The destructor.
    virtual ~DhcpConfigParser() {}
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
typedef boost::shared_ptr<DhcpConfigParser> ParserPtr;

/// @brief a collection of parsers
///
/// This container is used to store pointer to parsers for a given scope.
typedef std::vector<ParserPtr> ParserCollection;


/// \brief Configure an \c Dhcpv4Srv object with a set of configuration values.
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
/// this function throws an exception of class \c Dhcp4ConfigError.
/// If the given configuration requires resource allocation and it fails,
/// a corresponding standard exception will be thrown.
/// Other exceptions may also be thrown, depending on the implementation of
/// the underlying derived class of \c Dhcp4ConfigError.
/// In any case the strong guarantee is provided as described above except
/// in the very rare cases where the \c commit() method of a parser throws
/// an exception.  If that happens this function converts the exception
/// into a \c FatalError exception and rethrows it.  This exception is
/// expected to be caught at the highest level of the application to terminate
/// the program gracefully.
///
/// \param server The \c Dhcpv4Srv object to be configured.
/// \param config_set A JSON style configuration to apply to \c server.
isc::data::ConstElementPtr
configureDhcp4Server(Dhcpv4Srv& server,
                     isc::data::ConstElementPtr config_set);

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP4_CONFIG_PARSER_H
