// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorLogger::TranslatorLogger(S_Session session, const string& model)
    : TranslatorBasic(session, model) {
}

TranslatorLogger::~TranslatorLogger() {
}

ElementPtr
TranslatorLogger::getLogger(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            return (getLoggerKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting logger at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getLogger not implemented for the model: " << model_);
}

ElementPtr
TranslatorLogger::getLoggerKea(const string& xpath) {
    ConstElementPtr name = getItem(xpath + "/name");
    if (!name) {
        // Can't happen as name is the key.
        isc_throw(Unexpected, "getLoggerKea requires name: " << xpath);
    }
    ElementPtr result = Element::createMap();
    result->set("name", name);
    ConstElementPtr options = getOutputOptions(xpath);
    if (options && (options->size() > 0)) {
        result->set("output_options", options);
    }
    ConstElementPtr severity = getItem(xpath + "/severity");
    if (severity) {
        result->set("severity", severity);
    }
    ConstElementPtr debuglevel = getItem(xpath + "/debuglevel");
    if (debuglevel) {
        result->set("debuglevel", debuglevel);
    }
    ConstElementPtr context = getItem(xpath + "/user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

ElementPtr
TranslatorLogger::getOutputOption(const string& xpath) {
    ConstElementPtr output = getItem(xpath + "/output");
    if (!output) {
        // Can't happen as output is the key.
        isc_throw(Unexpected, "getOutputOption requires (!output): " << xpath);
    }
    ElementPtr result = Element::createMap();
    result->set("output", output);
    ConstElementPtr maxver = getItem(xpath + "/maxver");
    if (maxver) {
        result->set("maxver", maxver);
    }
    ConstElementPtr maxsize = getItem(xpath + "/maxsize");
    if (maxsize) {
        result->set("maxsize", maxsize);
    }
    ConstElementPtr flush = getItem(xpath + "/flush");
    if (flush) {
        result->set("flush", flush);
    }
    ConstElementPtr pattern = getItem(xpath + "/pattern");
    if (pattern) {
        result->set("pattern", pattern);
    }
    return (result);
}

ElementPtr
TranslatorLogger::getOutputOptions(const string& xpath) {
    return getList(xpath + "/output-option", *this,
                   &TranslatorLogger::getOutputOption);
}

void
TranslatorLogger::setLogger(const string& xpath, ConstElementPtr elem) {
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
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting logger '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorLogger::setLoggerKea(const string& xpath, ConstElementPtr elem) {
    // Skip name as it is the key.
    ConstElementPtr options = elem->get("output_options");
    if (options && (options->size() > 0)) {
        setOutputOptions(xpath, options);
    }
    ConstElementPtr debuglevel = elem->get("debuglevel");
    if (debuglevel) {
        setItem(xpath + "/debuglevel", debuglevel, SR_UINT8_T);
    }
    ConstElementPtr severity = elem->get("severity");
    if (severity) {
        setItem(xpath + "/severity", severity, SR_ENUM_T);
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                SR_STRING_T);
    }
}

void
TranslatorLogger::setOutputOption(const string& xpath, ConstElementPtr elem) {
    bool created = false;
    // Skip output as it is the key.
    ConstElementPtr maxver = elem->get("maxver");
    if (maxver) {
        setItem(xpath + "/maxver", maxver, SR_UINT32_T);
        created = true;
    }
    ConstElementPtr maxsize = elem->get("maxsize");
    if (maxsize) {
        setItem(xpath + "/maxsize", maxsize, SR_UINT32_T);
        created = true;
    }
    ConstElementPtr flush = elem->get("flush");
    if (flush) {
        setItem(xpath + "/flush", flush, SR_BOOL_T);
        created = true;
    }
    ConstElementPtr pattern = elem->get("pattern");
    if (pattern) {
        setItem(xpath + "/pattern", pattern, SR_STRING_T);
        created = true;
    }
    // There is no mandatory fields outside the key so force creation.
    if (!created) {
        ConstElementPtr list = Element::createList();
        setItem(xpath, list, SR_LIST_T);
    }
}

void
TranslatorLogger::setOutputOptions(const string& xpath, ConstElementPtr elem) {
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

TranslatorLoggers::TranslatorLoggers(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorLogger(session, model) {
}

TranslatorLoggers::~TranslatorLoggers() {
}

ConstElementPtr
TranslatorLoggers::getLoggers(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            return (getLoggersKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting loggeres at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getLoggers not implemented for the model: " << model_);
}

ElementPtr
TranslatorLoggers::getLoggersKea(const string& xpath) {
    return getList<TranslatorLogger>(xpath + "/logger", *this,
                                     &TranslatorLogger::getLogger);
}

void
TranslatorLoggers::setLoggers(const string& xpath, ConstElementPtr elem) {
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
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting loggeres '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorLoggers::setLoggersKea(const string& xpath, ConstElementPtr elem) {
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
