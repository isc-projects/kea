// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_DNR_H
#define OPTION_DNR_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dns/name.h>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when invalid domain name is specified.
class InvalidOptionDnrDomainName : public Exception {
public:
    InvalidOptionDnrDomainName(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {
    }
};

/// @brief Exception thrown when Service parameters have wrong format.
class InvalidOptionDnrSvcParams : public Exception {
public:
    InvalidOptionDnrSvcParams(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {
    }
};

/// @brief Represents DHCPv6 Encrypted DNS %Option (code 144).
///
/// This option has been defined in the draft-ietf-add-dnr-15 (to be replaced
/// with published RFC) and it has a following structure:
/// - option-code = 144 (2 octets)
/// - option-len (2 octets)
/// - Service Priority (2 octets)
/// - ADN Length (2 octets)
/// - Authentication Domain Name (variable length)
/// - Addr Length (2 octets)
/// - IPv6 Address(es) (variable length)
/// - Service Parameters (variable length).
class OptionDnr6 : public Option {
public:
    /// @brief A container for (IPv6) addresses.
    typedef std::vector<isc::asiolink::IOAddress> AddressContainer;

    /// @brief Size in octets of Service Priority field.
    static const uint8_t SERVICE_PRIORITY_SIZE = 2;

    /// @brief Size in octets of ADN Length field.
    static const uint8_t ADN_LENGTH_SIZE = 2;

    /// @brief Size in octets of Addr Length field.
    static const uint8_t ADDR_LENGTH_SIZE = 2;

    /// @brief Constructor of the %Option from on-wire data.
    ///
    /// This constructor creates an instance of the option using a buffer with
    /// on-wire data. It may throw an exception if the @c unpack method throws.
    ///
    /// @param begin Iterator pointing to the beginning of the buffer holding an
    /// option.
    /// @param end Iterator pointing to the end of the buffer holding an option.
    OptionDnr6(OptionBufferConstIter begin, OptionBufferConstIter end);

    OptionDnr6(const uint16_t service_priority, const std::string& adn, const AddressContainer& ipv6_addresses, const std::string& svc_params);

    OptionDnr6(const uint16_t service_priority, const std::string& adn);

    virtual OptionPtr clone() const;
    virtual void pack(util::OutputBuffer& buf, bool check = false) const;
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);
    virtual std::string toText(int indent = 0) const;
    virtual uint16_t len() const;

    /// @brief Getter of the @c service_priority_.
    ///
    /// @return The priority of this OPTION_V6_DNR instance compared to other instances.
    uint16_t getServicePriority() const {
        return (service_priority_);
    }

    /// @brief Getter of the @c adn_length_.
    ///
    /// @return Length of the authentication-domain-name data in octets.
    uint16_t getAdnLength() const {
        return (adn_length_);
    }

    /// @brief Returns the Authentication domain name in the text format.
    ///
    /// FQDN data stored in @c adn_ is converted into text format and returned.
    ///
    /// @return Authentication domain name in the text format.
    std::string getAdn() const;

    /// @brief Getter of the @c addr_length_.
    ///
    /// @return  Length of enclosed IPv6 addresses in octets.
    uint16_t getAddrLength() const {
        return (addr_length_);
    }

    /// @brief Getter of the @c svc_params_length_.
    ///
    /// @return Length of Service Parameters field in octets.
    uint16_t getSvcParamsLength() const {
        return (svc_params_length_);
    }

    /// @brief Returns vector with addresses.
    ///
    /// We return a copy of our list. Although this includes overhead,
    /// it also makes this list safe to use after this option object
    /// is no longer available. As options are expected to hold only
    /// a few (1-3) addresses, the overhead is not that big.
    ///
    /// @return Address container with addresses.
    AddressContainer getAddresses() const {
        return (ipv6_addresses_);
    }

protected:
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
    uint16_t addr_length_ = 0;

    /// @brief Vector container holding one or more IPv6 addresses.
    ///
    /// One or more IPv6 addresses to reach the encrypted DNS resolver.
    /// An address can be link-local, ULA, or GUA.
    AddressContainer ipv6_addresses_;

    /// @brief Length of Service Parameters field in octets.
    uint16_t svc_params_length_ = 0;

    /// @brief Flag stating whether ADN only mode is used or not.
    ///
    /// "Addr Length", "ipv6-address(es)", and "Service Parameters (SvcParams)"
    /// fields are not present if the ADN-only mode is used.
    bool adn_only_mode_ = true;

    /// @brief Service Parameters (SvcParams) (variable length).
    ///
    /// Specifies a set of service parameters that are encoded
    /// following the rules in Section 2.1 of [I-D.ietf-dnsop-svcb-https].
    std::string svc_params_;

private:
    /// @brief Returns minimal length of the option data (without headers) in octets.
    ///
    /// If the ADN-only mode is used, then "Addr Length", "ipv6-address(es)",
    /// and "Service Parameters (SvcParams)" fields are not present. In this
    /// case minimal length of data is 2 octets for Service Priority plus 2 octets
    /// for ADN Length.
    ///
    /// @return Minimal length of the option data (without headers) in octets.
    static uint8_t getMinimalLength() {
        return (SERVICE_PRIORITY_SIZE + ADN_LENGTH_SIZE);
    };

    /// @brief Writes the ADN FQDN in the wire format into a buffer.
    ///
    /// The Authentication Domain Name - fully qualified domain name of the encrypted
    /// DNS resolver data is appended at the end of the buffer.
    ///
    /// @param [out] buf buffer where ADN FQDN will be written.
    void packAdn(isc::util::OutputBuffer& buf) const;

    /// @brief Writes the IPv6 address(es) in the wire format into a buffer.
    ///
    /// The IPv6 address(es) (@c ipv6_addresses_) data is appended at the end
    /// of the buffer.
    ///
    /// @param [out] buf buffer where IPv6 address(es) will be written.
    void packAddresses(isc::util::OutputBuffer& buf) const;

    /// @brief Writes the Service Parameters in the wire format into a buffer.
    ///
    /// The Service Parameters (@c svc_params_) data is appended at the end
    /// of the buffer.
    ///
    /// @param [out] buf buffer where SvcParams will be written.
    void packSvcParams(isc::util::OutputBuffer& buf) const;

    /// @brief Checks SvcParams field if encoded correctly and throws in case of issue found.
    ///
    /// The field should be encoded following the rules in
    /// Section 2.1 of [I-D.ietf-dnsop-svcb-https].
    void checkSvcParams(bool from_wire_data = true);

    /// @brief Sets Authentication domain name from given string.
    ///
    /// Sets FQDN of the encrypted DNS resolver from given string.
    /// It may throw an exception if parsing of the FQDN fails or if
    /// provided FQDN length is bigger than uint16_t Max.
    /// It also calculates and sets value of Addr length field.
    ///
    /// @param adn string representation of ADN FQDN
    void setAdn(const std::string& adn);
    void checkFields();
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
