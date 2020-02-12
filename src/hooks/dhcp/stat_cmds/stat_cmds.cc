// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <config/command_mgr.h>
#include <config/cmds_impl.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/multi_threading_utils.h>
#include <dhcpsrv/subnet_id.h>
#include <hooks/hooks.h>
#include <exceptions/exceptions.h>
#include <stat_cmds.h>
#include <stat_cmds_log.h>
#include <stats/stats_mgr.h>
#include <util/boost_time_utils.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::config;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace isc::stats;
using namespace std;

namespace isc {
namespace stat_cmds {

/// @brief Exception thrown no subnets fall within the selection criteria
/// This exception is thrown when a valid combination of query parameters
/// excludes all known (i.e. configured) subnets.
class NotFound: public isc::Exception {
public:
    NotFound (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Implements command handling for stat-leaseX-get commands
class LeaseStatCmdsImpl : private CmdsImpl {
public:

    /// @brief Wrapper class for stat-leaseX-get command parameters.
    class Parameters {
    public:
        /// @brief Specifies the subnet-id for a single subnet, or
        /// the first subnet for a subnet range
        SubnetID first_subnet_id_;

        /// @brief Specifies the last subnet for subnet range
        SubnetID last_subnet_id_;

        /// @brief Denotes the query selection mode all, subnet,
        /// or subnet range
        LeaseStatsQuery::SelectMode select_mode_;

        /// @brief Generate a string version of the contents
        std::string toText() {
            std::stringstream os;
            switch (select_mode_) {
            case LeaseStatsQuery::ALL_SUBNETS:
                os << "[all subnets]";
                break;
            case LeaseStatsQuery::SINGLE_SUBNET:
                os << "[subnet-id=" << first_subnet_id_ << "]";
                break;
            case LeaseStatsQuery::SUBNET_RANGE:
                os << "[subnets " << first_subnet_id_
                   << " through " << last_subnet_id_ << "]";
                break;
            }

            return (os.str());
        }
    };

public:

    /// @brief Provides the implementation for stat-lease4-get,
    /// @ref isc::stat_cmds::StatCmds::statLease4GetHandler
    ///
    /// It parses the command arguments, and then invokes makeResult4()
    /// to fulfull the lease4 statistics fetch. It then constructs the outbound
    /// response based on those results.  If a NotFound exception is caught,
    /// a CONTROL_RESULT_EMTPY response is generated.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    statLease4GetHandler(CalloutHandle& handle);

    /// @brief Provides the implementation for stat-lease6-get,
    /// @ref isc::stat_cmds::StatCmds::statLease6GetHandler
    ///
    /// It parses the command arguments, and then invokes makeResult6()
    /// to fulfull the lease6 statistics fetch. It then constructs the outbound
    /// response based on those results.  If a NotFound exception is caught,
    /// a CONTROL_RESULT_EMTPY response is generated.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// command JSON text in the "command" argument
    /// @return 0 upon success, non-zero otherwise
    int
    statLease6GetHandler(CalloutHandle& handle);

    /// @brief Parses command arguments into stat-leaseX-get parameters
    /// @param cmd_args Element form of command arguments to parse
    /// @throw BadValue if any of the following rules are broken:
    ///
    /// -# If subnet-id is specified it must be an integer > 0
    /// -# If subnet-range is specified it must contain both
    /// first-subnet-id and last-subnet-id and their values
    /// must fulfill: 0 < first-subnet-id < last-subnet-id
    /// -# subnet-id and subnet-range are mutually exclusive
    Parameters getParameters(const ConstElementPtr& cmd_args);

    /// @brief Executes the lease4 query and constructs the outbound result set
    ///
    /// This method uses the command parameters to identify the range
    /// of configured subnets. If the range contains no known subnets
    /// then a NotFound exception is thrown.  Having determined the range
    /// to be valid, it then executes the appropriate Lease4 stats query via
    /// the LeaseMgr.
    ///
    /// Lastly, it iterates over the qualifying subnets adding a row
    /// of statistics for each one to the result-set.  Each row combines
    /// the totals from StatsMgr with the type and state counts from the
    /// query results.  For subnets with no query data (i.e. no leases),
    /// their rows have non-zero values for totals only.
    ///
    /// @param result Element to which the constructed result-set will be added.
    /// @param params Parsed stat-lease4-cmd parameters
    /// @throw NotFound if the selection criteria eliminates all known subnets
    uint64_t makeResultSet4(const ElementPtr& result, const Parameters& params);

    /// @brief Executes the lease4 query and constructs the outbound result set
    /// This method uses the command parameters to identify the range
    /// of configured subnets. If the range contains no known subnets
    /// then a NotFound exception is thrown.  Having determined the range
    /// to be valid, it then executes the appropriate Lease6 stats query via
    /// the LeaseMgr.
    ///
    /// Lastly, it iterates over the qualifying subnets adding a row
    /// of statistics for each one to the result-set.  Each row combines
    /// the totals from StatsMgr with the type and state counts from the
    /// query results.  For subnets with no query data (i.e. no leases),
    /// their rows have non-zero values for totals only.
    ///
    /// @param result Element to which the constructed result-set will be added.
    /// @param params Parsed stat-lease6-cmd parameters
    /// @throw NotFound if the selection criteria eliminates all known subnets
    uint64_t makeResultSet6(const ElementPtr& result, const Parameters& params);

    /// @brief Instantiates a new "empty" result-set Element
    ///
    /// Constructs a ElementPtr tree of an empty result set
    /// for holding rows of the given column labels. In JSON
    /// it appears as follows:
    ///
    /// "result-set": {
    ///     "timestamp": "2018-03-22 09:43:30.815371",
    ///     "columns": ["<label-1>, <label-2>, ... ],
    ///     "rows": []
    /// }
    ///
    /// And then adds it to the given wrapper element.
    ///
    /// @param wrapper Element to which the newly constructed result-set
    /// will be added.
    /// @param column_labels list of the column labels in the order the values
    /// for each column will appear in the result-set rows
    /// @return A reference to the writable list of rows of the result-set
    ElementPtr createResultSet(const ElementPtr& wrapper,
                               const std::vector<std::string>& column_labels);

    /// @brief Adds a row of Lease4 stat values to a list of value rows
    ///
    /// @param[out] value_rows  list of rows to which to add
    /// @param[out] subnet_id  id of the subnet of the new row. This value is
    /// also used for fetching the total addresses in the subnet
    /// @param assigned number of assigned addresses in the subnet
    /// @param declined number of declined addresses in the subnet
    void addValueRow4(ElementPtr value_rows, const SubnetID &subnet_id,
                      int64_t assigned, int64_t declined);

    /// @brief Adds a row of Lease6 stat values to a list of value rows
    ///
    /// @param[out] value_rows  list of rows to which to add
    /// @param[out] subnet_id  id of the subnet of the new row. This value is
    /// also used for fetching the total NAs and PDs in the subnet
    /// @param assigned number of assigned NAs in the subnet
    /// @param declined number of declined NAs in the subnet
    /// @param assigned_pds number of assigned PDs the subnet
    void addValueRow6(ElementPtr value_rows, const SubnetID &subnet_id,
                      int64_t assigned, int64_t declined, int64_t assigned_pds);

    /// @brief Fetches a single statistic for a subnet from StatsMgr
    ///
    /// Uses the given id and name to query the StatsMgr for the desired value.
    ///
    /// @param subnet_id id of the desired subnet
    /// @param name name of the desired statistic
    int64_t getSubnetStat(const SubnetID& subnet_id, const std::string& name);
};

int
LeaseStatCmdsImpl::statLease4GetHandler(CalloutHandle& handle) {
    ElementPtr result = Element::createMap();
    Parameters params;
    ConstElementPtr response;

    // Extract the command and then the parameters
    try {
        extractCommand(handle);
        params = getParameters(cmd_args_);
    } catch (const std::exception& ex) {
        LOG_ERROR(stat_cmds_logger, STAT_CMDS_LEASE4_GET_INVALID)
                  .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    try {
        // Now build the result set
        uint64_t rows = makeResultSet4(result, params);
        LOG_INFO(stat_cmds_logger, STAT_CMDS_LEASE4_GET)
                .arg(params.toText())
                .arg(rows);
        std::stringstream os;
        os << "stat-lease4-get" << params.toText() << ": " << rows << " rows found";
        response = createAnswer(CONTROL_RESULT_SUCCESS, os.str(), result);
    } catch (const NotFound& ex) {
        // Criteria was valid but included no known subnets,
        // so we return a not found response.
        LOG_INFO(stat_cmds_logger, STAT_CMDS_LEASE4_GET_NO_SUBNETS)
                 .arg(params.toText())
                 .arg(ex.what());
        std::stringstream os;
        os << "stat-lease4-get" << params.toText() <<  ": no matching data, " << ex.what();
        response = createAnswer(CONTROL_RESULT_EMPTY, os.str(), result);
    } catch (const std::exception& ex) {
        LOG_ERROR(stat_cmds_logger, STAT_CMDS_LEASE4_GET_FAILED)
                  .arg(params.toText())
                  .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    setResponse(handle, response);
    return (0);
}

int
LeaseStatCmdsImpl::statLease6GetHandler(CalloutHandle& handle) {
    ElementPtr result = Element::createMap();
    Parameters params;
    ConstElementPtr response;

    // Extract the command and then the parameters
    try {
        extractCommand(handle);
        params = getParameters(cmd_args_);
    } catch (const std::exception& ex) {
        LOG_ERROR(stat_cmds_logger, STAT_CMDS_LEASE6_GET_INVALID)
                  .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    try {
        // Now build the result set
        uint64_t rows = makeResultSet6(result, params);
        LOG_INFO(stat_cmds_logger, STAT_CMDS_LEASE6_GET)
                .arg(params.toText())
                .arg(rows);
        std::stringstream os;
        os << "stat-lease6-get" << params.toText() << ": " << rows << " rows found";
        response = createAnswer(CONTROL_RESULT_SUCCESS, os.str(), result);
    } catch (const NotFound& ex) {
        // Criteria was valid but included no known subnets,
        // so we return a not found response.
        LOG_INFO(stat_cmds_logger, STAT_CMDS_LEASE6_GET_NO_SUBNETS)
                 .arg(params.toText())
                 .arg(ex.what());
        std::stringstream os;
        os << "stat-lease6-get" << params.toText() <<  ": no matching data, " << ex.what();
        response = createAnswer(CONTROL_RESULT_EMPTY, os.str(), result);
    } catch (const std::exception& ex) {
        LOG_ERROR(stat_cmds_logger, STAT_CMDS_LEASE6_GET_FAILED)
                 .arg(params.toText())
                 .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    setResponse(handle, response);
    return (0);
}

LeaseStatCmdsImpl::Parameters
LeaseStatCmdsImpl::getParameters(const ConstElementPtr& cmd_args) {
    Parameters params;

    params.select_mode_ = LeaseStatsQuery::ALL_SUBNETS;
    params.first_subnet_id_ = 0;
    params.last_subnet_id_ = 0;
    if (!cmd_args ) {
        // No arguments defaults to ALL_SUBNETS.
        return (params);
    }

    if (cmd_args->getType() != Element::map) {
        isc_throw(BadValue, "'arguments' parameter is not a map");
    }

    params.select_mode_ = LeaseStatsQuery::ALL_SUBNETS;
    if (cmd_args->contains("subnet-id")) {

        ConstElementPtr value = cmd_args->get("subnet-id");
        if (value->getType() != Element::integer) {
            isc_throw(BadValue, "'subnet-id' parameter is not integer");
        }

        if (value->intValue() <= 0) {
            isc_throw(BadValue, "'subnet-id' parameter must be > 0");
        }

        params.first_subnet_id_ = value->intValue();
        params.select_mode_ = LeaseStatsQuery::SINGLE_SUBNET;
    }

    if (cmd_args->contains("subnet-range")) {
        if (params.select_mode_ == LeaseStatsQuery::SINGLE_SUBNET) {
            isc_throw(BadValue, "cannot specify both subnet-id and subnet-range");
        }

        ConstElementPtr range = cmd_args->get("subnet-range");
        if (range->getType() != Element::map) {
            isc_throw(BadValue, "subnet-range parameter is not a map");
        }

        ConstElementPtr value = range->get("first-subnet-id");
        if (!value || value->getType() != Element::integer) {
            isc_throw(BadValue, "'first-subnet-id' parameter missing or not an integer");
        }

        if (value->intValue() <= 0) {
            isc_throw(BadValue, "'first-subnet-id' parameter must be > 0");
        }

        params.first_subnet_id_ = value->intValue();

        value = range->get("last-subnet-id");
        if (!value || value->getType() != Element::integer) {
            isc_throw(BadValue, "'last-subnet-id' parameter missing or not an integer");
        }

        if (value->intValue() <= 0) {
            isc_throw(BadValue, "'last-subnet-id' parameter must be > 0");
        }

        params.last_subnet_id_ = value->intValue();

        if (params.last_subnet_id_ < params.first_subnet_id_) {
            isc_throw(BadValue, "'last-subnet-id' must be greater than 'first-subnet-id'");
        }

        params.select_mode_ = LeaseStatsQuery::SUBNET_RANGE;
    }

    return (params);
}

uint64_t
LeaseStatCmdsImpl::makeResultSet4(const ElementPtr& result_wrapper,
                                  const Parameters& params) {
    // First we need to determine the range of configured subnets
    // which meet the selection criteria.  If the range contains
    // no subnets we punt.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    const auto& idx = subnets->get<SubnetSubnetIdIndexTag>();

    // Init to ALL so we can use auto ;)
    auto lower = idx.begin();
    auto upper = idx.end();
    switch (params.select_mode_) {
    case LeaseStatsQuery::SINGLE_SUBNET:
        lower = idx.find(params.first_subnet_id_);
        // If it's an unknown subnet, punt.
        if (lower == idx.end()) {
            isc_throw(NotFound, "subnet-id: "
                      << params.first_subnet_id_ << " does not exist");
        }

        upper = idx.upper_bound(params.first_subnet_id_);
        break;
    case LeaseStatsQuery::SUBNET_RANGE:
        lower = idx.lower_bound(params.first_subnet_id_);
        upper = idx.upper_bound(params.last_subnet_id_);
        break;
    default:
        break;
    }

    // If it's an empty range, punt.
    if (lower == upper) {
        isc_throw(NotFound, "selected ID range: "
            << params.first_subnet_id_ << " through "
            << params.last_subnet_id_ << " includes no known subnets");
    }

    // Now, that we have a valid range, run the Lease query.
    LeaseStatsQueryPtr query;
    switch (params.select_mode_) {
    case LeaseStatsQuery::ALL_SUBNETS:
        query = LeaseMgrFactory::instance().startLeaseStatsQuery4();
        break;
    case LeaseStatsQuery::SINGLE_SUBNET:
        query = LeaseMgrFactory::instance()
                .startSubnetLeaseStatsQuery4(params.first_subnet_id_);
        break;
    case LeaseStatsQuery::SUBNET_RANGE:
        query = LeaseMgrFactory::instance()
                .startSubnetRangeLeaseStatsQuery4(params.first_subnet_id_,
                                                  params.last_subnet_id_);
        break;
    }

    // Create the empty result-set.
    std::vector<std::string>column_labels = { "subnet-id", "total-addreses",
                                              "assigned-addreses","declined-addreses"};
    ElementPtr value_rows = createResultSet(result_wrapper, column_labels);

    // Get the first query row
    LeaseStatsRow query_row;
    bool query_eof = !(query->getNextRow(query_row));

    // Now we iterate over the selected range, building rows accordingly.
    for (auto cur_subnet = lower; cur_subnet != upper; ++cur_subnet) {
        SubnetID cur_id = (*cur_subnet)->getID();

        // Add total only rows for subnets that occur before,
        // in-between, or after the subnets in the query content
        if ((cur_id < query_row.subnet_id_) ||
            (cur_id > query_row.subnet_id_) ||
            (query_eof)) {
            // Generate a totals only row
            addValueRow4(value_rows, cur_id, 0, 0);
            continue;
        }

        // Current subnet matches query row, so iterate over its
        // query rows (one per state) and accumulate them
        // into a result-set row.
        int64_t assigned = 0;
        int64_t declined = 0;
        bool add_row = false;
        while (!query_eof && (query_row.subnet_id_ == cur_id)) {
            if (query_row.lease_state_ == Lease::STATE_DEFAULT) {
                add_row = true;
                assigned = query_row.state_count_;
            } else if (query_row.lease_state_ == Lease::STATE_DECLINED) {
                add_row = true;
                declined = query_row.state_count_;
            }

            query_eof = !(query->getNextRow(query_row));
        }

        // Add the row for the current subnet
        if (add_row) {
            addValueRow4(value_rows, cur_id, assigned, declined);
        }
    }

    return (value_rows->size());
}

uint64_t
LeaseStatCmdsImpl::makeResultSet6(const ElementPtr& result_wrapper,
                                  const Parameters& params) {
    // Iterate over the selected range of configured subnets generating
    // a result-set row for each one.  If a subnet has data in the query
    // content use it, otherwise, it gets a row with totals only.  This
    // way we send back a row for every selected subnet.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();

    // Set the bounds on the selected subnet range
    const auto& idx = subnets->get<SubnetSubnetIdIndexTag>();

    // Init to all so we can use auto ;)
    auto lower = idx.begin();
    auto upper = idx.end();
    switch (params.select_mode_) {
    case LeaseStatsQuery::SINGLE_SUBNET:
        lower = idx.lower_bound(params.first_subnet_id_);
        // If it's an unknown subnet, punt.
        if (lower == idx.end()) {
            isc_throw(NotFound, "subnet-id: "
                      << params.first_subnet_id_ << " does not exist");
        }

        upper = idx.upper_bound(params.first_subnet_id_);
        break;
    case LeaseStatsQuery::SUBNET_RANGE:
        lower = idx.lower_bound(params.first_subnet_id_);
        upper = idx.upper_bound(params.last_subnet_id_);
        break;
    default:
        break;
    }

    // If it's empty range, punt.
    if (lower == upper) {
        isc_throw(NotFound, "selected ID range: "
            << params.first_subnet_id_ << " through "
            << params.last_subnet_id_ << " includes no known subnets");
    }

    // Create the result-set map.
    // labels could be class statics?
    std::vector<std::string>column_labels = { "subnet-id", "total-nas", "assigned-nas",
                                              "declined-nas", "total-pds", "assigned-pds"};
    ElementPtr value_rows = createResultSet(result_wrapper, column_labels);

    // Now we can run the stats query.
    LeaseStatsQueryPtr query;
    switch (params.select_mode_) {
    case LeaseStatsQuery::ALL_SUBNETS:
        query = LeaseMgrFactory::instance().startLeaseStatsQuery6();
        break;
    case LeaseStatsQuery::SINGLE_SUBNET:
        query = LeaseMgrFactory::instance()
                .startSubnetLeaseStatsQuery6(params.first_subnet_id_);
        break;
    case LeaseStatsQuery::SUBNET_RANGE:
        query = LeaseMgrFactory::instance()
                .startSubnetRangeLeaseStatsQuery6(params.first_subnet_id_,
                                                  params.last_subnet_id_);
        break;
    }

    // Get the first query row
    LeaseStatsRow query_row;
    bool query_eof = !(query->getNextRow(query_row));

    for (auto cur_subnet = lower; cur_subnet != upper; ++cur_subnet) {
        SubnetID cur_id = (*cur_subnet)->getID();

        // Add total only rows for subnets that occur before,
        // in-between, or after subnets in the query content
        if ((cur_id < query_row.subnet_id_) ||
            (cur_id > query_row.subnet_id_) ||
            (query_eof)) {
            // Generate a totals only row
            addValueRow6(value_rows, cur_id, 0, 0, 0);
            continue;
        }

        // Current subnet matches query row, so iterate over
        // its query rows and accumulate them into a result-set row.
        int64_t assigned = 0;
        int64_t declined = 0;
        int64_t assigned_pds = 0;
        bool add_row = false;
        while (!query_eof && (query_row.subnet_id_ == cur_id)) {

            if (query_row.lease_state_ == Lease::STATE_DEFAULT) {
                add_row = true;
                if (query_row.lease_type_ == Lease::TYPE_NA) {
                    assigned = query_row.state_count_;
                } else {
                    assigned_pds = query_row.state_count_;
                }
            } else if (query_row.lease_state_ == Lease::STATE_DECLINED) {
                add_row = true;
                declined = query_row.state_count_;
            }

            // Get next query row
            query_eof = !(query->getNextRow(query_row));
        }

        if (add_row) {
            addValueRow6(value_rows, cur_id, assigned, declined, assigned_pds);
        }
    }

    return (value_rows->size());
}

ElementPtr
LeaseStatCmdsImpl::createResultSet(const ElementPtr &result_wrapper,
                                   const std::vector<std::string>& column_labels) {
    // Create the result-set map and add it to the wrapper.
    ElementPtr result_set = Element::createMap();
    result_wrapper->set("result-set", result_set);

    // Create the timestamp based on time now and add it to the result set.
    boost::posix_time::ptime now(boost::posix_time::microsec_clock::universal_time());

    ElementPtr timestamp = Element::create(isc::util::ptimeToText(now));
    result_set->set("timestamp", timestamp);

    // Create the list of column names and add it to the result set.
    ElementPtr columns = Element::createList();
    for (auto label = column_labels.begin(); label != column_labels.end(); ++label) {
        columns->add(Element::create(*label));
    }
    result_set->set("columns", columns);

    // Create the empty value_rows list, add it and then return it.
    ElementPtr value_rows = Element::createList();
    result_set->set("rows", value_rows);
    return (value_rows);
}


void
LeaseStatCmdsImpl::addValueRow4(ElementPtr value_rows, const SubnetID &subnet_id,
                          int64_t assigned, int64_t declined) {
    ElementPtr row = Element::createList();
    row->add(Element::create(static_cast<int64_t>(subnet_id)));
    row->add(Element::create(getSubnetStat(subnet_id, "total-addresses")));
    row->add(Element::create(assigned));
    row->add(Element::create(declined));
    value_rows->add(row);
}

void
LeaseStatCmdsImpl::addValueRow6(ElementPtr value_rows, const SubnetID &subnet_id,
                           int64_t assigned, int64_t declined, int64_t assigned_pds) {
    ElementPtr row = Element::createList();
    row->add(Element::create(static_cast<int64_t>(subnet_id)));
    row->add(Element::create(getSubnetStat(subnet_id, "total-nas")));
    row->add(Element::create(assigned));
    row->add(Element::create(declined));
    row->add(Element::create(getSubnetStat(subnet_id, "total-pds")));
    row->add(Element::create(assigned_pds));
    value_rows->add(row);
}

int64_t
LeaseStatCmdsImpl::getSubnetStat(const SubnetID& subnet_id, const std::string& name) {
    ObservationPtr stat = StatsMgr::instance().
                          getObservation(StatsMgr::generateName("subnet", subnet_id, name));
    if (stat) {
        return (stat->getInteger().first);
    }

    return (0);
}

// Using a critical section to avoid any changes in parallel.

int
StatCmds::statLease4GetHandler(CalloutHandle& handle) {
    LeaseStatCmdsImpl impl;
    MultiThreadingCriticalSection sc;
    return(impl.statLease4GetHandler(handle));
}

int
StatCmds::statLease6GetHandler(CalloutHandle& handle) {
    LeaseStatCmdsImpl impl;
    MultiThreadingCriticalSection sc;
    return(impl.statLease6GetHandler(handle));
}

};
};
