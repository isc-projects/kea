// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ASIO_NO_WARNINGS_H
#define ASIO_NO_WARNINGS_H 1

// Boost ASIO defined an error category hierarchy without virtual destructors.
// As Kea is built with -Wnon-virtual-dtor this gives warnings on some headers
// where this warning is not disabled by boost.
// Note before Kea 1.7.1 these warnings were made invisible by -isystem but
// -isystem has unwanted and fatal effect on the include order.

#define GNU_CC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)

#if ((defined(__GNUC__) && (GNU_CC_VERSION >= 40600)) || defined(__clang__))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#include <boost/asio.hpp>
#pragma GCC diagnostic pop
#else
#include <boost/asio.hpp>
#endif

#endif // ASIO_NO_WARNINGS_H
