// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_DNR_H
#define OPTION_DNR_H

#include <dhcp/option.h>
#include <dns/name.h>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when invalid domain name is specified.
class InvalidOptionDnr6DomainName : public Exception {
public:
    InvalidOptionDnr6DomainName(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {
    }
};

class OptionDnr6 : public Option {
public:
    /// @brief Size in octets of Service Priority field
    static const uint8_t SERVICE_PRIORITY_SIZE = 2;

    /// @brief Size in octets of ADN Length field
    static const uint8_t ADN_LENGTH_SIZE = 2;

    /// @brief Size in octets of Addr Length field
    static const uint8_t ADDR_LENGTH_SIZE = 2;

    OptionDnr6(OptionBufferConstIter begin, OptionBufferConstIter end);
    virtual OptionPtr clone() const;
    virtual void pack(util::OutputBuffer& buf, bool check) const;
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);
    virtual std::string toText(int indent) const;
    virtual uint16_t len() const;

    /// @brief Getter of the @c service_priority_
    ///
    /// @return The priority of this OPTION_V6_DNR instance compared to other instances.
    uint16_t getServicePriority() const {
        return service_priority_;
    }

    /// @brief Getter of the @c adn_length_
    ///
    /// @return Length of the authentication-domain-name data in octets.
    uint16_t getAdnLength() const {
        return adn_length_;
    }

    /// @brief Returns the Authentication domain name in the text format.
    ///
    /// FQDN data stored in @c adn_ is converted into text format and returned.
    ///
    /// @return Authentication domain name in the text format.
    std::string getAdn() const;

    /// @brief Getter of the @c addr_length_
    ///
    /// @return  Length of enclosed IPv6 addresses in octets.
    uint16_t getAddrLength() const {
        return addr_length_;
    }

private:
    /// @brief The priority of this OPTION_V6_DNR instance compared to other instances.
    uint16_t service_priority_;

    /// @brief Length of the authentication-domain-name data in octets.
    uint16_t adn_length_;

    /// @brief Authentication domain name field of variable length.
    ///
    /// Authentication domain name field of variable length holding
    /// a fully qualified domain name of the encrypted DNS resolver.
    /// This field is formatted as specified in Section 10 of RFC8415.
    boost::shared_ptr<isc::dns::Name> adn_;

    /// @brief Length of enclosed IPv6 addresses in octets.
    uint16_t addr_length_;

    /// @brief Returns minimal length of the option data (without headers) in octets.
    ///
    /// If the ADN-only mode is used, then "Addr Length", "ipv6-address(es)",
    /// and "Service Parameters (SvcParams)" fields are not present. In this
    /// case minimal length of data is 2 octets for Service Priority plus 2 octets
    /// for ADN Length.
    ///
    /// @return Minimal length of the option data (without headers) in octets.
    static uint8_t getMinimalLength() {
        return SERVICE_PRIORITY_SIZE + ADN_LENGTH_SIZE;
    };
};

class OptionDnr4 : public Option {
public:
    OptionDnr4();
    OptionDnr4(OptionBufferConstIter begin, OptionBufferConstIter end);
    virtual OptionPtr clone() const;
    virtual void pack(util::OutputBuffer& buf, bool check) const;
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);
    virtual std::string toText(int indent) const;
    virtual uint16_t len() const;
};

/// A pointer to the @c OptionDnr6 object.
typedef boost::shared_ptr<OptionDnr6> OptionDnr6Ptr;

/// A pointer to the @c OptionDnr4 object.
typedef boost::shared_ptr<OptionDnr4> OptionDnr4Ptr;

}  // namespace dhcp
}  // namespace isc

#endif  // OPTION_DNR_H
