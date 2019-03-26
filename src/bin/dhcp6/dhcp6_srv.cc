// Copyright (C) 2011-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <kea_version.h>

#include <asiolink/io_address.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcp/dhcp6.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/duid.h>
#include <dhcp/duid_factory.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/option6_pdexclude.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt6.h>
#include <dhcp6/dhcp6to4_ipc.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcpsrv/cfg_host_operations.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/ncr_generator.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_selector.h>
#include <dhcpsrv/utils.h>
#include <eval/evaluate.h>
#include <eval/eval_messages.h>
#include <exceptions/exceptions.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_log.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>

#include <util/encode/hex.h>
#include <util/io_utilities.h>
#include <util/pointer_util.h>
#include <util/range_utilities.h>
#include <log/logger.h>
#include <cryptolink/cryptolink.h>
#include <cfgrpt/config_report.h>

#ifdef HAVE_MYSQL
#include <dhcpsrv/mysql_lease_mgr.h>
#endif
#ifdef HAVE_PGSQL
#include <dhcpsrv/pgsql_lease_mgr.h>
#endif
#ifdef HAVE_CQL
#include <dhcpsrv/cql_lease_mgr.h>
#endif
#include <dhcpsrv/memfile_lease_mgr.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>

#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::cryptolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::stats;
using namespace isc::util;
using namespace std;

namespace {

/// Structure that holds registered hook indexes
struct Dhcp6Hooks {
    int hook_index_buffer6_receive_;  ///< index for "buffer6_receive" hook point
    int hook_index_pkt6_receive_;     ///< index for "pkt6_receive" hook point
    int hook_index_subnet6_select_;   ///< index for "subnet6_select" hook point
    int hook_index_leases6_committed_;///< index for "leases6_committed" hook point
    int hook_index_lease6_release_;   ///< index for "lease6_release" hook point
    int hook_index_pkt6_send_;        ///< index for "pkt6_send" hook point
    int hook_index_buffer6_send_;     ///< index for "buffer6_send" hook point
    int hook_index_lease6_decline_;   ///< index for "lease6_decline" hook point
    int hook_index_host6_identifier_; ///< index for "host6_identifier" hook point

    /// Constructor that registers hook points for DHCPv6 engine
    Dhcp6Hooks() {
        hook_index_buffer6_receive_   = HooksManager::registerHook("buffer6_receive");
        hook_index_pkt6_receive_      = HooksManager::registerHook("pkt6_receive");
        hook_index_subnet6_select_    = HooksManager::registerHook("subnet6_select");
        hook_index_leases6_committed_ = HooksManager::registerHook("leases6_committed");
        hook_index_lease6_release_    = HooksManager::registerHook("lease6_release");
        hook_index_pkt6_send_         = HooksManager::registerHook("pkt6_send");
        hook_index_buffer6_send_      = HooksManager::registerHook("buffer6_send");
        hook_index_lease6_decline_    = HooksManager::registerHook("lease6_decline");
        hook_index_host6_identifier_  = HooksManager::registerHook("host6_identifier");
    }
};

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
Dhcp6Hooks Hooks;

/// @brief Creates instance of the Status Code option.
///
/// This variant of the function is used when the Status Code option
/// is added as a top-level option. It logs the debug message and
/// includes the information about the client and transaction.
///
/// @param pkt Reference to the client's message.
/// @param status_code Numeric status code.
/// @param status_message Status message.
///
/// @return Pointer to the Status Code option.
OptionPtr
createStatusCode(const Pkt6& pkt, const uint16_t status_code,
                 const std::string& status_message) {
    Option6StatusCodePtr option_status(new Option6StatusCode(status_code,
                                                             status_message));
    LOG_DEBUG(options6_logger, DBG_DHCP6_DETAIL, DHCP6_ADD_GLOBAL_STATUS_CODE)
        .arg(pkt.getLabel())
        .arg(option_status->dataToText());
    return (option_status);
}

/// @brief Creates instance of the Status Code option.
///
/// This variant of the function is used when the Status Code option
/// is added to one of the IA options. It logs the debug message and
/// includes the information about the client and transaction as well
/// as IAID of the IA option.
///
/// @param pkt Reference to the client's message.
/// param ia Reference to the IA option to which the Status Code is
/// being added.
/// @param status_code Numeric status code.
/// @param status_message Status message.
///
/// @return Pointer to the Status Code option.
OptionPtr
createStatusCode(const Pkt6& pkt, const Option6IA& ia, const uint16_t status_code,
                 const std::string& status_message) {
    Option6StatusCodePtr option_status(new Option6StatusCode(status_code,
                                                             status_message));
    LOG_DEBUG(options6_logger, DBG_DHCP6_DETAIL, DHCP6_ADD_STATUS_CODE_FOR_IA)
        .arg(pkt.getLabel())
        .arg(ia.getIAID())
        .arg(option_status->dataToText());
    return (option_status);
}

}; // anonymous namespace

namespace isc {
namespace dhcp {

const std::string Dhcpv6Srv::VENDOR_CLASS_PREFIX("VENDOR_CLASS_");

Dhcpv6Srv::Dhcpv6Srv(uint16_t server_port, uint16_t client_port)
    : io_service_(new IOService()), server_port_(server_port),
      client_port_(client_port), serverid_(), shutdown_(true),
      alloc_engine_(), name_change_reqs_(),
      network_state_(new NetworkState(NetworkState::DHCPv6)),
      cb_control_(new CBControlDHCPv6()) {
    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_OPEN_SOCKET)
        .arg(server_port);

    Dhcp6to4Ipc::instance().client_port = client_port;

    // Initialize objects required for DHCP server operation.
    try {
        // Port 0 is used for testing purposes where in most cases we don't
        // rely on the physical interfaces. Therefore, it should be possible
        // to create an object even when there are no usable interfaces.
        if ((server_port > 0) && (IfaceMgr::instance().countIfaces() == 0)) {
            LOG_ERROR(dhcp6_logger, DHCP6_NO_INTERFACES);
            return;
        }

        // Create a DUID instance but do not store it into a file.
        DUIDFactory duid_factory;
        DuidPtr duid = duid_factory.get();
        serverid_.reset(new Option(Option::V6, D6O_SERVERID, duid->getDuid()));

        // Instantiate allocation engine. The number of allocation attempts equal
        // to zero indicates that the allocation engine will use the number of
        // attempts depending on the pool size.
        alloc_engine_.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 0));

        /// @todo call loadLibraries() when handling configuration changes

    } catch (const std::exception &e) {
        LOG_ERROR(dhcp6_logger, DHCP6_SRV_CONSTRUCT_ERROR).arg(e.what());
        return;
    }

    // All done, so can proceed
    shutdown_ = false;
}

Dhcpv6Srv::~Dhcpv6Srv() {
    discardPackets();
    try {
        stopD2();
    } catch(const std::exception& ex) {
        // Highly unlikely, but lets Report it but go on
        LOG_ERROR(dhcp6_logger, DHCP6_SRV_D2STOP_ERROR).arg(ex.what());
    }

    try {
        Dhcp6to4Ipc::instance().close();
    } catch(const std::exception& ex) {
        // Highly unlikely, but lets Report it but go on
        // LOG_ERROR(dhcp6_logger, DHCP6_SRV_DHCP4O6_ERROR).arg(ex.what());
    }

    IfaceMgr::instance().closeSockets();

    LeaseMgrFactory::destroy();

    // Explicitly unload hooks
    HooksManager::getHooksManager().unloadLibraries();
}

void Dhcpv6Srv::shutdown() {
    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_SHUTDOWN_REQUEST);
    shutdown_ = true;
}

Pkt6Ptr Dhcpv6Srv::receivePacket(int timeout) {
    return (IfaceMgr::instance().receive6(timeout));
}

void Dhcpv6Srv::sendPacket(const Pkt6Ptr& packet) {
    IfaceMgr::instance().send(packet);
}

bool
Dhcpv6Srv::testServerID(const Pkt6Ptr& pkt) {
    /// @todo Currently we always check server identifier regardless if
    /// it is allowed in the received message or not (per RFC 8415).
    /// If the server identifier is not allowed in the message, the
    /// sanityCheck function should deal with it.
    OptionPtr server_id = pkt->getOption(D6O_SERVERID);
    if (server_id){
        // Let us test received ServerID if it is same as ServerID
        // which is being used by server
        if (getServerID()->getData() != server_id->getData()){
            LOG_DEBUG(bad_packet6_logger, DBG_DHCP6_DETAIL_DATA,
                      DHCP6_PACKET_DROP_SERVERID_MISMATCH)
                .arg(pkt->getLabel())
                .arg(duidToString(server_id))
                .arg(duidToString(getServerID()));
            return (false);
        }
    }
    // return True if: no serverid received or ServerIDs matching
    return (true);
}

bool
Dhcpv6Srv::testUnicast(const Pkt6Ptr& pkt) const {
    switch (pkt->getType()) {
    case DHCPV6_SOLICIT:
    case DHCPV6_CONFIRM:
    case DHCPV6_REBIND:
    case DHCPV6_INFORMATION_REQUEST:
        if (pkt->relay_info_.empty() && !pkt->getLocalAddr().isV6Multicast()) {
            LOG_DEBUG(bad_packet6_logger, DBG_DHCP6_DETAIL, DHCP6_PACKET_DROP_UNICAST)
                .arg(pkt->getLabel())
                .arg(pkt->getName());
            return (false);
        }
        break;
    default:
        // do nothing
        ;
    }
    return (true);
}

void
Dhcpv6Srv::initContext(const Pkt6Ptr& pkt,
                       AllocEngine::ClientContext6& ctx,
                       bool& drop) {
    ctx.subnet_ = selectSubnet(pkt, drop);
    ctx.duid_ = pkt->getClientId(),
    ctx.fwd_dns_update_ = false;
    ctx.rev_dns_update_ = false;
    ctx.hostname_ = "";
    ctx.query_ = pkt;
    ctx.callout_handle_ = getCalloutHandle(pkt);
    ctx.hwaddr_ = getMAC(pkt);

    if (drop) {
        // Caller will immediately drop the packet so simply return now.
        return;
    }

    // Collect host identifiers if host reservations enabled. The identifiers
    // are stored in order of preference. The server will use them in that
    // order to search for host reservations.
    if (ctx.subnet_) {
        const ConstCfgHostOperationsPtr cfg =
            CfgMgr::instance().getCurrentCfg()->getCfgHostOperations6();
        BOOST_FOREACH(const Host::IdentifierType& id_type,
                      cfg->getIdentifierTypes()) {
            switch (id_type) {
            case Host::IDENT_DUID:
                if (ctx.duid_) {
                    ctx.addHostIdentifier(id_type, ctx.duid_->getDuid());
                }
                break;

            case Host::IDENT_HWADDR:
                if (ctx.hwaddr_) {
                    ctx.addHostIdentifier(id_type, ctx.hwaddr_->hwaddr_);
                }
                break;
            case Host::IDENT_FLEX:
                // At this point the information in the packet has been unpacked into
                // the various packet fields and option objects has been created.
                // Execute callouts registered for packet6_receive.
                if (HooksManager::calloutsPresent(Hooks.hook_index_host6_identifier_)) {
                    CalloutHandlePtr callout_handle = getCalloutHandle(pkt);

                    Host::IdentifierType type = Host::IDENT_FLEX;
                    std::vector<uint8_t> id;

                    // Use the RAII wrapper to make sure that the callout handle state is
                    // reset when this object goes out of scope. All hook points must do
                    // it to prevent possible circular dependency between the callout
                    // handle and its arguments.
                    ScopedCalloutHandleState callout_handle_state(callout_handle);

                    // Pass incoming packet as argument
                    callout_handle->setArgument("query6", pkt);
                    callout_handle->setArgument("id_type", type);
                    callout_handle->setArgument("id_value", id);

                    // Call callouts
                    HooksManager::callCallouts(Hooks.hook_index_host6_identifier_,
                                               *callout_handle);

                    callout_handle->getArgument("id_type", type);
                    callout_handle->getArgument("id_value", id);

                    if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_CONTINUE) &&
                        !id.empty()) {

                        LOG_DEBUG(packet6_logger, DBGLVL_TRACE_BASIC, DHCP6_FLEX_ID)
                            .arg(Host::getIdentifierAsText(type, &id[0], id.size()));

                        ctx.addHostIdentifier(type, id);
                    }
                }
                break;
            default:
                ;
            }
        }

        // Find host reservations using specified identifiers.
        alloc_engine_->findReservation(ctx);
    }

    // Set KNOWN builtin class if something was found, UNKNOWN if not.
    if (!ctx.hosts_.empty()) {
        pkt->addClass("KNOWN");
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_CLASS_ASSIGNED)
          .arg(pkt->getLabel())
          .arg("KNOWN");
    } else {
        pkt->addClass("UNKNOWN");
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_CLASS_ASSIGNED)
          .arg(pkt->getLabel())
          .arg("UNKNOWN");
    }

    // Perform second pass of classification.
    evaluateClasses(pkt, true);
}

bool Dhcpv6Srv::run() {
    while (!shutdown_) {
        try {
            run_one();
            getIOService()->poll();
        } catch (const std::exception& e) {
            // General catch-all standard exceptions that are not caught by more
            // specific catches.
            LOG_ERROR(packet6_logger, DHCP6_PACKET_PROCESS_STD_EXCEPTION)
                .arg(e.what());
        } catch (...) {
            // General catch-all non-standard exception that are not caught
            // by more specific catches.
            LOG_ERROR(packet6_logger, DHCP6_PACKET_PROCESS_EXCEPTION);
        }
    }

    return (true);
}

void Dhcpv6Srv::run_one() {
    // client's message and server's response
    Pkt6Ptr query;
    Pkt6Ptr rsp;

    try {
        // Set select() timeout to 1s. This value should not be modified
        // because it is important that the select() returns control
        // frequently so as the IOService can be polled for ready handlers.
        uint32_t timeout = 1;
        query = receivePacket(timeout);

        // Log if packet has arrived. We can't log the detailed information
        // about the DHCP message because it hasn't been unpacked/parsed
        // yet, and it can't be parsed at this point because hooks will
        // have to process it first. The only information available at this
        // point are: the interface, source address and destination addresses
        // and ports.
        if (query) {
            LOG_DEBUG(packet6_logger, DBG_DHCP6_BASIC, DHCP6_BUFFER_RECEIVED)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getRemotePort())
                .arg(query->getLocalAddr().toText())
                .arg(query->getLocalPort())
                .arg(query->getIface());

            // Log reception of the packet. We need to increase it early, as
            // any failures in unpacking will cause the packet to be dropped.
            // we will increase type specific packets further down the road.
            // See processStatsReceived().
            StatsMgr::instance().addValue("pkt6-received", static_cast<int64_t>(1));

        }
        // We used to log that the wait was interrupted, but this is no longer
        // the case. Our wait time is 1s now, so the lack of query packet more
        // likely means that nothing new appeared within a second, rather than
        // we were interrupted. And we don't want to print a message every
        // second.


    } catch (const SignalInterruptOnSelect&) {
        // Packet reception interrupted because a signal has been received.
        // This is not an error because we might have received a SIGTERM,
        // SIGINT or SIGHUP which are handled by the server. For signals
        // that are not handled by the server we rely on the default
        // behavior of the system.
        LOG_DEBUG(packet6_logger, DBG_DHCP6_DETAIL, DHCP6_BUFFER_WAIT_SIGNAL)
            .arg(signal_set_->getNext());
    } catch (const std::exception& e) {
        LOG_ERROR(packet6_logger, DHCP6_PACKET_RECEIVE_FAIL).arg(e.what());
    }

    // Handle next signal received by the process. It must be called after
    // an attempt to receive a packet to properly handle server shut down.
    // The SIGTERM or SIGINT will be received prior to, or during execution
    // of select() (select is invoked by receivePacket()). When that happens,
    // select will be interrupted. The signal handler will be invoked
    // immediately after select(). The handler will set the shutdown flag
    // and cause the process to terminate before the next select() function
    // is called. If the function was called before receivePacket the
    // process could wait up to the duration of timeout of select() to
    // terminate.
    try {
        handleSignal();
    } catch (const std::exception& e) {
        // An (a standard or ISC) exception occurred.
        LOG_ERROR(dhcp6_logger, DHCP6_HANDLE_SIGNAL_EXCEPTION)
            .arg(e.what());
    }

    // Timeout may be reached or signal received, which breaks select()
    // with no packet received
    if (!query) {
        return;
    }

    // If the DHCP service has been globally disabled, drop the packet.
    if (!network_state_->isServiceEnabled()) {
        LOG_DEBUG(bad_packet6_logger, DBG_DHCP6_DETAIL_DATA,
                  DHCP6_PACKET_DROP_DHCP_DISABLED)
            .arg(query->getLabel());
        return;
    } else {
        processPacket(query, rsp);
    }

    if (!rsp) {
        return;
    }

    CalloutHandlePtr callout_handle = getCalloutHandle(query);
    processPacketBufferSend(callout_handle, rsp);
}

void
Dhcpv6Srv::processPacket(Pkt6Ptr& query, Pkt6Ptr& rsp) {
    bool skip_unpack = false;

    // The packet has just been received so contains the uninterpreted wire
    // data; execute callouts registered for buffer6_receive.
    if (HooksManager::calloutsPresent(Hooks.hook_index_buffer6_receive_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(query);

        // Pass incoming packet as argument
        callout_handle->setArgument("query6", query);

        // Call callouts
        HooksManager::callCallouts(Hooks.hook_index_buffer6_receive_, *callout_handle);

        // Callouts decided to skip the next processing step. The next
        // processing step would to parse the packet, so skip at this
        // stage means that callouts did the parsing already, so server
        // should skip parsing.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_DETAIL, DHCP6_HOOK_BUFFER_RCVD_SKIP)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getLocalAddr().toText())
                .arg(query->getIface());
            skip_unpack = true;
        }

        // Callouts decided to drop the received packet
        // The response (rsp) is null so the caller (run_one) will
        // immediately return too.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_DETAIL, DHCP6_HOOK_BUFFER_RCVD_DROP)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getLocalAddr().toText())
                .arg(query->getIface());

            // Increase the statistic of dropped packets.
            StatsMgr::instance().addValue("pkt6-receive-drop",
                                          static_cast<int64_t>(1));
            return;
        }

        callout_handle->getArgument("query6", query);
    }

    // Unpack the packet information unless the buffer6_receive callouts
    // indicated they did it
    if (!skip_unpack) {
        try {
            LOG_DEBUG(options6_logger, DBG_DHCP6_DETAIL, DHCP6_BUFFER_UNPACK)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getLocalAddr().toText())
                .arg(query->getIface());
            query->unpack();
        } catch (const SkipRemainingOptionsError& e) {
            // An option failed to unpack but we are to attempt to process it
            // anyway.  Log it and let's hope for the best.
            LOG_DEBUG(options6_logger, DBG_DHCP6_DETAIL,
                      DHCP6_PACKET_OPTIONS_SKIPPED)
                .arg(e.what());
        } catch (const std::exception &e) {
            // Failed to parse the packet.
            LOG_DEBUG(bad_packet6_logger, DBG_DHCP6_DETAIL,
                      DHCP6_PACKET_DROP_PARSE_FAIL)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getLocalAddr().toText())
                .arg(query->getIface())
                .arg(e.what());

            // Increase the statistics of parse failures and dropped packets.
            StatsMgr::instance().addValue("pkt6-parse-failed",
                                          static_cast<int64_t>(1));
            StatsMgr::instance().addValue("pkt6-receive-drop",
                                          static_cast<int64_t>(1));
            return;
        }
    }

    // Update statistics accordingly for received packet.
    processStatsReceived(query);

    // Check if received query carries server identifier matching
    // server identifier being used by the server.
    if (!testServerID(query)) {

        // Increase the statistic of dropped packets.
        StatsMgr::instance().addValue("pkt6-receive-drop", static_cast<int64_t>(1));
        return;
    }

    // Check if the received query has been sent to unicast or multicast.
    // The Solicit, Confirm, Rebind and Information Request will be
    // discarded if sent to unicast address.
    if (!testUnicast(query)) {

        // Increase the statistic of dropped packets.
        StatsMgr::instance().addValue("pkt6-receive-drop", static_cast<int64_t>(1));
        return;
    }

    // Assign this packet to a class, if possible
    classifyPacket(query);

    LOG_DEBUG(packet6_logger, DBG_DHCP6_BASIC_DATA, DHCP6_PACKET_RECEIVED)
        .arg(query->getLabel())
        .arg(query->getName())
        .arg(static_cast<int>(query->getType()))
        .arg(query->getRemoteAddr())
        .arg(query->getLocalAddr())
        .arg(query->getIface());
    LOG_DEBUG(packet6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_QUERY_DATA)
        .arg(query->getLabel())
        .arg(query->toText());

    // At this point the information in the packet has been unpacked into
    // the various packet fields and option objects has been created.
    // Execute callouts registered for packet6_receive.
    if (HooksManager::calloutsPresent(Hooks.hook_index_pkt6_receive_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(query);

        // Pass incoming packet as argument
        callout_handle->setArgument("query6", query);

        // Call callouts
        HooksManager::callCallouts(Hooks.hook_index_pkt6_receive_, *callout_handle);

        // Callouts decided to skip the next processing step. The next
        // processing step would to process the packet, so skip at this
        // stage means drop.
        if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
            (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_PACKET_RCVD_SKIP)
                .arg(query->getLabel());
            // Increase the statistic of dropped packets.
            StatsMgr::instance().addValue("pkt6-receive-drop",
                                          static_cast<int64_t>(1));
            return;
        }

        callout_handle->getArgument("query6", query);
    }

    // Reject the message if it doesn't pass the sanity check.
    if (!sanityCheck(query)) {
        return;
    }

    if (query->getType() == DHCPV6_DHCPV4_QUERY) {
        // This call never throws. Should this change, this section must be
        // enclosed in try-catch.
        processDhcp4Query(query);
        return;
    }

    // Let's create a simplified client context here.
    AllocEngine::ClientContext6 ctx;
    bool drop = false;
    initContext(query, ctx, drop);

    // Stop here if initContext decided to drop the packet.
    if (drop) {
        return;
    }

    // Park point here.

    try {
        switch (query->getType()) {
        case DHCPV6_SOLICIT:
            rsp = processSolicit(ctx);
            break;

        case DHCPV6_REQUEST:
            rsp = processRequest(ctx);
            break;

        case DHCPV6_RENEW:
            rsp = processRenew(ctx);
            break;

        case DHCPV6_REBIND:
            rsp = processRebind(ctx);
            break;

        case DHCPV6_CONFIRM:
            rsp = processConfirm(ctx);
            break;

        case DHCPV6_RELEASE:
            rsp = processRelease(ctx);
            break;

        case DHCPV6_DECLINE:
            rsp = processDecline(ctx);
            break;

        case DHCPV6_INFORMATION_REQUEST:
            rsp = processInfRequest(ctx);
            break;

        default:
            return;
        }

    } catch (const std::exception& e) {

        // Catch-all exception (at least for ones based on the isc Exception
        // class, which covers more or less all that are explicitly raised
        // in the Kea code), but also the standard one, which may possibly be
        // thrown from boost code.  Just log the problem and ignore the packet.
        // (The problem is logged as a debug message because debug is
        // disabled by default - it prevents a DDOS attack based on the
        // sending of problem packets.)
        LOG_DEBUG(bad_packet6_logger, DBG_DHCP6_BASIC, DHCP6_PACKET_PROCESS_FAIL)
            .arg(query->getName())
            .arg(query->getRemoteAddr().toText())
            .arg(e.what());

        // Increase the statistic of dropped packets.
        StatsMgr::instance().addValue("pkt6-receive-drop", static_cast<int64_t>(1));
    }

    if (!rsp) {
        return;
    }

    // Process relay-supplied options. It is important to call this very
    // late in the process, because we now have all the options the
    // server wanted to send already set. This is important, because
    // RFC6422, section 6 states:
    //
    //   The server SHOULD discard any options that appear in the RSOO
    //   for which it already has one or more candidates.
    //
    // So we ignore any RSOO options if there's an option with the same
    // code already present.
    processRSOO(query, rsp);

    rsp->setRemoteAddr(query->getRemoteAddr());
    rsp->setLocalAddr(query->getLocalAddr());

    if (client_port_) {
        // A command line option enforces a specific client port
        rsp->setRemotePort(client_port_);
    } else if (rsp->relay_info_.empty()) {
        // Direct traffic, send back to the client directly
        rsp->setRemotePort(DHCP6_CLIENT_PORT);
    } else {
        // Relayed traffic, send back to the relay agent
        uint16_t relay_port = checkRelaySourcePort(query);
        rsp->setRemotePort(relay_port ? relay_port : DHCP6_SERVER_PORT);
    }

    rsp->setLocalPort(DHCP6_SERVER_PORT);
    rsp->setIndex(query->getIndex());
    rsp->setIface(query->getIface());

    bool packet_park = false;

    if (!ctx.fake_allocation_ && (ctx.query_->getType() != DHCPV6_CONFIRM) &&
        (ctx.query_->getType() != DHCPV6_INFORMATION_REQUEST) &&
        HooksManager::calloutsPresent(Hooks.hook_index_leases6_committed_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(query);

        // Also pass the corresponding query packet as argument
        callout_handle->setArgument("query6", query);

        Lease6CollectionPtr new_leases(new Lease6Collection());
        if (!ctx.new_leases_.empty()) {
            new_leases->assign(ctx.new_leases_.cbegin(),
                               ctx.new_leases_.cend());
        }
        callout_handle->setArgument("leases6", new_leases);

        Lease6CollectionPtr deleted_leases(new Lease6Collection());

        // Do per IA lists
        for (auto const iac : ctx.ias_) {
            if (!iac.old_leases_.empty()) {
                for (auto old_lease : iac.old_leases_) {
                    if (ctx.new_leases_.empty()) {
                        deleted_leases->push_back(old_lease);
                        continue;
                    }
                    bool in_new = false;
                    for (auto const new_lease : ctx.new_leases_) {
                        if ((new_lease->addr_ == old_lease->addr_) &&
                            (new_lease->prefixlen_ == old_lease->prefixlen_)) {
                            in_new = true;
                            break;
                        }
                    }
                    if (!in_new) {
                        deleted_leases->push_back(old_lease);
                    }
                }
            }
        }
        callout_handle->setArgument("deleted_leases6", deleted_leases);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_leases6_committed_,
                                   *callout_handle);

        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS,
                      DHCP6_HOOK_LEASES6_COMMITTED_DROP)
                .arg(query->getLabel());
            rsp.reset();

        } else if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_PARK) {
            packet_park = true;
        }
    }

    if (!rsp) {
        return;
    }

    // PARKING SPOT after leases6_committed hook point.
    CalloutHandlePtr callout_handle = getCalloutHandle(query);
    if (packet_park) {
        LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS,
                  DHCP6_HOOK_LEASES6_COMMITTED_PARK)
            .arg(query->getLabel());

        // Park the packet. The function we bind here will be executed when the hook
        // library unparks the packet.
        HooksManager::park("leases6_committed", query,
        [this, callout_handle, query, rsp]() mutable {
            processPacketPktSend(callout_handle, query, rsp);
            processPacketBufferSend(callout_handle, rsp);
        });

        // If we have parked the packet, let's reset the pointer to the
        // response to indicate to the caller that it should return, as
        // the packet processing will continue via the callback.
        rsp.reset();

    } else {
        processPacketPktSend(callout_handle, query, rsp);
    }
}

void
Dhcpv6Srv::processPacketPktSend(hooks::CalloutHandlePtr& callout_handle,
                                Pkt6Ptr& query, Pkt6Ptr& rsp) {
    if (!rsp) {
        return;
    }

    // Specifies if server should do the packing
    bool skip_pack = false;

    // Server's reply packet now has all options and fields set.
    // Options are represented by individual objects, but the
    // output wire data has not been prepared yet.
    // Execute all callouts registered for packet6_send
    if (HooksManager::calloutsPresent(Hooks.hook_index_pkt6_send_)) {

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packets within hook library.
        ScopedEnableOptionsCopy<Pkt6> query_resp_options_copy(query, rsp);

        // Pass incoming packet as argument
        callout_handle->setArgument("query6", query);

        // Set our response
        callout_handle->setArgument("response6", rsp);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_pkt6_send_, *callout_handle);

        // Callouts decided to skip the next processing step. The next
        // processing step would to pack the packet (create wire data).
        // That step will be skipped if any callout sets skip flag.
        // It essentially means that the callout already did packing,
        // so the server does not have to do it again.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_PACKET_SEND_SKIP)
                .arg(rsp->getLabel());
            skip_pack = true;
        }

        /// Callouts decided to drop the packet.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_PACKET_SEND_DROP)
                .arg(rsp->getLabel());
            rsp.reset();
            return;
        }
    }

    if (!skip_pack) {
        try {
            rsp->pack();
        } catch (const std::exception& e) {
            LOG_ERROR(options6_logger, DHCP6_PACK_FAIL).arg(e.what());
            return;
        }

    }
}

void
Dhcpv6Srv::processPacketBufferSend(CalloutHandlePtr& callout_handle,
                                   Pkt6Ptr& rsp) {
    if (!rsp) {
        return;
    }

    try {
        // Now all fields and options are constructed into output wire buffer.
        // Option objects modification does not make sense anymore. Hooks
        // can only manipulate wire buffer at this stage.
        // Let's execute all callouts registered for buffer6_send
        if (HooksManager::calloutsPresent(Hooks.hook_index_buffer6_send_)) {

            // Use the RAII wrapper to make sure that the callout handle state is
            // reset when this object goes out of scope. All hook points must do
            // it to prevent possible circular dependency between the callout
            // handle and its arguments.
            ScopedCalloutHandleState callout_handle_state(callout_handle);

            // Enable copying options from the packet within hook library.
            ScopedEnableOptionsCopy<Pkt6> response6_options_copy(rsp);

            // Pass incoming packet as argument
            callout_handle->setArgument("response6", rsp);

            // Call callouts
            HooksManager::callCallouts(Hooks.hook_index_buffer6_send_,
                                       *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to parse the packet, so skip at this
            // stage means drop.
            if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
                (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
                LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS,
                          DHCP6_HOOK_BUFFER_SEND_SKIP)
                    .arg(rsp->getLabel());
                return;
            }

            callout_handle->getArgument("response6", rsp);
        }

        LOG_DEBUG(packet6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_RESPONSE_DATA)
            .arg(static_cast<int>(rsp->getType())).arg(rsp->toText());

        sendPacket(rsp);

        // Update statistics accordingly for sent packet.
        processStatsSent(rsp);

    } catch (const std::exception& e) {
        LOG_ERROR(packet6_logger, DHCP6_PACKET_SEND_FAIL).arg(e.what());
    }
}

std::string
Dhcpv6Srv::duidToString(const OptionPtr& opt) {
    stringstream tmp;

    OptionBuffer data = opt->getData();

    bool colon = false;
    for (OptionBufferConstIter it = data.begin(); it != data.end(); ++it) {
        if (colon) {
            tmp << ":";
        }
        tmp << hex << setw(2) << setfill('0') << static_cast<uint16_t>(*it);
        if (!colon) {
            colon = true;
        }
    }

    return tmp.str();
}

void
Dhcpv6Srv::copyClientOptions(const Pkt6Ptr& question, Pkt6Ptr& answer) {
    // Add client-id.
    OptionPtr clientid = question->getOption(D6O_CLIENTID);
    if (clientid) {
        answer->addOption(clientid);
    }
    /// @todo: Should throw if there is no client-id (except anonymous INF-REQUEST)

    // If this is a relayed message, we need to copy relay information
    if (!question->relay_info_.empty()) {
        answer->copyRelayInfo(question);
    }

}

void
Dhcpv6Srv::appendDefaultOptions(const Pkt6Ptr&, Pkt6Ptr& answer,
                                const CfgOptionList&) {
    // add server-id
    answer->addOption(getServerID());
}

void
Dhcpv6Srv::buildCfgOptionList(const Pkt6Ptr& question,
                              AllocEngine::ClientContext6& ctx,
                              CfgOptionList& co_list) {
    // Firstly, host specific options.
    if (ctx.currentHost() && !ctx.currentHost()->getCfgOption6()->empty()) {
        co_list.push_back(ctx.currentHost()->getCfgOption6());
    }

    // Secondly, pool specific options. Pools are defined within a subnet, so
    // if there is no subnet, there is nothing to do.
    if (ctx.subnet_) {
        BOOST_FOREACH(const AllocEngine::ResourceType& resource,
                      ctx.allocated_resources_) {
            PoolPtr pool = ctx.subnet_->getPool(resource.second == 128 ?
                                                Lease::TYPE_NA : Lease::TYPE_PD,
                                                resource.first, false);
            if (pool && !pool->getCfgOption()->empty()) {
                co_list.push_back(pool->getCfgOption());
            }
        }
    };

    if (ctx.subnet_) {
        // Next, subnet configured options.
        if (!ctx.subnet_->getCfgOption()->empty()) {
            co_list.push_back(ctx.subnet_->getCfgOption());
        }

        // Then, shared network specific options.
        SharedNetwork6Ptr network;
        ctx.subnet_->getSharedNetwork(network);
        if (network && !network->getCfgOption()->empty()) {
            co_list.push_back(network->getCfgOption());
        }
    }

    // Each class in the incoming packet
    const ClientClasses& classes = question->getClasses();
    for (ClientClasses::const_iterator cclass = classes.cbegin();
         cclass != classes.cend(); ++cclass) {
        // Find the client class definition for this class
        const ClientClassDefPtr& ccdef = CfgMgr::instance().getCurrentCfg()->
            getClientClassDictionary()->findClass(*cclass);
        if (!ccdef) {
            // Not found: the class is built-in or not configured
            if (!isClientClassBuiltIn(*cclass)) {
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_CLASS_UNCONFIGURED)
                    .arg(question->getLabel())
                    .arg(*cclass);
            }
            // Skip it
            continue;
        }

        if (ccdef->getCfgOption()->empty()) {
            // Skip classes which don't configure options
            continue;
        }

        co_list.push_back(ccdef->getCfgOption());
    }

    // Last global options
    if (!CfgMgr::instance().getCurrentCfg()->getCfgOption()->empty()) {
        co_list.push_back(CfgMgr::instance().getCurrentCfg()->getCfgOption());
    }
}

void
Dhcpv6Srv::appendRequestedOptions(const Pkt6Ptr& question, Pkt6Ptr& answer,
                                  const CfgOptionList& co_list) {

    // Unlikely short cut
    if (co_list.empty()) {
        return;
    }

    std::vector<uint16_t> requested_opts;

    // Client requests some options using ORO option. Try to
    // get this option from client's message.
    boost::shared_ptr<OptionIntArray<uint16_t> > option_oro =
        boost::dynamic_pointer_cast<OptionIntArray<uint16_t> >
        (question->getOption(D6O_ORO));

    // Get the list of options that client requested.
    if (option_oro) {
        requested_opts = option_oro->getValues();
    }
    // Iterate on the configured option list to add persistent options
    for (CfgOptionList::const_iterator copts = co_list.begin();
         copts != co_list.end(); ++copts) {
        const OptionContainerPtr& opts = (*copts)->getAll(DHCP6_OPTION_SPACE);
        if (!opts) {
            continue;
        }
        // Get persistent options
        const OptionContainerPersistIndex& idx = opts->get<2>();
        const OptionContainerPersistRange& range = idx.equal_range(true);
        for (OptionContainerPersistIndex::const_iterator desc = range.first;
             desc != range.second; ++desc) {
            // Add the persistent option code to requested options
            requested_opts.push_back(desc->option_->getType());
        }
    }

    BOOST_FOREACH(uint16_t opt, requested_opts) {
        // Iterate on the configured option list
        for (CfgOptionList::const_iterator copts = co_list.begin();
             copts != co_list.end(); ++copts) {
            OptionDescriptor desc = (*copts)->get(DHCP6_OPTION_SPACE, opt);
            // Got it: add it and jump to the outer loop
            if (desc.option_) {
                answer->addOption(desc.option_);
                break;
            }
        }
    }
}

void
Dhcpv6Srv::appendRequestedVendorOptions(const Pkt6Ptr& question,
                                        Pkt6Ptr& answer,
                                        AllocEngine::ClientContext6& ctx,
                                        const CfgOptionList& co_list) {

    // Leave if there is no subnet matching the incoming packet.
    // There is no need to log the error message here because
    // it will be logged in the assignLease() when it fails to
    // pick the suitable subnet. We don't want to duplicate
    // error messages in such case.
    //
    // Also, if there's no options to possibly assign, give up.
    if (!ctx.subnet_ || co_list.empty()) {
        return;
    }

    uint32_t vendor_id = 0;

    // Try to get the vendor option from a client. This is the usual way.
    boost::shared_ptr<OptionVendor> vendor_req =
        boost::dynamic_pointer_cast<OptionVendor>(question->getOption(D6O_VENDOR_OPTS));
    if (vendor_req) {
        vendor_id = vendor_req->getVendorId();
    }

    /// @todo: We could get the vendor-id from vendor-class option (16).

    // The alternative is that the server could have provided the option in some
    // other way, either using client classification or hooks. If there's a
    // vendor info option in the response already, use that.
    boost::shared_ptr<OptionVendor> vendor_rsp =
        boost::dynamic_pointer_cast<OptionVendor>(answer->getOption(D6O_VENDOR_OPTS));
    if (vendor_rsp) {
        vendor_id = vendor_rsp->getVendorId();
    }

    // If there's no vendor option in either request or response, then there's no way
    // to figure out what the vendor-id value is and we give up.
    if (!vendor_req && !vendor_rsp) {
        return;
    }

    std::vector<uint16_t> requested_opts;

    // Let's try to get ORO within that vendor-option
    /// @todo This is very specific to vendor-id=4491 (Cable Labs). Other vendors
    /// may have different policies.
    boost::shared_ptr<OptionUint16Array> oro;
    if (vendor_req) {
        OptionPtr oro_generic = vendor_req->getOption(DOCSIS3_V6_ORO);
        if (oro_generic) {
            oro = boost::dynamic_pointer_cast<OptionUint16Array>(oro_generic);
            if (oro) {
                requested_opts = oro->getValues();
            }
        }
    }

    // Iterate on the configured option list to add persistent options
    for (CfgOptionList::const_iterator copts = co_list.begin();
         copts != co_list.end(); ++copts) {
        const OptionContainerPtr& opts = (*copts)->getAll(vendor_id);
        if (!opts) {
            continue;
        }
        // Get persistent options
        const OptionContainerPersistIndex& idx = opts->get<2>();
        const OptionContainerPersistRange& range = idx.equal_range(true);
        for (OptionContainerPersistIndex::const_iterator desc = range.first;
             desc != range.second; ++desc) {
            // Add the persistent option code to requested options
            requested_opts.push_back(desc->option_->getType());
        }
    }

    // If there is nothing to add don't do anything then.
    if (requested_opts.empty()) {
        return;
    }

    if (!vendor_rsp) {
        // It's possible that the vendor opts option was inserted already
        // by client class or a hook. If that is so, let's use it.
        vendor_rsp.reset(new OptionVendor(Option::V6, vendor_id));
    }

    // Get the list of options that client requested.
    bool added = false;

    BOOST_FOREACH(uint16_t opt, requested_opts) {
        for (CfgOptionList::const_iterator copts = co_list.begin();
             copts != co_list.end(); ++copts) {
            OptionDescriptor desc = (*copts)->get(vendor_id, opt);
            if (desc.option_) {
                vendor_rsp->addOption(desc.option_);
                added = true;
                break;
            }
        }
    }

    // If we added some sub-options and the vendor opts option is not in
    // the response already, then add it.
    if (added && !answer->getOption(D6O_VENDOR_OPTS)) {
        answer->addOption(vendor_rsp);
    }
}

bool
Dhcpv6Srv::sanityCheck(const Pkt6Ptr& pkt) {
    try {
        switch (pkt->getType()) {
        case DHCPV6_SOLICIT:
        case DHCPV6_REBIND:
    case DHCPV6_CONFIRM:
            sanityCheck(pkt, MANDATORY, FORBIDDEN);
            return (true);

        case DHCPV6_REQUEST:
        case DHCPV6_RENEW:
        case DHCPV6_RELEASE:
        case DHCPV6_DECLINE:
            sanityCheck(pkt, MANDATORY, MANDATORY);
            return (true);

        case DHCPV6_INFORMATION_REQUEST:
        case DHCPV6_DHCPV4_QUERY:
            sanityCheck(pkt, OPTIONAL, OPTIONAL);
            return (true);

        default:
            LOG_DEBUG(bad_packet6_logger, DBG_DHCP6_BASIC,
                      DHCP6_UNKNOWN_MSG_RECEIVED)
                .arg(static_cast<int>(pkt->getType()))
                .arg(pkt->getIface());
        }

    } catch (const RFCViolation& e) {
        LOG_DEBUG(bad_packet6_logger, DBG_DHCP6_BASIC, DHCP6_REQUIRED_OPTIONS_CHECK_FAIL)
            .arg(pkt->getName())
            .arg(pkt->getRemoteAddr().toText())
            .arg(e.what());

    }

    // Increase the statistic of dropped packets.
    StatsMgr::instance().addValue("pkt6-receive-drop", static_cast<int64_t>(1));
    return (false);
}

void
Dhcpv6Srv::sanityCheck(const Pkt6Ptr& pkt, RequirementLevel clientid,
                       RequirementLevel serverid) {
    OptionCollection client_ids = pkt->getOptions(D6O_CLIENTID);
    switch (clientid) {
    case MANDATORY: {
        if (client_ids.size() != 1) {
            isc_throw(RFCViolation, "Exactly 1 client-id option expected in "
                      << pkt->getName() << ", but " << client_ids.size()
                      << " received");
        }
        sanityCheckDUID(client_ids.begin()->second, "client-id");
        break;
    }
    case OPTIONAL:
        if (client_ids.size() > 1) {
            isc_throw(RFCViolation, "Too many (" << client_ids.size()
                      << ") client-id options received in " << pkt->getName());
        }
        if (!client_ids.empty()) {
            sanityCheckDUID(client_ids.begin()->second, "client-id");
        }
        break;

    case FORBIDDEN:
        // doesn't make sense - client-id is always allowed
        break;
    }

    OptionCollection server_ids = pkt->getOptions(D6O_SERVERID);
    switch (serverid) {
    case FORBIDDEN:
        if (!server_ids.empty()) {
            isc_throw(RFCViolation, "Server-id option was not expected, but "
                      << server_ids.size() << " received in " << pkt->getName());
        }
        break;

    case MANDATORY:
        if (server_ids.size() != 1) {
            isc_throw(RFCViolation, "Invalid number of server-id options received ("
                      << server_ids.size() << "), exactly 1 expected in message "
                      << pkt->getName());
        }
        sanityCheckDUID(server_ids.begin()->second, "server-id");
        break;

    case OPTIONAL:
        if (server_ids.size() > 1) {
            isc_throw(RFCViolation, "Too many (" << server_ids.size()
                      << ") server-id options received in " << pkt->getName());
        }
        if (!server_ids.empty()) {
            sanityCheckDUID(server_ids.begin()->second, "server-id");
        }
    }
}

void Dhcpv6Srv::sanityCheckDUID(const OptionPtr& opt, const std::string& opt_name) {
    if (!opt) {
        isc_throw(RFCViolation, "Unable to find expected option " << opt_name);
    }

    // The client-id or server-id has to have at least 3 bytes of useful data:
    // two for duid type and one more for actual duid value.
    uint16_t len = opt->len() - opt->getHeaderLen();
    if (len < 3) {
        isc_throw(RFCViolation, "Received empty or truncated " << opt_name << " option: "
                  << len << " byte(s) only");
    }
}

Subnet6Ptr
Dhcpv6Srv::selectSubnet(const Pkt6Ptr& question, bool& drop) {
    const SubnetSelector& selector = CfgSubnets6::initSelector(question);

    Subnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->selectSubnet(selector);

    // Let's execute all callouts registered for subnet6_receive
    if (HooksManager::calloutsPresent(Hooks.hook_index_subnet6_select_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(question);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(question);

        // Set new arguments
        callout_handle->setArgument("query6", question);
        callout_handle->setArgument("subnet6", subnet);

        // We pass pointer to const collection for performance reasons.
        // Otherwise we would get a non-trivial performance penalty each
        // time subnet6_select is called.
        callout_handle->setArgument("subnet6collection",
                                    CfgMgr::instance().getCurrentCfg()->
                                    getCfgSubnets6()->getAll());

        // Call user (and server-side) callouts
        HooksManager::callCallouts(Hooks.hook_index_subnet6_select_, *callout_handle);

        // Callouts decided to skip this step. This means that no
        // subnet will be selected. Packet processing will continue,
        // but it will be severely limited (i.e. only global options
        // will be assigned)
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_SUBNET6_SELECT_SKIP)
                .arg(question->getLabel());
            return (Subnet6Ptr());
        }

        // Callouts decided to drop the packet. It is a superset of the
        // skip case so no subnet will be selected.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_SUBNET6_SELECT_DROP)
                .arg(question->getLabel());
            drop = true;
            return (Subnet6Ptr());
        }

        // Use whatever subnet was specified by the callout
        callout_handle->getArgument("subnet6", subnet);
    }

    if (subnet) {
        // Log at higher debug level that subnet has been found.
        LOG_DEBUG(packet6_logger, DBG_DHCP6_BASIC_DATA, DHCP6_SUBNET_SELECTED)
            .arg(question->getLabel())
            .arg(subnet->getID());
        // Log detailed information about the selected subnet at the
        // lower debug level.
        LOG_DEBUG(packet6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_SUBNET_DATA)
            .arg(question->getLabel())
            .arg(subnet->toText());

    } else {
        LOG_DEBUG(packet6_logger, DBG_DHCP6_DETAIL, DHCP6_SUBNET_SELECTION_FAILED)
            .arg(question->getLabel());
    }

    return (subnet);
}

void
Dhcpv6Srv::assignLeases(const Pkt6Ptr& question, Pkt6Ptr& answer,
                        AllocEngine::ClientContext6& ctx) {

    Subnet6Ptr subnet = ctx.subnet_;

    // We need to allocate addresses for all IA_NA options in the client's
    // question (i.e. SOLICIT or REQUEST) message.
    // @todo add support for IA_TA

    // For the lease allocation it is critical that the client has sent
    // DUID. There is no need to check for the presence of the DUID here
    // because we have already checked it in the sanityCheck().

    // Now that we have all information about the client, let's iterate over all
    // received options and handle IA_NA options one by one and store our
    // responses in answer message (ADVERTISE or REPLY).
    //
    // @todo: IA_TA once we implement support for temporary addresses.
    for (OptionCollection::iterator opt = question->options_.begin();
         opt != question->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = assignIA_NA(question, answer, ctx,
                                               boost::dynamic_pointer_cast<
                                               Option6IA>(opt->second));
            if (answer_opt) {
                answer->addOption(answer_opt);
            }
            break;
        }
        case D6O_IA_PD: {
            OptionPtr answer_opt = assignIA_PD(question, answer, ctx,
                                               boost::dynamic_pointer_cast<
                                               Option6IA>(opt->second));
            if (answer_opt) {
                answer->addOption(answer_opt);
            }
        }
        default:
            break;
        }
    }

    // Subnet may be modified by the allocation engine, if the initial subnet
    // belongs to a shared network.
    if (ctx.subnet_ && subnet && (subnet->getID() != ctx.subnet_->getID())) {
        SharedNetwork6Ptr network;
        subnet->getSharedNetwork(network);
        if (network) {
            LOG_DEBUG(packet6_logger, DBG_DHCP6_BASIC_DATA, DHCP6_SUBNET_DYNAMICALLY_CHANGED)
                .arg(question->getLabel())
                .arg(subnet->toText())
                .arg(ctx.subnet_->toText())
                .arg(network->getName());
        }
    }
}


void
Dhcpv6Srv::processClientFqdn(const Pkt6Ptr& question, const Pkt6Ptr& answer,
                             AllocEngine::ClientContext6& ctx) {
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();

    // Get Client FQDN Option from the client's message. If this option hasn't
    // been included, do nothing.
    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option6ClientFqdn>(question->getOption(D6O_CLIENT_FQDN));
    if (!fqdn) {
        D2ClientConfig::ReplaceClientNameMode replace_name_mode =
            d2_mgr.getD2ClientConfig()->getReplaceClientNameMode();
        if (d2_mgr.ddnsEnabled() &&
            (replace_name_mode == D2ClientConfig::RCM_ALWAYS ||
             replace_name_mode == D2ClientConfig::RCM_WHEN_NOT_PRESENT)) {
            // Fabricate an empty "client" FQDN with flags requesting
            // the server do all the updates.  The flags will get modified
            // below according the configuration options, the name will
            // be supplied later on.
            fqdn.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S, "",
                                             Option6ClientFqdn::PARTIAL));
            LOG_DEBUG(ddns6_logger, DBG_DHCP6_DETAIL, DHCP6_DDNS_GENERATE_FQDN)
                .arg(question->getLabel());
        } else {
            // No FQDN so get the lease hostname from the host reservation if
            // there is one.
            if (ctx.currentHost()) {
                ctx.hostname_ = ctx.currentHost()->getHostname();
            }

            return;
        }
    }

    LOG_DEBUG(ddns6_logger, DBG_DHCP6_DETAIL, DHCP6_DDNS_RECEIVE_FQDN)
        .arg(question->getLabel())
        .arg(fqdn->toText());

    // Create the DHCPv6 Client FQDN Option to be included in the server's
    // response to a client.
    Option6ClientFqdnPtr fqdn_resp(new Option6ClientFqdn(*fqdn));

    // Set the server S, N, and O flags based on client's flags and
    // current configuration.
    d2_mgr.adjustFqdnFlags<Option6ClientFqdn>(*fqdn, *fqdn_resp);

    // If there's a reservation and it has a hostname specified, use it!
    if (ctx.currentHost() && !ctx.currentHost()->getHostname().empty()) {
        // Add the qualifying suffix.
        // After #3765, this will only occur if the suffix is not empty.
        fqdn_resp->setDomainName(d2_mgr.qualifyName(ctx.currentHost()->getHostname(),
                                                    true),
                                                    Option6ClientFqdn::FULL);
    } else {
        // Adjust the domain name based on domain name value and type sent by
        // the client and current configuration.
        d2_mgr.adjustDomainName<Option6ClientFqdn>(*fqdn, *fqdn_resp);
    }

    // Once we have the FQDN setup to use it for the lease hostname.  This
    // only gets replaced later if the FQDN is to be generated from the address.
    ctx.hostname_ = fqdn_resp->getDomainName();

    // The FQDN has been processed successfully. Let's append it to the
    // response to be sent to a client. Note that the Client FQDN option is
    // always sent back to the client if Client FQDN was included in the
    // client's message.
    LOG_DEBUG(ddns6_logger, DBG_DHCP6_DETAIL, DHCP6_DDNS_RESPONSE_FQDN_DATA)
        .arg(question->getLabel())
        .arg(fqdn_resp->toText());
    answer->addOption(fqdn_resp);
}

void
Dhcpv6Srv::createNameChangeRequests(const Pkt6Ptr& answer,
                                    AllocEngine::ClientContext6& ctx) {
    // Don't create NameChangeRequests if DNS updates are disabled.
    if (!CfgMgr::instance().ddnsEnabled()) {
        return;
    }

    // The response message instance is always required. For instance it
    // holds the Client Identifier. It is a programming error if supplied
    // message is NULL.
    if (!answer) {
        isc_throw(isc::Unexpected, "an instance of the object"
                  << " encapsulating server's message must not be"
                  << " NULL when creating DNS NameChangeRequest");
    }

    // It is likely that client haven't included the FQDN option. In such case,
    // FQDN option will be NULL. This is valid state, so we simply return.
    Option6ClientFqdnPtr opt_fqdn = boost::dynamic_pointer_cast<
        Option6ClientFqdn>(answer->getOption(D6O_CLIENT_FQDN));
    if (!opt_fqdn) {
        return;
    }

    // Get the update directions that should be performed based on our
    // response FQDN flags.
    bool do_fwd = false;
    bool do_rev = false;
    CfgMgr::instance().getD2ClientMgr().getUpdateDirections(*opt_fqdn,
                                                             do_fwd, do_rev);
    if (!do_fwd && !do_rev) {
        // Flags indicate there is Nothing to do, get out now.
        // The Most likely scenario is that we are honoring the client's
        // request that no updates be done.
        return;
    }

    // Get the Client Id. It is mandatory and a function creating a response
    // would have thrown an exception if it was missing. Thus throwing
    // Unexpected if it is missing as it is a programming error.
    OptionPtr opt_duid = answer->getOption(D6O_CLIENTID);
    if (!opt_duid) {
        isc_throw(isc::Unexpected,
                  "client identifier is required when creating a new"
                  " DNS NameChangeRequest");
    }
    DuidPtr duid = DuidPtr(new DUID(opt_duid->getData()));

    // Get the FQDN in the on-wire format. It will be needed to compute
    // DHCID.
    OutputBuffer name_buf(1);
    opt_fqdn->packDomainName(name_buf);
    const uint8_t* name_data = static_cast<const uint8_t*>(name_buf.getData());
    // @todo currently D2Dhcid accepts a vector holding FQDN.
    // However, it will be faster if we used a pointer name_data.
    std::vector<uint8_t> buf_vec(name_data, name_data + name_buf.getLength());
    // Compute DHCID from Client Identifier and FQDN.
    isc::dhcp_ddns::D2Dhcid dhcid(*duid, buf_vec);

    // Get all IAs from the answer. For each IA, holding an address we will
    // create a corresponding NameChangeRequest.
    OptionCollection answer_ias = answer->getOptions(D6O_IA_NA);
    for (OptionCollection::const_iterator answer_ia =
             answer_ias.begin(); answer_ia != answer_ias.end(); ++answer_ia) {
        /// @todo IA_NA may contain multiple addresses. We should process
        /// each address individually. Currently we get only one.
        Option6IAAddrPtr iaaddr = boost::static_pointer_cast<
            Option6IAAddr>(answer_ia->second->getOption(D6O_IAADDR));
        // We need an address to create a name-to-address mapping.
        // If address is missing for any reason, go to the next IA.
        if (!iaaddr) {
            continue;
        }

        // If the lease for iaaddr is in the list of changed leases, we need
        // to determine if the changes included changes to the FQDN. If there
        // were  changes to the FQDN then we need to update DNS, otherwise
        // we do not.
        bool extended_only = false;
        for (Lease6Collection::const_iterator l = ctx.currentIA().changed_leases_.begin();
             l != ctx.currentIA().changed_leases_.end(); ++l) {
            if ((*l)->addr_ == iaaddr->getAddress()) {
                if ((*l)->hostname_ == opt_fqdn->getDomainName() &&
                    (*l)->fqdn_fwd_ == do_fwd && (*l)->fqdn_rev_ == do_rev) {
                    extended_only = true;
                    break;
                }
            }
        }

        if (extended_only) {
            continue;
        }

        // Create new NameChangeRequest. Use the domain name from the FQDN.
        // This is an FQDN included in the response to the client, so it
        // holds a fully qualified domain-name already (not partial).
        // Get the IP address from the lease.
        NameChangeRequestPtr ncr;
        ncr.reset(new NameChangeRequest(isc::dhcp_ddns::CHG_ADD,
                                        do_fwd, do_rev,
                                        opt_fqdn->getDomainName(),
                                        iaaddr->getAddress().toText(),
                                        dhcid, 0, iaaddr->getValid()));

        LOG_DEBUG(ddns6_logger, DBG_DHCP6_DETAIL,
                  DHCP6_DDNS_CREATE_ADD_NAME_CHANGE_REQUEST).arg(ncr->toText());

        // Post the NCR to the D2ClientMgr.
        CfgMgr::instance().getD2ClientMgr().sendRequest(ncr);

        /// @todo Currently we create NCR with the first IPv6 address that
        /// is carried in one of the IA_NAs. In the future, the NCR API should
        /// be extended to map multiple IPv6 addresses to a single FQDN.
        /// In such case, this return statement will be removed.
        return;
    }
}

HWAddrPtr
Dhcpv6Srv::getMAC(const Pkt6Ptr& pkt) {
    CfgMACSources mac_sources = CfgMgr::instance().getCurrentCfg()->
        getMACSources().get();
    HWAddrPtr hwaddr;
    for (CfgMACSources::const_iterator it = mac_sources.begin();
         it != mac_sources.end(); ++it) {
        hwaddr = pkt->getMAC(*it);
        if (hwaddr) {
            return (hwaddr);
        }
    }
    return (hwaddr);
}

OptionPtr
Dhcpv6Srv::assignIA_NA(const Pkt6Ptr& query, const Pkt6Ptr& answer,
                       AllocEngine::ClientContext6& ctx,
                       boost::shared_ptr<Option6IA> ia) {

    // Check if the client sent us a hint in his IA_NA. Clients may send an
    // address in their IA_NA options as a suggestion (e.g. the last address
    // they used before).
    Option6IAAddrPtr hint_opt =
        boost::dynamic_pointer_cast<Option6IAAddr>(ia->getOption(D6O_IAADDR));
    IOAddress hint = IOAddress::IPV6_ZERO_ADDRESS();
    if (hint_opt) {
        hint = hint_opt->getAddress();
    }

    LOG_DEBUG(lease6_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_NA_REQUEST)
        .arg(query->getLabel())
        .arg(ia->getIAID())
        .arg(hint_opt ? hint.toText() : "(no hint)");

    // convenience values
    const Subnet6Ptr& subnet = ctx.subnet_;

    // If there is no subnet selected for handling this IA_NA, the only thing left to do is
    // to say that we are sorry, but the user won't get an address. As a convenience, we
    // use a different status text to indicate that (compare to the same status code,
    // but different wording below)
    if (!subnet) {
        // Create an empty IA_NA option with IAID matching the request.
        // Note that we don't use OptionDefinition class to create this option.
        // This is because we prefer using a constructor of Option6IA that
        // initializes IAID. Otherwise we would have to use setIAID() after
        // creation of the option which has some performance implications.
        boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoAddrsAvail,
                                           "Server could not select subnet for"
                                           " this client"));
        return (ia_rsp);
    }

    // Get DDNS update direction flags
    bool do_fwd = false;
    bool do_rev = false;
    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option6ClientFqdn>(answer->getOption(D6O_CLIENT_FQDN));
    if (fqdn) {
        CfgMgr::instance().getD2ClientMgr().getUpdateDirections(*fqdn, do_fwd,
                                                                do_rev);
    }

    // Update per-packet context values.
    ctx.fwd_dns_update_ = do_fwd;
    ctx.rev_dns_update_ = do_rev;

    // Set per-IA context values.
    ctx.createIAContext();
    ctx.currentIA().iaid_ = ia->getIAID();
    ctx.currentIA().addHint(hint);
    ctx.currentIA().type_ = Lease::TYPE_NA;

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honor the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    Lease6Collection leases = alloc_engine_->allocateLeases6(ctx);

    /// @todo: Handle more than one lease
    Lease6Ptr lease;
    if (!leases.empty()) {
        lease = *leases.begin();
    }

    // Create IA_NA that we will put in the response.
    // Do not use OptionDefinition to create option's instance so
    // as we can initialize IAID using a constructor.
    Option6IAPtr ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

    if (lease) {
        // We have a lease! Let's wrap its content into IA_NA option
        // with IAADDR suboption.
        LOG_INFO(lease6_logger, ctx.fake_allocation_ ? DHCP6_LEASE_ADVERT : DHCP6_LEASE_ALLOC)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(ia->getIAID());
        LOG_DEBUG(lease6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_LEASE_DATA)
            .arg(query->getLabel())
            .arg(ia->getIAID())
            .arg(lease->toText());

        ia_rsp->setT1(subnet->getT1());
        ia_rsp->setT2(subnet->getT2());

        Option6IAAddrPtr addr(new Option6IAAddr(D6O_IAADDR, lease->addr_,
                                                lease->preferred_lft_,
                                                lease->valid_lft_));
        ia_rsp->addOption(addr);

        // It would be possible to insert status code=0(success) as well,
        // but this is considered waste of bandwidth as absence of status
        // code is considered a success.

    } else {
        // Allocation engine did not allocate a lease. The engine logged
        // cause of that failure. The only thing left is to insert
        // status code to pass the sad news to the client.

        LOG_DEBUG(lease6_logger, DBG_DHCP6_DETAIL, ctx.fake_allocation_ ?
                  DHCP6_LEASE_ADVERT_FAIL : DHCP6_LEASE_ALLOC_FAIL)
            .arg(query->getLabel())
            .arg(ia->getIAID());

        ia_rsp->addOption(createStatusCode(*query, *ia_rsp,
                                           STATUS_NoAddrsAvail,
                                           "Sorry, no address could be"
                                           " allocated."));
    }
    return (ia_rsp);
}

OptionPtr
Dhcpv6Srv::assignIA_PD(const Pkt6Ptr& query, const Pkt6Ptr& /*answer*/,
                       AllocEngine::ClientContext6& ctx,
                       boost::shared_ptr<Option6IA> ia) {

    // Check if the client sent us a hint in his IA_PD. Clients may send an
    // address in their IA_PD options as a suggestion (e.g. the last address
    // they used before). While the hint consists of a full prefix (prefix +
    // length), getting just the prefix is sufficient to identify a lease.
    Option6IAPrefixPtr hint_opt =
        boost::dynamic_pointer_cast<Option6IAPrefix>(ia->getOption(D6O_IAPREFIX));
    IOAddress hint = IOAddress::IPV6_ZERO_ADDRESS();
    if (hint_opt) {
        hint = hint_opt->getAddress();
    }

    LOG_DEBUG(lease6_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_PD_REQUEST)
        .arg(query->getLabel())
        .arg(ia->getIAID())
        .arg(hint_opt ? hint.toText() : "(no hint)");


    const Subnet6Ptr& subnet = ctx.subnet_;

    // Create IA_PD that we will put in the response.
    // Do not use OptionDefinition to create option's instance so
    // as we can initialize IAID using a constructor.
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_PD, ia->getIAID()));

    // If there is no subnet selected for handling this IA_PD, the only thing
    // left to do is to say that we are sorry, but the user won't get an address.
    // As a convenience, we use a different status text to indicate that
    // (compare to the same status code, but different wording below)
    if (!subnet) {

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoPrefixAvail,
                                           "Sorry, no subnet available."));
        return (ia_rsp);
    }

    // Set per-IA context values.
    ctx.createIAContext();
    ctx.currentIA().iaid_ = ia->getIAID();
    ctx.currentIA().addHint(hint);
    ctx.currentIA().type_ = Lease::TYPE_PD;

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honor the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    Lease6Collection leases = alloc_engine_->allocateLeases6(ctx);

    if (!leases.empty()) {

        ia_rsp->setT1(subnet->getT1());
        ia_rsp->setT2(subnet->getT2());

        const bool pd_exclude_requested = requestedInORO(query, D6O_PD_EXCLUDE);

        for (Lease6Collection::iterator l = leases.begin();
             l != leases.end(); ++l) {

            // We have a lease! Let's wrap its content into IA_PD option
            // with IAADDR suboption.
            LOG_INFO(lease6_logger, ctx.fake_allocation_ ?
                      DHCP6_PD_LEASE_ADVERT : DHCP6_PD_LEASE_ALLOC)
                .arg(query->getLabel())
                .arg((*l)->addr_.toText())
                .arg(static_cast<int>((*l)->prefixlen_))
                .arg(ia->getIAID());

            boost::shared_ptr<Option6IAPrefix>
                addr(new Option6IAPrefix(D6O_IAPREFIX, (*l)->addr_,
                                         (*l)->prefixlen_, (*l)->preferred_lft_,
                                         (*l)->valid_lft_));
            ia_rsp->addOption(addr);

            if (pd_exclude_requested) {
                // PD exclude option has been requested via ORO, thus we need to
                // include it if the pool configuration specifies this option.
                Pool6Ptr pool = boost::dynamic_pointer_cast<
                    Pool6>(subnet->getPool(Lease::TYPE_PD, (*l)->addr_));
                if (pool) {
                    Option6PDExcludePtr pd_exclude_option = pool->getPrefixExcludeOption();
                    if (pd_exclude_option) {
                        addr->addOption(pd_exclude_option);
                    }
                }
            }
        }

        // It would be possible to insert status code=0(success) as well,
        // but this is considered waste of bandwidth as absence of status
        // code is considered a success.

    } else {
        // Allocation engine did not allocate a lease. The engine logged
        // cause of that failure. The only thing left is to insert
        // status code to pass the sad news to the client.

        LOG_DEBUG(lease6_logger, DBG_DHCP6_DETAIL, ctx.fake_allocation_ ?
                  DHCP6_PD_LEASE_ADVERT_FAIL : DHCP6_PD_LEASE_ALLOC_FAIL)
            .arg(query->getLabel())
            .arg(ia->getIAID());

        ia_rsp->addOption(createStatusCode(*query, *ia_rsp,
                                           STATUS_NoPrefixAvail,
                                           "Sorry, no prefixes could"
                                           " be allocated."));
    }
    return (ia_rsp);
}

OptionPtr
Dhcpv6Srv::extendIA_NA(const Pkt6Ptr& query, const Pkt6Ptr& answer,
                       AllocEngine::ClientContext6& ctx,
                       boost::shared_ptr<Option6IA> ia) {

    LOG_DEBUG(lease6_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_NA_EXTEND)
        .arg(query->getLabel())
        .arg(ia->getIAID());

    // convenience values
    const Subnet6Ptr& subnet = ctx.subnet_;

    // Create empty IA_NA option with IAID matching the request.
    Option6IAPtr ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

    if (!subnet) {
        /// @todo For simplicity and due to limitations of LeaseMgr we don't
        /// get the binding for the client for which we don't get subnet id.
        /// Subnet id is a required value when searching for the bindings.
        /// The fact that we can't identify the subnet for the returning client
        /// doesn't really mean that the client has no binding. It is possible
        /// that due to server's reconfiguration the subnet has been removed
        /// or modified since the client has got his lease. We may need to
        /// rethink whether it is appropriate to send no binding if the subnet
        /// hasn't been found for the client.
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid."));
        return (ia_rsp);
    }

    // Set up T1, T2 timers
    ia_rsp->setT1(subnet->getT1());
    ia_rsp->setT2(subnet->getT2());

    // Get DDNS update directions
    bool do_fwd = false;
    bool do_rev = false;
    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option6ClientFqdn>(answer->getOption(D6O_CLIENT_FQDN));
    if (fqdn) {
        CfgMgr::instance().getD2ClientMgr().getUpdateDirections(*fqdn,
                                                                do_fwd, do_rev);
    }

    // Set per-packet context values.
    ctx.fwd_dns_update_ = do_fwd;
    ctx.rev_dns_update_ = do_rev;

    // Set per-IA context values.
    ctx.createIAContext();
    ctx.currentIA().iaid_ = ia->getIAID();
    ctx.currentIA().type_ = Lease::TYPE_NA;
    ctx.currentIA().ia_rsp_ = ia_rsp;

    // Extract the addresses that the client is trying to obtain.
    OptionCollection addrs = ia->getOptions();
    for (OptionCollection::const_iterator it = addrs.begin();
         it != addrs.end(); ++it) {
        if (it->second->getType() != D6O_IAADDR) {
            continue;
        }
        Option6IAAddrPtr iaaddr = boost::dynamic_pointer_cast<Option6IAAddr>(it->second);
        if (!iaaddr) {
            // That's weird. Option code was ok, but the object type was not.
            // This should never happen. The only case would be with badly
            // mis-implemented hook libraries that insert invalid option objects.
            // There's no way to protect against this.
            continue;
        }
        ctx.currentIA().addHint(iaaddr->getAddress());
    }

    Lease6Collection leases = alloc_engine_->renewLeases6(ctx);

    // Ok, now we have the leases extended. We have:
    // - what the client tried to renew in ctx.hints_
    // - what we actually assigned in leases
    // - old leases that are no longer valid in ctx.old_leases_

    // For each IA inserted by the client we have to determine what to do
    // about included addresses and notify the client. We will iterate over
    // those prefixes and remove those that we have already processed. We
    // don't want to remove them from the context, so we need to copy them
    // into temporary container.
    AllocEngine::HintContainer hints = ctx.currentIA().hints_;

    // For all leases we have now, add the IAADDR with non-zero lifetimes.
    for (Lease6Collection::const_iterator l = leases.begin(); l != leases.end(); ++l) {
        Option6IAAddrPtr iaaddr(new Option6IAAddr(D6O_IAADDR,
                                (*l)->addr_, (*l)->preferred_lft_, (*l)->valid_lft_));
        ia_rsp->addOption(iaaddr);
        LOG_INFO(lease6_logger, DHCP6_LEASE_RENEW)
            .arg(query->getLabel())
            .arg((*l)->addr_.toText())
            .arg(ia_rsp->getIAID());

        // Now remove this address from the hints list.
        AllocEngine::ResourceType hint_type((*l)->addr_, 128);
        hints.erase(std::remove(hints.begin(), hints.end(), hint_type),
                    hints.end());
    }

    // For the leases that we just retired, send the addresses with 0 lifetimes.
    for (Lease6Collection::const_iterator l = ctx.currentIA().old_leases_.begin();
                                          l != ctx.currentIA().old_leases_.end(); ++l) {

        // Send an address with zero lifetimes only when this lease belonged to
        // this client. Do not send it when we're reusing an old lease that belonged
        // to someone else.
        if (equalValues(query->getClientId(), (*l)->duid_)) {
            Option6IAAddrPtr iaaddr(new Option6IAAddr(D6O_IAADDR,
                                                      (*l)->addr_, 0, 0));
            ia_rsp->addOption(iaaddr);
        }

        // Now remove this address from the hints list.
        AllocEngine::ResourceType hint_type((*l)->addr_, 128);
        hints.erase(std::remove(hints.begin(), hints.end(), hint_type), hints.end());

        // If the new FQDN settings have changed for the lease, we need to
        // delete any existing FQDN records for this lease.
        if (((*l)->hostname_ != ctx.hostname_) || ((*l)->fqdn_fwd_ != do_fwd) ||
            ((*l)->fqdn_rev_ != do_rev)) {
            LOG_DEBUG(ddns6_logger, DBG_DHCP6_DETAIL,
                      DHCP6_DDNS_LEASE_RENEW_FQDN_CHANGE)
                .arg(query->getLabel())
                .arg((*l)->toText())
                .arg(ctx.hostname_)
                .arg(do_rev ? "true" : "false")
                .arg(do_fwd ? "true" : "false");

            queueNCR(CHG_REMOVE, *l);
        }
    }

    // Finally, if there are any addresses requested that we haven't dealt with
    // already, inform the client that he can't have them.
    for (AllocEngine::HintContainer::const_iterator hint = hints.begin();
         hint != hints.end(); ++hint) {
        Option6IAAddrPtr iaaddr(new Option6IAAddr(D6O_IAADDR,
                                                  hint->first, 0, 0));
        ia_rsp->addOption(iaaddr);
    }

    // All is left is to insert the status code.
    if (leases.empty()) {

        // The server wasn't able allocate new lease and renew an existing
        // lease. In that case, the server sends NoAddrsAvail per RFC 8415.
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp,
                                           STATUS_NoAddrsAvail,
                                           "Sorry, no addresses could be"
                                           " assigned at this time."));
    }

    return (ia_rsp);
}

OptionPtr
Dhcpv6Srv::extendIA_PD(const Pkt6Ptr& query,
                       AllocEngine::ClientContext6& ctx,
                       boost::shared_ptr<Option6IA> ia) {

    LOG_DEBUG(lease6_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_PD_EXTEND)
        .arg(query->getLabel())
        .arg(ia->getIAID());

    const Subnet6Ptr& subnet = ctx.subnet_;
    const DuidPtr& duid = ctx.duid_;

    // Let's create a IA_PD response and fill it in later
    Option6IAPtr ia_rsp(new Option6IA(D6O_IA_PD, ia->getIAID()));

    // If there is no subnet for the particular client, we can't retrieve
    // information about client's leases from lease database. We treat this
    // as no binding for the client.
    if (!subnet) {
        // Per RFC 8415, section 18.3.4, if there is no binding and we are
        // processing a Renew, the NoBinding status code should be returned.
        if (query->getType() == DHCPV6_RENEW) {
            // Insert status code NoBinding
            ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                                               "Sorry, no known PD leases"
                                               " for this duid/iaid."));
            return (ia_rsp);

        // Per RFC 8415, section 18.3.5, if there is no binding and we are
        // processing Rebind, the message has to be discarded (assuming that
        // the server doesn't know if the prefix in the IA_PD option is
        // appropriate for the client's link). The exception being thrown
        // here should propagate to the main loop and cause the message to
        // be discarded.
        } else {

            /// @todo: We may consider in which cases we could determine
            /// whether the delegated prefixes are appropriate for the
            /// link to which the client's interface is attached. Just not
            /// being able to select the subnet may not be enough, because
            /// there might be other DHCP servers around that are configured
            /// to handle that subnet. Therefore we don't fully follow all
            /// the paths in section 18.3.5 of RFC 8415 to respond with
            /// zero lifetimes for the prefixes being rebound.
            isc_throw(DHCPv6DiscardMessageError, "no subnet found for the"
                      " client sending Rebind to extend lifetime of the"
                      " prefix (DUID=" << duid->toText() << ", IAID="
                      << ia->getIAID() << ")");
        }
    }

    // Set up T1, T2 timers
    ia_rsp->setT1(subnet->getT1());
    ia_rsp->setT2(subnet->getT2());

    // Set per-IA context values.
    ctx.createIAContext();
    ctx.currentIA().iaid_ = ia->getIAID();
    ctx.currentIA().type_ = Lease::TYPE_PD;
    ctx.currentIA().ia_rsp_ = ia_rsp;

    // Extract prefixes that the client is trying to renew.
    OptionCollection addrs = ia->getOptions();
    for (OptionCollection::const_iterator it = addrs.begin();
         it != addrs.end(); ++it) {
        if (it->second->getType() != D6O_IAPREFIX) {
            continue;
        }
        Option6IAPrefixPtr prf = boost::dynamic_pointer_cast<Option6IAPrefix>(it->second);
        if (!prf) {
            // That's weird. Option code was ok, but the object type was not.
            // This should never happen. The only case would be with badly
            // mis-implemented hook libraries that insert invalid option objects.
            // There's no way to protect against this.
            continue;
        }

        // Put the client's prefix into the hints list.
        ctx.currentIA().addHint(prf->getAddress(), prf->getLength());
    }

    // Call Allocation Engine and attempt to renew leases. Number of things
    // may happen. Leases may be extended, revoked (if the lease is no longer
    // valid or reserved for someone else), or new leases may be added.
    // Important parameters are:
    // - returned container - current valid leases
    // - old_leases - leases that used to be, but are no longer valid
    // - changed_leases - leases that have FQDN changed (not really important
    //                    in PD context)
    Lease6Collection leases = alloc_engine_->renewLeases6(ctx);

    // For each IA inserted by the client we have to determine what to do
    // about included prefixes and notify the client. We will iterate over
    // those prefixes and remove those that we have already processed. We
    // don't want to remove them from the context, so we need to copy them
    // into temporary container.
    AllocEngine::HintContainer hints = ctx.currentIA().hints_;

    const bool pd_exclude_requested = requestedInORO(query, D6O_PD_EXCLUDE);

    // For all the leases we have now, add the IAPREFIX with non-zero lifetimes
    for (Lease6Collection::const_iterator l = leases.begin(); l != leases.end(); ++l) {

        Option6IAPrefixPtr prf(new Option6IAPrefix(D6O_IAPREFIX,
                               (*l)->addr_, (*l)->prefixlen_,
                               (*l)->preferred_lft_, (*l)->valid_lft_));
        ia_rsp->addOption(prf);


        if (pd_exclude_requested) {
            // PD exclude option has been requested via ORO, thus we need to
            // include it if the pool configuration specifies this option.
            Pool6Ptr pool = boost::dynamic_pointer_cast<
                Pool6>(subnet->getPool(Lease::TYPE_PD, (*l)->addr_));

            if (pool) {
                Option6PDExcludePtr pd_exclude_option = pool->getPrefixExcludeOption();
                if (pd_exclude_option) {
                    prf->addOption(pd_exclude_option);
                }
            }
        }


        LOG_INFO(lease6_logger, DHCP6_PD_LEASE_RENEW)
            .arg(query->getLabel())
            .arg((*l)->addr_.toText())
            .arg(static_cast<int>((*l)->prefixlen_))
            .arg(ia->getIAID());

        // Now remove this prefix from the hints list.
        AllocEngine::ResourceType hint_type((*l)->addr_, (*l)->prefixlen_);
        hints.erase(std::remove(hints.begin(), hints.end(), hint_type),
                    hints.end());
    }

    /// For the leases that we just retired, send the prefixes with 0 lifetimes.
    for (Lease6Collection::const_iterator l = ctx.currentIA().old_leases_.begin();
                                          l != ctx.currentIA().old_leases_.end(); ++l) {

        // Send a prefix with zero lifetimes only when this lease belonged to
        // this client. Do not send it when we're reusing an old lease that belonged
        // to someone else.
        if (equalValues(query->getClientId(), (*l)->duid_)) {
            Option6IAPrefixPtr prefix(new Option6IAPrefix(D6O_IAPREFIX, (*l)->addr_,
                                                          (*l)->prefixlen_, 0, 0));
            ia_rsp->addOption(prefix);
        }

        // Now remove this prefix from the hints list.
        AllocEngine::ResourceType hint_type((*l)->addr_, (*l)->prefixlen_);
        hints.erase(std::remove(hints.begin(), hints.end(), hint_type), hints.end());
    }

    // Finally, if there are any prefixes requested that we haven't dealt with
    // already, inform the client that he can't have them.
    for (AllocEngine::HintContainer::const_iterator prefix = hints.begin();
         prefix != hints.end(); ++prefix) {

        // Send the prefix with the zero lifetimes only if the prefix
        // contains non-zero value. A zero value indicates that the hint was
        // for the prefix length.
        if (!prefix->first.isV6Zero()) {
            OptionPtr prefix_opt(new Option6IAPrefix(D6O_IAPREFIX, prefix->first,
                                                     prefix->second, 0, 0));
            ia_rsp->addOption(prefix_opt);
        }
    }

    // All is left is to insert the status code.
    if (leases.empty()) {

        // The server wasn't able allocate new lease and renew an existing
        // lease. In that case, the server sends NoPrefixAvail per RFC 8415.
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp,
                                           STATUS_NoPrefixAvail,
                                           "Sorry, no prefixes could be"
                                           " assigned at this time."));
    }

    return (ia_rsp);
}

void
Dhcpv6Srv::extendLeases(const Pkt6Ptr& query, Pkt6Ptr& reply,
                       AllocEngine::ClientContext6& ctx) {

    // We will try to extend lease lifetime for all IA options in the client's
    // Renew or Rebind message.
    /// @todo add support for IA_TA

    // For the lease extension it is critical that the client has sent
    // DUID. There is no need to check for the presence of the DUID here
    // because we have already checked it in the sanityCheck().

    for (OptionCollection::iterator opt = query->options_.begin();
         opt != query->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = extendIA_NA(query, reply, ctx,
                                               boost::dynamic_pointer_cast<
                                                   Option6IA>(opt->second));
            if (answer_opt) {
                reply->addOption(answer_opt);
            }
            break;
        }

        case D6O_IA_PD: {
            OptionPtr answer_opt = extendIA_PD(query, ctx,
                                               boost::dynamic_pointer_cast<
                                                   Option6IA>(opt->second));
            if (answer_opt) {
                reply->addOption(answer_opt);
            }
            break;
        }

        default:
            break;
        }
    }
}

void
Dhcpv6Srv::releaseLeases(const Pkt6Ptr& release, Pkt6Ptr& reply,
                         AllocEngine::ClientContext6& ctx) {

    // We need to release addresses for all IA options in the client's
    // RELEASE message.

    /// @todo Add support for IA_TA
    /// @todo Consider supporting more than one address in a single IA.
    /// It is allowed by RFC 8415, but it is not widely implemented. The only
    /// software that supports that is Dibbler, but its author seriously doubts
    /// if anyone is really using it. Clients that want more than one address
    /// or prefix just include more instances of IA options.

    // Let's set the status to be success by default. We can override it with
    // error status if needed. The important thing to understand here is that
    // the global status code may be set to success only if all IA options were
    // handled properly. Therefore the releaseIA_NA and releaseIA_PD options
    // may turn the status code to some error, but can't turn it back to success.
    int general_status = STATUS_Success;
    for (OptionCollection::iterator opt = release->options_.begin();
         opt != release->options_.end(); ++opt) {
        Lease6Ptr old_lease;
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = releaseIA_NA(ctx.duid_, release, general_status,
                                                boost::dynamic_pointer_cast<Option6IA>(opt->second),
                                                old_lease);
            if (answer_opt) {
                reply->addOption(answer_opt);
            }
            break;
        }
        case D6O_IA_PD: {
            OptionPtr answer_opt = releaseIA_PD(ctx.duid_, release, general_status,
                                                boost::dynamic_pointer_cast<Option6IA>(opt->second),
                                                old_lease);
            if (answer_opt) {
                reply->addOption(answer_opt);
            }
            break;
        }
        // @todo: add support for IA_TA
        default:
            // remaining options are stateless and thus ignored in this context
            ;
        }

        // Store the old lease.
        if (old_lease) {
            ctx.currentIA().old_leases_.push_back(old_lease);
        }
    }

    // Include top-level status code as well.
    reply->addOption(createStatusCode(*release, general_status,
                     "Summary status for all processed IA_NAs"));
}

OptionPtr
Dhcpv6Srv::releaseIA_NA(const DuidPtr& duid, const Pkt6Ptr& query,
                        int& general_status, boost::shared_ptr<Option6IA> ia,
                        Lease6Ptr& old_lease) {

    LOG_DEBUG(lease6_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_NA_RELEASE)
        .arg(query->getLabel())
        .arg(ia->getIAID());


    // Release can be done in one of two ways:
    // Approach 1: extract address from client's IA_NA and see if it belongs
    // to this particular client.
    // Approach 2: find a subnet for this client, get a lease for
    // this subnet/duid/iaid and check if its content matches to what the
    // client is asking us to release.
    //
    // This method implements approach 1.

    // That's our response
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

    Option6IAAddrPtr release_addr = boost::dynamic_pointer_cast<Option6IAAddr>
        (ia->getOption(D6O_IAADDR));
    if (!release_addr) {
        ia_rsp->addOption(createStatusCode(*query, STATUS_NoBinding,
                                           "You did not include an address in your RELEASE"));
        general_status = STATUS_NoBinding;
        return (ia_rsp);
    }

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                            release_addr->getAddress());

    if (!lease) {
        // client releasing a lease that we don't know about.

        // Insert status code NoBinding.
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid, can't release."));
        general_status = STATUS_NoBinding;

        return (ia_rsp);
    }

    if (!lease->duid_) {
        // Something is gravely wrong here. We do have a lease, but it does not
        // have mandatory DUID information attached. Someone was messing with our
        // database.

        LOG_ERROR(lease6_logger, DHCP6_LEASE_NA_WITHOUT_DUID)
            .arg(query->getLabel())
            .arg(release_addr->getAddress().toText());

        general_status = STATUS_UnspecFail;
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_UnspecFail,
                          "Database consistency check failed when trying to RELEASE"));
        return (ia_rsp);
    }

    if (*duid != *(lease->duid_)) {

        // Sorry, it's not your address. You can't release it.
        LOG_INFO(lease6_logger, DHCP6_RELEASE_NA_FAIL_WRONG_DUID)
            .arg(query->getLabel())
            .arg(release_addr->getAddress().toText())
            .arg(lease->duid_->toText());

        general_status = STATUS_NoBinding;
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                          "This address does not belong to you, you can't release it"));
        return (ia_rsp);
    }

    if (ia->getIAID() != lease->iaid_) {
        // This address belongs to this client, but to a different IA
        LOG_WARN(lease6_logger, DHCP6_RELEASE_NA_FAIL_WRONG_IAID)
            .arg(query->getLabel())
            .arg(release_addr->getAddress().toText())
            .arg(lease->iaid_)
            .arg(ia->getIAID());
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                          "This is your address, but you used wrong IAID"));
        general_status = STATUS_NoBinding;
        return (ia_rsp);
    }

    // It is not necessary to check if the address matches as we used
    // getLease6(addr) method that is supposed to return a proper lease.

    bool skip = false;
    // Execute all callouts registered for packet6_send
    if (HooksManager::calloutsPresent(Hooks.hook_index_lease6_release_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(query);

        // Delete all previous arguments
        callout_handle->deleteAllArguments();

        // Pass the original packet
        callout_handle->setArgument("query6", query);

        // Pass the lease to be updated
        callout_handle->setArgument("lease6", lease);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_lease6_release_, *callout_handle);

        // Callouts decided to skip the next processing step. The next
        // processing step would to send the packet, so skip at this
        // stage means "drop response".
        if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
            (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
            skip = true;
            LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_LEASE6_RELEASE_NA_SKIP)
                .arg(query->getLabel());
        }
    }

    // Ok, we've passed all checks. Let's release this address.
    bool success = false; // was the removal operation successful?

    if (!skip) {
        success = LeaseMgrFactory::instance().deleteLease(lease->addr_);
    }

    // Here the success should be true if we removed lease successfully
    // and false if skip flag was set or the removal failed for whatever reason

    if (!success) {
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_UnspecFail,
                          "Server failed to release a lease"));

        LOG_ERROR(lease6_logger, DHCP6_RELEASE_NA_FAIL)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(lease->iaid_);
        general_status = STATUS_UnspecFail;

        return (ia_rsp);
    } else {
        old_lease = lease;

        LOG_INFO(lease6_logger, DHCP6_RELEASE_NA)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(lease->iaid_);

        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_Success,
                          "Lease released. Thank you, please come again."));

        // Need to decrease statistic for assigned addresses.
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", lease->subnet_id_, "assigned-nas"),
            static_cast<int64_t>(-1));

        // Check if a lease has flags indicating that the FQDN update has
        // been performed. If so, create NameChangeRequest which removes
        // the entries.
        queueNCR(CHG_REMOVE, lease);

        return (ia_rsp);
    }
}

OptionPtr
Dhcpv6Srv::releaseIA_PD(const DuidPtr& duid, const Pkt6Ptr& query,
                        int& general_status, boost::shared_ptr<Option6IA> ia,
                        Lease6Ptr& old_lease) {
    // Release can be done in one of two ways:
    // Approach 1: extract address from client's IA_NA and see if it belongs
    // to this particular client.
    // Approach 2: find a subnet for this client, get a lease for
    // this subnet/duid/iaid and check if its content matches to what the
    // client is asking us to release.
    //
    // This method implements approach 1.

    // That's our response. We will fill it in as we check the lease to be
    // released.
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_PD, ia->getIAID()));

    boost::shared_ptr<Option6IAPrefix> release_prefix =
        boost::dynamic_pointer_cast<Option6IAPrefix>(ia->getOption(D6O_IAPREFIX));
    if (!release_prefix) {
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                          "You did not include a prefix in your RELEASE"));
        general_status = STATUS_NoBinding;
        return (ia_rsp);
    }

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD,
                                                            release_prefix->getAddress());

    if (!lease) {
        // Client releasing a lease that we don't know about.

        // Insert status code NoBinding.
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid, can't release."));
        general_status = STATUS_NoBinding;

        return (ia_rsp);
    }

    if (!lease->duid_) {
        // Something is gravely wrong here. We do have a lease, but it does not
        // have mandatory DUID information attached. Someone was messing with our
        // database.
        LOG_ERROR(lease6_logger, DHCP6_LEASE_PD_WITHOUT_DUID)
            .arg(query->getLabel())
            .arg(release_prefix->getAddress().toText())
            .arg(static_cast<int>(release_prefix->getLength()));

        general_status = STATUS_UnspecFail;
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_UnspecFail,
                          "Database consistency check failed when trying to RELEASE"));
        return (ia_rsp);
    }

    if (*duid != *(lease->duid_)) {
        // Sorry, it's not your address. You can't release it.
        LOG_INFO(lease6_logger, DHCP6_RELEASE_PD_FAIL_WRONG_DUID)
            .arg(query->getLabel())
            .arg(release_prefix->getAddress().toText())
            .arg(static_cast<int>(release_prefix->getLength()))
            .arg(lease->duid_->toText());

        general_status = STATUS_NoBinding;
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                          "This address does not belong to you, you can't release it"));
        return (ia_rsp);
    }

    if (ia->getIAID() != lease->iaid_) {
        // This address belongs to this client, but to a different IA
        LOG_WARN(lease6_logger, DHCP6_RELEASE_PD_FAIL_WRONG_IAID)
            .arg(query->getLabel())
            .arg(release_prefix->getAddress().toText())
            .arg(static_cast<int>(release_prefix->getLength()))
            .arg(lease->iaid_)
            .arg(ia->getIAID());
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                          "This is your address, but you used wrong IAID"));
        general_status = STATUS_NoBinding;
        return (ia_rsp);
    }

    // It is not necessary to check if the address matches as we used
    // getLease6(addr) method that is supposed to return a proper lease.

    bool skip = false;
    // Execute all callouts registered for packet6_send
    if (HooksManager::calloutsPresent(Hooks.hook_index_lease6_release_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(query);

        // Pass the original packet
        callout_handle->setArgument("query6", query);

        // Pass the lease to be updated
        callout_handle->setArgument("lease6", lease);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_lease6_release_, *callout_handle);

        skip = callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP;
    }

    // Ok, we've passed all checks. Let's release this prefix.
    bool success = false; // was the removal operation successful?

    if (!skip) {
        success = LeaseMgrFactory::instance().deleteLease(lease->addr_);
    } else {
        // Callouts decided to skip the next processing step. The next
        // processing step would to send the packet, so skip at this
        // stage means "drop response".
        LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_LEASE6_RELEASE_PD_SKIP)
            .arg(query->getLabel());
    }

    // Here the success should be true if we removed lease successfully
    // and false if skip flag was set or the removal failed for whatever reason

    if (!success) {
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_UnspecFail,
                          "Server failed to release a lease"));

        LOG_ERROR(lease6_logger, DHCP6_RELEASE_PD_FAIL)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(static_cast<int>(lease->prefixlen_))
            .arg(lease->iaid_);
        general_status = STATUS_UnspecFail;

    } else {
        old_lease = lease;

        LOG_INFO(lease6_logger, DHCP6_RELEASE_PD)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(static_cast<int>(lease->prefixlen_))
            .arg(lease->iaid_);

        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_Success,
                          "Lease released. Thank you, please come again."));

        // Need to decrease statistic for assigned prefixes.
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", lease->subnet_id_, "assigned-pds"),
            static_cast<int64_t>(-1));
    }

    return (ia_rsp);
}


Pkt6Ptr
Dhcpv6Srv::processSolicit(AllocEngine::ClientContext6& ctx) {

    Pkt6Ptr solicit = ctx.query_;
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, solicit->getTransid()));

    // Handle Rapid Commit option, if present.
    if (ctx.subnet_ && ctx.subnet_->getRapidCommit()) {
        OptionPtr opt_rapid_commit = solicit->getOption(D6O_RAPID_COMMIT);
        if (opt_rapid_commit) {

            LOG_DEBUG(options6_logger, DBG_DHCP6_DETAIL, DHCP6_RAPID_COMMIT)
                .arg(solicit->getLabel());

            // If Rapid Commit has been sent by the client, change the
            // response type to Reply and include Rapid Commit option.
            response->setType(DHCPV6_REPLY);
            response->addOption(opt_rapid_commit);
        }
    }

    // "Fake" allocation is the case when the server is processing the Solicit
    // message without the Rapid Commit option and advertises a lease to
    // the client, but doesn't commit this lease to the lease database. If
    // the Solicit contains the Rapid Commit option and the server is
    // configured to honor the Rapid Commit option, or the client has sent
    // the Request message, the lease will be committed to the lease
    // database. The type of the server's response may be used to determine
    // if this is the fake allocation case or not. When the server sends
    // Reply message it means that it is committing leases. Other message
    // type (Advertise) means that server is not committing leases (fake
    // allocation).
    ctx.fake_allocation_ = (response->getType() != DHCPV6_REPLY);

    processClientFqdn(solicit, response, ctx);
    assignLeases(solicit, response, ctx);

    setReservedClientClasses(solicit, ctx);
    requiredClassify(solicit, ctx);

    copyClientOptions(solicit, response);
    CfgOptionList co_list;
    buildCfgOptionList(solicit, ctx, co_list);
    appendDefaultOptions(solicit, response, co_list);
    appendRequestedOptions(solicit, response, co_list);
    appendRequestedVendorOptions(solicit, response, ctx, co_list);

    updateReservedFqdn(ctx, response);

    // Only generate name change requests if sending a Reply as a result
    // of receiving Rapid Commit option.
    if (response->getType() == DHCPV6_REPLY) {
        createNameChangeRequests(response, ctx);
    }

    return (response);
}

Pkt6Ptr
Dhcpv6Srv::processRequest(AllocEngine::ClientContext6& ctx) {

    Pkt6Ptr request = ctx.query_;
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, request->getTransid()));

    processClientFqdn(request, reply, ctx);
    assignLeases(request, reply, ctx);

    setReservedClientClasses(request, ctx);
    requiredClassify(request, ctx);

    copyClientOptions(request, reply);
    CfgOptionList co_list;
    buildCfgOptionList(request, ctx, co_list);
    appendDefaultOptions(request, reply, co_list);
    appendRequestedOptions(request, reply, co_list);
    appendRequestedVendorOptions(request, reply, ctx, co_list);

    updateReservedFqdn(ctx, reply);
    generateFqdn(reply);
    createNameChangeRequests(reply, ctx);

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processRenew(AllocEngine::ClientContext6& ctx) {

    Pkt6Ptr renew = ctx.query_;
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, renew->getTransid()));

    processClientFqdn(renew, reply, ctx);
    extendLeases(renew, reply, ctx);

    setReservedClientClasses(renew, ctx);
    requiredClassify(renew, ctx);

    copyClientOptions(renew, reply);
    CfgOptionList co_list;
    buildCfgOptionList(renew, ctx, co_list);
    appendDefaultOptions(renew, reply, co_list);
    appendRequestedOptions(renew, reply, co_list);
    appendRequestedVendorOptions(renew, reply, ctx, co_list);

    updateReservedFqdn(ctx, reply);
    generateFqdn(reply);
    createNameChangeRequests(reply, ctx);

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processRebind(AllocEngine::ClientContext6& ctx) {

    Pkt6Ptr rebind = ctx.query_;
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, rebind->getTransid()));

    processClientFqdn(rebind, reply, ctx);
    extendLeases(rebind, reply, ctx);

    setReservedClientClasses(rebind, ctx);
    requiredClassify(rebind, ctx);

    copyClientOptions(rebind, reply);
    CfgOptionList co_list;
    buildCfgOptionList(rebind, ctx, co_list);
    appendDefaultOptions(rebind, reply, co_list);
    appendRequestedOptions(rebind, reply, co_list);
    appendRequestedVendorOptions(rebind, reply, ctx, co_list);

    updateReservedFqdn(ctx, reply);
    generateFqdn(reply);
    createNameChangeRequests(reply, ctx);

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processConfirm(AllocEngine::ClientContext6& ctx) {

    Pkt6Ptr confirm = ctx.query_;
    setReservedClientClasses(confirm, ctx);
    requiredClassify(confirm, ctx);

    // Get IA_NAs from the Confirm. If there are none, the message is
    // invalid and must be discarded. There is nothing more to do.
    OptionCollection ias = confirm->getOptions(D6O_IA_NA);
    if (ias.empty()) {
        return (Pkt6Ptr());
    }

    // The server sends Reply message in response to Confirm.
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, confirm->getTransid()));
    // Make sure that the necessary options are included.
    copyClientOptions(confirm, reply);
    CfgOptionList co_list;
    buildCfgOptionList(confirm, ctx, co_list);
    appendDefaultOptions(confirm, reply, co_list);
    appendRequestedOptions(confirm, reply, co_list);
    appendRequestedVendorOptions(confirm, reply, ctx, co_list);
    // Indicates if at least one address has been verified. If no addresses
    // are verified it means that the client has sent no IA_NA options
    // or no IAAddr options and that client's message has to be discarded.
    bool verified = false;
    // Check if subnet was selected for the message. If no subnet
    // has been selected, the client is not on link.
    SubnetPtr subnet = ctx.subnet_;

    // Regardless if the subnet has been selected or not, we will iterate
    // over the IA_NA options to check if they hold any addresses. If there
    // are no, the Confirm is discarded.
    // Check addresses in IA_NA options and make sure they are appropriate.
    for (OptionCollection::const_iterator ia = ias.begin();
         ia != ias.end(); ++ia) {
        const OptionCollection& opts = ia->second->getOptions();
        for (OptionCollection::const_iterator opt = opts.begin();
             opt != opts.end(); ++opt) {
            // Ignore options other than IAAddr.
            if (opt->second->getType() == D6O_IAADDR) {
                // Check that the address is in range in the subnet selected.
                Option6IAAddrPtr iaaddr = boost::dynamic_pointer_cast<
                    Option6IAAddr>(opt->second);
                // If there is subnet selected and the address has been included
                // in IA_NA, mark it verified and verify that it belongs to the
                // subnet.
                if (iaaddr) {
                    // If at least one address is not in range, then return
                    // the NotOnLink status code.
                    if (subnet && !subnet->inRange(iaaddr->getAddress())) {
                        std::ostringstream status_msg;
                        status_msg << "Address " << iaaddr->getAddress()
                                   << " is not on link.";
                        reply->addOption(createStatusCode(*confirm,
                                                          STATUS_NotOnLink,
                                                          status_msg.str()));
                        return (reply);
                    }
                    verified = true;
                } else {
                    isc_throw(Unexpected, "failed to cast the IA Address option"
                              " to the Option6IAAddrPtr. This is programming"
                              " error and should be reported");
                }
            }
        }
    }

    // It seems that the client hasn't included any addresses in which case
    // the Confirm must be discarded.
    if (!verified) {
        return (Pkt6Ptr());
    }

    // If there is a subnet, there were addresses in IA_NA options and the
    // addresses where consistent with the subnet then the client is on link.
    if (subnet) {
        // All addresses in range, so return success.
        reply->addOption(createStatusCode(*confirm, STATUS_Success,
                                          "All addresses are on-link"));
    } else {
        reply->addOption(createStatusCode(*confirm, STATUS_NotOnLink,
                                          "No subnet selected"));
    }

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processRelease(AllocEngine::ClientContext6& ctx) {

    Pkt6Ptr release = ctx.query_;
    setReservedClientClasses(release, ctx);
    requiredClassify(release, ctx);

    // Create an empty Reply message.
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, release->getTransid()));

    // Copy client options (client-id, also relay information if present)
    copyClientOptions(release, reply);

    // Get the configured option list
    CfgOptionList co_list;
    // buildCfgOptionList(release, ctx, co_list);
    appendDefaultOptions(release, reply, co_list);

    releaseLeases(release, reply, ctx);

    /// @todo If client sent a release and we should remove outstanding
    /// DNS records.

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processDecline(AllocEngine::ClientContext6& ctx) {

    Pkt6Ptr decline = ctx.query_;
    setReservedClientClasses(decline, ctx);
    requiredClassify(decline, ctx);

    // Create an empty Reply message.
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, decline->getTransid()));

    // Copy client options (client-id, also relay information if present)
    copyClientOptions(decline, reply);

    // Get the configured option list
    CfgOptionList co_list;
    buildCfgOptionList(decline, ctx, co_list);

    // Include server-id
    appendDefaultOptions(decline, reply, co_list);

    if (declineLeases(decline, reply, ctx)) {
        return (reply);
    } else {

        // declineLeases returns false only if the hooks set the next step
        // status to DROP. We'll just doing as requested.
        return (Pkt6Ptr());
    }
}

bool
Dhcpv6Srv::declineLeases(const Pkt6Ptr& decline, Pkt6Ptr& reply,
                         AllocEngine::ClientContext6& ctx) {

    // We need to decline addresses for all IA_NA options in the client's
    // DECLINE message.

    // Let's set the status to be success by default. We can override it with
    // error status if needed. The important thing to understand here is that
    // the global status code may be set to success only if all IA options were
    // handled properly. Therefore the declineIA  options
    // may turn the status code to some error, but can't turn it back to success.
    int general_status = STATUS_Success;

    for (OptionCollection::iterator opt = decline->options_.begin();
         opt != decline->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = declineIA(decline, ctx.duid_, general_status,
                                             boost::dynamic_pointer_cast<Option6IA>(opt->second),
                                             ctx.new_leases_);
            if (answer_opt) {

                // We have an answer, let's use it.
                reply->addOption(answer_opt);
            } else {

                // The only case when declineIA could return NULL is if one of the
                // hook callouts set next step status to DROP. We just need to drop
                // this packet.
                return (false);
            }
            break;
        }
        default:
            // We don't care for the remaining options
            ;
        }
    }

    return (true);
}

OptionPtr
Dhcpv6Srv::declineIA(const Pkt6Ptr& decline, const DuidPtr& duid,
                     int& general_status, boost::shared_ptr<Option6IA> ia,
                     Lease6Collection& new_leases) {

    LOG_DEBUG(lease6_logger, DBG_DHCP6_DETAIL, DHCP6_DECLINE_PROCESS_IA)
        .arg(decline->getLabel())
        .arg(ia->getIAID());

    // Decline can be done in one of two ways:
    // Approach 1: extract address from client's IA_NA and see if it belongs
    // to this particular client.
    // Approach 2: find a subnet for this client, get a lease for
    // this subnet/duid/iaid and check if its content matches to what the
    // client is asking us to decline.
    //
    // This method implements approach 1.

    // That's our response
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

    const OptionCollection& opts = ia->getOptions();
    int total_addrs = 0; // Let's count the total number of addresses.
    for (OptionCollection::const_iterator opt = opts.begin(); opt != opts.end();
         ++opt) {

        // Let's ignore nested options other than IAADDR (there shouldn't be anything
        // else in IA_NA in Decline message, but let's be on the safe side).
        if (opt->second->getType() != D6O_IAADDR) {
            continue;
        }
        Option6IAAddrPtr decline_addr = boost::dynamic_pointer_cast<Option6IAAddr>
            (opt->second);
        if (!decline_addr) {
            continue;
        }

        total_addrs++;

        Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                                decline_addr->getAddress());

        if (!lease) {
            // Client trying to decline a lease that we don't know about.
            LOG_INFO(lease6_logger, DHCP6_DECLINE_FAIL_NO_LEASE)
                .arg(decline->getLabel()).arg(decline_addr->getAddress().toText());

            // According to RFC 8415, section 18.3.8:
            // "For each IA in the Decline message for which the server has no
            // binding information, the server adds an IA option using the IAID
            // from the Decline message and includes a Status Code option with
            // the value NoBinding in the IA option".
            setStatusCode(ia_rsp, createStatusCode(*decline, *ia_rsp, STATUS_NoBinding,
                                  "Server does not know about such an address."));

            // In the same section of RFC 8415:
            // "The server ignores addresses not assigned to the IAs (though it may"
            // choose to log an error if it finds such addresses)."
            continue; // There may be other addresses.
        }

        if (!lease->duid_) {
            // Something is gravely wrong here. We do have a lease, but it does not
            // have mandatory DUID information attached. Someone was messing with our
            // database.

            LOG_ERROR(lease6_logger, DHCP6_DECLINE_FAIL_LEASE_WITHOUT_DUID)
                .arg(decline->getLabel())
                .arg(decline_addr->getAddress().toText());

            ia_rsp->addOption(createStatusCode(*decline, *ia_rsp, STATUS_UnspecFail,
                    "Database consistency check failed when attempting Decline."));

            continue;
        }

        // Ok, there's a sane lease with an address. Let's check if DUID matches first.
        if (*duid != *(lease->duid_)) {

            // Sorry, it's not your address. You can't release it.
            LOG_INFO(lease6_logger, DHCP6_DECLINE_FAIL_DUID_MISMATCH)
                .arg(decline->getLabel())
                .arg(decline_addr->getAddress().toText())
                .arg(lease->duid_->toText());

            ia_rsp->addOption(createStatusCode(*decline, *ia_rsp, STATUS_NoBinding,
                     "This address does not belong to you, you can't decline it"));

            continue;
        }

        // Let's check if IAID matches.
        if (ia->getIAID() != lease->iaid_) {
            // This address belongs to this client, but to a different IA
            LOG_INFO(lease6_logger, DHCP6_DECLINE_FAIL_IAID_MISMATCH)
                .arg(decline->getLabel())
                .arg(lease->addr_.toText())
                .arg(ia->getIAID())
                .arg(lease->iaid_);
            setStatusCode(ia_rsp, createStatusCode(*decline, *ia_rsp, STATUS_NoBinding,
                              "This is your address, but you used wrong IAID"));

            continue;
        }

        // Ok, all is good. Decline this lease.
        if (!declineLease(decline, lease, ia_rsp)) {
            // declineLease returns false only when hook callouts set the next
            // step status to drop. We just propagate the bad news here.
            return (OptionPtr());

        } else {
            new_leases.push_back(lease);
        }
    }

    if (total_addrs == 0) {
        setStatusCode(ia_rsp, createStatusCode(*decline, *ia_rsp, STATUS_NoBinding,
                                               "No addresses sent in IA_NA"));
        general_status = STATUS_NoBinding;
    }

    return (ia_rsp);
}

void
Dhcpv6Srv::setStatusCode(boost::shared_ptr<isc::dhcp::Option6IA>& container,
                         const OptionPtr& status) {
    // Let's delete any old status code we may have.
    container->delOption(D6O_STATUS_CODE);

    container->addOption(status);
}

bool
Dhcpv6Srv::declineLease(const Pkt6Ptr& decline, const Lease6Ptr lease,
                        boost::shared_ptr<Option6IA> ia_rsp) {
    // We do not want to decrease the assigned-nas at this time. While
    // technically a declined address is no longer allocated, the primary usage
    // of the assigned-addresses statistic is to monitor pool utilization. Most
    // people would forget to include declined-addresses in the calculation,
    // and simply do assigned-addresses/total-addresses. This would have a bias
    // towards under-representing pool utilization, if we decreased allocated
    // immediately after receiving DHCPDECLINE, rather than later when we recover
    // the address.

    // Let's call lease6_decline hooks if necessary.
    if (HooksManager::calloutsPresent(Hooks.hook_index_lease6_decline_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(decline);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt6> query6_options_copy(decline);

        // Pass incoming packet as argument
        callout_handle->setArgument("query6", decline);
        callout_handle->setArgument("lease6", lease);

        // Call callouts
        HooksManager::callCallouts(Hooks.hook_index_lease6_decline_,
                                   *callout_handle);

        // Callouts decided to SKIP the next processing step. The next
        // processing step would to actually decline the lease, so we'll
        // keep the lease as is.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_DETAIL, DHCP6_HOOK_DECLINE_SKIP)
                .arg(decline->getLabel())
                .arg(decline->getIface())
                .arg(lease->addr_.toText());
            return (true);
        }

        // Callouts decided to DROP the packet. Let's simply log it and
        // return false, so callers will act accordingly.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_DETAIL, DHCP6_HOOK_DECLINE_DROP)
                .arg(decline->getLabel())
                .arg(decline->getIface())
                .arg(lease->addr_.toText());
            return (false);
        }
    }

    // Check if a lease has flags indicating that the FQDN update has
    // been performed. If so, create NameChangeRequest which removes
    // the entries. This method does all necessary checks.
    queueNCR(CHG_REMOVE, lease);

    // Bump up the subnet-specific statistic.
    StatsMgr::instance().addValue(
        StatsMgr::generateName("subnet", lease->subnet_id_, "declined-addresses"),
        static_cast<int64_t>(1));

    // Global declined addresses counter.
    StatsMgr::instance().addValue("declined-addresses", static_cast<int64_t>(1));

    // We need to disassociate the lease from the client. Once we move a lease
    // to declined state, it is no longer associated with the client in any
    // way.
    lease->decline(CfgMgr::instance().getCurrentCfg()->getDeclinePeriod());
    LeaseMgrFactory::instance().updateLease6(lease);

    LOG_INFO(lease6_logger, DHCP6_DECLINE_LEASE).arg(decline->getLabel())
        .arg(lease->addr_.toText()).arg(lease->valid_lft_);

    ia_rsp->addOption(createStatusCode(*decline, *ia_rsp, STATUS_Success,
                      "Lease declined. Hopefully the next one will be better."));

    return (true);
}

Pkt6Ptr
Dhcpv6Srv::processInfRequest(AllocEngine::ClientContext6& ctx) {

    Pkt6Ptr inf_request = ctx.query_;
    setReservedClientClasses(inf_request, ctx);
    requiredClassify(inf_request, ctx);

    // Create a Reply packet, with the same trans-id as the client's.
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, inf_request->getTransid()));

    // Copy client options (client-id, also relay information if present)
    copyClientOptions(inf_request, reply);

    // Build the configured option list for append methods
    CfgOptionList co_list;
    buildCfgOptionList(inf_request, ctx, co_list);

    // Append default options, i.e. options that the server is supposed
    // to put in all messages it sends (server-id for now, but possibly other
    // options once we start supporting authentication)
    appendDefaultOptions(inf_request, reply, co_list);

    // Try to assign options that were requested by the client.
    appendRequestedOptions(inf_request, reply, co_list);

    // Try to assign vendor options that were requested by the client.
    appendRequestedVendorOptions(inf_request, reply, ctx, co_list);

    return (reply);
}

void
Dhcpv6Srv::processDhcp4Query(const Pkt6Ptr& dhcp4_query) {

    // flags are in transid
    // uint32_t flags = dhcp4_query->getTransid();
    // do nothing with DHCPV4_QUERY_FLAGS_UNICAST

    // Get the DHCPv4 message option
    OptionPtr dhcp4_msg = dhcp4_query->getOption(D6O_DHCPV4_MSG);
    if (dhcp4_msg) {
        try {
            // Forward the whole message to the DHCPv4 server via IPC
            Dhcp6to4Ipc::instance().send(dhcp4_query);
        } catch (...) {
            // Assume the error was already logged
            return;
        }
    }

    // This method does not return anything as we always sent back
    // the response via Dhcp6To4Ipc.
}

void Dhcpv6Srv::classifyByVendor(const Pkt6Ptr& pkt, std::string& classes) {
    OptionVendorClassPtr vclass = boost::dynamic_pointer_cast<
        OptionVendorClass>(pkt->getOption(D6O_VENDOR_CLASS));

    if (!vclass || vclass->getTuplesNum() == 0) {
        return;
    }

    if (vclass->hasTuple(DOCSIS3_CLASS_MODEM)) {
        pkt->addClass(VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_MODEM);
        classes += VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_MODEM + " ";

    } else if (vclass->hasTuple(DOCSIS3_CLASS_EROUTER)) {
        pkt->addClass(VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_EROUTER);
        classes += VENDOR_CLASS_PREFIX + DOCSIS3_CLASS_EROUTER + " ";

    } else {
        pkt->addClass(VENDOR_CLASS_PREFIX + vclass->getTuple(0).getText());
        classes + VENDOR_CLASS_PREFIX + vclass->getTuple(0).getText() + " ";
    }
}

void Dhcpv6Srv::classifyPacket(const Pkt6Ptr& pkt) {
    // All packets belongs to ALL
    pkt->addClass("ALL");
    string classes = "ALL ";

    // First: built-in vendor class processing
    classifyByVendor(pkt, classes);

    // Run match expressions on classes not depending on KNOWN/UNKNOWN.
    evaluateClasses(pkt, false);
}

void Dhcpv6Srv::evaluateClasses(const Pkt6Ptr& pkt, bool depend_on_known) {
    // Note getClientClassDictionary() cannot be null
    const ClientClassDictionaryPtr& dict =
        CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
    const ClientClassDefListPtr& defs_ptr = dict->getClasses();
    for (ClientClassDefList::const_iterator it = defs_ptr->cbegin();
         it != defs_ptr->cend(); ++it) {
        // Note second cannot be null
        const ExpressionPtr& expr_ptr = (*it)->getMatchExpr();
        // Nothing to do without an expression to evaluate
        if (!expr_ptr) {
            continue;
        }
        // Not the right time if only when required
        if ((*it)->getRequired()) {
            continue;
        }
        // Not the right pass.
        if ((*it)->getDependOnKnown() != depend_on_known) {
            continue;
        }
        // Evaluate the expression which can return false (no match),
        // true (match) or raise an exception (error)
        try {
            bool status = evaluateBool(*expr_ptr, *pkt);
            if (status) {
                LOG_INFO(dhcp6_logger, EVAL_RESULT)
                    .arg((*it)->getName())
                    .arg(status);
                // Matching: add the class
                pkt->addClass((*it)->getName());
            } else {
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, EVAL_RESULT)
                    .arg((*it)->getName())
                    .arg(status);
            }
        } catch (const Exception& ex) {
            LOG_ERROR(dhcp6_logger, EVAL_RESULT)
                .arg((*it)->getName())
                .arg(ex.what());
        } catch (...) {
            LOG_ERROR(dhcp6_logger, EVAL_RESULT)
                .arg((*it)->getName())
                .arg("get exception?");
        }
    }
}

void
Dhcpv6Srv::setReservedClientClasses(const Pkt6Ptr& pkt,
                                    const AllocEngine::ClientContext6& ctx) {
    if (ctx.currentHost() && pkt) {
        const ClientClasses& classes = ctx.currentHost()->getClientClasses6();
        for (ClientClasses::const_iterator cclass = classes.cbegin();
             cclass != classes.cend(); ++cclass) {
            pkt->addClass(*cclass);
        }
    }

    const ClientClasses& classes = pkt->getClasses();
    if (!classes.empty()) {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_CLASS_ASSIGNED)
            .arg(pkt->getLabel())
            .arg(classes.toText());
    }
}

void
Dhcpv6Srv::requiredClassify(const Pkt6Ptr& pkt, AllocEngine::ClientContext6& ctx) {
    // First collect required classes
    ClientClasses classes = pkt->getClasses(true);
    Subnet6Ptr subnet = ctx.subnet_;

    if (subnet) {
        // Begin by the shared-network
        SharedNetwork6Ptr network;
        subnet->getSharedNetwork(network);
        if (network) {
            const ClientClasses& to_add = network->getRequiredClasses();
            for (ClientClasses::const_iterator cclass = to_add.cbegin();
                 cclass != to_add.cend(); ++cclass) {
                classes.insert(*cclass);
            }
        }

        // Followed by the subnet
        const ClientClasses& to_add = subnet->getRequiredClasses();
        for (ClientClasses::const_iterator cclass = to_add.cbegin();
            cclass != to_add.cend(); ++cclass) {
            classes.insert(*cclass);
        }

        // And finish by pools
        BOOST_FOREACH(const AllocEngine::ResourceType& resource,
                      ctx.allocated_resources_) {
            PoolPtr pool = ctx.subnet_->getPool(resource.second == 128 ?
                                                    Lease::TYPE_NA :
                                                    Lease::TYPE_PD,
                                                resource.first,
                                                false);
            if (pool) {
                const ClientClasses& to_add = pool->getRequiredClasses();
                for (ClientClasses::const_iterator cclass = to_add.cbegin();
                     cclass != to_add.cend(); ++cclass) {
                    classes.insert(*cclass);
                }
            }
        }

        // host reservation???
    }

    // Run match expressions
    // Note getClientClassDictionary() cannot be null
    const ClientClassDictionaryPtr& dict =
        CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
    for (ClientClasses::const_iterator cclass = classes.cbegin();
         cclass != classes.cend(); ++cclass) {
        const ClientClassDefPtr class_def = dict->findClass(*cclass);
        if (!class_def) {
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_CLASS_UNDEFINED)
                .arg(*cclass);
            continue;
        }
        const ExpressionPtr& expr_ptr = class_def->getMatchExpr();
        // Nothing to do without an expression to evaluate
        if (!expr_ptr) {
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_CLASS_UNTESTABLE)
                .arg(*cclass);
            continue;
        }
        // Evaluate the expression which can return false (no match),
        // true (match) or raise an exception (error)
        try {
            bool status = evaluateBool(*expr_ptr, *pkt);
            if (status) {
                LOG_INFO(dhcp6_logger, EVAL_RESULT)
                    .arg(*cclass)
                    .arg(status);
                // Matching: add the class
                pkt->addClass(*cclass);
            } else {
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, EVAL_RESULT)
                    .arg(*cclass)
                    .arg(status);
            }
        } catch (const Exception& ex) {
            LOG_ERROR(dhcp6_logger, EVAL_RESULT)
                .arg(*cclass)
                .arg(ex.what());
        } catch (...) {
            LOG_ERROR(dhcp6_logger, EVAL_RESULT)
                .arg(*cclass)
                .arg("get exception?");
        }
    }
}

void
Dhcpv6Srv::updateReservedFqdn(const AllocEngine::ClientContext6& ctx,
                              const Pkt6Ptr& answer) {
    if (!answer) {
        isc_throw(isc::Unexpected, "an instance of the object encapsulating"
                  " a message must not be NULL when updating reserved FQDN");
    }

    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<Option6ClientFqdn>
        (answer->getOption(D6O_CLIENT_FQDN));

   // If Client FQDN option is not included, there is nothing to do.
   if (!fqdn) {
       return;
   }

   std::string name = fqdn->getDomainName();

   // If there is a host reservation for this client we have to check whether
   // this reservation has the same hostname as the hostname currently
   // present in the FQDN option. If not, it indicates that the allocation
   // engine picked a different subnet (from within a shared network) for
   // reservations and we have to send this new value to the client.
   if (ctx.currentHost() &&
       !ctx.currentHost()->getHostname().empty()) {
       std::string new_name = CfgMgr::instance().getD2ClientMgr().
           qualifyName(ctx.currentHost()->getHostname(), true);

       if (new_name != name) {
           fqdn->setDomainName(new_name, Option6ClientFqdn::FULL);

           // Replace previous instance of Client FQDN option.
           answer->delOption(D6O_CLIENT_FQDN);
           answer->addOption(fqdn);
       }
   }
}

void
Dhcpv6Srv::generateFqdn(const Pkt6Ptr& answer) {
    if (!answer) {
        isc_throw(isc::Unexpected, "an instance of the object encapsulating"
                  " a message must not be NULL when generating FQDN");
    }

    /// @todo Add proper logging for cases when we can't generate FQDN.
    /// See #3885 for details.

    // It is likely that client hasn't included the FQDN option. In such case,
    // FQDN option will be NULL. Also, there is nothing to do if the option
    // is present and conveys the non-empty FQDN.
    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option6ClientFqdn>(answer->getOption(D6O_CLIENT_FQDN));
    if (!fqdn || !fqdn->getDomainName().empty()) {
        return;
    }

    // Get the first IA_NA acquired for the client.
    OptionPtr ia = answer->getOption(D6O_IA_NA);
    if (!ia) {
        return;
    }

    // If it has any IAAddr, use the first one to generate unique FQDN.
    Option6IAAddrPtr iaaddr = boost::dynamic_pointer_cast<
        Option6IAAddr>(ia->getOption(D6O_IAADDR));
    if (!iaaddr) {
        return;
    }
    // Get the IPv6 address acquired by the client.
    IOAddress addr = iaaddr->getAddress();
    std::string generated_name =
        CfgMgr::instance().getD2ClientMgr().generateFqdn(addr);

    LOG_DEBUG(ddns6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_DDNS_FQDN_GENERATED)
        .arg(answer->getLabel())
        .arg(generated_name);

    try {
        // The lease has been acquired but the FQDN for this lease hasn't
        // been updated in the lease database. We now have new FQDN
        // generated, so the lease database has to be updated here.
        // However, never update lease database for Advertise, just send
        // our notion of client's FQDN in the Client FQDN option.
        if (answer->getType() != DHCPV6_ADVERTISE) {
            Lease6Ptr lease =
                LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
            if (lease) {
                lease->hostname_ = generated_name;
                LeaseMgrFactory::instance().updateLease6(lease);

            } else {
                isc_throw(isc::Unexpected, "there is no lease in the database "
                          " for address " << addr << ", so as it is impossible"
                          " to update FQDN data. This is a programmatic error"
                          " as the given address is now being handed to the"
                          " client");
            }
        }
        // Set the generated FQDN in the Client FQDN option.
        fqdn->setDomainName(generated_name, Option6ClientFqdn::FULL);

       answer->delOption(D6O_CLIENT_FQDN);
       answer->addOption(fqdn);

    } catch (const Exception& ex) {
        LOG_ERROR(ddns6_logger, DHCP6_DDNS_GENERATED_FQDN_UPDATE_FAIL)
            .arg(answer->getLabel())
            .arg(addr.toText())
            .arg(ex.what());
    }
}

void
Dhcpv6Srv::startD2() {
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    if (d2_mgr.ddnsEnabled()) {
        // Updates are enabled, so lets start the sender, passing in
        // our error handler.
        // This may throw so wherever this is called needs to ready.
        d2_mgr.startSender(boost::bind(&Dhcpv6Srv::d2ClientErrorHandler,
                                       this, _1, _2));
    }
}

void
Dhcpv6Srv::stopD2() {
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    if (d2_mgr.ddnsEnabled()) {
        // Updates are enabled, so lets stop the sender
        d2_mgr.stopSender();
    }
}

void
Dhcpv6Srv::d2ClientErrorHandler(const
                                dhcp_ddns::NameChangeSender::Result result,
                                dhcp_ddns::NameChangeRequestPtr& ncr) {
    LOG_ERROR(ddns6_logger, DHCP6_DDNS_REQUEST_SEND_FAILED).
              arg(result).arg((ncr ? ncr->toText() : " NULL "));
    // We cannot communicate with kea-dhcp-ddns, suspend further updates.
    /// @todo We may wish to revisit this, but for now we will simply turn
    /// them off.
    CfgMgr::instance().getD2ClientMgr().suspendUpdates();
}

// Refer to config_report so it will be embedded in the binary
const char* const* dhcp6_config_report = isc::detail::config_report;

std::string
Dhcpv6Srv::getVersion(bool extended) {
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
#ifdef HAVE_CQL
        tmp << CqlLeaseMgr::getDBVersion() << endl;
#endif
        tmp << Memfile_LeaseMgr::getDBVersion();

        // @todo: more details about database runtime
    }

    return (tmp.str());
}

void Dhcpv6Srv::processRSOO(const Pkt6Ptr& query, const Pkt6Ptr& rsp) {

    if (query->relay_info_.empty()) {
        // RSOO is inserted by relay agents, nothing to do here if it's
        // a direct message.
        return;
    }

    // Get RSOO configuration.
    ConstCfgRSOOPtr cfg_rsoo  = CfgMgr::instance().getCurrentCfg()->getCfgRSOO();

    // Let's get over all relays (encapsulation levels). We need to do
    // it in the same order as the client packet traversed the relays.
    for (int i = query->relay_info_.size(); i > 0 ; --i) {
        OptionPtr rsoo_container = query->getRelayOption(D6O_RSOO, i - 1);
        if (rsoo_container) {
            // There are RSOO options. Let's get through them one by one
            // and if it's RSOO-enabled and there's no such option provided yet,
            // copy it to the server's response
            const OptionCollection& rsoo = rsoo_container->getOptions();
            for (OptionCollection::const_iterator opt = rsoo.begin();
                 opt != rsoo.end(); ++opt) {

                // Echo option if it is RSOO enabled option and there is no such
                // option added yet.
                if (cfg_rsoo->enabled(opt->second->getType()) &&
                    !rsp->getOption(opt->second->getType())) {
                    rsp->addOption(opt->second);
                }
            }
        }
    }
}

uint16_t Dhcpv6Srv::checkRelaySourcePort(const Pkt6Ptr& query) {

    if (query->relay_info_.empty()) {
        // No relay agent
        return (0);
    }

    // Did the last relay agent add a relay-source-port?
    if (query->getRelayOption(D6O_RELAY_SOURCE_PORT, 0)) {
        // RFC 8357 section 5.2
        return (query->getRemotePort());
    }

    return (0);
}

void Dhcpv6Srv::processStatsReceived(const Pkt6Ptr& query) {
    // Note that we're not bumping pkt6-received statistic as it was
    // increased early in the packet reception code.

    string stat_name = "pkt6-unknown-received";
    switch (query->getType()) {
    case DHCPV6_SOLICIT:
        stat_name = "pkt6-solicit-received";
        break;
    case DHCPV6_ADVERTISE:
        // Should not happen, but let's keep a counter for it
        stat_name = "pkt6-advertise-received";
        break;
    case DHCPV6_REQUEST:
        stat_name = "pkt6-request-received";
        break;
    case DHCPV6_CONFIRM:
        stat_name = "pkt6-confirm-received";
        break;
    case DHCPV6_RENEW:
        stat_name = "pkt6-renew-received";
        break;
    case DHCPV6_REBIND:
        stat_name = "pkt6-rebind-received";
        break;
    case DHCPV6_REPLY:
        // Should not happen, but let's keep a counter for it
        stat_name = "pkt6-reply-received";
        break;
    case DHCPV6_RELEASE:
        stat_name = "pkt6-release-received";
        break;
    case DHCPV6_DECLINE:
        stat_name = "pkt6-decline-received";
        break;
    case DHCPV6_RECONFIGURE:
        stat_name = "pkt6-reconfigure-received";
        break;
    case DHCPV6_INFORMATION_REQUEST:
        stat_name = "pkt6-infrequest-received";
        break;
    case DHCPV6_DHCPV4_QUERY:
        stat_name = "pkt6-dhcpv4-query-received";
        break;
    case DHCPV6_DHCPV4_RESPONSE:
        // Should not happen, but let's keep a counter for it
        stat_name = "pkt6-dhcpv4-response-received";
        break;
    default:
            ; // do nothing
    }

    StatsMgr::instance().addValue(stat_name, static_cast<int64_t>(1));
}

void Dhcpv6Srv::processStatsSent(const Pkt6Ptr& response) {
    // Increase generic counter for sent packets.
    StatsMgr::instance().addValue("pkt6-sent", static_cast<int64_t>(1));

    // Increase packet type specific counter for packets sent.
    string stat_name;
    switch (response->getType()) {
    case DHCPV6_ADVERTISE:
        stat_name = "pkt6-advertise-sent";
        break;
    case DHCPV6_REPLY:
        stat_name = "pkt6-reply-sent";
        break;
    case DHCPV6_DHCPV4_RESPONSE:
        stat_name = "pkt6-dhcpv4-response-sent";
        break;
    default:
        // That should never happen
        return;
    }

    StatsMgr::instance().addValue(stat_name, static_cast<int64_t>(1));
}

int Dhcpv6Srv::getHookIndexBuffer6Send() {
    return (Hooks.hook_index_buffer6_send_);
}

bool
Dhcpv6Srv::requestedInORO(const Pkt6Ptr& query, const uint16_t code) const {
    OptionUint16ArrayPtr oro =
        boost::dynamic_pointer_cast<OptionUint16Array>(query->getOption(D6O_ORO));

    if (oro) {
        const std::vector<uint16_t>& codes = oro->getValues();
        return (std::find(codes.begin(), codes.end(), code) != codes.end());
    }

    return (false);
}

void Dhcpv6Srv::discardPackets() {
    // Dump all of our current packets, anything that is mid-stream
    isc::dhcp::Pkt6Ptr pkt6ptr_empty;
    isc::dhcp::getCalloutHandle(pkt6ptr_empty);
    HooksManager::clearParkingLots();
}

};
};
