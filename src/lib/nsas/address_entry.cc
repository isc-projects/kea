// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id$

/// \file address_entry.cc
///
/// This file exists to define the single constant \c AddressEntry::UNREACHABLE,
/// equal to the value \c UINT32_MAX.
///
/// Ideally we could use \c UINT32_MAX directly in the header file, but this
/// constant is defined in \c stdint.h only if the macro \c __STDC_LIMIT_MACROS
/// is defined first. (This apparently is the C89 standard.)  Defining the
/// macro in \c address_entry.h before including \c stdint.h doesn't work as
/// it is possible that in a source file, \c stdint.h will be included before
/// \c address_entry.h.  In that case, the \c stdint.h include sentinel will
/// prevent \c stdint.h being included a second time and the value won't be
/// defined.
///
/// The easiest solution is the one presented here: declare the value as a
/// static class constant, and define it in this source file.  As we can control
/// the order of include files, this ensures that the value is defined.

#define __STDC_LIMIT_MACROS
#include <stdint.h>

#include "address_entry.h"

namespace isc {
namespace nsas {
const uint32_t AddressEntry::UNREACHABLE = UINT32_MAX;
}
}
