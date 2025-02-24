// Copyright (C) 2016-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <cc/data.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/lease.h>
#include <eval/evaluate.h>
#include <hooks/hooks.h>
#include <util/str.h>
#include <legal_log_log.h>
#include <dhcpsrv/backend_store_factory.h>
#include <subnets_user_context.h>

#include <sstream>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace hooks;
using namespace legal_log;
using namespace std;

/// @brief Function which converts hardware address source to a string.
///
/// @param source integer value to convert
/// @return string label for the value or "UNKNOWN" if not recognized.
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

    return ("UNKNOWN");
}

/// @brief Creates legal store address column for a DHCPv6 Lease.
///
/// @param lease DHCPv6 lease for which the entry should be created
std::string genLease6Addr(const Lease6Ptr& lease) {
    std::stringstream stream;

    stream << lease->addr_;
    if (lease->type_ == Lease::TYPE_PD) {
        stream << "/" << static_cast<int>(lease->prefixlen_);
    }

    return (stream.str());
}

namespace isc {
namespace dhcp {

/// @brief Filter the IA_NA (3) option containing the OPTION_IAADDR (5)
/// option matching the respective lease. Used when filtering options.
class TokenLeaseIA_NA : public virtual TokenOption {
public:
    /// @brief Constructor.
    ///
    /// @param lease The lease used to match any OPTION_IAADDR option in the
    /// IA_NA packet options.
    /// @param rep_type Token representation type.
    TokenLeaseIA_NA(const Lease6Ptr& lease, const RepresentationType& rep_type)
    : TokenOption(D6O_IA_NA, rep_type), lease_(lease) {
        if (lease->type_ != Lease::TYPE_NA) {
            isc_throw(EvalTypeError, "Can not create token using non IPv6 address type");
        }
    }

    /// @brief Get the IA_NA (3) option containing the OPTION_IAADDR (5)
    /// option matching the respective lease.
    ///
    /// @param pkt The packet containing options.
    /// @return A copy of the IA_NA option containing only one OPTION_IAADDR
    /// option (but all other options of different type) matching the
    /// respective lease or null if none exists.
    virtual OptionPtr getOption(Pkt& pkt) {
        Pkt6* pkt6 = dynamic_cast<Pkt6*>(&pkt);
        if (!pkt6) {
            return (OptionPtr());
        }
        for (auto const& it : pkt6->getOptions(D6O_IA_NA)) {
            auto const& ia = boost::dynamic_pointer_cast<Option6IA>(it.second);
            if (ia && ia->getIAID() == lease_->iaid_) {
                OptionCollection opts = ia->getOptions();
                for (auto const& opt_it : opts) {
                    if (opt_it.second->getType() != D6O_IAADDR) {
                        continue;
                    }
                    Option6IAAddrPtr iaaddr =
                            boost::dynamic_pointer_cast<Option6IAAddr>(opt_it.second);
                    if (!iaaddr) {
                        continue;
                    }
                    if (iaaddr->getAddress() == lease_->addr_) {
                        boost::shared_ptr<Option6IA> ia_na(new Option6IA(D6O_IA_NA, ia->getIAID()));
                        ia_na->addOption(iaaddr);
                        for (auto const& other_opt_it : opts) {
                            if (other_opt_it.second->getType() == D6O_IAADDR ||
                                other_opt_it.second->getType() == D6O_IAPREFIX) {
                                continue;
                            }
                            ia_na->addOption(other_opt_it.second);
                        }
                        return (ia_na);
                    }
                }
            }
        }
        return (OptionPtr());
    }

private:
    /// @brief The lease used to match packet options.
    Lease6Ptr lease_;
};

/// @brief Filter all IA_NA so that no option is matched by the expression.
class TokenFilterIA_NA : public virtual TokenOption {
public:
    /// @brief Constructor.
    ///
    /// @param rep_type Token representation type.
    TokenFilterIA_NA(const RepresentationType& rep_type) : TokenOption(D6O_IA_NA, rep_type) {
    }

    /// @brief Get no option regardless of what the packet contains.
    ///
    /// @param pkt The packet containing options.
    /// @return Always return null option.
    virtual OptionPtr getOption(Pkt&) {
        return (OptionPtr());
    }
};

/// @brief Filter the IA_NA (3) option containing the OPTION_IAADDR (5)
/// option matching the respective lease. Used when filtering sub-options.
class TokenLeaseIA_NASuboption : public virtual TokenLeaseIA_NA, public virtual TokenSubOption {
public:
    /// @brief Constructor.
    ///
    /// @param lease The lease used to match any OPTION_IAADDR option in the
    /// IA_NA packet options.
    /// @param rep_type Token representation type.
    TokenLeaseIA_NASuboption(const Lease6Ptr& lease, const RepresentationType& rep_type)
    : TokenOption(D6O_IA_NA, rep_type), TokenLeaseIA_NA(lease, rep_type),
      TokenSubOption(D6O_IA_NA, D6O_IAADDR, rep_type) {
    }

    /// @brief Get the IA_NA (3) option containing the OPTION_IAADDR (5)
    /// option matching the respective lease.
    ///
    /// @param pkt The packet containing options.
    /// @return A copy of the IA_NA option containing only one OPTION_IAADDR
    /// option (but all other options of different type) matching the
    /// respective lease or null if none exists.
    virtual OptionPtr getOption(Pkt& pkt) {
        return (TokenLeaseIA_NA::getOption(pkt));
    }

    /// @brief Evaluate the expression using the @ref TokenSubOption
    /// implementation.
    ///
    /// @param pkt specified parent option will be extracted from this packet
    /// @param values value of the sub-option will be pushed here (or "")
    /// @return 0 which means evaluate next token if any.
    unsigned evaluate(Pkt& pkt, ValueStack& values) {
        return (TokenSubOption::evaluate(pkt, values));
    }
};

/// @brief Filter all IA_NA so that no sub-option is matched by the expression.
class TokenFilterIA_NASuboption : public virtual TokenFilterIA_NA, public virtual TokenSubOption {
public:
    /// @brief Constructor.
    ///
    /// @param rep_type Token representation type.
    TokenFilterIA_NASuboption(const RepresentationType& rep_type)
    : TokenOption(D6O_IA_NA, rep_type), TokenFilterIA_NA(rep_type),
      TokenSubOption(D6O_IA_NA, D6O_IAADDR, rep_type) {
    }

    /// @brief Get no option regardless of what the packet contains.
    ///
    /// @param pkt The packet containing options.
    /// @return Always return null option.
    virtual OptionPtr getOption(Pkt& pkt) {
        return (TokenFilterIA_NA::getOption(pkt));
    }

    /// @brief Evaluate the expression using the @ref TokenSubOption
    /// implementation.
    ///
    /// @param pkt specified parent option will be extracted from this packet
    /// @param values value of the sub-option will be pushed here (or "")
    /// @return 0 which means evaluate next token if any.
    unsigned evaluate(Pkt& pkt, ValueStack& values) {
        return (TokenSubOption::evaluate(pkt, values));
    }
};

/// @brief Filter the IA_PD (25) option containing the OPTION_IAPREFIX (25)
/// option matching the respective lease. Used when filtering options.
class TokenLeaseIA_PD : public virtual TokenOption {
public:
    /// @brief Constructor.
    ///
    /// @param lease The lease used to match any OPTION_IAPREFIX option in the
    /// IA_PD packet options.
    /// @param rep_type Token representation type.
    TokenLeaseIA_PD(const Lease6Ptr& lease, const RepresentationType& rep_type)
    : TokenOption(D6O_IA_PD, rep_type), lease_(lease) {
        if (lease->type_ != Lease::TYPE_PD) {
            isc_throw(EvalTypeError, "Can not create token using non IPv6 prefix type");
        }
    }

    /// @brief Get the IA_PD (25) option containing the OPTION_IAPREFIX (25)
    /// option matching the respective lease.
    ///
    /// @param pkt The packet containing options.
    /// @return A copy of the IA_PD option containing only one OPTION_IAPREFIX
    /// option (but all other options of different type) matching the
    /// respective lease or null if none exists.
    virtual OptionPtr getOption(Pkt& pkt) {
        Pkt6* pkt6 = dynamic_cast<Pkt6*>(&pkt);
        if (!pkt6) {
            return (OptionPtr());
        }
        for (auto const& it : pkt6->getOptions(D6O_IA_PD)) {
            auto const& ia = boost::dynamic_pointer_cast<Option6IA>(it.second);
            if (ia && ia->getIAID() == lease_->iaid_) {
                OptionCollection opts = ia->getOptions();
                for (auto const& opt_it : opts) {
                    if (opt_it.second->getType() != D6O_IAPREFIX) {
                        continue;
                    }
                    Option6IAPrefixPtr iaprefix =
                            boost::dynamic_pointer_cast<Option6IAPrefix>(opt_it.second);
                    if (!iaprefix) {
                        continue;
                    }
                    if ((iaprefix->getAddress() == lease_->addr_) &&
                        (iaprefix->getLength() == lease_->prefixlen_)) {
                        boost::shared_ptr<Option6IA> ia_pd(new Option6IA(D6O_IA_PD, ia->getIAID()));
                        ia_pd->addOption(iaprefix);
                        for (auto const& other_opt_it : opts) {
                            if (other_opt_it.second->getType() == D6O_IAADDR ||
                                other_opt_it.second->getType() == D6O_IAPREFIX) {
                                continue;
                            }
                            ia_pd->addOption(other_opt_it.second);
                        }
                        return (ia_pd);
                    }
                }
            }
        }
        return (OptionPtr());
    }

private:
    /// @brief The lease used to match packet options.
    Lease6Ptr lease_;
};

/// @brief Filter all IA_PD so that no option is matched by the expression.
class TokenFilterIA_PD : public virtual TokenOption {
public:
    /// @brief Constructor.
    ///
    /// @param rep_type Token representation type.
    TokenFilterIA_PD(const RepresentationType& rep_type) : TokenOption(D6O_IA_PD, rep_type) {
    }

    /// @brief Get no option regardless of what the packet contains.
    ///
    /// @param pkt The packet containing options.
    /// @return Always return null option.
    virtual OptionPtr getOption(Pkt&) {
        return (OptionPtr());
    }
};

/// @brief Filter the IA_PD (25) option containing the OPTION_IAPREFIX (25)
/// option matching the respective lease. Used when filtering sub-options.
class TokenLeaseIA_PDSuboption : public virtual TokenLeaseIA_PD, public virtual TokenSubOption {
public:
    /// @brief Constructor.
    ///
    /// @param lease The lease used to match any OPTION_IAPREFIX option in the
    /// IA_PD packet options.
    /// @param rep_type Token representation type.
    TokenLeaseIA_PDSuboption(const Lease6Ptr& lease, const RepresentationType& rep_type)
    : TokenOption(D6O_IA_PD, rep_type), TokenLeaseIA_PD(lease, rep_type),
      TokenSubOption(D6O_IA_PD, D6O_IAPREFIX, rep_type) {
    }

    /// @brief Get the IA_PD (25) option containing the OPTION_IAPREFIX (25)
    /// option matching the respective lease.
    ///
    /// @param pkt The packet containing options.
    /// @return A copy of the IA_PD option containing only one OPTION_IAPREFIX
    /// option (but all other options of different type) matching the
    /// respective lease or null if none exists.
    virtual OptionPtr getOption(Pkt& pkt) {
        return (TokenLeaseIA_PD::getOption(pkt));
    }

    /// @brief Evaluate the expression using the @ref TokenSubOption
    /// implementation.
    ///
    /// @param pkt specified parent option will be extracted from this packet
    /// @param values value of the sub-option will be pushed here (or "")
    /// @return 0 which means evaluate next token if any.
    unsigned evaluate(Pkt& pkt, ValueStack& values) {
        return (TokenSubOption::evaluate(pkt, values));
    }
};

/// @brief Filter all IA_PD so that no sub-option is matched by the expression.
class TokenFilterIA_PDSuboption : public virtual TokenFilterIA_PD, public virtual TokenSubOption {
public:
    /// @brief Constructor.
    ///
    /// @param rep_type Token representation type.
    TokenFilterIA_PDSuboption(const RepresentationType& rep_type)
    : TokenOption(D6O_IA_PD, rep_type), TokenFilterIA_PD(rep_type),
      TokenSubOption(D6O_IA_PD, D6O_IAPREFIX, rep_type) {
    }

    /// @brief Get no option regardless of what the packet contains.
    ///
    /// @param pkt The packet containing options.
    /// @return Always return null option.
    virtual OptionPtr getOption(Pkt& pkt) {
        return (TokenFilterIA_PD::getOption(pkt));
    }

    /// @brief Evaluate the expression using the @ref TokenSubOption
    /// implementation.
    ///
    /// @param pkt specified parent option will be extracted from this packet
    /// @param values value of the sub-option will be pushed here (or "")
    /// @return 0 which means evaluate next token if any.
    unsigned evaluate(Pkt& pkt, ValueStack& values) {
        return (TokenSubOption::evaluate(pkt, values));
    }
};

} // namespace dhcp
} // namespace isc

/// @brief Replace TokenOption and TokenSubOption expression tokens with the
/// IA_NA (3) option containing the OPTION_IAADDR (5) option matching the
/// respective lease.
///
/// @param expression The expression that needs to be updated with filtering
/// tokens.
/// @param lease The lease used to match any OPTION_IAADDR option in the IA_NA
/// packet options.
void filterLeaseIA_NA(isc::dhcp::Expression& expression, const Lease6Ptr& lease) {
    for (size_t i = 0; i < expression.size(); ++i) {
        boost::shared_ptr<TokenSubOption> suboption = boost::dynamic_pointer_cast<TokenSubOption>(expression[i]);
        if (suboption) {
            if ((suboption->getCode() == D6O_IA_NA) && (suboption->getSubCode() == D6O_IAADDR)) {
                expression[i] = TokenPtr(new TokenLeaseIA_NASuboption(lease, suboption->getRepresentation()));
                continue;
            }
            if ((suboption->getCode() == D6O_IA_PD) && (suboption->getSubCode() == D6O_IAPREFIX)) {
                expression[i] = TokenPtr(new TokenFilterIA_PDSuboption(suboption->getRepresentation()));
                continue;
            }
        }
        boost::shared_ptr<TokenOption> option = boost::dynamic_pointer_cast<TokenOption>(expression[i]);
        if (option) {
            if (option->getCode() == D6O_IA_NA) {
                expression[i] = TokenPtr(new TokenLeaseIA_NA(lease, option->getRepresentation()));
                continue;
            }
            if (option->getCode() == D6O_IA_PD) {
                expression[i] = TokenPtr(new TokenFilterIA_PD(option->getRepresentation()));
                continue;
            }
        }
    }
}

/// @brief Replace TokenOption and TokenSubOption expression tokens with the
/// IA_PD (25) option containing the OPTION_IAPREFIX (25) option matching the
/// respective lease.
///
/// @param expression The expression that needs to be updated with filtering
/// tokens.
/// @param lease The lease used to match any OPTION_IAPREFIX option in the IA_PD
/// packet options.
void filterLeaseIA_PD(isc::dhcp::Expression& expression, const Lease6Ptr& lease) {
    for (size_t i = 0; i < expression.size(); ++i) {
        boost::shared_ptr<TokenSubOption> suboption = boost::dynamic_pointer_cast<TokenSubOption>(expression[i]);
        if (suboption) {
            if ((suboption->getCode() == D6O_IA_NA) && (suboption->getSubCode() == D6O_IAADDR)) {
                expression[i] = TokenPtr(new TokenFilterIA_NASuboption(suboption->getRepresentation()));
                continue;
            }
            if ((suboption->getCode() == D6O_IA_PD) && (suboption->getSubCode() == D6O_IAPREFIX)) {
                expression[i] = TokenPtr(new TokenLeaseIA_PDSuboption(lease, suboption->getRepresentation()));
                continue;
            }
        }
        boost::shared_ptr<TokenOption> option = boost::dynamic_pointer_cast<TokenOption>(expression[i]);
        if (option) {
            if (option->getCode() == D6O_IA_NA) {
                expression[i] = TokenPtr(new TokenFilterIA_NA(option->getRepresentation()));
                continue;
            }
            if (option->getCode() == D6O_IA_PD) {
                expression[i] = TokenPtr(new TokenLeaseIA_PD(lease, option->getRepresentation()));
                continue;
            }
        }
    }
}

/// @brief Replace TokenOption and TokenSubOption expression tokens for all
/// IA_NA and IA_PD options and sub-options filtering by the current lease.
///
/// @param expression The expression which is updated to contain only
/// TokenOption and TokenSubOption expression tokens for IA_NA or IA_PD
/// which have an OPTION_IAADDR or an OPTION_IAPREFIX that matches the
/// respective lease.
/// @param lease The lease used to match any OPTION_IAADDR or OPTION_IAPREFIX
/// option in the packet.
void replaceTokensForLease(isc::dhcp::ExpressionPtr& expression,
                           const Lease6Ptr& lease) {
    // Copy the expression so that is can be safely modified.
    expression.reset(new isc::dhcp::Expression(*expression));
    if (lease->type_ == Lease::TYPE_NA) {
        filterLeaseIA_NA(*expression, lease);
    } else if (lease->type_ == Lease::TYPE_PD) {
        filterLeaseIA_PD(*expression, lease);
    }
}

/// @brief Create custom log entry for the current lease.
///
/// @param handle CalloutHandle which provides access to context.
/// @param query The query received by the server.
/// @param response The response of the server.
/// @param lease The current lease generating this log entry.
/// @param [out] value The value of the custom log entry after parser execution.
bool getCustomEntry(const Pkt6Ptr& query, const Pkt6Ptr& response,
                    const Lease6Ptr& lease, std::string& value) {
    bool using_custom_format = false;

    auto expression = BackendStoreFactory::instance()->getRequestFormatExpression();
    if (expression && query) {
        replaceTokensForLease(expression, lease);

        value = evaluateString(*expression, *query);
        using_custom_format = true;
    }

    expression = BackendStoreFactory::instance()->getResponseFormatExpression();
    if (expression && response) {
        replaceTokensForLease(expression, lease);

        value += evaluateString(*expression, *response);
        using_custom_format = true;
    }

    return (using_custom_format);
}

/// @brief Creates legal store entry for a DHCPv6 Lease.
///
/// Creates an entry based on the given DHCPv6 queries and corresponding
/// DHCPv6 lease.  The entry is returned as a single string with no embedded
/// EOL markers, a prepended timestamp and has the following sections:
///
///  "<timestamp><address><duration><device-id>{relay-info}*{user-context}*"
///
/// Where:
///     - timestamp - the current date and time the log entry was written
///     in "%Y-%m-%d %H:%M:%S %Z" strftime format.
///     - address - the leased IPv6 address or prefix given out and
///     whether it was assigned or renewed.
///     - duration - the lease lifetime expressed as in days (if present),
///     hours, minutes and seconds.  A lease lifetime of 0xFFFFFFFF will be
///     denoted with the text "infinite duration".
///     - device-id - the client's DUID and hardware address (if present)
///     - relay-info - for relayed packets the content of relay agent messages,
///     remote id and subscriber id options (x and xx) if present.
///     - user-context - the optional user context.
///
///     For example (on multiple lines for readibility):
/// @code
///  "2018-01-06 01:02:03 PST Address:2001:db8:1:: has been assigned
///  for 0 hrs 11 mins 53 secs to a device with DUID:
///  17:34:e2:ff:09:92:54 and hardware address: hwtype=1
///  08:00:2b:02:3f:4e (from Raw Socket) connected via relay at
///  address: fe80::abcd for client on link address: 3001::1, hop
///  count: 1, identified by remote-id: 01:02:03:04:0a:0b:0c:0d:0e:0f
///  and subscriber-id: 1a:2b:3c:4d:5e:6f"
/// @endcode
///
/// @param query DHCPv6 query packet for which the lease was generated
/// @param response DHCPv6 response packet
/// @param lease DHCPv6 lease for which the entry should be created
/// @param action Kind of event to log.
std::string genLease6Entry(const Pkt6Ptr& query,
                           const Pkt6Ptr& response,
                           const Lease6Ptr& lease,
                           const Action& action) {
    std::string value;
    if (getCustomEntry(query, response, lease, value)) {
        return (value);
    }

    std::stringstream stream;

    // <address>
    if (lease->type_ != Lease::TYPE_PD) {
        stream << "Address: " << lease->addr_;
    } else {
        stream << "Prefix: " << lease->addr_ << "/" << static_cast<int>(lease->prefixlen_);
    }

    stream << " has been " << actionToVerb(action);

    if (action != Action::RELEASE) {
        // <duration>
        stream << " for " << BackendStore::genDurationString(lease->valid_lft_) << " to";
    } else {
        stream << " from";
    }

    // <device-id>
    stream << " a device with DUID: " << lease->duid_->toText();

    if (lease->hwaddr_) {
        stream << " and hardware address: " << lease->hwaddr_->toText()
               << " (from " << hwaddrSourceToString(lease->hwaddr_->source_) << ")";
    }

    // Is it via relay(s)?
    if (query->relay_info_.size()) {
        const Pkt6::RelayInfo& server_relay = query->relay_info_[0];
        stream << " connected via relay at address: " << server_relay.peeraddr_.toText()
               << " for client on link address: " << server_relay.linkaddr_.toText()
               << ", hop count: " << static_cast<int>(server_relay.hop_count_);

        std::ostringstream idstream;
        // Look for the remote-id option
        OptionPtr opt = query->getAnyRelayOption(D6O_REMOTE_ID,
                                                 Pkt6::RELAY_SEARCH_FROM_CLIENT);
        if (opt) {
            const OptionBuffer id = opt->getData();
            if (!id.empty()) {
                idstream << "remote-id: " << BackendStore::vectorHexDump(id);

                if (str::isPrintable(id)) {
                    idstream << " (" << BackendStore::vectorDump(id) << ")";
                }
            }
        }

        // Look for the subscriber-id option
        opt = query->getAnyRelayOption(D6O_SUBSCRIBER_ID,
                                       Pkt6::RELAY_SEARCH_FROM_CLIENT);
        if (opt) {
            const OptionBuffer id = opt->getData();
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

        // Look for the interface-id option
        std::ostringstream location;
        opt = query->getAnyRelayOption(D6O_INTERFACE_ID,
                                       Pkt6::RELAY_SEARCH_FROM_CLIENT);
        if (opt) {
            const OptionBuffer id = opt->getData();
            if (!id.empty()) {
                if (!idstream.str().empty()) {
                    idstream << " and ";
                }

                location << "interface-id: " << BackendStore::vectorHexDump(id);

                if (str::isPrintable(id)) {
                    location << " (" << BackendStore::vectorDump(id) << ")";
                }
            }
        }

        if (!location.str().empty()) {
            stream << ", connected at location " << location.str();
        }

    }

    ConstElementPtr ctx = lease->getContext();
    if (ctx) {
        stream << ", context: " << ctx->str();
    }

    return (stream.str());
}

/// @brief Produces an DHCPv6 legal log entry from a callout handle.
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
int legalLog6Handler(CalloutHandle& handle, const Action& action) {
    if (!BackendStoreFactory::instance()) {
        LOG_ERROR(legal_log_logger, LEGAL_LOG_LEASE6_NO_LEGAL_STORE);
        return (1);
    }

    // Fetch the client's packet and the lease callout arguments.
    Pkt6Ptr query;
    handle.getArgument("query6", query);

    Pkt6Ptr response;
    handle.getArgument("response6", response);

    Lease6Ptr lease;
    handle.getContext("lease6", lease);

    if (!lease) {
        return (0);
    }

    ConstCfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    try {
        ConstSubnet6Ptr subnet = cfg->getBySubnetId(lease->subnet_id_);

        if (!isLoggingDisabled(subnet)) {
            BackendStoreFactory::instance()->writeln(genLease6Entry(query, response,
                                                             lease, action),
                                              genLease6Addr(lease));
        }

    } catch (const std::exception& ex) {
        LOG_ERROR(legal_log_logger, LEGAL_LOG_LEASE6_WRITE_ERROR)
                  .arg(ex.what());
        return (1);
    }

    return (0);
}

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief This callout is called at the "pkt6_receive" hook.
///
/// Creates context with empty "lease6" value.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt6_receive(CalloutHandle& handle) {
    handle.setContext("lease6", Lease4Ptr());
    handle.setContext("leases6", Lease6CollectionPtr());
    handle.setContext("deleted_leases6", Lease6CollectionPtr());
    return (0);
}

/// @brief This callout is called at the "leases6_committed" hook.
///
/// Stores the leases so that the logging option stored on the subnet context
/// can be available on pkt6_send hook.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int leases6_committed(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Lease6CollectionPtr leases;
    handle.getArgument("leases6", leases);
    handle.setContext("leases6", leases);

    Lease6CollectionPtr deleted_leases;
    handle.getArgument("deleted_leases6", deleted_leases);
    handle.setContext("deleted_leases6", deleted_leases);
    return (0);
}

/// @brief This callout is called at the "pkt6_send" hook.
///
/// Generates an entry in the legal log for a lease renewal if
/// the callout context values "leases6" and "deleted_leases6" are not empty.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt6_send(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Lease6CollectionPtr leases;
    handle.getContext("leases6", leases);

    int current = 0;
    int result = current;

    if (leases) {
        for (auto const& lease : *leases) {
            handle.setContext("lease6", lease);
            current = legalLog6Handler(handle, Action::ASSIGN);
            if (current) {
                result = current;
            }
        }
    }

    handle.getContext("deleted_leases6", leases);

    if (leases) {
        for (auto const& lease : *leases) {
            handle.setContext("lease6", lease);
            current = legalLog6Handler(handle, Action::RELEASE);
            if (current) {
                result = current;
            }
        }
    }

    return (result);
}

/// @brief This callout is called at the "lease6_release" hook.
///
/// Generates an entry in the legal log for a lease release if
/// the callout context values "leases6" and "deleted_leases6" are not empty.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease6_release(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Lease6Ptr lease;
    handle.getArgument("lease6", lease);

    Lease6CollectionPtr leases(new Lease6Collection());
    handle.setContext("leases6", leases);

    Lease6CollectionPtr deleted_leases(new Lease6Collection());
    deleted_leases->push_back(lease);
    handle.setContext("deleted_leases6", deleted_leases);

    return (0);
}

/// @brief This callout is called at the "lease6_decline" hook.
///
/// Generates an entry in the legal log for a lease decline if
/// the callout context values "leases6" and "deleted_leases6" are not empty.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int lease6_decline(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Lease6Ptr lease;
    handle.getArgument("lease6", lease);

    Lease6CollectionPtr leases(new Lease6Collection());
    handle.setContext("leases6", leases);

    Lease6CollectionPtr deleted_leases(new Lease6Collection());
    deleted_leases->push_back(lease);
    handle.setContext("deleted_leases6", deleted_leases);

    return (0);
}

} // end extern "C"
