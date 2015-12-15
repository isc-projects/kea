// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/daemon.h>
#include <dhcpsrv/logging.h>
#include <log/logger_support.h>

#include <gtest/gtest.h>

#include <sys/wait.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;

namespace isc {
namespace dhcp {

// @brief Derived Daemon class
class DaemonImpl : public Daemon {
public:
    static std::string getVersion(bool extended);

    using Daemon::makePIDFileName;
};

std::string DaemonImpl::getVersion(bool extended) {
    if (extended) {
        return (std::string("EXTENDED"));
    } else {
        return (std::string("BASIC"));
    }
}

};
};

namespace {

/// @brief Daemon Test test fixture class
class DaemonTest : public ::testing::Test {
public:
    /// @brief Constructor
    DaemonTest() : env_copy_() {
        // Take a copy of KEA_PIDFILE_DIR environment variable value
        char *env_value = getenv("KEA_PIDFILE_DIR");
        if (env_value) {
            env_copy_ = std::string(env_value);
        }
    }

    /// @brief Destructor
    ///
    /// As some of the tests have the side-effect of altering the logging
    /// settings (when configureLogger is called), the logging is reset to
    /// the default after each test completes.
    ~DaemonTest() {
        isc::log::setDefaultLoggingOutput();
        // Restore KEA_PIDFILE_DIR environment variable value
        if (env_copy_.empty()) {
            static_cast<void>(unsetenv("KEA_PIDFILE_DIR"));
        } else {
            static_cast<void>(setenv("KEA_PIDFILE_DIR", env_copy_.c_str(), 1));
        }
    }

private:
    /// @brief copy of KEA_PIDFILE_DIR environment variable value
    std::string env_copy_;
};


// Very simple test. Checks whether Daemon can be instantiated and its
// default parameters are sane
TEST_F(DaemonTest, constructor) {
    // Disable KEA_PIDFILE_DIR
    EXPECT_EQ(0, unsetenv("KEA_PIDFILE_DIR"));

    EXPECT_NO_THROW(Daemon instance1);

    // Check that the verbose mode is not set by default.
    Daemon instance2;
    EXPECT_FALSE(instance2.getVerbose());

    EXPECT_TRUE(instance2.getConfigFile().empty());
    EXPECT_TRUE(instance2.getProcName().empty());
    EXPECT_EQ(CfgMgr::instance().getDataDir(),instance2.getPIDFileDir());
    EXPECT_TRUE(instance2.getPIDFileName().empty());
}

// Verify config file accessors
TEST_F(DaemonTest, getSetConfigFile) {
    Daemon instance;

    EXPECT_NO_THROW(instance.setConfigFile("test.txt"));
    EXPECT_EQ("test.txt", instance.getConfigFile());
}

// Verify process name accessors
TEST_F(DaemonTest, getSetProcName) {
    Daemon instance;

    EXPECT_NO_THROW(instance.setProcName("myproc"));
    EXPECT_EQ("myproc", instance.getProcName());
}

// Verify PID file directory name accessors
TEST_F(DaemonTest, getSetPIDFileDir) {
    Daemon instance;

    EXPECT_NO_THROW(instance.setPIDFileDir("/tmp"));
    EXPECT_EQ("/tmp", instance.getPIDFileDir());
}

// Verify PID file name accessors.
TEST_F(DaemonTest, setPIDFileName) {
    Daemon instance;

    // Verify that PID file name may not be set to empty
    EXPECT_THROW(instance.setPIDFileName(""), BadValue);

    EXPECT_NO_THROW(instance.setPIDFileName("myproc"));
    EXPECT_EQ("myproc", instance.getPIDFileName());

    // Verify that setPIDFileName cannot be called twice on the same instance.
    EXPECT_THROW(instance.setPIDFileName("again"), InvalidOperation);
}

// Test the getVersion() redefinition
TEST_F(DaemonTest, getVersion) {
    EXPECT_THROW(Daemon::getVersion(false), NotImplemented);

    ASSERT_NO_THROW(DaemonImpl::getVersion(false));

    EXPECT_EQ(DaemonImpl::getVersion(false), "BASIC");

    ASSERT_NO_THROW(DaemonImpl::getVersion(true));

    EXPECT_EQ(DaemonImpl::getVersion(true), "EXTENDED");
}

// Verify makePIDFileName method
TEST_F(DaemonTest, makePIDFileName) {
    DaemonImpl instance;

    // Verify that config file cannot be blank
    instance.setProcName("notblank");
    EXPECT_THROW(instance.makePIDFileName(), InvalidOperation);

    // Verify that proc name cannot be blank
    instance.setProcName("");
    instance.setConfigFile("notblank");
    EXPECT_THROW(instance.makePIDFileName(), InvalidOperation);

    // Verify that config file must contain a file name
    instance.setProcName("myproc");
    instance.setConfigFile(".txt");
    EXPECT_THROW(instance.makePIDFileName(), BadValue);
    instance.setConfigFile("/tmp/");
    EXPECT_THROW(instance.makePIDFileName(), BadValue);

    // Given a valid config file name and proc name we should good to go
    instance.setConfigFile("/tmp/test.conf");
    std::string name;
    EXPECT_NO_THROW(name = instance.makePIDFileName());

    // Make sure the name is as we expect
    std::ostringstream stream;
    stream  << instance.getPIDFileDir() << "/test.myproc.pid";
    EXPECT_EQ(stream.str(), name);

    // Verify that the default directory can be overridden
    instance.setPIDFileDir("/tmp");
    EXPECT_NO_THROW(name = instance.makePIDFileName());
    EXPECT_EQ("/tmp/test.myproc.pid", name);
}

// Verifies the creation a PID file and that a pre-existing PID file
// which points to a live PID causes a throw.
TEST_F(DaemonTest, createPIDFile) {
    DaemonImpl instance;

    instance.setConfigFile("test.conf");
    instance.setProcName("daemon_test");
    instance.setPIDFileDir(TEST_DATA_BUILDDIR);

    EXPECT_NO_THROW(instance.createPIDFile());

    std::ostringstream stream;
    stream  << TEST_DATA_BUILDDIR << "/test.daemon_test.pid";
    EXPECT_EQ(stream.str(), instance.getPIDFileName());

    // If we try again, we should see our own PID file and fail
    EXPECT_THROW(instance.createPIDFile(), DaemonPIDExists);
}

// Verifies that a pre-existing PID file which points to a dead PID
// is overwritten.
TEST_F(DaemonTest, createPIDFileOverwrite) {
    DaemonImpl instance;

    // We're going to use fork to generate a PID we KNOW is dead.
    int pid = fork();
    ASSERT_GE(pid, 0);

    if (pid == 0) {
        // This is the child, die right away. Tragic, no?
        exit (0);
    }

    // Back in the parent test, we need to wait for the child to die
    // As with debugging waitpid() can be interrupted ignore EINTR.
    int stat;
    int ret;
    do {
        ret = waitpid(pid, &stat, 0);
    } while ((ret == -1) && (errno == EINTR));
    ASSERT_EQ(ret, pid);

    // Ok, so we should now have a PID that we know to be dead.
    // Let's use it to create a PID file.
    instance.setConfigFile("test.conf");
    instance.setProcName("daemon_test");
    instance.setPIDFileDir(TEST_DATA_BUILDDIR);
    EXPECT_NO_THROW(instance.createPIDFile(pid));

    // If we try to create the PID file again, this should work.
    EXPECT_NO_THROW(instance.createPIDFile());
}

// Verifies that Daemon destruction deletes the PID file
TEST_F(DaemonTest, PIDFileCleanup) {
    boost::shared_ptr<DaemonImpl> instance;
    instance.reset(new DaemonImpl);

    instance->setConfigFile("test.conf");
    instance->setProcName("daemon_test");
    instance->setPIDFileDir(TEST_DATA_BUILDDIR);
    EXPECT_NO_THROW(instance->createPIDFile());

    // If we try again, we should see our own PID file
    EXPECT_THROW(instance->createPIDFile(), DaemonPIDExists);

    // Save the pid file name
    std::string pid_file_name = instance->getPIDFileName();

    // Now delete the Daemon instance.  This should remove the
    // PID file.
    instance.reset();

    struct stat stat_buf;
    ASSERT_EQ(-1, stat(pid_file_name.c_str(), &stat_buf));
    EXPECT_EQ(errno, ENOENT);
}

// Checks that configureLogger method is behaving properly.
// More dedicated tests are availablef for LogConfigParser class.
// See logger_unittest.cc
TEST_F(DaemonTest, parsingConsoleOutput) {
    CfgMgr::instance().setVerbose(false);

    // Storage - parsed configuration will be stored here
    SrvConfigPtr storage(new SrvConfig());

    const char* config_txt =
    "{ \"loggers\": ["
    "    {"
    "        \"name\": \"kea\","
    "        \"output_options\": ["
    "            {"
    "                \"output\": \"stdout\""
    "            }"
    "        ],"
    "        \"debuglevel\": 99,"
    "        \"severity\": \"DEBUG\""
    "    }"
    "]}";
    ConstElementPtr config = Element::fromJSON(config_txt);

    // Spawn a daemon and tell it to configure logger
    Daemon x;
    EXPECT_NO_THROW(x.configureLogger(config, storage));

    // The parsed configuration should be processed by the daemon and
    // stored in configuration storage.
    ASSERT_EQ(1, storage->getLoggingInfo().size());

    EXPECT_EQ("kea", storage->getLoggingInfo()[0].name_);
    EXPECT_EQ(99, storage->getLoggingInfo()[0].debuglevel_);
    EXPECT_EQ(isc::log::DEBUG, storage->getLoggingInfo()[0].severity_);

    ASSERT_EQ(1, storage->getLoggingInfo()[0].destinations_.size());
    EXPECT_EQ("stdout" , storage->getLoggingInfo()[0].destinations_[0].output_);
}



// More tests will appear here as we develop Daemon class.

};
