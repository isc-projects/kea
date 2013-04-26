// Copyright (C) 2011-2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option_int_array.h>
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

#include <boost/algorithm/string/erase.hpp>

#include <iomanip>
#include <fstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::log;
using namespace std;

namespace isc {
namespace dhcp {

/// @brief file name of a server-id file
///
/// Server must store its server identifier in persistent storage that must not
/// change between restarts. This is name of the file that is created in dataDir
/// (see isc::dhcp::CfgMgr::getDataDir()). It is a text file that uses
/// regular IPv4 address, e.g. 192.0.2.1. Server will create it during
/// first run and then use it afterwards.
static const char* SERVER_ID_FILE = "b10-dhcp4-serverid";

// These are hardcoded parameters. Currently this is a skeleton server that only
// grants those options and a single, fixed, hardcoded lease.

Dhcpv4Srv::Dhcpv4Srv(uint16_t port, const char* dbconfig, const bool use_bcast) {
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_OPEN_SOCKET).arg(port);
    try {
        // First call to instance() will create IfaceMgr (it's a singleton)
        // it may throw something if things go wrong
        IfaceMgr::instance();

        if (port) {
            // open sockets only if port is non-zero. Port 0 is used
            // for non-socket related testing.
            IfaceMgr::instance().openSockets4(port, use_bcast);
        }

        string srvid_file = CfgMgr::instance().getDataDir() + "/" + string(SERVER_ID_FILE);
        if (loadServerID(srvid_file)) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_SERVERID_LOADED)
                .arg(srvidToString(getServerID()))
                .arg(srvid_file);
        } else {
            generateServerID();
            LOG_INFO(dhcp4_logger, DHCP4_SERVERID_GENERATED)
                .arg(srvidToString(getServerID()))
                .arg(srvid_file);

            if (!writeServerID(srvid_file)) {
                LOG_WARN(dhcp4_logger, DHCP4_SERVERID_WRITE_FAIL)
                    .arg(srvid_file);
            }

        }

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

void
Dhcpv4Srv::shutdown() {
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

            try {
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
                    // and that is covered by the debug statement before the
                    // "switch" statement.
                    ;
                }
            } catch (const isc::Exception& e) {

                // Catch-all exception (at least for ones based on the isc
                // Exception class, which covers more or less all that
                // are explicitly raised in the BIND 10 code).  Just log
                // the problem and ignore the packet. (The problem is logged
                // as a debug message because debug is disabled by default -
                // it prevents a DDOS attack based on the sending of problem
                // packets.)
                if (dhcp4_logger.isDebugEnabled(DBG_DHCP4_BASIC)) {
                    std::string source = "unknown";
                    HWAddrPtr hwptr = query->getHWAddr();
                    if (hwptr) {
                        source = hwptr->toText();
                    }
                    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC,
                              DHCP4_PACKET_PROCESS_FAIL)
                              .arg(source).arg(e.what());
                }
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
    }

    return (true);
}

bool
Dhcpv4Srv::loadServerID(const std::string& file_name) {

    // load content of the file into a string
    fstream f(file_name.c_str(), ios::in);
    if (!f.is_open()) {
        return (false);
    }

    string hex_string;
    f >> hex_string;
    f.close();

    // remove any spaces
    boost::algorithm::erase_all(hex_string, " ");

    try {
        IOAddress addr(hex_string);

        if (!addr.isV4()) {
            return (false);
        }

        // Now create server-id option
        serverid_.reset(new Option4AddrLst(DHO_DHCP_SERVER_IDENTIFIER, addr));

    } catch(...) {
        // any kind of malformed input (empty string, IPv6 address, complete
        // garbate etc.)
        return (false);
    }

    return (true);
}

void
Dhcpv4Srv::generateServerID() {

    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();

    // Let's find suitable interface.
    for (IfaceMgr::IfaceCollection::const_iterator iface = ifaces.begin();
         iface != ifaces.end(); ++iface) {

        // Let's don't use loopback.
        if (iface->flag_loopback_) {
            continue;
        }

        // Let's skip downed interfaces. It is better to use working ones.
        if (!iface->flag_up_) {
            continue;
        }

        const Iface::AddressCollection addrs = iface->getAddresses();

        for (Iface::AddressCollection::const_iterator addr = addrs.begin();
             addr != addrs.end(); ++addr) {
            if (addr->getFamily() != AF_INET) {
                continue;
            }

            serverid_ = OptionPtr(new Option4AddrLst(DHO_DHCP_SERVER_IDENTIFIER,
                                                     *addr));
            return;
        }


    }

    isc_throw(BadValue, "No suitable interfaces for server-identifier found");
}

bool
Dhcpv4Srv::writeServerID(const std::string& file_name) {
    fstream f(file_name.c_str(), ios::out | ios::trunc);
    if (!f.good()) {
        return (false);
    }
    f << srvidToString(getServerID());
    f.close();
    return (true);
}

string
Dhcpv4Srv::srvidToString(const OptionPtr& srvid) {
    if (!srvid) {
        isc_throw(BadValue, "NULL pointer passed to srvidToString()");
    }
    boost::shared_ptr<Option4AddrLst> generated =
        boost::dynamic_pointer_cast<Option4AddrLst>(srvid);
    if (!srvid) {
        isc_throw(BadValue, "Pointer to invalid option passed to srvidToString()");
    }

    Option4AddrLst::AddressContainer addrs = generated->getAddresses();
    if (addrs.size() != 1) {
        isc_throw(BadValue, "Malformed option passed to srvidToString(). "
                  << "Expected to contain a single IPv4 address.");
    }

    return (addrs[0].toText());
}

void
Dhcpv4Srv::copyDefaultFields(const Pkt4Ptr& question, Pkt4Ptr& answer) {
    answer->setIface(question->getIface());
    answer->setIndex(question->getIndex());
    answer->setCiaddr(question->getCiaddr());

    answer->setSiaddr(IOAddress("0.0.0.0")); // explicitly set this to 0
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

    // Let's copy client-id to response. See RFC6842.
    OptionPtr client_id = question->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (client_id) {
        answer->addOption(client_id);
    }
}

void
Dhcpv4Srv::appendDefaultOptions(Pkt4Ptr& msg, uint8_t msg_type) {
    OptionPtr opt;

    // add Message Type Option (type 53)
    msg->setType(msg_type);

    // DHCP Server Identifier (type 54)
    msg->addOption(getServerID());

    // more options will be added here later
}

void
Dhcpv4Srv::appendRequestedOptions(const Pkt4Ptr& question, Pkt4Ptr& msg) {

    // Get the subnet relevant for the client. We will need it
    // to get the options associated with it.
    Subnet4Ptr subnet = selectSubnet(question);
    // If we can't find the subnet for the client there is no way
    // to get the options to be sent to a client. We don't log an
    // error because it will be logged by the assignLease method
    // anyway.
    if (!subnet) {
        return;
    }

    // try to get the 'Parameter Request List' option which holds the
    // codes of requested options.
    OptionUint8ArrayPtr option_prl = boost::dynamic_pointer_cast<
        OptionUint8Array>(question->getOption(DHO_DHCP_PARAMETER_REQUEST_LIST));
    // If there is no PRL option in the message from the client then
    // there is nothing to do.
    if (!option_prl) {
        return;
    }

    // Get the codes of requested options.
    const std::vector<uint8_t>& requested_opts = option_prl->getValues();
    // For each requested option code get the instance of the option
    // to be returned to the client.
    for (std::vector<uint8_t>::const_iterator opt = requested_opts.begin();
         opt != requested_opts.end(); ++opt) {
        Subnet::OptionDescriptor desc =
            subnet->getOptionDescriptor("dhcp4", *opt);
        if (desc.option) {
            msg->addOption(desc.option);
        }
    }
}

void
Dhcpv4Srv::appendBasicOptions(const Pkt4Ptr& question, Pkt4Ptr& msg) {
    // Identify options that we always want to send to the
    // client (if they are configured).
    static const uint16_t required_options[] = {
        DHO_SUBNET_MASK,
        DHO_ROUTERS,
        DHO_DOMAIN_NAME_SERVERS,
        DHO_DOMAIN_NAME };

    static size_t required_options_size =
        sizeof(required_options) / sizeof(required_options[0]);

    // Get the subnet.
    Subnet4Ptr subnet = selectSubnet(question);
    if (!subnet) {
        return;
    }

    // Try to find all 'required' options in the outgoing
    // message. Those that are not present will be added.
    for (int i = 0; i < required_options_size; ++i) {
        OptionPtr opt = msg->getOption(required_options[i]);
        if (!opt) {
            // Check whether option has been configured.
            Subnet::OptionDescriptor desc =
                subnet->getOptionDescriptor("dhcp4", required_options[i]);
            if (desc.option) {
                msg->addOption(desc.option);
            }
        }
    }
}

void
Dhcpv4Srv::assignLease(const Pkt4Ptr& question, Pkt4Ptr& answer) {

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
        answer->setType(DHCPNAK);
        answer->setYiaddr(IOAddress("0.0.0.0"));
        return;
    }

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_SUBNET_SELECTED)
        .arg(subnet->toText());

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
    bool fake_allocation = (question->getType() == DHCPDISCOVER);

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honour the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    Lease4Ptr lease = alloc_engine_->allocateAddress4(subnet, client_id, hwaddr,
                                                      hint, fake_allocation);

    if (lease) {
        // We have a lease! Let's set it in the packet and send it back to
        // the client.
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, fake_allocation?
                  DHCP4_LEASE_ADVERT:DHCP4_LEASE_ALLOC)
            .arg(lease->addr_.toText())
            .arg(client_id?client_id->toText():"(no client-id)")
            .arg(hwaddr?hwaddr->toText():"(no hwaddr info)");

        answer->setYiaddr(lease->addr_);

        // If remote address is not set, we are dealing with a directly
        // connected client requesting new lease. We can send response to
        // the address assigned in the lease, but first we have to make sure
        // that IfaceMgr supports responding directly to the client when
        // client doesn't have address assigned to its interface yet.
        if (answer->getRemoteAddr().toText() == "0.0.0.0") {
            if (IfaceMgr::instance().isDirectResponseSupported()) {
                answer->setRemoteAddr(lease->addr_);
            } else {
                // Since IfaceMgr does not support direct responses to
                // clients not having IP addresses, we have to send response
                // to broadcast. We don't check whether the use_bcast flag
                // was set in the constructor, because this flag is only used
                // by unit tests to prevent opening broadcast sockets, as
                // it requires root privileges. If this function is invoked by
                // unit tests, we expect that it sets broadcast address if
                // direct response is not supported, so as a test can verify
                // function's behavior, regardless of the use_bcast flag's value.
                answer->setRemoteAddr(IOAddress("255.255.255.255"));
            }
        }

        // IP Address Lease time (type 51)
        opt = OptionPtr(new Option(Option::V4, DHO_DHCP_LEASE_TIME));
        opt->setUint32(lease->valid_lft_);
        answer->addOption(opt);

        // Router (type 3)
        Subnet::OptionDescriptor opt_routers =
            subnet->getOptionDescriptor("dhcp4", DHO_ROUTERS);
        if (opt_routers.option) {
            answer->addOption(opt_routers.option);
        }

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

        answer->setType(DHCPNAK);
        answer->setYiaddr(IOAddress("0.0.0.0"));
    }
}

OptionPtr
Dhcpv4Srv::getNetmaskOption(const Subnet4Ptr& subnet) {
    uint32_t netmask = getNetmask4(subnet->get().second);

    OptionPtr opt(new OptionInt<uint32_t>(Option::V4,
                  DHO_SUBNET_MASK, netmask));

    return (opt);
}

Pkt4Ptr
Dhcpv4Srv::processDiscover(Pkt4Ptr& discover) {
    Pkt4Ptr offer = Pkt4Ptr
        (new Pkt4(DHCPOFFER, discover->getTransid()));

    copyDefaultFields(discover, offer);
    appendDefaultOptions(offer, DHCPOFFER);
    appendRequestedOptions(discover, offer);

    assignLease(discover, offer);

    // There are a few basic options that we always want to
    // include in the response. If client did not request
    // them we append them for him.
    appendBasicOptions(discover, offer);

    return (offer);
}

Pkt4Ptr
Dhcpv4Srv::processRequest(Pkt4Ptr& request) {
    Pkt4Ptr ack = Pkt4Ptr
        (new Pkt4(DHCPACK, request->getTransid()));

    copyDefaultFields(request, ack);
    appendDefaultOptions(ack, DHCPACK);
    appendRequestedOptions(request, ack);

    assignLease(request, ack);

    // There are a few basic options that we always want to
    // include in the response. If client did not request
    // them we append them for him.
    appendBasicOptions(request, ack);

    return (ack);
}

void
Dhcpv4Srv::processRelease(Pkt4Ptr& release) {

    // Try to find client-id
    ClientIdPtr client_id;
    OptionPtr opt = release->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (opt) {
        client_id = ClientIdPtr(new ClientId(opt->getData()));
    }

    try {
        // Do we have a lease for that particular address?
        Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(release->getYiaddr());

        if (!lease) {
            // No such lease - bogus release
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_NO_LEASE)
                .arg(release->getYiaddr().toText())
                .arg(release->getHWAddr()->toText())
                .arg(client_id ? client_id->toText() : "(no client-id)");
            return;
        }

        // Does the hardware address match? We don't want one client releasing
        // second client's leases.
        if (lease->hwaddr_ != release->getHWAddr()->hwaddr_) {
            // @todo: Print hwaddr from lease as part of ticket #2589
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_WRONG_HWADDR)
                .arg(release->getYiaddr().toText())
                .arg(client_id ? client_id->toText() : "(no client-id)")
                .arg(release->getHWAddr()->toText());
            return;
        }

        // Does the lease have client-id info? If it has, then check it with what
        // the client sent us.
        if (lease->client_id_ && client_id && *lease->client_id_ != *client_id) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_WRONG_CLIENT_ID)
                .arg(release->getYiaddr().toText())
                .arg(client_id->toText())
                .arg(lease->client_id_->toText());
            return;
        }

        // Ok, hw and client-id match - let's release the lease.
        if (LeaseMgrFactory::instance().deleteLease(lease->addr_)) {

            // Release successful - we're done here
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE)
                .arg(lease->addr_.toText())
                .arg(client_id ? client_id->toText() : "(no client-id)")
                .arg(release->getHWAddr()->toText());
        } else {

            // Release failed -
            LOG_ERROR(dhcp4_logger, DHCP4_RELEASE_FAIL)
                .arg(lease->addr_.toText())
                .arg(client_id ? client_id->toText() : "(no client-id)")
                .arg(release->getHWAddr()->toText());
        }
    } catch (const isc::Exception& ex) {
        // Rethrow the exception with a bit more data.
        LOG_ERROR(dhcp4_logger, DHCP4_RELEASE_EXCEPTION)
            .arg(ex.what())
            .arg(release->getYiaddr());
    }

}

void
Dhcpv4Srv::processDecline(Pkt4Ptr& /* decline */) {
    /// TODO: Implement this.
}

Pkt4Ptr
Dhcpv4Srv::processInform(Pkt4Ptr& inform) {
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

Subnet4Ptr
Dhcpv4Srv::selectSubnet(const Pkt4Ptr& question) {

    // Is this relayed message?
    IOAddress relay = question->getGiaddr();
    if (relay.toText() == "0.0.0.0") {

        // Yes: Use relay address to select subnet
        return (CfgMgr::instance().getSubnet4(relay));
    } else {

        // No: Use client's address to select subnet
        return (CfgMgr::instance().getSubnet4(question->getRemoteAddr()));
    }
}

void
Dhcpv4Srv::sanityCheck(const Pkt4Ptr& pkt, RequirementLevel serverid) {
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

}   // namespace dhcp
}   // namespace isc
