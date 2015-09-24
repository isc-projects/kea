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


