//
// detail/weak_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_WEAK_PTR_HPP
#define ASIO_DETAIL_WEAK_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <boost/version.hpp>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# include <memory>
#else
# include <boost/weak_ptr.hpp>
#endif

namespace asio {
namespace detail {

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
using std::weak_ptr;
#else
using boost::weak_ptr;
#endif

} // namespace detail
} // namespace asio

#endif // ASIO_DETAIL_WEAK_PTR_HPP
