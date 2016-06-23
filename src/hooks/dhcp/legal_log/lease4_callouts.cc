// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file lease4_callouts.cc Defines lease4_select and lease4_renew callout functions.

#include <config.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/lease.h>
#include <hooks/hooks.h>
#include <legal_log_log.h>
#include <rotating_file.h>

#include <sstream>

using namespace isc;
using namespace dhcp;
using namespace hooks;
using namespace legal_log;
using namespace std;

/// @brief Pointer to the registry instance.
extern RotatingFilePtr legal_file;

/// @brief Creates legal file entry for a DHCPv4 Lease
///
/// Creates an entry based on the given DHCPREQUEST and corresponding
/// DHCPv4 lease.  The entry is returned as a single string with no embedded
/// EOL markers and has the following sections:
///
///  "<address><duration><device-id>{client-info}{relay-info}"
///
/// Where:
///     - address - the leased IPv4 address given out and whether it was
///     assigned or renewed.
///     - duration - the lease lifetime expressed as in days (if present),
///     hours, minutes and seconds.  A lease lifetime of 0xFFFFFFFF will be
///     denoted with the text "infinite duration".
///     - device-id - the client's hardware address shown as numerical type
///     and hex digit string.
///     - client-info - the DHCP client id option (61) if present, shown as
///     hex digit string.
///     - relay-info - for relayed packets the giaddr and the RAI circuit id
///     and remote id options (x and xx) if present.
///
///     For example (on multiple lines for readibility):
/// @code
///  "Address: 192.2.1.100 has been renewed for 1 hrs 52 min 15 secs
///  to a device with hardware address: hwtype=1 08:00:2b:02:3f:4e,
///  client-id: 17:34:e2:ff:09:92:54 connected via relay at address:
///  192.2.16.33, identified by circuit-id: 68:6f:77:64:79 and
///  remote-id: 87:f6:79:77:ef"
/// @endcode
///
/// @param query - DHCPREQUEST packet for which the lease was generated
/// @param lease - DHCPv4 lease for which the entry should be created
/// @param renewal - indicates whether or not the lease is a renewal.
std::string genLease4Entry(const Pkt4Ptr& query, const Lease4Ptr& lease, const bool renewal) {
    std::stringstream stream;

    // <address>
    stream << "Address: " << lease->addr_
        << " has been " << (renewal ? "renewed" : "assigned");

    // <duration>
    stream << " for " << RotatingFile::genDurationString(lease->valid_lft_);

    // <device-id>
    stream << " to a device with hardware address: "
           << lease->hwaddr_->toText();

    // <client-info>
    if (lease->client_id_) {
           stream << ", client-id: " << lease->client_id_->toText();
    }

    // <relay-info>
    const isc::asiolink::IOAddress& giaddr = query->getGiaddr();
    if (!giaddr.isV4Zero()) {
            stream << " connected via relay at address: " << giaddr.toText();

        // Look for relay agent information option
        OptionPtr rai = query->getOption(DHO_DHCP_AGENT_OPTIONS);
        if (rai) {
            // Look for circuit-id
            std::stringstream idstream;
            OptionPtr opt = rai->getOption(RAI_OPTION_AGENT_CIRCUIT_ID);
            if (opt) {
                const OptionBuffer& id = opt->getData();
                if (!id.empty()) {
                    idstream << "circuit-id: " << RotatingFile::vectorHexDump(id);
                }
            }

            // Look for remote-id
            opt = rai->getOption(RAI_OPTION_REMOTE_ID);
            if (opt) {
                const OptionBuffer& id = opt->getData();
                if (!id.empty()) {
                    if (!idstream.str().empty()) {
                        idstream << " and ";
                    }

                    idstream << "remote-id: " << RotatingFile::vectorHexDump(id);
                }
            }

            if (!idstream.str().empty()) {
                stream << ", identified by " << idstream.str();
            }
        }
    }

    return (stream.str());
}

/// @brief Produces an DHCPv4 legal log entry from a callout handle
///
/// Extracts the inbound packet and lease from the Callout, generates the
/// log entry text and writes it to the legal file.  If the the legal file
/// has not been instantiated or writing to it fails, the function log the
/// error and return failure.
///
/// @param handle CalloutHandle which provides access to context.
/// @param renewal indicates whether or not the lease is a renewal.
///
/// @return returns 0 upon success, non-zero otherwise
int legalLog4Handler(CalloutHandle& handle, bool renewal) {
    if (!legal_file) {
        LOG_ERROR(legal_log_logger,
                  LEGAL_LOG_LEASE4_NO_LEGAL_FILE);
        return (1);
    }

    // Fetch the client's packet and the lease callout arguments.
    Pkt4Ptr query;
    handle.getArgument("query4", query);

    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    try {
        legal_file->writeln(genLease4Entry(query, lease, renewal));
    } catch (const std::exception& ex) {
        LOG_ERROR(legal_log_logger, LEGAL_LOG_LEASE4_WRITE_ERROR)
                  .arg(ex.what());
        return (1);
    }

    return (0);
}


// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief  This callout is called at the "lease4_select" hook.
///
/// Generates an entry in the legal log for a lease assignment if
/// the fake_allocation argument is false.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease4_select(CalloutHandle& handle) {
    bool fake_allocation;
    handle.getArgument("fake_allocation", fake_allocation);
    return (fake_allocation ? 0 : legalLog4Handler(handle, false));
}

/// @brief  This callout is called at the "lease4_renew" hook.
///
/// Generates an entry in the legal log for a lease renewal if
/// the callout context value "query4" is not an empty pointer.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease4_renew(CalloutHandle& handle) {
    return (legalLog4Handler(handle, true));
}

} // end extern "C"
