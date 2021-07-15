// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorPool::TranslatorPool(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model) {
}

TranslatorPool::~TranslatorPool() {
}

ElementPtr
TranslatorPool::getPool(const string& xpath) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getPoolIetf6(xpath));
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            return (getPoolKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting pool at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getPool not implemented for the model: " << model_);
}

ElementPtr
TranslatorPool::getPoolIetf6(const string& xpath) {
    ElementPtr result = Element::createMap();
    // Skip pool-id which exists but is not used.
    ConstElementPtr pool = getItem(xpath + "/pool-prefix");
    if (!pool) {
        isc_throw(BadValue, "getPoolIetf6 requires pool prefix at " << xpath);
    }
    result->set("pool", pool);
    // Ignore start-address - end-address as prefix form is mandatory?
    ConstElementPtr guard = getItem(xpath + "/client-class");
    if (guard) {
        result->set("client-class", guard);
    }
    ConstElementPtr valid_lifetime = getItem(xpath + "/valid-lifetime");
    if (valid_lifetime) {
        result->set("valid-lifetime", valid_lifetime);
    }
    ConstElementPtr preferred_lifetime =
        getItem(xpath + "/preferred-lifetime");
    if (preferred_lifetime) {
        result->set("preferred-lifetime", preferred_lifetime);
    }
    ConstElementPtr renew_time = getItem(xpath + "/renew-time");
    if (renew_time) {
        result->set("renew-timer", renew_time);
    }
    ConstElementPtr rebind_time = getItem(xpath + "/rebind-time");
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
TranslatorPool::getPoolKea(const string& xpath) {
    ElementPtr result = Element::createMap();
    ConstElementPtr prefix = getItem(xpath + "/prefix");
    if (prefix) {
        result->set("pool", prefix);
    } else {
        ConstElementPtr start_addr = getItem(xpath + "/start-address");
        ConstElementPtr end_addr = getItem(xpath + "/end-address");
        if (!start_addr || !end_addr) {
            isc_throw(BadValue, "getPoolKea requires either prefix or "
                      "both start and end addresses at " << xpath);
        }
        ostringstream range;
        range << start_addr->stringValue() << " - "
              << end_addr->stringValue();
        result->set("pool", Element::create(range.str()));
    }
    ConstElementPtr options = getOptionDataList(xpath);
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    ConstElementPtr guard = getItem(xpath + "/client-class");
    if (guard) {
        result->set("client-class", guard);
    }
    ConstElementPtr required = getItems(xpath + "/require-client-classes");
    if (required && (required->size() > 0)) {
        result->set("require-client-classes", required);
    }
    ConstElementPtr context = getItem(xpath + "/user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

void
TranslatorPool::setPool(const string& xpath, ConstElementPtr elem) {
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
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting pool '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorPool::setPoolIetf6(const string& xpath, ConstElementPtr elem) {
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
    setItem(xpath + "/pool-prefix", pool, SR_STRING_T);
    string addr = prefix.substr(0, prefix.find_first_of(" /"));
    uint8_t plen = boost::lexical_cast<unsigned>
        (prefix.substr(prefix.find_last_of(" /") + 1, string::npos));
    const IOAddress& base(addr);
    setItem(xpath + "/start-address",
            Element::create(firstAddrInPrefix(base, plen).toText()),
            SR_STRING_T);
    setItem(xpath + "/end-address",
            Element::create(lastAddrInPrefix(base, plen).toText()),
            SR_STRING_T);
    ConstElementPtr valid_lifetime = elem->get("valid-lifetime");
    if (valid_lifetime) {
        setItem(xpath + "/valid-lifetime", valid_lifetime, SR_UINT32_T);
    }
    ConstElementPtr preferred_lifetime = elem->get("preferred-lifetime");
    if (preferred_lifetime) {
        setItem(xpath + "/preferred-lifetime",
                preferred_lifetime, SR_UINT32_T);
    }
    ConstElementPtr renew_timer = elem->get("renew-timer");
    if (renew_timer) {
        setItem(xpath + "/renew-time", renew_timer, SR_UINT32_T);
    }
    ConstElementPtr rebind_timer = elem->get("rebind-timer");
    if (rebind_timer) {
        setItem(xpath + "/rebind-time", rebind_timer, SR_UINT32_T);
    }
    // skip rapid-commit
    ConstElementPtr guard = elem->get("client-class");
    if (guard) {
        setItem(xpath + "/client-class", guard, SR_STRING_T);
    }
    // skip max-addr-count
    // @todo option-data
    // Set max address count to disabled.
    setItem(xpath + "/max-address-count",
            Element::create(string("disabled")),
            SR_ENUM_T);
}

void
TranslatorPool::setPoolKea(const string& xpath, ConstElementPtr elem) {
    ConstElementPtr pool = elem->get("pool");
    if (!pool) {
        isc_throw(BadValue, "setPoolKea requires pool: " << elem->str());
    }
    bool created = false;
    string prefix = pool->stringValue();
    string start_addr;
    string end_addr;
    getAddresses(prefix, start_addr, end_addr);
    if (prefix.find("/") != string::npos) {
        setItem(xpath + "/prefix", pool, SR_STRING_T);
        created = true;
    }
    // Skip start-address and end-address as are the keys.
    ConstElementPtr options = elem->get("option-data");
    if (options && (options->size() > 0)) {
        setOptionDataList(xpath, options);
        created = true;
    }
    ConstElementPtr guard = elem->get("client-class");
    if (guard) {
        setItem(xpath + "/client-class", guard, SR_STRING_T);
        created = true;
    }
    ConstElementPtr required = elem->get("require-client-classes");
    if (required && (required->size() > 0)) {
        for (ConstElementPtr rclass : required->listValue()) {
            setItem(xpath + "/require-client-classes", rclass, SR_STRING_T);
            created = true;
        }
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                SR_STRING_T);
        created = true;
    }
    // There is no mandatory fields outside the keys so force creation.
    if (!created) {
        ConstElementPtr list = Element::createList();
        setItem(xpath, list, SR_LIST_T);
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

TranslatorPools::TranslatorPools(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPool(session, model) {
}

TranslatorPools::~TranslatorPools() {
}

ElementPtr
TranslatorPools::getPools(const string& xpath) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getPoolsIetf(xpath));
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            return (getPoolsKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting pools at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getPools not implemented for the model: " << model_);
}

ElementPtr
TranslatorPools::getPoolsIetf(const string& xpath) {
    return getList<TranslatorPool>(xpath + "/address-pool", *this,
                                   &TranslatorPool::getPool);
}

ElementPtr
TranslatorPools::getPoolsKea(const string& xpath) {
    return getList<TranslatorPool>(xpath + "/pool", *this,
                                   &TranslatorPool::getPool);
}

void
TranslatorPools::setPools(const string& xpath, ConstElementPtr elem) {
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
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting pools '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorPools::setPoolsById(const string& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr pool = elem->get(i);
        ostringstream prefix;
        prefix << xpath << "/address-pool[pool-id='" << i << "']";
        setPool(prefix.str(), pool);
    }
}

void
TranslatorPools::setPoolsByAddresses(const string& xpath,
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
