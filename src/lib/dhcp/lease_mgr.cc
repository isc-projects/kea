// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "lease_mgr.h"
#include <exceptions/exceptions.h>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <iostream>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <time.h>

using namespace std;

using namespace isc::dhcp;

LeaseMgr* LeaseMgr::instance_ = NULL;

Lease6::Lease6(LeaseType type, const isc::asiolink::IOAddress& addr, DuidPtr duid,
               uint32_t iaid, uint32_t preferred, uint32_t valid, uint32_t t1,
               uint32_t t2, SubnetID subnet_id, uint8_t prefixlen)
    :type_(type), addr_(addr), prefixlen_(prefixlen), iaid_(iaid), duid_(duid),
     preferred_lft_(preferred), valid_lft_(valid), t1_(t1), t2_(t2),
     subnet_id_(subnet_id), fixed_(false), fqdn_fwd_(false),
     fqdn_rev_(false) {
    if (duid == DuidPtr()) {
        isc_throw(InvalidOperation, "DUID must be specified for a lease");
    }

    cltt_ = time(NULL);
}

LeaseMgr& LeaseMgr::instance() {
    if (!instance_) {
        isc_throw(InvalidOperation, "LeaseManager not instantiated yet");
    }
    return (*instance_);
}

LeaseMgr::LeaseMgr(const std::string& dbconfig) {
    if (instance_) {
        isc_throw(InvalidOperation, "LeaseManager already instantiated");
    }

    // remember the pointer to the singleton instance
    instance_ = this;

    if (dbconfig.length() == 0) {
        return;
    }

    vector<string> tokens;

    // we need to pass a string to is_any_of, not just char *. Otherwise there
    // are cryptic warnings on Debian6 running g++ 4.4 in /usr/include/c++/4.4
    // /bits/stl_algo.h:2178 "array subscript is above array bounds"
    boost::split(tokens, dbconfig, boost::is_any_of( string("\t ") ));
    BOOST_FOREACH(std::string token, tokens) {
        size_t pos = token.find("=");
        if (pos != string::npos) {
            string name = token.substr(0, pos);
            string value = token.substr(pos + 1);
            parameters_.insert(pair<string,string>(name, value));
        } else {
            isc_throw(InvalidParameter, "Cannot parse " << token
                      << ", expected format is name=value");
        }

    }
}

std::string LeaseMgr::getParameter(const std::string& name) const {
    std::map<std::string, std::string>::const_iterator param
        = parameters_.find(name);
    if (param == parameters_.end()) {
        isc_throw(BadValue, "Parameter not found");
    }
    return (param->second);
}

LeaseMgr::~LeaseMgr() {
    instance_ = NULL;
}
