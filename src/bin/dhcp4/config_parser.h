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

/// An exception that is thrown if an error occurs while configuring an
/// @c Dhcpv4Srv object.
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

/// @brief Configure DHCPv4 server (@c Dhcpv4Srv) with a set of configuration values.
///
/// This function parses configuration information stored in @c config_set
/// and configures the @c server by applying the configuration to it.
/// It provides the strong exception guarantee as long as the underlying
/// derived class implementations of @c DhcpConfigParser meet the assumption,
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
/// 2 - commit failed (parsing was successful, but failed to store the
/// values in to server's configuration)
///
/// @param config_set a new configuration (JSON) for DHCPv4 server
/// @return answer that contains result of reconfiguration
isc::data::ConstElementPtr
configureDhcp4Server(Dhcpv4Srv&,
                     isc::data::ConstElementPtr config_set);


/// @brief Returns the global uint32_t values storage.
///
/// This function must be only used by unit tests that need
/// to access uint32_t global storage to verify that the
/// Uint32Parser works as expected.
///
/// @return a reference to a global uint32 values storage.
const std::map<std::string, uint32_t>& getUint32Defaults();

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP4_CONFIG_PARSER_H
