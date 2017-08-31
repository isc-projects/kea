// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHARED_SUBNET_PARSER_H
#define SHARED_SUBNET_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/shared_network.h>

namespace isc {
namespace dhcp {

class SharedNetworkParser : public isc::data::SimpleParser {
public:

    virtual ~SharedNetworkParser();

    virtual SharedNetworkPtr
    parse(const data::ConstElementPtr& shared_network_data);

};

} // enf of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_SUBNET_PARSER_H
