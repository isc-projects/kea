// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file   defaults.h
/// 
/// @brief Contains the default values for various parameters.
///
/// While the content of this file is currently small, it is envisaged that it
/// will grow over time.

#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief Number of seconds after declined lease recovers
///
/// This define specifies the default value for decline probation period.
/// Once a lease is declined, it will spend this amount of seconds as
/// being unavailable. This is only the default value. Specific value may
/// be defined in the configuration file. The default is 1 day.
static const uint32_t DEFAULT_DECLINE_PROBATION_PERIOD = 24*3600;

};
};

#endif
