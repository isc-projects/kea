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

#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <dhcp/iface_mgr.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

Dhcpv6Srv::Dhcpv6Srv(uint16_t port) {

//void Dhcpv6Srv::Dhcpv6Srv_impl(uint16_t port) {
    cout << "Initialization" << endl;

    // First call to instance() will create IfaceMgr (it's a singleton).
    // It may throw something if things go wrong.
    IfaceMgr::instance();

    // Now try to open IPv6 sockets on detected interfaces.
    IfaceMgr::instance().openSockets6(port);

    /// @todo: instantiate LeaseMgr here once it is imlpemented.

    setServerID();

    shutdown = false;
}

Dhcpv6Srv::~Dhcpv6Srv() {
    cout << "DHCPv6 Srv shutdown." << endl;

    IfaceMgr::instance().closeSockets();
}

bool
Dhcpv6Srv::run() {
    while (!shutdown) {
        boost::shared_ptr<Pkt6> query; // client's message
        boost::shared_ptr<Pkt6> rsp;   // server's response

        query = IfaceMgr::instance().receive6();

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
            case DHCPV6_INFORMATION_REQUEST:
                rsp = processInfRequest(query);
                break;
            default:
                cout << "Unknown pkt type received:"
                     << query->getType() << endl;
            }

            cout << "Received " << query->data_len_ << " bytes packet type="
                 << query->getType() << endl;
            cout << query->toText();
            if (rsp) {
                rsp->remote_addr_ = query->remote_addr_;
                rsp->local_addr_ = query->local_addr_;
                rsp->remote_port_ = DHCP6_CLIENT_PORT;
                rsp->local_port_ = DHCP6_SERVER_PORT;
                rsp->ifindex_ = query->ifindex_;
                rsp->iface_ = query->iface_;
                cout << "Replying with:" << rsp->getType() << endl;
                cout << rsp->toText();
                cout << "----" << endl;
                if (rsp->pack()) {
                    cout << "#### pack successful." << endl;
                }
                IfaceMgr::instance().send(rsp);
            }
        }

        // TODO add support for config session (see src/bin/auth/main.cc)
        //      so this daemon can be controlled from bob
    }

    return (true);
}

void
Dhcpv6Srv::setServerID() {
    /// TODO implement this for real once interface detection is done.
    /// Use hardcoded server-id for now

    boost::shared_array<uint8_t> srvid(new uint8_t[14]);
    srvid[0] = 0;
    srvid[1] = 1; // DUID type 1 = DUID-LLT (see section 9.2 of RFC3315)
    srvid[2] = 0;
    srvid[3] = 6; // HW type = ethernet (I think. I'm typing this from my head
                  // in hotel, without Internet connection)
    for (int i=4; i<14; i++) {
        srvid[i]=i-4;
    }
    serverid_ = boost::shared_ptr<Option>(new Option(Option::V6,
                                                     D6O_SERVERID,
                                                     srvid,
                                                     0, 14));
}

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processSolicit(boost::shared_ptr<Pkt6> solicit) {

    boost::shared_ptr<Pkt6> reply(new Pkt6(DHCPV6_ADVERTISE,
                                           solicit->getTransid(),
                                           Pkt6::UDP));

    /// TODO Rewrite this once LeaseManager is implemented.

    // answer client's IA (this is mostly a dummy,
    // so let's answer only first IA and hope there is only one)
    boost::shared_ptr<Option> ia_opt = solicit->getOption(D6O_IA_NA);
    if (ia_opt) {
        // found IA
        Option* tmp = ia_opt.get();
        Option6IA* ia_req = dynamic_cast<Option6IA*>(tmp);
        if (ia_req) {
            boost::shared_ptr<Option6IA>
                ia_rsp(new Option6IA(D6O_IA_NA, ia_req->getIAID()));
            ia_rsp->setT1(1500);
            ia_rsp->setT2(2600);
            boost::shared_ptr<Option6IAAddr>
                addr(new Option6IAAddr(D6O_IAADDR,
                                       IOAddress("2001:db8:1234:5678::abcd"),
                                       5000, 7000));
            ia_rsp->addOption(addr);
            reply->addOption(ia_rsp);
        }
    }

    // add client-id
    boost::shared_ptr<Option> clientid = solicit->getOption(D6O_CLIENTID);
    if (clientid) {
        reply->addOption(clientid);
    }

    // add server-id
    reply->addOption(getServerID());
    return reply;
}

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processRequest(boost::shared_ptr<Pkt6> request) {
    /// TODO: Implement processRequest() for real
    boost::shared_ptr<Pkt6> reply = processSolicit(request);
    reply->setType(DHCPV6_REPLY);
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

boost::shared_ptr<Pkt6>
Dhcpv6Srv::processInfRequest(boost::shared_ptr<Pkt6> infRequest) {
    boost::shared_ptr<Pkt6> reply(new Pkt6(DHCPV6_REPLY,
                                           infRequest->getTransid(),
                                           Pkt6::UDP));
    return reply;
}
