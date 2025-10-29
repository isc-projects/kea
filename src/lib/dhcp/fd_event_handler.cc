// Copyright (C) 2011-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <fd_event_handler.h>

namespace isc {
namespace dhcp {

FDEventHandler::FDEventHandler(HandlerType type) : type_(type) {
}

FDEventHandler::HandlerType FDEventHandler::type() {
    return (type_);
}

} // end of namespace isc::dhcp
} // end of namespace isc
