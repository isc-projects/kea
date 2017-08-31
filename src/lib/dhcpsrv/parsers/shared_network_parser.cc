// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHARED_NETWORK_PARSER_H
#define SHARED_NETWORK_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <dhcpsrv/shared_network.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

SharedNetworkParser::~SharedNetworkParser() {
}

SharedNetworkPtr
SharedNetworkParser::parse(const ConstElementPtr& shared_network_data) {
    return (SharedNetworkPtr());
}

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_NETWORK_PARSER_H
