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

#include "dhcp/dhcp6.h"
#include "dhcp/pkt6.h"
#include "dhcp6/iface_mgr.h"
#include "dhcp6/dhcp6_srv.h"

using namespace std;
using namespace isc;

Dhcpv6Srv::Dhcpv6Srv() {
    cout << "Initialization" << endl;

    // first call to instance() will create IfaceMgr (it's a singleton)
    // it may throw something if things go wrong
    IfaceMgr::instance();
}

Dhcpv6Srv::~Dhcpv6Srv() {
    cout << "DHCPv6 Srv shutdown." << endl;
}

bool
Dhcpv6Srv::run() {
    while (true) {
        boost::shared_ptr<Pkt6> query; // client's message
        boost::shared_ptr<Pkt6> rsp;   // server's response

        query = IfaceMgr::instance().receive();

        if (query) {
            if (!query->unpack()) {
                cout << "Failed to parse incoming packet" << endl;
                continue;
            }
            switch (query->getType()) {
            case DHCPV6_SOLICIT:
                rsp = processSolicit(query);
                break;
            case DHCPV6_REQUEST:
                rsp = processRequest(query);
                break;
            case DHCPV6_RENEW:
                rsp = processRenew(query);
                break;
            case DHCPV6_REBIND:
                rsp = processRebind(query);
                break;
            case DHCPV6_CONFIRM:
                rsp = processConfirm(query);
                break;
            case DHCPV6_RELEASE:
                rsp = processRelease(query);
                break;
            case DHCPV6_DECLINE:
                rsp = processDecline(query);
                break;
            default:
                cout << "Unknown pkt type received:"
                     << query->getType() << endl;
            }

            cout << "Received " << query->data_len_ << " bytes packet type="
                 << query->getType() << endl;
            if (rsp != boost::shared_ptr<Pkt6>()) {
                cout << "Replying with " << rsp->getType() << endl;
                IfaceMgr::instance().send(rsp);
            }
        }

        // TODO add support for config session (see src/bin/auth/main.cc)
        //      so this daemon can be controlled from bob
        sleep(1);

    }

    return (true);
}

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processSolicit(boost::shared_ptr<Pkt6> solicit) {

    boost::shared_ptr<Pkt6> reply(new Pkt6(DHCPV6_ADVERTISE,
                                           solicit->getTransid(),
                                           Pkt6::UDP));

    return reply;
}

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processRequest(boost::shared_ptr<Pkt6> request) {
    boost::shared_ptr<Pkt6> reply(new Pkt6(DHCPV6_REPLY,
                                           request->getTransid(),
                                           Pkt6::UDP));

    return reply;
}

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processRenew(boost::shared_ptr<Pkt6> renew) {
    boost::shared_ptr<Pkt6> reply(new Pkt6(DHCPV6_REPLY,
                                           renew->getTransid(),
                                           Pkt6::UDP));
    return reply;
}

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processRebind(boost::shared_ptr<Pkt6> rebind) {
    boost::shared_ptr<Pkt6> reply(new Pkt6(DHCPV6_REPLY,
                                           rebind->getTransid(),
                                           Pkt6::UDP));
    return reply;
}

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processConfirm(boost::shared_ptr<Pkt6> confirm) {
    boost::shared_ptr<Pkt6> reply(new Pkt6(DHCPV6_REPLY,
                                           confirm->getTransid(),
                                           Pkt6::UDP));
    return reply;
}

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processRelease(boost::shared_ptr<Pkt6> release) {
    boost::shared_ptr<Pkt6> reply(new Pkt6(DHCPV6_REPLY,
                                           release->getTransid(),
                                           Pkt6::UDP));
    return reply;
}

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processDecline(boost::shared_ptr<Pkt6> decline) {
    boost::shared_ptr<Pkt6> reply(new Pkt6(DHCPV6_REPLY,
                                           decline->getTransid(),
                                           Pkt6::UDP));
    return reply;
}
