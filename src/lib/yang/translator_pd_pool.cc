// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorPdPool::TranslatorPdPool(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model) {
}

TranslatorPdPool::~TranslatorPdPool() {
}

ElementPtr
TranslatorPdPool::getPdPool(DataNode const& data_node) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getPdPoolIetf6(data_node));
        } else if (model_ == KEA_DHCP6_SERVER) {
            return (getPdPoolKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting pd-pool:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getPdPool not implemented for the model: " << model_);
}

ElementPtr
TranslatorPdPool::getPdPool(string const& xpath) {
    try {
        return getPdPool(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorPdPool::getPdPoolIetf6(DataNode const& data_node) {
    ElementPtr result = Element::createMap();
    ConstElementPtr pref = getItem(data_node, "prefix");
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
    ConstElementPtr preflen = getItem(data_node, "prefix-length");
    if (!preflen) {
        isc_throw(BadValue, "getPdPoolIetf6: prefix length is required");
    }
    result->set("prefix-len", preflen);
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
    // Skip rapid-commit.
    ConstElementPtr guard = getItem(data_node, "client-class");
    if (guard) {
        result->set("client-class", guard);
    }
    // no require-client-classes nor user-context.
    // Skip max-pd-space-utilization.
    // @todo option-data.
    return (result);
}

ElementPtr
TranslatorPdPool::getPdPoolKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();
    ConstElementPtr pref = getItem(data_node, "prefix");
    if (!pref) {
        isc_throw(BadValue, "getPdPoolKea: no prefix defined");
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

    ConstElementPtr xpref = getItem(data_node, "excluded-prefix");
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

    ConstElementPtr delegated = getItem(data_node, "delegated-len");
    if (delegated) {
        result->set("delegated-len", delegated);
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
TranslatorPdPool::setPdPool(string const& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setPdPoolIetf6(xpath, elem);
        } else if (model_ == KEA_DHCP6_SERVER) {
            setPdPoolKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setPdPool not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting pd-pool '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorPdPool::setPdPoolIetf6(string const& xpath, ConstElementPtr elem) {
    ConstElementPtr base = elem->get("prefix");
    ConstElementPtr length = elem->get("prefix-len");
    if (!base || !length) {
        isc_throw(BadValue,
                  "setPdPoolIetf6 requires prefix and prefix length: "
                  << elem->str());
    }
    ostringstream prefix;
    prefix << base->stringValue() << "/" << length->intValue();
    setItem(xpath + "/prefix", Element::create(prefix.str()), LeafBaseType::String);
    setItem(xpath + "/prefix-length", length, LeafBaseType::Uint8);
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
    // Skip rapid-commit.
    ConstElementPtr guard = elem->get("client-class");
    if (guard) {
        setItem(xpath + "/client-class", guard, LeafBaseType::String);
    }
    // Set max pd space utilization to disabled.
    setItem(xpath + "/max-pd-space-utilization",
            Element::create(string("disabled")),
            LeafBaseType::Enum);
    // @todo option-data.
}

void
TranslatorPdPool::setPdPoolKea(string const& xpath, ConstElementPtr elem) {
    // Keys are set by setting the list itself.
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    ConstElementPtr delegated = elem->get("delegated-len");
    if (delegated) {
        setItem(xpath + "/delegated-len", delegated, LeafBaseType::Uint8);
    }
    ConstElementPtr xprefix = elem->get("excluded-prefix");
    ConstElementPtr xlen = elem->get("excluded-prefix-len");
    if (xprefix && xlen) {
        ostringstream xpref;
        xpref << xprefix->stringValue() << "/" << xlen->intValue();
        setItem(xpath + "/excluded-prefix", Element::create(xpref.str()),
                LeafBaseType::String);
    }
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

TranslatorPdPools::TranslatorPdPools(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPdPool(session, model) {
}

TranslatorPdPools::~TranslatorPdPools() {
}

ElementPtr
TranslatorPdPools::getPdPools(DataNode const& data_node) {
    try {
        if ((model_ == IETF_DHCPV6_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getPdPoolsCommon(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting pd-pools:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getPdPools not implemented for the model: " << model_);
}

ElementPtr
TranslatorPdPools::getPdPools(string const& xpath) {
    try {
        return getPdPools(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorPdPools::getPdPoolsCommon(DataNode const& data_node) {
    return getList<TranslatorPdPool>(data_node, "pd-pool", *this,
                                     &TranslatorPdPool::getPdPool);
}

void
TranslatorPdPools::setPdPools(string const& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setPdPoolsId(xpath, elem);
        } else if (model_ == KEA_DHCP6_SERVER) {
            setPdPoolsPrefix(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setPdPools not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting pools '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorPdPools::setPdPoolsId(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr pool = elem->get(i);
        ostringstream prefix;
        prefix << xpath << "/pd-pool[pool-id='" << i << "']";
        setPdPool(prefix.str(), pool);
    }
}

void
TranslatorPdPools::setPdPoolsPrefix(string const& xpath,
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
