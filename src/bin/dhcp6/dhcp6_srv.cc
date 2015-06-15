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
#include <dhcp_ddns/ncr_msg.h>
#include <dhcp/dhcp6.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/duid.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt6.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcpsrv/callout_handle_store.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_selector.h>
#include <dhcpsrv/utils.h>
#include <exceptions/exceptions.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_log.h>
#include <hooks/hooks_manager.h>

#include <util/encode/hex.h>
#include <util/io_utilities.h>
#include <util/range_utilities.h>
#include <log/logger.h>
#include <cryptolink/cryptolink.h>
#include <cfgrpt/config_report.h>

#include <asio.hpp>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/erase.hpp>

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
using namespace isc::util;
using namespace std;

namespace {

/// Structure that holds registered hook indexes
struct Dhcp6Hooks {
    int hook_index_buffer6_receive_;///< index for "buffer6_receive" hook point
    int hook_index_pkt6_receive_;   ///< index for "pkt6_receive" hook point
    int hook_index_subnet6_select_; ///< index for "subnet6_select" hook point
    int hook_index_lease6_release_; ///< index for "lease6_release" hook point
    int hook_index_pkt6_send_;      ///< index for "pkt6_send" hook point
    int hook_index_buffer6_send_;   ///< index for "buffer6_send" hook point

    /// Constructor that registers hook points for DHCPv6 engine
    Dhcp6Hooks() {
        hook_index_buffer6_receive_= HooksManager::registerHook("buffer6_receive");
        hook_index_pkt6_receive_   = HooksManager::registerHook("pkt6_receive");
        hook_index_subnet6_select_ = HooksManager::registerHook("subnet6_select");
        hook_index_lease6_release_ = HooksManager::registerHook("lease6_release");
        hook_index_pkt6_send_      = HooksManager::registerHook("pkt6_send");
        hook_index_buffer6_send_   = HooksManager::registerHook("buffer6_send");
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
    LOG_DEBUG(options_logger, DBG_DHCP6_DETAIL, DHCP6_ADD_GLOBAL_STATUS_CODE)
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
    LOG_DEBUG(options_logger, DBG_DHCP6_DETAIL, DHCP6_ADD_STATUS_CODE_FOR_IA)
        .arg(pkt.getLabel())
        .arg(ia.getIAID())
        .arg(option_status->dataToText());
    return (option_status);
}

}; // anonymous namespace

namespace isc {
namespace dhcp {

const std::string Dhcpv6Srv::VENDOR_CLASS_PREFIX("VENDOR_CLASS_");

/// @brief file name of a server-id file
///
/// Server must store its duid in persistent storage that must not change
/// between restarts. This is name of the file that is created in dataDir
/// (see isc::dhcp::CfgMgr::getDataDir()). It is a text file that uses
/// double digit hex values separated by colons format, e.g.
/// 01:ff:02:03:06:80:90:ab:cd:ef. Server will create it during first
/// run and then use it afterwards.
static const char* SERVER_DUID_FILE = "kea-dhcp6-serverid";

Dhcpv6Srv::Dhcpv6Srv(uint16_t port)
:alloc_engine_(), serverid_(), port_(port), shutdown_(true)
{

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_OPEN_SOCKET).arg(port);

    // Initialize objects required for DHCP server operation.
    try {
        // Port 0 is used for testing purposes where in most cases we don't
        // rely on the physical interfaces. Therefore, it should be possible
        // to create an object even when there are no usable interfaces.
        if ((port > 0) && (IfaceMgr::instance().countIfaces() == 0)) {
            LOG_ERROR(dhcp6_logger, DHCP6_NO_INTERFACES);
            return;
        }

        string duid_file = CfgMgr::instance().getDataDir() + "/" + string(SERVER_DUID_FILE);
        if (loadServerID(duid_file)) {
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_SERVERID_LOADED)
                .arg(duidToString(getServerID()))
                .arg(duid_file);
        } else {
            generateServerID();
            LOG_INFO(dhcp6_logger, DHCP6_SERVERID_GENERATED)
                .arg(duidToString(getServerID()))
                .arg(duid_file);

            if (!writeServerID(duid_file)) {
                LOG_WARN(dhcp6_logger, DHCP6_SERVERID_WRITE_FAIL)
                    .arg(duid_file);
            }
        }

        // Instantiate allocation engine
        alloc_engine_.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));

        /// @todo call loadLibraries() when handling configuration changes

    } catch (const std::exception &e) {
        LOG_ERROR(dhcp6_logger, DHCP6_SRV_CONSTRUCT_ERROR).arg(e.what());
        return;
    }

    // All done, so can proceed
    shutdown_ = false;
}

Dhcpv6Srv::~Dhcpv6Srv() {
    IfaceMgr::instance().closeSockets();

    LeaseMgrFactory::destroy();
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
    /// it is allowed in the received message or not (per RFC3315).
    /// If the server identifier is not allowed in the message, the
    /// sanityCheck function should deal with it. We may rethink this
    /// design if we decide that it is appropriate to check at this stage
    /// of message processing that the server identifier must or must not
    /// be present. In such case however, the logic checking server id
    /// will have to be removed from sanityCheck and placed here instead,
    /// to avoid duplicate checks.
    OptionPtr server_id = pkt->getOption(D6O_SERVERID);
    if (server_id){
        // Let us test received ServerID if it is same as ServerID
        // which is being used by server
        if (getServerID()->getData() != server_id->getData()){
            LOG_DEBUG(bad_packet_logger, DBG_DHCP6_DETAIL_DATA,
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
            LOG_DEBUG(bad_packet_logger, DBG_DHCP6_DETAIL, DHCP6_PACKET_DROP_UNICAST)
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

AllocEngine::ClientContext6
Dhcpv6Srv::createContext(const Pkt6Ptr& pkt) {
    AllocEngine::ClientContext6 ctx;
    ctx.subnet_ = selectSubnet(pkt);
    ctx.duid_ = pkt->getClientId();
    ctx.hwaddr_ = getMAC(pkt);
    alloc_engine_->findReservation(ctx);

    return (ctx);
}

bool Dhcpv6Srv::run() {
    while (!shutdown_) {
        // client's message and server's response
        Pkt6Ptr query;
        Pkt6Ptr rsp;

        try {
            // The lease database backend may install some timers for which
            // the handlers need to be executed periodically. Retrieve the
            // maximum interval at which the handlers must be executed from
            // the lease manager.
            uint32_t timeout = LeaseMgrFactory::instance().getIOServiceExecInterval();
            // If the returned value is zero it means that there are no
            // timers installed, so use a default value.
            if (timeout == 0) {
                timeout = 1000;
            }
            LOG_DEBUG(packet_logger, DBG_DHCP6_DETAIL, DHCP6_BUFFER_WAIT).arg(timeout);
            query = receivePacket(timeout);

            // Log if packet has arrived. We can't log the detailed information
            // about the DHCP message because it hasn't been unpacked/parsed
            // yet, and it can't be parsed at this point because hooks will
            // have to process it first. The only information available at this
            // point are: the interface, source address and destination addresses
            // and ports.
            if (query) {
                LOG_DEBUG(packet_logger, DBG_DHCP6_BASIC, DHCP6_BUFFER_RECEIVED)
                    .arg(query->getRemoteAddr().toText())
                    .arg(query->getRemotePort())
                    .arg(query->getLocalAddr().toText())
                    .arg(query->getLocalPort())
                    .arg(query->getIface());

            } else {
                LOG_DEBUG(packet_logger, DBG_DHCP6_DETAIL, DHCP6_BUFFER_WAIT_INTERRUPTED)
                    .arg(timeout);
            }

        } catch (const SignalInterruptOnSelect) {
            // Packet reception interrupted because a signal has been received.
            // This is not an error because we might have received a SIGTERM,
            // SIGINT or SIGHUP which are handled by the server. For signals
            // that are not handled by the server we rely on the default
            // behavior of the system.
            LOG_DEBUG(packet_logger, DBG_DHCP6_DETAIL, DHCP6_BUFFER_WAIT_SIGNAL)
                .arg(signal_set_->getNext());
        } catch (const std::exception& e) {
            LOG_ERROR(packet_logger, DHCP6_PACKET_RECEIVE_FAIL).arg(e.what());
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
        handleSignal();

        // Execute ready timers for the lease database, e.g. Lease File Cleanup.
        try {
            LeaseMgrFactory::instance().getIOService()->poll();

        } catch (const std::exception& ex) {
            LOG_WARN(dhcp6_logger, DHCP6_LEASE_DATABASE_TIMERS_EXEC_FAIL)
                .arg(ex.what());
        }

        // Timeout may be reached or signal received, which breaks select()
        // with no packet received
        if (!query) {
            continue;
        }

        // In order to parse the DHCP options, the server needs to use some
        // configuration information such as: existing option spaces, option
        // definitions etc. This is the kind of information which is not
        // available in the libdhcp, so we need to supply our own implementation
        // of the option parsing function here, which would rely on the
        // configuration data.
        query->setCallback(boost::bind(&Dhcpv6Srv::unpackOptions, this, _1, _2,
                                       _3, _4, _5));

        bool skip_unpack = false;

        // The packet has just been received so contains the uninterpreted wire
        // data; execute callouts registered for buffer6_receive.
        if (HooksManager::calloutsPresent(Hooks.hook_index_buffer6_receive_)) {
            CalloutHandlePtr callout_handle = getCalloutHandle(query);

            // Delete previously set arguments
            callout_handle->deleteAllArguments();

            // Pass incoming packet as argument
            callout_handle->setArgument("query6", query);

            // Call callouts
            HooksManager::callCallouts(Hooks.hook_index_buffer6_receive_, *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to parse the packet, so skip at this
            // stage means that callouts did the parsing already, so server
            // should skip parsing.
            if (callout_handle->getSkip()) {
                LOG_DEBUG(hooks_logger, DBG_DHCP6_DETAIL, DHCP6_HOOK_BUFFER_RCVD_SKIP)
                    .arg(query->getRemoteAddr().toText())
                    .arg(query->getLocalAddr().toText())
                    .arg(query->getIface());
                skip_unpack = true;
            }

            callout_handle->getArgument("query6", query);
        }

        // Unpack the packet information unless the buffer6_receive callouts
        // indicated they did it
        if (!skip_unpack) {
            try {
                LOG_DEBUG(options_logger, DBG_DHCP6_DETAIL, DHCP6_BUFFER_UNPACK)
                    .arg(query->getRemoteAddr().toText())
                    .arg(query->getLocalAddr().toText())
                    .arg(query->getIface());
                query->unpack();
            } catch (const std::exception &e) {
                // Failed to parse the packet.
                LOG_DEBUG(bad_packet_logger, DBG_DHCP6_DETAIL,
                          DHCP6_PACKET_DROP_PARSE_FAIL)
                    .arg(query->getRemoteAddr().toText())
                    .arg(query->getLocalAddr().toText())
                    .arg(query->getIface())
                    .arg(e.what());
                continue;
            }
        }
        // Check if received query carries server identifier matching
        // server identifier being used by the server.
        if (!testServerID(query)) {
            continue;
        }

        // Check if the received query has been sent to unicast or multicast.
        // The Solicit, Confirm, Rebind and Information Request will be
        // discarded if sent to unicast address.
        if (!testUnicast(query)) {
            continue;
        }

        LOG_DEBUG(packet_logger, DBG_DHCP6_BASIC_DATA, DHCP6_PACKET_RECEIVED)
            .arg(query->getLabel())
            .arg(query->getName())
            .arg(query->getType())
            .arg(query->getRemoteAddr())
            .arg(query->getLocalAddr())
            .arg(query->getIface());
        LOG_DEBUG(packet_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_QUERY_DATA)
            .arg(query->getLabel())
            .arg(query->toText());

        // At this point the information in the packet has been unpacked into
        // the various packet fields and option objects has been created.
        // Execute callouts registered for packet6_receive.
        if (HooksManager::calloutsPresent(Hooks.hook_index_pkt6_receive_)) {
            CalloutHandlePtr callout_handle = getCalloutHandle(query);

            // Delete previously set arguments
            callout_handle->deleteAllArguments();

            // Pass incoming packet as argument
            callout_handle->setArgument("query6", query);

            // Call callouts
            HooksManager::callCallouts(Hooks.hook_index_pkt6_receive_, *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to process the packet, so skip at this
            // stage means drop.
            if (callout_handle->getSkip()) {
                LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_PACKET_RCVD_SKIP)
                    .arg(query->getLabel());
                continue;
            }

            callout_handle->getArgument("query6", query);
        }

        // Assign this packet to a class, if possible
        classifyPacket(query);

        try {
            NameChangeRequestPtr ncr;

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
                // We received a packet type that we do not recognize.
                LOG_DEBUG(bad_packet_logger, DBG_DHCP6_BASIC, DHCP6_UNKNOWN_MSG_RECEIVED)
                    .arg(static_cast<int>(query->getType()))
                    .arg(query->getIface());
                // Only action is to output a message if debug is enabled,
                // and that will be covered by the debug statement before
                // the "switch" statement.
                ;
            }

        } catch (const RFCViolation& e) {
            LOG_DEBUG(bad_packet_logger, DBG_DHCP6_BASIC, DHCP6_REQUIRED_OPTIONS_CHECK_FAIL)
                .arg(query->getName())
                .arg(query->getRemoteAddr().toText())
                .arg(e.what());

        } catch (const isc::Exception& e) {

            // Catch-all exception (at least for ones based on the isc Exception
            // class, which covers more or less all that are explicitly raised
            // in the Kea code).  Just log the problem and ignore the packet.
            // (The problem is logged as a debug message because debug is
            // disabled by default - it prevents a DDOS attack based on the
            // sending of problem packets.)
            LOG_DEBUG(bad_packet_logger, DBG_DHCP6_BASIC, DHCP6_PACKET_PROCESS_FAIL)
                .arg(query->getName())
                .arg(query->getRemoteAddr().toText())
                .arg(e.what());
        }

        if (rsp) {

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

            if (rsp->relay_info_.empty()) {
                // Direct traffic, send back to the client directly
                rsp->setRemotePort(DHCP6_CLIENT_PORT);
            } else {
                // Relayed traffic, send back to the relay agent
                rsp->setRemotePort(DHCP6_SERVER_PORT);
            }

            rsp->setLocalPort(DHCP6_SERVER_PORT);
            rsp->setIndex(query->getIndex());
            rsp->setIface(query->getIface());

            // Specifies if server should do the packing
            bool skip_pack = false;

            // Server's reply packet now has all options and fields set.
            // Options are represented by individual objects, but the
            // output wire data has not been prepared yet.
            // Execute all callouts registered for packet6_send
            if (HooksManager::calloutsPresent(Hooks.hook_index_pkt6_send_)) {
                CalloutHandlePtr callout_handle = getCalloutHandle(query);

                // Delete all previous arguments
                callout_handle->deleteAllArguments();

                // Set our response
                callout_handle->setArgument("response6", rsp);

                // Call all installed callouts
                HooksManager::callCallouts(Hooks.hook_index_pkt6_send_, *callout_handle);

                // Callouts decided to skip the next processing step. The next
                // processing step would to pack the packet (create wire data).
                // That step will be skipped if any callout sets skip flag.
                // It essentially means that the callout already did packing,
                // so the server does not have to do it again.
                if (callout_handle->getSkip()) {
                    LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_PACKET_SEND_SKIP)
                        .arg(rsp->getLabel());
                    skip_pack = true;
                }
            }

            LOG_DEBUG(packet_logger, DBG_DHCP6_DETAIL_DATA,
                      DHCP6_RESPONSE_DATA)
                .arg(static_cast<int>(rsp->getType())).arg(rsp->toText());

            if (!skip_pack) {
                try {
                    rsp->pack();
                } catch (const std::exception& e) {
                    LOG_ERROR(options_logger, DHCP6_PACK_FAIL)
                        .arg(e.what());
                    continue;
                }

            }

            try {

                // Now all fields and options are constructed into output wire buffer.
                // Option objects modification does not make sense anymore. Hooks
                // can only manipulate wire buffer at this stage.
                // Let's execute all callouts registered for buffer6_send
                if (HooksManager::calloutsPresent(Hooks.hook_index_buffer6_send_)) {
                    CalloutHandlePtr callout_handle = getCalloutHandle(query);

                    // Delete previously set arguments
                    callout_handle->deleteAllArguments();

                    // Pass incoming packet as argument
                    callout_handle->setArgument("response6", rsp);

                    // Call callouts
                    HooksManager::callCallouts(Hooks.hook_index_buffer6_send_, *callout_handle);

                    // Callouts decided to skip the next processing step. The next
                    // processing step would to parse the packet, so skip at this
                    // stage means drop.
                    if (callout_handle->getSkip()) {
                        LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_BUFFER_SEND_SKIP)
                            .arg(rsp->getLabel());
                        continue;
                    }

                    callout_handle->getArgument("response6", rsp);
                }

                LOG_DEBUG(packet_logger, DBG_DHCP6_DETAIL_DATA,
                          DHCP6_RESPONSE_DATA)
                    .arg(static_cast<int>(rsp->getType())).arg(rsp->toText());

                sendPacket(rsp);
            } catch (const std::exception& e) {
                LOG_ERROR(packet_logger, DHCP6_PACKET_SEND_FAIL)
                    .arg(e.what());
            }
        }
    }

    return (true);
}

bool Dhcpv6Srv::loadServerID(const std::string& file_name) {

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

    // now remove :
    /// @todo: We should check first if the format is sane.
    /// Otherwise 1:2:3:4 will be converted to 0x12, 0x34
    boost::algorithm::erase_all(hex_string, ":");

    std::vector<uint8_t> bin;

    // Decode the hex string and store it in bin (which happens
    // to be OptionBuffer format)
    isc::util::encode::decodeHex(hex_string, bin);

    // Now create server-id option
    serverid_.reset(new Option(Option::V6, D6O_SERVERID, bin));

    return (true);
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

bool
Dhcpv6Srv::writeServerID(const std::string& file_name) {
    fstream f(file_name.c_str(), ios::out | ios::trunc);
    if (!f.good()) {
        return (false);
    }
    f << duidToString(getServerID());
    f.close();
    return (true);
}

void
Dhcpv6Srv::generateServerID() {

    /// @todo: This code implements support for DUID-LLT (the recommended one).
    /// We should eventually add support for other DUID types: DUID-LL, DUID-EN
    /// and DUID-UUID

    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();

    // Let's find suitable interface.
    BOOST_FOREACH(IfacePtr iface, ifaces) {
        // All the following checks could be merged into one multi-condition
        // statement, but let's keep them separated as perhaps one day
        // we will grow knobs to selectively turn them on or off. Also,
        // this code is used only *once* during first start on a new machine
        // and then server-id is stored. (or at least it will be once
        // DUID storage is implemented)

        // I wish there was a this_is_a_real_physical_interface flag...

        // MAC address should be at least 6 bytes. Although there is no such
        // requirement in any RFC, all decent physical interfaces (Ethernet,
        // WiFi, InfiniBand, etc.) have 6 bytes long MAC address. We want to
        // base our DUID on real hardware address, rather than virtual
        // interface that pretends that underlying IP address is its MAC.
        if (iface->getMacLen() < MIN_MAC_LEN) {
            continue;
        }

        // Let's don't use loopback.
        if (iface->flag_loopback_) {
            continue;
        }

        // Let's skip downed interfaces. It is better to use working ones.
        if (!iface->flag_up_) {
            continue;
        }

        // Some interfaces (like lo on Linux) report 6-bytes long
        // MAC address 00:00:00:00:00:00. Let's not use such weird interfaces
        // to generate DUID.
        if (isRangeZero(iface->getMac(), iface->getMac() + iface->getMacLen())) {
            continue;
        }

        // Ok, we have useful MAC. Let's generate DUID-LLT based on
        // it. See RFC3315, Section 9.2 for details.

        // DUID uses seconds since midnight of 01-01-2000, time() returns
        // seconds since 01-01-1970. DUID_TIME_EPOCH substitution corrects
        // that.
        time_t seconds = time(NULL);
        seconds -= DUID_TIME_EPOCH;

        OptionBuffer srvid(8 + iface->getMacLen());
        // We know that the buffer is more than 8 bytes long at this point.
        writeUint16(DUID::DUID_LLT, &srvid[0], 2);
        writeUint16(HWTYPE_ETHERNET, &srvid[2], 2);
        writeUint32(static_cast<uint32_t>(seconds), &srvid[4], 4);
        memcpy(&srvid[8], iface->getMac(), iface->getMacLen());

        serverid_ = OptionPtr(new Option(Option::V6, D6O_SERVERID,
                                         srvid.begin(), srvid.end()));
        return;
    }

    // If we reached here, there are no suitable interfaces found.
    // Either interface detection is not supported on this platform or
    // this is really weird box. Let's use DUID-EN instead.
    // See Section 9.3 of RFC3315 for details.

    OptionBuffer srvid(12);
    writeUint16(DUID::DUID_EN, &srvid[0], srvid.size());
    writeUint32(ENTERPRISE_ID_ISC, &srvid[2], srvid.size() - 2);

    // Length of the identifier is company specific. I hereby declare
    // ISC "standard" of 6 bytes long pseudo-random numbers.
    srandom(time(NULL));
    fillRandom(&srvid[6], &srvid[12]);

    serverid_ = OptionPtr(new Option(Option::V6, D6O_SERVERID,
                                     srvid.begin(), srvid.end()));
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
Dhcpv6Srv::appendDefaultOptions(const Pkt6Ptr&, Pkt6Ptr& answer) {
    // add server-id
    answer->addOption(getServerID());
}

void
Dhcpv6Srv::appendRequestedOptions(const Pkt6Ptr& question, Pkt6Ptr& answer,
                                  AllocEngine::ClientContext6& ctx) {

    // Client requests some options using ORO option. Try to
    // get this option from client's message.
    boost::shared_ptr<OptionIntArray<uint16_t> > option_oro =
        boost::dynamic_pointer_cast<OptionIntArray<uint16_t> >
        (question->getOption(D6O_ORO));

    // Option ORO not found? We're done here then.
    if (!option_oro) {
        return;
    }

    // Get global option definitions (i.e. options defined to apply to all,
    // unless overwritten on a subnet or host level)
    ConstCfgOptionPtr global_opts = CfgMgr::instance().getCurrentCfg()->
        getCfgOption();

    // Get the list of options that client requested.
    const std::vector<uint16_t>& requested_opts = option_oro->getValues();
    BOOST_FOREACH(uint16_t opt, requested_opts) {
        // If we found a subnet for this client, all options (including the
        // global options) should be available through the options
        // configuration for the subnet.
        if (ctx.subnet_) {
            OptionDescriptor desc = ctx.subnet_->getCfgOption()->get("dhcp6",
                                                                     opt);
            if (desc.option_) {
                // Attempt to assign an option from subnet first.
                answer->addOption(desc.option_);
                continue;
            }

        // If there is no subnet selected (e.g. Information-request message
        // case) we need to look at the global options.
        } else {
            OptionDescriptor desc = global_opts->get("dhcp6", opt);
            if (desc.option_) {
                answer->addOption(desc.option_);
            }
        }
    }
}

void
Dhcpv6Srv::appendRequestedVendorOptions(const Pkt6Ptr& question, Pkt6Ptr& answer,
                                        AllocEngine::ClientContext6& ctx) {

    // Leave if there is no subnet matching the incoming packet.
    // There is no need to log the error message here because
    // it will be logged in the assignLease() when it fails to
    // pick the suitable subnet. We don't want to duplicate
    // error messages in such case.
    if (!ctx.subnet_) {
        return;
    }

    // Try to get the vendor option
    boost::shared_ptr<OptionVendor> vendor_req =
        boost::dynamic_pointer_cast<OptionVendor>(question->getOption(D6O_VENDOR_OPTS));
    if (!vendor_req) {
        return;
    }

    // Let's try to get ORO within that vendor-option
    /// @todo This is very specific to vendor-id=4491 (Cable Labs). Other vendors
    /// may have different policies.
    boost::shared_ptr<OptionUint16Array> oro =
        boost::dynamic_pointer_cast<OptionUint16Array>(vendor_req->getOption(DOCSIS3_V6_ORO));

    // Option ORO not found. Don't do anything then.
    if (!oro) {
        return;
    }

    uint32_t vendor_id = vendor_req->getVendorId();

    boost::shared_ptr<OptionVendor> vendor_rsp(new OptionVendor(Option::V6, vendor_id));

    // Get the list of options that client requested.
    bool added = false;
    const std::vector<uint16_t>& requested_opts = oro->getValues();
    BOOST_FOREACH(uint16_t opt, requested_opts) {
        OptionDescriptor desc = ctx.subnet_->getCfgOption()->get(vendor_id, opt);
        if (desc.option_) {
            vendor_rsp->addOption(desc.option_);
            added = true;
        }
    }

    if (added) {
        answer->addOption(vendor_rsp);
    }
}

void
Dhcpv6Srv::sanityCheck(const Pkt6Ptr& pkt, RequirementLevel clientid,
                       RequirementLevel serverid) {
    OptionCollection client_ids = pkt->getOptions(D6O_CLIENTID);
    switch (clientid) {
    case MANDATORY:
        if (client_ids.size() != 1) {
            isc_throw(RFCViolation, "Exactly 1 client-id option expected in "
                      << pkt->getName() << ", but " << client_ids.size()
                      << " received");
        }
        break;
    case OPTIONAL:
        if (client_ids.size() > 1) {
            isc_throw(RFCViolation, "Too many (" << client_ids.size()
                      << ") client-id options received in " << pkt->getName());
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
        break;

    case OPTIONAL:
        if (server_ids.size() > 1) {
            isc_throw(RFCViolation, "Too many (" << server_ids.size()
                      << ") server-id options received in " << pkt->getName());
        }
    }
}

Subnet6Ptr
Dhcpv6Srv::selectSubnet(const Pkt6Ptr& question) {
    // Initialize subnet selector with the values used to select the subnet.
    SubnetSelector selector;
    selector.iface_name_ = question->getIface();
    selector.remote_address_ = question->getRemoteAddr();
    selector.first_relay_linkaddr_ = IOAddress("::");
    selector.client_classes_ = question->classes_;

    // Initialize fields specific to relayed messages.
    if (!question->relay_info_.empty()) {
        selector.first_relay_linkaddr_ = question->relay_info_.back().linkaddr_;
        selector.interface_id_ =
            question->getAnyRelayOption(D6O_INTERFACE_ID,
                                        Pkt6::RELAY_GET_FIRST);
    }

    Subnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->selectSubnet(selector);


    // Let's execute all callouts registered for subnet6_receive
    if (HooksManager::calloutsPresent(Hooks.hook_index_subnet6_select_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(question);

        // We're reusing callout_handle from previous calls
        callout_handle->deleteAllArguments();

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
        if (callout_handle->getSkip()) {
            LOG_DEBUG(hooks_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_SUBNET6_SELECT_SKIP)
                .arg(question->getLabel());
            return (Subnet6Ptr());
        }

        // Use whatever subnet was specified by the callout
        callout_handle->getArgument("subnet6", subnet);
    }

    if (subnet) {
        // Log at higher debug level that subnet has been found.
        LOG_DEBUG(packet_logger, DBG_DHCP6_BASIC_DATA, DHCP6_SUBNET_SELECTED)
            .arg(question->getLabel())
            .arg(subnet->getID());
        // Log detailed information about the selected subnet at the
        // lower debug level.
        LOG_DEBUG(packet_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_SUBNET_DATA)
            .arg(question->getLabel())
            .arg(subnet->toText());

    } else {
        LOG_DEBUG(packet_logger, DBG_DHCP6_DETAIL, DHCP6_SUBNET_SELECTION_FAILED)
            .arg(question->getLabel());
    }

    return (subnet);
}

void
Dhcpv6Srv::assignLeases(const Pkt6Ptr& question, Pkt6Ptr& answer,
                        AllocEngine::ClientContext6& ctx) {

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
}


void
Dhcpv6Srv::processClientFqdn(const Pkt6Ptr& question, const Pkt6Ptr& answer,
                             AllocEngine::ClientContext6& ctx) {
    // Get Client FQDN Option from the client's message. If this option hasn't
    // been included, do nothing.
    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option6ClientFqdn>(question->getOption(D6O_CLIENT_FQDN));
    if (!fqdn) {
        // No FQDN so lease hostname comes from host reservation if one
        if (ctx.host_) {
            ctx.hostname_ = ctx.host_->getHostname();
        }

        return;
    }

    LOG_DEBUG(ddns_logger, DBG_DHCP6_DETAIL, DHCP6_DDNS_RECEIVE_FQDN)
        .arg(question->getLabel())
        .arg(fqdn->toText());

    // Create the DHCPv6 Client FQDN Option to be included in the server's
    // response to a client.
    Option6ClientFqdnPtr fqdn_resp(new Option6ClientFqdn(*fqdn));

    // Set the server S, N, and O flags based on client's flags and
    // current configuration.
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    d2_mgr.adjustFqdnFlags<Option6ClientFqdn>(*fqdn, *fqdn_resp);

    // If there's a reservation and it has a hostname specified, use it!
    if (ctx.host_ && !ctx.host_->getHostname().empty()) {
        D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
        // Add the qualifying suffix.
        // After #3765, this will only occur if the suffix is not empty.
        fqdn_resp->setDomainName(d2_mgr.qualifyName(ctx.host_->getHostname(),
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
    LOG_DEBUG(ddns_logger, DBG_DHCP6_DETAIL, DHCP6_DDNS_RESPONSE_FQDN_DATA)
        .arg(question->getLabel())
        .arg(fqdn_resp->toText());
    answer->addOption(fqdn_resp);
}

void
Dhcpv6Srv::createNameChangeRequests(const Pkt6Ptr& answer) {
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

        LOG_DEBUG(ddns_logger, DBG_DHCP6_DETAIL,
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

void
Dhcpv6Srv::createRemovalNameChangeRequest(const Pkt6Ptr& query, const Lease6Ptr& lease) {
    // Don't create NameChangeRequests if DNS updates are disabled
    // or DNS update hasn't been performed.
    if (!CfgMgr::instance().ddnsEnabled() || (!lease->fqdn_fwd_ && !lease->fqdn_rev_)) {
        LOG_DEBUG(ddns_logger, DBG_DHCP6_DETAIL_DATA,
                  DHCP6_DDNS_SKIP_REMOVE_NAME_CHANGE_REQUEST)
            .arg(query->getLabel())
            .arg(lease->toText());
        return;
    }

    // If hostname is non-empty, try to convert it to wire format so as
    // DHCID can be computed from it. This may throw an exception if hostname
    // has invalid format or is empty. Again, this should be only possible
    // in case of manual intervention in the database. Note that the last
    // parameter passed to the writeFqdn function forces conversion of the FQDN
    // to lower case. This is required by the RFC4701, section 3.5.
    // The DHCID computation is further in this function.
    std::vector<uint8_t> hostname_wire;
    try {
        OptionDataTypeUtil::writeFqdn(lease->hostname_, hostname_wire, true);

    } catch (const Exception& ex) {
        LOG_ERROR(ddns_logger, DHCP6_DDNS_REMOVE_INVALID_HOSTNAME)
            .arg(query->getLabel())
            .arg(lease->hostname_.empty() ? "(empty)" : lease->hostname_)
            .arg(lease->addr_.toText());
        return;
    }

    // DUID must have been checked already  by the caller of this function.
    // Let's be on the safe side and make sure it is non-NULL and throw
    // an exception if it is NULL.
    if (!lease->duid_) {
        isc_throw(isc::Unexpected, "DUID must be set when creating"
                  << " NameChangeRequest for DNS records removal for "
                  << lease->addr_);

    }
    isc::dhcp_ddns::D2Dhcid dhcid(*lease->duid_, hostname_wire);
    // Create a NameChangeRequest to remove the entry.
    NameChangeRequestPtr ncr;
    ncr.reset(new NameChangeRequest(isc::dhcp_ddns::CHG_REMOVE,
                                    lease->fqdn_fwd_, lease->fqdn_rev_,
                                    lease->hostname_,
                                    lease->addr_.toText(),
                                    dhcid, 0, lease->valid_lft_));

    LOG_DEBUG(ddns_logger, DBG_DHCP6_DETAIL,
              DHCP6_DDNS_CREATE_REMOVE_NAME_CHANGE_REQUEST)
        .arg(query->getLabel())
        .arg(ncr->toText());

    // Post the NCR to the D2ClientMgr.
    CfgMgr::instance().getD2ClientMgr().sendRequest(ncr);
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
                       AllocEngine::ClientContext6& orig_ctx,
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

    LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_NA_REQUEST)
        .arg(query->getLabel())
        .arg(ia->getIAID())
        .arg(hint_opt ? hint.toText() : "(no hint)");

    // convenience values
    const Subnet6Ptr& subnet = orig_ctx.subnet_;
    const DuidPtr& duid = orig_ctx.duid_;

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
    bool fake_allocation = (answer->getType() != DHCPV6_REPLY);

    // Get DDNS update direction flags
    bool do_fwd = false;
    bool do_rev = false;
    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option6ClientFqdn>(answer->getOption(D6O_CLIENT_FQDN));
    if (fqdn) {
        CfgMgr::instance().getD2ClientMgr().getUpdateDirections(*fqdn, do_fwd,
                                                                do_rev);
    }

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honor the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    AllocEngine::ClientContext6 ctx(subnet, duid, ia->getIAID(),
                                    hint, Lease::TYPE_NA, do_fwd, do_rev,
                                    orig_ctx.hostname_, fake_allocation);
    ctx.callout_handle_ = getCalloutHandle(query);
    ctx.hwaddr_ = orig_ctx.hwaddr_;
    ctx.host_ = orig_ctx.host_;

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
        LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, fake_allocation ?
                  DHCP6_LEASE_ADVERT : DHCP6_LEASE_ALLOC)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(ia->getIAID());
        LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_LEASE_DATA)
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

        if (!fake_allocation) {
            Lease6Ptr old_lease;
            if (!ctx.changed_leases_.empty()) {
                old_lease = *ctx.changed_leases_.begin();

                // Allocation engine has returned an existing lease. If so, we
                // have to check that the FQDN settings we provided are the same
                // that were set. If they aren't, we will have to remove existing
                // DNS records and update the lease with the new settings.
                conditionalNCRRemoval(query, old_lease, lease, ctx.hostname_,
                                      do_fwd, do_rev);
            }

            // We need to repeat that check for leases that used to be used, but
            // are no longer valid.
            if (!ctx.old_leases_.empty()) {
                old_lease = *ctx.old_leases_.begin();
                conditionalNCRRemoval(query, old_lease, lease, ctx.hostname_,
                                      do_fwd, do_rev);
            }
        }
    } else {
        // Allocation engine did not allocate a lease. The engine logged
        // cause of that failure. The only thing left is to insert
        // status code to pass the sad news to the client.

        LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, fake_allocation ?
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

void
Dhcpv6Srv::conditionalNCRRemoval(const Pkt6Ptr& query, Lease6Ptr& old_lease,
                                 Lease6Ptr& new_lease, const std::string& hostname,
                                 bool do_fwd, bool do_rev) {
    if (old_lease && !new_lease->hasIdenticalFqdn(*old_lease)) {
        LOG_DEBUG(ddns_logger, DBG_DHCP6_DETAIL, DHCP6_DDNS_LEASE_ASSIGN_FQDN_CHANGE)
            .arg(query->getLabel())
            .arg(old_lease->toText())
            .arg(hostname)
            .arg(do_rev ? "true" : "false")
            .arg(do_fwd ? "true" : "false");

        // Schedule removal of the existing lease.
        createRemovalNameChangeRequest(query, old_lease);
    }
}

OptionPtr
Dhcpv6Srv::assignIA_PD(const Pkt6Ptr& query, const Pkt6Ptr& answer,
                       AllocEngine::ClientContext6& orig_ctx,
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

    LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_PD_REQUEST)
        .arg(query->getLabel())
        .arg(ia->getIAID())
        .arg(hint_opt ? hint.toText() : "(no hint)");


    const Subnet6Ptr& subnet = orig_ctx.subnet_;
    const DuidPtr& duid = orig_ctx.duid_;

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
    bool fake_allocation = (answer->getType() != DHCPV6_REPLY);

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honor the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    Lease6Collection old_leases;
    AllocEngine::ClientContext6 ctx(subnet, duid, ia->getIAID(), hint, Lease::TYPE_PD,
                                    false, false, string(), fake_allocation);
    ctx.callout_handle_ = getCalloutHandle(query);
    ctx.hwaddr_ = orig_ctx.hwaddr_;
    ctx.host_ = orig_ctx.host_;

    Lease6Collection leases = alloc_engine_->allocateLeases6(ctx);

    if (!leases.empty()) {

        ia_rsp->setT1(subnet->getT1());
        ia_rsp->setT2(subnet->getT2());

        for (Lease6Collection::iterator l = leases.begin();
             l != leases.end(); ++l) {

            // We have a lease! Let's wrap its content into IA_PD option
            // with IAADDR suboption.
            LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, fake_allocation ?
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
        }

        // It would be possible to insert status code=0(success) as well,
        // but this is considered waste of bandwidth as absence of status
        // code is considered a success.

    } else {
        // Allocation engine did not allocate a lease. The engine logged
        // cause of that failure. The only thing left is to insert
        // status code to pass the sad news to the client.

        LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, fake_allocation ?
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
                       AllocEngine::ClientContext6& orig_ctx,
                       boost::shared_ptr<Option6IA> ia) {

    LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_NA_EXTEND)
        .arg(query->getLabel())
        .arg(ia->getIAID());

    // convenience values
    const Subnet6Ptr& subnet = orig_ctx.subnet_;
    const DuidPtr& duid = orig_ctx.duid_;

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

    // Get DDNS udpate directions
    bool do_fwd = false;
    bool do_rev = false;
    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option6ClientFqdn>(answer->getOption(D6O_CLIENT_FQDN));
    if (fqdn) {
        CfgMgr::instance().getD2ClientMgr().getUpdateDirections(*fqdn,
                                                                do_fwd, do_rev);
    }

    // Create client context for this renewal
    AllocEngine::ClientContext6 ctx(subnet, duid, ia->getIAID(),
                                    IOAddress::IPV6_ZERO_ADDRESS(), Lease::TYPE_NA,
                                    do_fwd, do_rev, orig_ctx.hostname_, false);

    ctx.callout_handle_ = getCalloutHandle(query);
    ctx.query_ = query;
    ctx.ia_rsp_ = ia_rsp;
    ctx.hwaddr_ = orig_ctx.hwaddr_;
    ctx.host_ = orig_ctx.host_;

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
            // As we use Dhcpv6Srv::unpackOptions() that is guaranteed to use
            // Option6IAAddr for D6O_IAADDR, this should never happen. The only
            // case would be with badly mis-implemented hook libraries that
            // insert invalid option objects. There's no way to protect against
            // this.
            continue;
        }
        ctx.hints_.push_back(make_pair(iaaddr->getAddress(), 128));
    }

    // We need to remember it as we'll be removing hints from this list as
    // we extend, cancel or otherwise deal with the leases.
    bool hints_present = !ctx.hints_.empty();

    /// @todo: This was clarified in draft-ietf-dhc-dhcpv6-stateful-issues that
    /// the server is allowed to assign new leases in both Renew and Rebind. For
    /// now, we only support it in Renew, because it breaks a lot of Rebind
    /// unit-tests. Ultimately, whether we allow it or not, should be exposed
    /// as configurable policy. See ticket #3717.
    if (query->getType() == DHCPV6_RENEW) {
        ctx.allow_new_leases_in_renewals_ = true;
    }

    Lease6Collection leases = alloc_engine_->renewLeases6(ctx);

    // Ok, now we have the leases extended. We have:
    // - what the client tried to renew in ctx.hints_
    // - what we actually assigned in leases
    // - old leases that are no longer valid in ctx.old_leases_

    // For all leases we have now, add the IAADDR with non-zero lifetimes.
    for (Lease6Collection::const_iterator l = leases.begin(); l != leases.end(); ++l) {
        Option6IAAddrPtr iaaddr(new Option6IAAddr(D6O_IAADDR,
                                (*l)->addr_, (*l)->preferred_lft_, (*l)->valid_lft_));
        ia_rsp->addOption(iaaddr);

        // Now remove this address from the hints list.
        AllocEngine::HintType tmp((*l)->addr_, 128);
        ctx.hints_.erase(std::remove(ctx.hints_.begin(), ctx.hints_.end(), tmp),
                         ctx.hints_.end());
    }

    // For the leases that we just retired, send the addresses with 0 lifetimes.
    for (Lease6Collection::const_iterator l = ctx.old_leases_.begin();
                                          l != ctx.old_leases_.end(); ++l) {
        Option6IAAddrPtr iaaddr(new Option6IAAddr(D6O_IAADDR,
                                                  (*l)->addr_, 0, 0));
        ia_rsp->addOption(iaaddr);

        // Now remove this address from the hints list.
        AllocEngine::HintType tmp((*l)->addr_, 128);
        ctx.hints_.erase(std::remove(ctx.hints_.begin(), ctx.hints_.end(), tmp),
                         ctx.hints_.end());

        // If the new FQDN settings have changed for the lease, we need to
        // delete any existing FQDN records for this lease.
        if (((*l)->hostname_ != ctx.hostname_) || ((*l)->fqdn_fwd_ != do_fwd) ||
            ((*l)->fqdn_rev_ != do_rev)) {
            LOG_DEBUG(ddns_logger, DBG_DHCP6_DETAIL,
                      DHCP6_DDNS_LEASE_RENEW_FQDN_CHANGE)
                .arg(query->getLabel())
                .arg((*l)->toText())
                .arg(ctx.hostname_)
                .arg(do_rev ? "true" : "false")
                .arg(do_fwd ? "true" : "false");

            createRemovalNameChangeRequest(query, *l);
        }
    }

    // Finally, if there are any addresses requested that we haven't dealt with
    // already, inform the client that he can't have them.
    for (AllocEngine::HintContainer::const_iterator hint = ctx.hints_.begin();
         hint != ctx.hints_.end(); ++hint) {
        Option6IAAddrPtr iaaddr(new Option6IAAddr(D6O_IAADDR,
                                                  hint->first, 0, 0));
        ia_rsp->addOption(iaaddr);
    }

    // All is left is to insert the status code.
    if (leases.empty()) {
        // We did not assign anything. If client has sent something, then
        // the status code is NoBinding, if he sent an empty IA_NA, then it's
        // NoAddrsAvailable
        if (hints_present) {
            // Insert status code NoBinding to indicate that the lease does not
            // exist for this client.
            ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                              "Sorry, no known leases for this duid/iaid/subnet."));

            LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, DHCP6_EXTEND_NA_UNKNOWN)
                .arg(query->getLabel())
                .arg(ia->getIAID())
                .arg(subnet->toText());
        } else {
            ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoAddrsAvail,
                              "Sorry, no addresses could be assigned at this time."));
        }
    } else {
        // Yay, the client still has something. For now, let's not insert
        // status-code=success to conserve bandwidth.
    }

    return (ia_rsp);
}

OptionPtr
Dhcpv6Srv::extendIA_PD(const Pkt6Ptr& query,
                       AllocEngine::ClientContext6& orig_ctx,
                       boost::shared_ptr<Option6IA> ia) {

    LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_PD_EXTEND)
        .arg(query->getLabel())
        .arg(ia->getIAID());

    const Subnet6Ptr& subnet = orig_ctx.subnet_;
    const DuidPtr& duid = orig_ctx.duid_;

    // Let's create a IA_PD response and fill it in later
    Option6IAPtr ia_rsp(new Option6IA(D6O_IA_PD, ia->getIAID()));

    // If there is no subnet for the particular client, we can't retrieve
    // information about client's leases from lease database. We treat this
    // as no binding for the client.
    if (!subnet) {
        // Per RFC3633, section 12.2, if there is no binding and we are
        // processing a Renew, the NoBinding status code should be returned.
        if (query->getType() == DHCPV6_RENEW) {
            // Insert status code NoBinding
            ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_NoBinding,
                                               "Sorry, no known PD leases"
                                               " for this duid/iaid."));
            return (ia_rsp);

        // Per RFC3633, section 12.2, if there is no binding and we are
        // processing Rebind, the message has to be discarded (assuming that
        // the server doesn't know if the prefix in the IA_PD option is
        // appropriate for the client's link). The exception being thrown
        // here should propagate to the main loop and cause the message to
        // be discarded.
        } else {

            /// @todo: RFC3315bis will probably change that behavior. Client
            /// may rebind prefixes and addresses at the same time.
            isc_throw(DHCPv6DiscardMessageError, "no subnet found for the"
                      " client sending Rebind to extend lifetime of the"
                      " prefix (DUID=" << duid->toText() << ", IAID="
                      << ia->getIAID() << ")");
        }
    }

    // Set up T1, T2 timers
    ia_rsp->setT1(subnet->getT1());
    ia_rsp->setT2(subnet->getT2());

    // Create client context for this renewal
    static const IOAddress none("::");
    AllocEngine::ClientContext6 ctx(subnet, duid, ia->getIAID(), none,
                                    Lease::TYPE_PD, false, false, string(""),
                                    false);
    ctx.callout_handle_ = getCalloutHandle(query);
    ctx.query_ = query;
    ctx.ia_rsp_ = ia_rsp;
    ctx.hwaddr_ = orig_ctx.hwaddr_;
    ctx.host_ = orig_ctx.host_;

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
            // As we use Dhcpv6Srv::unpackOptions() that is guaranteed to use
            // Option6IAPrefix for D6O_IAPREFIX, this should never happen. The only
            // case would be with badly mis-implemented hook libraries that
            // insert invalid option objects. There's no way to protect against
            // this.
            continue;
        }

        // Put the client's prefix into the hints list.
        ctx.hints_.push_back(make_pair(prf->getAddress(), prf->getLength()));
    }
    // We need to remember it as we'll be removing hints from this list as
    // we extend, cancel or otherwise deal with the leases.
    bool hints_present = !ctx.hints_.empty();

    /// @todo: The draft-ietf-dhc-dhcpv6-stateful-issues added a new capability
    /// of the server to to assign new PD leases in both Renew and Rebind.
    /// There's allow_new_leases_in_renewals_ in the ClientContext6, but we
    /// currently not use it in PD yet. This should be implemented as part
    /// of the stateful-issues implementation effort. See ticket #3718.

    // Call Allocation Engine and attempt to renew leases. Number of things
    // may happen. Leases may be extended, revoked (if the lease is no longer
    // valid or reserved for someone else), or new leases may be added.
    // Important parameters are:
    // - returned container - current valid leases
    // - old_leases - leases that used to be, but are no longer valid
    // - changed_leases - leases that have FQDN changed (not really important
    //                    in PD context)
    Lease6Collection leases = alloc_engine_->renewLeases6(ctx);

    // For all the leases we have now, add the IAPPREFIX with non-zero lifetimes
    for (Lease6Collection::const_iterator l = leases.begin(); l != leases.end(); ++l) {
        Option6IAPrefixPtr prf(new Option6IAPrefix(D6O_IAPREFIX,
                               (*l)->addr_, (*l)->prefixlen_,
                               (*l)->preferred_lft_, (*l)->valid_lft_));
        ia_rsp->addOption(prf);

        // Now remove this address from the hints list.
        AllocEngine::HintType tmp((*l)->addr_, (*l)->prefixlen_);
        ctx.hints_.erase(std::remove(ctx.hints_.begin(), ctx.hints_.end(), tmp),
                                     ctx.hints_.end());
    }

    /// @todo: Maybe we should iterate over ctx.old_leases_, i.e. the leases
    /// that used to be valid, but they are not anymore.

    // For all the leases the client had requested, but we didn't assign, put them with
    // zero lifetimes
    // Finally, if there are any addresses requested that we haven't dealt with
    // already, inform the client that he can't have them.
    for (AllocEngine::HintContainer::const_iterator prefix = ctx.hints_.begin();
         prefix != ctx.hints_.end(); ++prefix) {
        OptionPtr prefix_opt(new Option6IAPrefix(D6O_IAPREFIX, prefix->first,
                                                 prefix->second, 0, 0));
        ia_rsp->addOption(prefix_opt);
    }

    // All is left is to insert the status code.
    if (leases.empty()) {
        if (query->getType() == DHCPV6_RENEW) {

            // We did not assign anything. If client has sent something, then
            // the status code is NoBinding, if he sent an empty IA_NA, then it's
            // NoAddrsAvailable
            if (hints_present) {
                // Insert status code NoBinding to indicate that the lease does not
                // exist for this client.
                ia_rsp->addOption(createStatusCode(*query, *ia_rsp,
                                                   STATUS_NoBinding,
                                                   "Sorry, no known PD leases for"
                                                   " this duid/iaid/subnet."));
            } else {
                ia_rsp->addOption(createStatusCode(*query, *ia_rsp,
                                                   STATUS_NoPrefixAvail,
                                                   "Sorry, no prefixes could be"
                                                   " assigned at this time."));
            }
        } else {
            // Per RFC3633, section 12.2, if there is no binding and we are
            // processing Rebind, the message has to be discarded (assuming that
            // the server doesn't know if the prefix in the IA_PD option is
            // appropriate for the client's link). The exception being thrown
            // here should propagate to the main loop and cause the message to
            // be discarded.
            isc_throw(DHCPv6DiscardMessageError, "no binding found for the"
                      " DUID=" << duid->toText() << ", IAID="
                      << ia->getIAID() << ", subnet="
                      << subnet->toText() << " when processing a Rebind"
                      " message with IA_PD option");
        }
    }

    return (ia_rsp);
}

void
Dhcpv6Srv::extendLeases(const Pkt6Ptr& query, Pkt6Ptr& reply,
                       AllocEngine::ClientContext6& ctx) {

    // We will try to extend lease lifetime for all IA options in the client's
    // Renew or Rebind message.
    /// @todo add support for IA_TA

    /// @todo - assignLeases() drops the packet as RFC violation, shouldn't
    /// we do that here? Shouldn't sanityCheck defend against this? Maybe
    /// this should treated as a code error instead. If we're this far with
    /// no duid that seems wrong.
    if (!ctx.duid_) {
        // This should not happen. We have checked this before.
        reply->addOption(createStatusCode(*query, STATUS_UnspecFail,
                         "You did not include mandatory client-id"));
        return;
    }

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

    // We need to release addresses for all IA_NA options in the client's
    // RELEASE message.
    // @todo Add support for IA_TA
    // @todo Add support for IA_PD
    // @todo Consider supporting more than one address in a single IA_NA.
    // That was envisaged by RFC3315, but it never happened. The only
    // software that supports that is Dibbler, but its author seriously doubts
    // if anyone is really using it. Clients that want more than one address
    // just include more instances of IA_NA options.

    // Let's set the status to be success by default. We can override it with
    // error status if needed. The important thing to understand here is that
    // the global status code may be set to success only if all IA options were
    // handled properly. Therefore the releaseIA_NA and releaseIA_PD options
    // may turn the status code to some error, but can't turn it back to success.
    int general_status = STATUS_Success;
    for (OptionCollection::iterator opt = release->options_.begin();
         opt != release->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = releaseIA_NA(ctx.duid_, release, general_status,
                                   boost::dynamic_pointer_cast<Option6IA>(opt->second));
            if (answer_opt) {
                reply->addOption(answer_opt);
            }
            break;
        }
        case D6O_IA_PD: {
            OptionPtr answer_opt = releaseIA_PD(ctx.duid_, release, general_status,
                                   boost::dynamic_pointer_cast<Option6IA>(opt->second));
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
    }

    // To be pedantic, we should also include status code in the top-level
    // scope, not just in each IA_NA. See RFC3315, section 18.2.6.
    // This behavior will likely go away in RFC3315bis.
    reply->addOption(createStatusCode(*release, general_status,
                     "Summary status for all processed IA_NAs"));
}

OptionPtr
Dhcpv6Srv::releaseIA_NA(const DuidPtr& duid, const Pkt6Ptr& query,
                        int& general_status, boost::shared_ptr<Option6IA> ia) {

    LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_NA_RELEASE)
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

        LOG_ERROR(lease_logger, DHCP6_LEASE_NA_WITHOUT_DUID)
            .arg(query->getLabel())
            .arg(release_addr->getAddress().toText());

        general_status = STATUS_UnspecFail;
        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_UnspecFail,
                          "Database consistency check failed when trying to RELEASE"));
        return (ia_rsp);
    }

    if (*duid != *(lease->duid_)) {

        // Sorry, it's not your address. You can't release it.
        LOG_INFO(lease_logger, DHCP6_RELEASE_NA_FAIL_WRONG_DUID)
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
        LOG_WARN(lease_logger, DHCP6_RELEASE_NA_FAIL_WRONG_IAID)
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
        if (callout_handle->getSkip()) {
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

        LOG_ERROR(lease_logger, DHCP6_RELEASE_NA_FAIL)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(lease->iaid_);
        general_status = STATUS_UnspecFail;

        return (ia_rsp);
    } else {
        LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, DHCP6_RELEASE_NA)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(lease->iaid_);

        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_Success,
                          "Lease released. Thank you, please come again."));

        // Check if a lease has flags indicating that the FQDN update has
        // been performed. If so, create NameChangeRequest which removes
        // the entries.
        createRemovalNameChangeRequest(query, lease);

        return (ia_rsp);
    }
}

OptionPtr
Dhcpv6Srv::releaseIA_PD(const DuidPtr& duid, const Pkt6Ptr& query,
                        int& general_status, boost::shared_ptr<Option6IA> ia) {
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
        LOG_ERROR(lease_logger, DHCP6_LEASE_PD_WITHOUT_DUID)
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
        LOG_INFO(lease_logger, DHCP6_RELEASE_PD_FAIL_WRONG_DUID)
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
        LOG_WARN(lease_logger, DHCP6_RELEASE_PD_FAIL_WRONG_IAID)
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

        // Delete all previous arguments
        callout_handle->deleteAllArguments();

        // Pass the original packet
        callout_handle->setArgument("query6", query);

        // Pass the lease to be updated
        callout_handle->setArgument("lease6", lease);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_lease6_release_, *callout_handle);

        skip = callout_handle->getSkip();
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

        LOG_ERROR(lease_logger, DHCP6_RELEASE_PD_FAIL)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(static_cast<int>(lease->prefixlen_))
            .arg(lease->iaid_);
        general_status = STATUS_UnspecFail;

    } else {
        LOG_DEBUG(lease_logger, DBG_DHCP6_DETAIL, DHCP6_RELEASE_PD)
            .arg(query->getLabel())
            .arg(lease->addr_.toText())
            .arg(static_cast<int>(lease->prefixlen_))
            .arg(lease->iaid_);

        ia_rsp->addOption(createStatusCode(*query, *ia_rsp, STATUS_Success,
                          "Lease released. Thank you, please come again."));
    }

    return (ia_rsp);
}



Pkt6Ptr
Dhcpv6Srv::processSolicit(const Pkt6Ptr& solicit) {

    sanityCheck(solicit, MANDATORY, FORBIDDEN);

    // Let's create a simplified client context here.
    AllocEngine::ClientContext6 ctx = createContext(solicit);

    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, solicit->getTransid()));

    // Handle Rapid Commit option, if present.
    if (ctx.subnet_ && ctx.subnet_->getRapidCommit()) {
        OptionPtr opt_rapid_commit = solicit->getOption(D6O_RAPID_COMMIT);
        if (opt_rapid_commit) {

            /// @todo uncomment when #3807 is merged!
/*            LOG_DEBUG(options_logger, DBG_DHCP6_DETAIL, DHCP6_RAPID_COMMIT)
                .arg(solicit->getLabel()); */

            // If Rapid Commit has been sent by the client, change the
            // response type to Reply and include Rapid Commit option.
            response->setType(DHCPV6_REPLY);
            response->addOption(opt_rapid_commit);
        }
    }

    copyClientOptions(solicit, response);
    appendDefaultOptions(solicit, response);
    appendRequestedOptions(solicit, response, ctx);
    appendRequestedVendorOptions(solicit, response, ctx);

    processClientFqdn(solicit, response, ctx);
    assignLeases(solicit, response, ctx);

    // Only generate name change requests if sending a Reply as a result
    // of receiving Rapid Commit option.
    if (response->getType() == DHCPV6_REPLY) {
        createNameChangeRequests(response);
    }

    return (response);
}

Pkt6Ptr
Dhcpv6Srv::processRequest(const Pkt6Ptr& request) {

    sanityCheck(request, MANDATORY, MANDATORY);

    // Let's create a simplified client context here.
    AllocEngine::ClientContext6 ctx = createContext(request);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, request->getTransid()));

    copyClientOptions(request, reply);
    appendDefaultOptions(request, reply);
    appendRequestedOptions(request, reply, ctx);
    appendRequestedVendorOptions(request, reply, ctx);

    processClientFqdn(request, reply, ctx);
    assignLeases(request, reply, ctx);
    generateFqdn(reply);
    createNameChangeRequests(reply);

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processRenew(const Pkt6Ptr& renew) {

    sanityCheck(renew, MANDATORY, MANDATORY);

    // Let's create a simplified client context here.
    AllocEngine::ClientContext6 ctx = createContext(renew);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, renew->getTransid()));

    copyClientOptions(renew, reply);
    appendDefaultOptions(renew, reply);
    appendRequestedOptions(renew, reply, ctx);

    processClientFqdn(renew, reply, ctx);
    extendLeases(renew, reply, ctx);
    generateFqdn(reply);
    createNameChangeRequests(reply);

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processRebind(const Pkt6Ptr& rebind) {

    // Let's create a simplified client context here.
    AllocEngine::ClientContext6 ctx = createContext(rebind);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, rebind->getTransid()));

    copyClientOptions(rebind, reply);
    appendDefaultOptions(rebind, reply);
    appendRequestedOptions(rebind, reply, ctx);

    processClientFqdn(rebind, reply, ctx);
    extendLeases(rebind, reply, ctx);
    generateFqdn(reply);
    createNameChangeRequests(rebind);

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processConfirm(const Pkt6Ptr& confirm) {

    // Let's create a simplified client context here.
    AllocEngine::ClientContext6 ctx = createContext(confirm);

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
    appendDefaultOptions(confirm, reply);
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
Dhcpv6Srv::processRelease(const Pkt6Ptr& release) {

    sanityCheck(release, MANDATORY, MANDATORY);

    // Let's create a simplified client context here.
    AllocEngine::ClientContext6 ctx = createContext(release);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, release->getTransid()));

    copyClientOptions(release, reply);
    appendDefaultOptions(release, reply);

    releaseLeases(release, reply, ctx);

    /// @todo If client sent a release and we should remove outstanding
    /// DNS records.

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processDecline(const Pkt6Ptr& decline) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, decline->getTransid()));
    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processInfRequest(const Pkt6Ptr& inf_request) {

    // Let's create a simplified client context here.
    AllocEngine::ClientContext6 ctx = createContext(inf_request);

    // Create a Reply packet, with the same trans-id as the client's.
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, inf_request->getTransid()));

    // Copy client options (client-id, also relay information if present)
    copyClientOptions(inf_request, reply);

    // Append default options, i.e. options that the server is supposed
    // to put in all messages it sends (server-id for now, but possibly other
    // options once we start supporting authentication)
    appendDefaultOptions(inf_request, reply);

    // Try to assign options that were requested by the client.
    appendRequestedOptions(inf_request, reply, ctx);

    return (reply);
}

size_t
Dhcpv6Srv::unpackOptions(const OptionBuffer& buf,
                         const std::string& option_space,
                         isc::dhcp::OptionCollection& options,
                         size_t* relay_msg_offset,
                         size_t* relay_msg_len) {
    size_t offset = 0;
    size_t length = buf.size();

    OptionDefContainer option_defs;
    if (option_space == "dhcp6") {
        // Get the list of standard option definitions.
        option_defs = LibDHCP::getOptionDefs(Option::V6);
    } else if (!option_space.empty()) {
        OptionDefContainerPtr option_defs_ptr =
            CfgMgr::instance().getCurrentCfg()->getCfgOptionDef()->
            getAll(option_space);
        if (option_defs_ptr != NULL) {
            option_defs = *option_defs_ptr;
        }
    }

    // Get the search index #1. It allows to search for option definitions
    // using option code.
    const OptionDefContainerTypeIndex& idx = option_defs.get<1>();

    // The buffer being read comprises a set of options, each starting with
    // a two-byte type code and a two-byte length field.
    while (offset + 4 <= length) {
        // At this point, from the while condition, we know that there
        // are at least 4 bytes available following offset in the
        // buffer.
        uint16_t opt_type = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        uint16_t opt_len = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        if (offset + opt_len > length) {
            // @todo: consider throwing exception here.

            // We peeked at the option header of the next option, but discovered
            // that it would end up beyond buffer end, so the option is
            // truncated. Hence we can't parse it. Therefore we revert
            // by by those four bytes (as if we never parsed them).
            return (offset - 4);
        }

        if (opt_type == D6O_RELAY_MSG && relay_msg_offset && relay_msg_len) {
            // remember offset of the beginning of the relay-msg option
            *relay_msg_offset = offset;
            *relay_msg_len = opt_len;

            // do not create that relay-msg option
            offset += opt_len;
            continue;
        }

        // Get all definitions with the particular option code. Note that option
        // code is non-unique within this container however at this point we
        // expect to get one option definition with the particular code. If more
        // are returned we report an error.
        const OptionDefContainerTypeRange& range = idx.equal_range(opt_type);
        // Get the number of returned option definitions for the option code.
        size_t num_defs = distance(range.first, range.second);

        OptionPtr opt;
        if (num_defs > 1) {
            // Multiple options of the same code are not supported right now!
            isc_throw(isc::Unexpected, "Internal error: multiple option definitions"
                      " for option type " << opt_type << " returned. Currently it is not"
                      " supported to initialize multiple option definitions"
                      " for the same option code. This will be supported once"
                      " support for option spaces is implemented");
        } else if (num_defs == 0) {
            // @todo Don't crash if definition does not exist because only a few
            // option definitions are initialized right now. In the future
            // we will initialize definitions for all options and we will
            // remove this elseif. For now, return generic option.
            opt = OptionPtr(new Option(Option::V6, opt_type,
                                       buf.begin() + offset,
                                       buf.begin() + offset + opt_len));
            opt->setEncapsulatedSpace("dhcp6");
        } else {
            // The option definition has been found. Use it to create
            // the option instance from the provided buffer chunk.
            const OptionDefinitionPtr& def = *(range.first);
            assert(def);
            opt = def->optionFactory(Option::V6, opt_type,
                                     buf.begin() + offset,
                                     buf.begin() + offset + opt_len,
                                     boost::bind(&Dhcpv6Srv::unpackOptions, this, _1, _2,
                                                 _3, _4, _5));
        }
        // add option to options
        options.insert(std::make_pair(opt_type, opt));
        offset += opt_len;
    }

    return (offset);
}

void Dhcpv6Srv::classifyPacket(const Pkt6Ptr& pkt) {
    OptionVendorClassPtr vclass = boost::dynamic_pointer_cast<
        OptionVendorClass>(pkt->getOption(D6O_VENDOR_CLASS));

    if (!vclass || vclass->getTuplesNum() == 0) {
        return;
    }

    std::ostringstream classes;
    if (vclass->hasTuple(DOCSIS3_CLASS_MODEM)) {
        classes << VENDOR_CLASS_PREFIX << DOCSIS3_CLASS_MODEM;

    } else if (vclass->hasTuple(DOCSIS3_CLASS_EROUTER)) {
        classes << VENDOR_CLASS_PREFIX << DOCSIS3_CLASS_EROUTER;

    } else {
        classes << VENDOR_CLASS_PREFIX << vclass->getTuple(0).getText();
    }

    // If there is no class identified, leave.
    if (!classes.str().empty()) {
        pkt->addClass(classes.str());
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_CLASS_ASSIGNED)
            .arg(classes.str());
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

    LOG_DEBUG(ddns_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_DDNS_FQDN_GENERATED)
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

    } catch (const Exception& ex) {
        LOG_ERROR(ddns_logger, DHCP6_DDNS_GENERATED_FQDN_UPDATE_FAIL)
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
Dhcpv6Srv::d2ClientErrorHandler(const
                                dhcp_ddns::NameChangeSender::Result result,
                                dhcp_ddns::NameChangeRequestPtr& ncr) {
    LOG_ERROR(ddns_logger, DHCP6_DDNS_REQUEST_SEND_FAILED).
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
#ifdef HAVE_MYSQL
        tmp << "database: MySQL";
#else
#ifdef HAVE_PGSQL
        tmp << "database: PostgreSQL";
#else
        tmp << "no database";
#endif
#endif
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

};
};
