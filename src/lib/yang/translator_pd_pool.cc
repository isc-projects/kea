// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

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
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model) {
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
        isc_throw(NetconfError,
                  "getting pd-pool:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getPdPool not implemented for the model: " << model_);
}

ElementPtr
TranslatorPdPool::getPdPoolFromAbsoluteXpath(string const& xpath) {
    try {
        return getPdPool(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorPdPool::getPdPoolIetf6(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    ConstElementPtr pref = getItem(data_node, "prefix");
    if (!pref) {
        isc_throw(MissingNode, "getPdPoolIetf6: prefix is required");
    }
    const string& prefix = pref->stringValue();
    size_t slash = prefix.find("/");
    if (slash == string::npos) {
        isc_throw(MissingNode,
                  "getPdPoolIetf6: no '/' in prefix '" << prefix << "'");
    }
    const string& address = prefix.substr(0, slash);
    if (address.empty()) {
        isc_throw(MissingNode,
                  "getPdPoolIetf6: malformed prefix '" << prefix << "'");
    }
    result->set("prefix", Element::create(address));

    // Silly: the prefix length is specified twice...
    getMandatoryDivergingLeaf(result, data_node, "prefix-len", "prefix-length");

    checkAndGetLeaf(result, data_node, "preferred-lifetime");
    checkAndGetLeaf(result, data_node, "client-class");
    checkAndGetLeaf(result, data_node, "valid-lifetime");

    checkAndGetDivergingLeaf(result, data_node, "rebind-timer", "rebind-time");
    checkAndGetDivergingLeaf(result, data_node, "renew-timer", "renew-time");

    // no require-client-classes nor user-context.
    // Skip max-pd-space-utilization.
    // Skip rapid-commit.
    // @todo: option-data

    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorPdPool::getPdPoolKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();
    ConstElementPtr pref = getItem(data_node, "prefix");
    if (!pref) {
        isc_throw(MissingNode, "getPdPoolKea: no prefix defined");
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

    checkAndGetLeaf(result, data_node, "client-class");
    checkAndGetLeaf(result, data_node, "delegated-len");
    checkAndGetLeaf(result, data_node, "require-client-classes");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    ConstElementPtr options = getOptionDataList(data_node);
    if (options) {
        result->set("option-data", options);
    }

    return (result->empty() ? ElementPtr() : result);
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
        isc_throw(NetconfError,
                  "setting pd-pool '" << elem->str()
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

    checkAndSetLeaf(elem, xpath, "client-class", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "preferred-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "valid-lifetime", LeafBaseType::Uint32);

    checkAndSetDivergingLeaf(elem, xpath, "rebind-timer", "rebind-time", LeafBaseType::Uint32);
    checkAndSetDivergingLeaf(elem, xpath, "renew-timer", "renew-time", LeafBaseType::Uint32);

    // Set max pd space utilization to disabled.
    setItem(xpath + "/max-pd-space-utilization", Element::create("disabled"),
            LeafBaseType::Enum);

    // Skip rapid-commit.
    // @todo: option-data
}

void
TranslatorPdPool::setPdPoolKea(string const& xpath, ConstElementPtr elem) {
    // Keys are set by setting the list itself.
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    checkAndSetLeaf(elem, xpath, "client-class", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "delegated-len", LeafBaseType::Uint8);

    checkAndSetLeafList(elem, xpath, "require-client-classes", LeafBaseType::String);

    checkAndSetUserContext(elem, xpath);

    ConstElementPtr xprefix = elem->get("excluded-prefix");
    ConstElementPtr xlen = elem->get("excluded-prefix-len");
    if (xprefix && xlen) {
        ostringstream xpref;
        xpref << xprefix->stringValue() << "/" << xlen->intValue();
        setItem(xpath + "/excluded-prefix", Element::create(xpref.str()), LeafBaseType::String);
    }
    ConstElementPtr options = elem->get("option-data");
    if (options && !options->empty()) {
        setOptionDataList(xpath, options);
    }
}

TranslatorPdPools::TranslatorPdPools(Session session, const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPdPool(session, model) {
}

ElementPtr
TranslatorPdPools::getPdPools(DataNode const& data_node) {
    try {
        if ((model_ == IETF_DHCPV6_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getPdPoolsCommon(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting pd-pools:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getPdPools not implemented for the model: " << model_);
}

ElementPtr
TranslatorPdPools::getPdPoolsFromAbsoluteXpath(string const& xpath) {
    try {
        return getPdPools(findXPath(xpath));
    } catch (NetconfError const&) {
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
        isc_throw(NetconfError,
                  "setting pools '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorPdPools::setPdPoolsId(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr pool = elem->getNonConst(i);
        ostringstream prefix;
        prefix << xpath << "/pd-pool[pool-id='" << i << "']";
        setPdPool(prefix.str(), pool);
    }
}

void
TranslatorPdPools::setPdPoolsPrefix(string const& xpath,
                                    ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr pool = elem->getNonConst(i);
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
