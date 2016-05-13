// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file lease6_co.cc Defines lease6_select and lease6_renew callout functions.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_custom.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <hooks/hooks.h>
#include <legal_file.h>
#include <legal_log_log.h>

#include <sstream>

using namespace isc;
using namespace dhcp;
using namespace hooks;
using namespace legal_log;
using namespace std;

/// @brief Pointer to the registry instance.
extern LegalFilePtr legal_file;

/// @brief Function which converts hardware address source to a string
///
/// @param source - integer value to convert
/// @return - string label for the value or "UNKNOWN" if not recognized.
std::string hwaddrSourceToString(uint32_t source) {
    if (source == HWAddr::HWADDR_SOURCE_RAW) {
        return ("Raw Socket");
    }
    if (source == HWAddr::HWADDR_SOURCE_DUID) {
        return ("DUID");
    }
    if (source == HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL) {
        return ("IPv6 Link Local");
    }
    if (source == HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION) {
        return ("Client Address Relay Option");
    }
    if (source == HWAddr::HWADDR_SOURCE_REMOTE_ID) {
        return ("Remote ID");
    }
    if (source == HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID) {
        return ("Subscriber ID");
    }
    if (source == HWAddr::HWADDR_SOURCE_DOCSIS_CMTS) {
        return ("DOCSIS CMTS");
    }
    if (source == HWAddr::HWADDR_SOURCE_DOCSIS_MODEM) {
        return ("DOCSIS MODEM");
    }

    return ("UKNOWN");
}


/// @brief Creates legal file entry for a DHCPv6 Lease
///
/// Creates an entry based on the given DHCPv4 DHCPREQUEST and corresponding
/// DHCPv4 lease.  The entry is returned as a single string with no embedded
/// EOL markers and has the following sections:
///
///  <address><duration><device-id>{client-info}{relay-info}
///
/// Where:
///     # address - the leased IPv6 address given out and whether it was
///     assigned or renewed.
///     # duration - the lease lifetime expressed as in days (if present),
///     hours, minutes and seconds.  A lease lifetime of 0xFFFFFFFF will be
///     denoted with the text "infinite duration".
///     # device-id - the client's DUID and hardware address (if present)
///     # client-info - the DHCP client id option (61) if present, shown as
///     hex digit string
///     # relay-inf - for relayed packets the giaddr and the RAI circuit id
///     and remote id options (x and xx) if present
///
///     For example:
/// {{{
///  "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs to a device with hardware address: hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54 connected via relay at address: 192.2.16.33, identified by circuit-id: 68:6f:77:64:79 and remote-id: 87:f6:79:77:ef
/// }}}
///
/// @param query - DHCPREQUEST packet for which the lease was generated
/// @param lease - DHCPv4 lease for which the entry should be created
/// @param renewal - indicates whether or not the lease is a renewal.
std::string genLease6Entry(Pkt6Ptr query, Lease6Ptr lease, bool renewal) {
    std::stringstream stream;
    // <address>

    if (lease->type_  != Lease::TYPE_PD) {
        stream <<  "Address:" << lease->addr_;
    } else {
        stream <<  "Prefix:" << lease->addr_ << "/" << lease->prefixlen_;
    }

    stream << " has been " << (renewal ? "renewed" : "assigned");

    // <duration>
    stream << " for " << LegalFile::genDurationString(lease->valid_lft_);

    // <device-id>
    stream << " to a device with DUID: " << lease->duid_->toText();

    if (lease->hwaddr_) {
            stream << " and hardware address: " << lease->hwaddr_->toText()
                   << " (from " << hwaddrSourceToString(lease->hwaddr_->source_)
                    << ")";
    }

    // Is it via relay(s)?
    if (query->relay_info_.size()) {
        const Pkt6::RelayInfo& server_relay = query->relay_info_[0];
        stream << " connected via relay at address: "
               <<  server_relay.peeraddr_.toText()
               << " for client on link address: "
               <<  server_relay.linkaddr_.toText()
               << ", hop count: " << static_cast<int>(server_relay.hop_count_);

        std::ostringstream idstream;
        // Look for the remote-id option
        OptionPtr opt = query->getAnyRelayOption(D6O_REMOTE_ID,
                                                 Pkt6::RELAY_GET_FIRST);
        if (opt) {
            const OptionBuffer id = opt->getData();
            if (!id.empty()) {
                idstream << "remote-id: " << LegalFile::vectorHexDump(id);
            }
        }

        // Look for the subscriber-id option
        opt = query->getAnyRelayOption(D6O_SUBSCRIBER_ID,
                                       Pkt6::RELAY_GET_FIRST);
        if (opt) {
            const OptionBuffer id = opt->getData();
            if (!id.empty()) {
                if (!idstream.str().empty()) {
                        idstream << " and ";
                }
                idstream << "subscriber-id: " << LegalFile::vectorHexDump(id);
            }
        }

        if (!idstream.str().empty()) {
                stream << ", identified by " << idstream.str();
        }
    }

    return(stream.str());
}

/// @brief Produces an DHCPv6 legal log entry from a callout handle
///
/// Extracts the inbound packet and lease from the Callout, generates the
/// log entry text and writes it to the legal file.  If the the legal file
/// has not been instantiated or writing to it fails, the function log the
/// error and return failure.
///
/// @param handle CalloutHandle which provides access to context.
/// @param renewal - indicates whether or not the lease is a renewal.
///
/// @return - returns 0 upon success, non-zero otherwise
int legallog6_handler(CalloutHandle& handle, bool renewal) {
    if (!legal_file) {
        LOG_ERROR(legal_log_logger, LEGAL_FILE_HOOK_LEASE6_NO_LEGAL_FILE);
        return (1);
    }

    // Fetch the client's packet and the lease callout arguments.
    Pkt6Ptr query;
    handle.getArgument("query6", query);

    Lease6Ptr lease;
    handle.getArgument("lease6", lease);
    try {
        legal_file->writeln(genLease6Entry(query, lease, renewal));
    } catch (const std::exception& ex) {
        LOG_ERROR(legal_log_logger, LEGAL_FILE_HOOK_LEASE6_WRITE_ERROR)
                  .arg(ex.what());
        return (1);
    }

    return (0);
}


// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief  This callout is called at the "lease6_select" hook.
///
/// Generates an entry in the legal log for a lease assignment if
/// the fake_allocation argument is false.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease6_select(CalloutHandle& handle) {
    bool fake_allocation;
    handle.getArgument("fake_allocation", fake_allocation);
    if (fake_allocation) {
        return (0);
    }

    return(legallog6_handler(handle, false));
}

/// @brief  This callout is called at the "lease6_renew" hook.
///
/// Generates an entry in the legal log for a lease renewal if
/// the callout context value "query6" is not an empty pointer.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease6_renew(CalloutHandle& handle) {
    return(legallog6_handler(handle, true));
}

/// @brief  This callout is called at the "lease6_rebind" hook.
///
/// Generates an entry in the legal log for a lease renewal if
/// the callout context value "query6" is not an empty pointer.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease6_rebind(CalloutHandle& handle) {
    return(legallog6_handler(handle, true));
}

} // end extern "C"
