// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
