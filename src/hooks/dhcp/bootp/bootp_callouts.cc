// Copyright (C) 2019-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the End User License
// Agreement. See COPYING file in the premium/ directory.

#include <config.h>

#include <bootp_log.h>
#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <stats/stats_mgr.h>

#include <vector>

using namespace isc;
using namespace isc::bootp;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::stats;

namespace {

// DHCP Specific options listed in RFC 1533 section 9 and with a code name
// beginning by DHO_DHCP_.
const std::vector<uint16_t> DHCP_SPECIFIC_OPTIONS = {
    DHO_DHCP_REQUESTED_ADDRESS,
    DHO_DHCP_LEASE_TIME,
    DHO_DHCP_OPTION_OVERLOAD,
    DHO_DHCP_MESSAGE_TYPE,
    DHO_DHCP_SERVER_IDENTIFIER,
    DHO_DHCP_PARAMETER_REQUEST_LIST,
    DHO_DHCP_MESSAGE,
    DHO_DHCP_MAX_MESSAGE_SIZE,
    DHO_DHCP_RENEWAL_TIME,
    DHO_DHCP_REBINDING_TIME,
    DHO_DHCP_CLIENT_IDENTIFIER
};

// Size of the BOOTP space for vendor extensions.
const size_t BOOT_VENDOR_SPACE_SIZE = 64;

// Minimum size of a BOOTP message.
const size_t BOOT_MIN_SIZE = Pkt4::DHCPV4_PKT_HDR_LEN + BOOT_VENDOR_SPACE_SIZE;

// Check as compile time it is really 300!
static_assert(BOOT_MIN_SIZE == 300, "BOOT_MIN_SIZE is not 300");

} // end of anonymous namespace.

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

/// @brief This callout is called at the "pkt4_send" hook.
///
/// Remove DHCP specific options and pad the buffer to 300 octets.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_send(CalloutHandle& handle) {
    // Get the query message.
    Pkt4Ptr query;
    handle.getArgument("query4", query);

    // Check if it is a BOOTP query.
    if (!query->inClass("BOOTP")) {
        return (0);
    }

    // Get the response message.
    Pkt4Ptr response;
    handle.getArgument("response4", response);

    // @todo check if exists and/or already packed.

    for (uint16_t code : DHCP_SPECIFIC_OPTIONS) {
        while (response->delOption(code))
            ;
    }

    // Pack the response.
    try {
        LOG_DEBUG(bootp_logger, DBGLVL_TRACE_BASIC, BOOTP_PACKET_PACK)
            .arg(response->getLabel());
        response->pack();

        // The pack method adds a DHO_END option at the end.
        isc::util::OutputBuffer& buffer = response->getBuffer();
        size_t size = buffer.getLength();
        if (size < BOOT_MIN_SIZE) {
            size_t delta = BOOT_MIN_SIZE - size;
            std::vector<uint8_t> zeros(delta, 0);
            buffer.writeData(&zeros[0], delta);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(bootp_logger, BOOTP_PACKET_PACK_FAIL)
            .arg(response->getLabel())
            .arg(ex.what());
    }

    // Avoid to pack it a second time!
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

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
