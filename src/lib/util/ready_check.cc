// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/fd_event_handler_factory.h>

namespace isc {
namespace util {

int selectCheck(const int fd_to_check, const unsigned int timeout_sec,
                bool read_check, bool write_check) {
    FDEventHandlerPtr handler = FDEventHandlerFactory::factoryFDEventHandler();
    handler->add(fd_to_check, read_check, write_check);
    return (handler->waitEvent(timeout_sec, 0));
}

} // end of isc::util namespace
} // end of isc namespace
