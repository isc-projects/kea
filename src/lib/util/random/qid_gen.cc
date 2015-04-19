// Copyright (C) 2011, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#define KEA_UTIL_EXPORT

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
