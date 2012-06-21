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
#include <boost/shared_ptr.hpp>

using namespace isc;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dns;
using namespace std;
using namespace boost;

namespace {

class DatasrcConfiguratorTest;

class FakeList {
public:
    void configure(const Element& configuration, bool allow_cache) {
        EXPECT_TRUE(allow_cache);
        conf_ = configuration.get(0)->get("type")->stringValue();
    }
    const string& getConf() const {
        return (conf_);
    }
private:
    string conf_;
};

typedef shared_ptr<FakeList> ListPtr;

// We use the test fixture as both parameters, this makes it possible
// to easily fake all needed methods and look that they were called.
typedef DataSourceConfiguratorGeneric<DatasrcConfiguratorTest,
        FakeList> Configurator;

class DatasrcConfiguratorTest : public ::testing::Test {
public:
    // These pretend to be the server
    ListPtr getClientList(const RRClass& rrclass) {
        log_ += "get " + rrclass.toText() + "\n";
        return (lists_[rrclass]);
    }
    void setClientList(const RRClass& rrclass, const ListPtr& list) {
        log_ += "set " + rrclass.toText() + " " + list->getConf() + "\n";
        lists_[rrclass] = list;
    }
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
    void doInInit() {
        const ElementPtr
            config(Element::fromJSON("{\"IN\": [{\"type\": \"xxx\"}]}"));
        session.addMessage(createCommand("config_update", config), "data_sources",
                           "*");
        mccs->checkCommand();
        // Check it called the correct things (check that there's no IN yet and
        // set a new one.
        EXPECT_EQ("get IN\nset IN xxx\n", log_);
    }
    FakeSession session;
    auto_ptr<ModuleCCSession> mccs;
    const string specfile;
    map<RRClass, ListPtr> lists_;
    string log_;
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

// Push there a configuration with a single list.
TEST_F(DatasrcConfiguratorTest, createList) {
    doInInit();
}

TEST_F(DatasrcConfiguratorTest, modifyList) {
    // First, initialize the list
    doInInit();
    // And now change the configuration of the list
    const ElementPtr
        config(Element::fromJSON("{\"IN\": [{\"type\": \"yyy\"}]}"));
    session.addMessage(createCommand("config_update", config), "data_sources",
                       "*");
    log_ = "";
    mccs->checkCommand();
    // This one does not set
    EXPECT_EQ("get IN\n", log_);
    // But this should contain the yyy configuration
    EXPECT_EQ("yyy", lists_[RRClass::IN()]->getConf());
}

// Check we can have multiple lists at once
TEST_F(DatasrcConfiguratorTest, multiple) {
    const ElementPtr
        config(Element::fromJSON("{\"IN\": [{\"type\": \"yyy\"}], "
                                 "\"CH\": [{\"type\": \"xxx\"}]}"));
    session.addMessage(createCommand("config_update", config), "data_sources",
                       "*");
    mccs->checkCommand();
    // This one does not set
    EXPECT_EQ("get CH\nset CH xxx\nget IN\nset IN yyy\n", log_);
    // We should have both there
    EXPECT_EQ("yyy", lists_[RRClass::IN()]->getConf());
    EXPECT_EQ("xxx", lists_[RRClass::CH()]->getConf());
    EXPECT_EQ(2, lists_.size());
}

}
