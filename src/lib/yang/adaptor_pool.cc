// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/adaptor_pool.h>
#include <yang/yang_models.h>

#include <vector>

using namespace std;
using namespace isc::data;

namespace isc {
namespace yang {

void
AdaptorPool::canonizePool(ElementPtr pool) {
    const string& orig = pool->get("pool")->stringValue();
    vector<char> v;
    for (char ch : orig) {
        if ((ch == ' ') || (ch == '\t') || (ch == '\n')) {
            continue;
        } else if (ch == '-') {
            v.push_back(' ');
            v.push_back(ch);
            v.push_back(' ');
        } else {
            v.push_back(ch);
        }
    }
    string canon;
    canon.assign(v.begin(), v.end());
    if (orig != canon) {
        pool->set("pool", Element::create(canon));
    }
}

void
AdaptorPool::fromSubnet(const string& model, ConstElementPtr subnet,
                        ConstElementPtr pools) {
    if (model == IETF_DHCPV6_SERVER) {
        fromSubnetIetf6(subnet, pools);
    } else if ((model != KEA_DHCP4_SERVER) &&
               (model != KEA_DHCP6_SERVER)) {
        isc_throw(NotImplemented,
                  "fromSubnet not implemented for the model: " << model);
    }
}

void
AdaptorPool::fromSubnetIetf6(ConstElementPtr subnet, ConstElementPtr pools) {
    Adaptor::fromParent("valid-lifetime", subnet, pools);
    Adaptor::fromParent("preferred-lifetime", subnet, pools);
    Adaptor::fromParent("renew-timer", subnet, pools);
    Adaptor::fromParent("rebind-timer", subnet, pools);
}

void
AdaptorPool::toSubnet(const string& model, ElementPtr subnet,
                      ConstElementPtr pools) {
    if (model == IETF_DHCPV6_SERVER) {
        toSubnetIetf6(subnet, pools);
    } else if ((model != KEA_DHCP4_SERVER) &&
               (model != KEA_DHCP6_SERVER)) {
        isc_throw(NotImplemented,
                  "toSubnet not implemented for the model: " << model);
    }
}

void
AdaptorPool::toSubnetIetf6(ElementPtr subnet, ConstElementPtr pools) {
    Adaptor::toParent("valid-lifetime", subnet, pools);
    Adaptor::toParent("preferred-lifetime", subnet, pools);
    Adaptor::toParent("renew-timer", subnet, pools);
    Adaptor::toParent("rebind-timer", subnet, pools);
}

}  // namespace yang
}  // namespace isc
