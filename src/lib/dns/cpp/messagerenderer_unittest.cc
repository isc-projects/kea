// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <vector>

#include "buffer.h"
#include "name.h"
#include "messagerenderer.h"

#include "unittest_util.h"

#include <gtest/gtest.h>

using isc::UnitTestUtil;
using isc::dns::OutputBuffer;
using isc::dns::Name;
using isc::dns::MessageRenderer;

namespace {
class MessageRendererTest : public ::testing::Test {
protected:
    MessageRendererTest() : buffer(0), renderer(buffer) {}
    OutputBuffer buffer;
    MessageRenderer renderer;
    std::vector<unsigned char> data;
};

TEST_F(MessageRendererTest, toWire)
{
    UnitTestUtil::readWireData("testdata/name_toWire1", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."));
    renderer.writeName(Name("a.example.org."));
    EXPECT_EQ(true, buffer.getLength() == data.size() &&
              memcmp(buffer.getData(), &data[0], data.size()) == 0);
}

TEST_F(MessageRendererTest, toWireInLargeBuffer)
{
    size_t offset = 0x3fff;
    buffer.skip(offset);

    UnitTestUtil::readWireData("testdata/name_toWire2", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."));
    EXPECT_EQ(true, buffer.getLength() == data.size() + offset &&
              memcmp(static_cast<const uint8_t*>(buffer.getData()) + offset,
                     &data[0], data.size()) == 0);
}

TEST_F(MessageRendererTest, toWireTBD)
{
    UnitTestUtil::readWireData("testdata/name_toWire3", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."), false);
    renderer.writeName(Name("b.example.com."));
    EXPECT_EQ(true, buffer.getLength() == data.size() &&
              memcmp(buffer.getData(), &data[0], data.size()) == 0);
}
}
