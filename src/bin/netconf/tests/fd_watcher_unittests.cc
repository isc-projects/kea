// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <netconf/fd_watcher.h>
#include <yang/translator.h>
#include <yang/yang_models.h>
#include <asiolink/io_service.h>
#include <gtest/gtest.h>
#include <fcntl.h>

using namespace std;
using namespace isc;
using namespace isc::netconf;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::util::thread;

namespace {

/// @brief Test subscribe callback.
class TestCallback : public Callback {
public:
    /// @brief Module change callback.
    ///
    /// @param sess The running datastore session.
    /// @param module_name The module name.
    /// @param event The event.
    /// @param private_ctx The private context.
    /// @return the sysrepo return code.
    int module_change(S_Session sess,
                      const char* /*module_name*/,
                      sr_notif_event_t /*event*/,
                      void* /*private_ctx*/) {
        ++called;
        thread_id = pthread_self();
        return (SR_ERR_OK);
    }

    /// @brief Called counter.
    static size_t called;

    /// @brief Thread ID where the callback was run.
    static pthread_t thread_id;
};

pthread_t TestCallback::thread_id;
size_t TestCallback::called;

/// @brief Modify.
///
/// Used as a thread body to modify the configuration.
void
modify() {
    S_Connection conn(new Connection("modify thread"));
    S_Session sess(new Session(conn));

    // Set valid lifetime to 12345.
    string xpath = "/kea-dhcp4-server:config/valid-lifetime";
    ConstElementPtr elem = Element::create(12345);
    TranslatorBasic tb(sess);
    try {
        tb.setItem(xpath, elem, SR_UINT32_T);
    } catch (const std::exception& ex) {
        cerr << "setItem failed with: " << ex.what() << endl;
    }

    // Commit is so it becomes visible to subscriptions.
    try {
        sess->commit();
    } catch (const std::exception& ex) {
        cerr << "commit failed with: " << ex.what() << endl;
    }

    sess.reset();
    conn.reset();
}

// Verifies that before initialization file descriptor sets are empty.
TEST(FdWatcherTest, constructor) {
    FdWatcherPtr fw = FdWatcher::instance();
    ASSERT_TRUE(fw);
    EXPECT_EQ(0, fw->readFds.size());
    EXPECT_EQ(0, fw->writeFds.size());
    EXPECT_FALSE(fw->thread_);
}

// Verifies that init works as expected, e.g. there is one element in readFds.
TEST(FdWatcherTest, init) {
    FdWatcherPtr fw = FdWatcher::instance();
    ASSERT_TRUE(fw);
    IOServicePtr io_service(new IOService());
    ASSERT_TRUE(io_service);
    int ret = 0;
    EXPECT_NO_THROW(ret = fw->init(io_service));

    // Check the fd watcher.
    EXPECT_EQ(SR_ERR_OK, ret);
    EXPECT_EQ(1, fw->readFds.size());
    EXPECT_EQ(0, fw->writeFds.size());
    EXPECT_TRUE(fw->thread_);

    // init can be called twice.
    EXPECT_NO_THROW(ret = fw->init(io_service));
    EXPECT_EQ(SR_ERR_OK, ret);

    // Final cleanup (will go in a fixture class).
    fw->clear();
    io_service->stop();
    io_service.reset();
}

// Verifies that without the fd watcher a second thread handles subscriptions.
TEST(FdWatcherTest, subscribeThread) {
    pthread_t main_id = pthread_self();
    S_Connection conn(new Connection("testing main"));
    S_Session sess(new Session(conn));
    S_Subscribe subs(new Subscribe(sess));
    S_Callback cb(new TestCallback());
    string model = KEA_DHCP4_SERVER;

    // Check that a subscription opens file descriptors.
    int fd = open("/dev/null", O_RDONLY);
    close(fd);
    ASSERT_NO_THROW(subs->module_change_subscribe(model.c_str(), cb));
    int fd2 = open("/dev/null", O_RDONLY);
    close(fd2);
    EXPECT_LT(fd, fd2);

    // Modify the configuration in a thread.
    ThreadPtr th(new Thread(modify));
    th->wait();
    th.reset();
    subs.reset();
    sess.reset();
    conn.reset();

    // Check the subscribe callback is run in another thread.
    EXPECT_NE(main_id, TestCallback::thread_id);
}

// Verifies that with the fd watcher handles a subscription.
TEST(FdWatcherTest, subscribe) {
    FdWatcherPtr fw = FdWatcher::instance();
    ASSERT_TRUE(fw);
    IOServicePtr io_service(new IOService());
    ASSERT_TRUE(io_service);
    int ret = 0;
    ASSERT_NO_THROW(fw->init(io_service));
    ASSERT_EQ(SR_ERR_OK, ret);
    EXPECT_EQ(1, fw->readFds.size());
    EXPECT_EQ(0, fw->writeFds.size());
    EXPECT_TRUE(fw->thread_);

    // Get a session and subscribe to module changes.
    S_Connection conn(new Connection("testing main"));
    S_Session sess(new Session(conn));
    S_Subscribe subs(new Subscribe(sess));
    S_Callback cb(new TestCallback());
    string model = KEA_DHCP4_SERVER;
    ASSERT_NO_THROW(subs->module_change_subscribe(model.c_str(), cb));

    // Check some file descriptors were opened.
    io_service->poll();
    EXPECT_EQ(3, fw->readFds.size());
    EXPECT_EQ(0, fw->writeFds.size());

    // Reset subscription and check file descriptors are closed.
    subs.reset();
    io_service->poll();
    EXPECT_EQ(1, fw->readFds.size());

    // Cleanup.
    sess.reset();
    conn.reset();
    fw->clear();
    io_service->stop();
    io_service.reset();
}

// Verifies that with the fd watcher no second thread handles subscriptions.
TEST(FdWatcherTest, subscribeNoThread) {
    FdWatcherPtr fw = FdWatcher::instance();
    ASSERT_TRUE(fw);
    IOServicePtr io_service(new IOService());
    ASSERT_TRUE(io_service);
    int ret = 0;
    ASSERT_NO_THROW(fw->init(io_service));
    ASSERT_EQ(SR_ERR_OK, ret);
    EXPECT_EQ(1, fw->readFds.size());
    EXPECT_EQ(0, fw->writeFds.size());
    EXPECT_TRUE(fw->thread_);

    // Get a session and subscribe to module changes.
    pthread_t main_id = pthread_self();
    S_Connection conn(new Connection("testing main"));
    S_Session sess(new Session(conn));
    S_Subscribe subs(new Subscribe(sess));
    S_Callback cb(new TestCallback());
    string model = KEA_DHCP4_SERVER;
    ASSERT_NO_THROW(subs->module_change_subscribe(model.c_str(), cb));

    // Check some file descriptors were opened.
    io_service->poll();
    EXPECT_EQ(3, fw->readFds.size());
    EXPECT_EQ(0, fw->writeFds.size());

    // Modify the configuration in a thread.
    TestCallback::called = 0;
    ThreadPtr th(new Thread(modify));
    while (TestCallback::called == 0) {
        io_service->run_one();
    }
    io_service->poll();
    th->wait();
    th.reset();

    // Reset subscription and check file descriptors are closed.
    subs.reset();
    io_service->poll();
    EXPECT_EQ(1, fw->readFds.size());

    // Cleanup.
    sess.reset();
    conn.reset();
    fw->clear();
    io_service->stop();
    io_service.reset();

    // Check the subscribe callback is run in the Kea thread.
    EXPECT_EQ(main_id, TestCallback::thread_id);
}

// Verifies that with the fd watcher handles subscribe/unsubscribe sequence.
TEST(FdWatcherTest, unsubscribe) {
    FdWatcherPtr fw = FdWatcher::instance();
    ASSERT_TRUE(fw);
    IOServicePtr io_service(new IOService());
    ASSERT_TRUE(io_service);
    int ret = 0;
    ASSERT_NO_THROW(fw->init(io_service));
    ASSERT_EQ(SR_ERR_OK, ret);
    EXPECT_EQ(1, fw->readFds.size());
    EXPECT_EQ(0, fw->writeFds.size());
    EXPECT_TRUE(fw->thread_);

    // Get a session and subscribe to module changes.
    S_Connection conn(new Connection("testing main"));
    S_Session sess(new Session(conn));
    S_Subscribe subs1(new Subscribe(sess));
    S_Callback cb(new TestCallback());
    string model = KEA_DHCP4_SERVER;
    ASSERT_NO_THROW(subs1->module_change_subscribe(model.c_str(), cb));

    // Check some file descriptors were opened.
    io_service->poll();
    EXPECT_EQ(3, fw->readFds.size());
    EXPECT_EQ(0, fw->writeFds.size());

    // Reset subscription and check file descriptors are closed.
    subs1.reset();
    io_service->poll();
    EXPECT_EQ(1, fw->readFds.size());

    // Try again to subscribe.
    S_Subscribe subs2(new Subscribe(sess));
    ASSERT_NO_THROW(subs2->module_change_subscribe(model.c_str(), cb));
    io_service->poll();
    EXPECT_EQ(3, fw->readFds.size());
    EXPECT_EQ(0, fw->writeFds.size());

    // Unsubscribe.
    subs2.reset();
    io_service->poll();
    EXPECT_EQ(1, fw->readFds.size());

    // Cleanup.
    sess.reset();
    conn.reset();
    fw->clear();
    io_service->stop();
    io_service.reset();
}

}
