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
#include <util/threads/lock.h>

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
    FakeList(const RRClass&) :
        configuration_(new ListElement)
    {}
    void configure(const ConstElementPtr& configuration, bool allow_cache) {
        EXPECT_TRUE(allow_cache);
        conf_ = configuration->get(0)->get("type")->stringValue();
        configuration_ = configuration;
    }
    const string& getConf() const {
        return (conf_);
    }
    ConstElementPtr getConfiguration() const {
        return (configuration_);
    }
private:
    string conf_;
    ConstElementPtr configuration_;
};

typedef shared_ptr<FakeList> ListPtr;

// We use the test fixture as both parameters, this makes it possible
// to easily fake all needed methods and look that they were called.
typedef DataSourceConfiguratorGeneric<DatasrcConfiguratorTest,
        FakeList> Configurator;

void
datasrcConfigHandler(const std::string&,
                     isc::data::ConstElementPtr config,
                     const isc::config::ConfigData&)
{
    if (config->contains("classes")) {
        Configurator::reconfigure(config->get("classes"));
    }
}

class DatasrcConfiguratorTest : public ::testing::Test {
public:
    // These pretend to be the server
    ListPtr getClientList(const RRClass& rrclass) {
        log_ += "get " + rrclass.toText() + "\n";
        return (lists_[rrclass]);
    }
    void setClientList(const RRClass& rrclass, const ListPtr& list) {
        log_ += "set " + rrclass.toText() + " " +
            (list ? list->getConf() : "") + "\n";
        lists_[rrclass] = list;
    }
    vector<RRClass> getClientListClasses() const {
        vector<RRClass> result;
        for (std::map<RRClass, ListPtr>::const_iterator it(lists_.begin());
             it != lists_.end(); ++it) {
            result.push_back(it->first);
        }
        return (result);
    }
    isc::util::thread::Mutex& getClientListMutex() const {
        return (mutex_);
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
        mccs->removeRemoteConfig("data_sources");
        Configurator::cleanup();
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
        Configurator::init(this);
        mccs->addRemoteConfig("data_sources", datasrcConfigHandler, false);
    }
    void SetUp() {
        init();
    }
    ElementPtr buildConfig(const string& config) const {
        const ElementPtr internal(Element::fromJSON(config));
        const ElementPtr external(Element::fromJSON("{\"version\": 1}"));
        external->set("classes", internal);
        return (external);
    }
    void initializeINList() {
        const ConstElementPtr
            config(buildConfig("{\"IN\": [{\"type\": \"xxx\"}]}"));
        session.addMessage(createCommand("config_update", config),
                           "data_sources", "*");
        mccs->checkCommand();
        // Check it called the correct things (check that there's no IN yet and
        // set a new one.
        EXPECT_EQ("get IN\nset IN xxx\n", log_);
        EXPECT_EQ(1, lists_.size());
    }
    FakeSession session;
    auto_ptr<ModuleCCSession> mccs;
    const string specfile;
    std::map<RRClass, ListPtr> lists_;
    string log_;
    mutable isc::util::thread::Mutex mutex_;
};

// Check the initialization (and cleanup)
TEST_F(DatasrcConfiguratorTest, initialization) {
    // It can't be initialized again
    EXPECT_THROW(init(), InvalidOperation);
    EXPECT_TRUE(session.haveSubscription("data_sources", "*"));
    // Deinitialize to make the tests reasonable
    mccs->removeRemoteConfig("data_sources");
    Configurator::cleanup();
    EXPECT_FALSE(session.haveSubscription("data_sources", "*"));
    // We can't reconfigure now (not even manually)
    EXPECT_THROW(Configurator::reconfigure(ElementPtr(new MapElement())),
                 InvalidOperation);
    // If the server param is NULL, it does not work
    EXPECT_THROW(Configurator::init(NULL), InvalidParameter);
    EXPECT_FALSE(session.haveSubscription("data_sources", "*"));
    // But we can initialize it again now
    EXPECT_NO_THROW(init());
    EXPECT_TRUE(session.haveSubscription("data_sources", "*"));
}

// Push there a configuration with a single list.
TEST_F(DatasrcConfiguratorTest, createList) {
    initializeINList();
}

TEST_F(DatasrcConfiguratorTest, modifyList) {
    // First, initialize the list
    initializeINList();
    // And now change the configuration of the list
    const ElementPtr
        config(buildConfig("{\"IN\": [{\"type\": \"yyy\"}]}"));
    session.addMessage(createCommand("config_update", config), "data_sources",
                       "*");
    log_ = "";
    mccs->checkCommand();
    // This one does not set
    EXPECT_EQ("get IN\n", log_);
    // But this should contain the yyy configuration
    EXPECT_EQ("yyy", lists_[RRClass::IN()]->getConf());
    EXPECT_EQ(1, lists_.size());
}

// Check we can have multiple lists at once
TEST_F(DatasrcConfiguratorTest, multiple) {
    const ElementPtr
        config(buildConfig("{\"IN\": [{\"type\": \"yyy\"}], "
                                 "\"CH\": [{\"type\": \"xxx\"}]}"));
    session.addMessage(createCommand("config_update", config), "data_sources",
                       "*");
    mccs->checkCommand();
    // We have set commands for both classes.
    EXPECT_EQ("get CH\nset CH xxx\nget IN\nset IN yyy\n", log_);
    // We should have both there
    EXPECT_EQ("yyy", lists_[RRClass::IN()]->getConf());
    EXPECT_EQ("xxx", lists_[RRClass::CH()]->getConf());
    EXPECT_EQ(2, lists_.size());
}

// Check we can add another one later and the old one does not get
// overwritten.
//
// It's almost like above, but we initialize first with single-list
// config.
TEST_F(DatasrcConfiguratorTest, updateAdd) {
    initializeINList();
    const ElementPtr
        config(buildConfig("{\"IN\": [{\"type\": \"yyy\"}], "
                           "\"CH\": [{\"type\": \"xxx\"}]}"));
    session.addMessage(createCommand("config_update", config), "data_sources",
                       "*");
    log_ = "";
    mccs->checkCommand();
    // The CH is set, IN not
    EXPECT_EQ("get CH\nset CH xxx\nget IN\n", log_);
    // But this should contain the yyy configuration
    EXPECT_EQ("xxx", lists_[RRClass::CH()]->getConf());
    EXPECT_EQ("yyy", lists_[RRClass::IN()]->getConf());
    EXPECT_EQ(2, lists_.size());
}

// We delete a class list in this test.
TEST_F(DatasrcConfiguratorTest, updateDelete) {
    initializeINList();
    const ElementPtr
        config(buildConfig("{}"));
    session.addMessage(createCommand("config_update", config), "data_sources",
                       "*");
    log_ = "";
    mccs->checkCommand();
    EXPECT_EQ("get IN\nset IN \n", log_);
    EXPECT_FALSE(lists_[RRClass::IN()]);
    // In real auth server, the NULL one would be removed. However, we just
    // store it, so the IN bucket is still in there. This checks there's nothing
    // else.
    EXPECT_EQ(1, lists_.size());
}

// Check that we can rollback an addition if something else fails
TEST_F(DatasrcConfiguratorTest, rollbackAddition) {
    initializeINList();
    // The configuration is wrong. However, the CH one will get done first.
    const ElementPtr
        config(buildConfig("{\"IN\": [{\"type\": 13}], "
                           "\"CH\": [{\"type\": \"xxx\"}]}"));
    session.addMessage(createCommand("config_update", config), "data_sources",
                       "*");
    log_ = "";
    // It does not throw, as it is handled in the ModuleCCSession.
    // Throwing from the reconfigure is checked in other tests.
    EXPECT_NO_THROW(mccs->checkCommand());
    // Anyway, the result should not contain CH now and the original IN should
    // be there.
    EXPECT_EQ("xxx", lists_[RRClass::IN()]->getConf());
    EXPECT_FALSE(lists_[RRClass::CH()]);
}

// Check that we can rollback a deletion if something else fails
TEST_F(DatasrcConfiguratorTest, rollbackDeletion) {
    initializeINList();
    // Put the CH there
    const ElementPtr
        config1(Element::fromJSON("{\"IN\": [{\"type\": \"yyy\"}], "
                                  "\"CH\": [{\"type\": \"xxx\"}]}"));
    Configurator::reconfigure(config1);
    const ElementPtr
        config2(Element::fromJSON("{\"IN\": [{\"type\": 13}]}"));
    // This would delete CH. However, the IN one fails.
    // As the deletions happen after the additions/settings
    // and there's no known way to cause an exception during the
    // deletions, it is not a true rollback, but the result should
    // be the same.
    EXPECT_THROW(Configurator::reconfigure(config2), TypeError);
    EXPECT_EQ("yyy", lists_[RRClass::IN()]->getConf());
    EXPECT_EQ("xxx", lists_[RRClass::CH()]->getConf());
}

// Check that we can roll back configuration change if something
// fails later on.
TEST_F(DatasrcConfiguratorTest, rollbackConfiguration) {
    initializeINList();
    // Put the CH there
    const ElementPtr
        config1(Element::fromJSON("{\"IN\": [{\"type\": \"yyy\"}], "
                                  "\"CH\": [{\"type\": \"xxx\"}]}"));
    Configurator::reconfigure(config1);
    // Now, the CH happens first. But nevertheless, it should be
    // restored to the previoeus version.
    const ElementPtr
        config2(Element::fromJSON("{\"IN\": [{\"type\": 13}], "
                                  "\"CH\": [{\"type\": \"yyy\"}]}"));
    EXPECT_THROW(Configurator::reconfigure(config2), TypeError);
    EXPECT_EQ("yyy", lists_[RRClass::IN()]->getConf());
    EXPECT_EQ("xxx", lists_[RRClass::CH()]->getConf());
}

}
