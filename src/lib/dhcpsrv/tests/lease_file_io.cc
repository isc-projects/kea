// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcpsrv/tests/lease_file_io.h>
#include <fstream>
#include <sstream>

namespace isc {
namespace dhcp {
namespace test {

LeaseFileIO::LeaseFileIO(const std::string& filename, const bool recreate)
    : testfile_(filename), recreate_(recreate)  {
    if (recreate_) {
        removeFile();
    }
}

LeaseFileIO::~LeaseFileIO() {
    if (recreate_) {
        removeFile();
    }
}

bool
LeaseFileIO::exists() const {
    std::ifstream fs(testfile_.c_str());
    bool ok = fs.good();
    fs.close();
    return (ok);
}

std::string
LeaseFileIO::readFile() const {
    std::ifstream fs(testfile_.c_str());
    if (!fs.is_open()) {
        return ("");
    }
    std::string contents((std::istreambuf_iterator<char>(fs)),
                         std::istreambuf_iterator<char>());
    fs.close();
    return (contents);
}

void
LeaseFileIO::removeFile() const {
    static_cast<void>(remove(testfile_.c_str()));
}

void
LeaseFileIO::writeFile(const std::string& contents) const {
    std::ofstream fs(testfile_.c_str(), std::ofstream::out);
    if (fs.is_open()) {
        fs << contents;
        fs.close();
    }
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc

