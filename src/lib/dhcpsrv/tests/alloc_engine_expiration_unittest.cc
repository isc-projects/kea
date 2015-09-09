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
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <dhcpsrv/tests/test_utils.h>
#include <gtest/gtest.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/static_assert.hpp>
#include <iomanip>
#include <sstream>
#include <time.h>

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

/// @brief Test fixture class for the lease reclamation routines in the
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
/// @c ExpirationAllocEngine6Test::testLeases methods. These methods
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
/// See @c ExpirationAllocEngine6Test::testLeases for further details.
class ExpirationAllocEngine6Test : public AllocEngine6Test {
public:

    /// @brief Type definition for the lease algorithm.
    typedef boost::function<bool (const Lease6Ptr)> LeaseAlgorithmFun;
    /// @brief type definition for the lease index algorithm.
    typedef boost::function<bool (const size_t)> IndexAlgorithmFun;

    /// @brief Class constructor.
    ///
    /// This constructor initializes @c TEST_LEASES_NUM leases and
    /// stores them in the lease manager.
    ExpirationAllocEngine6Test();

    /// @brief Class destructor.
    ///
    /// It stops the D2 client, if it is running.
    virtual ~ExpirationAllocEngine6Test();

    /// @brief Creates collection of leases for a test.
    ///
    /// It is called internally at the construction time.
    void createLeases();

    /// @brief Starts D2 client.
    void enableDDNS() const;

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
    void expire(const unsigned int lease_index, const time_t secs);

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
                    const IndexAlgorithmFun& index_algorithm) const;


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
                    const UpperBound& upper_bound) const;

    /// @brief Index algorithm selecting even indexes.
    ///
    /// @param index Lease index.
    /// @return true if index is an even number.
    static bool evenLeaseIndex(const size_t index) {
        return (index % 2);
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
    static bool leaseExists(const Lease6Ptr& lease) {
        return (static_cast<bool>(lease));
    }

    /// @brief Lease algorithm checking if lease doesn't exist.
    ///
    /// @param lease Pointer to lease.
    /// @return true if lease pointer is null.
    static bool leaseDoesntExist(const Lease6Ptr& lease) {
        return (static_cast<bool>(!lease));
    }

    /// @brief Lease algorithm checking if lease state is expired-reclaimed.
    ///
    /// This algorithm also checks that the FQDN information has been removed
    /// from the lease.
    ///
    /// @param lease Pointer to lease.
    /// @return true if lease state is "expired-reclaimed".
    static bool leaseReclaimed(const Lease6Ptr& lease) {
        return (lease && lease->stateExpiredReclaimed() &&
                lease->hostname_.empty() && !lease->fqdn_fwd_ &&
                !lease->fqdn_rev_);
    }

    /// @brief Lease algorithm checking if lease state is not
    /// expired-reclaimed.
    ///
    /// @param lease Pointer to lease.
    /// @return true if lease state is not "expired-reclaimed".
    static bool leaseNotReclaimed(const Lease6Ptr& lease) {
        return (lease && !lease->stateExpiredReclaimed());
    }

    /// @brief Lease algorithm checking if removal name change request
    /// has been generated for lease.
    ///
    /// @param lease Pointer to lease.
    /// @return true if NCR has been generated for the lease.
    static bool dnsUpdateGeneratedForLease(const Lease6Ptr& lease);

    /// @brief Lease algorithm checking if removal name change request
    /// hasn't been generated for lease.
    ///
    /// @param lease Pointer to lease.
    /// @return true if NCR has not been generated for the lease.
    static bool dnsUpdateNotGeneratedForLease(const Lease6Ptr& lease);

    /// @brief Collection of leases created at construction time.
    Lease6Collection leases_;

};

ExpirationAllocEngine6Test::ExpirationAllocEngine6Test()
    : AllocEngine6Test() {
    createLeases();
}

ExpirationAllocEngine6Test::~ExpirationAllocEngine6Test() {
    // Stop D2 client if running and remove all queued name change
    // requests.
    D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
    if (mgr.amSending()) {
        mgr.stopSender();
        mgr.clearQueue();
    }
    // Reset configuration. This is important because the CfgMgr is
    // a singleton and test configuration would affect all subsequent
    // tests.
    D2ClientConfigPtr cfg(new D2ClientConfig());
    mgr.setD2ClientConfig(cfg);
}

void
ExpirationAllocEngine6Test::createLeases() {
    // Create TEST_LEASES_NUM leases.
    for (int i = 0; i < TEST_LEASES_NUM; ++i) {
        // DUID
        std::ostringstream duid_s;
        duid_s << "01020304050607" << std::setw(4) << std::setfill('0') << i;
        DuidPtr duid(new DUID(DUID::fromText(duid_s.str()).getDuid()));

        // Address.
        std::ostringstream address_s;
        address_s << "2001:db8:1::" << std::setw(4) << std::setfill('0') << i;
        IOAddress address(address_s.str());

        // Hostname.
        std::ostringstream hostname_s;
        hostname_s << "host" << std::setw(4) << std::setfill('0') << i
            << ".example.org";

        // Create lease.
        Lease6Ptr lease(new Lease6(Lease::TYPE_NA, address, duid, 1, 50, 60, 10, 20,
                                   SubnetID(1), true, true, hostname_s.str()));
        leases_.push_back(lease);
        LeaseMgrFactory::instance().addLease(lease);
    }
}

void
ExpirationAllocEngine6Test::enableDDNS() const {
    // Start DDNS and assign no-op error handler.
    D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
    D2ClientConfigPtr cfg(new D2ClientConfig());
    cfg->enableUpdates(true);
    mgr.setD2ClientConfig(cfg);
    mgr.startSender(boost::bind(&ExpirationAllocEngine6Test::d2ErrorHandler, _1, _2));
}

void
ExpirationAllocEngine6Test::expire(const unsigned int lease_index,
                                   const time_t secs) {
    ASSERT_GT(leases_.size(), lease_index);
    // We set the expiration time indirectly by modifying the cltt value.
    leases_[lease_index]->cltt_ = time(NULL) - secs - leases_[lease_index]->valid_lft_;
    ASSERT_NO_THROW(LeaseMgrFactory::instance().updateLease6(leases_[lease_index]));
}

bool
ExpirationAllocEngine6Test::testLeases(const LeaseAlgorithmFun& lease_algorithm,
                                       const IndexAlgorithmFun& index_algorithm) const {
    // No limits are specified, so test all leases in the range of
    // 0 .. TEST_LEASES_NUM.
    return (testLeases(lease_algorithm, index_algorithm, LowerBound(0),
                       UpperBound(TEST_LEASES_NUM)));
}

bool
ExpirationAllocEngine6Test::testLeases(const LeaseAlgorithmFun& lease_algorithm,
                                       const IndexAlgorithmFun& index_algorithm,
                                       const LowerBound& lower_bound,
                                       const UpperBound& upper_bound) const {
    // Select leases between the lower_bound and upper_bound.
    for (size_t i = lower_bound; i < upper_bound; ++i) {
        // Get the lease from the lease database.
        Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(leases_[i]->type_,
                                                                leases_[i]->addr_);
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

bool
ExpirationAllocEngine6Test::dnsUpdateGeneratedForLease(const Lease6Ptr& lease) {
    try {
        // Iterate over the generated name change requests and try
        // to find the match with our lease (using IP address). If
        D2ClientMgr& mgr = CfgMgr::instance().getD2ClientMgr();
        for (size_t i = 0; i < mgr.getQueueSize(); ++i) {
            const NameChangeRequestPtr& ncr = mgr.peekAt(i);
            // If match found, return true.
            if (ncr->getIpAddress() == lease->addr_.toText()) {
                return (true);
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
ExpirationAllocEngine6Test::dnsUpdateNotGeneratedForLease(const Lease6Ptr& lease) {
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

// This test verifies that the leases can be reclaimed without being removed
// from the database. In such case, the leases' state is set to
// "expired-reclaimed".
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeases6UpdateState) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

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
    ASSERT_NO_THROW(engine->reclaimExpiredLeases6(0, 0, false));

    // Leases with even indexes should be marked as reclaimed.
    EXPECT_TRUE(testLeases(&leaseReclaimed, &evenLeaseIndex));
    // Leases with odd indexes shouldn't be marked as reclaimed.
    EXPECT_TRUE(testLeases(&leaseNotReclaimed, &oddLeaseIndex));

}

// This test verifies that the reclaimed leases are deleted when requested.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeases6Delete) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    for (int i = 0; i < TEST_LEASES_NUM; ++i) {
        // Mark leases with even indexes as expired.
        if (evenLeaseIndex(i)) {
            // The higher the index, the more expired the lease.
            expire(i, 10 + i);
        }
    }

    // Run leases reclamation routine on all leases. This should result
    // in removal of all leases with even indexes.
    ASSERT_NO_THROW(engine->reclaimExpiredLeases6(0, 0, true));

    // Leases with odd indexes should be retained and their state
    // shouldn't be "expired-reclaimed".
    EXPECT_TRUE(testLeases(&leaseNotReclaimed, &oddLeaseIndex));
    // Leases with even indexes should have been removed.
    EXPECT_TRUE(testLeases(&leaseDoesntExist, &evenLeaseIndex));
}

// This test verifies that it is possible to specify the limit for the
// number of reclaimed leases.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeases6Limit) {
   boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

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
        ASSERT_NO_THROW(engine->reclaimExpiredLeases6(reclamation_group_size, 0,
                                                      false));

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

// This test verifies that DNS updates are generated for the leases
// for which the DNS records exist.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeases6WithDDNS) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

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
    ASSERT_NO_THROW(engine->reclaimExpiredLeases6(0, 0, false));

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

// This test verifies that it is DNS updates are generated only for the
// reclaimed expired leases. In this case we limit the number of leases
// reclaimed during a single call to reclamation routine.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeases6WithDDNSAndLimit) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

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
        // Reclaim 10 most expired leases. Note that the leases with the higher
        // index are more expired. For example, if the TEST_LEASES_NUM is equal
        // to 100, the most expired lease will be 98, then 96, 94 etc.
        ASSERT_NO_THROW(engine->reclaimExpiredLeases6(reclamation_group_size, 0,
                                                      false));

        // After the first iteration the lower bound is 80, because there will
        // be 10 the most expired leases in this group: 80, 82, 84, 86, 88, 90,
        // 92, 94, 96, 98. For subsequent iterations accordingly.
        int reclaimed_lower_bound = TEST_LEASES_NUM - 2 * i;
        // At some point the lower bound will hit the negative value, which
        // must be corrected to 0.
        if (reclaimed_lower_bound < 0) {
            reclaimed_lower_bound = 0;
        }

        // Leases between the lower bound calculated above and the upper bound
        // of all leases, and having even indexes should have been reclaimed.
        EXPECT_TRUE(testLeases(&leaseReclaimed, &evenLeaseIndex,
                               LowerBound(reclaimed_lower_bound),
                               UpperBound(TEST_LEASES_NUM)))
            << "check failed for i = " << i;

        // For the same leases we should have generated DNS updates (removal NCRs).
        EXPECT_TRUE(testLeases(&dnsUpdateGeneratedForLease, &evenLeaseIndex,
                               LowerBound(reclaimed_lower_bound),
                               UpperBound(TEST_LEASES_NUM)))
            << "check failed for i = " << i;

        // Leases with odd indexes (falling between the reclaimed ones) shouldn't
        // have been reclaimed, because they are not expired.
        EXPECT_TRUE(testLeases(&leaseNotReclaimed, &oddLeaseIndex,
                               LowerBound(reclaimed_lower_bound),
                               UpperBound(TEST_LEASES_NUM)))
            << "check failed for i = " << i;

        EXPECT_TRUE(testLeases(&dnsUpdateNotGeneratedForLease, &oddLeaseIndex,
                               LowerBound(reclaimed_lower_bound),
                               UpperBound(TEST_LEASES_NUM)))
            << "check failed for i = " << i;


        // At early stages of iterations, there should be conitnuous group of leases
        // (expired and not expired) which haven't been reclaimed.
        if (reclaimed_lower_bound > 0) {
            EXPECT_TRUE(testLeases(&leaseNotReclaimed, &allLeaseIndexes,
                                   LowerBound(0),
                                   UpperBound(reclaimed_lower_bound)))
                << "check failed for i = " << i;

            EXPECT_TRUE(testLeases(&dnsUpdateNotGeneratedForLease, &oddLeaseIndex,
                                   LowerBound(0), UpperBound(reclaimed_lower_bound)));

        }
    }
}

// This test verifies that if some leases have invalid hostnames, the
// lease reclamation routine continues with reclamation of leases anyway.
TEST_F(ExpirationAllocEngine6Test, reclaimExpiredLeases6InvalidHostname) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

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
            ASSERT_NO_THROW(LeaseMgrFactory::instance().updateLease6(leases_[i]));
        }
        // Every lease is expired.
        expire(i, 10 + i);
    }

    // Although we know that some hostnames are broken we don't want the
    // reclamation process to break when it finds a broken record.
    // It should rather continue to process other leases.
    ASSERT_NO_THROW(engine->reclaimExpiredLeases6(0, 0, false));

    // All leases should have been reclaimed. Broken DNS entry doesn't
    // warrant that we don't reclaim the lease.
    EXPECT_TRUE(testLeases(&leaseReclaimed, &allLeaseIndexes));
    // The routine should not generate DNS updates for the leases with broken
    // hostname.
    EXPECT_TRUE(testLeases(&dnsUpdateNotGeneratedForLease, &evenLeaseIndex));
    // But it should generate DNS updates for the leases with the correct
    // hostname.
    EXPECT_TRUE(testLeases(&dnsUpdateGeneratedForLease, &oddLeaseIndex));
}

}; // end of anonymous namespace
