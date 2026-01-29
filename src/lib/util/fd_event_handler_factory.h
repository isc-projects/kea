// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FD_EVENT_HANDLER_FACTORY_H
#define FD_EVENT_HANDLER_FACTORY_H

#include <util/fd_event_handler.h>

namespace isc {
namespace util {

/// @brief File descriptor event handler factory class handles the creation of
/// the FDEventHangler instance according to configuration and OS supported
/// syscalls.
class FDEventHandlerFactory {
public:

    /// @brief Constructor.
    FDEventHandlerFactory() = default;

    /// @brief Destructor.
    virtual ~FDEventHandlerFactory() = default;

    /// @brief Return an FDEventhandler.
    static FDEventHandlerPtr factoryFDEventHandler();
};

}  // namespace isc::util
}  // namespace isc

#endif  // FD_EVENT_HANDLER_FACTORY_H
