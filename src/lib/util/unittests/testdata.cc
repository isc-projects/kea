// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
