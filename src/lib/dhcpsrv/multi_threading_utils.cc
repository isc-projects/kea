// Copyright (C) 2019-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/multi_threading_utils.h>
#include <exceptions/exceptions.h>
#include <util/multi_threading_mgr.h>


using namespace isc::util;

namespace isc {
namespace dhcp {

void
MultiThreadingCriticalSection::stopPktProcessing() {
    isc_throw(NotImplemented,
              "MultiThreadingCriticalSection::stopPktProcessing "
              "is not yet implemented");
}

void
MultiThreadingCriticalSection::startPktProcessing() {
    isc_throw(NotImplemented,
              "MultiThreadingCriticalSection::startPktProcessing "
              "is not yet implemented");
}

MultiThreadingCriticalSection::MultiThreadingCriticalSection() {
    if (MultiThreadingMgr::instance().getMode()) {
        stopPktProcessing();
    }
}

MultiThreadingCriticalSection::~MultiThreadingCriticalSection() {
    if (MultiThreadingMgr::instance().getMode()) {
        startPktProcessing();
    }
}

}  // namespace dhcp
}  // namespace isc
