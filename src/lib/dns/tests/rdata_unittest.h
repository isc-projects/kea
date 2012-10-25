// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef RDATA_UNITTEST_H
#define RDATA_UNITTEST_H 1

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rdata.h>

#include <gtest/gtest.h>

using namespace isc::util;

namespace isc {
namespace dns {
namespace rdata {
class RdataTest : public ::testing::Test {
protected:
    RdataTest();
    static RdataPtr rdataFactoryFromFile(const RRType& rrtype,
                                         const RRClass& rrclass,
                                         const char* datafile,
                                         size_t position = 0);
    OutputBuffer obuffer;
    MessageRenderer renderer;
    /// This is an RDATA object of some "unknown" RR type so that it can be
    /// used to test the compare() method against a well-known RR type.
    RdataPtr rdata_nomatch;
};
}
}
}
#endif // RDATA_UNITTEST_H

// Local Variables: 
// mode: c++
// End: 
