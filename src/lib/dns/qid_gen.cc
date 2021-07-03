// Copyright (C) 2011-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// qid_gen defines a generator for query id's
//
// We probably want to merge this with the weighted random in the nsas
// (and other parts where we need randomness, perhaps another thing
// for a general libutil?)

#include <config.h>

#include <cryptolink/crypto_rng.h>
#include <dns/qid_gen.h>
#include <cstring>

namespace isc {
namespace dns {

QidGenerator qid_generator_instance;

QidGenerator&
QidGenerator::getInstance() {
    return (qid_generator_instance);
}

QidGenerator::QidGenerator()
{
}

uint16_t
QidGenerator::generateQid() {
    uint16_t val;
    std::vector<uint8_t> rnd = isc::cryptolink::random(sizeof(uint16_t));
    memmove(&val, &rnd[0], sizeof(uint16_t));
    return (val);
}

} // namespace dns
} // namespace isc
