// Copyright (C) 2019-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the End User License
// Agreement. See COPYING file in the premium/ directory.

#include <config.h>

#include <bootp_log.h>
#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <stats/stats_mgr.h>

using namespace isc;
using namespace isc::bootp;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::stats;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief This callout is called at the "buffer4_receive" hook.
///
/// Ignore DHCP and BOOTREPLY messages.
/// Remaining packets should be BOOTP requests so add the BOOTP client class
/// and set the message type to DHCPREQUEST.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, non-zero otherwise.
int buffer4_receive(CalloutHandle& handle) {
    // Get the received unpacked message.
    Pkt4Ptr query;
    handle.getArgument("query4", query);

    try {
        // Unpack it (TODO check if it was already unpacked).
        query->unpack();

        // Not DHCP query nor BOOTP response?
        if ((query->getType() == DHCP_NOTYPE) &&
            (query->getOp() == BOOTREQUEST)) {

            query->addClass("BOOTP");
            query->setType(DHCPREQUEST);

            LOG_DEBUG(bootp_logger, DBGLVL_TRACE_BASIC, BOOTP_BOOTP_QUERY)
                .arg(query->getLabel());
        }
    } catch (const SkipRemainingOptionsError& ex) {
        // An option failed to unpack but we are to attempt to process it
        // anyway.  Log it and let's hope for the best.
        LOG_DEBUG(bootp_logger, DBGLVL_TRACE_BASIC,
                  BOOTP_PACKET_OPTIONS_SKIPPED)
            .arg(ex.what());
    } catch (const std::exception& ex) {
        // Failed to parse the packet.
        LOG_DEBUG(bootp_logger, DBGLVL_TRACE_BASIC,
                  BOOTP_PACKET_UNPACK_FAILED)
            .arg(query->getRemoteAddr().toText())
            .arg(query->getLocalAddr().toText())
            .arg(query->getIface())
            .arg(ex.what());

        // Increase the statistics of parse failures and dropped packets.
        StatsMgr::instance().addValue("pkt4-parse-failed",
                                      static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt4-receive-drop",
                                      static_cast<int64_t>(1));

        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        return (0);
    }

    // Avoid to unpack it a second time!
    handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);

    return (0);
}

/// @brief This function is called when the library is loaded.
///
/// @return always 0.
int load(LibraryHandle& /* handle */) {
    LOG_INFO(bootp_logger, BOOTP_LOAD);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return always 0.
int unload() {
    LOG_INFO(bootp_logger, BOOTP_UNLOAD);
    return (0);
}

} // end extern "C"
