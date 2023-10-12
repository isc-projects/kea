// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/strutil.h>

#include <boost/algorithm/string/erase.hpp>

#include <option_classless_static_route.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

OptionClasslessStaticRoute::OptionClasslessStaticRoute(OptionBufferConstIter begin,
                                                       OptionBufferConstIter end)
    : Option(V4, DHO_CLASSLESS_STATIC_ROUTE), static_routes_(), data_len_(0) {
    unpack(begin, end);
}

OptionPtr
OptionClasslessStaticRoute::clone() const {
    return (cloneInternal<OptionClasslessStaticRoute>());
}

void
OptionClasslessStaticRoute::pack(isc::util::OutputBuffer& buf, bool check) const {
    // Header = option code and length.
    packHeader(buf, check);
    for (const auto& route : static_routes_) {
        // 1-5 octets of destination descriptor
        auto dest = encodeDestinationDescriptor(route);
        buf.writeData(&dest[0], dest.size());
        // IP address of the router
        buf.writeUint32(get<2>(route).toUint32());
    }
}

void
OptionClasslessStaticRoute::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    // Classless Static route option data must contain at least 5 octets.
    // 1 octet - shortest possible destination descriptor (0x00) + 4 octets router IPv4 addr.
    if (distance(begin, end) < 5) {
        isc_throw(OutOfRange, "DHCPv4 OptionClasslessStaticRoute "
                                  << type_ << " has invalid length=" << distance(begin, end)
                                  << ", must be at least 5.");
    }

    // As an alternative to binary format,
    // we provide convenience option definition as a string in format:
    // subnet1 - router1 IP addr, subnet2 - router2 IP addr, ...
    // e.g.:
    // 10.0.0.0/8 - 10.2.3.1, 10.229.0.128/25 - 10.1.0.3, ...
    // where destination descriptors will be encoded as per RFC3442.
    // We need to determine if OptionBuffer contains dash `-` separator (0x2d).
    // If not, we assume this is binary format and no encoding needs to be done.
    auto begin_copy = begin;
    while (begin_copy != end) {
        if (*begin_copy == '-') {
            break;
        }
        ++begin_copy;
    }
    if (begin_copy == end) {
        // no separator found, assuming this is a hex on-wire data
        setData(begin, end); // TODO: do this or parse hex and feed static_routes_
        // TODO: pack(), toText(), len() etc. basing on _data
    } else {
        // separator was found, assuming this is option data string from config
        std::string buffer_to_str = std::string(begin, end);
        // this option allows more than one static route, so let's separate them using comma
        std::vector<std::string> tokens = util::str::tokens(buffer_to_str, std::string(","));
        std::ostringstream stream;
        for (const auto& route_str : tokens) {
            std::vector<std::string> parts = util::str::tokens(util::str::trim(route_str), std::string("-"));
            if (parts.size() != 2) {
                isc_throw(BadValue, "DHCPv4 OptionClasslessStaticRoute "
                                        << type_ << " has invalid value, route definition must"
                                                    " have format as in example: 10.229.0.128/25 - 10.229.0.1, "
                                                    "0.0.0.0/0 - 10.129.0.2");
            }
            std::string txt = parts[0];

            // first let's remove any whitespaces
            boost::erase_all(txt, " "); // space
            boost::erase_all(txt, "\t"); // tabulation

            // Is this prefix/len notation?
            size_t pos = txt.find("/");

            if (pos == std::string::npos) {
                isc_throw(BadValue, "DHCPv4 OptionClasslessStaticRoute "
                                        << type_ << " has invalid value, provided IPv4 prefix "
                                        << parts[0] << " is not valid.");
            }

            std::string txt_address = txt.substr(0, pos);
            isc::asiolink::IOAddress address = isc::asiolink::IOAddress(txt_address);
            if (!address.isV4()) {
                isc_throw(BadValue, "DHCPv4 OptionClasslessStaticRoute "
                                        << type_ << " has invalid value, provided address "
                                               << txt_address
                                               << " is not a valid IPv4 address.");
            }

            std::string txt_prefix = txt.substr(pos + 1);
            uint8_t len = 0;
            try {
                // start with the first character after /
                len = static_cast<uint8_t>(boost::lexical_cast<int64_t>(txt_prefix));
            } catch (...)  {
                isc_throw(BadValue, "DHCPv4 OptionClasslessStaticRoute "
                                        << type_ << " has invalid value, provided prefix len "
                                               << txt_prefix
                                               << " is not valid.");
            }

            stream << route_str << ", ";
        }


        isc_throw(OutOfRange, "DHCPv4 OptionClasslessStaticRoute unpack from string '" + (buffer_to_str) + "' tokens: " + stream.str());
    }


    while (begin != end) {
        // Subnet number IP address e.g. 10.229.0.128
        const uint8_t* ptr = &(*begin);
        auto subnet_nr = IOAddress(readUint32(ptr, distance(begin, end)));
        begin += V4ADDRESS_LEN;

        // Subnet mask e.g. 255.255.255.128
        uint32_t subnet_mask = readUint32(ptr + V4ADDRESS_LEN, distance(begin, end));
        uint8_t mask_width = calcMaskWidth(subnet_mask);
        begin += V4ADDRESS_LEN;

        // Router IP address
        auto router_addr = IOAddress(readUint32(ptr + (2 * V4ADDRESS_LEN), distance(begin, end)));
        begin += V4ADDRESS_LEN;

        StaticRouteTuple route = std::make_tuple(subnet_nr, mask_width, router_addr);
        static_routes_.push_back(route);
    }

    calcDataLen();
}

std::string
OptionClasslessStaticRoute::toText(int indent) const {
    std::ostringstream stream;
    std::string in(indent, ' ');  // base indentation
    stream << in << "type=" << type_ << "(CLASSLESS_STATIC_ROUTE), "
           << "len=" << (len() - getHeaderLen());
    int i = 0;
    for (const auto& route : static_routes_) {
        stream << ", Route " << ++i
               << " (subnet " << get<0>(route).toText() << "/"
               << static_cast<int>(get<1>(route)) << ", router IP "
               << get<2>(route) << ")";
    }

    return (stream.str());
}

uint16_t
OptionClasslessStaticRoute::len() const {
    uint16_t len = OPTION4_HDR_LEN;
    len += data_len_;
    return (len);
}

uint8_t
OptionClasslessStaticRoute::calcMaskWidth(uint32_t subnet_mask) {
    uint8_t len = 0;
    while (subnet_mask) {
        if (subnet_mask & 0x80000000) {
            ++len;
            subnet_mask <<= 1;
            continue;
        }

        break;
    }

    return (len);
}

void
OptionClasslessStaticRoute::addRoute(const StaticRouteTuple& route) {
    static_routes_.push_back(route);
    calcDataLen();
}

std::vector<uint8_t>
OptionClasslessStaticRoute::encodeDestinationDescriptor(const StaticRouteTuple& route) {
    // Encoding as per RFC3442
    const std::vector<uint8_t>& subnet = get<0>(route).toBytes();
    const uint8_t& mask_width = get<1>(route);

    std::vector<uint8_t> res;
    res.push_back(mask_width);
    if (mask_width == 0) {
        // there are no significant octets, destination descriptor is 0 value - one octet long
        return (res);
    }

    uint8_t significant_octets = calcSignificantOctets(mask_width);
    res.insert(res.end(), subnet.begin(), subnet.begin() + significant_octets);

    return (res);
}

uint8_t
OptionClasslessStaticRoute::calcSignificantOctets(const uint8_t& mask_width) {
    return (mask_width / 8 + (mask_width % 8 != 0));
}

void
OptionClasslessStaticRoute::calcDataLen() {
    uint16_t len = 0;
    for (const auto& route : static_routes_) {
        // 1-5 octets of destination descriptor
        len += calcSignificantOctets(get<1>(route)) + 1;
        // IP address of the router
        len += 4;
    }

    data_len_ = len;
}

}  // namespace dhcp
}  // namespace isc
