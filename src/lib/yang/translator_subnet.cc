// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorSubnet::TranslatorSubnet(S_Session session, const string& model)
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
TranslatorSubnet::getSubnet(const string& xpath) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getSubnetIetf6(xpath));
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            return (getSubnetKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting subnet at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getSubnet not implemented for the model: " << model_);
}

ElementPtr
TranslatorSubnet::getSubnetIetf6(const string& xpath) {
    ElementPtr result = Element::createMap();
    /// @todo timers
    /// @todo: option-data
    ConstElementPtr pools = getPools(xpath + "/address-pools");
    if (pools) {
        /// Set empty list too.
        result->set("pools", pools);
    }
    pools = getPdPools(xpath + "/pd-pools");
    if (pools && (pools->size() > 0)) {
        result->set("pd-pools", pools);
    }
    ConstElementPtr subnet = getItem(xpath + "/network-prefix");
    if (!subnet) {
        isc_throw(BadValue, "getSubnetIetf6 requires network prefix");
    }
    result->set("subnet", subnet);
    ConstElementPtr id = getItem(xpath + "/network-range-id");
    if (!id) {
        isc_throw(BadValue, "getSubnetIetf6 requires network range id");
    }
    result->set("id", id);
    /// @todo: reservations
    /// missing a lot of things
    ConstElementPtr description = getItem(xpath + "/network-description");
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
TranslatorSubnet::getSubnetKea(const string& xpath) {
    ElementPtr result = Element::createMap();
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr preferred = getItem(xpath + "/preferred-lifetime");
        if (preferred) {
            result->set("preferred-lifetime", preferred);
        }
        ConstElementPtr min_pref = getItem(xpath + "/min-preferred-lifetime");
        if (min_pref) {
            result->set("min-preferred-lifetime", min_pref);
        }
        ConstElementPtr max_pref = getItem(xpath + "/max-preferred-lifetime");
        if (max_pref) {
            result->set("max-preferred-lifetime", max_pref);
        }
    }
    ConstElementPtr valid = getItem(xpath + "/valid-lifetime");
    if (valid) {
        result->set("valid-lifetime", valid);
    }
    ConstElementPtr min_valid = getItem(xpath + "/min-valid-lifetime");
    if (min_valid) {
        result->set("min-valid-lifetime", min_valid);
    }
    ConstElementPtr max_valid = getItem(xpath + "/max-valid-lifetime");
    if (max_valid) {
        result->set("max-valid-lifetime", max_valid);
    }
    ConstElementPtr renew = getItem(xpath + "/renew-timer");

    if (renew) {
        result->set("renew-timer", renew);
    }
    ConstElementPtr rebind = getItem(xpath + "/rebind-timer");
    if (rebind) {
        result->set("rebind-timer", rebind);
    }
    ConstElementPtr calculate = getItem(xpath + "/calculate-tee-times");
    if (calculate) {
        result->set("calculate-tee-times", calculate);
    }
    ConstElementPtr t1_percent = getItem(xpath + "/t1-percent");
    if (t1_percent) {
        result->set("t1-percent", t1_percent);
    }
    ConstElementPtr t2_percent = getItem(xpath + "/t2-percent");
    if (t2_percent) {
        result->set("t2-percent", t2_percent);
    }
    ConstElementPtr options = getOptionDataList(xpath);
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    ConstElementPtr pools = getPools(xpath);
    if (pools && (pools->size() > 0)) {
        result->set("pools", pools);
    }
    if (model_ == KEA_DHCP6_SERVER) {
        pools = getPdPools(xpath);
        if (pools && (pools->size() > 0)) {
            result->set("pd-pools", pools);
        }
    }
    ConstElementPtr subnet = getItem(xpath + "/subnet");
    if (!subnet) {
        isc_throw(BadValue, "getSubnetKea requires subnet");
    }
    result->set("subnet", subnet);
    ConstElementPtr interface = getItem(xpath + "/interface");
    if (interface) {
        result->set("interface", interface);
    }
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr interface_id = getItem(xpath + "/interface-id");
        if (interface_id) {
            result->set("interface-id", interface_id);
        }
    }
    ConstElementPtr id = getItem(xpath + "/id");
    if (!id) {
        isc_throw(BadValue, "getSubnetKea requires id");
    }
    result->set("id", id);
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr rapid_commit = getItem(xpath + "/rapid-commit");
        if (rapid_commit) {
            result->set("rapid-commit", rapid_commit);
        }
    }
    ConstElementPtr guard =  getItem(xpath + "/client-class");
    if (guard) {
        result->set("client-class", guard);
    }
    ConstElementPtr required = getItems(xpath + "/require-client-classes");
    if (required && (required->size() > 0)) {
        result->set("require-client-classes", required);
    }
    ConstElementPtr hosts = getHosts(xpath);
    if (hosts && (hosts->size() > 0)) {
        result->set("reservations", hosts);
    }
    ConstElementPtr mode = getItem(xpath + "/reservation-mode");
    if (mode) {
        result->set("reservation-mode", mode);
    }
    ConstElementPtr relay = getItems(xpath + "/relay/ip-addresses");
    if (relay && (relay->size() > 0)) {
        ElementPtr relay_map = Element::createMap();
        relay_map->set("ip-addresses", relay);
        result->set("relay", relay_map);
    }
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr match = getItem(xpath + "/match-client-id");
        if (match) {
            result->set("match-client-id", match);
        }
        ConstElementPtr auth = getItem(xpath + "/authoritative");
        if (auth) {
            result->set("authoritative", auth);
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
        ConstElementPtr s4o6_if = getItem(xpath + "/subnet-4o6-interface");
        if (s4o6_if) {
            result->set("4o6-interface", s4o6_if);
        }
        ConstElementPtr s4o6_id = getItem(xpath + "/subnet-4o6-interface-id");
        if (s4o6_id) {
            result->set("4o6-interface-id", s4o6_id);
        }
        ConstElementPtr s4o6_sub = getItem(xpath + "/subnet-4o6-subnet");
        if (s4o6_sub) {
            result->set("4o6-subnet", s4o6_sub);
        }
    }
    ConstElementPtr context = getItem(xpath + "/user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    checkAndGetLeaf(result, xpath, "cache-max-age");
    checkAndGetLeaf(result, xpath, "cache-threshold");
    checkAndGetLeaf(result, xpath, "ddns-generated-prefix");
    checkAndGetLeaf(result, xpath, "ddns-override-client-update");
    checkAndGetLeaf(result, xpath, "ddns-override-no-update");
    checkAndGetLeaf(result, xpath, "ddns-qualifying-suffix");
    checkAndGetLeaf(result, xpath, "ddns-replace-client-name");
    checkAndGetLeaf(result, xpath, "ddns-send-updates");
    checkAndGetLeaf(result, xpath, "ddns-update-on-renew");
    checkAndGetLeaf(result, xpath, "ddns-use-conflict-resolution");
    checkAndGetLeaf(result, xpath, "hostname-char-replacement");
    checkAndGetLeaf(result, xpath, "hostname-char-set");
    checkAndGetLeaf(result, xpath, "reservations-global");
    checkAndGetLeaf(result, xpath, "reservations-in-subnet");
    checkAndGetLeaf(result, xpath, "reservations-out-of-pool");
    checkAndGetLeaf(result, xpath, "store-extended-info");
    return (result);
}

void
TranslatorSubnet::setSubnet(const string& xpath, ConstElementPtr elem) {
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
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting subnet '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorSubnet::setSubnetIetf6(const string& xpath, ConstElementPtr elem) {
    /// Skip id as it is the key.
    AdaptorPool::fromSubnet(model_, elem, elem->get("pools"));
    ConstElementPtr context = elem->get("user-context");
    if (context && context->contains("description")) {
        ConstElementPtr description = context->get("description");
        if (description->getType() == Element::string) {
            setItem(xpath + "/network-description", description, SR_STRING_T);
        }
    }
    ConstElementPtr subnet = elem->get("subnet");
    if (!subnet) {
        isc_throw(BadValue, "setSubnetIetf6 requires subnet: " << elem->str());
    }
    setItem(xpath + "/network-prefix", subnet, SR_STRING_T);
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
TranslatorSubnet::setSubnetKea(const string& xpath, ConstElementPtr elem) {
    /// Skip id as it is the key.
    if (model_ == KEA_DHCP6_SERVER) {
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
    }
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
    setItem(xpath + "/subnet", subnet, SR_STRING_T);
    ConstElementPtr interface = elem->get("interface");
    if (interface) {
        setItem(xpath + "/interface", interface, SR_STRING_T);
    }
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr interface_id = elem->get("interface-id");
        if (interface_id) {
            setItem(xpath + "/interface-id", interface_id, SR_STRING_T);
        }
    }
    if (model_ == KEA_DHCP6_SERVER) {
        ConstElementPtr rapid_commit = elem->get("rapid-commit");
        if (rapid_commit) {
            setItem(xpath + "/rapid-commit", rapid_commit, SR_BOOL_T);
        }
    }
    ConstElementPtr guard = elem->get("client-class");
    if (guard) {
        setItem(xpath + "/client-class", guard, SR_STRING_T);
    }
    ConstElementPtr required = elem->get("require-client-classes");
    if (required && (required->size() > 0)) {
        for (ConstElementPtr rclass : required->listValue()) {
            setItem(xpath + "/require-client-classes", rclass, SR_STRING_T);
        }
    }
    ConstElementPtr hosts = elem->get("reservations");
    if (hosts && (hosts->size() > 0)) {
        setHosts(xpath, hosts);
    }
    ConstElementPtr mode = elem->get("reservation-mode");
    if (mode) {
        setItem(xpath + "/reservation-mode", mode, SR_ENUM_T);
    }
    ConstElementPtr relay = elem->get("relay");
    if (relay) {
        ConstElementPtr address = relay->get("ip-address");
        ConstElementPtr addresses = relay->get("ip-addresses");
        if (address) {
            setItem(xpath + "/relay/ip-addresses", address, SR_STRING_T);
        } else if (addresses && (addresses->size() > 0)) {
            for (ConstElementPtr addr : addresses->listValue()) {
                setItem(xpath + "/relay/ip-addresses", addr, SR_STRING_T);
            }
        }
    }
    checkAndSetLeaf(elem, xpath, "cache-max-age", SR_UINT32_T);
    checkAndSetLeaf(elem, xpath, "cache-threshold", SR_DECIMAL64_T);
    checkAndSetLeaf(elem, xpath, "ddns-generated-prefix", SR_STRING_T);
    checkAndSetLeaf(elem, xpath, "ddns-override-client-update", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "ddns-override-no-update", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "ddns-qualifying-suffix", SR_STRING_T);
    checkAndSetLeaf(elem, xpath, "ddns-replace-client-name", SR_STRING_T);
    checkAndSetLeaf(elem, xpath, "ddns-send-updates", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "ddns-update-on-renew", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "ddns-use-conflict-resolution", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "hostname-char-replacement", SR_STRING_T);
    checkAndSetLeaf(elem, xpath, "hostname-char-set", SR_STRING_T);
    checkAndSetLeaf(elem, xpath, "reservations-global", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "reservations-in-subnet", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "reservations-out-of-pool", SR_BOOL_T);
    checkAndSetLeaf(elem, xpath, "store-extended-info", SR_BOOL_T);
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr match = elem->get("match-client-id");
        if (match) {
            setItem(xpath + "/match-client-id", match, SR_BOOL_T);
        }
        ConstElementPtr auth = elem->get("authoritative");
        if (auth) {
            setItem(xpath + "/authoritative", auth, SR_BOOL_T);
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
        ConstElementPtr s4o6_if = elem->get("4o6-interface");
        if (s4o6_if) {
            setItem(xpath + "/subnet-4o6-interface", s4o6_if, SR_STRING_T);
        }
        ConstElementPtr s4o6_id = elem->get("4o6-interface-id");
        if (s4o6_id) {
            setItem(xpath + "/subnet-4o6-interface-id", s4o6_id, SR_STRING_T);
        }
        ConstElementPtr s4o6_subnet = elem->get("4o6-subnet");
        if (s4o6_subnet) {
            setItem(xpath + "/subnet-4o6-subnet", s4o6_subnet, SR_STRING_T);
        }
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        ConstElementPtr repr = Element::create(context->str());
        setItem(xpath + "/user-context", repr, SR_STRING_T);
    }
}

TranslatorSubnets::TranslatorSubnets(S_Session session, const string& model)
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
TranslatorSubnets::getSubnets(const string& xpath) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getSubnetsCommon(xpath, "network-range"));
        } else if (model_ == KEA_DHCP4_SERVER) {
            return (getSubnetsCommon(xpath, "subnet4"));
        } else if (model_ == KEA_DHCP6_SERVER) {
            return (getSubnetsCommon(xpath, "subnet6"));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting subnets at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getSubnets not implemented for the model: " << model_);
}

ElementPtr
TranslatorSubnets::getSubnetsCommon(const string& xpath,
                                    const std::string& subsel) {
    return getList<TranslatorSubnet>(xpath + "/" + subsel, *this,
                                     &TranslatorSubnet::getSubnet);
}

void
TranslatorSubnets::setSubnets(const string& xpath, ConstElementPtr elem) {
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
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting subnets '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorSubnets::setSubnetsIetf6(const string& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr subnet = elem->get(i);
        ostringstream range;
        range << xpath << "/network-range[network-range-id='";
        ConstElementPtr id = subnet->get("id");
        if (!id) {
            isc_throw(BadValue, "subnet without id: " << elem->str());
        }
        range << id->intValue() << "']";
        setSubnet(range.str().c_str(), subnet);
    }
}

void
TranslatorSubnets::setSubnetsKea(const string& xpath, ConstElementPtr elem,
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
