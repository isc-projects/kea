// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef ASIO_WRAPPER_H
#define ASIO_WRAPPER_H 1

/// !!! IMPORTANT THIS IS A HACK FOR BOOST HEADERS ONLY BUILDING !!!!
///
/// As of #5215 (Kea 1.3) The default build configuration is to link with
/// Boost's system library (boost_system) rather than build with Boost's
/// headers only. Linking with the boost_system eliminates the issue as
/// detailed below. This file exists solely for the purpose of allowing
/// people to attempt to build headers only.  ISC DOES NOT RECOMMEND
/// building Kea with Boost headers only.
///
/// This file must be included anywhere one would normally have included
/// boost/asio.hpp.  Until the issue described below is resolved in some
/// other fashion, (or we abandon support for headers only building)
/// asio.hpp MUST NOT be included other than through this file.
///
/// The optimizer as of gcc 5.2.0, may not reliably ensure a single value
/// returned by boost::system::system_category() within a translation unit
/// when building the header only version of the boost error handling.
/// See Trac #4243 for more details. For now we turn off optimization for
/// header only builds the under the suspect GCC versions.
///
/// The issue arises from in-lining the above function, which returns a
/// reference to a local static variable, system_category_const.  This leads
/// to situations where a construct such as the following:
///
/// {{{
///    if (ec == boost::asio::error::would_block
///       || ec == boost::asio::error::try_again)
///      return false;
/// }}}
///
/// which involve implicit conversion of enumerates to error_code instances
/// to not evaluate correctly.  During the implicit conversion the error_code
/// instances may be assigned differing values error_code:m_cat. This
/// causes two instances of error_code which should have been equal to
/// to not be equal.
///
/// The problem disappears if either error handling code is not built header
/// only as this results in a single definition of system_category() supplied
/// by libboost_system; or the error handling code is not optimized.
///
/// We're doing the test here, rather than in configure to guard against the
/// user supplying the header only flag via environment variables.
///
/// We opened bugs with GNU and BOOST:
///
/// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=69789
/// https://svn.boost.org/trac/boost/ticket/11989
///
/// @todo Version 6.0 will need to be tested.
///
/// As of 2016-08-19, the version 5.4.0 from Ubuntu 16.04 is affected. Updated
/// the check to cover everything that is not 6.0, hoping that 6.0 solves the
/// problem.

// Some boost headers need the <utility> header to be included for some Boost versions under C++20.
// Include it in all situations for simplicity.
#include <utility>

#define GNU_CC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

#if (defined(__GNUC__) && \
    ((GNU_CC_VERSION >= 50200) && (GNU_CC_VERSION < 60000)) \
    && defined(BOOST_ERROR_CODE_HEADER_ONLY))
#pragma GCC push_options
#pragma GCC optimize ("O0")
#include <boost/asio.hpp>
#pragma GCC pop_options
#else
#include <boost/asio.hpp>
#endif

#endif // ASIO_WRAPPER_H
