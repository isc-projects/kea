// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
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

using namespace isc::data;

namespace isc {
namespace dhcp {
namespace test {

GenericBackendTest::GenericBackendTest() {
    LibDHCP::clearRuntimeOptionDefs();
}

GenericBackendTest::~GenericBackendTest() {
    LibDHCP::clearRuntimeOptionDefs();
}

OptionDescriptor
GenericBackendTest::createEmptyOption(const Option::Universe& universe,
                                      const uint16_t option_type,
                                      const bool persist) const {
    OptionPtr option(new Option(universe, option_type));
    OptionDescriptor desc(option, persist);
    return (desc);
}

OptionDescriptor
GenericBackendTest::createVendorOption(const Option::Universe& universe,
                                       const bool persist,
                                       const bool formatted,
                                       const uint32_t vendor_id) const {
    OptionVendorPtr option(new OptionVendor(universe, vendor_id));

    std::ostringstream s;
    if (formatted) {
        // Vendor id comprises vendor-id field, for which we need to
        // assign a value in the textual (formatted) format.
        s << vendor_id;
    }

    OptionDescriptor desc(option, persist, s.str());
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
    EXPECT_EQ(ref_option.space_name_, tested_option.space_name_);
}

void
GenericBackendTest::checkConfiguredGlobal(const SrvConfigPtr& srv_cfg,
                                          const std::string &name,
                                          ConstElementPtr exp_value) {
    ConstElementPtr globals = srv_cfg->getConfiguredGlobals();
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


} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
