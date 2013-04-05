// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <resolver/bench/fake_resolution.h>
#include <resolver/bench/dummy_work.h>

#include <algorithm>
#include <cstdlib>

namespace isc {
namespace resolver {
namespace bench {

// Parameters of the generated queries.
// How much work is each operation?
const size_t parse_size = 10000000;
const size_t render_size = 10000000;
const size_t send_size = 100000;
const size_t cache_read_size = 1000000;
const size_t cache_write_size = 1000000;
// How large a change is to terminate in this iteration (either by getting
// the complete answer, or by finding it in the cache). With 0.5, half the
// queries are found in the cache directly. Half of the rest needs just one
// upstream query. Etc.
const float chance_complete = 0.5;
// Number of milliseconds an upstream query can take. It picks a random number
// in between.
const size_t upstream_time_min = 2;
const size_t upstream_time_max = 30;

FakeQuery::FakeQuery(FakeInterface& interface) :
    interface_(&interface),
    outstanding_(false)
{
    // Schedule what tasks are needed.
    // First, parse the query
    steps_.push_back(Step(Compute, parse_size));
    // Look into the cache if it is there
    steps_.push_back(Step(CacheRead, cache_read_size));
    while (1.0 * random() / RAND_MAX > chance_complete) {
        // Needs another step of recursion. Render the upstream query.
        steps_.push_back(Step(Compute, render_size));
        // Send it and wait for the answer.
        steps_.push_back(Step(Upstream, upstream_time_min +
                              (random() *
                               (upstream_time_max - upstream_time_min) /
                               RAND_MAX)));
        // After it comes, parse the answer and store it in the cache.
        steps_.push_back(Step(Compute, parse_size));
        steps_.push_back(Step(CacheWrite, cache_write_size));
    }
    // Last, render the answer and send it.
    steps_.push_back(Step(Compute, render_size));
    steps_.push_back(Step(Send, send_size));
    // Reverse it, so we can pop_back the tasks as we work on them.
    std::reverse(steps_.begin(), steps_.end());
}

void
FakeQuery::performTask(const StepCallback& callback) {
    // nextTask also does all the sanity checking we need.
    if (nextTask() == Upstream) {
        outstanding_ = true;
        interface_->scheduleUpstreamAnswer(this, callback,
                                           steps_.back().second);
        steps_.pop_back();
    } else {
        for (size_t i = 0; i < steps_.back().second; ++i) {
            dummy_work();
        }
        steps_.pop_back();
        callback();
    }
}

}
}
}
