// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef ASIO_WRAPPER_H
#define ASIO_WRAPPER_H 1

// The optimizer as of gcc 5.2.0, may not reliably ensure a single value
// returned by boost::system::system_category() within a translation unit
// when building the header only version of the boost error handling.
// See Trac #4309 for more details. For now we turn off optimization for
// header only builds the under the suspect GCC versions.
//
// The issue arises from in-lining the above function, which returns a
// reference to a local static variable, system_category_const,  This leads
// to situations where a construct such as the following:
//
// {{{
//    if (ec == boost::asio::error::would_block
//       || ec == boost::asio::error::try_again)
//      return false;
// }}}
//
// which involve implicit conversion of enumerates to error_code instances
// to not evaluate correctly.  During the implicit conversion the error_code
// instances may be assigned differeing values error_code:m_cat. This
// causes two instances of error_code which should have been equal to
// to not be equal.
//
// The problem disappers if either error handling code is not built header
// only as this results in a single definiton of system_category() supplied
// by libboost_system; or the error handling code is not optimized.
//
// We're doing the test here, rather than in configure to guard against the
// user supplying the header only flag via environment variables.
//
// @todo Currently, 5.3.0 is the latest released versio of GCC. Version 6.0 is
// in development and will need to be tested.

#define GNU_CC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

#if (defined(__GNUC__) && \
    ((GNU_CC_VERSION >= 50200) && (GNU_CC_VERSION <= 50300)) \
    && defined(BOOST_ERROR_CODE_HEADER_ONLY))
#pragma GCC push_options
#pragma GCC optimize ("O0")
#include <boost/asio.hpp>
#pragma GCC pop_options
#else
#include <boost/asio.hpp>
#endif

#endif // ASIO_WRAPPER_H
