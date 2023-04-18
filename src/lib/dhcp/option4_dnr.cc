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
#include <dhcp/option4_dnr.h>
#include <dhcp/option6_dnr.h>
#include <dns/labelsequence.h>
#include <util/strutil.h>
#include <set>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

Option4Dnr::Option4Dnr(OptionBufferConstIter begin, OptionBufferConstIter end)
    : Option(V4, DHO_V4_DNR) {
    unpack(begin, end);
}

OptionPtr
Option4Dnr::clone() const {
    return (cloneInternal<Option4Dnr>());
}

void
Option4Dnr::pack(util::OutputBuffer& buf, bool check) const {
    packHeader(buf, check);
    for (const DnrInstance& dnr_instance : dnr_instances_) {
        buf.writeUint16(dnr_instance.getDnrInstanceDataLength());
        buf.writeUint16(dnr_instance.getServicePriority());
        buf.writeUint8(dnr_instance.getAdnLength());
        dnr_instance.packAdn(buf);
        if (dnr_instance.isAdnOnlyMode()) {
            return;
        }
        buf.writeUint8(dnr_instance.getAddrLength());
        dnr_instance.packAddresses(buf);
        dnr_instance.packSvcParams(buf);
    }
}

void
Option4Dnr::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    setData(begin, end);
    size_t offset = 0;
    while (offset < std::distance(begin, end)) {
        if (std::distance(begin + offset, end) < getMinimalLength()) {
            isc_throw(OutOfRange, "DHCPv4 Encrypted DNS Option (" << type_ << ") malformed: "
                                  "DNR instance data truncated to size "
                                  << std::distance(begin + offset, end));
        }
        DnrInstance dnr_instance(V4);
        dnr_instance.setDnrInstanceDataLength(
            readUint16(&(*(begin + offset)), DNR_INSTANCE_DATA_LENGTH_SIZE));
        OptionBufferConstIter dnr_instance_end = begin + offset +
                                                 dnr_instance.getDnrInstanceDataLength();
        offset += DNR_INSTANCE_DATA_LENGTH_SIZE;
        dnr_instance.setServicePriority(
            readUint16(&(*(begin + offset)), SERVICE_PRIORITY_SIZE));
        offset += SERVICE_PRIORITY_SIZE;

        OpaqueDataTuple adn_tuple(OpaqueDataTuple::LENGTH_1_BYTE, begin + offset, dnr_instance_end);
        auto adn_length = adn_tuple.getLength();
        dnr_instance.setAdnLength(adn_length);

        // Encrypted DNS options are designed to always include an authentication domain name,
        // so when there is no FQDN included, we shall throw an exception.
        if (adn_length == 0) {
            isc_throw(InvalidOptionDnrDomainName, "Mandatory Authentication Domain Name fully "
                                                  "qualified domain-name is missing");
        }

        // Let's try to extract ADN FQDN data.
        InputBuffer name_buf(&(*adn_tuple.getData().begin()), adn_length);
        try {
            auto adn = dnr_instance.getAdn();
            adn.reset(new isc::dns::Name(name_buf, true));
        } catch (const Exception& ex) {
            isc_throw(InvalidOptionDnrDomainName, "failed to parse "
                                                  "fully qualified domain-name from wire format "
                                                  "- " << ex.what());
        }

        offset += adn_tuple.getTotalLength();

        if (begin + offset == dnr_instance_end) {
            // ADN only mode, other fields are not included.
            addDnrInstance(dnr_instance);
            continue;
        }
        dnr_instance.setAdnOnlyMode(false);

        OpaqueDataTuple addr_tuple(OpaqueDataTuple::LENGTH_1_BYTE, begin + offset,
                                   dnr_instance_end);
        auto addr_length = addr_tuple.getLength();
        dnr_instance.setAddrLength(addr_length);
        // It MUST be a multiple of 4.
        if ((addr_length % V4ADDRESS_LEN) != 0) {
            isc_throw(OutOfRange, "DHCPv4 Encrypted DNS Option ("
                                  << type_ << ")"
                                  << " malformed: Addr Len=" << addr_length
                                  << " is not divisible by 4");
        }

        // As per draft-ietf-add-dnr 3.1.8:
        // If additional data is supplied (i.e. not ADN only mode),
        // the option includes at least one valid IP address.
        if (addr_length == 0) {
            isc_throw(OutOfRange, "DHCPv4 Encrypted DNS Option ("
                                  << type_ << ")"
                                  << " malformed: Addr Len=" << addr_length
                                  << " is not greater than 0");
        }

        offset += ADDR_LENGTH_SIZE;
        OptionBufferConstIter addr_begin = begin + offset;
        OptionBufferConstIter addr_end = addr_begin + addr_length;
        auto ip_addresses = dnr_instance.getIpAddresses();

        while (addr_begin != addr_end) {
            const uint8_t* ptr = &(*addr_begin);
            ip_addresses.push_back(IOAddress(readUint32(ptr, std::distance(addr_begin, addr_end))));
            addr_begin += V4ADDRESS_LEN;
            offset += V4ADDRESS_LEN;
        }

        // SvcParams (variable length) field is last.
        auto svc_params_length = std::distance(begin + offset, dnr_instance_end);
        if (svc_params_length > 0) {
            std::string svc_params = dnr_instance.getSvcParams();
            svc_params.assign(begin + offset, dnr_instance_end);
            dnr_instance.checkSvcParams();
        }

        addDnrInstance(dnr_instance);
    }
}

std::string
Option4Dnr::toText(int indent) const {
    return Option::toText(indent);
}

uint16_t
Option4Dnr::len() const {
    uint16_t len = OPTION4_HDR_LEN;
    for (const DnrInstance& dnr_instance : dnr_instances_) {
        len += dnr_instance.getDnrInstanceDataLength() + DNR_INSTANCE_DATA_LENGTH_SIZE;
    }
    return (len);
}

void
Option4Dnr::addDnrInstance(DnrInstance& dnr_instance) {
    dnr_instances_.push_back(dnr_instance);
}

void
DnrInstance::packAdn(util::OutputBuffer& buf) const {
    if (!adn_) {
        // This should not happen since Encrypted DNS options are designed
        // to always include an authentication domain name.
        isc_throw(InvalidOptionDnrDomainName, "Mandatory Authentication Domain Name fully "
                                              "qualified domain-name is missing");
    }
    isc::dns::LabelSequence label_sequence(*adn_);
    if (label_sequence.getDataLength() > 0) {
        size_t data_length = 0;
        const uint8_t* data = label_sequence.getData(&data_length);
        buf.writeData(data, data_length);
    }
}

void
DnrInstance::packAddresses(util::OutputBuffer& buf) const {
    AddressContainer::const_iterator address = ip_addresses_.begin();
    while (address != ip_addresses_.end()) {
        buf.writeUint32(address->toUint32());
        ++address;
    }
}

void
DnrInstance::packSvcParams(util::OutputBuffer& buf) const {
    if (svc_params_length_ > 0) {
        buf.writeData(&(*svc_params_.begin()), svc_params_length_);
    }
}

std::string
DnrInstance::getAdnAsText() const {
    if (adn_) {
        return (adn_->toText());
    }
    return ("");
}

void
DnrInstance::setAdn(const std::string& adn) {
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
        isc_throw(InvalidOptionDnrDomainName,
                  "Given ADN FQDN length " << adn_len << " is bigger than uint_16 MAX");
    }

    adn_length_ = adn_len;
}

void
DnrInstance::checkSvcParams(bool from_wire_data) {
    std::string svc_params = isc::util::str::trim(svc_params_);
    if (svc_params.empty()) {
        isc_throw(InvalidOptionDnrSvcParams, "Provided Svc Params field is empty");
    }
    if (!from_wire_data) {
        // If Service Params field was not parsed from on-wire data,
        // but actually was provided with ctor, let's calculate svc_params_length_.
        auto svc_params_len = svc_params.length();
        if (svc_params_len > std::numeric_limits<uint16_t>::max()) {
            isc_throw(OutOfRange, "Given Svc Params length " << svc_params_len
                                                             << " is bigger than uint_16 MAX");
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
            isc_throw(InvalidOptionDnrSvcParams,
                      "Wrong Svc Params syntax - key " << key << " must not be used");
        }

        auto insert_res = keys.insert(key);
        if (!insert_res.second) {
            isc_throw(InvalidOptionDnrSvcParams,
                      "Wrong Svc Params syntax - key " << key << " was duplicated");
        }

        if (key.length() > 63) {
            isc_throw(InvalidOptionDnrSvcParams, "Wrong Svc Params syntax - key had more than 63 "
                                                 "characters - "
                                                     << key);
        }

        std::string sanitized_key = sanitizer->scrub(key);
        if (sanitized_key.size() < key.size()) {
            isc_throw(InvalidOptionDnrSvcParams, "Wrong Svc Params syntax - invalid character "
                                                 "used in key - "
                                                     << key);
        }

        if (key_val.size() == 2) {
            // tbd Check value syntax
            std::string value = key_val[1];
        }
    }
}

void
DnrInstance::checkFields() {
    if (svc_params_.empty() && ip_addresses_.empty()) {
        // ADN only mode, nothing more to do.
        return;
    }
    if (!svc_params_.empty() && ip_addresses_.empty()) {
        // As per draft-ietf-add-dnr 3.1.8:
        // If additional data is supplied (i.e. not ADN only mode),
        // the option includes at least one valid IP address.
        isc_throw(OutOfRange,
                  getLogPrefix()
                      << " malformed: No IP address given. Since this is not "
                         "ADN only mode, at least one valid IP address must be included");
    }
    if (!svc_params_.empty()) {
        checkSvcParams(false);
    }
    adn_only_mode_ = false;
    auto addr_len = ip_addresses_.size() * V6ADDRESS_LEN;
    if (addr_len > std::numeric_limits<uint16_t>::max()) {
        isc_throw(OutOfRange,
                  "Given IPv6 addresses length " << addr_len << " is bigger than uint_16 MAX");
    }
    addr_length_ = addr_len;
}

std::string
DnrInstance::getLogPrefix() const {
    return (universe_ == Option::V4) ?
               ("DHCPv4 Encrypted DNS Option (" + std::to_string(DHO_V4_DNR) + ")") :
               ("DHCPv6 Encrypted DNS Option (" + std::to_string(D6O_V6_DNR) + ")");
}

}  // namespace dhcp
}  // namespace isc
