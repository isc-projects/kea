// Copyright (C) 2009-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UNITTEST_UTIL_H
#define UNITTEST_UTIL_H

#include <vector>
#include <string>

#include <dns/name.h>
#include <dns/message.h>

#include <gtest/gtest.h>

namespace isc {

class UnitTestUtil {
public:
    ///
    /// read text format wire data from a file and put it to the given vector.
    ///
    static void readWireData(const char* datafile,
                             std::vector<unsigned char>& data);

    ///
    /// add a path that \c readWireData() will search for test data files.
    ///
    static void addDataPath(const std::string& directory);

    ///
    /// convert a sequence of hex strings into the corresponding list of
    /// 8-bit integers, and append them to the vector.
    ///
    static void readWireData(const std::string& datastr,
                             std::vector<unsigned char>& data);

    ///
    /// Compare two names.
    ///
    /// This check method uses \c Name::compare() for comparison, which performs
    /// deeper checks including the equality of offsets, and should be better
    /// than EXPECT_EQ, which uses operator==.  Like the \c matchWireData()
    /// method, the usage is a bit awkward; the caller should use
    /// \c EXPECT_PRED_FORMAT2.
    ///
    static ::testing::AssertionResult
    matchName(const char* nameexp1, const char* nameexp2,
              const isc::dns::Name& name1, const isc::dns::Name& name2);
};

}
#endif // UNITTEST_UTIL_H
