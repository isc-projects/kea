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

#include <auth/datasrc_clients_mgr.h>

#include <boost/function.hpp>

#include <list>

// Below we extend the isc::auth::internal namespace to specialize
// the doNoop() method.
namespace isc {
namespace auth {
namespace internal {
class TestMutex {
public:
    TestMutex() : lock_count(0), unlock_count(0), noop_count(0) {}
    class Locker {
    public:
        Locker(TestMutex& mutex) : mutex_(mutex) {
            ++mutex.lock_count;
        }
        ~Locker() {
            ++mutex_.unlock_count;
        }
    private:
        TestMutex& mutex_;
    };
    size_t lock_count;
    size_t unlock_count;
    size_t noop_count;          // allow doNoop() to modify this
};

class TestCondVar {
public:
    TestCondVar(std::list<Command>& command_queue,
                std::list<Command>& delayed_command_queue) :
        wait_count(0),
        command_queue_(command_queue),
        delayed_command_queue_(delayed_command_queue)
    {
    }
    void wait(TestMutex& mutex) {
        // bookkeeping
        ++mutex.unlock_count;
        ++wait_count;
        ++mutex.lock_count;

        // make the delayed commands available
        command_queue_.splice(command_queue_.end(), delayed_command_queue_);
    }
    size_t wait_count;
private:
    std::list<Command>& command_queue_;
    std::list<Command>& delayed_command_queue_;
};

class TestThread {
public:
    TestThread(const boost::function<void()>& /*main*/);
};

// Convenient shortcut
typedef DataSrcClientsBuilderBase<TestMutex, TestCondVar>
TestDataSrcClientsBuilder;

// We specialize this command handler for the convenience of tests.
// It abuses our specialized Mutex to count the number of calls of this method.
template<>
void
TestDataSrcClientsBuilder::doNoop();

} // namespace internal
}
}

#endif  // TEST_DATASRC_CLIENTS_MGR_H

// Local Variables:
// mode: c++
// End:
