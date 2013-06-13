// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <datasrc/memory/zone_writer.h>
#include <datasrc/memory/zone_table_segment_local.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_data_loader.h>
#include <datasrc/memory/load_action.h>
#include <datasrc/memory/zone_table.h>
#include <datasrc/exceptions.h>
#include <datasrc/result.h>

#include <util/memory_segment_mapped.h>

#include <cc/data.h>

#include <dns/rrclass.h>
#include <dns/name.h>

#include <datasrc/tests/memory/memory_segment_mock.h>
#include <datasrc/tests/memory/zone_table_segment_mock.h>

#include <gtest/gtest.h>

#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>

#include <string>
#include <unistd.h>

using boost::scoped_ptr;
using boost::bind;
using isc::dns::RRClass;
using isc::dns::Name;
using isc::datasrc::ZoneLoaderException;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::memory::test;

namespace {

class TestException {};

class ZoneWriterTest : public ::testing::Test {
protected:
    ZoneWriterTest() :
        segment_(new ZoneTableSegmentMock(RRClass::IN(), mem_sgmt_)),
        writer_(new
            ZoneWriter(*segment_,
                       bind(&ZoneWriterTest::loadAction, this, _1),
                       Name("example.org"), RRClass::IN(), false)),
        load_called_(false),
        load_throw_(false),
        load_loader_throw_(false),
        load_null_(false),
        load_data_(false)
    {}
    virtual void TearDown() {
        // Release the writer
        writer_.reset();
    }
    MemorySegmentMock mem_sgmt_;
    scoped_ptr<ZoneTableSegmentMock> segment_;
    scoped_ptr<ZoneWriter> writer_;
    bool load_called_;
    bool load_throw_;
    bool load_loader_throw_;
    bool load_null_;
    bool load_data_;
public:
    ZoneData* loadAction(isc::util::MemorySegment& segment) {
        // Make sure it is the correct segment passed. We know the
        // exact instance, can compare pointers to them.
        EXPECT_EQ(&segment_->getMemorySegment(), &segment);
        // We got called
        load_called_ = true;
        if (load_throw_) {
            throw TestException();
        }
        if (load_loader_throw_) {
            isc_throw(ZoneLoaderException, "faked loader exception");
        }

        if (load_null_) {
            // Be nasty to the caller and return NULL, which is forbidden
            return (NULL);
        }
        ZoneData* data = ZoneData::create(segment, Name("example.org"));
        if (load_data_) {
            // Put something inside. The node itself should be enough for
            // the tests.
            ZoneNode* node(NULL);
            data->insertName(segment, Name("subdomain.example.org"), &node);
            EXPECT_NE(static_cast<ZoneNode*>(NULL), node);
        }
        return (data);
    }
};

class ReadOnlySegment : public ZoneTableSegmentMock {
public:
    ReadOnlySegment(const isc::dns::RRClass& rrclass,
                    isc::util::MemorySegment& mem_sgmt) :
        ZoneTableSegmentMock(rrclass, mem_sgmt)
    {}

    // Returns false indicating that the segment is not usable. We
    // override this too as ZoneTableSegment implementations may use it
    // internally.
    virtual bool isUsable() const {
        return (false);
    }

    // Returns false indicating it is a read-only segment. It is used in
    // the ZoneWriter tests.
    virtual bool isWritable() const {
        return (false);
    }
};

TEST_F(ZoneWriterTest, constructForReadOnlySegment) {
    MemorySegmentMock mem_sgmt;
    ReadOnlySegment ztable_segment(RRClass::IN(), mem_sgmt);
    EXPECT_THROW(ZoneWriter(ztable_segment,
                            bind(&ZoneWriterTest::loadAction, this, _1),
                            Name("example.org"), RRClass::IN(), false),
                 isc::InvalidOperation);
}

// We call it the way we are supposed to, check every callback is called in the
// right moment.
TEST_F(ZoneWriterTest, correctCall) {
    // Nothing called before we call it
    EXPECT_FALSE(load_called_);

    // Just the load gets called now
    EXPECT_NO_THROW(writer_->load());
    EXPECT_TRUE(load_called_);
    load_called_ = false;

    EXPECT_NO_THROW(writer_->install());
    EXPECT_FALSE(load_called_);

    // We don't check explicitly how this works, but call it to free memory. If
    // everything is freed should be checked inside the TearDown.
    EXPECT_NO_THROW(writer_->cleanup());
}

TEST_F(ZoneWriterTest, loadTwice) {
    // Load it the first time
    EXPECT_NO_THROW(writer_->load());
    EXPECT_TRUE(load_called_);
    load_called_ = false;

    // The second time, it should not be possible
    EXPECT_THROW(writer_->load(), isc::InvalidOperation);
    EXPECT_FALSE(load_called_);

    // The object should not be damaged, try installing and clearing now
    EXPECT_NO_THROW(writer_->install());
    EXPECT_FALSE(load_called_);

    // We don't check explicitly how this works, but call it to free memory. If
    // everything is freed should be checked inside the TearDown.
    EXPECT_NO_THROW(writer_->cleanup());
}

// Try loading after call to install and call to cleanup. Both is
// forbidden.
TEST_F(ZoneWriterTest, loadLater) {
    // Load first, so we can install
    EXPECT_NO_THROW(writer_->load());
    EXPECT_NO_THROW(writer_->install());
    // Reset so we see nothing is called now
    load_called_ = false;

    EXPECT_THROW(writer_->load(), isc::InvalidOperation);
    EXPECT_FALSE(load_called_);

    // Cleanup and try loading again. Still shouldn't work.
    EXPECT_NO_THROW(writer_->cleanup());

    EXPECT_THROW(writer_->load(), isc::InvalidOperation);
    EXPECT_FALSE(load_called_);
}

// Try calling install at various bad times
TEST_F(ZoneWriterTest, invalidInstall) {
    // Nothing loaded yet
    EXPECT_THROW(writer_->install(), isc::InvalidOperation);
    EXPECT_FALSE(load_called_);

    EXPECT_NO_THROW(writer_->load());
    load_called_ = false;
    // This install is OK
    EXPECT_NO_THROW(writer_->install());
    // But we can't call it second time now
    EXPECT_THROW(writer_->install(), isc::InvalidOperation);
    EXPECT_FALSE(load_called_);
}

// We check we can clean without installing first and nothing bad
// happens. We also misuse the testcase to check we can't install
// after cleanup.
TEST_F(ZoneWriterTest, cleanWithoutInstall) {
    EXPECT_NO_THROW(writer_->load());
    EXPECT_NO_THROW(writer_->cleanup());

    EXPECT_TRUE(load_called_);

    // We cleaned up, no way to install now
    EXPECT_THROW(writer_->install(), isc::InvalidOperation);
}

// Test the case when load callback throws
TEST_F(ZoneWriterTest, loadThrows) {
    load_throw_ = true;
    EXPECT_THROW(writer_->load(), TestException);

    // We can't install now
    EXPECT_THROW(writer_->install(), isc::InvalidOperation);
    EXPECT_TRUE(load_called_);

    // But we can cleanup
    EXPECT_NO_THROW(writer_->cleanup());
}

// Emulate the situation where load() throws loader error.
TEST_F(ZoneWriterTest, loadLoaderException) {
    std::string error_msg;

    // By default, the exception is propagated.
    load_loader_throw_ = true;
    EXPECT_THROW(writer_->load(), ZoneLoaderException);
    // In this case, passed error_msg won't be updated.
    writer_.reset(new ZoneWriter(*segment_,
                                 bind(&ZoneWriterTest::loadAction, this, _1),
                                 Name("example.org"), RRClass::IN(), false));
    EXPECT_THROW(writer_->load(&error_msg), ZoneLoaderException);
    EXPECT_EQ("", error_msg);

    // If we specify allowing load error, load() will succeed and install()
    // adds an empty zone.  Note that we implicitly pass NULL to load()
    // as it's the default parameter, so the following also confirms it doesn't
    // cause disruption.
    writer_.reset(new ZoneWriter(*segment_,
                                 bind(&ZoneWriterTest::loadAction, this, _1),
                                 Name("example.org"), RRClass::IN(), true));
    writer_->load();
    writer_->install();
    writer_->cleanup();

    // Check an empty zone has been really installed.
    using namespace isc::datasrc::result;
    const ZoneTable* ztable = segment_->getHeader().getTable();
    ASSERT_TRUE(ztable);
    const ZoneTable::FindResult result = ztable->findZone(Name("example.org"));
    EXPECT_EQ(SUCCESS, result.code);
    EXPECT_EQ(ZONE_EMPTY, result.flags);

    // Allowing an error, and passing a template for the error message.
    // It will be filled with the reason for the error.
    writer_.reset(new ZoneWriter(*segment_,
                                 bind(&ZoneWriterTest::loadAction, this, _1),
                                 Name("example.org"), RRClass::IN(), true));
    writer_->load(&error_msg);
    EXPECT_NE("", error_msg);

    // In case of no error, the placeholder will be intact.
    load_loader_throw_ = false;
    error_msg.clear();
    writer_.reset(new ZoneWriter(*segment_,
                                 bind(&ZoneWriterTest::loadAction, this, _1),
                                 Name("example.org"), RRClass::IN(), true));
    writer_->load(&error_msg);
    EXPECT_EQ("", error_msg);
}

// Check the strong exception guarantee - if it throws, nothing happened
// to the content.
TEST_F(ZoneWriterTest, retry) {
    // First attempt fails due to some exception.
    load_throw_ = true;
    EXPECT_THROW(writer_->load(), TestException);
    // This one shall succeed.
    load_called_ = load_throw_ = false;
    // We want some data inside.
    load_data_ = true;
    EXPECT_NO_THROW(writer_->load());
    // And this one will fail again. But the old data will survive.
    load_data_ = false;
    EXPECT_THROW(writer_->load(), isc::InvalidOperation);

    // The rest still works correctly
    EXPECT_NO_THROW(writer_->install());
    ZoneTable* const table(segment_->getHeader().getTable());
    const ZoneTable::FindResult found(table->findZone(Name("example.org")));
    ASSERT_EQ(isc::datasrc::result::SUCCESS, found.code);
    // For some reason it doesn't seem to work by the ZoneNode typedef, using
    // the full definition instead. At least on some compilers.
    const isc::datasrc::memory::DomainTreeNode<RdataSet>* node;
    EXPECT_EQ(isc::datasrc::memory::DomainTree<RdataSet>::EXACTMATCH,
              found.zone_data->getZoneTree().
              find(Name("subdomain.example.org"), &node));
    EXPECT_NO_THROW(writer_->cleanup());
}

// Check the writer defends itsefl when load action returns NULL
TEST_F(ZoneWriterTest, loadNull) {
    load_null_ = true;
    EXPECT_THROW(writer_->load(), isc::InvalidOperation);

    // We can't install that
    EXPECT_THROW(writer_->install(), isc::InvalidOperation);

    // It should be possible to clean up safely
    EXPECT_NO_THROW(writer_->cleanup());
}

// Check the object cleans up in case we forget it.
TEST_F(ZoneWriterTest, autoCleanUp) {
    // Load data and forget about it. It should get released
    // when the writer itself is destroyed.
    EXPECT_NO_THROW(writer_->load());
}

// Used in the manyWrites test, encapsulating loadZoneData() to avoid
// its signature ambiguity.
ZoneData*
loadZoneDataWrapper(isc::util::MemorySegment& segment, const RRClass& rrclass,
                    const Name& name, const std::string& filename)
{
    return (loadZoneData(segment, rrclass, name, filename));
}

// Check the behavior of creating many small zones.  The main purpose of
// test is to trigger MemorySegmentGrown exception in ZoneWriter::install.
// There's no easy (if any) way to cause that reliably as it's highly
// dependent on details of the underlying boost implementation and probably
// also on the system behavior, but we'll try some promising scenario (it
// in fact triggered the intended result at least on one environment).
TEST_F(ZoneWriterTest, manyWrites) {
#ifdef USE_SHARED_MEMORY
    // First, make a fresh mapped file of a small size (so it'll be more likely
    // to grow in the test.
    const char* const mapped_file = TEST_DATA_BUILDDIR "/test.mapped";
    unlink(mapped_file);
    boost::scoped_ptr<isc::util::MemorySegmentMapped> segment(
        new isc::util::MemorySegmentMapped(
            mapped_file, isc::util::MemorySegmentMapped::CREATE_ONLY, 4096));
    segment.reset();

    // Then prepare a ZoneTableSegment of the 'mapped' type specifying the
    // file we just created.
    boost::scoped_ptr<ZoneTableSegment> zt_segment(
        ZoneTableSegment::create(RRClass::IN(), "mapped"));
    const isc::data::ConstElementPtr params =
        isc::data::Element::fromJSON(
            "{\"mapped-file\": \"" + std::string(mapped_file) + "\"}");
    zt_segment->reset(ZoneTableSegment::READ_WRITE, params);
#else
    // Do the same test for the local segment, although there shouldn't be
    // anything tricky in that case.
    boost::scoped_ptr<ZoneTableSegment> zt_segment(
        ZoneTableSegment::create(RRClass::IN(), "local"));
#endif

    // Now, create many small zones in the zone table with a ZoneWriter.
    // We use larger origin names so it'll (hopefully) require the memory
    // segment to grow while adding the name into the internal table.
    const size_t zone_count = 10000; // arbitrary choice
    for (size_t i = 0; i < zone_count; ++i) {
        const Name origin(
            boost::str(boost::format("%063u.%063u.%063u.example.org")
                       % i % i % i));
        const LoadAction action = boost::bind(loadZoneDataWrapper, _1,
                                              RRClass::IN(), origin,
                                              TEST_DATA_DIR
                                              "/template.zone");
        ZoneWriter writer(*zt_segment, action, origin, RRClass::IN(), false);
        writer.load();
        writer.install();
        writer.cleanup();

        // Confirm it's been successfully added and can be actually found.
        const ZoneTable::FindResult result =
            zt_segment->getHeader().getTable()->findZone(origin);
        EXPECT_EQ(isc::datasrc::result::SUCCESS, result.code);
        EXPECT_NE(static_cast<const ZoneData*>(NULL), result.zone_data) <<
            "unexpected find result: " + origin.toText();
    }

    // Make sure to close the segment before (possibly) removing the mapped
    // file.
    zt_segment.reset();

#ifdef USE_SHARED_MEMORY
    unlink(mapped_file);
#endif
}

}
