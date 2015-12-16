// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <d2/d2_zone.h>

namespace isc {
namespace d2 {

D2Zone::D2Zone(const dns::Name& name, const dns::RRClass& rrclass)
    : name_(name), rrclass_(rrclass) {
}

std::string D2Zone::toText() const {
    return (name_.toText() + " " + rrclass_.toText() + " SOA\n");
}

std::ostream&
operator<<(std::ostream& os, const D2Zone& zone) {
    os << zone.toText();
    return (os);
}

} // namespace d2
} // namespace isc

