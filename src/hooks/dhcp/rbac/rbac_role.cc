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
using namespace isc::log;
using namespace isc::rbac;
using namespace std;

namespace isc {
namespace rbac {

RolePtr
Role::parse(ConstElementPtr cfg) {
    if (!cfg) {
        isc_throw(BadValue, "parse null role assignment config");
    }
    if (cfg->getType() != Element::string) {
        isc_throw(BadValue, "role assignment config is not a string");
    }
    const string& role = cfg->stringValue();
    if (role == "remote-address") {
        return (RolePtr(new RemoteRole()));
    } else if (role == "cert-subject") {
        return (RolePtr(new SubjectRole()));
    } else if (role == "cert-issuer") {
        return (RolePtr(new IssuerRole()));
    } else if (role == "basic-authentication") {
        return (RolePtr(new BasicAuthRole()));
    } else if (role == "custom-value") {
        return (RolePtr(new CustomRole()));
    } else {
        isc_throw(BadValue, "unknown role assignment keyword '" << role << "'");
    }
}

} // end of namespace rbac
} // end of namespace isc
