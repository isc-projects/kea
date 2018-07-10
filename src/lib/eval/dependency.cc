// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <eval/dependency.h>
#include <boost/pointer_cast.hpp>

namespace isc {
namespace dhcp {

bool dependOnClass(const TokenPtr& token, const std::string& name) {
    boost::shared_ptr<TokenMember> member;
    member = boost::dynamic_pointer_cast<TokenMember>(token);
    if (!member) {
        return (false);
    }
    return (member->getClientClass() == name);
}

bool dependOnClass(const ExpressionPtr& expr, const std::string& name) {
    if (!expr) {
        return (false);
    }
    for (auto it = expr->cbegin(); it != expr->cend(); ++it) {
        if (dependOnClass(*it, name)) {
            return (true);
        }
    }
    return (false);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
