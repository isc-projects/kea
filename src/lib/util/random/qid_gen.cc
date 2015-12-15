// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// qid_gen defines a generator for query id's
//
// We probably want to merge this with the weighted random in the nsas
// (and other parts where we need randomness, perhaps another thing
// for a general libutil?)

#include <util/random/qid_gen.h>

#include <sys/time.h>

namespace isc {
namespace util {
namespace random {

QidGenerator qid_generator_instance;

QidGenerator&
QidGenerator::getInstance() {
    return (qid_generator_instance);
}

QidGenerator::QidGenerator() : dist_(0, 65535),
                               vgen_(generator_, dist_)
{
    seed();
}

void
QidGenerator::seed() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    generator_.seed((tv.tv_sec * 1000000) + tv.tv_usec);
}

uint16_t
QidGenerator::generateQid() {
    return (vgen_());
}


} // namespace random
} // namespace util
} // namespace isc
