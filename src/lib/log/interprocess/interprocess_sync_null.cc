// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <log/interprocess/interprocess_sync_null.h>

namespace isc {
namespace log {
namespace interprocess {

InterprocessSyncNull::~InterprocessSyncNull() {
}

bool
InterprocessSyncNull::lock() {
    is_locked_ = true;
    return (true);
}

bool
InterprocessSyncNull::tryLock() {
    is_locked_ = true;
    return (true);
}

bool
InterprocessSyncNull::unlock() {
    is_locked_ = false;
    return (true);
}

} // namespace interprocess
} // namespace log
} // namespace isc
