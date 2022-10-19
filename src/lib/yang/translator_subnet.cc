// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/adaptor_pool.h>
#include <yang/translator_subnet.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorSubnet::TranslatorSubnet(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPool(session, model),
      TranslatorPools(session, model),
      TranslatorPdPool(session, model),
      TranslatorPdPools(session, model),
      TranslatorHost(session, model),
      TranslatorHosts(session, model) {
}

TranslatorSubnet::~TranslatorSubnet() {
}

ElementPtr
TranslatorSubnet::getSubnet(DataNode const& data_node) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getSubnetIetf6(data_node));
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            return (getSubnetKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting subnet:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getSubnet not implemented for the model: " << model_);
}

ElementPtr
TranslatorSubnet::getSubnet(string const& xpath) {
    try {
        return getSubnet(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorSubnet::getSubnetIetf6(DataNode const& data_node) {
    ElementPtr result = Element::createMap();
    /// @todo timers
    /// @todo: option-data
    Set<DataNode> const& address_pools(data_node.findXPath("address-pools"));
    if (!address_pools.empty()) {
        ConstElementPtr const& pools(getPools(address_pools.front()));
        if (pools && !pools->empty()) {
            result->set("pools", pools);
        }
    }
    Set<DataNode> const& yang_pd_pools(data_node.findXPath("pd-pools"));
    if (!yang_pd_pools.empty()) {
        ConstElementPtr const& pd_pools(getPdPools(yang_pd_pools.front()));
        if (pd_pools && !pd_pools->empty()) {
            result->set("pd-pools", pd_pools);
        }
    }
    ConstElementPtr subnet = getItem(data_node, "network-prefix");
    if (!subnet) {
        isc_throw(BadValue, "getSubnetIetf6 requires network prefix");
    }
    result->set("subnet", subnet);
    ConstElementPtr id = getItem(data_node, "network-range-id");
    if (!id) {
        isc_throw(BadValue, "getSubnetIetf6 requires network range id");
    }
    result->set("id", id);
    /// @todo: reservations
    /// missing a lot of things
    ConstElementPtr description = getItem(data_node, "network-description");
    /// Adding description if exists.
    if (description) {
        ElementPtr context = Element::createMap();
        context->set("description", description);
        result->set("user-context", context);
    }
    /// missing a lot of things
    if (result->get("pools")) {
        AdaptorPool::toSubnet(model_, result, result->get("pools"));
    }
    return (result);
}

ElementPtr
TranslatorSubnet::getSubnetKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr preferred = getItem(data_node, "preferred-lifetime");
        if (preferred) {
            result->set("preferred-lifetime", preferred);
        }
        ConstElementPtr min_pref = getItem(data_node, "min-preferred-lifetime");
        if (min_pref) {
            result->set("min-preferred-lifetime", min_pref);
        }
        ConstElementPtr max_pref = getItem(data_node, "max-preferred-lifetime");
        if (max_pref) {
            result->set("max-preferred-lifetime", max_pref);
        }
    }
    ConstElementPtr valid = getItem(data_node, "valid-lifetime");
    if (valid) {
        result->set("valid-lifetime", valid);
    }
    ConstElementPtr min_valid = getItem(data_node, "min-valid-lifetime");
    if (min_valid) {
        result->set("min-valid-lifetime", min_valid);
    }
    ConstElementPtr max_valid = getItem(data_node, "max-valid-lifetime");
    if (max_valid) {
        result->set("max-valid-lifetime", max_valid);
    }
    ConstElementPtr renew = getItem(data_node, "renew-timer");

    if (renew) {
        result->set("renew-timer", renew);
    }
    ConstElementPtr rebind = getItem(data_node, "rebind-timer");
    if (rebind) {
        result->set("rebind-timer", rebind);
    }
    ConstElementPtr calculate = getItem(data_node, "calculate-tee-times");
    if (calculate) {
        result->set("calculate-tee-times", calculate);
    }
    ConstElementPtr t1_percent = getItem(data_node, "t1-percent");
    if (t1_percent) {
        result->set("t1-percent", t1_percent);
    }
    ConstElementPtr t2_percent = getItem(data_node, "t2-percent");
    if (t2_percent) {
        result->set("t2-percent", t2_percent);
    }
    ConstElementPtr options = getOptionDataList(data_node);
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    ConstElementPtr pools = getPools(data_node);
    if (pools && (pools->size() > 0)) {
        result->set("pools", pools);
    }
    if (model_ == KEA_DHCP6_SERVER) {
        ElementPtr pd_pools = getPdPools(data_node);
        if (pd_pools && (pd_pools->size() > 0)) {
            result->set("pd-pools", pd_pools);
        }
    }
    ConstElementPtr subnet = getItem(data_node, "subnet");
    if (!subnet) {
        isc_throw(BadValue, "getSubnetKea requires subnet");
    }
    result->set("subnet", subnet);
    ConstElementPtr interface = getItem(data_node, "interface");
    if (interface) {
        result->set("interface", interface);
    }
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr interface_id = getItem(data_node, "interface-id");
        if (interface_id) {
            result->set("interface-id", interface_id);
        }
    }
    ConstElementPtr id = getItem(data_node, "id");
    if (!id) {
        isc_throw(BadValue, "getSubnetKea requires id");
    }
    result->set("id", id);
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr rapid_commit = getItem(data_node, "rapid-commit");
        if (rapid_commit) {
            result->set("rapid-commit", rapid_commit);
        }
    }
    ConstElementPtr guard =  getItem(data_node, "client-class");
    if (guard) {
        result->set("client-class", guard);
    }
    ConstElementPtr required = getItem(data_node, "require-client-classes");
    if (required && (required->size() > 0)) {
        result->set("require-client-classes", required);
    }
    ConstElementPtr hosts = getHosts(data_node);
    if (hosts && (hosts->size() > 0)) {
        result->set("reservations", hosts);
    }
    ConstElementPtr mode = getItem(data_node, "reservation-mode");
    if (mode) {
        result->set("reservation-mode", mode);
    }
    ConstElementPtr relay = getItem(data_node, "relay/ip-addresses");
    if (relay && (relay->size() > 0)) {
        ElementPtr relay_map = Element::createMap();
        relay_map->set("ip-addresses", relay);
        result->set("relay", relay_map);
    }
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr match = getItem(data_node, "match-client-id");
        if (match) {
            result->set("match-client-id", match);
        }
        ConstElementPtr auth = getItem(data_node, "authoritative");
        if (auth) {
            result->set("authoritative", auth);
        }
        ConstElementPtr next = getItem(data_node, "next-server");
        if (next) {
            result->set("next-server", next);
        }
        ConstElementPtr hostname = getItem(data_node, "server-hostname");
        if (hostname) {
            result->set("server-hostname", hostname);
        }
        ConstElementPtr boot = getItem(data_node, "boot-file-name");
        if (boot) {
            result->set("boot-file-name", boot);
        }
        ConstElementPtr s4o6_if = getItem(data_node, "subnet-4o6-interface");
        if (s4o6_if) {
            result->set("4o6-interface", s4o6_if);
        }
        ConstElementPtr s4o6_id = getItem(data_node, "subnet-4o6-interface-id");
        if (s4o6_id) {
            result->set("4o6-interface-id", s4o6_id);
        }
        ConstElementPtr s4o6_sub = getItem(data_node, "subnet-4o6-subnet");
        if (s4o6_sub) {
            result->set("4o6-subnet", s4o6_sub);
        }
    }
    ConstElementPtr context = getItem(data_node, "user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    checkAndGetLeaf(result, data_node, "cache-max-age");
    checkAndGetLeaf(result, data_node, "cache-threshold");
    checkAndGetLeaf(result, data_node, "ddns-generated-prefix");
    checkAndGetLeaf(result, data_node, "ddns-override-client-update");
    checkAndGetLeaf(result, data_node, "ddns-override-no-update");
    checkAndGetLeaf(result, data_node, "ddns-qualifying-suffix");
    checkAndGetLeaf(result, data_node, "ddns-replace-client-name");
    checkAndGetLeaf(result, data_node, "ddns-send-updates");
    checkAndGetLeaf(result, data_node, "ddns-update-on-renew");
    checkAndGetLeaf(result, data_node, "ddns-use-conflict-resolution");
    checkAndGetLeaf(result, data_node, "hostname-char-replacement");
    checkAndGetLeaf(result, data_node, "hostname-char-set");
    checkAndGetLeaf(result, data_node, "reservations-global");
    checkAndGetLeaf(result, data_node, "reservations-in-subnet");
    checkAndGetLeaf(result, data_node, "reservations-out-of-pool");
    checkAndGetLeaf(result, data_node, "store-extended-info");
    return (result);
}

void
TranslatorSubnet::setSubnet(string const& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setSubnetIetf6(xpath, elem);
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            setSubnetKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setSubnet not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting subnet '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorSubnet::setSubnetIetf6(string const& xpath, ConstElementPtr elem) {
    /// Skip id as it is the key.
    AdaptorPool::fromSubnet(model_, elem, elem->get("pools"));
    ConstElementPtr context = elem->get("user-context");
    if (context && context->contains("description")) {
        ConstElementPtr description = context->get("description");
        if (description->getType() == Element::string) {
            setItem(xpath + "/network-description", description, LeafBaseType::String);
        }
    }
    ConstElementPtr subnet = elem->get("subnet");
    if (!subnet) {
        isc_throw(BadValue, "setSubnetIetf6 requires subnet: " << elem->str());
    }
    setItem(xpath + "/network-prefix", subnet, LeafBaseType::String);
    /// @todo option-data
    ConstElementPtr pools = elem->get("pools");
    if (pools && (pools->size() > 0)) {
        setPools(xpath + "/address-pools", pools);
    }
    pools = elem->get("pd-pools");
    if (pools && (pools->size() > 0)) {
        setPdPools(xpath + "/pd-pools", pools);
    }
    /// @todo reservations
}

void
TranslatorSubnet::setSubnetKea(string const& xpath, ConstElementPtr elem) {
    /// Skip id as it is the key.
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr preferred = elem->get("preferred-lifetime");
        if (preferred) {
            setItem(xpath + "/preferred-lifetime", preferred, LeafBaseType::Uint32);
        }
        ConstElementPtr min_pref = elem->get("min-preferred-lifetime");
        if (min_pref) {
            setItem(xpath + "/min-preferred-lifetime", min_pref, LeafBaseType::Uint32);
        }
        ConstElementPtr max_pref = elem->get("max-preferred-lifetime");
        if (max_pref) {
            setItem(xpath + "/max-preferred-lifetime", max_pref, LeafBaseType::Uint32);
        }
    }
    ConstElementPtr valid = elem->get("valid-lifetime");
    if (valid) {
        setItem(xpath + "/valid-lifetime", valid, LeafBaseType::Uint32);
    }
    ConstElementPtr min_valid = elem->get("min-valid-lifetime");
    if (min_valid) {
        setItem(xpath + "/min-valid-lifetime", min_valid, LeafBaseType::Uint32);
    }
    ConstElementPtr max_valid = elem->get("max-valid-lifetime");
    if (max_valid) {
        setItem(xpath + "/max-valid-lifetime", max_valid, LeafBaseType::Uint32);
    }
    ConstElementPtr renew = elem->get("renew-timer");
    if (renew) {
        setItem(xpath + "/renew-timer", renew, LeafBaseType::Uint32);
    }
    ConstElementPtr rebind = elem->get("rebind-timer");
    if (rebind) {
        setItem(xpath + "/rebind-timer", rebind, LeafBaseType::Uint32);
    }
    ConstElementPtr calculate = elem->get("calculate-tee-times");
    if (calculate) {
        setItem(xpath + "/calculate-tee-times", calculate, LeafBaseType::Bool);
    }
    ConstElementPtr t1_percent =  elem->get("t1-percent");
    if (t1_percent) {
        setItem(xpath + "/t1-percent", t1_percent, LeafBaseType::Dec64);
    }
    ConstElementPtr t2_percent =  elem->get("t2-percent");
    if (t2_percent) {
        setItem(xpath + "/t2-percent", t2_percent, LeafBaseType::Dec64);
    }
    ConstElementPtr options = elem->get("option-data");
    if (options && (options->size() > 0)) {
        setOptionDataList(xpath, options);
    }
    ConstElementPtr pools = elem->get("pools");
    if (pools && (pools->size() > 0)) {
        setPools(xpath, pools);
    }
    if (model_ == KEA_DHCP6_SERVER) {
        pools = elem->get("pd-pools");
        if (pools && (pools->size() > 0)) {
            setPdPools(xpath, pools);
        }
    }
    ConstElementPtr subnet = elem->get("subnet");
    if (!subnet) {
        isc_throw(BadValue, "setSubnetKea requires subnet: " << elem->str());
    }
    setItem(xpath + "/subnet", subnet, LeafBaseType::String);
    ConstElementPtr interface = elem->get("interface");
    if (interface) {
        setItem(xpath + "/interface", interface, LeafBaseType::String);
    }
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr interface_id = elem->get("interface-id");
        if (interface_id) {
            setItem(xpath + "/interface-id", interface_id, LeafBaseType::String);
        }
    }
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr rapid_commit = elem->get("rapid-commit");
        if (rapid_commit) {
            setItem(xpath + "/rapid-commit", rapid_commit, LeafBaseType::Bool);
        }
    }
    ConstElementPtr guard = elem->get("client-class");
    if (guard) {
        setItem(xpath + "/client-class", guard, LeafBaseType::String);
    }
    ConstElementPtr required = elem->get("require-client-classes");
    if (required && (required->size() > 0)) {
        for (ConstElementPtr rclass : required->listValue()) {
            setItem(xpath + "/require-client-classes", rclass, LeafBaseType::String);
        }
    }
    ConstElementPtr hosts = elem->get("reservations");
    if (hosts && (hosts->size() > 0)) {
        setHosts(xpath, hosts);
    }
    ConstElementPtr mode = elem->get("reservation-mode");
    if (mode) {
        setItem(xpath + "/reservation-mode", mode, LeafBaseType::Enum);
    }
    ConstElementPtr relay = elem->get("relay");
    if (relay) {
        ConstElementPtr address = relay->get("ip-address");
        ConstElementPtr addresses = relay->get("ip-addresses");
        if (address) {
            setItem(xpath + "/relay/ip-addresses", address, LeafBaseType::String);
        } else if (addresses && (addresses->size() > 0)) {
            for (ConstElementPtr addr : addresses->listValue()) {
                setItem(xpath + "/relay/ip-addresses", addr, LeafBaseType::String);
            }
        }
    }
    checkAndSetLeaf(elem, xpath, "cache-max-age", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "cache-threshold", LeafBaseType::Dec64);
    checkAndSetLeaf(elem, xpath, "ddns-generated-prefix", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-override-client-update", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-override-no-update", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-qualifying-suffix", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-replace-client-name", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-send-updates", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-update-on-renew", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-use-conflict-resolution", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "hostname-char-replacement", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "hostname-char-set", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "reservations-global", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-in-subnet", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-out-of-pool", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "store-extended-info", LeafBaseType::Bool);
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr match = elem->get("match-client-id");
        if (match) {
            setItem(xpath + "/match-client-id", match, LeafBaseType::Bool);
        }
        ConstElementPtr auth = elem->get("authoritative");
        if (auth) {
            setItem(xpath + "/authoritative", auth, LeafBaseType::Bool);
        }
        ConstElementPtr next = elem->get("next-server");
        if (next) {
            setItem(xpath + "/next-server", next, LeafBaseType::String);
        }
        ConstElementPtr hostname = elem->get("server-hostname");
        if (hostname) {
            setItem(xpath + "/server-hostname", hostname, LeafBaseType::String);
        }
        ConstElementPtr boot = elem->get("boot-file-name");
        if (boot) {
            setItem(xpath + "/boot-file-name", boot, LeafBaseType::String);
        }
        ConstElementPtr s4o6_if = elem->get("4o6-interface");
        if (s4o6_if) {
            setItem(xpath + "/subnet-4o6-interface", s4o6_if, LeafBaseType::String);
        }
        ConstElementPtr s4o6_id = elem->get("4o6-interface-id");
        if (s4o6_id) {
            setItem(xpath + "/subnet-4o6-interface-id", s4o6_id, LeafBaseType::String);
        }
        ConstElementPtr s4o6_subnet = elem->get("4o6-subnet");
        if (s4o6_subnet) {
            setItem(xpath + "/subnet-4o6-subnet", s4o6_subnet, LeafBaseType::String);
        }
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        ConstElementPtr repr = Element::create(context->str());
        setItem(xpath + "/user-context", repr, LeafBaseType::String);
    }
}

TranslatorSubnets::TranslatorSubnets(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPool(session, model),
      TranslatorPools(session, model),
      TranslatorPdPool(session, model),
      TranslatorPdPools(session, model),
      TranslatorHost(session, model),
      TranslatorHosts(session, model),
      TranslatorSubnet(session, model) {
}

TranslatorSubnets::~TranslatorSubnets() {
}

ElementPtr
TranslatorSubnets::getSubnets(DataNode const& data_node) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getSubnetsCommon(data_node, "network-range"));
        } else if (model_ == KEA_DHCP4_SERVER) {
            return (getSubnetsCommon(data_node, "subnet4"));
        } else if (model_ == KEA_DHCP6_SERVER) {
            return (getSubnetsCommon(data_node, "subnet6"));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting subnets:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getSubnets not implemented for the model: " << model_);
}

ElementPtr
TranslatorSubnets::getSubnets(string const& xpath) {
    try {
        return getSubnets(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorSubnets::getSubnetsCommon(DataNode const& data_node,
                                    const std::string& subsel) {
    return getList<TranslatorSubnet>(data_node, subsel, *this,
                                     &TranslatorSubnet::getSubnet);
}

void
TranslatorSubnets::setSubnets(string const& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setSubnetsIetf6(xpath, elem);
        } else if (model_ == KEA_DHCP4_SERVER) {
            setSubnetsKea(xpath, elem, "subnet4");
        } else if (model_ == KEA_DHCP6_SERVER) {
            setSubnetsKea(xpath, elem, "subnet6");
        } else {
            isc_throw(NotImplemented,
                      "setSubnets not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting subnets '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorSubnets::setSubnetsIetf6(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr subnet = elem->get(i);
        ostringstream range;
        range << xpath << "/network-range[network-range-id='";
        ConstElementPtr id = subnet->get("id");
        if (!id) {
            isc_throw(BadValue, "subnet without id: " << elem->str());
        }
        range << id->intValue() << "']";
        setSubnet(range.str(), subnet);
    }
}

void
TranslatorSubnets::setSubnetsKea(string const& xpath, ConstElementPtr elem,
                                 const std::string& subsel) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr subnet = elem->get(i);
        if (!subnet->contains("id")) {
            isc_throw(BadValue, "subnet without id: " << subnet->str());
        }
        ostringstream prefix;
        prefix << xpath << "/" << subsel << "[id='"
               << subnet->get("id")->intValue() << "']";
        setSubnet(prefix.str(), subnet);
    }
}

}  // namespace yang
}  // namespace isc
