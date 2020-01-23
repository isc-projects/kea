// Copyright (C) 2012-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/timer_mgr.h>
#include <dhcpsrv/testutils/lease_file_io.h>
#include <dhcpsrv/tests/test_utils.h>
#include <dhcpsrv/tests/generic_lease_mgr_unittest.h>
#include <util/multi_threading_mgr.h>
#include <util/pid_file.h>
#include <util/range_utilities.h>
#include <util/stopwatch.h>

#include <boost/bind.hpp>
#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::db;
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
    LFCMemfileLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
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
    NakedMemfileLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
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
        io_service_(new IOService()),
        timer_mgr_(TimerMgr::instance()) {

        timer_mgr_->setIOService(io_service_);

        std::ostringstream s;
        s << KEA_LFC_BUILD_DIR << "/kea-lfc";
        setenv("KEA_LFC_EXECUTABLE", s.str().c_str(), 1);

        // Remove lease files and products of Lease File Cleanup.
        removeFiles(getLeaseFilePath("leasefile4_0.csv"));
        removeFiles(getLeaseFilePath("leasefile6_0.csv"));

        MultiThreadingMgr::instance().setMode(false);
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
        // Make sure there are no timers registered.
        timer_mgr_->unregisterTimers();
        LeaseMgrFactory::destroy();
        // Remove lease files and products of Lease File Cleanup.
        removeFiles(getLeaseFilePath("leasefile4_0.csv"));
        removeFiles(getLeaseFilePath("leasefile6_0.csv"));
        // Disable multi-threading.
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Remove files being products of Lease File Cleanup.
    ///
    /// @param base_name Path to the lease file name. This file is removed
    /// and all files which names are created from this name (having specific
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
          << getLeaseFilePath(u == V4 ? "leasefile4_0.csv" : "leasefile6_0.csv")
          << " lfc-interval=0";
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
        IntervalTimer timer(*io_service_);
        timer.setup([this]() {
                io_service_->stop();
        }, ms, IntervalTimer::ONE_SHOT);

        io_service_->run();
        io_service_->get_io_service().reset();
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

    /// @brief Generates a DHCPv4 lease with random content.
    ///
    /// The following lease parameters are randomly generated:
    /// - HW address,
    /// - client identifier,
    /// - hostname,
    /// - subnet identifier,
    /// - client last transmission time,
    ///
    /// The following lease parameters are set to constant values:
    /// - valid lifetime = 1200,
    /// - DNS update forward flag = false,
    /// - DNS update reverse flag = false,
    ///
    /// The lease address is set to address passed as function
    /// argument.
    ///
    /// @param address Lease address.
    ///
    /// @return new lease with random content
    Lease4Ptr initiateRandomLease4(const IOAddress& address) {

        // Randomize HW address.
        vector<uint8_t> mac(6);
        fillRandom(mac.begin(), mac.end());
        HWAddrPtr hwaddr(new HWAddr(mac, HTYPE_ETHER));

        // Let's generate clientid of random length
        vector<uint8_t> clientid(4 + random()%20);
        // And then fill it with random value.
        fillRandom(clientid.begin(), clientid.end());

        uint32_t valid_lft = 1200;
        time_t timestamp = time(NULL) - 86400 + random()%86400;
        bool fqdn_fwd = false;
        bool fqdn_rev = false;
        uint32_t subnet_id = 1000 + random()%16;

        std::ostringstream hostname;
        hostname << "hostname" << (random() % 2048);

        // Return created lease.
        return (Lease4Ptr(new Lease4(address, hwaddr, &clientid[0],
                                     clientid.size(), valid_lft,
                                     timestamp, subnet_id, fqdn_fwd,
                                     fqdn_rev, hostname.str())));
    }

    /// @brief Generates a DHCPv6 lease with random content.
    ///
    /// The following lease parameters are randomly generated:
    /// - DUID,
    /// - IAID,
    /// - hostname,
    /// - subnet identifier,
    /// - client last transmission time,
    ///
    /// The following lease parameters are set to constant values:
    /// - lease type = IA_NA
    /// - valid lifetime = 1200,
    /// - preferred lifetime = 1000
    /// - DNS update forward flag = false,
    /// - DNS update reverse flag = false,
    ///
    /// The lease address is set to address passed as function
    /// argument.
    ///
    /// @param address Lease address.
    ///
    /// @return new lease with random content
    Lease6Ptr initiateRandomLease6(const IOAddress& address) {
        // Let's generate DUID of random length.
        std::vector<uint8_t> duid_vec(8 + random()%20);
        // And then fill it with random value.
        fillRandom(duid_vec.begin(), duid_vec.end());
        DuidPtr duid(new DUID(duid_vec));

        Lease::Type lease_type = Lease::TYPE_NA;
        uint32_t iaid = 1 + random()%100;
        uint32_t valid_lft = 1200;
        uint32_t preferred_lft = 1000;
        time_t timestamp = time(NULL) - 86400 + random()%86400;
        bool fqdn_fwd = false;
        bool fqdn_rev = false;
        uint32_t subnet_id = 1000 + random()%16;

        std::ostringstream hostname;
        hostname << "hostname" << (random() % 2048);

        // Return created lease.
        Lease6Ptr lease(new Lease6(lease_type, address, duid, iaid,
                                   preferred_lft, valid_lft,
                                   subnet_id, fqdn_fwd, fqdn_rev,
                                   hostname.str()));
        lease->cltt_ = timestamp;
        return (lease);
    }

    /// @brief Object providing access to v4 lease IO.
    LeaseFileIO io4_;

    /// @brief Object providing access to v6 lease IO.
    LeaseFileIO io6_;

    /// @brief Pointer to the IO service used by the tests.
    IOServicePtr io_service_;

    /// @brief Pointer to the instance of the @c TimerMgr.
    TimerMgrPtr timer_mgr_;
};

/// @brief This test checks if the LeaseMgr can be instantiated and that it
/// parses parameters string properly.
TEST_F(MemfileLeaseMgrTest, constructor) {
    DatabaseConnection::ParameterMap pmap;
    pmap["universe"] = "4";
    pmap["persist"] = "false";
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr;

    EXPECT_NO_THROW(lease_mgr.reset(new Memfile_LeaseMgr(pmap)));

    pmap["lfc-interval"] = "10";
    pmap["persist"] = "true";
    pmap["name"] = getLeaseFilePath("leasefile4_1.csv");
    pmap["max-row-errors"] = "5";
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

    // The max-row-errors must be an integer.
    pmap["persist"] = "true";
    pmap["max-row-errors"] = "bogus";
    EXPECT_THROW(lease_mgr.reset(new Memfile_LeaseMgr(pmap)), isc::BadValue);

    // The max-row-errors must be >= 0.
    pmap["persist"] = "true";
    pmap["max-row-errors"] = "-1";
    EXPECT_THROW(lease_mgr.reset(new Memfile_LeaseMgr(pmap)), isc::BadValue);
}

/// @brief Checks if there is no lease manager NoLeaseManager is thrown.
TEST_F(MemfileLeaseMgrTest, noLeaseManager) {
    LeaseMgrFactory::destroy();
    EXPECT_THROW(LeaseMgrFactory::instance(), NoLeaseManager);
}

/// @brief Checks if the getType() and getName() methods both return "memfile".
TEST_F(MemfileLeaseMgrTest, getTypeAndName) {
    startBackend(V4);
    EXPECT_EQ(std::string("memfile"), lmptr_->getType());
    EXPECT_EQ(std::string("memory"),  lmptr_->getName());
}

/// @brief Checks if the path to the lease files is initialized correctly.
TEST_F(MemfileLeaseMgrTest, getLeaseFilePath) {
    // Initialize IO objects, so as the test csv files get removed after the
    // test (when destructors are called).
    LeaseFileIO io4(getLeaseFilePath("leasefile4_1.csv"));
    LeaseFileIO io6(getLeaseFilePath("leasefile6_1.csv"));

    DatabaseConnection::ParameterMap pmap;
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

/// @brief Check if the persistLeases correctly checks that leases should not be written
/// to disk when disabled through configuration.
TEST_F(MemfileLeaseMgrTest, persistLeases) {
    // Initialize IO objects, so as the test csv files get removed after the
    // test (when destructors are called).
    LeaseFileIO io4(getLeaseFilePath("leasefile4_1.csv"));
    LeaseFileIO io6(getLeaseFilePath("leasefile6_1.csv"));

    DatabaseConnection::ParameterMap pmap;
    pmap["universe"] = "4";
    pmap["lfc-interval"] = "0";
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

/// @brief Check if it is possible to schedule the timer to perform the Lease
/// File Cleanup periodically.
TEST_F(MemfileLeaseMgrTest, lfcTimer) {
    DatabaseConnection::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "4";
    // Specify the names of the lease files. Leases will be written.
    pmap["name"] = getLeaseFilePath("leasefile4_0.csv");
    pmap["lfc-interval"] = "1";

    boost::scoped_ptr<LFCMemfileLeaseMgr>
        lease_mgr(new LFCMemfileLeaseMgr(pmap));

    // Run the test for at most 2.9 seconds.
    setTestTime(2900);

    // Within 2.9 we should record two LFC executions.
    EXPECT_EQ(2, lease_mgr->getLFCCount());
}

/// @brief This test checks if the LFC timer is disabled (doesn't trigger)
/// cleanups when the lfc-interval is set to 0.
TEST_F(MemfileLeaseMgrTest, lfcTimerDisabled) {
    DatabaseConnection::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "4";
    pmap["name"] = getLeaseFilePath("leasefile4_0.csv");
    // Set the LFC interval to 0, which should effectively disable it.
    pmap["lfc-interval"] = "0";

    boost::scoped_ptr<LFCMemfileLeaseMgr>
        lease_mgr(new LFCMemfileLeaseMgr(pmap));

    // Run the test for at most 1.9 seconds.
    setTestTime(1900);

    // There should be no LFC execution recorded.
    EXPECT_EQ(0, lease_mgr->getLFCCount());
}

/// @brief This test checks that the callback function executing the cleanup of the
/// DHCPv4 lease file works as expected.
TEST_F(MemfileLeaseMgrTest, leaseFileCleanup4) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,hwaddr,client_id,valid_lifetime,expire,"
        "subnet_id,fqdn_fwd,fqdn_rev,hostname,state,user_context\n";

    // This string contains the contents of the lease file with exactly
    // one lease, but two entries. One of the entries should be removed
    // as a result of lease file cleanup.
    std::string current_file_contents = new_file_contents +
        "192.0.2.2,02:02:02:02:02:02,,200,200,8,1,1,,1,{ \"foo\": true }\n"
        "192.0.2.2,02:02:02:02:02:02,,200,800,8,1,1,,1,\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile4_0.csv"));
    current_file.writeFile(current_file_contents);

    std::string previous_file_contents = new_file_contents +
        "192.0.2.3,03:03:03:03:03:03,,200,200,8,1,1,,1,\n"
        "192.0.2.3,03:03:03:03:03:03,,200,800,8,1,1,,1,{ \"bar\": true }\n";
    LeaseFileIO previous_file(getLeaseFilePath("leasefile4_0.csv.2"));
    previous_file.writeFile(previous_file_contents);

    // Create the backend.
    DatabaseConnection::ParameterMap pmap;
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
    Lease4Ptr new_lease(new Lease4(IOAddress("192.0.2.45"), hwaddr,
                                   static_cast<const uint8_t*>(0), 0,
                                   100, 0, 1));
    ASSERT_NO_THROW(lease_mgr->addLease(new_lease));

    std::string updated_file_contents = new_file_contents +
        "192.0.2.45,00:00:00:00:00:00,,100,100,1,0,0,,0,\n";
    EXPECT_EQ(updated_file_contents, current_file.readFile());

    // This string contains the contents of the lease file we
    // expect after the LFC run.  It has two leases with one
    // entry each.
    std::string result_file_contents = new_file_contents +
        "192.0.2.2,02:02:02:02:02:02,,200,800,8,1,1,,1,\n"
        "192.0.2.3,03:03:03:03:03:03,,200,800,8,1,1,,1,{ \"bar\": true }\n";

    // The LFC should have created a file with the two leases and moved it
    // to leasefile4_0.csv.2
    LeaseFileIO input_file(getLeaseFilePath("leasefile4_0.csv.2"), false);
    ASSERT_TRUE(input_file.exists());
    // And this file should contain the contents of the result file.
    EXPECT_EQ(result_file_contents, input_file.readFile());
}

/// @brief This test checks that the callback function executing the cleanup of the
/// DHCPv6 lease file works as expected.
TEST_F(MemfileLeaseMgrTest, leaseFileCleanup6) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,duid,valid_lifetime,expire,subnet_id,"
        "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
        "fqdn_rev,hostname,hwaddr,state,user_context\n";

    // This string contains the contents of the lease file with exactly
    // one lease, but two entries. One of the entries should be removed
    // as a result of lease file cleanup.
    std::string current_file_contents = new_file_contents +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,200,"
        "8,100,0,7,0,1,1,,,1,\n"
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,,1,{ \"foo\": true }\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile6_0.csv"));
    current_file.writeFile(current_file_contents);

    std::string previous_file_contents = new_file_contents +
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,200,"
        "8,100,0,7,0,1,1,,,1,{ \"bar\": true }\n"
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,,1,\n";
    LeaseFileIO previous_file(getLeaseFilePath("leasefile6_0.csv.2"));
    previous_file.writeFile(previous_file_contents);

    // Create the backend.
    DatabaseConnection::ParameterMap pmap;
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
    Lease6Ptr new_lease(new Lease6(Lease::TYPE_NA, IOAddress("3000::1"), duid,
                                   123, 300, 400, 2));
    new_lease->cltt_ = 0;
    ASSERT_NO_THROW(lease_mgr->addLease(new_lease));

    std::string update_file_contents = new_file_contents +
        "3000::1,00:00:00:00:00:00:00:00:00:00:00:00:00,400,"
        "400,2,300,0,123,128,0,0,,,0,\n";
    EXPECT_EQ(update_file_contents, current_file.readFile());

    // This string contains the contents of the lease file we
    // expect after the LFC run.  It has two leases with one
    // entry each.
    std::string result_file_contents = new_file_contents +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,,1,{ \"foo\": true }\n"
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,,1,\n";

    // The LFC should have created a file with the two leases and moved it
    // to leasefile6_0.csv.2
    LeaseFileIO input_file(getLeaseFilePath("leasefile6_0.csv.2"), false);
    ASSERT_TRUE(input_file.exists());
    // And this file should contain the contents of the result file.
    EXPECT_EQ(result_file_contents, input_file.readFile());
}

/// @brief This test verifies that EXIT_FAILURE status code is returned when
/// the LFC process fails to start.
TEST_F(MemfileLeaseMgrTest, leaseFileCleanupStartFail) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,hwaddr,client_id,valid_lifetime,expire,"
        "subnet_id,fqdn_fwd,fqdn_rev,hostname,state,user_context\n";

    // Create the lease file to be used by the backend.
    std::string current_file_contents = new_file_contents +
        "192.0.2.2,02:02:02:02:02:02,,200,200,8,1,1,,1,\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile4_0.csv"));
    current_file.writeFile(current_file_contents);

    // Specify invalid path to the kea-lfc executable. This should result
    // in failure status code returned by the child process.
    setenv("KEA_LFC_EXECUTABLE", "foobar", 1);

    // Create the backend.
    DatabaseConnection::ParameterMap pmap;
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

/// @brief This test checks that the callback function executing the cleanup of the
/// files doesn't move the current file if the finish file exists
TEST_F(MemfileLeaseMgrTest, leaseFileFinish) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,duid,valid_lifetime,expire,subnet_id,"
        "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
        "fqdn_rev,hostname,hwaddr,state,user_context\n";

    // This string contains the contents of the current lease file.
    // It should not be moved.
    std::string current_file_contents = new_file_contents +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,200,"
        "8,100,0,7,0,1,1,,,1,\n"
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,,1,\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile6_0.csv"));
    current_file.writeFile(current_file_contents);

    // This string contains the contents of the finish file.  It should
    // be moved to the previous file.
    std::string finish_file_contents = new_file_contents +
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,,1,\n";
    LeaseFileIO finish_file(getLeaseFilePath("leasefile6_0.csv.completed"));
    finish_file.writeFile(finish_file_contents);

    // Create the backend.
    DatabaseConnection::ParameterMap pmap;
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

/// @brief This test checks that the callback function executing the cleanup of the
/// files doesn't move the current file if the copy file exists
TEST_F(MemfileLeaseMgrTest, leaseFileCopy) {
    // This string contains the lease file header, which matches
    // the contents of the new file in which no leases have been
    // stored.
    std::string new_file_contents =
        "address,duid,valid_lifetime,expire,subnet_id,"
        "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
        "fqdn_rev,hostname,hwaddr,state,user_context\n";

    // This string contains the contents of the current lease file.
    // It should not be moved.
    std::string current_file_contents = new_file_contents +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,200,"
        "8,100,0,7,0,1,1,,,1,\n"
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,,1,{ \"foo\": true }\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile6_0.csv"));
    current_file.writeFile(current_file_contents);

    // This string contains the contents of the copy file.  It should
    // be processed and moved to the previous file.  As there is only
    // one lease the processing should result in the previous file being
    // the same.
    std::string input_file_contents = new_file_contents +
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,,1,{ \"foo\": true }\n";
    LeaseFileIO input_file(getLeaseFilePath("leasefile6_0.csv.1"));
    input_file.writeFile(input_file_contents);

    // Create the backend.
    DatabaseConnection::ParameterMap pmap;
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

/// @brief Checks that adding/getting/deleting a Lease6 object works.
TEST_F(MemfileLeaseMgrTest, addGetDelete6) {
    startBackend(V6);
    testAddGetDelete6();
}

/// @brief Checks that adding/getting/deleting a Lease6 object works.
TEST_F(MemfileLeaseMgrTest, addGetDelete6MultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testAddGetDelete6();
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4 (by address) and deleteLease (with an
/// IPv4 address) works.
TEST_F(MemfileLeaseMgrTest, basicLease4) {
    startBackend(V4);
    testBasicLease4();
}

/// @brief Basic Lease4 Checks
TEST_F(MemfileLeaseMgrTest, basicLease4MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testBasicLease4();
}

/// @todo Write more memfile tests

/// @brief Simple test about lease4 retrieval through client id method
TEST_F(MemfileLeaseMgrTest, getLease4ClientId) {
    startBackend(V4);
    testGetLease4ClientId();
}

/// @brief Simple test about lease4 retrieval through client id method
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdMultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLease4ClientId();
}

/// @brief Checks that lease4 retrieval client id is null is working
TEST_F(MemfileLeaseMgrTest, getLease4NullClientId) {
    startBackend(V4);
    testGetLease4NullClientId();
}

/// @brief Checks that lease4 retrieval client id is null is working
TEST_F(MemfileLeaseMgrTest, getLease4NullClientIdMultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLease4NullClientId();
}

/// @brief Checks lease4 retrieval through HWAddr
TEST_F(MemfileLeaseMgrTest, getLease4HWAddr1) {
    startBackend(V4);
    testGetLease4HWAddr1();
}

/// @brief Checks lease4 retrieval through HWAddr
TEST_F(MemfileLeaseMgrTest, getLease4HWAddr1MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Check GetLease4 methods - access by Hardware Address
TEST_F(MemfileLeaseMgrTest, getLease4HWAddr2MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLease4HWAddr2();
}

/// @brief Checks lease4 retrieval with clientId, HWAddr and subnet_id
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdHWAddrSubnetId) {
    startBackend(V4);
    testGetLease4ClientIdHWAddrSubnetId();
}

/// @brief Checks lease4 retrieval with clientId, HWAddr and subnet_id
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdHWAddrSubnetIdMultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLease4ClientIdHWAddrSubnetId();
}

/// @brief Basic Lease4 Checks
///
/// Checks that the addLease, getLease4(by address), getLease4(hwaddr,subnet_id),
/// updateLease4() and deleteLease can handle NULL client-id.
/// (client-id is optional and may not be present)
TEST_F(MemfileLeaseMgrTest, lease4NullClientId) {
    startBackend(V4);
    testLease4NullClientId();
}

/// @brief Basic Lease4 Checks
TEST_F(MemfileLeaseMgrTest, lease4NullClientIdMultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Check GetLease4 methods - access by Hardware Address & Subnet ID
TEST_F(MemfileLeaseMgrTest, DISABLED_getLease4HwaddrSubnetIdMultiThread) {
    /// @todo: fails on memfile. It's probably a memfile bug.
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Check GetLease4 methods - access by Client ID
TEST_F(MemfileLeaseMgrTest, getLease4ClientId2MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLease4ClientId2();
}

/// @brief Get Lease4 by client ID
///
/// Check that the system can cope with a client ID of any size.
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdSize) {
    startBackend(V4);
    testGetLease4ClientIdSize();
}

/// @brief Get Lease4 by client ID
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdSizeMultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Check GetLease4 methods - access by Client ID & Subnet ID
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdSubnetIdMultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLease4ClientIdSubnetId();
}

/// @brief This test checks that all IPv4 leases for a specified subnet id are returned.
TEST_F(MemfileLeaseMgrTest, getLeases4SubnetId) {
    startBackend(V4);
    testGetLeases4SubnetId();
}

/// @brief This test checks that all IPv4 leases for a specified subnet id are returned.
TEST_F(MemfileLeaseMgrTest, getLeases4SubnetIdMultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases4SubnetId();
}

/// @brief This test checks that all IPv4 leases with a specified hostname are returned.
TEST_F(MemfileLeaseMgrTest, getLeases4Hostname) {
    startBackend(V4);
    testGetLeases4Hostname();
}

/// @brief This test checks that all IPv4 leases with a specified hostname are returned.
TEST_F(MemfileLeaseMgrTest, getLeases4HostnameMultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases4Hostname();
}

/// @brief This test checks that all IPv4 leases are returned.
TEST_F(MemfileLeaseMgrTest, getLeases4) {
    startBackend(V4);
    testGetLeases4();
}

/// @brief This test checks that all IPv4 leases are returned.
TEST_F(MemfileLeaseMgrTest, getLeases4MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases4();
}

/// @brief Test that a range of IPv4 leases is returned with paging.
TEST_F(MemfileLeaseMgrTest, getLeases4Paged) {
    startBackend(V4);
    testGetLeases4Paged();
}

/// @brief Test that a range of IPv4 leases is returned with paging.
TEST_F(MemfileLeaseMgrTest, getLeases4PagedMultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases4Paged();
}

/// @brief This test checks that all IPv6 leases for a specified subnet id are returned.
TEST_F(MemfileLeaseMgrTest, getLeases6SubnetId) {
    startBackend(V6);
    testGetLeases6SubnetId();
}

/// @brief This test checks that all IPv6 leases for a specified subnet id are returned.
TEST_F(MemfileLeaseMgrTest, getLeases6SubnetIdMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases6SubnetId();
}

/// @brief This test checks that all IPv6 leases with a specified hostname are returned.
TEST_F(MemfileLeaseMgrTest, getLeases6Hostname) {
    startBackend(V6);
    testGetLeases6Hostname();
}

/// @brief This test checks that all IPv6 leases with a specified hostname are returned.
TEST_F(MemfileLeaseMgrTest, getLeases6HostnameMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases6Hostname();
}

/// @brief This test adds 3 leases  and verifies fetch by DUID.
/// Verifies retrival of non existant DUID fails
TEST_F(MemfileLeaseMgrTest, getLeases6Duid) {
    startBackend(V6);
    testGetLeases6Duid();
}

/// @brief This test adds 3 leases  and verifies fetch by DUID.
TEST_F(MemfileLeaseMgrTest, getLeases6DuidMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases6Duid();
}

/// @brief This test checks that all IPv6 leases are returned.
TEST_F(MemfileLeaseMgrTest, getLeases6) {
    startBackend(V6);
    testGetLeases6();
}

/// @brief This test checks that all IPv6 leases are returned.
TEST_F(MemfileLeaseMgrTest, getLeases6MultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases6();
}

/// @brief Test that a range of IPv6 leases is returned with paging.
TEST_F(MemfileLeaseMgrTest, getLeases6Paged) {
    startBackend(V6);
    testGetLeases6Paged();
}

/// @brief Test that a range of IPv6 leases is returned with paging.
TEST_F(MemfileLeaseMgrTest, getLeases6PagedMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases6Paged();
}

/// @brief Basic Lease6 Checks
///
/// Checks that the addLease, getLease6 (by address) and deleteLease (with an
/// IPv6 address) works.
TEST_F(MemfileLeaseMgrTest, basicLease6) {
    startBackend(V6);
    testBasicLease6();
}

/// @brief Basic Lease6 Checks
TEST_F(MemfileLeaseMgrTest, basicLease6MultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Check GetLease6 methods - access by DUID/IAID
TEST_F(MemfileLeaseMgrTest, getLeases6DuidIaidMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testGetLeases6DuidIaid();
}

/// @brief Check that the system can cope with a DUID of allowed size.
TEST_F(MemfileLeaseMgrTest, getLeases6DuidSize) {
    startBackend(V6);
    testGetLeases6DuidSize();
}

/// @brief Check that the system can cope with a DUID of allowed size.
TEST_F(MemfileLeaseMgrTest, getLeases6DuidSizeMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Check that the expired DHCPv4 leases can be retrieved.
TEST_F(MemfileLeaseMgrTest, getExpiredLeases4MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Check that the expired DHCPv6 leases can be retrieved.
TEST_F(MemfileLeaseMgrTest, getExpiredLeases6MultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testGetExpiredLeases6();
}

/// @brief Check that expired reclaimed DHCPv6 leases are removed.
TEST_F(MemfileLeaseMgrTest, deleteExpiredReclaimedLeases6) {
    startBackend(V6);
    testDeleteExpiredReclaimedLeases6();
}

/// @brief Check that expired reclaimed DHCPv6 leases are removed.
TEST_F(MemfileLeaseMgrTest, deleteExpiredReclaimedLeases6MultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testDeleteExpiredReclaimedLeases6();
}

/// @brief Check that expired reclaimed DHCPv4 leases are removed.
TEST_F(MemfileLeaseMgrTest, deleteExpiredReclaimedLeases4) {
    startBackend(V4);
    testDeleteExpiredReclaimedLeases4();
}

/// @brief Check that expired reclaimed DHCPv4 leases are removed.
TEST_F(MemfileLeaseMgrTest, deleteExpiredReclaimedLeases4MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Check that getLease6 methods discriminate by lease type.
TEST_F(MemfileLeaseMgrTest, lease6LeaseTypeCheckMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Check GetLease6 methods - access by DUID/IAID/SubnetID
TEST_F(MemfileLeaseMgrTest, getLease6DuidIaidSubnetIdMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testGetLease6DuidIaidSubnetId();
}

/// @brief Checks that getLease6(type, duid, iaid, subnet-id) works with different
/// DUID sizes
TEST_F(MemfileLeaseMgrTest, getLease6DuidIaidSubnetIdSize) {
    startBackend(V6);
    testGetLease6DuidIaidSubnetIdSize();
}

/// @brief Checks that getLease6(type, duid, iaid, subnet-id) works with different
/// DUID sizes
TEST_F(MemfileLeaseMgrTest, getLease6DuidIaidSubnetIdSizeMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Lease4 update tests
TEST_F(MemfileLeaseMgrTest, DISABLED_updateLease4MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Lease6 update tests
TEST_F(MemfileLeaseMgrTest, DISABLED_updateLease6MultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief DHCPv4 Lease recreation tests
TEST_F(MemfileLeaseMgrTest, testRecreateLease4MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief DHCPv6 Lease recreation tests
TEST_F(MemfileLeaseMgrTest, testRecreateLease6MultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Checks that null DUID is not allowed.
TEST_F(MemfileLeaseMgrTest, DISABLED_nullDuidMultiThread) {
    MultiThreadingMgr::instance().setMode(true);
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

/// @brief Tests whether memfile can store and retrieve hardware addresses
TEST_F(MemfileLeaseMgrTest, testLease6MacMultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testLease6MAC();
}

/// @brief Check that memfile reports version correctly.
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

/// @brief Checks that declined IPv4 leases can be returned correctly.
TEST_F(MemfileLeaseMgrTest, getDeclined4) {
    startBackend(V4);
    testGetDeclinedLeases4();
}

/// @brief Checks that declined IPv4 leases can be returned correctly.
TEST_F(MemfileLeaseMgrTest, getDeclined4MultiThread) {
    startBackend(V4);
    MultiThreadingMgr::instance().setMode(true);
    testGetDeclinedLeases4();
}

/// @brief Checks that declined IPv6 leases can be returned correctly.
TEST_F(MemfileLeaseMgrTest, getDeclined6) {
    startBackend(V6);
    testGetDeclinedLeases6();
}

/// @brief Checks that declined IPv6 leases can be returned correctly.
TEST_F(MemfileLeaseMgrTest, getDeclined6MultiThread) {
    startBackend(V6);
    MultiThreadingMgr::instance().setMode(true);
    testGetDeclinedLeases6();
}

/// @brief This test checks that the backend reads DHCPv4 lease data from multiple
/// files.
TEST_F(MemfileLeaseMgrTest, load4MultipleLeaseFiles) {
    LeaseFileIO io2(getLeaseFilePath("leasefile4_0.csv.2"));
    io2.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
                  "192.0.2.2,02:02:02:02:02:02,,200,200,8,1,1,,1,\n"
                  "192.0.2.11,bb:bb:bb:bb:bb:bb,,200,200,8,1,1,,1,\n");

    LeaseFileIO io1(getLeaseFilePath("leasefile4_0.csv.1"));
    io1.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
                  "192.0.2.1,01:01:01:01:01:01,,200,200,8,1,1,,1,\n"
                  "192.0.2.11,bb:bb:bb:bb:bb:bb,,200,400,8,1,1,,1,\n"
                  "192.0.2.12,cc:cc:cc:cc:cc:cc,,200,200,8,1,1,,1,\n");

    LeaseFileIO io(getLeaseFilePath("leasefile4_0.csv"));
    io.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                 "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
                 "192.0.2.10,0a:0a:0a:0a:0a:0a,,200,200,8,1,1,,1,\n"
                 "192.0.2.12,cc:cc:cc:cc:cc:cc,,200,400,8,1,1,,1,\n");

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

/// @brief This test checks that the lease database backend loads the file with
/// the .completed postfix instead of files with postfixes .1 and .2 if
/// the file with .completed postfix exists.
TEST_F(MemfileLeaseMgrTest, load4CompletedFile) {
    LeaseFileIO io2(getLeaseFilePath("leasefile4_0.csv.2"));
    io2.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
                  "192.0.2.2,02:02:02:02:02:02,,200,200,8,1,1,,1,\n"
                  "192.0.2.11,bb:bb:bb:bb:bb:bb,,200,200,8,1,1,,1,\n");

    LeaseFileIO io1(getLeaseFilePath("leasefile4_0.csv.1"));
    io1.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
                  "192.0.2.1,01:01:01:01:01:01,,200,200,8,1,1,,1,\n"
                  "192.0.2.11,bb:bb:bb:bb:bb:bb,,200,400,8,1,1,,1,\n"
                  "192.0.2.12,cc:cc:cc:cc:cc:cc,,200,200,8,1,1,,1,\n");

    LeaseFileIO io(getLeaseFilePath("leasefile4_0.csv"));
    io.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                 "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
                 "192.0.2.10,0a:0a:0a:0a:0a:0a,,200,200,8,1,1,,1,\n"
                 "192.0.2.12,cc:cc:cc:cc:cc:cc,,200,400,8,1,1,,1,\n");

    LeaseFileIO ioc(getLeaseFilePath("leasefile4_0.csv.completed"));
    ioc.writeFile("address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname,state,user_context\n"
                  "192.0.2.13,ff:ff:ff:ff:ff:ff,,200,200,8,1,1,,1,\n");

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

/// @brief This test checks that backend constructor refuses to load leases from the
/// lease files if the LFC is in progress.
TEST_F(MemfileLeaseMgrTest, load4LFCInProgress) {
    // Create the backend configuration.
    DatabaseConnection::ParameterMap pmap;
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

    // Remove the pid file, and retry. The backend should be created.
    pid_file.deleteFile();
    ASSERT_NO_THROW(lease_mgr.reset(new NakedMemfileLeaseMgr(pmap)));
}

/// @brief This test checks that the backend reads DHCPv6 lease data from multiple
/// files.
TEST_F(MemfileLeaseMgrTest, load6MultipleLeaseFiles) {
    LeaseFileIO io2(getLeaseFilePath("leasefile6_0.csv.2"));
    io2.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                  "2001:db8:1::1,01:01:01:01:01:01:01:01:01:01:01:01:01,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n");

    LeaseFileIO io1(getLeaseFilePath("leasefile6_0.csv.1"));
    io1.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                  "2001:db8:1::3,03:03:03:03:03:03:03:03:03:03:03:03:03,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "300,800,8,100,0,7,0,1,1,,,1,\n"
                  "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n");

    LeaseFileIO io(getLeaseFilePath("leasefile6_0.csv"));
    io.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                 "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                 "400,1000,8,100,0,7,0,1,1,,,1,\n"
                 "2001:db8:1::5,05:05:05:05:05:05:05:05:05:05:05:05:05,"
                 "200,200,8,100,0,7,0,1,1,,,1,\n");

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

/// @brief This test checks that the backend reads DHCPv6 lease data from the
/// leasefile without the postfix and the file with a .1 postfix when
/// the file with the .2 postfix is missing.
TEST_F(MemfileLeaseMgrTest, load6MultipleNoSecondFile) {
    LeaseFileIO io1(getLeaseFilePath("leasefile6_0.csv.1"));
    io1.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                  "2001:db8:1::3,03:03:03:03:03:03:03:03:03:03:03:03:03,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "300,800,8,100,0,7,0,1,1,,,1,\n"
                  "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n");

    LeaseFileIO io(getLeaseFilePath("leasefile6_0.csv"));
    io.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                 "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                 "400,1000,8,100,0,7,0,1,1,,,1,\n"
                 "2001:db8:1::5,05:05:05:05:05:05:05:05:05:05:05:05:05,"
                 "200,200,8,100,0,7,0,1,1,,,1,\n");

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

/// @brief This test checks that the backend reads DHCPv6 lease data from the
/// leasefile without the postfix and the file with a .2 postfix when
/// the file with the .1 postfix is missing.
TEST_F(MemfileLeaseMgrTest, load6MultipleNoFirstFile) {
    LeaseFileIO io2(getLeaseFilePath("leasefile6_0.csv.2"));
    io2.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                  "2001:db8:1::1,01:01:01:01:01:01:01:01:01:01:01:01:01,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n");

    LeaseFileIO io(getLeaseFilePath("leasefile6_0.csv"));
    io.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                 "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                 "400,1000,8,100,0,7,0,1,1,,,1,\n"
                 "2001:db8:1::5,05:05:05:05:05:05:05:05:05:05:05:05:05,"
                 "200,200,8,100,0,7,0,1,1,,,1,\n");

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

/// @brief This test checks that the lease database backend loads the file with
/// the .completed postfix instead of files with postfixes .1 and .2 if
/// the file with .completed postfix exists.
TEST_F(MemfileLeaseMgrTest, load6CompletedFile) {
    LeaseFileIO io2(getLeaseFilePath("leasefile6_0.csv.2"));
    io2.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                  "2001:db8:1::1,01:01:01:01:01:01:01:01:01:01:01:01:01,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n");

    LeaseFileIO io1(getLeaseFilePath("leasefile6_0.csv.1"));
    io1.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                  "2001:db8:1::3,03:03:03:03:03:03:03:03:03:03:03:03:03,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n"
                  "2001:db8:1::2,02:02:02:02:02:02:02:02:02:02:02:02:02,"
                  "300,800,8,100,0,7,0,1,1,,,1,\n"
                  "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                  "200,200,8,100,0,7,0,1,1,,,1,\n");

    LeaseFileIO io(getLeaseFilePath("leasefile6_0.csv"));
    io.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                 "2001:db8:1::4,04:04:04:04:04:04:04:04:04:04:04:04:04,"
                 "400,1000,8,100,0,7,0,1,1,,,1,\n"
                 "2001:db8:1::5,05:05:05:05:05:05:05:05:05:05:05:05:05,"
                 "200,200,8,100,0,7,0,1,1,,,1,\n");

    LeaseFileIO ioc(getLeaseFilePath("leasefile6_0.csv.completed"));
    ioc.writeFile("address,duid,valid_lifetime,expire,subnet_id,pref_lifetime,"
                  "lease_type,iaid,prefix_len,fqdn_fwd,fqdn_rev,hostname,"
                  "hwaddr,state,user_context\n"
                  "2001:db8:1::125,ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff,"
                  "400,1000,8,100,0,7,0,1,1,,,1,\n");

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

/// @brief This test checks that backend constructor refuses to load leases from the
/// lease files if the LFC is in progress.
TEST_F(MemfileLeaseMgrTest, load6LFCInProgress) {
    // Create the backend configuration.
    DatabaseConnection::ParameterMap pmap;
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

    // Remove the pid file, and retry. The backend should be created.
    pid_file.deleteFile();
    ASSERT_NO_THROW(lease_mgr.reset(new NakedMemfileLeaseMgr(pmap)));
}

/// @brief Verifies that LFC is automatically run during MemfileLeasemMgr construction
/// when the lease file(s) being loaded need to be upgraded.
TEST_F(MemfileLeaseMgrTest, leaseUpgrade4) {
    // Create header strings for each schema
    std::string header_1_0 =
        "address,hwaddr,client_id,valid_lifetime,expire,"
        "subnet_id,fqdn_fwd,fqdn_rev,hostname\n";

    std::string header_2_0 =
        "address,hwaddr,client_id,valid_lifetime,expire,"
        "subnet_id,fqdn_fwd,fqdn_rev,hostname,state,user_context\n";

    // Create 1.0 Schema current lease file with two entries for
    // the same lease
    std::string current_file_contents = header_1_0 +
        "192.0.2.2,02:02:02:02:02:02,,200,200,8,1,1,\n"
        "192.0.2.2,02:02:02:02:02:02,,200,800,8,1,1,\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile4_0.csv"));
    current_file.writeFile(current_file_contents);

    // Create 1.0 Schema previous lease file, with two entries for
    // a another lease
    std::string previous_file_contents = header_1_0 +
        "192.0.2.3,03:03:03:03:03:03,,200,200,8,1,1,\n"
        "192.0.2.3,03:03:03:03:03:03,,200,800,8,1,1,\n";
    LeaseFileIO previous_file(getLeaseFilePath("leasefile4_0.csv.2"));
    previous_file.writeFile(previous_file_contents);

    // Create the backend.
    DatabaseConnection::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "4";
    pmap["name"] = getLeaseFilePath("leasefile4_0.csv");
    pmap["lfc-interval"] = "0";
    boost::scoped_ptr<NakedMemfileLeaseMgr> lease_mgr(new NakedMemfileLeaseMgr(pmap));

    // Since lease files are loaded during lease manager
    // constructor, LFC should get launched automatically.
    // The new lease file should be 2.0 schema and have no entries
    ASSERT_TRUE(current_file.exists());
    EXPECT_EQ(header_2_0, current_file.readFile());

    // Wait for the LFC process to complete and
    // make sure it has returned an exit status of 0.
    ASSERT_TRUE(waitForProcess(*lease_mgr, 2));
    ASSERT_EQ(0, lease_mgr->getLFCExitStatus())
        << "Executing the LFC process failed: make sure that"
        " the kea-lfc program has been compiled.";

    // The LFC should have created a 2.0 schema completion file with the
    // one entry for each lease and moved it to leasefile4_0.csv.2
    LeaseFileIO input_file(getLeaseFilePath("leasefile4_0.csv.2"), false);
    ASSERT_TRUE(input_file.exists());

    // Verify cleaned, converted contents
    std::string result_file_contents = header_2_0 +
        "192.0.2.2,02:02:02:02:02:02,,200,800,8,1,1,,0,\n"
        "192.0.2.3,03:03:03:03:03:03,,200,800,8,1,1,,0,\n";
    EXPECT_EQ(result_file_contents, input_file.readFile());
}

/// @brief Verifies that LFC is automatically run during MemfileLeasemMgr construction
/// when the lease file(s) being loaded need to be upgraded.
TEST_F(MemfileLeaseMgrTest, leaseUpgrade6) {
    // Create header strings for all three schemas
    std::string header_1_0 =
        "address,duid,valid_lifetime,expire,subnet_id,"
        "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
        "fqdn_rev,hostname\n";

    std::string header_2_0 =
        "address,duid,valid_lifetime,expire,subnet_id,"
        "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
        "fqdn_rev,hostname,hwaddr\n";

    std::string header_3_0 =
        "address,duid,valid_lifetime,expire,subnet_id,"
        "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
        "fqdn_rev,hostname,hwaddr,state,user_context\n";

    // The current lease file is schema 1.0 and has two entries for
    // the same lease
    std::string current_file_contents = header_1_0 +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,200,"
        "8,100,0,7,0,1,1,,\n"
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,\n";
    LeaseFileIO current_file(getLeaseFilePath("leasefile6_0.csv"));
    current_file.writeFile(current_file_contents);

    // The previous lease file is schema 2.0 and has two entries for
    // a different lease
    std::string previous_file_contents = header_2_0 +
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,200,"
        "8,100,0,7,0,1,1,,11:22:33:44:55\n"
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,11:22:33:44:55\n";
    LeaseFileIO previous_file(getLeaseFilePath("leasefile6_0.csv.2"));
    previous_file.writeFile(previous_file_contents);

    // Create the backend.
    DatabaseConnection::ParameterMap pmap;
    pmap["type"] = "memfile";
    pmap["universe"] = "6";
    pmap["name"] = getLeaseFilePath("leasefile6_0.csv");
    pmap["lfc-interval"] = "0";
    boost::scoped_ptr<NakedMemfileLeaseMgr> lease_mgr(new NakedMemfileLeaseMgr(pmap));

    // Since lease files are loaded during lease manager
    // constructor, LFC should get launched automatically.
    // The new lease file should been 3.0 and contain no leases.
    ASSERT_TRUE(current_file.exists());
    EXPECT_EQ(header_3_0, current_file.readFile());

    // Wait for the LFC process to complete and
    // make sure it has returned an exit status of 0.
    ASSERT_TRUE(waitForProcess(*lease_mgr, 2));
    ASSERT_EQ(0, lease_mgr->getLFCExitStatus())
        << "Executing the LFC process failed: make sure that"
        " the kea-lfc program has been compiled.";

    // The LFC should have created a 3.0 schema cleaned file with one entry
    // for each lease as leasefile6_0.csv.2
    LeaseFileIO input_file(getLeaseFilePath("leasefile6_0.csv.2"), false);
    ASSERT_TRUE(input_file.exists());

    // Verify cleaned, converted contents
    std::string result_file_contents = header_3_0 +
        "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,200,800,"
        "8,100,0,7,0,1,1,,,0,\n"
        "2001:db8:1::2,01:01:01:01:01:01:01:01:01:01:01:01:01,200,800,"
        "8,100,0,7,0,1,1,,11:22:33:44:55,0,\n";
    EXPECT_EQ(result_file_contents, input_file.readFile());
}

/// @brief This test verifies that the indexes of the container holding
/// DHCPv4 leases are updated correctly when a lease is updated.
TEST_F(MemfileLeaseMgrTest, lease4ContainerIndexUpdate) {

    const uint32_t seed = 12345678; // Used to initialize the random generator
    const uint32_t leases_cnt = 100; // Number of leases generated per round.
    const uint32_t updates_cnt = 5; // Number of times existing leases are updated

    const string leasefile(getLeaseFilePath("leasefile4_0.csv"));

    // Parameters for the lease file. Make sure the leases are persistent, so they
    // are written to disk.
    DatabaseConnection::ParameterMap pmap;
    pmap["universe"] = "4";
    pmap["name"] = leasefile;
    pmap["persist"] = "true";
    pmap["lfc-interval"] = "0";

    srand(seed);

    IOAddress addr("10.0.0.1"); // Let's generate leases sequentially

    // Recreate Memfile_LeaseMgr.
    LeaseMgrFactory::destroy();
    ASSERT_NO_THROW(lmptr_ = new Memfile_LeaseMgr(pmap));

    // We will store addresses here, so it will be easier to randomly
    // pick a lease.
    std::vector<IOAddress> lease_addresses;

    // Generate random leases. We remember their addresses in
    // lease_addresses.
    for (uint32_t i = 0; i < leases_cnt; ++i) {
        Lease4Ptr lease = initiateRandomLease4(addr);
        lease_addresses.push_back(addr);
        ASSERT_NO_THROW(lmptr_->addLease(lease));
        addr = IOAddress::increase(addr);
    }

    // Check that we inserted correct number of leases.
    ASSERT_EQ(leases_cnt, lease_addresses.size());

    // Now, conduct updates. We call initiateRandomLease4(), so most
    // of the fields are randomly changed. The only constant field
    // is the address.
    for (uint32_t i = 0; i < updates_cnt; ++i) {
        uint32_t offset = random() % lease_addresses.size();
        Lease4Ptr existing(lmptr_->getLease4(lease_addresses[offset]));
        Lease4Ptr updated(initiateRandomLease4(lease_addresses[offset]));

        // Update a lease with new data but preserve lease address.
        // This update should also cause lease container indexes to
        // be updated.
        ASSERT_NO_THROW(lmptr_->updateLease4(updated))
            << "Attempt " << i << " out of " << updates_cnt
            << ":Failed to update lease for address "
            << lease_addresses[offset];
    }

    // Re-create lease manager to cause it to reload leases
    // from a lease file. We want to make sure that lease
    // container is rebuilt correctly and the indexes are
    // consistent with lease information held.
    ASSERT_NO_THROW({
        LeaseMgrFactory::destroy();
        lmptr_ = new Memfile_LeaseMgr(pmap);
    });

    // Ok, let's check if the leases are really accessible.
    // First, build an array of leases. Get them by address.
    // This should work in general, as we haven't updated the addresses.
    std::vector<Lease4Ptr> leases;
    for (uint32_t i = 0; i < lease_addresses.size(); ++i) {
        Lease4Ptr from_mgr = lmptr_->getLease4(lease_addresses[i]);
        ASSERT_TRUE(from_mgr) << "Lease for address " << lease_addresses[i].toText()
                              << " not found";
        leases.push_back(from_mgr);
    }

    ASSERT_EQ(leases_cnt, leases.size());

    // Now do the actual checks.
    for (uint32_t i = 0; i < leases.size(); ++i) {
        Lease4Ptr tested = leases[i];

        // Get the lease by different access patterns.
        // In properly working lease manager all queries should return
        // exactly the same lease.

        std::string error_desc = " which indicates that the lease indexes were"
            " not updated correctly when the lease was updated.";

        // Retrieve lease by address.
        Lease4Ptr lease_by_address = lmptr_->getLease4(tested->addr_);
        ASSERT_TRUE(lease_by_address)
            << "Lease " << tested->addr_.toText()
            << " not found by getLease4(addr)"
            << error_desc;
        detailCompareLease(tested, lease_by_address);

        // Retrieve lease by HW address and subnet id.
        Lease4Ptr lease_by_hwaddr_subnet = lmptr_->getLease4(*tested->hwaddr_,
                                                             tested->subnet_id_);
        ASSERT_TRUE(lease_by_hwaddr_subnet)
            << "Lease " << tested->addr_.toText()
            << " not found by getLease4(hwaddr, subnet_id)"
            << error_desc;
        detailCompareLease(tested, lease_by_hwaddr_subnet);

        // Retrieve lease by client identifier and subnet id.
        Lease4Ptr lease_by_clientid_subnet = lmptr_->getLease4(*tested->client_id_,
                                                               tested->subnet_id_);
        ASSERT_TRUE(lease_by_clientid_subnet)
            << "Lease " << tested->addr_.toText()
            << " not found by getLease4(clientid, subnet_id)"
            << error_desc;
        detailCompareLease(tested, lease_by_clientid_subnet);

        // Retrieve lease by client id, HW address and subnet.
        Lease4Ptr lease_by_clientid_hwaddr_subnet = lmptr_->getLease4(*tested->client_id_,
                                                                      *tested->hwaddr_,
                                                                      tested->subnet_id_);
        ASSERT_TRUE(lease_by_clientid_hwaddr_subnet)
            << "Lease " << tested->addr_.toText()
            << " not found by getLease4(clientid, hwaddr, subnet_id)"
            << error_desc;
        detailCompareLease(tested, lease_by_clientid_hwaddr_subnet);

        // Retrieve lease by HW address.
        Lease4Collection leases_by_hwaddr = lmptr_->getLease4(*tested->hwaddr_);
        ASSERT_EQ(1, leases_by_hwaddr.size());
        detailCompareLease(tested, leases_by_hwaddr[0]);

        // Retrieve lease by client identifier.
        Lease4Collection leases_by_client_id = lmptr_->getLease4(*tested->client_id_);
        ASSERT_EQ(1, leases_by_client_id.size());
        detailCompareLease(tested, leases_by_client_id[0]);
    }
}

/// @brief This test verifies that the indexes of the container holding
/// DHCPv4 leases are updated correctly when a lease is updated.
TEST_F(MemfileLeaseMgrTest, lease6ContainerIndexUpdate) {

    const uint32_t seed = 12345678; // Used to initialize the random generator
    const uint32_t leases_cnt = 100; // Number of leases generated per round.
    const uint32_t updates_cnt = 5; // Number of times existing leases are updated

    const string leasefile(getLeaseFilePath("leasefile6_0.csv"));

    // Parameters for the lease file. Make sure the leases are persistent, so they
    // are written to disk.
    DatabaseConnection::ParameterMap pmap;
    pmap["universe"] = "6";
    pmap["name"] = leasefile;
    pmap["persist"] = "true";
    pmap["lfc-interval"] = "0";

    srand(seed);

    IOAddress addr("2001:db8:1::1"); // Let's generate leases sequentially

    // Recreate Memfile_LeaseMgr.
    LeaseMgrFactory::destroy();
    ASSERT_NO_THROW(lmptr_ = new Memfile_LeaseMgr(pmap));

    // We will store addresses here, so it will be easier to randomly
    // pick a lease.
    std::vector<IOAddress> lease_addresses;

    // Generate random leases. We remember their addresses in
    // lease_addresses.
    for (uint32_t i = 0; i < leases_cnt; ++i) {
        Lease6Ptr lease = initiateRandomLease6(addr);
        lease_addresses.push_back(addr);
        ASSERT_NO_THROW(lmptr_->addLease(lease));
        addr = IOAddress::increase(addr);
    }

    // Check that we inserted correct number of leases.
    ASSERT_EQ(leases_cnt, lease_addresses.size());

    // Now, conduct updates. We call initiateRandomLease6(), so most
    // of the fields are randomly changed. The only constant field
    // is the address.
    for (uint32_t i = 0; i < updates_cnt; ++i) {
        uint32_t offset = random() % lease_addresses.size();
        Lease6Ptr existing(lmptr_->getLease6(Lease::TYPE_NA,
                                             lease_addresses[offset]));
        Lease6Ptr updated(initiateRandomLease6(lease_addresses[offset]));

        // Update a lease with new data but preserve lease address.
        // This update should also cause lease container indexes to
        // be updated.
        ASSERT_NO_THROW(lmptr_->updateLease6(updated))
            << "Attempt " << i << " out of " << updates_cnt
            << ":Failed to update lease for address "
            << lease_addresses[offset];
    }

    // Re-create lease manager to cause it to reload leases
    // from a lease file. We want to make sure that lease
    // container is rebuilt correctly and the indexes are
    // consistent with lease information held.
    ASSERT_NO_THROW({
        LeaseMgrFactory::destroy();
        lmptr_ = new Memfile_LeaseMgr(pmap);
    });

    // Ok, let's check if the leases are really accessible.
    // First, build an array of leases. Get them by address.
    // This should work in general, as we haven't updated the addresses.
    std::vector<Lease6Ptr> leases;
    for (uint32_t i = 0; i < lease_addresses.size(); ++i) {
        Lease6Ptr from_mgr = lmptr_->getLease6(Lease::TYPE_NA,
                                               lease_addresses[i]);
        ASSERT_TRUE(from_mgr) << "Lease for address " << lease_addresses[i].toText()
                              << " not found";
        leases.push_back(from_mgr);
    }

    ASSERT_EQ(leases_cnt, leases.size());

    // Now do the actual checks.
    for (uint32_t i = 0; i < leases.size(); ++i) {
        Lease6Ptr tested = leases[i];

        // Get the lease by different access patterns.
        // In properly working lease manager all queries should return
        // exactly the same lease.

        std::string error_desc = " which indicates that the lease indexes were"
            " not updated correctly when the lease was updated.";

        // Retrieve lease by address.
        Lease6Ptr lease_by_address = lmptr_->getLease6(Lease::TYPE_NA,
                                                       tested->addr_);
        ASSERT_TRUE(lease_by_address)
            << "Lease " << tested->addr_.toText()
            << " not found by getLease6(addr)"
            << error_desc;
        detailCompareLease(tested, lease_by_address);

        // Retrieve lease by type, DUID, IAID.
        Lease6Collection leases_by_duid_iaid = lmptr_->getLeases6(tested->type_,
                                                                  *tested->duid_,
                                                                  tested->iaid_);
        ASSERT_EQ(1, leases_by_duid_iaid.size());
        ASSERT_TRUE(leases_by_duid_iaid[0])
            << "Lease " << tested->addr_.toText()
            << " not found by getLease6(type, duid, iaid)"
            << error_desc;
        detailCompareLease(tested, leases_by_duid_iaid[0]);

        // Retrieve lease by type, DUID, IAID, subnet identifier.
        Lease6Collection leases_by_duid_iaid_subnet =
            lmptr_->getLeases6(tested->type_, *tested->duid_,
                               tested->iaid_, tested->subnet_id_);
        ASSERT_EQ(1, leases_by_duid_iaid_subnet.size());
        ASSERT_TRUE(leases_by_duid_iaid_subnet[0])
            << "Lease " << tested->addr_.toText()
            << " not found by getLease6(type, duid, iaid, subnet_id)"
            << error_desc;
        detailCompareLease(tested, leases_by_duid_iaid_subnet[0]);
    }
}

/// @brief Verifies that IPv4 lease statistics can be recalculated.
TEST_F(MemfileLeaseMgrTest, recountLeaseStats4) {
    startBackend(V4);
    testRecountLeaseStats4();
}

/// @brief Verifies that IPv6 lease statistics can be recalculated.
TEST_F(MemfileLeaseMgrTest, recountLeaseStats6) {
    startBackend(V6);
    testRecountLeaseStats6();
}

/// @brief Tests that leases from specific subnet can be removed.
TEST_F(MemfileLeaseMgrTest, wipeLeases4) {
    startBackend(V4);
    testWipeLeases4();
}

/// @brief Tests that leases from specific subnet can be removed.
TEST_F(MemfileLeaseMgrTest, wipeLeases6) {
    startBackend(V6);
    testWipeLeases6();
}

/// @brief Tests v4 lease stats query variants.
TEST_F(MemfileLeaseMgrTest, leaseStatsQuery4) {
    startBackend(V4);
    testLeaseStatsQuery4();
}

/// @brief Tests v6 lease stats query variants.
TEST_F(MemfileLeaseMgrTest, leaseStatsQuery6) {
    startBackend(V6);
    testLeaseStatsQuery6();
}

}  // namespace
