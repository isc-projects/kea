// Copyright (C) 2009, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>
#include <util/buffer.h>
#include <dns/name.h>
#include <dns/labelsequence.h>
#include <dns/messagerenderer.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>
#include <util/unittests/test_exceptions.h>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>

using isc::UnitTestUtil;
using isc::dns::Name;
using isc::dns::LabelSequence;
using isc::dns::MessageRenderer;
using isc::util::OutputBuffer;
using boost::lexical_cast;
using isc::util::unittests::matchWireData;

namespace {
class MessageRendererTest : public ::testing::Test {
protected:
    MessageRendererTest() : expected_size(0) {
        data16 = (2 << 8) | 3;
        data32 = (4 << 24) | (5 << 16) | (6 << 8) | 7;
    }
    size_t expected_size;
    uint16_t data16;
    uint32_t data32;
    MessageRenderer renderer;
    std::vector<unsigned char> data;
    static const uint8_t testdata[5];
};

const uint8_t MessageRendererTest::testdata[5] = {1, 2, 3, 4, 5};

// The test cases are borrowed from those for the OutputBuffer class.
TEST_F(MessageRendererTest, writeIntger) {
    renderer.writeUint16(data16);
    expected_size += sizeof(data16);

    matchWireData(&testdata[1], sizeof(data16),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageRendererTest, writeName) {
    UnitTestUtil::readWireData("name_toWire1", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."));
    renderer.writeName(Name("a.example.org."));
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageRendererTest, writeNameInLargeBuffer) {
    size_t offset = 0x3fff;
    renderer.skip(offset);

    UnitTestUtil::readWireData("name_toWire2", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."));
    matchWireData(&data[0], data.size(),
                  static_cast<const uint8_t*>(renderer.getData()) + offset,
                  renderer.getLength() - offset);
}

TEST_F(MessageRendererTest, writeNameWithUncompressed) {
    UnitTestUtil::readWireData("name_toWire3", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."), false);
    renderer.writeName(Name("b.example.com."));
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageRendererTest, writeNamePointerChain) {
    UnitTestUtil::readWireData("name_toWire4", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.example.com."));
    renderer.writeName(Name("b.example.com."));
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
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
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageRendererTest, writeNameCaseSensitiveCompress) {
    // name compression in case sensitive manner.  See the data file
    // description for details.
    renderer.setCompressMode(MessageRenderer::CASE_SENSITIVE);
    UnitTestUtil::readWireData("name_toWire5.wire", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.eXample.com."));
    renderer.writeName(Name("c.eXample.com."));
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageRendererTest, writeNameMixedCaseCompress) {
    renderer.setCompressMode(MessageRenderer::CASE_SENSITIVE);
    UnitTestUtil::readWireData("name_toWire6.wire", data);
    renderer.writeName(Name("a.example.com."));
    renderer.writeName(Name("b.eXample.com."));

    // Change the compression mode in the middle of rendering.  This is not
    // allowed in this implementation.
    EXPECT_THROW_WITH(renderer.setCompressMode(
                            MessageRenderer::CASE_INSENSITIVE),
                      isc::InvalidParameter,
                      "compress mode cannot be changed during rendering");

    // Once the renderer is cleared, it's okay again.
    renderer.clear();
    EXPECT_NO_THROW(renderer.setCompressMode(
                        MessageRenderer::CASE_INSENSITIVE));
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
    matchWireData(static_cast<const uint8_t*>(expected.getData()),
                  expected.getLength(),
                  static_cast<const uint8_t*>(renderer.getData()),
                  renderer.getLength());
}

TEST_F(MessageRendererTest, writeNameLabelSequence1) {
    UnitTestUtil::readWireData("name_toWire7", data);

    Name n1("a.example.com");
    LabelSequence ls1(n1);

    // a.example.com.
    renderer.writeName(ls1);

    ls1.stripLeft(1);

    // example.com.
    renderer.writeName(ls1);

    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageRendererTest, writeNameLabelSequence2) {
    UnitTestUtil::readWireData("name_toWire8", data);

    Name n1("a.example.com");
    LabelSequence ls1(n1);

    ls1.stripRight(1);

    // a.example.com (without root .)
    renderer.writeName(ls1);

    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageRendererTest, writeNameLabelSequence3) {
    UnitTestUtil::readWireData("name_toWire9", data);

    Name n1("a.example.com");
    LabelSequence ls1(n1);

    // a.example.com.
    renderer.writeName(ls1);

    ls1.stripRight(1);

    // a.example.com (without root .)
    renderer.writeName(ls1);

    ls1.stripRight(1);

    // a.example
    renderer.writeName(ls1);

    ls1.stripLeft(1);

    // example
    renderer.writeName(ls1);

    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageRendererTest, setBuffer) {
    OutputBuffer new_buffer(0);
    renderer.setBuffer(&new_buffer);
    EXPECT_EQ(0, new_buffer.getLength()); // the buffer should be still empty
    renderer.writeUint32(42);
    EXPECT_EQ(sizeof(uint32_t), new_buffer.getLength());
    EXPECT_EQ(sizeof(uint32_t), renderer.getLength());

    // Change some other internal state for the reset test below.
    EXPECT_EQ(512, renderer.getLengthLimit());
    renderer.setLengthLimit(4096);
    EXPECT_EQ(4096, renderer.getLengthLimit());

    // Reset the buffer to the default again.  Other internal states and
    // resources should be cleared.  The used buffer should be intact.
    renderer.setBuffer(NULL);
    EXPECT_EQ(sizeof(uint32_t), new_buffer.getLength());
    EXPECT_EQ(0, renderer.getLength());
    EXPECT_EQ(512, renderer.getLengthLimit());
}

TEST_F(MessageRendererTest, setBufferErrors) {
    OutputBuffer new_buffer(0);

    // Buffer cannot be reset when the renderer is in use.
    renderer.writeUint32(10);
    EXPECT_THROW_WITH(renderer.setBuffer(&new_buffer), isc::InvalidParameter,
                      "MessageRenderer buffer cannot be set when in use");

    renderer.clear();
    renderer.setBuffer(&new_buffer);
    renderer.writeUint32(10);
    EXPECT_THROW_WITH(renderer.setBuffer(&new_buffer), isc::InvalidParameter,
                      "MessageRenderer buffer cannot be set when in use");

    // Resetting the buffer isn't allowed for the default buffer.
    renderer.setBuffer(NULL);
    EXPECT_THROW_WITH(renderer.setBuffer(NULL), isc::InvalidParameter,
                      "Default MessageRenderer buffer cannot be reset");

    // It's okay to reset a temporary buffer without using it.
    renderer.setBuffer(&new_buffer);
    EXPECT_NO_THROW(renderer.setBuffer(NULL));
}

TEST_F(MessageRendererTest, manyRRs) {
    // Render a large number of names, and the confirm the resulting wire
    // data store the expected names in the correct order (1000 is an
    // arbitrary choice).
    for (size_t i = 0; i < 1000; ++i) {
        renderer.writeName(Name(lexical_cast<std::string>(i) + ".example"));
    }
    isc::util::InputBuffer b(renderer.getData(), renderer.getLength());
    for (size_t i = 0; i < 1000; ++i) {
        EXPECT_EQ(Name(lexical_cast<std::string>(i) + ".example"), Name(b));
    }
    // This will trigger trimming excessive hash items.  It shouldn't cause
    // any disruption.
    EXPECT_NO_THROW(renderer.clear());
}
}
