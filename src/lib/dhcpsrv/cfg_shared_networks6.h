// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_SHARED_NETWORKS6_H
#define CFG_SHARED_NETWORKS6_H

#include <cc/cfg_to_element.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

class CfgSharedNetworks6 : public data::CfgToElement {
public:

};

typedef boost::shared_ptr<CfgSharedNetworks6> CfgSharedNetworks6Ptr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CFG_SHARED_NETWORKS6_H
