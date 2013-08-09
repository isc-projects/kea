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

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt6.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/utils.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>
#include <util/range_utilities.h>
#include <util/encode/hex.h>
#include <hooks/hooks_manager.h>
#include <hooks/callout_handle.h>

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/erase.hpp>

#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <fstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;
using namespace std;

namespace {

/// Structure that holds registered hook indexes
struct Dhcp6Hooks {
    int hook_index_buffer6_receive_;///< index for "buffer6_receive" hook point
    int hook_index_pkt6_receive_;   ///< index for "pkt6_receive" hook point
    int hook_index_subnet6_select_; ///< index for "subnet6_select" hook point
    int hook_index_lease6_renew_;   ///< index for "lease6_renew" hook point
    int hook_index_lease6_release_; ///< index for "lease6_release" hook point
    int hook_index_pkt6_send_;      ///< index for "pkt6_send" hook point
    int hook_index_buffer6_send_;   ///< index for "buffer6_send" hook point

    /// Constructor that registers hook points for DHCPv6 engine
    Dhcp6Hooks() {
        hook_index_buffer6_receive_= HooksManager::registerHook("buffer6_receive");
        hook_index_pkt6_receive_   = HooksManager::registerHook("pkt6_receive");
        hook_index_subnet6_select_ = HooksManager::registerHook("subnet6_select");
        hook_index_lease6_renew_   = HooksManager::registerHook("lease6_renew");
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

}; // anonymous namespace

namespace isc {
namespace dhcp {

/// @brief file name of a server-id file
///
/// Server must store its duid in persistent storage that must not change
/// between restarts. This is name of the file that is created in dataDir
/// (see isc::dhcp::CfgMgr::getDataDir()). It is a text file that uses
/// double digit hex values separated by colons format, e.g.
/// 01:ff:02:03:06:80:90:ab:cd:ef. Server will create it during first
/// run and then use it afterwards.
static const char* SERVER_DUID_FILE = "b10-dhcp6-serverid";

Dhcpv6Srv::Dhcpv6Srv(uint16_t port)
:alloc_engine_(), serverid_(), shutdown_(true), port_(port)
{

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_OPEN_SOCKET).arg(port);

    // Initialize objects required for DHCP server operation.
    try {
        // Port 0 is used for testing purposes. It means that the server should
        // not open any sockets at all. Some tests, e.g. configuration parser,
        // require Dhcpv6Srv object, but they don't really need it to do
        // anything. This speed up and simplifies the tests.
        if (port > 0) {
            if (IfaceMgr::instance().countIfaces() == 0) {
                LOG_ERROR(dhcp6_logger, DHCP6_NO_INTERFACES);
                return;
            }
            IfaceMgr::instance().openSockets6(port_);
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

bool Dhcpv6Srv::run() {
    while (!shutdown_) {
        /// @todo Calculate actual timeout to the next event (e.g. lease
        /// expiration) once we have lease database. The idea here is that
        /// it is possible to do everything in a single process/thread.
        /// For now, we are just calling select for 1000 seconds. There
        /// were some issues reported on some systems when calling select()
        /// with too large values. Unfortunately, I don't recall the details.
        //cppcheck-suppress variableScope This is temporary anyway
        const int timeout = 1000;

        // client's message and server's response
        Pkt6Ptr query;
        Pkt6Ptr rsp;

        try {
            query = receivePacket(timeout);
        } catch (const std::exception& e) {
            LOG_ERROR(dhcp6_logger, DHCP6_PACKET_RECEIVE_FAIL).arg(e.what());
        }

        // Timeout may be reached or signal received, which breaks select() with no packet received
        if (!query) {
            continue;
        }

        bool skip_unpack = false;

        // The packet has just been received so contains the uninterpreted wire
        // data; execute callouts registered for buffer6_receive.
        if (HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_buffer6_receive_)) {
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
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_BUFFER_RCVD_SKIP);
                skip_unpack = true;
            }

            callout_handle->getArgument("query6", query);
        }

        // Unpack the packet information unless the buffer6_receive callouts
        // indicated they did it
        if (!skip_unpack) {
            if (!query->unpack()) {
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL,
                          DHCP6_PACKET_PARSE_FAIL);
                continue;
            }
        }
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_PACKET_RECEIVED)
            .arg(query->getName());
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_QUERY_DATA)
            .arg(static_cast<int>(query->getType()))
            .arg(query->getBuffer().getLength())
            .arg(query->toText());

        // At this point the information in the packet has been unpacked into
        // the various packet fields and option objects has been cretated.
        // Execute callouts registered for packet6_receive.
        if (HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_pkt6_receive_)) {
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
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_PACKET_RCVD_SKIP);
                continue;
            }

            callout_handle->getArgument("query6", query);
        }

        try {
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
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_UNKNOWN_MSG_RECEIVED)
                    .arg(static_cast<int>(query->getType()))
                    .arg(query->getIface());
                // Only action is to output a message if debug is enabled,
                // and that will be covered by the debug statement before
                // the "switch" statement.
                ;
            }

        } catch (const RFCViolation& e) {
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_REQUIRED_OPTIONS_CHECK_FAIL)
                .arg(query->getName())
                .arg(query->getRemoteAddr().toText())
                .arg(e.what());

        } catch (const isc::Exception& e) {

            // Catch-all exception (at least for ones based on the isc
            // Exception class, which covers more or less all that
            // are explicitly raised in the BIND 10 code).  Just log
            // the problem and ignore the packet. (The problem is logged
            // as a debug message because debug is disabled by default -
            // it prevents a DDOS attack based on the sending of problem
            // packets.)
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_PACKET_PROCESS_FAIL)
                .arg(query->getName())
                .arg(query->getRemoteAddr().toText())
                .arg(e.what());
        }

        if (rsp) {
            rsp->setRemoteAddr(query->getRemoteAddr());
            rsp->setLocalAddr(query->getLocalAddr());
            rsp->setRemotePort(DHCP6_CLIENT_PORT);
            rsp->setLocalPort(DHCP6_SERVER_PORT);
            rsp->setIndex(query->getIndex());
            rsp->setIface(query->getIface());

            // Specifies if server should do the packing
            bool skip_pack = false;

            // Server's reply packet now has all options and fields set.
            // Options are represented by individual objects, but the
            // output wire data has not been prepared yet.
            // Execute all callouts registered for packet6_send
            if (HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_pkt6_send_)) {
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
                    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_PACKET_SEND_SKIP);
                    skip_pack = true;
                }
            }

            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL_DATA,
                      DHCP6_RESPONSE_DATA)
                .arg(static_cast<int>(rsp->getType())).arg(rsp->toText());

            if (!skip_pack) {
                try {
                    rsp->pack();
                } catch (const std::exception& e) {
                    LOG_ERROR(dhcp6_logger, DHCP6_PACK_FAIL)
                        .arg(e.what());
                    continue;
                }
            }

            try {

                // Now all fields and options are constructed into output wire buffer.
                // Option objects modification does not make sense anymore. Hooks
                // can only manipulate wire buffer at this stage.
                // Let's execute all callouts registered for buffer6_send
                if (HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_buffer6_send_)) {
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
                        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_BUFFER_SEND_SKIP);
                        continue;
                    }
                    
                    callout_handle->getArgument("response6", rsp);
                }

                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL_DATA,
                          DHCP6_RESPONSE_DATA)
                    .arg(static_cast<int>(rsp->getType())).arg(rsp->toText());

                sendPacket(rsp);
            } catch (const std::exception& e) {
                LOG_ERROR(dhcp6_logger, DHCP6_PACKET_SEND_FAIL)
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
    for (IfaceMgr::IfaceCollection::const_iterator iface = ifaces.begin();
         iface != ifaces.end(); ++iface) {
        // All the following checks could be merged into one multi-condition
        // statement, but let's keep them separated as perhaps one day
        // we will grow knobs to selectively turn them on or off. Also,
        // this code is used only *once* during first start on a new machine
        // and then server-id is stored. (or at least it will be once
        // DUID storage is implemented)

        // I wish there was a this_is_a_real_physical_interface flag...

        // MAC address should be at least 6 bytes. Although there is no such
        // requirement in any RFC, all decent physical interfaces (Ethernet,
        // WiFi, Infiniband, etc.) have 6 bytes long MAC address. We want to
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
        // seconds since 01-01-1970. DUID_TIME_EPOCH substution corrects that.
        time_t seconds = time(NULL);
        seconds -= DUID_TIME_EPOCH;

        OptionBuffer srvid(8 + iface->getMacLen());
        writeUint16(DUID::DUID_LLT, &srvid[0]);
        writeUint16(HWTYPE_ETHERNET, &srvid[2]);
        writeUint32(static_cast<uint32_t>(seconds), &srvid[4]);
        memcpy(&srvid[0] + 8, iface->getMac(), iface->getMacLen());

        serverid_ = OptionPtr(new Option(Option::V6, D6O_SERVERID,
                                         srvid.begin(), srvid.end()));
        return;
    }

    // If we reached here, there are no suitable interfaces found.
    // Either interface detection is not supported on this platform or
    // this is really weird box. Let's use DUID-EN instead.
    // See Section 9.3 of RFC3315 for details.

    OptionBuffer srvid(12);
    writeUint16(DUID::DUID_EN, &srvid[0]);
    writeUint32(ENTERPRISE_ID_ISC, &srvid[2]);

    // Length of the identifier is company specific. I hereby declare
    // ISC "standard" of 6 bytes long pseudo-random numbers.
    srandom(time(NULL));
    fillRandom(&srvid[6], &srvid[12]);

    serverid_ = OptionPtr(new Option(Option::V6, D6O_SERVERID,
                                     srvid.begin(), srvid.end()));
}

void
Dhcpv6Srv::copyDefaultOptions(const Pkt6Ptr& question, Pkt6Ptr& answer) {
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
Dhcpv6Srv::appendRequestedOptions(const Pkt6Ptr& question, Pkt6Ptr& answer) {
    // Get the configured subnet suitable for the incoming packet.
    Subnet6Ptr subnet = selectSubnet(question);
    // Leave if there is no subnet matching the incoming packet.
    // There is no need to log the error message here because
    // it will be logged in the assignLease() when it fails to
    // pick the suitable subnet. We don't want to duplicate
    // error messages in such case.
    if (!subnet) {
        return;
    }

    // Client requests some options using ORO option. Try to
    // get this option from client's message.
    boost::shared_ptr<OptionIntArray<uint16_t> > option_oro =
        boost::dynamic_pointer_cast<OptionIntArray<uint16_t> >(question->getOption(D6O_ORO));
    // Option ORO not found. Don't do anything then.
    if (!option_oro) {
        return;
    }
    // Get the list of options that client requested.
    const std::vector<uint16_t>& requested_opts = option_oro->getValues();
    BOOST_FOREACH(uint16_t opt, requested_opts) {
        Subnet::OptionDescriptor desc = subnet->getOptionDescriptor("dhcp6", opt);
        if (desc.option) {
            answer->addOption(desc.option);
        }
    }
}

OptionPtr
Dhcpv6Srv::createStatusCode(uint16_t code, const std::string& text) {
    // @todo This function uses OptionCustom class to manage contents
    // of the data fields. Since this this option is frequently used
    // it may be good to implement dedicated class to avoid performance
    // impact.

    // Get the definition of the option holding status code.
    OptionDefinitionPtr status_code_def =
        LibDHCP::getOptionDef(Option::V6, D6O_STATUS_CODE);
    // This definition is assumed to be initialized in LibDHCP.
    assert(status_code_def);

    // As there is no dedicated class to represent Status Code
    // the OptionCustom class is used here instead.
    OptionCustomPtr option_status =
        OptionCustomPtr(new OptionCustom(*status_code_def, Option::V6));
    assert(option_status);

    // Set status code to 'code' (0 - means data field #0).
    option_status->writeInteger(code, 0);
    // Set a message (1 - means data field #1).
    option_status->writeString(text, 1);
    return (option_status);
}

void
Dhcpv6Srv::sanityCheck(const Pkt6Ptr& pkt, RequirementLevel clientid,
                       RequirementLevel serverid) {
    Option::OptionCollection client_ids = pkt->getOptions(D6O_CLIENTID);
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

    Option::OptionCollection server_ids = pkt->getOptions(D6O_SERVERID);
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

    Subnet6Ptr subnet;

    if (question->relay_info_.empty()) {
        // This is a direct (non-relayed) message

        // Try to find a subnet if received packet from a directly connected client
        subnet = CfgMgr::instance().getSubnet6(question->getIface());
        if (!subnet) {
            // If no subnet was found, try to find it based on remote address
            subnet = CfgMgr::instance().getSubnet6(question->getRemoteAddr());
        }
    } else {

        // This is a relayed message
        OptionPtr interface_id = question->getAnyRelayOption(D6O_INTERFACE_ID,
                                                             Pkt6::RELAY_GET_FIRST);
        if (interface_id) {
            subnet = CfgMgr::instance().getSubnet6(interface_id);
        }

        if (!subnet) {
            // If no interface-id was specified (or not configured on server), let's
            // try address matching
            IOAddress link_addr = question->relay_info_.back().linkaddr_;

            // if relay filled in link_addr field, then let's use it
            if (link_addr != IOAddress("::")) {
                subnet = CfgMgr::instance().getSubnet6(link_addr);
            }
        }
    }

    // Let's execute all callouts registered for subnet6_receive
    if (HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_subnet6_select_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(question);

        // We're reusing callout_handle from previous calls
        callout_handle->deleteAllArguments();

        // Set new arguments
        callout_handle->setArgument("query6", question);
        callout_handle->setArgument("subnet6", subnet);

        // We pass pointer to const collection for performance reasons.
        // Otherwise we would get a non-trivial performance penalty each
        // time subnet6_select is called.
        callout_handle->setArgument("subnet6collection", CfgMgr::instance().getSubnets6());

        // Call user (and server-side) callouts
        HooksManager::callCallouts(Hooks.hook_index_subnet6_select_, *callout_handle);

        // Callouts decided to skip this step. This means that no subnet will be
        // selected. Packet processing will continue, but it will be severly limited
        // (i.e. only global options will be assigned)
        if (callout_handle->getSkip()) {
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_SUBNET6_SELECT_SKIP);
            return (Subnet6Ptr());
        }

        // Use whatever subnet was specified by the callout
        callout_handle->getArgument("subnet6", subnet);
    }

    return (subnet);
}

void
Dhcpv6Srv::assignLeases(const Pkt6Ptr& question, Pkt6Ptr& answer) {

    // We need to allocate addresses for all IA_NA options in the client's
    // question (i.e. SOLICIT or REQUEST) message.
    // @todo add support for IA_TA
    // @todo add support for IA_PD

    // We need to select a subnet the client is connected in.
    Subnet6Ptr subnet = selectSubnet(question);
    if (!subnet) {
        // This particular client is out of luck today. We do not have
        // information about the subnet he is connected to. This likely means
        // misconfiguration of the server (or some relays). We will continue to
        // process this message, but our response will be almost useless: no
        // addresses or prefixes, no subnet specific configuration etc. The only
        // thing this client can get is some global information (like DNS
        // servers).

        LOG_WARN(dhcp6_logger, DHCP6_SUBNET_SELECTION_FAILED)
            .arg(question->getRemoteAddr().toText())
            .arg(question->getName());

    } else {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_SUBNET_SELECTED)
            .arg(subnet->toText());
    }

    // @todo: We should implement Option6Duid some day, but we can do without it
    // just fine for now

    // Let's find client's DUID. Client is supposed to include its client-id
    // option almost all the time (the only exception is an anonymous inf-request,
    // but that is mostly a theoretical case). Our allocation engine needs DUID
    // and will refuse to allocate anything to anonymous clients.
    DuidPtr duid;
    OptionPtr opt_duid = question->getOption(D6O_CLIENTID);
    if (opt_duid) {
        duid = DuidPtr(new DUID(opt_duid->getData()));
    } else {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_CLIENTID_MISSING);
        // Let's drop the message. This client is not sane.
        isc_throw(RFCViolation, "Mandatory client-id is missing in received message");
    }

    // Now that we have all information about the client, let's iterate over all
    // received options and handle IA_NA options one by one and store our
    // responses in answer message (ADVERTISE or REPLY).
    //
    // @todo: expand this to cover IA_PD and IA_TA once we implement support for
    // prefix delegation and temporary addresses.
    for (Option::OptionCollection::iterator opt = question->options_.begin();
         opt != question->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = assignIA_NA(subnet, duid, question,
                                               boost::dynamic_pointer_cast<Option6IA>(opt->second),
                                               question);
            if (answer_opt) {
                answer->addOption(answer_opt);
            }
            break;
        }
        default:
            break;
        }
    }
}

OptionPtr
Dhcpv6Srv::assignIA_NA(const Subnet6Ptr& subnet, const DuidPtr& duid,
                       Pkt6Ptr question, boost::shared_ptr<Option6IA> ia, const Pkt6Ptr& query) {
    // If there is no subnet selected for handling this IA_NA, the only thing to do left is
    // to say that we are sorry, but the user won't get an address. As a convenience, we
    // use a different status text to indicate that (compare to the same status code,
    // but different wording below)
    if (!subnet) {
        // Create empty IA_NA option with IAID matching the request.
        // Note that we don't use OptionDefinition class to create this option.
        // This is because we prefer using a constructor of Option6IA that
        // initializes IAID. Otherwise we would have to use setIAID() after
        // creation of the option which has some performance implications.
        boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(STATUS_NoAddrsAvail, "Sorry, no subnet available."));
        return (ia_rsp);
    }

    // Check if the client sent us a hint in his IA_NA. Clients may send an
    // address in their IA_NA options as a suggestion (e.g. the last address
    // they used before).
    boost::shared_ptr<Option6IAAddr> hintOpt = boost::dynamic_pointer_cast<Option6IAAddr>
                                        (ia->getOption(D6O_IAADDR));
    IOAddress hint("::");
    if (hintOpt) {
        hint = hintOpt->getAddress();
    }

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_NA_REQUEST)
        .arg(duid?duid->toText():"(no-duid)").arg(ia->getIAID())
        .arg(hintOpt?hint.toText():"(no hint)");

    // "Fake" allocation is processing of SOLICIT message. We pretend to do an
    // allocation, but we do not put the lease in the database. That is ok,
    // because we do not guarantee that the user will get that exact lease. If
    // the user selects this server to do actual allocation (i.e. sends REQUEST)
    // it should include this hint. That will help us during the actual lease
    // allocation.
    bool fake_allocation = false;
    if (question->getType() == DHCPV6_SOLICIT) {
        /// @todo: Check if we support rapid commit
        fake_allocation = true;
    }

    CalloutHandlePtr callout_handle = getCalloutHandle(query);

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honour the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    Lease6Ptr lease = alloc_engine_->allocateAddress6(subnet, duid, ia->getIAID(),
                                                      hint, fake_allocation,
                                                      callout_handle);

    // Create IA_NA that we will put in the response.
    // Do not use OptionDefinition to create option's instance so
    // as we can initialize IAID using a constructor.
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

    if (lease) {
        // We have a lease! Let's wrap its content into IA_NA option
        // with IAADDR suboption.
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, fake_allocation?
                  DHCP6_LEASE_ADVERT:DHCP6_LEASE_ALLOC)
            .arg(lease->addr_.toText())
            .arg(duid?duid->toText():"(no-duid)")
            .arg(ia->getIAID());

        ia_rsp->setT1(subnet->getT1());
        ia_rsp->setT2(subnet->getT2());

        boost::shared_ptr<Option6IAAddr>
            addr(new Option6IAAddr(D6O_IAADDR,
                                   lease->addr_,
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

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, fake_allocation ?
                  DHCP6_LEASE_ADVERT_FAIL : DHCP6_LEASE_ALLOC_FAIL)
            .arg(duid?duid->toText():"(no-duid)")
            .arg(ia->getIAID());

        ia_rsp->addOption(createStatusCode(STATUS_NoAddrsAvail,
                          "Sorry, no address could be allocated."));
    }
    return (ia_rsp);
}

OptionPtr
Dhcpv6Srv::renewIA_NA(const Subnet6Ptr& subnet, const DuidPtr& duid,
                      const Pkt6Ptr& query, boost::shared_ptr<Option6IA> ia) {
    if (!subnet) {
        // There's no subnet select for this client. There's nothing to renew.
        boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid."));

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_RENEW_UNKNOWN_SUBNET)
            .arg(duid->toText())
            .arg(ia->getIAID());

        return (ia_rsp);
    }

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(*duid, ia->getIAID(),
                                                            subnet->getID());

    if (!lease) {
        // client renewing a lease that we don't know about.

        // Create empty IA_NA option with IAID matching the request.
        boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid."));

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_UNKNOWN_RENEW)
            .arg(duid->toText())
            .arg(ia->getIAID())
            .arg(subnet->toText());

        return (ia_rsp);
    }

    // Keep the old data in case the callout tells us to skip update
    Lease6 old_data = *lease;

    lease->preferred_lft_ = subnet->getPreferred();
    lease->valid_lft_ = subnet->getValid();
    lease->t1_ = subnet->getT1();
    lease->t2_ = subnet->getT2();
    lease->cltt_ = time(NULL);

    // Create empty IA_NA option with IAID matching the request.
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

    ia_rsp->setT1(subnet->getT1());
    ia_rsp->setT2(subnet->getT2());

    boost::shared_ptr<Option6IAAddr> addr(new Option6IAAddr(D6O_IAADDR,
                                          lease->addr_, lease->preferred_lft_,
                                          lease->valid_lft_));
    ia_rsp->addOption(addr);

    bool skip = false;
    // Execute all callouts registered for packet6_send
    if (HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_lease6_renew_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Delete all previous arguments
        callout_handle->deleteAllArguments();

        // Pass the original packet
        callout_handle->setArgument("query6", query);

        // Pass the lease to be updated
        callout_handle->setArgument("lease6", lease);

        // Pass the IA option to be sent in response
        callout_handle->setArgument("ia_na", ia_rsp);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_lease6_renew_, *callout_handle);

        // Callouts decided to skip the next processing step. The next
        // processing step would to actually renew the lease, so skip at this
        // stage means "keep the old lease as it is".
        if (callout_handle->getSkip()) {
            skip = true;
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_LEASE6_RENEW_SKIP);
        }
    }

    if (!skip) {
        LeaseMgrFactory::instance().updateLease6(lease);
    } else {
        // Copy back the original date to the lease. For MySQL it doesn't make
        // much sense, but for memfile, the Lease6Ptr points to the actual lease
        // in memfile, so the actual update is performed when we manipulate fields
        // of returned Lease6Ptr, the actual updateLease6() is no-op.
        *lease = old_data;
    }

    return (ia_rsp);
}

void
Dhcpv6Srv::renewLeases(const Pkt6Ptr& renew, Pkt6Ptr& reply) {

    // We need to renew addresses for all IA_NA options in the client's
    // RENEW message.
    // @todo add support for IA_TA
    // @todo add support for IA_PD

    // We need to select a subnet the client is connected in.
    Subnet6Ptr subnet = selectSubnet(renew);
    if (!subnet) {
        // This particular client is out of luck today. We do not have
        // information about the subnet he is connected to. This likely means
        // misconfiguration of the server (or some relays). We will continue to
        // process this message, but our response will be almost useless: no
        // addresses or prefixes, no subnet specific configuration etc. The only
        // thing this client can get is some global information (like DNS
        // servers).

        LOG_WARN(dhcp6_logger, DHCP6_SUBNET_SELECTION_FAILED)
            .arg(renew->getRemoteAddr().toText())
            .arg(renew->getName());
    } else {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_SUBNET_SELECTED)
            .arg(subnet->toText());
    }

    // Let's find client's DUID. Client is supposed to include its client-id
    // option almost all the time (the only exception is an anonymous inf-request,
    // but that is mostly a theoretical case). Our allocation engine needs DUID
    // and will refuse to allocate anything to anonymous clients.
    OptionPtr opt_duid = renew->getOption(D6O_CLIENTID);
    if (!opt_duid) {
        // This should not happen. We have checked this before.
        reply->addOption(createStatusCode(STATUS_UnspecFail,
                         "You did not include mandatory client-id"));
        return;
    }
    DuidPtr duid(new DUID(opt_duid->getData()));

    for (Option::OptionCollection::iterator opt = renew->options_.begin();
         opt != renew->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = renewIA_NA(subnet, duid, renew,
                                   boost::dynamic_pointer_cast<Option6IA>(opt->second));
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
Dhcpv6Srv::releaseLeases(const Pkt6Ptr& release, Pkt6Ptr& reply) {

    // We need to release addresses for all IA_NA options in the client's
    // RELEASE message.
    // @todo Add support for IA_TA
    // @todo Add support for IA_PD
    // @todo Consider supporting more than one address in a single IA_NA.
    // That was envisaged by RFC3315, but it never happened. The only
    // software that supports that is Dibbler, but its author seriously doubts
    // if anyone is really using it. Clients that want more than one address
    // just include more instances of IA_NA options.

    // Let's find client's DUID. Client is supposed to include its client-id
    // option almost all the time (the only exception is an anonymous inf-request,
    // but that is mostly a theoretical case). Our allocation engine needs DUID
    // and will refuse to allocate anything to anonymous clients.
    OptionPtr opt_duid = release->getOption(D6O_CLIENTID);
    if (!opt_duid) {
        // This should not happen. We have checked this before.
        // see sanityCheck() called from processRelease()
        LOG_WARN(dhcp6_logger, DHCP6_RELEASE_MISSING_CLIENTID)
            .arg(release->getRemoteAddr().toText());

        reply->addOption(createStatusCode(STATUS_UnspecFail,
                         "You did not include mandatory client-id"));
        return;
    }
    DuidPtr duid(new DUID(opt_duid->getData()));

    int general_status = STATUS_Success;
    for (Option::OptionCollection::iterator opt = release->options_.begin();
         opt != release->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = releaseIA_NA(duid, release, general_status,
                                   boost::dynamic_pointer_cast<Option6IA>(opt->second));
            if (answer_opt) {
                reply->addOption(answer_opt);
            }
            break;
        }
        // @todo: add support for IA_PD
        // @todo: add support for IA_TA
        default:
            // remaining options are stateless and thus ignored in this context
            ;
        }
    }

    // To be pedantic, we should also include status code in the top-level
    // scope, not just in each IA_NA. See RFC3315, section 18.2.6.
    // This behavior will likely go away in RFC3315bis.
    reply->addOption(createStatusCode(general_status,
                     "Summary status for all processed IA_NAs"));
}

OptionPtr
Dhcpv6Srv::releaseIA_NA(const DuidPtr& duid, const Pkt6Ptr& query,
                        int& general_status, boost::shared_ptr<Option6IA> ia) {
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

    boost::shared_ptr<Option6IAAddr> release_addr = boost::dynamic_pointer_cast<Option6IAAddr>
        (ia->getOption(D6O_IAADDR));
    if (!release_addr) {
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                                           "You did not include address in your RELEASE"));
        general_status = STATUS_NoBinding;
        return (ia_rsp);
    }

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(release_addr->getAddress());

    if (!lease) {
        // client releasing a lease that we don't know about.

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid, can't release."));
        general_status = STATUS_NoBinding;

        LOG_INFO(dhcp6_logger, DHCP6_UNKNOWN_RELEASE)
            .arg(duid->toText())
            .arg(ia->getIAID());

        return (ia_rsp);
    }

    if (!lease->duid_) {
        // Something is gravely wrong here. We do have a lease, but it does not
        // have mandatory DUID information attached. Someone was messing with our
        // database.

        LOG_ERROR(dhcp6_logger, DHCP6_LEASE_WITHOUT_DUID)
            .arg(release_addr->getAddress().toText());

        general_status = STATUS_UnspecFail;
        ia_rsp->addOption(createStatusCode(STATUS_UnspecFail,
                          "Database consistency check failed when trying to RELEASE"));
        return (ia_rsp);
    }

    if (*duid != *(lease->duid_)) {
        // Sorry, it's not your address. You can't release it.

        LOG_INFO(dhcp6_logger, DHCP6_RELEASE_FAIL_WRONG_DUID)
            .arg(duid->toText())
            .arg(release_addr->getAddress().toText())
            .arg(lease->duid_->toText());

        general_status = STATUS_NoBinding;
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "This address does not belong to you, you can't release it"));
        return (ia_rsp);
    }

    if (ia->getIAID() != lease->iaid_) {
        // This address belongs to this client, but to a different IA
        LOG_WARN(dhcp6_logger, DHCP6_RELEASE_FAIL_WRONG_IAID)
            .arg(duid->toText())
            .arg(release_addr->getAddress().toText())
            .arg(lease->iaid_)
            .arg(ia->getIAID());
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "This is your address, but you used wrong IAID"));
        general_status = STATUS_NoBinding;
        return (ia_rsp);
    }

    // It is not necessary to check if the address matches as we used
    // getLease6(addr) method that is supposed to return a proper lease.

    bool skip = false;
    // Execute all callouts registered for packet6_send
    if (HooksManager::getHooksManager().calloutsPresent(Hooks.hook_index_lease6_release_)) {
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
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_LEASE6_RELEASE_SKIP);
        }
    }

    // Ok, we've passed all checks. Let's release this address.
    bool success = false; // was the removal operation succeessful?

    if (!skip) {
        success = LeaseMgrFactory::instance().deleteLease(lease->addr_);
    }

    // Here the success should be true if we removed lease successfully
    // and false if skip flag was set or the removal failed for whatever reason

    if (!success) {
        ia_rsp->addOption(createStatusCode(STATUS_UnspecFail,
                          "Server failed to release a lease"));

        LOG_ERROR(dhcp6_logger, DHCP6_RELEASE_FAIL)
            .arg(lease->addr_.toText())
            .arg(duid->toText())
            .arg(lease->iaid_);
        general_status = STATUS_UnspecFail;

        return (ia_rsp);
    } else {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_RELEASE)
            .arg(lease->addr_.toText())
            .arg(duid->toText())
            .arg(lease->iaid_);

        ia_rsp->addOption(createStatusCode(STATUS_Success,
                          "Lease released. Thank you, please come again."));

        return (ia_rsp);
    }
}

Pkt6Ptr
Dhcpv6Srv::processSolicit(const Pkt6Ptr& solicit) {

    sanityCheck(solicit, MANDATORY, FORBIDDEN);

    Pkt6Ptr advertise(new Pkt6(DHCPV6_ADVERTISE, solicit->getTransid()));

    copyDefaultOptions(solicit, advertise);
    appendDefaultOptions(solicit, advertise);
    appendRequestedOptions(solicit, advertise);

    assignLeases(solicit, advertise);

    return (advertise);
}

Pkt6Ptr
Dhcpv6Srv::processRequest(const Pkt6Ptr& request) {

    sanityCheck(request, MANDATORY, MANDATORY);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, request->getTransid()));

    copyDefaultOptions(request, reply);
    appendDefaultOptions(request, reply);
    appendRequestedOptions(request, reply);

    assignLeases(request, reply);

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processRenew(const Pkt6Ptr& renew) {

    sanityCheck(renew, MANDATORY, MANDATORY);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, renew->getTransid()));

    copyDefaultOptions(renew, reply);
    appendDefaultOptions(renew, reply);
    appendRequestedOptions(renew, reply);

    renewLeases(renew, reply);

    return reply;
}

Pkt6Ptr
Dhcpv6Srv::processRebind(const Pkt6Ptr& rebind) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, rebind->getTransid()));
    return reply;
}

Pkt6Ptr
Dhcpv6Srv::processConfirm(const Pkt6Ptr& confirm) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, confirm->getTransid()));
    return reply;
}

Pkt6Ptr
Dhcpv6Srv::processRelease(const Pkt6Ptr& release) {

    sanityCheck(release, MANDATORY, MANDATORY);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, release->getTransid()));

    copyDefaultOptions(release, reply);
    appendDefaultOptions(release, reply);

    releaseLeases(release, reply);

    return reply;
}

Pkt6Ptr
Dhcpv6Srv::processDecline(const Pkt6Ptr& decline) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, decline->getTransid()));
    return reply;
}

Pkt6Ptr
Dhcpv6Srv::processInfRequest(const Pkt6Ptr& infRequest) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, infRequest->getTransid()));
    return reply;
}

isc::hooks::CalloutHandlePtr Dhcpv6Srv::getCalloutHandle(const Pkt6Ptr& pkt) {
    // This method returns a CalloutHandle for a given packet. It is guaranteed
    // to return the same callout_handle (so user library contexts are
    // preserved). This method works well if the server processes one packet
    // at a time. Once the server architecture is extended to cover parallel
    // packets processing (e.g. delayed-ack, some form of buffering etc.), this
    // method has to be extended (e.g. store callouts in a map and use pkt as
    // a key). Additional code would be required to release the callout handle
    // once the server finished processing.

    CalloutHandlePtr callout_handle;
    static Pkt6Ptr old_pointer;

    if (!callout_handle ||
        old_pointer != pkt) {
        // This is the first packet or a different packet than previously
        // passed to getCalloutHandle()

        // Remember the pointer to this packet
        old_pointer = pkt;

        callout_handle = HooksManager::getHooksManager().createCalloutHandle();
    }

    return (callout_handle);
}

void
Dhcpv6Srv::openActiveSockets(const uint16_t port) {
    IfaceMgr::instance().closeSockets();

    // Get the reference to the collection of interfaces. This reference should be
    // valid as long as the program is run because IfaceMgr is a singleton.
    // Therefore we can safely iterate over instances of all interfaces and modify
    // their flags. Here we modify flags which indicate wheter socket should be
    // open for a particular interface or not.
    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();
    for (IfaceMgr::IfaceCollection::const_iterator iface = ifaces.begin();
         iface != ifaces.end(); ++iface) {
        Iface* iface_ptr = IfaceMgr::instance().getIface(iface->getName());
        if (iface_ptr == NULL) {
            isc_throw(isc::Unexpected, "Interface Manager returned NULL"
                      << " instance of the interface when DHCPv6 server was"
                      << " trying to reopen sockets after reconfiguration");
        }
        if (CfgMgr::instance().isActiveIface(iface->getName())) {
            iface_ptr->inactive4_ = false;
            LOG_INFO(dhcp6_logger, DHCP6_ACTIVATE_INTERFACE)
                .arg(iface->getFullName());

        } else {
            // For deactivating interface, it should be sufficient to log it
            // on the debug level because it is more useful to know what
            // interface is activated which is logged on the info level.
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC,
                      DHCP6_DEACTIVATE_INTERFACE).arg(iface->getName());
            iface_ptr->inactive6_ = true;

        }
    }
    // Let's reopen active sockets. openSockets6 will check internally whether
    // sockets are marked active or inactive.
    // @todo Optimization: we should not reopen all sockets but rather select
    // those that have been affected by the new configuration.
    if (!IfaceMgr::instance().openSockets6(port)) {
        LOG_WARN(dhcp6_logger, DHCP6_NO_SOCKETS_OPEN);
    }
}

};
};
