// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/fd_event_handler_factory.h>
#include <util/select_event_handler.h>

namespace isc {
namespace util {

FDEventHandlerPtr FDEventHandlerFactory::factoryFDEventHandler() {
    // todo: use configuration to initialize the FDEventHandler.
    return (FDEventHandlerPtr(new SelectEventHandler()));
}

} // end of namespace isc::util
} // end of namespace isc
