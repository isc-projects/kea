// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
