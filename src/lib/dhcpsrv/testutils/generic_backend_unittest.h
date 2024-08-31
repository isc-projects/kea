// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_BACKEND_UNITTEST_H
#define GENERIC_BACKEND_UNITTEST_H

#include <asiolink/io_address.h>
#include <cc/stamped_value.h>
#include <database/audit_entry.h>
#include <database/server_selector.h>
#include <dhcp/option.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/srv_config.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <string>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Describes an expected audit table entry.
struct ExpAuditEntry {
    /// @brief Type of object changed.
    std::string object_type;

    /// @brief Timestamp the change occurred.
    db::AuditEntry::ModificationType modification_type;

    /// @brief Log message describing the change.
    std::string log_message;
};

/// @brief Generic test fixture class with utility functions for
/// testing database backends.
class GenericBackendTest : public ::testing::Test {
public:

    /// @brief Constructor.
    GenericBackendTest();

    /// @brief Virtual destructor.
    virtual ~GenericBackendTest();

    /// @brief Creates an option descriptor holding an empty option.
    ///
    /// @param universe V4 or V6.
    /// @param option_type Option type.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    /// @param cancel A boolean flag indicating if the option must never
    /// be returned to the client,
    ///
    /// @return Descriptor holding an empty option.
    OptionDescriptor createEmptyOption(const Option::Universe& universe,
                                       const uint16_t option_type,
                                       const bool persist,
                                       const bool cancel) const;

    /// @brief Creates an instance of the option for which it is possible to
    /// specify universe, option type, persistence flag  and value in
    /// the constructor.
    ///
    /// Examples of options that can be created using this function are:
    /// - @ref OptionString
    /// - different variants of @ref OptionInt.
    ///
    /// @param universe V4 or V6.
    /// @param option_type Option type.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    /// @param cancel A boolean flag indicating if the option must never
    /// be returned to the client,
    /// @param formatted A boolean value selecting if the formatted option
    /// value should be used (if true), or binary value (if false).
    /// @param value Option value to be assigned to the option.
    /// @tparam OptionType Class encapsulating the option.
    /// @tparam DataType Option value data type.
    ///
    /// @return Descriptor holding an instance of the option created.
    template<typename OptionType, typename DataType>
    OptionDescriptor createOption(const Option::Universe& universe,
                                  const uint16_t option_type,
                                  const bool persist,
                                  const bool cancel,
                                  const bool formatted,
                                  const DataType& value) const {
        boost::shared_ptr<OptionType> option(new OptionType(universe, option_type,
                                                            value));
        std::ostringstream s;
        if (formatted) {
            // Using formatted option value. Convert option value to a
            // textual format.
            s << value;
        }
        OptionDescriptor desc(option, persist, cancel, s.str());
        return (desc);
    }

    /// @brief Creates an instance of the option for which it is possible to
    /// specify option type, persistence flag  and value in the constructor.
    ///
    /// Examples of options that can be created using this function are:
    /// - @ref Option4AddrLst
    /// - @ref Option6AddrLst
    ///
    /// @param option_type Option type.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    /// @param cancel A boolean flag indicating if the option must never
    /// be returned to the client,
    /// @param formatted A boolean value selecting if the formatted option
    /// value should be used (if true), or binary value (if false).
    /// @param value Option value to be assigned to the option.
    /// @tparam OptionType Class encapsulating the option.
    /// @tparam DataType Option value data type.
    ///
    /// @return Descriptor holding an instance of the option created.
    template<typename OptionType, typename DataType>
    OptionDescriptor createOption(const uint16_t option_type,
                                  const bool persist,
                                  const bool cancel,
                                  const bool formatted,
                                  const DataType& value) const {
        boost::shared_ptr<OptionType> option(new OptionType(option_type, value));

        std::ostringstream s;
        if (formatted) {
            // Using formatted option value. Convert option value to a
            // textual format.
            s << value;
        }

        OptionDescriptor desc(option, persist, cancel, s.str());
        return (desc);
    }

    /// @brief Creates an instance of the option holding list of IP addresses.
    ///
    /// @param option_type Option type.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    /// @param cancel A boolean flag indicating if the option must never
    /// be returned to the client,
    /// @param formatted A boolean value selecting if the formatted option
    /// value should be used (if true), or binary value (if false).
    /// @param address1 First address to be included. If address is empty, it is
    /// not included.
    /// @param address2 Second address to be included. If address is empty, it
    /// is not included.
    /// @param address3 Third address to be included. If address is empty, it
    /// is not included.
    /// @tparam OptionType Class encapsulating the option.
    ///
    /// @return Descriptor holding an instance of the option created.
    template<typename OptionType>
    OptionDescriptor
    createAddressOption(const uint16_t option_type,
                        const bool persist,
                        const bool cancel,
                        const bool formatted,
                        const std::string& address1 = "",
                        const std::string& address2 = "",
                        const std::string& address3 = "") const {
        std::ostringstream s;
        // First address.
        typename OptionType::AddressContainer addresses;
        if (!address1.empty()) {
            addresses.push_back(asiolink::IOAddress(address1));
            if (formatted) {
                s << address1;
            }
        }
        // Second address.
        if (!address2.empty()) {
            addresses.push_back(asiolink::IOAddress(address2));
            if (formatted) {
                if (s.tellp() != std::streampos(0)) {
                    s << ",";
                }
                s << address2;
            }
        }
        // Third address.
        if (!address3.empty()) {
            addresses.push_back(asiolink::IOAddress(address3));
            if (formatted) {
                if (s.tellp() != std::streampos(0)) {
                    s << ",";
                }
                s << address3;
            }
        }

        boost::shared_ptr<OptionType> option(new OptionType(option_type,
                                                            addresses));
        OptionDescriptor desc(option, persist, cancel, s.str());
        return (desc);
    }

    /// @brief Creates an instance of the vendor option.
    ///
    /// @param universe V4 or V6.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    /// @param cancel A boolean flag indicating if the option must never
    /// be returned to the client,
    /// @param formatted A boolean value selecting if the formatted option
    /// value should be used (if true), or binary value (if false).
    /// @param vendor_id Vendor identifier.
    ///
    /// @return Descriptor holding an instance of the option created.
    OptionDescriptor createVendorOption(const Option::Universe& universe,
                                        const bool persist,
                                        const bool cancel,
                                        const bool formatted,
                                        const uint32_t vendor_id) const;

    /// @brief Verify the option returned by the backend against a
    /// reference option.
    ///
    /// DHCP option value can be specified in two ways. First, it can be
    /// specified as a string of hexadecimal digits which is converted to
    /// a binary option value. Second, it can be specified as a string of
    /// comma separated values in a user readable form. The comma separated
    /// values are parsed according to the definition of the given option
    /// and then stored in the respective fields of the option. The second
    /// approach always requires an option definition to be known to the
    /// parser. It may either be a standard option definition or a runtime
    /// option definition created by a user. While standard option
    /// definitions are available in the Kea header files, the custom
    /// option definitions may not be available to the Config Backend
    /// fetching an option from the database for the following reasons:
    ///
    /// - the server to which the Config Backend is attached is not the
    ///   one for which the configuration is being returned.
    /// - the server is starting up and hasn't yet configured its runtime
    ///   option definitions.
    /// - the Config Backend implementation is not attached to the DHCP
    ///   server but to the Control Agent.
    ///
    /// Note that the last case it currently not supported but may be
    /// supported in the future.
    ///
    /// Since the option definitions aren't always available to the Config
    /// Backend fetching the options from the database, the backend doesn't
    /// interpret formatted options (those that use comma separated values
    /// notation). It simply creates an @c OptionDescriptor with the generic
    /// option instance (containing an option code and no option value) and
    /// the other @c OptionDescriptor parameters set appropriately. The
    /// @c CfgOption class contains methods that can be used on demand to
    /// replace these instances with the appropriate types (derived from
    /// @c Option) which represent formatted option data, if necessary.
    ///
    /// This test verifies that the @c OptionDescriptor returned by the
    /// Config Backend is correct in that:
    /// - the @c option_ member is non-null,
    /// - the option instance is of a @c Option type rather than any of the
    ///   derived types (is a raw option),
    /// - the wire data of the returned option is equal to the wire data of
    ///   the reference option (the reference option can be of a type derived
    ///   from @c Option),
    /// - the @c formatted_value_, @c persistent_ and @c space_name_ members
    ///   of the returned option are equal to the respective members of the
    ///   reference option.
    ///
    /// @param ref_option Reference option to compare tested option to.
    /// @param tested_option Option returned by the backend to be tested.
    void testOptionsEquivalent(const OptionDescriptor& ref_option,
                               const OptionDescriptor& tested_option) const;

    /// @brief Tests that a given global is in the configured globals
    ///
    /// @param srv_cfg server config where the global should be checked.
    /// @param name name of the global parameter
    /// @param exp_value expected value of the global parameter as an Element
    void checkConfiguredGlobal(const SrvConfigPtr& srv_cfg,
                               const std::string &name,
                               data::ConstElementPtr exp_value);

    /// @brief Tests that a given global is in the configured globals
    ///
    /// @param srv_cfg server config where the global should be checked.
    /// @param exp_global StampedValue representing the global value to verify
    ///
    /// @todo At the point in time StampedVlaue carries type, exp_type should be
    /// replaced with exp_global->getType()
    void checkConfiguredGlobal(const SrvConfigPtr& srv_cfg,
                               data::StampedValuePtr& exp_global);

    /// @brief Tests that the new audit entry is added.
    ///
    /// This method retrieves a collection of the existing audit entries and
    /// checks that the new one has been added at the end of this collection.
    /// It then verifies the values of the audit entry against the values
    /// specified by the caller.
    ///
    /// @param exp_object_type Expected object type.
    /// @param exp_modification_type Expected modification type.
    /// @param exp_log_message Expected log message.
    /// @param server_selector Server selector to be used for next query.
    /// @param new_entries_num Number of the new entries expected to be inserted.
    /// @param max_tested_entries Maximum number of entries tested.
    void testNewAuditEntry(const std::string& exp_object_type,
                           const db::AuditEntry::ModificationType& exp_modification_type,
                           const std::string& exp_log_message,
                           const db::ServerSelector& server_selector = db::ServerSelector::ALL(),
                           const size_t new_entries_num = 1,
                           const size_t max_tested_entries = 65535);

    /// @brief Checks the new audit entries against a list of
    /// expected entries.
    ///
    /// This method retrieves a collection of the existing audit entries and
    /// checks that number and content of the expected new entries have been
    /// added to the end of this collection.
    ///
    /// @param exp_entries a list of the expected new audit entries.
    /// @param server_selector Server selector to be used for next query.
    void testNewAuditEntry(const std::vector<ExpAuditEntry>& exp_entries,
                           const db::ServerSelector& server_selector);

    /// @brief Logs audit entries in the @c audit_entries_ member.
    ///
    /// This function is called in case of an error.
    ///
    /// @param server_tag Server tag for which the audit entries should be logged.
    std::string logExistingAuditEntries(const std::string& server_tag);

    /// @brief Retrieves the most recent audit entries.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Timestamp being a lower limit for the returned
    /// result set, i.e. entries later than specified time are returned.
    /// @param modification_id Identifier being a lower limit for the returned
    /// result set, used when two (or more) entries have the same
    /// modification_time.
    /// @return Collection of audit entries.
    virtual db::AuditEntryCollection
    getRecentAuditEntries(const db::ServerSelector& server_selector,
                          const boost::posix_time::ptime& modification_time,
                          const uint64_t& modification_id) const ;

    /// @brief Initialize posix time values used in tests.
    void initTimestamps();

    /// @brief Holds timestamp values used in tests.
    std::map<std::string, boost::posix_time::ptime> timestamps_;

    /// @brief Holds the most recent audit entries.
    std::map<std::string, db::AuditEntryCollection> audit_entries_;
};

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc

#endif
