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
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_vendor.h>
#include <dhcp/pkt4.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcpsrv/addr_utilities.h>
#include <dhcpsrv/callout_handle_store.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/utils.h>
#include <dhcpsrv/utils.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>

#include <boost/algorithm/string/erase.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <iomanip>
#include <fstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;
using namespace std;

/// Structure that holds registered hook indexes
struct Dhcp4Hooks {
    int hook_index_buffer4_receive_;///< index for "buffer4_receive" hook point
    int hook_index_pkt4_receive_;   ///< index for "pkt4_receive" hook point
    int hook_index_subnet4_select_; ///< index for "subnet4_select" hook point
    int hook_index_lease4_release_; ///< index for "lease4_release" hook point
    int hook_index_pkt4_send_;      ///< index for "pkt4_send" hook point
    int hook_index_buffer4_send_;   ///< index for "buffer4_send" hook point

    /// Constructor that registers hook points for DHCPv4 engine
    Dhcp4Hooks() {
        hook_index_buffer4_receive_= HooksManager::registerHook("buffer4_receive");
        hook_index_pkt4_receive_   = HooksManager::registerHook("pkt4_receive");
        hook_index_subnet4_select_ = HooksManager::registerHook("subnet4_select");
        hook_index_pkt4_send_      = HooksManager::registerHook("pkt4_send");
        hook_index_lease4_release_ = HooksManager::registerHook("lease4_release");
        hook_index_buffer4_send_   = HooksManager::registerHook("buffer4_send");
    }
};

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
Dhcp4Hooks Hooks;

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

Dhcpv4Srv::Dhcpv4Srv(uint16_t port, const char* dbconfig, const bool use_bcast,
                     const bool direct_response_desired)
: serverid_(), shutdown_(true), alloc_engine_(), port_(port),
    use_bcast_(use_bcast), hook_index_pkt4_receive_(-1),
    hook_index_subnet4_select_(-1), hook_index_pkt4_send_(-1) {

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_OPEN_SOCKET).arg(port);
    try {
        // First call to instance() will create IfaceMgr (it's a singleton)
        // it may throw something if things go wrong.
        // The 'true' value of the call to setMatchingPacketFilter imposes
        // that IfaceMgr will try to use the mechanism to respond directly
        // to the client which doesn't have address assigned. This capability
        // may be lacking on some OSes, so there is no guarantee that server
        // will be able to respond directly.
        IfaceMgr::instance().setMatchingPacketFilter(direct_response_desired);

        if (port) {
            // open sockets only if port is non-zero. Port 0 is used
            // for non-socket related testing.
            IfaceMgr::instance().openSockets4(port_, use_bcast_);
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
        alloc_engine_.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100,
                                            false /* false = IPv4 */));

        // Register hook points
        hook_index_pkt4_receive_   = Hooks.hook_index_pkt4_receive_;
        hook_index_subnet4_select_ = Hooks.hook_index_subnet4_select_;
        hook_index_pkt4_send_      = Hooks.hook_index_pkt4_send_;

        /// @todo call loadLibraries() when handling configuration changes

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

Pkt4Ptr
Dhcpv4Srv::receivePacket(int timeout) {
    return (IfaceMgr::instance().receive4(timeout));
}

void
Dhcpv4Srv::sendPacket(const Pkt4Ptr& packet) {
    IfaceMgr::instance().send(packet);
}

bool
Dhcpv4Srv::run() {
    while (!shutdown_) {
        /// @todo: calculate actual timeout once we have lease database
        //cppcheck-suppress variableScope This is temporary anyway
        const int timeout = 1000;

        // client's message and server's response
        Pkt4Ptr query;
        Pkt4Ptr rsp;

        try {
            query = receivePacket(timeout);
        } catch (const std::exception& e) {
            LOG_ERROR(dhcp4_logger, DHCP4_PACKET_RECEIVE_FAIL).arg(e.what());
        }

        // Timeout may be reached or signal received, which breaks select()
        // with no reception ocurred
        if (!query) {
            continue;
        }

        // In order to parse the DHCP options, the server needs to use some
        // configuration information such as: existing option spaces, option
        // definitions etc. This is the kind of information which is not
        // available in the libdhcp, so we need to supply our own implementation
        // of the option parsing function here, which would rely on the
        // configuration data.
        query->setCallback(boost::bind(&Dhcpv4Srv::unpackOptions, this,
                                       _1, _2, _3));

        bool skip_unpack = false;

        // The packet has just been received so contains the uninterpreted wire
        // data; execute callouts registered for buffer4_receive.
        if (HooksManager::calloutsPresent(Hooks.hook_index_buffer4_receive_)) {
            CalloutHandlePtr callout_handle = getCalloutHandle(query);

            // Delete previously set arguments
            callout_handle->deleteAllArguments();

            // Pass incoming packet as argument
            callout_handle->setArgument("query4", query);

            // Call callouts
            HooksManager::callCallouts(Hooks.hook_index_buffer4_receive_,
                                       *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to parse the packet, so skip at this
            // stage means that callouts did the parsing already, so server
            // should skip parsing.
            if (callout_handle->getSkip()) {
                LOG_DEBUG(dhcp4_logger, DBG_DHCP4_HOOKS, DHCP4_HOOK_BUFFER_RCVD_SKIP);
                skip_unpack = true;
            }

            callout_handle->getArgument("query4", query);
        }

        // Unpack the packet information unless the buffer4_receive callouts
        // indicated they did it
        if (!skip_unpack) {
            try {
                query->unpack();
            } catch (const std::exception& e) {
                // Failed to parse the packet.
                LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL,
                          DHCP4_PACKET_PARSE_FAIL).arg(e.what());
                continue;
            }
        }

        // When receiving a packet without message type option, getType() will
        // throw. Let's set type to -1 as default error indicator.
        int type = -1;
        try {
            type = query->getType();
        } catch (...) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_NO_TYPE)
                .arg(query->getIface());
            continue;
        }

        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_RECEIVED)
            .arg(serverReceivedPacketName(type))
            .arg(type)
            .arg(query->getIface());
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_QUERY_DATA)
            .arg(type)
            .arg(query->toText());

        // Let's execute all callouts registered for pkt4_receive
        if (HooksManager::calloutsPresent(hook_index_pkt4_receive_)) {
            CalloutHandlePtr callout_handle = getCalloutHandle(query);

            // Delete previously set arguments
            callout_handle->deleteAllArguments();

            // Pass incoming packet as argument
            callout_handle->setArgument("query4", query);

            // Call callouts
            HooksManager::callCallouts(hook_index_pkt4_receive_,
                                       *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to process the packet, so skip at this
            // stage means drop.
            if (callout_handle->getSkip()) {
                LOG_DEBUG(dhcp4_logger, DBG_DHCP4_HOOKS, DHCP4_HOOK_PACKET_RCVD_SKIP);
                continue;
            }

            callout_handle->getArgument("query4", query);
        }

        try {
            switch (query->getType()) {
            case DHCPDISCOVER:
                rsp = processDiscover(query);
                break;

            case DHCPREQUEST:
                // Note that REQUEST is used for many things in DHCPv4: for
                // requesting new leases, renewing existing ones and even
                // for rebinding.
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

        if (!rsp) {
            continue;
        }

        adjustRemoteAddr(query, rsp);

        if (!rsp->getHops()) {
            rsp->setRemotePort(DHCP4_CLIENT_PORT);
        } else {
            rsp->setRemotePort(DHCP4_SERVER_PORT);
        }

        rsp->setLocalAddr(query->getLocalAddr());
        rsp->setLocalPort(DHCP4_SERVER_PORT);
        rsp->setIface(query->getIface());
        rsp->setIndex(query->getIndex());

        // Specifies if server should do the packing
        bool skip_pack = false;

        // Execute all callouts registered for pkt4_send
        if (HooksManager::calloutsPresent(hook_index_pkt4_send_)) {
            CalloutHandlePtr callout_handle = getCalloutHandle(query);

            // Delete all previous arguments
            callout_handle->deleteAllArguments();

            // Clear skip flag if it was set in previous callouts
            callout_handle->setSkip(false);

            // Set our response
            callout_handle->setArgument("response4", rsp);

            // Call all installed callouts
            HooksManager::callCallouts(hook_index_pkt4_send_,
                                       *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to send the packet, so skip at this
            // stage means "drop response".
            if (callout_handle->getSkip()) {
                LOG_DEBUG(dhcp4_logger, DBG_DHCP4_HOOKS, DHCP4_HOOK_PACKET_SEND_SKIP);
                skip_pack = true;
            }
        }

        if (!skip_pack) {
            try {
                rsp->pack();
            } catch (const std::exception& e) {
                LOG_ERROR(dhcp4_logger, DHCP4_PACKET_SEND_FAIL)
                    .arg(e.what());
            }
        }

        try {
            // Now all fields and options are constructed into output wire buffer.
            // Option objects modification does not make sense anymore. Hooks
            // can only manipulate wire buffer at this stage.
            // Let's execute all callouts registered for buffer4_send
            if (HooksManager::calloutsPresent(Hooks.hook_index_buffer4_send_)) {
                CalloutHandlePtr callout_handle = getCalloutHandle(query);

                // Delete previously set arguments
                callout_handle->deleteAllArguments();

                // Pass incoming packet as argument
                callout_handle->setArgument("response4", rsp);

                // Call callouts
                HooksManager::callCallouts(Hooks.hook_index_buffer4_send_,
                                           *callout_handle);

                // Callouts decided to skip the next processing step. The next
                // processing step would to parse the packet, so skip at this
                // stage means drop.
                if (callout_handle->getSkip()) {
                    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_HOOKS,
                              DHCP4_HOOK_BUFFER_SEND_SKIP);
                    continue;
                }

                callout_handle->getArgument("response4", rsp);
            }

            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL_DATA,
                      DHCP4_RESPONSE_DATA)
                .arg(static_cast<int>(rsp->getType())).arg(rsp->toText());

            sendPacket(rsp);
        } catch (const std::exception& e) {
            LOG_ERROR(dhcp4_logger, DHCP4_PACKET_SEND_FAIL)
                .arg(e.what());
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

    // Let's copy client-id to response. See RFC6842.
    OptionPtr client_id = question->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (client_id) {
        answer->addOption(client_id);
    }

    // If src/dest HW addresses are used by the packet filtering class
    // we need to copy them as well. There is a need to check that the
    // address being set is not-NULL because an attempt to set the NULL
    // HW would result in exception. If these values are not set, the
    // the default HW addresses (zeroed) should be generated by the
    // packet filtering class when creating Ethernet header for
    // outgoing packet.
    HWAddrPtr src_hw_addr = question->getLocalHWAddr();
    if (src_hw_addr) {
        answer->setLocalHWAddr(src_hw_addr);
    }
    HWAddrPtr dst_hw_addr = question->getRemoteHWAddr();
    if (dst_hw_addr) {
        answer->setRemoteHWAddr(dst_hw_addr);
    }

    // If this packet is relayed, we want to copy Relay Agent Info option
    OptionPtr rai = question->getOption(DHO_DHCP_AGENT_OPTIONS);
    if (rai) {
        answer->addOption(rai);
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
Dhcpv4Srv::appendRequestedVendorOptions(const Pkt4Ptr& question, Pkt4Ptr& answer) {
    // Get the configured subnet suitable for the incoming packet.
    Subnet4Ptr subnet = selectSubnet(question);
    // Leave if there is no subnet matching the incoming packet.
    // There is no need to log the error message here because
    // it will be logged in the assignLease() when it fails to
    // pick the suitable subnet. We don't want to duplicate
    // error messages in such case.
    if (!subnet) {
        return;
    }

    // Try to get the vendor option
    boost::shared_ptr<OptionVendor> vendor_req =
        boost::dynamic_pointer_cast<OptionVendor>(question->getOption(DHO_VIVSO_SUBOPTIONS));
    if (!vendor_req) {
        return;
    }

    uint32_t vendor_id = vendor_req->getVendorId();

    // Let's try to get ORO within that vendor-option
    /// @todo This is very specific to vendor-id=4491 (Cable Labs). Other vendors
    /// may have different policies.
    OptionPtr oro = vendor_req->getOption(DOCSIS3_V4_ORO);

    /// @todo: see OPT_UINT8_TYPE definition in OptionDefinition::optionFactory().
    /// I think it should be OptionUint8Array, not OptionGeneric

    // Option ORO not found. Don't do anything then.
    if (!oro) {
        return;
    }

    boost::shared_ptr<OptionVendor> vendor_rsp(new OptionVendor(Option::V4, vendor_id));

    // Get the list of options that client requested.
    bool added = false;
    const OptionBuffer& requested_opts = oro->getData();

    for (OptionBuffer::const_iterator code = requested_opts.begin();
         code != requested_opts.end(); ++code) {
        Subnet::OptionDescriptor desc = subnet->getVendorOptionDescriptor(vendor_id, *code);
        if (desc.option) {
            vendor_rsp->addOption(desc.option);
            added = true;
        }
    }

    if (added) {
        answer->addOption(vendor_rsp);
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

    CalloutHandlePtr callout_handle = getCalloutHandle(question);

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honour the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    // @todo pass the actual FQDN data.
    Lease4Ptr old_lease;
    Lease4Ptr lease = alloc_engine_->allocateLease4(subnet, client_id, hwaddr,
                                                    hint, false, false, "",
                                                    fake_allocation,
                                                    callout_handle,
                                                    old_lease);

    if (lease) {
        // We have a lease! Let's set it in the packet and send it back to
        // the client.
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, fake_allocation?
                  DHCP4_LEASE_ADVERT:DHCP4_LEASE_ALLOC)
            .arg(lease->addr_.toText())
            .arg(client_id?client_id->toText():"(no client-id)")
            .arg(hwaddr?hwaddr->toText():"(no hwaddr info)");

        answer->setYiaddr(lease->addr_);

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

void
Dhcpv4Srv::adjustRemoteAddr(const Pkt4Ptr& question, Pkt4Ptr& msg) {
    // Let's create static objects representing zeroed and broadcast
    // addresses. We will use them further in this function to test
    // other addresses against them. Since they are static, they will
    // be created only once.
    static const IOAddress zero_addr("0.0.0.0");
    static const IOAddress bcast_addr("255.255.255.255");

    // If received relayed message, server responds to the relay address.
    if (question->getGiaddr() != zero_addr) {
        msg->setRemoteAddr(question->getGiaddr());

    // If giaddr is 0 but client set ciaddr, server should unicast the
    // response to ciaddr.
    } else if (question->getCiaddr() != zero_addr) {
        msg->setRemoteAddr(question->getCiaddr());

    // We can't unicast the response to the client when sending NAK,
    // because we haven't allocated address for him. Therefore,
    // NAK is broadcast.
    } else if (msg->getType() == DHCPNAK) {
        msg->setRemoteAddr(bcast_addr);

    // If yiaddr is set it means that we have created a lease for a client.
    } else if (msg->getYiaddr() != zero_addr) {
        // If the broadcast bit is set in the flags field, we have to
        // send the response to broadcast address. Client may have requested it
        // because it doesn't support reception of messages on the interface
        // which doesn't have an address assigned. The other case when response
        // must be broadcasted is when our server does not support responding
        // directly to a client without address assigned.
        const bool bcast_flag = ((question->getFlags() & Pkt4::FLAG_BROADCAST_MASK) != 0);
        if (!IfaceMgr::instance().isDirectResponseSupported() || bcast_flag) {
            msg->setRemoteAddr(bcast_addr);

        // Client cleared the broadcast bit and we support direct responses
        // so we should unicast the response to a newly allocated address -
        // yiaddr.
        } else {
            msg->setRemoteAddr(msg->getYiaddr());

        }

    // In most cases, we should have the remote address found already. If we
    // found ourselves at this point, the rational thing to do is to respond
    // to the address we got the query from.
    } else {
        msg->setRemoteAddr(question->getRemoteAddr());

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

    sanityCheck(discover, FORBIDDEN);

    Pkt4Ptr offer = Pkt4Ptr
        (new Pkt4(DHCPOFFER, discover->getTransid()));

    copyDefaultFields(discover, offer);
    appendDefaultOptions(offer, DHCPOFFER);
    appendRequestedOptions(discover, offer);
    appendRequestedVendorOptions(discover, offer);

    assignLease(discover, offer);

    // There are a few basic options that we always want to
    // include in the response. If client did not request
    // them we append them for him.
    appendBasicOptions(discover, offer);

    return (offer);
}

Pkt4Ptr
Dhcpv4Srv::processRequest(Pkt4Ptr& request) {

    /// @todo Uncomment this (see ticket #3116)
    // sanityCheck(request, MANDATORY);

    Pkt4Ptr ack = Pkt4Ptr
        (new Pkt4(DHCPACK, request->getTransid()));

    copyDefaultFields(request, ack);
    appendDefaultOptions(ack, DHCPACK);
    appendRequestedOptions(request, ack);
    appendRequestedVendorOptions(request, ack);

    // Note that we treat REQUEST message uniformly, regardless if this is a
    // first request (requesting for new address), renewing existing address
    // or even rebinding.
    assignLease(request, ack);

    // There are a few basic options that we always want to
    // include in the response. If client did not request
    // them we append them for him.
    appendBasicOptions(request, ack);

    return (ack);
}

void
Dhcpv4Srv::processRelease(Pkt4Ptr& release) {

    /// @todo Uncomment this (see ticket #3116)
    // sanityCheck(release, MANDATORY);

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

        bool skip = false;

        // Execute all callouts registered for lease4_release
        if (HooksManager::calloutsPresent(Hooks.hook_index_lease4_release_)) {
            CalloutHandlePtr callout_handle = getCalloutHandle(release);

            // Delete all previous arguments
            callout_handle->deleteAllArguments();

            // Pass the original packet
            callout_handle->setArgument("query4", release);

            // Pass the lease to be updated
            callout_handle->setArgument("lease4", lease);

            // Call all installed callouts
            HooksManager::callCallouts(Hooks.hook_index_lease4_release_,
                                       *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to send the packet, so skip at this
            // stage means "drop response".
            if (callout_handle->getSkip()) {
                skip = true;
                LOG_DEBUG(dhcp4_logger, DBG_DHCP4_HOOKS,
                          DHCP4_HOOK_LEASE4_RELEASE_SKIP);
            }
        }

        // Ok, hw and client-id match - let's release the lease.
        if (!skip) {
            bool success = LeaseMgrFactory::instance().deleteLease(lease->addr_);

            if (success) {
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
    /// @todo Implement this (also see ticket #3116)
}

Pkt4Ptr
Dhcpv4Srv::processInform(Pkt4Ptr& inform) {

    /// @todo Implement this for real. (also see ticket #3116)
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

    Subnet4Ptr subnet;
    // Is this relayed message?
    IOAddress relay = question->getGiaddr();
    static const IOAddress notset("0.0.0.0");

    if (relay != notset) {
        // Yes: Use relay address to select subnet
        subnet = CfgMgr::instance().getSubnet4(relay);
    } else {

        // No: Use client's address to select subnet
        subnet = CfgMgr::instance().getSubnet4(question->getRemoteAddr());
    }

    /// @todo Implement getSubnet4(interface-name)

    // Let's execute all callouts registered for subnet4_select
    if (HooksManager::calloutsPresent(hook_index_subnet4_select_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(question);

        // We're reusing callout_handle from previous calls
        callout_handle->deleteAllArguments();

        // Set new arguments
        callout_handle->setArgument("query4", question);
        callout_handle->setArgument("subnet4", subnet);
        callout_handle->setArgument("subnet4collection",
                                    CfgMgr::instance().getSubnets4());

        // Call user (and server-side) callouts
        HooksManager::callCallouts(hook_index_subnet4_select_,
                                   *callout_handle);

        // Callouts decided to skip this step. This means that no subnet will be
        // selected. Packet processing will continue, but it will be severly
        // limited (i.e. only global options will be assigned)
        if (callout_handle->getSkip()) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_HOOKS,
                      DHCP4_HOOK_SUBNET4_SELECT_SKIP);
            return (Subnet4Ptr());
        }

        // Use whatever subnet was specified by the callout
        callout_handle->getArgument("subnet4", subnet);
    }

    return (subnet);
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

    // If there is HWAddress set and it is non-empty, then we're good
    if (pkt->getHWAddr() && !pkt->getHWAddr()->hwaddr_.empty()) {
        return;
    }

    // There has to be something to uniquely identify the client:
    // either non-zero MAC address or client-id option present (or both)
    OptionPtr client_id = pkt->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

    // If there's no client-id (or a useless one is provided, i.e. 0 length)
    if (!client_id || client_id->len() == client_id->getHeaderLen()) {
        isc_throw(RFCViolation, "Missing or useless client-id and no HW address "
                  " provided in message "
                  << serverReceivedPacketName(pkt->getType()));
    }
}

void
Dhcpv4Srv::openActiveSockets(const uint16_t port,
                             const bool use_bcast) {
    IfaceMgr::instance().closeSockets();

    // Get the reference to the collection of interfaces. This reference should
    // be valid as long as the program is run because IfaceMgr is a singleton.
    // Therefore we can safely iterate over instances of all interfaces and
    // modify their flags. Here we modify flags which indicate whether socket
    // should be open for a particular interface or not.
    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();
    for (IfaceMgr::IfaceCollection::const_iterator iface = ifaces.begin();
         iface != ifaces.end(); ++iface) {
        Iface* iface_ptr = IfaceMgr::instance().getIface(iface->getName());
        if (iface_ptr == NULL) {
            isc_throw(isc::Unexpected, "Interface Manager returned NULL"
                      << " instance of the interface when DHCPv4 server was"
                      << " trying to reopen sockets after reconfiguration");
        }
        if (CfgMgr::instance().isActiveIface(iface->getName())) {
            iface_ptr->inactive4_ = false;
            LOG_INFO(dhcp4_logger, DHCP4_ACTIVATE_INTERFACE)
                .arg(iface->getFullName());

        } else {
            // For deactivating interface, it should be sufficient to log it
            // on the debug level because it is more useful to know what
            // interface is activated which is logged on the info level.
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC,
                      DHCP4_DEACTIVATE_INTERFACE).arg(iface->getName());
            iface_ptr->inactive4_ = true;

        }
    }
    // Let's reopen active sockets. openSockets4 will check internally whether
    // sockets are marked active or inactive.
    // @todo Optimization: we should not reopen all sockets but rather select
    // those that have been affected by the new configuration.
    if (!IfaceMgr::instance().openSockets4(port, use_bcast)) {
        LOG_WARN(dhcp4_logger, DHCP4_NO_SOCKETS_OPEN);
    }
}

size_t
Dhcpv4Srv::unpackOptions(const OptionBuffer& buf,
                          const std::string& option_space,
                          isc::dhcp::OptionCollection& options) {
    size_t offset = 0;

    OptionDefContainer option_defs;
    if (option_space == "dhcp4") {
        // Get the list of stdandard option definitions.
        option_defs = LibDHCP::getOptionDefs(Option::V4);
    } else if (!option_space.empty()) {
        OptionDefContainerPtr option_defs_ptr =
            CfgMgr::instance().getOptionDefs(option_space);
        if (option_defs_ptr != NULL) {
            option_defs = *option_defs_ptr;
        }
    }
    // Get the search index #1. It allows to search for option definitions
    // using option code.
    const OptionDefContainerTypeIndex& idx = option_defs.get<1>();

    // The buffer being read comprises a set of options, each starting with
    // a one-byte type code and a one-byte length field.
    while (offset + 1 <= buf.size()) {
        uint8_t opt_type = buf[offset++];

        // DHO_END is a special, one octet long option
        if (opt_type == DHO_END)
            return (offset); // just return. Don't need to add DHO_END option

        // DHO_PAD is just a padding after DHO_END. Let's continue parsing
        // in case we receive a message without DHO_END.
        if (opt_type == DHO_PAD)
            continue;

        if (offset + 1 >= buf.size()) {
            // opt_type must be cast to integer so as it is not treated as
            // unsigned char value (a number is presented in error message).
            isc_throw(OutOfRange, "Attempt to parse truncated option "
                      << static_cast<int>(opt_type));
        }

        uint8_t opt_len =  buf[offset++];
        if (offset + opt_len > buf.size()) {
            isc_throw(OutOfRange, "Option parse failed. Tried to parse "
                      << offset + opt_len << " bytes from " << buf.size()
                      << "-byte long buffer.");
        }

        /// @todo: Not sure if this is needed. Perhaps it would be better to extend
        /// DHO_VIVSO_SUBOPTIONS definitions in std_option_defs.h to cover
        /// OptionVendor class?
        if (opt_type == DHO_VIVSO_SUBOPTIONS) {
            if (offset + 4 > buf.size()) {
                // Truncated vendor-option. There is expected at least 4 bytes
                // long enterprise-id field
                return (offset);
            }

            // Parse this as vendor option
            OptionPtr vendor_opt(new OptionVendor(Option::V4, buf.begin() + offset,
                                                  buf.begin() + offset + opt_len));
            options.insert(std::make_pair(opt_type, vendor_opt));

            offset += opt_len;
            continue;
        }

        // Get all definitions with the particular option code. Note that option code
        // is non-unique within this container however at this point we expect
        // to get one option definition with the particular code. If more are
        // returned we report an error.
        const OptionDefContainerTypeRange& range = idx.equal_range(opt_type);
        // Get the number of returned option definitions for the option code.
        size_t num_defs = distance(range.first, range.second);

        OptionPtr opt;
        if (num_defs > 1) {
            // Multiple options of the same code are not supported right now!
            isc_throw(isc::Unexpected, "Internal error: multiple option definitions"
                      " for option type " << static_cast<int>(opt_type)
                      << " returned. Currently it is not supported to initialize"
                      << " multiple option definitions for the same option code."
                      << " This will be supported once support for option spaces"
                      << " is implemented");
        } else if (num_defs == 0) {
            opt = OptionPtr(new Option(Option::V4, opt_type,
                                       buf.begin() + offset,
                                       buf.begin() + offset + opt_len));
            opt->setEncapsulatedSpace("dhcp4");
        } else {
            // The option definition has been found. Use it to create
            // the option instance from the provided buffer chunk.
            const OptionDefinitionPtr& def = *(range.first);
            assert(def);
            opt = def->optionFactory(Option::V4, opt_type,
                                     buf.begin() + offset,
                                     buf.begin() + offset + opt_len,
                                     boost::bind(&Dhcpv4Srv::unpackOptions,
                                                 this, _1, _2, _3));
        }

        options.insert(std::make_pair(opt_type, opt));
        offset += opt_len;
    }
    return (offset);
}


}   // namespace dhcp
}   // namespace isc
