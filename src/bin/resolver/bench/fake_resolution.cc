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

#include <resolver/bench/fake_resolution.h>
#include <resolver/bench/dummy_work.h>

#include <asiolink/interval_timer.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <stdlib.h> // not cstdlib, which doesn't officially have random()

namespace isc {
namespace resolver {
namespace bench {

// Parameters of the generated queries.
// How much work is each operation?
const size_t parse_size = 100000;
const size_t render_size = 100000;
const size_t send_size = 1000;
const size_t cache_read_size = 10000;
const size_t cache_write_size = 10000;
// How large a change is to terminate in this iteration (either by getting
// the complete answer, or by finding it in the cache). With 0.5, half the
// queries are found in the cache directly. Half of the rest needs just one
// upstream query. Etc.
const float chance_complete = 0.5;
// Number of milliseconds an upstream query can take. It picks a random number
// in between.
const size_t upstream_time_min = 2;
const size_t upstream_time_max = 50;

FakeQuery::FakeQuery(FakeInterface& interface) :
    interface_(&interface),
    outstanding_(false)
{
    // Schedule what tasks are needed.
    // First, parse the query
    steps_.push_back(Step(Compute, parse_size));
    // Look into the cache if it is there
    steps_.push_back(Step(CacheRead, cache_read_size));
    while ((1.0 * random()) / RAND_MAX > chance_complete) {
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

FakeInterface::FakeInterface(size_t query_count) :
    queries_(query_count)
{
    BOOST_FOREACH(FakeQueryPtr& query, queries_) {
        query = FakeQueryPtr(new FakeQuery(*this));
    }
}

void
FakeInterface::processEvents() {
    service_.run_one();
}

namespace {

void
processDone(bool* flag) {
    *flag = true;
}

}

FakeQueryPtr
FakeInterface::receiveQuery() {
    // Handle all the events that are already scheduled.
    // As processEvents blocks until an event happens and we want to terminate
    // if there are no events, we do a small trick. We post an event to the end
    // of the queue and work until it is found. This should process all the
    // events that were there already.
    bool processed = false;
    service_.post(boost::bind(&processDone, &processed));
    while (!processed) {
        processEvents();
    }

    // Now, look if there are more queries to return.
    if (queries_.empty()) {
        return (FakeQueryPtr());
    } else {
        // Take from the back. The order doesn't matter and it's faster from
        // there.
        FakeQueryPtr result(queries_.back());
        queries_.pop_back();
        return (result);
    }
}

class FakeInterface::UpstreamQuery {
public:
    UpstreamQuery(FakeQuery* query, const FakeQuery::StepCallback& callback,
                  const boost::shared_ptr<asiolink::IntervalTimer> timer) :
        query_(query),
        callback_(callback),
        timer_(timer)
    {}
    void trigger() {
        query_->answerReceived();
        callback_();
        // We are not needed any more.
        delete this;
    }
private:
    FakeQuery* const query_;
    const FakeQuery::StepCallback callback_;
    // Just to hold it alive before the callback is called.
    const boost::shared_ptr<asiolink::IntervalTimer> timer_;
};

void
FakeInterface::scheduleUpstreamAnswer(FakeQuery* query,
                                      const FakeQuery::StepCallback& callback,
                                      size_t msec)
{
    const boost::shared_ptr<asiolink::IntervalTimer>
        timer(new asiolink::IntervalTimer(service_));
    UpstreamQuery* q(new UpstreamQuery(query, callback, timer));
    timer->setup(boost::bind(&UpstreamQuery::trigger, q), msec);
}

}
}
}
