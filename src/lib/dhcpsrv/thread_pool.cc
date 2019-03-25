#include <cassert>
#include <config.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/thread_pool.h>

#include <functional>

using namespace std;

namespace isc {
namespace dhcp {

ThreadPool::ThreadPool() : exit_(true) {
}

ThreadPool::~ThreadPool() {
    destroy();
}

void ThreadPool::create(uint32_t worker_threads) {
    LOG_INFO(dhcpsrv_logger, "Starting packet thread pool with %1 worker threads")
        .arg(worker_threads);
    if (!worker_threads) {
        return;
    }
    destroy();
    queue_.create();
    exit_ = false;
    for (int i = 0; i < worker_threads; ++i) {
        worker_threads_.push_back(make_shared<thread>(&ThreadPool::threadRun, this));
    }

    LOG_INFO(dhcpsrv_logger, "Packet thread pool started");
}

void ThreadPool::destroy() {
    LOG_INFO(dhcpsrv_logger, "Shutting down packet thread pool");
    exit_ = true;
    queue_.destroy();
    for (auto thread : worker_threads_) {
        thread->join();
    }
    worker_threads_.clear();

    LOG_INFO(dhcpsrv_logger, "Packet thread pool shut down");
}

void ThreadPool::add(WorkItemCallBack call_back) {
    queue_.add(call_back);
}

size_t ThreadPool::count() {
    return queue_.count();
}

void ThreadPool::threadRun() {
    thread::id th_id = this_thread::get_id();
    LOG_INFO(dhcpsrv_logger, "Packet thread pool new thread started. id: %1").arg(th_id);

    while (!exit_) {
        WorkItemCallBack work_item;
        if (queue_.get(work_item)) {
            work_item();
        }
    }

    LOG_INFO(dhcpsrv_logger, "Packet thread pool thread ended. id: %1").arg(th_id);
}

}  // namespace dhcp
}  // namespace isc
