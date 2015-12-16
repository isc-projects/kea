// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <gtest/gtest.h>

#include <netinet/in.h>

#include <boost/asio.hpp>
#include <asiolink/io_socket.h>

using namespace isc::asiolink;

TEST(IOSocketTest, dummySockets) {
    EXPECT_EQ(static_cast<short>(IPPROTO_UDP),
              IOSocket::getDummyUDPSocket().getProtocol());
    EXPECT_EQ(static_cast<short>(IPPROTO_TCP),
              IOSocket::getDummyTCPSocket().getProtocol());
    EXPECT_EQ(-1, IOSocket::getDummyUDPSocket().getNative());
    EXPECT_EQ(-1, IOSocket::getDummyTCPSocket().getNative());
}


