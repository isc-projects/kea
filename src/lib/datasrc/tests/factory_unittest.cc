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

#include <datasrc/datasrc_config.h>
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

// note this helper only checks the error that is received up to the length
// of the expected string. It will always pass if you give it an empty
// expected_error
void
pathtestHelper(const std::string& file, const std::string& expected_error) {
    std::string error;
    try {
        DataSourceClientContainer(file, ElementPtr());
    } catch (const DataSourceLibraryError& dsle) {
        error = dsle.what();
    }
    ASSERT_LT(expected_error.size(), error.size());
    EXPECT_EQ(expected_error, error.substr(0, expected_error.size()));
}

TEST(FactoryTest, paths) {
    // Test whether the paths are made absolute if they are not,
    // by inspecting the error that is raised when they are wrong
    const std::string error("dlopen failed for ");
    // With the current implementation, we can safely assume this has
    // been set for this test (as the loader would otherwise also fail
    // unless the loadable backend library happens to be installed)
    const std::string builddir(getenv("B10_FROM_BUILD"));

    // Absolute and ending with .so should have no change
    pathtestHelper("/no_such_file.so", error + "/no_such_file.so");

    // If no ending in .so, it should get _ds.so
    pathtestHelper("/no_such_file", error + "/no_such_file_ds.so");

    // If not starting with /, path should be added. For this test that
    // means the build directory as set in B10_FROM_BUILD
    pathtestHelper("no_such_file.so", error + builddir +
                   "/src/lib/datasrc/.libs/no_such_file.so");
    pathtestHelper("no_such_file", error + builddir +
                   "/src/lib/datasrc/.libs/no_such_file_ds.so");

    // Some tests with '.so' in the name itself
    pathtestHelper("no_such_file.so.something", error + builddir +
                   "/src/lib/datasrc/.libs/no_such_file.so.something_ds.so");
    pathtestHelper("/no_such_file.so.something", error +
                   "/no_such_file.so.something_ds.so");
    pathtestHelper("/no_such_file.so.something.so", error +
                   "/no_such_file.so.something.so");
    pathtestHelper("/no_such_file.so.so", error +
                   "/no_such_file.so.so");
    pathtestHelper("no_such_file.so.something", error + builddir +
                   "/src/lib/datasrc/.libs/no_such_file.so.something_ds.so");

    // Temporarily unset B10_FROM_BUILD to see that BACKEND_LIBRARY_PATH
    // is used
    unsetenv("B10_FROM_BUILD");
    pathtestHelper("no_such_file.so", error + BACKEND_LIBRARY_PATH +
                   "no_such_file.so");
    // Put it back just in case
    setenv("B10_FROM_BUILD", builddir.c_str(), 1);

    // Test some bad input values
    ASSERT_THROW(DataSourceClientContainer("", ElementPtr()),
                 DataSourceLibraryError);
    ASSERT_THROW(DataSourceClientContainer(".so", ElementPtr()),
                 DataSourceLibraryError);
}

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

