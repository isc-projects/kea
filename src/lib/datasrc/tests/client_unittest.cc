// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <utility>

#include <datasrc/client.h>

#include <dns/name.h>

#include <gtest/gtest.h>

using namespace isc::datasrc;
using isc::dns::Name;

namespace {

/*
 * The DataSourceClient can't be created as it has pure virtual methods.
 * So we implement them as NOPs and test the other methods.
 */
class NopClient : public DataSourceClient {
public:
    virtual FindResult findZone(const isc::dns::Name&) const {
        return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
    }
    virtual ZoneUpdaterPtr getUpdater(const isc::dns::Name&, bool, bool)
        const
    {
        return (ZoneUpdaterPtr());
    }
    virtual std::pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
    getJournalReader(const isc::dns::Name&, uint32_t, uint32_t) const {
        isc_throw(isc::NotImplemented, "Journaling isn't supported "
                  "in Nop data source");
    }
};

class ClientTest : public ::testing::Test {
public:
    NopClient client_;
};

// The default implementation is NotImplemented
TEST_F(ClientTest, defaultIterator) {
    EXPECT_THROW(client_.getIterator(Name(".")), isc::NotImplemented);
}

TEST_F(ClientTest, defaultGetZoneCount) {
    EXPECT_THROW(client_.getZoneCount(), isc::NotImplemented);
}

TEST_F(ClientTest, defaultCreateZone) {
    EXPECT_THROW(client_.createZone(Name("example.com.")), isc::NotImplemented);
}

}
