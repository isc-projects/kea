// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION4_DNR_H
#define OPTION4_DNR_H

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option.h>
#include <dns/name.h>

namespace isc {
namespace dhcp {

class DnrInstance {
public:
    /// @brief A Type defined for container holding IP addresses.
    typedef std::vector<isc::asiolink::IOAddress> AddressContainer;

    /// @brief Size in octets of Service Priority field.
    static const uint8_t SERVICE_PRIORITY_SIZE = 2;

    explicit DnrInstance(Option::Universe universe) : universe_(universe) {}

    DnrInstance(Option::Universe universe, const uint16_t service_priority,
                const std::string& adn,
                const AddressContainer& ip_addresses,
                const std::string& svc_params);

    DnrInstance(Option::Universe universe, const uint16_t service_priority,
                const std::string& adn);

    virtual ~DnrInstance() = default;

    const AddressContainer& getIpAddresses() const {
        return ip_addresses_;
    }

    const boost::shared_ptr<isc::dns::Name>& getAdn() const {
        return adn_;
    }

    uint16_t getDnrInstanceDataLength() const {
        return (dnr_instance_data_length_);
    }

    /// @brief Getter of the @c service_priority_.
    ///
    /// @return The priority of this DNR instance compared to other instances.
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
    std::string getAdnAsText() const;

    std::string getDnrInstanceAsText() const;

    /// @brief Getter of the @c addr_length_.
    ///
    /// @return  Length of enclosed IP addresses in octets.
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
        return (ip_addresses_);
    }

    /// @brief Getter of the @c svc_params_ field.
    ///
    /// @return Returns Service Parameters as a string.
    const std::string& getSvcParams() const {
        return svc_params_;
    }

    /// @brief Returns minimal length of the DNR instance data (without headers) in octets.
    ///
    /// If the ADN-only mode is used, then "Addr Length", "ip(v4/v6)-address(es)",
    /// and "Service Parameters (SvcParams)" fields are not present.
    /// So minimal length of data is calculated by adding 2 octets for Service Priority,
    /// octets needed for ADN Length and octets needed for DNR Instance Data Length
    /// (only in case of DHCPv4).
    ///
    /// @return Minimal length of the DNR instance data (without headers) in octets.
    uint8_t getMinimalLength() const;

    /// @brief Returns size in octets of Addr Length field.
    uint8_t getAddrLengthSize() const;

    /// @brief Returns size in octets of DNR Instance Data Length field.
    uint8_t getDnrInstanceDataLengthSize() const;

    bool isAdnOnlyMode() const {
        return adn_only_mode_;
    }

    /// @brief Sets Authentication domain name from given string.
    ///
    /// Sets FQDN of the encrypted DNS resolver from given string.
    /// It may throw an exception if parsing of the FQDN fails or if
    /// provided FQDN length is bigger than uint16_t Max.
    /// It also calculates and sets value of Addr length field.
    ///
    /// @param adn string representation of ADN FQDN
    void setAdn(const std::string& adn);

    void setDnrInstanceDataLength(uint16_t dnr_instance_data_length) {
        dnr_instance_data_length_ = dnr_instance_data_length;
    }
    void setServicePriority(uint16_t service_priority) {
        service_priority_ = service_priority;
    }
    void setAdnLength(uint16_t adn_length) {
        adn_length_ = adn_length;
    }
    void setAddrLength(uint16_t addr_length) {
        addr_length_ = addr_length;
    }
//    void setSvcParamsLength(uint16_t svc_params_length) {
//        svc_params_length_ = svc_params_length;
//    }
    void setAdnOnlyMode(bool adn_only_mode) {
        adn_only_mode_ = adn_only_mode;
    }
    void setSvcParams(const std::string& svc_params) {
        svc_params_ = svc_params;
    }

    /// @brief Writes the ADN FQDN in the wire format into a buffer.
    ///
    /// The Authentication Domain Name - fully qualified domain name of the encrypted
    /// DNS resolver data is appended at the end of the buffer.
    ///
    /// @param [out] buf buffer where ADN FQDN will be written.
    void packAdn(isc::util::OutputBuffer& buf) const;

    /// @brief Writes the IP address(es) in the wire format into a buffer.
    ///
    /// The IP address(es) (@c ip_addresses_) data is appended at the end
    /// of the buffer.
    ///
    /// @param [out] buf buffer where IP address(es) will be written.
    virtual void packAddresses(isc::util::OutputBuffer& buf) const;

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

    void checkFields();

protected:
    Option::Universe universe_;

    /// @brief Authentication domain name field of variable length.
    ///
    /// Authentication domain name field of variable length holding
    /// a fully qualified domain name of the encrypted DNS resolver.
    /// This field is formatted as specified in Section 10 of RFC8415.
    boost::shared_ptr<isc::dns::Name> adn_;

    /// @brief Length of all following data in octets.
    ///
    /// This field is only used for DHCPv4 Encrypted DNS %Option.
    uint16_t dnr_instance_data_length_;

    /// @brief The priority of this instance compared to other DNR instances.
    uint16_t service_priority_;

    /// @brief Length of the authentication-domain-name data in octets.
    uint16_t adn_length_;

    /// @brief Length of included IP addresses in octets.
    uint16_t addr_length_ = 0;

    /// @brief Vector container holding one or more IP addresses.
    ///
    /// One or more IP addresses to reach the encrypted DNS resolver.
    /// In case of DHCPv4, both private and public IPv4 addresses can
    /// be included in this field.
    /// In case of DHCPv6, an address can be link-local, ULA, or GUA.
    AddressContainer ip_addresses_;

    /// @brief Length of Service Parameters field in octets.
    uint16_t svc_params_length_ = 0;

    /// @brief Flag stating whether ADN only mode is used or not.
    ///
    /// "Addr Length", "IP(v4/v6) Address(es)", and "Service Parameters (SvcParams)"
    /// fields are not present if the ADN-only mode is used.
    bool adn_only_mode_ = true;

    /// @brief Service Parameters (SvcParams) (variable length).
    ///
    /// Specifies a set of service parameters that are encoded
    /// following the rules in Section 2.1 of [I-D.ietf-dnsop-svcb-https].
    std::string svc_params_;

    uint16_t dnrInstanceLen() const;

private:
    std::string getLogPrefix() const;

    /// @brief Returns size in octets of ADN Length field.
    uint8_t getAdnLengthSize() const;
};

class Option4Dnr : public Option {
public:
    typedef std::vector<DnrInstance> DnrInstanceContainer;

    Option4Dnr(OptionBufferConstIter begin, OptionBufferConstIter end);

    Option4Dnr() : Option(V4, DHO_V4_DNR) {}

    void addDnrInstance(DnrInstance& dnr_instance);

    const DnrInstanceContainer& getDnrInstances() const {
        return dnr_instances_;
    }

    virtual OptionPtr clone() const;
    virtual void pack(util::OutputBuffer& buf, bool check = true) const;
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);
    virtual std::string toText(int indent = 0) const;
    virtual uint16_t len() const;

protected:
    DnrInstanceContainer dnr_instances_;
};

/// A pointer to the @c OptionDnr4 object.
typedef boost::shared_ptr<Option4Dnr> Option4DnrPtr;

}  // namespace dhcp
}  // namespace isc

#endif  // OPTION4_DNR_H
