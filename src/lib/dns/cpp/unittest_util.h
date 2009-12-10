// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __UNITTEST_UTIL_H
#define __UNITTEST_UTIL_H 1

#include <vector>
#include <string>

namespace isc {

class UnitTestUtil {
public:
    ///
    /// read text format wire data from a file and put it to the given vector.
    ///
    static void readWireData(const char*datafile,
                             std::vector<unsigned char>& data);

    ///
    /// convert a sequence of hex strings into the corresponding list of
    /// 8-bit integers, and append them to the vector.
    ///
    static void readWireData(const std::string& datastr,
                             std::vector<unsigned char>& data);
};

}
#endif // __UNITTEST_UTIL_H

// Local Variables: 
// mode: c++
// End: 
