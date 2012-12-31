// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/pkt4.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcpsrv/utils.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/utils.h>
#include <dhcpsrv/addr_utilities.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::log;
using namespace std;

// These are hardcoded parameters. Currently this is a skeleton server that only
// grants those options and a single, fixed, hardcoded lease.
const std::string HARDCODED_GATEWAY = "192.0.2.1";
const std::string HARDCODED_DNS_SERVER = "192.0.2.2";
const std::string HARDCODED_DOMAIN_NAME = "isc.example.com";
const std::string HARDCODED_SERVER_ID = "192.0.2.1";

Dhcpv4Srv::Dhcpv4Srv(uint16_t port, const char* dbconfig) {
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_OPEN_SOCKET).arg(port);
    try {
        // First call to instance() will create IfaceMgr (it's a singleton)
        // it may throw something if things go wrong
        IfaceMgr::instance();

        if (port) {
            // open sockets only if port is non-zero. Port 0 is used
            // for non-socket related testing.
            IfaceMgr::instance().openSockets4(port);
        }

        setServerID();

        // Instantiate LeaseMgr
        LeaseMgrFactory::create(dbconfig);
        LOG_INFO(dhcp4_logger, DHCP4_DB_BACKEND_STARTED)
            .arg(LeaseMgrFactory::instance().getType())
            .arg(LeaseMgrFactory::instance().getName());

        // Instantiate allocation engine
        alloc_engine_.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));

    } catch (const std::exception &e) {
        LOG_ERROR(dhcp4_logger, DHCP4_SRV_CONSTRUCT_ERROR).arg(e.what());
        shutdown_ = true;
        return;
    }

    shutdown_ = false;
}

Dhcpv4Srv::~Dhcpv4Srv() {
    IfaceMgr::instance().closeSockets();
}

void Dhcpv4Srv::shutdown() {
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_SHUTDOWN_REQUEST);
    shutdown_ = true;
}

bool
Dhcpv4Srv::run() {
    while (!shutdown_) {
        /// @todo: calculate actual timeout once we have lease database
        int timeout = 1000;

        // client's message and server's response
        Pkt4Ptr query;
        Pkt4Ptr rsp;

        try {
            query = IfaceMgr::instance().receive4(timeout);
        } catch (const std::exception& e) {
            LOG_ERROR(dhcp4_logger, DHCP4_PACKET_RECEIVE_FAIL).arg(e.what());
        }

        if (query) {
            try {
                query->unpack();

            } catch (const std::exception& e) {
                // Failed to parse the packet.
                LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL,
                          DHCP4_PACKET_PARSE_FAIL).arg(e.what());
                continue;
            }
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_RECEIVED)
                      .arg(serverReceivedPacketName(query->getType()))
                      .arg(query->getType())
                      .arg(query->getIface());
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_QUERY_DATA)
                      .arg(query->toText());

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
                // Only action is to output a message if debug is enabled,
                // and that will be covered by the debug statement before
                // the "switch" statement.
                ;
            }

            if (rsp) {
                if (rsp->getRemoteAddr().toText() == "0.0.0.0") {
                    rsp->setRemoteAddr(query->getRemoteAddr());
                }
                if (!rsp->getHops()) {
                    rsp->setRemotePort(DHCP4_CLIENT_PORT);
                } else {
                    rsp->setRemotePort(DHCP4_SERVER_PORT);
                }

                rsp->setLocalAddr(query->getLocalAddr());
                rsp->setLocalPort(DHCP4_SERVER_PORT);
                rsp->setIface(query->getIface());
                rsp->setIndex(query->getIndex());

                LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL_DATA,
                          DHCP4_RESPONSE_DATA)
                          .arg(rsp->getType()).arg(rsp->toText());

                if (rsp->pack()) {
                    try {
                        IfaceMgr::instance().send(rsp);
                    } catch (const std::exception& e) {
                        LOG_ERROR(dhcp4_logger, DHCP4_PACKET_SEND_FAIL).arg(e.what());
                    }
                } else {
                    LOG_ERROR(dhcp4_logger, DHCP4_PACK_FAIL);
                }
            }
        }

        // TODO add support for config session (see src/bin/auth/main.cc)
        //      so this daemon can be controlled from bob
    }

    return (true);
}

void
Dhcpv4Srv::setServerID() {
    /// @todo: implement this for real (see ticket #2588)
    serverid_ = OptionPtr(new Option4AddrLst(DHO_DHCP_SERVER_IDENTIFIER,
                                             IOAddress(HARDCODED_SERVER_ID)));
}

void Dhcpv4Srv::copyDefaultFields(const Pkt4Ptr& question, Pkt4Ptr& answer) {
    answer->setIface(question->getIface());
    answer->setIndex(question->getIndex());
    answer->setCiaddr(question->getCiaddr());

    answer->setSiaddr(IOAddress("0.0.0.0")); // explictly set this to 0
    answer->setHops(question->getHops());

    // copy MAC address
    answer->setHWAddr(question->getHWAddr());

    // relay address
    answer->setGiaddr(question->getGiaddr());

    if (question->getGiaddr().toText() != "0.0.0.0") {
        // relayed traffic
        answer->setRemoteAddr(question->getGiaddr());
    } else {
        // direct traffic
        answer->setRemoteAddr(question->getRemoteAddr());
    }

    OptionPtr client_id = question->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (client_id) {
        answer->addOption(client_id);
    }
}

void Dhcpv4Srv::appendDefaultOptions(Pkt4Ptr& msg, uint8_t msg_type) {
    OptionPtr opt;

    // add Message Type Option (type 53)
    std::vector<uint8_t> tmp;
    tmp.push_back(static_cast<uint8_t>(msg_type));
    opt = OptionPtr(new Option(Option::V4, DHO_DHCP_MESSAGE_TYPE, tmp));
    msg->addOption(opt);

    // DHCP Server Identifier (type 54)
    msg->addOption(getServerID());

    // more options will be added here later
}


void Dhcpv4Srv::appendRequestedOptions(Pkt4Ptr& msg) {
    OptionPtr opt;

    // Domain name (type 15)
    vector<uint8_t> domain(HARDCODED_DOMAIN_NAME.begin(), HARDCODED_DOMAIN_NAME.end());
    opt = OptionPtr(new Option(Option::V4, DHO_DOMAIN_NAME, domain));
    msg->addOption(opt);
    // TODO: Add Option_String class

    // DNS servers (type 6)
    opt = OptionPtr(new Option4AddrLst(DHO_DOMAIN_NAME_SERVERS, IOAddress(HARDCODED_DNS_SERVER)));
    msg->addOption(opt);
}

void Dhcpv4Srv::assignLease(const Pkt4Ptr& question, Pkt4Ptr& answer) {

    // We need to select a subnet the client is connected in.
    Subnet4Ptr subnet = selectSubnet(question);
    if (!subnet) {
        // This particular client is out of luck today. We do not have
        // information about the subnet he is connected to. This likely means
        // misconfiguration of the server (or some relays). We will continue to
        // process this message, but our response will be almost useless: no
        // addresses or prefixes, no subnet specific configuration etc. The only
        // thing this client can get is some global information (like DNS
        // servers).

        // perhaps this should be logged on some higher level? This is most likely
        // configuration bug.
        LOG_ERROR(dhcp4_logger, DHCP4_SUBNET_SELECTION_FAILED)
            .arg(question->getRemoteAddr().toText())
            .arg(serverReceivedPacketName(question->getType()));
        setMsgType(answer, DHCPNAK);
        answer->setYiaddr(IOAddress("0.0.0.0"));
        return;
    } else {
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_SUBNET_SELECTED)
            .arg(subnet->toText());
    }

    // Get client-id option
    ClientIdPtr client_id;
    OptionPtr opt = question->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (opt) {
        client_id = ClientIdPtr(new ClientId(opt->getData()));
    }
    // client-id is not mandatory in DHCPv4

    IOAddress hint = question->getYiaddr();

    HWAddrPtr hwaddr = question->getHWAddr();

    // "Fake" allocation is processing of DISCOVER message. We pretend to do an
    // allocation, but we do not put the lease in the database. That is ok,
    // because we do not guarantee that the user will get that exact lease. If
    // the user selects this server to do actual allocation (i.e. sends REQUEST)
    // it should include this hint. That will help us during the actual lease
    // allocation.
    bool fake_allocation = false;
    if (question->getType() == DHCPDISCOVER) {
        fake_allocation = true;
    }

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honour the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    Lease4Ptr lease = alloc_engine_->allocateAddress4(subnet, client_id, hwaddr,
                                                      hint, fake_allocation);

    if (lease) {
        // We have a lease! Let's wrap its content into IA_NA option
        // with IAADDR suboption.
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, fake_allocation?
                  DHCP4_LEASE_ADVERT:DHCP4_LEASE_ALLOC)
            .arg(client_id?client_id->toText():"(no client-id)")
            .arg(hwaddr?hwaddr->toText():"(no hwaddr info)")
            .arg(hint.toText());

        answer->setYiaddr(lease->addr_);

        // IP Address Lease time (type 51)
        opt = OptionPtr(new Option(Option::V4, DHO_DHCP_LEASE_TIME));
        opt->setUint32(lease->valid_lft_);
        answer->addOption(opt);

        // @todo: include real router information here
        // Router (type 3)
        opt = OptionPtr(new Option4AddrLst(DHO_ROUTERS, IOAddress(HARDCODED_GATEWAY)));
        answer->addOption(opt);

        // Subnet mask (type 1)
        answer->addOption(getNetmaskOption(subnet));

        // @todo: send renew timer option (T1, option 58)
        // @todo: send rebind timer option (T2, option 59)

    } else {
        // Allocation engine did not allocate a lease. The engine logged
        // cause of that failure. The only thing left is to insert
        // status code to pass the sad news to the client.

        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, fake_allocation?
                  DHCP4_LEASE_ADVERT_FAIL:DHCP4_LEASE_ALLOC_FAIL)
            .arg(client_id?client_id->toText():"(no client-id)")
            .arg(hwaddr?hwaddr->toText():"(no hwaddr info)")
            .arg(hint.toText());

        setMsgType(answer, DHCPNAK);
        answer->setYiaddr(IOAddress("0.0.0.0"));
    }
}

OptionPtr Dhcpv4Srv::getNetmaskOption(const Subnet4Ptr& subnet) {
    uint32_t netmask = getNetmask4(subnet->get().second);

    OptionPtr opt(new OptionInt<uint32_t>(Option::V4,
                  DHO_SUBNET_MASK, netmask));

    return (opt);
}

void Dhcpv4Srv::setMsgType(Pkt4Ptr& pkt, uint8_t dhcp_type) {
    OptionPtr opt = pkt->getOption(DHO_DHCP_MESSAGE_TYPE);
    if (opt) {
        // There is message type option already, update it
        opt->setUint8(dhcp_type);
    } else {
        // There is no message type option yet, add it
        std::vector<uint8_t> tmp(1, dhcp_type);
        opt = OptionPtr(new Option(Option::V4, DHO_DHCP_MESSAGE_TYPE, tmp));
        pkt->addOption(opt);
    }
}

Pkt4Ptr Dhcpv4Srv::processDiscover(Pkt4Ptr& discover) {
    Pkt4Ptr offer = Pkt4Ptr
        (new Pkt4(DHCPOFFER, discover->getTransid()));

    copyDefaultFields(discover, offer);
    appendDefaultOptions(offer, DHCPOFFER);
    appendRequestedOptions(offer);

    assignLease(discover, offer);

    return (offer);
}

Pkt4Ptr Dhcpv4Srv::processRequest(Pkt4Ptr& request) {
    Pkt4Ptr ack = Pkt4Ptr
        (new Pkt4(DHCPACK, request->getTransid()));

    copyDefaultFields(request, ack);
    appendDefaultOptions(ack, DHCPACK);
    appendRequestedOptions(ack);

    assignLease(request, ack);

    return (ack);
}

void Dhcpv4Srv::processRelease(Pkt4Ptr& release) {
    ClientIdPtr client_id;
    OptionPtr opt = release->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (opt) {
        client_id = ClientIdPtr(new ClientId(opt->getData()));
    }

    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(release->getYiaddr());

    if (!lease) {
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_NO_LEASE)
            .arg(release->getYiaddr().toText())
            .arg(release->getHWAddr()->toText())
            .arg(client_id ? client_id->toText() : "(no client-id)");
        return;
    }

    if (lease->hwaddr_ != release->getHWAddr()->hwaddr_) {
        // @todo: Print hwaddr from lease as part of ticket #2589
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_WRONG_HWADDR)
            .arg(release->getYiaddr().toText())
            .arg(client_id ? client_id->toText() : "(no client-id)")
            .arg(release->getHWAddr()->toText());
        return;
    }

    if (lease->client_id_ && client_id && *lease->client_id_ != *client_id) {
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_WRONG_CLIENT_ID)
            .arg(release->getYiaddr().toText())
            .arg(client_id->toText())
            .arg(lease->client_id_->toText());
        return;
    }

    if (LeaseMgrFactory::instance().deleteLease(lease->addr_)) {
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE)
            .arg(lease->addr_.toText())
            .arg(client_id ? client_id->toText() : "(no client-id)")
            .arg(release->getHWAddr()->toText());
    } else {
        LOG_ERROR(dhcp4_logger, DHCP4_RELEASE_FAIL)
            .arg(lease->addr_.toText())
            .arg(client_id ? client_id->toText() : "(no client-id)")
            .arg(release->getHWAddr()->toText());
    }
}

void Dhcpv4Srv::processDecline(Pkt4Ptr& decline) {
    /// TODO: Implement this.
}

Pkt4Ptr Dhcpv4Srv::processInform(Pkt4Ptr& inform) {
    /// TODO: Currently implemented echo mode. Implement this for real
    return (inform);
}

const char*
Dhcpv4Srv::serverReceivedPacketName(uint8_t type) {
    static const char* DISCOVER = "DISCOVER";
    static const char* REQUEST = "REQUEST";
    static const char* RELEASE = "RELEASE";
    static const char* DECLINE = "DECLINE";
    static const char* INFORM = "INFORM";
    static const char* UNKNOWN = "UNKNOWN";

    switch (type) {
    case DHCPDISCOVER:
        return (DISCOVER);

    case DHCPREQUEST:
        return (REQUEST);

    case DHCPRELEASE:
        return (RELEASE);

    case DHCPDECLINE:
        return (DECLINE);

    case DHCPINFORM:
        return (INFORM);

    default:
        ;
    }
    return (UNKNOWN);
}

Subnet4Ptr Dhcpv4Srv::selectSubnet(const Pkt4Ptr& question) {
    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(question->getRemoteAddr());

    return (subnet);
}

void Dhcpv4Srv::sanityCheck(const Pkt4Ptr& pkt, RequirementLevel serverid) {
    OptionPtr server_id = pkt->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    switch (serverid) {
    case FORBIDDEN:
        if (server_id) {
            isc_throw(RFCViolation, "Server-id option was not expected, but "
                      << "received in " << serverReceivedPacketName(pkt->getType()));
        }
        break;

    case MANDATORY:
        if (!server_id) {
            isc_throw(RFCViolation, "Server-id option was expected, but not "
                      " received in message "
                      << serverReceivedPacketName(pkt->getType()));
        }
        break;

    case OPTIONAL:
        // do nothing here
        ;
    }
}
