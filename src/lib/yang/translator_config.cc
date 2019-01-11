// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

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
    ConstElementPtr loggers = dhcp->get("loggers");
    if (loggers) {
        dhcp->remove("loggers");

        ElementPtr logging = Element::createMap();
        logging->set("loggers", loggers);
        result->set("Logging", logging);
    }
    return (result);
}

ElementPtr
TranslatorConfig::getConfigKea6() {
    ElementPtr result = Element::createMap();
    ElementPtr dhcp = getServerKeaDhcp6();
    result->set("Dhcp6", dhcp);
    ConstElementPtr loggers = dhcp->get("loggers");
    if (loggers) {
        dhcp->remove("loggers");

        ElementPtr logging = Element::createMap();
        logging->set("loggers", loggers);
        result->set("Logging", logging);
    }
    return (result);
}

void
TranslatorConfig::getParam(ElementPtr& storage, const std::string& xpath,
                           const std::string& name) {
    ConstElementPtr x = getItem(xpath + "/" + name);
    if (x) {
        storage->set(name, x);
    }
}

ElementPtr
TranslatorConfig::getHooksKea(const std::string& xpath) {
    S_Iter_Value iter = getIter(xpath + "/hook-library");
    if (iter) {
        ElementPtr hook_libs = Element::createList();
        for (;;) {
            const string& lib = getNext(iter);
            if (lib.empty()) {
                break;
            }
            ElementPtr hook_lib = Element::createMap();
            ConstElementPtr name = getItem(lib + "/library");
            if (name) {
                hook_lib->set("library", name);
                ConstElementPtr params = getItem(lib + "/parameters");
                if (params) {
                    string parameters = params->stringValue();
                    if (!parameters.empty()) {
                        hook_lib->set("parameters",
                                      Element::fromJSON(parameters));
                    }
                }
                hook_libs->add(hook_lib);
            }
        }
        if (!hook_libs->empty()) {
            return (hook_libs);
        }
    }
    return (ElementPtr());
}

isc::data::ElementPtr
TranslatorConfig::getExpiredKea(const std::string& xpath) {
    ElementPtr expired = Element::createMap();

    getParam(expired, xpath, "reclaim-timer-wait-time");
    getParam(expired, xpath, "flush-reclaimed-timer-wait-time");
    getParam(expired, xpath, "hold-reclaimed-time");
    getParam(expired, xpath, "max-reclaim-leases");
    getParam(expired, xpath, "max-reclaim-time");
    getParam(expired, xpath, "unwarned-reclaim-cycles");

    if (!expired->empty()) {
        return (expired);
    }

    return (ElementPtr());
}

isc::data::ElementPtr
TranslatorConfig::getDdnsKea(const std::string& xpath) {
    ElementPtr ddns = Element::createMap();
    getParam(ddns, xpath, "enable-updates");
    getParam(ddns, xpath, "qualifying-suffix");
    getParam(ddns, xpath, "server-ip");
    getParam(ddns, xpath, "server-port");
    getParam(ddns, xpath, "sender-ip");
    getParam(ddns, xpath, "sender-port");
    getParam(ddns, xpath, "max-queue-size");
    getParam(ddns, xpath, "ncr-protocol");
    getParam(ddns, xpath, "ncr-format");
    getParam(ddns, xpath, "override-no-update");
    getParam(ddns, xpath, "override-client-update");
    getParam(ddns, xpath, "replace-client-name");
    getParam(ddns, xpath, "generated-prefix");
    getParam(ddns, xpath, "hostname-char-set");
    getParam(ddns, xpath, "hostname-char-replacement");

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

    getParam(result, xpath, "valid-lifetime");
    getParam(result, xpath, "renew-timer");
    getParam(result, xpath, "rebind-timer");
    getParam(result, xpath, "decline-probation-period");

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
    getParam(result, xpath, "dhcp4o6-port");
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
    getParam(result, xpath, "reservation-mode");
    ConstElementPtr hosts = getHosts(xpath);
    if (hosts && !hosts->empty()) {
        result->set("reservations", hosts);
    }
    ConstElementPtr config_ctrl =
        getConfigControlKea(xpath + "/config-control");
    if (config_ctrl) {
        result->set("config-control", config_ctrl);
    }
    getParam(result, xpath, "server-tag");
    ConstElementPtr queue_ctrl = getItem(xpath + "/dhcp-queue-control");
    if (queue_ctrl) {
        result->set("dhcp-queue-control",
                    Element::fromJSON(queue_ctrl->stringValue()));
    }
    ConstElementPtr loggers = getLoggers(xpath);
    if (loggers && !loggers->empty()) {
        result->set("loggers", loggers);
    }
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
    getParam(if_config, xpath + "/interfaces-config", "dhcp-socket-type");
    getParam(if_config, xpath + "/interfaces-config", "outbound-interface");
    getParam(if_config, xpath + "/interfaces-config", "re-detect");
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
    getParam(result, xpath, "echo-client-id");
    getParam(result, xpath, "match-client-id");
    getParam(result, xpath, "next-server");
    getParam(result, xpath, "server-hostname");
    getParam(result, xpath, "boot-file-name");
    getParam(result, xpath, "authoritative");
    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcp6() {
    string xpath = "/kea-dhcp6-server:config";
    ElementPtr result = getServerKeaDhcpCommon(xpath);
    // Handle DHCPv6 specific global parameters.
    getParam(result, xpath, "preferred-lifetime");
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
    getParam(if_config, xpath + "/interfaces-config", "re-detect");
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
    getParam(server_id, xpath + "/server-id", "type");
    getParam(server_id, xpath + "/server-id", "identifier");
    getParam(server_id, xpath + "/server-id", "time");
    getParam(server_id, xpath + "/server-id", "htype");
    getParam(server_id, xpath + "/server-id", "enterprise-id");
    getParam(server_id, xpath + "/server-id", "persist");
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
    ConstElementPtr logging = elem->get("Logging");
    if (logging) {
        setServerKeaLogging(logging);
    }
}

void
TranslatorConfig::setConfigKea6(ConstElementPtr elem) {
    ConstElementPtr dhcp = elem->get("Dhcp6");
    if (dhcp) {
        setServerKeaDhcp6(dhcp);
    }
    ConstElementPtr logging = elem->get("Logging");
    if (logging) {
        setServerKeaLogging(logging);
    }
}

void
TranslatorConfig::setServerKeaDhcpCommon(const string& xpath,
                                         ConstElementPtr elem) {
    ConstElementPtr valid = elem->get("valid-lifetime");
    if (valid) {
        setItem(xpath + "/valid-lifetime", valid, SR_UINT32_T);
    }
    ConstElementPtr renew = elem->get("renew-timer");
    if (renew) {
        setItem(xpath + "/renew-timer", renew, SR_UINT32_T);
    }
    ConstElementPtr rebind = elem->get("rebind-timer");
    if (rebind) {
        setItem(xpath + "/rebind-timer", rebind, SR_UINT32_T);
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
    ConstElementPtr preferred = elem->get("preferred-lifetime");
    if (preferred) {
        setItem(xpath + "/preferred-lifetime", preferred, SR_UINT32_T);
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

void
TranslatorConfig::setServerKeaLogging(ConstElementPtr elem) {
    string xpath = "/" + model_ + ":config";
    ConstElementPtr loggers = elem->get("loggers");
    if (loggers) {
        setLoggers(xpath, loggers);
    }
}

}; // end of namespace isc::yang
}; // end of namespace isc
