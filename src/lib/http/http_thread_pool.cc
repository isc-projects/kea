// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>
#include <exceptions/exceptions.h>
#include <http/http_log.h>
#include <http/http_messages.h>
#include <http/http_thread_pool.h>
#include <util/multi_threading_mgr.h>
#include <util/unlock_guard.h>

#include <boost/shared_ptr.hpp>

#include <atomic>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::http;
using namespace isc::util;

HttpThreadPool::HttpThreadPool(IOServicePtr io_service, size_t pool_size,
                               bool defer_start /* = false */)
    : pool_size_(pool_size), io_service_(io_service),
      run_state_(RunState::STOPPED), mutex_(), cv_()  {
    if (!pool_size) {
        isc_throw(BadValue, "HttpThreadPool::ctor pool_size must be > 0");
    }

    // If we weren't given an IOService, create our own.
    if (!io_service_) {
        io_service_.reset(new IOService());
    }

    // If we're not deferring the start, do it now.
    if (!defer_start) {
        start();
    }
}

HttpThreadPool::~HttpThreadPool() {
    if (getRunState() != RunState::STOPPED) {
        // Stop if we aren't already stopped
        stop();
    }
}

void
HttpThreadPool::start() {
    if (getRunState() != RunState::STOPPED) {
        isc_throw(InvalidOperation, "HttpThreadPool::start already started!");
    }

    // Set state to RUN.
    setRunState(RunState::RUN);

    // Prep IOservice for run() invocations.
    io_service_->restart();

    // Create a pool of threads, each calls run() on our
    // io_service instance.
    for (std::size_t i = 0; i < pool_size_; ++i) {
        boost::shared_ptr<std::thread> thread(new std::thread(
            [this]() {
                bool done = false;
                while (!done) {
                    switch (getRunState()) {
                    case RunState::RUN:
                        io_service_->run();
                        break;
                    case RunState::PAUSED:
                    {
                        // We need to stop and wait to be released. We don't care how 
                        // we exit, we'll do whatever the current state dictates.
                        std::unique_lock<std::mutex> lck(mutex_);
                        static_cast<void>(cv_.wait_for(lck, std::chrono::milliseconds(25),
                            [&]() {
                                return (run_state_ != RunState::PAUSED);
                            }));

                        break;
                    }
                    case RunState::SHUTDOWN:
                        done = true;
                        break;
                    case RunState::STOPPED:
                        // This should never happen.
                        done = true;
                        break;
                    }
                }
            }));

        threads_.push_back(thread);
    }
}

void
HttpThreadPool::stop() {
    if (getRunState() == RunState::STOPPED) {
        // Nothing to do.
        return;
    }

    // Set the state to SHUTDOWN.
    setRunState(RunState::SHUTDOWN);

    // Stop our IOService.
    if (!io_service_->stopped()) {
        io_service_->stop();
    }

    // Shutdown the threads.
    for (auto const& thread : threads_) {
        thread->join();
    }

    // Empty the thread pool.
    threads_.clear();

    // Set the state to STOPPED.
    setRunState(RunState::STOPPED);
}

void
HttpThreadPool::pause() {
    if (getRunState() !=  RunState::RUN) {
        // Not running, can't pause.
        return;
    }

    /// @todo TKM - Take this out
    std::cout << "HttpThreadPool pausing" << std::endl;
    setRunState(RunState::PAUSED);
    io_service_->stop();
}

void
HttpThreadPool::resume() {
    if (getRunState() !=  RunState::PAUSED) {
        // Not PAUSED, can't resume.
        return;
    }

    /// @todo TKM - Take this out
    std::cout << "HttpThreadPool resuming" << std::endl;
    io_service_->restart();
    setRunState(RunState::RUN);
}

HttpThreadPool::RunState
HttpThreadPool::getRunState() {
    std::lock_guard<std::mutex> lck(mutex_);
    return (run_state_);
}

void
HttpThreadPool::setRunState(RunState state) {
    {
        std::lock_guard<std::mutex> lck(mutex_);
        run_state_ = state;
    }
    cv_.notify_all();
}

IOServicePtr
HttpThreadPool::getIOService() const {
    return (io_service_);
}

uint16_t
HttpThreadPool::getPoolSize() const {
    return (pool_size_);
}

uint16_t
HttpThreadPool::getThreadCount() const {
    return (threads_.size());
}
