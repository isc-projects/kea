//
// detail/win_iocp_socket_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP
#define ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_IOCP)

#include <boost/utility/addressof.hpp>
#include "asio/detail/bind_handler.hpp"
#include "asio/detail/buffer_sequence_adapter.hpp"
#include "asio/detail/fenced_block.hpp"
#include "asio/detail/handler_alloc_helpers.hpp"
#include "asio/detail/handler_invoke_helpers.hpp"
#include "asio/detail/operation.hpp"
#include "asio/detail/socket_ops.hpp"
#include "asio/error.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace detail {

template <typename ConstBufferSequence, typename Handler>
class win_iocp_socket_send_op : public operation
{
public:
  ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_send_op);

  win_iocp_socket_send_op(socket_ops::weak_cancel_token_type cancel_token,
      const ConstBufferSequence& buffers, Handler handler)
    : operation(&win_iocp_socket_send_op::do_complete),
      cancel_token_(cancel_token),
      buffers_(buffers),
      handler_(handler)
  {
  }

  static void do_complete(io_service_impl* owner, operation* base,
      asio::error_code ec, std::size_t bytes_transferred)
  {
    // Take ownership of the operation object.
    win_iocp_socket_send_op* o(static_cast<win_iocp_socket_send_op*>(base));
    ptr p = { boost::addressof(o->handler_), o, o };

#if defined(ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<asio::const_buffer,
          ConstBufferSequence>::validate(o->buffers_);
    }
#endif // defined(ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_send(o->cancel_token_, ec);

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, asio::error_code, std::size_t>
      handler(o->handler_, ec, bytes_transferred);
    p.h = boost::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      asio::detail::fenced_block b;
      asio_handler_invoke_helpers::invoke(handler, handler.handler_);
    }
  }

private:
  socket_ops::weak_cancel_token_type cancel_token_;
  ConstBufferSequence buffers_;
  Handler handler_;
};

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // defined(ASIO_HAS_IOCP)

#endif // ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP
