// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_space.h>
#include <util/encode/hex.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <string>
#include <sstream>
#include <vector>

using namespace isc::data;

namespace isc {
namespace dhcp {

bool
OptionDescriptor::equals(const OptionDescriptor& other) const {
    return ((persistent_ == other.persistent_) &&
            (formatted_value_ == other.formatted_value_) &&
            (space_name_ == other.space_name_) &&
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

void
CfgOption::replace(const OptionDescriptor& desc, const std::string& option_space) {
    if (!desc.option_) {
        isc_throw(isc::BadValue, "option being replaced must not be NULL");
    } 

    // Check for presence of options.
    OptionContainerPtr options = getAll(option_space);
    if (!options) {
        isc_throw(isc::BadValue, "option space " << option_space
                  << " does not exist");
    }

    // Find the option we want to replace.
    OptionContainerTypeIndex& idx = options->get<1>();
    OptionContainerTypeIndex::const_iterator od_itr = idx.find(desc.option_->getType());
    if (od_itr == idx.end()) {
        isc_throw(isc::BadValue, "cannot replace option: " 
                  << option_space << ":" << desc.option_->getType()
                  << ", it does not exist");
    } 

    idx.replace(od_itr, desc);
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
CfgOption::merge(CfgOptionDefPtr cfg_def,  CfgOption& other) {
    // First we merge our options into other.
    // This adds my options that are not
    // in other, to other (i.e we skip over
    // duplicates).
    mergeTo(other);

    // Create option instances based on the given definitions.
    other.createOptions(cfg_def);

    // Next we copy "other" on top of ourself.
    other.copyTo(*this);
}

void
CfgOption::createOptions(CfgOptionDefPtr cfg_def) {
    // Iterate over all the option descriptors in
    // all the spaces and instantiate the options
    // based on the given definitions.
    for (auto space : getOptionSpaceNames()) {
        for (auto opt_desc : *(getAll(space))) {
            if (createDescriptorOption(cfg_def, space, opt_desc)) {
                // Option was recreated, let's replace the descriptor. 
                replace(opt_desc,space);
            }
        }
    }
}

bool
CfgOption::createDescriptorOption(CfgOptionDefPtr cfg_def, const std::string& space,
                                  OptionDescriptor& opt_desc) {
    if (!opt_desc.option_) {
        isc_throw(BadValue,
                  "validateCreateOption: descriptor has no option instance");
    }

    Option::Universe universe = opt_desc.option_->getUniverse();
    uint16_t code = opt_desc.option_->getType();

    // Find the option's defintion, if it has one.
    // First, check for a standard definition.
    OptionDefinitionPtr def = LibDHCP::getOptionDef(space, code);

    // If there is no standard definition but the option is vendor specific,
    // we should search the definition within the vendor option space.
    if (!def && (space != DHCP4_OPTION_SPACE) && (space != DHCP6_OPTION_SPACE)) {
        uint32_t vendor_id = LibDHCP::optionSpaceToVendorId(space);
        if (vendor_id > 0) {
            def = LibDHCP::getVendorOptionDef(universe, vendor_id, code);
        }
    }

    // Still haven't found the definition, so look for custom
    // definition in the given set of configured definitions
    if (!def) {
        def = cfg_def->get(space, code);
    }

    std::string& formatted_value = opt_desc.formatted_value_;
    if (!def) {
        if (!formatted_value.empty()) {
            isc_throw(InvalidOperation, "option: " << space << "." << code
                      << " has a formatted value: '" << formatted_value
                      << "' but no option definition");
        }

        // If there's no definition and no formatted string, we'll
        // settle for the generic option already in the descriptor.
        // Indicate no-change by returning false.
        return (false);
    }

    try {
        // Definition found. Let's replace the generic option in
        // the descriptor with one created based on definition's factory.
        if (formatted_value.empty()) {
            // No formatted value, use data stored in the generic option.
            opt_desc.option_ = def->optionFactory(universe, code, opt_desc.option_->getData());
        } else {
            // Spit the value specified in comma separated values format.
            std::vector<std::string> split_vec;
            boost::split(split_vec, formatted_value, boost::is_any_of(","));
            opt_desc.option_ = def->optionFactory(universe, code, split_vec);
        }
    } catch (const std::exception& ex) {
            isc_throw(InvalidOperation, "could not create option: " << space << "." << code
                      << " from data specified, reason: " << ex.what());
    }

    // Indicate we replaced the definition.
    return(true);
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
        encapsulateInternal(opt->option_);
    }
}

void
CfgOption::encapsulateInternal(const OptionPtr& option) {
    // Get encapsulated option space for the option.
    const std::string& encap_space = option->getEncapsulatedSpace();
    // Empty value means that no option space is encapsulated.
    if (!encap_space.empty()) {
        // Retrieve all options from the encapsulated option space.
        OptionContainerPtr encap_options = getAll(encap_space);
        for (OptionContainer::const_iterator encap_opt =
                 encap_options->begin(); encap_opt != encap_options->end();
             ++encap_opt) {
            // Add sub-option if there isn't one added already.
            if (!option->getOption(encap_opt->option_->getType())) {
                option->addOption(encap_opt->option_);
            }
            // This is a workaround for preventing infinite recursion when
            // trying to encapsulate options created with default global option
            // spaces.
            if (encap_space != DHCP4_OPTION_SPACE &&
                encap_space != DHCP6_OPTION_SPACE) {
                encapsulateInternal(encap_opt->option_);
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
                dest_container.addItem(OptionDescriptor(*src_opt), *it);
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

size_t
CfgOption::del(const std::string& option_space, const uint16_t option_code) {
    // Check for presence of options.
    OptionContainerPtr options = getAll(option_space);
    if (!options || options->empty()) {
        // There are no options, so there is nothing to do.
        return (0);
    }

    // If this is not top level option we may also need to delete the
    // option instance from options encapsulating the particular option
    // space.
    if ((option_space != DHCP4_OPTION_SPACE) &&
        (option_space != DHCP6_OPTION_SPACE)) {
        // For each option space name iterate over the existing options.
        auto option_space_names = getOptionSpaceNames();
        for (auto option_space_from_list : option_space_names) {
            // Get all options within the particular option space.
            auto options_in_space = getAll(option_space_from_list);
            for (auto option_it = options_in_space->begin();
                 option_it != options_in_space->end();
                 ++option_it) {

                // Check if the option encapsulates our option space and
                // it does, try to delete our option.
                if (option_it->option_ &&
                    (option_it->option_->getEncapsulatedSpace() == option_space)) {
                    option_it->option_->delOption(option_code);
                }
            }
        }
    }

    auto& idx = options->get<1>();
    return (idx.erase(option_code));
}

size_t
CfgOption::del(const uint32_t vendor_id, const uint16_t option_code) {
    // Check for presence of options.
    OptionContainerPtr vendor_options = getAll(vendor_id);
    if (!vendor_options || vendor_options->empty()) {
        // There are no options, so there is nothing to do.
        return (0);
    }

    auto& idx = vendor_options->get<1>();
    return (idx.erase(option_code));
}

ElementPtr
CfgOption::toElement() const {
    // option-data value is a list of maps
    ElementPtr result = Element::createList();
    // Iterate first on options using space names
    const std::list<std::string>& names = options_.getOptionSpaceNames();
    for (std::list<std::string>::const_iterator name = names.begin();
         name != names.end(); ++name) {
        OptionContainerPtr opts = getAll(*name);
        for (OptionContainer::const_iterator opt = opts->begin();
             opt != opts->end(); ++opt) {
            // Get and fill the map for this option
            ElementPtr map = Element::createMap();
            // Set user context
            opt->contextToElement(map);
            // Set space from parent iterator
            map->set("space", Element::create(*name));
            // Set the code
            uint16_t code = opt->option_->getType();
            map->set("code", Element::create(code));
            // Set the name (always for standard options else when asked for)
            OptionDefinitionPtr def = LibDHCP::getOptionDef(*name, code);
            if (!def) {
                def = LibDHCP::getRuntimeOptionDef(*name, code);
            }
            if (!def) {
                def = LibDHCP::getLastResortOptionDef(*name, code);
            }
            if (def) {
                map->set("name", Element::create(def->getName()));
            }
            // Set the data item
            if (!opt->formatted_value_.empty()) {
                map->set("csv-format", Element::create(true));
                map->set("data", Element::create(opt->formatted_value_));
            } else {
                map->set("csv-format", Element::create(false));
                std::vector<uint8_t> bin = opt->option_->toBinary();
                std::string repr = util::encode::encodeHex(bin);
                map->set("data", Element::create(repr));
            }
            // Set the persistency flag
            map->set("always-send", Element::create(opt->persistent_));
            // Push on the list
            result->add(map);
        }
    }
    // Iterate first on vendor_options using vendor ids
    const std::list<uint32_t>& ids = vendor_options_.getOptionSpaceNames();
    for (std::list<uint32_t>::const_iterator id = ids.begin();
         id != ids.end(); ++id) {
        OptionContainerPtr opts = getAll(*id);
        for (OptionContainer::const_iterator opt = opts->begin();
             opt != opts->end(); ++opt) {
            // Get and fill the map for this option
            ElementPtr map = Element::createMap();
            // Set user context
            opt->contextToElement(map);
            // Set space from parent iterator
            std::ostringstream oss;
            oss << "vendor-" << *id;
            map->set("space", Element::create(oss.str()));
            // Set the code
            uint16_t code = opt->option_->getType();
            map->set("code", Element::create(code));
            // Set the name
            Option::Universe universe = opt->option_->getUniverse();
            OptionDefinitionPtr def =
                LibDHCP::getVendorOptionDef(universe, *id, code);
            if (!def) {
                // vendor-XXX space is in oss
                def = LibDHCP::getRuntimeOptionDef(oss.str(), code);
            }
            if (def) {
                map->set("name", Element::create(def->getName()));
            }
            // Set the data item
            if (!opt->formatted_value_.empty()) {
                map->set("csv-format", Element::create(true));
                map->set("data", Element::create(opt->formatted_value_));
            } else {
                map->set("csv-format", Element::create(false));
                std::vector<uint8_t> bin = opt->option_->toBinary();
                std::string repr = util::encode::encodeHex(bin);
                map->set("data", Element::create(repr));
            }
            // Set the persistency flag
            map->set("always-send", Element::create(opt->persistent_));
            // Push on the list
            result->add(map);
        }
    }
    return (result);
}

}  // namespace dhcp
}  // namespace isc
