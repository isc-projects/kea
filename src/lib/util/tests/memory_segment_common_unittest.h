// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/memory_segment.h>

namespace isc {
namespace util {
namespace test {

/// \brief Implementation dependent checks on memory segment named addresses.
///
/// This function contains a set of test cases for given memory segment
/// regarding "named address" methods.  The test cases basically only depend
/// on the base class interfaces, but if the underlying implementation does
/// not check if the given address to setNamedAddress() belongs to the segment,
/// out_of_segment_ok should be set to true.
void checkSegmentNamedAddress(MemorySegment& segment, bool out_of_segment_ok);

}
}
}

// Local Variables:
// mode: c++
// End:
