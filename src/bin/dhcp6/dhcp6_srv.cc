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
#include <dhcp/option_custom.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt6.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcpsrv/callout_handle_store.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/utils.h>
#include <exceptions/exceptions.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>
#include <util/encode/hex.h>
#include <util/io_utilities.h>
#include <util/range_utilities.h>

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/erase.hpp>

#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <fstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp_ddns;
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

namespace {

// The following constants describe server's behavior with respect to the
// DHCPv6 Client FQDN Option sent by a client. They will be removed
// when DDNS parameters for DHCPv6 are implemented with the ticket #3034.

// Should server always include the FQDN option in its response, regardless
// if it has been requested in ORO (Disabled).
const bool FQDN_ALWAYS_INCLUDE = false;
// Enable AAAA RR update delegation to the client (Disabled).
const bool FQDN_ALLOW_CLIENT_UPDATE = false;
// Globally enable updates (Enabled).
const bool FQDN_ENABLE_UPDATE = true;
// The partial name generated for the client if empty name has been
// supplied.
const char* FQDN_GENERATED_PARTIAL_NAME = "myhost";
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
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_PACKET_RCVD_SKIP);
                continue;
            }

            callout_handle->getArgument("query6", query);
        }

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

            // Send NameChangeRequests to the b10-dhcp_ddns module.
            sendNameChangeRequests();
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

void
Dhcpv6Srv::appendRequestedVendorOptions(const Pkt6Ptr& question, Pkt6Ptr& answer) {
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

    // Try to get the vendor option
    boost::shared_ptr<OptionVendor> vendor_req =
        boost::dynamic_pointer_cast<OptionVendor>(question->getOption(D6O_VENDOR_OPTS));
    if (!vendor_req) {
        return;
    }

    uint32_t vendor_id = vendor_req->getVendorId();

    // Let's try to get ORO within that vendor-option
    /// @todo This is very specific to vendor-id=4491 (Cable Labs). Other vendors
    /// may have different policies.
    boost::shared_ptr<OptionUint16Array> oro =
        boost::dynamic_pointer_cast<OptionUint16Array>(vendor_req->getOption(DOCSIS3_V6_ORO));

    // Option ORO not found. Don't do anything then.
    if (!oro) {
        return;
    }

    boost::shared_ptr<OptionVendor> vendor_rsp(new OptionVendor(Option::V6, vendor_id));

    // Get the list of options that client requested.
    bool added = false;
    const std::vector<uint16_t>& requested_opts = oro->getValues();
    BOOST_FOREACH(uint16_t opt, requested_opts) {
        Subnet::OptionDescriptor desc = subnet->getVendorOptionDescriptor(vendor_id, opt);
        if (desc.option) {
            vendor_rsp->addOption(desc.option);
            added = true;
        }
    }

    if (added) {
        answer->addOption(vendor_rsp);
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
Dhcpv6Srv::assignLeases(const Pkt6Ptr& question, Pkt6Ptr& answer,
                        const Option6ClientFqdnPtr& fqdn) {

    // We need to allocate addresses for all IA_NA options in the client's
    // question (i.e. SOLICIT or REQUEST) message.
    // @todo add support for IA_TA

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
    for (OptionCollection::iterator opt = question->options_.begin();
         opt != question->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = assignIA_NA(subnet, duid, question,
                                               boost::dynamic_pointer_cast<
                                               Option6IA>(opt->second),
                                               fqdn);
            if (answer_opt) {
                answer->addOption(answer_opt);
            }
            break;
        }
        case D6O_IA_PD: {
            OptionPtr answer_opt = assignIA_PD(subnet, duid, question,
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

Option6ClientFqdnPtr
Dhcpv6Srv::processClientFqdn(const Pkt6Ptr& question) {
    // Get Client FQDN Option from the client's message. If this option hasn't
    // been included, do nothing.
    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option6ClientFqdn>(question->getOption(D6O_CLIENT_FQDN));
    if (!fqdn) {
        return (fqdn);
    }

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL,
              DHCP6_DDNS_RECEIVE_FQDN).arg(fqdn->toText());


    // Prepare the FQDN option which will be included in the response to
    // the client.
    Option6ClientFqdnPtr fqdn_resp(new Option6ClientFqdn(*fqdn));
    // RFC 4704, section 6. - all flags set to 0.
    fqdn_resp->resetFlags();

    // Conditions when N flag has to be set to indicate that server will not
    // perform DNS updates:
    // 1. Updates are globally disabled,
    // 2. Client requested no update and server respects it,
    // 3. Client requested that the AAAA update is delegated to the client but
    //    server neither respects delegation of updates nor it is configured
    //    to send update on its own when client requested delegation.
    if (!FQDN_ENABLE_UPDATE ||
        (fqdn->getFlag(Option6ClientFqdn::FLAG_N) &&
         !FQDN_OVERRIDE_NO_UPDATE) ||
        (!fqdn->getFlag(Option6ClientFqdn::FLAG_S) &&
         !FQDN_ALLOW_CLIENT_UPDATE && !FQDN_OVERRIDE_CLIENT_UPDATE)) {
        fqdn_resp->setFlag(Option6ClientFqdn::FLAG_N, true);

    // Conditions when S flag is set to indicate that server will perform
    // DNS update on its own:
    // 1. Client requested that server performs DNS update and DNS updates are
    //    globally enabled
    // 2. Client requested that server delegates AAAA update to the client but
    //    server doesn't respect delegation and it is configured to perform
    //    an update on its own when client requested delegation.
    } else if (fqdn->getFlag(Option6ClientFqdn::FLAG_S) ||
               (!fqdn->getFlag(Option6ClientFqdn::FLAG_S) &&
                !FQDN_ALLOW_CLIENT_UPDATE && FQDN_OVERRIDE_CLIENT_UPDATE)) {
        fqdn_resp->setFlag(Option6ClientFqdn::FLAG_S, true);
    }

    // Server MUST set the O flag if it has overridden the client's setting
    // of S flag.
    if (fqdn->getFlag(Option6ClientFqdn::FLAG_S) !=
        fqdn_resp->getFlag(Option6ClientFqdn::FLAG_S)) {
        fqdn_resp->setFlag(Option6ClientFqdn::FLAG_O, true);
    }

    // If client supplied partial or empty domain-name, server should
    // generate one.
    if (fqdn->getDomainNameType() == Option6ClientFqdn::PARTIAL) {
        std::ostringstream name;
        if (fqdn->getDomainName().empty()) {
            name << FQDN_GENERATED_PARTIAL_NAME;
        } else {
            name << fqdn->getDomainName();
        }
        name << "." << FQDN_PARTIAL_SUFFIX;
        fqdn_resp->setDomainName(name.str(), Option6ClientFqdn::FULL);

    // Server may be configured to replace a name supplied by a client,
    // even if client supplied fully qualified domain-name.
    } else if (FQDN_REPLACE_CLIENT_NAME) {
        std::ostringstream name;
        name << FQDN_GENERATED_PARTIAL_NAME << "." << FQDN_PARTIAL_SUFFIX;
        fqdn_resp->setDomainName(name.str(), Option6ClientFqdn::FULL);

    }

    // Return the FQDN option which can be included in the server's response.
    // Note that it doesn't have to be included, if client didn't request
    // it using ORO and server is not configured to always include it.
    return (fqdn_resp);
}


void
Dhcpv6Srv::appendClientFqdn(const Pkt6Ptr& question,
                            Pkt6Ptr& answer,
                            const Option6ClientFqdnPtr& fqdn) {

    // If FQDN is NULL, it means that client did not request DNS Update, plus
    // server doesn't force updates.
    if (fqdn) {
        return;
    }

    // Server sends back the FQDN option to the client if client has requested
    // it using Option Request Option. However, server may be configured to
    // send the FQDN option in its response, regardless whether client requested
    // it or not.
    bool include_fqdn = FQDN_ALWAYS_INCLUDE;
    if (!include_fqdn) {
        OptionUint16ArrayPtr oro = boost::dynamic_pointer_cast<
            OptionUint16Array>(question->getOption(D6O_ORO));
        if (oro) {
            const std::vector<uint16_t>& values = oro->getValues();
            for (int i = 0; i < values.size(); ++i) {
                if (values[i] == D6O_CLIENT_FQDN) {
                    include_fqdn = true;
                }
            }
        }
    }

    if (include_fqdn) {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL,
                  DHCP6_DDNS_SEND_FQDN).arg(fqdn->toText());
        answer->addOption(fqdn);
    }

}

void
Dhcpv6Srv::createNameChangeRequests(const Pkt6Ptr& answer,
                                    const Option6ClientFqdnPtr& opt_fqdn) {

    // It is likely that client haven't included the FQDN option in the message
    // and server is not configured to always update DNS. In such cases,
    // FQDN option will be NULL. This is valid state, so we simply return.
    if (!opt_fqdn) {
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

    // Get the Client Id. It is mandatory and a function creating a response
    // would have thrown an exception if it was missing. Thus throwning
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
        // @todo IA_NA may contain multiple addresses. We should process
        // each address individually. Currently we get only one.
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
        // Get the IP address from the lease. Also, use the S flag to determine
        // if forward change should be performed. This flag will always be
        // set if server has taken responsibility for the forward update.
        NameChangeRequest ncr(isc::dhcp_ddns::CHG_ADD,
                              opt_fqdn->getFlag(Option6ClientFqdn::FLAG_S),
                              true, opt_fqdn->getDomainName(),
                              iaaddr->getAddress().toText(),
                              dhcid, 0, iaaddr->getValid());
        // Add the request to the queue. This queue will be read elsewhere in
        // the code and all requests from this queue will be sent to the
        // D2 module.
        name_change_reqs_.push(ncr);

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL,
                  DHCP6_DDNS_CREATE_ADD_NAME_CHANGE_REQUEST).arg(ncr.toText());
    }
}

void
Dhcpv6Srv::createRemovalNameChangeRequest(const Lease6Ptr& lease) {
    // If we haven't performed a DNS Update when lease was acquired,
    // there is nothing to do here.
    if (!lease->fqdn_fwd_ && !lease->fqdn_rev_) {
        return;
    }

    // When lease was added into a database the host name should have
    // been added. The hostname can be empty if someone messed up in the
    // lease data base and removed the hostname.
    if (lease->hostname_.empty()) {
        LOG_ERROR(dhcp6_logger, DHCP6_DDNS_REMOVE_EMPTY_HOSTNAME)
            .arg(lease->addr_.toText());
        return;
    }

    // If hostname is non-empty, try to convert it to wire format so as
    // DHCID can be computed from it. This may throw an exception if hostname
    // has invalid format. Again, this should be only possible in case of
    // manual intervention in the database. Note that the last parameter
    // passed to the writeFqdn function forces conversion of the FQDN
    // to lower case. This is required by the RFC4701, section 3.5.
    // The DHCID computation is further in this function.
    std::vector<uint8_t> hostname_wire;
    try {
        OptionDataTypeUtil::writeFqdn(lease->hostname_, hostname_wire, true);
    } catch (const Exception& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_DDNS_REMOVE_INVALID_HOSTNAME)
            .arg(lease->hostname_);
        return;
    }

    // DUID must have been checked already  by the caller of this function.
    // Let's be on the safe side and make sure it is non-NULL and throw
    // an exception if it is NULL.
    if (!lease->duid_) {
        isc_throw(isc::Unexpected, "DUID must be set when creating"
                  << " NameChangeRequest for DNS records removal for "
                  << lease->addr_.toText());

    }
    isc::dhcp_ddns::D2Dhcid dhcid(*lease->duid_, hostname_wire);

    // Create a NameChangeRequest to remove the entry.
    NameChangeRequest ncr(isc::dhcp_ddns::CHG_REMOVE,
                          lease->fqdn_fwd_, lease->fqdn_rev_,
                          lease->hostname_,
                          lease->addr_.toText(),
                          dhcid, 0, lease->valid_lft_);
    name_change_reqs_.push(ncr);

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL,
              DHCP6_DDNS_CREATE_REMOVE_NAME_CHANGE_REQUEST).arg(ncr.toText());

}

void
Dhcpv6Srv::sendNameChangeRequests() {
    while (!name_change_reqs_.empty()) {
        // @todo Once next NameChangeRequest is picked from the queue
        // we should send it to the bind10-dhcp_ddns module. Currently we
        // just drop it.
        name_change_reqs_.pop();
    }
}


OptionPtr
Dhcpv6Srv::assignIA_NA(const Subnet6Ptr& subnet, const DuidPtr& duid,
                       const Pkt6Ptr& query, boost::shared_ptr<Option6IA> ia,
                       const Option6ClientFqdnPtr& fqdn) {
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
    if (query->getType() == DHCPV6_SOLICIT) {
        /// @todo: Check if we support rapid commit
        fake_allocation = true;
    }

    CalloutHandlePtr callout_handle = getCalloutHandle(query);

    // At this point, we have to make make some decisions with respect to the
    // FQDN option that we have generated as a result of receiving client's
    // FQDN. In particular, we have to get to know if the DNS update will be
    // performed or not. It is possible that option is NULL, which is valid
    // condition if client didn't request DNS updates and server didn't force
    // the update.
    bool do_fwd = false;
    bool do_rev = false;
    if (fqdn) {
        // Flag S must not coexist with flag N being set to 1, so if S=1
        // server takes responsibility for both reverse and forward updates.
        // Otherwise, we have to check N.
        if (fqdn->getFlag(Option6ClientFqdn::FLAG_S)) {
            do_fwd = true;
            do_rev = true;
        } else if (!fqdn->getFlag(Option6ClientFqdn::FLAG_N)) {
            do_rev = true;
        }
    }
    // Set hostname only in case any of the updates is being performed.
    std::string hostname;
    if (do_fwd || do_rev) {
        hostname = fqdn->getDomainName();
    }

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honour the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    Lease6Collection leases = alloc_engine_->allocateLeases6(subnet, duid,
                                                             ia->getIAID(),
                                                             hint, Lease::TYPE_NA,
                                                             do_fwd, do_rev,
                                                             hostname,
                                                             fake_allocation,
                                                             callout_handle);
    /// @todo: Handle more than one lease
    Lease6Ptr lease;
    if (!leases.empty()) {
        lease = *leases.begin();
    }

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

        // Allocation engine may have returned an existing lease. If so, we
        // have to check that the FQDN settings we provided are the same
        // that were set. If they aren't, we will have to remove existing
        // DNS records and update the lease with the new settings.
        if ((lease->hostname_ != hostname) || (lease->fqdn_fwd_ != do_fwd) ||
            (lease->fqdn_rev_ != do_rev)) {
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL,
                      DHCP6_DDNS_LEASE_ASSIGN_FQDN_CHANGE)
                .arg(lease->toText())
                .arg(hostname)
                .arg(do_rev ? "true" : "false")
                .arg(do_fwd ? "true" : "false");

            // Schedule removal of the existing lease.
            createRemovalNameChangeRequest(lease);
            // Set the new lease properties and update.
            lease->hostname_ = hostname;
            lease->fqdn_fwd_ = do_fwd;
            lease->fqdn_rev_ = do_rev;
            LeaseMgrFactory::instance().updateLease6(lease);
        }

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
Dhcpv6Srv::assignIA_PD(const Subnet6Ptr& subnet, const DuidPtr& duid,
                       const Pkt6Ptr& query, boost::shared_ptr<Option6IA> ia) {

    // Create IA_PD that we will put in the response.
    // Do not use OptionDefinition to create option's instance so
    // as we can initialize IAID using a constructor.
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_PD, ia->getIAID()));

    // If there is no subnet selected for handling this IA_PD, the only thing to
    // do left is to say that we are sorry, but the user won't get an address.
    // As a convenience, we use a different status text to indicate that
    // (compare to the same status code, but different wording below)
    if (!subnet) {

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(STATUS_NoPrefixAvail,
                                           "Sorry, no subnet available."));
        return (ia_rsp);
    }

    // Check if the client sent us a hint in his IA_PD. Clients may send an
    // address in their IA_NA options as a suggestion (e.g. the last address
    // they used before).
    boost::shared_ptr<Option6IAPrefix> hintOpt =
      boost::dynamic_pointer_cast<Option6IAPrefix>(ia->getOption(D6O_IAPREFIX));
    IOAddress hint("::");
    if (hintOpt) {
        hint = hintOpt->getAddress();
    }

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_PD_REQUEST)
        .arg(duid ? duid->toText() : "(no-duid)").arg(ia->getIAID())
        .arg(hintOpt ? hint.toText() : "(no hint)");

    // "Fake" allocation is processing of SOLICIT message. We pretend to do an
    // allocation, but we do not put the lease in the database. That is ok,
    // because we do not guarantee that the user will get that exact lease. If
    // the user selects this server to do actual allocation (i.e. sends REQUEST)
    // it should include this hint. That will help us during the actual lease
    // allocation.
    bool fake_allocation = (query->getType() == DHCPV6_SOLICIT);

    CalloutHandlePtr callout_handle = getCalloutHandle(query);

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honour the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    Lease6Collection leases = alloc_engine_->allocateLeases6(subnet, duid,
                                                            ia->getIAID(),
                                                            hint, Lease::TYPE_PD,
                                                            false, false,
                                                            string(),
                                                            fake_allocation,
                                                            callout_handle);

    if (!leases.empty()) {

        ia_rsp->setT1(subnet->getT1());
        ia_rsp->setT2(subnet->getT2());

        for (Lease6Collection::iterator l = leases.begin();
             l != leases.end(); ++l) {

            // We have a lease! Let's wrap its content into IA_PD option
            // with IAADDR suboption.
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, fake_allocation ?
                      DHCP6_PD_LEASE_ADVERT : DHCP6_PD_LEASE_ALLOC)
                .arg((*l)->addr_.toText())
                .arg(static_cast<int>((*l)->prefixlen_))
                .arg(duid ? duid->toText() : "(no-duid)")
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

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, fake_allocation ?
                  DHCP6_PD_LEASE_ADVERT_FAIL : DHCP6_PD_LEASE_ALLOC_FAIL)
            .arg(duid ? duid->toText() : "(no-duid)")
            .arg(ia->getIAID());

        ia_rsp->addOption(createStatusCode(STATUS_NoPrefixAvail,
                          "Sorry, no prefixes could be allocated."));
    }
    return (ia_rsp);
}

OptionPtr
Dhcpv6Srv::renewIA_NA(const Subnet6Ptr& subnet, const DuidPtr& duid,
                      const Pkt6Ptr& query, boost::shared_ptr<Option6IA> ia,
                      const Option6ClientFqdnPtr& fqdn) {
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

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                            *duid, ia->getIAID(),
                                                            subnet->getID());

    if (!lease) {
        // client renewing a lease that we don't know about.

        // Create empty IA_NA option with IAID matching the request.
        boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid."));

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_UNKNOWN_RENEW_NA)
            .arg(duid->toText())
            .arg(ia->getIAID())
            .arg(subnet->toText());

        return (ia_rsp);
    }

    // Keep the old data in case the callout tells us to skip update
    Lease6 old_data = *lease;

    // At this point, we have to make make some decisions with respect to the
    // FQDN option that we have generated as a result of receiving client's
    // FQDN. In particular, we have to get to know if the DNS update will be
    // performed or not. It is possible that option is NULL, which is valid
    // condition if client didn't request DNS updates and server didn't force
    // the update.
    bool do_fwd = false;
    bool do_rev = false;
    if (fqdn) {
        if (fqdn->getFlag(Option6ClientFqdn::FLAG_S)) {
            do_fwd = true;
            do_rev = true;
        } else if (!fqdn->getFlag(Option6ClientFqdn::FLAG_N)) {
            do_rev = true;
        }
    }

    std::string hostname;
    if (do_fwd || do_rev) {
        hostname = fqdn->getDomainName();
    }

    // If the new FQDN settings have changed for the lease, we need to
    // delete any existing FQDN records for this lease.
    if ((lease->hostname_ != hostname) || (lease->fqdn_fwd_ != do_fwd) ||
        (lease->fqdn_rev_ != do_rev)) {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL,
                  DHCP6_DDNS_LEASE_RENEW_FQDN_CHANGE)
            .arg(lease->toText())
            .arg(hostname)
            .arg(do_rev ? "true" : "false")
            .arg(do_fwd ? "true" : "false");

        createRemovalNameChangeRequest(lease);
    }

    lease->preferred_lft_ = subnet->getPreferred();
    lease->valid_lft_ = subnet->getValid();
    lease->t1_ = subnet->getT1();
    lease->t2_ = subnet->getT2();
    lease->cltt_ = time(NULL);
    lease->hostname_ = hostname;
    lease->fqdn_fwd_ = do_fwd;
    lease->fqdn_rev_ = do_rev;

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
    if (HooksManager::calloutsPresent(Hooks.hook_index_lease6_renew_)) {
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

OptionPtr
Dhcpv6Srv::renewIA_PD(const Subnet6Ptr& subnet, const DuidPtr& duid,
                      const Pkt6Ptr& query, boost::shared_ptr<Option6IA> ia) {

    // Let's create a IA_NA response and fill it in later
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_PD, ia->getIAID()));

    if (!subnet) {
        // Insert status code NoBinding
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid."));

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_RENEW_UNKNOWN_SUBNET)
            .arg(duid->toText())
            .arg(ia->getIAID());

        return (ia_rsp);
    }

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD,
                                                            *duid, ia->getIAID(),
                                                            subnet->getID());

    if (!lease) {
        // Client is renewing a lease that we don't know about.

        // Insert status code NoBinding
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid."));

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_UNKNOWN_RENEW_PD)
            .arg(duid->toText())
            .arg(ia->getIAID())
            .arg(subnet->toText());

        return (ia_rsp);
    }

    // Keep the old data in case the callout tells us to skip update.
    Lease6 old_data = *lease;

    // Do the actual lease update
    lease->preferred_lft_ = subnet->getPreferred();
    lease->valid_lft_ = subnet->getValid();
    lease->t1_ = subnet->getT1();
    lease->t2_ = subnet->getT2();
    lease->cltt_ = time(NULL);

    // Also update IA_PD container with proper T1, T2 values
    ia_rsp->setT1(subnet->getT1());
    ia_rsp->setT2(subnet->getT2());

    boost::shared_ptr<Option6IAPrefix>
        prefix(new Option6IAPrefix(D6O_IAPREFIX, lease->addr_,
                                   lease->prefixlen_, lease->preferred_lft_,
                                   lease->valid_lft_));
    ia_rsp->addOption(prefix);

    bool skip = false;
    // Execute all callouts registered for packet6_send
    if (HooksManager::calloutsPresent(Hooks.hook_index_lease6_renew_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Delete all previous arguments
        callout_handle->deleteAllArguments();

        // Pass the original packet
        callout_handle->setArgument("query6", query);

        // Pass the lease to be updated
        callout_handle->setArgument("lease6", lease);

        // Pass the IA option to be sent in response
        callout_handle->setArgument("ia_pd", ia_rsp);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_lease6_renew_,
                                   *callout_handle);

        // Remember hook's instruction whether we want to skip update or not
        skip = callout_handle->getSkip();
    }

    if (!skip) {
        LeaseMgrFactory::instance().updateLease6(lease);
    } else {
        // Callouts decided to skip the next processing step. The next
        // processing step would to actually renew the lease, so skip at this
        // stage means "keep the old lease as it is".
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_LEASE6_RENEW_SKIP);

        // Copy back the original date to the lease. For MySQL it doesn't make
        // much sense, but for memfile, the Lease6Ptr points to the actual lease
        // in memfile, so the actual update is performed when we manipulate
        // fields of returned Lease6Ptr, the actual updateLease6() is no-op.
        *lease = old_data;
    }

    return (ia_rsp);
}

void
Dhcpv6Srv::renewLeases(const Pkt6Ptr& renew, Pkt6Ptr& reply,
                       const Option6ClientFqdnPtr& fqdn) {

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

    for (OptionCollection::iterator opt = renew->options_.begin();
         opt != renew->options_.end(); ++opt) {
        switch (opt->second->getType()) {

        case D6O_IA_NA: {
            OptionPtr answer_opt = renewIA_NA(subnet, duid, renew,
                                              boost::dynamic_pointer_cast<
                                              Option6IA>(opt->second),
                                              fqdn);
            if (answer_opt) {
                reply->addOption(answer_opt);
            }
            break;
        }

        case D6O_IA_PD: {
            OptionPtr answer_opt = renewIA_PD(subnet, duid, renew,
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
            OptionPtr answer_opt = releaseIA_NA(duid, release, general_status,
                                   boost::dynamic_pointer_cast<Option6IA>(opt->second));
            if (answer_opt) {
                reply->addOption(answer_opt);
            }
            break;
        }
        case D6O_IA_PD: {
            OptionPtr answer_opt = releaseIA_PD(duid, release, general_status,
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
                                           "You did not include an address in your RELEASE"));
        general_status = STATUS_NoBinding;
        return (ia_rsp);
    }

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                            release_addr->getAddress());

    if (!lease) {
        // client releasing a lease that we don't know about.

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid, can't release."));
        general_status = STATUS_NoBinding;

        LOG_INFO(dhcp6_logger, DHCP6_UNKNOWN_RELEASE_NA)
            .arg(duid->toText())
            .arg(ia->getIAID());

        return (ia_rsp);
    }

    if (!lease->duid_) {
        // Something is gravely wrong here. We do have a lease, but it does not
        // have mandatory DUID information attached. Someone was messing with our
        // database.

        LOG_ERROR(dhcp6_logger, DHCP6_LEASE_NA_WITHOUT_DUID)
            .arg(release_addr->getAddress().toText());

        general_status = STATUS_UnspecFail;
        ia_rsp->addOption(createStatusCode(STATUS_UnspecFail,
                          "Database consistency check failed when trying to RELEASE"));
        return (ia_rsp);
    }

    if (*duid != *(lease->duid_)) {

        // Sorry, it's not your address. You can't release it.
        LOG_INFO(dhcp6_logger, DHCP6_RELEASE_NA_FAIL_WRONG_DUID)
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
        LOG_WARN(dhcp6_logger, DHCP6_RELEASE_PD_FAIL_WRONG_IAID)
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
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_LEASE6_RELEASE_NA_SKIP);
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

        LOG_ERROR(dhcp6_logger, DHCP6_RELEASE_NA_FAIL)
            .arg(lease->addr_.toText())
            .arg(duid->toText())
            .arg(lease->iaid_);
        general_status = STATUS_UnspecFail;

        return (ia_rsp);
    } else {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_RELEASE_NA)
            .arg(lease->addr_.toText())
            .arg(duid->toText())
            .arg(lease->iaid_);

        ia_rsp->addOption(createStatusCode(STATUS_Success,
                          "Lease released. Thank you, please come again."));

        // Check if a lease has flags indicating that the FQDN update has
        // been performed. If so, create NameChangeRequest which removes
        // the entries.
        createRemovalNameChangeRequest(lease);

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
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "You did not include a prefix in your RELEASE"));
        general_status = STATUS_NoBinding;
        return (ia_rsp);
    }

    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD,
                                                            release_prefix->getAddress());

    if (!lease) {
        // Client releasing a lease that we don't know about.

        // Insert status code NoBinding.
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "Sorry, no known leases for this duid/iaid, can't release."));
        general_status = STATUS_NoBinding;

        LOG_INFO(dhcp6_logger, DHCP6_UNKNOWN_RELEASE_PD)
            .arg(duid->toText())
            .arg(ia->getIAID());

        return (ia_rsp);
    }

    if (!lease->duid_) {
        // Something is gravely wrong here. We do have a lease, but it does not
        // have mandatory DUID information attached. Someone was messing with our
        // database.
        LOG_ERROR(dhcp6_logger, DHCP6_LEASE_PD_WITHOUT_DUID)
            .arg(release_prefix->getAddress().toText());

        general_status = STATUS_UnspecFail;
        ia_rsp->addOption(createStatusCode(STATUS_UnspecFail,
                          "Database consistency check failed when trying to RELEASE"));
        return (ia_rsp);
    }

    if (*duid != *(lease->duid_)) {
        // Sorry, it's not your address. You can't release it.
        LOG_INFO(dhcp6_logger, DHCP6_RELEASE_PD_FAIL_WRONG_DUID)
            .arg(duid->toText())
            .arg(release_prefix->getAddress().toText())
            .arg(lease->duid_->toText());

        general_status = STATUS_NoBinding;
        ia_rsp->addOption(createStatusCode(STATUS_NoBinding,
                          "This address does not belong to you, you can't release it"));
        return (ia_rsp);
    }

    if (ia->getIAID() != lease->iaid_) {
        // This address belongs to this client, but to a different IA
        LOG_WARN(dhcp6_logger, DHCP6_RELEASE_PD_FAIL_WRONG_IAID)
            .arg(duid->toText())
            .arg(release_prefix->getAddress().toText())
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
    bool success = false; // was the removal operation succeessful?

    if (!skip) {
        success = LeaseMgrFactory::instance().deleteLease(lease->addr_);
    } else {
        // Callouts decided to skip the next processing step. The next
        // processing step would to send the packet, so skip at this
        // stage means "drop response".
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_HOOKS, DHCP6_HOOK_LEASE6_RELEASE_PD_SKIP);
    }

    // Here the success should be true if we removed lease successfully
    // and false if skip flag was set or the removal failed for whatever reason

    if (!success) {
        ia_rsp->addOption(createStatusCode(STATUS_UnspecFail,
                          "Server failed to release a lease"));

        LOG_ERROR(dhcp6_logger, DHCP6_RELEASE_PD_FAIL)
            .arg(lease->addr_.toText())
            .arg(duid->toText())
            .arg(lease->iaid_);
        general_status = STATUS_UnspecFail;
    } else {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_RELEASE_PD)
            .arg(lease->addr_.toText())
            .arg(duid->toText())
            .arg(lease->iaid_);

        ia_rsp->addOption(createStatusCode(STATUS_Success,
                          "Lease released. Thank you, please come again."));
    }

    return (ia_rsp);
}

Pkt6Ptr
Dhcpv6Srv::processSolicit(const Pkt6Ptr& solicit) {

    sanityCheck(solicit, MANDATORY, FORBIDDEN);

    Pkt6Ptr advertise(new Pkt6(DHCPV6_ADVERTISE, solicit->getTransid()));

    copyDefaultOptions(solicit, advertise);
    appendDefaultOptions(solicit, advertise);
    appendRequestedOptions(solicit, advertise);
    appendRequestedVendorOptions(solicit, advertise);

    Option6ClientFqdnPtr fqdn = processClientFqdn(solicit);
    assignLeases(solicit, advertise, fqdn);
    appendClientFqdn(solicit, advertise, fqdn);
    // Note, that we don't create NameChangeRequests here because we don't
    // perform DNS Updates for Solicit. Client must send Request to update
    // DNS.

    return (advertise);
}

Pkt6Ptr
Dhcpv6Srv::processRequest(const Pkt6Ptr& request) {

    sanityCheck(request, MANDATORY, MANDATORY);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, request->getTransid()));

    copyDefaultOptions(request, reply);
    appendDefaultOptions(request, reply);
    appendRequestedOptions(request, reply);
    appendRequestedVendorOptions(request, reply);

    Option6ClientFqdnPtr fqdn = processClientFqdn(request);
    assignLeases(request, reply, fqdn);
    appendClientFqdn(request, reply, fqdn);
    createNameChangeRequests(reply, fqdn);

    return (reply);
}

Pkt6Ptr
Dhcpv6Srv::processRenew(const Pkt6Ptr& renew) {

    sanityCheck(renew, MANDATORY, MANDATORY);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, renew->getTransid()));

    copyDefaultOptions(renew, reply);
    appendDefaultOptions(renew, reply);
    appendRequestedOptions(renew, reply);

    Option6ClientFqdnPtr fqdn = processClientFqdn(renew);
    renewLeases(renew, reply, fqdn);
    appendClientFqdn(renew, reply, fqdn);
    createNameChangeRequests(reply, fqdn);

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

    // @todo If client sent a release and we should remove outstanding
    // DNS records.

    return (reply);
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
        // Get the list of stdandard option definitions.
        option_defs = LibDHCP::getOptionDefs(Option::V6);
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
    // a two-byte type code and a two-byte length field.
    while (offset + 4 <= length) {
        uint16_t opt_type = isc::util::readUint16(&buf[offset]);
        offset += 2;

        uint16_t opt_len = isc::util::readUint16(&buf[offset]);
        offset += 2;

        if (offset + opt_len > length) {
            // @todo: consider throwing exception here.
            return (offset);
        }

        if (opt_type == D6O_RELAY_MSG && relay_msg_offset && relay_msg_len) {
            // remember offset of the beginning of the relay-msg option
            *relay_msg_offset = offset;
            *relay_msg_len = opt_len;

            // do not create that relay-msg option
            offset += opt_len;
            continue;
        }

        if (opt_type == D6O_VENDOR_OPTS) {
            if (offset + 4 > length) {
                // Truncated vendor-option. There is expected at least 4 bytes
                // long enterprise-id field
                return (offset);
            }

            // Parse this as vendor option
            OptionPtr vendor_opt(new OptionVendor(Option::V6, buf.begin() + offset,
                                                  buf.begin() + offset + opt_len));
            options.insert(std::make_pair(opt_type, vendor_opt));

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


};
};
