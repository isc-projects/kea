// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/simple_parser.h>
#include <http/cfg_http_header.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace http {

ElementPtr
CfgHttpHeader::toElement() const {
    ElementPtr map = isc::data::Element::createMap();
    contextToElement(map);
    map->set("name", Element::create(name_));
    map->set("value", Element::create(value_));
    return (map);
}

ElementPtr
CfgHttpHeaderstoElement(const CfgHttpHeaders& headers) {
    ElementPtr list = Element::createList();
    for (auto const& header : headers) {
        list->add(header.toElement());
    }
    return (list);
}

namespace {

const SimpleKeywords HTTP_HEADER_KEYWORDS = {
    { "name", Element::string },
    { "value", Element::string },
    { "user-context", Element::map }
};

const SimpleRequiredKeywords HTTP_HEADER_REQUIRED = { "name", "value" };

CfgHttpHeader
parseCfgHttpHeader(const ConstElementPtr& config) {
    if (!config) {
        // Should not happen.
        isc_throw(DhcpConfigError, "null 'http-headers' item");
    }
    if (config->getType() != Element::map) {
        isc_throw(DhcpConfigError, "invalid type specified for 'http-headers' "
                  "item (" << config->getPosition() << ")");
    }
    SimpleParser::checkKeywords(HTTP_HEADER_KEYWORDS, config);
    SimpleParser::checkRequired(HTTP_HEADER_REQUIRED, config);
    string name = config->get("name")->stringValue();
    if (name.empty()) {
        isc_throw(DhcpConfigError, "empty 'name' parameter ("
                  << config->get("name")->getPosition() << ")");
    }
    string value = config->get("value")->stringValue();
    if (value.empty()) {
        isc_throw(DhcpConfigError, "empty 'value' parameter ("
                  << config->get("value")->getPosition() << ")");
    }
    CfgHttpHeader header(name, value);
    ConstElementPtr user_context = config->get("user-context");
    if (user_context) {
        header.setContext(user_context);
    }
    return (header);
}

}

CfgHttpHeaders
parseCfgHttpHeaders(const ConstElementPtr& config) {
    CfgHttpHeaders headers;
    if (!config) {
        return (headers);
    }
    if (config->getType() != Element::list) {
        isc_throw(DhcpConfigError, "invalid type specified for parameter "
                  "'http-headers' (" << config->getPosition() << ")");
    }
    for (auto const& item : config->listValue()) {
        headers.push_back(parseCfgHttpHeader(item));
    }
    return (headers);
}

} // namespace http
} // namespace isc
