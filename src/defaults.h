// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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
