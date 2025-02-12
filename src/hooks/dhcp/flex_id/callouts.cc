// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file callouts.cc Defines callouts used to generate flexible identifier
///                   values.

#include <config.h>
#include <util/str.h>
#include <asiolink/asio_wrapper.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/option6_ia.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/host.h>
#include <hooks/hooks.h>
#include <eval/evaluate.h>
#include <eval/token.h>
#include <eval/eval_context.h>
#include <flex_id_log.h>
#include <algorithm>
#include <sstream>

using namespace isc;
using namespace dhcp;
using namespace hooks;
using namespace util;
using namespace log;
using namespace std;
using namespace flex_id;

namespace {

bool flex_id_apply_to_leases = false;
Expression flex_id_expr;
bool flex_id_ignore_iaid = false;

}

namespace isc {
namespace flex_id {

/// @brief Parses expression provided as text.
///
/// @param v6 Indicates if the expression refers to IPv6 or IPv4 case.
/// @param expr Expression in the textual form.
void parseAndStoreExpression(bool v6, const std::string& expr) {
    try {
        EvalContext eval_ctx(v6 ? Option::V6 : Option::V4);
        eval_ctx.parseString(expr, EvalContext::PARSER_STRING);
        flex_id_expr = eval_ctx.expression_;
    } catch (const std::exception& ex) {
        // Append position if there is a failure.
        isc_throw(Unexpected,
                  "expression: [" << expr <<  "] error: " << ex.what() );
    }
}

void storeConfiguration(bool v6, const std::string& expr,
                        const bool apply_to_leases,
                        const bool ignore_iaid) {
    flex_id_apply_to_leases = apply_to_leases;
    if (!expr.empty()) {
        parseAndStoreExpression(v6, expr);
    }
    flex_id_ignore_iaid = ignore_iaid;
}

void clearConfiguration() {
    flex_id_apply_to_leases = false;
    flex_id_expr.clear();
    flex_id_ignore_iaid = false;
}

/// @brief Retrieves flexible identifier from the context or computes it.
///
/// @param callout_handle Callout handle.
/// @param expression Expression to be applied for evaluation against the packet.
/// @param pkt Packet against which expression should be evaluated.
/// @param [out] id Reference to the storage into which the flexible identifier
/// should be stored after evaluation.
template<typename PacketType>
void retrieveFlexId(CalloutHandle& callout_handle, const Expression& expression,
                    PacketType& pkt, std::vector<uint8_t>& id) {
    try {
        // Flexible identifier could have been already computed by other callout.
        // Let's try to retrieve it.
        callout_handle.getContext("id_value", id);

    } catch (const NoSuchCalloutContext& ex) {
        // Calculate the flexible identifier.
        std::string value = evaluateString(expression, pkt);
        if (str::isPrintable(value)) {
            LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC, FLEX_ID_EXPRESSION_EVALUATED)
                .arg(value).arg(value.size());
        } else {
            ostringstream repr;
            repr << hex;
            for (const char& ch : value) {
                repr << setw(2) << setfill('0') << static_cast<unsigned>(ch);
            }
            LOG_INFO(flex_id_logger, FLEX_ID_EXPRESSION_EVALUATED_NP)
                .arg(repr.str()).arg(value.size());
        }

        // ... and prepare data to be sent back to Kea.
        id.resize(value.size());
        if (!id.empty()) {
            std::copy(value.begin(), value.end(), id.begin());

            // Remember newly computed values for other callouts.
            callout_handle.setContext("id_value", id);

            DUID duid(id);
            LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC, FLEX_ID_EXPRESSION_HEX)
                .arg(duid.toText());
        }
    }
}

}
}

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief  This callout is called at the "host4_identifier" hook.
///
/// It retrieves v4 packet and then generates flexible identifier for it.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int host4_identifier(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    if (flex_id_expr.empty()) {
        // Expression not specified. Nothing to do here.
        return (0);
    }

    // Get the parameters.
    Pkt4Ptr pkt;
    Host::IdentifierType type;
    std::vector<uint8_t> id;
    handle.getArgument("query4", pkt);
    handle.getArgument("id_type", type);
    handle.getArgument("id_value", id);

    // Calculate flexible identifier from the expression and the contents of
    // the packet.
    retrieveFlexId(handle, flex_id_expr, *pkt, id);
    if (!id.empty()) {
        type = Host::IDENT_FLEX;

        handle.setArgument("id_value", id);
        handle.setArgument("id_type", type);
    }

    return (0);
}

/// @brief This callout is called at "pkt4_receive" hook point.
///
/// It replaces existing or inserts new client identifier option into a
/// received packet using flexible identifier value.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_receive(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    if (!flex_id_apply_to_leases || flex_id_expr.empty()) {
        // Expression not specified or flexible identifier should not be used
        // for lease identification. Nothing to do here.
        return (0);
    }

    // Packet will be needed to evaluate expression.
    Pkt4Ptr pkt;
    handle.getArgument("query4", pkt);

    // Retrieve already stored flex-id (if computed by other callouts for this
    // packet) or compute it here.
    std::vector<uint8_t> id;
    retrieveFlexId(handle, flex_id_expr, *pkt, id);

    // Flex-id is required to proceed.
    if (!id.empty()) {
        // Remember client identifier supplied by the DHCP client and remove
        // it from the packet.
        OptionPtr client_id = pkt->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
        if (client_id) {
            handle.setContext("client_identifier", client_id);
            static_cast<void>(pkt->delOption(DHO_DHCP_CLIENT_IDENTIFIER));
        }

        // Use 0 as a client identifier type.
        OptionBuffer buf(1, 0);

        // Create new client identifier from the flex-id.
        buf.insert(buf.end(), id.begin(), id.end());
        OptionPtr new_client_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, buf));
        pkt->addOption(new_client_id);

        ClientId cid(buf);
        LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC, FLEX_ID_USED_AS_CLIENT_ID)
            .arg(cid.toText());
    }

    return (0);
}

/// @brief This callout is called at "pkt4_send" hook point.
///
/// It restores client identifier sent by the DHCP client and temporarily replaced
/// in the pkt4_receive callout to flex-id.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_send(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP) {
        return (0);
    }

    // There is nothing to do if flexible identifier is not to be used as client
    // identifier per configuration.
    if (!flex_id_apply_to_leases) {
        return (0);
    }

    // The first thing to do is to check whether the flex-id is in use. If not, there
    // might have been an error evaluating expression or the flex-id was empty. If so,
    // there is nothing to do.
    try {
        std::vector<uint8_t> id;
        handle.getContext("id_value", id);

    } catch (const NoSuchCalloutContext& ex) {
        return (0);
    }

    if (status == CalloutHandle::NEXT_STEP_SKIP) {
        isc_throw(InvalidOperation, "packet pack already handled");
    }

    Pkt4Ptr pkt;
    Pkt4Ptr response;
    handle.getArgument("query4", pkt);
    handle.getArgument("response4", response);

    OptionPtr old_client_id;
    try {
        handle.getContext("client_identifier", old_client_id);

    } catch (const NoSuchCalloutContext& ex) {
        // Ignore that the context  doesn't exist. We will examine old_client_id
        // value instead.
    }

    // Remove currently used client identifier (presumably flex-id value).
    static_cast<void>(response->delOption(DHO_DHCP_CLIENT_IDENTIFIER));

    // Add the client supplied client identifier into the outbound packet.
    if (old_client_id) {
        response->addOption(old_client_id);

        ClientId client_id(old_client_id->getData());
        LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC, FLEX_ID_RESTORE_CLIENT_ID)
            .arg(client_id.toText());
    }

    return (0);
}

/// @brief  This callout is called at the "host6_identifier" hook.
///
/// It retrieves the v6 packet and then generates flexible identifier for it.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int host6_identifier(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    if (flex_id_expr.empty()) {
        // Expression not specified. Nothing to do here.
        return (0);
    }

    // Get the parameters.
    Pkt6Ptr pkt;
    Host::IdentifierType type;
    std::vector<uint8_t> id;
    handle.getArgument("query6", pkt);
    handle.getArgument("id_type", type);
    handle.getArgument("id_value", id);

    // Calculate flexible identifier from the expression and the contents of
    // the packet.
    retrieveFlexId(handle, flex_id_expr, *pkt, id);
    if (!id.empty()) {
        type = Host::IDENT_FLEX;

        handle.setArgument("id_value", id);
        handle.setArgument("id_type", type);
    }

    return (0);
}

/// @brief This callout is called at "pkt6_receive" hook point.
///
/// It replaces existing or inserts new DUID into a received packet
/// using flexible identifier value.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt6_receive(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    // Packet will be needed to evaluate expression.
    Pkt6Ptr pkt;
    handle.getArgument("query6", pkt);

    if (flex_id_ignore_iaid) {
        uint32_t iana_count = 0;
        uint32_t iapd_count = 0;
        for (auto const& opt : pkt->options_) {
            switch (opt.second->getType()) {
                case D6O_IA_NA: {
                    iana_count++;
                    break;
                }
                case D6O_IA_PD: {
                    iapd_count++;
                    break;
                }
            }
        }
        handle.setContext("iana_count", iana_count);
        handle.setContext("iapd_count", iapd_count);
        if (iana_count > 1) {
            LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC,
                      FLEX_ID_IGNORE_IAID_NOT_APPLIED_ON_NA);
        }
        if (iapd_count > 1) {
            LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC,
                      FLEX_ID_IGNORE_IAID_NOT_APPLIED_ON_PD);
        }
        uint32_t iana_iaid = 0;
        uint32_t iapd_iaid = 0;
        if (iana_count == 1) {
            for (auto const& opt : pkt->options_) {
                switch (opt.second->getType()) {
                    case D6O_IA_NA: {
                        auto iana = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                        iana_iaid = iana->getIAID();
                        iana->setIAID(0);
                        LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC,
                                  FLEX_ID_IGNORE_IAID_APPLIED_ON_NA)
                                .arg(iana_iaid);
                        break;
                    }
                }
            }
            handle.setContext("iana_iaid", iana_iaid);
        }
        if (iapd_count == 1) {
            for (auto const& opt : pkt->options_) {
                switch (opt.second->getType()) {
                    case D6O_IA_PD: {
                        auto iapd = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                        iapd_iaid = iapd->getIAID();
                        iapd->setIAID(0);
                        LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC,
                                  FLEX_ID_IGNORE_IAID_APPLIED_ON_PD)
                                .arg(iapd_iaid);
                        break;
                    }
                }
            }
            handle.setContext("iapd_iaid", iapd_iaid);
        }
    }

    if (!flex_id_apply_to_leases || flex_id_expr.empty()) {
        // Expression not specified or flexible identifier should not be used
        // for lease identification. Nothing to do here.
        return (0);
    }

    // Retrieve already stored flex-id (if computed by other callouts for this
    // packet) or compute it here.
    std::vector<uint8_t> id;
    retrieveFlexId(handle, flex_id_expr, *pkt, id);

    // Flex-id is required to proceed.
    if (!id.empty()) {
        // Remember DUID supplied by the DHCP client and remove it from the
        // packet.
        OptionPtr opt_duid = pkt->getOption(D6O_CLIENTID);
        if (opt_duid) {
            handle.setContext("duid", opt_duid);
            static_cast<void>(pkt->delOption(D6O_CLIENTID));
        }

        // Use 0 as a DUID type. Since this is a synthesized value, we do not
        // want to use any of the currently existing DUID types (as of 2017,
        // values 1 through 4 are defined). Zero is a safe choice here.
        OptionBuffer buf(2, 0);

        // Create new DUID from the flex-id.
        buf.insert(buf.end(), id.begin(), id.end());
        OptionPtr new_duid(new Option(Option::V6, D6O_CLIENTID, buf));
        pkt->addOption(new_duid);

        DUID duid(buf);
        LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC, FLEX_ID_USED_AS_DUID)
            .arg(duid.toText());
    }

    return (0);
}

/// @brief This callout is called at "pkt6_send" hook point.
///
/// It restores DUID sent by the DHCP client and temporarily replaced in the
/// pkt6_receive callout to flex-id.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt6_send(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP) {
        return (0);
    }

    Pkt6Ptr pkt;
    Pkt6Ptr response;
    handle.getArgument("query6", pkt);
    handle.getArgument("response6", response);

    if (flex_id_ignore_iaid) {
        uint32_t iana_count = 0;
        uint32_t iapd_count = 0;
        handle.getContext("iana_count", iana_count);
        handle.getContext("iapd_count", iapd_count);
        if (iana_count == 1) {
            for (auto const& opt : response->options_) {
                switch (opt.second->getType()) {
                    case D6O_IA_NA: {
                        auto iana = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                        uint32_t iana_iaid = 0;
                        handle.getContext("iana_iaid", iana_iaid);
                        iana->setIAID(iana_iaid);
                        break;
                    }
                }
            }
        }
        if (iapd_count == 1) {
            for (auto const& opt : response->options_) {
                switch (opt.second->getType()) {
                    case D6O_IA_PD: {
                        auto iapd = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                        uint32_t iapd_iaid = 0;
                        handle.getContext("iapd_iaid", iapd_iaid);
                        iapd->setIAID(iapd_iaid);
                        break;
                    }
                }
            }
        }
    }

    // There is nothing to do if flexible identifier is not to be used as client
    // identifier per configuration.
    if (!flex_id_apply_to_leases) {
        return (0);
    }

    // The first thing to do is to check whether the flex-id is in use. If not, there
    // might have been an error evaluating expression or the flex-id was empty. If so,
    // there is nothing to do.
    try {
        std::vector<uint8_t> id;
        handle.getContext("id_value", id);

    } catch (const NoSuchCalloutContext& ex) {
        return (0);
    }

    if (status == CalloutHandle::NEXT_STEP_SKIP) {
        isc_throw(InvalidOperation, "packet pack already handled");
    }

    OptionPtr old_duid;
    try {
        handle.getContext("duid", old_duid);

    } catch (const NoSuchCalloutContext& ex) {
        // Ignore that the context doesn't exist. We will examine old_duid
        // value instead.
    }

    // Remove currently used DUID (presumably flex-id value).
    static_cast<void>(response->delOption(D6O_CLIENTID));

    // Add the client supplied client identifier into the outbound packet.
    if (old_duid) {
        response->addOption(old_duid);

        DUID duid(old_duid->getData());
        LOG_DEBUG(flex_id_logger, DBGLVL_TRACE_BASIC, FLEX_ID_RESTORE_DUID)
            .arg(duid.toText());
    }

    return (0);
}

} // end extern "C"
