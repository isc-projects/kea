// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_SHARED_NETWORKS4_H
#define CFG_SHARED_NETWORKS4_H

#include <cc/cfg_to_element.h>
#include <dhcpsrv/shared_network.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

class CfgSharedNetworks4 : public data::CfgToElement {
public:

    void add(const SharedNetwork4Ptr& shared_network);

};

typedef boost::shared_ptr<CfgSharedNetworks4> CfgSharedNetworks4Ptr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CFG_SHARED_NETWORKS4_H
