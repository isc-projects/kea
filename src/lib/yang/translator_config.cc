// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorConfig::TranslatorConfig(Session session, const string& model)
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
    } catch (Error const& ex) {
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
    checkAndGetLeaf(result, xpath, "early-global-reservations-lookup");
    checkAndGetLeaf(result, xpath, "reservations-lookup-first");
    ElementPtr multi_threading = Element::createMap();
    string mt_xpath = xpath + "/multi-threading";
    checkAndGetLeaf(multi_threading, mt_xpath, "enable-multi-threading");
    checkAndGetLeaf(multi_threading, mt_xpath, "packet-queue-size");
    checkAndGetLeaf(multi_threading, mt_xpath, "thread-pool-size");
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
    string if_cfg_xpath = xpath + "/interfaces-config";
    checkAndGetLeaf(if_config, if_cfg_xpath, "dhcp-socket-type");
    checkAndGetLeaf(if_config, if_cfg_xpath, "outbound-interface");
    checkAndGetLeaf(if_config, if_cfg_xpath, "service-sockets-require-all");
    checkAndGetLeaf(if_config, if_cfg_xpath, "service-sockets-max-retries");
    checkAndGetLeaf(if_config, if_cfg_xpath, "service-sockets-retry-wait-time");
    checkAndGetLeaf(if_config, if_cfg_xpath, "re-detect");
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
    string if_cfg_xpath = xpath + "/interfaces-config";
    checkAndGetLeaf(if_config, if_cfg_xpath, "service-sockets-require-all");
    checkAndGetLeaf(if_config, if_cfg_xpath, "service-sockets-max-retries");
    checkAndGetLeaf(if_config, if_cfg_xpath, "service-sockets-retry-wait-time");
    checkAndGetLeaf(if_config, if_cfg_xpath, "re-detect");
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
    string srv_id_xpath = xpath + "/server-id";
    checkAndGetLeaf(server_id, srv_id_xpath, "type");
    checkAndGetLeaf(server_id, srv_id_xpath, "identifier");
    checkAndGetLeaf(server_id, srv_id_xpath, "time");
    checkAndGetLeaf(server_id, srv_id_xpath, "htype");
    checkAndGetLeaf(server_id, srv_id_xpath, "enterprise-id");
    checkAndGetLeaf(server_id, srv_id_xpath, "persist");
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
    } catch (Error const& ex) {
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
    checkAndSetLeaf(elem, xpath, "valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "min-valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "max-valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "renew-timer", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "rebind-timer", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "calculate-tee-times", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "t1-percent", LeafBaseType::Dec64);
    checkAndSetLeaf(elem, xpath, "t2-percent", LeafBaseType::Dec64);
    checkAndSetLeaf(elem, xpath, "decline-probation-period", LeafBaseType::Uint32);
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
            setItem(xpath + "/host-reservation-identifiers", id, LeafBaseType::Enum);
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
            setItem(hook_lib.str(), ElementPtr(), LeafBaseType::Unknown);
            ConstElementPtr params = lib->get("parameters");
            if (params) {
                hook_lib << "/parameters";
                setItem(hook_lib.str(), Element::create(params->str()),
                        LeafBaseType::String);
            }
        }
    }
    ConstElementPtr expired = elem->get("expired-leases-processing");
    if (expired) {
        string expired_xpath = xpath + "/expired-leases-processing";
        checkAndSetLeaf(expired, expired_xpath, "reclaim-timer-wait-time", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "flush-reclaimed-timer-wait-time", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "hold-reclaimed-time", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "max-reclaim-leases", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "max-reclaim-time", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "unwarned-reclaim-cycles", LeafBaseType::Uint32);
    }
    checkAndSetLeaf(elem, xpath, "dhcp4o6-port", LeafBaseType::Uint16);
    ConstElementPtr socket = elem->get("control-socket");
    if (socket) {
        setControlSocket(xpath + "/control-socket", socket);
    }
    checkAndSetLeaf(elem, xpath, "hostname-char-set", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "hostname-char-replacement", LeafBaseType::String);
    ConstElementPtr ddns = elem->get("dhcp-ddns");
    if (ddns) {
        string ddns_xpath = xpath + "/dhcp-ddns";
        checkAndSetLeaf(ddns, ddns_xpath, "enable-updates", LeafBaseType::Bool);
        checkAndSetLeaf(ddns, ddns_xpath, "qualifying-suffix", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "server-ip", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "server-port", LeafBaseType::Uint16);
        checkAndSetLeaf(ddns, ddns_xpath, "sender-ip", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "sender-port", LeafBaseType::Uint16);
        checkAndSetLeaf(ddns, ddns_xpath, "max-queue-size", LeafBaseType::Uint32);
        checkAndSetLeaf(ddns, ddns_xpath, "ncr-protocol", LeafBaseType::Enum);
        checkAndSetLeaf(ddns, ddns_xpath, "ncr-format", LeafBaseType::Enum);
        checkAndSetLeaf(ddns, ddns_xpath, "override-no-update", LeafBaseType::Bool);
        checkAndSetLeaf(ddns, ddns_xpath, "override-client-update", LeafBaseType::Bool);
        checkAndSetLeaf(ddns, ddns_xpath, "replace-client-name", LeafBaseType::Enum);
        checkAndSetLeaf(ddns, ddns_xpath, "generated-prefix", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "hostname-char-set", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "hostname-char-replacement", LeafBaseType::String);
        ConstElementPtr context = Adaptor::getContext(ddns);
        if (context) {
            ConstElementPtr repr = Element::create(context->str());
            setItem(xpath + "/dhcp-ddns/user-context", repr, LeafBaseType::String);
        }
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        ConstElementPtr repr = Element::create(context->str());
        setItem(xpath + "/user-context", repr, LeafBaseType::String);
    }
    ConstElementPtr sanity = elem->get("sanity-checks");
    if (sanity) {
        checkAndSetLeaf(sanity, xpath + "/sanity-checks", "lease-checks", LeafBaseType::Enum);
    }
    checkAndSetLeaf(elem, xpath, "reservation-mode", LeafBaseType::Enum);
    ConstElementPtr hosts = elem->get("reservations");
    if (hosts && !hosts->empty()) {
        setHosts(xpath, hosts);
    }
    ConstElementPtr config_ctrl = elem->get("config-control");
    if (config_ctrl && !config_ctrl->empty()) {
        checkAndSetLeaf(config_ctrl, xpath + "/config-control", "config-fetch-wait-time", LeafBaseType::Uint32);
        databases = config_ctrl->get("config-databases");
        if (databases && !databases->empty()) {
            setDatabases(xpath + "/config-control/config-database", databases);
        }
    }
    checkAndSetLeaf(elem, xpath, "server-tag", LeafBaseType::String);
    ConstElementPtr queue_ctrl = elem->get("dhcp-queue-control");
    if (queue_ctrl) {
        ConstElementPtr repr = Element::create(queue_ctrl->str());
        setItem(xpath + "/dhcp-queue-control", repr, LeafBaseType::String);
    }
    ConstElementPtr loggers = elem->get("loggers");
    if (loggers) {
        setLoggers(xpath, loggers);
    }
    checkAndSetLeaf(elem, xpath, "cache-max-age", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "cache-threshold", LeafBaseType::Dec64);
    ConstElementPtr compatibility(elem->get("compatibility"));
    if (compatibility) {
        checkAndSetLeaf(compatibility, xpath + "/compatibility", "lenient-option-parsing", LeafBaseType::Bool);
    }
    checkAndSetLeaf(elem, xpath, "ddns-generated-prefix", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-override-client-update", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-override-no-update", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-qualifying-suffix", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-replace-client-name", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-send-updates", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-update-on-renew", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-use-conflict-resolution", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ip-reservations-unique", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "early-global-reservations-lookup", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-lookup-first", LeafBaseType::Bool);
    ConstElementPtr multi_threading(elem->get("multi-threading"));
    if (multi_threading) {
        string mt_xpath = xpath + "/multi-threading";
        checkAndSetLeaf(multi_threading, mt_xpath, "enable-multi-threading", LeafBaseType::Bool);
        checkAndSetLeaf(multi_threading, mt_xpath, "packet-queue-size", LeafBaseType::Uint32);
        checkAndSetLeaf(multi_threading, mt_xpath, "thread-pool-size", LeafBaseType::Uint32);
    }
    checkAndSetLeaf(elem, xpath, "parked-packet-limit", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "reservations-global", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-in-subnet", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-out-of-pool", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "statistic-default-sample-age", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "statistic-default-sample-count", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "store-extended-info", LeafBaseType::Bool);
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
                        intf, LeafBaseType::String);
            }
        }
        string if_cfg_xpath = xpath + "/interfaces-config";
        checkAndSetLeaf(if_config, if_cfg_xpath, "dhcp-socket-type", LeafBaseType::Enum);
        checkAndSetLeaf(if_config, if_cfg_xpath, "outbound-interface", LeafBaseType::Enum);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-require-all", LeafBaseType::Bool);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-max-retries", LeafBaseType::Uint32);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-retry-wait-time", LeafBaseType::Uint32);
        checkAndSetLeaf(if_config, if_cfg_xpath, "re-detect", LeafBaseType::Bool);
        ConstElementPtr context = Adaptor::getContext(if_config);
        if (context) {
            setItem(xpath + "/interfaces-config/user-context",
                    Element::create(context->str()), LeafBaseType::String);
        }
    }
    checkAndSetLeaf(elem, xpath, "echo-client-id", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "match-client-id", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "next-server", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "server-hostname", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "boot-file-name", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "authoritative", LeafBaseType::Bool);
}

void
TranslatorConfig::setServerKeaDhcp6(ConstElementPtr elem) {
    string xpath = "/kea-dhcp6-server:config";
    setServerKeaDhcpCommon(xpath, elem);
    checkAndSetLeaf(elem, xpath, "data-directory", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "preferred-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "min-preferred-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "max-preferred-lifetime", LeafBaseType::Uint32);
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
                        intf, LeafBaseType::String);
            }
        }
        string if_cfg_xpath = xpath + "/interfaces-config";
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-require-all", LeafBaseType::Bool);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-max-retries", LeafBaseType::Uint32);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-retry-wait-time", LeafBaseType::Uint32);
        checkAndSetLeaf(if_config, if_cfg_xpath, "re-detect", LeafBaseType::Bool);
        ConstElementPtr context = Adaptor::getContext(if_config);
        if (context) {
            setItem(xpath + "/interfaces-config/user-context",
                    Element::create(context->str()), LeafBaseType::String);
        }
    }
    ConstElementPtr relay = elem->get("relay-supplied-options");
    if (relay) {
        for (ConstElementPtr addr : relay->listValue()) {
            setItem(xpath + "/relay-supplied-options", addr, LeafBaseType::String);
        }
    }
    ConstElementPtr macs = elem->get("mac-sources");
    if (macs) {
        for (ConstElementPtr source : macs->listValue()) {
            setItem(xpath + "/mac-sources", source, LeafBaseType::String);
        }
    }
    ConstElementPtr server_id = elem->get("server-id");
    if (server_id) {
        string srv_id_xpath = xpath + "/server-id";
        checkAndSetLeaf(server_id, srv_id_xpath, "type", LeafBaseType::Enum);
        checkAndSetLeaf(server_id, srv_id_xpath, "identifier", LeafBaseType::String);
        checkAndSetLeaf(server_id, srv_id_xpath, "time", LeafBaseType::Uint32);
        checkAndSetLeaf(server_id, srv_id_xpath, "htype", LeafBaseType::Uint16);
        checkAndSetLeaf(server_id, srv_id_xpath, "enterprise-id", LeafBaseType::Uint32);
        checkAndSetLeaf(server_id, srv_id_xpath, "persist", LeafBaseType::Bool);
        ConstElementPtr context = Adaptor::getContext(server_id);
        if (context) {
            ConstElementPtr repr = Element::create(context->str());
            setItem(xpath + "/server-id/user-context", repr, LeafBaseType::String);
        }
    }
}

}  // namespace yang
}  // namespace isc
