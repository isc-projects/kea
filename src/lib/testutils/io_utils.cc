// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <testutils/io_utils.h>
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>

namespace isc {
namespace dhcp {
namespace test {

bool fileExists(const std::string& file_path) {
    std::ifstream fs(file_path.c_str());
    const bool file_exists = fs.good();
    fs.close();
    return (file_exists);
}

std::string readFile(const std::string& file_path) {
    std::ifstream ifs;
    ifs.open(file_path.c_str(), std::ifstream::in);
    if (!ifs.good()) {
        return (std::string());
    }
    std::string buf;
    std::ostringstream output;
    while (!ifs.eof() && ifs.good()) {
        ifs >> buf;
        output << buf;
    }
    ifs.close();

    return (output.str());
}

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

