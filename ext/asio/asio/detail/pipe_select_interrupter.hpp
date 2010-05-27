//
// pipe_select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP
#define ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/push_options.hpp"

#include "asio/detail/push_options.hpp"
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include "asio/detail/pop_options.hpp"

#if !defined(BOOST_WINDOWS) && !defined(__CYGWIN__)

#include "asio/detail/push_options.hpp"
#include <fcntl.h>
#include "asio/detail/pop_options.hpp"

#include "asio/error.hpp"
#include "asio/system_error.hpp"
#include "asio/detail/socket_types.hpp"

namespace asio {
namespace detail {

class pipe_select_interrupter
{
public:
  // Constructor.
  pipe_select_interrupter()
  {
    int pipe_fds[2];
    if (pipe(pipe_fds) == 0)
    {
      read_descriptor_ = pipe_fds[0];
      ::fcntl(read_descriptor_, F_SETFL, O_NONBLOCK);
      write_descriptor_ = pipe_fds[1];
      ::fcntl(write_descriptor_, F_SETFL, O_NONBLOCK);
    }
    else
    {
      asio::error_code ec(errno,
          asio::error::get_system_category());
      asio::system_error e(ec, "pipe_select_interrupter");
      boost::throw_exception(e);
    }
  }

  // Destructor.
  ~pipe_select_interrupter()
  {
    if (read_descriptor_ != -1)
      ::close(read_descriptor_);
    if (write_descriptor_ != -1)
      ::close(write_descriptor_);
  }

  // Interrupt the select call.
  void interrupt()
  {
    char byte = 0;
    int result = ::write(write_descriptor_, &byte, 1);
    (void)result;
  }

  // Reset the select interrupt. Returns true if the call was interrupted.
  bool reset()
  {
    for (;;)
    {
      char data[1024];
      int bytes_read = ::read(read_descriptor_, data, sizeof(data));
      if (bytes_read < 0 && errno == EINTR)
        continue;
      bool was_interrupted = (bytes_read > 0);
      while (bytes_read == sizeof(data))
        bytes_read = ::read(read_descriptor_, data, sizeof(data));
      return was_interrupted;
    }
  }

  // Get the read descriptor to be passed to select.
  int read_descriptor() const
  {
    return read_descriptor_;
  }

private:
  // The read end of a connection used to interrupt the select call. This file
  // descriptor is passed to select such that when it is time to stop, a single
  // byte will be written on the other end of the connection and this
  // descriptor will become readable.
  int read_descriptor_;

  // The write end of a connection used to interrupt the select call. A single
  // byte may be written to this to wake up the select which is waiting for the
  // other end to become readable.
  int write_descriptor_;
};

} // namespace detail
} // namespace asio

#endif // !defined(BOOST_WINDOWS) && !defined(__CYGWIN__)

#include "asio/detail/pop_options.hpp"

#endif // ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP
