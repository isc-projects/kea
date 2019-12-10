// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the End User License
// Agreement. See COPYING file in the premium/ directory.

#include <config.h>

#include <bootp_log.h>
#include <hooks/hooks.h>
#include <dhcp/pkt4.h>

using namespace isc;
using namespace isc::bootp;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief This callout is called at the "buffer4_receive" hook.
///
/// Ignore DHCP and BOOTREPLY messages.
/// Remaining packets should be BOOTP requests so add the BOOTP client class,
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, non-zero otherwise.
int buffer4_receive(CalloutHandle& handle) {
    // Get the received unpacked message.
    Pkt4Ptr query;
    handle.getArgument("query4", query);

    try {
        // Take a copy and unpack it.
        Pkt4Ptr copy(new Pkt4(&query->data_[0], query->data_.size()));
        copy->unpack();

        if (copy->getType() != DHCP_NOTYPE) {
            // DHCP query.
            return (0);
        }
        if (copy->getOp() == BOOTREPLY) {
            // BOOTP response.
            return (0);
        }
        // BOOTP query.
        query->addClass("BOOTP");
        LOG_DEBUG(bootp_logger, DBGLVL_TRACE_BASIC, BOOTP_ADDED_CLASS)
            .arg(query->getLabel());
    } catch (const std::exception&) {
        // Got an error. The query shall very likely be dropped later.
        // Note this covers malformed DHCP packets where the message
        // type option can't be unpacked, and RFC 951 BOOTP.
    }

    return (0);
}

/// @brief This callout is called at the "pkt4_receive" hook.
///
/// If in the BOOTP class add a DHCPREQUEST dhcp-message-type.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_receive(CalloutHandle& handle) {
    // Get the received unpacked message.
    Pkt4Ptr query;
    handle.getArgument("query4", query);

    try {
        if (!query->inClass("BOOTP")) {
            return (0);
        }
        query->setType(DHCPREQUEST);
        LOG_DEBUG(bootp_logger, DBGLVL_TRACE_BASIC, BOOTP_ADDED_MSGTYPE)
            .arg(query->getLabel());
    } catch (const std::exception&) {
        // Got an error (should not happen).
    }

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
