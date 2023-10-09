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
    : Option(V4, DHO_CLASSLESS_STATIC_ROUTE) {
    unpack(begin, end);
}

OptionPtr
OptionClasslessStaticRoute::clone() const {
    return (cloneInternal<OptionClasslessStaticRoute>());
}

void
OptionClasslessStaticRoute::pack(isc::util::OutputBuffer& buf, bool check) const {
    Option::pack(buf, check);
}

void
OptionClasslessStaticRoute::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    if (distance(begin, end) % (V4ADDRESS_LEN * 3)) {
        isc_throw(OutOfRange, "DHCPv4 OptionClasslessStaticRoute "
                                  << type_ << " has invalid length=" << distance(begin, end)
                                  << ", must be divisible by 12.");
    }

    while (begin != end) {
        const uint8_t* ptr = &(*begin);
        auto subnet_nr = IOAddress(readUint32(ptr, distance(begin, end)));
        begin += V4ADDRESS_LEN;

        uint32_t subnet_mask = readUint32(ptr, distance(begin, end));
        uint8_t mask_width = calcMaskWidth(subnet_mask);
        begin += V4ADDRESS_LEN;

        auto router_addr = IOAddress(readUint32(ptr, distance(begin, end)));
        begin += V4ADDRESS_LEN;

        StaticRouteTuple route = std::make_tuple(subnet_nr, PrefixLen(mask_width), router_addr);
        addRoute(route);
    }
}

std::string
OptionClasslessStaticRoute::toText(int indent) const {
    return Option::toText(indent);
}

uint16_t
OptionClasslessStaticRoute::len() const {
    return Option::len();
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
OptionClasslessStaticRoute::addRoute(StaticRouteTuple& route) {
    static_routes_.push_back(route);
}

std::vector<uint8_t>
OptionClasslessStaticRoute::encodeDestinationDescriptor(StaticRouteTuple& route) {
    auto subnet = get<0>(route).toBytes();
    auto mask_width= get<1>(route).asUint8();
    std::vector<uint8_t> res;
    res.push_back(mask_width);
    if (mask_width == 0) {
        return (res);
    }

    uint8_t significant_octets = mask_width / 8 + (mask_width % 8 != 0);
    res.insert(res.end(), subnet.begin(), subnet.begin() + significant_octets);

    return (res);
}

}  // namespace dhcp
}  // namespace isc

