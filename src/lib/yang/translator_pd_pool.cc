// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/adaptor.h>
#include <yang/translator_pd_pool.h>
#include <yang/yang_models.h>
#include <boost/lexical_cast.hpp>
#include <sstream>

using namespace std;
using namespace isc::data;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorPdPool::TranslatorPdPool(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model) {
}

TranslatorPdPool::~TranslatorPdPool() {
}

ElementPtr
TranslatorPdPool::getPdPool(const string& xpath) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getPdPoolIetf6(xpath));
        } else if (model_ == KEA_DHCP6_SERVER) {
            return (getPdPoolKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting pd-pool at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getPdPool not implemented for the model: " << model_);
}

ElementPtr
TranslatorPdPool::getPdPoolIetf6(const string& xpath) {
    ElementPtr result = Element::createMap();
    ConstElementPtr pref = getItem(xpath + "/prefix");
    if (!pref) {
        isc_throw(BadValue, "getPdPoolIetf6: prefix is required");
    }
    const string& prefix = pref->stringValue();
    size_t slash = prefix.find("/");
    if (slash == string::npos) {
        isc_throw(BadValue,
                  "getPdPoolIetf6: no '/' in prefix '" << prefix << "'");
    }
    const string& address = prefix.substr(0, slash);
    if (address.empty()) {
        isc_throw(BadValue,
                  "getPdPoolIetf6: malformed prefix '" << prefix << "'");
    }
    result->set("prefix", Element::create(address));
    // Silly: the prefix length is specified twice...
    ConstElementPtr preflen = getItem(xpath + "/prefix-length");
    if (!preflen) {
        isc_throw(BadValue, "getPdPoolIetf6: prefix length is required");
    }
    result->set("prefix-len", preflen);
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
    // Skip rapid-commit.
    ConstElementPtr guard = getItem(xpath + "/client-class");
    if (guard) {
        result->set("client-class", guard);
    }
    // no require-client-classes nor user-context.
    // Skip max-pd-space-utilization.
    // @todo option-data.
    return (result);
}

ElementPtr
TranslatorPdPool::getPdPoolKea(const string& xpath) {
    ElementPtr result = Element::createMap();
    ConstElementPtr pref = getItem(xpath + "/prefix");
    if (!pref) {
        isc_throw(BadValue, "getPdPoolKea: no prefix defined at " << xpath);
    }
    const string& prefix = pref->stringValue();
    size_t slash = prefix.find("/");
    if (slash == string::npos) {
        isc_throw(BadValue,
                  "getPdPoolKea: no '/' in prefix '" << prefix << "'");
    }
    const string& address = prefix.substr(0, slash);
    const string& length = prefix.substr(slash + 1, string::npos);
    if (address.empty() || length.empty()) {
        isc_throw(BadValue,
                  "getPdPoolKea: malformed prefix '" << prefix << "'");
    }
    result->set("prefix", Element::create(address));
    try {
        unsigned len = boost::lexical_cast<unsigned>(length);
        result->set("prefix-len", Element::create(static_cast<int>(len)));
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(BadValue,
                  "getPdPoolKea: bad prefix length in '" << prefix << "'");
    }

    ConstElementPtr xpref = getItem(xpath + "/excluded-prefix");
    if (xpref) {
        const string& xprefix = xpref->stringValue();
        size_t xslash = xprefix.find("/");
        if (xslash == string::npos) {
            isc_throw(BadValue,
                      "getPdPoolKea: no '/' in excluded prefix '"
                      << xprefix << "'");
        }
        const string& xaddress = xprefix.substr(0, xslash);
        const string& xlength = xprefix.substr(xslash + 1, string::npos);
        if (xaddress.empty() || xlength.empty()) {
            isc_throw(BadValue,
                      "getPdPoolKea: malformed excluded prefix '"
                      << xprefix << "'");
        }
        result->set("excluded-prefix", Element::create(xaddress));
        try {
            unsigned xlen = boost::lexical_cast<unsigned>(xlength);
            result->set("excluded-prefix-len",
                        Element::create(static_cast<int>(xlen)));
        } catch (const boost::bad_lexical_cast&) {
            isc_throw(BadValue,
                      "getPdPoolKea: bad excluded prefix length in '"
                      << xprefix << "'");
        }
    }

    ConstElementPtr delegated = getItem(xpath + "/delegated-len");
    if (delegated) {
        result->set("delegated-len", delegated);
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
TranslatorPdPool::setPdPool(const string& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setPdPoolIetf6(xpath, elem);
        } else if (model_ == KEA_DHCP6_SERVER) {
            setPdPoolKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setPdPool not implemented for the model: " << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting pd-pool '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorPdPool::setPdPoolIetf6(const string& xpath, ConstElementPtr elem) {
    ConstElementPtr base = elem->get("prefix");
    ConstElementPtr length = elem->get("prefix-len");
    if (!base || !length) {
        isc_throw(BadValue,
                  "setPdPoolIetf6 requires prefix and prefix length: "
                  << elem->str());
    }
    ostringstream prefix;
    prefix << base->stringValue() << "/" << length->intValue();
    setItem(xpath + "/prefix", Element::create(prefix.str()), SR_STRING_T);
    setItem(xpath + "/prefix-length", length, SR_UINT8_T);
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
    // Skip rapid-commit.
    ConstElementPtr guard = elem->get("client-class");
    if (guard) {
        setItem(xpath + "/client-class", guard, SR_STRING_T);
    }
    // Set max pd space utilization to disabled.
    setItem(xpath + "/max-pd-space-utilization",
            Element::create(string("disabled")),
            SR_ENUM_T);
    // @todo option-data.
}

void
TranslatorPdPool::setPdPoolKea(const string& xpath, ConstElementPtr elem) {
    // Skip prefix as it is the key.
    bool created = false;
    ConstElementPtr delegated = elem->get("delegated-len");
    if (delegated) {
        setItem(xpath + "/delegated-len", delegated, SR_UINT8_T);
    }
    ConstElementPtr xprefix = elem->get("excluded-prefix");
    ConstElementPtr xlen = elem->get("excluded-prefix-len");
    if (xprefix && xlen) {
        ostringstream xpref;
        xpref << xprefix->stringValue() << "/" << xlen->intValue();
        setItem(xpath + "/excluded-prefix", Element::create(xpref.str()),
                SR_STRING_T);
        created = true;
    }
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

TranslatorPdPools::TranslatorPdPools(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPdPool(session, model) {
}

TranslatorPdPools::~TranslatorPdPools() {
}

ElementPtr
TranslatorPdPools::getPdPools(const string& xpath) {
    try {
        if ((model_ == IETF_DHCPV6_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getPdPoolsCommon(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting pd-pools at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getPdPools not implemented for the model: " << model_);
}

ElementPtr
TranslatorPdPools::getPdPoolsCommon(const string& xpath) {
    return getList<TranslatorPdPool>(xpath + "/pd-pool", *this,
                                     &TranslatorPdPool::getPdPool);
}

void
TranslatorPdPools::setPdPools(const string& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setPdPoolsId(xpath, elem);
        } else if (model_ == KEA_DHCP6_SERVER) {
            setPdPoolsPrefix(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setPdPools not implemented for the model: " << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting pools '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorPdPools::setPdPoolsId(const string& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr pool = elem->get(i);
        ostringstream prefix;
        prefix << xpath << "/pd-pool[pool-id='" << i << "']";
        setPdPool(prefix.str(), pool);
    }
}

void
TranslatorPdPools::setPdPoolsPrefix(const string& xpath,
                                    ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr pool = elem->get(i);
        if (!pool->contains("prefix") || !pool->contains("prefix-len")) {
            isc_throw(BadValue, "pd-pool requires prefix and prefix length: "
                      << pool->str());
        }
        ostringstream prefix;
        prefix << xpath << "/pd-pool[prefix='"
               << pool->get("prefix")->stringValue() << "/"
               << pool->get("prefix-len")->intValue() << "']";
        setPdPool(prefix.str(), pool);
    }
}

}  // namespace yang
}  // namespace isc
