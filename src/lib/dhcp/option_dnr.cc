// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option_dnr.h>
#include <dns/labelsequence.h>
#include <util/strutil.h>
#include <set>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

OptionDnr6::OptionDnr6(OptionBufferConstIter begin, OptionBufferConstIter end)
    : Option(V6, D6O_V6_DNR) {
    unpack(begin, end);
}

OptionDnr6::OptionDnr6(const uint16_t service_priority,
                       const std::string& adn,
                       const OptionDnr6::AddressContainer& ipv6_addresses,
                       const std::string& svc_params)
    : Option(V6, D6O_V6_DNR), service_priority_(service_priority),
      ipv6_addresses_(ipv6_addresses), svc_params_(svc_params) {
    setAdn(adn);
    checkFields();
}

OptionDnr6::OptionDnr6(const uint16_t service_priority, const std::string& adn)
    : Option(V6, D6O_V6_DNR), service_priority_(service_priority) {
    setAdn(adn);
}

OptionPtr
OptionDnr6::clone() const {
    return (cloneInternal<OptionDnr6>());
}

void
OptionDnr6::pack(util::OutputBuffer& buf, bool check) const {
    packHeader(buf, check);

    buf.writeUint16(service_priority_);
    buf.writeUint16(adn_length_);
    packAdn(buf);
    if (adn_only_mode_) {
        return;
    }
    buf.writeUint16(addr_length_);
    packAddresses(buf);
    packSvcParams(buf);
}

void
OptionDnr6::packAdn(util::OutputBuffer& buf) const {
    if (!adn_) {
        // This should not happen since Encrypted DNS options are designed
        // to always include an authentication domain name.
        return;
    }
    isc::dns::LabelSequence label_sequence(*adn_);
    if (label_sequence.getDataLength() > 0) {
        size_t data_length = 0;
        const uint8_t* data = label_sequence.getData(&data_length);
        buf.writeData(data, data_length);
    }
}

void
OptionDnr6::packAddresses(util::OutputBuffer& buf) const {
    for (const auto& address : ipv6_addresses_) {
        if (!address.isV6()) {
            isc_throw(isc::BadValue, address.toText() << " is not an IPv6 address");
        }
        buf.writeData(&address.toBytes()[0], V6ADDRESS_LEN);
    }
}

void
OptionDnr6::packSvcParams(util::OutputBuffer& buf) const {
    if (svc_params_length_ > 0) {
        buf.writeData(&(*svc_params_.begin()), svc_params_length_);
    }
}

void
OptionDnr6::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    if (std::distance(begin, end) < getMinimalLength()) {
        isc_throw(OutOfRange, "DHCPv6 Encrypted DNS Option (" << type_ << ") malformed: "
                              "data truncated to"
                              " size " << std::distance(begin, end));
    }
    setData(begin, end);
    // First two octets of Option data is Service Priority - this is mandatory field.
    service_priority_ = isc::util::readUint16(&(*begin), SERVICE_PRIORITY_SIZE);
    begin += SERVICE_PRIORITY_SIZE;

    // Next come two octets of ADN Length plus the ADN data itself (variable length).
    // This is Opaque Data Tuple so let's use this class to retrieve the ADN data.
    OpaqueDataTuple adn_tuple(OpaqueDataTuple::LENGTH_2_BYTES, begin, end);
    adn_length_ = adn_tuple.getLength();

    // Encrypted DNS options are designed to always include an authentication domain name,
    // so when there is no FQDN included, we shall throw an exception.
    if (adn_length_ == 0) {
        isc_throw(InvalidOptionDnrDomainName, "Mandatory Authentication Domain Name fully "
                                              "qualified domain-name is missing");
    }

    // Let's try to extract ADN FQDN data.
    isc::util::InputBuffer name_buf(&(*adn_tuple.getData().begin()), adn_length_);
    try {
        adn_.reset(new isc::dns::Name(name_buf, true));
    } catch (const Exception& ex) {
        isc_throw(InvalidOptionDnrDomainName, "failed to parse "
                                              "fully qualified domain-name from wire format "
                                              "- " << ex.what());
    }

    begin += adn_tuple.getTotalLength();

    if (begin == end) {
        // ADN only mode, other fields are not included.
        return;
    }
    adn_only_mode_ = false;
    if (std::distance(begin, end) < ADDR_LENGTH_SIZE) {
        isc_throw(OutOfRange, "DHCPv6 Encrypted DNS Option (" << type_ << ") malformed: after"
                              " ADN field, there should be at least "
                              "2 bytes long Addr Length field");
    }
    // Next come two octets of Addr Length.
    addr_length_ = isc::util::readUint16(&(*begin), ADDR_LENGTH_SIZE);
    begin += ADDR_LENGTH_SIZE;
    // It MUST be a multiple of 16.
    if ((addr_length_ % V6ADDRESS_LEN) != 0) {
        isc_throw(OutOfRange, "DHCPv6 Encrypted DNS Option (" << type_ << ")"
                               << " malformed: Addr Len=" << addr_length_
                               << " is not divisible by 16");
    }

    // As per draft-ietf-add-dnr 3.1.8:
    // If additional data is supplied (i.e. not ADN only mode),
    // the option includes at least one valid IP address.
    if (addr_length_ == 0) {
        isc_throw(OutOfRange, "DHCPv6 Encrypted DNS Option (" << type_ << ")"
                               << " malformed: Addr Len=" << addr_length_
                               << " is not greater than 0");
    }

    // Check if IPv6 Address(es) field is not truncated.
    if (std::distance(begin, end) < addr_length_) {
        isc_throw(OutOfRange, "DHCPv6 Encrypted DNS Option (" << type_ << ")"
                              << " malformed: Addr Len=" << addr_length_
                              << " but IPv6 address(es) are truncated to len="
                              << std::distance(begin, end));
    }

    // Let's unpack the ipv6-address(es).
    auto addr_end = begin + addr_length_;
    while (begin != addr_end) {
        ipv6_addresses_.push_back(IOAddress::fromBytes(AF_INET6, &(*begin)));
        begin += V6ADDRESS_LEN;
    }

    // SvcParams (variable length) field is last.
    svc_params_length_ = std::distance(begin, end);
    if (svc_params_length_ > 0) {
        svc_params_.assign(begin, end);
        checkSvcParams();
    }
}

std::string
OptionDnr6::toText(int indent) const {
    std::ostringstream stream;
    std::string in(indent, ' '); // base indentation
    stream << in  << "type=" << type_ << "(V6_DNR), "
           << "len=" << (len() - getHeaderLen()) << ", "
           << "service_priority=" << service_priority_ << ", "
           << "adn_length=" << adn_length_ << ", "
           << "adn='" << getAdn() << "'";
    if (!adn_only_mode_) {
        stream << ", addr_length=" << addr_length_
               << ", address(es):";
        for (const auto& address : ipv6_addresses_) {
            stream << " " << address.toText();
        }

        if (svc_params_length_ > 0) {
            stream << ", svc_params='" << svc_params_ << "'";
        }
    }

    return (stream.str());
}

uint16_t
OptionDnr6::len() const {
    uint16_t len = OPTION6_HDR_LEN + SERVICE_PRIORITY_SIZE + adn_length_ + ADN_LENGTH_SIZE;
    if (!adn_only_mode_) {
        len += addr_length_ + ADDR_LENGTH_SIZE + svc_params_length_;
    }
    return (len);
}

std::string
OptionDnr6::getAdn() const {
    if (adn_) {
        return (adn_->toText());
    }
    return ("");
}

void
OptionDnr6::checkSvcParams(bool from_wire_data) {
    std::string svc_params = isc::util::str::trim(svc_params_);
    if (svc_params.empty()) {
        isc_throw(InvalidOptionDnrSvcParams, "Provided Svc Params field is empty");
    }
    if (!from_wire_data) {
        // If Service Params field was not parsed from on-wire data,
        // but actually was provided with ctor, let's calculate svc_params_length_.
        auto svc_params_len = svc_params.length();
        if (svc_params_len > std::numeric_limits<uint16_t>::max()) {
            isc_throw(OutOfRange, "Given Svc Params length "
                                  << svc_params_len << " is bigger than uint_16 MAX");
        }
        svc_params_length_ = svc_params_len;
        // If Service Params field was not parsed from on-wire data,
        // but actually was provided with ctor, let's replace it with trimmed value.
        svc_params_ = svc_params;
    }

    // SvcParams are a whitespace-separated list, with each SvcParam
    // consisting of a SvcParamKey=SvcParamValue pair or a standalone SvcParamKey.
    // SvcParams in presentation format MAY appear in any order, but keys MUST NOT be repeated.

    // Let's put all elements of a whitespace-separated list into a vector.
    std::vector<std::string> tokens = isc::util::str::tokens(svc_params, " ");

    // Set of keys used to check if a key is not repeated.
    std::set<std::string> keys;
    // String sanitizer is used to check keys syntax.
    util::str::StringSanitizerPtr sanitizer;
    // SvcParamKeys are lower-case alphanumeric strings. Key names
    // contain 1-63 characters from the ranges "a"-"z", "0"-"9", and "-".
    std::string regex = "[^a-z0-9-]";
    sanitizer.reset(new util::str::StringSanitizer(regex, ""));
    // The service parameters MUST NOT include
    // "ipv4hint" or "ipv6hint" SvcParams as they are superseded by the
    // included IP addresses.
    std::set<std::string> forbidden_keys = {"ipv4hint", "ipv6hint"};

    // Now let's check each SvcParamKey=SvcParamValue pair.
    for (const std::string& token : tokens) {
        std::vector<std::string> key_val = isc::util::str::tokens(token, "=");
        if (key_val.size() > 2) {
            isc_throw(InvalidOptionDnrSvcParams, "Wrong Svc Params syntax - more than one "
                                                 "equals sign found in SvcParamKey=SvcParamValue "
                                                 "pair");
        }

        // SvcParam Key related checks come below.
        std::string key = key_val[0];
        if (forbidden_keys.find(key) != forbidden_keys.end()) {
            isc_throw(InvalidOptionDnrSvcParams, "Wrong Svc Params syntax - key "
                                                 << key << " must not be used");
        }

        auto insert_res = keys.insert(key);
        if (!insert_res.second) {
            isc_throw(InvalidOptionDnrSvcParams, "Wrong Svc Params syntax - key "
                                                 << key << " was duplicated");
        }

        if (key.length() > 63) {
            isc_throw(InvalidOptionDnrSvcParams, "Wrong Svc Params syntax - key had more than 63 "
                                                 "characters - " << key);
        }

        std::string sanitized_key = sanitizer->scrub(key);
        if (sanitized_key.size() < key.size()) {
            isc_throw(InvalidOptionDnrSvcParams, "Wrong Svc Params syntax - invalid character "
                                                 "used in key - " << key);
        }

        if (key_val.size() == 2) {
            // tbd Check value syntax
            std::string value = key_val[1];
        }
    }

}

void
OptionDnr6::setAdn(const std::string& adn) {
    std::string trimmed_adn = isc::util::str::trim(adn);
    if (trimmed_adn.empty()) {
        isc_throw(InvalidOptionDnrDomainName, "Mandatory Authentication Domain Name fully "
                                              "qualified domain-name must not be empty");
    }
    try {
        adn_.reset(new isc::dns::Name(trimmed_adn, true));
    } catch (const Exception& ex) {
        isc_throw(InvalidOptionDnrDomainName, "Failed to parse "
                                              "fully qualified domain-name from string "
                                              "- " << ex.what());
    }
    size_t adn_len = 0;
    isc::dns::LabelSequence label_sequence(*adn_);
    label_sequence.getData(&adn_len);
    if (adn_len > std::numeric_limits<uint16_t>::max()) {
        isc_throw(InvalidOptionDnrDomainName, "Given ADN FQDN length "
                                              << adn_len << " is bigger than uint_16 MAX");
    }

    adn_length_ = adn_len;
}

void
OptionDnr6::checkFields() {
    if (svc_params_.empty() && ipv6_addresses_.empty()) {
        // ADN only mode, nothing more to do.
        return;
    }
    if(!svc_params_.empty() && ipv6_addresses_.empty()) {
        // As per draft-ietf-add-dnr 3.1.8:
        // If additional data is supplied (i.e. not ADN only mode),
        // the option includes at least one valid IP address.
        isc_throw(OutOfRange, "DHCPv6 Encrypted DNS Option ("
                               << type_ << ")"
                               << " malformed: No IPv6 address given. Since this is not "
                                  "ADN only mode, at least one valid IP address must be included");

    }
    if(!svc_params_.empty()) {
        checkSvcParams(false);
    }
    adn_only_mode_ = false;
    auto addr_len = ipv6_addresses_.size() * V6ADDRESS_LEN;
    if (addr_len > std::numeric_limits<uint16_t>::max()) {
        isc_throw(OutOfRange, "Given IPv6 addresses length "
                              << addr_len << " is bigger than uint_16 MAX");
    }
    addr_length_ = addr_len;
}

OptionDnr4::OptionDnr4() : Option(V4, DHO_V4_DNR) {
}

OptionDnr4::OptionDnr4(OptionBufferConstIter begin, OptionBufferConstIter end)
    : Option(V4, DHO_V4_DNR) {
    unpack(begin, end);
}

OptionPtr
OptionDnr4::clone() const {
    return Option::clone();
}

void
OptionDnr4::pack(util::OutputBuffer& buf, bool check) const {
    Option::pack(buf, check);
}

void
OptionDnr4::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    Option::unpack(begin, end);
}

std::string
OptionDnr4::toText(int indent) const {
    return Option::toText(indent);
}

uint16_t
OptionDnr4::len() const {
    return Option::len();
}

}  // namespace dhcp
}  // namespace isc
