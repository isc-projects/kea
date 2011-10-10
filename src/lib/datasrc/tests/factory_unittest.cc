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

#include <boost/scoped_ptr.hpp>

#include <datasrc/factory.h>
#include <datasrc/data_source.h>
#include <datasrc/sqlite3_accessor.h>

#include <dns/rrclass.h>
#include <cc/data.h>

#include <gtest/gtest.h>

using namespace isc::datasrc;
using namespace isc::data;

std::string SQLITE_DBFILE_EXAMPLE_ORG = TEST_DATA_DIR "/example.org.sqlite3";

namespace {

TEST(FactoryTest, sqlite3ClientBadConfig) {
    // We start out by building the configuration data bit by bit,
    // testing each form of 'bad config', until we have a good one.
    // Then we do some very basic operation on the client (detailed
    // tests are left to the implementation-specific backends)
    ElementPtr config;
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config = Element::create("asdf");
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config = Element::createMap();
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config->set("class", ElementPtr());
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config->set("class", Element::create(1));
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config->set("class", Element::create("FOO"));
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config->set("class", Element::create("IN"));
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config->set("database_file", ElementPtr());
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config->set("database_file", Element::create(1));
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config->set("database_file", Element::create("/foo/bar/doesnotexist"));
    ASSERT_THROW(DataSourceClientContainer("sqlite3", config),
                 DataSourceError);

    config->set("database_file", Element::create(SQLITE_DBFILE_EXAMPLE_ORG));
    DataSourceClientContainer dsc("sqlite3", config);

    DataSourceClient::FindResult result1(
        dsc.getInstance().findZone(isc::dns::Name("example.org.")));
    ASSERT_EQ(result::SUCCESS, result1.code);

    DataSourceClient::FindResult result2(
        dsc.getInstance().findZone(isc::dns::Name("no.such.zone.")));
    ASSERT_EQ(result::NOTFOUND, result2.code);

    ZoneIteratorPtr iterator(dsc.getInstance().getIterator(
        isc::dns::Name("example.org.")));

    ZoneUpdaterPtr updater(dsc.getInstance().getUpdater(
        isc::dns::Name("example.org."), false));
}

TEST(FactoryTest, memoryClient) {
    // We start out by building the configuration data bit by bit,
    // testing each form of 'bad config', until we have a good one.
    // Then we do some very basic operation on the client (detailed
    // tests are left to the implementation-specific backends)
    ElementPtr config;
    ASSERT_THROW(DataSourceClientContainer client("memory", config),
                 DataSourceError);

    config = Element::create("asdf");
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config = Element::createMap();
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("type", ElementPtr());
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("type", Element::create(1));
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("type", Element::create("FOO"));
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("type", Element::create("memory"));
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("class", ElementPtr());
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("class", Element::create(1));
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("class", Element::create("FOO"));
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("class", Element::create("IN"));
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("zones", ElementPtr());
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("zones", Element::create(1));
    ASSERT_THROW(DataSourceClientContainer("memory", config),
                 DataSourceError);

    config->set("zones", Element::createList());
    DataSourceClientContainer dsc("memory", config);

    // Once it is able to load some zones, we should add a few tests
    // here to see that it does.
    DataSourceClient::FindResult result(
        dsc.getInstance().findZone(isc::dns::Name("no.such.zone.")));
    ASSERT_EQ(result::NOTFOUND, result.code);

    ASSERT_THROW(dsc.getInstance().getIterator(isc::dns::Name("example.org.")),
                 DataSourceError);

    ASSERT_THROW(dsc.getInstance().getUpdater(isc::dns::Name("no.such.zone."),
                                              false), isc::NotImplemented);
}

TEST(FactoryTest, badType) {
    ASSERT_THROW(DataSourceClientContainer("foo", ElementPtr()),
                                           DataSourceError);
}

} // end anonymous namespace

