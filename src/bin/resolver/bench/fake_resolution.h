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

#ifndef FAKE_RESOLUTION_H
#define FAKE_RESOLUTION_H

#include <exceptions/exceptions.h>
#include <asiolink/io_service.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <utility>
#include <vector>

namespace isc {
namespace resolver {
namespace bench {

/// \brief The kind of task a FakeQuery might want to perform.
///
/// The benchmark should examine which kind of task the query needs to perform
/// to progress forward. According to the task, some resources might need to be
/// locked, something re-scheduled, or such.
enum Task {
    /// \brief Some CPU-bound computation.
    ///
    /// The query needs to do some computation without any shared resources.
    /// This might be parsing or rendering of the query, verification of
    /// signatures, etc.
    Compute,
    /// \brief The query needs to read data from cache.
    CacheRead,
    /// \brief The query needs to modify the cache.
    CacheWrite,
    /// \brief A response is to be sent.
    ///
    /// This needs to access the interface/socket. If the socket is shared
    /// between threads, it might need to lock it.
    Send,
    /// \brief An answer from upstream server is needed.
    ///
    /// The query needs to send a query to some authoritative server and wait
    /// for the answer. Something might need to be locked (or not, depending
    /// on the architecture of the thing that sends and receives). Also, the
    /// task will not complete immediately, the callback of performTask
    /// will be called at later time.
    Upstream
};

class FakeInterface;

/// \brief Imitation of the work done to resolve a query.
///
/// An object of this class represents some fake work that should look like
/// the work needed to perform resolution of one query. No real work is done,
/// but several steps are scheduled, with characteristics hopefully
/// corresponding to steps of the real query.
///
/// The idea is that benchmark will repeatedly check if the query is done.
/// If not, it examines the next task by calling nextTask(). Depending on
/// the result, it'd lock or prepare any shared resources. After that, it'd
/// call performTask() to do the task. Once the query calls the callback
/// passed, it can proceed to the next step.
///
/// See naive_resolver.cc for example code how this could be done.
class FakeQuery {
private:
    // The queries come only through an interface. Don't let others create.
    friend class FakeInterface;
    /// \brief Constructor
    FakeQuery(FakeInterface& interface);
public:
    /// \brief Is work on the query completely done?
    ///
    /// If this returns true, do not call performTask or nextTask any more.
    /// The resolution is done.
    ///
    /// \throw isc::InvalidOperation if upstream query is still in progress.
    bool done() const {
        if (outstanding_) {
            isc_throw(isc::InvalidOperation, "Upstream query outstanding");
        }
        return (steps_.empty());
    }
    /// \brief Callback to signify a task has been performed.
    typedef boost::function<void()> StepCallback;
    /// \brief Perform next step in the resolution.
    ///
    /// Do whatever is needed to be done for the next step of resolution.
    /// Once the step is done, the callback is called.
    ///
    /// The callback is usually called from within this call. However, in
    /// the case when the nextTask() returned `Upstream`, the call to the
    /// callback is delayed for some period of time after the method
    /// returns.
    ///
    /// \throw isc::InvalidOperation if it is called when done() is true, or
    ///     if an upstream query is still in progress (performTask was called
    ///     before and the callback was not called by the query yet).
    void performTask(const StepCallback& callback);
    /// \brief Examine the kind of the next resolution process.
    ///
    /// Call this to know what kind of task will performTask do next.
    ///
    /// \throw isc::InvalidOperation if it is called when done() is true, or
    ///     if an upstream query is still in progress (performTask was called
    ///     before and the callback was not called by the query yet).
    Task nextTask() const {
        // Will check for outstanding_ internally too
        if (done()) {
            isc_throw(isc::InvalidOperation, "We are done, no more tasks");
        }
        return (steps_.back().first);
    }
    /// \brief Move network communication to different interface.
    ///
    /// By default, a query does all the "communication" on the interface
    /// it was born on. This may be used to move a query from one interface
    /// to another.
    ///
    /// You don't have to lock either of the interfaces to do so, this
    /// only switches the data in the query.
    ///
    /// \throw isc::InvalidOperation if it is called while an upstream query
    ///     is in progress.
    void migrateTo(FakeInterface& dst_interface) {
        if (outstanding_) {
            isc_throw(isc::InvalidOperation,
                      "Can't migrate in the middle of query");
        }
        interface_ = &dst_interface;
    }
    /// \brief The answer for upstream query was received
    ///
    /// This should be called from within the FakeInterface only.
    /// It marks that the query from upstream was answered.
    void answerReceived() {
        outstanding_ = false;
    }
private:
    // The scheduled steps for this task.
    typedef std::pair<Task, size_t> Step;
    // The scheduled steps. Reversed (first to be done at the end), so we can
    // pop_back() the completed steps.
    std::vector<Step> steps_;
    // The interface to schedule timeouts on.
    FakeInterface* interface_;
    // Is an upstream query outstanding?
    bool outstanding_;
};

typedef boost::shared_ptr<FakeQuery> FakeQueryPtr;

/// \brief An imitation of interface for receiving queries.
///
/// This is effectively a little bit smarter factory for queries. You can
/// request a new query from it, or let process events (incoming answers).
///
/// It contains its own event loop. If the benchmark has more threads, have
/// one in each of the threads (if the threads ever handles network
/// communication -- if it accepts queries, sends answers or does upstream
/// queries).
///
/// If the model simulated would share the same interface between multiple
/// threads, it is better to have one in each thread as well, but lock
/// access to receiveQuery() so only one is used at once (no idea what happens
/// if ASIO loop is accessed from multiple threads).
///
/// Note that the creation of the queries is not thread safe (due to
/// the random() function inside). The interface generates all its queries
/// in advance, on creation time. But you need to create all the needed
/// interfaces from single thread and then distribute them to your threads.
class FakeInterface {
public:
    /// \brief Constructor
    ///
    /// Initiarile the interface and create query_count queries for the
    /// benchmark. They will be handed out one by one with receiveQuery().
    FakeInterface(size_t query_count);
    /// \brief Wait for answers from upstream servers.
    ///
    /// Wait until at least one "answer" comes from the remote server. This
    /// will effectively block the calling thread until it is time to call
    /// a callback of performTask.
    ///
    /// It is not legal to call it without any outstanding upstream queries
    /// on this interface. However, the situation is not explicitly checked.
    ///
    /// \note Due to internal implementation, it is not impossible no or more
    ///    than one callbacks to be called from within this method.
    void processEvents();
    /// \brief Accept another query.
    ///
    /// Generate a new fake query to resolve.
    ///
    /// This method might call callbacks of other queries waiting for upstream
    /// answer.
    ///
    /// This returns a NULL pointer when there are no more queries to answer
    /// (the number designated for the benchmark was reached).
    FakeQueryPtr receiveQuery();
private:
    class UpstreamQuery;
    friend class FakeQuery;
    void scheduleUpstreamAnswer(FakeQuery* query,
                                const FakeQuery::StepCallback& callback,
                                size_t msec);
    asiolink::IOService service_;
    std::vector<FakeQueryPtr> queries_;
};

}
}
}

#endif
