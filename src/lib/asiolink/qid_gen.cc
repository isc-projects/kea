// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

// qid_gen defines a generator for query id's
//
// We probably want to merge this with the weighted random in the nsas
// (and other parts where we need randomness, perhaps another thing
// for a general libutil?)

#include <asiolink/qid_gen.h>

#include <sys/time.h>

namespace {
    asiolink::QidGenerator* qid_generator_instance = NULL;
}

namespace asiolink {
QidGenerator*
QidGenerator::getInstance() {
    if (!qid_generator_instance) {
        qid_generator_instance = new QidGenerator();
        qid_generator_instance->seed();
    }

    return qid_generator_instance;
}

void
QidGenerator::cleanInstance() {
    delete qid_generator_instance;
    qid_generator_instance = NULL;
}

QidGenerator::QidGenerator() : dist(0, 65535), vgen(generator, dist) {}

void
QidGenerator::seed() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    long int seed;
    seed = (tv.tv_sec * 1000000) + tv.tv_usec;
    generator.seed(seed);
}

isc::dns::qid_t
QidGenerator::generateQid() {
    return vgen();
}

} // namespace asiolink
