// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/daemon.h>
#include <gtest/gtest.h>
#include <fstream>

using namespace isc;
using namespace isc::dhcp;

/// Temporary file name used in some tests
const char* TEMP_FILE="temp-file.json";

namespace {

/// @brief Test-friendly version of the daemon
///
/// This class exposes internal Daemon class methods.
class NakedDaemon: public Daemon {
public:

    using Daemon::readFile;
};

TEST(Daemon, readFile) {
    NakedDaemon x;

    const char* content = "Horse doesn't eat cucumber salad";

    // Write sample content to disk
    unlink(TEMP_FILE);
    std::ofstream write_me(TEMP_FILE);
    EXPECT_TRUE(write_me.is_open());
    write_me << content;
    write_me.close();

    // Check that the read content is correct
    EXPECT_EQ(std::string(content), x.readFile(TEMP_FILE));

    unlink(TEMP_FILE);
}

TEST(Daemon, readFileError) {
    NakedDaemon x;

    // Check that the read content is correct
    EXPECT_THROW(x.readFile("no-such-file.txt"), isc::InvalidOperation);

    unlink(TEMP_FILE);
}

};
