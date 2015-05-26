// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>

#include <cc/data.h>
#include <config/command_mgr.h>
#include <config/command_socket_factory.h>

using namespace isc::config;
using namespace isc::data;

// Test class for Command Manager
class CommandSocketFactoryTest : public ::testing::Test {
public:

    /// Default constructor
    CommandSocketFactoryTest() {
        unlink(SOCKET_NAME);
    }

    /// Default destructor
    ~CommandSocketFactoryTest() {
        unlink(SOCKET_NAME);
    }

    static const char* SOCKET_NAME;
};

const char* CommandSocketFactoryTest::SOCKET_NAME = "test-socket";

TEST_F(CommandSocketFactoryTest, unixCreate) {
    // Null pointer is obviously a bad idea.
    EXPECT_THROW(CommandSocketFactory::create(ConstElementPtr()),
                 isc::config::BadSocketInfo);

    // So is passing no parameters.
    ElementPtr socket_info = Element::createMap();
    EXPECT_THROW(CommandSocketFactory::create(socket_info),
                 isc::config::BadSocketInfo);

    // We don't support ipx sockets
    socket_info->set("socket-type", Element::create("ipx"));
    EXPECT_THROW(CommandSocketFactory::create(socket_info),
                 isc::config::BadSocketInfo);

    socket_info->set("socket-type", Element::create("unix"));
    EXPECT_THROW(CommandSocketFactory::create(socket_info),
                 isc::config::BadSocketInfo);

    socket_info->set("socket-name", Element::create(SOCKET_NAME));
    int fd;
    EXPECT_NO_THROW(fd = CommandSocketFactory::create(socket_info));
    EXPECT_NE(-1, fd);

    // It should be possible to close the socket.
    EXPECT_NO_THROW(CommandSocketFactory::close(fd, socket_info));
}
