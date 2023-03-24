// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/libdhcp++.h>
#include <dhcp/option_vendor.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <util/buffer.h>
#include <typeinfo>
#include <testutils/gtest_utils.h>

using namespace isc::data;
using namespace isc::db;

namespace isc {
namespace dhcp {
namespace test {

GenericBackendTest::GenericBackendTest()
    : timestamps_(), audit_entries_() {
    LibDHCP::clearRuntimeOptionDefs();
    initTimestamps();
}

GenericBackendTest::~GenericBackendTest() {
    LibDHCP::clearRuntimeOptionDefs();
}

OptionDescriptor
GenericBackendTest::createEmptyOption(const Option::Universe& universe,
                                      const uint16_t option_type,
                                      const bool persist,
                                      const bool cancel) const {
    OptionPtr option(new Option(universe, option_type));
    OptionDescriptor desc(option, persist, cancel);
    return (desc);
}

OptionDescriptor
GenericBackendTest::createVendorOption(const Option::Universe& universe,
                                       const bool persist,
                                       const bool cancel,
                                       const bool formatted,
                                       const uint32_t vendor_id) const {
    OptionVendorPtr option(new OptionVendor(universe, vendor_id));

    std::ostringstream s;
    if (formatted) {
        // Vendor id comprises vendor-id field, for which we need to
        // assign a value in the textual (formatted) format.
        s << vendor_id;
    }

    OptionDescriptor desc(option, persist, cancel, s.str());
    return (desc);
}

void
GenericBackendTest::testOptionsEquivalent(const OptionDescriptor& ref_option,
                                          const OptionDescriptor& tested_option) const {
    // Make sure that all pointers are non-null.
    ASSERT_TRUE(ref_option.option_);
    ASSERT_TRUE(tested_option.option_);

    // Get the reference to the tested option. Make should it has
    // generic type.
    Option& tested_option_reference = *tested_option.option_;
    EXPECT_TRUE(typeid(tested_option_reference) == typeid(Option));

    // Only test the binary data if the formatted value is not provided.
    if (tested_option.formatted_value_.empty()) {

        // Prepare on-wire data of the option under test.
        isc::util::OutputBuffer tested_option_buf(1);
        tested_option.option_->pack(tested_option_buf);
        const uint8_t* tested_option_buf_data = static_cast<const uint8_t*>
            (tested_option_buf.getData());
        std::vector<uint8_t> tested_option_buf_vec(tested_option_buf_data,
                                                   tested_option_buf_data + tested_option_buf.getLength());

        // Prepare on-wire data of the reference option.
        isc::util::OutputBuffer ref_option_buf(1);
        ref_option.option_->pack(ref_option_buf);
        const uint8_t* ref_option_buf_data = static_cast<const uint8_t*>
            (ref_option_buf.getData());
        std::vector<uint8_t> ref_option_buf_vec(ref_option_buf_data,
                                                ref_option_buf_data + ref_option_buf.getLength());

        // Compare the on-wire data.
        EXPECT_EQ(ref_option_buf_vec, tested_option_buf_vec);

    } else {
        // If the formatted value is non-empty the buffer should be empty.
        EXPECT_TRUE(tested_option.option_->getData().empty());
    }

    // Compare other members of the @c OptionDescriptor, e.g. the
    // tested option may contain formatted option data which can be
    // later used to turn this option instance into a formatted
    // option when an option definition is available.
    EXPECT_EQ(ref_option.formatted_value_, tested_option.formatted_value_);
    EXPECT_EQ(ref_option.persistent_, tested_option.persistent_);
    EXPECT_EQ(ref_option.cancelled_, tested_option.cancelled_);
    EXPECT_EQ(ref_option.space_name_, tested_option.space_name_);
}

void
GenericBackendTest::checkConfiguredGlobal(const SrvConfigPtr& srv_cfg,
                                          const std::string &name,
                                          ConstElementPtr exp_value) {
    ConstCfgGlobalsPtr globals = srv_cfg->getConfiguredGlobals();
    ConstElementPtr found_global = globals->get(name);
    ASSERT_TRUE(found_global) << "expected global: "
                              << name << " not found";

    ASSERT_EQ(exp_value->getType(), found_global->getType())
        << "expected global: " << name << " has wrong type";

    ASSERT_EQ(*exp_value, *found_global)
        << "expected global: " << name << " has wrong value";
}

void
GenericBackendTest::checkConfiguredGlobal(const SrvConfigPtr& srv_cfg,
                                          StampedValuePtr& exp_global) {
    checkConfiguredGlobal(srv_cfg, exp_global->getName(), exp_global->getElementValue());
}


void
GenericBackendTest::testNewAuditEntry(const std::string& exp_object_type,
                                      const AuditEntry::ModificationType& exp_modification_type,
                                      const std::string& exp_log_message,
                                      const ServerSelector& server_selector,
                                      const size_t new_entries_num,
                                      const size_t max_tested_entries) {
    // Get the server tag for which the entries are fetched.
    std::string tag;
    if (server_selector.getType() == ServerSelector::Type::ALL) {
        // Server tag is 'all'.
        tag = "all";
    } else {
        const auto& tags = server_selector.getTags();
        // This test is not meant to handle multiple server tags all at once.
        if (tags.size() > 1) {
            ADD_FAILURE() << "Test error: do not use multiple server tags";
        } else if (tags.size() == 1) {
            // Get the server tag for which we run the current test.
            tag = tags.begin()->get();
        }
    }

    auto audit_entries_size_save = audit_entries_[tag].size();

    // Audit entries for different server tags are stored in separate
    // containers.
    ASSERT_NO_THROW_LOG(audit_entries_[tag]
                        = getRecentAuditEntries(server_selector, timestamps_["two days ago"], 0));

    ASSERT_EQ(audit_entries_size_save + new_entries_num, audit_entries_[tag].size())
              << logExistingAuditEntries(tag);

    auto& mod_time_idx = audit_entries_[tag].get<AuditEntryModificationTimeIdTag>();

    // Iterate over specified number of entries starting from the most recent
    // one and check they have correct values.
    for (auto audit_entry_it = mod_time_idx.rbegin();
         ((std::distance(mod_time_idx.rbegin(), audit_entry_it) < new_entries_num) &&
         (std::distance(mod_time_idx.rbegin(), audit_entry_it) < max_tested_entries));
         ++audit_entry_it) {
        auto audit_entry = *audit_entry_it;
        EXPECT_EQ(exp_object_type, audit_entry->getObjectType())
                  << logExistingAuditEntries(tag);
        EXPECT_EQ(exp_modification_type, audit_entry->getModificationType())
                  << logExistingAuditEntries(tag);
        EXPECT_EQ(exp_log_message, audit_entry->getLogMessage())
                  << logExistingAuditEntries(tag);
    }
}

void
GenericBackendTest::testNewAuditEntry(const std::vector<ExpAuditEntry>& exp_entries,
                                      const ServerSelector& server_selector) {
    // Get the server tag for which the entries are fetched.
    std::string tag;
    if (server_selector.getType() == ServerSelector::Type::ALL) {
        // Server tag is 'all'.
        tag = "all";
    } else {
        const auto& tags = server_selector.getTags();
        // This test is not meant to handle multiple server tags all at once.
        if (tags.size() != 1) {
            ADD_FAILURE() << "Test error: tags.size(): " << tags.size()
                          << ", you must specify one and only one server tag";
        }

        // Get the server tag for which we run the current test.
        tag = tags.begin()->get();
    }

    size_t new_entries_num = exp_entries.size();

    auto audit_entries_size_save = audit_entries_[tag].size();

    // Audit entries for different server tags are stored in separate
    // containers.
    ASSERT_NO_THROW_LOG(audit_entries_[tag]
                        = getRecentAuditEntries(server_selector, timestamps_["two days ago"], 0));

    ASSERT_EQ(audit_entries_size_save + new_entries_num, audit_entries_[tag].size())
              << logExistingAuditEntries(tag);

    auto& mod_time_idx = audit_entries_[tag].get<AuditEntryModificationTimeIdTag>();

    // Iterate over specified number of entries starting from the most recent
    // one and check they have correct values.
    auto exp_entry = exp_entries.rbegin();
    for (auto audit_entry_it = mod_time_idx.rbegin();
         ((std::distance(mod_time_idx.rbegin(), audit_entry_it) < new_entries_num));
         ++audit_entry_it) {

        auto audit_entry = *audit_entry_it;
        EXPECT_EQ((*exp_entry).object_type, audit_entry->getObjectType())
                  << logExistingAuditEntries(tag);
        EXPECT_EQ((*exp_entry).modification_type, audit_entry->getModificationType())
                  << logExistingAuditEntries(tag);
        EXPECT_EQ((*exp_entry).log_message, audit_entry->getLogMessage())
                  << logExistingAuditEntries(tag);

        ++exp_entry;
    }
}

void
GenericBackendTest::initTimestamps() {
    // Current time minus 1 hour to make sure it is in the past.
    timestamps_["today"] = boost::posix_time::second_clock::local_time()
                           - boost::posix_time::hours(1);
    // One second after today.
    timestamps_["after today"] = timestamps_["today"] + boost::posix_time::seconds(1);
    // Yesterday.
    timestamps_["yesterday"] = timestamps_["today"] - boost::posix_time::hours(24);
    // One second after yesterday.
    timestamps_["after yesterday"] = timestamps_["yesterday"] + boost::posix_time::seconds(1);
    // Two days ago.
    timestamps_["two days ago"] = timestamps_["today"] - boost::posix_time::hours(48);
    // Tomorrow.
    timestamps_["tomorrow"] = timestamps_["today"] + boost::posix_time::hours(24);
    // One second after tomorrow.
    timestamps_["after tomorrow"] = timestamps_["tomorrow"] + boost::posix_time::seconds(1);
}

std::string
GenericBackendTest::logExistingAuditEntries(const std::string& server_tag) {
    std::ostringstream s;

    auto& mod_time_idx = audit_entries_[server_tag].get<AuditEntryModificationTimeIdTag>();

    for (auto audit_entry_it = mod_time_idx.begin();
         audit_entry_it != mod_time_idx.end();
         ++audit_entry_it) {
        auto audit_entry = *audit_entry_it;
        s << audit_entry->getObjectType() << ", "
          << audit_entry->getObjectId() << ", "
          << static_cast<int>(audit_entry->getModificationType()) << ", "
          << audit_entry->getModificationTime() << ", "
          << audit_entry->getRevisionId() << ", "
          << audit_entry->getLogMessage()
          << std::endl;
    }

    return (s.str());
}

AuditEntryCollection
GenericBackendTest::getRecentAuditEntries(const ServerSelector&, const boost::posix_time::ptime&,
                                          const uint64_t&) const {
    return (AuditEntryCollection());
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
