// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/callout_handle_associate.h>
#include <hooks/hooks_manager.h>

namespace isc {
namespace hooks {

CalloutHandleAssociate::CalloutHandleAssociate()
    : callout_handle_() {
}

CalloutHandlePtr
CalloutHandleAssociate::getCalloutHandle() {
    if (!callout_handle_) {
        callout_handle_ = HooksManager::createCalloutHandle();
    }

    return (callout_handle_);
}

void
CalloutHandleAssociate::resetCalloutHandle() {
    callout_handle_.reset();
}

} // end of namespace isc::hooks
} // end of namespace isc
