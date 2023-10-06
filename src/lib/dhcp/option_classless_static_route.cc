// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "option_classless_static_route.h"

namespace isc {
namespace dhcp {

OptionPtr
OptionClasslessStaticRoute::clone() const {
    return Option::clone();
}

void
OptionClasslessStaticRoute::pack(isc::util::OutputBuffer& buf, bool check) const {
    Option::pack(buf, check);
}

void
OptionClasslessStaticRoute::unpack(OptionBufferConstIter begin,
                                              OptionBufferConstIter end) {
    Option::unpack(begin, end);
}

std::string
OptionClasslessStaticRoute::toText(int indent) const {
    return Option::toText(indent);
}

uint16_t
OptionClasslessStaticRoute::len() const {
    return Option::len();
}

}  // namespace dhcp
}  // namespace isc

