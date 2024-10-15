// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <fuzz.h>

#include <log/logger_support.h>
#include <process/daemon.h>
#include <util/filesystem.h>
#include <util/encode/encode.h>

#include <cassert>
#include <string>

using namespace isc::process;
using namespace isc::util::encode;
using namespace isc::util::file;
using namespace std;

extern "C" {

string KEA_LFC = isFile(KEA_LFC_INSTALLATION) ? KEA_LFC_INSTALLATION : KEA_LFC_SOURCES;
// string KEA_FUZZ_DIR = isFile(KEA_FUZZ_DIR_INSTALLATION) ? KEA_FUZZ_DIR_INSTALLATION : KEA_FUZZ_DIR_SOURCES;
TemporaryDirectory TEMP_DIR = TemporaryDirectory();
string KEA_FUZZ_DIR = TEMP_DIR.dirName();

bool
DoInitialization() {
    LLVMFuzzerTearDown();

    // Spoof the logger just enough to not get LoggingNotInitialized thrown.
    // We explicitly don't want any logging during fuzzing for performance reasons.
    setenv("KEA_LOCKFILE_DIR", KEA_FUZZ_DIR.c_str(), 0);
    setenv("KEA_LFC_EXECUTABLE", "/bin/true", 0);
    if (!getenv("DEBUG")) {
        setenv("KEA_LOGGER_DESTINATION", "/dev/null", 0);
    }
    setenv("KEA_PIDFILE_DIR", KEA_FUZZ_DIR.c_str(), 0);
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
