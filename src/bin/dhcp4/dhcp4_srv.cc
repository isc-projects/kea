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

#include <dhcp/dhcp4.h>
#include <dhcp/pkt4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp4/dhcp4_srv.h>
#include <asiolink/io_address.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

// #define ECHO_SERVER

Dhcpv4Srv::Dhcpv4Srv(uint16_t port) {
    cout << "Initialization: opening sockets on port " << port << endl;

    // first call to instance() will create IfaceMgr (it's a singleton)
    // it may throw something if things go wrong
    IfaceMgr::instance();

    /// @todo: instantiate LeaseMgr here once it is imlpemented.
    IfaceMgr::instance().printIfaces();

    IfaceMgr::instance().openSockets4(port);

    setServerID();

    shutdown = false;
}

Dhcpv4Srv::~Dhcpv4Srv() {
    cout << "DHCPv4 server shutdown." << endl;
    IfaceMgr::instance().closeSockets();
}

bool
Dhcpv4Srv::run() {
    while (!shutdown) {
        boost::shared_ptr<Pkt4> query; // client's message
        boost::shared_ptr<Pkt4> rsp;   // server's response

        query = IfaceMgr::instance().receive4();

#if defined(ECHO_SERVER)
        query->repack();
        IfaceMgr::instance().send(query);
        continue;
#endif

        if (query) {
            try {
                query->unpack();
            } catch (const std::exception& e) {
                /// TODO: Printout reasons of failed parsing
                cout << "Failed to parse incoming packet " << endl;
                continue;
            }

            switch (query->getType()) {
            case DHCPDISCOVER:
                rsp = processDiscover(query);
                break;
            case DHCPREQUEST:
                rsp = processRequest(query);
                break;
            case DHCPRELEASE:
                processRelease(query);
                break;
            case DHCPDECLINE:
                processDecline(query);
                break;
            case DHCPINFORM:
                processInform(query);
                break;
            default:
                cout << "Unknown pkt type received:"
                     << query->getType() << endl;
            }

            cout << "Received message type " << int(query->getType()) << endl;

            // TODO: print out received packets only if verbose (or debug)
            // mode is enabled
            cout << query->toText();

            if (rsp) {
                rsp->setRemoteAddr(query->getRemoteAddr());
                rsp->setLocalAddr(query->getLocalAddr());
                rsp->setRemotePort(DHCP4_CLIENT_PORT);
                rsp->setLocalPort(DHCP4_SERVER_PORT);
                rsp->setIface(query->getIface());
                rsp->setIndex(query->getIndex());

                cout << "Replying with message type "
                     << static_cast<int>(rsp->getType()) << ":" << endl;
                cout << rsp->toText();
                cout << "----" << endl;
                if (rsp->pack()) {
                    cout << "Packet assembled correctly." << endl;
                }
#if 1
                // uncomment this once ticket 1240 is merged.
                IfaceMgr::instance().send(rsp);
#endif
            }
        }

        // TODO add support for config session (see src/bin/auth/main.cc)
        //      so this daemon can be controlled from bob
    }

    return (true);
}

void
Dhcpv4Srv::setServerID() {
    /// TODO implement this for real once interface detection (ticket 1237)
    /// is done. Use hardcoded server-id for now.

#if 0
    // uncomment this once ticket 1350 is merged.
    IOAddress srvId("127.0.0.1");
    serverid_ = boost::shared_ptr<Option>(
      new Option4AddrLst(Option::V4, DHO_DHCP_SERVER_IDENTIFIER, srvId));
#endif
}

boost::shared_ptr<Pkt4>
Dhcpv4Srv::processDiscover(boost::shared_ptr<Pkt4> discover) {
    /// TODO: Currently implemented echo mode. Implement this for real
    return (discover);
}

boost::shared_ptr<Pkt4>
Dhcpv4Srv::processRequest(boost::shared_ptr<Pkt4> request) {
    /// TODO: Currently implemented echo mode. Implement this for real
    return (request);
}

void Dhcpv4Srv::processRelease(boost::shared_ptr<Pkt4> release) {
    /// TODO: Implement this.
    cout << "Received RELEASE on " << release->getIface() << " interface." << endl;
}

void Dhcpv4Srv::processDecline(boost::shared_ptr<Pkt4> decline) {
    /// TODO: Implement this.
    cout << "Received DECLINE on " << decline->getIface() << " interface." << endl;
}

boost::shared_ptr<Pkt4> Dhcpv4Srv::processInform(boost::shared_ptr<Pkt4> inform) {
    /// TODO: Currently implemented echo mode. Implement this for real
    return (inform);
}
