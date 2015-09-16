// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>

#include <util/unittests/testdata.h>

using namespace std;

namespace {
vector<string>&
getDataPaths() {
    static vector<string> data_path;
    return (data_path);
}
}

namespace isc {
namespace util {
namespace unittests {

void
addTestDataPath(const string& path) {
    getDataPaths().push_back(path);
}

void
openTestData(const char* const datafile, ifstream& ifs) {
    vector<string>::const_iterator it = getDataPaths().begin();
    for (; it != getDataPaths().end(); ++it) {
        string data_path = *it;
        if (data_path.empty() || *data_path.rbegin() != '/') {
            data_path.push_back('/');
        }
        ifs.open((data_path + datafile).c_str(), ios_base::in);
        if (!ifs.fail()) {
            return;
        }
    }

    throw runtime_error("failed to open data file in data paths: " +
                        string(datafile));
}

}
}
}
