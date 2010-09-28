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

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>

#include <dns/tests/unittest_util.h>

#include <gtest/gtest.h>

using isc::UnitTestUtil;
using isc::dns::OutputBuffer;
using isc::dns::Name;
using isc::dns::MessageRenderer;

namespace {
class MessageRendererTest : public ::testing::Test {
protected:
    MessageRendererTest() : expected_size(0), buffer(0), renderer(buffer)
    {
        data16 = (2 << 8) | 3;
        data32 = (4 << 24) | (5 << 16) | (6 << 8) | 7;
    }
    size_t expected_size;
    uint16_t data16;
    uint32_t data32;
    OutputBuffer buffer;
    MessageRenderer renderer;
    std::vector<unsigned char> data;
    static const uint8_t testdata[5];
};

const uint8_t MessageRendererTest::testdata[5] = {1, 2, 3, 4, 5};

// The test cases are borrowed from those for the OutputBuffer class.
TEST_F(MessageRendererTest, writeIntger) {
    renderer.writeUint16(data16);
    expected_size += sizeof(data16);

    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, renderer.getData(),
                        renderer.getLength(), &testdata[1], sizeof(data16));
}

TEST_F(MessageRendererTest, writeName) {
    UnitTestUtil::readWireData("name_toWire1", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."));
    renderer.writeName(Name("a.example.org."));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &data[0], data.size());
}

TEST_F(MessageRendererTest, writeNameInLargeBuffer) {
    size_t offset = 0x3fff;
    buffer.skip(offset);

    UnitTestUtil::readWireData("name_toWire2", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t*>(buffer.getData()) + offset,
                        buffer.getLength() - offset,
                        &data[0], data.size());
}

TEST_F(MessageRendererTest, writeNameWithUncompressed) {
    UnitTestUtil::readWireData("name_toWire3", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."), false);
    renderer.writeName(Name("b.example.com."));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &data[0], data.size());
}

TEST_F(MessageRendererTest, writeNamePointerChain) {
    UnitTestUtil::readWireData("name_toWire4", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."));
    renderer.writeName(Name("b.example.com."));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &data[0], data.size());
}

TEST_F(MessageRendererTest, compressMode) {
    // By default the render performs case insensitive compression.
    EXPECT_EQ(MessageRenderer::CASE_INSENSITIVE, renderer.getCompressMode());

    // The mode can be explicitly changed.
    renderer.setCompressMode(MessageRenderer::CASE_SENSITIVE);
    EXPECT_EQ(MessageRenderer::CASE_SENSITIVE, renderer.getCompressMode());
    renderer.setCompressMode(MessageRenderer::CASE_INSENSITIVE);
    EXPECT_EQ(MessageRenderer::CASE_INSENSITIVE, renderer.getCompressMode());

    // The clear() method resets the mode to the default.
    renderer.setCompressMode(MessageRenderer::CASE_SENSITIVE);
    renderer.clear();
    EXPECT_EQ(MessageRenderer::CASE_INSENSITIVE, renderer.getCompressMode());
}

TEST_F(MessageRendererTest, writeNameCaseCompress) {
    // By default MessageRenderer performs case insensitive compression.

    UnitTestUtil::readWireData("name_toWire1", data);
    renderer.writeName(Name("a.example.com."));
    // this should match the first name in terms of compression:
    renderer.writeName(Name("b.exAmple.CoM."));
    renderer.writeName(Name("a.example.org."));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &data[0], data.size());
}

TEST_F(MessageRendererTest, writeNameCaseSensitiveCompress) {
    // name compression in case sensitive manner.  See the data file
    // description for details.
    renderer.setCompressMode(MessageRenderer::CASE_SENSITIVE);
    UnitTestUtil::readWireData("name_toWire5.wire", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.eXample.com."));
    renderer.writeName(Name("c.eXample.com."));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &data[0], data.size());
}

TEST_F(MessageRendererTest, writeNameMixedCaseCompress) {
    renderer.setCompressMode(MessageRenderer::CASE_SENSITIVE);
    UnitTestUtil::readWireData("name_toWire6.wire", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.eXample.com."));

    // Change the compression mode in the middle of rendering.  This is an
    // unusual operation and is unlikely to happen in practice, but is still
    // allowed in this API.
    renderer.setCompressMode(MessageRenderer::CASE_INSENSITIVE);
    renderer.writeName(Name("c.b.EXAMPLE.com."));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &data[0], data.size());
}

TEST_F(MessageRendererTest, writeRootName) {
    // root name is special: it never causes compression or can (reasonably)
    // be a compression pointer.  So it makes sense to check this case
    // explicitly.
    Name example_name = Name("www.example.com");

    OutputBuffer expected(0);
    expected.writeUint8(0);     // root name
    example_name.toWire(expected);

    renderer.writeName(Name("."));
    renderer.writeName(example_name);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t*>(buffer.getData()),
                        buffer.getLength(),
                        static_cast<const uint8_t*>(expected.getData()),
                        expected.getLength());
}
}
