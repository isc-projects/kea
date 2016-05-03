// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file lease4_co.cc Defines lease4_select and lease4_renew callout functions.

#include <config.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/lease.h>
#include <hooks/hooks.h>
#include <legal_file.h>
#include <legal_log_log.h>

#include <sstream>
#include <locale>

using namespace isc;
using namespace dhcp;
using namespace hooks;
using namespace legal_log;
using namespace std;

/// @brief Pointer to the registry instance.
extern LegalFilePtr legal_file;

/// @brief Creates a string of hex digit pairs from a vector of bytes
///
/// @param bytes - vector of bytes to convert
/// @param delimiter - string to use a delimiter, defaults to ":"
/// @return std::string containing the hex output
std::string vectorHexDump(const std::vector<uint8_t>& bytes, const std::string& delimiter = ":") {
    std::stringstream tmp;
    tmp << std::hex;
    bool delim = false;
    for (std::vector<uint8_t>::const_iterator it = bytes.begin();
         it != bytes.end(); ++it) {
        if (delim) {
            tmp << delimiter;
        }
        tmp << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(*it);
        delim = true;
    }
    return (tmp.str());
}

/// @brief Creates legal file entry for a DHCPv4 Lease
///
/// Creates an entry based on the given DHCPv4 DHCPREQUEST and corresponding
/// DHCPv4 lease.  The entry is returned as a single string with no embedded
/// EOL markers and has the following sections:
///
///  <address><duration><device-id>{client-info}{relay-info}
///
/// Where:
///     # address - the leased IPv4 address given out and whether it was assigned
///     or renewed.
///     # duration - the lease lifetime expressed as in days (if present),
///     hours, minutes and seconds.  A lease lifetime of 0xFFFFFFFF will be
///     denoted with the text "infinite duration".
///     # device-id - the client's hardware address shown as numerical type
///     and hex digit string
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
std::string genLease4Entry(Pkt4Ptr query, Lease4Ptr lease, bool renewal) {
    std::stringstream stream;

    // <address>
    stream << "Address: " << lease->addr_
        << " has been " << (renewal ? "renewed" : "assigned");

    // <duration>
    stream << " for " << LegalFile::genDurationString(lease->valid_lft_);

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
            std::stringstream idstream;
            OptionPtr circuit_id_opt = rai->getOption(RAI_OPTION_AGENT_CIRCUIT_ID);
            if (circuit_id_opt) {
                const OptionBuffer& circuit_id_vec = circuit_id_opt->getData();
                if (!circuit_id_vec.empty()) {
                    idstream << "circuit-id: " << vectorHexDump(circuit_id_vec);
                }
            }

            OptionPtr remote_id_opt = rai->getOption(RAI_OPTION_REMOTE_ID);
            if (remote_id_opt) {
                const OptionBuffer& remote_id_vec = remote_id_opt->getData();
                if (!remote_id_vec.empty()) {
                    if (!idstream.str().empty()) {
                        idstream << " and ";
                    }

                    idstream << "remote-id: " << vectorHexDump(remote_id_vec);
                }
            }

            if (!idstream.str().empty()) {
                stream << ", identified by " << idstream.str();
            }
        }
    }

    return(stream.str());
}

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief  This callout is called at the "pkt4_receive" hook.
///
/// If the inbound packet is a DHCP REQUEST, we push the packet
/// to the context, so we can retrieve necessary info in lease4_select
/// or lease4_renew to generate the legal log.  Currently those
/// callouts do not receive the packet as an argument.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_receive(CalloutHandle& handle) {

    try {
        Pkt4Ptr query;
        handle.getArgument("query4", query);
        if (query->getType() == DHCPREQUEST) {
            handle.setContext("query4", query);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(legal_log_logger, LEGAL_FILE_HOOK_PKT4_RECEIVE_ERROR)
                  .arg(ex.what());
        return (1);
    }

    return (0);
}


/// @brief  This callout is called at the "lease4_select" hook.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease4_select(CalloutHandle& handle) {
    if (!legal_file) {
        LOG_ERROR(legal_log_logger, LEGAL_FILE_HOOK_LEASE4_SELECT_NO_LEGAL_FILE);
        return (1);
    }

    // Fetch the client's packet from the callout context. It should be
    // there since we pushed it into the context in pkt4_receive().
    Pkt4Ptr query;
    handle.getContext("query4", query);
    if (!query) {
        LOG_ERROR(legal_log_logger, LEGAL_FILE_HOOK_LEASE4_SELECT_NO_QRY);
        return (1);
    }

    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    try {
        legal_file->writeln(genLease4Entry(query,lease, false));
    } catch (const std::exception& ex) {
        LOG_ERROR(legal_log_logger, LEGAL_FILE_HOOK_LEASE4_SELECT_WRITE_ERROR)
                  .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief  This callout is called at the "lease4_renew" hook.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease4_renew(CalloutHandle& handle) {
    if (!legal_file) {
        LOG_ERROR(legal_log_logger, LEGAL_FILE_HOOK_LEASE4_RENEW_NO_LEGAL_FILE);
        return (1);
    }

    // Fetch the client's packet from the callout context. It should be
    // there since we pushed it into the context in pkt4_receive().
    Pkt4Ptr query;
    handle.getContext("query4", query);
    if (!query) {
        LOG_ERROR(legal_log_logger, LEGAL_FILE_HOOK_LEASE4_RENEW_NO_QRY);
        return (1);
    }

    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    try {
        legal_file->writeln(genLease4Entry(query,lease, true));
    } catch (const std::exception& ex) {
        LOG_ERROR(legal_log_logger, LEGAL_FILE_HOOK_LEASE4_RENEW_WRITE_ERROR)
                  .arg(ex.what());
        return (1);
    }

    return (0);
}

} // end extern "C"
