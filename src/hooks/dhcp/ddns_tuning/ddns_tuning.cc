// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ddns_tuning.h>
#include <ddns_tuning_log.h>
#include <eval/token.h>
#include <eval/eval_context.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace isc::log;
using namespace isc::util;
using namespace std;

namespace isc {
namespace ddns_tuning {

DdnsTuningImpl::~DdnsTuningImpl() {
}

void DdnsTuningImpl::configure(isc::data::ConstElementPtr params) {
    if (!params) {
        isc_throw(BadValue, "params must not be null");
        return;
    }

    if (params->getType() != Element::map) {
        isc_throw(BadValue, "params must be an Element::map");
        return;
    }

    // Discard cached expressions, some or all may be stale.
    flushCache(false);

    // Handle global hostname-expr if it exists.
    ConstElementPtr json = params->get("hostname-expr");
    if (json) {
        if (json->getType() != Element::string) {
            isc_throw(BadValue, "'hostname-expr' must be a string");
        }

        std::string expression_str = json->stringValue();
        if (!expression_str.empty()) {
            // Parse and cache the expression.
            try {
                ExpressionPtr global_expr = parseExpression(expression_str);
                setGlobalHostnameExpression(global_expr);
                LOG_INFO(ddns_tuning_logger, DDNS_TUNING_GLOBAL_EXPR_SET).arg(expression_str);
            } catch (const std::exception& ex) {
                isc_throw(BadValue, "global expression parsing failed: " << ex.what());
            }
        }
    }
}

void
DdnsTuningImpl::setHostnameExpression(const SubnetID& subnet_id, ExpressionPtr& expression) {
    subnet_exprs_.cacheExpression(subnet_id, expression);
}

ExpressionPtr
DdnsTuningImpl::getHostnameExpression(const SubnetID& subnet_id) {
    ExpressionPtr expression;
    static_cast<void>(subnet_exprs_.findExpression(subnet_id, expression));
    return (expression);
}

ExpressionPtr
DdnsTuningImpl::getGlobalHostnameExpression() {
    return (getHostnameExpression(SUBNET_ID_GLOBAL));
}

void DdnsTuningImpl::setGlobalHostnameExpression(ExpressionPtr& expression) {
    setHostnameExpression(SUBNET_ID_GLOBAL, expression);
}

ExpressionPtr
DdnsTuningImpl::fetchScopedHostnameExpression(ConstSubnetPtr subnet) {
    if (!subnet) {
        isc_throw(Unexpected, "fetchScopedHostnameExpression: subnet cannot be empty");
    }

    ExpressionPtr expression;
    bool found = false;

    // If the subnet has been modified since we last flushed, then we need to flush the
    // cache and return not found.  This will force us to update the subnet's expression.
    if (subnet->getModificationTime() > subnet_exprs_.getLastFlushTime()) {
        flushCache();
    } else {
        // Subnet hasn't changed since last flush, so fetch its cached expression (if one).
        found = subnet_exprs_.findExpression(subnet->getID(), expression);
    }

    // If there's no entry for the subnet, cache an entry for it.
    if (!found) {
        expression = cacheExpression(subnet);
    }

    // We found an expression for the subnet return it. It is possible for the expression
    // to be present but empty.  We return empty expressions to allow subnets to suppress
    // a global level expression.
    if (expression) {
        LOG_DEBUG(ddns_tuning_logger, DBGLVL_TRACE_BASIC, DDNS_TUNING_SUBNET_EXPR_CACHED)
                .arg(subnet->toText());
        return (expression);
    }

    // Return the global expression (may be empty);
    return (getGlobalHostnameExpression());
}

ExpressionPtr DdnsTuningImpl::cacheExpression(ConstSubnetPtr subnet) {
    ExpressionPtr expression;

    // Check if there's a subnet-specific expression defined in the
    // user context.  If it's there parse it, cache it, and return it.
    auto ctx = subnet->getContext();
    if (ctx) {
        // Look for ddns-tuning map within user-context.
        ConstElementPtr json = ctx->get("ddns-tuning");

        // If it's there look for hostname-expr within ddns-tuning.
        if (json && json->getType() == Element::map) {
            json = json->get("hostname-expr");
            if (json && json->getType() == Element::string) {
                try {
                    // Get either the parsed expression specified by the subnet via
                    // user-context::hostname-expr or an empty pointer.
                    LOG_DEBUG(ddns_tuning_logger, DBGLVL_TRACE_BASIC,
                              DDNS_TUNING_SUBNET_EXPRESSION_PARSE)
                            .arg(json->stringValue())
                            .arg(subnet->toText());
                    expression = parseExpression(json->stringValue());
                } catch (const std::exception& ex) {
                    // Cache an empty pointer so we don't retry each time the subnet is presented.
                    setHostnameExpression(subnet->getID(), expression);
                    isc_throw(BadValue, "hostname expression for subnet: " << subnet->toText()
                              << " parsing failed: " << ex.what());
                }
            }
        }
    }

    // Cache whatever we have, an expression or an empty pointer.
    setHostnameExpression(subnet->getID(), expression);
    return (expression);
}

ExpressionPtr
DdnsTuningImpl::parseExpression(const std::string& expression_str) const {
    ExpressionPtr expr;
    try {
        // We allow empty expressions so higher precedence scopes may
        // override lower precedence scopes.
        if (expression_str.empty()) {
            expr.reset(new Expression());
        } else {
            EvalContext eval_ctx(family_ == AF_INET ? Option::V4 : Option::V6);
            eval_ctx.parseString(expression_str, EvalContext::PARSER_STRING);
            expr.reset(new Expression(eval_ctx.expression_));
        }
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "error parsing expression: ["
                  << expression_str << "] : " << ex.what());
    }

    return (expr);
}

std::string
DdnsTuningImpl::calculateHostname(PktPtr query, ConstSubnetPtr subnet) {
    // Look for a hostname expression first by subnet, then globally.
    auto hostname_expr = fetchScopedHostnameExpression(subnet);

    // If there isn't an expression or the expression is empty
    // return an empty string.
    if (!hostname_expr || (hostname_expr->empty())) {
        return (std::string(""));
    }

    // We have an expression use it to calculate the hostname.
    return (isc::dhcp::evaluateString(*hostname_expr, *query));
}

void
DdnsTuningImpl::flushCache(bool preserve_global /* = true */) {
    ExpressionPtr global_expr;
    if (preserve_global) {
        global_expr = getGlobalHostnameExpression();
    }

    subnet_exprs_.clear();
    if (global_expr) {
        setGlobalHostnameExpression(global_expr);
    }
}

size_t
DdnsTuningImpl::getCacheSize() {
    return (subnet_exprs_.size());
}

boost::posix_time::ptime
DdnsTuningImpl::getLastFlushTime() {
    return (subnet_exprs_.getLastFlushTime());
}

} // end of namespace ddns_tuning
} // end of namespace isc
