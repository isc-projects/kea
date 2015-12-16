// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ASIOLINK_H
#define ASIOLINK_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.

#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>

#include <asiolink/io_address.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_socket.h>
#include <asiolink/io_error.h>

/// \namespace asiolink
/// \brief A wrapper interface for the ASIO library.
///
/// The \c asiolink namespace is used to define a set of wrapper interfaces
/// for the ASIO library.
///
/// Kea uses the Boost version of ASIO in its header-only mode,
/// i.e., does not require a separate library object to be linked, and thus
/// lowers the bar for introduction.
///
/// But the advantage comes with its own costs: since the header-only version
/// includes more definitions in public header files, it tends to trigger
/// more compiler warnings for our own sources, and, depending on the
/// compiler options, may make the build fail.
///
/// We also found it may be tricky to use ASIO and standard C++ libraries
/// in a single translation unit, i.e., a .cc file: depending on the order
/// of including header files, ASIO may or may not work on some platforms.
///
/// This wrapper interface is intended to centralize these
/// problematic issues in a single sub module.  Other Kea modules should
/// simply include \c asiolink.h and use the wrapper API instead of
/// including ASIO header files and using ASIO-specific classes directly.
///
/// This wrapper may be used for other IO libraries if and when we want to
/// switch, but generality for that purpose is not the primary goal of
/// this module.  The resulting interfaces are thus straightforward mapping
/// to the ASIO counterparts.
///
/// One obvious drawback of this approach is performance overhead
/// due to the additional layer.  We should eventually evaluate the cost
/// of the wrapper abstraction in benchmark tests. Another drawback is
/// that the wrapper interfaces don't provide all features of ASIO
/// (at least for the moment).  We should also re-evaluate the
/// maintenance overhead of providing necessary wrappers as we develop
/// more.
///
/// On the other hand, we may be able to exploit the wrapper approach to
/// simplify the interfaces (by limiting the usage) and unify performance
/// optimization points.
///
/// As for optimization, we may want to provide a custom allocator for
/// the placeholder of callback handlers:
/// http://think-async.com/Asio/asio-1.3.1/doc/asio/reference/asio_handler_allocate.html

#endif // ASIOLINK_H
