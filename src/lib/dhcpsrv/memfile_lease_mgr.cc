// Copyright (C) 2012-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <dhcpsrv/cfg_consistency.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_exceptions.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_file_loader.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/timer_mgr.h>
#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>
#include <util/multi_threading_mgr.h>
#include <util/pid_file.h>

#include <boost/foreach.hpp>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <limits>
#include <sstream>

namespace {

/// @brief A name of the environmental variable specifying the kea-lfc
/// program location.
///
/// This variable can be set by tests to point to the location of the
/// kea-lfc program within a build directory. If this variable is not
/// set, the backend will use the location of the kea-lfc in the
/// Kea installation directory.
const char* KEA_LFC_EXECUTABLE_ENV_NAME = "KEA_LFC_EXECUTABLE";

}  // namespace

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::util;
using namespace isc::stats;

namespace isc {
namespace dhcp {

/// @brief Represents a configuration for Lease File Cleanup.
///
/// This class is solely used by the @c Memfile_LeaseMgr as a configuration
/// information storage for %Lease File Cleanup. Internally, it creates
/// the interval timer and assigns a callback function (pointer to which is
/// passed in the constructor), which will be called at the specified
/// intervals to perform the cleanup. It is also responsible for creating
/// and maintaining the object which is used to spawn the new process which
/// executes the @c kea-lfc program.
///
/// This functionality is enclosed in a separate class so as the implementation
/// details are not exposed in the @c Memfile_LeaseMgr header file and
/// to maintain a single place with the LFC configuration, instead of multiple
/// members and functions scattered in the @c Memfile_LeaseMgr class.
class LFCSetup {
public:

    /// @brief Constructor.
    ///
    /// Assigns a pointer to the function triggered to perform the cleanup.
    /// This pointer should point to the appropriate method of the
    /// @c Memfile_LeaseMgr class.
    ///
    /// @param callback A pointer to the callback function.
    LFCSetup(asiolink::IntervalTimer::Callback callback);

    /// @brief Destructor.
    ///
    /// Unregisters LFC timer.
    ~LFCSetup();

    /// @brief Sets the new configuration for the %Lease File Cleanup.
    ///
    /// @param lfc_interval An interval in seconds at which the cleanup should
    /// be performed.
    /// @param lease_file4 A pointer to the DHCPv4 lease file to be cleaned up
    /// or null. If this is null, the @c lease_file6 must be non-null.
    /// @param lease_file6 A pointer to the DHCPv6 lease file to be cleaned up
    /// or null. If this is null, the @c lease_file4 must be non-null.
    /// @param run_once_now A flag that causes LFC to be invoked immediately,
    /// regardless of the value of lfc_interval.  This is primarily used to
    /// cause lease file schema upgrades upon startup.
    void setup(const uint32_t lfc_interval,
               const boost::shared_ptr<CSVLeaseFile4>& lease_file4,
               const boost::shared_ptr<CSVLeaseFile6>& lease_file6,
               bool run_once_now = false);

    /// @brief Spawns a new process.
    void execute();

    /// @brief Checks if the lease file cleanup is in progress.
    ///
    /// @return true if the lease file cleanup is being executed.
    bool isRunning() const;

    /// @brief Returns exit code of the last completed cleanup.
    int getExitStatus() const;

private:

    /// @brief A pointer to the @c ProcessSpawn object used to execute
    /// the LFC.
    boost::scoped_ptr<ProcessSpawn> process_;

    /// @brief A pointer to the callback function executed by the timer.
    asiolink::IntervalTimer::Callback callback_;

    /// @brief A PID of the last executed LFC process.
    pid_t pid_;

    /// @brief Pointer to the timer manager.
    ///
    /// We have to hold this pointer here to make sure that the timer
    /// manager is not destroyed before the lease manager.
    TimerMgrPtr timer_mgr_;
};

LFCSetup::LFCSetup(asiolink::IntervalTimer::Callback callback)
    : process_(), callback_(callback), pid_(0),
      timer_mgr_(TimerMgr::instance()) {
}

LFCSetup::~LFCSetup() {
    try {
        // Remove the timer. This will throw an exception if the timer does not
        // exist.  There are several possible reasons for this:
        // a) It hasn't been registered (although if the LFC Setup instance
        //    exists it means that the timer must have been registered or that
        //    such registration has been attempted).
        // b) The registration may fail if the duplicate timer exists or if the
        //    TimerMgr's worker thread is running but if this happens it is a
        //    programming error.
        // c) The program is shutting down and the timer has been removed by
        //    another component.
        timer_mgr_->unregisterTimer("memfile-lfc");

    } catch (const std::exception& ex) {
        // We don't want exceptions being thrown from the destructor so we just
        // log a message here.  The message is logged at debug severity as
        // we don't want an error message output during shutdown.
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_MEMFILE_LFC_UNREGISTER_TIMER_FAILED).arg(ex.what());
    }
}

void
LFCSetup::setup(const uint32_t lfc_interval,
                const boost::shared_ptr<CSVLeaseFile4>& lease_file4,
                const boost::shared_ptr<CSVLeaseFile6>& lease_file6,
                bool run_once_now) {

    // If to nothing to do, punt
    if (lfc_interval == 0 && !run_once_now) {
        return;
    }

    // Start preparing the command line for kea-lfc.
    std::string executable;
    char* c_executable = getenv(KEA_LFC_EXECUTABLE_ENV_NAME);
    if (!c_executable) {
        executable = KEA_LFC_EXECUTABLE;
    } else {
        executable = c_executable;
    }

    // Gather the base file name.
    std::string lease_file = lease_file4 ? lease_file4->getFilename() :
                                           lease_file6->getFilename();

    // Create the other names by appending suffixes to the base name.
    ProcessArgs args;
    // Universe: v4 or v6.
    args.push_back(lease_file4 ? "-4" : "-6");

    // Previous file.
    args.push_back("-x");
    args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                  Memfile_LeaseMgr::FILE_PREVIOUS));
    // Input file.
    args.push_back("-i");
    args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                  Memfile_LeaseMgr::FILE_INPUT));
    // Output file.
    args.push_back("-o");
    args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                  Memfile_LeaseMgr::FILE_OUTPUT));
    // Finish file.
    args.push_back("-f");
    args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                  Memfile_LeaseMgr::FILE_FINISH));
    // PID file.
    args.push_back("-p");
    args.push_back(Memfile_LeaseMgr::appendSuffix(lease_file,
                                                  Memfile_LeaseMgr::FILE_PID));

    // The configuration file is currently unused.
    args.push_back("-c");
    args.push_back("ignored-path");

    // Create the process (do not start it yet).
    process_.reset(new ProcessSpawn(ProcessSpawn::ASYNC, executable, args,
                                    ProcessEnvVars(), true));

    // If we've been told to run it once now, invoke the callback directly.
    if (run_once_now) {
        callback_();
    }

    // If it's supposed to run periodically, setup that now.
    if (lfc_interval > 0) {
        // Set the timer to call callback function periodically.
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_SETUP).arg(lfc_interval);

        // Multiple the lfc_interval value by 1000 as this value specifies
        // a timeout in seconds, whereas the setup() method expects the
        // timeout in milliseconds.
        timer_mgr_->registerTimer("memfile-lfc", callback_, lfc_interval * 1000,
                                  asiolink::IntervalTimer::REPEATING);
        timer_mgr_->setup("memfile-lfc");
    }
}

void
LFCSetup::execute() {
    try {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_EXECUTE)
            .arg(process_->getCommandLine());
        pid_ = process_->spawn();

    } catch (const ProcessSpawnError&) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_SPAWN_FAIL);
    }
}

bool
LFCSetup::isRunning() const {
    return (process_ && process_->isRunning(pid_));
}

int
LFCSetup::getExitStatus() const {
    if (!process_) {
        isc_throw(InvalidOperation, "unable to obtain LFC process exit code: "
                  " the process is null");
    }
    return (process_->getExitStatus(pid_));
}


/// @brief Base Memfile derivation of the statistical lease data query
///
/// This class provides the functionality such as results storage and row
/// fetching common to fulfilling the statistical lease data query.
///
class MemfileLeaseStatsQuery : public LeaseStatsQuery {
public:
    /// @brief Constructor for all subnets query
    ///
    /// @param select_mode The selection criteria which is either ALL_SUBNETS or
    /// ALL_SUBNET_POOLS
    MemfileLeaseStatsQuery(const SelectMode& select_mode = ALL_SUBNETS)
        : LeaseStatsQuery(select_mode), rows_(0), next_pos_(rows_.end()) {
    };

    /// @brief Constructor for single subnet query
    ///
    /// @param subnet_id ID of the desired subnet
    MemfileLeaseStatsQuery(const SubnetID& subnet_id)
        : LeaseStatsQuery(subnet_id), rows_(0), next_pos_(rows_.end()) {
    };

    /// @brief Constructor for subnet range query
    ///
    /// @param first_subnet_id ID of the first subnet in the desired range
    /// @param last_subnet_id ID of the last subnet in the desired range
    MemfileLeaseStatsQuery(const SubnetID& first_subnet_id, const SubnetID& last_subnet_id)
        : LeaseStatsQuery(first_subnet_id, last_subnet_id), rows_(0), next_pos_(rows_.end()) {
    };

    /// @brief Destructor
    virtual ~MemfileLeaseStatsQuery() {};

    /// @brief Fetches the next row in the result set
    ///
    /// Once the internal result set has been populated by invoking the
    /// the start() method, this method is used to iterate over the
    /// result set rows.  Once the last row has been fetched, subsequent
    /// calls will return false.
    /// @param row Storage for the fetched row
    ///
    /// @return True if the fetch succeeded, false if there are no more
    /// rows to fetch.
    virtual bool getNextRow(LeaseStatsRow& row) {
        if (next_pos_ == rows_.end()) {
            return (false);
        }

        row = *next_pos_;
        ++next_pos_;
        return (true);
    }

    /// @brief Returns the number of rows in the result set
    int getRowCount() const {
        return (rows_.size());
    }

protected:
    /// @brief A vector containing the "result set"
    std::vector<LeaseStatsRow> rows_;

    /// @brief An iterator for accessing the next row within the result set
    std::vector<LeaseStatsRow>::iterator next_pos_;
};

/// @brief Memfile derivation of the IPv4 statistical lease data query
///
/// This class is used to recalculate IPv4 lease statistics for Memfile
/// lease storage.  It does so by iterating over the given storage,
/// accumulating counts of leases in each of the monitored lease states
/// for each subnet and storing these counts in an internal collection.
/// The populated result set will contain one entry per monitored state
/// per subnet.
///
class MemfileLeaseStatsQuery4 : public MemfileLeaseStatsQuery {
public:
    /// @brief Constructor for an all subnets query
    ///
    /// @param storage4 A pointer to the v4 lease storage to be counted
    /// @param select_mode The selection criteria which is either ALL_SUBNETS or
    /// ALL_SUBNET_POOLS
    MemfileLeaseStatsQuery4(Lease4Storage& storage4,
                            const SelectMode& select_mode = ALL_SUBNETS)
        : MemfileLeaseStatsQuery(select_mode), storage4_(storage4) {
    };

    /// @brief Constructor for a single subnet query
    ///
    /// @param storage4 A pointer to the v4 lease storage to be counted
    /// @param subnet_id ID of the desired subnet
    MemfileLeaseStatsQuery4(Lease4Storage& storage4, const SubnetID& subnet_id)
        : MemfileLeaseStatsQuery(subnet_id), storage4_(storage4) {
    };

    /// @brief Constructor for a subnet range query
    ///
    /// @param storage4 A pointer to the v4 lease storage to be counted
    /// @param first_subnet_id ID of the first subnet in the desired range
    /// @param last_subnet_id ID of the last subnet in the desired range
    MemfileLeaseStatsQuery4(Lease4Storage& storage4, const SubnetID& first_subnet_id,
                            const SubnetID& last_subnet_id)
        : MemfileLeaseStatsQuery(first_subnet_id, last_subnet_id), storage4_(storage4) {
    };

    /// @brief Destructor
    virtual ~MemfileLeaseStatsQuery4() {};

    /// @brief Creates the IPv4 lease statistical data result set
    ///
    /// The result set is populated by iterating over the IPv4 leases in
    /// storage, in ascending order by subnet id or by subnet id and pool id,
    /// accumulating the lease state counts per subnet or per subnet and pool.
    /// At the completion of all entries for a given subnet or pool, the counts
    /// are used to create LeaseStatsRow instances which are appended to an
    /// internal vector.  The process results in a vector containing one entry
    /// per state per subnet or per subnet and pool.
    ///
    /// Currently the states counted are:
    ///
    /// - Lease::STATE_DEFAULT (i.e. assigned)
    /// - Lease::STATE_DECLINED
    void start() {
        switch (getSelectMode()) {
        case ALL_SUBNETS:
        case SINGLE_SUBNET:
        case SUBNET_RANGE:
            startSubnets();
            break;

        case ALL_SUBNET_POOLS:
            startSubnetPools();
            break;
        }
    }

private:
    /// @brief Creates the IPv4 lease statistical data result set
    ///
    /// The result set is populated by iterating over the IPv4 leases in
    /// storage, in ascending order by subnet id, accumulating the lease state
    /// counts per subnet.
    /// At the completion of all entries for a given subnet, the counts are
    /// used to create LeaseStatsRow instances which are appended to an
    /// internal vector.  The process results in a vector containing one entry
    /// per state per subnet.
    ///
    /// Currently the states counted are:
    ///
    /// - Lease::STATE_DEFAULT (i.e. assigned)
    /// - Lease::STATE_DECLINED
    void startSubnets() {
        const Lease4StorageSubnetIdIndex& idx
            = storage4_.get<SubnetIdIndexTag>();

        // Set lower and upper bounds based on select mode
        Lease4StorageSubnetIdIndex::const_iterator lower;
        Lease4StorageSubnetIdIndex::const_iterator upper;

        switch (getSelectMode()) {
        case ALL_SUBNETS:
            lower = idx.begin();
            upper = idx.end();
            break;

        case SINGLE_SUBNET:
            lower = idx.lower_bound(getFirstSubnetID());
            upper = idx.upper_bound(getFirstSubnetID());
            break;

        case SUBNET_RANGE:
            lower = idx.lower_bound(getFirstSubnetID());
            upper = idx.upper_bound(getLastSubnetID());
            break;

        default:
            return;
        }

        // Return an empty set if there are no rows.
        if (lower == upper) {
            return;
        }

        // Iterate over the leases in order by subnet, accumulating per
        // subnet counts for each state of interest.  As we finish each
        // subnet, add the appropriate rows to our result set.
        SubnetID cur_id = 0;
        int64_t assigned = 0;
        int64_t declined = 0;
        for (Lease4StorageSubnetIdIndex::const_iterator lease = lower;
             lease != upper; ++lease) {
            // If we've hit the next subnet, add rows for the current subnet
            // and wipe the accumulators
            if ((*lease)->subnet_id_ != cur_id) {
                if (cur_id > 0) {
                    if (assigned > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id,
                                                      Lease::STATE_DEFAULT,
                                                      assigned));
                        assigned = 0;
                    }

                    if (declined > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id,
                                                      Lease::STATE_DECLINED,
                                                      declined));
                        declined = 0;
                    }
                }

                // Update current subnet id
                cur_id = (*lease)->subnet_id_;
            }

            // Bump the appropriate accumulator
            if ((*lease)->state_ == Lease::STATE_DEFAULT) {
                ++assigned;
            } else if ((*lease)->state_ == Lease::STATE_DECLINED) {
                ++declined;
            }
        }

        // Make the rows for last subnet
        if (assigned > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::STATE_DEFAULT,
                                          assigned));
        }

        if (declined > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::STATE_DECLINED,
                                          declined));
        }

        // Reset the next row position back to the beginning of the rows.
        next_pos_ = rows_.begin();
    }

    /// @brief Creates the IPv4 lease statistical data result set
    ///
    /// The result set is populated by iterating over the IPv4 leases in
    /// storage, in ascending order by subnet id and pool id, accumulating the
    /// lease state counts per subnet and pool.
    /// At the completion of all entries for a given subnet or pool, the counts
    /// are used to create LeaseStatsRow instances which are appended to an
    /// internal vector.  The process results in a vector containing one entry
    /// per state per subnet and pool.
    ///
    /// Currently the states counted are:
    ///
    /// - Lease::STATE_DEFAULT (i.e. assigned)
    /// - Lease::STATE_DECLINED
    void startSubnetPools() {
        const Lease4StorageSubnetIdPoolIdIndex& idx
            = storage4_.get<SubnetIdPoolIdIndexTag>();

        // Set lower and upper bounds based on select mode
        Lease4StorageSubnetIdPoolIdIndex::const_iterator lower;
        Lease4StorageSubnetIdPoolIdIndex::const_iterator upper;
        switch (getSelectMode()) {
        case ALL_SUBNET_POOLS:
            lower = idx.begin();
            upper = idx.end();
            break;

        default:
            return;
        }

        // Return an empty set if there are no rows.
        if (lower == upper) {
            return;
        }

        // Iterate over the leases in order by subnet and pool, accumulating per
        // subnet and pool counts for each state of interest.  As we finish each
        // subnet or pool, add the appropriate rows to our result set.
        SubnetID cur_id = 0;
        uint32_t cur_pool_id = 0;
        int64_t assigned = 0;
        int64_t declined = 0;
        for (Lease4StorageSubnetIdPoolIdIndex::const_iterator lease = lower;
             lease != upper; ++lease) {
            // If we've hit the next pool, add rows for the current subnet and
            // pool and wipe the accumulators
            if ((*lease)->pool_id_ != cur_pool_id) {
                if (assigned > 0) {
                    rows_.push_back(LeaseStatsRow(cur_id,
                                                  Lease::STATE_DEFAULT,
                                                  assigned, cur_pool_id));
                    assigned = 0;
                }

                if (declined > 0) {
                    rows_.push_back(LeaseStatsRow(cur_id,
                                                  Lease::STATE_DECLINED,
                                                  declined, cur_pool_id));
                    declined = 0;
                }

                // Update current pool id
                cur_pool_id = (*lease)->pool_id_;
            }

            // If we've hit the next subnet, add rows for the current subnet
            // and wipe the accumulators
            if ((*lease)->subnet_id_ != cur_id) {
                if (cur_id > 0) {
                    if (assigned > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id,
                                                      Lease::STATE_DEFAULT,
                                                      assigned, cur_pool_id));
                        assigned = 0;
                    }

                    if (declined > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id,
                                                      Lease::STATE_DECLINED,
                                                      declined, cur_pool_id));
                        declined = 0;
                    }
                }

                // Update current subnet id
                cur_id = (*lease)->subnet_id_;

                // Reset pool id
                cur_pool_id = 0;
            }

            // Bump the appropriate accumulator
            if ((*lease)->state_ == Lease::STATE_DEFAULT) {
                ++assigned;
            } else if ((*lease)->state_ == Lease::STATE_DECLINED) {
                ++declined;
            }
        }

        // Make the rows for last subnet
        if (assigned > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::STATE_DEFAULT,
                                          assigned, cur_pool_id));
        }

        if (declined > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::STATE_DECLINED,
                                          declined, cur_pool_id));
        }

        // Reset the next row position back to the beginning of the rows.
        next_pos_ = rows_.begin();
    }

    /// @brief The Memfile storage containing the IPv4 leases to analyze
    Lease4Storage& storage4_;
};


/// @brief Memfile derivation of the IPv6 statistical lease data query
///
/// This class is used to recalculate IPv6 lease statistics for Memfile
/// lease storage.  It does so by iterating over the given storage,
/// accumulating counts of leases in each of the monitored lease states
/// for each subnet and storing these counts in an internal collection.
/// The populated result set will contain one entry per monitored state
/// per subnet.
///
class MemfileLeaseStatsQuery6 : public MemfileLeaseStatsQuery {
public:
    /// @brief Constructor
    ///
    /// @param storage6 A pointer to the v6 lease storage to be counted
    /// @param select_mode The selection criteria which is either ALL_SUBNETS or
    /// ALL_SUBNET_POOLS
    MemfileLeaseStatsQuery6(Lease6Storage& storage6,
                            const SelectMode& select_mode = ALL_SUBNETS)
        : MemfileLeaseStatsQuery(select_mode), storage6_(storage6) {
    };

    /// @brief Constructor for a single subnet query
    ///
    /// @param storage6 A pointer to the v6 lease storage to be counted
    /// @param subnet_id ID of the desired subnet
    MemfileLeaseStatsQuery6(Lease6Storage& storage6, const SubnetID& subnet_id)
        : MemfileLeaseStatsQuery(subnet_id), storage6_(storage6) {
    };

    /// @brief Constructor for a subnet range query
    ///
    /// @param storage6 A pointer to the v6 lease storage to be counted
    /// @param first_subnet_id ID of the first subnet in the desired range
    /// @param last_subnet_id ID of the last subnet in the desired range
    MemfileLeaseStatsQuery6(Lease6Storage& storage6, const SubnetID& first_subnet_id,
                            const SubnetID& last_subnet_id)
        : MemfileLeaseStatsQuery(first_subnet_id, last_subnet_id), storage6_(storage6) {
    };

    /// @brief Destructor
    virtual ~MemfileLeaseStatsQuery6() {};

    /// @brief Creates the IPv6 lease statistical data result set
    ///
    /// The result set is populated by iterating over the IPv6 leases in
    /// storage, in ascending order by subnet id or by subnet id and pool id,
    /// accumulating the lease state counts per subnet or per subnet and pool.
    /// At the completion of all entries for a given subnet or pool, the counts
    /// are used to create LeaseStatsRow instances which are appended to an
    /// internal vector.  The process results in a vector containing one entry
    /// per state per subnet or per subnet and pool.
    ///
    /// Currently the states counted are:
    ///
    /// - Lease::STATE_DEFAULT (i.e. assigned)
    /// - Lease::STATE_DECLINED
    /// - Lease::STATE_REGISTERED
    void start() {
        switch (getSelectMode()) {
        case ALL_SUBNETS:
        case SINGLE_SUBNET:
        case SUBNET_RANGE:
            startSubnets();
            break;

        case ALL_SUBNET_POOLS:
            startSubnetPools();
            break;
        }
    }

private:
    /// @brief Creates the IPv6 lease statistical data result set
    ///
    /// The result set is populated by iterating over the IPv6 leases in
    /// storage, in ascending order by subnet id, accumulating the lease state
    /// counts per subnet.
    /// At the completion of all entries for a given subnet, the counts are
    /// used to create LeaseStatsRow instances which are appended to an
    /// internal vector.  The process results in a vector containing one entry
    /// per state per subnet.
    ///
    /// Currently the states counted are:
    ///
    /// - Lease::STATE_DEFAULT (i.e. assigned)
    /// - Lease::STATE_DECLINED
    /// - Lease::STATE_REGISTERED
    virtual void startSubnets() {
        const Lease6StorageSubnetIdIndex& idx
            = storage6_.get<SubnetIdIndexTag>();

        // Set lower and upper bounds based on select mode
        Lease6StorageSubnetIdIndex::const_iterator lower;
        Lease6StorageSubnetIdIndex::const_iterator upper;
        switch (getSelectMode()) {
        case ALL_SUBNETS:
            lower = idx.begin();
            upper = idx.end();
            break;

        case SINGLE_SUBNET:
            lower = idx.lower_bound(getFirstSubnetID());
            upper = idx.upper_bound(getFirstSubnetID());
            break;

        case SUBNET_RANGE:
            lower = idx.lower_bound(getFirstSubnetID());
            upper = idx.upper_bound(getLastSubnetID());
            break;

        default:
            return;
        }

        // Return an empty set if there are no rows.
        if (lower == upper) {
            return;
        }

        // Iterate over the leases in order by subnet, accumulating per
        // subnet counts for each state of interest.  As we finish each
        // subnet, add the appropriate rows to our result set.
        SubnetID cur_id = 0;
        int64_t assigned = 0;
        int64_t declined = 0;
        int64_t assigned_pds = 0;
        int64_t registered = 0;
        for (Lease6StorageSubnetIdIndex::const_iterator lease = lower;
             lease != upper; ++lease) {
            // If we've hit the next subnet, add rows for the current subnet
            // and wipe the accumulators
            if ((*lease)->subnet_id_ != cur_id) {
                if (cur_id > 0) {
                    if (assigned > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                                      Lease::STATE_DEFAULT,
                                                      assigned));
                        assigned = 0;
                    }

                    if (declined > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                                      Lease::STATE_DECLINED,
                                                      declined));
                        declined = 0;
                    }

                    if (assigned_pds > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_PD,
                                                      Lease::STATE_DEFAULT,
                                                      assigned_pds));
                        assigned_pds = 0;
                    }

                    if (registered > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                                      Lease::STATE_REGISTERED,
                                                      registered));
                        registered = 0;
                    }
                }

                // Update current subnet id
                cur_id = (*lease)->subnet_id_;
            }

            // Bump the appropriate accumulator
            if ((*lease)->state_ == Lease::STATE_DEFAULT) {
                switch((*lease)->type_) {
                case Lease::TYPE_NA:
                    ++assigned;
                    break;
                case Lease::TYPE_PD:
                    ++assigned_pds;
                    break;
                default:
                    break;
                }
            } else if ((*lease)->state_ == Lease::STATE_DECLINED) {
                // In theory only NAs can be declined
                if (((*lease)->type_) == Lease::TYPE_NA) {
                    ++declined;
                }
            } else if ((*lease)->state_ == Lease::STATE_REGISTERED) {
                // In theory only NAs can be registered
                if (((*lease)->type_) == Lease::TYPE_NA) {
                    ++registered;
                }
            }
        }

        // Make the rows for last subnet, unless there were no rows
        if (assigned > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                          Lease::STATE_DEFAULT, assigned));
        }

        if (declined > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                          Lease::STATE_DECLINED, declined));
        }

        if (assigned_pds > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_PD,
                                          Lease::STATE_DEFAULT, assigned_pds));
        }

        if (registered > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                          Lease::STATE_REGISTERED, registered));
        }

        // Set the next row position to the beginning of the rows.
        next_pos_ = rows_.begin();
    }

    /// @brief Creates the IPv6 lease statistical data result set
    ///
    /// The result set is populated by iterating over the IPv6 leases in
    /// storage, in ascending order by subnet id and pool id, accumulating the
    /// lease state counts per subnet and pool.
    /// At the completion of all entries for a given subnet or pool, the counts
    /// are used to create LeaseStatsRow instances which are appended to an
    /// internal vector.  The process results in a vector containing one entry
    /// per state per subnet and pool.
    ///
    /// Currently the states counted are:
    ///
    /// - Lease::STATE_DEFAULT (i.e. assigned)
    /// - Lease::STATE_DECLINED
    virtual void startSubnetPools() {
        const Lease6StorageSubnetIdPoolIdIndex& idx
            = storage6_.get<SubnetIdPoolIdIndexTag>();

        // Set lower and upper bounds based on select mode
        Lease6StorageSubnetIdPoolIdIndex::const_iterator lower;
        Lease6StorageSubnetIdPoolIdIndex::const_iterator upper;
        switch (getSelectMode()) {
        case ALL_SUBNET_POOLS:
            lower = idx.begin();
            upper = idx.end();
            break;

        default:
            return;
        }

        // Return an empty set if there are no rows.
        if (lower == upper) {
            return;
        }

        // Iterate over the leases in order by subnet, accumulating per
        // subnet counts for each state of interest.  As we finish each
        // subnet, add the appropriate rows to our result set.
        SubnetID cur_id = 0;
        uint32_t cur_pool_id = 0;
        int64_t assigned = 0;
        int64_t declined = 0;
        int64_t assigned_pds = 0;
        for (Lease6StorageSubnetIdPoolIdIndex::const_iterator lease = lower;
             lease != upper; ++lease) {
            // If we've hit the next pool, add rows for the current subnet and
            // pool and wipe the accumulators
            if ((*lease)->pool_id_ != cur_pool_id) {
                if (assigned > 0) {
                    rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                                  Lease::STATE_DEFAULT,
                                                  assigned, cur_pool_id));
                    assigned = 0;
                }

                if (declined > 0) {
                    rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                                  Lease::STATE_DECLINED,
                                                  declined, cur_pool_id));
                    declined = 0;
                }

                if (assigned_pds > 0) {
                    rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_PD,
                                                  Lease::STATE_DEFAULT,
                                                  assigned_pds, cur_pool_id));
                    assigned_pds = 0;
                }

                // Update current pool id
                cur_pool_id = (*lease)->pool_id_;
            }

            // If we've hit the next subnet, add rows for the current subnet
            // and wipe the accumulators
            if ((*lease)->subnet_id_ != cur_id) {
                if (cur_id > 0) {
                    if (assigned > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                                      Lease::STATE_DEFAULT,
                                                      assigned, cur_pool_id));
                        assigned = 0;
                    }

                    if (declined > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                                      Lease::STATE_DECLINED,
                                                      declined, cur_pool_id));
                        declined = 0;
                    }

                    if (assigned_pds > 0) {
                        rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_PD,
                                                      Lease::STATE_DEFAULT,
                                                      assigned_pds, cur_pool_id));
                        assigned_pds = 0;
                    }
                }

                // Update current subnet id
                cur_id = (*lease)->subnet_id_;

                // Reset pool id
                cur_pool_id = 0;
            }

            // Bump the appropriate accumulator
            if ((*lease)->state_ == Lease::STATE_DEFAULT) {
                switch((*lease)->type_) {
                case Lease::TYPE_NA:
                    ++assigned;
                    break;
                case Lease::TYPE_PD:
                    ++assigned_pds;
                    break;
                default:
                    break;
                }
            } else if ((*lease)->state_ == Lease::STATE_DECLINED) {
                // In theory only NAs can be declined
                if (((*lease)->type_) == Lease::TYPE_NA) {
                    ++declined;
                }
            }
        }

        // Make the rows for last subnet, unless there were no rows
        if (assigned > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                          Lease::STATE_DEFAULT, assigned,
                                          cur_pool_id));
        }

        if (declined > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_NA,
                                          Lease::STATE_DECLINED, declined,
                                          cur_pool_id));
        }

        if (assigned_pds > 0) {
            rows_.push_back(LeaseStatsRow(cur_id, Lease::TYPE_PD,
                                          Lease::STATE_DEFAULT, assigned_pds,
                                          cur_pool_id));
        }

        // Set the next row position to the beginning of the rows.
        next_pos_ = rows_.begin();
    }

    /// @brief The Memfile storage containing the IPv6 leases to analyze
    Lease6Storage& storage6_;
};

// Explicit definition of class static constants.  Values are given in the
// declaration so they're not needed here.
const int Memfile_LeaseMgr::MAJOR_VERSION_V4;
const int Memfile_LeaseMgr::MINOR_VERSION_V4;
const int Memfile_LeaseMgr::MAJOR_VERSION_V6;
const int Memfile_LeaseMgr::MINOR_VERSION_V6;

Memfile_LeaseMgr::Memfile_LeaseMgr(const DatabaseConnection::ParameterMap& parameters)
    : TrackingLeaseMgr(), lfc_setup_(), conn_(parameters), mutex_(new std::mutex) {
    bool conversion_needed = false;

    // Check if the extended info tables are enabled.
    setExtendedInfoTablesEnabled(parameters);

    // Check the universe and use v4 file or v6 file.
    std::string universe = conn_.getParameter("universe");
    if (universe == "4") {
        std::string file4 = initLeaseFilePath(V4);
        if (!file4.empty()) {
            conversion_needed = loadLeasesFromFiles<Lease4,
                                                 CSVLeaseFile4>(file4,
                                                                lease_file4_,
                                                                storage4_);
            static_cast<void>(extractExtendedInfo4(false, false));
        }
    } else {
        std::string file6 = initLeaseFilePath(V6);
        if (!file6.empty()) {
            conversion_needed = loadLeasesFromFiles<Lease6,
                                                 CSVLeaseFile6>(file6,
                                                                lease_file6_,
                                                                storage6_);
            buildExtendedInfoTables6();
        }
    }

    // If lease persistence have been disabled for both v4 and v6,
    // issue a warning. It is ok not to write leases to disk when
    // doing testing, but it should not be done in normal server
    // operation.
    if (!persistLeases(V4) && !persistLeases(V6)) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_MEMFILE_NO_STORAGE);
    } else {
        if (conversion_needed) {
            auto const& version(getVersion());
            LOG_WARN(dhcpsrv_logger, DHCPSRV_MEMFILE_CONVERTING_LEASE_FILES)
                    .arg(version.first).arg(version.second);
        }
        lfcSetup(conversion_needed);
    }
}

Memfile_LeaseMgr::~Memfile_LeaseMgr() {
    if (lease_file4_) {
        lease_file4_->close();
        lease_file4_.reset();
    }
    if (lease_file6_) {
        lease_file6_->close();
        lease_file6_.reset();
    }
}

std::string
Memfile_LeaseMgr::getDBVersionInternal(Universe const& u) {
    std::stringstream tmp;
    tmp << "Memfile backend ";
    if (u == V4) {
        tmp << MAJOR_VERSION_V4 << "." << MINOR_VERSION_V4;
    } else if (u == V6) {
        tmp << MAJOR_VERSION_V6 << "." << MINOR_VERSION_V6;
    }
    return tmp.str();
}

std::string
Memfile_LeaseMgr::getDBVersion() {
    uint16_t family = CfgMgr::instance().getFamily();
    if (family == AF_INET6) {
        return (Memfile_LeaseMgr::getDBVersionInternal(Memfile_LeaseMgr::V6));
    } else {
        return (Memfile_LeaseMgr::getDBVersionInternal(Memfile_LeaseMgr::V4));
    }
}

bool
Memfile_LeaseMgr::addLeaseInternal(const Lease4Ptr& lease) {
    if (getLease4Internal(lease->addr_)) {
        // there is a lease with specified address already
        return (false);
    }

    // Try to write a lease to disk first. If this fails, the lease will
    // not be inserted to the memory and the disk and in-memory data will
    // remain consistent.
    if (persistLeases(V4)) {
        lease_file4_->append(*lease);
    }

    storage4_.insert(lease);

    // Update lease current expiration time (allows update between the creation
    // of the Lease up to the point of insertion in the database).
    lease->updateCurrentExpirationTime();

    // Increment class lease counters.
    class_lease_counter_.addLease(lease);

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackAddLease(lease);
    }

    return (true);
}

bool
Memfile_LeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_ADD_ADDR4).arg(lease->addr_.toText());

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (addLeaseInternal(lease));
    } else {
        return (addLeaseInternal(lease));
    }
}

bool
Memfile_LeaseMgr::addLeaseInternal(const Lease6Ptr& lease) {
    if (getLease6Internal(lease->type_, lease->addr_)) {
        // there is a lease with specified address already
        return (false);
    }

    // Try to write a lease to disk first. If this fails, the lease will
    // not be inserted to the memory and the disk and in-memory data will
    // remain consistent.
    if (persistLeases(V6)) {
        lease_file6_->append(*lease);
    }

    lease->extended_info_action_ = Lease6::ACTION_IGNORE;
    storage6_.insert(lease);

    // Update lease current expiration time (allows update between the creation
    // of the Lease up to the point of insertion in the database).
    lease->updateCurrentExpirationTime();

    // Increment class lease counters.
    class_lease_counter_.addLease(lease);

    if (getExtendedInfoTablesEnabled()) {
        static_cast<void>(addExtendedInfo6(lease));
    }

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackAddLease(lease);
    }

    return (true);
}

bool
Memfile_LeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_ADD_ADDR6).arg(lease->addr_.toText());

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (addLeaseInternal(lease));
    } else {
        return (addLeaseInternal(lease));
    }
}

Lease4Ptr
Memfile_LeaseMgr::getLease4Internal(const isc::asiolink::IOAddress& addr) const {
    const Lease4StorageAddressIndex& idx = storage4_.get<AddressIndexTag>();
    Lease4StorageAddressIndex::iterator l = idx.find(addr);
    if (l == idx.end()) {
        return (Lease4Ptr());
    } else {
        return (Lease4Ptr(new Lease4(**l)));
    }
}

Lease4Ptr
Memfile_LeaseMgr::getLease4(const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_ADDR4).arg(addr.toText());

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLease4Internal(addr));
    } else {
        return (getLease4Internal(addr));
    }
}

void
Memfile_LeaseMgr::getLease4Internal(const HWAddr& hwaddr,
                                    Lease4Collection& collection) const {
    // Using composite index by 'hw address' and 'subnet id'. It is
    // ok to use it for searching by the 'hw address' only.
    const Lease4StorageHWAddressSubnetIdIndex& idx =
        storage4_.get<HWAddressSubnetIdIndexTag>();
    std::pair<Lease4StorageHWAddressSubnetIdIndex::const_iterator,
              Lease4StorageHWAddressSubnetIdIndex::const_iterator> l
        = idx.equal_range(boost::make_tuple(hwaddr.hwaddr_));

    BOOST_FOREACH(auto const& lease, l) {
        collection.push_back(Lease4Ptr(new Lease4(*lease)));
    }
}

Lease4Collection
Memfile_LeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_HWADDR).arg(hwaddr.toText());

    Lease4Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLease4Internal(hwaddr, collection);
    } else {
        getLease4Internal(hwaddr, collection);
    }

    return (collection);
}

Lease4Ptr
Memfile_LeaseMgr::getLease4Internal(const HWAddr& hwaddr,
                                    SubnetID subnet_id) const {
    // Get the index by HW Address and Subnet Identifier.
    const Lease4StorageHWAddressSubnetIdIndex& idx =
        storage4_.get<HWAddressSubnetIdIndexTag>();
    // Try to find the lease using HWAddr and subnet id.
    Lease4StorageHWAddressSubnetIdIndex::const_iterator lease =
        idx.find(boost::make_tuple(hwaddr.hwaddr_, subnet_id));
    // Lease was not found. Return empty pointer to the caller.
    if (lease == idx.end()) {
        return (Lease4Ptr());
    }

    // Lease was found. Return it to the caller.
    return (Lease4Ptr(new Lease4(**lease)));
}

Lease4Ptr
Memfile_LeaseMgr::getLease4(const HWAddr& hwaddr,
                            SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_SUBID_HWADDR).arg(subnet_id)
        .arg(hwaddr.toText());

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLease4Internal(hwaddr, subnet_id));
    } else {
        return (getLease4Internal(hwaddr, subnet_id));
    }
}

void
Memfile_LeaseMgr::getLease4Internal(const ClientId& client_id,
                                    Lease4Collection& collection) const {
    // Using composite index by 'client id' and 'subnet id'. It is ok
    // to use it to search by 'client id' only.
    const Lease4StorageClientIdSubnetIdIndex& idx =
        storage4_.get<ClientIdSubnetIdIndexTag>();
    std::pair<Lease4StorageClientIdSubnetIdIndex::const_iterator,
              Lease4StorageClientIdSubnetIdIndex::const_iterator> l
        = idx.equal_range(boost::make_tuple(client_id.getClientId()));

    BOOST_FOREACH(auto const& lease, l) {
        collection.push_back(Lease4Ptr(new Lease4(*lease)));
    }
}

Lease4Collection
Memfile_LeaseMgr::getLease4(const ClientId& client_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_CLIENTID).arg(client_id.toText());

    Lease4Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLease4Internal(client_id, collection);
    } else {
        getLease4Internal(client_id, collection);
    }

    return (collection);
}

Lease4Ptr
Memfile_LeaseMgr::getLease4Internal(const ClientId& client_id,
                                    SubnetID subnet_id) const {
    // Get the index by client and subnet id.
    const Lease4StorageClientIdSubnetIdIndex& idx =
        storage4_.get<ClientIdSubnetIdIndexTag>();
    // Try to get the lease using client id and subnet id.
    Lease4StorageClientIdSubnetIdIndex::const_iterator lease =
        idx.find(boost::make_tuple(client_id.getClientId(), subnet_id));
    // Lease was not found. Return empty pointer to the caller.
    if (lease == idx.end()) {
        return (Lease4Ptr());
    }
    // Lease was found. Return it to the caller.
    return (Lease4Ptr(new Lease4(**lease)));
}

Lease4Ptr
Memfile_LeaseMgr::getLease4(const ClientId& client_id,
                            SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_SUBID_CLIENTID).arg(subnet_id)
              .arg(client_id.toText());

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLease4Internal(client_id, subnet_id));
    } else {
        return (getLease4Internal(client_id, subnet_id));
    }
}

void
Memfile_LeaseMgr::getLeases4Internal(SubnetID subnet_id,
                                     Lease4Collection& collection) const {
    const Lease4StorageSubnetIdIndex& idx = storage4_.get<SubnetIdIndexTag>();
    std::pair<Lease4StorageSubnetIdIndex::const_iterator,
              Lease4StorageSubnetIdIndex::const_iterator> l =
        idx.equal_range(subnet_id);

    BOOST_FOREACH(auto const& lease, l) {
        collection.push_back(Lease4Ptr(new Lease4(*lease)));
    }
}

Lease4Collection
Memfile_LeaseMgr::getLeases4(SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET_SUBID4)
        .arg(subnet_id);

    Lease4Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases4Internal(subnet_id, collection);
    } else {
        getLeases4Internal(subnet_id, collection);
    }

    return (collection);
}

void
Memfile_LeaseMgr::getLeases4Internal(const std::string& hostname,
                                     Lease4Collection& collection) const {
    const Lease4StorageHostnameIndex& idx = storage4_.get<HostnameIndexTag>();
    std::pair<Lease4StorageHostnameIndex::const_iterator,
              Lease4StorageHostnameIndex::const_iterator> l =
        idx.equal_range(hostname);

    BOOST_FOREACH(auto const& lease, l) {
        collection.push_back(Lease4Ptr(new Lease4(*lease)));
    }
}

Lease4Collection
Memfile_LeaseMgr::getLeases4(const std::string& hostname) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET_HOSTNAME4)
        .arg(hostname);

    Lease4Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases4Internal(hostname, collection);
    } else {
        getLeases4Internal(hostname, collection);
    }

    return (collection);
}

void
Memfile_LeaseMgr::getLeases4Internal(Lease4Collection& collection) const {
   for (auto const& lease : storage4_) {
       collection.push_back(Lease4Ptr(new Lease4(*lease)));
   }
}

Lease4Collection
Memfile_LeaseMgr::getLeases4() const {
   LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET4);

   Lease4Collection collection;
   if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases4Internal(collection);
   } else {
        getLeases4Internal(collection);
   }

   return (collection);
}

void
Memfile_LeaseMgr::getLeases4Internal(const asiolink::IOAddress& lower_bound_address,
                                     const LeasePageSize& page_size,
                                     Lease4Collection& collection) const {
    const Lease4StorageAddressIndex& idx = storage4_.get<AddressIndexTag>();
    Lease4StorageAddressIndex::const_iterator lb = idx.lower_bound(lower_bound_address);

    // Exclude the lower bound address specified by the caller.
    if ((lb != idx.end()) && ((*lb)->addr_ == lower_bound_address)) {
        ++lb;
    }

    // Return all other leases being within the page size.
    for (auto lease = lb;
         (lease != idx.end()) &&
         (static_cast<size_t>(std::distance(lb, lease)) < page_size.page_size_);
         ++lease) {
        collection.push_back(Lease4Ptr(new Lease4(**lease)));
    }
}

Lease4Collection
Memfile_LeaseMgr::getLeases4(const asiolink::IOAddress& lower_bound_address,
                             const LeasePageSize& page_size) const {
    // Expecting IPv4 address.
    if (!lower_bound_address.isV4()) {
        isc_throw(InvalidAddressFamily, "expected IPv4 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET_PAGE4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText());

    Lease4Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases4Internal(lower_bound_address, page_size, collection);
    } else {
        getLeases4Internal(lower_bound_address, page_size, collection);
    }

    return (collection);
}

Lease6Ptr
Memfile_LeaseMgr::getLease6Internal(Lease::Type type,
                                    const isc::asiolink::IOAddress& addr) const {
    Lease6Storage::iterator l = storage6_.find(addr);
    if (l == storage6_.end() || !(*l) || ((*l)->type_ != type)) {
        return (Lease6Ptr());
    } else {
        return (Lease6Ptr(new Lease6(**l)));
    }
}

Lease6Ptr
Memfile_LeaseMgr::getAnyLease6Internal(const isc::asiolink::IOAddress& addr) const {
    Lease6Storage::iterator l = storage6_.find(addr);
    if (l == storage6_.end() || !(*l)) {
        return (Lease6Ptr());
    } else {
        return (Lease6Ptr(new Lease6(**l)));
    }
}

Lease6Ptr
Memfile_LeaseMgr::getLease6(Lease::Type type,
                            const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_ADDR6)
        .arg(addr.toText())
        .arg(Lease::typeToText(type));

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLease6Internal(type, addr));
    } else {
        return (getLease6Internal(type, addr));
    }
}

void
Memfile_LeaseMgr::getLeases6Internal(Lease::Type type,
                                     const DUID& duid,
                                     uint32_t iaid,
                                     Lease6Collection& collection) const {
    // Get the index by DUID, IAID, lease type.
    const Lease6StorageDuidIaidTypeIndex& idx = storage6_.get<DuidIaidTypeIndexTag>();
    // Try to get the lease using the DUID, IAID and lease type.
    std::pair<Lease6StorageDuidIaidTypeIndex::const_iterator,
              Lease6StorageDuidIaidTypeIndex::const_iterator> l =
        idx.equal_range(boost::make_tuple(duid.getDuid(), iaid, type));

    for (Lease6StorageDuidIaidTypeIndex::const_iterator lease =
         l.first; lease != l.second; ++lease) {
        collection.push_back(Lease6Ptr(new Lease6(**lease)));
    }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6(Lease::Type type,
                             const DUID& duid,
                             uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_IAID_DUID)
        .arg(iaid)
        .arg(duid.toText())
        .arg(Lease::typeToText(type));

    Lease6Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases6Internal(type, duid, iaid, collection);
    } else {
        getLeases6Internal(type, duid, iaid, collection);
    }

    return (collection);
}

void
Memfile_LeaseMgr::getLeases6Internal(Lease::Type type,
                                     const DUID& duid,
                                     uint32_t iaid,
                                     SubnetID subnet_id,
                                     Lease6Collection& collection) const {
    // Get the index by DUID, IAID, lease type.
    const Lease6StorageDuidIaidTypeIndex& idx = storage6_.get<DuidIaidTypeIndexTag>();
    // Try to get the lease using the DUID, IAID and lease type.
    std::pair<Lease6StorageDuidIaidTypeIndex::const_iterator,
              Lease6StorageDuidIaidTypeIndex::const_iterator> l =
        idx.equal_range(boost::make_tuple(duid.getDuid(), iaid, type));

    for (Lease6StorageDuidIaidTypeIndex::const_iterator lease =
         l.first; lease != l.second; ++lease) {
        // Filter out the leases which subnet id doesn't match.
        if ((*lease)->subnet_id_ == subnet_id) {
            collection.push_back(Lease6Ptr(new Lease6(**lease)));
        }
    }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6(Lease::Type type,
                             const DUID& duid,
                             uint32_t iaid,
                             SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_IAID_SUBID_DUID)
        .arg(iaid)
        .arg(subnet_id)
        .arg(duid.toText())
        .arg(Lease::typeToText(type));

    Lease6Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases6Internal(type, duid, iaid, subnet_id, collection);
    } else {
        getLeases6Internal(type, duid, iaid, subnet_id, collection);
    }

    return (collection);
}

void
Memfile_LeaseMgr::getLeases6Internal(SubnetID subnet_id,
                                     Lease6Collection& collection) const {
    const Lease6StorageSubnetIdIndex& idx = storage6_.get<SubnetIdIndexTag>();
    std::pair<Lease6StorageSubnetIdIndex::const_iterator,
              Lease6StorageSubnetIdIndex::const_iterator> l =
        idx.equal_range(subnet_id);

    BOOST_FOREACH(auto const& lease, l) {
        collection.push_back(Lease6Ptr(new Lease6(*lease)));
    }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6(SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET_SUBID6)
        .arg(subnet_id);

    Lease6Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases6Internal(subnet_id, collection);
    } else {
        getLeases6Internal(subnet_id, collection);
    }

    return (collection);
}

void
Memfile_LeaseMgr::getLeases6Internal(const std::string& hostname,
                                     Lease6Collection& collection) const {
    const Lease6StorageHostnameIndex& idx = storage6_.get<HostnameIndexTag>();
    std::pair<Lease6StorageHostnameIndex::const_iterator,
              Lease6StorageHostnameIndex::const_iterator> l =
        idx.equal_range(hostname);

    BOOST_FOREACH(auto const& lease, l) {
        collection.push_back(Lease6Ptr(new Lease6(*lease)));
    }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6(const std::string& hostname) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET_HOSTNAME6)
        .arg(hostname);

    Lease6Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases6Internal(hostname, collection);
    } else {
        getLeases6Internal(hostname, collection);
    }

    return (collection);
}

void
Memfile_LeaseMgr::getLeases6Internal(Lease6Collection& collection) const {
   for (auto const& lease : storage6_) {
       collection.push_back(Lease6Ptr(new Lease6(*lease)));
   }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6() const {
   LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET6);

   Lease6Collection collection;
   if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases6Internal(collection);
   } else {
        getLeases6Internal(collection);
   }

   return (collection);
}

void
Memfile_LeaseMgr::getLeases6Internal(const DUID& duid,
                                     Lease6Collection& collection) const {
    const Lease6StorageDuidIndex& idx = storage6_.get<DuidIndexTag>();
    std::pair<Lease6StorageDuidIndex::const_iterator,
              Lease6StorageDuidIndex::const_iterator> l =
        idx.equal_range(duid.getDuid());

    BOOST_FOREACH(auto const& lease, l) {
        collection.push_back(Lease6Ptr(new Lease6(*lease)));
    }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6(const DUID& duid) const {
   LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET6_DUID)
       .arg(duid.toText());

    Lease6Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases6Internal(duid, collection);
    } else {
        getLeases6Internal(duid, collection);
    }

    return (collection);
}

void
Memfile_LeaseMgr::getLeases6Internal(const asiolink::IOAddress& lower_bound_address,
                                     const LeasePageSize& page_size,
                                     Lease6Collection& collection) const {
    const Lease6StorageAddressIndex& idx = storage6_.get<AddressIndexTag>();
    Lease6StorageAddressIndex::const_iterator lb = idx.lower_bound(lower_bound_address);

    // Exclude the lower bound address specified by the caller.
    if ((lb != idx.end()) && ((*lb)->addr_ == lower_bound_address)) {
        ++lb;
    }

    // Return all other leases being within the page size.
    for (auto lease = lb;
         (lease != idx.end()) &&
         (static_cast<size_t>(std::distance(lb, lease)) < page_size.page_size_);
         ++lease) {
        collection.push_back(Lease6Ptr(new Lease6(**lease)));
    }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6(const asiolink::IOAddress& lower_bound_address,
                             const LeasePageSize& page_size) const {
    // Expecting IPv6 address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET_PAGE6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText());

    Lease6Collection collection;
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getLeases6Internal(lower_bound_address, page_size, collection);
    } else {
        getLeases6Internal(lower_bound_address, page_size, collection);
    }

    return (collection);
}

Lease6Collection
Memfile_LeaseMgr::getLeases6Internal(SubnetID subnet_id,
                                     const IOAddress& lower_bound_address,
                                     const LeasePageSize& page_size) const {
    Lease6Collection collection;
    const Lease6StorageSubnetIdIndex& idx = storage6_.get<SubnetIdIndexTag>();
    Lease6StorageSubnetIdIndex::const_iterator lb =
        idx.lower_bound(boost::make_tuple(subnet_id, lower_bound_address));

    // Exclude the lower bound address specified by the caller.
    if ((lb != idx.end()) && ((*lb)->addr_ == lower_bound_address)) {
        ++lb;
    }

    // Return all leases being within the page size.
    for (auto it = lb; it != idx.end(); ++it) {
        if ((*it)->subnet_id_ != subnet_id) {
            // Gone after the subnet id index.
            break;
        }
        collection.push_back(Lease6Ptr(new Lease6(**it)));
        if (collection.size() >= page_size.page_size_) {
            break;
        }
    }
    return (collection);
}

Lease6Collection
Memfile_LeaseMgr::getLeases6(SubnetID subnet_id,
                             const IOAddress& lower_bound_address,
                             const LeasePageSize& page_size) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_SUBID_PAGE6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(subnet_id);

    // Expecting IPv6 valid address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLeases6Internal(subnet_id,
                                   lower_bound_address,
                                   page_size));
    } else {
        return (getLeases6Internal(subnet_id,
                                   lower_bound_address,
                                    page_size));
    }
}

void
Memfile_LeaseMgr::getExpiredLeases4Internal(Lease4Collection& expired_leases,
                                            const size_t max_leases) const {
    // Obtain the index which segragates leases by state and time.
    const Lease4StorageExpirationIndex& index = storage4_.get<ExpirationIndexTag>();

    // Retrieve leases which are not reclaimed and which haven't expired. The
    // 'less-than' operator will be used for both components of the index. So,
    // for the 'state' 'false' is less than 'true'. Also the leases with
    // expiration time lower than current time will be returned.
    Lease4StorageExpirationIndex::const_iterator ub =
        index.upper_bound(boost::make_tuple(false, time(0)));

    // Copy only the number of leases indicated by the max_leases parameter.
    for (Lease4StorageExpirationIndex::const_iterator lease = index.begin();
         (lease != ub) &&
         ((max_leases == 0) ||
          (static_cast<size_t>(std::distance(index.begin(), lease)) < max_leases));
         ++lease) {
        expired_leases.push_back(Lease4Ptr(new Lease4(**lease)));
    }
}

void
Memfile_LeaseMgr::getExpiredLeases4(Lease4Collection& expired_leases,
                                    const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET_EXPIRED4)
        .arg(max_leases);

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getExpiredLeases4Internal(expired_leases, max_leases);
    } else {
        getExpiredLeases4Internal(expired_leases, max_leases);
    }
}

void
Memfile_LeaseMgr::getExpiredLeases6Internal(Lease6Collection& expired_leases,
                                            const size_t max_leases) const {
    // Obtain the index which segragates leases by state and time.
    const Lease6StorageExpirationIndex& index = storage6_.get<ExpirationIndexTag>();

    // Retrieve leases which are not reclaimed and which haven't expired. The
    // 'less-than' operator will be used for both components of the index. So,
    // for the 'state' 'false' is less than 'true'. Also the leases with
    // expiration time lower than current time will be returned.
    Lease6StorageExpirationIndex::const_iterator ub =
        index.upper_bound(boost::make_tuple(false, time(0)));

    // Copy only the number of leases indicated by the max_leases parameter.
    for (Lease6StorageExpirationIndex::const_iterator lease = index.begin();
         (lease != ub) &&
         ((max_leases == 0) ||
          (static_cast<size_t>(std::distance(index.begin(), lease)) < max_leases));
         ++lease) {
        expired_leases.push_back(Lease6Ptr(new Lease6(**lease)));
    }
}

void
Memfile_LeaseMgr::getExpiredLeases6(Lease6Collection& expired_leases,
                                    const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_GET_EXPIRED6)
        .arg(max_leases);

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        getExpiredLeases6Internal(expired_leases, max_leases);
    } else {
        getExpiredLeases6Internal(expired_leases, max_leases);
    }
}

void
Memfile_LeaseMgr::updateLease4Internal(const Lease4Ptr& lease) {
    // Obtain 'by address' index.
    Lease4StorageAddressIndex& index = storage4_.get<AddressIndexTag>();

    bool persist = persistLeases(V4);

    // Lease must exist if it is to be updated.
    Lease4StorageAddressIndex::const_iterator lease_it = index.find(lease->addr_);
    if (lease_it == index.end()) {
        isc_throw(NoSuchLease, "failed to update the lease with address "
                  << lease->addr_ << " - no such lease");
    } else if ((!persist) && (((*lease_it)->cltt_ != lease->current_cltt_) ||
        ((*lease_it)->valid_lft_ != lease->current_valid_lft_))) {
        // For test purpose only: check that the lease has not changed in
        // the database.
        isc_throw(NoSuchLease, "unable to update lease for address " <<
                  lease->addr_.toText() << " either because the lease does not exist, "
                      "it has been deleted or it has changed in the database.");
    }

    // Try to write a lease to disk first. If this fails, the lease will
    // not be inserted to the memory and the disk and in-memory data will
    // remain consistent.
    if (persist) {
        lease_file4_->append(*lease);
    }

    // Update lease current expiration time.
    lease->updateCurrentExpirationTime();

    // Save a copy of the old lease as lease_it will point to the new
    // one after the replacement.
    Lease4Ptr old_lease = *lease_it;

    // Use replace() to re-index leases.
    index.replace(lease_it, Lease4Ptr(new Lease4(*lease)));

    // Adjust class lease counters.
    class_lease_counter_.updateLease(lease, old_lease);

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackUpdateLease(lease);
    }
}

void
Memfile_LeaseMgr::updateLease4(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_UPDATE_ADDR4).arg(lease->addr_.toText());

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        updateLease4Internal(lease);
    } else {
        updateLease4Internal(lease);
    }
}

void
Memfile_LeaseMgr::updateLease6Internal(const Lease6Ptr& lease) {
    // Obtain 'by address' index.
    Lease6StorageAddressIndex& index = storage6_.get<AddressIndexTag>();

    bool persist = persistLeases(V6);

    // Get the recorded action and reset it.
    Lease6::ExtendedInfoAction recorded_action = lease->extended_info_action_;
    lease->extended_info_action_ = Lease6::ACTION_IGNORE;

    // Lease must exist if it is to be updated.
    Lease6StorageAddressIndex::const_iterator lease_it = index.find(lease->addr_);
    if (lease_it == index.end()) {
        isc_throw(NoSuchLease, "failed to update the lease with address "
                  << lease->addr_ << " - no such lease");
    } else if ((!persist) && (((*lease_it)->cltt_ != lease->current_cltt_) ||
        ((*lease_it)->valid_lft_ != lease->current_valid_lft_))) {
        // For test purpose only: check that the lease has not changed in
        // the database.
        isc_throw(NoSuchLease, "unable to update lease for address " <<
                  lease->addr_.toText() << " either because the lease does not exist, "
                      "it has been deleted or it has changed in the database.");
    }

    // Try to write a lease to disk first. If this fails, the lease will
    // not be inserted to the memory and the disk and in-memory data will
    // remain consistent.
    if (persist) {
        lease_file6_->append(*lease);
    }

    // Update lease current expiration time.
    lease->updateCurrentExpirationTime();

    // Save a copy of the old lease as lease_it will point to the new
    // one after the replacement.
    Lease6Ptr old_lease = *lease_it;

    // Use replace() to re-index leases.
    index.replace(lease_it, Lease6Ptr(new Lease6(*lease)));

    // Adjust class lease counters.
    class_lease_counter_.updateLease(lease, old_lease);

    // Update extended info tables.
    if (getExtendedInfoTablesEnabled()) {
        switch (recorded_action) {
        case Lease6::ACTION_IGNORE:
            break;

        case Lease6::ACTION_DELETE:
            deleteExtendedInfo6(lease->addr_);
            break;

        case Lease6::ACTION_UPDATE:
            deleteExtendedInfo6(lease->addr_);
            static_cast<void>(addExtendedInfo6(lease));
            break;
        }
    }

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackUpdateLease(lease);
    }
}

void
Memfile_LeaseMgr::updateLease6(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_UPDATE_ADDR6).arg(lease->addr_.toText());

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        updateLease6Internal(lease);
    } else {
        updateLease6Internal(lease);
    }
}

bool
Memfile_LeaseMgr::deleteLeaseInternal(const Lease4Ptr& lease) {
    const isc::asiolink::IOAddress& addr = lease->addr_;
    Lease4Storage::iterator l = storage4_.find(addr);
    if (l == storage4_.end()) {
        // No such lease
        return (false);
    } else {
        if (persistLeases(V4)) {
            // Copy the lease. The valid lifetime needs to be modified and
            // we don't modify the original lease.
            Lease4 lease_copy = **l;
            // Setting valid lifetime to 0 means that lease is being
            // removed.
            lease_copy.valid_lft_ = 0;
            lease_file4_->append(lease_copy);
        } else {
            // For test purpose only: check that the lease has not changed in
            // the database.
            if (((*l)->cltt_ != lease->current_cltt_) ||
                ((*l)->valid_lft_ != lease->current_valid_lft_)) {
                return false;
            }
        }

        storage4_.erase(l);

        // Decrement class lease counters.
        class_lease_counter_.removeLease(lease);

        // Run installed callbacks.
        if (hasCallbacks()) {
            trackDeleteLease(lease);
        }

        return (true);
    }
}

bool
Memfile_LeaseMgr::deleteLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_DELETE_ADDR4).arg(lease->addr_.toText());

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (deleteLeaseInternal(lease));
    } else {
        return (deleteLeaseInternal(lease));
    }
}

bool
Memfile_LeaseMgr::deleteLeaseInternal(const Lease6Ptr& lease) {
    lease->extended_info_action_ = Lease6::ACTION_IGNORE;

    const isc::asiolink::IOAddress& addr = lease->addr_;
    Lease6Storage::iterator l = storage6_.find(addr);
    if (l == storage6_.end()) {
        // No such lease
        return (false);
    } else {
        if (persistLeases(V6)) {
            // Copy the lease. The lifetimes need to be modified and we
            // don't modify the original lease.
            Lease6 lease_copy = **l;
            // Setting lifetimes to 0 means that lease is being removed.
            lease_copy.valid_lft_ = 0;
            lease_copy.preferred_lft_ = 0;
            lease_file6_->append(lease_copy);
        } else {
            // For test purpose only: check that the lease has not changed in
            // the database.
            if (((*l)->cltt_ != lease->current_cltt_) ||
                ((*l)->valid_lft_ != lease->current_valid_lft_)) {
                return false;
            }
        }

        storage6_.erase(l);

        // Decrement class lease counters.
        class_lease_counter_.removeLease(lease);

        // Delete references from extended info tables.
        if (getExtendedInfoTablesEnabled()) {
            deleteExtendedInfo6(lease->addr_);
        }

        // Run installed callbacks.
        if (hasCallbacks()) {
            trackDeleteLease(lease);
        }

        return (true);
    }
}

bool
Memfile_LeaseMgr::deleteLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_DELETE_ADDR6).arg(lease->addr_.toText());

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (deleteLeaseInternal(lease));
    } else {
        return (deleteLeaseInternal(lease));
    }
}

uint64_t
Memfile_LeaseMgr::deleteExpiredReclaimedLeases4(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED4)
        .arg(secs);

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (deleteExpiredReclaimedLeases<
                Lease4StorageExpirationIndex, Lease4
                >(secs, V4, storage4_, lease_file4_));
    } else {
        return (deleteExpiredReclaimedLeases<
                Lease4StorageExpirationIndex, Lease4
                >(secs, V4, storage4_, lease_file4_));
    }
}

uint64_t
Memfile_LeaseMgr::deleteExpiredReclaimedLeases6(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED6)
        .arg(secs);

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (deleteExpiredReclaimedLeases<
                Lease6StorageExpirationIndex, Lease6
                >(secs, V6, storage6_, lease_file6_));
    } else {
        return (deleteExpiredReclaimedLeases<
                Lease6StorageExpirationIndex, Lease6
                >(secs, V6, storage6_, lease_file6_));
    }
}

template<typename IndexType, typename LeaseType, typename StorageType,
         typename LeaseFileType>
uint64_t
Memfile_LeaseMgr::deleteExpiredReclaimedLeases(const uint32_t secs,
                                               const Universe& universe,
                                               StorageType& storage,
                                               LeaseFileType& lease_file) {
    // Obtain the index which segragates leases by state and time.
    IndexType& index = storage.template get<ExpirationIndexTag>();

    // This returns the first element which is greater than the specified
    // tuple (true, time(0) - secs). However, the range between the
    // beginning of the index and returned element also includes all the
    // elements for which the first value is false (lease state is NOT
    // reclaimed), because false < true. All elements between the
    // beginning of the index and the element returned, for which the
    // first value is true, represent the reclaimed leases which should
    // be deleted, because their expiration time + secs has occurred earlier
    // than current time.
    typename IndexType::const_iterator upper_limit =
        index.upper_bound(boost::make_tuple(true, time(0) - secs));

    // Now, we have to exclude all elements of the index which represent
    // leases in the state other than reclaimed - with the first value
    // in the index equal to false. Note that elements in the index are
    // ordered from the lower to the higher ones. So, all elements with
    // the first value of false are placed before the elements with the
    // value of true. Hence, we have to find the first element which
    // contains value of true. The time value is the lowest possible.
    typename IndexType::const_iterator lower_limit =
        index.upper_bound(boost::make_tuple(true, std::numeric_limits<int64_t>::min()));

    // If there are some elements in this range, delete them.
    uint64_t num_leases = static_cast<uint64_t>(std::distance(lower_limit, upper_limit));
    if (num_leases > 0) {

        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED_START)
            .arg(num_leases);

        // If lease persistence is enabled, we also have to mark leases
        // as deleted in the lease file. We do this by setting the
        // lifetime to 0.
        if (persistLeases(universe)) {
            for (typename IndexType::const_iterator lease = lower_limit;
                 lease != upper_limit; ++lease) {
                // Copy lease to not affect the lease in the container.
                LeaseType lease_copy(**lease);
                // Set the valid lifetime to 0 to indicate the removal
                // of the lease.
                lease_copy.valid_lft_ = 0;
                lease_file->append(lease_copy);
            }
        }

        // Erase leases from memory.
        index.erase(lower_limit, upper_limit);

    }
    // Return number of leases deleted.
    return (num_leases);
}

std::string
Memfile_LeaseMgr::getDescription() const {
    return (std::string("In memory database with leases stored in a CSV file."));
}

std::pair<uint32_t, uint32_t>
Memfile_LeaseMgr::getVersion(const std::string& /* timer_name */) const {
    std::string const& universe(conn_.getParameter("universe"));
    if (universe == "4") {
        return std::make_pair(MAJOR_VERSION_V4, MINOR_VERSION_V4);
    } else if (universe == "6") {
        return std::make_pair(MAJOR_VERSION_V6, MINOR_VERSION_V6);
    }
    isc_throw(BadValue, "cannot determine version for universe " << universe);
}

void
Memfile_LeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MEMFILE_COMMIT);
}

void
Memfile_LeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_ROLLBACK);
}

std::string
Memfile_LeaseMgr::appendSuffix(const std::string& file_name,
                               const LFCFileType& file_type) {
    std::string name(file_name);
    switch (file_type) {
    case FILE_INPUT:
        name += ".1";
        break;
    case FILE_PREVIOUS:
        name += ".2";
        break;
    case FILE_OUTPUT:
        name += ".output";
        break;
    case FILE_FINISH:
        name += ".completed";
        break;
    case FILE_PID:
        name += ".pid";
        break;
    default:
        // Do not append any suffix for the FILE_CURRENT.
        ;
    }

    return (name);
}

std::string
Memfile_LeaseMgr::getDefaultLeaseFilePath(Universe u) const {
    std::ostringstream s;
    s << CfgMgr::instance().getDataDir() << "/kea-leases";
    s << (u == V4 ? "4" : "6");
    s << ".csv";
    return (s.str());
}

std::string
Memfile_LeaseMgr::getLeaseFilePath(Universe u) const {
    if (u == V4) {
        return (lease_file4_ ? lease_file4_->getFilename() : "");
    }

    return (lease_file6_ ? lease_file6_->getFilename() : "");
}

bool
Memfile_LeaseMgr::persistLeases(Universe u) const {
    // Currently, if the lease file IO is not created, it means that writes to
    // disk have been explicitly disabled by the administrator. At some point,
    // there may be a dedicated ON/OFF flag implemented to control this.
    if (u == V4 && lease_file4_) {
        return (true);
    }

    return (u == V6 && lease_file6_);
}

std::string
Memfile_LeaseMgr::initLeaseFilePath(Universe u) {
    std::string persist_val;
    try {
        persist_val = conn_.getParameter("persist");
    } catch (const Exception&) {
        // If parameter persist hasn't been specified, we use a default value
        // 'yes'.
        persist_val = "true";
    }
    // If persist_val is 'false' we will not store leases to disk, so let's
    // return empty file name.
    if (persist_val == "false") {
        return ("");

    } else if (persist_val != "true") {
        isc_throw(isc::BadValue, "invalid value 'persist="
                  << persist_val << "'");
    }

    std::string lease_file;
    try {
        lease_file = conn_.getParameter("name");
    } catch (const Exception&) {
        lease_file = getDefaultLeaseFilePath(u);
    }
    return (lease_file);
}

template<typename LeaseObjectType, typename LeaseFileType, typename StorageType>
bool
Memfile_LeaseMgr::loadLeasesFromFiles(const std::string& filename,
                                      boost::shared_ptr<LeaseFileType>& lease_file,
                                      StorageType& storage) {
    // Check if the instance of the LFC is running right now. If it is
    // running, we refuse to load leases as the LFC may be writing to the
    // lease files right now. When the user retries server configuration
    // it should go through.
    /// @todo Consider applying a timeout for an LFC and retry when this
    /// timeout elapses.
    PIDFile pid_file(appendSuffix(filename, FILE_PID));
    if (pid_file.check()) {
        isc_throw(DbOpenError, "unable to load leases from files while the "
                  "lease file cleanup is in progress");
    }

    storage.clear();

    std::string max_row_errors_str = "0";
    try {
        max_row_errors_str = conn_.getParameter("max-row-errors");
    } catch (const std::exception&) {
        // Ignore and default to 0.
    }

    int64_t max_row_errors64;
    try {
        max_row_errors64 = boost::lexical_cast<int64_t>(max_row_errors_str);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(isc::BadValue, "invalid value of the max-row-errors "
                  << max_row_errors_str << " specified");
    }
    if ((max_row_errors64 < 0) ||
        (max_row_errors64 > std::numeric_limits<uint32_t>::max())) {
        isc_throw(isc::BadValue, "invalid value of the max-row-errors "
                  << max_row_errors_str << " specified");
    }
    uint32_t max_row_errors = static_cast<uint32_t>(max_row_errors64);

    // Load the leasefile.completed, if exists.
    bool conversion_needed = false;
    lease_file.reset(new LeaseFileType(std::string(filename + ".completed")));
    if (lease_file->exists()) {
        LeaseFileLoader::load<LeaseObjectType>(*lease_file, storage,
                                               max_row_errors);
        conversion_needed = conversion_needed || lease_file->needsConversion();
    } else {
        // If the leasefile.completed doesn't exist, let's load the leases
        // from leasefile.2 and leasefile.1, if they exist.
        lease_file.reset(new LeaseFileType(appendSuffix(filename, FILE_PREVIOUS)));
        if (lease_file->exists()) {
            LeaseFileLoader::load<LeaseObjectType>(*lease_file, storage,
                                                   max_row_errors);
            conversion_needed = conversion_needed || lease_file->needsConversion();
        }

        lease_file.reset(new LeaseFileType(appendSuffix(filename, FILE_INPUT)));
        if (lease_file->exists()) {
            LeaseFileLoader::load<LeaseObjectType>(*lease_file, storage,
                                                   max_row_errors);
            conversion_needed = conversion_needed || lease_file->needsConversion();
        }
    }

    // Always load leases from the primary lease file. If the lease file
    // doesn't exist it will be created by the LeaseFileLoader. Note
    // that the false value passed as the last parameter to load
    // function causes the function to leave the file open after
    // it is parsed. This file will be used by the backend to record
    // future lease updates.
    lease_file.reset(new LeaseFileType(filename));
    LeaseFileLoader::load<LeaseObjectType>(*lease_file, storage,
                                           max_row_errors, false);
    conversion_needed = conversion_needed || lease_file->needsConversion();

    return (conversion_needed);
}


bool
Memfile_LeaseMgr::isLFCRunning() const {
    return (lfc_setup_->isRunning());
}

int
Memfile_LeaseMgr::getLFCExitStatus() const {
    return (lfc_setup_->getExitStatus());
}

void
Memfile_LeaseMgr::lfcCallback() {
    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_START);

    // Check if we're in the v4 or v6 space and use the appropriate file.
    if (lease_file4_) {
        MultiThreadingCriticalSection cs;
        lfcExecute(lease_file4_);
    } else if (lease_file6_) {
        MultiThreadingCriticalSection cs;
        lfcExecute(lease_file6_);
    }
}

void
Memfile_LeaseMgr::lfcSetup(bool conversion_needed) {
    std::string lfc_interval_str = "3600";
    try {
        lfc_interval_str = conn_.getParameter("lfc-interval");
    } catch (const std::exception&) {
        // Ignore and default to 3600.
    }

    uint32_t lfc_interval = 0;
    try {
        lfc_interval = boost::lexical_cast<uint32_t>(lfc_interval_str);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(isc::BadValue, "invalid value of the lfc-interval "
                  << lfc_interval_str << " specified");
    }

    if (lfc_interval > 0 || conversion_needed) {
        lfc_setup_.reset(new LFCSetup(std::bind(&Memfile_LeaseMgr::lfcCallback, this)));
        lfc_setup_->setup(lfc_interval, lease_file4_, lease_file6_, conversion_needed);
    }
}

template<typename LeaseFileType>
void
Memfile_LeaseMgr::lfcExecute(boost::shared_ptr<LeaseFileType>& lease_file) {
    bool do_lfc = true;

    // Check the status of the LFC instance.
    // If the finish file exists or the copy of the lease file exists it
    // is an indication that another LFC instance may be in progress or
    // may be stalled. In that case we don't want to rotate the current
    // lease file to avoid overriding the contents of the existing file.
    CSVFile lease_file_finish(appendSuffix(lease_file->getFilename(), FILE_FINISH));
    CSVFile lease_file_copy(appendSuffix(lease_file->getFilename(), FILE_INPUT));
    if (!lease_file_finish.exists() && !lease_file_copy.exists()) {
        // Close the current file so as we can move it to the copy file.
        lease_file->close();
        // Move the current file to the copy file. Remember the result
        // because we don't want to run LFC if the rename failed.
        do_lfc = (rename(lease_file->getFilename().c_str(),
                         lease_file_copy.getFilename().c_str()) == 0);

        if (!do_lfc) {
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_LEASE_FILE_RENAME_FAIL)
                .arg(lease_file->getFilename())
                .arg(lease_file_copy.getFilename())
                .arg(strerror(errno));
        }

        // Regardless if we successfully moved the current file or not,
        // we need to re-open the current file for the server to write
        // new lease updates. If the file has been successfully moved,
        // this will result in creation of the new file. Otherwise,
        // an existing file will be opened.
        try {
            lease_file->open(true);

        } catch (const CSVFileError& ex) {
            // If we're unable to open the lease file this is a serious
            // error because the server will not be able to persist
            // leases.
            /// @todo We need to better address this error. It should
            /// trigger an alarm (once we have a monitoring system in
            /// place) so as an administrator can correct it. In
            /// practice it should be very rare that this happens and
            /// is most likely related to a human error, e.g. changing
            /// file permissions.
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_MEMFILE_LFC_LEASE_FILE_REOPEN_FAIL)
                .arg(lease_file->getFilename())
                .arg(ex.what());
            // Reset the pointer to the file so as the backend doesn't
            // try to write leases to disk.
            lease_file.reset();
            do_lfc = false;
        }
    }
    // Once the files have been rotated, or untouched if another LFC had
    // not finished, a new process is started.
    if (do_lfc) {
        lfc_setup_->execute();
    }
}

LeaseStatsQueryPtr
Memfile_LeaseMgr::startLeaseStatsQuery4() {
    LeaseStatsQueryPtr query(new MemfileLeaseStatsQuery4(storage4_));
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        query->start();
    } else {
        query->start();
    }

    return(query);
}

LeaseStatsQueryPtr
Memfile_LeaseMgr::startPoolLeaseStatsQuery4() {
    LeaseStatsQueryPtr query(new MemfileLeaseStatsQuery4(storage4_, LeaseStatsQuery::ALL_SUBNET_POOLS));
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        query->start();
    } else {
        query->start();
    }

    return(query);
}

LeaseStatsQueryPtr
Memfile_LeaseMgr::startSubnetLeaseStatsQuery4(const SubnetID& subnet_id) {
    LeaseStatsQueryPtr query(new MemfileLeaseStatsQuery4(storage4_, subnet_id));
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        query->start();
    } else {
        query->start();
    }

    return(query);
}

LeaseStatsQueryPtr
Memfile_LeaseMgr::startSubnetRangeLeaseStatsQuery4(const SubnetID& first_subnet_id,
                                                   const SubnetID& last_subnet_id) {
    LeaseStatsQueryPtr query(new MemfileLeaseStatsQuery4(storage4_, first_subnet_id,
                                                         last_subnet_id));
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        query->start();
    } else {
        query->start();
    }

    return(query);
}

LeaseStatsQueryPtr
Memfile_LeaseMgr::startLeaseStatsQuery6() {
    LeaseStatsQueryPtr query(new MemfileLeaseStatsQuery6(storage6_));
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        query->start();
    } else {
        query->start();
    }

    return(query);
}

LeaseStatsQueryPtr
Memfile_LeaseMgr::startPoolLeaseStatsQuery6() {
    LeaseStatsQueryPtr query(new MemfileLeaseStatsQuery6(storage6_, LeaseStatsQuery::ALL_SUBNET_POOLS));
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        query->start();
    } else {
        query->start();
    }

    return(query);
}

LeaseStatsQueryPtr
Memfile_LeaseMgr::startSubnetLeaseStatsQuery6(const SubnetID& subnet_id) {
    LeaseStatsQueryPtr query(new MemfileLeaseStatsQuery6(storage6_, subnet_id));
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        query->start();
    } else {
        query->start();
    }

    return(query);
}

LeaseStatsQueryPtr
Memfile_LeaseMgr::startSubnetRangeLeaseStatsQuery6(const SubnetID& first_subnet_id,
                                                   const SubnetID& last_subnet_id) {
    LeaseStatsQueryPtr query(new MemfileLeaseStatsQuery6(storage6_, first_subnet_id,
                                                         last_subnet_id));
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        query->start();
    } else {
        query->start();
    }

    return(query);
}

size_t
Memfile_LeaseMgr::wipeLeases4(const SubnetID& subnet_id) {
    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_WIPE_LEASES4)
        .arg(subnet_id);

    // Get the index by DUID, IAID, lease type.
    const Lease4StorageSubnetIdIndex& idx = storage4_.get<SubnetIdIndexTag>();

    // Try to get the lease using the DUID, IAID and lease type.
    std::pair<Lease4StorageSubnetIdIndex::const_iterator,
              Lease4StorageSubnetIdIndex::const_iterator> r =
        idx.equal_range(subnet_id);

    // Let's collect all leases.
    Lease4Collection leases;
    BOOST_FOREACH(auto const& lease, r) {
        leases.push_back(lease);
    }

    size_t num = leases.size();
    for (auto const& l : leases) {
        deleteLease(l);
    }
    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_WIPE_LEASES4_FINISHED)
        .arg(subnet_id).arg(num);

    return (num);
}

size_t
Memfile_LeaseMgr::wipeLeases6(const SubnetID& subnet_id) {
    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_WIPE_LEASES6)
        .arg(subnet_id);

    // Get the index by DUID, IAID, lease type.
    const Lease6StorageSubnetIdIndex& idx = storage6_.get<SubnetIdIndexTag>();

    // Try to get the lease using the DUID, IAID and lease type.
    std::pair<Lease6StorageSubnetIdIndex::const_iterator,
              Lease6StorageSubnetIdIndex::const_iterator> r =
        idx.equal_range(subnet_id);

    // Let's collect all leases.
    Lease6Collection leases;
    BOOST_FOREACH(auto const& lease, r) {
        leases.push_back(lease);
    }

    size_t num = leases.size();
    for (auto const& l : leases) {
        deleteLease(l);
    }
    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_WIPE_LEASES6_FINISHED)
        .arg(subnet_id).arg(num);

    return (num);
}

void
Memfile_LeaseMgr::recountClassLeases4() {
    class_lease_counter_.clear();
    for (auto const& lease : storage4_) {
        // Bump the appropriate accumulator
        if (lease->state_ == Lease::STATE_DEFAULT) {
            class_lease_counter_.addLease(lease);
        }
    }
}

void
Memfile_LeaseMgr::recountClassLeases6() {
    class_lease_counter_.clear();
    for (auto const& lease : storage6_) {
        // Bump the appropriate accumulator
        if (lease->state_ == Lease::STATE_DEFAULT) {
            class_lease_counter_.addLease(lease);
        }
    }
}

size_t
Memfile_LeaseMgr::getClassLeaseCount(const ClientClass& client_class,
                                     const Lease::Type& ltype /* = Lease::TYPE_V4*/) const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return(class_lease_counter_.getClassCount(client_class, ltype));
    } else {
        return(class_lease_counter_.getClassCount(client_class, ltype));
    }
}

void
Memfile_LeaseMgr::clearClassLeaseCounts() {
    return(class_lease_counter_.clear());
}

std::string
Memfile_LeaseMgr::checkLimits4(isc::data::ConstElementPtr const& user_context) const {
    if (!user_context) {
        return ("");
    }

    ConstElementPtr limits = user_context->find("ISC/limits");
    if (!limits) {
        return ("");
    }

    // Iterate of the 'client-classes' list in 'limits'. For each class that specifies
    // an "address-limit", check its value against the class's lease count.
    ConstElementPtr classes = limits->get("client-classes");
    if (classes) {
        for (unsigned i = 0; i < classes->size(); ++i) {
            ConstElementPtr class_elem = classes->get(i);
            // Get class name.
            ConstElementPtr name_elem = class_elem->get("name");
            if (!name_elem) {
                isc_throw(BadValue, "checkLimits4 - client-class.name is missing: "
                          << prettyPrint(limits));
            }

            std::string name = name_elem->stringValue();

            // Now look for an address-limit
            size_t limit;
            if (!getLeaseLimit(class_elem, Lease::TYPE_V4, limit)) {
                // No limit, go to the next class.
                continue;
            }

            // If the limit is > 0 look up the class lease count.  Limit of 0 always
            // denies the lease.
            size_t lease_count = 0;
            if (limit) {
                lease_count = getClassLeaseCount(name);
            }

            // If we're over the limit, return the error, no need to evaluate any others.
            if (lease_count >= limit) {
                std::ostringstream ss;
                ss << "address limit " << limit << " for client class \""
                   << name << "\", current lease count " << lease_count;
                return (ss.str());
            }
        }
    }

    // If there were class limits we passed them, now look for a subnet limit.
    ConstElementPtr subnet_elem = limits->get("subnet");
    if (subnet_elem) {
        // Get the subnet id.
        ConstElementPtr id_elem = subnet_elem->get("id");
        if (!id_elem) {
            isc_throw(BadValue, "checkLimits4 - subnet.id is missing: "
                      << prettyPrint(limits));
        }

        SubnetID subnet_id = id_elem->intValue();

        // Now look for an address-limit.
        size_t limit;
        if (getLeaseLimit(subnet_elem, Lease::TYPE_V4, limit)) {
            // If the limit is > 0 look up the subnet lease count. Limit of 0 always
            // denies the lease.
            int64_t lease_count = 0;
            if (limit) {
                lease_count = getSubnetStat(subnet_id, "assigned-addresses");
            }

            // If we're over the limit, return the error.
            if (static_cast<uint64_t>(lease_count) >= limit) {
                std::ostringstream ss;
                ss << "address limit " << limit << " for subnet ID " << subnet_id
                   << ", current lease count " << lease_count;
                return (ss.str());
            }
        }
    }

    // No limits exceeded!
    return ("");
}

std::string
Memfile_LeaseMgr::checkLimits6(isc::data::ConstElementPtr const& user_context) const {
    if (!user_context) {
        return ("");
    }

    ConstElementPtr limits = user_context->find("ISC/limits");
    if (!limits) {
        return ("");
    }

    // Iterate over the 'client-classes' list in 'limits'. For each class that specifies
    // limit (either "address-limit" or "prefix-limit", check its value against the appropriate
    // class lease count.
    ConstElementPtr classes = limits->get("client-classes");
    if (classes) {
        for (unsigned i = 0; i < classes->size(); ++i) {
            ConstElementPtr class_elem = classes->get(i);
            // Get class name.
            ConstElementPtr name_elem = class_elem->get("name");
            if (!name_elem) {
                isc_throw(BadValue, "checkLimits6 - client-class.name is missing: "
                          << prettyPrint(limits));
            }

            std::string name = name_elem->stringValue();

            // Now look for either address-limit or a prefix=limit.
            size_t limit = 0;
            Lease::Type ltype = Lease::TYPE_NA;
            if (!getLeaseLimit(class_elem, ltype, limit)) {
                ltype = Lease::TYPE_PD;
                if (!getLeaseLimit(class_elem, ltype, limit)) {
                    // No limits for this class, skip to the next.
                    continue;
                }
            }

            // If the limit is > 0 look up the class lease count.  Limit of 0 always
            // denies the lease.
            size_t lease_count = 0;
            if (limit) {
                lease_count = getClassLeaseCount(name, ltype);
            }

            // If we're over the limit, return the error, no need to evaluate any others.
            if (lease_count >= limit) {
                std::ostringstream ss;
                ss << (ltype == Lease::TYPE_NA ? "address" : "prefix")
                   << " limit " << limit << " for client class \""
                   << name << "\", current lease count " << lease_count;
                return (ss.str());
            }
        }
    }

    // If there were class limits we passed them, now look for a subnet limit.
    ConstElementPtr subnet_elem = limits->get("subnet");
    if (subnet_elem) {
        // Get the subnet id.
        ConstElementPtr id_elem = subnet_elem->get("id");
        if (!id_elem) {
            isc_throw(BadValue, "checkLimits6 - subnet.id is missing: "
                      << prettyPrint(limits));
        }

        SubnetID subnet_id = id_elem->intValue();

        // Now look for either address-limit or a prefix=limit.
        size_t limit = 0;
        Lease::Type ltype = Lease::TYPE_NA;
        if (!getLeaseLimit(subnet_elem, ltype, limit)) {
            ltype = Lease::TYPE_PD;
            if (!getLeaseLimit(subnet_elem, ltype, limit)) {
                // No limits for the subnet so none exceeded!
                return ("");
            }
        }

        // If the limit is > 0 look up the class lease count.  Limit of 0 always
        // denies the lease.
        int64_t lease_count = 0;
        if (limit) {
            lease_count = getSubnetStat(subnet_id, (ltype == Lease::TYPE_NA ?
                                                    "assigned-nas" : "assigned-pds"));
        }

        // If we're over the limit, return the error.
        if (static_cast<uint64_t>(lease_count) >= limit) {
            std::ostringstream ss;
            ss << (ltype == Lease::TYPE_NA ? "address" : "prefix")
               << " limit " << limit << " for subnet ID " << subnet_id
               << ", current lease count " << lease_count;
            return (ss.str());
        }
    }

    // No limits exceeded!
    return ("");
}

bool
Memfile_LeaseMgr::isJsonSupported() const {
    return true;
}

int64_t
Memfile_LeaseMgr::getSubnetStat(const SubnetID& subnet_id, const std::string& stat_label) const {
    /// @todo This could be simplified if StatsMgr provided a mechanism to
    /// return the most recent sample as an InterSample.
    std::string stat_name = StatsMgr::generateName("subnet", subnet_id, stat_label);
    ConstElementPtr stat = StatsMgr::instance().get(stat_name);
    ConstElementPtr samples = stat->get(stat_name);
    if (samples && samples->size()) {
        auto sample = samples->get(0);
        if (sample->size()) {
            auto count_elem = sample->get(0);
            return (count_elem->intValue());
        }
    }

    return (0);
}

bool
Memfile_LeaseMgr::getLeaseLimit(ConstElementPtr parent, Lease::Type ltype, size_t& limit) const {
    ConstElementPtr limit_elem = parent->get(ltype == Lease::TYPE_PD ?
                                             "prefix-limit" : "address-limit");
    if (limit_elem) {
        limit = limit_elem->intValue();
        return (true);
    }

    return (false);
}

namespace {

std::string
idToText(const OptionBuffer& id) {
    std::stringstream tmp;
    tmp << std::hex;
    bool delim = false;
    for (auto const& it : id) {
        if (delim) {
            tmp << ":";
        }
        tmp << std::setw(2) << std::setfill('0')
            << static_cast<unsigned int>(it);
        delim = true;
    }
    return (tmp.str());
}

} // anonymous namespace

Lease4Collection
Memfile_LeaseMgr::getLeases4ByRelayId(const OptionBuffer& relay_id,
                                      const IOAddress& lower_bound_address,
                                      const LeasePageSize& page_size,
                                      const time_t& qry_start_time /* = 0 */,
                                      const time_t& qry_end_time /* = 0 */) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_RELAYID4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(idToText(relay_id))
        .arg(qry_start_time)
        .arg(qry_end_time);

    // Expecting IPv4 address.
    if (!lower_bound_address.isV4()) {
        isc_throw(InvalidAddressFamily, "expected IPv4 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    // Catch 2038 bug with 32 bit time_t.
    if ((qry_start_time < 0) || (qry_end_time < 0)) {
        isc_throw(BadValue, "negative time value");
    }

    // Start time must be before end time.
    if ((qry_start_time > 0) && (qry_end_time > 0) &&
        (qry_start_time > qry_end_time)) {
        isc_throw(BadValue, "start time must be before end time");
    }

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLeases4ByRelayIdInternal(relay_id,
                                            lower_bound_address,
                                            page_size,
                                            qry_start_time,
                                            qry_end_time));
    } else {
        return (getLeases4ByRelayIdInternal(relay_id,
                                            lower_bound_address,
                                            page_size,
                                            qry_start_time,
                                            qry_end_time));
    }
}

Lease4Collection
Memfile_LeaseMgr::getLeases4ByRelayIdInternal(const OptionBuffer& relay_id,
                                              const IOAddress& lower_bound_address,
                                              const LeasePageSize& page_size,
                                              const time_t& qry_start_time,
                                              const time_t& qry_end_time) {
    Lease4Collection collection;
    const Lease4StorageRelayIdIndex& idx = storage4_.get<RelayIdIndexTag>();
    Lease4StorageRelayIdIndex::const_iterator lb =
        idx.lower_bound(boost::make_tuple(relay_id, lower_bound_address));
    // Return all convenient leases being within the page size.
    IOAddress last_addr = lower_bound_address;
    for (; lb != idx.end(); ++lb) {
        if ((*lb)->addr_ == last_addr) {
            // Already seen: skip it.
            continue;
        }
        if ((*lb)->relay_id_ != relay_id) {
            // Gone after the relay id index.
            break;
        }
        last_addr = (*lb)->addr_;
        if ((qry_start_time > 0) && ((*lb)->cltt_ < qry_start_time)) {
            // Too old.
            continue;
        }
        if ((qry_end_time > 0) && ((*lb)->cltt_ > qry_end_time)) {
            // Too young.
            continue;
        }
        collection.push_back(Lease4Ptr(new Lease4(**lb)));
        if (collection.size() >= page_size.page_size_) {
            break;
        }
    }
    return (collection);
}

Lease4Collection
Memfile_LeaseMgr::getLeases4ByRemoteId(const OptionBuffer& remote_id,
                                       const IOAddress& lower_bound_address,
                                       const LeasePageSize& page_size,
                                       const time_t& qry_start_time /* = 0 */,
                                       const time_t& qry_end_time /* = 0 */) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_REMOTEID4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(idToText(remote_id))
        .arg(qry_start_time)
        .arg(qry_end_time);

    // Expecting IPv4 address.
    if (!lower_bound_address.isV4()) {
        isc_throw(InvalidAddressFamily, "expected IPv4 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    // Catch 2038 bug with 32 bit time_t.
    if ((qry_start_time < 0) || (qry_end_time < 0)) {
        isc_throw(BadValue, "negative time value");
    }

    // Start time must be before end time.
    if ((qry_start_time > 0) && (qry_end_time > 0) &&
        (qry_start_time > qry_end_time)) {
        isc_throw(BadValue, "start time must be before end time");
    }

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLeases4ByRemoteIdInternal(remote_id,
                                             lower_bound_address,
                                             page_size,
                                             qry_start_time,
                                             qry_end_time));
    } else {
        return (getLeases4ByRemoteIdInternal(remote_id,
                                             lower_bound_address,
                                             page_size,
                                             qry_start_time,
                                             qry_end_time));
    }
}

Lease4Collection
Memfile_LeaseMgr::getLeases4ByRemoteIdInternal(const OptionBuffer& remote_id,
                                               const IOAddress& lower_bound_address,
                                               const LeasePageSize& page_size,
                                               const time_t& qry_start_time,
                                               const time_t& qry_end_time) {
    Lease4Collection collection;
    std::map<IOAddress, Lease4Ptr> sorted;
    const Lease4StorageRemoteIdIndex& idx = storage4_.get<RemoteIdIndexTag>();
    Lease4StorageRemoteIdRange er = idx.equal_range(remote_id);
    // Store all convenient leases being within the page size.
    BOOST_FOREACH(auto const& it, er) {
        const IOAddress& addr = it->addr_;
        if (addr <= lower_bound_address) {
            // Not greater than lower_bound_address.
            continue;
        }
        if ((qry_start_time > 0) && (it->cltt_ < qry_start_time)) {
            // Too old.
            continue;
        }
        if ((qry_end_time > 0) && (it->cltt_ > qry_end_time)) {
            // Too young.
            continue;
        }
        sorted[addr] = it;
    }

    // Return all leases being within the page size.
    for (auto const& it : sorted) {
        collection.push_back(Lease4Ptr(new Lease4(*it.second)));
        if (collection.size() >= page_size.page_size_) {
            break;
        }
    }
    return (collection);
}

void
Memfile_LeaseMgr::wipeExtendedInfoTables6() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        relay_id6_.clear();
        remote_id6_.clear();
    } else {
        relay_id6_.clear();
        remote_id6_.clear();
    }
}

size_t
Memfile_LeaseMgr::byRelayId6size() const {
    return (relay_id6_.size());
}

size_t
Memfile_LeaseMgr::byRemoteId6size() const {
    return (remote_id6_.size());
}

Lease6Collection
Memfile_LeaseMgr::getLeases6ByRelayId(const DUID& relay_id,
                                      const IOAddress& lower_bound_address,
                                      const LeasePageSize& page_size) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_RELAYID6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(relay_id.toText());

    // Expecting IPv6 valid address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLeases6ByRelayIdInternal(relay_id,
                                            lower_bound_address,
                                            page_size));
    } else {
        return (getLeases6ByRelayIdInternal(relay_id,
                                            lower_bound_address,
                                            page_size));
    }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6ByRelayIdInternal(const DUID& relay_id,
                                              const IOAddress& lower_bound_address,
                                              const LeasePageSize& page_size) {
    const std::vector<uint8_t>& relay_id_data = relay_id.getDuid();
    Lease6Collection collection;
    const RelayIdIndex& idx = relay_id6_.get<RelayIdIndexTag>();
    RelayIdIndex::const_iterator lb =
        idx.lower_bound(boost::make_tuple(relay_id_data, lower_bound_address));

    // Return all leases being within the page size.
    IOAddress last_addr = lower_bound_address;
    for (; lb != idx.end(); ++lb) {
        if ((*lb)->lease_addr_ == last_addr) {
            // Already seen: skip it.
            continue;
        }
        if ((*lb)->id_ != relay_id_data) {
            // Gone after the relay id index.
            break;
        }
        last_addr = (*lb)->lease_addr_;
        Lease6Ptr lease = getAnyLease6Internal(last_addr);
        if (lease) {
            collection.push_back(lease);
            if (collection.size() >= page_size.page_size_) {
                break;
            }
        }
    }
    return (collection);
}

Lease6Collection
Memfile_LeaseMgr::getLeases6ByRemoteId(const OptionBuffer& remote_id,
                                       const IOAddress& lower_bound_address,
                                       const LeasePageSize& page_size) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MEMFILE_GET_REMOTEID6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(idToText(remote_id));

    // Expecting IPv6 valid address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getLeases6ByRemoteIdInternal(remote_id,
                                             lower_bound_address,
                                             page_size));
    } else {
        return (getLeases6ByRemoteIdInternal(remote_id,
                                             lower_bound_address,
                                             page_size));
    }
}

Lease6Collection
Memfile_LeaseMgr::getLeases6ByRemoteIdInternal(const OptionBuffer& remote_id,
                                               const IOAddress& lower_bound_address,
                                               const LeasePageSize& page_size) {
    Lease6Collection collection;
    std::set<IOAddress> sorted;
    const RemoteIdIndex& idx = remote_id6_.get<RemoteIdIndexTag>();
    RemoteIdIndexRange er = idx.equal_range(remote_id);
    // Store all addresses greater than lower_bound_address.
    BOOST_FOREACH(auto const& it, er) {
        const IOAddress& addr = it->lease_addr_;
        if (addr <= lower_bound_address) {
            continue;
        }
        static_cast<void>(sorted.insert(addr));
    }

    // Return all leases being within the page size.
    for (const IOAddress& addr : sorted) {
        Lease6Ptr lease = getAnyLease6Internal(addr);
        if (lease) {
            collection.push_back(lease);
            if (collection.size() >= page_size.page_size_) {
                break;
            }
        }
    }
    return (collection);
}

size_t
Memfile_LeaseMgr::extractExtendedInfo4(bool update, bool current) {
    CfgConsistencyPtr cfg;
    if (current) {
        cfg = CfgMgr::instance().getCurrentCfg()->getConsistency();
    } else {
        cfg = CfgMgr::instance().getStagingCfg()->getConsistency();
    }
    if (!cfg) {
        isc_throw(Unexpected, "the " << (current ? "current" : "staging")
                  << " consistency configuration is null");
    }
    auto check = cfg->getExtendedInfoSanityCheck();

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_MEMFILE_BEGIN_EXTRACT_EXTENDED_INFO4)
        .arg(CfgConsistency::sanityCheckToText(check))
        .arg(update ? " updating in file" : "");

    size_t leases = 0;
    size_t modified = 0;
    size_t updated = 0;
    size_t processed = 0;
    auto& index = storage4_.get<AddressIndexTag>();
    auto lease_it = index.begin();
    auto next_it = index.end();

    for (; lease_it != index.end(); lease_it = next_it) {
        next_it = std::next(lease_it);
        Lease4Ptr lease = *lease_it;
        ++leases;
        try {
            if (upgradeLease4ExtendedInfo(lease, check)) {
                ++modified;
                if (update && persistLeases(V4)) {
                    lease_file4_->append(*lease);
                    ++updated;
                }
            }
            // Work on a copy as the multi-index requires fields used
            // as indexes to be read-only.
            Lease4Ptr copy(new Lease4(*lease));
            extractLease4ExtendedInfo(copy, false);
            if (!copy->relay_id_.empty() || !copy->remote_id_.empty()) {
                index.replace(lease_it, copy);
                ++processed;
            }
        } catch (const std::exception& ex) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_MEMFILE_EXTRACT_EXTENDED_INFO4_ERROR)
                .arg(lease->addr_.toText())
                .arg(ex.what());
        }
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_EXTRACT_EXTENDED_INFO4)
        .arg(leases)
        .arg(modified)
        .arg(updated)
        .arg(processed);

    return (updated);
}

size_t
Memfile_LeaseMgr::upgradeExtendedInfo4(const LeasePageSize& /* page_size */) {
    return (0);
}

void
Memfile_LeaseMgr::buildExtendedInfoTables6() {
    CfgConsistencyPtr cfg = CfgMgr::instance().getStagingCfg()->getConsistency();
    if (!cfg) {
        isc_throw(Unexpected, "the staging consistency configuration is null");
    }
    auto check = cfg->getExtendedInfoSanityCheck();
    bool enabled = getExtendedInfoTablesEnabled();

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_MEMFILE_BEGIN_BUILD_EXTENDED_INFO_TABLES6)
        .arg(CfgConsistency::sanityCheckToText(check))
        .arg(enabled ? "enabled" : "disabled");

    // Clear tables when enabled.
    if (enabled) {
        relay_id6_.clear();
        remote_id6_.clear();
    }

    size_t leases = 0;
    size_t modified = 0;
    size_t processed = 0;

    for (auto const& lease : storage6_) {
        ++leases;
        try {
            if (upgradeLease6ExtendedInfo(lease, check)) {
                ++modified;
            }
            if (enabled && addExtendedInfo6(lease)) {
                ++processed;
            }
        } catch (const std::exception& ex) {
            LOG_ERROR(dhcpsrv_logger,
                      DHCPSRV_MEMFILE_BUILD_EXTENDED_INFO_TABLES6_ERROR)
                .arg(lease->addr_.toText())
                .arg(ex.what());
        }
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_BUILD_EXTENDED_INFO_TABLES6)
        .arg(leases)
        .arg(modified)
        .arg(processed);
}

size_t
Memfile_LeaseMgr::upgradeExtendedInfo6(const LeasePageSize& /* page_size */) {
    return (0);
}

void
Memfile_LeaseMgr::deleteExtendedInfo6(const IOAddress& addr) {
    LeaseAddressRelayIdIndex& relay_id_idx =
        relay_id6_.get<LeaseAddressIndexTag>();
    static_cast<void>(relay_id_idx.erase(addr));
    LeaseAddressRemoteIdIndex& remote_id_idx =
        remote_id6_.get<LeaseAddressIndexTag>();
    static_cast<void>(remote_id_idx.erase(addr));
}

void
Memfile_LeaseMgr::addRelayId6(const IOAddress& lease_addr,
                              const std::vector<uint8_t>& relay_id) {
    Lease6ExtendedInfoPtr ex_info;
    ex_info.reset(new Lease6ExtendedInfo(lease_addr, relay_id));
    relay_id6_.insert(ex_info);
}

void
Memfile_LeaseMgr::addRemoteId6(const IOAddress& lease_addr,
                               const std::vector<uint8_t>& remote_id) {
    Lease6ExtendedInfoPtr ex_info;
    ex_info.reset(new Lease6ExtendedInfo(lease_addr, remote_id));
    remote_id6_.insert(ex_info);
}

void
Memfile_LeaseMgr::writeLeases4(const std::string& filename) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        writeLeases4Internal(filename);
    } else {
        writeLeases4Internal(filename);
    }
}

void
Memfile_LeaseMgr::writeLeases4Internal(const std::string& filename) {
    bool overwrite = (lease_file4_ && lease_file4_->getFilename() == filename);
    try {
        if (overwrite) {
            lease_file4_->close();
        }
        std::ostringstream old;
        old << filename << ".bak" << getpid();
        ::rename(filename.c_str(), old.str().c_str());
        CSVLeaseFile4 backup(filename);
        backup.open();
        for (auto const& lease : storage4_) {
            backup.append(*lease);
        }
        backup.close();
        if (overwrite) {
            lease_file4_->open(true);
        }
    } catch (const std::exception&) {
        if (overwrite) {
            lease_file4_->open(true);
        }
        throw;
    }
}

void
Memfile_LeaseMgr::writeLeases6(const std::string& filename) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        writeLeases6Internal(filename);
    } else {
        writeLeases6Internal(filename);
    }
}

void
Memfile_LeaseMgr::writeLeases6Internal(const std::string& filename) {
    bool overwrite = (lease_file6_ && lease_file6_->getFilename() == filename);
    try {
        if (overwrite) {
            lease_file6_->close();
        }
        std::ostringstream old;
        old << filename << ".bak" << getpid();
        ::rename(filename.c_str(), old.str().c_str());
        CSVLeaseFile6 backup(filename);
        backup.open();
        for (auto const& lease : storage6_) {
            backup.append(*lease);
        }
        backup.close();
        if (overwrite) {
            lease_file6_->open(true);
        }
    } catch (const std::exception&) {
        if (overwrite) {
            lease_file6_->open(true);
        }
        throw;
    }
}

TrackingLeaseMgrPtr
Memfile_LeaseMgr::factory(const isc::db::DatabaseConnection::ParameterMap& parameters) {
    LOG_INFO(dhcpsrv_logger, DHCPSRV_MEMFILE_DB)
        .arg(DatabaseConnection::redactedAccessString(parameters));
    return (TrackingLeaseMgrPtr(new Memfile_LeaseMgr(parameters)));
}

}  // namespace dhcp
}  // namespace isc
