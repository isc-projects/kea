// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ND_H
#define ND_H

#include <stdint.h>

namespace isc {
namespace slaac {

/// @brief Neighbor Discovery message types.
enum NDMessageType {
    ND_RT_SOL    = 133, //< Router Solicitation
    ND_RT_ADV    = 134, //< Router Advertisement
    ND_NB_SOL    = 135, //< Neighbor Solicitation
    ND_NB_ADV    = 136, //< Neighbor Advertisement
    ND_REDIRECT  = 137  //< Redirect
};

/// @brief Neighbor Discover option types.
enum NDOptionType {
    ND_SRC_LL_ADDR    = 1,  //< Source Link-Layer Address
    ND_TGT_LL_ADDR    = 2,  //< Target Link-Layer Address
    ND_PREFIX_INFO    = 3,  //< Prefix Information
    ND_REDIRECT_HDR   = 4,  //< Redirected Header
    ND_MTU            = 5,  //< MTU
    // Many new options...
    // reference IANA "IPv6 Neighbor Discovery Option Formats" registry.
    ND_UNIVERSAL_RA   = 42  //< Universal RA Option
};

}; // namespace isc::slaac
}; // namespace isc

#endif
