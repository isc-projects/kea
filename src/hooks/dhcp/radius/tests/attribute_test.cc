// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <attribute_test.h>

namespace isc {
namespace radius {
namespace test {

bool
AttributeTest::compare(ConstAttributePtr first, ConstAttributePtr second) {
    if ((!first && second) || (first && !second)) {
        return (false);
    }
    if (!first && !second) {
        return (true);
    }
    if ((first->getType() != second->getType()) ||
        (first->getValueType() != second->getValueType())) {
        return (false);
    }
    if (first->getValueType() == PW_TYPE_STRING) {
        return (first->toString() == second->toString());
    } else if (first->getValueType() == PW_TYPE_INTEGER) {
        return (first->toInt() == second->toInt());
    } else if (first->getValueType() == PW_TYPE_IPADDR) {
        return (first->toIpAddr() == second->toIpAddr());
    } else if (first->getValueType() == PW_TYPE_IPV6ADDR) {
        return (first->toIpv6Addr() == second->toIpv6Addr());
    } else if (first->getValueType() == PW_TYPE_IPV6PREFIX) {
        return ((first->toIpv6Prefix() == second->toIpv6Prefix()) &&
                (first->toIpv6PrefixLen() == second->toIpv6PrefixLen()));
    }
    // Should not happen...
    return (false);
}

bool
AttributeTest::compare(const Attributes& first, const Attributes& second) {
    auto f = [&](ConstAttributePtr first, ConstAttributePtr second) {
        return (AttributeTest::compare(first, second));
    };
    return (std::equal(first.cbegin(), first.cend(), second.cbegin(), second.cend(), f));
}

} // end of namespace isc::radius::test
} // end of namespace isc::radius
} // end of namespace isc
