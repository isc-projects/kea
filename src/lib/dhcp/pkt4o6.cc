// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/pkt4o6.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace {

/// @brief Default address used in Pkt4 constructor
const IOAddress DEFAULT_ADDRESS("0.0.0.0");
}

namespace isc {
namespace dhcp {

Pkt4o6::Pkt4o6(const OptionBuffer& pkt4, const Pkt6Ptr& pkt6)
    :Pkt4(&pkt4[0], pkt4.size()), pkt6_(pkt6)
{
    static_cast<void>(pkt6->delOption(D6O_DHCPV4_MSG));
    setIface(pkt6->getIface());
    setIndex(pkt6->getIndex());
    setRemoteAddr(pkt6->getRemoteAddr());
}

Pkt4o6::Pkt4o6(const Pkt4Ptr& pkt4, const Pkt6Ptr& pkt6)
    :Pkt4(*pkt4), pkt6_(pkt6) {
}

void Pkt4o6::pack() {
    Pkt4::pack();
    OutputBuffer& buf = getBuffer();
    const uint8_t* ptr = static_cast<const uint8_t*>(buf.getData());
    OptionBuffer msg(ptr, ptr + buf.getLength());
    OptionPtr dhcp4_msg(new Option(Option::V6, D6O_DHCPV4_MSG, msg));
    pkt6_->addOption(dhcp4_msg);
    pkt6_->pack();
}

} // end of namespace isc::dhcp

} // end of namespace isc
