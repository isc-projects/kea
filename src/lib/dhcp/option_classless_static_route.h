// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_CLASSLESS_STATIC_ROUTE_H
#define OPTION_CLASSLESS_STATIC_ROUTE_H

#include <dhcp/dhcp4.h>
#include <dhcp/option.h>

namespace isc {
namespace dhcp {

class OptionClasslessStaticRoute : public Option {
public:
    /// @brief Constructor
    OptionClasslessStaticRoute() : Option(V4, DHO_CLASSLESS_STATIC_ROUTE) {

    }

    /// @brief Copies this option and returns a pointer to the copy.
    ///
    /// @return Pointer to the copy of the option.
    OptionPtr clone() const override;

    /// @brief Writes option in wire-format to a buffer.
    ///
    /// Writes option in wire-format to buffer, returns pointer to first unused
    /// byte after stored option (that is useful for writing options one after
    /// another).
    ///
    /// @param buf pointer to a buffer
    /// @param check flag which indicates if checking the option length is
    /// required (used only in V4)
    ///
    /// @throw InvalidOptionDnrDomainName Thrown when Option's mandatory field ADN is empty.
    void pack(util::OutputBuffer& buf, bool check = false) const override;

    /// @brief Parses received wire data buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    void unpack(OptionBufferConstIter begin, OptionBufferConstIter end) override;

    /// @brief Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    std::string toText(int indent = 0) const override;

    /// @brief Returns length of the complete option (data length + DHCPv4/DHCPv6
    /// option header)
    ///
    /// @return length of the option
    uint16_t len() const override;

};

}  // namespace dhcp
}  // namespace isc

#endif  // OPTION_CLASSLESS_STATIC_ROUTE_H
