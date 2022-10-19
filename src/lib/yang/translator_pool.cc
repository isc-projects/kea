// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <asiolink/addr_utilities.h>
#include <yang/adaptor.h>
#include <yang/translator_pool.h>
#include <yang/yang_models.h>
#include <boost/lexical_cast.hpp>
#include <sstream>

using namespace std;
using namespace isc::data;
using namespace isc::asiolink;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorPool::TranslatorPool(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model) {
}

TranslatorPool::~TranslatorPool() {
}

ElementPtr
TranslatorPool::getPool(DataNode const& data_node) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getPoolIetf6(data_node));
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            return (getPoolKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting pool:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getPool not implemented for the model: " << model_);
}

ElementPtr
TranslatorPool::getPool(string const& xpath) {
    try {
        return getPool(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorPool::getPoolIetf6(DataNode const& data_node) {
    ElementPtr result = Element::createMap();
    // Skip pool-id which exists but is not used.
    ConstElementPtr pool = getItem(data_node, "pool-prefix");
    if (!pool) {
        isc_throw(BadValue, "getPoolIetf6 requires pool prefix");
    }
    result->set("pool", pool);
    // Ignore start-address - end-address as prefix form is mandatory?
    ConstElementPtr guard = getItem(data_node, "client-class");
    if (guard) {
        result->set("client-class", guard);
    }
    ConstElementPtr valid_lifetime = getItem(data_node, "valid-lifetime");
    if (valid_lifetime) {
        result->set("valid-lifetime", valid_lifetime);
    }
    ConstElementPtr preferred_lifetime =
        getItem(data_node, "preferred-lifetime");
    if (preferred_lifetime) {
        result->set("preferred-lifetime", preferred_lifetime);
    }
    ConstElementPtr renew_time = getItem(data_node, "renew-time");
    if (renew_time) {
        result->set("renew-timer", renew_time);
    }
    ConstElementPtr rebind_time = getItem(data_node, "rebind-time");
    if (rebind_time) {
        result->set("rebind-timer", rebind_time);
    }
    // Skip max-addr-count
    // @todo: option-data
    /// no require-client-classes nor user-context.
    // Skip rapid-commit.
    if (result->empty()) {
        return ElementPtr();
    }
    return (result);
}

ElementPtr
TranslatorPool::getPoolKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();
    ConstElementPtr prefix = getItem(data_node, "prefix");
    if (prefix) {
        result->set("pool", prefix);
    } else {
        ConstElementPtr start_addr = getItem(data_node, "start-address");
        ConstElementPtr end_addr = getItem(data_node, "end-address");
        if (!start_addr || !end_addr) {
            isc_throw(BadValue, "getPoolKea requires either prefix or "
                      "both start and end addresses");
        }
        ostringstream range;
        range << start_addr->stringValue() << " - "
              << end_addr->stringValue();
        result->set("pool", Element::create(range.str()));
    }
    ConstElementPtr options = getOptionDataList(data_node);
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    ConstElementPtr guard = getItem(data_node, "client-class");
    if (guard) {
        result->set("client-class", guard);
    }
    ConstElementPtr required = getItem(data_node, "require-client-classes");
    if (required && (required->size() > 0)) {
        result->set("require-client-classes", required);
    }
    ConstElementPtr context = getItem(data_node, "user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

void
TranslatorPool::setPool(string const& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setPoolIetf6(xpath, elem);
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            setPoolKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setPool not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting pool '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorPool::setPoolIetf6(string const& xpath, ConstElementPtr elem) {
    ConstElementPtr pool = elem->get("pool");
    if (!pool) {
        isc_throw(BadValue, "setPoolIetf6 requires pool: " << elem->str());
    }
    string prefix = pool->stringValue();
    if (prefix.find("/") == string::npos) {
        isc_throw(BadValue,
                  "setPoolIetf only supports pools in prefix (vs range) "
                  "format and was called with '" << prefix << "'");
    }
    setItem(xpath + "/pool-prefix", pool, LeafBaseType::String);
    string addr = prefix.substr(0, prefix.find_first_of(" /"));
    uint8_t plen = boost::lexical_cast<unsigned>
        (prefix.substr(prefix.find_last_of(" /") + 1, string::npos));
    const IOAddress& base(addr);
    setItem(xpath + "/start-address",
            Element::create(firstAddrInPrefix(base, plen).toText()),
            LeafBaseType::String);
    setItem(xpath + "/end-address",
            Element::create(lastAddrInPrefix(base, plen).toText()),
            LeafBaseType::String);
    ConstElementPtr valid_lifetime = elem->get("valid-lifetime");
    if (valid_lifetime) {
        setItem(xpath + "/valid-lifetime", valid_lifetime, LeafBaseType::Uint32);
    }
    ConstElementPtr preferred_lifetime = elem->get("preferred-lifetime");
    if (preferred_lifetime) {
        setItem(xpath + "/preferred-lifetime",
                preferred_lifetime, LeafBaseType::Uint32);
    }
    ConstElementPtr renew_timer = elem->get("renew-timer");
    if (renew_timer) {
        setItem(xpath + "/renew-time", renew_timer, LeafBaseType::Uint32);
    }
    ConstElementPtr rebind_timer = elem->get("rebind-timer");
    if (rebind_timer) {
        setItem(xpath + "/rebind-time", rebind_timer, LeafBaseType::Uint32);
    }
    // skip rapid-commit
    ConstElementPtr guard = elem->get("client-class");
    if (guard) {
        setItem(xpath + "/client-class", guard, LeafBaseType::String);
    }
    // skip max-addr-count
    // @todo option-data
    // Set max address count to disabled.
    setItem(xpath + "/max-address-count",
            Element::create(string("disabled")),
            LeafBaseType::Enum);
}

void
TranslatorPool::setPoolKea(string const& xpath, ConstElementPtr elem) {
    ConstElementPtr pool = elem->get("pool");
    if (!pool) {
        isc_throw(BadValue, "setPoolKea requires pool: " << elem->str());
    }

    // Keys are set by setting the list itself.
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    string prefix = pool->stringValue();
    string start_addr;
    string end_addr;
    getAddresses(prefix, start_addr, end_addr);
    if (prefix.find("/") != string::npos) {
        setItem(xpath + "/prefix", pool, LeafBaseType::String);
    }
    // Skip start-address and end-address as are the keys.
    ConstElementPtr options = elem->get("option-data");
    if (options && (options->size() > 0)) {
        setOptionDataList(xpath, options);
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
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                LeafBaseType::String);
    }
}

void
TranslatorPool::getAddresses(const string& prefix,
                             string& start_address, string& end_address) {
    size_t slash = prefix.find("/");
    if (slash != string::npos) {
        string addr = prefix.substr(0, prefix.find_first_of(" /"));
        uint8_t plen = boost::lexical_cast<unsigned>
            (prefix.substr(prefix.find_last_of(" /") + 1, string::npos));
        start_address = firstAddrInPrefix(IOAddress(addr), plen).toText();
        end_address = lastAddrInPrefix(IOAddress(addr), plen).toText();
        return;
    }
    size_t dash = prefix.find("-");
    if (dash == string::npos) {
        isc_throw(BadValue,
                  "getAddresses called with invalid prefix: " << prefix);
    }
    start_address = prefix.substr(0, prefix.find_first_of(" -"));
    end_address = prefix.substr(prefix.find_last_of(" -") + 1, string::npos);
}

TranslatorPools::TranslatorPools(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPool(session, model) {
}

TranslatorPools::~TranslatorPools() {
}

ElementPtr
TranslatorPools::getPools(DataNode const& data_node) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getPoolsIetf(data_node));
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            return (getPoolsKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting pools:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getPools not implemented for the model: " << model_);
}

ElementPtr
TranslatorPools::getPools(string const& xpath) {
    try {
        return getPools(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorPools::getPoolsIetf(DataNode const& data_node) {
    return getList<TranslatorPool>(data_node, "address-pool", *this,
                                   &TranslatorPool::getPool);
}

ElementPtr
TranslatorPools::getPoolsKea(DataNode const& data_node) {
    return getList<TranslatorPool>(data_node, "pool", *this,
                                   &TranslatorPool::getPool);
}

void
TranslatorPools::setPools(string const& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setPoolsById(xpath, elem);
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            setPoolsByAddresses(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setPools not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting pools '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorPools::setPoolsById(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr pool = elem->get(i);
        ostringstream prefix;
        prefix << xpath << "/address-pool[pool-id='" << i << "']";
        setPool(prefix.str(), pool);
    }
}

void
TranslatorPools::setPoolsByAddresses(string const& xpath,
                                     ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr pool = elem->get(i);
        if (!pool->contains("pool")) {
            isc_throw(BadValue, "setPoolsByAddresses: missing required pool: "
                      << pool->str());
        }
        string pref = pool->get("pool")->stringValue();
        string start_addr;
        string end_addr;
        getAddresses(pref, start_addr, end_addr);
        ostringstream prefix;
        prefix << xpath << "/pool[start-address='" << start_addr
               << "'][end-address='" << end_addr << "']";
        setPool(prefix.str(), pool);
    }
}

}  // namespace yang
}  // namespace isc
