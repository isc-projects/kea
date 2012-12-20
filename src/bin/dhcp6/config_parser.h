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

#ifndef DHCP6_CONFIG_PARSER_H
#define DHCP6_CONFIG_PARSER_H

/// @todo: This header file and its .cc counterpart are very similar between
/// DHCPv4 and DHCPv6. They should be merged. See ticket #2355.

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <string>

namespace isc {
namespace dhcp {

class Dhcpv6Srv;

/// An exception that is thrown if an error occurs while configuring an
/// \c Dhcpv6Srv object.
class Dhcp6ConfigError : public isc::Exception {
public:

    /// @brief constructor
    ///
    /// @param file name of the file, where exception occurred
    /// @param line line of the file, where exception occurred
    /// @param what text description of the issue that caused exception
    Dhcp6ConfigError(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {}
};


/// \brief Configure an \c Dhcpv6Srv object with a set of configuration values.
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
isc::data::ConstElementPtr
configureDhcp6Server(Dhcpv6Srv& server,
                     isc::data::ConstElementPtr config_set);

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP6_CONFIG_PARSER_H
