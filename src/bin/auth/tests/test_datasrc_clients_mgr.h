// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef TEST_DATASRC_CLIENTS_MGR_H
#define TEST_DATASRC_CLIENTS_MGR_H 1

#include <exceptions/exceptions.h>

#include <auth/datasrc_clients_mgr.h>
#include <datasrc/datasrc_config.h>

#include <boost/function.hpp>

#include <list>

// In this file we provide specialization of thread, mutex, condition variable,
// and DataSrcClientsBuilder for convenience of tests.  They don't use
// actual threads or mutex, and allow tests to inspect some internal states
// of the corresponding objects.
//
// In many cases, tests can use TestDataSrcClientsMgr (defined below) where
// DataSrcClientsMgr is needed.

// Below we extend the isc::auth::datasrc_clientmgr_internal namespace to
// specialize the doNoop() method.
namespace isc {
namespace auth {
namespace datasrc_clientmgr_internal {
class TestMutex {
public:
    // for throw_from_noop.
    // None: no throw from specialized doNoop()
    // EXCLASS: throw some exception class object
    // INTEGER: throw an integer
    enum ExceptionFromNoop { NONE, EXCLASS, INTEGER };

    TestMutex() : lock_count(0), unlock_count(0), noop_count(0),
                  throw_from_noop(NONE)
    {}
    class Locker {
    public:
        Locker(TestMutex& mutex) : mutex_(mutex) {
            if (mutex.lock_count != mutex.unlock_count) {
                isc_throw(Unexpected,
                          "attempt of duplicate lock acquisition");
            }

            ++mutex.lock_count;
            if (mutex.lock_count > 100) { // 100 is an arbitrary choice
                isc_throw(Unexpected,
                          "too many test mutex count, likely a bug in test");
            }
        }
        ~Locker() {
            ++mutex_.unlock_count;
        }
    private:
        TestMutex& mutex_;
    };
    size_t lock_count; // number of lock acquisitions; tests can check this
    size_t unlock_count; // number of lock releases; tests can check this
    size_t noop_count;          // allow doNoop() to modify this
    ExceptionFromNoop throw_from_noop; // tests can set this to control doNoop
};

class TestCondVar {
public:
    TestCondVar() : wait_count(0), signal_count(0), command_queue_(NULL),
                    delayed_command_queue_(NULL)
    {}
    TestCondVar(std::list<Command>& command_queue,
                std::list<Command>& delayed_command_queue) :
        wait_count(0),
        signal_count(0),
        command_queue_(&command_queue),
        delayed_command_queue_(&delayed_command_queue)
    {
    }
    void wait(TestMutex& mutex) {
        // bookkeeping
        ++mutex.unlock_count;
        ++wait_count;
        ++mutex.lock_count;

        if (wait_count > 100) { // 100 is an arbitrary choice
            isc_throw(Unexpected,
                      "too many cond wait count, likely a bug in test");
        }

        // make the delayed commands available
        command_queue_->splice(command_queue_->end(), *delayed_command_queue_);
    }
    void signal() {
        ++signal_count;
    }
    size_t wait_count; // number of calls to wait(); tests can check this
    size_t signal_count; // number of calls to signal(); tests can check this
private:
    std::list<Command>* command_queue_;
    std::list<Command>* delayed_command_queue_;
};

// Convenient shortcut
typedef DataSrcClientsBuilderBase<TestMutex, TestCondVar>
TestDataSrcClientsBuilder;

// We specialize this command handler for the convenience of tests.
// It abuses our specialized Mutex to count the number of calls of this method.
template<>
void
TestDataSrcClientsBuilder::doNoop();

// A specialization of DataSrcClientsBuilder that allows tests to inspect
// its internal states via static class variables.  Using static is suboptimal,
// but DataSrcClientsMgr is highly encapsulated, this seems to be the best
// possible compromise.
class FakeDataSrcClientsBuilder {
public:
    // true iff a builder has started.
    static bool started;

    // These three correspond to the resource shared with the manager.
    // xxx_copy will be set in the manager's destructor to record the
    // final state of the manager.
    static std::list<Command>* command_queue;
    static TestCondVar* cond;
    static TestMutex* queue_mutex;
    static isc::datasrc::ClientListMapPtr* clients_map;
    static TestMutex* map_mutex;
    static std::list<Command> command_queue_copy;
    static TestCondVar cond_copy;
    static TestMutex queue_mutex_copy;

    // true iff the manager waited on the thread running the builder.
    static bool thread_waited;

    // If set to true by a test, TestThread::wait() throws an exception
    // exception.
    enum ExceptionFromWait { NOTHROW, THROW_UNCAUGHT_EX, THROW_OTHER };
    static ExceptionFromWait thread_throw_on_wait;

    FakeDataSrcClientsBuilder(
        std::list<Command>* command_queue,
        TestCondVar* cond,
        TestMutex* queue_mutex,
        isc::datasrc::ClientListMapPtr* clients_map,
        TestMutex* map_mutex)
    {
        FakeDataSrcClientsBuilder::started = false;
        FakeDataSrcClientsBuilder::command_queue = command_queue;
        FakeDataSrcClientsBuilder::cond = cond;
        FakeDataSrcClientsBuilder::queue_mutex = queue_mutex;
        FakeDataSrcClientsBuilder::clients_map = clients_map;
        FakeDataSrcClientsBuilder::map_mutex = map_mutex;
        FakeDataSrcClientsBuilder::thread_waited = false;
        FakeDataSrcClientsBuilder::thread_throw_on_wait = NOTHROW;
    }
    void run() {
        FakeDataSrcClientsBuilder::started = true;
    }
};

// A fake thread class that doesn't really invoke thread but simply calls
// the given main function (synchronously).  Tests can tweak the wait()
// behavior via some static variables so it will throw some exceptions.
class TestThread {
public:
    TestThread(const boost::function<void()>& main) {
        main();
    }
    void wait() {
        FakeDataSrcClientsBuilder::thread_waited = true;
        switch (FakeDataSrcClientsBuilder::thread_throw_on_wait) {
        case FakeDataSrcClientsBuilder::NOTHROW:
            break;
        case FakeDataSrcClientsBuilder::THROW_UNCAUGHT_EX:
            isc_throw(util::thread::Thread::UncaughtException,
                      "TestThread wait() saw an exception");
        case FakeDataSrcClientsBuilder::THROW_OTHER:
            isc_throw(Unexpected,
                      "General emulated failure in TestThread wait()");
        }
    }
};
} // namespace datasrc_clientmgr_internal

// Convenient shortcut
typedef DataSrcClientsMgrBase<
    datasrc_clientmgr_internal::TestThread,
    datasrc_clientmgr_internal::FakeDataSrcClientsBuilder,
    datasrc_clientmgr_internal::TestMutex,
    datasrc_clientmgr_internal::TestCondVar> TestDataSrcClientsMgr;

// A specialization of manager's "cleanup" called at the end of the
// destructor.  We use this to record the final values of some of the class
// member variables.
template<>
void
TestDataSrcClientsMgr::cleanup();

template<>
void
TestDataSrcClientsMgr::reconfigureHook();
} // namespace auth
} // namespace isc

#endif  // TEST_DATASRC_CLIENTS_MGR_H

// Local Variables:
// mode: c++
// End:
