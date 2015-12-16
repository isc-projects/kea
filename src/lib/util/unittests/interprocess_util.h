// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

namespace isc {
namespace util {
namespace unittests {
/// \brief A helper utility for a simple synchronization with another process.
///
/// It waits for incoming data on a given file descriptor up to 5 seconds
/// (arbitrary choice), read one byte data, and return it to the caller.
/// On any failure it returns 0xff (255), so the sender process should use
/// a different value to pass.
unsigned char parentReadState(int fd);
}
}
}

// Local Variables:
// mode: c++
// End:
