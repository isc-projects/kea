// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_TLS_H
#define RADIUS_TLS_H

#include <radius_service.h>

namespace isc {
namespace radius {

/// @brief Radius service for TLS transport.
class RadiusTls : public RadiusService {
public:

    /// @brief Constructor.
    RadiusTls();

    /// @brief Destructor.
    virtual ~RadiusTls() = default;

    /// @brief Set idle timer.
    ///
    /// @note: The caller must hold the idle timer mutex.
    void setIdleTimer();

    /// @brief Idle timer callback.
    static void IdleTimerCallback();
};

} // end of namespace isc::radius
} // end of namespace isc

#endif
