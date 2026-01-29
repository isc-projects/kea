// Copyright (C) 2025-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>

#include <util/fd_event_handler_factory.h>
#include <util/poll_event_handler.h>
#include <util/select_event_handler.h>

#include <cstdlib>
#include <string>

using namespace std;

namespace isc {
namespace util {

FDEventHandlerPtr FDEventHandlerFactory::factoryFDEventHandler() {
    // todo: use configuration to initialize the FDEventHandler.
    FDEventHandler::HandlerType type = FDEventHandler::TYPE_SELECT;
    const char* env_type = getenv("KEA_EVENT_HANDLER_TYPE");
    if (env_type) {
        if (string(env_type) == string("select")) {
            type = FDEventHandler::TYPE_SELECT;
        }
        if (string(env_type) == string("poll")) {
            type = FDEventHandler::TYPE_POLL;
        }
    }
    switch(type) {
    case FDEventHandler::TYPE_SELECT:
        return (FDEventHandlerPtr(new SelectEventHandler()));
    case FDEventHandler::TYPE_POLL:
        return (FDEventHandlerPtr(new PollEventHandler()));
    default:
        return (FDEventHandlerPtr(new SelectEventHandler()));
    }
    return (FDEventHandlerPtr(new SelectEventHandler()));
}

} // end of namespace isc::util
} // end of namespace isc
