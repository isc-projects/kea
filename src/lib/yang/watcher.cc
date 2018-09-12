// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/watcher.h>

using namespace std;
using namespace isc::data;

namespace isc {
namespace yang {

Watcher::Watcher(SysrepoConnection &connection, const string &xpath)
    : xpath_(xpath), netconf_data_(0), connection_(connection) {
};

Watcher::~Watcher() {
}

const string&
Watcher::getXPath() const {
    return (xpath_);
}

ElementPtr
Watcher::getJSON() {
    return (json_);
}

}  // namespace netconf
}  // namespace isc
