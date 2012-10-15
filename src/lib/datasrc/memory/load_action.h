// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LOAD_ACTION_H
#define LOAD_ACTION_H

#include <boost/function.hpp>

namespace isc {
// Forward declarations
namespace util{
class MemorySegment;
}
namespace datasrc {
namespace memory {
class ZoneData;

/// \brief Callback to load data into the memory
///
/// This callback should create new ZoneData (allocated from the passed
/// memory segment) and fill it with relevant loaded data. The caller
/// of the callback takes ownership of the ZoneData.
///
/// It must not return NULL.
typedef boost::function<ZoneData*(util::MemorySegment&)> LoadAction;

}
}
}

#endif
