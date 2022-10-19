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
    string const xpath("/ietf-dhcpv6-server:server");
    optional<DataNode> config;
    try {
        config = findXPath(xpath);
    } catch(SysrepoError const&) {
        return result;
    }
    Set<DataNode> const& nodes(config->findXPath("server-config/network-ranges"));
    if (!nodes.empty()) {
        ConstElementPtr ranges = getSubnets(nodes.front());
        if (ranges && !ranges->empty()) {
            dhcp6->set("subnet6", ranges);
        }
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

ElementPtr TranslatorConfig::getHook(DataNode const& data_node) {
    ElementPtr const& hook_library(Element::createMap());
    ElementPtr const& name(getItem(data_node, "library"));
    if (name) {
        hook_library->set("library", name);
        ElementPtr const& parameters(getItem(data_node, "parameters"));
        if (parameters) {
            hook_library->set("parameters",
                              Element::fromJSON(parameters->stringValue()));
        }
    }
    return hook_library;
}

ElementPtr
TranslatorConfig::getHooksKea(DataNode const& data_node) {
    return getList(data_node, "hook-library", *this, &TranslatorConfig::getHook);
}

isc::data::ElementPtr
TranslatorConfig::getExpiredKea(DataNode const& data_node) {
    ElementPtr expired = Element::createMap();

    checkAndGetLeaf(expired, data_node, "reclaim-timer-wait-time");
    checkAndGetLeaf(expired, data_node, "flush-reclaimed-timer-wait-time");
    checkAndGetLeaf(expired, data_node, "hold-reclaimed-time");
    checkAndGetLeaf(expired, data_node, "max-reclaim-leases");
    checkAndGetLeaf(expired, data_node, "max-reclaim-time");
    checkAndGetLeaf(expired, data_node, "unwarned-reclaim-cycles");

    if (!expired->empty()) {
        return (expired);
    }

    return (ElementPtr());
}

isc::data::ElementPtr
TranslatorConfig::getDdnsKea(DataNode const& data_node) {
    ElementPtr ddns = Element::createMap();
    checkAndGetLeaf(ddns, data_node, "enable-updates");
    checkAndGetLeaf(ddns, data_node, "qualifying-suffix");
    checkAndGetLeaf(ddns, data_node, "server-ip");
    checkAndGetLeaf(ddns, data_node, "server-port");
    checkAndGetLeaf(ddns, data_node, "sender-ip");
    checkAndGetLeaf(ddns, data_node, "sender-port");
    checkAndGetLeaf(ddns, data_node, "max-queue-size");
    checkAndGetLeaf(ddns, data_node, "ncr-protocol");
    checkAndGetLeaf(ddns, data_node, "ncr-format");
    checkAndGetLeaf(ddns, data_node, "override-no-update");
    checkAndGetLeaf(ddns, data_node, "override-client-update");
    checkAndGetLeaf(ddns, data_node, "replace-client-name");
    checkAndGetLeaf(ddns, data_node, "generated-prefix");
    checkAndGetLeaf(ddns, data_node, "hostname-char-set");
    checkAndGetLeaf(ddns, data_node, "hostname-char-replacement");

    ConstElementPtr context = getItem(data_node, "user-context");
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
TranslatorConfig::getConfigControlKea(DataNode const& data_node) {
    ElementPtr config_ctrl = Element::createMap();
    checkAndGetLeaf(config_ctrl, data_node, "config-fetch-wait-time");
    ConstElementPtr databases = getDatabases(data_node, "config-database");
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
        checkAndGetLeaf(result, interfaces_config, "service-sockets-require-all");
        checkAndGetLeaf(result, interfaces_config, "service-sockets-max-retries");
        checkAndGetLeaf(result, interfaces_config, "service-sockets-retry-wait-time");
        ConstElementPtr const& context(getItem(interfaces_config, "user-context"));
        if (context) {
            result->set("user-context", Element::fromJSON(context->stringValue()));
        }
    }
    return result;
}

ElementPtr
TranslatorConfig::getServerKeaDhcpCommon(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    checkAndGetLeaf(result, data_node, "valid-lifetime");
    checkAndGetLeaf(result, data_node, "min-valid-lifetime");
    checkAndGetLeaf(result, data_node, "max-valid-lifetime");
    checkAndGetLeaf(result, data_node, "renew-timer");
    checkAndGetLeaf(result, data_node, "rebind-timer");
    checkAndGetLeaf(result, data_node, "calculate-tee-times");
    checkAndGetLeaf(result, data_node, "t1-percent");
    checkAndGetLeaf(result, data_node, "t2-percent");
    checkAndGetLeaf(result, data_node, "decline-probation-period");
    checkAndGetLeaf(result, data_node, "hostname-char-set");
    checkAndGetLeaf(result, data_node, "hostname-char-replacement");

    ConstElementPtr networks = getSharedNetworks(data_node);
    if (networks && !networks->empty()) {
        result->set("shared-networks", networks);
    }
    ConstElementPtr classes = getClasses(data_node);
    if (classes && !classes->empty()) {
        result->set("client-classes", classes);
    }
    ConstElementPtr const& hosts_databases(getDatabases(data_node, "hosts-database"));
    if (hosts_databases && !hosts_databases->empty()) {
        result->set("hosts-databases", hosts_databases);
    }
    Set<DataNode> const& yang_lease_database(data_node.findXPath("lease-database"));
    if (!yang_lease_database.empty()) {
        ConstElementPtr const& lease_database(getDatabase(yang_lease_database.front()));
        if (lease_database && !lease_database->empty()) {
            result->set("lease-database", lease_database);
        }
    }
    ConstElementPtr host_ids =
        getItem(data_node, "host-reservation-identifiers");
    if (host_ids) {
        result->set("host-reservation-identifiers", host_ids);
    }
    ConstElementPtr defs = getOptionDefList(data_node);
    if (defs && !defs->empty()) {
        result->set("option-def", defs);
    }
    ConstElementPtr options = getOptionDataList(data_node);
    if (options && !options->empty()) {
        result->set("option-data", options);
    }
    ConstElementPtr hooks = getHooksKea(data_node);
    if (hooks && !hooks->empty()) {
        result->set("hooks-libraries", hooks);
    }
    checkAndGetLeaf(result, data_node, "dhcp4o6-port");
    Set<DataNode> const& yang_control_socket(data_node.findXPath("control-socket"));
    if (!yang_control_socket.empty()) {
        ConstElementPtr const& control_socket(getControlSocket(yang_control_socket.front()));
        if (control_socket) {
            result->set("control-socket", control_socket);
        }
    }
    Set<DataNode> const& yang_dhcp_ddns(data_node.findXPath("dhcp-ddns"));
    if (!yang_dhcp_ddns.empty()) {
        ConstElementPtr const& dhcp_ddns(getDdnsKea(yang_dhcp_ddns.front()));
        if (dhcp_ddns) {
            result->set("dhcp-ddns", dhcp_ddns);
        }
    }
    Set<DataNode> const& yang_expired_leases_processing(
        data_node.findXPath("expired-leases-processing"));
    if (!yang_expired_leases_processing.empty()) {
        ConstElementPtr const& expired_leases_processing(getExpiredKea(yang_expired_leases_processing.front()));
        if (expired_leases_processing) {
            result->set("expired-leases-processing", expired_leases_processing);
        }
    }
    ConstElementPtr context = getItem(data_node, "user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    ConstElementPtr checks = getItem(data_node, "sanity-checks/lease-checks");
    if (checks) {
        ElementPtr sanity = Element::createMap();
        sanity->set("lease-checks", checks);
        result->set("sanity-checks", sanity);
    }
    checkAndGetLeaf(result, data_node, "reservation-mode");
    ConstElementPtr hosts = getHosts(data_node);
    if (hosts && !hosts->empty()) {
        result->set("reservations", hosts);
    }
    Set<DataNode> const& yang_config_control(data_node.findXPath("config-control"));
    if (!yang_config_control.empty()) {
        ConstElementPtr const& config_control(getConfigControlKea(yang_config_control.front()));
        if (config_control) {
            result->set("config-control", config_control);
        }
    }
    checkAndGetLeaf(result, data_node, "server-tag");
    ConstElementPtr queue_ctrl = getItem(data_node, "dhcp-queue-control");
    if (queue_ctrl) {
        result->set("dhcp-queue-control",
                    Element::fromJSON(queue_ctrl->stringValue()));
    }
    ConstElementPtr loggers = getLoggers(data_node);
    if (loggers && !loggers->empty()) {
        result->set("loggers", loggers);
    }
    checkAndGetLeaf(result, data_node, "cache-max-age");
    checkAndGetLeaf(result, data_node, "cache-threshold");
    ElementPtr compatibility = Element::createMap();
    Set<DataNode> const& yang_compatibility(data_node.findXPath("compatibility"));
    if (!yang_compatibility.empty()) {
        checkAndGetLeaf(compatibility, yang_compatibility.front(), "lenient-option-parsing");
    }
    if (!compatibility->empty()) {
        result->set("compatibility", compatibility);
    }
    checkAndGetLeaf(result, data_node, "ddns-generated-prefix");
    checkAndGetLeaf(result, data_node, "ddns-override-client-update");
    checkAndGetLeaf(result, data_node, "ddns-override-no-update");
    checkAndGetLeaf(result, data_node, "ddns-qualifying-suffix");
    checkAndGetLeaf(result, data_node, "ddns-replace-client-name");
    checkAndGetLeaf(result, data_node, "ddns-send-updates");
    checkAndGetLeaf(result, data_node, "ddns-update-on-renew");
    checkAndGetLeaf(result, data_node, "ddns-use-conflict-resolution");
    checkAndGetLeaf(result, data_node, "ip-reservations-unique");
    checkAndGetLeaf(result, data_node, "early-global-reservations-lookup");
    checkAndGetLeaf(result, data_node, "reservations-lookup-first");
    ElementPtr multi_threading = Element::createMap();
    Set<DataNode> const& yang_multi_threading(data_node.findXPath("multi-threading"));
    if (!yang_multi_threading.empty()) {
        DataNode const& mt(yang_multi_threading.front());
        checkAndGetLeaf(multi_threading, mt, "enable-multi-threading");
        checkAndGetLeaf(multi_threading, mt, "packet-queue-size");
        checkAndGetLeaf(multi_threading, mt, "thread-pool-size");
    }
    if (!multi_threading->empty()) {
        result->set("multi-threading", multi_threading);
    }
    checkAndGetLeaf(result, data_node, "parked-packet-limit");
    checkAndGetLeaf(result, data_node, "reservations-global");
    checkAndGetLeaf(result, data_node, "reservations-in-subnet");
    checkAndGetLeaf(result, data_node, "reservations-out-of-pool");
    checkAndGetLeaf(result, data_node, "statistic-default-sample-age");
    checkAndGetLeaf(result, data_node, "statistic-default-sample-count");
    checkAndGetLeaf(result, data_node, "store-extended-info");
    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcp4() {
    string xpath = "/kea-dhcp4-server:config";
    optional<DataNode> config_optional;
    try {
        config_optional = findXPath(xpath);
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
    DataNode const config(*config_optional);
    ElementPtr result = getServerKeaDhcpCommon(config);
    // Handle subnets.
    ConstElementPtr subnets = getSubnets(config);
    if (subnets && !subnets->empty()) {
        result->set("subnet4", subnets);
    }

    // Handle interfaces.
    ElementPtr interfaces_config(getInterfacesKea(config));
    if (interfaces_config && !interfaces_config->empty()) {
        result->set("interfaces-config", interfaces_config);
    }

    // Handle DHCPv4 specific global parameters.
    checkAndGetLeaf(result, config, "echo-client-id");
    checkAndGetLeaf(result, config, "match-client-id");
    checkAndGetLeaf(result, config, "next-server");
    checkAndGetLeaf(result, config, "server-hostname");
    checkAndGetLeaf(result, config, "boot-file-name");
    checkAndGetLeaf(result, config, "authoritative");
    return (result);
}

ElementPtr
TranslatorConfig::getServerKeaDhcp6() {
    string xpath = "/kea-dhcp6-server:config";
    optional<DataNode> config_optional;
    try {
        config_optional = findXPath(xpath);
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
    DataNode const config(*config_optional);
    ElementPtr result = getServerKeaDhcpCommon(config);
    // Handle DHCPv6 specific global parameters.
    checkAndGetLeaf(result, config, "data-directory");
    checkAndGetLeaf(result, config, "preferred-lifetime");
    checkAndGetLeaf(result, config, "min-preferred-lifetime");
    checkAndGetLeaf(result, config, "max-preferred-lifetime");
    // Handle subnets.
    ConstElementPtr subnets = getSubnets(config);
    if (subnets && !subnets->empty()) {
        result->set("subnet6", subnets);
    }

    // Handle interfaces.
    ElementPtr interfaces_config(getInterfacesKea(config));
    if (interfaces_config && !interfaces_config->empty()) {
        result->set("interfaces-config", interfaces_config);
    }

    // Handle DHCPv6 specific global entries.
    ConstElementPtr relay = getItem(config, "relay-supplied-options");
    if (relay) {
        result->set("relay-supplied-options", relay);
    }
    ConstElementPtr macs = getItem(config, "mac-sources");
    if (macs) {
        result->set("mac-sources", macs);
    }

    // Handle server-id.
    // @todo: move to a DUID translator.
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
        ElementPtr const& context(getItem(server_id, "user-context"));
        if (context) {
            server_id_map->set("user-context",
                        Element::fromJSON(context->stringValue()));
        }
        if (!server_id_map->empty()) {
            result->set("server-id", server_id_map);
        }
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
TranslatorConfig::setServerKeaDhcpCommon(string const& xpath,
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
    ConstElementPtr hosts_databases = elem->get("hosts-databases");
    if (hosts_databases && !hosts_databases->empty()) {
        setDatabases(xpath + "/hosts-database", hosts_databases);
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
        ConstElementPtr config_databases = config_ctrl->get("config-databases");
        if (config_databases && !config_databases->empty()) {
            setDatabases(xpath + "/config-control/config-database", config_databases);
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
