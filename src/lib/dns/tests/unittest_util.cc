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

#include <config.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

#include <gtest/gtest.h>

#include <dns/name.h>
#include <dns/tests/unittest_util.h>

using namespace std;

using isc::UnitTestUtil;
using isc::dns::NameComparisonResult;

namespace {
class UnitTestUtilConfig {
private:
    // This is a singleton object and cannot be constructed explicitly.
    UnitTestUtilConfig() {}
    UnitTestUtilConfig(const UnitTestUtilConfig& source);
    ~UnitTestUtilConfig() {}
public:
    /// Return a singleton unit test configuration object.  On first invocation
    /// one will be constructed.
    static UnitTestUtilConfig& getConfig();

    /// A list of paths to wire data files.
    /// \c UnitTestUtil::readWireData() (first version)
    /// will search the directories in this list for the specified data file.
    std::vector<string> data_paths_;
};

UnitTestUtilConfig&
UnitTestUtilConfig::getConfig() {
    static UnitTestUtilConfig config;
    return (config);
}
}

void
UnitTestUtil::readWireData(const char* datafile, vector<unsigned char>& data) {
    ifstream ifs;

    const UnitTestUtilConfig& config = UnitTestUtilConfig::getConfig();
    vector<string>::const_iterator it = config.data_paths_.begin();
    for (; it != config.data_paths_.end(); ++it) {
        string data_path = *it;
        if (data_path.empty() || *data_path.rbegin() != '/') {
            data_path.push_back('/');
        }
        ifs.open((data_path + datafile).c_str(), ios_base::in);
        if ((ifs.rdstate() & istream::failbit) == 0) {
            break;
        }
    }

    if (it == config.data_paths_.end()) {
        throw runtime_error("failed to open data file in data paths: " +
                            string(datafile));
    }

    data.clear();

    string s;
    while (getline(ifs, s), !ifs.eof()) {
        if (ifs.bad() || ifs.fail()) {
            throw runtime_error("unexpected data line");
        }
        if (s.empty() || s[0] == '#') {
            continue;
        }

        readWireData(s, data);
    }
}

void
UnitTestUtil::addDataPath(const string& directory) {
    UnitTestUtilConfig::getConfig().data_paths_.push_back(directory);
}

void
UnitTestUtil::readWireData(const string& datastr,
                           vector<unsigned char>& data)
{
    istringstream iss(datastr);

    do {
        string bytes;
        iss >> bytes;
        if (iss.bad() || iss.fail() || (bytes.size() % 2) != 0) {
            ostringstream err_oss;
            err_oss << "unexpected input or I/O error in reading " <<
                datastr;
            throw runtime_error(err_oss.str());
        }

        for (int pos = 0; pos < bytes.size(); pos += 2) {
            istringstream iss_byte(bytes.substr(pos, 2));
            unsigned int ch;

            iss_byte >> hex >> ch;
            if (iss_byte.rdstate() != istream::eofbit) {
                ostringstream err_oss;
                err_oss << "invalid byte representation: " << iss_byte.str();
                throw runtime_error(err_oss.str());
            }
            data.push_back(static_cast<unsigned char>(ch));
        }
    } while (!iss.eof());
}

::testing::AssertionResult
UnitTestUtil::matchWireData(const char* dataexp1 UNUSED_PARAM,
                            const char* lenexp1 UNUSED_PARAM,
                            const char* dataexp2 UNUSED_PARAM,
                            const char* lenexp2 UNUSED_PARAM,
                            const void* data1, size_t len1,
                            const void* data2, size_t len2)
{
    ::testing::Message msg;
    size_t cmplen = min(len1, len2);

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
    return (::testing::AssertionSuccess());
}

::testing::AssertionResult
UnitTestUtil::matchName(const char* nameexp1 UNUSED_PARAM,
                        const char* nameexp2 UNUSED_PARAM,
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
    return (::testing::AssertionSuccess());
}
