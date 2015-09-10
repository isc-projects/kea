// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/duid.h>
#include <dhcp/option_data_types.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <dhcpsrv/tests/test_utils.h>
#include <gtest/gtest.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/static_assert.hpp>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <vector>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::dhcp_ddns;

namespace {

/// @brief Number of leases to be initialized for each test.
///
/// This value is expected by some of the tests to be multiple
/// of 10.
const unsigned int TEST_LEASES_NUM = 100;

/// @brief Structure wrapping a lower limit within the collection
/// of leases.
///
/// We're using this structure rather than a size_t value directly
/// to make API of the test fixture class more readable, i.e. the
/// struct name indicates the purpose of the value being held.
struct LowerBound {
    /// @brief Constructor.
    ///
    /// @param lower_bound Interger value wrapped by the structure.
    explicit LowerBound(const size_t lower_bound)
        : lower_bound_(lower_bound) { };

    /// @brief Operator returning the size_t value wrapped.
    operator size_t() const {
        return (lower_bound_);
    }

    /// @brief Value wrapped in the structure.
    size_t lower_bound_;
};

/// @brief Structure wrapping an upper limit within the collection
/// of leases.
///
/// We're using this structure rather than a size_t value directly
/// to make API of the test fixture class more readable, i.e. the
/// struct name indicates the purpose of the value being held.
struct UpperBound {
    /// @brief Constructor.
    ///
    /// @param lower_bound Interger value wrapped by the structure.
    explicit UpperBound(const size_t upper_bound)
        : upper_bound_(upper_bound) { };

    /// @brief Operator returning the size_t value wrapped.
    operator size_t() const {
        return (upper_bound_);
    }

    /// @brief Value wrapped in the structure.
    size_t upper_bound_;
};

/// @brief Base test fixture class for the lease reclamation routines in the
/// @c AllocEngine.
///
/// This class implements infrastructure for testing leases reclamation
/// routines. The lease reclamation routine has the following
/// characteristic:
/// - it processes multiple leases,
/// - leases are processed in certain order,
/// - number of processed leases may be limited by the parameters,
/// - maxium duration of the lease reclamation routine may be limited,
/// - reclaimed leases may be marked as reclaimed or deleted,
/// - DNS records for some of the leases must be removed when the lease
///   is reclaimed and DNS updates are enabled,
/// - hooks must be invoked (if installed) for each reclaimed lease
///
/// The typical test requires many leases to be initialized and stored
/// in the lease database for the test. The test fixture class creates
/// these leases upon construction. It is possible to modify these
/// leases to test various properties of the lease reclamation routine
/// as listed above. For example: some of the leases may be marked
/// as expired or hostname may be cleared for some of the leases to
/// check that DNS updates are not generated for them.
///
/// The tests are built around the
/// @c ExpirationAllocEngineTest::testLeases methods. These methods
/// verify that the certain operations have been performed by the
/// lease reclamation routine on selected leases. The leases for which
/// certain conditions should be met are selected using the "index
/// algorithms". Various index algorithms are implemented in the
/// test fixture class as static functions and the algorithm is
/// selected by passing function pointer to the @c testLeases method.
///
/// Examples of index algorithms are:
/// - evenLeaseIndex(index) - picks even index numbers,
/// - oddLeaseIndex(index) - picks odd index numbers,
/// - allLeasesIndexes(index) - picks all index number.
///
/// For example, the test may use the @c evenLeaseIndex algorithm
/// to mark leases with even indexes as expired and then test whether
/// leases with even indexes have been successfully reclaimed.
///
/// The "lease algorithm" verifies if the given lease fulfils the
/// specific conditions after reclamation. These are the examples of
/// the lease algorithms:
/// - leaseExists - lease still exists in the database,
/// - leaseDoesntExist - lease removed from the database,
/// - leaseReclaimed - lease exists but has reclaimed status,
/// - leaseNotReclaimed - lease exists and is not in the reclaimed status,
/// - dnsUpdateGeneratedForLease - DNS updates generated for lease,
/// - dnsUpdateNotGeneratedForLease - DNS updates not generated for lease
///
/// The combination of index algorithm and lease algorithm allows for
/// verifying that the whole sets of leases in the lease database fulfil
/// certain conditions. For example, it is possible to verify that
/// after lease reclamation leases with even indexes have state set to
/// "expired-reclaimed".
///
/// See @c ExpirationAllocEngineTest::testLeases for further details.
template<typename LeasePtrType>
class ExpirationAllocEngineTest : public ::testing::Test {
public:

    /// @brief Type definition for the lease algorithm.
    typedef boost::function<bool (const LeasePtrType)> LeaseAlgorithmFun;
    /// @brief type definition for the lease index algorithm.
    typedef boost::function<bool (const size_t)> IndexAlgorithmFun;

    /// @brief Constructor.
    ///
    /// Clears configuration, creates new lease manager and allocation engine
    /// instances.
    ExpirationAllocEngineTest(const std::string& lease_mgr_params) {
        CfgMgr::instance().clear();
        LeaseMgrFactory::create(lease_mgr_params);

        engine_.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                      100, false));

    }

    /// @brief Destructor
    ///
    /// Stops D2 client (if running), clears configuration and removes
    /// an instance of the lease manager.
    virtual ~ExpirationAllocEngineTest() {
        // Stop D2 client if running and remove all queued name change
        // requests.
        D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
        if (mgr.amSending()) {
            mgr.stopSender();
            mgr.clearQueue();
        }

        CfgMgr::instance().clear();
        LeaseMgrFactory::destroy();
    }

    /// @brief Starts D2 client.
    void enableDDNS() const {
        // Start DDNS and assign no-op error handler.
        D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
        D2ClientConfigPtr cfg(new D2ClientConfig());
        cfg->enableUpdates(true);
        mgr.setD2ClientConfig(cfg);
        mgr.startSender(boost::bind(&ExpirationAllocEngineTest::d2ErrorHandler, _1, _2));
    }

    /// @brief No-op error handler for the D2 client.
    static void d2ErrorHandler(const dhcp_ddns::NameChangeSender::Result,
                               dhcp_ddns::NameChangeRequestPtr&) {
    }

    /// @brief Marks a lease as expired.
    ///
    /// @param lease_index Lease index. Must be between 0 and
    /// @c TEST_LEASES_NUM.
    /// @param secs Offset of the expiration time since now. For example
    /// a value of 2 would set the lease expiration time to 2 seconds ago.
    void expire(const uint16_t lease_index, const time_t secs) {
        ASSERT_GT(leases_.size(), lease_index);
        // We set the expiration time indirectly by modifying the cltt value.
        leases_[lease_index]->cltt_ = time(NULL) - secs -
            leases_[lease_index]->valid_lft_;
        ASSERT_NO_THROW(updateLease(lease_index));
    }

    /// @brief Updates lease in the lease database.
    ///
    /// @param lease_index Index of the lease.
    virtual void updateLease(const unsigned int lease_index) = 0;

    /// @brief Retrieves lease from the database.
    ///
    /// @param lease_index Index of the lease.
    virtual LeasePtrType getLease(const unsigned int lease_index) const = 0;

    /// @brief Wrapper method running lease reclamation routine.
    ///
    /// @param max_leases Maximum number of leases to be reclaimed.
    /// @param timeout Maximum amount of time that the reclaimation routine
    /// may be processing expired leases, expressed in seconds.
    /// @param remove_lease A boolean value indicating if the lease should
    /// be removed when it is reclaimed (if true) or it should be left in the
    /// database in the "expired-reclaimed" state (if false).
    virtual void reclaimExpiredLeases(const size_t max_leases,
                                      const uint16_t timeout,
                                      const bool remove_lease) = 0;

    /// @brief Test selected leases using the specified algorithms.
    ///
    /// This function picks leases from the range of 0 thru
    /// @c TEST_LEASES_NUM and selects the ones to be verified using the
    /// specified index algorithm. Selected leases are tested using
    /// the specified lease algorithm.
    ///
    /// @param lease_algorithm Pointer to the lease algorithm function.
    /// @param index_algorithm Pointer to the index algorithm function.
    bool testLeases(const LeaseAlgorithmFun& lease_algorithm,
                    const IndexAlgorithmFun& index_algorithm) const {
        // No limits are specified, so test all leases in the range of
        // 0 .. TEST_LEASES_NUM.
        return (testLeases(lease_algorithm, index_algorithm, LowerBound(0),
                           UpperBound(TEST_LEASES_NUM)));
    }


    /// @brief Test selected leases using the specified algorithms.
    ///
    /// This function picks leases from the range of @c lower_bound
    /// thru @c upper_bound and selects the ones to be verified using the
    /// specified index algorithm. Selected leases are tested using the
    /// specified lease algorithm.
    ///
    /// @param lease_algorithm Pointer to the lease algorithm function.
    /// @param index_algorithm Pointer to the index algorithm function.
    /// @param lower_bound First index in the range.
    /// @param upper_bound Last + 1 index in the range.
    bool testLeases(const LeaseAlgorithmFun& lease_algorithm,
                    const IndexAlgorithmFun& index_algorithm,
                    const LowerBound& lower_bound,
                    const UpperBound& upper_bound) const {
        // Select leases between the lower_bound and upper_bound.
        for (size_t i = lower_bound; i < upper_bound; ++i) {
            // Get the lease from the lease database.
            LeasePtrType lease = getLease(i);
            // index_algorithm(i) checks if the lease should be checked.
            // If so, check if the lease_algorithm indicates that the
            // lease fulfils a given condition, e.g. is present in the
            // database. If not, return false.
            if (index_algorithm(i) && !lease_algorithm(lease)) {
                return (false);
            }
        }
        // All leases checked, so return true.
        return (true);
    }

    /// @brief Index algorithm selecting even indexes.
    ///
    /// @param index Lease index.
    /// @return true if index is an even number.
    static bool evenLeaseIndex(const size_t index) {
        return (index % 2 == 0);
    }

    /// @brief Index algorithm selecting odd indexes.
    ///
    /// @param index Lease index.
    /// @return true if index is an odd number.
    static bool oddLeaseIndex(const size_t index) {
        return (!evenLeaseIndex(index));
    }

    /// @brief Index algorithm selecting all indexes.
    ///
    /// @param index Lease index.
    /// @return true if the index is in the range of [0 .. TEST_LEASES_NUM).
    static bool allLeaseIndexes(const size_t index) {
        return (index < TEST_LEASES_NUM);
    }

    /// @brief Lease algorithm checking if lease exists.
    ///
    /// @param lease Pointer to lease.
    /// @return true if lease pointer is non-null.
    static bool leaseExists(const LeasePtrType& lease) {
        return (static_cast<bool>(lease));
    }

    /// @brief Lease algorithm checking if lease doesn't exist.
    ///
    /// @param lease Pointer to lease.
    /// @return true if lease pointer is null.
    static bool leaseDoesntExist(const LeasePtrType& lease) {
        return (static_cast<bool>(!lease));
    }

    /// @brief Lease algorithm checking if lease state is expired-reclaimed.
    ///
    /// This algorithm also checks that the FQDN information has been removed
    /// from the lease.
    ///
    /// @param lease Pointer to lease.
    /// @return true if lease state is "expired-reclaimed".
    static bool leaseReclaimed(const LeasePtrType& lease) {
        return (lease && lease->stateExpiredReclaimed() &&
                lease->hostname_.empty() && !lease->fqdn_fwd_ &&
                !lease->fqdn_rev_);
    }

    /// @brief Lease algorithm checking if lease state is not
    /// expired-reclaimed.
    ///
    /// @param lease Pointer to lease.
    /// @return true if lease state is not "expired-reclaimed".
    static bool leaseNotReclaimed(const LeasePtrType& lease) {
        return (lease && !lease->stateExpiredReclaimed());
    }

    /// @brief Lease algorithm checking if removal name change request
    /// has been generated for lease.
    ///
    /// @param lease Pointer to lease.
    /// @return true if NCR has been generated for the lease.
    static bool dnsUpdateGeneratedForLease(const LeasePtrType& lease) {
        try {
            return (static_cast<bool>(getNCRForLease(lease)));

        } catch (...) {
            // If error occurred, treat it as no match.
            return (false);
        }
    }

    /// @brief Lease algorithm checking if removal name change request
    /// hasn't been generated for lease.
    ///
    /// @param lease Pointer to lease.
    /// @return true if NCR has not been generated for the lease.
    static bool dnsUpdateNotGeneratedForLease(const LeasePtrType& lease) {
        try {
            // Iterate over the generated name change requests and try
            // to find the match with our lease (using IP address). If
            D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
            for (size_t i = 0; i < mgr.getQueueSize(); ++i) {
                const NameChangeRequestPtr& ncr = mgr.peekAt(i);
                // If match found, we treat it as if the test fails
                // because we expected no NCR.
                if (ncr->getIpAddress() == lease->addr_.toText()) {
                    return (false);
                }
            }
        } catch (...) {
            return (false);
        }

        // No match found, so we're good.
        return (true);
    }

    /// @brief Returns Name Change Request from the D2 client queue.
    ///
    /// @param lease Pointer to the lease to be matched with NCR.
    ///
    /// @return null pointer if no match found.
    static NameChangeRequestPtr getNCRForLease(const LeasePtrType& lease) {
        // Iterate over the generated name change requests and try
        // to find the match with our lease (using IP address). If
        D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
        for (size_t i = 0; i < mgr.getQueueSize(); ++i) {
            const NameChangeRequestPtr& ncr = mgr.peekAt(i);
            // If match found, return true.
            if (ncr->getIpAddress() == lease->addr_.toText()) {
                return (ncr);
            }
        }
        return (NameChangeRequestPtr());
    }

    /// @brief Returns index of the lease from the address.
    ///
    /// This method assumes that leases are ordered from the smallest to
    /// the highest address, e.g. 10.0.0.0, 10.0.0.1, 10.0.0.2 etc. The
    /// last two bytes can be used to extract index.
    ///
    /// @param address Address.
    ///
    /// @return index
    static uint16_t getLeaseIndexFromAddress(const IOAddress& address) {
        std::vector<uint8_t> bytes = address.toBytes();
        std::vector<uint8_t>::reverse_iterator bytes_it = bytes.rbegin();
        uint16_t index = static_cast<uint16_t>(*bytes_it) |
            (static_cast<uint16_t>(*(bytes_it + 1)) << 8);
        return (index);
    }

    /// @brief Generates hostname for lease index.
    ///
    /// Generates hostname in the form of "hostXXXX.example.org", where
    /// XXXX is a lease index.
    ///
    /// @param index Lease index.
    ///
    /// @return Generated hostname.
    static std::string generateHostnameForLeaseIndex(const uint16_t index) {
        std::ostringstream hostname_s;
        hostname_s << "host" << std::setw(4) << std::setfill('0')
                   << index << ".example.org";
        return (hostname_s.str());
    }

    /// @brief Test that leases can be reclaimed without being removed.
    void testReclaimExpiredLeasesUpdateState() {
        for (int i = 0; i < TEST_LEASES_NUM; ++i) {
            // Mark leases with even indexes as expired.
            if (evenLeaseIndex(i)) {
                // The higher the index, the more expired the lease.
                expire(i, 10 + i);
            }
        }

        // Run leases reclamation routine on all leases. This should result
        // in setting "expired-reclaimed" state for all leases with even
        // indexes.
        ASSERT_NO_THROW(reclaimExpiredLeases(0, 0, false));

        // Leases with even indexes should be marked as reclaimed.
        EXPECT_TRUE(testLeases(&leaseReclaimed, &evenLeaseIndex));
        // Leases with odd indexes shouldn't be marked as reclaimed.
        EXPECT_TRUE(testLeases(&leaseNotReclaimed, &oddLeaseIndex));
    }

    /// @brief Test that the leases may be reclaimed by being deleted.
    void testReclaimExpiredLeasesDelete() {
        for (int i = 0; i < TEST_LEASES_NUM; ++i) {
            // Mark leases with even indexes as expired.
            if (evenLeaseIndex(i)) {
                // The higher the index, the more expired the lease.
                expire(i, 10 + i);
            }
        }

        // Run leases reclamation routine on all leases. This should result
        // in removal of all leases with even indexes.
        ASSERT_NO_THROW(reclaimExpiredLeases(0, 0, true));

        // Leases with odd indexes should be retained and their state
        // shouldn't be "expired-reclaimed".
        EXPECT_TRUE(testLeases(&leaseNotReclaimed, &oddLeaseIndex));
        // Leases with even indexes should have been removed.
        EXPECT_TRUE(testLeases(&leaseDoesntExist, &evenLeaseIndex));
    }

    /// @brief Test that it is possible to specify the limit for the number
    /// of reclaimed leases.
    void testReclaimExpiredLeasesLimit() {
        for (int i = 0; i < TEST_LEASES_NUM; ++i) {
            // Mark all leaes as expired. The higher the index the less
            // expired the lease.
            expire(i, 1000 - i);
        }

        // We will be performing lease reclamation on lease groups of 10.
        // Hence, it is convenient if the number of test leases is a
        // multiple of 10.
        const size_t reclamation_group_size = 10;
        BOOST_STATIC_ASSERT(TEST_LEASES_NUM % reclamation_group_size == 0);

        // Leases will be reclaimed in groups of 10.
        for (int i = reclamation_group_size; i < TEST_LEASES_NUM;
             i += reclamation_group_size) {

            // Reclaim 10 most expired leases out of TEST_LEASES_NUM. Since
            // leases are ordered from the most expired to the least expired
            // this should reclaim leases between 0 and 9, then 10 and 19 etc.
            ASSERT_NO_THROW(reclaimExpiredLeases(reclamation_group_size,
                                                 0, false));

            // Check that leases having all indexes between 0 and 9, 19, 29 etc.
            // have been reclaimed.
            EXPECT_TRUE(testLeases(&leaseReclaimed, &allLeaseIndexes,
                                   LowerBound(0), UpperBound(i)))
                << "check failed for i = " << i;

            // Check that all remaining leases haven't been reclaimed.
            EXPECT_TRUE(testLeases(&leaseNotReclaimed, &allLeaseIndexes,
                                   LowerBound(i), UpperBound(TEST_LEASES_NUM)))
                << "check failed for i = " << i;
        }
    }

    /// @brief Test that DNS updates are generated for the leases for which
    /// the DNS records exist.
    void testReclaimExpiredLeasesWithDDNS() {
        // DNS must be started for the D2 client to accept NCRs.
        ASSERT_NO_THROW(enableDDNS());

        for (int i = 0; i < TEST_LEASES_NUM; ++i) {
            // Expire all leases with even indexes.
            if (evenLeaseIndex(i)) {
                // The higher the index, the more expired the lease.
                expire(i, 10 + i);
            }
        }

        // Reclaim all expired leases.
        ASSERT_NO_THROW(reclaimExpiredLeases(0, 0, false));

        // Leases with odd indexes shouldn't be reclaimed.
        EXPECT_TRUE(testLeases(&leaseNotReclaimed, &oddLeaseIndex));
        // Leases with even indexes should be reclaimed.
        EXPECT_TRUE(testLeases(&leaseReclaimed, &evenLeaseIndex));
        // DNS updates (removal NCRs) should be generated for leases with even
        // indexes.
        EXPECT_TRUE(testLeases(&dnsUpdateGeneratedForLease, &evenLeaseIndex));
        // DNS updates (removal NCRs) shouldn't be generated for leases with
        // odd indexes.
        EXPECT_TRUE(testLeases(&dnsUpdateNotGeneratedForLease, &oddLeaseIndex));
    }

    /// @brief Test that DNS updates are only generated for the reclaimed
    /// leases (not for all leases with hostname stored).
    void testReclaimExpiredLeasesWithDDNSAndLimit() {
        // DNS must be started for the D2 client to accept NCRs.
        ASSERT_NO_THROW(enableDDNS());

        for (int i = 0; i < TEST_LEASES_NUM; ++i) {
            // Expire only leases with even indexes.
            if (evenLeaseIndex(i)) {
                // The higher the index, the more expired the lease.
                expire(i, 10 + i);
            }
        }

        const size_t reclamation_group_size = 10;
        BOOST_STATIC_ASSERT(TEST_LEASES_NUM % reclamation_group_size == 0);

        // Leases will be reclaimed in groups of 10
        for (int i = 10; i < TEST_LEASES_NUM;  i += reclamation_group_size) {
            // Reclaim 10 most expired leases. Note that the leases with the
            // higher index are more expired. For example, if the
            // TEST_LEASES_NUM is equal to 100, the most expired lease will
            // be 98, then 96, 94 etc.
            ASSERT_NO_THROW(reclaimExpiredLeases(reclamation_group_size, 0,
                                                 false));

            // After the first iteration the lower bound is 80, because there
            // will be 10 the most expired leases in this group: 80, 82, 84,
            // 86, 88, 90, 92, 94, 96, 98. For subsequent iterations
            // accordingly.
            int reclaimed_lower_bound = TEST_LEASES_NUM - 2 * i;
            // At some point the lower bound will hit the negative value, which
            // must be corrected to 0.
            if (reclaimed_lower_bound < 0) {
                reclaimed_lower_bound = 0;
            }

            // Leases between the lower bound calculated above and the upper
            // bound of all leases, and having even indexes should have been
            // reclaimed.
            EXPECT_TRUE(testLeases(&leaseReclaimed, &evenLeaseIndex,
                                   LowerBound(reclaimed_lower_bound),
                                   UpperBound(TEST_LEASES_NUM)))
                << "check failed for i = " << i;

            // For the same leases we should have generated DNS updates
            // (removal NCRs).
            EXPECT_TRUE(testLeases(&dnsUpdateGeneratedForLease, &evenLeaseIndex,
                                   LowerBound(reclaimed_lower_bound),
                                   UpperBound(TEST_LEASES_NUM)))
                << "check failed for i = " << i;

            // Leases with odd indexes (falling between the reclaimed ones)
            // shouldn't have been reclaimed, because they are not expired.
            EXPECT_TRUE(testLeases(&leaseNotReclaimed, &oddLeaseIndex,
                                   LowerBound(reclaimed_lower_bound),
                                   UpperBound(TEST_LEASES_NUM)))
                << "check failed for i = " << i;

            EXPECT_TRUE(testLeases(&dnsUpdateNotGeneratedForLease,
                                   &oddLeaseIndex,
                                   LowerBound(reclaimed_lower_bound),
                                   UpperBound(TEST_LEASES_NUM)))
                << "check failed for i = " << i;


            // At early stages of iterations, there should be conitnuous
            // group of leases (expired and not expired) which haven't been
            // reclaimed.
            if (reclaimed_lower_bound > 0) {
                EXPECT_TRUE(testLeases(&leaseNotReclaimed, &allLeaseIndexes,
                                       LowerBound(0),
                                       UpperBound(reclaimed_lower_bound)))
                    << "check failed for i = " << i;

                EXPECT_TRUE(testLeases(&dnsUpdateNotGeneratedForLease,
                                       &oddLeaseIndex,
                                       LowerBound(0),
                                       UpperBound(reclaimed_lower_bound)));
            }
        }
    }

    /// @brief This test verifies that reclamation routine continues if the
    /// DNS update has failed for some leases.
    void testReclaimExpiredLeasesInvalidHostname() {
        // DNS must be started for the D2 client to accept NCRs.
        ASSERT_NO_THROW(enableDDNS());

        for (size_t i = 0; i < TEST_LEASES_NUM; ++i) {
            // Generate invalid hostname for every other lease.
            if (evenLeaseIndex(i)) {
                // Hostname with two consecutive dots is invalid and may result
                // in exception if the reclamation routine doesn't protect
                // aginst such exceptions.
                std::ostringstream hostname_s;
                hostname_s << "invalid-host" << i << "..example.com";
                leases_[i]->hostname_ = hostname_s.str();
                ASSERT_NO_THROW(updateLease(i));
            }
            // Every lease is expired.
            expire(i, 10 + i);
        }

        // Although we know that some hostnames are broken we don't want the
        // reclamation process to break when it finds a broken record.
        // It should rather continue to process other leases.
        ASSERT_NO_THROW(reclaimExpiredLeases(0, 0, false));

        // All leases should have been reclaimed. Broken DNS entry doesn't
        // warrant that we don't reclaim the lease.
        EXPECT_TRUE(testLeases(&leaseReclaimed, &allLeaseIndexes));
        // The routine should not generate DNS updates for the leases with
        // broken hostname.
        EXPECT_TRUE(testLeases(&dnsUpdateNotGeneratedForLease,
                               &evenLeaseIndex));
        // But it should generate DNS updates for the leases with the correct
        // hostname.
        EXPECT_TRUE(testLeases(&dnsUpdateGeneratedForLease, &oddLeaseIndex));
    }

    /// @brief Collection of leases created at construction time.
    std::vector<LeasePtrType> leases_;

    /// @brief Allocation engine instance used for tests.
    AllocEnginePtr engine_;

};

/// @brief Specialization of the @c ExpirationAllocEngineTest class to test
/// reclamation of the IPv6 leases.
class ExpirationAllocEngine6Test : public ExpirationAllocEngineTest<Lease6Ptr> {
public:

    /// @brief Class constructor.
    ///
    /// This constructor initializes @c TEST_LEASES_NUM leases and
    /// stores them in the lease manager.
    ExpirationAllocEngine6Test();

    /// @brief Creates collection of leases for a test.
    ///
    /// It is called internally at the construction time.
    void createLeases();

    /// @brief Updates lease in the lease database.
    ///
    /// @param lease_index Index of the lease.
    virtual void updateLease(const unsigned int lease_index) {
        LeaseMgrFactory::instance().updateLease6(leases_[lease_index]);
    }

    /// @brief Retrieves lease from the database.
    ///
    /// @param lease_index Index of the lease.
    virtual Lease6Ptr getLease(const unsigned int lease_index) const {
        return (LeaseMgrFactory::instance().getLease6(leases_[lease_index]->type_,
                                                      leases_[lease_index]->addr_));
    }

    /// @brief Wrapper method running lease reclamation routine.
    ///
    /// @param max_leases Maximum number of leases to be reclaimed.
    /// @param timeout Maximum amount of time that the reclaimation routine
    /// may be processing expired leases, expressed in seconds.
    /// @param remove_lease A boolean value indicating if the lease should
    /// be removed when it is reclaimed (if true) or it should be left in the
    /// database in the "expired-reclaimed" state (if false).
    virtual void reclaimExpiredLeases(const size_t max_leases,
                                      const uint16_t timeout,
                                      const bool remove_lease) {
        engine_->reclaimExpiredLeases6(max_leases, timeout, remove_lease);
    }

};

ExpirationAllocEngine6Test::ExpirationAllocEngine6Test()
    : ExpirationAllocEngineTest("type=memfile universe=6 persist=false") {
    createLeases();
}

void
ExpirationAllocEngine6Test::createLeases() {
    // Create TEST_LEASES_NUM leases.
    for (uint16_t i = 0; i < TEST_LEASES_NUM; ++i) {
        // DUID
        std::ostringstream duid_s;
        duid_s << "01020304050607" << std::setw(4) << std::setfill('0') << i;
        DuidPtr duid(new DUID(DUID::fromText(duid_s.str()).getDuid()));

        // Address.
        std::ostringstream address_s;
        address_s << "2001:db8:1::" << std::setw(4) << std::setfill('0') << i;
        IOAddress address(address_s.str());

        // Create lease.
        Lease6Ptr lease(new Lease6(Lease::TYPE_NA, address, duid, 1, 50, 60, 10,
                                   20, SubnetID(1), true, true,
                                   generateHostnameForLeaseIndex(i)));
        leases_.push_back(lease);
        LeaseMgrFactory::instance().addLease(lease);
    }
}


// This test verifies that the leases can be reclaimed without being removed
// from the database. In such case, the leases' state is set to
// "expired-reclaimed".
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeases6UpdateState) {
    testReclaimExpiredLeasesUpdateState();
}

// This test verifies that the reclaimed leases are deleted when requested.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeasesDelete) {
    testReclaimExpiredLeasesDelete();
}

// This test verifies that it is possible to specify the limit for the
// number of reclaimed leases.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeasesLimit) {
    testReclaimExpiredLeasesLimit();
}

// This test verifies that DNS updates are generated for the leases
// for which the DNS records exist.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeasesWithDDNS) {
    testReclaimExpiredLeasesWithDDNS();
}

// This test verifies that it is DNS updates are generated only for the
// reclaimed expired leases. In this case we limit the number of leases
// reclaimed during a single call to reclamation routine.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeasesWithDDNSAndLimit) {
    testReclaimExpiredLeasesWithDDNSAndLimit();
}

// This test verifies that if some leases have invalid hostnames, the
// lease reclamation routine continues with reclamation of leases anyway.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeasesInvalidHostname) {
    testReclaimExpiredLeasesInvalidHostname();
}

// *******************************************************
//
// DHCPv4 lease reclamation routine tests start here!
//
// *******************************************************

/// @brief Specialization of the @c ExpirationAllocEngineTest class to test
/// reclamation of the IPv4 leases.
class ExpirationAllocEngine4Test : public ExpirationAllocEngineTest<Lease4Ptr> {
public:

    /// @brief Class constructor.
    ///
    /// This constructor initializes @c TEST_LEASES_NUM leases and
    /// stores them in the lease manager.
    ExpirationAllocEngine4Test();

    /// @brief Creates collection of leases for a test.
    ///
    /// It is called internally at the construction time.
    void createLeases();

    /// @brief Generates unique client identifier from lease index.
    ///
    /// @param index lease index.
    void setUniqueClientId(const uint16_t index);

    /// @brief Updates lease in the lease database.
    ///
    /// @param lease_index Index of the lease.
    virtual void updateLease(const unsigned int lease_index) {
        LeaseMgrFactory::instance().updateLease4(leases_[lease_index]);
    }

    /// @brief Retrieves lease from the database.
    ///
    /// @param lease_index Index of the lease.
    virtual Lease4Ptr getLease(const unsigned int lease_index) const {
        return (LeaseMgrFactory::instance().getLease4(leases_[lease_index]->addr_));
    }

    /// @brief Wrapper method running lease reclamation routine.
    ///
    /// @param max_leases Maximum number of leases to be reclaimed.
    /// @param timeout Maximum amount of time that the reclaimation routine
    /// may be processing expired leases, expressed in seconds.
    /// @param remove_lease A boolean value indicating if the lease should
    /// be removed when it is reclaimed (if true) or it should be left in the
    /// database in the "expired-reclaimed" state (if false).
    virtual void reclaimExpiredLeases(const size_t max_leases,
                                      const uint16_t timeout,
                                      const bool remove_lease) {
        engine_->reclaimExpiredLeases4(max_leases, timeout, remove_lease);
    }

    /// @brief Lease algorithm checking if NCR has been generated from client
    /// identifier.
    ///
    /// @param lease Pointer to the lease for which the NCR needs to be checked.
    static bool dnsUpdateGeneratedFromClientId(const Lease4Ptr& lease);

    /// @brief Lease algorithm checking if NCR has been generated from
    /// HW address.
    static bool dnsUpdateGeneratedFromHWAddress(const Lease4Ptr& lease);

    /// @brief Test that DNS updates are properly generated when the
    /// reclaimed leases contain client identifier.
    void testReclaimExpiredLeasesWithDDNSAndClientId();
};

ExpirationAllocEngine4Test::ExpirationAllocEngine4Test()
    : ExpirationAllocEngineTest("type=memfile universe=4 persist=false") {
    createLeases();
}

void
ExpirationAllocEngine4Test::createLeases() {
    // Create TEST_LEASES_NUM leases.
    for (uint16_t i = 0; i < TEST_LEASES_NUM; ++i) {
        // HW address
        std::ostringstream hwaddr_s;
        hwaddr_s << "01:02:03:04:" << std::setw(2) << std::setfill('0')
                 << (i >> 8) << ":" << std::setw(2) << std::setfill('0')
                 << (i & 0x00FF);
        HWAddrPtr hwaddr(new HWAddr(HWAddr::fromText(hwaddr_s.str(),
                                                     HTYPE_ETHER)));

        // Address.
        std::ostringstream address_s;
        address_s << "10.0." << (i >> 8) << "." << (i & 0x00FF);
        IOAddress address(address_s.str());

        // Create lease.
        Lease4Ptr lease(new Lease4(address, hwaddr, ClientIdPtr(), 60, 10, 20,
                                   time(NULL), SubnetID(1), true, true,
                                   generateHostnameForLeaseIndex(i)));
        leases_.push_back(lease);
        LeaseMgrFactory::instance().addLease(lease);
    }
}

void
ExpirationAllocEngine4Test::setUniqueClientId(const uint16_t index) {
    std::ostringstream clientid_s;
    clientid_s << "AA:BB:" << std::setw(2) << std::setfill('0')
        << (index >> 16) << ":" << std::setw(2) << std::setfill('0')
        << (index & 0x00FF);
    ClientIdPtr client_id(ClientId::fromText(clientid_s.str()));
    leases_[index]->client_id_ = client_id;
    LeaseMgrFactory::instance().updateLease4(leases_[index]);
}

bool
ExpirationAllocEngine4Test::dnsUpdateGeneratedFromClientId(const Lease4Ptr& lease) {
    try {
        NameChangeRequestPtr ncr = getNCRForLease(lease);
        if (ncr) {
            if (lease->client_id_) {
                // Generate hostname for this lease. Note that the lease
                // in the database doesn't have the hostname because it
                // has been removed by the lease reclamation routine.
                std::string hostname = generateHostnameForLeaseIndex(
                      getLeaseIndexFromAddress(lease->addr_));

                // Get DHCID from NCR.
                const D2Dhcid& dhcid = ncr->getDhcid();
                // Generate reference DHCID to compare with the one from
                // the NCR.
                std::vector<uint8_t> fqdn_wire;
                OptionDataTypeUtil::writeFqdn(hostname, fqdn_wire, true);
                D2Dhcid clientid_dhcid(lease->client_id_->getClientId(),
                                       fqdn_wire);
                // Return true if they match.
                return (dhcid == clientid_dhcid);
            }
        }

    } catch (...) {
        // If error occurred, treat it as no match.
        return (false);
    }

    // All leases checked - no match.
    return (false);
}

bool
ExpirationAllocEngine4Test::dnsUpdateGeneratedFromHWAddress(const Lease4Ptr& lease) {
    try {
        NameChangeRequestPtr ncr = getNCRForLease(lease);
        if (ncr) {
            if (lease->hwaddr_) {
                // Generate hostname for this lease. Note that the lease
                // in the database doesn't have the hostname because it
                // has been removed by the lease reclamation routine.
                std::string hostname = generateHostnameForLeaseIndex(
                      getLeaseIndexFromAddress(lease->addr_));

                // Get DHCID from NCR.
                const D2Dhcid& dhcid = ncr->getDhcid();
                // Generate reference DHCID to compare with the one from
                // the NCR.
                std::vector<uint8_t> fqdn_wire;
                OptionDataTypeUtil::writeFqdn(hostname, fqdn_wire, true);
                D2Dhcid hwaddr_dhcid(lease->hwaddr_, fqdn_wire);
                // Return true if they match.
                return (dhcid == hwaddr_dhcid);
            }
        }

    } catch (...) {
        // If error occurred, treat it as no match.
        return (false);
    }

    // All leases checked - no match.
    return (false);
}

void
ExpirationAllocEngine4Test::testReclaimExpiredLeasesWithDDNSAndClientId() {
    // DNS must be started for the D2 client to accept NCRs.
    ASSERT_NO_THROW(enableDDNS());

    for (int i = 0; i < TEST_LEASES_NUM; ++i) {
        // Set client identifiers for leases with even indexes only.
        if (evenLeaseIndex(i)) {
            setUniqueClientId(i);
        }
        // Expire all leases. The higher the index, the more expired the lease.
        expire(i, 10 + i);
    }

    // Reclaim all expired leases.
    ASSERT_NO_THROW(reclaimExpiredLeases(0, 0, false));

    // Leases with even indexes should be reclaimed.
    EXPECT_TRUE(testLeases(&leaseReclaimed, &evenLeaseIndex));
    // DNS updates (removal NCRs) should be generated for all leases.
    EXPECT_TRUE(testLeases(&dnsUpdateGeneratedForLease, &allLeaseIndexes));
    // Leases with even indexes include client identifiers so the DHCID should
    // be generated from the client identifiers.
    EXPECT_TRUE(testLeases(&dnsUpdateGeneratedFromClientId, &evenLeaseIndex));
    // Leases with odd indexes do not include client identifiers so their
    // DHCID should be generated from the HW address.
    EXPECT_TRUE(testLeases(&dnsUpdateGeneratedFromHWAddress, &oddLeaseIndex));
}

// This test verifies that the leases can be reclaimed without being removed
// from the database. In such case, the leases' state is set to
// "expired-reclaimed".
TEST_F(ExpirationAllocEngine4Test, reclaimExpiredLeasesUpdateState) {
    testReclaimExpiredLeasesUpdateState();
}

// This test verifies that the reclaimed leases are deleted when requested.
TEST_F(ExpirationAllocEngine4Test, reclaimExpiredLeasesDelete) {
    testReclaimExpiredLeasesDelete();
}

// This test verifies that it is possible to specify the limit for the
// number of reclaimed leases.
TEST_F(ExpirationAllocEngine4Test, reclaimExpiredLeasesLimit) {
    testReclaimExpiredLeasesLimit();
}

// This test verifies that DNS updates are generated for the leases
// for which the DNS records exist.
TEST_F(ExpirationAllocEngine4Test, reclaimExpiredLeasesWithDDNS) {
    testReclaimExpiredLeasesWithDDNS();
}

// This test verifies that it is DNS updates are generated only for the
// reclaimed expired leases. In this case we limit the number of leases
// reclaimed during a single call to reclamation routine.
TEST_F(ExpirationAllocEngine4Test, reclaimExpiredLeasesWithDDNSAndLimit) {
    testReclaimExpiredLeasesWithDDNSAndLimit();
}

// This test verifies that if some leases have invalid hostnames, the
// lease reclamation routine continues with reclamation of leases anyway.
TEST_F(ExpirationAllocEngine4Test, reclaimExpiredLeasesInvalidHostname) {
    testReclaimExpiredLeasesInvalidHostname();
}

// This test verifies that DNS updates are properly generated when the
// client id is used as a primary identifier in the lease.
TEST_F(ExpirationAllocEngine4Test, reclaimExpiredLeasesWithDDNSAndClientId) {
    testReclaimExpiredLeasesWithDDNSAndClientId();
}

}; // end of anonymous namespace
