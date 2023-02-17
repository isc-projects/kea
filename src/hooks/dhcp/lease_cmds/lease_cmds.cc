// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <config/command_mgr.h>
#include <config/cmds_impl.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <asiolink/io_address.h>
#include <database/db_exceptions.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_exceptions.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/ncr_generator.h>
#include <dhcpsrv/resource_handler.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/sanity_checker.h>
#include <dhcp/duid.h>
#include <hooks/hooks.h>
#include <exceptions/exceptions.h>
#include <lease_cmds.h>
#include <lease_cmds_exceptions.h>
#include <lease_parser.h>
#include <lease_cmds_log.h>
#include <stats/stats_mgr.h>
#include <util/encode/hex.h>
#include <util/multi_threading_mgr.h>
#include <util/strutil.h>

#include <boost/scoped_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <sstream>

using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::dhcp_ddns;
using namespace isc::config;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace isc::stats;
using namespace isc::util;
using namespace std;

namespace isc {
namespace lease_cmds {

/// @brief Wrapper class around reservation command handlers.
class LeaseCmdsImpl : private CmdsImpl {
public:

    /// @brief Parameters specified for lease commands.
    class Parameters {
    public:

        /// @brief specifies type of query (by IP addr, by hwaddr, by DUID)
        typedef enum {
            TYPE_ADDR,      ///< query by IP address (either v4 or v6)
            TYPE_HWADDR,    ///< query by hardware address (v4 only)
            TYPE_DUID,      ///< query by DUID (v6 only)
            TYPE_CLIENT_ID  ///< query by client identifier (v4 only).
        } Type;

        /// @brief Specifies subnet-id (always used)
        SubnetID subnet_id;

        /// @brief Specifies IPv4/v6 address (used when query_type is TYPE_ADDR)
        IOAddress addr;

        /// @brief Specifies hardware address (used when query_type is TYPE_HWADDR)
        HWAddrPtr hwaddr;

        /// @brief Specifies identifier value (used when query_type is TYPE_DUID)
        isc::dhcp::DuidPtr duid;

        /// @brief Specifies identifier value (used when query_type is TYPE_CLIENT_ID)
        isc::dhcp::ClientIdPtr client_id;

        /// @brief Attempts to covert text to one of specified types
        ///
        /// Supported values are: "address", hw-address and duid.
        ///
        /// @param txt text to be converted
        ///
        /// @return value converted to Parameters::Type
        ///
        /// @throw BadValue if unsupported type is specified
        static Type txtToType(const std::string& txt) {
            if (txt == "address") {
                return (Parameters::TYPE_ADDR);
            } else if (txt == "hw-address") {
                return (Parameters::TYPE_HWADDR);
            } else if (txt == "duid") {
                return (Parameters::TYPE_DUID);
            } else if (txt == "client-id") {
                return (Parameters::TYPE_CLIENT_ID);
            } else {
                isc_throw(BadValue, "Incorrect identifier type: "
                          << txt << ", the only supported values are: "
                          "address, hw-address, duid");
            }
        }

        /// @brief specifies parameter types
        Type query_type;

        /// @brief Lease type (NA,TA or PD) used for v6 leases
        Lease::Type lease_type;

        /// @brief IAID identifier used for v6 leases
        uint32_t iaid;

        /// @brief Indicates whether or not DNS should be updated.
        bool updateDDNS;

        /// @brief Default constructor.
        Parameters()
            : subnet_id(0), addr("::"), query_type(TYPE_ADDR),
              lease_type(Lease::TYPE_NA), iaid(0), updateDDNS(false) {
        }
    };

public:

    /// @brief lease4-add, lease6-add command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::leaseAddHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// add command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    leaseAddHandler(CalloutHandle& handle);

    /// @brief lease6-bulk-apply command handler
    ///
    /// Provides the implementation for the
    /// @ref isc::lease_cmds::LeaseCmds::lease6BulkApplyHandler.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// add command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    lease6BulkApplyHandler(CalloutHandle& handle);

    /// @brief lease4-get, lease6-get command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::leaseGetHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    leaseGetHandler(CalloutHandle& handle);

    /// @brief lease4-get-all, lease6-get-all commands handler
    ///
    /// These commands attempt to retrieve all IPv4 or IPv6 leases,
    /// or all IPv4 or all IPv6 leases belonging to the particular
    /// subnets. If no subnet identifiers are provided, it returns all
    /// IPv4 or IPv6 leases from the database.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise.
    int
    leaseGetAllHandler(CalloutHandle& handle);

    /// @brief lease4-get-page, lease6-get-page commands handler
    ///
    /// These commands attempt to retrieve 1 page of leases. The maximum size
    /// of the page is specified by the caller. The caller also specifies
    /// the last address returned in the previous page. The new page
    /// starts from the first address following the address specified by
    /// the caller. If the first page should be returned the IPv4
    /// zero address, IPv6 zero address or the keyword "start" should
    /// be provided instead of the last address.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get commands JSON text in the "command" argument.
    ///
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetPageHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-get-by-hw-address command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::leaseGetByHwAddressHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    ///
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetByHwAddressHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-get-by-client-id command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::leaseGetByClientIdHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    ///
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetByClientIdHandler(hooks::CalloutHandle& handle);

    /// @brief lease6-get-by-duid command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::leaseGetByDuidHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    ///
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetByDuidHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-get-by-hostname and lease6-get-by-hostname commands
    /// handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::leaseGetByHostnameHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    ///
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetByHostnameHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-del command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease4DelHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// delete command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    lease4DelHandler(CalloutHandle& handle);

    /// @brief lease6-del command handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease6DelHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// delete command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    lease6DelHandler(CalloutHandle& handle);

    /// @brief lease4-update handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease4UpdateHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// update command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    lease4UpdateHandler(CalloutHandle& handle);

    /// @brief lease6-update handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease6UpdateHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// update command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    lease6UpdateHandler(CalloutHandle& handle);

    /// @brief lease4-wipe handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease4WipeHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// wipe command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    lease4WipeHandler(CalloutHandle& handle);

    /// @brief lease6-wipe handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease6WipeHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// wipe command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    lease6WipeHandler(CalloutHandle& handle);

    /// @brief lease4-resend-ddns handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease4ResendDdnsHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// lease4-resend-ddns command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int lease4ResendDdnsHandler(CalloutHandle& handle);

    /// @brief lease6-resend-ddns handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::lease6ResendDdnsHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// lease6-resend-ddns command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int lease6ResendDdnsHandler(CalloutHandle& handle);

    /// @brief lease4-write handler, lease6-write handler
    ///
    /// Provides the implementation for @ref isc::lease_cmds::LeaseCmds::leaseWriteHandler
    ///
    /// @param handle Callout context - which is expected to contain the
    /// write command JSON text in the "command" argument
    ///
    /// @return 0 upon success, non-zero otherwise
    int
    leaseWriteHandler(CalloutHandle& handle);

    /// @brief Extracts parameters required for reservation-get and reservation-del
    ///
    /// See @ref Parameters class for detailed description of what is expected
    /// in the args structure.
    ///
    /// @param v6 whether addresses allowed are v4 (false) or v6 (true)
    /// @param args arguments passed to command
    ///
    /// @return parsed parameters
    ///
    /// @throw BadValue if input arguments don't make sense.
    Parameters getParameters(bool v6, const ConstElementPtr& args);

    /// @brief Convenience function fetching IPv6 address to be used to
    /// delete a lease.
    ///
    /// The returned parameter depends on the @c query_type value stored
    /// in the passed object. Note that the HW address is not allowed and
    /// this query type results in an exception. If the query type is of
    /// the address type, the address is returned. If the type is set to
    /// DUID, this function will try to find the lease for this DUID
    /// and return the corresponding address.
    ///
    /// @param parameters parameters extracted from the command.
    ///
    /// @return Lease of the lease to be deleted.
    ///
    /// @throw InvalidParameter if the DUID is not found when needed to
    /// find the lease or if the query type is by HW address.
    /// @throw InvalidOperation if the query type is unknown.
    Lease6Ptr getIPv6LeaseForDelete(const Parameters& parameters) const;

    /// @brief Returns a map holding brief information about a lease which
    /// failed to be deleted, updated or added.
    ///
    /// The DUID is only included if it is non-null. The address is only
    /// included if it is non-zero.
    ///
    /// @param lease_type lease type.
    /// @param lease_address lease address.
    /// @param duid DUID of the client.
    /// @param control_result Control result: "empty" of the lease was
    /// not found, "error" otherwise.
    /// @param error_message Error message.
    ///
    /// @return The JSON map of the failed leases.
    ElementPtr createFailedLeaseMap(const Lease::Type& lease_type,
                                    const IOAddress& lease_address,
                                    const DuidPtr& duid,
                                    const int control_result,
                                    const std::string& error_message) const;

    /// @brief Fetches an IP address parameter from a map of parameters
    ///
    /// @param map of parameters in which to look
    /// @name name of the parameter desired
    /// @param family expected protocol family of the address parameter,
    /// AF_INET or AF_INET6
    ///
    /// @return IOAddress containing the value of the parameter.
    ///
    /// @throw BadValue if the parameter is missing or invalid
    IOAddress getAddressParam(ConstElementPtr params, const std::string name,
                              short family = AF_INET) const;

    /// @brief Update stats when adding lease.
    ///
    /// @param lease Added lease.
    static void updateStatsOnAdd(const Lease4Ptr& lease);

    /// @brief Update stats when adding lease.
    ///
    /// @param lease Added lease.
    static void updateStatsOnAdd(const Lease6Ptr& lease);

    /// @brief Update stats when updating lease.
    ///
    /// @param existing Lease data before update.
    /// @param lease Lease data after update.
    static void updateStatsOnUpdate(const Lease4Ptr& existing,
                                    const Lease4Ptr& lease);

    /// @brief Update stats when updating lease.
    ///
    /// @param existing Lease data before update.
    /// @param lease Lease data after update.
    static void updateStatsOnUpdate(const Lease6Ptr& existing,
                                    const Lease6Ptr& lease);

    /// @brief Update stats when deleting lease.
    ///
    /// @param lease Deleted lease.
    static void updateStatsOnDelete(const Lease4Ptr& lease);

    /// @brief Update stats when deleting lease.
    ///
    /// @param lease Deleted lease.
    static void updateStatsOnDelete(const Lease6Ptr& lease);

    /// @brief Add or update lease.
    ///
    /// @param lease The lease to be added or updated (if exists).
    /// @param force_create Flag to indicate if the function should try to
    /// create the lease if it does not exists, or simply update and fail in
    /// such case.
    ///
    /// @return true if lease has been successfully added, false otherwise.
    static bool addOrUpdate4(Lease4Ptr lease, bool force_create);

    /// @brief Add or update lease.
    ///
    /// @param lease The lease to be added or updated (if exists).
    /// @param force_create Flag to indicate if the function should try to
    /// create the lease if it does not exists, or simply update and fail in
    /// such case.
    ///
    /// @return true if lease has been successfully added, false otherwise.
    static bool addOrUpdate6(Lease6Ptr lease, bool force_create);

    /// @brief Get DHCPv6 extended info.
    ///
    /// @param lease The lease to get extended info from.
    /// @return The extended info or null.
    inline static ConstElementPtr getExtendedInfo6(const Lease6Ptr& lease) {
        ConstElementPtr user_context = lease->getContext();
        if (!user_context || (user_context->getType() != Element::map)) {
            return (ConstElementPtr());
        }
        ConstElementPtr isc = user_context->get("ISC");
        if (!isc || (isc->getType() != Element::map)) {
            return (ConstElementPtr());
        }
        return (isc->get("relay-info"));
    }
};

void
LeaseCmdsImpl::updateStatsOnAdd(const Lease4Ptr& lease) {
    if (!lease->stateExpiredReclaimed()) {
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", lease->subnet_id_,
                                   "assigned-addresses"),
            int64_t(1));
        if (lease->stateDeclined()) {
            StatsMgr::instance().addValue("declined-addresses", int64_t(1));

            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", lease->subnet_id_,
                                       "declined-addresses"),
                int64_t(1));
        }
    }
}

void
LeaseCmdsImpl::updateStatsOnAdd(const Lease6Ptr& lease) {
    if (!lease->stateExpiredReclaimed()) {
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", lease->subnet_id_,
                                   lease->type_ == Lease::TYPE_NA ?
                                   "assigned-nas" : "assigned-pds"),
            int64_t(1));
        if (lease->stateDeclined()) {
            StatsMgr::instance().addValue("declined-addresses", int64_t(1));

            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", lease->subnet_id_,
                                       "declined-addresses"),
                int64_t(1));
        }
    }
}

void
LeaseCmdsImpl::updateStatsOnUpdate(const Lease4Ptr& existing,
                                   const Lease4Ptr& lease) {
    if (!existing->stateExpiredReclaimed()) {
        // old lease is non expired-reclaimed
        if (existing->subnet_id_ != lease->subnet_id_) {
            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", existing->subnet_id_,
                                       "assigned-addresses"),
                int64_t(-1));
        }
        if (existing->stateDeclined()) {
            // old lease is declined
            StatsMgr::instance().addValue("declined-addresses", int64_t(-1));

            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", existing->subnet_id_,
                                       "declined-addresses"),
                int64_t(-1));
        }
        if (!lease->stateExpiredReclaimed()) {
            // new lease is non expired-reclaimed
            if (existing->subnet_id_ != lease->subnet_id_) {
                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", lease->subnet_id_,
                                           "assigned-addresses"),
                    int64_t(1));
            }
            if (lease->stateDeclined()) {
                // new lease is declined
                StatsMgr::instance().addValue("declined-addresses", int64_t(1));

                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", lease->subnet_id_,
                                           "declined-addresses"),
                    int64_t(1));
            }
        }
    } else {
        // old lease is expired-reclaimed
        if (!lease->stateExpiredReclaimed()) {
            // new lease is non expired-reclaimed
            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", lease->subnet_id_,
                                       "assigned-addresses"),
                int64_t(1));
            if (lease->stateDeclined()) {
                // new lease is declined
                StatsMgr::instance().addValue("declined-addresses", int64_t(1));

                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", lease->subnet_id_,
                                           "declined-addresses"),
                    int64_t(1));
            }
        }
    }
}

void
LeaseCmdsImpl::updateStatsOnUpdate(const Lease6Ptr& existing,
                                   const Lease6Ptr& lease) {
    if (!existing->stateExpiredReclaimed()) {
        // old lease is non expired-reclaimed
        if (existing->subnet_id_ != lease->subnet_id_) {
            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", existing->subnet_id_,
                                       lease->type_ == Lease::TYPE_NA ?
                                       "assigned-nas" : "assigned-pds"),
                int64_t(-1));
        }
        if (existing->stateDeclined()) {
            // old lease is declined
            StatsMgr::instance().addValue("declined-addresses", int64_t(-1));

            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", existing->subnet_id_,
                                       "declined-addresses"),
                int64_t(-1));
        }
        if (!lease->stateExpiredReclaimed()) {
            // new lease is non expired-reclaimed
            if (existing->subnet_id_ != lease->subnet_id_) {
                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", lease->subnet_id_,
                                           lease->type_ == Lease::TYPE_NA ?
                                           "assigned-nas" : "assigned-pds"),
                    int64_t(1));
            }
            if (lease->stateDeclined()) {
                // new lease is declined
                StatsMgr::instance().addValue("declined-addresses", int64_t(1));

                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", lease->subnet_id_,
                                           "declined-addresses"),
                    int64_t(1));
            }
        }
    } else {
        // old lease is expired-reclaimed
        if (!lease->stateExpiredReclaimed()) {
            // new lease is non expired-reclaimed
            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", lease->subnet_id_,
                                       lease->type_ == Lease::TYPE_NA ?
                                       "assigned-nas" : "assigned-pds"),
                int64_t(1));
            if (lease->stateDeclined()) {
                // new lease is declined
                StatsMgr::instance().addValue("declined-addresses", int64_t(1));

                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", lease->subnet_id_,
                                           "declined-addresses"),
                    int64_t(1));
            }
        }
    }
}

void
LeaseCmdsImpl::updateStatsOnDelete(const Lease4Ptr& lease) {
    if (!lease->stateExpiredReclaimed()) {
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", lease->subnet_id_,
                                   "assigned-addresses"),
            int64_t(-1));
        if (lease->stateDeclined()) {
            StatsMgr::instance().addValue("declined-addresses", int64_t(-1));

            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", lease->subnet_id_,
                                       "declined-addresses"),
                int64_t(-1));
        }
    }
}

void
LeaseCmdsImpl::updateStatsOnDelete(const Lease6Ptr& lease) {
    if (!lease->stateExpiredReclaimed()) {
        StatsMgr::instance().addValue(
            StatsMgr::generateName("subnet", lease->subnet_id_,
                                   lease->type_ == Lease::TYPE_NA ?
                                   "assigned-nas" : "assigned-pds"),
            int64_t(-1));
        if (lease->stateDeclined()) {
            StatsMgr::instance().addValue("declined-addresses", int64_t(-1));

            StatsMgr::instance().addValue(
                StatsMgr::generateName("subnet", lease->subnet_id_,
                                       "declined-addresses"),
                int64_t(-1));
        }
    }
}

bool
LeaseCmdsImpl::addOrUpdate4(Lease4Ptr lease, bool force_create) {
    Lease4Ptr existing = LeaseMgrFactory::instance().getLease4(lease->addr_);
    if (force_create && !existing) {
        // lease does not exist
        if (!LeaseMgrFactory::instance().addLease(lease)) {
            isc_throw(LeaseCmdsConflict,
                      "lost race between calls to get and add");
        }
        LeaseCmdsImpl::updateStatsOnAdd(lease);
        return (true);
    }
    if (existing) {
        // Update lease current expiration time with value received from the
        // database. Some database backends reject operations on the lease if
        // the current expiration time value does not match what is stored.
        Lease::syncCurrentExpirationTime(*existing, *lease);
    }
    try {
        LeaseMgrFactory::instance().updateLease4(lease);
    } catch (const NoSuchLease&) {
        isc_throw(LeaseCmdsConflict, "failed to update the lease with address "
                  << lease->addr_ << " either because the lease has been "
                  "deleted or it has changed in the database, in both cases a "
                  "retry might succeed");
    }

    LeaseCmdsImpl::updateStatsOnUpdate(existing, lease);
    return (false);
}

bool
LeaseCmdsImpl::addOrUpdate6(Lease6Ptr lease, bool force_create) {
    Lease6Ptr existing =
        LeaseMgrFactory::instance().getLease6(lease->type_, lease->addr_);
    if (force_create && !existing) {
        // lease does not exist
        if (!LeaseMgrFactory::instance().addLease(lease)) {
            isc_throw(LeaseCmdsConflict,
                      "lost race between calls to get and add");
        }
        LeaseCmdsImpl::updateStatsOnAdd(lease);
        return (true);
    }
    if (existing) {
        // Update lease current expiration time with value received from the
        // database. Some database backends reject operations on the lease if
        // the current expiration time value does not match what is stored.
        Lease::syncCurrentExpirationTime(*existing, *lease);

        // Check what is the action about extended info.
        ConstElementPtr old_extended_info = getExtendedInfo6(existing);
        ConstElementPtr extended_info = getExtendedInfo6(lease);
        if ((!old_extended_info && !extended_info) ||
            (old_extended_info && extended_info &&
             (*old_extended_info == *extended_info))) {
            // Leave the default Lease6::ACTION_IGNORE.
        } else {
            lease->extended_info_action_ = Lease6::ACTION_UPDATE;
        }
    }
    try {
        LeaseMgrFactory::instance().updateLease6(lease);
    } catch (const NoSuchLease&) {
        isc_throw(LeaseCmdsConflict, "failed to update the lease with address "
                  << lease->addr_ << " either because the lease has been "
                  "deleted or it has changed in the database, in both cases a "
                  "retry might succeed");
    }

    LeaseCmdsImpl::updateStatsOnUpdate(existing, lease);
    return (false);
}

int
LeaseCmdsImpl::leaseAddHandler(CalloutHandle& handle) {
    // Arbitrary defaulting to DHCPv4 or with other words extractCommand
    // below is not expected to throw...
    bool v4 = true;
    stringstream resp;
    string lease_address = "unknown";
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-add");
        if (!cmd_args_) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();

        // This parameter is ignored for the commands adding the lease.
        bool force_create = false;
        Lease4Ptr lease4;
        Lease6Ptr lease6;
        if (v4) {
            Lease4Parser parser;
            lease4 = parser.parse(config, cmd_args_, force_create);
            if (lease4) {
                lease_address = lease4->addr_.toText();
                bool success;
                if (!MultiThreadingMgr::instance().getMode()) {
                    // Not multi-threading.
                    success = LeaseMgrFactory::instance().addLease(lease4);
                } else {
                    // Multi-threading, try to lock first to avoid a race.
                    ResourceHandler4 resource_handler;
                    if (resource_handler.tryLock4(lease4->addr_)) {
                        success = LeaseMgrFactory::instance().addLease(lease4);
                    } else {
                        isc_throw(LeaseCmdsConflict,
                                  "ResourceBusy: IP address:" << lease4->addr_
                                  << " could not be added.");
                    }
                }

                if (!success) {
                    isc_throw(LeaseCmdsConflict, "IPv4 lease already exists.");
                }

                LeaseCmdsImpl::updateStatsOnAdd(lease4);
                resp << "Lease for address " << lease4->addr_.toText()
                     << ", subnet-id " << lease4->subnet_id_ << " added.";
            }
        } else {
            Lease6Parser parser;
            lease6 = parser.parse(config, cmd_args_, force_create);
            if (lease6) {
                lease_address = lease6->addr_.toText();
                bool success;
                if (!MultiThreadingMgr::instance().getMode()) {
                    // Not multi-threading.
                    success = LeaseMgrFactory::instance().addLease(lease6);
                } else {
                    // Multi-threading, try to lock first to avoid a race.
                    ResourceHandler resource_handler;
                    if (resource_handler.tryLock(lease6->type_, lease6->addr_)) {
                        success = LeaseMgrFactory::instance().addLease(lease6);
                    } else {
                        isc_throw(LeaseCmdsConflict,
                                  "ResourceBusy: IP address:" << lease6->addr_
                                  << " could not be added.");
                    }
                }

                if (!success) {
                    isc_throw(LeaseCmdsConflict, "IPv6 lease already exists.");
                }

                LeaseCmdsImpl::updateStatsOnAdd(lease6);
                if (lease6->type_ == Lease::TYPE_NA) {
                    resp << "Lease for address " << lease6->addr_.toText()
                         << ", subnet-id " << lease6->subnet_id_ << " added.";
                } else {
                    resp << "Lease for prefix " << lease6->addr_.toText()
                         << "/" << static_cast<int>(lease6->prefixlen_)
                         << ", subnet-id " << lease6->subnet_id_ << " added.";
                }
            }
        }
    } catch (const LeaseCmdsConflict& ex) {
        LOG_WARN(lease_cmds_logger, v4 ? LEASE_CMDS_ADD4_CONFLICT : LEASE_CMDS_ADD6_CONFLICT)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what(), CONTROL_RESULT_CONFLICT);
        return (0);

    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, v4 ? LEASE_CMDS_ADD4_FAILED : LEASE_CMDS_ADD6_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA,
              v4 ? LEASE_CMDS_ADD4 : LEASE_CMDS_ADD6)
        .arg(lease_address);
    setSuccessResponse(handle, resp.str());
    return (0);
}

LeaseCmdsImpl::Parameters
LeaseCmdsImpl::getParameters(bool v6, const ConstElementPtr& params) {
    Parameters x;

    if (!params || params->getType() != Element::map) {
        isc_throw(BadValue, "Parameters missing or are not a map.");
    }

    if (params->contains("update-ddns")) {
        ConstElementPtr tmp = params->get("update-ddns");
        if (tmp->getType() != Element::boolean) {
            isc_throw(BadValue, "'update-ddns' is not a boolean");
        } else {
            x.updateDDNS = tmp->boolValue();
        }
    }

    // We support several sets of parameters for leaseX-get/lease-del:
    // lease-get(type, address)
    // lease-get(type, subnet-id, identifier-type, identifier)

    if (params->contains("type")) {
        string t = params->get("type")->stringValue();
        if (t == "IA_NA" || t == "0") {
            x.lease_type = Lease::TYPE_NA;
        } else if (t == "IA_TA" || t == "1") {
            x.lease_type = Lease::TYPE_TA;
        } else if (t == "IA_PD" || t == "2") {
            x.lease_type = Lease::TYPE_PD;
        } else if (t == "V4" || t == "3") {
            x.lease_type = Lease::TYPE_V4;
        } else {
            isc_throw(BadValue, "Invalid lease type specified: "
                      << t << ", only supported values are: IA_NA, IA_TA,"
                      << " IA_PD and V4");
        }
    }

    ConstElementPtr tmp = params->get("ip-address");
    if (tmp) {
        if (tmp->getType() != Element::string) {
            isc_throw(BadValue, "'ip-address' is not a string.");
        }

        x.addr = IOAddress(tmp->stringValue());

        if ((v6 && !x.addr.isV6()) || (!v6 && !x.addr.isV4())) {
            stringstream txt;
            txt << "Invalid " << (v6 ? "IPv6" : "IPv4")
                << " address specified: " << tmp->stringValue();
            isc_throw(BadValue, txt.str());
        }

        x.query_type = Parameters::TYPE_ADDR;
        return (x);
    }

    tmp = params->get("subnet-id");
    if (!tmp) {
        isc_throw(BadValue, "Mandatory 'subnet-id' parameter missing.");
    }
    if (tmp->getType() != Element::integer) {
        isc_throw(BadValue, "'subnet-id' parameter is not integer.");
    }
    x.subnet_id = tmp->intValue();

    if (params->contains("iaid")) {
        x.iaid = params->get("iaid")->intValue();
    }

    // No address specified. Ok, so it must be identifier based query.
    // "identifier-type": "duid",
    // "identifier": "aa:bb:cc:dd:ee:..."

    ConstElementPtr type = params->get("identifier-type");
    ConstElementPtr ident = params->get("identifier");
    if (!type || type->getType() != Element::string) {
        isc_throw(BadValue, "No 'ip-address' provided"
                  " and 'identifier-type' is either missing or not a string.");
    }
    if (!ident || ident->getType() != Element::string) {
        isc_throw(BadValue, "No 'ip-address' provided"
                  " and 'identifier' is either missing or not a string.");
    }

    // Got the parameters. Let's see if their values make sense.
    // Try to convert identifier-type
    x.query_type = Parameters::txtToType(type->stringValue());

    switch (x.query_type) {
    case Parameters::TYPE_HWADDR: {
        HWAddr hw = HWAddr::fromText(ident->stringValue());
        x.hwaddr = HWAddrPtr(new HWAddr(hw));
        break;
    }
    case Parameters::TYPE_CLIENT_ID: {
        x.client_id = ClientId::fromText(ident->stringValue());
        break;
    }
    case Parameters::TYPE_DUID: {
        DUID duid = DUID::fromText(ident->stringValue());
        x.duid = DuidPtr(new DUID(duid));
        break;
    }
    case Parameters::TYPE_ADDR: {
        // We should never get here. The address clause should have been caught
        // earlier.
        return (x);
    }
    default: {
        isc_throw(BadValue, "Identifier type " << type->stringValue() <<
                  " is not supported.");
    }
    }

    return (x);
}

int
LeaseCmdsImpl::leaseGetHandler(CalloutHandle& handle) {
    Parameters p;
    Lease4Ptr lease4;
    Lease6Ptr lease6;
    bool v4 = true;
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-get");
        p = getParameters(!v4, cmd_args_);
        switch (p.query_type) {
        case Parameters::TYPE_ADDR: {
            // Query by address
            if (v4) {
                lease4 = LeaseMgrFactory::instance().getLease4(p.addr);
            } else {
                lease6 = LeaseMgrFactory::instance().getLease6(p.lease_type, p.addr);
            }
            break;
        }
        case Parameters::TYPE_HWADDR:
            if (v4) {
                if (!p.hwaddr) {
                    isc_throw(InvalidParameter, "Program error: Query by hw-address "
                                                "requires hwaddr to be specified");
                }

                lease4 = LeaseMgrFactory::instance().getLease4(*p.hwaddr, p.subnet_id);
            } else {
                isc_throw(isc::InvalidParameter, "Query by hw-address is not allowed in v6.");
            }
            break;

        case Parameters::TYPE_DUID:
            if (!v4) {
                if (!p.duid) {
                    isc_throw(InvalidParameter, "Program error: Query by duid "
                                                "requires duid to be specified");
                }

                lease6 = LeaseMgrFactory::instance().getLease6(p.lease_type, *p.duid,
                                                               p.iaid, p.subnet_id);
            } else {
                isc_throw(InvalidParameter, "Query by duid is not allowed in v4.");
            }
            break;

        case Parameters::TYPE_CLIENT_ID:
            if (v4) {
                if (!p.client_id) {
                    isc_throw(InvalidParameter, "Program error: Query by client-id "
                                                "requires client-id to be specified");
                }

                lease4 = LeaseMgrFactory::instance().getLease4(*p.client_id, p.subnet_id);
            } else {
                isc_throw(isc::InvalidParameter, "Query by client-id is not allowed in v6.");
            }
            break;

        default: {
            isc_throw(InvalidOperation, "Unknown query type: " << static_cast<int>(p.query_type));
            break;
        }
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, v4 ? LEASE_CMDS_GET4_FAILED : LEASE_CMDS_GET6_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    ElementPtr lease_json;
    if (v4 && lease4) {
        lease_json = lease4->toElement();
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                "IPv4 lease found.", lease_json);
        setResponse(handle, response);
    } else if (!v4 && lease6) {
        lease_json = lease6->toElement();
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS,
                                                "IPv6 lease found.", lease_json);
        setResponse(handle, response);
    } else {
        // If we got here, the lease has not been found.
        setErrorResponse(handle, "Lease not found.", CONTROL_RESULT_EMPTY);
    }

    return (0);
}

int
LeaseCmdsImpl::leaseGetAllHandler(CalloutHandle& handle) {
    bool v4 = true;
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-get-all");

        ElementPtr leases_json = Element::createList();

        // The argument may contain a list of subnets for which leases should
        // be returned.
        if (cmd_args_) {
            ConstElementPtr subnets = cmd_args_->get("subnets");
            if (!subnets) {
                isc_throw(BadValue, "'subnets' parameter not specified");
            }
            if (subnets->getType() != Element::list) {
                isc_throw(BadValue, "'subnets' parameter must be a list");
            }

            const std::vector<ElementPtr>& subnet_ids = subnets->listValue();
            for (auto subnet_id = subnet_ids.begin();
                 subnet_id != subnet_ids.end();
                 ++subnet_id) {
                if ((*subnet_id)->getType() != Element::integer) {
                    isc_throw(BadValue, "listed subnet identifiers must be numbers");
                }

                if (v4) {
                    Lease4Collection leases =
                        LeaseMgrFactory::instance().getLeases4((*subnet_id)->intValue());
                    for (auto lease : leases) {
                        ElementPtr lease_json = lease->toElement();
                        leases_json->add(lease_json);
                    }
                } else {
                    Lease6Collection leases =
                        LeaseMgrFactory::instance().getLeases6((*subnet_id)->intValue());
                    for (auto lease : leases) {
                        ElementPtr lease_json = lease->toElement();
                        leases_json->add(lease_json);
                    }
                }
            }

        } else {
            // There is no 'subnets' argument so let's return all leases.
            if (v4) {
                Lease4Collection leases = LeaseMgrFactory::instance().getLeases4();
                for (auto lease : leases) {
                    ElementPtr lease_json = lease->toElement();
                    leases_json->add(lease_json);
                }
            } else {
                Lease6Collection leases = LeaseMgrFactory::instance().getLeases6();
                for (auto lease : leases) {
                    ElementPtr lease_json = lease->toElement();
                    leases_json->add(lease_json);
                }
            }
        }

        std::ostringstream s;
        s << leases_json->size()
          << " IPv" << (v4 ? "4" : "6")
          << " lease(s) found.";
        ElementPtr args = Element::createMap();
        args->set("leases", leases_json);
        ConstElementPtr response =
            createAnswer(leases_json->size() > 0 ?
                         CONTROL_RESULT_SUCCESS :
                         CONTROL_RESULT_EMPTY,
                         s.str(), args);
        setResponse(handle, response);

    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (0);
}

int
LeaseCmdsImpl::leaseGetPageHandler(CalloutHandle& handle) {
    bool v4 = true;
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-get-page");

        // arguments must always be present
        if (!cmd_args_) {
            isc_throw(BadValue, "no parameters specified for the " << cmd_name_
                      << " command");
        }

        // The 'from' argument denotes from which lease we should start the
        // results page. The results page excludes this lease.
        ConstElementPtr from = cmd_args_->get("from");
        if (!from) {
            isc_throw(BadValue, "'from' parameter not specified");
        }

        // The 'from' argument is a string. It may contain a 'start' keyword or
        // an IP address.
        if (from->getType() != Element::string) {
            isc_throw(BadValue, "'from' parameter must be a string");
        }

        boost::scoped_ptr<IOAddress> from_address;
        try {
            if (from->stringValue() == "start") {
                from_address.reset(new IOAddress(v4 ? "0.0.0.0" : "::"));

            } else {
                // Conversion of a string to an IP address may throw.
                from_address.reset(new IOAddress(from->stringValue()));
            }

        } catch (...) {
            isc_throw(BadValue, "'from' parameter value is neither 'start' keyword nor "
                      "a valid IPv" << (v4 ? "4" : "6") << " address");
        }

        // It must be either IPv4 address for lease4-get-page or IPv6 address for
        // lease6-get-page.
        if (v4 && (!from_address->isV4())) {
            isc_throw(BadValue, "'from' parameter value " << from_address->toText()
                      << " is not an IPv4 address");

        } else if (!v4 && from_address->isV4()) {
            isc_throw(BadValue, "'from' parameter value " << from_address->toText()
                      << " is not an IPv6 address");
        }

        // The 'limit' is a desired page size. It must always be present.
        ConstElementPtr page_limit = cmd_args_->get("limit");
        if (!page_limit) {
            isc_throw(BadValue, "'limit' parameter not specified");
        }

        // The 'limit' must be a number.
        if (page_limit->getType() != Element::integer) {
            isc_throw(BadValue, "'limit' parameter must be a number");
        }

        // Retrieve the desired page size.
        size_t page_limit_value = static_cast<size_t>(page_limit->intValue());

        ElementPtr leases_json = Element::createList();

        if (v4) {
            // Get page of IPv4 leases.
            Lease4Collection leases =
                LeaseMgrFactory::instance().getLeases4(*from_address,
                                                       LeasePageSize(page_limit_value));

            // Convert leases into JSON list.
            for (auto lease : leases) {
                ElementPtr lease_json = lease->toElement();
                leases_json->add(lease_json);
            }

        } else {
            // Get page of IPv6 leases.
            Lease6Collection leases =
                LeaseMgrFactory::instance().getLeases6(*from_address,
                                                       LeasePageSize(page_limit_value));
            // Convert leases into JSON list.
            for (auto lease : leases) {
                ElementPtr lease_json = lease->toElement();
                leases_json->add(lease_json);
            }
        }

        // Prepare textual status.
        std::ostringstream s;
        s << leases_json->size()
          << " IPv" << (v4 ? "4" : "6")
          << " lease(s) found.";
        ElementPtr args = Element::createMap();

        // Put gathered data into arguments map.
        args->set("leases", leases_json);
        args->set("count", Element::create(static_cast<int64_t>(leases_json->size())));

        // Create the response.
        ConstElementPtr response =
            createAnswer(leases_json->size() > 0 ?
                         CONTROL_RESULT_SUCCESS :
                         CONTROL_RESULT_EMPTY,
                         s.str(), args);
        setResponse(handle, response);

    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

int
LeaseCmdsImpl::leaseGetByHwAddressHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        // arguments must always be present
        if (!cmd_args_ || (cmd_args_->getType() != Element::map)) {
            isc_throw(BadValue, "Command arguments missing or a not a map.");
        }

        // the hw-address parameter is mandatory.
        ConstElementPtr hw_address = cmd_args_->get("hw-address");
        if (!hw_address) {
            isc_throw(BadValue, "'hw-address' parameter not specified");
        }

        // The 'hw-address' argument is a string.
        if (hw_address->getType() != Element::string) {
            isc_throw(BadValue, "'hw-address' parameter must be a string");
        }

        HWAddr hwaddr = HWAddr::fromText(hw_address->stringValue());

        Lease4Collection leases =
            LeaseMgrFactory::instance().getLease4(hwaddr);
        ElementPtr leases_json = Element::createList();
        for (auto lease : leases) {
            ElementPtr lease_json = lease->toElement();
            leases_json->add(lease_json);
        }

        std::ostringstream s;
        s << leases_json->size() << " IPv4 lease(s) found.";
        ElementPtr args = Element::createMap();
        args->set("leases", leases_json);
        ConstElementPtr response =
            createAnswer(leases_json->size() > 0 ?
                         CONTROL_RESULT_SUCCESS :
                         CONTROL_RESULT_EMPTY,
                         s.str(), args);
        setResponse(handle, response);

    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (0);
}

int
LeaseCmdsImpl::leaseGetByClientIdHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        // arguments must always be present
        if (!cmd_args_ || (cmd_args_->getType() != Element::map)) {
            isc_throw(BadValue, "Command arguments missing or a not a map.");
        }

        // the client-id parameter is mandatory.
        ConstElementPtr client_id = cmd_args_->get("client-id");
        if (!client_id) {
            isc_throw(BadValue, "'client-id' parameter not specified");
        }

        // The 'client-id' argument is a string.
        if (client_id->getType() != Element::string) {
            isc_throw(BadValue, "'client-id' parameter must be a string");
        }

        ClientIdPtr clientid = ClientId::fromText(client_id->stringValue());

        Lease4Collection leases =
            LeaseMgrFactory::instance().getLease4(*clientid);
        ElementPtr leases_json = Element::createList();
        for (auto lease : leases) {
            ElementPtr lease_json = lease->toElement();
            leases_json->add(lease_json);
        }

        std::ostringstream s;
        s << leases_json->size() << " IPv4 lease(s) found.";
        ElementPtr args = Element::createMap();
        args->set("leases", leases_json);
        ConstElementPtr response =
            createAnswer(leases_json->size() > 0 ?
                         CONTROL_RESULT_SUCCESS :
                         CONTROL_RESULT_EMPTY,
                         s.str(), args);
        setResponse(handle, response);

    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (0);
}

int
LeaseCmdsImpl::leaseGetByDuidHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        // arguments must always be present
        if (!cmd_args_ || (cmd_args_->getType() != Element::map)) {
            isc_throw(BadValue, "Command arguments missing or a not a map.");
        }

        // the duid parameter is mandatory.
        ConstElementPtr duid = cmd_args_->get("duid");
        if (!duid) {
            isc_throw(BadValue, "'duid' parameter not specified");
        }

        // The 'duid' argument is a string.
        if (duid->getType() != Element::string) {
            isc_throw(BadValue, "'duid' parameter must be a string");
        }

        DUID duid_ = DUID::fromText(duid->stringValue());

        Lease6Collection leases =
            LeaseMgrFactory::instance().getLeases6(duid_);
        ElementPtr leases_json = Element::createList();
        for (auto lease : leases) {
            ElementPtr lease_json = lease->toElement();
            leases_json->add(lease_json);
        }

        std::ostringstream s;
        s << leases_json->size() << " IPv6 lease(s) found.";
        ElementPtr args = Element::createMap();
        args->set("leases", leases_json);
        ConstElementPtr response =
            createAnswer(leases_json->size() > 0 ?
                         CONTROL_RESULT_SUCCESS :
                         CONTROL_RESULT_EMPTY,
                         s.str(), args);
        setResponse(handle, response);

    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (0);
}

int
LeaseCmdsImpl::leaseGetByHostnameHandler(CalloutHandle& handle) {
    bool v4 = true;
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-get-by-hostname");

        // arguments must always be present
        if (!cmd_args_ || (cmd_args_->getType() != Element::map)) {
            isc_throw(BadValue, "Command arguments missing or a not a map.");
        }

        // the hostname parameter is mandatory.
        ConstElementPtr hostname = cmd_args_->get("hostname");
        if (!hostname) {
            isc_throw(BadValue, "'hostname' parameter not specified");
        }

        // The 'hostname' argument is a string.
        if (hostname->getType() != Element::string) {
            isc_throw(BadValue, "'hostname' parameter must be a string");
        }

        std::string hostname_ = hostname->stringValue();
        /// The 'hostname' argument should not be empty.
        if (hostname_.empty()) {
            isc_throw(BadValue, "'hostname' parameter is empty");
        }
        boost::algorithm::to_lower(hostname_);

        ElementPtr leases_json = Element::createList();
        if (v4) {
            Lease4Collection leases =
                LeaseMgrFactory::instance().getLeases4(hostname_);

            for (auto lease : leases) {
                ElementPtr lease_json = lease->toElement();
                leases_json->add(lease_json);
            }
        } else {
            Lease6Collection leases =
                LeaseMgrFactory::instance().getLeases6(hostname_);

            for (auto lease : leases) {
                ElementPtr lease_json = lease->toElement();
                leases_json->add(lease_json);
            }
        }

        std::ostringstream s;
        s << leases_json->size()
          << " IPv" << (v4 ? "4" : "6")
          << " lease(s) found.";
        ElementPtr args = Element::createMap();
        args->set("leases", leases_json);
        ConstElementPtr response =
            createAnswer(leases_json->size() > 0 ?
                         CONTROL_RESULT_SUCCESS :
                         CONTROL_RESULT_EMPTY,
                         s.str(), args);
        setResponse(handle, response);

    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (0);
}

int
LeaseCmdsImpl::lease4DelHandler(CalloutHandle& handle) {
    Parameters p;
    Lease4Ptr lease4;
    try {
        extractCommand(handle);
        p = getParameters(false, cmd_args_);
        switch (p.query_type) {
        case Parameters::TYPE_ADDR: {
            // If address was specified explicitly, let's use it as is.
            lease4 = LeaseMgrFactory::instance().getLease4(p.addr);
            if (!lease4) {
                setErrorResponse(handle, "IPv4 lease not found.", CONTROL_RESULT_EMPTY);
                return (0);
            }
            break;
        }
        case Parameters::TYPE_HWADDR: {
            if (!p.hwaddr) {
                isc_throw(InvalidParameter, "Program error: Query by hw-address "
                                            "requires hwaddr to be specified");
            }

            // Let's see if there's such a lease at all.
            lease4 = LeaseMgrFactory::instance().getLease4(*p.hwaddr, p.subnet_id);
            if (!lease4) {
                setErrorResponse(handle, "IPv4 lease not found.", CONTROL_RESULT_EMPTY);
                return (0);
            }
            break;
        }
        case Parameters::TYPE_CLIENT_ID: {
            if (!p.client_id) {
                isc_throw(InvalidParameter, "Program error: Query by client-id "
                                            "requires client-id to be specified");
            }

            // Let's see if there's such a lease at all.
            lease4 = LeaseMgrFactory::instance().getLease4(*p.client_id, p.subnet_id);
            if (!lease4) {
                setErrorResponse(handle, "IPv4 lease not found.", CONTROL_RESULT_EMPTY);
                return (0);
            }
            break;
        }
        case Parameters::TYPE_DUID: {
            isc_throw(InvalidParameter, "Delete by duid is not allowed in v4.");
            break;
        }
        default: {
            isc_throw(InvalidOperation, "Unknown query type: " << static_cast<int>(p.query_type));
            break;
        }
        }

        if (LeaseMgrFactory::instance().deleteLease(lease4)) {
            setSuccessResponse(handle, "IPv4 lease deleted.");
            LeaseCmdsImpl::updateStatsOnDelete(lease4);
        } else {
            setErrorResponse (handle, "IPv4 lease not found.", CONTROL_RESULT_EMPTY);
        }

        // Queue an NCR to remove DNS if configured and the lease has it.
        if (p.updateDDNS) {
            queueNCR(CHG_REMOVE, lease4);
        }

    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, LEASE_CMDS_DEL4_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }
    LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA, LEASE_CMDS_DEL4)
        .arg(lease4->addr_.toText());
    return (0);
}

int
LeaseCmdsImpl::lease6BulkApplyHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        // Arguments are mandatory.
        if (!cmd_args_ || (cmd_args_->getType() != Element::map)) {
            isc_throw(BadValue, "Command arguments missing or a not a map.");
        }

        // At least one of the 'deleted-leases' or 'leases' must be present.
        auto deleted_leases = cmd_args_->get("deleted-leases");
        auto leases = cmd_args_->get("leases");

        if (!deleted_leases && !leases) {
            isc_throw(BadValue, "neither 'deleted-leases' nor 'leases' parameter"
                      " specified");
        }

        // Make sure that 'deleted-leases' is a list, if present.
        if (deleted_leases && (deleted_leases->getType() != Element::list)) {
            isc_throw(BadValue, "the 'deleted-leases' parameter must be a list");
        }

        // Make sure that 'leases' is a list, if present.
        if (leases && (leases->getType() != Element::list)) {
            isc_throw(BadValue, "the 'leases' parameter must be a list");
        }

        // Parse deleted leases without deleting them from the database
        // yet. If any of the deleted leases or new leases appears to be
        // malformed we can easily rollback.
        std::list<std::pair<Parameters, Lease6Ptr> > parsed_deleted_list;
        if (deleted_leases) {
            auto leases_list = deleted_leases->listValue();

            // Iterate over leases to be deleted.
            for (auto lease_params : leases_list) {
                // Parsing the lease may throw and it means that the lease
                // information is malformed.
                Parameters p = getParameters(true, lease_params);
                auto lease = getIPv6LeaseForDelete(p);
                parsed_deleted_list.push_back(std::make_pair(p, lease));
            }
        }

        // Parse new/updated leases without affecting the database to detect
        // any errors that should cause an error response.
        std::list<Lease6Ptr> parsed_leases_list;
        if (leases) {
            ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();

            // Iterate over all leases.
            auto leases_list = leases->listValue();
            for (auto lease_params : leases_list) {

                Lease6Parser parser;
                bool force_update;

                // If parsing the lease fails we throw, as it indicates that the
                // command is malformed.
                Lease6Ptr lease6 = parser.parse(config, lease_params, force_update);
                parsed_leases_list.push_back(lease6);
            }
        }

        // Count successful deletions and updates.
        size_t success_count = 0;

        ElementPtr failed_deleted_list;
        if (!parsed_deleted_list.empty()) {

            // Iterate over leases to be deleted.
            for (auto lease_params_pair : parsed_deleted_list) {

                // This part is outside of the try-catch because an exception
                // indicates that the command is malformed.
                Parameters p = lease_params_pair.first;
                auto lease = lease_params_pair.second;

                try {
                    if (lease) {
                        // This may throw if the lease couldn't be deleted for
                        // any reason, but we still want to proceed with other
                        // leases.
                        if (LeaseMgrFactory::instance().deleteLease(lease)) {
                            ++success_count;
                            LeaseCmdsImpl::updateStatsOnDelete(lease);

                        } else {
                            // Lazy creation of the list of leases which failed to delete.
                            if (!failed_deleted_list) {
                                failed_deleted_list = Element::createList();
                            }

                            // If the lease doesn't exist we also want to put it
                            // on the list of leases which failed to delete. That
                            // corresponds to the lease6-del command which returns
                            // an error when the lease doesn't exist.
                            failed_deleted_list->add(createFailedLeaseMap(p.lease_type,
                                                                          p.addr, p.duid,
                                                                          CONTROL_RESULT_EMPTY,
                                                                          "lease not found"));
                        }
                    }

                } catch (const std::exception& ex) {
                    // Lazy creation of the list of leases which failed to delete.
                    if (!failed_deleted_list) {
                         failed_deleted_list = Element::createList();
                    }
                    failed_deleted_list->add(createFailedLeaseMap(p.lease_type,
                                                                  p.addr, p.duid,
                                                                  CONTROL_RESULT_ERROR,
                                                                  ex.what()));
                }
            }
        }

        // Process leases to be added or/and updated.
        ElementPtr failed_leases_list;
        if (!parsed_leases_list.empty()) {
            ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();

            // Iterate over all leases.
            for (auto lease : parsed_leases_list) {

                auto result = CONTROL_RESULT_SUCCESS;
                std::ostringstream text;
                try {
                    if (!MultiThreadingMgr::instance().getMode()) {
                        // Not multi-threading.
                        addOrUpdate6(lease, true);
                    } else {
                        // Multi-threading, try to lock first to avoid a race.
                        ResourceHandler resource_handler;
                        if (resource_handler.tryLock(lease->type_, lease->addr_)) {
                            addOrUpdate6(lease, true);
                        } else {
                            isc_throw(LeaseCmdsConflict,
                                      "ResourceBusy: IP address:" << lease->addr_
                                      << " could not be updated.");
                        }
                    }

                    ++success_count;
                } catch (const LeaseCmdsConflict& ex) {
                    result = CONTROL_RESULT_CONFLICT;
                    text << ex.what();

                } catch (const std::exception& ex) {
                    result = CONTROL_RESULT_ERROR;
                    text << ex.what();
                }
                // Handle an error.
                if (result != CONTROL_RESULT_SUCCESS) {
                    // Lazy creation of the list of leases which failed to add/update.
                    if (!failed_leases_list) {
                        failed_leases_list = Element::createList();
                    }
                    failed_leases_list->add(createFailedLeaseMap(lease->type_,
                                                                 lease->addr_,
                                                                 lease->duid_,
                                                                 result,
                                                                 text.str()));
                }
            }
        }

        // Start preparing the response.
        ElementPtr args;

        if (failed_deleted_list || failed_leases_list) {
            // If there are any failed leases, let's include them in the response.
            args = Element::createMap();

            // failed-deleted-leases
            if (failed_deleted_list) {
                args->set("failed-deleted-leases", failed_deleted_list);
            }

            // failed-leases
            if (failed_leases_list) {
                args->set("failed-leases", failed_leases_list);
            }
        }

        // Send the success response and include failed leases.
        std::ostringstream resp_text;
        resp_text << "Bulk apply of " << success_count << " IPv6 leases completed.";
        auto answer = createAnswer(success_count > 0 ? CONTROL_RESULT_SUCCESS :
                                   CONTROL_RESULT_EMPTY, resp_text.str(), args);
        setResponse(handle, answer);

        LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA,
                  LEASE_CMDS_BULK_APPLY6)
            .arg(success_count);

    } catch (const std::exception& ex) {
        // Unable to parse the command and similar issues.
        LOG_ERROR(lease_cmds_logger, LEASE_CMDS_BULK_APPLY6_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (0);
}

int
LeaseCmdsImpl::lease6DelHandler(CalloutHandle& handle) {
    Parameters p;
    Lease6Ptr lease6;
    IOAddress addr(IOAddress::IPV6_ZERO_ADDRESS());
    try {
        extractCommand(handle);
        p = getParameters(true, cmd_args_);

        switch (p.query_type) {
        case Parameters::TYPE_ADDR: {
            // If address was specified explicitly, let's use it as is.

            // Let's see if there's such a lease at all.
            lease6 = LeaseMgrFactory::instance().getLease6(p.lease_type, p.addr);
            if (!lease6) {
                setErrorResponse(handle, "IPv6 lease not found.", CONTROL_RESULT_EMPTY);
                return (0);
            }
            break;
        }
        case Parameters::TYPE_HWADDR: {
            isc_throw(InvalidParameter, "Delete by hw-address is not allowed in v6.");
            break;
        }
        case Parameters::TYPE_DUID: {
            if (!p.duid) {
                isc_throw(InvalidParameter, "Program error: Query by duid "
                                            "requires duid to be specified");
            }

            // Let's see if there's such a lease at all.
            lease6 = LeaseMgrFactory::instance().getLease6(p.lease_type, *p.duid,
                                                           p.iaid, p.subnet_id);
            if (!lease6) {
                setErrorResponse(handle, "IPv6 lease not found.", CONTROL_RESULT_EMPTY);
                return (0);
            }
            break;
        }
        default: {
            isc_throw(InvalidOperation, "Unknown query type: " << static_cast<int>(p.query_type));
            break;
        }
        }

        if (LeaseMgrFactory::instance().deleteLease(lease6)) {
            setSuccessResponse(handle, "IPv6 lease deleted.");
            LeaseCmdsImpl::updateStatsOnDelete(lease6);
        } else {
            setErrorResponse (handle, "IPv6 lease not found.", CONTROL_RESULT_EMPTY);
        }

        // Queue an NCR to remove DNS if configured and the lease has it.
        if (p.updateDDNS) {
            queueNCR(CHG_REMOVE, lease6);
        }

    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, LEASE_CMDS_DEL6_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA, LEASE_CMDS_DEL6)
        .arg(lease6->addr_.toText());
    return (0);
}

int
LeaseCmdsImpl::lease4UpdateHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        // We need the lease to be specified.
        if (!cmd_args_) {
            isc_throw(isc::BadValue, "no parameters specified for lease4-update command");
        }

        // Get the parameters specified by the user first.
        ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
        Lease4Ptr lease4;
        Lease4Parser parser;
        bool force_create = false;

        // The parser does sanity checks (if the address is in scope, if
        // subnet-id is valid, etc)
        lease4 = parser.parse(config, cmd_args_, force_create);
        bool added = false;
        if (!MultiThreadingMgr::instance().getMode()) {
            // Not multi-threading.
            added = addOrUpdate4(lease4, force_create);
        } else {
            // Multi-threading, try to lock first to avoid a race.
            ResourceHandler4 resource_handler;
            if (resource_handler.tryLock4(lease4->addr_)) {
                added = addOrUpdate4(lease4, force_create);
            } else {
                isc_throw(LeaseCmdsConflict,
                          "ResourceBusy: IP address:" << lease4->addr_
                          << " could not be updated.");
            }
        }

        if (added) {
            setSuccessResponse(handle, "IPv4 lease added.");
        } else {
            setSuccessResponse(handle, "IPv4 lease updated.");
        }
        LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA,
                  LEASE_CMDS_UPDATE4)
            .arg(lease4->addr_.toText());

    } catch (const LeaseCmdsConflict& ex) {
        LOG_WARN(lease_cmds_logger, LEASE_CMDS_UPDATE4_CONFLICT)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what(), CONTROL_RESULT_CONFLICT);
        return (0);

    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, LEASE_CMDS_UPDATE4_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
LeaseCmdsImpl::lease6UpdateHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        // We need the lease to be specified.
        if (!cmd_args_) {
            isc_throw(isc::BadValue, "no parameters specified for lease6-update command");
        }

        // Get the parameters specified by the user first.
        ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
        Lease6Ptr lease6;
        Lease6Parser parser;
        bool force_create = false;

        // The parser does sanity checks (if the address is in scope, if
        // subnet-id is valid, etc)
        lease6 = parser.parse(config, cmd_args_, force_create);
        bool added = false;
        if (!MultiThreadingMgr::instance().getMode()) {
            // Not multi-threading.
            added = addOrUpdate6(lease6, force_create);
        } else {
            // Multi-threading, try to lock first to avoid a race.
            ResourceHandler resource_handler;
            if (resource_handler.tryLock(lease6->type_, lease6->addr_)) {
                added = addOrUpdate6(lease6, force_create);
            } else {
                isc_throw(LeaseCmdsConflict,
                          "ResourceBusy: IP address:" << lease6->addr_
                          << " could not be updated.");
            }
        }

        if (added) {
            setSuccessResponse(handle, "IPv6 lease added.");
        } else {
            setSuccessResponse(handle, "IPv6 lease updated.");
        }
        LOG_DEBUG(lease_cmds_logger, LEASE_CMDS_DBG_COMMAND_DATA,
                  LEASE_CMDS_UPDATE6)
            .arg(lease6->addr_.toText());

    } catch (const LeaseCmdsConflict& ex) {
        LOG_WARN(lease_cmds_logger, LEASE_CMDS_UPDATE6_CONFLICT)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what(), CONTROL_RESULT_CONFLICT);
        return (0);

    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, LEASE_CMDS_UPDATE6_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    return (0);
}

int
LeaseCmdsImpl::lease4WipeHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        SimpleParser parser;
        SubnetID id = 0;

        size_t num = 0; // number of leases deleted
        stringstream ids; // a text with subnet-ids being wiped

        // The subnet-id parameter is now optional.
        if (cmd_args_ && cmd_args_->contains("subnet-id")) {
            id = parser.getUint32(cmd_args_, "subnet-id");
        }

        if (id) {
            // Wipe a single subnet.
            num = LeaseMgrFactory::instance().wipeLeases4(id);
            ids << " " << id;

            auto observation = StatsMgr::instance().getObservation(
                StatsMgr::generateName("subnet", id, "declined-addresses"));

            int64_t previous_declined = 0;

            if (observation) {
                previous_declined = observation->getInteger().first;
            }

            StatsMgr::instance().setValue(
                StatsMgr::generateName("subnet", id, "assigned-addresses"),
                int64_t(0));

            StatsMgr::instance().setValue(
                StatsMgr::generateName("subnet", id, "declined-addresses"),
                int64_t(0));

            StatsMgr::instance().addValue("declined-addresses", -previous_declined);
        } else {
            // Wipe them all!
            ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
            ConstCfgSubnets4Ptr subnets = config->getCfgSubnets4();
            const Subnet4Collection * subs = subnets->getAll();

            // Go over all subnets and wipe leases in each of them.
            for (auto sub : *subs) {
                num += LeaseMgrFactory::instance().wipeLeases4(sub->getID());
                ids << " " << sub->getID();
                StatsMgr::instance().setValue(
                    StatsMgr::generateName("subnet", sub->getID(), "assigned-addresses"),
                    int64_t(0));

                StatsMgr::instance().setValue(
                    StatsMgr::generateName("subnet", sub->getID(), "declined-addresses"),
                    int64_t(0));
            }

            StatsMgr::instance().setValue("declined-addresses", int64_t(0));
        }

        stringstream tmp;
        tmp << "Deleted " << num << " IPv4 lease(s) from subnet(s)" << ids.str();
        ConstElementPtr response = createAnswer(num ? CONTROL_RESULT_SUCCESS
                                                    : CONTROL_RESULT_EMPTY, tmp.str());
        setResponse(handle, response);
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, LEASE_CMDS_WIPE4_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(lease_cmds_logger, LEASE_CMDS_WIPE4)
        .arg(cmd_args_ ? cmd_args_->str() : "<no args>");
    return (0);
}

int
LeaseCmdsImpl::lease6WipeHandler(CalloutHandle& handle) {
    try {
        extractCommand(handle);

        SimpleParser parser;
        SubnetID id = 0;

        size_t num = 0; // number of leases deleted
        stringstream ids; // a text with subnet-ids being wiped

        /// @todo: consider extending the code with wipe-leases:
        /// - of specific type (v6)
        /// - from specific shared network
        /// - from specific pool
        /// see https://oldkea.isc.org/ticket/5543#comment:6 for background.

        // The subnet-id parameter is now optional.
        if (cmd_args_ && cmd_args_->contains("subnet-id")) {
            id = parser.getUint32(cmd_args_, "subnet-id");
        }

        if (id) {
            // Wipe a single subnet.
            num = LeaseMgrFactory::instance().wipeLeases6(id);
            ids << " " << id;

            auto observation = StatsMgr::instance().getObservation(
                StatsMgr::generateName("subnet", id, "declined-addresses"));

            int64_t previous_declined = 0;

            if (observation) {
                previous_declined = observation->getInteger().first;
            }

            StatsMgr::instance().setValue(
                StatsMgr::generateName("subnet", id, "assigned-nas" ),
                int64_t(0));

            StatsMgr::instance().setValue(
                StatsMgr::generateName("subnet", id, "assigned-pds"),
                int64_t(0));

            StatsMgr::instance().setValue(
                StatsMgr::generateName("subnet", id, "declined-addresses"),
                int64_t(0));

            StatsMgr::instance().addValue("declined-addresses", -previous_declined);
       } else {
            // Wipe them all!
            ConstSrvConfigPtr config = CfgMgr::instance().getCurrentCfg();
            ConstCfgSubnets6Ptr subnets = config->getCfgSubnets6();
            const Subnet6Collection * subs = subnets->getAll();

            // Go over all subnets and wipe leases in each of them.
            for (auto sub : *subs) {
                num += LeaseMgrFactory::instance().wipeLeases6(sub->getID());
                ids << " " << sub->getID();
                StatsMgr::instance().setValue(
                    StatsMgr::generateName("subnet", sub->getID(), "assigned-nas" ),
                    int64_t(0));

                StatsMgr::instance().setValue(
                    StatsMgr::generateName("subnet", sub->getID(), "assigned-pds"),
                    int64_t(0));

                StatsMgr::instance().setValue(
                    StatsMgr::generateName("subnet", sub->getID(), "declined-addresses"),
                    int64_t(0));
            }

            StatsMgr::instance().setValue("declined-addresses", int64_t(0));
        }

        stringstream tmp;
        tmp << "Deleted " << num << " IPv6 lease(s) from subnet(s)" << ids.str();
        ConstElementPtr response = createAnswer(num ? CONTROL_RESULT_SUCCESS
                                                    : CONTROL_RESULT_EMPTY, tmp.str());
        setResponse(handle, response);
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_cmds_logger, LEASE_CMDS_WIPE6_FAILED)
            .arg(cmd_args_ ? cmd_args_->str() : "<no args>")
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(lease_cmds_logger, LEASE_CMDS_WIPE6)
        .arg(cmd_args_ ? cmd_args_->str() : "<no args>");
    return (0);
}

Lease6Ptr
LeaseCmdsImpl::getIPv6LeaseForDelete(const Parameters& parameters) const {
    Lease6Ptr lease6;

    switch (parameters.query_type) {
    case Parameters::TYPE_ADDR: {
        // If address was specified explicitly, let's use it as is.

        // Let's see if there's such a lease at all.
        lease6 = LeaseMgrFactory::instance().getLease6(parameters.lease_type,
                                                       parameters.addr);
        if (!lease6) {
            lease6.reset(new Lease6());
            lease6->addr_ = parameters.addr;
        }
        break;
    }
    case Parameters::TYPE_HWADDR: {
        isc_throw(InvalidParameter, "Delete by hw-address is not allowed in v6.");
        break;
    }
    case Parameters::TYPE_DUID: {
        if (!parameters.duid) {
            isc_throw(InvalidParameter, "Program error: Query by duid "
                      "requires duid to be specified");
        }

        // Let's see if there's such a lease at all.
        lease6 = LeaseMgrFactory::instance().getLease6(parameters.lease_type,
                                                       *parameters.duid,
                                                       parameters.iaid,
                                                       parameters.subnet_id);
        break;
    }
    default:
        isc_throw(InvalidOperation, "Unknown query type: "
                  << static_cast<int>(parameters.query_type));
    }

    return (lease6);
}

IOAddress
LeaseCmdsImpl::getAddressParam(ConstElementPtr params, const std::string name,
                               short family) const {
    ConstElementPtr param = params->get(name);
    if (!param) {
        isc_throw(BadValue, "'" << name << "' parameter is missing.");
    }

    if (param->getType() != Element::string) {
        isc_throw(BadValue, "'" << name << "' is not a string.");
    }

    IOAddress addr(0);
    try {
        addr = IOAddress(param->stringValue());
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "'" << param->stringValue()
                                << "' is not a valid IP address.");
    }

    if (addr.getFamily() != family) {
        isc_throw(BadValue, "Invalid "
                  << (family == AF_INET6 ? "IPv6" : "IPv4")
                  << " address specified: " << param->stringValue());
    }

    return (addr);
}

int
LeaseCmdsImpl::lease4ResendDdnsHandler(CalloutHandle& handle) {
    std::stringstream ss;
    int resp_code = CONTROL_RESULT_ERROR;

    try {
        extractCommand(handle);

        // Get the target lease address. Invalid value will throw.
        IOAddress addr = getAddressParam(cmd_args_, "ip-address", AF_INET);

        if (!CfgMgr::instance().getD2ClientMgr().ddnsEnabled()) {
            ss << "DDNS updating is not enabled";
            resp_code = CONTROL_RESULT_CONFLICT;
        } else {
            // Find the lease.
            Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(addr);
            if (!lease) {
                ss << "No lease found for: " << addr.toText();
                resp_code = CONTROL_RESULT_EMPTY;
            } else if (lease->hostname_.empty()) {
                ss << "Lease for: " << addr.toText()
                   << ", has no hostname, nothing to update";
                resp_code = CONTROL_RESULT_CONFLICT;
            } else if (!lease->fqdn_fwd_ && !lease->fqdn_rev_) {
                ss << "Neither forward nor reverse updates enabled for lease for: "
                   << addr.toText();
                resp_code = CONTROL_RESULT_CONFLICT;
            } else {
                // We have a lease with a hostname and updates in at least
                // one direction enabled.  Queue an NCR for it.
                queueNCR(CHG_ADD, lease);
                ss << "NCR generated for: " << addr.toText()
                   << ", hostname: " << lease->hostname_;
                setSuccessResponse(handle, ss.str());
                LOG_INFO(lease_cmds_logger, LEASE_CMDS_RESEND_DDNS4).arg(ss.str());
                return (0);
            }
        }
    } catch (const std::exception& ex) {
        ss << ex.what();
    }

    LOG_ERROR(lease_cmds_logger, LEASE_CMDS_RESEND_DDNS4_FAILED).arg(ss.str());
    setErrorResponse(handle, ss.str(), resp_code);
    return (resp_code == CONTROL_RESULT_EMPTY || resp_code == CONTROL_RESULT_CONFLICT ? 0 : 1);
}

int
LeaseCmdsImpl::lease6ResendDdnsHandler(CalloutHandle& handle) {
    std::stringstream ss;
    int resp_code = CONTROL_RESULT_ERROR;

    try {
        extractCommand(handle);

        // Get the target lease address. Invalid value will throw.
        IOAddress addr = getAddressParam(cmd_args_, "ip-address", AF_INET6);

        if (!CfgMgr::instance().getD2ClientMgr().ddnsEnabled()) {
            ss << "DDNS updating is not enabled";
            resp_code = CONTROL_RESULT_CONFLICT;
        } else {
            // Find the lease.
            Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
            if (!lease) {
                ss << "No lease found for: " << addr.toText();
                resp_code = CONTROL_RESULT_EMPTY;
            } else if (lease->hostname_.empty()) {
                ss << "Lease for: " << addr.toText()
                   << ", has no hostname, nothing to update";
                resp_code = CONTROL_RESULT_CONFLICT;
            } else if (!lease->fqdn_fwd_ && !lease->fqdn_rev_) {
                ss << "Neither forward nor reverse updates enabled for lease for: "
                   << addr.toText();
                resp_code = CONTROL_RESULT_CONFLICT;
            } else {
                // We have a lease with a hostname and updates in at least
                // one direction enabled.  Queue an NCR for it.
                queueNCR(CHG_ADD, lease);
                ss << "NCR generated for: " << addr.toText()
                   << ", hostname: " << lease->hostname_;
                setSuccessResponse(handle, ss.str());
                LOG_INFO(lease_cmds_logger, LEASE_CMDS_RESEND_DDNS6).arg(ss.str());
                return (0);
            }
        }
    } catch (const std::exception& ex) {
        ss << ex.what();
    }

    LOG_ERROR(lease_cmds_logger, LEASE_CMDS_RESEND_DDNS6_FAILED).arg(ss.str());
    setErrorResponse(handle, ss.str(), resp_code);
    return (resp_code == CONTROL_RESULT_EMPTY ? 0 : 1);
}

ElementPtr
LeaseCmdsImpl::createFailedLeaseMap(const Lease::Type& lease_type,
                                    const IOAddress& lease_address,
                                    const DuidPtr& duid,
                                    const int control_result,
                                    const std::string& error_message) const {
    auto failed_lease_map = Element::createMap();
    failed_lease_map->set("type", Element::create(Lease::typeToText(lease_type)));

    if (!lease_address.isV6Zero()) {
        failed_lease_map->set("ip-address", Element::create(lease_address.toText()));

    } else if (duid) {
        failed_lease_map->set("duid", Element::create(duid->toText()));
    }

    // Associate the result with the lease.
    failed_lease_map->set("result", Element::create(control_result));
    failed_lease_map->set("error-message", Element::create(error_message));

    return (failed_lease_map);
}

int
LeaseCmdsImpl::leaseWriteHandler(CalloutHandle& handle) {
    bool v4 = true;
    try {
        extractCommand(handle);
        v4 = (cmd_name_ == "lease4-write");

        if (!cmd_args_) {
            isc_throw(isc::BadValue, "no parameters specified for the command");
        }

        ConstElementPtr file = cmd_args_->get("filename");
        if (!file) {
            isc_throw(BadValue, "'filename' parameter not specified");
        }
        if (file->getType() != Element::string) {
            isc_throw(BadValue, "'filename' parameter must be a string");
        }
        string filename = file->stringValue();
        if (filename.empty()) {
            isc_throw(BadValue, "'filename' parameter is empty");
        }

        if (v4) {
            LeaseMgrFactory::instance().writeLeases4(filename);
        } else {
            LeaseMgrFactory::instance().writeLeases6(filename);
        }
        ostringstream s;
        s << (v4 ? "IPv4" : "IPv6")
          << " lease database into '"
          << filename << "'.";
        ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS, s.str());
        setResponse(handle, response);
    } catch (const std::exception& ex) {
        setErrorResponse(handle, ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (0);
}

int
LeaseCmds::leaseAddHandler(CalloutHandle& handle) {
    return (impl_->leaseAddHandler(handle));
}

int
LeaseCmds::lease6BulkApplyHandler(CalloutHandle& handle) {
    return (impl_->lease6BulkApplyHandler(handle));
}

int
LeaseCmds::leaseGetHandler(CalloutHandle& handle) {
    return (impl_->leaseGetHandler(handle));
}

int
LeaseCmds::leaseGetAllHandler(hooks::CalloutHandle& handle) {
    return (impl_->leaseGetAllHandler(handle));
}

int
LeaseCmds::leaseGetPageHandler(hooks::CalloutHandle& handle) {
    return (impl_->leaseGetPageHandler(handle));
}

int
LeaseCmds::leaseGetByHwAddressHandler(hooks::CalloutHandle& handle) {
    return (impl_->leaseGetByHwAddressHandler(handle));
}

int
LeaseCmds::leaseGetByClientIdHandler(hooks::CalloutHandle& handle) {
    return (impl_->leaseGetByClientIdHandler(handle));
}

int
LeaseCmds::leaseGetByDuidHandler(hooks::CalloutHandle& handle) {
    return (impl_->leaseGetByDuidHandler(handle));
}

int
LeaseCmds::leaseGetByHostnameHandler(hooks::CalloutHandle& handle) {
    return (impl_->leaseGetByHostnameHandler(handle));
}

int
LeaseCmds::lease4DelHandler(CalloutHandle& handle) {
    return (impl_->lease4DelHandler(handle));
}

int
LeaseCmds::lease6DelHandler(CalloutHandle& handle) {
    return (impl_->lease6DelHandler(handle));
}

int
LeaseCmds::lease4UpdateHandler(CalloutHandle& handle) {
    return (impl_->lease4UpdateHandler(handle));
}

int
LeaseCmds::lease6UpdateHandler(CalloutHandle& handle) {
    return (impl_->lease6UpdateHandler(handle));
}

int
LeaseCmds::lease4WipeHandler(CalloutHandle& handle) {
    MultiThreadingCriticalSection cs;
    return (impl_->lease4WipeHandler(handle));
}

int
LeaseCmds::lease6WipeHandler(CalloutHandle& handle) {
    MultiThreadingCriticalSection cs;
    return (impl_->lease6WipeHandler(handle));
}

int
LeaseCmds::lease4ResendDdnsHandler(CalloutHandle& handle) {
    return (impl_->lease4ResendDdnsHandler(handle));
}

int
LeaseCmds::lease6ResendDdnsHandler(CalloutHandle& handle) {
    return (impl_->lease6ResendDdnsHandler(handle));
}

int
LeaseCmds::leaseWriteHandler(CalloutHandle& handle) {
    return (impl_->leaseWriteHandler(handle));
}

LeaseCmds::LeaseCmds()
    :impl_(new LeaseCmdsImpl()) {
}

} // end of namespace lease_cmds
} // end of namespace isc
