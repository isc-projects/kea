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

#include <datasrc/memory/zone_updater.h>
#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/zone_data.h>

#include <cc/data.h>
#include <dns/rrclass.h>
#include <dns/name.h>

#include <gtest/gtest.h>

#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>

using boost::scoped_ptr;
using boost::bind;
using isc::dns::RRClass;
using isc::dns::Name;
using namespace isc::datasrc::memory;

namespace {

class TestException {};

class ZoneUpdaterLocalTest : public ::testing::Test {
public:
    ZoneUpdaterLocalTest() :
        // FIXME: The NullElement probably isn't the best one, but we don't
        // know how the config will look, so it just fills the argument
        // (which is currently ignored)
        segment_(ZoneTableSegment::create(isc::data::NullElement())),
        updater_(new
            ZoneUpdaterLocal(segment_.get(),
                             bind(&ZoneUpdaterLocalTest::loadAction, this, _1),
                             bind(&ZoneUpdaterLocalTest::installAction, this,
                                  _1, _2),
                             Name("example.org"), RRClass::IN())),
        load_called_(false),
        install_called_(false),
        load_throw_(false),
        install_throw_(false)
    {}
    void TearDown() {
        // Release the updater
        updater_.reset();
        // And check we freed all memory
        EXPECT_TRUE(segment_->getMemorySegment().allMemoryDeallocated());
    }
protected:
    scoped_ptr<ZoneTableSegment> segment_;
    scoped_ptr<ZoneUpdaterLocal> updater_;
    bool load_called_;
    bool install_called_;
    bool load_throw_;
    bool install_throw_;
private:
    void loadAction(ZoneData* data) {
        // Make sure we get something.
        EXPECT_NE(static_cast<const ZoneData*>(NULL), data);
        // We got called
        load_called_ = true;
        if (load_throw_) {
            throw TestException();
        }
    }
    ZoneData* installAction(const ZoneSegmentID&, ZoneSegment* segment) {
        install_called_ = true;

        // Check we got something
        if (segment == NULL) {
            ADD_FAILURE() << "Zone segment is NULL in install action";
            return (NULL);
        }
        EXPECT_NE(static_cast<const ZoneData*>(NULL), segment->getZoneData());

        if (install_throw_) {
            // In case we throw, we do so before releasing the memory there,
            // as in that case we don't claim the ownership of the data.
            throw TestException();
        }

        // We received ownership of the parameters here. And we don't really need
        // them in the tests, so we just release them.
        ZoneData::destroy(segment_->getMemorySegment(), segment->getZoneData(),
                          RRClass::IN());
        delete segment;

        // And we are supposed to pass the old version back. So we create
        // new zone data and pass it.
        return (ZoneData::create(segment_->getMemorySegment(), Name("exmaple.org")));
    }
};

// We call it the way we are supposed to, check every callback is called in the
// right moment.
TEST_F(ZoneUpdaterLocalTest, correctCall) {
    // Nothing called before we call it
    EXPECT_FALSE(load_called_);
    EXPECT_FALSE(install_called_);

    // Just the load gets called now
    EXPECT_NO_THROW(updater_->load());
    EXPECT_TRUE(load_called_);
    EXPECT_FALSE(install_called_);
    load_called_ = false;

    EXPECT_NO_THROW(updater_->install());
    EXPECT_FALSE(load_called_);
    EXPECT_TRUE(install_called_);

    // We don't check explicitly how this works, but call it to free memory. If
    // everything is freed should be checked inside the TearDown.
    EXPECT_NO_THROW(updater_->cleanup());
}

TEST_F(ZoneUpdaterLocalTest, loadTwice) {
    // Load it the first time
    EXPECT_NO_THROW(updater_->load());
    EXPECT_TRUE(load_called_);
    EXPECT_FALSE(install_called_);
    load_called_ = false;

    // The second time, it should not be possible
    EXPECT_THROW(updater_->load(), isc::Unexpected);
    EXPECT_FALSE(load_called_);
    EXPECT_FALSE(install_called_);

    // The object should not be damaged, try installing and clearing now
    EXPECT_NO_THROW(updater_->install());
    EXPECT_FALSE(load_called_);
    EXPECT_TRUE(install_called_);

    // We don't check explicitly how this works, but call it to free memory. If
    // everything is freed should be checked inside the TearDown.
    EXPECT_NO_THROW(updater_->cleanup());
}

// Try loading after call to install and call to cleanup. Both is
// forbidden.
TEST_F(ZoneUpdaterLocalTest, loadLater) {
    // Load first, so we can install
    EXPECT_NO_THROW(updater_->load());
    EXPECT_NO_THROW(updater_->install());
    // Reset so we see nothing is called now
    install_called_ = load_called_ = false;

    EXPECT_THROW(updater_->load(), isc::Unexpected);
    EXPECT_FALSE(load_called_);
    EXPECT_FALSE(install_called_);

    // Cleanup and try loading again. Still shouldn't work.
    EXPECT_NO_THROW(updater_->cleanup());

    EXPECT_THROW(updater_->load(), isc::Unexpected);
    EXPECT_FALSE(load_called_);
    EXPECT_FALSE(install_called_);
}

// Try calling install at various bad times
TEST_F(ZoneUpdaterLocalTest, invalidInstall) {
    // Nothing loaded yet
    EXPECT_THROW(updater_->install(), isc::Unexpected);
    EXPECT_FALSE(load_called_);
    EXPECT_FALSE(install_called_);

    EXPECT_NO_THROW(updater_->load());
    load_called_ = false;
    // This install is OK
    EXPECT_NO_THROW(updater_->install());
    install_called_ = false;
    // But we can't call it second time now
    EXPECT_THROW(updater_->install(), isc::Unexpected);
    EXPECT_FALSE(load_called_);
    EXPECT_FALSE(install_called_);
}

// We check we can clean without installing first and nothing bad
// happens. We also misuse the testcase to check we can't install
// after cleanup.
TEST_F(ZoneUpdaterLocalTest, cleanWithoutInstall) {
    EXPECT_NO_THROW(updater_->load());
    EXPECT_NO_THROW(updater_->cleanup());

    EXPECT_TRUE(load_called_);
    EXPECT_FALSE(install_called_);

    // We cleaned up, no way to install now
    EXPECT_THROW(updater_->install(), isc::Unexpected);
    EXPECT_FALSE(install_called_);
}

// Test the case when load callback throws
TEST_F(ZoneUpdaterLocalTest, loadThrows) {
    load_throw_ = true;
    EXPECT_THROW(updater_->load(), TestException);

    // We can't install now
    EXPECT_THROW(updater_->install(), isc::Unexpected);
    EXPECT_TRUE(load_called_);
    EXPECT_FALSE(install_called_);

    // But we can cleanup
    EXPECT_NO_THROW(updater_->cleanup());
}

// Test we free all our memory even when we throw from install
TEST_F(ZoneUpdaterLocalTest, installThrows) {
    install_throw_ = true;
    EXPECT_NO_THROW(updater_->load());

    EXPECT_THROW(updater_->install(), TestException);
    EXPECT_TRUE(load_called_);
    EXPECT_TRUE(install_called_);

    // We can't try again
    install_throw_ = false;
    EXPECT_THROW(updater_->install(), isc::Unexpected);

    // But it is not completely broken
    EXPECT_NO_THROW(updater_->cleanup());
}

}
