// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <asiolink/io_service_thread_pool.h>
#include <exceptions/exceptions.h>
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
using namespace isc::util;

IoServiceThreadPool::IoServiceThreadPool(IOServicePtr io_service, size_t pool_size,
                                         bool defer_start /* = false */)
    : pool_size_(pool_size), io_service_(io_service),
      run_state_(State::STOPPED), mutex_(), thread_cv_(),
      main_cv_(), paused_(0), running_(0), exited_(0)  {
    if (!pool_size) {
        isc_throw(BadValue, "pool_size must be non 0");
    }

    // If we weren't given an IOService, create our own.
    if (!io_service_) {
        io_service_.reset(new IOService());
    }

    // If we're not deferring the start, do it now.
    if (!defer_start) {
        run();
    }
}

IoServiceThreadPool::~IoServiceThreadPool() {
    stop();
}

void
IoServiceThreadPool::run() {
    setState(State::RUNNING);
}

void
IoServiceThreadPool::pause() {
    setState(State::PAUSED);
}

void
IoServiceThreadPool::stop() {
    setState(State::STOPPED);
}

IoServiceThreadPool::State
IoServiceThreadPool::getState() {
    std::lock_guard<std::mutex> lck(mutex_);
    return (run_state_);
}

bool
IoServiceThreadPool::validateStateChange(State state) const {
    switch (run_state_) {
    case State::STOPPED:
        return (state == State::RUNNING);
    case State::RUNNING:
        return (state != State::RUNNING);
    case State::PAUSED:
        return (state != State::PAUSED);
    }
    return (false);
}

std::string
IoServiceThreadPool::stateToText(State state) {
    switch (state) {
    case State::STOPPED:
        return (std::string("stopped"));
    case State::RUNNING:
        return (std::string("running"));
    case State::PAUSED:
        return (std::string("paused"));
    }
    return (std::string("unknown-state"));
}

void
IoServiceThreadPool::checkPausePermissions() {
    checkPermissions(State::PAUSED);
}

void
IoServiceThreadPool::checkPermissions(State state) {
    auto id = std::this_thread::get_id();
    if (checkThreadId(id)) {
        isc_throw(MultiThreadingInvalidOperation, "invalid thread pool state change to "
                  << IoServiceThreadPool::stateToText(state) << " performed by worker thread");
    }
}

bool
IoServiceThreadPool::checkThreadId(std::thread::id id) {
    for (auto thread : threads_) {
        if (id == thread->get_id()) {
            return (true);
        }
    }
    return (false);
}

void
IoServiceThreadPool::setState(State state) {
    checkPermissions(state);

    std::unique_lock<std::mutex> main_lck(mutex_);

    // Bail if the transition is invalid.
    if (!validateStateChange(state)) {
        return;
    }

    run_state_ = state;
    // Notify threads of state change.
    thread_cv_.notify_all();

    switch (state) {
    case State::RUNNING: {
        // Restart the IOService.
        io_service_->restart();

        // While we have fewer threads than we should, make more.
        while (threads_.size() < pool_size_) {
            boost::shared_ptr<std::thread> thread(new std::thread(
                std::bind(&IoServiceThreadPool::threadWork, this)));

            // Add thread to the pool.
            threads_.push_back(thread);
        }

        // Main thread waits here until all threads are running.
        main_cv_.wait(main_lck,
            [&]() {
                return (running_ == threads_.size());
            });

        exited_ = 0;
        break;
    }

    case State::PAUSED: {
        // Stop IOService.
        if (!io_service_->stopped()) {
            io_service_->poll();
            io_service_->stop();
        }

        // Main thread waits here until all threads are paused.
        main_cv_.wait(main_lck,
            [&]() {
                return (paused_ == threads_.size());
            });

        break;
    }

    case State::STOPPED: {
        // Stop IOService.
        if (!io_service_->stopped()) {
            io_service_->poll();
            io_service_->stop();
        }

        // Main thread waits here until all threads have exited.
        main_cv_.wait(main_lck,
            [&]() {
                return (exited_ == threads_.size());
            });

        for (auto const& thread : threads_) {
            thread->join();
        }

        threads_.clear();
        break;
    }}
}

void
IoServiceThreadPool::threadWork() {
    bool done = false;
    while (!done) {
        switch (getState()) {
        case State::RUNNING: {
            {
                std::unique_lock<std::mutex> lck(mutex_);
                running_++;

                // If We're all running notify main thread.
                if (running_ == pool_size_) {
                    main_cv_.notify_all();
                }
            }

            // Run the IOService.
            io_service_->run();

            {
                std::unique_lock<std::mutex> lck(mutex_);
                running_--;
            }

            break;
        }

        case State::PAUSED: {
            std::unique_lock<std::mutex> lck(mutex_);
            paused_++;

            // If we're all paused notify main.
            if (paused_ == threads_.size()) {
                main_cv_.notify_all();
            }

            // Wait here till I'm released.
            thread_cv_.wait(lck,
                [&]() {
                    return (run_state_ != State::PAUSED);
                });

            paused_--;
            break;
        }

        case State::STOPPED: {
            done = true;
            break;
        }}
    }

    std::unique_lock<std::mutex> lck(mutex_);
    exited_++;

    // If we've all exited, notify main.
    if (exited_ == threads_.size()) {
        main_cv_.notify_all();
    }
}

IOServicePtr
IoServiceThreadPool::getIOService() const {
    return (io_service_);
}

uint16_t
IoServiceThreadPool::getPoolSize() const {
    return (pool_size_);
}

uint16_t
IoServiceThreadPool::getThreadCount() const {
    return (threads_.size());
}
