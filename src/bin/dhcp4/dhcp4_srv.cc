// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_selector.h>
#include <dhcpsrv/utils.h>
#include <dhcpsrv/utils.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_log.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>
#include <util/strutil.h>
#include <stats/stats_mgr.h>
#include <log/logger.h>
#include <cryptolink/cryptolink.h>
#include <cfgrpt/config_report.h>

#ifdef HAVE_MYSQL
#include <dhcpsrv/mysql_lease_mgr.h>
#endif
#ifdef HAVE_PGSQL
#include <dhcpsrv/pgsql_lease_mgr.h>
#endif
#include <dhcpsrv/memfile_lease_mgr.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <iomanip>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::cryptolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::stats;
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

Dhcpv4Exchange::Dhcpv4Exchange(const AllocEnginePtr& alloc_engine,
                               const Pkt4Ptr& query,
                               const Subnet4Ptr& subnet)
    : alloc_engine_(alloc_engine), query_(query), resp_(),
      context_(new AllocEngine::ClientContext4()) {

    if (!alloc_engine_) {
        isc_throw(BadValue, "alloc_engine value must not be NULL"
                  " when creating an instance of the Dhcpv4Exchange");
    }

    if (!query_) {
        isc_throw(BadValue, "query value must not be NULL when"
                  " creating an instance of the Dhcpv4Exchange");
    }

    // Create response message.
    initResponse();
    // Select subnet for the query message.
    context_->subnet_ = subnet;
    // Hardware address.
    context_->hwaddr_ = query->getHWAddr();
    // Pointer to client's query.
    context_->query_ = query;

    // Set client identifier if the match-client-id flag is enabled (default).
    // If the subnet wasn't found it doesn't matter because we will not be
    // able to allocate a lease anyway so this context will not be used.
    if (subnet) {
        if (subnet->getMatchClientId()) {
            OptionPtr opt_clientid = query->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
            if (opt_clientid) {
                context_->clientid_.reset(new ClientId(opt_clientid->getData()));
            }
        } else {
            /// @todo When merging with #3806 use different logger.
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_CLIENTID_IGNORED_FOR_LEASES)
                .arg(query->getLabel())
                .arg(subnet->getID());
        }
    }
    // Check for static reservations.
    alloc_engine->findReservation(*context_);
};

void
Dhcpv4Exchange::initResponse() {
    uint8_t resp_type = 0;
    switch (getQuery()->getType()) {
    case DHCPDISCOVER:
        resp_type = DHCPOFFER;
        break;
    case DHCPREQUEST:
    case DHCPINFORM:
        resp_type = DHCPACK;
        break;
    default:
        ;
    }
    // Only create a response if one is required.
    if (resp_type > 0) {
        resp_.reset(new Pkt4(resp_type, getQuery()->getTransid()));
        copyDefaultFields();
    }
}

void
Dhcpv4Exchange::copyDefaultFields() {
    resp_->setIface(query_->getIface());
    resp_->setIndex(query_->getIndex());

    // explicitly set this to 0
    resp_->setSiaddr(IOAddress::IPV4_ZERO_ADDRESS());
    // ciaddr is always 0, except for the Renew/Rebind state when it may
    // be set to the ciaddr sent by the client.
    resp_->setCiaddr(IOAddress::IPV4_ZERO_ADDRESS());
    resp_->setHops(query_->getHops());

    // copy MAC address
    resp_->setHWAddr(query_->getHWAddr());

    // relay address
    resp_->setGiaddr(query_->getGiaddr());

    // Let's copy client-id to response. See RFC6842.
    // It is possible to disable RFC6842 to keep backward compatibility
    bool echo = CfgMgr::instance().echoClientId();
    OptionPtr client_id = query_->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (client_id && echo) {
        resp_->addOption(client_id);
    }

    // If src/dest HW addresses are used by the packet filtering class
    // we need to copy them as well. There is a need to check that the
    // address being set is not-NULL because an attempt to set the NULL
    // HW would result in exception. If these values are not set, the
    // the default HW addresses (zeroed) should be generated by the
    // packet filtering class when creating Ethernet header for
    // outgoing packet.
    HWAddrPtr src_hw_addr = query_->getLocalHWAddr();
    if (src_hw_addr) {
        resp_->setLocalHWAddr(src_hw_addr);
    }
    HWAddrPtr dst_hw_addr = query_->getRemoteHWAddr();
    if (dst_hw_addr) {
        resp_->setRemoteHWAddr(dst_hw_addr);
    }

    // If this packet is relayed, we want to copy Relay Agent Info option
    OptionPtr rai = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    if (rai) {
        resp_->addOption(rai);
    }
}

const std::string Dhcpv4Srv::VENDOR_CLASS_PREFIX("VENDOR_CLASS_");

Dhcpv4Srv::Dhcpv4Srv(uint16_t port, const bool use_bcast,
                     const bool direct_response_desired)
    : shutdown_(true), alloc_engine_(), port_(port),
      use_bcast_(use_bcast), hook_index_pkt4_receive_(-1),
      hook_index_subnet4_select_(-1), hook_index_pkt4_send_(-1) {

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_OPEN_SOCKET).arg(port);
    try {
        // Port 0 is used for testing purposes where we don't open broadcast
        // capable sockets. So, set the packet filter handling direct traffic
        // only if we are in non-test mode.
        if (port) {
            // First call to instance() will create IfaceMgr (it's a singleton)
            // it may throw something if things go wrong.
            // The 'true' value of the call to setMatchingPacketFilter imposes
            // that IfaceMgr will try to use the mechanism to respond directly
            // to the client which doesn't have address assigned. This capability
            // may be lacking on some OSes, so there is no guarantee that server
            // will be able to respond directly.
            IfaceMgr::instance().setMatchingPacketFilter(direct_response_desired);
        }

        // Instantiate allocation engine. The number of allocation attempts equal
        // to zero indicates that the allocation engine will use the number of
        // attempts depending on the pool size.
        alloc_engine_.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 0,
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
    try {
        stopD2();
    } catch(const std::exception& ex) {
        // Highly unlikely, but lets Report it but go on
        LOG_ERROR(dhcp4_logger, DHCP4_SRV_D2STOP_ERROR).arg(ex.what());
    }

    IfaceMgr::instance().closeSockets();
}

void
Dhcpv4Srv::shutdown() {
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_SHUTDOWN_REQUEST);
    shutdown_ = true;
}

isc::dhcp::Subnet4Ptr
Dhcpv4Srv::selectSubnet(const Pkt4Ptr& query) const {

    Subnet4Ptr subnet;

    SubnetSelector selector;
    selector.ciaddr_ = query->getCiaddr();
    selector.giaddr_ = query->getGiaddr();
    selector.local_address_ = query->getLocalAddr();
    selector.remote_address_ = query->getRemoteAddr();
    selector.client_classes_ = query->classes_;
    selector.iface_name_ = query->getIface();

    CfgMgr& cfgmgr = CfgMgr::instance();
    subnet = cfgmgr.getCurrentCfg()->getCfgSubnets4()->selectSubnet(selector);

    // Let's execute all callouts registered for subnet4_select
    if (HooksManager::calloutsPresent(hook_index_subnet4_select_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // We're reusing callout_handle from previous calls
        callout_handle->deleteAllArguments();

        // Set new arguments
        callout_handle->setArgument("query4", query);
        callout_handle->setArgument("subnet4", subnet);
        callout_handle->setArgument("subnet4collection",
                                    cfgmgr.getCurrentCfg()->
                                    getCfgSubnets4()->getAll());

        // Call user (and server-side) callouts
        HooksManager::callCallouts(hook_index_subnet4_select_,
                                   *callout_handle);

        // Callouts decided to skip this step. This means that no subnet
        // will be selected. Packet processing will continue, but it will
        // be severely limited (i.e. only global options will be assigned)
        if (callout_handle->getSkip()) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                      DHCP4_HOOK_SUBNET4_SELECT_SKIP)
                .arg(query->getLabel());
            return (Subnet4Ptr());
        }

        // Use whatever subnet was specified by the callout
        callout_handle->getArgument("subnet4", subnet);
    }

    if (subnet) {
        // Log at higher debug level that subnet has been found.
        LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC_DATA, DHCP4_SUBNET_SELECTED)
            .arg(query->getLabel())
            .arg(subnet->getID());
        // Log detailed information about the selected subnet at the
        // lower debug level.
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_SUBNET_DATA)
            .arg(query->getLabel())
            .arg(subnet->toText());

    } else {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL,
                  DHCP4_SUBNET_SELECTION_FAILED)
            .arg(query->getLabel());
    }

    return (subnet);
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
        // client's message and server's response
        Pkt4Ptr query;
        Pkt4Ptr rsp;

        try {
            uint32_t timeout = 1000;
            LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_BUFFER_WAIT).arg(timeout);
            query = receivePacket(timeout);

            // Log if packet has arrived. We can't log the detailed information
            // about the DHCP message because it hasn't been unpacked/parsed
            // yet, and it can't be parsed at this point because hooks will
            // have to process it first. The only information available at this
            // point are: the interface, source address and destination addresses
            // and ports.
            if (query) {
                LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC, DHCP4_BUFFER_RECEIVED)
                    .arg(query->getRemoteAddr().toText())
                    .arg(query->getRemotePort())
                    .arg(query->getLocalAddr().toText())
                    .arg(query->getLocalPort())
                    .arg(query->getIface());

            } else {
                LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_BUFFER_WAIT_INTERRUPTED)
                    .arg(timeout);
            }

        } catch (const SignalInterruptOnSelect) {
            // Packet reception interrupted because a signal has been received.
            // This is not an error because we might have received a SIGTERM,
            // SIGINT, SIGHUP or SIGCHILD which are handled by the server. For
            // signals that are not handled by the server we rely on the default
            // behavior of the system.
            LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_BUFFER_WAIT_SIGNAL)
                .arg(signal_set_->getNext());
        } catch (const std::exception& e) {
            // Log all other errors.
            LOG_ERROR(packet4_logger, DHCP4_BUFFER_RECEIVE_FAIL).arg(e.what());
        }

        // Handle next signal received by the process. It must be called after
        // an attempt to receive a packet to properly handle server shut down.
        // The SIGTERM or SIGINT will be received prior to, or during execution
        // of select() (select is invoked by receivePacket()). When that
        // happens, select will be interrupted. The signal handler will be
        // invoked immediately after select(). The handler will set the
        // shutdown flag and cause the process to terminate before the next
        // select() function is called. If the function was called before
        // receivePacket the process could wait up to the duration of timeout
        // of select() to terminate.
        try {
            handleSignal();
        } catch (const std::exception& e) {
            // Standard exception occurred. Let's be on the safe side to
            // catch std::exception.
            LOG_ERROR(dhcp4_logger, DHCP4_HANDLE_SIGNAL_EXCEPTION)
                .arg(e.what());
        }

        // Timeout may be reached or signal received, which breaks select()
        // with no reception occurred. No need to log anything here because
        // we have logged right after the call to receivePacket().
        if (!query) {
            continue;
        }

        // Log reception of the packet. We need to increase it early, as any
        // failures in unpacking will cause the packet to be dropped. We
        // will increase type specific packets further down the road.
        // See processStatsReceived().
        isc::stats::StatsMgr::instance().addValue("pkt4-received",
                                                  static_cast<int64_t>(1));

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
                LOG_DEBUG(hooks_logger, DBG_DHCP4_DETAIL, DHCP4_HOOK_BUFFER_RCVD_SKIP)
                    .arg(query->getRemoteAddr().toText())
                    .arg(query->getLocalAddr().toText())
                    .arg(query->getIface());
                skip_unpack = true;
            }

            callout_handle->getArgument("query4", query);
        }

        // Unpack the packet information unless the buffer4_receive callouts
        // indicated they did it
        if (!skip_unpack) {
            try {
                LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL, DHCP4_BUFFER_UNPACK)
                    .arg(query->getRemoteAddr().toText())
                    .arg(query->getLocalAddr().toText())
                    .arg(query->getIface());
                query->unpack();
            } catch (const std::exception& e) {
                // Failed to parse the packet.
                LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL,
                          DHCP4_PACKET_DROP_0001)
                    .arg(query->getRemoteAddr().toText())
                    .arg(query->getLocalAddr().toText())
                    .arg(query->getIface())
                    .arg(e.what());

                // Increase the statistics of parse failues and dropped packets.
                isc::stats::StatsMgr::instance().addValue("pkt4-parse-failed",
                                                          static_cast<int64_t>(1));
                isc::stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                          static_cast<int64_t>(1));
                continue;
            }
        }

        // Update statistics accordingly for received packet.
        processStatsReceived(query);

        // Assign this packet to one or more classes if needed. We need to do
        // this before calling accept(), because getSubnet4() may need client
        // class information.
        classifyPacket(query);

        // Check whether the message should be further processed or discarded.
        // There is no need to log anything here. This function logs by itself.
        if (!accept(query)) {
            // Increase the statistic of dropped packets.
            isc::stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                      static_cast<int64_t>(1));
            continue;
        }

        // We have sanity checked (in accept() that the Message Type option
        // exists, so we can safely get it here.
        int type = query->getType();
        LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC_DATA, DHCP4_PACKET_RECEIVED)
            .arg(query->getLabel())
            .arg(query->getName())
            .arg(type)
            .arg(query->getRemoteAddr())
            .arg(query->getLocalAddr())
            .arg(query->getIface());
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_QUERY_DATA)
            .arg(query->getLabel())
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
                LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS, DHCP4_HOOK_PACKET_RCVD_SKIP)
                    .arg(query->getLabel());
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
                rsp = processInform(query);
                break;

            default:
                // Only action is to output a message if debug is enabled,
                // and that is covered by the debug statement before the
                // "switch" statement.
                ;
            }
        } catch (const std::exception& e) {

            // Catch-all exception (we used to call only isc::Exception, but
            // std::exception could potentially be raised and if we don't catch
            // it here, it would be caught in main() and the process would
            // terminate).  Just log the problem and ignore the packet.
            // (The problem is logged as a debug message because debug is
            // disabled by default - it prevents a DDOS attack based on the
            // sending of problem packets.)
            LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_BASIC,
                      DHCP4_PACKET_DROP_0007)
                .arg(query->getLabel())
                .arg(e.what());

            // Increase the statistic of dropped packets.
            isc::stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                      static_cast<int64_t>(1));
        }

        if (!rsp) {
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
                LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS, DHCP4_HOOK_PACKET_SEND_SKIP)
                    .arg(query->getLabel());
                skip_pack = true;
            }
        }

        if (!skip_pack) {
            try {
                LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_PACK)
                    .arg(rsp->getLabel());
                rsp->pack();
            } catch (const std::exception& e) {
                LOG_ERROR(options4_logger, DHCP4_PACKET_PACK_FAIL)
                    .arg(rsp->getLabel())
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
                    LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                              DHCP4_HOOK_BUFFER_SEND_SKIP)
                        .arg(rsp->getLabel());
                    continue;
                }

                callout_handle->getArgument("response4", rsp);
            }

            LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC, DHCP4_PACKET_SEND)
                .arg(rsp->getLabel())
                .arg(rsp->getName())
                .arg(static_cast<int>(rsp->getType()))
                .arg(rsp->getLocalAddr())
                .arg(rsp->getLocalPort())
                .arg(rsp->getRemoteAddr())
                .arg(rsp->getRemotePort())
                .arg(rsp->getIface());

            LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL_DATA,
                      DHCP4_RESPONSE_DATA)
                .arg(rsp->getLabel())
                .arg(rsp->getName())
                .arg(static_cast<int>(rsp->getType()))
                .arg(rsp->toText());
            sendPacket(rsp);

            // Update statistics accordingly for sent packet.
            processStatsSent(rsp);

        } catch (const std::exception& e) {
            LOG_ERROR(packet4_logger, DHCP4_PACKET_SEND_FAIL)
                .arg(rsp->getLabel())
                .arg(e.what());
        }
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
            return (D2Dhcid(lease->hwaddr_, fqdn_wire));
        }
    } catch (const Exception& ex) {
        isc_throw(DhcidComputeError, "unable to compute DHCID: "
                  << ex.what());

    }

}

void
Dhcpv4Srv::appendServerID(Dhcpv4Exchange& ex) {
    // The source address for the outbound message should have been set already.
    // This is the address that to the best of the server's knowledge will be
    // available from the client.
    /// @todo: perhaps we should consider some more sophisticated server id
    /// generation, but for the current use cases, it should be ok.
    OptionPtr opt_srvid(new Option4AddrLst(DHO_DHCP_SERVER_IDENTIFIER,
                                           ex.getResponse()->getLocalAddr()));
    ex.getResponse()->addOption(opt_srvid);
}

void
Dhcpv4Srv::appendRequestedOptions(Dhcpv4Exchange& ex) {
    // Get the subnet relevant for the client. We will need it
    // to get the options associated with it.
    Subnet4Ptr subnet = ex.getContext()->subnet_;
    // If we can't find the subnet for the client there is no way
    // to get the options to be sent to a client. We don't log an
    // error because it will be logged by the assignLease method
    // anyway.
    if (!subnet) {
        return;
    }

    Pkt4Ptr query = ex.getQuery();

    // try to get the 'Parameter Request List' option which holds the
    // codes of requested options.
    OptionUint8ArrayPtr option_prl = boost::dynamic_pointer_cast<
        OptionUint8Array>(query->getOption(DHO_DHCP_PARAMETER_REQUEST_LIST));
    // If there is no PRL option in the message from the client then
    // there is nothing to do.
    if (!option_prl) {
        return;
    }

    Pkt4Ptr resp = ex.getResponse();

    // Get the codes of requested options.
    const std::vector<uint8_t>& requested_opts = option_prl->getValues();
    // For each requested option code get the instance of the option
    // to be returned to the client.
    for (std::vector<uint8_t>::const_iterator opt = requested_opts.begin();
         opt != requested_opts.end(); ++opt) {
        if (!resp->getOption(*opt)) {
            OptionDescriptor desc = subnet->getCfgOption()->get("dhcp4", *opt);
            if (desc.option_) {
                resp->addOption(desc.option_);
            }
        }
    }
}

void
Dhcpv4Srv::appendRequestedVendorOptions(Dhcpv4Exchange& ex) {
    // Get the configured subnet suitable for the incoming packet.
    Subnet4Ptr subnet = ex.getContext()->subnet_;
    // Leave if there is no subnet matching the incoming packet.
    // There is no need to log the error message here because
    // it will be logged in the assignLease() when it fails to
    // pick the suitable subnet. We don't want to duplicate
    // error messages in such case.
    if (!subnet) {
        return;
    }

    // Try to get the vendor option
    boost::shared_ptr<OptionVendor> vendor_req = boost::dynamic_pointer_cast<
        OptionVendor>(ex.getQuery()->getOption(DHO_VIVSO_SUBOPTIONS));
    if (!vendor_req) {
        return;
    }

    uint32_t vendor_id = vendor_req->getVendorId();

    // Let's try to get ORO within that vendor-option
    /// @todo This is very specific to vendor-id=4491 (Cable Labs). Other
    /// vendors may have different policies.
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
            OptionDescriptor desc = subnet->getCfgOption()->get(vendor_id,
                                                                *code);
            if (desc.option_) {
                vendor_rsp->addOption(desc.option_);
                added = true;
            }
        }

        if (added) {
            ex.getResponse()->addOption(vendor_rsp);
        }
    }
}


void
Dhcpv4Srv::appendBasicOptions(Dhcpv4Exchange& ex) {
    // Identify options that we always want to send to the
    // client (if they are configured).
    static const uint16_t required_options[] = {
        DHO_ROUTERS,
        DHO_DOMAIN_NAME_SERVERS,
        DHO_DOMAIN_NAME };

    static size_t required_options_size =
        sizeof(required_options) / sizeof(required_options[0]);

    // Get the subnet.
    Subnet4Ptr subnet = ex.getContext()->subnet_;
    if (!subnet) {
        return;
    }

    Pkt4Ptr resp = ex.getResponse();

    // Try to find all 'required' options in the outgoing
    // message. Those that are not present will be added.
    for (int i = 0; i < required_options_size; ++i) {
        OptionPtr opt = resp->getOption(required_options[i]);
        if (!opt) {
            // Check whether option has been configured.
            OptionDescriptor desc = subnet->getCfgOption()->
                get("dhcp4", required_options[i]);
            if (desc.option_) {
                resp->addOption(desc.option_);
            }
        }
    }
}

void
Dhcpv4Srv::processClientName(Dhcpv4Exchange& ex) {
    // It is possible that client has sent both Client FQDN and Hostname
    // option. In such case, server should prefer Client FQDN option and
    // ignore the Hostname option.
    try {
        Pkt4Ptr resp = ex.getResponse();
        Option4ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<Option4ClientFqdn>
            (ex.getQuery()->getOption(DHO_FQDN));
        if (fqdn) {
            LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL, DHCP4_CLIENT_FQDN_PROCESS)
                .arg(ex.getQuery()->getLabel());
            processClientFqdnOption(ex);

        } else {
            OptionStringPtr hostname = boost::dynamic_pointer_cast<OptionString>
                (ex.getQuery()->getOption(DHO_HOST_NAME));
            if (hostname) {
                LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL, DHCP4_CLIENT_HOSTNAME_PROCESS)
                    .arg(ex.getQuery()->getLabel());
                processHostnameOption(ex);
            }
        }
    } catch (const Exception& e) {
        // In some rare cases it is possible that the client's name processing
        // fails. For example, the Hostname option may be malformed, or there
        // may be an error in the server's logic which would cause multiple
        // attempts to add the same option to the response message. This
        // error message aggregates all these errors so they can be diagnosed
        // from the log. We don't want to throw an exception here because,
        // it will impact the processing of the whole packet. We rather want
        // the processing to continue, even if the client's name is wrong.
        LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_CLIENT_NAME_PROC_FAIL)
            .arg(ex.getQuery()->getLabel())
            .arg(e.what());
    }
}

void
Dhcpv4Srv::processClientFqdnOption(Dhcpv4Exchange& ex) {
    // Obtain the FQDN option from the client's message.
    Option4ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option4ClientFqdn>(ex.getQuery()->getOption(DHO_FQDN));

    LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_CLIENT_FQDN_DATA)
        .arg(ex.getQuery()->getLabel())
        .arg(fqdn->toText());

    // Create the DHCPv4 Client FQDN Option to be included in the server's
    // response to a client.
    Option4ClientFqdnPtr fqdn_resp(new Option4ClientFqdn(*fqdn));

    // Set the server S, N, and O flags based on client's flags and
    // current configuration.
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    d2_mgr.adjustFqdnFlags<Option4ClientFqdn>(*fqdn, *fqdn_resp);

    // Carry over the client's E flag.
    fqdn_resp->setFlag(Option4ClientFqdn::FLAG_E,
                       fqdn->getFlag(Option4ClientFqdn::FLAG_E));

    if (ex.getContext()->host_ && !ex.getContext()->host_->getHostname().empty()) {
        D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
        fqdn_resp->setDomainName(d2_mgr.qualifyName(ex.getContext()->host_->getHostname(),
                                                    true), Option4ClientFqdn::FULL);

    } else {
        // Adjust the domain name based on domain name value and type sent by the
        // client and current configuration.
        d2_mgr.adjustDomainName<Option4ClientFqdn>(*fqdn, *fqdn_resp);
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
    // If we don't store the option in the response message, we will have to
    // propagate it in the different way to the functions which acquire the
    // lease. This would require modifications to the API of this class.
    LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_RESPONSE_FQDN_DATA)
        .arg(ex.getQuery()->getLabel())
        .arg(fqdn_resp->toText());
    ex.getResponse()->addOption(fqdn_resp);
}

void
Dhcpv4Srv::processHostnameOption(Dhcpv4Exchange& ex) {
    // Obtain the Hostname option from the client's message.
    OptionStringPtr opt_hostname = boost::dynamic_pointer_cast<OptionString>
        (ex.getQuery()->getOption(DHO_HOST_NAME));

    LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_CLIENT_HOSTNAME_DATA)
        .arg(ex.getQuery()->getLabel())
        .arg(opt_hostname->getValue());

    // Fetch D2 configuration.
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();

    // Do nothing if the DNS updates are disabled.
    if (!d2_mgr.ddnsEnabled()) {
        return;
    }

    std::string hostname = isc::util::str::trim(opt_hostname->getValue());
    unsigned int label_count = OptionDataTypeUtil::getLabelCount(hostname);
    // The hostname option sent by the client should be at least 1 octet long.
    // If it isn't we ignore this option. (Per RFC 2131, section 3.14)
    /// @todo It would be more liberal to accept this and let it fall into
    /// the case  of replace or less than two below.
    if (label_count == 0) {
        LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_EMPTY_HOSTNAME)
            .arg(ex.getQuery()->getLabel());
        return;
    }
    // Copy construct the hostname provided by the client. It is entirely
    // possible that we will use the hostname option provided by the client
    // to perform the DNS update and we will send the same option to him to
    // indicate that we accepted this hostname.
    OptionStringPtr opt_hostname_resp(new OptionString(*opt_hostname));

    // The hostname option may be unqualified or fully qualified. The lab_count
    // holds the number of labels for the name. The number of 1 means that
    // there is only root label "." (even for unqualified names, as the
    // getLabelCount function treats each name as a fully qualified one).
    // By checking the number of labels present in the hostname we may infer
    // whether client has sent the fully qualified or unqualified hostname.

    // If there is a hostname reservation for this client, use it.
    if (ex.getContext()->host_ && !ex.getContext()->host_->getHostname().empty()) {
        opt_hostname_resp->setValue(d2_mgr.qualifyName(ex.getContext()->host_->getHostname(),
                                                       false));

    } else if ((d2_mgr.getD2ClientConfig()->getReplaceClientName()) ||
               (label_count < 2)) {
        // Set to root domain to signal later on that we should replace it.
        // DHO_HOST_NAME is a string option which cannot be empty.
        /// @todo We may want to reconsider whether it is appropriate for the
        /// client to send a root domain name as a Hostname. There are
        /// also extensions to the auto generation of the client's name,
        /// e.g. conversion to the puny code which may be considered at some point.
        /// For now, we just remain liberal and expect that the DNS will handle
        /// conversion if needed and possible.
        opt_hostname_resp->setValue(".");

    } else if (label_count == 2) {
        // If there are two labels, it means that the client has specified
        // the unqualified name. We have to concatenate the unqualified name
        // with the domain name. The false value passed as a second argument
        // indicates that the trailing dot should not be appended to the
        // hostname. We don't want to append the trailing dot because
        // we don't know whether the hostname is partial or not and some
        // clients do not handle the hostnames with the trailing dot.
        opt_hostname_resp->setValue(d2_mgr.qualifyName(hostname, false));
    }

    LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_RESPONSE_HOSTNAME_DATA)
        .arg(ex.getQuery()->getLabel())
        .arg(opt_hostname_resp->getValue());
    ex.getResponse()->addOption(opt_hostname_resp);
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
        // There will be a NameChangeRequest generated to remove existing
        // DNS entries if the following conditions are met:
        // - The hostname is set for the existing lease, we can't generate
        //   removal request for non-existent hostname.
        // - A server has performed reverse, forward or both updates.
        // - FQDN data between the new and old lease do not match.
        if (!lease->hasIdenticalFqdn(*old_lease)) {
            queueNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, old_lease);

            // If FQDN data from both leases match, there is no need to update.
        } else if (lease->hasIdenticalFqdn(*old_lease)) {
            return;

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
        LOG_ERROR(ddns4_logger, DHCP4_DHCID_COMPUTE_ERROR)
            .arg(lease->toText())
            .arg(ex.what());
        return;
    }

    // Create NameChangeRequest
    NameChangeRequestPtr ncr(new NameChangeRequest(chg_type, lease->fqdn_fwd_,
                                                   lease->fqdn_rev_,
                                                   lease->hostname_,
                                                   lease->addr_.toText(),
                                                   dhcid,
                                                   (lease->cltt_ +
                                                    lease->valid_lft_),
                                                   lease->valid_lft_));

    LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_QUEUE_NCR)
        .arg(chg_type == CHG_ADD ? "add" : "remove")
        .arg(ncr->toText());

    // And pass it to the the manager.
    CfgMgr::instance().getD2ClientMgr().sendRequest(ncr);
}

void
Dhcpv4Srv::assignLease(Dhcpv4Exchange& ex) {
    // Get the pointers to the query and the response messages.
    Pkt4Ptr query = ex.getQuery();
    Pkt4Ptr resp = ex.getResponse();

    // Get the context.
    AllocEngine::ClientContext4Ptr ctx = ex.getContext();

    // Subnet should have been already selected when the context was created.
    Subnet4Ptr subnet = ctx->subnet_;
    if (!subnet) {
        // This particular client is out of luck today. We do not have
        // information about the subnet he is connected to. This likely means
        // misconfiguration of the server (or some relays).

        // Perhaps this should be logged on some higher level?
        LOG_ERROR(bad_packet4_logger, DHCP4_PACKET_NAK_0001)
            .arg(query->getLabel())
            .arg(query->getRemoteAddr().toText())
            .arg(query->getName());
        resp->setType(DHCPNAK);
        resp->setYiaddr(IOAddress::IPV4_ZERO_ADDRESS());
        return;
    }

    // Set up siaddr. Perhaps assignLease is not the best place to call this
    // as siaddr has nothing to do with a lease, but otherwise we would have
    // to select subnet twice (performance hit) or update too many functions
    // at once.
    /// @todo: move subnet selection to a common code
    resp->setSiaddr(subnet->getSiaddr());

    // Get the server identifier. It will be used to determine the state
    // of the client.
    OptionCustomPtr opt_serverid = boost::dynamic_pointer_cast<
        OptionCustom>(query->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Check if the client has sent a requested IP address option or
    // ciaddr.
    OptionCustomPtr opt_requested_address = boost::dynamic_pointer_cast<
        OptionCustom>(query->getOption(DHO_DHCP_REQUESTED_ADDRESS));
    IOAddress hint(IOAddress::IPV4_ZERO_ADDRESS());
    if (opt_requested_address) {
        hint = opt_requested_address->readAddress();

    } else if (!query->getCiaddr().isV4Zero()) {
        hint = query->getCiaddr();

    }

    HWAddrPtr hwaddr = query->getHWAddr();

    // "Fake" allocation is processing of DISCOVER message. We pretend to do an
    // allocation, but we do not put the lease in the database. That is ok,
    // because we do not guarantee that the user will get that exact lease. If
    // the user selects this server to do actual allocation (i.e. sends REQUEST)
    // it should include this hint. That will help us during the actual lease
    // allocation.
    bool fake_allocation = (query->getType() == DHCPDISCOVER);

    // Get client-id. It is not mandatory in DHCPv4.
    ClientIdPtr client_id = ex.getContext()->clientid_;

    // If there is no server id and there is a Requested IP Address option
    // the client is in the INIT-REBOOT state in which the server has to
    // determine whether the client's notion of the address is correct
    // and whether the client is known, i.e., has a lease.
    if (!fake_allocation && !opt_serverid && opt_requested_address) {

        LOG_DEBUG(lease4_logger, DBG_DHCP4_DETAIL, DHCP4_INIT_REBOOT)
            .arg(query->getLabel())
            .arg(hint.toText());

        Lease4Ptr lease;
        if (client_id) {
            lease = LeaseMgrFactory::instance().getLease4(*client_id, subnet->getID());
        }

        if (!lease && hwaddr) {
            lease = LeaseMgrFactory::instance().getLease4(*hwaddr, subnet->getID());
        }

        // Check the first error case: unknown client. We check this before
        // validating the address sent because we don't want to respond if
        // we don't know this client.
        if (!lease || !lease->belongsToClient(hwaddr, client_id)) {
            LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL,
                      DHCP4_NO_LEASE_INIT_REBOOT)
                .arg(query->getLabel())
                .arg(hint.toText());

            ex.deleteResponse();
            return;
        }

        // We know this client so we can now check if his notion of the
        // IP address is correct.
        if (lease && (lease->addr_ != hint)) {
            LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL,
                      DHCP4_PACKET_NAK_0002)
                .arg(query->getLabel())
                .arg(hint.toText());

            resp->setType(DHCPNAK);
            resp->setYiaddr(IOAddress::IPV4_ZERO_ADDRESS());
            return;
        }
    }


    CalloutHandlePtr callout_handle = getCalloutHandle(query);

    std::string hostname;
    bool fqdn_fwd = false;
    bool fqdn_rev = false;
    OptionStringPtr opt_hostname;
    Option4ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option4ClientFqdn>(resp->getOption(DHO_FQDN));
    if (fqdn) {
        hostname = fqdn->getDomainName();
        CfgMgr::instance().getD2ClientMgr().getUpdateDirections(*fqdn,
                                                                fqdn_fwd,
                                                                fqdn_rev);
    } else {
        opt_hostname = boost::dynamic_pointer_cast<OptionString>
            (resp->getOption(DHO_HOST_NAME));

        if (opt_hostname) {
            hostname = opt_hostname->getValue();
            // DHO_HOST_NAME is string option which cannot be blank,
            // we use "." to know we should replace it with a fully
            // generated name. The local string variable needs to be
            // blank in logic below.
            if (hostname == ".") {
                hostname = "";
            }
            /// @todo It could be configurable what sort of updates the
            /// server is doing when Hostname option was sent.
            fqdn_fwd = true;
            fqdn_rev = true;
        }
    }

    // We need to set these values in the context as they haven't been set yet.
    ctx->requested_address_ = hint;
    ctx->fwd_dns_update_ = fqdn_fwd;
    ctx->rev_dns_update_ = fqdn_rev;
    ctx->hostname_ = hostname;
    ctx->fake_allocation_ = fake_allocation;
    ctx->callout_handle_ = callout_handle;

    Lease4Ptr lease = alloc_engine_->allocateLease4(*ctx);

    if (lease) {
        // We have a lease! Let's set it in the packet and send it back to
        // the client.
        LOG_DEBUG(lease4_logger, DBG_DHCP4_BASIC_DATA, fake_allocation?
                  DHCP4_LEASE_ADVERT : DHCP4_LEASE_ALLOC)
            .arg(query->getLabel())
            .arg(lease->addr_.toText());

        resp->setYiaddr(lease->addr_);

        /// @todo The server should check what ciaddr the client has supplied
        /// in ciaddr. Currently the ciaddr is ignored except for the subnet
        /// selection. If the client supplied an invalid address, the server
        /// will also return an invalid address here.
        if (!fake_allocation) {
            // If this is a renewing client it will set a ciaddr which the
            // server may include in the response. If this is a new allocation
            // the client will set ciaddr to 0 and this will also be propagated
            // to the server's resp.
            resp->setCiaddr(query->getCiaddr());
        }

        // If there has been Client FQDN or Hostname option sent, but the
        // hostname is empty, it means that server is responsible for
        // generating the entire hostname for the client. The example of the
        // client's name, generated from the IP address is: host-192-0-2-3.
        if ((fqdn || opt_hostname) && lease->hostname_.empty()) {

            // Note that if we have received the hostname option, rather than
            // Client FQDN the trailing dot is not appended to the generated
            // hostname because some clients don't handle the trailing dot in
            // the hostname. Whether the trailing dot is appended or not is
            // controlled by the second argument to the generateFqdn().
            lease->hostname_ = CfgMgr::instance().getD2ClientMgr()
                .generateFqdn(lease->addr_, static_cast<bool>(fqdn));

            LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL, DHCP4_RESPONSE_HOSTNAME_GENERATE)
                .arg(query->getLabel())
                .arg(lease->hostname_);

            // The operations below are rather safe, but we want to catch
            // any potential exceptions (e.g. invalid lease database backend
            // implementation) and log an error.
            try {
                if (!fake_allocation) {
                    // The lease update should be safe, because the lease should
                    // be already in the database. In most cases the exception
                    // would be thrown if the lease was missing.
                    LeaseMgrFactory::instance().updateLease4(lease);
                }

                // The name update in the option should be also safe,
                // because the generated name is well formed.
                if (fqdn) {
                    fqdn->setDomainName(lease->hostname_,
                                        Option4ClientFqdn::FULL);
                } else if (opt_hostname) {
                    opt_hostname->setValue(lease->hostname_);
                }

            } catch (const Exception& ex) {
                LOG_ERROR(ddns4_logger, DHCP4_NAME_GEN_UPDATE_FAIL)
                    .arg(query->getLabel())
                    .arg(lease->hostname_)
                    .arg(ex.what());
            }
        }

        // IP Address Lease time (type 51)
        OptionPtr opt(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME,
                                       lease->valid_lft_));
        resp->addOption(opt);

        // Subnet mask (type 1)
        resp->addOption(getNetmaskOption(subnet));

        // renewal-timer (type 58)
        if (!subnet->getT1().unspecified()) {
            OptionUint32Ptr t1(new OptionUint32(Option::V4,
                                                DHO_DHCP_RENEWAL_TIME,
                                                subnet->getT1()));
            resp->addOption(t1);
        }

        // rebind timer (type 59)
        if (!subnet->getT2().unspecified()) {
            OptionUint32Ptr t2(new OptionUint32(Option::V4,
                                                DHO_DHCP_REBINDING_TIME,
                                                subnet->getT2()));
            resp->addOption(t2);
        }

        // Create NameChangeRequests if DDNS is enabled and this is a
        // real allocation.
        if (!fake_allocation && CfgMgr::instance().ddnsEnabled()) {
            try {
                LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL, DHCP4_NCR_CREATE)
                    .arg(query->getLabel());
                createNameChangeRequests(lease, ctx->old_lease_);

            } catch (const Exception& ex) {
                LOG_ERROR(ddns4_logger, DHCP4_NCR_CREATION_FAILED)
                    .arg(query->getLabel())
                    .arg(ex.what());
            }
        }

    } else {
        // Allocation engine did not allocate a lease. The engine logged
        // cause of that failure.
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, fake_allocation ?
                  DHCP4_PACKET_NAK_0003 : DHCP4_PACKET_NAK_0004)
            .arg(query->getLabel())
            .arg(query->getCiaddr().toText())
            .arg(opt_requested_address ?
                 opt_requested_address->readAddress().toText() : "(no address)");

        resp->setType(DHCPNAK);
        resp->setYiaddr(IOAddress::IPV4_ZERO_ADDRESS());

        resp->delOption(DHO_FQDN);
        resp->delOption(DHO_HOST_NAME);
    }
}

void
Dhcpv4Srv::adjustIfaceData(Dhcpv4Exchange& ex) {
    adjustRemoteAddr(ex);

    // Initialize the pointers to the client's message and the server's
    // response.
    Pkt4Ptr query = ex.getQuery();
    Pkt4Ptr response = ex.getResponse();

    // For the non-relayed message, the destination port is the client's port.
    // For the relayed message, the server/relay port is a destination.
    // Note that the call to this function may throw if invalid combination
    // of hops and giaddr is found (hops = 0 if giaddr = 0 and hops != 0 if
    // giaddr != 0). The exception will propagate down and eventually cause the
    // packet to be discarded.
    response->setRemotePort(query->isRelayed() ? DHCP4_SERVER_PORT :
                            DHCP4_CLIENT_PORT);


    IOAddress local_addr = query->getLocalAddr();

    // In many cases the query is sent to a broadcast address. This address
    // apears as a local address in the query message. We can't simply copy
    // this address to a response message and use it as a source address.
    // Instead we will need to use the address assigned to the interface
    // on which the query has been received. In other cases, we will just
    // use this address as a source address for the response.
    if (local_addr.isV4Bcast()) {
        SocketInfo sock_info = IfaceMgr::instance().getSocket(*query);
        local_addr = sock_info.addr_;
    }
    // We assume that there is an appropriate socket bound to this address
    // and that the address is correct. This is safe assumption because
    // the local address of the query is set when the query is received.
    // The query sent to an incorrect address wouldn't have been received.
    // However, if socket is closed for this address between the reception
    // of the query and sending a response, the IfaceMgr should detect it
    // and return an error.
    response->setLocalAddr(local_addr);
    // In many cases the query is sent to a broadcast address. This address
    // appears as a local address in the query message. Therefore we can't
    // simply copy local address from the query and use it as a source
    // address for the response. Instead, we have to check what address our
    // socket is bound to and use it as a source address. This operation
    // may throw if for some reason the socket is closed.
    /// @todo Consider an optimization that we use local address from
    /// the query if this address is not broadcast.
    response->setLocalPort(DHCP4_SERVER_PORT);
    response->setIface(query->getIface());
    response->setIndex(query->getIndex());
}

void
Dhcpv4Srv::adjustRemoteAddr(Dhcpv4Exchange& ex) {
    // Initialize the pointers to the client's message and the server's
    // response.
    Pkt4Ptr query = ex.getQuery();
    Pkt4Ptr response = ex.getResponse();

    // The DHCPINFORM is slightly different than other messages in a sense
    // that the server should always unicast the response to the ciaddr.
    // It appears however that some clients don't set the ciaddr. We still
    // want to provision these clients and we do what we can't to send the
    // packet to the address where client can receive it.
    if (query->getType() == DHCPINFORM) {
        // If client adheres to RFC2131 it will set the ciaddr and in this
        // case we always unicast our response to this address.
        if (!query->getCiaddr().isV4Zero()) {
            response->setRemoteAddr(query->getCiaddr());

        // If we received DHCPINFORM via relay and the ciaddr is not set we
        // will try to send the response via relay. The caveat is that the
        // relay will not have any idea where to forward the packet because
        // the yiaddr is likely not set. So, the broadcast flag is set so
        // as the response may be broadcast.
        } else if (query->isRelayed()) {
            response->setRemoteAddr(query->getGiaddr());
            response->setFlags(response->getFlags() | BOOTP_BROADCAST);

        // If there is no ciaddr and no giaddr the only thing we can do is
        // to use the source address of the packet.
        } else {
            response->setRemoteAddr(query->getRemoteAddr());
        }
        // Remote address is now set so return.
        return;
    }

    // If received relayed message, server responds to the relay address.
    if (query->isRelayed()) {
        // The client should set the ciaddr when sending the DHCPINFORM
        // but in case he didn't, the relay may not be able to determine the
        // address of the client, because yiaddr is not set when responding
        // to Confirm and the only address available was the source address
        // of the client. The source address is however not used here because
        // the message is relayed. Therefore, we set the BROADCAST flag so
        // as the relay can broadcast the packet.
        if ((query->getType() == DHCPINFORM) &&
            query->getCiaddr().isV4Zero()) {
            response->setFlags(BOOTP_BROADCAST);
        }
        response->setRemoteAddr(query->getGiaddr());

    // If giaddr is 0 but client set ciaddr, server should unicast the
    // response to ciaddr.
    } else if (!query->getCiaddr().isV4Zero()) {
        response->setRemoteAddr(query->getCiaddr());

    // We can't unicast the response to the client when sending NAK,
    // because we haven't allocated address for him. Therefore,
    // NAK is broadcast.
    } else if (response->getType() == DHCPNAK) {
        response->setRemoteAddr(IOAddress::IPV4_BCAST_ADDRESS());

    // If yiaddr is set it means that we have created a lease for a client.
    } else if (!response->getYiaddr().isV4Zero()) {
        // If the broadcast bit is set in the flags field, we have to
        // send the response to broadcast address. Client may have requested it
        // because it doesn't support reception of messages on the interface
        // which doesn't have an address assigned. The other case when response
        // must be broadcasted is when our server does not support responding
        // directly to a client without address assigned.
        const bool bcast_flag = ((query->getFlags() & Pkt4::FLAG_BROADCAST_MASK) != 0);
        if (!IfaceMgr::instance().isDirectResponseSupported() || bcast_flag) {
            response->setRemoteAddr(IOAddress::IPV4_BCAST_ADDRESS());

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
        response->setRemoteAddr(query->getRemoteAddr());

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

    Dhcpv4Exchange ex(alloc_engine_, discover, selectSubnet(discover));

    // If DHCPDISCOVER message contains the FQDN or Hostname option, server
    // may respond to the client with the appropriate FQDN or Hostname
    // option to indicate that whether it will take responsibility for
    // updating DNS when the client sends DHCPREQUEST message.
    processClientName(ex);

    assignLease(ex);

    if (!ex.getResponse()) {
        // The offer is empty so return it *now*!
        return (Pkt4Ptr());
    }

    // Adding any other options makes sense only when we got the lease.
    if (!ex.getResponse()->getYiaddr().isV4Zero()) {
        appendRequestedOptions(ex);
        appendRequestedVendorOptions(ex);
        // There are a few basic options that we always want to
        // include in the response. If client did not request
        // them we append them for him.
        appendBasicOptions(ex);

    } else {
        // If the server can't offer an address, it drops the packet.
        return (Pkt4Ptr());

    }

    // Set the src/dest IP address, port and interface for the outgoing
    // packet.
    adjustIfaceData(ex);

    appendServerID(ex);

    /// @todo: decide whether we want to add a new hook point for
    /// doing class specific processing.
    if (!classSpecificProcessing(ex)) {
        /// @todo add more verbosity here
        LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL, DHCP4_DISCOVER_CLASS_PROCESSING_FAILED)
            .arg(discover->getLabel());
    }

    return (ex.getResponse());
}

Pkt4Ptr
Dhcpv4Srv::processRequest(Pkt4Ptr& request) {
    /// @todo Uncomment this (see ticket #3116)
    /// sanityCheck(request, MANDATORY);

    Dhcpv4Exchange ex(alloc_engine_, request, selectSubnet(request));

    // If DHCPREQUEST message contains the FQDN or Hostname option, server
    // should respond to the client with the appropriate FQDN or Hostname
    // option to indicate if it takes responsibility for the DNS updates.
    // This is performed by the function below.
    processClientName(ex);

    // Note that we treat REQUEST message uniformly, regardless if this is a
    // first request (requesting for new address), renewing existing address
    // or even rebinding.
    assignLease(ex);

    if (!ex.getResponse()) {
        // The ack is empty so return it *now*!
        return (Pkt4Ptr());
    }

    // Adding any other options makes sense only when we got the lease.
    if (!ex.getResponse()->getYiaddr().isV4Zero()) {
        appendRequestedOptions(ex);
        appendRequestedVendorOptions(ex);
        // There are a few basic options that we always want to
        // include in the response. If client did not request
        // them we append them for him.
        appendBasicOptions(ex);
    }

    // Set the src/dest IP address, port and interface for the outgoing
    // packet.
    adjustIfaceData(ex);

    appendServerID(ex);

    /// @todo: decide whether we want to add a new hook point for
    /// doing class specific processing.
    if (!classSpecificProcessing(ex)) {
        /// @todo add more verbosity here
        LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL, DHCP4_REQUEST_CLASS_PROCESSING_FAILED)
            .arg(ex.getQuery()->getLabel());
    }

    return (ex.getResponse());
}

void
Dhcpv4Srv::processRelease(Pkt4Ptr& release) {
    /// @todo Uncomment this (see ticket #3116)
    /// sanityCheck(release, MANDATORY);

    // Try to find client-id. Note that for the DHCPRELEASE we don't check if the
    // match-client-id configuration parameter is disabled because this parameter
    // is configured for subnets and we don't select subnet for the DHCPRELEASE.
    // Bogus clients usually generate new client identifiers when they first
    // connect to the network, so whatever client identifier has been used to
    // acquire the lease, the client identifier carried in the DHCPRELEASE is
    // likely to be the same and the lease will be correctly identified in the
    // lease database. If supplied client identifier differs from the one used
    // to acquire the lease then the lease will remain in the database and
    // simply expire.
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
            LOG_DEBUG(lease4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_NO_LEASE)
                .arg(release->getLabel())
                .arg(release->getCiaddr().toText());
            return;
        }

        if (!lease->belongsToClient(release->getHWAddr(), client_id)) {
            LOG_DEBUG(lease4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_WRONG_CLIENT)
                .arg(release->getLabel())
                .arg(release->getCiaddr().toText());
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
                LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                          DHCP4_HOOK_LEASE4_RELEASE_SKIP)
                    .arg(release->getLabel());
            }
        }

        // Callout didn't indicate to skip the release process. Let's release
        // the lease.
        if (!skip) {
            bool success = LeaseMgrFactory::instance().deleteLease(lease->addr_);

            if (success) {
                // Release successful
                LOG_DEBUG(lease4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE)
                    .arg(release->getLabel())
                    .arg(lease->addr_.toText());

                // Need to decrease statistic for assigned addresses.
                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", lease->subnet_id_, "assigned-addresses"),
                    static_cast<int64_t>(-1));

                if (CfgMgr::instance().ddnsEnabled()) {
                    // Remove existing DNS entries for the lease, if any.
                    queueNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, lease);
                }
            } else {
                // Release failed
                LOG_ERROR(lease4_logger, DHCP4_RELEASE_FAIL)
                    .arg(release->getLabel())
                    .arg(lease->addr_.toText());
            }
        }
    } catch (const isc::Exception& ex) {
        LOG_ERROR(lease4_logger, DHCP4_RELEASE_EXCEPTION)
            .arg(release->getLabel())
            .arg(release->getCiaddr())
            .arg(ex.what());
    }
}

void
Dhcpv4Srv::processDecline(Pkt4Ptr& decline) {

    // Server-id is mandatory in DHCPDECLINE (see table 5, RFC2131)
    /// @todo Uncomment this (see ticket #3116)
    // sanityCheck(decline, MANDATORY);

    // Client is supposed to specify the address being declined in
    // Requested IP address option, but must not set its ciaddr.
    // (again, see table 5 in RFC2131).

    OptionCustomPtr opt_requested_address = boost::dynamic_pointer_cast<
        OptionCustom>(decline->getOption(DHO_DHCP_REQUESTED_ADDRESS));
    if (!opt_requested_address) {

        isc_throw(RFCViolation, "Mandatory 'Requested IP address' option missing"
                  "in DHCPDECLINE sent from " << decline->getLabel());
    }
    IOAddress addr(opt_requested_address->readAddress());

    // We could also extract client's address from ciaddr, but that's clearly
    // against RFC2131.

    // Now we need to check whether this address really belongs to the client
    // that attempts to decline it.
    const Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(addr);

    if (!lease) {
        // Client tried to decline an address, but we don't have a lease for
        // that address. Let's ignore it.
        //
        // We could assume that we're recovering from a mishandled migration
        // to a new server and mark the address as declined, but the window of
        // opportunity for that to be useful is small and the attack vector
        // would be pretty severe.
        LOG_WARN(dhcp4_logger, DHCP4_DECLINE_LEASE_NOT_FOUND)
            .arg(addr.toText()).arg(decline->getLabel());
        return;
    }

    // Get client-id, if available.
    OptionPtr opt_clientid = decline->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    ClientIdPtr client_id;
    if (opt_clientid) {
        client_id.reset(new ClientId(opt_clientid->getData()));
    }

    // Check if the client attempted to decline a lease it doesn't own.
    if (!lease->belongsToClient(decline->getHWAddr(), client_id)) {

        // Get printable hardware addresses
        string client_hw = decline->getHWAddr() ?
            decline->getHWAddr()->toText(false) : "(none)";
        string lease_hw = lease->hwaddr_ ?
            lease->hwaddr_->toText(false) : "(none)";

        // Get printable client-ids
        string client_id_txt = client_id ? client_id->toText() : "(none)";
        string lease_id_txt = lease->client_id_ ?
            lease->client_id_->toText() : "(none)";

        // Print the warning and we're done here.
        LOG_WARN(dhcp4_logger, DHCP4_DECLINE_LEASE_MISMATCH)
            .arg(addr.toText()).arg(decline->getLabel())
            .arg(client_hw).arg(lease_hw).arg(client_id_txt).arg(lease_id_txt);

        return;
    }

    // Ok, all is good. The client is reporting its own address. Let's
    // process it.
    declineLease(lease, decline->getLabel());
}

void
Dhcpv4Srv::declineLease(const Lease4Ptr& lease, const std::string& descr) {

    // Clean up DDNS, if needed.
    if (CfgMgr::instance().ddnsEnabled()) {
        // Remove existing DNS entries for the lease, if any.
        // queueNameChangeRequest will do the necessary checks and will
        // skip the update, if not needed.
        queueNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, lease);
    }

    // Bump up the statistics.

    // Per subnet declined addresses counter.
    StatsMgr::instance().addValue(
        StatsMgr::generateName("subnet", lease->subnet_id_, "declined-addresses"),
        static_cast<int64_t>(1));

    // Global declined addresses counter.
    StatsMgr::instance().addValue("declined-addresses", static_cast<int64_t>(1));

    // We do not want to decrease the assigned-addresses at this time. While
    // technically a declined address is no longer allocated, the primary usage
    // of the assigned-addresses statistic is to monitor pool utilization. Most
    // people would forget to include declined-addresses in the calculation,
    // and simply do assigned-addresses/total-addresses. This would have a bias
    // towards under-representing pool utilization, if we decreased allocated
    // immediately after receiving DHCPDECLINE, rather than later when we recover
    // the address.

    // @todo: Call hooks.

    // We need to disassociate the lease from the client. Once we move a lease
    // to declined state, it is no longer associated with the client in any
    // way.
    lease->decline(CfgMgr::instance().getCurrentCfg()->getDeclinePeriod());

    LeaseMgrFactory::instance().updateLease4(lease);

    LOG_INFO(dhcp4_logger, DHCP4_DECLINE_LEASE).arg(lease->addr_.toText())
        .arg(descr).arg(lease->valid_lft_);
}

Pkt4Ptr
Dhcpv4Srv::processInform(Pkt4Ptr& inform) {
    // DHCPINFORM MUST not include server identifier.
    sanityCheck(inform, FORBIDDEN);

    Dhcpv4Exchange ex(alloc_engine_, inform, selectSubnet(inform));

    Pkt4Ptr ack = ex.getResponse();

    appendRequestedOptions(ex);
    appendRequestedVendorOptions(ex);
    appendBasicOptions(ex);
    adjustIfaceData(ex);

    // There are cases for the DHCPINFORM that the server receives it via
    // relay but will send the response to the client's unicast address
    // carried in the ciaddr. In this case, the giaddr and hops field should
    // be cleared (these fields were copied by the copyDefaultFields function).
    // Also Relay Agent Options should be removed if present.
    if (ack->getRemoteAddr() != inform->getGiaddr()) {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_INFORM_DIRECT_REPLY)
            .arg(inform->getLabel())
            .arg(ack->getRemoteAddr())
            .arg(ack->getIface());
        ack->setHops(0);
        ack->setGiaddr(IOAddress::IPV4_ZERO_ADDRESS());
        ack->delOption(DHO_DHCP_AGENT_OPTIONS);
    }

    // The DHCPACK must contain server id.
    appendServerID(ex);

    /// @todo: decide whether we want to add a new hook point for
    /// doing class specific processing.
    if (!classSpecificProcessing(ex)) {
        LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL,
                  DHCP4_INFORM_CLASS_PROCESSING_FAILED)
            .arg(inform->getLabel());
    }

    return (ex.getResponse());
}

bool
Dhcpv4Srv::accept(const Pkt4Ptr& query) const {
    // Check that the message type is accepted by the server. We rely on the
    // function called to log a message if needed.
    if (!acceptMessageType(query)) {
        return (false);
    }
    // Check if the message from directly connected client (if directly
    // connected) should be dropped or processed.
    if (!acceptDirectRequest(query)) {
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0002)
            .arg(query->getLabel())
            .arg(query->getIface());
        return (false);
    }

    // Check if the DHCPv4 packet has been sent to us or to someone else.
    // If it hasn't been sent to us, drop it!
    if (!acceptServerId(query)) {
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0003)
            .arg(query->getLabel())
            .arg(query->getIface());
        return (false);
    }

    return (true);
}

bool
Dhcpv4Srv::acceptDirectRequest(const Pkt4Ptr& pkt) const {
    // Accept all relayed messages.
    if (pkt->isRelayed()) {
        return (true);
    }
    // The source address must not be zero for the DHCPINFORM message from
    // the directly connected client because the server will not know where
    // to respond if the ciaddr was not present.
    try {
        if (pkt->getType() == DHCPINFORM) {
            if (pkt->getRemoteAddr().isV4Zero() &&
                pkt->getCiaddr().isV4Zero()) {
                return (false);
            }
        }
    } catch (...) {
        // If we got here, it is probably because the message type hasn't
        // been set. But, this should not really happen assuming that
        // we validate the message type prior to calling this function.
        return (false);
    }
    return (!pkt->getLocalAddr().isV4Bcast() || selectSubnet(pkt));
}

bool
Dhcpv4Srv::acceptMessageType(const Pkt4Ptr& query) const {
    // When receiving a packet without message type option, getType() will
    // throw.
    int type;
    try {
        type = query->getType();

    } catch (...) {
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0004)
            .arg(query->getLabel())
            .arg(query->getIface());
        return (false);
    }

    // If we receive a message with a non-existing type, we are logging it.
    if (type > DHCPLEASEQUERYDONE) {
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0005)
            .arg(query->getLabel())
            .arg(type);
        return (false);
    }

    // Once we know that the message type is within a range of defined DHCPv4
    // messages, we do a detailed check to make sure that the received message
    // is targeted at server. Note that we could have received some Offer
    // message broadcasted by the other server to a relay. Even though, the
    // server would rather unicast its response to a relay, let's be on the
    // safe side. Also, we want to drop other messages which we don't support.
    // All these valid messages that we are not going to process are dropped
    // silently.
    if ((type != DHCPDISCOVER) && (type != DHCPREQUEST) &&
        (type != DHCPRELEASE) && (type != DHCPDECLINE) &&
        (type != DHCPINFORM)) {
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0006)
            .arg(query->getLabel())
            .arg(type);
        return (false);
    }

    return (true);
}

bool
Dhcpv4Srv::acceptServerId(const Pkt4Ptr& query) const {
    // This function is meant to be called internally by the server class, so
    // we rely on the caller to sanity check the pointer and we don't check
    // it here.

    // Check if server identifier option is present. If it is not present
    // we accept the message because it is targeted to all servers.
    // Note that we don't check cases that server identifier is mandatory
    // but not present. This is meant to be sanity checked in other
    // functions.
    OptionPtr option = query->getOption(DHO_DHCP_SERVER_IDENTIFIER);
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
Dhcpv4Srv::sanityCheck(const Pkt4Ptr& query, RequirementLevel serverid) {
    OptionPtr server_id = query->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    switch (serverid) {
    case FORBIDDEN:
        if (server_id) {
            isc_throw(RFCViolation, "Server-id option was not expected, but "
                      << "received in "
                      << query->getName());
        }
        break;

    case MANDATORY:
        if (!server_id) {
            isc_throw(RFCViolation, "Server-id option was expected, but not "
                      " received in message "
                      << query->getName());
        }
        break;

    case OPTIONAL:
        // do nothing here
        ;
    }

    // If there is HWAddress set and it is non-empty, then we're good
    if (query->getHWAddr() && !query->getHWAddr()->hwaddr_.empty()) {
        return;
    }

    // There has to be something to uniquely identify the client:
    // either non-zero MAC address or client-id option present (or both)
    OptionPtr client_id = query->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

    // If there's no client-id (or a useless one is provided, i.e. 0 length)
    if (!client_id || client_id->len() == client_id->getHeaderLen()) {
        isc_throw(RFCViolation, "Missing or useless client-id and no HW address "
                  " provided in message "
                  << query->getName());
    }
}

size_t
Dhcpv4Srv::unpackOptions(const OptionBuffer& buf,
                         const std::string& option_space,
                         isc::dhcp::OptionCollection& options) {
    size_t offset = 0;

    OptionDefContainer option_defs;
    if (option_space == "dhcp4") {
        // Get the list of standard option definitions.
        option_defs = LibDHCP::getOptionDefs(Option::V4);
    } else if (!option_space.empty()) {
        OptionDefContainerPtr option_defs_ptr = CfgMgr::instance()
            .getCurrentCfg()->getCfgOptionDef()->getAll(option_space);
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

        if (offset + 1 > buf.size()) {
            // opt_type must be cast to integer so as it is not treated as
            // unsigned char value (a number is presented in error message).
            isc_throw(OutOfRange, "Attempt to parse truncated option "
                      << static_cast<int>(opt_type));
        }

        uint8_t opt_len =  buf[offset++];
        if (offset + opt_len > buf.size()) {

            // We peeked at the option header of the next option, but discovered
            // that it would end up beyond buffer end, so the option is
            // truncated. Hence we can't parse it. Therefore we revert
            // back by two bytes (as if we never parsed them).
            return (offset - 2);

            // isc_throw(OutOfRange, "Option parse failed. Tried to parse "
            //          << offset + opt_len << " bytes from " << buf.size()
            //          << "-byte long buffer.");
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
        pkt->addClass(VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_MODEM);
        classes += string(VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_MODEM) + " ";
    } else
    if (vendor_class->getValue().find(DOCSIS3_CLASS_EROUTER) != std::string::npos) {
        pkt->addClass(VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_EROUTER);
        classes += string(VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_EROUTER) + " ";
    } else {
        classes += VENDOR_CLASS_PREFIX + vendor_class->getValue();
        pkt->addClass(VENDOR_CLASS_PREFIX + vendor_class->getValue());
    }

    if (!classes.empty()) {
        LOG_DEBUG(options4_logger, DBG_DHCP4_BASIC, DHCP4_CLASS_ASSIGNED)
            .arg(pkt->getLabel())
            .arg(classes);
    }
}

bool
Dhcpv4Srv::classSpecificProcessing(const Dhcpv4Exchange& ex) {

    Subnet4Ptr subnet = ex.getContext()->subnet_;
    Pkt4Ptr query = ex.getQuery();
    Pkt4Ptr rsp = ex.getResponse();

    // If any of those is missing, there is nothing to do.
    if (!subnet || !query || !rsp) {
        return (true);
    }

    if (query->inClass(VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_MODEM)) {

        // Set next-server. This is TFTP server address. Cable modems will
        // download their configuration from that server.
        rsp->setSiaddr(subnet->getSiaddr());

        // Now try to set up file field in DHCPv4 packet. We will just copy
        // content of the boot-file option, which contains the same information.
        OptionDescriptor desc = subnet->getCfgOption()->
            get("dhcp4", DHO_BOOT_FILE_NAME);

        if (desc.option_) {
            boost::shared_ptr<OptionString> boot =
                boost::dynamic_pointer_cast<OptionString>(desc.option_);
            if (boot) {
                std::string filename = boot->getValue();
                rsp->setFile((const uint8_t*)filename.c_str(), filename.size());
            }
        }
    }

    if (query->inClass(VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_EROUTER)) {

        // Do not set TFTP server address for eRouter devices.
        rsp->setSiaddr(IOAddress::IPV4_ZERO_ADDRESS());
    }

    return (true);
}

void
Dhcpv4Srv::startD2() {
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    if (d2_mgr.ddnsEnabled()) {
        // Updates are enabled, so lets start the sender, passing in
        // our error handler.
        // This may throw so wherever this is called needs to ready.
        d2_mgr.startSender(boost::bind(&Dhcpv4Srv::d2ClientErrorHandler,
                                       this, _1, _2));
    }
}

void
Dhcpv4Srv::stopD2() {
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    if (d2_mgr.ddnsEnabled()) {
        // Updates are enabled, so lets stop the sender
        d2_mgr.stopSender();
    }
}

void
Dhcpv4Srv::d2ClientErrorHandler(const
                                dhcp_ddns::NameChangeSender::Result result,
                                dhcp_ddns::NameChangeRequestPtr& ncr) {
    LOG_ERROR(ddns4_logger, DHCP4_DDNS_REQUEST_SEND_FAILED).
              arg(result).arg((ncr ? ncr->toText() : " NULL "));
    // We cannot communicate with kea-dhcp-ddns, suspend further updates.
    /// @todo We may wish to revisit this, but for now we will simply turn
    /// them off.
    CfgMgr::instance().getD2ClientMgr().suspendUpdates();
}

// Refer to config_report so it will be embedded in the binary
const char* const* dhcp4_config_report = isc::detail::config_report;

std::string
Dhcpv4Srv::getVersion(bool extended) {
    std::stringstream tmp;

    tmp << VERSION;
    if (extended) {
        tmp << endl << EXTENDED_VERSION << endl;
        tmp << "linked with:" << endl;
        tmp << Logger::getVersion() << endl;
        tmp << CryptoLink::getVersion() << endl;
        tmp << "database:" << endl;
#ifdef HAVE_MYSQL
        tmp << MySqlLeaseMgr::getDBVersion() << endl;
#endif
#ifdef HAVE_PGSQL
        tmp << PgSqlLeaseMgr::getDBVersion() << endl;
#endif
        tmp << Memfile_LeaseMgr::getDBVersion();

        // @todo: more details about database runtime
    }

    return (tmp.str());
}

void Dhcpv4Srv::processStatsReceived(const Pkt4Ptr& query) {
    // Note that we're not bumping pkt4-received statistic as it was
    // increased early in the packet reception code.

    string stat_name = "pkt4-unknown-received";
    try {
        switch (query->getType()) {
        case DHCPDISCOVER:
            stat_name = "pkt4-discover-received";
            break;
        case DHCPOFFER:
            // Should not happen, but let's keep a counter for it
            stat_name = "pkt4-offer-received";
            break;
        case DHCPREQUEST:
            stat_name = "pkt4-request-received";
            break;
        case DHCPACK:
            // Should not happen, but let's keep a counter for it
            stat_name = "pkt4-ack-received";
            break;
        case DHCPNAK:
            // Should not happen, but let's keep a counter for it
            stat_name = "pkt4-nak-received";
            break;
        case DHCPRELEASE:
            stat_name = "pkt4-release-received";
        break;
        case DHCPDECLINE:
            stat_name = "pkt4-decline-received";
            break;
        case DHCPINFORM:
            stat_name = "pkt4-inform-received";
            break;
        default:
            ; // do nothing
        }
    }
    catch (...) {
        // If the incoming packet doesn't have option 53 (message type)
        // or a hook set pkt4_receive_skip, then Pkt4::getType() may
        // throw an exception. That's ok, we'll then use the default
        // name of pkt4-unknown-received.
    }

    isc::stats::StatsMgr::instance().addValue(stat_name,
                                              static_cast<int64_t>(1));
}

void Dhcpv4Srv::processStatsSent(const Pkt4Ptr& response) {
    // Increase generic counter for sent packets.
    isc::stats::StatsMgr::instance().addValue("pkt4-sent",
                                              static_cast<int64_t>(1));

    // Increase packet type specific counter for packets sent.
    string stat_name;
    switch (response->getType()) {
    case DHCPOFFER:
        stat_name = "pkt4-offer-sent";
        break;
    case DHCPACK:
        stat_name = "pkt4-ack-sent";
        break;
    case DHCPNAK:
        stat_name = "pkt4-nak-sent";
        break;
    default:
        // That should never happen
        return;
    }

    isc::stats::StatsMgr::instance().addValue(stat_name,
                                              static_cast<int64_t>(1));
}

}   // namespace dhcp
}   // namespace isc
