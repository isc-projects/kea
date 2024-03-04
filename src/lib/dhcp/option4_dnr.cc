// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option4_dnr.h>
#include <dns/labelsequence.h>
#include <util/io.h>
#include <util/str.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

Option4Dnr::Option4Dnr(OptionBufferConstIter begin,
                       OptionBufferConstIter end,
                       bool convenient_notation)
    : Option(V4, DHO_V4_DNR), convenient_notation_(convenient_notation) {
    unpack(begin, end);
}

OptionPtr
Option4Dnr::clone() const {
    return (cloneInternal<Option4Dnr>());
}

void
Option4Dnr::pack(OutputBuffer& buf, bool check) const {
    packHeader(buf, check);
    for (const DnrInstance& dnr_instance : dnr_instances_) {
        buf.writeUint16(dnr_instance.getDnrInstanceDataLength());
        buf.writeUint16(dnr_instance.getServicePriority());
        buf.writeUint8(dnr_instance.getAdnLength());
        dnr_instance.packAdn(buf);
        if (dnr_instance.isAdnOnlyMode()) {
            continue;
        }

        buf.writeUint8(dnr_instance.getAddrLength());
        dnr_instance.packAddresses(buf);
        dnr_instance.packSvcParams(buf);
    }
}

void
Option4Dnr::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    if (convenient_notation_) {
        // parse convenient notation
        std::string config_txt = std::string(begin, end);
        parseConfigData(config_txt);
    } else {
        setData(begin, end);
        while (begin != end) {
            DnrInstance dnr_instance(V4);
            if (std::distance(begin, end) < dnr_instance.getMinimalLength()) {
                isc_throw(OutOfRange, dnr_instance.getLogPrefix()
                                          << "DNR instance data truncated to size "
                                          << std::distance(begin, end));
            }

            // Unpack DnrInstanceDataLength.
            dnr_instance.unpackDnrInstanceDataLength(begin, end);

            const OptionBufferConstIter dnr_instance_end = begin +
                                                           dnr_instance.getDnrInstanceDataLength();

            // Unpack Service priority.
            dnr_instance.unpackServicePriority(begin);

            // Unpack ADN len + ADN.
            dnr_instance.unpackAdn(begin, dnr_instance_end);

            if (begin == dnr_instance_end) {
                // ADN only mode, other fields are not included.
                addDnrInstance(dnr_instance);
                continue;
            }

            dnr_instance.setAdnOnlyMode(false);

            // Unpack Addr Len + IPv4 Address(es).
            dnr_instance.unpackAddresses(begin, dnr_instance_end);

            // SvcParams (variable length) field is last.
            dnr_instance.unpackSvcParams(begin, dnr_instance_end);

            addDnrInstance(dnr_instance);
        }
    }
}

std::string
Option4Dnr::toText(int indent) const {
    std::ostringstream stream;
    std::string in(indent, ' ');  // base indentation
    stream << in << "type=" << type_ << "(V4_DNR), "
           << "len=" << (len() - getHeaderLen());
    int i = 0;
    for (const DnrInstance& dnr_instance : dnr_instances_) {
        stream << ", DNR Instance " << ++i
               << "(Instance len=" << dnr_instance.getDnrInstanceDataLength() << ", "
               << dnr_instance.getDnrInstanceAsText() << ")";
    }

    return (stream.str());
}

uint16_t
Option4Dnr::len() const {
    uint16_t len = OPTION4_HDR_LEN;
    for (const DnrInstance& dnr_instance : dnr_instances_) {
        len += dnr_instance.getDnrInstanceDataLength() +
               dnr_instance.getDnrInstanceDataLengthSize();
    }

    return (len);
}

void
Option4Dnr::addDnrInstance(DnrInstance& dnr_instance) {
    dnr_instances_.push_back(dnr_instance);
}

void
Option4Dnr::parseConfigData(const std::string& config_txt) {
    // This parses convenient option config notation.
    // The config to be parsed may contain escaped characters like "\\," or "\\|".
    // Example configs are below (first contains two DNR instances in one option with recommended
    // resolvers' IP addresses, and SvcParams - DNR instances are separated with pipe "|" char;
    // second is an example of ADN-only mode;
    // third is like the first example, but for single DNR instance):
    //
    // "name": "v4-dnr",
    // "data": "10, dot1.example.org., 10.0.2.3 10.3.4.5, alpn=dot\\,doq | 20, dot2.example.org., 10.0.2.3 10.3.4.5, alpn=dot"
    //
    // "name": "v4-dnr",
    // "data": "200, resolver.example."
    //
    // "name": "v4-dnr",
    // "data": "100, dot1.example.org., 10.0.3.4 10.1.5.6, alpn=dot\\,doq\\,h2\\,h3 port=8530 dohpath=/q{?dns}"

    // Get Dnr Instance tokens using pipe separator with double backslash escaping enabled.
    std::vector<std::string> tokens = str::tokens(config_txt, std::string("|"), true);

    for (auto const& txt_dnr_instance : tokens) {
        DnrInstance dnr_instance(V4);
        dnr_instance.parseDnrInstanceConfigData(txt_dnr_instance);
        dnr_instance.setDnrInstanceDataLength();
        addDnrInstance(dnr_instance);
    }
}

const std::unordered_set<std::string> DnrInstance::FORBIDDEN_SVC_PARAMS = {"ipv4hint", "ipv6hint"};

const DnrInstance::SvcParamsMap DnrInstance::SVC_PARAMS =
    boost::assign::list_of<DnrInstance::SvcParamsMap::relation>
    ("mandatory", 0)        // RFC 9460, Section 14.3.2, not used in DNR
    ("alpn", 1)             // RFC 9460, Section 14.3.2, mandatory in DNR
    ("no-default-alpn", 2)  // RFC 9460, Section 14.3.2, not used in DNR
    ("port", 3)             // RFC 9460, Section 14.3.2, optional in DNR
    ("ipv4hint", 4)         // RFC 9460, Section 14.3.2, forbidden in DNR
    ("ech", 5)              // RFC 9460, Section 14.3.2, not used in DNR
    ("ipv6hint", 6)         // RFC 9460, Section 14.3.2, forbidden in DNR
    ("dohpath", 7)          // RFC 9461, optional in DNR
    ("ohttp", 8)            // https://datatracker.ietf.org/doc/draft-ietf-ohai-svcb-config,
                            // not used in DNR
    ;

const std::set<uint8_t> DnrInstance::SUPPORTED_SVC_PARAMS = {1, 3, 7};

const std::unordered_set<std::string> DnrInstance::ALPN_IDS = {
    "http/0.9",            // HTTP/0.9
    "http/1.0",            // HTTP/1.0
    "http/1.1",            // HTTP/1.1
    "spdy/1",              // SPDY/1
    "spdy/2",              // SPDY/2
    "spdy/3",              // SPDY/3
    "stun.turn",           // Traversal Using Relays around NAT (TURN)
    "stun.nat-discovery",  // NAT discovery using Session Traversal Utilities for NAT (STUN)
    "h2",                  // HTTP/2 over TLS
    "h2c",                 // HTTP/2 over TCP
    "webrtc",              // WebRTC Media and Data
    "c-webrtc",            // Confidential WebRTC Media and Data
    "ftp",                 // FTP
    "imap",                // IMAP
    "pop3",                // POP3
    "managesieve",         // ManageSieve
    "coap",                // CoAP
    "xmpp-client",         // XMPP jabber:client namespace
    "xmpp-server",         // XMPP jabber:server namespace
    "acme-tls/1",          // acme-tls/1
    "mqtt",                // OASIS Message Queuing Telemetry Transport (MQTT)
    "dot",                 // DNS-over-TLS
    "ntske/1",             // Network Time Security Key Establishment, version 1
    "sunrpc",              // SunRPC
    "h3",                  // HTTP/3
    "smb",                 // SMB2
    "irc",                 // IRC
    "nntp",                // NNTP (reading)
    "nnsp",                // NNTP (transit)
    "doq",                 // DoQ
    "sip/2",               // SIP
    "tds/8.0",             // TDS/8.0
    "dicom"                // DICOM
};

DnrInstance::DnrInstance(Option::Universe universe)
    : universe_(universe), dnr_instance_data_length_(0), service_priority_(0), adn_length_(0),
      addr_length_(0), svc_params_length_(0), adn_only_mode_(true), alpn_http_(false),
      dnr_instance_data_length_size_(0), adn_length_size_(0), addr_length_size_(0),
      minimal_length_(0) {
    initMembers();
}

void
DnrInstance::packAdn(OutputBuffer& buf) const {
    if (!adn_) {
        // This should not happen since Encrypted DNS options are designed
        // to always include an authentication domain name.
        isc_throw(InvalidOptionDnrDomainName, getLogPrefix()
                                                  << "Mandatory Authentication Domain Name fully "
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
DnrInstance::packAddresses(OutputBuffer& buf) const {
    AddressContainer::const_iterator address = ip_addresses_.begin();
    while (address != ip_addresses_.end()) {
        buf.writeUint32(address->toUint32());
        ++address;
    }
}

void
DnrInstance::packSvcParams(OutputBuffer& buf) const {
    if (svc_params_length_ > 0 && !svc_params_buf_.empty()) {
        buf.writeData(svc_params_buf_.data(), svc_params_length_);
    }
}

std::string
DnrInstance::getAdnAsText() const {
    return (adn_) ? (adn_->toText()) : ("");
}

void
DnrInstance::unpackAdn(OptionBufferConstIter& begin, OptionBufferConstIter end) {
    OpaqueDataTuple::LengthFieldType lft = OptionDataTypeUtil::getTupleLenFieldType(universe_);
    OpaqueDataTuple adn_tuple(lft);
    try {
        adn_tuple.unpack(begin, end);
    } catch (const Exception& ex) {
        isc_throw(BadValue, getLogPrefix() << "failed to unpack ADN data"
                                           << " - " << ex.what());
    }

    adn_length_ = adn_tuple.getLength();

    // Encrypted DNS options are designed to always include an authentication domain name,
    // so when there is no FQDN included, we shall throw an exception.
    if (adn_length_ == 0) {
        isc_throw(InvalidOptionDnrDomainName, getLogPrefix()
                                                  << "Mandatory Authentication Domain Name fully "
                                                     "qualified domain-name is missing");
    }

    InputBuffer name_buf(adn_tuple.getData().data(), adn_length_);
    try {
        adn_.reset(new isc::dns::Name(name_buf, true));
    } catch (const Exception& ex) {
        isc_throw(InvalidOptionDnrDomainName, getLogPrefix()
                                                  << "Failed to parse fully qualified domain-name "
                                                  << "from wire format - " << ex.what());
    }

    begin += adn_length_ + getAdnLengthSize();
}

std::string
DnrInstance::svcParamValAsText(const std::pair<uint16_t, OpaqueDataTuple>& svc_param) const {
    OptionBufferConstIter alpn_begin;
    OptionBufferConstIter alpn_end;
    std::ostringstream stream;
    OpaqueDataTuple alpn_id_tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    bool first = true;
    std::string ret;

    switch (svc_param.first) {
    case 1:
        // alpn
        // read all protocols and concatenate them with comma
        alpn_begin = svc_param.second.getData().begin();
        alpn_end = svc_param.second.getData().end();
        while (alpn_begin != alpn_end) {
            try {
                alpn_id_tuple.unpack(alpn_begin, alpn_end);
            } catch (const Exception& e) {
                isc_throw(BadValue, getLogPrefix()
                                        << "Exception happened when tried to parse ALPN IDs"
                                        << ". Error: " << e.what());
            }

            if (first) {
                first = false;
            } else {
                stream << ",";
            }

            stream << alpn_id_tuple.getText();
            alpn_begin += alpn_id_tuple.getTotalLength();
        }

        ret = stream.str();
        break;
    case 3:
        // port
        // read uint16 from data buffer and return as string
        ret = std::to_string(
            readUint16(svc_param.second.getData().data(), svc_param.second.getLength()));
        break;
    case 7:
        // dohpath
        // conversion not needed, let's return data as string
        ret = svc_param.second.getText();
        break;
    }

    return (ret);
}

std::string
DnrInstance::getDnrInstanceAsText() const {
    std::ostringstream stream;
    stream << "service_priority=" << service_priority_ << ", adn_length=" << adn_length_ << ", "
           << "adn='" << getAdnAsText() << "'";
    if (!adn_only_mode_) {
        stream << ", addr_length=" << addr_length_ << ", address(es):";
        for (auto const& address : ip_addresses_) {
            stream << " " << address.toText();
        }

        if (svc_params_length_ > 0) {
            stream << ", svc_params='";
            bool first = true;
            for (auto const& it : svc_params_map_) {
                auto const& k = SVC_PARAMS.right.at(it.first);
                if (first) {
                    first = false;
                } else {
                    stream << " ";
                }

                stream << k << "=" << svcParamValAsText(it);
            }

            stream << "'";
        }
    }

    return (stream.str());
}

uint16_t
DnrInstance::dnrInstanceLen() const {
    uint16_t len = SERVICE_PRIORITY_SIZE + adn_length_ + getAdnLengthSize();
    if (!adn_only_mode_) {
        len += addr_length_ + getAddrLengthSize() + svc_params_length_;
    }

    return (len);
}

void
DnrInstance::addIpAddress(const IOAddress& ip_address) {
    ip_addresses_.push_back(ip_address);
}

void
DnrInstance::unpackDnrInstanceDataLength(OptionBufferConstIter& begin, OptionBufferConstIter end) {
    dnr_instance_data_length_ = readUint16(&*begin, getDnrInstanceDataLengthSize());
    begin += getDnrInstanceDataLengthSize();
    if (std::distance(begin, end) < dnr_instance_data_length_) {
        isc_throw(OutOfRange, getLogPrefix()
                                  << "DNR instance data truncated to size "
                                  << std::distance(begin, end) << " but it was supposed to be "
                                  << dnr_instance_data_length_);
    }
}

void
DnrInstance::unpackServicePriority(OptionBufferConstIter& begin) {
    service_priority_ = readUint16(&*begin, SERVICE_PRIORITY_SIZE);
    begin += SERVICE_PRIORITY_SIZE;
}

void
DnrInstance::unpackAddresses(OptionBufferConstIter& begin, const OptionBufferConstIter end) {
    OpaqueDataTuple addr_tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    try {
        addr_tuple.unpack(begin, end);
    } catch (const Exception& ex) {
        isc_throw(BadValue, getLogPrefix() << "failed to unpack IP Addresses data"
                                           << " - " << ex.what());
    }

    addr_length_ = addr_tuple.getLength();
    // It MUST be a multiple of 4.
    if ((addr_length_ % V4ADDRESS_LEN) != 0) {
        isc_throw(OutOfRange, getLogPrefix()
                                  << "Addr Len=" << addr_length_ << " is not divisible by 4");
    }

    // As per RFC9463 Section 3.1.8:
    // If additional data is supplied (i.e. not ADN only mode),
    // the option includes at least one valid IP address.
    if (addr_length_ == 0) {
        isc_throw(OutOfRange, getLogPrefix()
                                  << "Addr Len=" << addr_length_
                                  << " but it must contain at least one valid IP address");
    }

    begin += getAddrLengthSize();
    OptionBufferConstIter addr_begin = begin;
    OptionBufferConstIter addr_end = addr_begin + addr_length_;

    while (addr_begin != addr_end) {
        const uint8_t* ptr = &(*addr_begin);
        addIpAddress(IOAddress(readUint32(ptr, std::distance(addr_begin, addr_end))));
        addr_begin += V4ADDRESS_LEN;
        begin += V4ADDRESS_LEN;
    }
}

void
DnrInstance::unpackSvcParams(OptionBufferConstIter& begin, OptionBufferConstIter end) {
    svc_params_length_ = std::distance(begin, end);
    if (svc_params_length_ > 0) {
        svc_params_buf_.assign(begin, end);

        // used to check correct order of SvcParams
        int prev_svc_param_key = -1;

        // When the list of SvcParams is non-empty, it contains a series of
        // SvcParamKey=SvcParamValue pairs, represented as:
        // - a 2-octet field containing the SvcParamKey as an integer in network byte order.
        // - a 2-octet field containing the length of the SvcParamValue as an integer
        //   between 0 and 65535 in network byte order. (uint16)
        // - an octet string of this length whose contents are the SvcParamValue in a format
        //   determined by the SvcParamKey.
        while (begin != end) {
            // Minimum SvcParams len shall be 4:
            // 2 octets SvcParamKey + 2 octets SvcParamValue Len
            if (std::distance(begin, end) < 4) {
                isc_throw(OutOfRange, getLogPrefix() << "DNR SvcParams data truncated to size "
                                                     << std::distance(begin, end));
            }

            uint16_t num_svc_param_key = readUint16(&*begin, 2);
            begin += 2;

            // Check if SvcParamKey is known in
            // https://www.iana.org/assignments/dns-svcb/dns-svcb.xhtml
            auto it = SVC_PARAMS.right.find(num_svc_param_key);
            if (it == SVC_PARAMS.right.end()) {
                isc_throw(InvalidOptionDnrSvcParams,
                          getLogPrefix() << "Wrong Svc Params syntax - key " << num_svc_param_key
                                         << " not found in SvcParamKeys registry");
            }

            std::string svc_param_key = it->second;

            // As per RFC9463 Section 3.1.8:
            // The service parameters do not include "ipv4hint" or "ipv6hint" parameters.
            if (FORBIDDEN_SVC_PARAMS.find(svc_param_key) != FORBIDDEN_SVC_PARAMS.end()) {
                isc_throw(InvalidOptionDnrSvcParams, getLogPrefix()
                                                         << "Wrong Svc Params syntax - key "
                                                         << svc_param_key << " must not be used");
            }

            // Check if SvcParamKey usage is supported by DNR DHCP option.
            // Note that SUPPORTED_SVC_PARAMS set may expand in the future.
            if (SUPPORTED_SVC_PARAMS.find(num_svc_param_key) == SUPPORTED_SVC_PARAMS.end()) {
                isc_throw(InvalidOptionDnrSvcParams,
                          getLogPrefix() << "Wrong Svc Params syntax - key " << svc_param_key
                                         << " not supported in DNR option SvcParams");
            }

            // As per RFC9460 Section 2.2:
            // SvcParamKeys SHALL appear in increasing numeric order. (...)
            // There are no duplicate SvcParamKeys.
            //
            // We check for duplicates here.
            if (svc_params_map_.find(num_svc_param_key) != svc_params_map_.end()) {
                isc_throw(InvalidOptionDnrSvcParams, getLogPrefix()
                                                         << "Wrong Svc Params syntax - key "
                                                         << svc_param_key << " is duplicated.");
            }

            // And we check correct order here.
            if (num_svc_param_key <= prev_svc_param_key) {
                isc_throw(InvalidOptionDnrSvcParams,
                          getLogPrefix() << "Wrong Svc Params syntax - SvcParamKeys"
                                         << " SHALL appear in increasing numeric order.");
            }

            prev_svc_param_key = num_svc_param_key;

            // Let's try to unpack SvcParamVal into a tuple.
            OpaqueDataTuple svc_param_tuple(OpaqueDataTuple::LENGTH_2_BYTES);
            try {
                svc_param_tuple.unpack(begin, end);
            } catch (const Exception& e) {
                isc_throw(InvalidOptionDnrSvcParams,
                          getLogPrefix()
                              << "Wrong Svc Params syntax - failed to unpack SvcParamVal for "
                              << "SvcParamKey " << svc_param_key << ". Error: " << e.what());
            }

            svc_params_map_.insert(std::make_pair(num_svc_param_key, svc_param_tuple));
            begin += svc_param_tuple.getTotalLength();
        }
    }
}

void
DnrInstance::initMembers() {
    dnr_instance_data_length_size_ = (universe_ == Option::V6) ? 0 : 2;
    adn_length_size_ = (universe_ == Option::V6) ? 2 : 1;
    addr_length_size_ = (universe_ == Option::V6) ? 2 : 1;
    minimal_length_ = dnr_instance_data_length_size_ + SERVICE_PRIORITY_SIZE + adn_length_size_;
    log_prefix_ =
        (universe_ == Option::V4) ?
            ("DHCPv4 Encrypted DNS Option (" + std::to_string(DHO_V4_DNR) + ") malformed: ") :
            ("DHCPv6 Encrypted DNS Option (" + std::to_string(D6O_V6_DNR) + ") malformed: ");
}

void
DnrInstance::parseDnrInstanceConfigData(const std::string& config_txt) {
    // This parses convenient option config notation.
    // The config to be parsed may contain escaped characters like "\\," or "\\|".
    // Example configs are below (first contains recommended resolvers' IP addresses, and SvcParams;
    // second is an example of ADN-only mode;
    // third is like the first example, but for DNRv4 - single DNR instance):
    //
    // "name": "v6-dnr",
    // "data": "100, dot1.example.org., 2001:db8::1 2001:db8::2, alpn=dot\\,doq\\,h2\\,h3 port=8530 dohpath=/q{?dns}"
    //
    // "name": "v6-dnr",
    // "data": "200, resolver.example."
    //
    // "name": "v4-dnr",
    // "data": "100, dot1.example.org., 10.0.3.4 10.1.5.6, alpn=dot\\,doq\\,h2\\,h3 port=8530 dohpath=/q{?dns}"

    // get tokens using comma separator with double backslash escaping enabled
    std::vector<std::string> tokens = str::tokens(config_txt, std::string(","), true);

    if (tokens.size() < 2) {
        isc_throw(BadValue, getLogPrefix() << "Option config requires at least comma separated "
                                           << "Service Priority and ADN");
    }

    if (tokens.size() > 4) {
        isc_throw(BadValue, getLogPrefix() << "Option config supports maximum 4 comma separated "
                                           << "fields: Service Priority, ADN, resolver IP "
                                           << "address(es) and SvcParams");
    }

    // parse Service Priority
    std::string txt_svc_priority = str::trim(tokens[0]);
    try {
        service_priority_ = boost::lexical_cast<uint16_t>(txt_svc_priority);
    } catch (const std::exception& e) {
        isc_throw(BadValue, getLogPrefix() << "Cannot parse uint_16 integer Service priority "
                                           << "from given value: " << txt_svc_priority
                                           << ". Error: " << e.what());
    }

    // parse ADN
    std::string txt_adn = str::trim(tokens[1]);
    try {
        adn_.reset(new isc::dns::Name(txt_adn, true));
    } catch (const std::exception& e) {
        isc_throw(InvalidOptionDnrDomainName, getLogPrefix() << "Cannot parse ADN FQDN "
                                                             << "from given value: " << txt_adn
                                                             << ". Error: " << e.what());
    }

    adn_length_ = adn_->getLength();
    if (adn_length_ == 0) {
        isc_throw(InvalidOptionDnrDomainName, getLogPrefix()
                                                  << "Mandatory Authentication Domain Name fully "
                                                  << "qualified domain-name is missing");
    }

    if (tokens.size() > 2) {
        setAdnOnlyMode(false);

        // parse resolver IP address(es)
        std::string txt_addresses = str::trim(tokens[2]);

        parseIpAddresses(txt_addresses);
    }

    if (tokens.size() == 4) {
        // parse Service Parameters
        std::string txt_svc_params = str::trim(tokens[3]);

        parseSvcParams(txt_svc_params);
    }
}

void
DnrInstance::parseIpAddresses(const std::string& txt_addresses) {
    // determine v4/v6 universe
    std::string ip_version = (universe_ == Option::V6) ? "IPv6" : "IPv4";
    const size_t addr_len = (universe_ == Option::V6) ? V6ADDRESS_LEN : V4ADDRESS_LEN;

    // IP addresses are separated with space
    std::vector<std::string> addresses = str::tokens(txt_addresses, std::string(" "));
    for (auto const& txt_addr : addresses) {
        try {
            const IOAddress address = IOAddress(str::trim(txt_addr));
            if ((address.isV4() && universe_ == Option::V6) ||
                (address.isV6() && universe_ == Option::V4)) {
                isc_throw(BadValue, "Given address is not " << ip_version << " address.");
            }

            addIpAddress(address);
        } catch (const Exception& e) {
            isc_throw(BadValue, getLogPrefix()
                                    << "Cannot parse " << ip_version << " address "
                                    << "from given value: " << txt_addr << ". Error: " << e.what());
        }
    }

    // As per RFC9463 section 3.1.8:
    // (If ADN-only mode is not used)
    // The option includes at least one valid IP address.
    if (ip_addresses_.empty()) {
        isc_throw(BadValue, getLogPrefix() << "Option config requires at least one valid IP "
                                           << "address.");
    }

    addr_length_ = ip_addresses_.size() * addr_len;
}

void
DnrInstance::parseSvcParams(const std::string& txt_svc_params) {
    // SvcParamKey=SvcParamValue pairs are separated with space
    std::vector<std::string> svc_params_pairs = str::tokens(txt_svc_params, std::string(" "));

    for (auto const& svc_param_pair : svc_params_pairs) {
        std::vector<std::string> key_val_tokens = str::tokens(str::trim(svc_param_pair), "=");
        if (key_val_tokens.size() != 2) {
            isc_throw(InvalidOptionDnrSvcParams,
                      getLogPrefix() << "Wrong Svc Params syntax - SvcParamKey=SvcParamValue "
                                     << "pair syntax must be used");
        }

        // SvcParam Key related checks come below.
        std::string svc_param_key = str::trim(key_val_tokens[0]);

        // As per RFC9463 Section 3.1.8:
        // The service parameters do not include "ipv4hint" or "ipv6hint" parameters.
        if (FORBIDDEN_SVC_PARAMS.find(svc_param_key) != FORBIDDEN_SVC_PARAMS.end()) {
            isc_throw(InvalidOptionDnrSvcParams, getLogPrefix()
                                                     << "Wrong Svc Params syntax - key "
                                                     << svc_param_key << " must not be used");
        }

        // Check if SvcParamKey is known in
        // https://www.iana.org/assignments/dns-svcb/dns-svcb.xhtml
        auto svc_params_iterator = SVC_PARAMS.left.find(svc_param_key);
        if (svc_params_iterator == SVC_PARAMS.left.end()) {
            isc_throw(InvalidOptionDnrSvcParams,
                      getLogPrefix() << "Wrong Svc Params syntax - key " << svc_param_key
                                     << " not found in SvcParamKeys registry");
        }

        // Check if SvcParamKey usage is supported by DNR DHCP option.
        // Note that SUPPORTED_SVC_PARAMS set may expand in the future.
        uint16_t num_svc_param_key = svc_params_iterator->second;
        if (SUPPORTED_SVC_PARAMS.find(num_svc_param_key) == SUPPORTED_SVC_PARAMS.end()) {
            isc_throw(InvalidOptionDnrSvcParams,
                      getLogPrefix() << "Wrong Svc Params syntax - key " << svc_param_key
                                     << " not supported in DNR option SvcParams");
        }

        // As per RFC9460 Section 2.2:
        // SvcParamKeys SHALL appear in increasing numeric order. (...)
        // There are no duplicate SvcParamKeys.
        //
        // We check for duplicates here. Correct ordering is done when option gets packed.
        if (svc_params_map_.find(num_svc_param_key) != svc_params_map_.end()) {
            isc_throw(InvalidOptionDnrSvcParams, getLogPrefix()
                                                     << "Wrong Svc Params syntax - key "
                                                     << svc_param_key << " is duplicated.");
        }

        // SvcParam Val check.
        std::string svc_param_val = str::trim(key_val_tokens[1]);
        if (svc_param_val.empty()) {
            isc_throw(InvalidOptionDnrSvcParams,
                      getLogPrefix() << "Wrong Svc Params syntax - empty SvcParamValue for key "
                                     << svc_param_key);
        }

        switch (num_svc_param_key) {
        case 1:
            parseAlpnSvcParam(svc_param_val);
            break;
        case 3:
            parsePortSvcParam(svc_param_val);
            break;
        case 7:
            parseDohpathSvcParam(svc_param_val);
            break;
        default:
            // This should not happen because we check if num_svc_param_key is
            // in SUPPORTED_SVC_PARAMS before. But in case new SvcParam appears in Supported,
            // and is not handled here...
            isc_throw(InvalidOptionDnrSvcParams, getLogPrefix()
                                                     << "Wrong Svc Params syntax - key "
                                                     << num_svc_param_key << " not supported yet.");
        }
    }

    // If the "alpn" SvcParam indicates support for HTTP, "dohpath" MUST be present.
    if (alpn_http_ && svc_params_map_.find(7) == svc_params_map_.end()) {
        isc_throw(InvalidOptionDnrSvcParams,
                  getLogPrefix() << "Wrong Svc Params syntax - dohpath SvcParam missing. "
                                 << "When alpn SvcParam indicates "
                                 << "support for HTTP, dohpath must be present.");
    }

    // At this step all given SvcParams should be fine. We can pack everything to data
    // buffer according to RFC9460 Section 2.2.
    //
    // When the list of SvcParams is non-empty, it contains a series of
    // SvcParamKey=SvcParamValue pairs, represented as:
    // - a 2-octet field containing the SvcParamKey as an integer in network byte order.
    // - a 2-octet field containing the length of the SvcParamValue as an integer
    //   between 0 and 65535 in network byte order. (uint16)
    // - an octet string of this length whose contents are the SvcParamValue in a format
    //   determined by the SvcParamKey.
    // (...)
    // SvcParamKeys SHALL appear in increasing numeric order.
    // Note that (...) there are no duplicate SvcParamKeys.
    OutputBuffer out_buf(2);

    for (auto const& svc_param_key : SUPPORTED_SVC_PARAMS) {
        auto it = svc_params_map_.find(svc_param_key);
        if (it != svc_params_map_.end()) {
            // Write 2-octet field containing the SvcParamKey as an integer
            // in network byte order.
            out_buf.writeUint16(it->first);
            // Write 2-octet field containing the length of the SvcParamValue
            // and an octet string of this length whose contents are the SvcParamValue.
            // We use OpaqueDataTuple#pack(&buf) here that will write correct len-data
            // tuple to the buffer.
            (it->second).pack(out_buf);
        }
    }

    // Copy SvcParams buffer from OutputBuffer to OptionBuffer.
    const uint8_t* ptr = static_cast<const uint8_t*>(out_buf.getData());
    OptionBuffer temp_buf(ptr, ptr + out_buf.getLength());
    svc_params_buf_ = temp_buf;
    svc_params_length_ = out_buf.getLength();
    out_buf.clear();
}

void
DnrInstance::parseAlpnSvcParam(const std::string& svc_param_val) {
    // The wire-format value for "alpn" consists of at least one alpn-id prefixed by its
    // length as a single octet, and these length-value pairs are concatenated to form
    // the SvcParamValue.
    OutputBuffer out_buf(2);
    OpaqueDataTuple svc_param_val_tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    std::vector<std::string> alpn_ids_tokens = str::tokens(svc_param_val, std::string(","));
    for (auto const& alpn_id : alpn_ids_tokens) {
        // Check if alpn-id is known in
        // https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xhtml#alpn-protocol-ids
        if (ALPN_IDS.find(alpn_id) == ALPN_IDS.end()) {
            isc_throw(InvalidOptionDnrSvcParams,
                      getLogPrefix() << "Wrong Svc Params syntax - alpn-id " << alpn_id
                                     << " not found in ALPN-IDs registry");
        }

        // Make notice if this is any of http alpn-ids.
        if (alpn_id[0] == 'h') {
            alpn_http_ = true;
        }

        OpaqueDataTuple alpn_id_tuple(OpaqueDataTuple::LENGTH_1_BYTE);
        alpn_id_tuple.append(alpn_id);
        alpn_id_tuple.pack(out_buf);
    }

    svc_param_val_tuple.append(out_buf.getData(), out_buf.getLength());
    svc_params_map_.insert(std::make_pair(1, svc_param_val_tuple));
    out_buf.clear();
}

void
DnrInstance::parsePortSvcParam(const std::string& svc_param_val) {
    // The wire format of the SvcParamValue is the corresponding 2-octet numeric value
    // in network byte order.
    OutputBuffer out_buf(2);
    OpaqueDataTuple svc_param_val_tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    uint16_t port;
    try {
        port = boost::lexical_cast<uint16_t>(svc_param_val);
    } catch (const std::exception& e) {
        isc_throw(InvalidOptionDnrSvcParams, getLogPrefix()
                                                 << "Cannot parse uint_16 integer port nr "
                                                 << "from given value: " << svc_param_val
                                                 << ". Error: " << e.what());
    }

    out_buf.writeUint16(port);
    svc_param_val_tuple.append(out_buf.getData(), out_buf.getLength());
    out_buf.clear();
    svc_params_map_.insert(std::make_pair(3, svc_param_val_tuple));
}

void
DnrInstance::parseDohpathSvcParam(const std::string& svc_param_val) {
    // RFC9461 Section 5
    // single-valued SvcParamKey whose value (in both presentation format and wire
    // format) MUST be a URI Template in relative form ([RFC6570], Section 1.1) encoded
    // in UTF-8 [RFC3629]. If the "alpn" SvcParam indicates support for HTTP,
    // "dohpath" MUST be present. The URI Template MUST contain a "dns" variable,
    // and MUST be chosen such that the result after DoH URI Template expansion
    // (Section 6 of [RFC8484]) is always a valid and functional ":path" value
    // ([RFC9113], Section 8.3.1).
    std::vector<uint8_t> utf8_encoded;
    OpaqueDataTuple svc_param_val_tuple(OpaqueDataTuple::LENGTH_2_BYTES);

    // Check that "dns" variable is there
    if (svc_param_val.find("{?dns}") == std::string::npos) {
        isc_throw(InvalidOptionDnrSvcParams,
                  getLogPrefix() << "Wrong Svc Params syntax - dohpath SvcParamValue URI"
                                 << " Template MUST contain a 'dns' variable.");
    }

    // We hope to have URI containing < 0x80 ASCII chars, however to be sure
    // and to be inline with RFC9461 Section 5, let's encode the dohpath with utf8.
    utf8_encoded = encode::encodeUtf8(svc_param_val);
    svc_param_val_tuple.append(utf8_encoded.begin(), utf8_encoded.size());
    svc_params_map_.insert(std::make_pair(7, svc_param_val_tuple));
}

}  // namespace dhcp
}  // namespace isc
