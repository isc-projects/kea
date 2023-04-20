// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION6_DNR_H
#define OPTION6_DNR_H

#include <dhcp/option4_dnr.h>

namespace isc {
namespace dhcp {

/// @brief Represents DHCPv6 Encrypted DNS %Option (code 144).
///
/// This option has been defined in the @c draft-ietf-add-dnr (to be replaced
/// with published RFC) and it has a following structure:
/// - option-code = 144 (2 octets)
/// - option-len (2 octets)
/// - Service Priority (2 octets)
/// - ADN Length (2 octets)
/// - Authentication Domain Name (variable length)
/// - Addr Length (2 octets)
/// - IPv6 Address(es) (variable length)
/// - Service Parameters (variable length).
class Option6Dnr : public Option, public DnrInstance {
public:
    /// @brief Constructor of the %Option from on-wire data.
    ///
    /// This constructor creates an instance of the option using a buffer with
    /// on-wire data. It may throw an exception if the @c unpack method throws.
    ///
    /// @param begin Iterator pointing to the beginning of the buffer holding an
    /// option.
    /// @param end Iterator pointing to the end of the buffer holding an option.
    Option6Dnr(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Constructor of the %Option with all fields from params.
    ///
    /// Constructor of the %Option where all fields
    /// i.e. Service priority, ADN, IP address(es) and Service params
    /// are provided as ctor parameters.
    ///
    /// @param service_priority Service priority
    /// @param adn ADN FQDN
    /// @param ip_addresses Container of IP addresses
    /// @param svc_params Service Parameters
    Option6Dnr(const uint16_t service_priority,
               const std::string& adn,
               const Option6Dnr::AddressContainer& ip_addresses,
               const std::string& svc_params)
        : Option(V6, D6O_V6_DNR), DnrInstance(V6, service_priority, adn, ip_addresses, svc_params) {
    }

    /// @brief Constructor of the %Option in ADN only mode.
    ///
    /// Constructor of the %Option in ADN only mode
    /// i.e. only Service priority and ADN FQDN
    /// are provided as ctor parameters.
    ///
    /// @param service_priority Service priority
    /// @param adn ADN FQDN
    Option6Dnr(const uint16_t service_priority, const std::string& adn)
        : Option(V6, D6O_V6_DNR), DnrInstance(V6, service_priority, adn) {}

    OptionPtr clone() const override;
    void pack(util::OutputBuffer& buf, bool check = false) const override;
    void unpack(OptionBufferConstIter begin, OptionBufferConstIter end) override;
    std::string toText(int indent = 0) const override;
    uint16_t len() const override;

    void packAddresses(isc::util::OutputBuffer& buf) const override;
    void unpackAddresses(OptionBufferConstIter& begin, OptionBufferConstIter end) override;
};

/// A pointer to the @c Option6Dnr object.
typedef boost::shared_ptr<Option6Dnr> Option6DnrPtr;

}  // namespace dhcp
}  // namespace isc

#endif  // OPTION6_DNR_H
