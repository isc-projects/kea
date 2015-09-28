// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <boost/asio.hpp>
#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/timer_mgr.h>
#include <dhcpsrv/tests/lease_file_io.h>
#include <dhcpsrv/tests/test_utils.h>
#include <dhcpsrv/tests/generic_lease_mgr_unittest.h>
#include <util/pid_file.h>
#include <util/stopwatch.h>
#include <gtest/gtest.h>

#include <boost/bind.hpp>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;

namespace {

/// @brief Class derived from @c Memfile_LeaseMgr to test LFC timer.
///
/// This class provides a custom callback function which is invoked
/// when the timer for Lease File Cleanup goes off. It is used to
/// test that the timer is correctly installed.
class LFCMemfileLeaseMgr : public Memfile_LeaseMgr {
public:

    /// @brief Constructor.
    ///
    /// Sets the counter for callbacks to 0.
    LFCMemfileLeaseMgr(const ParameterMap& parameters)
        : Memfile_LeaseMgr(parameters), lfc_cnt_(0) {
    }

    /// @brief Returns the number of callback executions.
    int getLFCCount() {
        return (lfc_cnt_);
    }

protected:

    /// @brief Custom callback.
    ///
    /// This callback function increases the counter of callback executions.
    /// By examining the counter value a test may verify that the callback
    /// was triggered an expected number of times.
    virtual void lfcCallback() {
        ++lfc_cnt_;
    }

private:

    /// @brief Counter of callback function executions.
    int lfc_cnt_;

};

/// @brief A derivation of the lease manager exposing protected methods.
class NakedMemfileLeaseMgr : public Memfile_LeaseMgr {
public:

    /// @brief Constructor.
    ///
    /// Creates instance of the lease manager.
    NakedMemfileLeaseMgr(const ParameterMap& parameters)
        : Memfile_LeaseMgr(parameters) {
    }

    using Memfile_LeaseMgr::lfcCallback;
};

/// @brief Test fixture class for @c Memfile_LeaseMgr
class MemfileLeaseMgrTest : public GenericLeaseMgrTest {
public:

    /// @brief memfile lease mgr test constructor
    ///
    /// Creates memfile and stores it in lmptr_ pointer
    MemfileLeaseMgrTest() :
        io4_(getLeaseFilePath("leasefile4_0.csv")),
        io6_(getLeaseFilePath("leasefile6_0.csv")),
        timer_mgr_(TimerMgr::instance()) {

        std::ostringstream s;
        s << KEA_LFC_BUILD_DIR << "/kea-lfc";
        setenv("KEA_LFC_EXECUTABLE", s.str().c_str(), 1);

        // Remove lease files and products of Lease File Cleanup.
        removeFiles(getLeaseFilePath("leasefile4_0.csv"));
        removeFiles(getLeaseFilePath("leasefile6_0.csv"));
    }

    /// @brief Reopens the connection to the backend.
    ///
    /// This function is called by unit tests to force reconnection of the
    /// backend to check that the leases are stored and can be retrieved
    /// from the storage.
    ///
    /// @param u Universe (V4 or V6)
    virtual void reopen(Universe u) {
        LeaseMgrFactory::destroy();
        startBackend(u);
    }

    /// @brief destructor
    ///
    /// destroys lease manager backend.
    virtual ~MemfileLeaseMgrTest() {
        // Stop TimerMgr worker thread if it is running.
        timer_mgr_->stopThread();
        // Make sure there are no timers registered.
        timer_mgr_->unregisterTimers();
        LeaseMgrFactory::destroy();
        // Remove lease files and products of Lease File Cleanup.
        removeFiles(getLeaseFilePath("leasefile4_0.csv"));
        removeFiles(getLeaseFilePath("leasefile6_0.csv"));
    }


    /// @brief Remove files being products of Lease File Cleanup.
    ///
    /// @param base_name Path to the lease file name. This file is removed
    /// and all files which names are crated from this name (having specific
    /// suffixes used by Lease File Cleanup mechanism).
    void removeFiles(const std::string& base_name) const {
        // Generate suffixes and append them to the base name. The
        // resulting file names are the ones that may exist as a
        // result of LFC.
        for (int i = static_cast<int>(Memfile_LeaseMgr::FILE_CURRENT);
             i <= static_cast<int>(Memfile_LeaseMgr::FILE_FINISH);
             ++i) {
            Memfile_LeaseMgr::LFCFileType type = static_cast<
                Memfile_LeaseMgr::LFCFileType>(i);
            LeaseFileIO io(Memfile_LeaseMgr::appendSuffix(base_name, type));
            io.removeFile();
        }
    }

    /// @brief Return path to the lease file used by unit tests.
    ///
    /// @param filename Name of the lease file appended to the path to the
    /// directory where test data is held.
    ///
    /// @return Full path to the lease file.
    static std::string getLeaseFilePath(const std::string& filename) {
        std::ostringstream s;
        s << TEST_DATA_BUILDDIR << "/" << filename;
        return (s.str());
    }

    /// @brief Returns the configuration string for the backend.
    ///
    /// This string configures the @c LeaseMgrFactory to create the memfile
    /// backend and use leasefile4_0.csv and leasefile6_0.csv files as
    /// storage for leases.
    ///
    /// @param no_universe Indicates whether universe parameter should be
    /// included (false), or not (true).
    ///
    /// @return Configuration string for @c LeaseMgrFactory.
    static std::string getConfigString(Universe u) {
        std::ostringstream s;
        s << "type=memfile " << (u == V4 ? "universe=4 " : "universe=6 ")
          << "name="
          << getLeaseFilePath(u == V4 ? "leasefile4_0.csv" : "leasefile6_0.csv");
        return (s.str());
    }

    /// @brief Creates instance of the backend.
    ///
    /// @param u Universe (v4 or V6).
    void startBackend(Universe u) {
        try {
            LeaseMgrFactory::create(getConfigString(u));
        } catch (...) {
            std::cerr << "*** ERROR: unable to create instance of the Memfile\n"
                " lease database backend.\n";
            throw;
        }
        lmptr_ = &(LeaseMgrFactory::instance());
    }

    /// @brief Runs @c IfaceMgr::receive6 in a look for a specified time.
    ///
    /// @param ms Duration in milliseconds.
    void setTestTime(const uint32_t ms) {
        // Measure test time and exit if timeout hit.
        Stopwatch stopwatch;
        while (stopwatch.getTotalMilliseconds() < ms) {
            // Block for one 1 millisecond.
            IfaceMgr::instance().receive6(0, 1000);
        }
    }

    /// @brief Waits for the specified process to finish.
    ///
    /// @param process An object which started the process.
    /// @param timeout Timeout in seconds.
    ///
    /// @return true if the process ended, false otherwise
    bool waitForProcess(const Memfile_LeaseMgr& lease_mgr,
                        const uint8_t timeout) {
        uint32_t iterations = 0;
        const uint32_t iterations_max = timeout * 1000;
        while (lease_mgr.isLFCRunning() && (iterations < iterations_max)) {
            usleep(1000);
            ++iterations;
        }
        return (iterations < iterations_max);
    }


    /// @brief Object providing access to v4 lease IO.
    LeaseFileIO io4_;

    /// @brief Object providing access to v6 lease IO.
    LeaseFileIO io6_;

    /// @brief Pointer to the instance of the @c TimerMgr.
    TimerMgrPtr timer_mgr_;
};

// This test checks if the LeaseMgr can be instantiated and that it
// parses parameters string properly.
TEST_F(MemfileLeaseMgrTest, constructor) {
    LeaseMgr::ParameterMap pmap;
    pmap["universe"] = "4";
    pmap["persist"] = "false";
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr;

    EXPECT_NO_THROW(lease_mgr.reset(new Memfile_LeaseMgr(pmap)));

    pmap["lfc-interval"] = "10";
    pmap["persist"] = "true";
    pmap["name"] = getLeaseFilePath("leasefile4_1.csv");
    EXPECT_NO_THROW(lease_mgr.reset(new Memfile_LeaseMgr(pmap)));

    // Expecting that persist parameter is yes or no. Everything other than
    // that is wrong.
    pmap["persist"] = "bogus";
    pmap["name"] = getLeaseFilePath("leasefile4_1.csv");
    EXPECT_THROW(lease_mgr.reset(new Memfile_LeaseMgr(pmap)), isc::BadValue);

    // The lfc-interval must be an integer.
    pmap["persist"] = "true";
    pmap["lfc-interval"] = "bogus";
    EXPECT_THROW(lease_mgr.reset(new Memfile_LeaseMgr(pmap)), isc::BadValue);
}

// Checks if the getType() and getName() methods both return "memfile".
TEST_F(MemfileLeaseMgrTest, getTypeAndName) {
    startBackend(V4);
    EXPECT_EQ(std::string("memfile"), lmptr_->getType());
    EXPECT_EQ(std::string("memory"),  lmptr_->getName());
}

// Checks if the path to the lease files is initialized correctly.
TEST_F(MemfileLeaseMgrTest, getLeaseFilePath) {
    // Initialize IO objects, so as the test csv files get removed after the
    // test (when destructors are called).
    LeaseFileIO io4(getLeaseFilePath("leasefile4_1.csv"));
    LeaseFileIO io6(getLeaseFilePath("leasefile6_1.csv"));

    LeaseMgr::ParameterMap pmap;
    pmap["universe"] = "4";
    pmap["name"] = getLeaseFilePath("leasefile4_1.csv");
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr(new Memfile_LeaseMgr(pmap));

    EXPECT_EQ(pmap["name"],
              lease_mgr->getLeaseFilePath(Memfile_LeaseMgr::V4));

    pmap["persist"] = "false";
    lease_mgr.reset(new Memfile_LeaseMgr(pmap));
    EXPECT_TRUE(lease_mgr->getLeaseFilePath(Memfile_LeaseMgr::V4).empty());
    EXPECT_TRUE(lease_mgr->getLeaseFilePath(Memfile_LeaseMgr::V6).empty());
}

// Check if the persitLeases correctly checks that leases should not be written
// to disk when disabled through configuration.
TEST_F(MemfileLeaseMgrTest, persistLeases) {
    // Initialize IO objects, so as the test csv files get removed after the
    // test (when destructors are called).
    LeaseFileIO io4(getLeaseFilePath("leasefile4_1.csv"));
    LeaseFileIO io6(getLeaseFilePath("leasefile6_1.csv"));

    LeaseMgr::ParameterMap pmap;
    pmap["universe"] = "4";
    // Specify the names of the lease files. Leases will be written.
    pmap["name"] = getLeaseFilePath("leasefile4_1.csv");
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr(new Memfile_LeaseMgr(pmap));

    lease_mgr.reset(new Memfile_LeaseMgr(pmap));
    EXPECT_TRUE(lease_mgr->persistLeases(Memfile_LeaseMgr::V4));
    EXPECT_FALSE(lease_mgr->persistLeases(Memfile_LeaseMgr::V6));

    pmap["universe"] = "6";
    pmap["name"] = getLeaseFilePath("leasefile6_1.csv");
    lease_mgr.reset(new Memfile_LeaseMgr(pmap));
    EXPECT_FALSE(lease_mgr->persistLeases(Memfile_LeaseMgr::V4));
    EXPECT_TRUE(lease_mgr->persistLeases(Memfile_LeaseMgr::V6));

    // This should disable writes of leases to disk.
    pmap["persist"] = "false";
    lease_mgr.reset(new Memfile_LeaseMgr(pmap));
    EXPECT_FALSE(lease_mgr->persistLeases(Memfile_LeaseMgr::V4));
    EXPECT_FALSE(lease_mgr->persistLeases(Memfile_LeaseMgr::V6));
}

// Check if it is possible to schedule the timer to perform the Lease
// File Cleanup periodically.
TEST_F(MemfileLeaseMgrTest, lfcTimer) {
    LeaseMgr::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "4";
    // Specify the names of the lease files. Leases will be written.
    pmap["name"] = getLeaseFilePath("leasefile4_0.csv");
    pmap["lfc-interval"] = "1";

    boost::scoped_ptr<LFCMemfileLeaseMgr>
        lease_mgr(new LFCMemfileLeaseMgr(pmap));

    // Start worker thread to execute LFC periodically.
    ASSERT_NO_THROW(timer_mgr_->startThread());

    // Run the test for at most 2.9 seconds.
    setTestTime(2900);

    // Stop worker thread to make sure it is not running when lease
    // manager is destroyed. The lease manager will be unable to
    // unregster timer when the thread is active.
    ASSERT_NO_THROW(timer_mgr_->stopThread());

    // Within 2.9 we should record two LFC executions.
    EXPECT_EQ(2, lease_mgr->getLFCCount());
}


// This test checks if the LFC timer is disabled (doesn't trigger)
// cleanups when the lfc-interval is set to 0.
TEST_F(MemfileLeaseMgrTest, lfcTimerDisabled) {
    LeaseMgr::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "4";
    pmap["name"] = getLeaseFilePath("leasefile4_0.csv");
    // Set the LFC interval to 0, which should effectively disable it.
    pmap["lfc-interval"] = "0";

    boost::scoped_ptr<LFCMemfileLeaseMgr>
        lease_mgr(new LFCMemfileLeaseMgr(pmap));

    // Start worker thread to execute LFC periodically.
    ASSERT_NO_THROW(timer_mgr_->startThread());

    // Run the test for at most 1.9 seconds.
    setTestTime(1900);

    // Stop worker thread to make sure it is not running when lease
    // manager is destroyed. The lease manager will be unable to
    // unregster timer when the thread is active.
    ASSERT_NO_THROW(timer_mgr_->stopThread());

    // There should be no LFC execution recorded.
    EXPECT_EQ(0, lease_mgr->getLFCCount());
}

// This test checks that the callback function executing the cleanup of the
// DHCPv4 lease file works as expected.
TEST_F(MemfileLeaseMgrTest, leaseFileCleanup4) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,hwaddr,client_id,valid_lifetime,expire,"
        "subnet_id,fqdn_fwd,fqdn_rev,hostname,state\n";

    // This string contains the contents of the lease file with exactly
    // one lease, but two entries. One of the entries should be removed
    // as a result of lease file cleanup.
    std::string current_file_contents = new_file_contents +
        "192.0.2.2,02:02:02:02:02:02,,200,200,8,1,1,,1\n"
        "192.0.2.2,02:02:02:02:02:02,,200,800,8,1,1,,1\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile4_0.csv"));
    current_file.writeFile(current_file_contents);

    std::string previous_file_contents = new_file_contents +
        "192.0.2.3,03:03:03:03:03:03,,200,200,8,1,1,,1\n"
        "192.0.2.3,03:03:03:03:03:03,,200,800,8,1,1,,1\n";
    LeaseFileIO previous_file(getLeaseFilePath("leasefile4_0.csv.2"));
    previous_file.writeFile(previous_file_contents);

    // Create the backend.
    LeaseMgr::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "4";
    pmap["name"] = getLeaseFilePath("leasefile4_0.csv");
    pmap["lfc-interval"] = "1";
    boost::scoped_ptr<NakedMemfileLeaseMgr> lease_mgr(new NakedMemfileLeaseMgr(pmap));

    // Try to run the lease file cleanup.
    ASSERT_NO_THROW(lease_mgr->lfcCallback());

    // The new lease file should have been created and it should contain
    // no leases.
    ASSERT_TRUE(current_file.exists());
    EXPECT_EQ(new_file_contents, current_file.readFile());

    // Wait for the LFC process to complete.
    ASSERT_TRUE(waitForProcess(*lease_mgr, 2));

    // And make sure it has returned an exit status of 0.
    EXPECT_EQ(0, lease_mgr->getLFCExitStatus())
        << "Executing the LFC process failed: make sure that"
        " the kea-lfc program has been compiled.";

    // Check if we can still write to the lease file.
    std::vector<uint8_t> hwaddr_vec(6);
    HWAddrPtr hwaddr(new HWAddr(hwaddr_vec, HTYPE_ETHER));
    Lease4Ptr new_lease(new Lease4(IOAddress("192.0.2.45"), hwaddr, 0, 0,
                                   100, 50, 60, 0, 1));
    ASSERT_NO_THROW(lease_mgr->addLease(new_lease));

    std::string updated_file_contents = new_file_contents +
        "192.0.2.45,00:00:00:00:00:00,,100,100,1,0,0,,0\n";
    EXPECT_EQ(updated_file_contents, current_file.readFile());

    // This string contains the contents of the lease file we
    // expect after the LFC run.  It has two leases with one
    // entry each.
    std::string result_file_contents = new_file_contents +
        "192.0.2.2,02:02:02:02:02:02,,200,800,8,1,1,,1\n"
        "192.0.2.3,03:03:03:03:03:03,,200,800,8,1,1,,1\n";

    // The LFC should have created a file with the two leases and moved it
    // to leasefile4_0.csv.2
    LeaseFileIO input_file(getLeaseFilePath("leasefile4_0.csv.2"), false);
    ASSERT_TRUE(input_file.exists());
    // And this file should contain the contents of the result file.
    EXPECT_EQ(result_file_contents, input_file.readFile());
}

// This test checks that the callback function executing the cleanup of the
// DHCPv6 lease file works as expected.
TEST_F(MemfileLeaseMgrTest, leaseFileCleanup6) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,duid,valid_lifetime,expire,subnet_id,"
        "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
        "fqdn_rev,hostname,hwaddr,state\n";

    // This string contains the contents of the lease file with exactly
    // one lease, but two entries. One of the entries should be removed
    // as a result of lease file cleanup.
    std::string current_file_contents = new_file_contents +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,200,"
        "8,100,0,7,0,1,1,,,1\n"
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,,1\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile6_0.csv"));
    current_file.writeFile(current_file_contents);

    std::string previous_file_contents = new_file_contents +
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,200,"
        "8,100,0,7,0,1,1,,,1\n"
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,,1\n";
    LeaseFileIO previous_file(getLeaseFilePath("leasefile6_0.csv.2"));
    previous_file.writeFile(previous_file_contents);

    // Create the backend.
    LeaseMgr::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "6";
    pmap["name"] = getLeaseFilePath("leasefile6_0.csv");
    pmap["lfc-interval"] = "1";
    boost::scoped_ptr<NakedMemfileLeaseMgr> lease_mgr(new NakedMemfileLeaseMgr(pmap));

    // Try to run the lease file cleanup.
    ASSERT_NO_THROW(lease_mgr->lfcCallback());

    // The new lease file should have been created and it should contain
    // no leases.
    ASSERT_TRUE(current_file.exists());
    EXPECT_EQ(new_file_contents, current_file.readFile());

    // Wait for the LFC process to complete.
    ASSERT_TRUE(waitForProcess(*lease_mgr, 2));

    // And make sure it has returned an exit status of 0.
    EXPECT_EQ(0, lease_mgr->getLFCExitStatus())
        << "Executing the LFC process failed: make sure that"
        " the kea-lfc program has been compiled.";


    // Check if we can still write to the lease file.
    std::vector<uint8_t> duid_vec(13);
    DuidPtr duid(new DUID(duid_vec));
    Lease6Ptr new_lease(new Lease6(Lease::TYPE_NA, IOAddress("3000::1"),duid,
                                   123, 300, 400, 100, 300, 2));
    new_lease->cltt_ = 0;
    ASSERT_NO_THROW(lease_mgr->addLease(new_lease));

    std::string update_file_contents = new_file_contents +
        "3000::1,00:00:00:00:00:00:00:00:00:00:00:00:00,400,"
        "400,2,300,0,123,128,0,0,,,0\n";
    EXPECT_EQ(update_file_contents, current_file.readFile());

    // This string contains the contents of the lease file we
    // expect after the LFC run.  It has two leases with one
    // entry each.
    std::string result_file_contents = new_file_contents +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,,1\n"
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,,1\n";

    // The LFC should have created a file with the two leases and moved it
    // to leasefile6_0.csv.2
    LeaseFileIO input_file(getLeaseFilePath("leasefile6_0.csv.2"), false);
    ASSERT_TRUE(input_file.exists());
    // And this file should contain the contents of the result file.
    EXPECT_EQ(result_file_contents, input_file.readFile());
}

// This test verifies that EXIT_FAILURE status code is returned when
// the LFC process fails to start.
TEST_F(MemfileLeaseMgrTest, leaseFileCleanupStartFail) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,hwaddr,client_id,valid_lifetime,expire,"
        "subnet_id,fqdn_fwd,fqdn_rev,hostname,state\n";

    // Create the lease file to be used by the backend.
    std::string current_file_contents = new_file_contents +
        "192.0.2.2,02:02:02:02:02:02,,200,200,8,1,1,,1\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile4_0.csv"));
    current_file.writeFile(current_file_contents);

    // Specify invalid path to the kea-lfc executable. This should result
    // in failure status code returned by the child process.
    setenv("KEA_LFC_EXECUTABLE", "foobar", 1);

    // Create the backend.
    LeaseMgr::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "4";
    pmap["name"] = getLeaseFilePath("leasefile4_0.csv");
    pmap["lfc-interval"] = "1";
    boost::scoped_ptr<NakedMemfileLeaseMgr> lease_mgr(new NakedMemfileLeaseMgr(pmap));

    // Try to run the lease file cleanup.
    ASSERT_NO_THROW(lease_mgr->lfcCallback());

    // Wait for the LFC process to complete.
    ASSERT_TRUE(waitForProcess(*lease_mgr, 2));

    // And make sure it has returned an error.
    EXPECT_EQ(EXIT_FAILURE, lease_mgr->getLFCExitStatus())
        << "Executing the LFC process failed: make sure that"
        " the kea-lfc program has been compiled.";
}

// This test checks that the callback function executing the cleanup of the
// files doesn't move the current file if the finish file exists
TEST_F(MemfileLeaseMgrTest, leaseFileFinish) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,duid,valid_lifetime,expire,subnet_id,"
        "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
        "fqdn_rev,hostname,hwaddr,state\n";

    // This string contains the contents of the current lease file.
    // It should not be moved.
    std::string current_file_contents = new_file_contents +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,200,"
        "8,100,0,7,0,1,1,,,1\n"
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,,1\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile6_0.csv"));
    current_file.writeFile(current_file_contents);

    // This string contains the contents of the finish file.  It should
    // be moved to the previous file.
    std::string finish_file_contents = new_file_contents +
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,,1\n";
    LeaseFileIO finish_file(getLeaseFilePath("leasefile6_0.csv.completed"));
    finish_file.writeFile(finish_file_contents);

    // Create the backend.
    LeaseMgr::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "6";
    pmap["name"] = getLeaseFilePath("leasefile6_0.csv");
    pmap["lfc-interval"] = "1";
    boost::scoped_ptr<NakedMemfileLeaseMgr> lease_mgr(new NakedMemfileLeaseMgr(pmap));

    // Try to run the lease file cleanup.
    ASSERT_NO_THROW(lease_mgr->lfcCallback());

    // The current lease file should not have been touched.
    ASSERT_TRUE(current_file.exists());
    EXPECT_EQ(current_file_contents, current_file.readFile());

    // Wait for the LFC process to complete.
    ASSERT_TRUE(waitForProcess(*lease_mgr, 5));

    // And make sure it has returned an exit status of 0.
    EXPECT_EQ(0, lease_mgr->getLFCExitStatus())
        << "Executing the LFC process failed: make sure that"
        " the kea-lfc program has been compiled.";

    // The LFC should have moved the finish file to the previous file -
    // leasefile6_0.csv.2
    LeaseFileIO previous_file(getLeaseFilePath("leasefile6_0.csv.2"), false);
    ASSERT_TRUE(previous_file.exists());
    // And this file should contain the contents of the finish file.
    EXPECT_EQ(finish_file_contents, previous_file.readFile());

    // The finish file should have been removed
    ASSERT_FALSE(finish_file.exists());
}

// This test checks that the callback function executing the cleanup of the
// files doesn't move the current file if the copy file exists
TEST_F(MemfileLeaseMgrTest, leaseFileCopy) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,duid,valid_lifetime,expire,subnet_id,"
        "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
        "fqdn_rev,hostname,hwaddr,state\n";

    // This string contains the contents of the current lease file.
    // It should not be moved.
    std::string current_file_contents = new_file_contents +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,200,"
        "8,100,0,7,0,1,1,,,1\n"
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,,1\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile6_0.csv"));
    current_file.writeFile(current_file_contents);

    // This string contains the contents of the copy file.  It should
    // be processed and moved to the previous file.  As there is only
    // one lease the processing should result in the previous file being
    // the same.
    std::string input_file_contents = new_file_contents +
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,,1\n";
    LeaseFileIO input_file(getLeaseFilePath("leasefile6_0.csv.1"));
    input_file.writeFile(input_file_contents);

    // Create the backend.
    LeaseMgr::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "6";
    pmap["name"] = getLeaseFilePath("leasefile6_0.csv");
    pmap["lfc-interval"] = "1";
    boost::scoped_ptr<NakedMemfileLeaseMgr> lease_mgr(new NakedMemfileLeaseMgr(pmap));

    // Try to run the lease file cleanup.
    ASSERT_NO_THROW(lease_mgr->lfcCallback());

    // The current lease file should not have been touched.
    ASSERT_TRUE(current_file.exists());
    EXPECT_EQ(current_file_contents, current_file.readFile());

    // Wait for the LFC process to complete.
    ASSERT_TRUE(waitForProcess(*lease_mgr, 5));

    // And make sure it has returned an exit status of 0.
    EXPECT_EQ(0, lease_mgr->getLFCExitStatus())
        << "Executing the LFC process failed: make sure that"
        " the kea-lfc program has been compiled.";

    // The LFC should have processed the lease and moved it to the previous
    // file - leasefile6_0.csv.2
    LeaseFileIO previous_file(getLeaseFilePath("leasefile6_0.csv.2"), false);
    ASSERT_TRUE(previous_file.exists());
    // And this file should contain the contents of the copy file.
    EXPECT_EQ(input_file_contents, previous_file.readFile());

    // The input file should have been removed
    ASSERT_FALSE(input_file.exists());
}

// Checks that adding/getting/deleting a Lease6 object works.
TEST_F(MemfileLeaseMgrTest, addGetDelete6) {
    startBackend(V6);
    testAddGetDelete6(true); // true - check T1,T2 values
    // memfile is able to preserve those values, but some other
    // backends can't do that.
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4 (by address) and deleteLease (with an
/// IPv4 address) works.
TEST_F(MemfileLeaseMgrTest, basicLease4) {
    startBackend(V4);
    testBasicLease4();
}

/// @todo Write more memfile tests

// Simple test about lease4 retrieval through client id method
TEST_F(MemfileLeaseMgrTest, getLease4ClientId) {
    startBackend(V4);
    testGetLease4ClientId();
}

// Checks that lease4 retrieval client id is null is working
TEST_F(MemfileLeaseMgrTest, getLease4NullClientId) {
    startBackend(V4);
    testGetLease4NullClientId();
}

// Checks lease4 retrieval through HWAddr
TEST_F(MemfileLeaseMgrTest, getLease4HWAddr1) {
    startBackend(V4);
    testGetLease4HWAddr1();
}

/// @brief Check GetLease4 methods - access by Hardware Address
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DUID and IAID.
TEST_F(MemfileLeaseMgrTest, getLease4HWAddr2) {
    startBackend(V4);
    testGetLease4HWAddr2();
}

// Checks lease4 retrieval with clientId, HWAddr and subnet_id
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdHWAddrSubnetId) {
    startBackend(V4);
    testGetLease4ClientIdHWAddrSubnetId();
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4(by address), getLease4(hwaddr,subnet_id),
/// updateLease4() and deleteLease (IPv4 address) can handle NULL client-id.
/// (client-id is optional and may not be present)
TEST_F(MemfileLeaseMgrTest, lease4NullClientId) {
    startBackend(V4);
    testLease4NullClientId();
}

/// @brief Check GetLease4 methods - access by Hardware Address & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of hardware address and subnet ID
TEST_F(MemfileLeaseMgrTest, DISABLED_getLease4HwaddrSubnetId) {

    /// @todo: fails on memfile. It's probably a memfile bug.
    startBackend(V4);
    testGetLease4HWAddrSubnetId();
}

/// @brief Check GetLease4 methods - access by Client ID
///
/// Adds leases to the database and checks that they can be accessed via
/// the Client ID.
TEST_F(MemfileLeaseMgrTest, getLease4ClientId2) {
    startBackend(V4);
    testGetLease4ClientId2();
}

// @brief Get Lease4 by client ID
//
// Check that the system can cope with a client ID of any size.
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdSize) {
    startBackend(V4);
    testGetLease4ClientIdSize();
}

/// @brief Check GetLease4 methods - access by Client ID & Subnet ID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of client and subnet IDs.
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdSubnetId) {
    startBackend(V4);
    testGetLease4ClientIdSubnetId();
}

/// @brief Basic Lease6 Checks
///
/// Checks that the addLease, getLease6 (by address) and deleteLease (with an
/// IPv6 address) works.
TEST_F(MemfileLeaseMgrTest, basicLease6) {
    startBackend(V6);
    testBasicLease6();
}


/// @brief Check GetLease6 methods - access by DUID/IAID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DUID and IAID.
/// @todo: test disabled, because Memfile_LeaseMgr::getLeases6(Lease::Type,
/// const DUID& duid, uint32_t iaid) const is not implemented yet.
TEST_F(MemfileLeaseMgrTest, getLeases6DuidIaid) {
    startBackend(V6);
    testGetLeases6DuidIaid();
}

/// @brief Check that the system can cope with a DUID of allowed size.
TEST_F(MemfileLeaseMgrTest, getLeases6DuidSize) {
    startBackend(V6);
    testGetLeases6DuidSize();
}

/// @brief Check that the expired DHCPv4 leases can be retrieved.
///
/// This test adds a number of leases to the lease database and marks
/// some of them as expired. Then it queries for expired leases and checks
/// whether only expired leases are returned, and that they are returned in
/// the order from most to least expired. It also checks that the lease
/// which is marked as 'reclaimed' is not returned.
TEST_F(MemfileLeaseMgrTest, getExpiredLeases4) {
    startBackend(V4);
    testGetExpiredLeases4();
}

/// @brief Check that the expired DHCPv6 leases can be retrieved.
///
/// This test adds a number of leases to the lease database and marks
/// some of them as expired. Then it queries for expired leases and checks
/// whether only expired leases are returned, and that they are returned in
/// the order from most to least expired. It also checks that the lease
/// which is marked as 'reclaimed' is not returned.
TEST_F(MemfileLeaseMgrTest, getExpiredLeases6) {
    startBackend(V6);
    testGetExpiredLeases6();
}

/// @brief Check that expired reclaimed DHCPv6 leases are removed.
TEST_F(MemfileLeaseMgrTest, deleteExpiredReclaimedLeases6) {
    startBackend(V6);
    testDeleteExpiredReclaimedLeases6();
}

/// @brief Check that expired reclaimed DHCPv4 leases are removed.
TEST_F(MemfileLeaseMgrTest, deleteExpiredReclaimedLeases4) {
    startBackend(V4);
    testDeleteExpiredReclaimedLeases4();
}

/// @brief Check that getLease6 methods discriminate by lease type.
///
/// Adds six leases, two per lease type all with the same duid and iad but
/// with alternating subnet_ids.
/// It then verifies that all of getLeases6() method variants correctly
/// discriminate between the leases based on lease type alone.
/// @todo: Disabled, because type parameter in Memfile_LeaseMgr::getLease6
/// (Lease::Type, const isc::asiolink::IOAddress& addr) const is not used.
TEST_F(MemfileLeaseMgrTest, lease6LeaseTypeCheck) {
    startBackend(V6);
    testLease6LeaseTypeCheck();
}

/// @brief Check GetLease6 methods - access by DUID/IAID/SubnetID
///
/// Adds leases to the database and checks that they can be accessed via
/// a combination of DIUID and IAID.
TEST_F(MemfileLeaseMgrTest, getLease6DuidIaidSubnetId) {
    startBackend(V6);
    testGetLease6DuidIaidSubnetId();
}

/// Checks that getLease6(type, duid, iaid, subnet-id) works with different
/// DUID sizes
TEST_F(MemfileLeaseMgrTest, getLease6DuidIaidSubnetIdSize) {
    startBackend(V6);
    testGetLease6DuidIaidSubnetIdSize();
}

/// @brief Lease4 update tests
///
/// Checks that we are able to update a lease in the database.
/// @todo: Disabled, because memfile does not throw when lease is updated.
/// We should reconsider if lease{4,6} structures should have a limit
/// implemented in them.
TEST_F(MemfileLeaseMgrTest, DISABLED_updateLease4) {
    startBackend(V4);
    testUpdateLease4();
}

/// @brief Lease6 update tests
///
/// Checks that we are able to update a lease in the database.
/// @todo: Disabled, because memfile does not throw when lease is updated.
/// We should reconsider if lease{4,6} structures should have a limit
/// implemented in them.
TEST_F(MemfileLeaseMgrTest, DISABLED_updateLease6) {
    startBackend(V6);
    testUpdateLease6();
}

/// @brief DHCPv4 Lease recreation tests
///
/// Checks that the lease can be created, deleted and recreated with
/// different parameters. It also checks that the re-created lease is
/// correctly stored in the lease database.
TEST_F(MemfileLeaseMgrTest, testRecreateLease4) {
    startBackend(V4);
    testRecreateLease4();
}

/// @brief DHCPv6 Lease recreation tests
///
/// Checks that the lease can be created, deleted and recreated with
/// different parameters. It also checks that the re-created lease is
/// correctly stored in the lease database.
TEST_F(MemfileLeaseMgrTest, testRecreateLease6) {
    startBackend(V6);
    testRecreateLease6();
}

// The following tests are not applicable for memfile. When adding
// new tests to the list here, make sure to provide brief explanation
// why they are not applicable:
//
// testGetLease4HWAddrSubnetIdSize() - memfile just keeps Lease structure
//     and does not do any checks of HWAddr content

/// @brief Checks that null DUID is not allowed.
/// Test is disabled as Memfile does not currently defend against a null DUID.
TEST_F(MemfileLeaseMgrTest, DISABLED_nullDuid) {
    // Create leases, although we need only one.
    vector<Lease6Ptr> leases = createLeases6();

    leases[1]->duid_.reset();
    ASSERT_THROW(lmptr_->addLease(leases[1]), DbOperationError);
}

/// @brief Tests whether memfile can store and retrieve hardware addresses
TEST_F(MemfileLeaseMgrTest, testLease6Mac) {
    startBackend(V6);
    testLease6MAC();
}

// Check that memfile reports version correctly.
TEST_F(MemfileLeaseMgrTest, versionCheck) {

    // Check that V4 backend reports versions correctly.
    startBackend(V4);
    testVersion(Memfile_LeaseMgr::MAJOR_VERSION,
                Memfile_LeaseMgr::MINOR_VERSION);
    LeaseMgrFactory::destroy();

    // Check that V6 backends reports them ok, too.
    startBackend(V6);
    testVersion(Memfile_LeaseMgr::MAJOR_VERSION,
                Memfile_LeaseMgr::MINOR_VERSION);
    LeaseMgrFactory::destroy();
}

// This test checks that the backend reads DHCPv4 lease data from multiple
// files.
TEST_F(MemfileLeaseMgrTest, load4MultipleLeaseFiles) {
    LeaseFileIO io2(getLeaseFilePath("leasefile4_0.csv.2"));
    io2.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state\n"
                  "192.0.2.2,02:02:02:02:02:02,,200,200,8,1,1,,1\n"
                  "192.0.2.11,bb:bb:bb:bb:bb:bb,,200,200,8,1,1,,1\n");

    LeaseFileIO io1(getLeaseFilePath("leasefile4_0.csv.1"));
    io1.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state\n"
                  "192.0.2.1,01:01:01:01:01:01,,200,200,8,1,1,,1\n"
                  "192.0.2.11,bb:bb:bb:bb:bb:bb,,200,400,8,1,1,,1\n"
                  "192.0.2.12,cc:cc:cc:cc:cc:cc,,200,200,8,1,1,,1\n");

    LeaseFileIO io(getLeaseFilePath("leasefile4_0.csv"));
    io.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                 "fqdn_fwd,fqdn_rev,hostname,state\n"
                 "192.0.2.10,0a:0a:0a:0a:0a:0a,,200,200,8,1,1,,1\n"
                 "192.0.2.12,cc:cc:cc:cc:cc:cc,,200,400,8,1,1,,1\n");

    startBackend(V4);

    // This lease only exists in the second file and the cltt should
    // be 0.
    Lease4Ptr lease = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // This lease only exists in the first file and the cltt should
    // be 0.
    lease = lmptr_->getLease4(IOAddress("192.0.2.2"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // This lease only exists in the third file and the cltt should
    // be 0.
    lease = lmptr_->getLease4(IOAddress("192.0.2.10"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // This lease exists in the first and second file and the cltt
    // should be calculated using the expiration time and the
    // valid lifetime from the second file.
    lease = lmptr_->getLease4(IOAddress("192.0.2.11"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(200, lease->cltt_);

    // This lease exists in the second and third file and the cltt
    // should be calculated using the expiration time and the
    // valid lifetime from the third file.
    lease = lmptr_->getLease4(IOAddress("192.0.2.12"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(200, lease->cltt_);
}

// This test checks that the lease database backend loads the file with
// the .completed postfix instead of files with postfixes .1 and .2 if
// the file with .completed postfix exists.
TEST_F(MemfileLeaseMgrTest, load4CompletedFile) {
    LeaseFileIO io2(getLeaseFilePath("leasefile4_0.csv.2"));
    io2.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state\n"
                  "192.0.2.2,02:02:02:02:02:02,,200,200,8,1,1,,1\n"
                  "192.0.2.11,bb:bb:bb:bb:bb:bb,,200,200,8,1,1,,1\n");

    LeaseFileIO io1(getLeaseFilePath("leasefile4_0.csv.1"));
    io1.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state\n"
                  "192.0.2.1,01:01:01:01:01:01,,200,200,8,1,1,,1\n"
                  "192.0.2.11,bb:bb:bb:bb:bb:bb,,200,400,8,1,1,,1\n"
                  "192.0.2.12,cc:cc:cc:cc:cc:cc,,200,200,8,1,1,,1\n");

    LeaseFileIO io(getLeaseFilePath("leasefile4_0.csv"));
    io.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                 "fqdn_fwd,fqdn_rev,hostname,state\n"
                 "192.0.2.10,0a:0a:0a:0a:0a:0a,,200,200,8,1,1,,1\n"
                 "192.0.2.12,cc:cc:cc:cc:cc:cc,,200,400,8,1,1,,1\n");

    LeaseFileIO ioc(getLeaseFilePath("leasefile4_0.csv.completed"));
    ioc.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state\n"
                  "192.0.2.13,ff:ff:ff:ff:ff:ff,,200,200,8,1,1,,1\n");

    startBackend(V4);

    // We expect that this file only holds leases that belong to the
    // lease file or to the file with .completed postfix.
    Lease4Ptr lease = lmptr_->getLease4(IOAddress("192.0.2.10"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    lease = lmptr_->getLease4(IOAddress("192.0.2.12"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(200, lease->cltt_);

    // This lease is in the .completed file.
    lease = lmptr_->getLease4(IOAddress("192.0.2.13"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // Leases from the .1 and .2 files should not be loaded.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.11")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

// This test checks that backend constructor refuses to load leases from the
// lease files if the LFC is in progress.
TEST_F(MemfileLeaseMgrTest, load4LFCInProgress) {
    // Create the backend configuration.
    LeaseMgr::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "4";
    pmap["name"] = getLeaseFilePath("leasefile4_0.csv");
    pmap["lfc-interval"] = "1";

    // Create a pid file holding the PID of the current process. Choosing the
    // pid of the current process guarantees that when the backend starts up
    // the process is alive.
    PIDFile pid_file(Memfile_LeaseMgr::appendSuffix(pmap["name"], Memfile_LeaseMgr::FILE_PID));
    pid_file.write();

    // There is a pid file and the process which pid is in the file is
    // running, so the backend should refuse to start.
    boost::scoped_ptr<NakedMemfileLeaseMgr> lease_mgr;
    ASSERT_THROW(lease_mgr.reset(new NakedMemfileLeaseMgr(pmap)),
                 DbOpenError);

    // Remove the pid file, and retry. The bakckend should be created.
    pid_file.deleteFile();
    ASSERT_NO_THROW(lease_mgr.reset(new NakedMemfileLeaseMgr(pmap)));
}

// This test checks that the backend reads DHCPv6 lease data from multiple
// files.
TEST_F(MemfileLeaseMgrTest, load6MultipleLeaseFiles) {
    LeaseFileIO io2(getLeaseFilePath("leasefile6_0.csv.2"));
    io2.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                  "state\n"
                  "2001:db8:1::1,01:01:01:01:01:01:01:01:01:01:01:01:01,"
                  "200,200,8,100,0,7,0,1,1,,,1\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "200,200,8,100,0,7,0,1,1,,,1\n");

    LeaseFileIO io1(getLeaseFilePath("leasefile6_0.csv.1"));
    io1.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                  "state\n"
                  "2001:db8:1::3,03:03:03:03:03:03:03:03:03:03:03:03:03,"
                  "200,200,8,100,0,7,0,1,1,,,1\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "300,800,8,100,0,7,0,1,1,,,1\n"
                  "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                  "200,200,8,100,0,7,0,1,1,,,1\n");

    LeaseFileIO io(getLeaseFilePath("leasefile6_0.csv"));
    io.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                 "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                 "state\n"
                 "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                 "400,1000,8,100,0,7,0,1,1,,,1\n"
                 "2001:db8:1::5,05:05:05:05:05:05:05:05:05:05:05:05:05,"
                 "200,200,8,100,0,7,0,1,1,,,1\n");

    startBackend(V6);

    // This lease only exists in the first file and the cltt should be 0.
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA,
                                        IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // This lease exists in the first and second file and the cltt should
    // be calculated using the expiration time and the valid lifetime
    // from the second file.
    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(500, lease->cltt_);

    // This lease only exists in the second file and the cltt should be 0.
    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // This lease exists in the second and third file and the cltt should
    // be calculated using the expiration time and the valid lifetime
    // from the third file.
    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::4"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(600, lease->cltt_);

    // This lease only exists in the third file and the cltt should be 0.
    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);
}

// This test checks that the backend reads DHCPv6 lease data from the
// leasefile without the postfix and the file with a .1 postfix when
// the file with the .2 postfix is missing.
TEST_F(MemfileLeaseMgrTest, load6MultipleNoSecondFile) {
    LeaseFileIO io1(getLeaseFilePath("leasefile6_0.csv.1"));
    io1.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                  "state\n"
                  "2001:db8:1::3,03:03:03:03:03:03:03:03:03:03:03:03:03,"
                  "200,200,8,100,0,7,0,1,1,,,1\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "300,800,8,100,0,7,0,1,1,,,1\n"
                  "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                  "200,200,8,100,0,7,0,1,1,,,1\n");

    LeaseFileIO io(getLeaseFilePath("leasefile6_0.csv"));
    io.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                 "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                 "state\n"
                 "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                 "400,1000,8,100,0,7,0,1,1,,,1\n"
                 "2001:db8:1::5,05:05:05:05:05:05:05:05:05:05:05:05:05,"
                 "200,200,8,100,0,7,0,1,1,,,1\n");

    startBackend(V6);

    // Check that leases from the leasefile6_0 and leasefile6_0.1 have
    // been loaded.
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(500, lease->cltt_);

    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::4"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(600, lease->cltt_);

    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // Make sure that a lease which is not in those files is not loaded.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

// This test checks that the backend reads DHCPv6 lease data from the
// leasefile without the postfix and the file with a .2 postfix when
// the file with the .1 postfix is missing.
TEST_F(MemfileLeaseMgrTest, load6MultipleNoFirstFile) {
    LeaseFileIO io2(getLeaseFilePath("leasefile6_0.csv.2"));
    io2.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                  "state\n"
                  "2001:db8:1::1,01:01:01:01:01:01:01:01:01:01:01:01:01,"
                  "200,200,8,100,0,7,0,1,1,,,1\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "200,200,8,100,0,7,0,1,1,,,1\n");

    LeaseFileIO io(getLeaseFilePath("leasefile6_0.csv"));
    io.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                 "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                 "state\n"
                 "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                 "400,1000,8,100,0,7,0,1,1,,,1\n"
                 "2001:db8:1::5,05:05:05:05:05:05:05:05:05:05:05:05:05,"
                 "200,200,8,100,0,7,0,1,1,,,1\n");

    startBackend(V6);

    // Verify that leases which belong to the leasefile6_0.csv and
    // leasefile6_0.2 are loaded.
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA,
                                        IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::4"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(600, lease->cltt_);

    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    // A lease which doesn't belong to these files should not be loaded.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3")));
}


// This test checks that the lease database backend loads the file with
// the .completed postfix instead of files with postfixes .1 and .2 if
// the file with .completed postfix exists.
TEST_F(MemfileLeaseMgrTest, load6CompletedFile) {
    LeaseFileIO io2(getLeaseFilePath("leasefile6_0.csv.2"));
    io2.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                  "state\n"
                  "2001:db8:1::1,01:01:01:01:01:01:01:01:01:01:01:01:01,"
                  "200,200,8,100,0,7,0,1,1,,,1\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "200,200,8,100,0,7,0,1,1,,,1\n");

    LeaseFileIO io1(getLeaseFilePath("leasefile6_0.csv.1"));
    io1.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                  "state\n"
                  "2001:db8:1::3,03:03:03:03:03:03:03:03:03:03:03:03:03,"
                  "200,200,8,100,0,7,0,1,1,,,1\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "300,800,8,100,0,7,0,1,1,,,1\n"
                  "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                  "200,200,8,100,0,7,0,1,1,,,1\n");

    LeaseFileIO io(getLeaseFilePath("leasefile6_0.csv"));
    io.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                 "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                 "state\n"
                 "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                 "400,1000,8,100,0,7,0,1,1,,,1\n"
                 "2001:db8:1::5,05:05:05:05:05:05:05:05:05:05:05:05:05,"
                 "200,200,8,100,0,7,0,1,1,,,1\n");

    LeaseFileIO ioc(getLeaseFilePath("leasefile6_0.csv.completed"));
    ioc.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,hwaddr,"
                  "state\n"
                  "2001:db8:1::125,ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff,"
                  "400,1000,8,100,0,7,0,1,1,,,1\n");

    startBackend(V6);

    // We expect that this file only holds leases that belong to the
    // lease file or to the file with .completed postfix.
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::4"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(600, lease->cltt_);

    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(0, lease->cltt_);

    lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::125"));
    ASSERT_TRUE(lease);
    EXPECT_EQ(600, lease->cltt_);

    // Leases from the .1 and .2 files should not be loaded.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3")));
}

// This test checks that backend constructor refuses to load leases from the
// lease files if the LFC is in progress.
TEST_F(MemfileLeaseMgrTest, load6LFCInProgress) {
    // Create the backend configuration.
    LeaseMgr::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "6";
    pmap["name"] = getLeaseFilePath("leasefile6_0.csv");
    pmap["lfc-interval"] = "1";

    // Create a pid file holding the PID of the current process. Choosing the
    // pid of the current process guarantees that when the backend starts up
    // the process is alive.
    PIDFile pid_file(Memfile_LeaseMgr::appendSuffix(pmap["name"], Memfile_LeaseMgr::FILE_PID));
    pid_file.write();

    // There is a pid file and the process which pid is in the file is
    // running, so the backend should refuse to start.
    boost::scoped_ptr<NakedMemfileLeaseMgr> lease_mgr;
    ASSERT_THROW(lease_mgr.reset(new NakedMemfileLeaseMgr(pmap)),
                 DbOpenError);

    // Remove the pid file, and retry. The bakckend should be created.
    pid_file.deleteFile();
    ASSERT_NO_THROW(lease_mgr.reset(new NakedMemfileLeaseMgr(pmap)));
}

}; // end of anonymous namespace
