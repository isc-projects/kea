// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/multi_threading_utils.h>
#include <util/multi_threading_mgr.h>
#include <exceptions/exceptions.h>

using namespace isc::util;

namespace isc {
namespace dhcp {

void
MultiThreadingCriticalSection::stop_pkt_processing() {
    isc_throw(NotImplemented,
              "MultiThreadingCriticalSection::stop_pkt_processing "
              "is not yet implemented");
}

void
MultiThreadingCriticalSection::start_pkt_processing() {
    isc_throw(NotImplemented,
              "MultiThreadingCriticalSection::start_pkt_processing "
              "is not yet implemented");
}

MultiThreadingCriticalSection::MultiThreadingCriticalSection()
    : enabled_(MultiThreadingMgr::instance().getMode()) {
    if (enabled_) {
        stop_pkt_processing();
    }
}

MultiThreadingCriticalSection::~MultiThreadingCriticalSection() {
    if (enabled_) {
        start_pkt_processing();
    }
}

}
}
