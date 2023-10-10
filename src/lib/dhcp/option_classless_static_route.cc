// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

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
    // Static route definition requires n * 3 IPv4 addresses (n>0):
    // Subnet number, subnet mask, router IP
    if (!distance(begin, end) || distance(begin, end) % (V4ADDRESS_LEN * 3)) {
        isc_throw(OutOfRange, "DHCPv4 OptionClasslessStaticRoute "
                                  << type_ << " has invalid length=" << distance(begin, end)
                                  << ", must be not 0 and divisible by 12.");
    }

    while (begin != end) {
        // Subnet number IP address e.g. 10.229.0.128
        const uint8_t* ptr = &(*begin);
        auto subnet_nr = IOAddress(readUint32(ptr, distance(begin, end)));
        begin += V4ADDRESS_LEN;

        // Subnet mask e.g. 255.255.255.128
        uint32_t subnet_mask = readUint32(ptr, distance(begin, end));
        uint8_t mask_width = calcMaskWidth(subnet_mask);
        begin += V4ADDRESS_LEN;

        // Router IP address
        auto router_addr = IOAddress(readUint32(ptr, distance(begin, end)));
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
               << get<1>(route) << ", router IP "
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
