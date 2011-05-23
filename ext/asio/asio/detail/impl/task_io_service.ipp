//
// detail/impl/task_io_service.ipp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_IMPL_TASK_IO_SERVICE_IPP
#define ASIO_DETAIL_IMPL_TASK_IO_SERVICE_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if !defined(ASIO_HAS_IOCP)

#include <boost/limits.hpp>
#include "asio/detail/call_stack.hpp"
#include "asio/detail/event.hpp"
#include "asio/detail/reactor.hpp"
#include "asio/detail/task_io_service.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

struct task_io_service::task_cleanup
{
  ~task_cleanup()
  {
    // Enqueue the completed operations and reinsert the task at the end of
    // the operation queue.
    lock_->lock();
    task_io_service_->task_interrupted_ = true;
    task_io_service_->op_queue_.push(*ops_);
    task_io_service_->op_queue_.push(&task_io_service_->task_operation_);
  }

  task_io_service* task_io_service_;
  mutex::scoped_lock* lock_;
  op_queue<operation>* ops_;
};

struct task_io_service::work_finished_on_block_exit
{
  ~work_finished_on_block_exit()
  {
    task_io_service_->work_finished();
  }

  task_io_service* task_io_service_;
};

struct task_io_service::idle_thread_info
{
  event wakeup_event;
  idle_thread_info* next;
};

task_io_service::task_io_service(asio::io_service& io_service)
  : asio::detail::service_base<task_io_service>(io_service),
    mutex_(),
    task_(0),
    task_interrupted_(true),
    outstanding_work_(0),
    stopped_(false),
    shutdown_(false),
    first_idle_thread_(0)
{
}

void task_io_service::init(std::size_t /*concurrency_hint*/)
{
}

void task_io_service::shutdown_service()
{
  mutex::scoped_lock lock(mutex_);
  shutdown_ = true;
  lock.unlock();

  // Destroy handler objects.
  while (!op_queue_.empty())
  {
    operation* o = op_queue_.front();
    op_queue_.pop();
    if (o != &task_operation_)
      o->destroy();
  }

  // Reset to initial state.
  task_ = 0;
}

void task_io_service::init_task()
{
  mutex::scoped_lock lock(mutex_);
  if (!shutdown_ && !task_)
  {
    task_ = &use_service<reactor>(this->get_io_service());
    op_queue_.push(&task_operation_);
    wake_one_thread_and_unlock(lock);
  }
}

std::size_t task_io_service::run(asio::error_code& ec)
{
  ec = asio::error_code();
  if (outstanding_work_ == 0)
  {
    stop();
    return 0;
  }

  call_stack<task_io_service>::context ctx(this);

  idle_thread_info this_idle_thread;
  this_idle_thread.next = 0;

  mutex::scoped_lock lock(mutex_);

  std::size_t n = 0;
  for (; do_one(lock, &this_idle_thread); lock.lock())
    if (n != (std::numeric_limits<std::size_t>::max)())
      ++n;
  return n;
}

std::size_t task_io_service::run_one(asio::error_code& ec)
{
  ec = asio::error_code();
  if (outstanding_work_ == 0)
  {
    stop();
    return 0;
  }

  call_stack<task_io_service>::context ctx(this);

  idle_thread_info this_idle_thread;
  this_idle_thread.next = 0;

  mutex::scoped_lock lock(mutex_);

  return do_one(lock, &this_idle_thread);
}

std::size_t task_io_service::poll(asio::error_code& ec)
{
  if (outstanding_work_ == 0)
  {
    stop();
    ec = asio::error_code();
    return 0;
  }

  call_stack<task_io_service>::context ctx(this);

  mutex::scoped_lock lock(mutex_);

  std::size_t n = 0;
  for (; do_one(lock, 0); lock.lock())
    if (n != (std::numeric_limits<std::size_t>::max)())
      ++n;
  return n;
}

std::size_t task_io_service::poll_one(asio::error_code& ec)
{
  ec = asio::error_code();
  if (outstanding_work_ == 0)
  {
    stop();
    return 0;
  }

  call_stack<task_io_service>::context ctx(this);

  mutex::scoped_lock lock(mutex_);

  return do_one(lock, 0);
}

void task_io_service::stop()
{
  mutex::scoped_lock lock(mutex_);
  stop_all_threads(lock);
}

void task_io_service::reset()
{
  mutex::scoped_lock lock(mutex_);
  stopped_ = false;
}

void task_io_service::post_immediate_completion(task_io_service::operation* op)
{
  work_started();
  post_deferred_completion(op);
}

void task_io_service::post_deferred_completion(task_io_service::operation* op)
{
  mutex::scoped_lock lock(mutex_);
  op_queue_.push(op);
  wake_one_thread_and_unlock(lock);
}

void task_io_service::post_deferred_completions(
    op_queue<task_io_service::operation>& ops)
{
  if (!ops.empty())
  {
    mutex::scoped_lock lock(mutex_);
    op_queue_.push(ops);
    wake_one_thread_and_unlock(lock);
  }
}

std::size_t task_io_service::do_one(mutex::scoped_lock& lock,
    task_io_service::idle_thread_info* this_idle_thread)
{
  bool polling = !this_idle_thread;
  bool task_has_run = false;
  while (!stopped_)
  {
    if (!op_queue_.empty())
    {
      // Prepare to execute first handler from queue.
      operation* o = op_queue_.front();
      op_queue_.pop();
      bool more_handlers = (!op_queue_.empty());

      if (o == &task_operation_)
      {
        task_interrupted_ = more_handlers || polling;

        // If the task has already run and we're polling then we're done.
        if (task_has_run && polling)
        {
          task_interrupted_ = true;
          op_queue_.push(&task_operation_);
          return 0;
        }
        task_has_run = true;

        if (!more_handlers || !wake_one_idle_thread_and_unlock(lock))
          lock.unlock();

        op_queue<operation> completed_ops;
        task_cleanup c = { this, &lock, &completed_ops };
        (void)c;

        // Run the task. May throw an exception. Only block if the operation
        // queue is empty and we're not polling, otherwise we want to return
        // as soon as possible.
        task_->run(!more_handlers && !polling, completed_ops);
      }
      else
      {
        if (more_handlers)
          wake_one_thread_and_unlock(lock);
        else
          lock.unlock();

        // Ensure the count of outstanding work is decremented on block exit.
        work_finished_on_block_exit on_exit = { this };
        (void)on_exit;

        // Complete the operation. May throw an exception.
        o->complete(*this); // deletes the operation object

        return 1;
      }
    }
    else if (this_idle_thread)
    {
      // Nothing to run right now, so just wait for work to do.
      this_idle_thread->next = first_idle_thread_;
      first_idle_thread_ = this_idle_thread;
      this_idle_thread->wakeup_event.clear(lock);
      this_idle_thread->wakeup_event.wait(lock);
    }
    else
    {
      return 0;
    }
  }

  return 0;
}

void task_io_service::stop_all_threads(
    mutex::scoped_lock& lock)
{
  stopped_ = true;

  while (first_idle_thread_)
  {
    idle_thread_info* idle_thread = first_idle_thread_;
    first_idle_thread_ = idle_thread->next;
    idle_thread->next = 0;
    idle_thread->wakeup_event.signal(lock);
  }

  if (!task_interrupted_ && task_)
  {
    task_interrupted_ = true;
    task_->interrupt();
  }
}

bool task_io_service::wake_one_idle_thread_and_unlock(
    mutex::scoped_lock& lock)
{
  if (first_idle_thread_)
  {
    idle_thread_info* idle_thread = first_idle_thread_;
    first_idle_thread_ = idle_thread->next;
    idle_thread->next = 0;
    idle_thread->wakeup_event.signal_and_unlock(lock);
    return true;
  }
  return false;
}

void task_io_service::wake_one_thread_and_unlock(
    mutex::scoped_lock& lock)
{
  if (!wake_one_idle_thread_and_unlock(lock))
  {
    if (!task_interrupted_ && task_)
    {
      task_interrupted_ = true;
      task_->interrupt();
    }
    lock.unlock();
  }
}

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // !defined(ASIO_HAS_IOCP)

#endif // ASIO_DETAIL_IMPL_TASK_IO_SERVICE_IPP
