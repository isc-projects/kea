// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_logger.h>
#include <yang/adaptor.h>
#include <yang/yang_models.h>
#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorLogger::TranslatorLogger(Session session, const string& model)
    : TranslatorBasic(session, model) {
}

TranslatorLogger::~TranslatorLogger() {
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
        isc_throw(SysrepoError,
                  "sysrepo error getting logger: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getLogger not implemented for the model: " << model_);
}

ElementPtr
TranslatorLogger::getLoggerKea(DataNode const& data_node) {
    ConstElementPtr name = getItem(data_node, "name");
    if (!name) {
        // Can't happen as name is the key.
        isc_throw(Unexpected, "getLoggerKea requires name: ");
    }
    ElementPtr result = Element::createMap();
    result->set("name", name);
    ConstElementPtr options = getOutputOptions(data_node);
    if (options && (options->size() > 0)) {
        result->set("output_options", options);
    }
    ConstElementPtr severity = getItem(data_node, "severity");
    if (severity) {
        result->set("severity", severity);
    }
    ConstElementPtr debuglevel = getItem(data_node, "debuglevel");
    if (debuglevel) {
        result->set("debuglevel", debuglevel);
    }
    ConstElementPtr context = getItem(data_node, "user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

ElementPtr
TranslatorLogger::getOutputOption(DataNode const& data_node) {
    ConstElementPtr output = getItem(data_node, "output");
    if (!output) {
        // Can't happen as output is the key.
        isc_throw(Unexpected, "getOutputOption requires (!output): ");
    }
    ElementPtr result = Element::createMap();
    result->set("output", output);
    ConstElementPtr maxver = getItem(data_node, "maxver");
    if (maxver) {
        result->set("maxver", maxver);
    }
    ConstElementPtr maxsize = getItem(data_node, "maxsize");
    if (maxsize) {
        result->set("maxsize", maxsize);
    }
    ConstElementPtr flush = getItem(data_node, "flush");
    if (flush) {
        result->set("flush", flush);
    }
    ConstElementPtr pattern = getItem(data_node, "pattern");
    if (pattern) {
        result->set("pattern", pattern);
    }
    return (result);
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
        isc_throw(SysrepoError,
                  "sysrepo error setting logger '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorLogger::setLoggerKea(string const& xpath, ConstElementPtr elem) {
    // Skip name as it is the key.
    ConstElementPtr options = elem->get("output_options");
    if (options && (options->size() > 0)) {
        setOutputOptions(xpath, options);
    }
    ConstElementPtr debuglevel = elem->get("debuglevel");
    if (debuglevel) {
        setItem(xpath + "/debuglevel", debuglevel, LeafBaseType::Uint8);
    }
    ConstElementPtr severity = elem->get("severity");
    if (severity) {
        setItem(xpath + "/severity", severity, LeafBaseType::Enum);
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                LeafBaseType::String);
    }
}

void
TranslatorLogger::setOutputOption(string const& xpath, ConstElementPtr elem) {
    // Keys are set by setting the list itself.
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    ConstElementPtr maxver = elem->get("maxver");
    if (maxver) {
        setItem(xpath + "/maxver", maxver, LeafBaseType::Uint32);
    }
    ConstElementPtr maxsize = elem->get("maxsize");
    if (maxsize) {
        setItem(xpath + "/maxsize", maxsize, LeafBaseType::Uint32);
    }
    ConstElementPtr flush = elem->get("flush");
    if (flush) {
        setItem(xpath + "/flush", flush, LeafBaseType::Bool);
    }
    ConstElementPtr pattern = elem->get("pattern");
    if (pattern) {
        setItem(xpath + "/pattern", pattern, LeafBaseType::String);
    }
}

void
TranslatorLogger::setOutputOptions(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr option = elem->get(i);
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
    : TranslatorBasic(session, model),
      TranslatorLogger(session, model) {
}

TranslatorLoggers::~TranslatorLoggers() {
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
        isc_throw(SysrepoError,
                  "sysrepo error getting loggers: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getLoggers not implemented for the model: " << model_);
}

ConstElementPtr
TranslatorLoggers::getLoggers(string const& xpath) {
    try {
        return getLoggers(findXPath(xpath));
    } catch(SysrepoError const&) {
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
        isc_throw(SysrepoError,
                  "sysrepo error setting loggers '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorLoggers::setLoggersKea(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr logger = elem->get(i);
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
