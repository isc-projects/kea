// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file load_unload.cc Defines the load and unload hooks library functions.

#include <config.h>

#include <cc/data.h>
#include <dhcp/option.h>
#include <dhcpsrv/cfgmgr.h>
#include <eval/token.h>
#include <eval/eval_context.h>
#include <hooks/hooks.h>
#include <process/daemon.h>
#include <flex_id.h>
#include <flex_id_log.h>

using namespace isc;
using namespace hooks;
using namespace flex_id;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;

namespace { // anonymous namespace.

/// @brief Check if the expression provided as text will parse.
///
/// @param v6 Indicates if the expression refers to IPv6 or IPv4 case.
/// @param expr Expression in the textual form.
bool checkExpression(bool v6, const std::string& expr) {
    try {
        EvalContext eval_ctx(v6 ? Option::V6 : Option::V4);
        eval_ctx.parseString(expr, EvalContext::PARSER_STRING);
        return (true);
    } catch (const std::exception& ex) {
        LOG_ERROR(flex_id_logger, FLEX_ID_EXPRESSION_PARSE_FAILED)
            .arg(expr)
            .arg(ex.what());
        return (false);
    }
}

} // end of anonymous namespace.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief Called by the Hooks library manager when the library is loaded.
///
/// @param handle library handle passed for new library being loaded.
///
/// @return 0 upon success, non-zero if the parameters passed to flex-id
///         library are incorrect.
int load(LibraryHandle& handle) {
    // non-zero indicates an error.
    int ret_val = 0;

    try {
        // Make the hook library not loadable by d2 or ca.
        bool v6 = (CfgMgr::instance().getFamily() == AF_INET6);
        const std::string& proc_name = Daemon::getProcName();
        const std::string& expected_proc_name =
            (v6 ? "kea-dhcp6" : "kea-dhcp4");
        if (proc_name != expected_proc_name) {
            isc_throw(Unexpected, "Bad process name: " << proc_name
                      << ", expected " << expected_proc_name);
        }

        // identifier-expression is mandatory
        data::ConstElementPtr param = handle.getParameter("identifier-expression");
        if (!param) {
            LOG_ERROR(flex_id_logger, FLEX_ID_EXPRESSION_NOT_DEFINED);
            return (1);
        }

        // It must be a string...
        if (param->getType() != Element::string) {
            LOG_ERROR(flex_id_logger, FLEX_ID_EXPRESSION_INVALID_JSON_TYPE)
                .arg(Element::typeToName(param->getType()));
            return (1);
        }

        // ... and shouldn't be empty.
        std::string expr = param->stringValue();
        if (expr.empty()) {
            // Ok, we can continue without the expression, but it's just useless
            // to have this lib loaded. Nevertheless, there may be cases when
            // user temporarily changes the expression to empty string to
            // troubleshoot something.
            LOG_WARN(flex_id_logger, FLEX_ID_EXPRESSION_EMPTY);
        } else if (!checkExpression(v6, expr)) {
            // The error was logged.
            return (1);
        }

        // replace-client-id indicates if flexible identifier should be used to
        // replace original client identifier (or DUID) within the client query.
        bool replace_client_id = false;
        data::ConstElementPtr param_replace = handle.getParameter("replace-client-id");
        if (param_replace) {
            // It must be a boolean value.
            if (param_replace->getType() != Element::boolean) {
                LOG_ERROR(flex_id_logger, FLEX_ID_REPLACE_CLIENT_ID_JSON_TYPE)
                    .arg(Element::typeToName(param_replace->getType()));
                return (1);
            }

            replace_client_id = param_replace->boolValue();
        }

        // ignore-iaid indicates if iaid should be ignored.
        bool ignore_iaid = false;
        if (v6) {
            data::ConstElementPtr param_ignore = handle.getParameter("ignore-iaid");
            if (param_ignore) {
                // It must be a boolean value.
                if (param_ignore->getType() != Element::boolean) {
                    LOG_ERROR(flex_id_logger, FLEX_ID_IGNORE_IAID_JSON_TYPE)
                        .arg(Element::typeToName(param_ignore->getType()));
                    return (1);
                }

                ignore_iaid = param_ignore->boolValue();
            }
        }

        // Remove any old expressions that may have been stored.
        clearConfiguration();

        // Store specified expression.
        storeConfiguration(v6, expr, replace_client_id, ignore_iaid);

        if (ignore_iaid) {
            LOG_WARN(flex_id_logger, FLEX_ID_IGNORE_IAID_ENABLED);
        }
    } catch (const std::exception& ex) {
        // Log the error and return failure.
        LOG_ERROR(flex_id_logger, FLEX_ID_LOAD_ERROR)
            .arg(ex.what());
        ret_val = 1;
    }

    return (ret_val);
}

/// @brief Called by the Hooks library manager when the library is unloaded.
///
/// @return Always 0.
int unload() {
    LOG_INFO(flex_id_logger, FLEX_ID_UNLOAD);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

}
