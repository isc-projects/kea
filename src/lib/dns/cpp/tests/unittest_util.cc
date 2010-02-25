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

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

#include <gtest/gtest.h>

#include <dns/name.h>
#include "unittest_util.h"

using isc::UnitTestUtil;
using isc::dns::NameComparisonResult;

void
UnitTestUtil::readWireData(const char* datafile,
                           std::vector<unsigned char>& data)
{
    std::ifstream ifs;
 
    ifs.open(datafile, std::ios_base::in);
    if ((ifs.rdstate() & std::istream::failbit) != 0) {
        throw std::runtime_error("failed to open data file: " +
                                 std::string(datafile));
    }

    data.clear();

    std::string s;
    while (getline(ifs, s), !ifs.eof()) {
        if (ifs.bad() || ifs.fail()) {
            throw std::runtime_error("unexpected data line");
        }
        if (s.empty() || s[0] == '#') {
            continue;
        }

        readWireData(s, data);
    }
}

void
UnitTestUtil::readWireData(const std::string& datastr,
                           std::vector<unsigned char>& data)
{
    std::istringstream iss(datastr);

    do {
        std::string bytes;
        iss >> bytes;
        if (iss.bad() || iss.fail() || (bytes.size() % 2) != 0) {
            throw std::runtime_error("unexpected input or I/O error");
        }

        for (int pos = 0; pos < bytes.size(); pos += 2) {
            unsigned int ch;
            std::istringstream(bytes.substr(pos, 2)) >> std::hex >> ch;
            data.push_back(static_cast<unsigned char>(ch));
        }
    } while (!iss.eof());
}

::testing::AssertionResult
UnitTestUtil::matchWireData(const char* dataexp1, const char* lenexp1,
                            const char* dataexp2, const char* lenexp2,
                            const void* data1, size_t len1,
                            const void* data2, size_t len2)
{
    ::testing::Message msg;
    size_t cmplen = std::min(len1, len2);

    for (int i = 0; i < cmplen; i++) {
        int ch1 = static_cast<const uint8_t*>(data1)[i];
        int ch2 = static_cast<const uint8_t*>(data2)[i];
        if (ch1 != ch2) {
            msg << "Wire data mismatch at " << i << "th byte\n"
                << "  Actual: " << ch1 << "\n"
                << "Expected: " << ch2 << "\n";
            return (::testing::AssertionFailure(msg));
        }
    }
    if (len1 != len2) {
        msg << "Wire data mismatch in length:\n"
            << "  Actual: " << len1 << "\n"
            << "Expected: " << len2 << "\n";
        return (::testing::AssertionFailure(msg));
    }
    return ::testing::AssertionSuccess();
}

::testing::AssertionResult
UnitTestUtil::matchName(const char* nameexp1, const char* nameexp2,
                        const isc::dns::Name& name1,
                        const isc::dns::Name& name2)
{
    ::testing::Message msg;

    NameComparisonResult cmpresult = name1.compare(name2);
    if (cmpresult.getOrder() != 0 ||
        cmpresult.getRelation() != NameComparisonResult::EQUAL) {
        msg << "Two names are expected to be equal but not:\n"
            << "  One: " << name1 << "\n"
            << "Other: " << name2 << "\n";
        return (::testing::AssertionFailure(msg));
    }
    return ::testing::AssertionSuccess();
}
