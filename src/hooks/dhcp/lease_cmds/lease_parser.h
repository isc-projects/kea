// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_PARSER_H
#define LEASE_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/lease.h>

namespace isc {
namespace lease_cmds {

/// @brief Parser for a single Lease information.
class LeaseParser : public isc::data::SimpleParser {
};

class Lease4Parser : public LeaseParser {
public:
    virtual isc::dhcp::Lease4Ptr parse(const isc::data::ConstElementPtr& lease_info);
    virtual ~Lease4Parser() {}
};

class Lease6Parser : public LeaseParser {
public:
    virtual isc::dhcp::Lease6Ptr parse(const isc::data::ConstElementPtr& lease_info);
    virtual ~Lease6Parser() {}
};
    
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
    
