// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/exceptions.h>

#include <gtest/gtest.h>

namespace { // begin unnamed namespace

TEST(DNSExceptionsTest, checkExceptionsHierarchy) {
    EXPECT_NO_THROW({
        const isc::dns::Exception exception("", 0, "");
        const isc::Exception& exception_cast =
          dynamic_cast<const isc::Exception&>(exception);
        // to avoid compiler warning
        exception_cast.what();
    });

    EXPECT_NO_THROW({
        const isc::dns::DNSTextError exception("", 0, "");
        const isc::dns::Exception& exception_cast =
          dynamic_cast<const isc::dns::Exception&>(exception);
        // to avoid compiler warning
        exception_cast.what();
    });

    EXPECT_NO_THROW({
        const isc::dns::NameParserException exception("", 0, "");
        const isc::dns::DNSTextError& exception_cast =
          dynamic_cast<const isc::dns::DNSTextError&>(exception);
        // to avoid compiler warning
        exception_cast.what();
    });

    EXPECT_NO_THROW({
        const isc::dns::DNSMessageFORMERR exception("", 0, "");
        const isc::dns::DNSProtocolError& exception_cast =
          dynamic_cast<const isc::dns::DNSProtocolError&>(exception);
        const isc::dns::Exception& exception_cast2 =
          dynamic_cast<const isc::dns::Exception&>(exception);
        // to avoid compiler warning
        exception_cast.what();
        exception_cast2.what();
    });

    EXPECT_NO_THROW({
        const isc::dns::DNSMessageBADVERS exception("", 0, "");
        const isc::dns::DNSProtocolError& exception_cast =
          dynamic_cast<const isc::dns::DNSProtocolError&>(exception);
        const isc::dns::Exception& exception_cast2 =
          dynamic_cast<const isc::dns::Exception&>(exception);
        // to avoid compiler warning
        exception_cast.what();
        exception_cast2.what();
    });
}

} // end unnamed namespace
