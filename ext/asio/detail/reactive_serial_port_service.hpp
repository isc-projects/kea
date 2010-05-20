//
// reactive_serial_port_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_REACTIVE_SERIAL_PORT_SERVICE_HPP
#define ASIO_DETAIL_REACTIVE_SERIAL_PORT_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/push_options.hpp"

#include "asio/detail/push_options.hpp"
#include <cstring>
#include <string>
#include "asio/detail/pop_options.hpp"

#include "asio/serial_port_base.hpp"

#if defined(ASIO_HAS_SERIAL_PORT) \
  && !defined(BOOST_WINDOWS) && !defined(__CYGWIN__)

#include "asio/error.hpp"
#include "asio/io_service.hpp"
#include "asio/detail/descriptor_ops.hpp"
#include "asio/detail/reactive_descriptor_service.hpp"

namespace asio {
namespace detail {

// Extend reactive_descriptor_service to provide serial port support.
class reactive_serial_port_service
{
public:
  // The native type of a serial port.
  typedef reactive_descriptor_service::native_type native_type;

  // The implementation type of the serial port.
  typedef reactive_descriptor_service::implementation_type implementation_type;

  reactive_serial_port_service(asio::io_service& io_service)
    : descriptor_service_(io_service)
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown_service()
  {
    descriptor_service_.shutdown_service();
  }

  // Construct a new handle implementation.
  void construct(implementation_type& impl)
  {
    descriptor_service_.construct(impl);
  }

  // Destroy a handle implementation.
  void destroy(implementation_type& impl)
  {
    descriptor_service_.destroy(impl);
  }

  // Open the serial port using the specified device name.
  asio::error_code open(implementation_type& impl,
      const std::string& device, asio::error_code& ec)
  {
    if (is_open(impl))
    {
      ec = asio::error::already_open;
      return ec;
    }

    int fd = descriptor_ops::open(device.c_str(),
        O_RDWR | O_NONBLOCK | O_NOCTTY, ec);
    if (fd < 0)
      return ec;

    int s = descriptor_ops::fcntl(fd, F_GETFL, ec);
    if (s >= 0)
      s = descriptor_ops::fcntl(fd, F_SETFL, s | O_NONBLOCK, ec);
    if (s < 0)
    {
      asio::error_code ignored_ec;
      descriptor_ops::close(fd, ignored_ec);
      return ec;
    }
  
    // Set up default serial port options.
    termios ios;
    descriptor_ops::clear_error(ec);
    s = descriptor_ops::error_wrapper(::tcgetattr(fd, &ios), ec);
    if (s >= 0)
    {
#if defined(_BSD_SOURCE)
      ::cfmakeraw(&ios);
#else
      ios.c_iflag &= ~(IGNBRK | BRKINT | PARMRK
          | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
      ios.c_oflag &= ~OPOST;
      ios.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
      ios.c_cflag &= ~(CSIZE | PARENB);
      ios.c_cflag |= CS8;
#endif
      ios.c_iflag |= IGNPAR;
      ios.c_cflag |= CREAD | CLOCAL;
      descriptor_ops::clear_error(ec);
      s = descriptor_ops::error_wrapper(::tcsetattr(fd, TCSANOW, &ios), ec);
    }
    if (s < 0)
    {
      asio::error_code ignored_ec;
      descriptor_ops::close(fd, ignored_ec);
      return ec;
    }
  
    // We're done. Take ownership of the serial port descriptor.
    if (descriptor_service_.assign(impl, fd, ec))
    {
      asio::error_code ignored_ec;
      descriptor_ops::close(fd, ignored_ec);
    }

    return ec;
  }

  // Assign a native handle to a handle implementation.
  asio::error_code assign(implementation_type& impl,
      const native_type& native_descriptor, asio::error_code& ec)
  {
    return descriptor_service_.assign(impl, native_descriptor, ec);
  }

  // Determine whether the handle is open.
  bool is_open(const implementation_type& impl) const
  {
    return descriptor_service_.is_open(impl);
  }

  // Destroy a handle implementation.
  asio::error_code close(implementation_type& impl,
      asio::error_code& ec)
  {
    return descriptor_service_.close(impl, ec);
  }

  // Get the native handle representation.
  native_type native(implementation_type& impl)
  {
    return descriptor_service_.native(impl);
  }

  // Cancel all operations associated with the handle.
  asio::error_code cancel(implementation_type& impl,
      asio::error_code& ec)
  {
    return descriptor_service_.cancel(impl, ec);
  }

  // Set an option on the serial port.
  template <typename SettableSerialPortOption>
  asio::error_code set_option(implementation_type& impl,
      const SettableSerialPortOption& option, asio::error_code& ec)
  {
    termios ios;
    descriptor_ops::clear_error(ec);
    descriptor_ops::error_wrapper(::tcgetattr(
          descriptor_service_.native(impl), &ios), ec);
    if (ec)
      return ec;

    if (option.store(ios, ec))
      return ec;

    descriptor_ops::clear_error(ec);
    descriptor_ops::error_wrapper(::tcsetattr(
          descriptor_service_.native(impl), TCSANOW, &ios), ec);
    return ec;
  }

  // Get an option from the serial port.
  template <typename GettableSerialPortOption>
  asio::error_code get_option(const implementation_type& impl,
      GettableSerialPortOption& option, asio::error_code& ec) const
  {
    termios ios;
    descriptor_ops::clear_error(ec);
    descriptor_ops::error_wrapper(::tcgetattr(
          descriptor_service_.native(impl), &ios), ec);
    if (ec)
      return ec;

    return option.load(ios, ec);
  }

  // Send a break sequence to the serial port.
  asio::error_code send_break(implementation_type& impl,
      asio::error_code& ec)
  {
    descriptor_ops::clear_error(ec);
    descriptor_ops::error_wrapper(::tcsendbreak(
          descriptor_service_.native(impl), 0), ec);
    return ec;
  }

  // Write the given data. Returns the number of bytes sent.
  template <typename ConstBufferSequence>
  size_t write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, asio::error_code& ec)
  {
    return descriptor_service_.write_some(impl, buffers, ec);
  }

  // Start an asynchronous write. The data being written must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler>
  void async_write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, Handler handler)
  {
    descriptor_service_.async_write_some(impl, buffers, handler);
  }

  // Read some data. Returns the number of bytes received.
  template <typename MutableBufferSequence>
  size_t read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, asio::error_code& ec)
  {
    return descriptor_service_.read_some(impl, buffers, ec);
  }

  // Start an asynchronous read. The buffer for the data being received must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence, typename Handler>
  void async_read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, Handler handler)
  {
    descriptor_service_.async_read_some(impl, buffers, handler);
  }

private:
  // The implementation used for initiating asynchronous operations.
  reactive_descriptor_service descriptor_service_;
};

} // namespace detail
} // namespace asio

#endif // defined(ASIO_HAS_SERIAL_PORT)
       //   && !defined(BOOST_WINDOWS) && !defined(__CYGWIN__)

#include "asio/detail/pop_options.hpp"

#endif // ASIO_DETAIL_REACTIVE_SERIAL_PORT_SERVICE_HPP
