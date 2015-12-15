// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/exceptions.h>
#include <dns/rcode.h>

namespace isc {
namespace dns {

const Rcode&
DNSMessageFORMERR::getRcode() const {
    return (Rcode::FORMERR());
}

const Rcode&
DNSMessageBADVERS::getRcode() const {
    return (Rcode::BADVERS());
}

} // end of namespace dns
} // end of namespace isc
