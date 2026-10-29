// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <rbac/rbac.h>
#include <rbac_log.h>

using namespace isc;
using namespace isc::data;
using namespace isc::http;
using namespace isc::log;
using namespace isc::rbac;
using namespace std;

namespace isc {
namespace rbac {

RolePtr roleAssign;

RoleConfigTable roleConfigTable;

RoleConfigPtr defaultRoleConfig;

RoleConfigPtr unknownRoleConfig;

const SimpleKeywords RoleConfig::ROLE_PARAMETERS = {
    { "name",              Element::string },
    { "accept-commands",   Element::any },
    { "reject-commands",   Element::any },
    { "other-commands",    Element::string },
    { "list-match-first",  Element::string },
    { "response-filters",  Element::list },
    { "comment",           Element::string }
};

RoleConfigPtr
RoleConfig::getConfig(const string& role) {
    if (role.empty()) {
        return (defaultRoleConfig);
    }
    auto it = roleConfigTable.find(role);
    if (it == roleConfigTable.end()) {
        return (unknownRoleConfig);
    }
    return (it->second);
}

RoleConfigPtr
RoleConfig::parse(ConstElementPtr cfg, string name) {
    if (!cfg) {
        isc_throw(BadValue, "parse null role config");
    }
    if (cfg->getType() != Element::map) {
        isc_throw(BadValue, "role config is not a map");
    }

    // Keywords.
    SimpleParser::checkKeywords(RoleConfig::ROLE_PARAMETERS, cfg);

    // Name.
    ConstElementPtr name_elem = cfg->get("name");
    if (!name.empty() && name_elem) {
        isc_throw(BadValue, "spurious 'name' parameter for " << name
                  << " role");
    } else if (name.empty() && !name_elem) {
        isc_throw(BadValue, "'name' parameter is required in " << cfg->str());
    }
    if (name_elem) {
        name = name_elem->stringValue();
        if (name.empty()) {
            isc_throw(BadValue, "role config name is empty");
        }
    }

    // Accept ACL.
    ConstElementPtr accept_elem = cfg->get("accept-commands");
    AclPtr accept;
    if (accept_elem) {
        accept = Acl::parse(accept_elem);
    }

    // Reject ACL.
    ConstElementPtr reject_elem = cfg->get("reject-commands");
    AclPtr reject;
    if (reject_elem) {
        reject = Acl::parse(reject_elem);
    }

    // Others.
    bool others = false;
    ConstElementPtr others_elem = cfg->get("other-commands");
    if (others_elem) {
        const string& action = others_elem->stringValue();
        if ((action!= "accept") && (action != "reject")) {
            isc_throw(BadValue, "other-commands '" << action
                      << "' is not 'accept' or 'reject'");
        }
        others = (action == "accept");
    }

    // Preference.
    bool preference = true;
    ConstElementPtr pref_elem = cfg->get("list-match-first");
    if (pref_elem) {
        const string& pref = pref_elem->stringValue();
        if ((pref != "accept") && (pref != "reject")) {
            isc_throw(BadValue, "list-match-first '" << pref
                      << "' is not 'accept' or 'reject'");
        }
        preference = (pref == "accept");
    }

    // Response filters.
    ConstElementPtr resp_filters = cfg->get("response-filters");
    ResponseFilterList response_filters;
    if (resp_filters) {
        response_filters = ResponseFilter::parse(resp_filters);
    }

    return (RoleConfigPtr(new RoleConfig(name, accept, reject, others,
                                         preference, response_filters)));
}

HttpResponseJsonPtr
RoleConfig::createReject(const HttpRequestPtr& request,
                         const HttpStatusCode& status_code) {
    if (!request) {
        // Should not happen!
        isc_throw(Unexpected, "null request");
    }
    // From CmdResponseCreator::createStockHttpResponseInternal.
    HttpVersion http_version(request->context()->http_version_major_,
                             request->context()->http_version_minor_);
    if ((http_version < HttpVersion(1, 0)) ||
        (HttpVersion(1, 1) < http_version)) {
        http_version.major_ = 1;
        http_version.minor_ = 0;
    }
    HttpResponseJsonPtr response(new HttpResponseJson(http_version,
                                                      status_code));
    ElementPtr body = Element::createMap();
    uint16_t result = HttpResponse::statusCodeToNumber(status_code);
    body->set("result", Element::create(static_cast<long long>(result)));
    const string& text = HttpResponse::statusCodeToString(status_code);
    body->set("text", Element::create(text));
    response->setBodyAsJson(body);
    response->finalize();
    return (response);
}

} // end of namespace rbac
} // end of namespace isc
