// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <exceptions/exceptions.h>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <list>
#include <mutex>
#include <queue>
#include <thread>

#include <signal.h>

namespace isc {
namespace util {

/// @brief Defines a thread pool which uses a thread pool queue for managing
/// work items. Each work item is a 'functor' object.
///
/// @tparam WorkItem a functor
/// @tparam Container a 'queue like' container
template <typename WorkItem, typename Container = std::deque<boost::shared_ptr<WorkItem>>>
struct ThreadPool {
    /// @brief Rounding value for 10 packet statistic.
    static const double CEXP10;

    /// @brief Rounding value for 100 packet statistic.
    static const double CEXP100;

    /// @brief Rounding value for 1000 packet statistic.
    static const double CEXP1000;

    /// @brief Type of shared pointers to work items.
    typedef typename boost::shared_ptr<WorkItem> WorkItemPtr;

    /// @brief Constructor
    ThreadPool() {
    }

    /// @brief Destructor
    ~ThreadPool() {
        reset();
    }

    /// @brief reset the thread pool stopping threads and clearing the internal
    /// queue
    ///
    /// It can be called several times even when the thread pool is stopped
    void reset() {
        stopInternal();
        queue_.clear();
    }

    /// @brief start all the threads
    ///
    /// @param thread_count specifies the number of threads to be created and
    /// started
    ///
    /// @throw InvalidOperation if thread pool already started
    /// @throw InvalidParameter if thread count is 0
    void start(uint32_t thread_count) {
        if (!thread_count) {
            isc_throw(InvalidParameter, "thread count is 0");
        }
        if (queue_.enabled()) {
            isc_throw(InvalidOperation, "thread pool already started");
        }
        startInternal(thread_count);
    }

    /// @brief stop all the threads
    ///
    /// @throw InvalidOperation if thread pool already stopped
    void stop() {
        if (!queue_.enabled()) {
            isc_throw(InvalidOperation, "thread pool already stopped");
        }
        stopInternal();
    }

    /// @brief add a work item to the thread pool
    ///
    /// @param item the 'functor' object to be added to the queue
    /// @return false if the queue was full and oldest item(s) was dropped,
    /// true otherwise.
    bool add(const WorkItemPtr& item) {
        return (queue_.pushBack(item));
    }

    /// @brief add a work item to the thread pool at front
    ///
    /// @param item the 'functor' object to be added to the queue
    /// @return false if the queue was full, true otherwise.
    bool addFront(const WorkItemPtr& item) {
        return (queue_.pushFront(item));
    }

    /// @brief count number of work items in the queue
    ///
    /// @return the number of work items in the queue
    size_t count() {
        return (queue_.count());
    }

    /// @brief wait for current items to be processed
    ///
    /// Used to block the calling thread until all items in the queue have
    /// been processed
    void wait() {
        auto id = std::this_thread::get_id();
        if (checkThreadId(id)) {
            isc_throw(MultiThreadingInvalidOperation, "thread pool wait called by worker thread");
        }
        queue_.wait();
    }

    /// @brief wait for items to be processed or return after timeout
    ///
    /// Used to block the calling thread until all items in the queue have
    /// been processed or return after timeout
    ///
    /// @param seconds the time in seconds to wait for tasks to finish
    /// @return true if all tasks finished, false on timeout
    bool wait(uint32_t seconds) {
        auto id = std::this_thread::get_id();
        if (checkThreadId(id)) {
            isc_throw(MultiThreadingInvalidOperation, "thread pool wait with timeout called by worker thread");
        }
        return (queue_.wait(seconds));
    }

    /// @brief set maximum number of work items in the queue
    ///
    /// @param max_queue_size the maximum size (0 means unlimited)
    void setMaxQueueSize(size_t max_queue_size) {
        queue_.setMaxQueueSize(max_queue_size);
    }

    /// @brief get maximum number of work items in the queue
    ///
    /// @return the maximum size (0 means unlimited)
    size_t getMaxQueueSize() {
        return (queue_.getMaxQueueSize());
    }

    /// @brief size number of thread pool threads
    ///
    /// @return the number of threads
    size_t size() {
        return (threads_.size());
    }

    /// @brief get queue length statistic
    ///
    /// @param which select the statistic (10, 100 or 1000)
    /// @return the queue length statistic
    /// @throw InvalidParameter if which is not 10 and 100 and 1000.
    double getQueueStat(size_t which) {
        return (queue_.getQueueStat(which));
    }

private:
    /// @brief start all the threads
    ///
    /// @param thread_count specifies the number of threads to be created and
    /// started
    void startInternal(uint32_t thread_count) {
        // Protect us against signals
        sigset_t sset;
        sigset_t osset;
        sigemptyset(&sset);
        sigaddset(&sset, SIGCHLD);
        sigaddset(&sset, SIGINT);
        sigaddset(&sset, SIGHUP);
        sigaddset(&sset, SIGTERM);
        pthread_sigmask(SIG_BLOCK, &sset, &osset);
        queue_.enable(thread_count);
        try {
            for (uint32_t i = 0; i < thread_count; ++i) {
                threads_.push_back(boost::make_shared<std::thread>(&ThreadPool::run, this));
            }
        } catch (...) {
            // Restore signal mask.
            pthread_sigmask(SIG_SETMASK, &osset, 0);
            throw;
        }
        // Restore signal mask.
        pthread_sigmask(SIG_SETMASK, &osset, 0);
    }

    /// @brief stop all the threads
    void stopInternal() {
        auto id = std::this_thread::get_id();
        if (checkThreadId(id)) {
            isc_throw(MultiThreadingInvalidOperation, "thread pool stop called by worker thread");
        }
        queue_.disable();
        for (auto thread : threads_) {
            thread->join();
        }
        threads_.clear();
    }

    /// @brief check specified thread id against own threads
    ///
    /// @return true if thread is owned, false otherwise
    bool checkThreadId(std::thread::id id) {
        for (auto thread : threads_) {
            if (id == thread->get_id()) {
                return (true);
            }
        }
        return (false);
    }

    /// @brief Defines a generic thread pool queue.
    ///
    /// The main purpose is to safely manage thread pool tasks.
    /// The thread pool queue can be 'disabled', which means that no items can be
    /// removed from the queue, or 'enabled', which guarantees that inserting or
    /// removing items are thread safe.
    /// In 'disabled' state, all threads waiting on the queue are unlocked and all
    /// operations are non blocking.
    ///
    /// @tparam Item a 'smart pointer' to a functor
    /// @tparam QueueContainer a 'queue like' container
    template <typename Item, typename QueueContainer = std::queue<Item>>
    struct ThreadPoolQueue {
        /// @brief Constructor
        ///
        /// Creates the thread pool queue in 'disabled' state
        ThreadPoolQueue()
            : enabled_(false), max_queue_size_(0), working_(0),
              stat10(0.), stat100(0.), stat1000(0.) {
        }

        /// @brief Destructor
        ///
        /// Destroys the thread pool queue
        ~ThreadPoolQueue() {
            disable();
            clear();
        }

        /// @brief set maximum number of work items in the queue
        ///
        /// @return the maximum size (0 means unlimited)
        void setMaxQueueSize(size_t max_queue_size) {
            std::lock_guard<std::mutex> lock(mutex_);
            max_queue_size_ = max_queue_size;
        }

        /// @brief get maximum number of work items in the queue
        ///
        /// @return the maximum size (0 means unlimited)
        size_t getMaxQueueSize() {
            std::lock_guard<std::mutex> lock(mutex_);
            return (max_queue_size_);
        }

        /// @brief push work item to the queue
        ///
        /// Used to add work items to the queue.
        /// When the queue is full oldest items are removed and false is
        /// returned.
        /// This function adds an item to the queue and wakes up at least one
        /// thread waiting on the queue.
        ///
        /// @param item the new item to be added to the queue
        /// @return false if the queue was full and oldest item(s) dropped,
        /// true otherwise
        bool pushBack(const Item& item) {
            bool ret = true;
            if (!item) {
                return (ret);
            }
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (max_queue_size_ != 0) {
                    while (queue_.size() >= max_queue_size_) {
                        queue_.pop_front();
                        ret = false;
                    }
                }
                queue_.push_back(item);
            }
            // Notify pop function so that it can effectively remove a work item.
            cv_.notify_one();
            return (ret);
        }

        /// @brief push work item to the queue at front.
        ///
        /// Used to add work items to the queue at front.
        /// When the queue is full the item is not added.
        ///
        /// @param item the new item to be added to the queue
        /// @return false if the queue was full, true otherwise
        bool pushFront(const Item& item) {
            if (!item) {
                return (true);
            }
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if ((max_queue_size_ != 0) &&
                    (queue_.size() >= max_queue_size_)) {
                    return (false);
                }
                queue_.push_front(item);
            }
            // Notify pop function so that it can effectively remove a work item.
            cv_.notify_one();
            return (true);
        }

        /// @brief pop work item from the queue or block waiting
        ///
        /// Used to retrieve and remove a work item from the queue
        /// If the queue is 'disabled', this function returns immediately an empty
        /// element.
        /// If the queue is 'enabled', this function returns the first element in
        /// the queue or blocks the calling thread if there are no work items
        /// available.
        /// Before a work item is returned statistics are updated.
        ///
        /// @return the first work item from the queue or an empty element.
        Item pop() {
            std::unique_lock<std::mutex> lock(mutex_);
            --working_;
            // Wait for push or disable functions.
            if (working_ == 0 && queue_.empty()) {
                wait_cv_.notify_all();
            }
            cv_.wait(lock, [&]() {return (!enabled_ || !queue_.empty());});
            if (!enabled_) {
                return (Item());
            }
            ++working_;
            size_t length = queue_.size();
            stat10 = stat10 * CEXP10 + (1 - CEXP10) * length;
            stat100 = stat100 * CEXP100 + (1 - CEXP100) * length;
            stat1000 = stat1000 * CEXP1000 + (1 - CEXP1000) * length;
            Item item = queue_.front();
            queue_.pop_front();
            return (item);
        }

        /// @brief count number of work items in the queue
        ///
        /// Returns the number of work items in the queue
        ///
        /// @return the number of work items
        size_t count() {
            std::lock_guard<std::mutex> lock(mutex_);
            return (queue_.size());
        }

        /// @brief wait for current items to be processed
        ///
        /// Used to block the calling thread until all items in the queue have
        /// been processed
        void wait() {
            std::unique_lock<std::mutex> lock(mutex_);
            // Wait for any item or for working threads to finish.
            wait_cv_.wait(lock, [&]() {return (working_ == 0 && queue_.empty());});
        }

        /// @brief wait for items to be processed or return after timeout
        ///
        /// Used to block the calling thread until all items in the queue have
        /// been processed or return after timeout
        ///
        /// @param seconds the time in seconds to wait for tasks to finish
        /// @return true if all tasks finished, false on timeout
        bool wait(uint32_t seconds) {
            std::unique_lock<std::mutex> lock(mutex_);
            // Wait for any item or for working threads to finish.
            bool ret = wait_cv_.wait_for(lock, std::chrono::seconds(seconds),
                                         [&]() {return (working_ == 0 && queue_.empty());});
            return (ret);
        }

        /// @brief get queue length statistic
        ///
        /// @param which select the statistic (10, 100 or 1000)
        /// @return the queue length statistic
        /// @throw InvalidParameter if which is not 10 and 100 and 1000.
        double getQueueStat(size_t which) {
            std::lock_guard<std::mutex> lock(mutex_);
            switch (which) {
            case 10:
                return (stat10);
            case 100:
                return (stat100);
            case 1000:
                return (stat1000);
            default:
                isc_throw(InvalidParameter, "supported statistic for "
                          << "10/100/1000 only, not " << which);
            }
        }

        /// @brief clear remove all work items
        ///
        /// Removes all queued work items
        void clear() {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_ = QueueContainer();
            working_ = 0;
            wait_cv_.notify_all();
        }

        /// @brief enable the queue
        ///
        /// Sets the queue state to 'enabled'
        ///
        /// @param number of working threads
        void enable(uint32_t thread_count) {
            std::lock_guard<std::mutex> lock(mutex_);
            enabled_ = true;
            working_ = thread_count;
        }

        /// @brief disable the queue
        ///
        /// Sets the queue state to 'disabled'
        void disable() {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                enabled_ = false;
            }
            // Notify pop so that it can exit.
            cv_.notify_all();
        }

        /// @brief return the state of the queue
        ///
        /// Returns the state of the queue
        ///
        /// @return the state
        bool enabled() {
            return (enabled_);
        }

    private:
        /// @brief underlying queue container
        QueueContainer queue_;

        /// @brief mutex used for critical sections
        std::mutex mutex_;

        /// @brief condition variable used to signal waiting threads
        std::condition_variable cv_;

        /// @brief condition variable used to wait for all items to be processed
        std::condition_variable wait_cv_;

        /// @brief the sate of the queue
        /// The 'enabled' state corresponds to true value
        /// The 'disabled' state corresponds to false value
        std::atomic<bool> enabled_;

        /// @brief maximum number of work items in the queue
        /// (0 means unlimited)
        size_t max_queue_size_;

        /// @brief number of threads currently doing work
        uint32_t working_;

        /// @brief queue length statistic for 10 packets
        double stat10;

        /// @brief queue length statistic for 100 packets
        double stat100;

        /// @brief queue length statistic for 1000 packets
        double stat1000;
    };

    /// @brief run function of each thread
    void run() {
        while (queue_.enabled()) {
            WorkItemPtr item = queue_.pop();
            if (item) {
                try {
                    (*item)();
                } catch (...) {
                    // catch all exceptions
                }
            }
        }
    }

    /// @brief list of worker threads
    std::vector<boost::shared_ptr<std::thread>> threads_;

    /// @brief underlying work items queue
    ThreadPoolQueue<WorkItemPtr, Container> queue_;
};

/// Initialize the 10 packet rounding to exp(-.1)
template <typename W, typename C>
const double ThreadPool<W, C>::CEXP10 = std::exp(-.1);

/// Initialize the 100 packet rounding to exp(-.01)
template <typename W, typename C>
const double ThreadPool<W, C>::CEXP100 = std::exp(-.01);

/// Initialize the 1000 packet rounding to exp(-.001)
template <typename W, typename C>
const double ThreadPool<W, C>::CEXP1000 = std::exp(-.001);

}  // namespace util
}  // namespace isc

#endif  // THREAD_POOL_H
