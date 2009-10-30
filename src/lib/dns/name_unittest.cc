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

#include <dns/exceptions.h>
#include <dns/buffer.h>
#include <dns/name.h>

#include <gtest/gtest.h>

namespace {

using isc::dns::Name;
using isc::dns::DNSLabelTooLong;

// The fixture for testing class Name.
class NameTest : public ::testing::Test {
protected:
    NameTest()
    {
        example_name =
            new isc::dns::Name("www.example.com");
                             //01234567890123456 => length should be 17.
    }
    virtual ~NameTest()
    {
        delete example_name;
    }

    isc::dns::Name *example_name;
};

TEST_F(NameTest, getLength)
{
    EXPECT_EQ(17, static_cast<int>(example_name->getLength()));
}

TEST_F(NameTest, toText)
{
    EXPECT_EQ(std::string("www.example.com"), example_name->toText(true));
    EXPECT_EQ(std::string("www.example.com."), example_name->toText(false));
}

TEST_F(NameTest, invalid_label)
{
    EXPECT_THROW(Name invalidlabel("012345678901234567890123456789"
                                   "0123456789012345678901234567890123456789"),
                 DNSLabelTooLong);
}

TEST_F(NameTest, equals)
{
    EXPECT_EQ(true, example_name->equals(Name("WWW.EXAMPLE.COM")));
    EXPECT_EQ(true, example_name->equals(Name("www.example.com.")));
}

TEST_F(NameTest, operator_equals)
{
    EXPECT_EQ(true, *example_name == Name("WWW.EXAMPLE.COM"));
    EXPECT_EQ(true, *example_name == Name("www.example.com."));
}

TEST_F(NameTest, toFromWire)
{
    isc::SingleBuffer buffer;
    isc::dns::NameCompressor compressor;
    isc::dns::NameDecompressor decompressor;

    example_name->toWire(buffer, compressor);
    buffer.setCurrent(0);
    EXPECT_EQ(std::string("www.example.com."),
              Name(buffer, decompressor).toText(false));
}
}
