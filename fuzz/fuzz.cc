// Copyright (C) 2024-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <log/logger_support.h>
#include <process/daemon.h>
#include <util/encode/encode.h>
#include <util/filesystem.h>

#include <cassert>
#include <cstdlib>
#include <string>

#include <fuzz.h>

using namespace isc::process;
using namespace isc::util::encode;
using namespace isc::util::file;
using namespace std;

string KEA_FUZZ_DIR() {
    static TemporaryDirectory TEMP_DIR = TemporaryDirectory();
    return TEMP_DIR.dirName();
}

extern "C" {

bool
DoInitialization() {
    LLVMFuzzerTearDown();

    // Spoof the logger just enough to not get LoggingNotInitialized thrown.
    // We explicitly don't want any logging during fuzzing for performance reasons.
    setenv("KEA_LOCKFILE_DIR", KEA_FUZZ_DIR().c_str(), 0);
    setenv("KEA_LFC_EXECUTABLE", "/bin/true", 0);
    if (!getenv("DEBUG")) {
        setenv("KEA_LOGGER_DESTINATION", "/dev/null", 0);
    }
    setenv("KEA_PIDFILE_DIR", KEA_FUZZ_DIR().c_str(), 0);
    if (!isc::log::isLoggingInitialized()) {
        isc::log::initLogger("fuzzer");
        Daemon::loggerInit("fuzzer", /* verbose = */ false);
        Daemon::setDefaultLoggerName("fuzzer");
    }

    return true;
}

void writeToFile(string const& file, string const& content) {
    // Create the config file.
    ofstream out(file, ios::out | ios::trunc);
    assert(out.is_open());
    out << content;
    out.close();
    assert(!out.is_open());
}

bool byteStreamToPacketData(uint8_t const* data, size_t size, vector<uint8_t>& byte_stream) {
    string str(data, data + size);
    if (!str.empty() && str.at(str.size() - 1) == '\n') {
        str = str.substr(0, str.size() - 1);
    }
    if (str.find_first_not_of("0123456789abcdefABCDEF") != string::npos) {
        return false;
    }
    if (str.size() % 2) {
        return false;
    }
    decodeHex(str, byte_stream);
    return true;
}

}  // extern "C"
