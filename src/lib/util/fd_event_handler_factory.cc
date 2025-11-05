// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>

#ifdef HAVE_EPOLL
#include <util/epoll_event_handler.h>
#endif
#include <util/fd_event_handler_factory.h>
#ifdef HAVE_KQUEUE
#include <util/kqueue_event_handler.h>
#endif
#include <util/poll_event_handler.h>
#include <util/select_event_handler.h>

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
        if (string(env_type) == string("epoll")) {
            type = FDEventHandler::TYPE_EPOLL;
        }
    }
    switch(type) {
    case FDEventHandler::TYPE_SELECT:
        return (FDEventHandlerPtr(new SelectEventHandler()));
    case FDEventHandler::TYPE_EPOLL:
#ifdef HAVE_EPOLL
        return (FDEventHandlerPtr(new EPollEventHandler()));
#else
        isc_throw(BadValue, "fd event handler of type 'epoll' is not supported");
#endif
    case FDEventHandler::TYPE_KQUEUE:
#ifdef HAVE_KQUEUE
        return (FDEventHandlerPtr(new KQueueEventHandler()));
#else
        isc_throw(BadValue, "fd event handler of type 'kqueue' is not supported");
#endif
    case FDEventHandler::TYPE_POLL:
        return (FDEventHandlerPtr(new PollEventHandler()));
    default:
        return (FDEventHandlerPtr(new SelectEventHandler()));
    }
    return (FDEventHandlerPtr(new SelectEventHandler()));
}

} // end of namespace isc::util
} // end of namespace isc
