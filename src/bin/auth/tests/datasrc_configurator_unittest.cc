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

#include <auth/datasrc_configurator.h>

#include <config/tests/fake_session.h>
#include <config/ccsession.h>

#include <gtest/gtest.h>
#include <memory>

using namespace isc;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::data;
using namespace std;

namespace {

class DatasrcConfiguratorTest;

class FakeList {

};

// We use the test fixture as both parameters, this makes it possible
// to easily fake all needed methods and look that they were called.
typedef DataSourceConfiguratorGeneric<DatasrcConfiguratorTest,
        FakeList> Configurator;

class DatasrcConfiguratorTest : public ::testing::Test {
protected:
    DatasrcConfiguratorTest() :
        session(ElementPtr(new ListElement), ElementPtr(new ListElement),
                ElementPtr(new ListElement)),
        specfile(string(TEST_OWN_DATA_DIR) + "/spec.spec")
    {
        initSession();
    }
    void initSession() {
        session.getMessages()->add(createAnswer());
        mccs.reset(new ModuleCCSession(specfile, session, NULL, NULL, false,
                                       false));
    }
    void TearDown() {
        // Make sure no matter what we did, it is cleaned up.
        Configurator::deinit();
    }
    void init(const ElementPtr& config = ElementPtr()) {
        session.getMessages()->
            add(createAnswer(0,
                             moduleSpecFromFile(string(PLUGIN_DATA_PATH) +
                                                "/datasrc.spec").
                             getFullSpec()));
        if (config) {
            session.getMessages()->add(createAnswer(0, config));
        } else {
            session.getMessages()->
                add(createAnswer(0, ElementPtr(new MapElement)));
        }
        Configurator::init(mccs.get(), this);
    }
    void SetUp() {
        init();
    }
    FakeSession session;
    auto_ptr<ModuleCCSession> mccs;
    const string specfile;
};

// Check the initialization (and deinitialization)
TEST_F(DatasrcConfiguratorTest, initialization) {
    // It can't be initialized again
    EXPECT_THROW(init(), InvalidOperation);
    EXPECT_TRUE(session.haveSubscription("data_sources", "*"));
    // Deinitialize to make the tests reasonable
    Configurator::deinit();
    EXPECT_FALSE(session.haveSubscription("data_sources", "*"));
    // If one of them is NULL, it does not work
    EXPECT_THROW(Configurator::init(NULL, this), InvalidParameter);
    EXPECT_FALSE(session.haveSubscription("data_sources", "*"));
    EXPECT_THROW(Configurator::init(mccs.get(), NULL), InvalidParameter);
    EXPECT_FALSE(session.haveSubscription("data_sources", "*"));
    // But we can initialize it again now
    EXPECT_NO_THROW(init());
    EXPECT_TRUE(session.haveSubscription("data_sources", "*"));
}

}
