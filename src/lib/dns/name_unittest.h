/*
 * Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/* $Id$ */

#ifndef __NAME_UNITTEST_H
#define __NAME_UNITTEST_H 1

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class NameTest : public CppUnit::TestFixture {
public:
    void get_length();
    void to_text();
    //static CppUnit::Test* suite();

    CPPUNIT_TEST_SUITE(NameTest);
    CPPUNIT_TEST(get_length);
    CPPUNIT_TEST(to_text);
    CPPUNIT_TEST_SUITE_END();
};

#endif // __NAME_UNITTEST_H

// Local Variables: 
// mode: c++
// End: 
