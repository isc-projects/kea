// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file command_callouts.cc Defines lease4_select and lease4_renew callout functions.

#include <config.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/subnet.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <util/str.h>
#include <legal_log_log.h>
#include <dhcpsrv/backend_store_factory.h>
#include <rotating_file.h>
#include <subnets_user_context.h>

#include <sstream>
#include <unordered_set>

using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;
using namespace isc::legal_log;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief Fetch value for a string element if it is an element scope
///
/// Exception safe fetcher which looks for a string element with the
/// given name within an given element scope. Rather than throw if the
/// element is not found, it returns true if found, false if not.
///
/// @param arguments element scope to search, assumed to be a map
/// @param name name of the desired element
/// @param[out] value reference to a string in which the found value is
/// returned.  Will be set to "" if the element is not found.
///
/// @return true if the element was found, false if not
bool getOptionalString(ConstElementPtr& arguments, const string& name,
                       string& value) {
    value = "";
    try {
        value = SimpleParser::getString(arguments, name);
        return (true);
    } catch (...) {
        // we don't care why
    }

    return (false);
}

/// @brief Fetch value for a integer element if it is an element scope
///
/// Exception safe fetcher which looks for an integer element with the
/// given name within an given element scope. Rather than throw if the
/// element is not found, it returns true if found, false if not.
///
/// @param arguments element scope to search, assumed to be a map
/// @param name name of the desired element
/// @param[out] value reference to an integer in which the found value is
/// returned.  Will be set to 0 if the element is not found.
///
/// @return true if the element was found, false if not
bool getOptionalInt(ConstElementPtr& arguments, const string& name,
                    int64_t& value) {
    value = 0;
    try {
        value = SimpleParser::getInteger(arguments, name);
        return (true);
    } catch (...) {
        // we don't care why
    }

    return (false);
}

/// @brief Returns true if an element scope describes a prefix delegation
///
/// Searches the given scope of an lease type element, "type".  If it
/// exists and it's value is "IA_PD" or "2" return true, false otherwise.
///
/// @param arguments element scope to search, assumed to be a map
///
/// @return true if the scope describes a prefix delegation
bool isPrefix(ConstElementPtr arguments) {
    string type_str;
    if (getOptionalString(arguments, "type", type_str)) {
        return (type_str == "IA_PD" || type_str == "2");
    }

    return (false);
}

/// @brief Outputs text describing lease duration to a stream
///
/// Looks for either a lease valid lifetime or expiry from which to
/// generate the duration text using @ref
/// isc::legal_log::BackendStore::genDurationString().
///
/// @param os output stream to which the text is output
/// @param arguments element scope which may contain duration values
void addDuration(ostringstream& os, ConstElementPtr& arguments) {

    int64_t duration = 0;
    if (!getOptionalInt(arguments, "valid-lft", duration)) {
        int64_t expire = 0;
        if (getOptionalInt(arguments, "expire", expire)) {
            duration = expire - BackendStoreFactory::instance(managerID())->now().tv_sec;
        }
    }

    if (duration > 0) {
        os << " for " << BackendStore::genDurationString(duration);
    }
}

/// @brief Outputs text describing lease optional user context to a stream
///
/// Looks for an user context or a comment and display it
///
/// @param os output stream to which the text is output
/// @param arguments element scope which may contain user context or comment
void addContext(ostringstream& os, ConstElementPtr& arguments) {

    ConstElementPtr comment = arguments->get("comment");
    ConstElementPtr ctx = arguments->get("user-context");
    if (comment) {
        ElementPtr copied;
        if (ctx) {
            copied = copy(ctx, 0);
        } else {
            copied = Element::createMap();
        }
        copied->set("comment", comment);
        ctx = copied;
    }
    if (ctx) {
        os << ", context: " << ctx->str();
    }
}

/// @brief Check if command has optional subnet-id parameter and if it does,
/// check that the respective subnet has logging enabled.
///
/// @param arguments The command arguments.
///
/// @return true if logging is enabled (default), false otherwise.
bool checkLoggingEnabledSubnet4(ConstElementPtr& arguments) {
    // Check if the subnet identifier has been specified for the command.
    // In some cases it may be missing, i.e. lease4-del command, when deleting a
    // lease by an IP address.
    int64_t subnet_id_value = 0;
    if (getOptionalInt(arguments, "subnet-id", subnet_id_value) && (subnet_id_value > 0)) {
        // The subnet identifier is present and valid.
        SubnetID subnet_id = static_cast<SubnetID>(subnet_id_value);

        CfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
        // Get the subnet by id and if the subnet is present, check if its user
        // context to see if legal logging is enabled for this subnet.
        ConstSubnet4Ptr subnet = cfg->getBySubnetId(subnet_id);
        if (isLoggingDisabled(subnet)) {
            return (false);
        }
    }
    return (true);
}

/// @brief Handle lease4 related commands.
///
/// @param handle CalloutHandle which provides access to context.
/// @param name The command name.
/// @param arguments The command arguments.
/// @param response The command response.
int handleLease4Cmds(string& name, ConstElementPtr& arguments,
                     ConstElementPtr& /*response*/) {
    if (!BackendStoreFactory::instance(managerID())) {
        LOG_ERROR(legal_log_logger,
                  LEGAL_LOG_COMMAND_NO_LEGAL_STORE);
        return (1);
    }
    try {
        if (!checkLoggingEnabledSubnet4(arguments)) {
            return (0);
        }
        ostringstream os;
        ostringstream osa;
        string origin;
        getOptionalString(arguments, "origin", origin);
        if (origin == "ha-partner") {
            os << "HA partner";
        } else {
            os << "Administrator";
        }
        if ((name == "lease4-add") || name == "lease4-update") {
            if (name == "lease4-add") {
                os << " added a lease of address: ";
            } else {
                os << " updated information on the lease of address: ";
            }
            osa << SimpleParser::getString(arguments, "ip-address");
            os << SimpleParser::getString(arguments, "ip-address")
               << " to a device with hardware address: "
               << SimpleParser::getString(arguments, "hw-address");

            string client_id;
            if (getOptionalString(arguments, "client-id", client_id)) {
                os << ", client-id: " << client_id;
                // It is not uncommon to provide a printable client ID
                try {
                    auto bin = ClientId::fromText(client_id)->getClientId();
                    if (str::isPrintable(bin)) {
                        os << " (" << BackendStore::vectorDump(bin) << ")";
                    }
                } catch (...) {
                    // Ignore any error
                }
            }

            addDuration(os, arguments);
            addContext(os, arguments);
        } else if (name == "lease4-del") {
            string ip_address;
            if (getOptionalString(arguments, "ip-address", ip_address)) {
                osa << SimpleParser::getString(arguments, "ip-address");
                os << " deleted the lease for address: "
                   << SimpleParser::getString(arguments, "ip-address");
            } else {
                os << " deleted a lease for a device identified by: "
                   << SimpleParser::getString(arguments, "identifier-type")
                   << " of " << SimpleParser::getString(arguments, "identifier");
            }
        }

        BackendStoreFactory::instance(managerID())->writeln(os.str(), osa.str());
    } catch (const exception& ex) {
        LOG_ERROR(legal_log_logger, LEGAL_LOG_COMMAND_WRITE_ERROR)
                  .arg(ex.what());
        return (1);
    }
    return (0);
}

/// @brief Check if command has optional subnet-id parameter and if it does,
/// check that the respective subnet has logging enabled.
///
/// @param arguments The command arguments.
///
/// @return true if logging is enabled (default), false otherwise.
bool checkLoggingEnabledSubnet6(ConstElementPtr& arguments) {
    // Check if the subnet identifier has been specified for the command.
    // In some cases it may be missing, i.e. lease6-del command, when deleting a
    // lease by an IP address or prefix or lease6-bulk-apply command.
    int64_t subnet_id_value = 0;
    if (getOptionalInt(arguments, "subnet-id", subnet_id_value) && (subnet_id_value > 0)) {
        // The subnet identifier is present and valid.
        SubnetID subnet_id = static_cast<SubnetID>(subnet_id_value);

        CfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
        // Get the subnet by id and if the subnet is present, check if its user
        // context to see if legal logging is enabled for this subnet.
        ConstSubnet6Ptr subnet = cfg->getBySubnetId(subnet_id);
        if (isLoggingDisabled(subnet)) {
            return (false);
        }
    }
    return (true);
}

/// @brief Handle lease6 related commands.
///
/// @param name The command name.
/// @param arguments The command arguments.
/// @param response The command response.
int handleLease6Cmds(string& name, ConstElementPtr& arguments,
                     ConstElementPtr& response) {
    if (!BackendStoreFactory::instance(managerID())) {
        LOG_ERROR(legal_log_logger,
                  LEGAL_LOG_COMMAND_NO_LEGAL_STORE);
        return (1);
    }
    try {
        if (!checkLoggingEnabledSubnet6(arguments)) {
            return (0);
        }
        ostringstream os;
        ostringstream osa;
        string origin;
        getOptionalString(arguments, "origin", origin);
        if (origin == "ha-partner") {
            os << "HA partner";
        } else {
            os << "Administrator";
        }
        if ((name == "lease6-add") || name == "lease6-update") {
            if (name == "lease6-add") {
                os << " added a lease of";
            } else {
                os << " updated information on the lease of";
            }

            osa << SimpleParser::getString(arguments, "ip-address");
            if (isPrefix(arguments)) {
                os << " prefix: "
                   << SimpleParser::getString(arguments, "ip-address")
                   << "/"
                   << SimpleParser::getInteger(arguments, "prefix-len");
                osa << "/"
                    << SimpleParser::getInteger(arguments, "prefix-len");
            } else {
                os << " address: "
                   << SimpleParser::getString(arguments, "ip-address");
            }

            os << " to a device with DUID: "
               << SimpleParser::getString(arguments, "duid");

            string hw_address;
            if (getOptionalString(arguments, "hw-address", hw_address)) {
                os << ", hardware address: " << hw_address;
            }

            addDuration(os, arguments);
            addContext(os, arguments);
        } else if (name == "lease6-del") {
            string ip_address;
            if (getOptionalString(arguments, "ip-address", ip_address)) {
                osa << SimpleParser::getString(arguments, "ip-address");
                os << " deleted the lease for address: "
                   << SimpleParser::getString(arguments, "ip-address");
            } else {
                os << " deleted a lease for a device identified by: "
                   << SimpleParser::getString(arguments, "identifier-type")
                   << " of " << SimpleParser::getString(arguments, "identifier");
            }
        } else if (name == "lease6-bulk-apply") {
            // At least one of the 'deleted-leases' or 'leases' must be present.
            auto deleted_leases = arguments->get("deleted-leases");
            auto leases = arguments->get("leases");

            if (!deleted_leases && !leases) {
                isc_throw(BadValue, "neither 'deleted-leases' nor 'leases' parameter"
                          " specified");
            }

            // Make sure that 'deleted-leases' is a list, if present.
            if (deleted_leases && (deleted_leases->getType() != Element::list)) {
                isc_throw(BadValue, "the 'deleted-leases' parameter must be a list");
            }

            // Make sure that 'leases' is a list, if present.
            if (leases && (leases->getType() != Element::list)) {
                isc_throw(BadValue, "the 'leases' parameter must be a list");
            }

            ConstElementPtr failed_deleted_leases;
            ConstElementPtr failed_leases;

            auto response_args = response->get("arguments");

            if (response_args) {
                failed_deleted_leases = response_args->get("failed-deleted-leases");
                failed_leases = response_args->get("failed-leases");
            }

            int status = 0;

            if (deleted_leases) {
                unordered_set<string> failed_deleted_leases_set;
                if (failed_deleted_leases) {
                    // Make sure that 'failed-deleted-leases' is a list, if present.
                    if (failed_deleted_leases->getType() != Element::list) {
                        isc_throw(BadValue, "the 'failed-deleted-leases' parameter must be a list");
                    }
                    auto leases_list = failed_deleted_leases->listValue();

                    for (auto const& lease_params : leases_list) {
                        auto address = lease_params->get("ip-address");
                        if (address) {
                            failed_deleted_leases_set.emplace(address->stringValue());
                        }
                    }
                }

                auto leases_list = deleted_leases->listValue();
                for (auto const& lease_params : leases_list) {
                    auto address = lease_params->get("ip-address");
                    if (address && failed_deleted_leases_set.count(address->stringValue()) == 0) {
                        ElementPtr copy;
                        if (!origin.empty()) {
                            copy = data::copy(lease_params);
                            copy->set("origin", Element::create(origin));
                        } else {
                            copy = lease_params;
                        }
                        ConstElementPtr args(copy);
                        ConstElementPtr resp;
                        string cmd_name("lease6-del");
                        int result = handleLease6Cmds(cmd_name, args, resp);
                        if (result) {
                            status = result;
                        }
                    }
                }
            }

            if (leases) {
                unordered_set<string> failed_leases_set;
                if (failed_leases) {
                    // Make sure that 'failed-leases' is a list, if present.
                    if (failed_leases->getType() != Element::list) {
                        isc_throw(BadValue, "the 'failed-leases' parameter must be a list");
                    }
                    auto leases_list = failed_leases->listValue();

                    for (auto const& lease_params : leases_list) {
                        auto address = lease_params->get("ip-address");
                        if (address) {
                            failed_leases_set.emplace(address->stringValue());
                        }
                    }
                }
                auto leases_list = leases->listValue();
                for (auto const& lease_params : leases_list) {
                    auto address = lease_params->get("ip-address");
                    if (address && failed_leases_set.count(address->stringValue()) == 0) {
                        ElementPtr copy;
                        if (!origin.empty()) {
                            copy = data::copy(lease_params);
                            copy->set("origin", Element::create(origin));
                        } else {
                            copy = lease_params;
                        }
                        ConstElementPtr args(copy);
                        ConstElementPtr resp;
                        string cmd_name("lease6-update");
                        int result = handleLease6Cmds(cmd_name, args, resp);
                        if (result) {
                            status = result;
                        }
                    }
                }
            }
            return (status);
        }

        BackendStoreFactory::instance(managerID())->writeln(os.str(), osa.str());
    } catch (const exception& ex) {
        LOG_ERROR(legal_log_logger, LEGAL_LOG_COMMAND_WRITE_ERROR)
                  .arg(ex.what());
        return (1);
    }
    return (0);
}

/// @brief This callout is called at the "command_processed" hook point.
///
/// Generates an entry in the legal log for the given control channel
/// command.
///
/// It is possible to disable logging for selected subnets by specifying a
/// "legal-logging" boolean parameter within the subnet's user context. If
/// this parameter is not specified it defaults to 'true', in which case the
/// logging is performed. When this value is set to 'false' the log is not
/// produced and the function returns.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int command_processed(CalloutHandle& handle) {
    if (!BackendStoreFactory::instance(managerID())) {
        LOG_ERROR(legal_log_logger,
                  LEGAL_LOG_COMMAND_NO_LEGAL_STORE);
        return (1);
    }

    string name;
    ConstElementPtr arguments;
    ConstElementPtr response;
    try {
        handle.getArgument("name", name);
        handle.getArgument("arguments", arguments);
        handle.getArgument("response", response);

        int result = SimpleParser::getInteger(response, "result");
        if (result != 0) {
            // We don't log failed commands
            return (0);
        }

        // We are only interested in the following commands.
        static unordered_set<string> const supported = {
            "lease4-add", "lease4-update","lease4-del", "lease6-add",
            "lease6-update", "lease6-del", "lease6-bulk-apply"
        };
        if (supported.count(name) == 0) {
            return (0);
        }

        // We need to get a different configuration pointer depending if we're
        // in v4 or v6 universe. The easiest way to check the universe is by the
        // command name.
        if (name.find("lease4-") != string::npos) {
            return (handleLease4Cmds(name, arguments, response));
        } else if (name.find("lease6-") != string::npos) {
            return (handleLease6Cmds(name, arguments, response));
        }

    } catch (const exception& ex) {
        LOG_ERROR(legal_log_logger, LEGAL_LOG_COMMAND_WRITE_ERROR)
                  .arg(ex.what());
        return (1);
    }

    return (0);
}

} // end extern "C"
