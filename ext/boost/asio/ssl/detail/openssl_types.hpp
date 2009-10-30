//
// openssl_types.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2005-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_OPENSSL_TYPES_HPP
#define BOOST_ASIO_SSL_DETAIL_OPENSSL_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>
#include <openssl/conf.h>
#include <openssl/ssl.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_OPENSSL_TYPES_HPP
