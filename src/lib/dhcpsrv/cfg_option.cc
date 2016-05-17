// Copyright (C) 2014-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/libdhcp++.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcp/dhcp6.h>
#include <string>

namespace isc {
namespace dhcp {

bool
OptionDescriptor::equals(const OptionDescriptor& other) const {
    return (persistent_ == other.persistent_ &&
            formatted_value_ == other.formatted_value_ &&
            option_->equals(other.option_));
}

CfgOption::CfgOption() {
}

bool
CfgOption::empty() const {
    return (options_.empty() && vendor_options_.empty());
}

bool
CfgOption::equals(const CfgOption& other) const {
    return (options_.equals(other.options_) &&
            vendor_options_.equals(other.vendor_options_));
}

void
CfgOption::add(const OptionPtr& option, const bool persistent,
               const std::string& option_space) {
    add(OptionDescriptor(option, persistent), option_space);
}

void
CfgOption::add(const OptionDescriptor& desc, const std::string& option_space) {
    if (!desc.option_) {
        isc_throw(isc::BadValue, "option being configured must not be NULL");

    } else  if (!OptionSpace::validateName(option_space)) {
        isc_throw(isc::BadValue, "invalid option space name: '"
                  << option_space << "'");
    }

    const uint32_t vendor_id = LibDHCP::optionSpaceToVendorId(option_space);
    if (vendor_id) {
        vendor_options_.addItem(desc, vendor_id);
    } else {
        options_.addItem(desc, option_space);
    }
}

std::list<std::string>
CfgOption::getVendorIdsSpaceNames() const {
    std::list<uint32_t> ids = getVendorIds();
    std::list<std::string> names;
    for (std::list<uint32_t>::const_iterator id = ids.begin();
         id != ids.end(); ++id) {
        std::ostringstream s;
        // Vendor space name is constructed as "vendor-XYZ" where XYZ is an
        // uint32_t value, without leading zeros.
        s << "vendor-" << *id;
        names.push_back(s.str());
    }
    return (names);
}

void
CfgOption::mergeTo(CfgOption& other) const {
    // Merge non-vendor options.
    mergeInternal(options_, other.options_);
    // Merge vendor options.
    mergeInternal(vendor_options_, other.vendor_options_);
}

void
CfgOption::copyTo(CfgOption& other) const {
    // Remove any existing data in the destination.
    other.options_.clearItems();
    other.vendor_options_.clearItems();
    mergeTo(other);
}

void
CfgOption::encapsulate() {
    // Append sub-options to the top level "dhcp4" option space.
    encapsulateInternal(DHCP4_OPTION_SPACE);
    // Append sub-options to the top level "dhcp6" option space.
    encapsulateInternal(DHCP6_OPTION_SPACE);
}

void
CfgOption::encapsulateInternal(const std::string& option_space) {
    // Get all options for the particular option space.
    OptionContainerPtr options = getAll(option_space);
    // For each option in the option space we will append sub-options
    // from the option spaces they encapsulate.
    for (OptionContainer::const_iterator opt = options->begin();
         opt != options->end(); ++opt) {
        // Get encapsulated option space for the option.
        const std::string& encap_space = opt->option_->getEncapsulatedSpace();
        // Empty value means that no option space is encapsulated.
        if (!encap_space.empty()) {
            // Retrieve all options from the encapsulated option space.
            OptionContainerPtr encap_options = getAll(encap_space);
            for (OptionContainer::const_iterator encap_opt =
                     encap_options->begin(); encap_opt != encap_options->end();
                 ++encap_opt) {
                // Add sub-option if there isn't one added already.
                if (!opt->option_->getOption(encap_opt->option_->getType())) {
                    opt->option_->addOption(encap_opt->option_);
                }
            }
        }
    }
}

template <typename Selector>
void
CfgOption::mergeInternal(const OptionSpaceContainer<OptionContainer,
                         OptionDescriptor, Selector>& src_container,
                         OptionSpaceContainer<OptionContainer,
                         OptionDescriptor, Selector>& dest_container) const {
    // Get all option spaces used in source container.
    std::list<Selector> selectors = src_container.getOptionSpaceNames();

    // For each space in the source container retrieve the actual options and
    // match them with the options held in the destination container under
    // the same space.
    for (typename std::list<Selector>::const_iterator it = selectors.begin();
         it != selectors.end(); ++it) {
        // Get all options in the destination container for the particular
        // option space.
        OptionContainerPtr dest_all = dest_container.getItems(*it);
        OptionContainerPtr src_all = src_container.getItems(*it);
        // For each option under this option space check if there is a
        // corresponding option in the destination container. If not,
        // add one.
        for (OptionContainer::const_iterator src_opt = src_all->begin();
             src_opt != src_all->end(); ++src_opt) {
            const OptionContainerTypeIndex& idx = dest_all->get<1>();
            const OptionContainerTypeRange& range =
                idx.equal_range(src_opt->option_->getType());
            // If there is no such option in the destination container,
            // add one.
            if (std::distance(range.first, range.second) == 0) {
                dest_container.addItem(OptionDescriptor(src_opt->option_,
                                                        src_opt->persistent_),
                                       *it);
            }
        }
    }
}


OptionContainerPtr
CfgOption::getAll(const std::string& option_space) const {
    return (options_.getItems(option_space));
}

OptionContainerPtr
CfgOption::getAll(const uint32_t vendor_id) const {
    return (vendor_options_.getItems(vendor_id));
}

} // end of namespace isc::dhcp
} // end of namespace isc
