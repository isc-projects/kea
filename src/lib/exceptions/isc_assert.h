// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_ASSERT_H
#define ISC_ASSERT_H

#include <exceptions/exceptions.h>

namespace isc {

/// @brief Replacement for assert() that throws if the expression is false.
/// It exists because some of the original code has asserts and we prefer to
/// throw rather than crash the server or be compile out asserts.
#define isc_throw_assert(expr) \
{\
    if(!(static_cast<bool>(expr))) \
    {\
        isc_throw(isc::Unexpected, __FILE__ << ":" << __LINE__ << " (" << #expr << ") failed");\
    }\
}

}

#endif // ISC_ASSERT_H
