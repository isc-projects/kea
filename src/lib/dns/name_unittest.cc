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

#include <string>

#include <cppunit/TestAssert.h>

#include <dns/name.h>
#include <dns/name_unittest.h>

using ISC::DNS::Name;

void
NameTest::get_length()
{
    Name name("www.example.cam");
            //01234567890123456 => length should be 17.

    CPPUNIT_ASSERT_EQUAL(17, static_cast<int>(name.get_length()));
}

void
NameTest::to_text()
{
    Name name("www.isc.org");

    CPPUNIT_ASSERT_EQUAL(std::string("www.isc.org"), name.to_text(true));
    CPPUNIT_ASSERT_EQUAL(std::string("www.isc.org."), name.to_text(false));
}
