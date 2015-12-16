// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
    // Convert wire-format Pkt4 data in the form of OptionBuffer.
    Pkt4::pack();
    OutputBuffer& buf = getBuffer();
    const uint8_t* ptr = static_cast<const uint8_t*>(buf.getData());
    OptionBuffer msg(ptr, ptr + buf.getLength());

    // Build the DHCPv4 Message option for the DHCPv6 message, and pack the
    // entire stuff.
    OptionPtr dhcp4_msg(new Option(Option::V6, D6O_DHCPV4_MSG, msg));
    pkt6_->addOption(dhcp4_msg);
    pkt6_->pack();
}

} // end of namespace isc::dhcp

} // end of namespace isc
