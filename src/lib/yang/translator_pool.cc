// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <asiolink/io_address.h>
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
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model) {
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
        isc_throw(NetconfError,
                  "getting pool:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getPool not implemented for the model: " << model_);
}

ElementPtr
TranslatorPool::getPoolFromAbsoluteXpath(string const& xpath) {
    try {
        return getPool(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorPool::getPoolIetf6(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    getMandatoryDivergingLeaf(result, data_node, "pool", "pool-prefix");

    checkAndGetLeaf(result, data_node, "client-class");
    checkAndGetLeaf(result, data_node, "preferred-lifetime");
    checkAndGetLeaf(result, data_node, "valid-lifetime");

    checkAndGetDivergingLeaf(result, data_node, "rebind-timer", "rebind-time");
    checkAndGetDivergingLeaf(result, data_node, "renew-timer", "renew-time");

    // Skip max-addr-count.
    // Skip pool-id which exists but is not used.
    // Skip rapid-commit.
    // Skip start-address - end-address as prefix form is mandatory?
    // @todo: option-data
    // No require-client-classes.
    // No user-context.

    return (result->empty() ? ElementPtr() : result);
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
            isc_throw(MissingNode, "getPoolKea requires either prefix or "
                      "both start and end addresses");
        }
        ostringstream range;
        range << start_addr->stringValue() << " - "
              << end_addr->stringValue();
        result->set("pool", Element::create(range.str()));
    }
    ConstElementPtr options = getOptionDataList(data_node);
    if (options) {
        result->set("option-data", options);
    }

    checkAndGetLeaf(result, data_node, "client-class");
    checkAndGetLeaf(result, data_node, "require-client-classes");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    return (result->empty() ? ElementPtr() : result);
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
        isc_throw(NetconfError,
                  "setting pool '" << elem->str()
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

    checkAndSetLeaf(elem, xpath, "client-class", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "preferred-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "valid-lifetime", LeafBaseType::Uint32);

    checkAndSetDivergingLeaf(elem, xpath, "rebind-timer", "rebind-time", LeafBaseType::Uint32);
    checkAndSetDivergingLeaf(elem, xpath, "renew-timer", "renew-time", LeafBaseType::Uint32);

    // Set max address count to disabled.
    setItem(xpath + "/max-address-count",
            Element::create("disabled"),
            LeafBaseType::Enum);

    // Skip max-addr-count.
    // Skip rapid-commit.
    // @todo: option-data
}

void
TranslatorPool::setPoolKea(string const& xpath, ConstElementPtr elem) {
    // Skip keys "start-address" and "end-address".

    ConstElementPtr pool = elem->get("pool");
    if (!pool) {
        isc_throw(BadValue, "setPoolKea requires pool: " << elem->str());
    }

    // Keys are set by setting the list itself.
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    checkAndSetLeaf(elem, xpath, "client-class", LeafBaseType::String);

    checkAndSetLeafList(elem, xpath, "require-client-classes", LeafBaseType::String);

    checkAndSetUserContext(elem, xpath);

    string prefix = pool->stringValue();
    string start_addr;
    string end_addr;
    getAddresses(prefix, start_addr, end_addr);
    if (prefix.find("/") != string::npos) {
        setItem(xpath + "/prefix", pool, LeafBaseType::String);
    }
    ConstElementPtr options = elem->get("option-data");
    if (options && !options->empty()) {
        setOptionDataList(xpath, options);
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
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPool(session, model) {
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
        isc_throw(NetconfError,
                  "getting pools:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getPools not implemented for the model: " << model_);
}

ElementPtr
TranslatorPools::getPoolsFromAbsoluteXpath(string const& xpath) {
    try {
        return getPools(findXPath(xpath));
    } catch (NetconfError const&) {
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
        isc_throw(NetconfError,
                  "setting pools '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorPools::setPoolsById(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr pool = elem->getNonConst(i);
        ostringstream prefix;
        prefix << xpath << "/address-pool[pool-id='" << i << "']";
        setPool(prefix.str(), pool);
    }
}

void
TranslatorPools::setPoolsByAddresses(string const& xpath,
                                     ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr pool = elem->getNonConst(i);
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
