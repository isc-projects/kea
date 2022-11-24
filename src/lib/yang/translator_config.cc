// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/adaptor_config.h>
#include <yang/translator_config.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorConfig::TranslatorConfig(Session session, const string& model)
    : Translator(session, model),
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
        isc_throw(NetconfError, "getting config: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getConfig not implemented for the model: " << model_);
}

ElementPtr
TranslatorConfig::getConfigIetf6() {
    ElementPtr result = Element::createMap();
    ElementPtr dhcp6 = Element::createMap();
    result->set("Dhcp6", dhcp6);
    string const xpath("/ietf-dhcpv6-server:server");
    optional<DataNode> config;
    try {
        config = findXPath(xpath);
    } catch (NetconfError const&) {
        return result;
    }

    checkAndGetDiverging(dhcp6, *config, "subnet6", "server-config/network-ranges",
                         [&](DataNode const& data_node) -> ElementPtr const {
                             return getSubnets(data_node);
                         });

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

ElementPtr TranslatorConfig::getHook(DataNode const& data_node) {
    ElementPtr hook_library(Element::createMap());
    checkAndGetLeaf(hook_library, data_node, "library");
    checkAndGetAndJsonifyLeaf(hook_library, data_node, "parameters");
    return hook_library;
}

ElementPtr
TranslatorConfig::getHooksKea(DataNode const& data_node) {
    return getList(data_node, "hook-library", *this, &TranslatorConfig::getHook);
}

isc::data::ElementPtr
TranslatorConfig::getExpiredKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    checkAndGetLeaf(result, data_node, "flush-reclaimed-timer-wait-time");
    checkAndGetLeaf(result, data_node, "hold-reclaimed-time");
    checkAndGetLeaf(result, data_node, "max-reclaim-leases");
    checkAndGetLeaf(result, data_node, "max-reclaim-time");
    checkAndGetLeaf(result, data_node, "reclaim-timer-wait-time");
    checkAndGetLeaf(result, data_node, "unwarned-reclaim-cycles");

    return (result->empty() ? ElementPtr() : result);
}

isc::data::ElementPtr
TranslatorConfig::getDdnsKea(DataNode const& data_node) {
    ElementPtr result(Element::createMap());

    checkAndGetLeaf(result, data_node, "enable-updates");
    checkAndGetLeaf(result, data_node, "generated-prefix");
    checkAndGetLeaf(result, data_node, "hostname-char-replacement");
    checkAndGetLeaf(result, data_node, "hostname-char-set");
    checkAndGetLeaf(result, data_node, "max-queue-size");
    checkAndGetLeaf(result, data_node, "ncr-format");
    checkAndGetLeaf(result, data_node, "ncr-protocol");
    checkAndGetLeaf(result, data_node, "qualifying-suffix");
    checkAndGetLeaf(result, data_node, "override-client-update");
    checkAndGetLeaf(result, data_node, "override-no-update");
    checkAndGetLeaf(result, data_node, "replace-client-name");
    checkAndGetLeaf(result, data_node, "sender-ip");
    checkAndGetLeaf(result, data_node, "sender-port");
    checkAndGetLeaf(result, data_node, "server-ip");
    checkAndGetLeaf(result, data_node, "server-port");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorConfig::getConfigControlKea(DataNode const& data_node) {
    ElementPtr result(Element::createMap());
    checkAndGetLeaf(result, data_node, "config-fetch-wait-time");
    ConstElementPtr databases = getDatabases(data_node, "config-database");
    if (databases && !databases->empty()) {
        result->set("config-databases", databases);
    }
    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorConfig::getInterfacesKea(DataNode const& config) {
    ElementPtr result;
    optional<DataNode> const& interfaces_config_optional(config.findPath("interfaces-config"));
    if (interfaces_config_optional) {
        DataNode const interfaces_config(*interfaces_config_optional);
        result = Element::createMap();

        checkAndGetLeaf(result, interfaces_config, "dhcp-socket-type");
        checkAndGetLeaf(result, interfaces_config, "interfaces");
        checkAndGetLeaf(result, interfaces_config, "outbound-interface");
        checkAndGetLeaf(result, interfaces_config, "re-detect");
        checkAndGetLeaf(result, interfaces_config, "service-sockets-max-retries");
        checkAndGetLeaf(result, interfaces_config, "service-sockets-require-all");
        checkAndGetLeaf(result, interfaces_config, "service-sockets-retry-wait-time");

        checkAndGetAndJsonifyLeaf(result, interfaces_config, "user-context");
    }
    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcpCommon(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    checkAndGetLeaf(result, data_node, "cache-max-age");
    checkAndGetLeaf(result, data_node, "cache-threshold");
    checkAndGetLeaf(result, data_node, "calculate-tee-times");
    checkAndGetLeaf(result, data_node, "dhcp4o6-port");
    checkAndGetLeaf(result, data_node, "ddns-generated-prefix");
    checkAndGetLeaf(result, data_node, "ddns-override-client-update");
    checkAndGetLeaf(result, data_node, "ddns-override-no-update");
    checkAndGetLeaf(result, data_node, "ddns-qualifying-suffix");
    checkAndGetLeaf(result, data_node, "ddns-replace-client-name");
    checkAndGetLeaf(result, data_node, "ddns-send-updates");
    checkAndGetLeaf(result, data_node, "ddns-update-on-renew");
    checkAndGetLeaf(result, data_node, "ddns-use-conflict-resolution");
    checkAndGetLeaf(result, data_node, "decline-probation-period");
    checkAndGetLeaf(result, data_node, "early-global-reservations-lookup");
    checkAndGetLeaf(result, data_node, "host-reservation-identifiers");
    checkAndGetLeaf(result, data_node, "hostname-char-replacement");
    checkAndGetLeaf(result, data_node, "hostname-char-set");
    checkAndGetLeaf(result, data_node, "ip-reservations-unique");
    checkAndGetLeaf(result, data_node, "max-valid-lifetime");
    checkAndGetLeaf(result, data_node, "min-valid-lifetime");
    checkAndGetLeaf(result, data_node, "parked-packet-limit");
    checkAndGetLeaf(result, data_node, "rebind-timer");
    checkAndGetLeaf(result, data_node, "renew-timer");
    checkAndGetLeaf(result, data_node, "reservation-mode");
    checkAndGetLeaf(result, data_node, "reservations-global");
    checkAndGetLeaf(result, data_node, "reservations-in-subnet");
    checkAndGetLeaf(result, data_node, "reservations-lookup-first");
    checkAndGetLeaf(result, data_node, "reservations-out-of-pool");
    checkAndGetLeaf(result, data_node, "server-tag");
    checkAndGetLeaf(result, data_node, "statistic-default-sample-age");
    checkAndGetLeaf(result, data_node, "statistic-default-sample-count");
    checkAndGetLeaf(result, data_node, "store-extended-info");
    checkAndGetLeaf(result, data_node, "t1-percent");
    checkAndGetLeaf(result, data_node, "t2-percent");
    checkAndGetLeaf(result, data_node, "valid-lifetime");

    checkAndGetAndJsonifyLeaf(result, data_node, "dhcp-queue-control");
    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    ConstElementPtr classes = getClasses(data_node);
    if (classes && !classes->empty()) {
        result->set("client-classes", classes);
    }

    checkAndGet(result, data_node, "compatibility",
                [&](DataNode const& node) -> ElementPtr const {
                    ElementPtr compatibility(Element::createMap());
                    checkAndGetLeaf(compatibility, node, "ignore-rai-link-selection");
                    checkAndGetLeaf(compatibility, node, "lenient-option-parsing");
                    return compatibility;
                });

    checkAndGet(result, data_node, "config-control",
                [&](DataNode const& node) -> ElementPtr const {
                    return getConfigControlKea(node);
                });

    checkAndGet(result, data_node, "control-socket",
                [&](DataNode const& node) -> ElementPtr const {
                    return getControlSocket(node);
                });

    checkAndGet(result, data_node, "dhcp-ddns",
                [&](DataNode const& node) -> ElementPtr const {
                    return getDdnsKea(node);
                });

    checkAndGet(result, data_node, "expired-leases-processing",
                [&](DataNode const& node) -> ElementPtr const {
                    return getExpiredKea(node);
                });

    ConstElementPtr hooks = getHooksKea(data_node);
    if (hooks && !hooks->empty()) {
        result->set("hooks-libraries", hooks);
    }

    ConstElementPtr const& hosts_databases(getDatabases(data_node, "hosts-database"));
    if (hosts_databases && !hosts_databases->empty()) {
        result->set("hosts-databases", hosts_databases);
    }

    checkAndGet(result, data_node, "lease-database",
                [&](DataNode const& node) -> ElementPtr const {
                    return getDatabase(node);
                });

    ConstElementPtr loggers = getLoggers(data_node);
    if (loggers && !loggers->empty()) {
        result->set("loggers", loggers);
    }

    checkAndGet(result, data_node, "multi-threading",
                [&](DataNode const& node) -> ElementPtr const {
                    ElementPtr multi_threading(Element::createMap());
                    checkAndGetLeaf(multi_threading, node, "enable-multi-threading");
                    checkAndGetLeaf(multi_threading, node, "packet-queue-size");
                    checkAndGetLeaf(multi_threading, node, "thread-pool-size");
                    return multi_threading;
                });

    ConstElementPtr options = getOptionDataList(data_node);
    if (options) {
        result->set("option-data", options);
    }

    ConstElementPtr defs = getOptionDefList(data_node);
    if (defs) {
        result->set("option-def", defs);
    }

    ConstElementPtr hosts = getHosts(data_node);
    if (hosts) {
        result->set("reservations", hosts);
    }

    ConstElementPtr networks = getSharedNetworks(data_node);
    if (networks) {
        result->set("shared-networks", networks);
    }

    checkAndGet(result, data_node, "sanity-checks",
                [&](DataNode const& node) -> ElementPtr const {
                    ElementPtr sanity_checks = Element::createMap();
                    checkAndGetLeaf(sanity_checks, node, "extended-info-checks");
                    checkAndGetLeaf(sanity_checks, node, "lease-checks");
                    return sanity_checks;
                });

    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcp4() {
    string xpath = "/kea-dhcp4-server:config";
    optional<DataNode> config_optional;
    try {
        config_optional = findXPath(xpath);
    } catch (NetconfError const&) {
        return ElementPtr();
    }
    DataNode const config(*config_optional);
    ElementPtr result = getServerKeaDhcpCommon(config);

    // Handle DHCPv4 specific global parameters.
    checkAndGetLeaf(result, config, "authoritative");
    checkAndGetLeaf(result, config, "boot-file-name");
    checkAndGetLeaf(result, config, "echo-client-id");
    checkAndGetLeaf(result, config, "match-client-id");
    checkAndGetLeaf(result, config, "next-server");
    checkAndGetLeaf(result, config, "server-hostname");

    // Handle interfaces.
    ElementPtr interfaces_config(getInterfacesKea(config));
    if (interfaces_config) {
        result->set("interfaces-config", interfaces_config);
    }

    // Handle subnets.
    ConstElementPtr subnets = getSubnets(config);
    if (subnets) {
        result->set("subnet4", subnets);
    }

    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcp6() {
    string xpath = "/kea-dhcp6-server:config";
    optional<DataNode> config_optional;
    try {
        config_optional = findXPath(xpath);
    } catch (NetconfError const&) {
        return ElementPtr();
    }
    DataNode const config(*config_optional);
    ElementPtr result = getServerKeaDhcpCommon(config);

    // Handle DHCPv6 specific global parameters.
    checkAndGetLeaf(result, config, "data-directory");
    checkAndGetLeaf(result, config, "mac-sources");
    checkAndGetLeaf(result, config, "max-preferred-lifetime");
    checkAndGetLeaf(result, config, "min-preferred-lifetime");
    checkAndGetLeaf(result, config, "preferred-lifetime");
    checkAndGetLeaf(result, config, "relay-supplied-options");

    // Handle interfaces.
    ElementPtr interfaces_config(getInterfacesKea(config));
    if (interfaces_config) {
        result->set("interfaces-config", interfaces_config);
    }

    // Handle server-id.
    optional<DataNode> const& server_id_optional(config.findPath("server-id"));
    if (server_id_optional) {
        DataNode const server_id(*server_id_optional);
        ElementPtr server_id_map(Element::createMap());
        checkAndGetLeaf(server_id_map, server_id, "type");
        checkAndGetLeaf(server_id_map, server_id, "identifier");
        checkAndGetLeaf(server_id_map, server_id, "time");
        checkAndGetLeaf(server_id_map, server_id, "htype");
        checkAndGetLeaf(server_id_map, server_id, "enterprise-id");
        checkAndGetLeaf(server_id_map, server_id, "persist");
        checkAndGetAndJsonifyLeaf(server_id_map, server_id, "user-context");
        if (!server_id_map->empty()) {
            result->set("server-id", server_id_map);
        }
    }

    // Handle subnets.
    ConstElementPtr subnets = getSubnets(config);
    if (subnets) {
        result->set("subnet6", subnets);
    }

    return (result);
}

void
TranslatorConfig::setConfig(ElementPtr elem) {
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
        isc_throw(NetconfError,
                  "setting config '" << elem->str()
                  << "': " << ex.what());
    }
}

void
TranslatorConfig::delConfigIetf6() {
    deleteItem("/" + model_ + ":server");
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
    deleteItem("/" + model_ + ":config");
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
TranslatorConfig::setServerKeaDhcpCommon(string const& xpath,
                                         ConstElementPtr elem) {
    checkAndSetLeaf(elem, xpath, "cache-max-age", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "cache-threshold", LeafBaseType::Dec64);
    checkAndSetLeaf(elem, xpath, "calculate-tee-times", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-generated-prefix", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-override-client-update", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-override-no-update", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-qualifying-suffix", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-replace-client-name", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-send-updates", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-update-on-renew", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-use-conflict-resolution", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "dhcp4o6-port", LeafBaseType::Uint16);
    checkAndSetLeaf(elem, xpath, "decline-probation-period", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "early-global-reservations-lookup", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "hostname-char-replacement", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "hostname-char-set", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ip-reservations-unique", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "max-valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "min-valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "parked-packet-limit", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "rebind-timer", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "renew-timer", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "reservation-mode", LeafBaseType::Enum);
    checkAndSetLeaf(elem, xpath, "reservations-global", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-in-subnet", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-lookup-first", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-out-of-pool", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "server-tag", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "statistic-default-sample-age", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "statistic-default-sample-count", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "store-extended-info", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "t1-percent", LeafBaseType::Dec64);
    checkAndSetLeaf(elem, xpath, "t2-percent", LeafBaseType::Dec64);
    checkAndSetLeaf(elem, xpath, "valid-lifetime", LeafBaseType::Uint32);

    checkAndSetLeafList(elem, xpath, "host-reservation-identifiers", LeafBaseType::Enum);

    checkAndStringifyAndSetLeaf(elem, xpath, "dhcp-queue-control");

    checkAndSetUserContext(elem, xpath);

    ConstElementPtr classes = elem->get("client-classes");
    if (classes && !classes->empty()) {
        setClasses(xpath, classes);
    }

    ConstElementPtr compatibility(elem->get("compatibility"));
    if (compatibility) {
        checkAndSetLeaf(compatibility, xpath + "/compatibility", "ignore-rai-link-selection", LeafBaseType::Bool);
        checkAndSetLeaf(compatibility, xpath + "/compatibility", "lenient-option-parsing", LeafBaseType::Bool);
    }

    ConstElementPtr config_ctrl = elem->get("config-control");
    if (config_ctrl && !config_ctrl->empty()) {
        checkAndSetLeaf(config_ctrl, xpath + "/config-control", "config-fetch-wait-time", LeafBaseType::Uint32);
        ConstElementPtr config_databases = config_ctrl->get("config-databases");
        if (config_databases && !config_databases->empty()) {
            setDatabases(xpath + "/config-control/config-database", config_databases);
        }
    }

    ConstElementPtr socket = elem->get("control-socket");
    if (socket && !socket->empty()) {
        setControlSocket(xpath + "/control-socket", socket);
    }

    ConstElementPtr ddns = elem->get("dhcp-ddns");
    if (ddns) {
        string const ddns_xpath(xpath + "/dhcp-ddns");
        checkAndSetLeaf(ddns, ddns_xpath, "enable-updates", LeafBaseType::Bool);
        checkAndSetLeaf(ddns, ddns_xpath, "generated-prefix", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "hostname-char-replacement", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "hostname-char-set", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "max-queue-size", LeafBaseType::Uint32);
        checkAndSetLeaf(ddns, ddns_xpath, "ncr-format", LeafBaseType::Enum);
        checkAndSetLeaf(ddns, ddns_xpath, "ncr-protocol", LeafBaseType::Enum);
        checkAndSetLeaf(ddns, ddns_xpath, "override-client-update", LeafBaseType::Bool);
        checkAndSetLeaf(ddns, ddns_xpath, "override-no-update", LeafBaseType::Bool);
        checkAndSetLeaf(ddns, ddns_xpath, "qualifying-suffix", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "replace-client-name", LeafBaseType::Enum);
        checkAndSetLeaf(ddns, ddns_xpath, "sender-ip", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "sender-port", LeafBaseType::Uint16);
        checkAndSetLeaf(ddns, ddns_xpath, "server-ip", LeafBaseType::String);
        checkAndSetLeaf(ddns, ddns_xpath, "server-port", LeafBaseType::Uint16);
        checkAndSetUserContext(ddns, ddns_xpath);
    }

    ConstElementPtr expired = elem->get("expired-leases-processing");
    if (expired) {
        string const expired_xpath(xpath + "/expired-leases-processing");
        checkAndSetLeaf(expired, expired_xpath, "flush-reclaimed-timer-wait-time", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "hold-reclaimed-time", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "max-reclaim-leases", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "max-reclaim-time", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "reclaim-timer-wait-time", LeafBaseType::Uint32);
        checkAndSetLeaf(expired, expired_xpath, "unwarned-reclaim-cycles", LeafBaseType::Uint32);
    }

    ConstElementPtr hook_libs = elem->get("hooks-libraries");
    if (hook_libs) {
        for (ElementPtr const& lib : hook_libs->listValue()) {
            ConstElementPtr name = lib->get("library");
            if (!name) {
                continue;
            }
            ostringstream hook_lib;
            hook_lib << xpath << "/hook-library[library='"
                     << name->stringValue() << "']";
            string const hook_xpath(hook_lib.str());
            setItem(hook_xpath, ElementPtr(), LeafBaseType::Unknown);
            checkAndStringifyAndSetLeaf(lib, hook_xpath, "parameters");
        }
    }

    ConstElementPtr hosts_databases = elem->get("hosts-databases");
    if (hosts_databases && !hosts_databases->empty()) {
        setDatabases(xpath + "/hosts-database", hosts_databases);
    }

    ConstElementPtr database = elem->get("lease-database");
    if (database && !database->empty()) {
        setDatabase(xpath + "/lease-database", database);
    }

    ConstElementPtr loggers = elem->get("loggers");
    if (loggers) {
        setLoggers(xpath, loggers);
    }

    ConstElementPtr multi_threading(elem->get("multi-threading"));
    if (multi_threading) {
        string const mt_xpath(xpath + "/multi-threading");
        checkAndSetLeaf(multi_threading, mt_xpath, "enable-multi-threading", LeafBaseType::Bool);
        checkAndSetLeaf(multi_threading, mt_xpath, "packet-queue-size", LeafBaseType::Uint32);
        checkAndSetLeaf(multi_threading, mt_xpath, "thread-pool-size", LeafBaseType::Uint32);
    }

    ConstElementPtr options = elem->get("option-data");
    if (options && !options->empty()) {
        setOptionDataList(xpath, options);
    }

    ConstElementPtr defs = elem->get("option-def");
    if (defs && !defs->empty()) {
        setOptionDefList(xpath, defs);
    }

    ConstElementPtr hosts = elem->get("reservations");
    if (hosts && !hosts->empty()) {
        setHosts(xpath, hosts);
    }

    ConstElementPtr sanity = elem->get("sanity-checks");
    if (sanity) {
        checkAndSetLeaf(sanity, xpath + "/sanity-checks", "extended-info-checks", LeafBaseType::Enum);
        checkAndSetLeaf(sanity, xpath + "/sanity-checks", "lease-checks", LeafBaseType::Enum);
    }

    ConstElementPtr networks = elem->get("shared-networks");
    if (networks && !networks->empty()) {
        setSharedNetworks(xpath, networks);
    }
}

void
TranslatorConfig::setServerKeaDhcp4(ConstElementPtr elem) {
    string xpath = "/kea-dhcp4-server:config";

    setServerKeaDhcpCommon(xpath, elem);

    checkAndSetLeaf(elem, xpath, "authoritative", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "boot-file-name", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "echo-client-id", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "match-client-id", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "next-server", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "server-hostname", LeafBaseType::String);

    ConstElementPtr if_config = elem->get("interfaces-config");
    if (if_config) {
        string const if_cfg_xpath(xpath + "/interfaces-config");
        checkAndSetLeaf(if_config, if_cfg_xpath, "dhcp-socket-type", LeafBaseType::Enum);
        checkAndSetLeaf(if_config, if_cfg_xpath, "outbound-interface", LeafBaseType::Enum);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-max-retries", LeafBaseType::Uint32);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-require-all", LeafBaseType::Bool);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-retry-wait-time", LeafBaseType::Uint32);
        checkAndSetLeaf(if_config, if_cfg_xpath, "re-detect", LeafBaseType::Bool);
        checkAndSetLeafList(if_config, if_cfg_xpath, "interfaces", LeafBaseType::String);
        checkAndSetUserContext(if_config, if_cfg_xpath);
    }

    ConstElementPtr subnets = elem->get("subnet4");
    if (subnets) {
        setSubnets(xpath, subnets);
    }
}

void
TranslatorConfig::setServerKeaDhcp6(ConstElementPtr elem) {
    string xpath = "/kea-dhcp6-server:config";

    setServerKeaDhcpCommon(xpath, elem);

    checkAndSetLeaf(elem, xpath, "data-directory", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "max-preferred-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "min-preferred-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "preferred-lifetime", LeafBaseType::Uint32);

    checkAndSetLeafList(elem, xpath, "mac-sources", LeafBaseType::String);
    checkAndSetLeafList(elem, xpath, "relay-supplied-options", LeafBaseType::String);

    ConstElementPtr if_config = elem->get("interfaces-config");
    if (if_config) {
        string const if_cfg_xpath(xpath + "/interfaces-config");
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-max-retries", LeafBaseType::Uint32);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-require-all", LeafBaseType::Bool);
        checkAndSetLeaf(if_config, if_cfg_xpath, "service-sockets-retry-wait-time", LeafBaseType::Uint32);
        checkAndSetLeaf(if_config, if_cfg_xpath, "re-detect", LeafBaseType::Bool);
        checkAndSetLeafList(if_config, if_cfg_xpath, "interfaces", LeafBaseType::String);
        checkAndSetUserContext(if_config, if_cfg_xpath);
    }

    ConstElementPtr server_id = elem->get("server-id");
    if (server_id) {
        string const srv_id_xpath(xpath + "/server-id");
        checkAndSetLeaf(server_id, srv_id_xpath, "type", LeafBaseType::Enum);
        checkAndSetLeaf(server_id, srv_id_xpath, "identifier", LeafBaseType::String);
        checkAndSetLeaf(server_id, srv_id_xpath, "time", LeafBaseType::Uint32);
        checkAndSetLeaf(server_id, srv_id_xpath, "htype", LeafBaseType::Uint16);
        checkAndSetLeaf(server_id, srv_id_xpath, "enterprise-id", LeafBaseType::Uint32);
        checkAndSetLeaf(server_id, srv_id_xpath, "persist", LeafBaseType::Bool);
        checkAndSetUserContext(server_id, srv_id_xpath);
    }

    ConstElementPtr subnets = elem->get("subnet6");
    if (subnets) {
        setSubnets(xpath, subnets);
    }
}

}  // namespace yang
}  // namespace isc
