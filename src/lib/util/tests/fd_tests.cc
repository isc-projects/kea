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

#include <config.h>

#include <util/unittests/check_valgrind.h>

#include <util/io/fd.h>

#include <util/unittests/fork.h>

#include <gtest/gtest.h>

using namespace isc::util::io;
using namespace isc::util::unittests;

namespace {

// Make sure the test is large enough and does not fit into one
// read or write request
const size_t TEST_DATA_SIZE = 8 * 1024 * 1024;

class FDTest : public ::testing::Test {
    public:
        unsigned char *data, *buffer;
        FDTest() :
            // We do not care what is inside, we just need it to be the same
            data(new unsigned char[TEST_DATA_SIZE]),
            buffer(NULL)
        {
            memset(data, 0, TEST_DATA_SIZE);
        }
        ~ FDTest() {
            delete[] data;
            delete[] buffer;
        }
};

// Test we read what was sent
TEST_F(FDTest, read) {
    if (!isc::util::unittests::runningOnValgrind()) {
        int read_pipe(0);
        buffer = new unsigned char[TEST_DATA_SIZE];
        pid_t feeder(provide_input(&read_pipe, data, TEST_DATA_SIZE));
        ASSERT_GE(feeder, 0);
        ssize_t received(read_data(read_pipe, buffer, TEST_DATA_SIZE));
        EXPECT_TRUE(process_ok(feeder));
        EXPECT_EQ(TEST_DATA_SIZE, received);
        EXPECT_EQ(0, memcmp(data, buffer, received));
    }
}

// Test we write the correct thing
TEST_F(FDTest, write) {
    if (!isc::util::unittests::runningOnValgrind()) {
        int write_pipe(0);
        pid_t checker(check_output(&write_pipe, data, TEST_DATA_SIZE));
        ASSERT_GE(checker, 0);
        EXPECT_TRUE(write_data(write_pipe, data, TEST_DATA_SIZE));
        EXPECT_EQ(0, close(write_pipe));
        EXPECT_TRUE(process_ok(checker));
    }
}

}
