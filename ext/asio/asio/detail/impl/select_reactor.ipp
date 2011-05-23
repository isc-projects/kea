//
// detail/impl/select_reactor.ipp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_IMPL_SELECT_REACTOR_IPP
#define ASIO_DETAIL_IMPL_SELECT_REACTOR_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_IOCP) \
  || (!defined(ASIO_HAS_DEV_POLL) \
      && !defined(ASIO_HAS_EPOLL) \
      && !defined(ASIO_HAS_KQUEUE))

#include "asio/detail/bind_handler.hpp"
#include "asio/detail/fd_set_adapter.hpp"
#include "asio/detail/select_reactor.hpp"
#include "asio/detail/signal_blocker.hpp"
#include "asio/detail/socket_ops.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

select_reactor::select_reactor(asio::io_service& io_service)
  : asio::detail::service_base<select_reactor>(io_service),
    io_service_(use_service<io_service_impl>(io_service)),
    mutex_(),
    interrupter_(),
#if defined(ASIO_HAS_IOCP)
    stop_thread_(false),
    thread_(0),
#endif // defined(ASIO_HAS_IOCP)
    shutdown_(false)
{
#if defined(ASIO_HAS_IOCP)
  asio::detail::signal_blocker sb;
  thread_ = new asio::detail::thread(
      bind_handler(&select_reactor::call_run_thread, this));
#endif // defined(ASIO_HAS_IOCP)
}

select_reactor::~select_reactor()
{
  shutdown_service();
}

void select_reactor::shutdown_service()
{
  asio::detail::mutex::scoped_lock lock(mutex_);
  shutdown_ = true;
#if defined(ASIO_HAS_IOCP)
  stop_thread_ = true;
#endif // defined(ASIO_HAS_IOCP)
  lock.unlock();

#if defined(ASIO_HAS_IOCP)
  if (thread_)
  {
    interrupter_.interrupt();
    thread_->join();
    delete thread_;
    thread_ = 0;
  }
#endif // defined(ASIO_HAS_IOCP)

  op_queue<operation> ops;

  for (int i = 0; i < max_ops; ++i)
    op_queue_[i].get_all_operations(ops);

  timer_queues_.get_all_timers(ops);
}

void select_reactor::init_task()
{
  io_service_.init_task();
}

int select_reactor::register_descriptor(socket_type,
    select_reactor::per_descriptor_data&)
{
  return 0;
}

void select_reactor::start_op(int op_type, socket_type descriptor,
    select_reactor::per_descriptor_data&, reactor_op* op, bool)
{
  asio::detail::mutex::scoped_lock lock(mutex_);

  if (shutdown_)
  {
    post_immediate_completion(op);
    return;
  }

  bool first = op_queue_[op_type].enqueue_operation(descriptor, op);
  io_service_.work_started();
  if (first)
    interrupter_.interrupt();
}

void select_reactor::cancel_ops(socket_type descriptor,
    select_reactor::per_descriptor_data&)
{
  asio::detail::mutex::scoped_lock lock(mutex_);
  cancel_ops_unlocked(descriptor, asio::error::operation_aborted);
}

void select_reactor::close_descriptor(socket_type descriptor,
    select_reactor::per_descriptor_data&)
{
  asio::detail::mutex::scoped_lock lock(mutex_);
  cancel_ops_unlocked(descriptor, asio::error::operation_aborted);
}

void select_reactor::run(bool block, op_queue<operation>& ops)
{
  asio::detail::mutex::scoped_lock lock(mutex_);

#if defined(ASIO_HAS_IOCP)
  // Check if the thread is supposed to stop.
  if (stop_thread_)
    return;
#endif // defined(ASIO_HAS_IOCP)

  // Set up the descriptor sets.
  fd_set_adapter fds[max_select_ops];
  fds[read_op].set(interrupter_.read_descriptor());
  socket_type max_fd = 0;
  bool have_work_to_do = !timer_queues_.all_empty();
  for (int i = 0; i < max_select_ops; ++i)
  {
    have_work_to_do = have_work_to_do || !op_queue_[i].empty();
    op_queue_[i].get_descriptors(fds[i], ops);
    if (fds[i].max_descriptor() > max_fd)
      max_fd = fds[i].max_descriptor();
  }

#if defined(BOOST_WINDOWS) || defined(__CYGWIN__)
  // Connection operations on Windows use both except and write fd_sets.
  have_work_to_do = have_work_to_do || !op_queue_[connect_op].empty();
  op_queue_[connect_op].get_descriptors(fds[write_op], ops);
  if (fds[write_op].max_descriptor() > max_fd)
    max_fd = fds[write_op].max_descriptor();
  op_queue_[connect_op].get_descriptors(fds[except_op], ops);
  if (fds[except_op].max_descriptor() > max_fd)
    max_fd = fds[except_op].max_descriptor();
#endif // defined(BOOST_WINDOWS) || defined(__CYGWIN__)

  // We can return immediately if there's no work to do and the reactor is
  // not supposed to block.
  if (!block && !have_work_to_do)
    return;

  // Determine how long to block while waiting for events.
  timeval tv_buf = { 0, 0 };
  timeval* tv = block ? get_timeout(tv_buf) : &tv_buf;

  lock.unlock();

  // Block on the select call until descriptors become ready.
  asio::error_code ec;
  int retval = socket_ops::select(static_cast<int>(max_fd + 1),
      fds[read_op], fds[write_op], fds[except_op], tv, ec);

  // Reset the interrupter.
  if (retval > 0 && fds[read_op].is_set(interrupter_.read_descriptor()))
    interrupter_.reset();

  lock.lock();

  // Dispatch all ready operations.
  if (retval > 0)
  {
#if defined(BOOST_WINDOWS) || defined(__CYGWIN__)
    // Connection operations on Windows use both except and write fd_sets.
    op_queue_[connect_op].perform_operations_for_descriptors(
        fds[except_op], ops);
    op_queue_[connect_op].perform_operations_for_descriptors(
        fds[write_op], ops);
#endif // defined(BOOST_WINDOWS) || defined(__CYGWIN__)

    // Exception operations must be processed first to ensure that any
    // out-of-band data is read before normal data.
    for (int i = max_select_ops - 1; i >= 0; --i)
      op_queue_[i].perform_operations_for_descriptors(fds[i], ops);
  }
  timer_queues_.get_ready_timers(ops);
}

void select_reactor::interrupt()
{
  interrupter_.interrupt();
}

#if defined(ASIO_HAS_IOCP)
void select_reactor::run_thread()
{
  asio::detail::mutex::scoped_lock lock(mutex_);
  while (!stop_thread_)
  {
    lock.unlock();
    op_queue<operation> ops;
    run(true, ops);
    io_service_.post_deferred_completions(ops);
    lock.lock();
  }
}

void select_reactor::call_run_thread(select_reactor* reactor)
{
  reactor->run_thread();
}
#endif // defined(ASIO_HAS_IOCP)

void select_reactor::do_add_timer_queue(timer_queue_base& queue)
{
  mutex::scoped_lock lock(mutex_);
  timer_queues_.insert(&queue);
}

void select_reactor::do_remove_timer_queue(timer_queue_base& queue)
{
  mutex::scoped_lock lock(mutex_);
  timer_queues_.erase(&queue);
}

timeval* select_reactor::get_timeout(timeval& tv)
{
  // By default we will wait no longer than 5 minutes. This will ensure that
  // any changes to the system clock are detected after no longer than this.
  long usec = timer_queues_.wait_duration_usec(5 * 60 * 1000 * 1000);
  tv.tv_sec = usec / 1000000;
  tv.tv_usec = usec % 1000000;
  return &tv;
}

void select_reactor::cancel_ops_unlocked(socket_type descriptor,
    const asio::error_code& ec)
{
  bool need_interrupt = false;
  op_queue<operation> ops;
  for (int i = 0; i < max_ops; ++i)
    need_interrupt = op_queue_[i].cancel_operations(
        descriptor, ops, ec) || need_interrupt;
  io_service_.post_deferred_completions(ops);
  if (need_interrupt)
    interrupter_.interrupt();
}

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // defined(ASIO_HAS_IOCP)
       //   || (!defined(ASIO_HAS_DEV_POLL)
       //       && !defined(ASIO_HAS_EPOLL)
       //       && !defined(ASIO_HAS_KQUEUE))

#endif // ASIO_DETAIL_IMPL_SELECT_REACTOR_IPP
