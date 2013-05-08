// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <resolver/bench/naive_resolver.h>

#include <cassert>
#include <boost/bind.hpp>

namespace isc {
namespace resolver {
namespace bench {

NaiveResolver::NaiveResolver(size_t query_count) :
    interface_(query_count),
    processed_(false)
{}

namespace {

void
stepDone(bool* flag) {
    *flag = true;
}

}

size_t
NaiveResolver::run() {
    assert(!processed_);
    size_t count = 0;
    FakeQueryPtr query;
    // Process a query at a time. As the previous is already handled, the
    // receiveQuery may never trigger other events.
    while ((query = interface_.receiveQuery())) {
        // Handle each step
        while (!query->done()) {
            bool done = false; // This step is not yet done.
            // If there were more queries/threads/whatever, we would examine
            // the query->nextTask() and lock or prepare resources accordingly.
            // But as there's just one, we simply do the task, without caring.
            query->performTask(boost::bind(&stepDone, &done));
            // We may need to wait for the upstream query.
            while (!done) {
                interface_.processEvents();
            }
        }
        count ++;
    }
    processed_ = true;
    return (count);
}

}
}
}
