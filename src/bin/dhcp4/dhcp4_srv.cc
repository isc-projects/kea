// Copyright (C) 2011-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option_string.h>
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
#include <util/strutil.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <iomanip>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
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

namespace {

// @todo The following constants describe server's behavior with respect to the
// DHCPv4 Client FQDN Option sent by a client. They will be removed
// when DDNS parameters for DHCPv4 are implemented with the ticket #3033.

// @todo Additional configuration parameter which we may consider is the one
// that controls whether the DHCP server sends the removal NameChangeRequest
// if it discovers that the entry for the particular client exists or that
// it always updates the DNS.

// Should server always include the FQDN option in its response, regardless
// if it has been requested in Parameter Request List Option (Disabled).
const bool FQDN_ALWAYS_INCLUDE = false;
// Enable A RR update delegation to the client (Disabled).
const bool FQDN_ALLOW_CLIENT_UPDATE = false;
// Globally enable updates (Enabled).
const bool FQDN_ENABLE_UPDATE = true;
// Do update, even if client requested no updates with N flag (Disabled).
const bool FQDN_OVERRIDE_NO_UPDATE = false;
// Server performs an update when client requested delegation (Enabled).
const bool FQDN_OVERRIDE_CLIENT_UPDATE = true;
// The fully qualified domain-name suffix if partial name provided by
// a client.
const char* FQDN_PARTIAL_SUFFIX = "example.com";
// Should server replace the domain-name supplied by the client (Disabled).
const bool FQDN_REPLACE_CLIENT_NAME = false;

}

Dhcpv4Srv::Dhcpv4Srv(uint16_t port, const char* dbconfig, const bool use_bcast,
                     const bool direct_response_desired)
: shutdown_(true), alloc_engine_(), port_(port),
    use_bcast_(use_bcast), hook_index_pkt4_receive_(-1),
    hook_index_subnet4_select_(-1), hook_index_pkt4_send_(-1) {

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_OPEN_SOCKET).arg(port);
    try {
        // Open sockets only if port is non-zero. Port 0 is used for testing
        // purposes in two cases:
        // - when non-socket related testing is performed
        // - when the particular test supplies its own packet filtering class.
        if (port) {
            // First call to instance() will create IfaceMgr (it's a singleton)
            // it may throw something if things go wrong.
            // The 'true' value of the call to setMatchingPacketFilter imposes
            // that IfaceMgr will try to use the mechanism to respond directly
            // to the client which doesn't have address assigned. This capability
            // may be lacking on some OSes, so there is no guarantee that server
            // will be able to respond directly.
            IfaceMgr::instance().setMatchingPacketFilter(direct_response_desired);

            // Create error handler. This handler will be called every time
            // the socket opening operation fails. We use this handler to
            // log a warning.
            isc::dhcp::IfaceMgrErrorMsgCallback error_handler =
                boost::bind(&Dhcpv4Srv::ifaceMgrSocket4ErrorHandler, _1);
            IfaceMgr::instance().openSockets4(port_, use_bcast_, error_handler);
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

        // Check if the DHCPv4 packet has been sent to us or to someone else.
        // If it hasn't been sent to us, drop it!
        if (!acceptServerId(query)) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_NOT_FOR_US)
                .arg(query->getTransid())
                .arg(query->getIface());
            continue;
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

        // Assign this packet to one or more classes if needed
        classifyPacket(query);

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

        // Let's do class specific processing. This is done before
        // pkt4_send.
        //
        /// @todo: decide whether we want to add a new hook point for
        /// doing class specific processing.
        if (!classSpecificProcessing(query, rsp)) {
            /// @todo add more verbosity here
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_CLASS_PROCESSING_FAILED);

            continue;
        }

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

        // Send NameChangeRequests to the b10-dhcp_ddns module.
        sendNameChangeRequests();
    }

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

isc::dhcp_ddns::D2Dhcid
Dhcpv4Srv::computeDhcid(const Lease4Ptr& lease) {
    if (!lease) {
        isc_throw(DhcidComputeError, "a pointer to the lease must be not"
                  " NULL to compute DHCID");

    } else if (lease->hostname_.empty()) {
        isc_throw(DhcidComputeError, "unable to compute the DHCID for the"
                  " lease which has empty hostname set");

    }

    // In order to compute DHCID the client's hostname must be encoded in
    // canonical wire format. It is unlikely that the FQDN is malformed
    // because it is validated by the classes which encapsulate options
    // carrying client FQDN. However, if the client name was carried in the
    // Hostname option it is more likely as it carries the hostname as a
    // regular string.
    std::vector<uint8_t> fqdn_wire;
    try {
        OptionDataTypeUtil::writeFqdn(lease->hostname_, fqdn_wire, true);

    } catch (const Exception& ex) {
        isc_throw(DhcidComputeError, "unable to compute DHCID because the"
                  " hostname: " << lease->hostname_ << " is invalid");

    }

    // Prefer client id to HW address to compute DHCID. If Client Id is
    // NULL, use HW address.
    try {
        if (lease->client_id_) {
            return (D2Dhcid(lease->client_id_->getClientId(), fqdn_wire));

        } else {
            HWAddrPtr hwaddr(new HWAddr(lease->hwaddr_, HTYPE_ETHER));
            return (D2Dhcid(hwaddr, fqdn_wire));
        }
    } catch (const Exception& ex) {
        isc_throw(DhcidComputeError, "unable to compute DHCID: "
                  << ex.what());

    }

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
    // It is possible to disable RFC6842 to keep backward compatibility
    bool echo = CfgMgr::instance().echoClientId();
    OptionPtr client_id = question->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (client_id && echo) {
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

    // more options will be added here later
}

void
Dhcpv4Srv::appendServerID(const Pkt4Ptr& response) {
    // The source address for the outbound message should have been set already.
    // This is the address that to the best of the server's knowledge will be
    // available from the client.
    // @todo: perhaps we should consider some more sophisticated server id
    // generation, but for the current use cases, it should be ok.
    response->addOption(OptionPtr(new Option4AddrLst(DHO_DHCP_SERVER_IDENTIFIER,
                                                     response->getLocalAddr()))
                        );
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
        if (!msg->getOption(*opt)) {
            Subnet::OptionDescriptor desc =
                subnet->getOptionDescriptor("dhcp4", *opt);
            if (desc.option && !msg->getOption(*opt)) {
                msg->addOption(desc.option);
            }
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
    OptionUint8ArrayPtr oro =
        boost::dynamic_pointer_cast<OptionUint8Array>(vendor_req->getOption(DOCSIS3_V4_ORO));

    // Option ORO not found. Don't do anything then.
    if (!oro) {
        return;
    }

    boost::shared_ptr<OptionVendor> vendor_rsp(new OptionVendor(Option::V4, vendor_id));

    // Get the list of options that client requested.
    bool added = false;
    const std::vector<uint8_t>& requested_opts = oro->getValues();

    for (std::vector<uint8_t>::const_iterator code = requested_opts.begin();
         code != requested_opts.end(); ++code) {
        if  (!vendor_rsp->getOption(*code)) {
            Subnet::OptionDescriptor desc = subnet->getVendorOptionDescriptor(vendor_id,
                                                                              *code);
            if (desc.option) {
                vendor_rsp->addOption(desc.option);
                added = true;
            }
        }

        if (added) {
            answer->addOption(vendor_rsp);
        }
    }
}


void
Dhcpv4Srv::appendBasicOptions(const Pkt4Ptr& question, Pkt4Ptr& msg) {
    // Identify options that we always want to send to the
    // client (if they are configured).
    static const uint16_t required_options[] = {
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
Dhcpv4Srv::processClientName(const Pkt4Ptr& query, Pkt4Ptr& answer) {
    // It is possible that client has sent both Client FQDN and Hostname
    // option. In such case, server should prefer Client FQDN option and
    // ignore the Hostname option.
    try {
        Option4ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<Option4ClientFqdn>
            (query->getOption(DHO_FQDN));
        if (fqdn) {
            processClientFqdnOption(fqdn, answer);

        } else {
            OptionCustomPtr hostname = boost::dynamic_pointer_cast<OptionCustom>
                (query->getOption(DHO_HOST_NAME));
            if (hostname) {
                processHostnameOption(hostname, answer);
            }

        }
    } catch (const Exception& ex) {
        // In some rare cases it is possible that the client's name processing
        // fails. For example, the Hostname option may be malformed, or there
        // may be an error in the server's logic which would cause multiple
        // attempts to add the same option to the response message. This
        // error message aggregates all these errors so they can be diagnosed
        // from the log. We don't want to throw an exception here because,
        // it will impact the processing of the whole packet. We rather want
        // the processing to continue, even if the client's name is wrong.
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_CLIENT_NAME_PROC_FAIL)
            .arg(ex.what());
    }
}

void
Dhcpv4Srv::processClientFqdnOption(const Option4ClientFqdnPtr& fqdn,
                                   Pkt4Ptr& answer) {
    // Create the DHCPv4 Client FQDN Option to be included in the server's
    // response to a client.
    Option4ClientFqdnPtr fqdn_resp(new Option4ClientFqdn(*fqdn));

    // RFC4702, section 4 - set 'NOS' flags to 0.
    fqdn_resp->setFlag(Option4ClientFqdn::FLAG_S, 0);
    fqdn_resp->setFlag(Option4ClientFqdn::FLAG_O, 0);
    fqdn_resp->setFlag(Option4ClientFqdn::FLAG_N, 0);

    // Conditions when N flag has to be set to indicate that server will not
    // perform DNS updates:
    // 1. Updates are globally disabled,
    // 2. Client requested no update and server respects it,
    // 3. Client requested that the forward DNS update is delegated to the
    //    client but server neither respects requests for forward update
    //    delegation nor it is configured to send update on its own when
    //    client requested delegation.
    if (!FQDN_ENABLE_UPDATE ||
        (fqdn->getFlag(Option4ClientFqdn::FLAG_N) &&
         !FQDN_OVERRIDE_NO_UPDATE) ||
        (!fqdn->getFlag(Option4ClientFqdn::FLAG_S) &&
         !FQDN_ALLOW_CLIENT_UPDATE && !FQDN_OVERRIDE_CLIENT_UPDATE)) {
        fqdn_resp->setFlag(Option4ClientFqdn::FLAG_N, true);

    // Conditions when S flag is set to indicate that server will perform DNS
    // update on its own:
    // 1. Client requested that server performs DNS update and DNS updates are
    //    globally enabled.
    // 2. Client requested that server delegates forward update to the client
    //    but server doesn't respect requests for delegation and it is
    // configured to perform an update on its own when client requested the
    // delegation.
    } else  if (fqdn->getFlag(Option4ClientFqdn::FLAG_S) ||
                (!fqdn->getFlag(Option4ClientFqdn::FLAG_S) &&
                 !FQDN_ALLOW_CLIENT_UPDATE && FQDN_OVERRIDE_CLIENT_UPDATE)) {
        fqdn_resp->setFlag(Option4ClientFqdn::FLAG_S, true);
    }

    // Server MUST set the O flag if it has overriden the client's setting
    // of S flag.
    if (fqdn->getFlag(Option4ClientFqdn::FLAG_S) !=
        fqdn_resp->getFlag(Option4ClientFqdn::FLAG_S)) {
        fqdn_resp->setFlag(Option4ClientFqdn::FLAG_O, true);
    }

    // If client suppled partial or empty domain-name, server should generate
    // one.
    if (fqdn->getDomainNameType() == Option4ClientFqdn::PARTIAL) {
        std::ostringstream name;
        if (fqdn->getDomainName().empty() || FQDN_REPLACE_CLIENT_NAME) {
            fqdn_resp->setDomainName("", Option4ClientFqdn::PARTIAL);

        } else {
            name << fqdn->getDomainName();
            name << "." << FQDN_PARTIAL_SUFFIX;
            fqdn_resp->setDomainName(name.str(), Option4ClientFqdn::FULL);

        }

    // Server may be configured to replace a name supplied by a client, even if
    // client supplied fully qualified domain-name. The empty domain-name is
    // is set to indicate that the name must be generated when the new lease
    // is acquired.
    } else if(FQDN_REPLACE_CLIENT_NAME) {
        fqdn_resp->setDomainName("", Option4ClientFqdn::PARTIAL);
    }

    // Add FQDN option to the response message. Note that, there may be some
    // cases when server may choose not to include the FQDN option in a
    // response to a client. In such cases, the FQDN should be removed from the
    // outgoing message. In theory we could cease to include the FQDN option
    // in this function until it is confirmed that it should be included.
    // However, we include it here for simplicity. Functions used to acquire
    // lease for a client will scan the response message for FQDN and if it
    // is found they will take necessary actions to store the FQDN information
    // in the lease database as well as to generate NameChangeRequests to DNS.
    // If we don't store the option in the reponse message, we will have to
    // propagate it in the different way to the functions which acquire the
    // lease. This would require modifications to the API of this class.
    answer->addOption(fqdn_resp);
}

void
Dhcpv4Srv::processHostnameOption(const OptionCustomPtr& opt_hostname,
                                 Pkt4Ptr& answer) {
    // Do nothing if the DNS updates are disabled.
    if (!FQDN_ENABLE_UPDATE) {
        return;
    }

    std::string hostname = isc::util::str::trim(opt_hostname->readString());
    unsigned int label_count = OptionDataTypeUtil::getLabelCount(hostname);
    // The hostname option sent by the client should be at least 1 octet long.
    // If it isn't we ignore this option.
    if (label_count == 0) {
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_EMPTY_HOSTNAME);
        return;
    }
    // Copy construct the hostname provided by the client. It is entirely
    // possible that we will use the hostname option provided by the client
    // to perform the DNS update and we will send the same option to him to
    // indicate that we accepted this hostname.
    OptionCustomPtr opt_hostname_resp(new OptionCustom(*opt_hostname));

    // The hostname option may be unqualified or fully qualified. The lab_count
    // holds the number of labels for the name. The number of 1 means that
    // there is only root label "." (even for unqualified names, as the
    // getLabelCount function treats each name as a fully qualified one).
    // By checking the number of labels present in the hostname we may infer
    // whether client has sent the fully qualified or unqualified hostname.

    // @todo We may want to reconsider whether it is appropriate for the
    // client to send a root domain name as a Hostname. There are
    // also extensions to the auto generation of the client's name,
    // e.g. conversion to the puny code which may be considered at some point.
    // For now, we just remain liberal and expect that the DNS will handle
    // conversion if needed and possible.
    if (FQDN_REPLACE_CLIENT_NAME || (label_count < 2)) {
        opt_hostname_resp->writeString("");
    // If there are two labels, it means that the client has specified
    // the unqualified name. We have to concatenate the unqalified name
    // with the domain name.
    } else if (label_count == 2) {
        std::ostringstream resp_hostname;
        resp_hostname << hostname << "." << FQDN_PARTIAL_SUFFIX << ".";
        opt_hostname_resp->writeString(resp_hostname.str());
    }

    answer->addOption(opt_hostname_resp);
}

void
Dhcpv4Srv::createNameChangeRequests(const Lease4Ptr& lease,
                                    const Lease4Ptr& old_lease) {
    if (!lease) {
        isc_throw(isc::Unexpected,
                  "NULL lease specified when creating NameChangeRequest");
    }

    // If old lease is not NULL, it is an indication that the lease has
    // just been renewed. In such case we may need to generate the
    // additional NameChangeRequest to remove an existing entry before
    // we create a NameChangeRequest to add the entry for an updated lease.
    // We may also decide not to generate any requests at all. This is when
    // we discover that nothing has changed in the client's FQDN data.
    if (old_lease) {
        if (!lease->matches(*old_lease)) {
            isc_throw(isc::Unexpected,
                      "there is no match between the current instance of the"
                      " lease: " << lease->toText() << ", and the previous"
                      " instance: " << lease->toText());
        } else {
            // There will be a NameChangeRequest generated to remove existing
            // DNS entries if the following conditions are met:
            // - The hostname is set for the existing lease, we can't generate
            //   removal request for non-existent hostname.
            // - A server has performed reverse, forward or both updates.
            // - FQDN data between the new and old lease do not match.
            if  ((lease->hostname_ != old_lease->hostname_) ||
                 (lease->fqdn_fwd_ != old_lease->fqdn_fwd_) ||
                 (lease->fqdn_rev_ != old_lease->fqdn_rev_)) {
                queueNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE,
                                       old_lease);

            // If FQDN data from both leases match, there is no need to update.
            } else if ((lease->hostname_ == old_lease->hostname_) &&
                       (lease->fqdn_fwd_ == old_lease->fqdn_fwd_) &&
                       (lease->fqdn_rev_ == old_lease->fqdn_rev_)) {
                return;
            }

        }
    }

    // We may need to generate the NameChangeRequest for the new lease. It
    // will be generated only if hostname is set and if forward or reverse
    // update has been requested.
    queueNameChangeRequest(isc::dhcp_ddns::CHG_ADD, lease);
}

void
Dhcpv4Srv::
queueNameChangeRequest(const isc::dhcp_ddns::NameChangeType chg_type,
                       const Lease4Ptr& lease) {
    // The hostname must not be empty, and at least one type of update
    // should be requested.
    if (!lease || lease->hostname_.empty() ||
        (!lease->fqdn_rev_ && !lease->fqdn_fwd_)) {
        return;
    }

    // Create the DHCID for the NameChangeRequest.
    D2Dhcid dhcid;
    try {
        dhcid  = computeDhcid(lease);
    } catch (const DhcidComputeError& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_DHCID_COMPUTE_ERROR)
            .arg(lease->toText())
            .arg(ex.what());
        return;
    }
    // Create NameChangeRequest
    NameChangeRequest ncr(chg_type, lease->fqdn_fwd_, lease->fqdn_rev_,
                          lease->hostname_, lease->addr_.toText(),
                          dhcid, lease->cltt_ + lease->valid_lft_,
                          lease->valid_lft_);
    // And queue it.
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_QUEUE_NCR)
        .arg(chg_type == CHG_ADD ? "add" : "remove")
        .arg(ncr.toText());
    name_change_reqs_.push(ncr);
}

void
Dhcpv4Srv::sendNameChangeRequests() {
    while (!name_change_reqs_.empty()) {
        // @todo Once next NameChangeRequest is picked from the queue
        // we should send it to the b10-dhcp_ddns module. Currently we
        // just drop it.
        name_change_reqs_.pop();
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

    // Set up siaddr. Perhaps assignLease is not the best place to call this
    // as siaddr has nothing to do with a lease, but otherwise we would have
    // to select subnet twice (performance hit) or update too many functions
    // at once.
    // @todo: move subnet selection to a common code
    answer->setSiaddr(subnet->getSiaddr());

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

    std::string hostname;
    bool fqdn_fwd = false;
    bool fqdn_rev = false;
    OptionCustomPtr opt_hostname;
    Option4ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option4ClientFqdn>(answer->getOption(DHO_FQDN));
    if (fqdn) {
        hostname = fqdn->getDomainName();
        fqdn_fwd = fqdn->getFlag(Option4ClientFqdn::FLAG_S);
        fqdn_rev = !fqdn->getFlag(Option4ClientFqdn::FLAG_N);
    } else {
        opt_hostname = boost::dynamic_pointer_cast<OptionCustom>
            (answer->getOption(DHO_HOST_NAME));
        if (opt_hostname) {
            hostname = opt_hostname->readString();
            // @todo It could be configurable what sort of updates the server
            // is doing when Hostname option was sent.
            fqdn_fwd = true;
            fqdn_rev = true;
        }
    }

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honour the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    // @todo pass the actual FQDN data.
    Lease4Ptr old_lease;
    Lease4Ptr lease = alloc_engine_->allocateLease4(subnet, client_id, hwaddr,
                                                      hint, fqdn_fwd, fqdn_rev,
                                                      hostname,
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

        // If there has been Client FQDN or Hostname option sent, but the
        // hostname is empty, it means that server is responsible for
        // generating the entire hostname for the client. The example of the
        // client's name, generated from the IP address is: host-192-0-2-3.
        if ((fqdn || opt_hostname) && lease->hostname_.empty()) {
            hostname = lease->addr_.toText();
            // Replace dots with hyphens.
            std::replace(hostname.begin(), hostname.end(), '.', '-');
            ostringstream stream;
            // The partial suffix will need to be replaced with the actual
            // domain-name for the client when configuration is implemented.
            stream << "host-" << hostname << "." << FQDN_PARTIAL_SUFFIX << ".";
            lease->hostname_ = stream.str();
            // The operations below are rather safe, but we want to catch
            // any potential exceptions (e.g. invalid lease database backend
            // implementation) and log an error.
            try {
                // The lease update should be safe, because the lease should
                // be already in the database. In most cases the exception
                // would be thrown if the lease was missing.
                LeaseMgrFactory::instance().updateLease4(lease);
                // The name update in the option should be also safe,
                // because the generated name is well formed.
                if (fqdn) {
                    fqdn->setDomainName(lease->hostname_,
                                        Option4ClientFqdn::FULL);
                } else if (opt_hostname) {
                    opt_hostname->writeString(lease->hostname_);
                }

            } catch (const Exception& ex) {
                LOG_ERROR(dhcp4_logger, DHCP4_NAME_GEN_UPDATE_FAIL)
                    .arg(ex.what());
            }
        }

        // IP Address Lease time (type 51)
        opt = OptionPtr(new Option(Option::V4, DHO_DHCP_LEASE_TIME));
        opt->setUint32(lease->valid_lft_);
        answer->addOption(opt);

        // Subnet mask (type 1)
        answer->addOption(getNetmaskOption(subnet));

        // @todo: send renew timer option (T1, option 58)
        // @todo: send rebind timer option (T2, option 59)

        // @todo Currently the NameChangeRequests are always generated if
        // real (not fake) allocation is being performed. Should we have
        // control switch to enable/disable NameChangeRequest creation?
        // Perhaps we need a way to detect whether the b10-dhcp-ddns module
        // is up an running?
        if (!fake_allocation) {
            try {
                createNameChangeRequests(lease, old_lease);
            } catch (const Exception& ex) {
                LOG_ERROR(dhcp4_logger, DHCP4_NCR_CREATION_FAILED)
                    .arg(ex.what());
            }

        }

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

        answer->delOption(DHO_FQDN);
        answer->delOption(DHO_HOST_NAME);
    }
}

void
Dhcpv4Srv::adjustIfaceData(const Pkt4Ptr& query, const Pkt4Ptr& response) {
    adjustRemoteAddr(query, response);

    // For the non-relayed message, the destination port is the client's port.
    // For the relayed message, the server/relay port is a destination.
    // Note that the call to this function may throw if invalid combination
    // of hops and giaddr is found (hops = 0 if giaddr = 0 and hops != 0 if
    // giaddr != 0). The exception will propagate down and eventually cause the
    // packet to be discarded.
    response->setRemotePort(query->isRelayed() ? DHCP4_SERVER_PORT :
                            DHCP4_CLIENT_PORT);

    // In many cases the query is sent to a broadcast address. This address
    // appears as a local address in the query message. Therefore we can't
    // simply copy local address from the query and use it as a source
    // address for the response. Instead, we have to check what address our
    // socket is bound to and use it as a source address. This operation
    // may throw if for some reason the socket is closed.
    // @todo Consider an optimization that we use local address from
    // the query if this address is not broadcast.
    SocketInfo sock_info = IfaceMgr::instance().getSocket(*query);
    // Set local adddress, port and interface.
    response->setLocalAddr(sock_info.addr_);
    response->setLocalPort(DHCP4_SERVER_PORT);
    response->setIface(query->getIface());
    response->setIndex(query->getIndex());
}

void
Dhcpv4Srv::adjustRemoteAddr(const Pkt4Ptr& question, const Pkt4Ptr& response) {
    // Let's create static objects representing zeroed and broadcast
    // addresses. We will use them further in this function to test
    // other addresses against them. Since they are static, they will
    // be created only once.
    static const IOAddress zero_addr("0.0.0.0");
    static const IOAddress bcast_addr("255.255.255.255");

    // If received relayed message, server responds to the relay address.
    if (question->isRelayed()) {
        response->setRemoteAddr(question->getGiaddr());

    // If giaddr is 0 but client set ciaddr, server should unicast the
    // response to ciaddr.
    } else if (question->getCiaddr() != zero_addr) {
        response->setRemoteAddr(question->getCiaddr());

    // We can't unicast the response to the client when sending NAK,
    // because we haven't allocated address for him. Therefore,
    // NAK is broadcast.
    } else if (response->getType() == DHCPNAK) {
        response->setRemoteAddr(bcast_addr);

    // If yiaddr is set it means that we have created a lease for a client.
    } else if (response->getYiaddr() != zero_addr) {
        // If the broadcast bit is set in the flags field, we have to
        // send the response to broadcast address. Client may have requested it
        // because it doesn't support reception of messages on the interface
        // which doesn't have an address assigned. The other case when response
        // must be broadcasted is when our server does not support responding
        // directly to a client without address assigned.
        const bool bcast_flag = ((question->getFlags() & Pkt4::FLAG_BROADCAST_MASK) != 0);
        if (!IfaceMgr::instance().isDirectResponseSupported() || bcast_flag) {
            response->setRemoteAddr(bcast_addr);

        // Client cleared the broadcast bit and we support direct responses
        // so we should unicast the response to a newly allocated address -
        // yiaddr.
        } else {
            response->setRemoteAddr(response ->getYiaddr());

        }

    // In most cases, we should have the remote address found already. If we
    // found ourselves at this point, the rational thing to do is to respond
    // to the address we got the query from.
    } else {
        response->setRemoteAddr(question->getRemoteAddr());

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

    // If DISCOVER message contains the FQDN or Hostname option, server
    // may respond to the client with the appropriate FQDN or Hostname
    // option to indicate that whether it will take responsibility for
    // updating DNS when the client sends REQUEST message.
    processClientName(discover, offer);

    assignLease(discover, offer);

    // Adding any other options makes sense only when we got the lease.
    if (offer->getYiaddr() != IOAddress("0.0.0.0")) {
        appendRequestedOptions(discover, offer);
        appendRequestedVendorOptions(discover, offer);
        // There are a few basic options that we always want to
        // include in the response. If client did not request
        // them we append them for him.
        appendBasicOptions(discover, offer);
    }

    // Set the src/dest IP address, port and interface for the outgoing
    // packet.
    adjustIfaceData(discover, offer);

    appendServerID(offer);

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

    // If REQUEST message contains the FQDN or Hostname option, server
    // should respond to the client with the appropriate FQDN or Hostname
    // option to indicate if it takes responsibility for the DNS updates.
    // This is performed by the function below.
    processClientName(request, ack);

    // Note that we treat REQUEST message uniformly, regardless if this is a
    // first request (requesting for new address), renewing existing address
    // or even rebinding.
    assignLease(request, ack);

    // Adding any other options makes sense only when we got the lease.
    if (ack->getYiaddr() != IOAddress("0.0.0.0")) {
        appendRequestedOptions(request, ack);
        appendRequestedVendorOptions(request, ack);
        // There are a few basic options that we always want to
        // include in the response. If client did not request
        // them we append them for him.
        appendBasicOptions(request, ack);
    }

    // Set the src/dest IP address, port and interface for the outgoing
    // packet.
    adjustIfaceData(request, ack);

    appendServerID(ack);

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
        Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(release->getCiaddr());

        if (!lease) {
            // No such lease - bogus release
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_NO_LEASE)
                .arg(release->getCiaddr().toText())
                .arg(release->getHWAddr()->toText())
                .arg(client_id ? client_id->toText() : "(no client-id)");
            return;
        }

        // Does the hardware address match? We don't want one client releasing
        // second client's leases.
        if (lease->hwaddr_ != release->getHWAddr()->hwaddr_) {
            // @todo: Print hwaddr from lease as part of ticket #2589
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_WRONG_HWADDR)
                .arg(release->getCiaddr().toText())
                .arg(client_id ? client_id->toText() : "(no client-id)")
                .arg(release->getHWAddr()->toText());
            return;
        }

        // Does the lease have client-id info? If it has, then check it with what
        // the client sent us.
        if (lease->client_id_ && client_id && *lease->client_id_ != *client_id) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_WRONG_CLIENT_ID)
                .arg(release->getCiaddr().toText())
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
                // Release successful
                LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE)
                    .arg(lease->addr_.toText())
                    .arg(client_id ? client_id->toText() : "(no client-id)")
                    .arg(release->getHWAddr()->toText());

                // Remove existing DNS entries for the lease, if any.
                queueNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, lease);

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

        // No: the message has been received from a directly connected client.
        // The IPv4 address assigned to the interface on which this message
        // has been received, will be used to determine the subnet suitable for
        // a client.
        subnet = CfgMgr::instance().getSubnet4(question->getIface());
    }

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

bool
Dhcpv4Srv::acceptServerId(const Pkt4Ptr& pkt) const {
    // This function is meant to be called internally by the server class, so
    // we rely on the caller to sanity check the pointer and we don't check
    // it here.

    // Check if server identifier option is present. If it is not present
    // we accept the message because it is targetted to all servers.
    // Note that we don't check cases that server identifier is mandatory
    // but not present. This is meant to be sanity checked in other
    // functions.
    OptionPtr option = pkt->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    if (!option) {
        return (true);
    }
    // Server identifier is present. Let's convert it to 4-byte address
    // and try to match with server identifiers used by the server.
    OptionCustomPtr option_custom =
        boost::dynamic_pointer_cast<OptionCustom>(option);
    // Unable to convert the option to the option type which encapsulates it.
    // We treat this as non-matching server id.
    if (!option_custom) {
        return (false);
    }
    // The server identifier option should carry exactly one IPv4 address.
    // If the option definition for the server identifier doesn't change,
    // the OptionCustom object should have exactly one IPv4 address and
    // this check is somewhat redundant. On the other hand, if someone
    // breaks option it may be better to check that here.
    if (option_custom->getDataFieldsNum() != 1) {
        return (false);
    }

    // The server identifier MUST be an IPv4 address. If given address is
    // v6, it is wrong.
    IOAddress server_id = option_custom->readAddress();
    if (!server_id.isV4()) {
        return (false);
    }

    // This function iterates over all interfaces on which the
    // server is listening to find the one which has a socket bound
    // to the address carried in the server identifier option.
    // This has some performance implications. However, given that
    // typically there will be just a few active interfaces the
    // performance hit should be acceptable. If it turns out to
    // be significant, we will have to cache server identifiers
    // when sockets are opened.
    return (IfaceMgr::instance().hasOpenSocket(server_id));
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
    isc::dhcp::IfaceMgrErrorMsgCallback error_handler =
        boost::bind(&Dhcpv4Srv::ifaceMgrSocket4ErrorHandler, _1);
    if (!IfaceMgr::instance().openSockets4(port, use_bcast, error_handler)) {
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

void
Dhcpv4Srv::ifaceMgrSocket4ErrorHandler(const std::string& errmsg) {
    // Log the reason for socket opening failure and return.
    LOG_WARN(dhcp4_logger, DHCP4_OPEN_SOCKET_FAIL).arg(errmsg);
}

void Dhcpv4Srv::classifyPacket(const Pkt4Ptr& pkt) {
    boost::shared_ptr<OptionString> vendor_class =
        boost::dynamic_pointer_cast<OptionString>(pkt->getOption(DHO_VENDOR_CLASS_IDENTIFIER));

    string classes = "";

    if (!vendor_class) {
        return;
    }

    // DOCSIS specific section

    // Let's keep this as a series of checks. So far we're supporting only
    // docsis3.0, but there are also docsis2.0, docsis1.1 and docsis1.0. We
    // may come up with adding several classes, e.g. for docsis2.0 we would
    // add classes docsis2.0, docsis1.1 and docsis1.0.

    // Also we are using find, because we have at least one traffic capture
    // where the user class was followed by a space ("docsis3.0 ").

    // For now, the code is very simple, but it is expected to get much more
    // complex soon. One specific case is that the vendor class is an option
    // sent by the client, so we should not trust it. To confirm that the device
    // is indeed a modem, John B. suggested to check whether chaddr field
    // quals subscriber-id option that was inserted by the relay (CMTS).
    // This kind of logic will appear here soon.
    if (vendor_class->getValue().find(DOCSIS3_CLASS_MODEM) != std::string::npos) {
        pkt->addClass(DOCSIS3_CLASS_MODEM);
        classes += string(DOCSIS3_CLASS_MODEM) + " ";
    } else
    if (vendor_class->getValue().find(DOCSIS3_CLASS_EROUTER) != std::string::npos) {
        pkt->addClass(DOCSIS3_CLASS_EROUTER);
        classes += string(DOCSIS3_CLASS_EROUTER) + " ";
    } else {
        classes += vendor_class->getValue();
        pkt->addClass(vendor_class->getValue());
    }

    if (!classes.empty()) {
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_CLASS_ASSIGNED)
            .arg(classes);
    }
}

bool Dhcpv4Srv::classSpecificProcessing(const Pkt4Ptr& query, const Pkt4Ptr& rsp) {

    Subnet4Ptr subnet = selectSubnet(query);
    if (!subnet) {
        return (true);
    }

    if (query->inClass(DOCSIS3_CLASS_MODEM)) {

        // Set next-server. This is TFTP server address. Cable modems will
        // download their configuration from that server.
        rsp->setSiaddr(subnet->getSiaddr());

        // Now try to set up file field in DHCPv4 packet. We will just copy
        // content of the boot-file option, which contains the same information.
        Subnet::OptionDescriptor desc =
            subnet->getOptionDescriptor("dhcp4", DHO_BOOT_FILE_NAME);

        if (desc.option) {
            boost::shared_ptr<OptionString> boot =
                boost::dynamic_pointer_cast<OptionString>(desc.option);
            if (boot) {
                std::string filename = boot->getValue();
                rsp->setFile((const uint8_t*)filename.c_str(), filename.size());
            }
        }
    }

    if (query->inClass(DOCSIS3_CLASS_EROUTER)) {

        // Do not set TFTP server address for eRouter devices.
        rsp->setSiaddr(IOAddress("0.0.0.0"));
    }

    return (true);
}

}   // namespace dhcp
}   // namespace isc
