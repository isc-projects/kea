// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include "dhcp6/addr6.h"
#include "dhcp6/pkt6.h"
#include "dhcp6/iface_mgr.h"
#include "dhcp6/dhcp6_srv.h"

using namespace std;
using namespace isc;

Dhcpv6Srv::Dhcpv6Srv() {
    cout << "Initialization" << endl;
}

Dhcpv6Srv::~Dhcpv6Srv() {
    cout << "DHCPv6 Srv shutdown." << endl;
}

bool Dhcpv6Srv::run() {
    while (true) {
        Pkt6 * pkt;

        pkt = IfaceMgr::instance().receive();

        if (pkt) {
            Addr6 client = pkt->remoteAddr;
            cout << "Received " << pkt->dataLen_ << " bytes, echoing back."
                 << endl;
            IfaceMgr::instance().send(*pkt);
            delete pkt;
        }

        sleep(1);

    }

    return true;
}
