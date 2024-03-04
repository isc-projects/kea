// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink.h>
#include <cryptolink/crypto_rng.h>

#include <boost/scoped_ptr.hpp>

#include <cstring>

namespace isc {
namespace cryptolink {

RNG::RNG() {
}

RNG::~RNG() {
}

std::vector<uint8_t>
random(size_t len) {
    RNGPtr rng(CryptoLink::getCryptoLink().getRNG());
    return (rng->random(len));
}

uint16_t generateQid() {
    uint16_t val;
    std::vector<uint8_t> rnd = random(sizeof(uint16_t));
    memmove(&val, &rnd[0], sizeof(uint16_t));
    return (val);
}

} // namespace cryptolink
} // namespace isc
