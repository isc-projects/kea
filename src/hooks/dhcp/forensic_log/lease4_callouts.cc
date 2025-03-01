// Copyright (C) 2016-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <cc/data.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/lease.h>
#include <eval/evaluate.h>
#include <hooks/hooks.h>
#include <util/str.h>
#include <legal_log_log.h>
#include <dhcpsrv/backend_store_factory.h>
#include <rotating_file.h>
#include <subnets_user_context.h>

#include <sstream>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace hooks;
using namespace legal_log;
using namespace std;

/// @brief Create custom log entry for the current lease.
///
/// @param query The query received by the server.
/// @param response The response of the server.
/// @param lease The current lease generating this log entry.
/// @param [out] value The value of the custom log entry after parser execution.
bool getCustomEntry(const Pkt4Ptr& query, const Pkt4Ptr& response,
                    const Lease4Ptr& /*lease*/, std::string& value) {
    bool using_custom_format = false;

    auto expression = BackendStoreFactory::instance(managerID())->getRequestFormatExpression();
    if (expression && query) {
        value = evaluateString(*expression, *query);
        using_custom_format = true;
    }

    expression = BackendStoreFactory::instance(managerID())->getResponseFormatExpression();
    if (expression && response) {
        value += evaluateString(*expression, *response);
        using_custom_format = true;
    }

    return (using_custom_format);
}

/// @brief Creates legal store entry for a DHCPv4 Lease.
///
/// Creates an entry based on the given DHCPREQUEST and corresponding
/// DHCPv4 lease.  The entry is returned as a single string with no embedded
/// EOL markers, a prepended timestamp and has the following sections:
///
///  "<timestamp><address><duration><device-id>{client-info}{relay-info}{user-context}"
///
/// Where:
///     - timestamp - the current date and time the log entry was written
///     in "%Y-%m-%d %H:%M:%S %Z" strftime format.
///     - address - the leased IPv4 address given out and whether it was
///     assigned or renewed.
///     - duration - the lease lifetime expressed as in days (if present),
///     hours, minutes and seconds.  A lease lifetime of 0xFFFFFFFF will be
///     denoted with the text "infinite duration".
///     - device-id - the client's hardware address shown as numerical type
///     and hex digit string.
///     - client-info - the DHCP client id option (61) if present, shown as
///     hex digit string and eventually its printable content.
///     - relay-info - for relayed packets the giaddr and the RAI circuit id
///     and remote id options (x and xx) if present.
///     - user-context - the optional user context.
///
///     For example (on multiple lines for readibility):
/// @code
///  "2018-01-06 01:02:03 CET Address: 192.2.1.100 has been renewed
///  for 1 hrs 52 min 15 secs to a device with hardware address:
///  hwtype=1 08:00:2b:02:3f:4e, client-id: 17:34:e2:ff:09:92:54
///  connected via relay at address: 192.2.16.33, identified by
///  circuit-id: 68:6f:77:64:79 (howdy) and remote-id: 87:f6:79:77:ef"
/// @endcode
///
/// @param query DHCPv4 query packet for which the lease was generated
/// @param response DHCPv4 response packet
/// @param lease DHCPv4 lease for which the entry should be created
/// @param action Kind of event to log.
std::string genLease4Entry(const Pkt4Ptr& query,
                           const Pkt4Ptr& response,
                           const Lease4Ptr& lease,
                           const Action& action) {
    std::string value;
    if (getCustomEntry(query, response, lease, value)) {
        return (value);
    }

    std::stringstream stream;

    // <address>
    stream << "Address: " << lease->addr_ << " has been " << actionToVerb(action);

    if (action != Action::RELEASE) {
        // <duration>
        stream << " for " << BackendStore::genDurationString(lease->valid_lft_) << " to";
    } else {
        stream << " from";
    }

    // <device-id>
    stream << " a device with hardware address: " << lease->hwaddr_->toText();

    // <client-info>
    if (lease->client_id_) {
        stream << ", client-id: " << lease->client_id_->toText();

        // It is not uncommon to provide a printable client ID
        auto bin = lease->client_id_->getClientId();

        if (str::isPrintable(bin)) {
            stream << " (" << BackendStore::vectorDump(bin) << ")";
        }
    }

    // <relay-info>
    const isc::asiolink::IOAddress& giaddr = query->getGiaddr();
    if (!giaddr.isV4Zero()) {
        stream << " connected via relay at address: " << giaddr.toText();

        // Look for relay agent information option (option 82)
        OptionPtr rai = query->getOption(DHO_DHCP_AGENT_OPTIONS);
        if (rai) {
            // Look for circuit-id (sub-option 1)
            std::stringstream idstream;
            OptionPtr opt = rai->getOption(RAI_OPTION_AGENT_CIRCUIT_ID);
            if (opt) {
                const OptionBuffer& id = opt->getData();
                if (!id.empty()) {
                    idstream << "circuit-id: " << BackendStore::vectorHexDump(id);

                    if (str::isPrintable(id)) {
                        idstream << " (" << BackendStore::vectorDump(id) << ")";
                    }
                }
            }

            // Look for remote-id (sub-option 2)
            opt = rai->getOption(RAI_OPTION_REMOTE_ID);
            if (opt) {
                const OptionBuffer& id = opt->getData();
                if (!id.empty()) {
                    if (!idstream.str().empty()) {
                        idstream << " and ";
                    }

                    idstream << "remote-id: " << BackendStore::vectorHexDump(id);

                    if (str::isPrintable(id)) {
                        idstream << " (" << BackendStore::vectorDump(id) << ")";
                    }
                }
            }

            // Look for subscriber-id (sub-option 6)
            opt = rai->getOption(RAI_OPTION_SUBSCRIBER_ID);
            if (opt) {
                const OptionBuffer& id = opt->getData();
                if (!id.empty()) {
                    if (!idstream.str().empty()) {
                        idstream << " and ";
                    }

                    idstream << "subscriber-id: " << BackendStore::vectorHexDump(id);

                    if (str::isPrintable(id)) {
                        idstream << " (" << BackendStore::vectorDump(id) << ")";
                    }
                }
            }

            if (!idstream.str().empty()) {
                stream << ", identified by " << idstream.str();
            }
        }
    }

    ConstElementPtr ctx = lease->getContext();
    if (ctx) {
        stream << ", context: " << ctx->str();
    }

    return (stream.str());
}

/// @brief Produces an DHCPv4 legal log entry from a callout handle.
///
/// Extracts the inbound packet and lease from the Callout, generates the
/// log entry text and writes it to the legal store.  If the the legal store
/// has not been instantiated or writing to it fails, the function log the
/// error and return failure.
///
/// It is possible to disable logging for selected subnets by specifying a
/// "legal-logging" boolean parameter within the subnet's user context. If
/// this parameter is not specified it defaults to 'true', in which case the
/// logging is performed. When this value is set to 'false' the log is not
/// produced and the function returns.
///
/// @param handle CalloutHandle which provides access to context.
/// @param action Kind of event to log.
///
/// @return returns 0 upon success, non-zero otherwise
int legalLog4Handler(CalloutHandle& handle, const Action& action) {
    if (!BackendStoreFactory::instance(managerID())) {
        LOG_ERROR(legal_log_logger,
                  LEGAL_LOG_LEASE4_NO_LEGAL_STORE);
        return (1);
    }

    // Fetch the client's packet and the lease callout arguments.
    Pkt4Ptr query;
    handle.getArgument("query4", query);

    Pkt4Ptr response;
    handle.getArgument("response4", response);

    Lease4Ptr lease;
    handle.getContext("lease4", lease);

    if (!lease) {
        return (0);
    }

    ConstCfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    try {
        ConstSubnet4Ptr subnet = cfg->getBySubnetId(lease->subnet_id_);

        if (!isLoggingDisabled(subnet)) {
            BackendStoreFactory::instance(managerID())->writeln(genLease4Entry(query, response,
                                                                               lease, action),
                                                                lease->addr_.toText());
        }

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

/// @brief This callout is called at the "pkt4_receive" hook.
///
/// Creates context with empty "lease4" value.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_receive(CalloutHandle& handle) {
    handle.setContext("lease4", Lease4Ptr());
    handle.setContext("leases4", Lease4CollectionPtr());
    handle.setContext("deleted_leases4", Lease4CollectionPtr());
    return (0);
}

/// @brief This callout is called at the "leases4_committed" hook.
///
/// Stores the leases so that the logging option stored on the subnet context
/// can be available on pkt4_send hook.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int leases4_committed(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Lease4CollectionPtr leases;
    handle.getArgument("leases4", leases);
    handle.setContext("leases4", leases);

    Lease4CollectionPtr deleted_leases;
    handle.getArgument("deleted_leases4", deleted_leases);
    handle.setContext("deleted_leases4", deleted_leases);
    return (0);
}

/// @brief This callout is called at the "pkt4_send" hook.
///
/// Generates an entry in the legal log for a lease renewal if
/// the callout context values "leases4" and "deleted_leases4" are not empty.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_send(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Lease4CollectionPtr leases;
    handle.getContext("leases4", leases);

    int current = 0;
    int result = current;

    if (leases) {
        for (auto const& lease : *leases) {
            handle.setContext("lease4", lease);
            current = legalLog4Handler(handle, Action::ASSIGN);
            if (current) {
                result = current;
            }
        }
    }

    handle.getContext("deleted_leases4", leases);

    if (leases) {
        for (auto const& lease : *leases) {
            handle.setContext("lease4", lease);
            current = legalLog4Handler(handle, Action::RELEASE);
            if (current) {
                result = current;
            }
        }
    }

    return (result);
}

/// @brief This callout is called at the "lease4_release" hook.
///
/// Generates an entry in the legal log for a lease release if
/// the callout context value "lease4" is not an empty pointer.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease4_release(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    handle.setContext("lease4", lease);

    Pkt4Ptr response;
    handle.setArgument("response4", response);

    return (legalLog4Handler(handle, Action::RELEASE));
}

/// @brief This callout is called at the "lease4_decline" hook.
///
/// Generates an entry in the legal log for a lease decline if
/// the callout context value "lease4" is not an empty pointer.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease4_decline(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    handle.setContext("lease4", lease);

    Pkt4Ptr response;
    handle.setArgument("response4", response);

    return (legalLog4Handler(handle, Action::RELEASE));
}

} // end extern "C"
