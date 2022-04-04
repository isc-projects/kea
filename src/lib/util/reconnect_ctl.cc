// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <util/reconnect_ctl.h>
#include <exceptions/exceptions.h>

namespace isc {
namespace util {

std::string
ReconnectCtl::onFailActionToText(OnFailAction action) {
    switch (action) {
    case OnFailAction::STOP_RETRY_EXIT:
        return ("stop-retry-exit");
    case OnFailAction::SERVE_RETRY_EXIT:
        return ("serve-retry-exit");
    case OnFailAction::SERVE_RETRY_CONTINUE:
        return ("serve-retry-continue");
    }
    return ("invalid-action-type");
}

OnFailAction
ReconnectCtl::onFailActionFromText(const std::string& text) {
    if (text == "stop-retry-exit") {
        return (OnFailAction::STOP_RETRY_EXIT);
    } else if (text == "serve-retry-exit") {
        return (OnFailAction::SERVE_RETRY_EXIT);
    } else if (text == "serve-retry-continue") {
        return (OnFailAction::SERVE_RETRY_CONTINUE);
    } else {
        isc_throw(BadValue, "Invalid action on connection loss: " << text);
    }
}

}
}
