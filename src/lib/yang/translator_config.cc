// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_config.h>
#include <yang/adaptor_config.h>
#include <yang/yang_models.h>
#include <sstream>

using namespace std;
using namespace isc::data;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorConfig::TranslatorConfig(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorControlSocket(session, model),
      TranslatorDatabase(session, model),
      TranslatorDatabases(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorOptionDef(session, model),
      TranslatorOptionDefList(session, model),
      TranslatorClass(session, model),
      TranslatorClasses(session, model),
      TranslatorPool(session, model),
      TranslatorPools(session, model),
      TranslatorPdPool(session, model),
      TranslatorPdPools(session, model),
      TranslatorHost(session, model),
      TranslatorHosts(session, model),
      TranslatorSubnet(session, model),
      TranslatorSubnets(session, model),
      TranslatorSharedNetwork(session, model),
      TranslatorSharedNetworks(session, model),
      TranslatorLogger(session, model),
      TranslatorLoggers(session, model) {
}

TranslatorConfig::~TranslatorConfig() {
}

ElementPtr
TranslatorConfig::getConfig() {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getConfigIetf6());
        } else if (model_ == KEA_DHCP4_SERVER) {
            return (getConfigKea4());
        } else if (model_ == KEA_DHCP6_SERVER) {
            return (getConfigKea6());
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError, "sysrepo error getting config: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getConfig not implemented for the model: " << model_);
}

ElementPtr
TranslatorConfig::getConfigIetf6() {
    ElementPtr result = Element::createMap();
    ElementPtr dhcp6 = Element::createMap();
    result->set("Dhcp6", dhcp6);
    string xpath = "/" + model_ + ":server/server-config";
    ConstElementPtr ranges =
        getSubnets(xpath + "/network-ranges");
    if (ranges && !ranges->empty()) {
        dhcp6->set("subnet6", ranges);
    }
    // Skip everything else.
    return (result);
}

ElementPtr
TranslatorConfig::getConfigKea4() {
    ElementPtr result = Element::createMap();
    ElementPtr dhcp = getServerKeaDhcp4();
    result->set("Dhcp4", dhcp);
    return (result);
}

ElementPtr
TranslatorConfig::getConfigKea6() {
    ElementPtr result = Element::createMap();
    ElementPtr dhcp = getServerKeaDhcp6();
    result->set("Dhcp6", dhcp);
    return (result);
}

ElementPtr TranslatorConfig::getHook(string const& xpath) {
    ElementPtr const& hook_library(Element::createMap());
    ElementPtr const& name(getItem(xpath + "/library"));
    if (name) {
        hook_library->set("library", name);
        ElementPtr const& parameters(getItem(xpath + "/parameters"));
        if (parameters) {
            hook_library->set("parameters",
                              Element::fromJSON(parameters->stringValue()));
        }
    }
    return hook_library;
}

ElementPtr
TranslatorConfig::getHooksKea(const std::string& xpath) {
    return getList(xpath + "/hook-library", *this, &TranslatorConfig::getHook);
}

isc::data::ElementPtr
TranslatorConfig::getExpiredKea(const std::string& xpath) {
    ElementPtr expired = Element::createMap();

    checkAndGetLeaf(expired, xpath, "reclaim-timer-wait-time");
    checkAndGetLeaf(expired, xpath, "flush-reclaimed-timer-wait-time");
    checkAndGetLeaf(expired, xpath, "hold-reclaimed-time");
    checkAndGetLeaf(expired, xpath, "max-reclaim-leases");
    checkAndGetLeaf(expired, xpath, "max-reclaim-time");
    checkAndGetLeaf(expired, xpath, "unwarned-reclaim-cycles");

    if (!expired->empty()) {
        return (expired);
    }

    return (ElementPtr());
}

isc::data::ElementPtr
TranslatorConfig::getDdnsKea(const std::string& xpath) {
    ElementPtr ddns = Element::createMap();
    checkAndGetLeaf(ddns, xpath, "enable-updates");
    checkAndGetLeaf(ddns, xpath, "qualifying-suffix");
    checkAndGetLeaf(ddns, xpath, "server-ip");
    checkAndGetLeaf(ddns, xpath, "server-port");
    checkAndGetLeaf(ddns, xpath, "sender-ip");
    checkAndGetLeaf(ddns, xpath, "sender-port");
    checkAndGetLeaf(ddns, xpath, "max-queue-size");
    checkAndGetLeaf(ddns, xpath, "ncr-protocol");
    checkAndGetLeaf(ddns, xpath, "ncr-format");
    checkAndGetLeaf(ddns, xpath, "override-no-update");
    checkAndGetLeaf(ddns, xpath, "override-client-update");
    checkAndGetLeaf(ddns, xpath, "replace-client-name");
    checkAndGetLeaf(ddns, xpath, "generated-prefix");
    checkAndGetLeaf(ddns, xpath, "hostname-char-set");
    checkAndGetLeaf(ddns, xpath, "hostname-char-replacement");

    ConstElementPtr context = getItem(xpath + "/user-context");
    if (context) {
        ddns->set("user-context", Element::fromJSON(context->stringValue()));
    }

    if (!ddns->empty()) {
        // If there's something to return, use it.
        return (ddns);
    }

    // If not, return null.
    return (ElementPtr());
}

ElementPtr
TranslatorConfig::getConfigControlKea(const string& xpath) {
    ElementPtr config_ctrl = Element::createMap();
    checkAndGetLeaf(config_ctrl, xpath, "config-fetch-wait-time");
    ConstElementPtr databases = getDatabases(xpath + "/config-database");
    if (databases && !databases->empty()) {
        config_ctrl->set("config-databases", databases);
    }
    if (!config_ctrl->empty()) {
        // If there's something to return, use it.
        return (config_ctrl);
    }

    // If not, return null.
    return (ElementPtr());
}

ElementPtr
TranslatorConfig::getServerKeaDhcpCommon(const string& xpath) {
    ElementPtr result = Element::createMap();

    checkAndGetLeaf(result, xpath, "valid-lifetime");
    checkAndGetLeaf(result, xpath, "min-valid-lifetime");
    checkAndGetLeaf(result, xpath, "max-valid-lifetime");
    checkAndGetLeaf(result, xpath, "renew-timer");
    checkAndGetLeaf(result, xpath, "rebind-timer");
    checkAndGetLeaf(result, xpath, "calculate-tee-times");
    checkAndGetLeaf(result, xpath, "t1-percent");
    checkAndGetLeaf(result, xpath, "t2-percent");
    checkAndGetLeaf(result, xpath, "decline-probation-period");
    checkAndGetLeaf(result, xpath, "hostname-char-set");
    checkAndGetLeaf(result, xpath, "hostname-char-replacement");

    ConstElementPtr networks = getSharedNetworks(xpath);
    if (networks && !networks->empty()) {
        result->set("shared-networks", networks);
    }
    ConstElementPtr classes = getClasses(xpath);
    if (classes && !classes->empty()) {
        result->set("client-classes", classes);
    }
    ConstElementPtr database = getDatabase(xpath + "/lease-database");
    if (database) {
        result->set("lease-database", database);
    }
    ConstElementPtr databases = getDatabases(xpath + "/hosts-database");
    if (databases && !databases->empty()) {
        result->set("hosts-databases", databases);
    }
    ConstElementPtr host_ids =
        getItems(xpath + "/host-reservation-identifiers");
    if (host_ids) {
        result->set("host-reservation-identifiers", host_ids);
    }
    ConstElementPtr defs = getOptionDefList(xpath);
    if (defs && !defs->empty()) {
        result->set("option-def", defs);
    }
    ConstElementPtr options = getOptionDataList(xpath);
    if (options && !options->empty()) {
        result->set("option-data", options);
    }
    ConstElementPtr hooks = getHooksKea(xpath);
    if (hooks && !hooks->empty()) {
        result->set("hooks-libraries", hooks);
    }
    ConstElementPtr expired =
        getExpiredKea(xpath + "/expired-leases-processing");
    if (expired) {
        result->set("expired-leases-processing", expired);
    }
    checkAndGetLeaf(result, xpath, "dhcp4o6-port");
    ConstElementPtr socket = getControlSocket(xpath + "/control-socket");
    if (socket) {
        result->set("control-socket", socket);
    }
    ConstElementPtr ddns = getDdnsKea(xpath + "/dhcp-ddns");
    if (ddns) {
        result->set("dhcp-ddns", ddns);
    }
    ConstElementPtr context = getItem(xpath + "/user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    ConstElementPtr checks = getItem(xpath + "/sanity-checks/lease-checks");
    if (checks) {
        ElementPtr sanity = Element::createMap();
        sanity->set("lease-checks", checks);
        result->set("sanity-checks", sanity);
    }
    checkAndGetLeaf(result, xpath, "reservation-mode");
    ConstElementPtr hosts = getHosts(xpath);
    if (hosts && !hosts->empty()) {
        result->set("reservations", hosts);
    }
    ConstElementPtr config_ctrl =
        getConfigControlKea(xpath + "/config-control");
    if (config_ctrl) {
        result->set("config-control", config_ctrl);
    }
    checkAndGetLeaf(result, xpath, "server-tag");
    ConstElementPtr queue_ctrl = getItem(xpath + "/dhcp-queue-control");
    if (queue_ctrl) {
        result->set("dhcp-queue-control",
                    Element::fromJSON(queue_ctrl->stringValue()));
    }
    ConstElementPtr loggers = getLoggers(xpath);
    if (loggers && !loggers->empty()) {
        result->set("loggers", loggers);
    }
    checkAndGetLeaf(result, xpath, "cache-max-age");
    checkAndGetLeaf(result, xpath, "cache-threshold");
    ElementPtr compatibility = Element::createMap();
    checkAndGetLeaf(compatibility, xpath + "/compatibility", "lenient-option-parsing");
    if (!compatibility->empty()) {
        result->set("compatibility", compatibility);
    }
    checkAndGetLeaf(result, xpath, "ddns-generated-prefix");
    checkAndGetLeaf(result, xpath, "ddns-override-client-update");
    checkAndGetLeaf(result, xpath, "ddns-override-no-update");
    checkAndGetLeaf(result, xpath, "ddns-qualifying-suffix");
    checkAndGetLeaf(result, xpath, "ddns-replace-client-name");
    checkAndGetLeaf(result, xpath, "ddns-send-updates");
    checkAndGetLeaf(result, xpath, "ddns-update-on-renew");
    checkAndGetLeaf(result, xpath, "ddns-use-conflict-resolution");
    checkAndGetLeaf(result, xpath, "ip-reservations-unique");
    ElementPtr multi_threading = Element::createMap();
    checkAndGetLeaf(multi_threading, xpath + "/multi-threading", "enable-multi-threading");
    checkAndGetLeaf(multi_threading, xpath + "/multi-threading", "packet-queue-size");
    checkAndGetLeaf(multi_threading, xpath + "/multi-threading", "thread-pool-size");
    if (!multi_threading->empty()) {
        result->set("multi-threading", multi_threading);
    }
    checkAndGetLeaf(result, xpath, "parked-packet-limit");
    checkAndGetLeaf(result, xpath, "reservations-global");
    checkAndGetLeaf(result, xpath, "reservations-in-subnet");
    checkAndGetLeaf(result, xpath, "reservations-out-of-pool");
    checkAndGetLeaf(result, xpath, "statistic-default-sample-age");
    checkAndGetLeaf(result, xpath, "statistic-default-sample-count");
    checkAndGetLeaf(result, xpath, "store-extended-info");
    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcp4() {
    string xpath = "/kea-dhcp4-server:config";
    ElementPtr result = getServerKeaDhcpCommon(xpath);
    // Handle subnets.
    ConstElementPtr subnets = getSubnets(xpath);
    if (subnets && !subnets->empty()) {
        result->set("subnet4", subnets);
    }
    // Handle interfaces.
    ElementPtr if_config = Element::createMap();
    ConstElementPtr ifs = getItems(xpath + "/interfaces-config/interfaces");
    if (ifs && !ifs->empty()) {
        if_config->set("interfaces", ifs);
    }
    checkAndGetLeaf(if_config, xpath + "/interfaces-config", "dhcp-socket-type");
    checkAndGetLeaf(if_config, xpath + "/interfaces-config", "outbound-interface");
    checkAndGetLeaf(if_config, xpath + "/interfaces-config", "re-detect");
    ConstElementPtr context =
        getItem(xpath + "/interfaces-config/user-context");
    if (context) {
        if_config->set("user-context",
                       Element::fromJSON(context->stringValue()));
    }
    if (!if_config->empty()) {
        result->set("interfaces-config", if_config);
    }
    // Handle DHCPv4 specific global parameters.
    checkAndGetLeaf(result, xpath, "echo-client-id");
    checkAndGetLeaf(result, xpath, "match-client-id");
    checkAndGetLeaf(result, xpath, "next-server");
    checkAndGetLeaf(result, xpath, "server-hostname");
    checkAndGetLeaf(result, xpath, "boot-file-name");
    checkAndGetLeaf(result, xpath, "authoritative");
    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcp6() {
    string xpath = "/kea-dhcp6-server:config";
    ElementPtr result = getServerKeaDhcpCommon(xpath);
    // Handle DHCPv6 specific global parameters.
    checkAndGetLeaf(result, xpath, "data-directory");
    checkAndGetLeaf(result, xpath, "preferred-lifetime");
    checkAndGetLeaf(result, xpath, "min-preferred-lifetime");
    checkAndGetLeaf(result, xpath, "max-preferred-lifetime");
    // Handle subnets.
    ConstElementPtr subnets = getSubnets(xpath);
    if (subnets && !subnets->empty()) {
        result->set("subnet6", subnets);
    }
    // Handle interfaces.
    ElementPtr if_config = Element::createMap();
    ConstElementPtr ifs = getItems(xpath + "/interfaces-config/interfaces");
    if (ifs && !ifs->empty()) {
        if_config->set("interfaces", ifs);
    }
    checkAndGetLeaf(if_config, xpath + "/interfaces-config", "re-detect");
    ConstElementPtr context =
        getItem(xpath + "/interfaces-config/user-context");
    if (context) {
        if_config->set("user-context",
                       Element::fromJSON(context->stringValue()));
    }
    if (!if_config->empty()) {
        result->set("interfaces-config", if_config);
    }
    // Handle DHCPv6 specific global entries.
    ConstElementPtr relay = getItems(xpath + "/relay-supplied-options");
    if (relay) {
        result->set("relay-supplied-options", relay);
    }
    ConstElementPtr macs = getItems(xpath + "/mac-sources");
    if (macs) {
        result->set("mac-sources", macs);
    }
    // Handle server-id.
    // @todo: move to a DUID translator.
    ElementPtr server_id = Element::createMap();
    checkAndGetLeaf(server_id, xpath + "/server-id", "type");
    checkAndGetLeaf(server_id, xpath + "/server-id", "identifier");
    checkAndGetLeaf(server_id, xpath + "/server-id", "time");
    checkAndGetLeaf(server_id, xpath + "/server-id", "htype");
    checkAndGetLeaf(server_id, xpath + "/server-id", "enterprise-id");
    checkAndGetLeaf(server_id, xpath + "/server-id", "persist");
    context = getItem(xpath + "/server-id/user-context");
    if (context) {
        server_id->set("user-context",
                       Element::fromJSON(context->stringValue()));
    }
    if (!server_id->empty()) {
        result->set("server-id", server_id);
    }
    return (result);
}

void
TranslatorConfig::setConfig(ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            if (elem) {
                AdaptorConfig::preProcess6(elem);
                setConfigIetf6(elem);
            } else {
                delConfigIetf6();
            }
        } else if (model_ == KEA_DHCP4_SERVER) {
            if (elem) {
                AdaptorConfig::preProcess4(elem);
                setConfigKea4(elem);
            } else {
                delConfigKea();
            }
        } else if (model_ == KEA_DHCP6_SERVER) {
            if (elem) {
                AdaptorConfig::preProcess6(elem);
                setConfigKea6(elem);
            } else {
                delConfigKea();
            }
        } else {
            isc_throw(NotImplemented,
                      "setConfig not implemented for the model: " << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting config '" << elem->str()
                  << "': " << ex.what());
    }
}

void
TranslatorConfig::delConfigIetf6() {
    delItem("/" + model_ + ":server");
}

void
TranslatorConfig::setConfigIetf6(ConstElementPtr elem) {
    string xpath = "/" + model_ + ":server/server-config";
    ConstElementPtr dhcp6 = elem->get("Dhcp6");
    if (!dhcp6) {
        isc_throw(BadValue, "no Dhcp6 entry in " << elem->str());
    }
    ConstElementPtr ranges = dhcp6->get("subnet6");
    if (ranges && !ranges->empty()) {
        setSubnets(xpath + "/network-ranges", ranges);
    }
    // Skip everything else.
}

void
TranslatorConfig::delConfigKea() {
    delItem("/" + model_ + ":config");
}

void
TranslatorConfig::setConfigKea4(ConstElementPtr elem) {
    ConstElementPtr dhcp = elem->get("Dhcp4");
    if (dhcp) {
        setServerKeaDhcp4(dhcp);
    }
}

void
TranslatorConfig::setConfigKea6(ConstElementPtr elem) {
    ConstElementPtr dhcp = elem->get("Dhcp6");
    if (dhcp) {
        setServerKeaDhcp6(dhcp);
    }
}

void
TranslatorConfig::setServerKeaDhcpCommon(const string& xpath,
                                         ConstElementPtr elem) {
    ConstElementPtr valid = elem->get("valid-lifetime");
    if (valid) {
        setItem(xpath + "/valid-lifetime", valid, SR_UINT32_T);
    }
    ConstElementPtr min_valid = elem->get("min-valid-lifetime");
    if (min_valid) {
        setItem(xpath + "/min-valid-lifetime", min_valid, SR_UINT32_T);
    }
    ConstElementPtr max_valid = elem->get("max-valid-lifetime");
    if (max_valid) {
        setItem(xpath + "/max-valid-lifetime", max_valid, SR_UINT32_T);
    }
    ConstElementPtr renew = elem->get("renew-timer");
    if (renew) {
        setItem(xpath + "/renew-timer", renew, SR_UINT32_T);
    }
    ConstElementPtr rebind = elem->get("rebind-timer");
    if (rebind) {
        setItem(xpath + "/rebind-timer", rebind, SR_UINT32_T);
    }
    ConstElementPtr calculate = elem->get("calculate-tee-times");
    if (calculate) {
        setItem(xpath + "/calculate-tee-times", calculate, SR_BOOL_T);
    }
    ConstElementPtr t1_percent =  elem->get("t1-percent");
    if (t1_percent) {
        setItem(xpath + "/t1-percent", t1_percent, SR_DECIMAL64_T);
    }
    ConstElementPtr t2_percent =  elem->get("t2-percent");
    if (t2_percent) {
        setItem(xpath + "/t2-percent", t2_percent, SR_DECIMAL64_T);
    }
    ConstElementPtr period = elem->get("decline-probation-period");
    if (period) {
        setItem(xpath + "/decline-probation-period", period, SR_UINT32_T);
    }
    ConstElementPtr networks = elem->get("shared-networks");
    if (networks) {
        setSharedNetworks(xpath, networks);
    }
    ConstElementPtr classes = elem->get("client-classes");
    if (classes && !classes->empty()) {
        setClasses(xpath, classes);
    }
    ConstElementPtr database = elem->get("lease-database");
    if (database) {
        setDatabase(xpath + "/lease-database", database);
    }
    ConstElementPtr databases = elem->get("hosts-databases");
    if (databases && !databases->empty()) {
        setDatabases(xpath + "/hosts-database", databases);
    } else {
        // Reuse of database from lease-database.
        database = elem->get("hosts-database");
        if (database) {
            ElementPtr list = Element::createList();
            list->add(copy(database));
            setDatabases(xpath + "/hosts-database", list);
        }
    }
    ConstElementPtr host_ids = elem->get("host-reservation-identifiers");
    if (host_ids) {
        for (ConstElementPtr id : host_ids->listValue()) {
            setItem(xpath + "/host-reservation-identifiers", id, SR_ENUM_T);
        }
    }
    ConstElementPtr defs = elem->get("option-def");
    if (defs && !defs->empty()) {
        setOptionDefList(xpath, defs);
    }
    ConstElementPtr options = elem->get("option-data");
    if (options && !options->empty()) {
        setOptionDataList(xpath, options);
    }
    ConstElementPtr hook_libs = elem->get("hooks-libraries");
    if (hook_libs) {
        for (ConstElementPtr lib : hook_libs->listValue()) {
            ConstElementPtr name = lib->get("library");
            if (!name) {
                continue;
            }
            ostringstream hook_lib;
            hook_lib << xpath << "/hook-library[library='"
                     << name->stringValue() << "']";
            ConstElementPtr params = lib->get("parameters");
            if (params) {
                hook_lib << "/parameters";
                setItem(hook_lib.str(), Element::create(params->str()),
                        SR_STRING_T);
            } else {
                ConstElementPtr list = Element::createList();
                setItem(hook_lib.str(), list, SR_LIST_T);
            }
        }
    }
    ConstElementPtr expired = elem->get("expired-leases-processing");
    if (expired) {
        ConstElementPtr reclaim = expired->get("reclaim-timer-wait-time");
        if (reclaim) {
            setItem(xpath + "/expired-leases-processing/reclaim-timer-wait-time",
                    reclaim, SR_UINT32_T);
        }
        ConstElementPtr flush =
            expired->get("flush-reclaimed-timer-wait-time");
        if (flush) {
            setItem(xpath + "/expired-leases-processing/flush-reclaimed-timer-wait-time",
                    flush, SR_UINT32_T);
        }
        ConstElementPtr hold = expired->get("hold-reclaimed-time");
        if (hold) {
            setItem(xpath + "/expired-leases-processing/hold-reclaimed-time",
                    hold, SR_UINT32_T);
        }
        ConstElementPtr max_leases = expired->get("max-reclaim-leases");
        if (max_leases) {
            setItem(xpath + "/expired-leases-processing/max-reclaim-leases",
                    max_leases, SR_UINT32_T);
        }
        ConstElementPtr max_time = expired->get("max-reclaim-time");
        if (max_time) {
            setItem(xpath + "/expired-leases-processing/max-reclaim-time",
                    max_time, SR_UINT32_T);
        }
        ConstElementPtr unwarned = expired->get("unwarned-reclaim-cycles");
        if (unwarned) {
            setItem(xpath + "/expired-leases-processing/unwarned-reclaim-cycles",
                    unwarned, SR_UINT32_T);
        }
    }
    ConstElementPtr port = elem->get("dhcp4o6-port");
    if (port) {
        setItem(xpath + "/dhcp4o6-port", port, SR_UINT16_T);
    }
    ConstElementPtr socket = elem->get("control-socket");
    if (socket) {
        setControlSocket(xpath + "/control-socket", socket);
    }
    ConstElementPtr char_set = elem->get("hostname-char-set");
    if (char_set) {
        setItem(xpath + "/hostname-char-set", char_set, SR_STRING_T);
    }
    ConstElementPtr char_repl = elem->get("hostname-char-replacement");
    if (char_repl) {
        setItem(xpath + "/hostname-char-replacement", char_repl, SR_STRING_T);
    }
    ConstElementPtr ddns = elem->get("dhcp-ddns");
    if (ddns) {
        ConstElementPtr enable = ddns->get("enable-updates");
        if (enable) {
            setItem(xpath + "/dhcp-ddns/enable-updates", enable, SR_BOOL_T);
        }
        ConstElementPtr suffix = ddns->get("qualifying-suffix");
        if (suffix) {
            setItem(xpath + "/dhcp-ddns/qualifying-suffix", suffix,
                    SR_STRING_T);
        }
        ConstElementPtr server_ip = ddns->get("server-ip");
        if (server_ip) {
            setItem(xpath + "/dhcp-ddns/server-ip", server_ip, SR_STRING_T);
        }
        ConstElementPtr server_port = ddns->get("server-port");
        if (server_port) {
            setItem(xpath + "/dhcp-ddns/server-port", server_port,
                    SR_UINT16_T);
        }
        ConstElementPtr sender_ip = ddns->get("sender-ip");
        if (sender_ip) {
            setItem(xpath + "/dhcp-ddns/sender-ip", sender_ip, SR_STRING_T);
        }
        ConstElementPtr sender_port = ddns->get("sender-port");
        if (sender_port) {
            setItem(xpath + "/dhcp-ddns/sender-port", sender_port,
                    SR_UINT16_T);
        }
        ConstElementPtr queue = ddns->get("max-queue-size");
        if (queue) {
            setItem(xpath + "/dhcp-ddns/max-queue-size", queue, SR_UINT32_T);
        }
        ConstElementPtr protocol = ddns->get("ncr-protocol");
        if (protocol) {
            setItem(xpath + "/dhcp-ddns/ncr-protocol", protocol, SR_ENUM_T);
        }
        ConstElementPtr format = ddns->get("ncr-format");
        if (format) {
            setItem(xpath + "/dhcp-ddns/ncr-format", format, SR_ENUM_T);
        }
        ConstElementPtr no_up = ddns->get("override-no-update");
        if (no_up) {
            setItem(xpath + "/dhcp-ddns/override-no-update", no_up, SR_BOOL_T);
        }
        ConstElementPtr client = ddns->get("override-client-update");
        if (client) {
            setItem(xpath + "/dhcp-ddns/override-client-update", client,
                    SR_BOOL_T);
        }
        ConstElementPtr replace = ddns->get("replace-client-name");
        if (replace) {
            setItem(xpath + "/dhcp-ddns/replace-client-name", replace,
                    SR_ENUM_T);
        }
        ConstElementPtr generated = ddns->get("generated-prefix");
        if (generated) {
            setItem(xpath + "/dhcp-ddns/generated-prefix", generated,
                    SR_STRING_T);
        }
        ConstElementPtr char_set = ddns->get("hostname-char-set");
        if (char_set) {
            setItem(xpath + "/dhcp-ddns/hostname-char-set", char_set,
                    SR_STRING_T);
        }
        ConstElementPtr char_repl = ddns->get("hostname-char-replacement");
        if (char_repl) {
            setItem(xpath + "/dhcp-ddns/hostname-char-replacement", char_repl,
                    SR_STRING_T);
        }
        ConstElementPtr context = Adaptor::getContext(ddns);
        if (context) {
            ConstElementPtr repr = Element::create(context->str());
            setItem(xpath + "/dhcp-ddns/user-context", repr, SR_STRING_T);
        }
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        ConstElementPtr repr = Element::create(context->str());
        setItem(xpath + "/user-context", repr, SR_STRING_T);
    }
    ConstElementPtr sanity = elem->get("sanity-checks");
    if (sanity) {
        ConstElementPtr checks = sanity->get("lease-checks");
        if (checks) {
            setItem(xpath + "/sanity-checks/lease-checks", checks, SR_ENUM_T);
        }
    }
    ConstElementPtr hr_mode = elem->get("reservation-mode");
    if (hr_mode) {
        setItem(xpath + "/reservation-mode", hr_mode, SR_ENUM_T);
    }
    ConstElementPtr hosts = elem->get("reservations");
    if (hosts && !hosts->empty()) {
        setHosts(xpath, hosts);
    }
    ConstElementPtr config_ctrl = elem->get("config-control");
    if (config_ctrl && !config_ctrl->empty()) {
        ConstElementPtr cfwt = config_ctrl->get("config-fetch-wait-time");
        if (cfwt) {
            setItem(xpath + "/config-control/config-fetch-wait-time", cfwt,
                    SR_UINT32_T);
        }
        databases = config_ctrl->get("config-databases");
        if (databases && !databases->empty()) {
            setDatabases(xpath + "/config-control/config-database", databases);
        }
    }
    ConstElementPtr server_tag = elem->get("server-tag");
    if (server_tag) {
        setItem(xpath + "/server-tag", server_tag, SR_STRING_T);
    }
    ConstElementPtr queue_ctrl = elem->get("dhcp-queue-control");
    if (queue_ctrl) {
        ConstElementPtr repr = Element::create(queue_ctrl->str());
        setItem(xpath + "/dhcp-queue-control", repr, SR_STRING_T);
    }
    ConstElementPtr loggers = elem->get("loggers");
    if (loggers) {
        setLoggers(xpath, loggers);
    }
    checkAndSetLeaf(elem, xpath, "cache-max-age", SR_UINT32_T);
    checkAndSetLeaf(elem, xpath, "cache-threshold", SR_DECIMAL64_T);
    ConstElementPtr compatibility(elem->get("compatibility"));
    if (compatibility) {
        checkAndSetLeaf(compatibility, xpath + "/compatibility", "lenient-option-parsing", SR_BOOL_T);
    }
    checkAndSetLeaf(elem, xpath, "ddns-generated-prefix", SR_STRING_T);
    checkAndSetLeaf(elem, xpath, "ddns-override-client-update", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "ddns-override-no-update", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "ddns-qualifying-suffix", SR_STRING_T);
    checkAndSetLeaf(elem, xpath, "ddns-replace-client-name", SR_STRING_T);
    checkAndSetLeaf(elem, xpath, "ddns-send-updates", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "ddns-update-on-renew", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "ddns-use-conflict-resolution", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "ip-reservations-unique", SR_BOOL_T);
    ConstElementPtr multi_threading(elem->get("multi-threading"));
    if (multi_threading) {
        checkAndSetLeaf(multi_threading, xpath + "/multi-threading", "enable-multi-threading", SR_BOOL_T);
        checkAndSetLeaf(multi_threading, xpath + "/multi-threading", "packet-queue-size", SR_UINT32_T);
        checkAndSetLeaf(multi_threading, xpath + "/multi-threading", "thread-pool-size", SR_UINT32_T);
    }
    checkAndSetLeaf(elem, xpath, "parked-packet-limit", SR_UINT32_T);
    checkAndSetLeaf(elem, xpath, "reservations-global", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "reservations-in-subnet", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "reservations-out-of-pool", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "statistic-default-sample-age", SR_UINT32_T);
    checkAndSetLeaf(elem, xpath, "statistic-default-sample-count", SR_UINT32_T);
    checkAndSetLeaf(elem, xpath, "store-extended-info", SR_BOOL_T);
}

void
TranslatorConfig::setServerKeaDhcp4(ConstElementPtr elem) {
    string xpath = "/kea-dhcp4-server:config";
    setServerKeaDhcpCommon(xpath, elem);
    ConstElementPtr subnets = elem->get("subnet4");
    if (subnets) {
        setSubnets(xpath, subnets);
    }
    ConstElementPtr if_config = elem->get("interfaces-config");
    if (if_config) {
        ConstElementPtr ifs = if_config->get("interfaces");
        if (ifs && !ifs->empty()) {
            for (ConstElementPtr intf : ifs->listValue()) {
                setItem(xpath + "/interfaces-config/interfaces",
                        intf, SR_STRING_T);
            }
        }
        ConstElementPtr ds_type = if_config->get("dhcp-socket-type");
        if (ds_type) {
            setItem(xpath + "/interfaces-config/dhcp-socket-type",
                    ds_type, SR_ENUM_T);
        }
        ConstElementPtr out_if = if_config->get("outbound-interface");
        if (out_if) {
            setItem(xpath + "/interfaces-config/outbound-interface",
                    out_if, SR_ENUM_T);
        }
        ConstElementPtr redetect = if_config->get("re-detect");
        if (redetect) {
            setItem(xpath + "/interfaces-config/re-detect",
                    redetect, SR_BOOL_T);
        }
        ConstElementPtr context = Adaptor::getContext(if_config);
        if (context) {
            setItem(xpath + "/interfaces-config/user-context",
                    Element::create(context->str()), SR_STRING_T);
        }
    }
    ConstElementPtr echo = elem->get("echo-client-id");
    if (echo) {
        setItem(xpath + "/echo-client-id", echo, SR_BOOL_T);
    }
    ConstElementPtr match = elem->get("match-client-id");
    if (match) {
        setItem(xpath + "/match-client-id", match, SR_BOOL_T);
    }
    ConstElementPtr next = elem->get("next-server");
    if (next) {
        setItem(xpath + "/next-server", next, SR_STRING_T);
    }
    ConstElementPtr hostname = elem->get("server-hostname");
    if (hostname) {
        setItem(xpath + "/server-hostname", hostname, SR_STRING_T);
    }
    ConstElementPtr boot = elem->get("boot-file-name");
    if (boot) {
        setItem(xpath + "/boot-file-name", boot, SR_STRING_T);
    }
    ConstElementPtr auth = elem->get("authoritative");
    if (auth) {
        setItem(xpath + "/authoritative", auth, SR_BOOL_T);
    }
}

void
TranslatorConfig::setServerKeaDhcp6(ConstElementPtr elem) {
    string xpath = "/kea-dhcp6-server:config";
    setServerKeaDhcpCommon(xpath, elem);
    ConstElementPtr data_dir = elem->get("data-directory");
    if (data_dir) {
        setItem(xpath + "/data-directory", data_dir, SR_STRING_T);
    }
    ConstElementPtr preferred = elem->get("preferred-lifetime");
    if (preferred) {
        setItem(xpath + "/preferred-lifetime", preferred, SR_UINT32_T);
    }
    ConstElementPtr min_pref = elem->get("min-preferred-lifetime");
    if (min_pref) {
        setItem(xpath + "/min-preferred-lifetime", min_pref, SR_UINT32_T);
    }
    ConstElementPtr max_pref = elem->get("max-preferred-lifetime");
    if (max_pref) {
        setItem(xpath + "/max-preferred-lifetime", max_pref, SR_UINT32_T);
    }
    ConstElementPtr subnets = elem->get("subnet6");
    if (subnets) {
        setSubnets(xpath, subnets);
    }
    ConstElementPtr if_config = elem->get("interfaces-config");
    if (if_config) {
        ConstElementPtr ifs = if_config->get("interfaces");
        if (ifs && !ifs->empty()) {
            for (ConstElementPtr intf : ifs->listValue()) {
                setItem(xpath + "/interfaces-config/interfaces",
                        intf, SR_STRING_T);
            }
        }
        ConstElementPtr redetect = if_config->get("re-detect");
        if (redetect) {
            setItem(xpath + "/interfaces-config/re-detect",
                    redetect, SR_BOOL_T);
        }
        ConstElementPtr context = Adaptor::getContext(if_config);
        if (context) {
            setItem(xpath + "/interfaces-config/user-context",
                    Element::create(context->str()), SR_STRING_T);
        }
    }
    ConstElementPtr relay = elem->get("relay-supplied-options");
    if (relay) {
        for (ConstElementPtr addr : relay->listValue()) {
            setItem(xpath + "/relay-supplied-options", addr, SR_STRING_T);
        }
    }
    ConstElementPtr macs = elem->get("mac-sources");
    if (macs) {
        for (ConstElementPtr source : macs->listValue()) {
            setItem(xpath + "/mac-sources", source, SR_STRING_T);
        }
    }
    ConstElementPtr server_id = elem->get("server-id");
    if (server_id) {
        ConstElementPtr id_type = server_id->get("type");
        if (id_type) {
            setItem(xpath + "/server-id/type", id_type, SR_ENUM_T);
        }
        ConstElementPtr id_id = server_id->get("identifier");
        if (id_id) {
            setItem(xpath + "/server-id/identifier", id_id, SR_STRING_T);
        }
        ConstElementPtr id_time = server_id->get("time");
        if (id_time) {
            setItem(xpath + "/server-id/time", id_time, SR_UINT32_T);
        }
        ConstElementPtr id_htype = server_id->get("htype");
        if (id_htype) {
            setItem(xpath + "/server-id/htype", id_htype, SR_UINT16_T);
        }
        ConstElementPtr id_ent_id = server_id->get("enterprise-id");
        if (id_ent_id) {
            setItem(xpath + "/server-id/enterprise-id", id_ent_id,
                    SR_UINT32_T);
        }
        ConstElementPtr id_persist = server_id->get("persist");
        if (id_persist) {
            setItem(xpath + "/server-id/persist", id_persist, SR_BOOL_T);
        }
        ConstElementPtr context = Adaptor::getContext(server_id);
        if (context) {
            ConstElementPtr repr = Element::create(context->str());
            setItem(xpath + "/server-id/user-context", repr, SR_STRING_T);
        }
    }
}

}  // namespace yang
}  // namespace isc
