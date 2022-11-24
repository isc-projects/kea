// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_logger.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorLogger::TranslatorLogger(Session session, const string& model)
    : Translator(session, model) {
}

ElementPtr
TranslatorLogger::getLogger(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            return (getLoggerKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting logger: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getLogger not implemented for the model: " << model_);
}

ElementPtr
TranslatorLogger::getLoggerKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    getMandatoryLeaf(result, data_node, "name");

    checkAndGetLeaf(result, data_node, "debuglevel");
    checkAndGetLeaf(result, data_node, "severity");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    ConstElementPtr options = getOutputOptions(data_node);
    if (options) {
        result->set("output_options", options);
    }

    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorLogger::getOutputOption(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    getMandatoryLeaf(result, data_node, "output");

    checkAndGetLeaf(result, data_node, "flush");
    checkAndGetLeaf(result, data_node, "maxsize");
    checkAndGetLeaf(result, data_node, "maxver");
    checkAndGetLeaf(result, data_node, "pattern");

    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorLogger::getOutputOptions(DataNode const& data_node) {
    return getList(data_node, "output-option", *this,
                   &TranslatorLogger::getOutputOption);
}

void
TranslatorLogger::setLogger(string const& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            setLoggerKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setLogger not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting logger '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorLogger::setLoggerKea(string const& xpath, ConstElementPtr elem) {
    // Skip key "name".

    checkAndSetLeaf(elem, xpath, "debuglevel", LeafBaseType::Uint8);
    checkAndSetLeaf(elem, xpath, "severity", LeafBaseType::Enum);
    checkAndSetUserContext(elem, xpath);

    ConstElementPtr options = elem->get("output_options");
    if (options && !options->empty()) {
        setOutputOptions(xpath, options);
    }
}

void
TranslatorLogger::setOutputOption(string const& xpath, ConstElementPtr elem) {
    // Keys are set by setting the list itself.
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    checkAndSetLeaf(elem, xpath, "flush", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "maxsize", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "maxver", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "pattern", LeafBaseType::String);
}

void
TranslatorLogger::setOutputOptions(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr option = elem->getNonConst(i);
        if (!option->contains("output")) {
            isc_throw(BadValue, "output-option without output: "
                      << option->str());
        }
        string output = option->get("output")->stringValue();
        ostringstream key;
        key << xpath << "/output-option[output='" << output << "']";
        setOutputOption(key.str(), option);
    }
}

TranslatorLoggers::TranslatorLoggers(Session session, const string& model)
    : Translator(session, model),
      TranslatorLogger(session, model) {
}

ConstElementPtr
TranslatorLoggers::getLoggers(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            return (getLoggersKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting loggers: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getLoggers not implemented for the model: " << model_);
}

ConstElementPtr
TranslatorLoggers::getLoggersFromAbsoluteXpath(string const& xpath) {
    try {
        return getLoggers(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorLoggers::getLoggersKea(DataNode const& data_node) {
    return getList<TranslatorLogger>(data_node, "logger", *this,
                                     &TranslatorLogger::getLogger);
}

void
TranslatorLoggers::setLoggers(string const& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            setLoggersKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setLoggers not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting loggers '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorLoggers::setLoggersKea(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr logger = elem->getNonConst(i);
        if (!logger->contains("name")) {
            isc_throw(BadValue, "logger without name: " << logger->str());
        }
        string name = logger->get("name")->stringValue();
        ostringstream key;
        key << xpath << "/logger[name='" << name << "']";
        setLogger(key.str(), logger);
    }
}

}  // namespace yang
}  // namespace isc
