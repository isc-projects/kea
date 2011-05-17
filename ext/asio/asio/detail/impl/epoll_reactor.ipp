//
// detail/impl/epoll_reactor.ipp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_IMPL_EPOLL_REACTOR_IPP
#define ASIO_DETAIL_IMPL_EPOLL_REACTOR_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_EPOLL)

#include <cstddef>
#include <sys/epoll.h>
#include "asio/detail/epoll_reactor.hpp"
#include "asio/detail/throw_error.hpp"
#include "asio/error.hpp"

#if defined(ASIO_HAS_TIMERFD)
# include <sys/timerfd.h>
#endif // defined(ASIO_HAS_TIMERFD)

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

epoll_reactor::epoll_reactor(asio::io_service& io_service)
  : asio::detail::service_base<epoll_reactor>(io_service),
    io_service_(use_service<io_service_impl>(io_service)),
    mutex_(),
    epoll_fd_(do_epoll_create()),
#if defined(ASIO_HAS_TIMERFD)
    timer_fd_(timerfd_create(CLOCK_MONOTONIC, 0)),
#else // defined(ASIO_HAS_TIMERFD)
    timer_fd_(-1),
#endif // defined(ASIO_HAS_TIMERFD)
    interrupter_(),
    shutdown_(false)
{
  // Add the interrupter's descriptor to epoll.
  epoll_event ev = { 0, { 0 } };
  ev.events = EPOLLIN | EPOLLERR | EPOLLET;
  ev.data.ptr = &interrupter_;
  epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, interrupter_.read_descriptor(), &ev);
  interrupter_.interrupt();

  // Add the timer descriptor to epoll.
  if (timer_fd_ != -1)
  {
    ev.events = EPOLLIN | EPOLLERR;
    ev.data.ptr = &timer_fd_;
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, timer_fd_, &ev);
  }
}

epoll_reactor::~epoll_reactor()
{
  close(epoll_fd_);
  if (timer_fd_ != -1)
    close(timer_fd_);
}

void epoll_reactor::shutdown_service()
{
  mutex::scoped_lock lock(mutex_);
  shutdown_ = true;
  lock.unlock();

  op_queue<operation> ops;

  while (descriptor_state* state = registered_descriptors_.first())
  {
    for (int i = 0; i < max_ops; ++i)
      ops.push(state->op_queue_[i]);
    state->shutdown_ = true;
    registered_descriptors_.free(state);
  }

  timer_queues_.get_all_timers(ops);
}

void epoll_reactor::init_task()
{
  io_service_.init_task();
}

int epoll_reactor::register_descriptor(socket_type descriptor,
    epoll_reactor::per_descriptor_data& descriptor_data)
{
  mutex::scoped_lock lock(registered_descriptors_mutex_);

  descriptor_data = registered_descriptors_.alloc();
  descriptor_data->shutdown_ = false;

  lock.unlock();

  epoll_event ev = { 0, { 0 } };
  ev.events = EPOLLIN | EPOLLERR | EPOLLHUP | EPOLLOUT | EPOLLPRI | EPOLLET;
  ev.data.ptr = descriptor_data;
  int result = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, descriptor, &ev);
  if (result != 0)
    return errno;

  return 0;
}

void epoll_reactor::start_op(int op_type, socket_type descriptor,
    epoll_reactor::per_descriptor_data& descriptor_data,
    reactor_op* op, bool allow_speculative)
{
  if (!descriptor_data)
  {
    op->ec_ = asio::error::bad_descriptor;
    post_immediate_completion(op);
    return;
  }

  mutex::scoped_lock descriptor_lock(descriptor_data->mutex_);

  if (descriptor_data->shutdown_)
  {
    post_immediate_completion(op);
    return;
  }

  if (descriptor_data->op_queue_[op_type].empty())
  {
    if (allow_speculative
        && (op_type != read_op
          || descriptor_data->op_queue_[except_op].empty()))
    {
      if (op->perform())
      {
        descriptor_lock.unlock();
        io_service_.post_immediate_completion(op);
        return;
      }
    }
    else
    {
      epoll_event ev = { 0, { 0 } };
      ev.events = EPOLLIN | EPOLLERR | EPOLLHUP
        | EPOLLOUT | EPOLLPRI | EPOLLET;
      ev.data.ptr = descriptor_data;
      epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, descriptor, &ev);
    }
  }

  descriptor_data->op_queue_[op_type].push(op);
  io_service_.work_started();
}

void epoll_reactor::cancel_ops(socket_type,
    epoll_reactor::per_descriptor_data& descriptor_data)
{
  if (!descriptor_data)
    return;

  mutex::scoped_lock descriptor_lock(descriptor_data->mutex_);

  op_queue<operation> ops;
  for (int i = 0; i < max_ops; ++i)
  {
    while (reactor_op* op = descriptor_data->op_queue_[i].front())
    {
      op->ec_ = asio::error::operation_aborted;
      descriptor_data->op_queue_[i].pop();
      ops.push(op);
    }
  }

  descriptor_lock.unlock();

  io_service_.post_deferred_completions(ops);
}

void epoll_reactor::close_descriptor(socket_type,
    epoll_reactor::per_descriptor_data& descriptor_data)
{
  if (!descriptor_data)
    return;

  mutex::scoped_lock descriptor_lock(descriptor_data->mutex_);
  mutex::scoped_lock descriptors_lock(registered_descriptors_mutex_);

  if (!descriptor_data->shutdown_)
  {
    // Remove the descriptor from the set of known descriptors. The descriptor
    // will be automatically removed from the epoll set when it is closed.

    op_queue<operation> ops;
    for (int i = 0; i < max_ops; ++i)
    {
      while (reactor_op* op = descriptor_data->op_queue_[i].front())
      {
        op->ec_ = asio::error::operation_aborted;
        descriptor_data->op_queue_[i].pop();
        ops.push(op);
      }
    }

    descriptor_data->shutdown_ = true;

    descriptor_lock.unlock();

    registered_descriptors_.free(descriptor_data);
    descriptor_data = 0;

    descriptors_lock.unlock();

    io_service_.post_deferred_completions(ops);
  }
}

void epoll_reactor::run(bool block, op_queue<operation>& ops)
{
  // Calculate a timeout only if timerfd is not used.
  int timeout;
  if (timer_fd_ != -1)
    timeout = block ? -1 : 0;
  else
  {
    mutex::scoped_lock lock(mutex_);
    timeout = block ? get_timeout() : 0;
  }

  // Block on the epoll descriptor.
  epoll_event events[128];
  int num_events = epoll_wait(epoll_fd_, events, 128, timeout);

#if defined(ASIO_HAS_TIMERFD)
  bool check_timers = (timer_fd_ == -1);
#else // defined(ASIO_HAS_TIMERFD)
  bool check_timers = true;
#endif // defined(ASIO_HAS_TIMERFD)

  // Dispatch the waiting events.
  for (int i = 0; i < num_events; ++i)
  {
    void* ptr = events[i].data.ptr;
    if (ptr == &interrupter_)
    {
      // No need to reset the interrupter since we're leaving the descriptor
      // in a ready-to-read state and relying on edge-triggered notifications
      // to make it so that we only get woken up when the descriptor's epoll
      // registration is updated.

#if defined(ASIO_HAS_TIMERFD)
      if (timer_fd_ == -1)
        check_timers = true;
#else // defined(ASIO_HAS_TIMERFD)
      check_timers = true;
#endif // defined(ASIO_HAS_TIMERFD)
    }
#if defined(ASIO_HAS_TIMERFD)
    else if (ptr == &timer_fd_)
    {
      check_timers = true;
    }
#endif // defined(ASIO_HAS_TIMERFD)
    else
    {
      descriptor_state* descriptor_data = static_cast<descriptor_state*>(ptr);
      mutex::scoped_lock descriptor_lock(descriptor_data->mutex_);

      // Exception operations must be processed first to ensure that any
      // out-of-band data is read before normal data.
      static const int flag[max_ops] = { EPOLLIN, EPOLLOUT, EPOLLPRI };
      for (int j = max_ops - 1; j >= 0; --j)
      {
        if (events[i].events & (flag[j] | EPOLLERR | EPOLLHUP))
        {
          while (reactor_op* op = descriptor_data->op_queue_[j].front())
          {
            if (op->perform())
            {
              descriptor_data->op_queue_[j].pop();
              ops.push(op);
            }
            else
              break;
          }
        }
      }
    }
  }

  if (check_timers)
  {
    mutex::scoped_lock common_lock(mutex_);
    timer_queues_.get_ready_timers(ops);

#if defined(ASIO_HAS_TIMERFD)
    if (timer_fd_ != -1)
    {
      itimerspec new_timeout;
      itimerspec old_timeout;
      int flags = get_timeout(new_timeout);
      timerfd_settime(timer_fd_, flags, &new_timeout, &old_timeout);
    }
#endif // defined(ASIO_HAS_TIMERFD)
  }
}

void epoll_reactor::interrupt()
{
  epoll_event ev = { 0, { 0 } };
  ev.events = EPOLLIN | EPOLLERR | EPOLLET;
  ev.data.ptr = &interrupter_;
  epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, interrupter_.read_descriptor(), &ev);
}

int epoll_reactor::do_epoll_create()
{
  int fd = epoll_create(epoll_size);
  if (fd == -1)
  {
    asio::error_code ec(errno,
        asio::error::get_system_category());
    asio::detail::throw_error(ec, "epoll");
  }
  return fd;
}

void epoll_reactor::do_add_timer_queue(timer_queue_base& queue)
{
  mutex::scoped_lock lock(mutex_);
  timer_queues_.insert(&queue);
}

void epoll_reactor::do_remove_timer_queue(timer_queue_base& queue)
{
  mutex::scoped_lock lock(mutex_);
  timer_queues_.erase(&queue);
}

void epoll_reactor::update_timeout()
{
#if defined(ASIO_HAS_TIMERFD)
  if (timer_fd_ != -1)
  {
    itimerspec new_timeout;
    itimerspec old_timeout;
    int flags = get_timeout(new_timeout);
    timerfd_settime(timer_fd_, flags, &new_timeout, &old_timeout);
    return;
  }
#endif // defined(ASIO_HAS_TIMERFD)
  interrupt();
}

int epoll_reactor::get_timeout()
{
  // By default we will wait no longer than 5 minutes. This will ensure that
  // any changes to the system clock are detected after no longer than this.
  return timer_queues_.wait_duration_msec(5 * 60 * 1000);
}

#if defined(ASIO_HAS_TIMERFD)
int epoll_reactor::get_timeout(itimerspec& ts)
{
  ts.it_interval.tv_sec = 0;
  ts.it_interval.tv_nsec = 0;

  long usec = timer_queues_.wait_duration_usec(5 * 60 * 1000 * 1000);
  ts.it_value.tv_sec = usec / 1000000;
  ts.it_value.tv_nsec = usec ? (usec % 1000000) * 1000 : 1;

  return usec ? 0 : TFD_TIMER_ABSTIME;
}
#endif // defined(ASIO_HAS_TIMERFD)

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // defined(ASIO_HAS_EPOLL)

#endif // ASIO_DETAIL_IMPL_EPOLL_REACTOR_IPP
