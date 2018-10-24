// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <yang/translator_config.h>
#include <yang/adaptor_config.h>
#include <yang/yang_models.h>
#include <sstream>

using namespace std;
using namespace isc::data;

namespace isc {
namespace yang {

TranslatorConfig::TranslatorConfig(S_Session session, const string& model)
    : TranslatorBasic(session),
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
      TranslatorLoggers(session, model),
      model_(model) {
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
    ConstElementPtr ranges = getSubnets(xpath + "/network-ranges");
    if (ranges && (ranges->size() > 0)) {
        dhcp6->set("subnet6", ranges);
    }
    // Skip everything else.
    return (result);
}

ElementPtr
TranslatorConfig::getConfigKea4() {
    ElementPtr result = Element::createMap();
    result->set("Dhcp4", getServerKeaDhcp4());
    ConstElementPtr logging = getServerKeaLogging();
    if (logging && (logging->size() > 0)) {
        result->set("Logging", logging);
    }
    return (result);
}

ElementPtr
TranslatorConfig::getConfigKea6() {
    ElementPtr result = Element::createMap();
    result->set("Dhcp6", getServerKeaDhcp6());
    ConstElementPtr logging = getServerKeaLogging();
    if (logging && (logging->size() > 0)) {
        result->set("Logging", logging);
    }
    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcpCommon(const string& xpath) {
    ElementPtr result = Element::createMap();
    ConstElementPtr valid = getItem(xpath + "/valid-lifetime");
    if (valid) {
        result->set("valid-lifetime", valid);
    }
    ConstElementPtr renew = getItem(xpath + "/renew-timer");
    if (renew) {
        result->set("renew-timer", renew);
    }
    ConstElementPtr rebind = getItem(xpath + "/rebind-timer");
    if (rebind) {
        result->set("rebind-timer", rebind);
    }
    ConstElementPtr period = getItem(xpath + "/decline-probation-period");
    if (period) {
        result->set("decline-probation-period", period);
    }
    ConstElementPtr networks = getSharedNetworks(xpath + "/shared-networks");
    if (networks && (networks->size() > 0)) {
        result->set("shared-networks", networks);
    }
    ConstElementPtr classes = getClasses(xpath + "/client-classes");
    if (classes && (classes->size() > 0)) {
        result->set("client-classes", classes);
    }
    ConstElementPtr database = getDatabase(xpath + "/lease-database");
    if (database) {
        result->set("lease-database", database);
    }
    ConstElementPtr databases = getDatabases(xpath + "/hosts-databases");
    if (databases && (databases->size() > 0)) {
        result->set("hosts-databases", databases);
    }
    ConstElementPtr host_ids =
        getItems(xpath + "/host-reservation-identifiers");
    if (host_ids) {
        result->set("host-reservation-identifiers", host_ids);
    }
    ConstElementPtr defs = getOptionDefList(xpath + "/option-def-list");
    if (defs && (defs->size() > 0)) {
        result->set("option-def", defs);
    }
    ConstElementPtr options = getOptionDataList(xpath + "/option-data-list");
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    S_Iter_Value iter = getIter(xpath + "/hooks-libraries/*");
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
        if (hook_libs->size() > 0) {
            result->set("hooks-libraries", hook_libs);
        }
    }
    ElementPtr expired = Element::createMap();
    ConstElementPtr reclaim =
        getItem(xpath + "/expired-leases-processing/reclaim-timer-wait-time");
    if (reclaim) {
        expired->set("reclaim-timer-wait-time", reclaim);
    }
    ConstElementPtr flush =
        getItem(xpath + "/expired-leases-processing/flush-reclaimed-timer-wait-time");
    if (flush) {
        expired->set("flush-reclaimed-timer-wait-time", flush);
    }
    ConstElementPtr hold =
        getItem(xpath + "/expired-leases-processing/hold-reclaimed-time");
    if (hold) {
        expired->set("hold-reclaimed-time", hold);
    }
    ConstElementPtr max_leases =
        getItem(xpath + "/expired-leases-processing/max-reclaim-leases");
    if (max_leases) {
        expired->set("max-reclaim-leases", max_leases);
    }
    ConstElementPtr max_time =
        getItem(xpath + "/expired-leases-processing/max-reclaim-time");
    if (max_time) {
        expired->set("max-reclaim-time", max_time);
    }
    ConstElementPtr unwarned =
        getItem(xpath + "/expired-leases-processing/unwarned-reclaim-cycles");
    if (unwarned) {
        expired->set("unwarned-reclaim-cycles", unwarned);
    }
    if (expired->size() > 0) {
        result->set("expired-leases-processing", expired);
    }
    ConstElementPtr port = getItem(xpath + "/dhcp4o6-port");
    if (port) {
        result->set("dhcp4o6-port", port);
    }
    ConstElementPtr socket = getControlSocket(xpath + "/control-socket");
    if (socket) {
        result->set("control-socket", socket);
    }
    ElementPtr ddns = Element::createMap();
    ConstElementPtr enable = getItem(xpath + "/dhcp-ddns/enable-updates");
    if (enable) {
        ddns->set("enable-updates", enable);
    }
    ConstElementPtr suffix = getItem(xpath + "/dhcp-ddns/qualifying-suffix");
    if (suffix) {
        ddns->set("qualifying-suffix", suffix);
    }
    ConstElementPtr server_ip = getItem(xpath + "/dhcp-ddns/server-ip");
    if (server_ip) {
        ddns->set("server-ip", server_ip);
    }
    ConstElementPtr server_port = getItem(xpath + "/dhcp-ddns/server-port");
    if (server_port) {
        ddns->set("server-port", server_port);
    }
    ConstElementPtr sender_ip = getItem(xpath + "/dhcp-ddns/sender-ip");
    if (sender_ip) {
        ddns->set("sender-ip", sender_ip);
    }
    ConstElementPtr sender_port = getItem(xpath + "/dhcp-ddns/sender-port");
    if (sender_port) {
        ddns->set("sender-port", sender_port);
    }
    ConstElementPtr queue = getItem(xpath + "/dhcp-ddns/max-queue-size");
    if (queue) {
        ddns->set("max-queue-size", queue);
    }
    ConstElementPtr protocol = getItem(xpath + "/dhcp-ddns/ncr-protocol");
    if (protocol) {
        ddns->set("ncr-protocol", protocol);
    }
    ConstElementPtr format = getItem(xpath + "/dhcp-ddns/ncr-format");
    if (format) {
        ddns->set("ncr-format", format);
    }
    ConstElementPtr always = getItem(xpath + "/dhcp-ddns/always-include-fqdn");
    if (always) {
        ddns->set("always-include-fqdn", always);
    }
    ConstElementPtr no_up = getItem(xpath + "/dhcp-ddns/override-no-update");
    if (no_up) {
        ddns->set("override-no-update", no_up);
    }
    ConstElementPtr client =
        getItem(xpath + "/dhcp-ddns/override-client-update");
    if (client) {
        ddns->set("override-client-update", client);
    }
    ConstElementPtr replace =
        getItem(xpath + "/dhcp-ddns/replace-client-name");
    if (replace) {
        ddns->set("replace-client-name", replace);
    }
    ConstElementPtr generated = getItem(xpath + "/dhcp-ddns/generated-prefix");
    if (generated) {
        ddns->set("generated-prefix", generated);
    }
    ConstElementPtr char_set = getItem(xpath + "/dhcp-ddns/hostname-char-set");
    if (char_set) {
        ddns->set("hostname-char-set", char_set);
    }
    ConstElementPtr char_repl =
        getItem(xpath + "/dhcp-ddns/hostname-char-replacement");
    if (char_repl) {
        ddns->set("hostname-char-replacement", char_repl);
    }
    ConstElementPtr context = getItem(xpath + "/dhcp-ddns/user-context");
    if (context) {
        ddns->set("user-context", Element::fromJSON(context->stringValue()));
    }
    if (ddns->size() > 0) {
        result->set("dhcp-ddns", ddns);
    }
    context = getItem(xpath + "/user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    ConstElementPtr checks = getItem(xpath + "/sanity-checks/lease-checks");
    if (checks) {
        ElementPtr sanity = Element::createMap();
        sanity->set("lease-checks", checks);
        result->set("sanity-checks", sanity);
    }
    ConstElementPtr hosts = getHosts(xpath + "/reservations");
    if (hosts && (hosts->size() > 0)) {
        result->set("reservations", hosts);
    }
    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcp4() {
    string xpath = "/kea-dhcp4-server:config";
    ElementPtr result = getServerKeaDhcpCommon(xpath);
    ConstElementPtr subnets = getSubnets(xpath + "/subnet4");
    if (subnets && (subnets->size() > 0)) {
        result->set("subnet4", subnets);
    }
    ElementPtr if_config = Element::createMap();
    ConstElementPtr ifs = getItems(xpath + "/interfaces-config/interfaces");
    if (ifs && (ifs->size() > 0)) {
        if_config->set("interfaces", ifs);
    }
    ConstElementPtr ds_type =
        getItem(xpath + "/interfaces-config/dhcp-socket-type");
    if (ds_type) {
        if_config->set("dhcp-socket-type", ds_type);
    }
    ConstElementPtr out_if =
        getItem(xpath + "/interfaces-config/outbound-interface");
    if (out_if) {
        if_config->set("outbound-interface", out_if);
    }
    ConstElementPtr redetect =
        getItem(xpath + "/interfaces-config/re-detect");
    if (redetect) {
        if_config->set("re-detect", redetect);
    }
    ConstElementPtr context =
        getItem(xpath + "/interfaces-config/user-context");
    if (context) {
        if_config->set("user-context",
                       Element::fromJSON(context->stringValue()));
    }
    if (if_config->size() > 0) {
        result->set("interfaces-config", if_config);
    }
    ConstElementPtr echo = getItem(xpath + "/echo-client-id");
    if (echo) {
        result->set("echo-client-id", echo);
    }
    ConstElementPtr match = getItem(xpath + "/match-client-id");
    if (match) {
        result->set("match-client-id", match);
    }
    ConstElementPtr next = getItem(xpath + "/next-server");
    if (next) {
        result->set("next-server", next);
    }
    ConstElementPtr hostname = getItem(xpath + "/server-hostname");
    if (hostname) {
        result->set("server-hostname", hostname);
    }
    ConstElementPtr boot = getItem(xpath + "/boot-file-name");
    if (boot) {
        result->set("boot-file-name", boot);
    }
    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcp6() {
    string xpath = "/kea-dhcp6-server:config";
    ElementPtr result = getServerKeaDhcpCommon(xpath);
    ConstElementPtr preferred = getItem(xpath + "/preferred-lifetime");
    if (preferred) {
        result->set("preferred-lifetime", preferred);
    }
    ConstElementPtr subnets = getSubnets(xpath + "/subnet6");
    if (subnets && (subnets->size() > 0)) {
        result->set("subnet6", subnets);
    }
    ElementPtr if_config = Element::createMap();
    ConstElementPtr ifs = getItems(xpath + "/interfaces-config/interfaces");
    if (ifs && (ifs->size() > 0)) {
        if_config->set("interfaces", ifs);
    }
    ConstElementPtr redetect =
        getItem(xpath + "/interfaces-config/re-detect");
    if (redetect) {
        if_config->set("re-detect", redetect);
    }
    ConstElementPtr context =
        getItem(xpath + "/interfaces-config/user-context");
    if (context) {
        if_config->set("user-context",
                       Element::fromJSON(context->stringValue()));
    }
    if (if_config->size() > 0) {
        result->set("interfaces-config", if_config);
    }
    ConstElementPtr relay = getItems(xpath + "/relay-supplied-options");
    if (relay) {
        result->set("relay-supplied-options", relay);
    }
    ConstElementPtr macs = getItems(xpath + "/mac-sources");
    if (macs) {
        result->set("mac-sources", macs);
    }
    ElementPtr server_id = Element::createMap();
    ConstElementPtr id_type = getItem(xpath + "/server-id/type");
    if (id_type) {
        server_id->set("type", id_type);
    }
    ConstElementPtr id_id = getItem(xpath + "/server-id/identifier");
    if (id_id) {
        server_id->set("identifier", id_id);
    }
    ConstElementPtr id_time = getItem(xpath + "/server-id/time");
    if (id_time) {
        server_id->set("time", id_time);
    }
    ConstElementPtr id_htype = getItem(xpath + "/server-id/htype");
    if (id_htype) {
        server_id->set("htype", id_htype);
    }
    ConstElementPtr id_ent_id = getItem(xpath + "/server-id/enterprise-id");
    if (id_ent_id) {
        server_id->set("enterprise-id", id_ent_id);
    }
    ConstElementPtr id_persist = getItem(xpath + "/server-id/persist");
    if (id_persist) {
        server_id->set("persist", id_persist);
    }
    context = getItem(xpath + "/server-id/user-context");
    if (context) {
        server_id->set("user-context",
                       Element::fromJSON(context->stringValue()));
    }
    if (server_id->size() > 0) {
        result->set("server-id", server_id);
    }
    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaLogging() {
    string xpath = "/" + model_ + ":logging";
    ElementPtr result = Element::createMap();
    ConstElementPtr loggers = getLoggers(xpath + "/loggers");
    if (loggers && (loggers->size() > 0)) {
        result->set("loggers", loggers);
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
    if (ranges && (ranges->size() > 0)) {
        setSubnets(xpath + "/network-ranges", ranges);
    }
    // Skip everything else.
}

void
TranslatorConfig::delConfigKea() {
    delItem("/" + model_ + ":config");
    delItem("/" + model_ + ":logging");
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
        setSharedNetworks(xpath + "/shared-networks", networks);
    }
    ConstElementPtr classes = elem->get("client-classes");
    if (classes && (classes->size() > 0)) {
        setClasses(xpath + "/client-classes", classes);
    }
    ConstElementPtr database = elem->get("lease-database");
    if (database) {
        setDatabase(xpath + "/lease-database", database);
    }
    ConstElementPtr databases = elem->get("hosts-databases");
    if (databases) {
        if (databases->size() > 0) {
            setDatabases(xpath + "/hosts-databases", databases);
        }
    } else {
        database = elem->get("hosts-database");
        if (database) {
            ElementPtr list = Element::createList();
            list->add(copy(database));
            setDatabases(xpath + "/hosts-databases", list);
        }
    }
    ConstElementPtr host_ids = elem->get("host-reservation-identifiers");
    if (host_ids) {
        for (ConstElementPtr id : host_ids->listValue()) {
            setItem(xpath + "/host-reservation-identifiers", id, SR_ENUM_T);
        }
    }
    ConstElementPtr defs = elem->get("option-def");
    if (defs && (defs->size() > 0)) {
        setOptionDefList(xpath + "/option-def-list", defs);
    }
    ConstElementPtr options = elem->get("option-data");
    if (options && (options->size() > 0)) {
        setOptionDataList(xpath + "/option-data-list", options);
    }
    ConstElementPtr hook_libs = elem->get("hooks-libraries");
    if (hook_libs) {
        for (ConstElementPtr lib : hook_libs->listValue()) {
            ConstElementPtr name = lib->get("library");
            if (!name) {
                continue;
            }
            ostringstream hook_lib;
            hook_lib << xpath << "/hooks-libraries/hook-library[library='"
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
        ConstElementPtr always = ddns->get("always-include-fqdn");
        if (always) {
            setItem(xpath + "/dhcp-ddns/always-include-fqdn", always,
                    SR_BOOL_T);
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
    ConstElementPtr hosts = elem->get("reservations");
    if (hosts && (hosts->size() > 0)) {
        setHosts(xpath + "/reservations", hosts);
    }
}

void
TranslatorConfig::setServerKeaDhcp4(ConstElementPtr elem) {
    string xpath = "/kea-dhcp4-server:config";
    setServerKeaDhcpCommon(xpath, elem);
    ConstElementPtr subnets = elem->get("subnet4");
    if (subnets) {
        setSubnets(xpath + "/subnet4", subnets);
    }
    ConstElementPtr if_config = elem->get("interfaces-config");
    if (if_config) {
        ConstElementPtr ifs = if_config->get("interfaces");
        if (ifs && (ifs->size() > 0)) {
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
        setSubnets(xpath + "/subnet6", subnets);
    }
    ConstElementPtr if_config = elem->get("interfaces-config");
    if (if_config) {
        ConstElementPtr ifs = if_config->get("interfaces");
        if (ifs && (ifs->size() > 0)) {
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
    string xpath = "/" + model_ + ":logging";
    ConstElementPtr loggers = elem->get("loggers");
    if (loggers) {
        setLoggers(xpath + "/loggers", loggers);
    }
}

}; // end of namespace isc::yang
}; // end of namespace isc
