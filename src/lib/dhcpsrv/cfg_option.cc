// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_space.h>
#include <util/encode/encode.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/make_shared.hpp>
#include <string>
#include <sstream>
#include <vector>

using namespace isc::data;

namespace isc {
namespace dhcp {

OptionDescriptorPtr
OptionDescriptor::create(const OptionPtr& opt, bool persist, bool cancel,
                         const std::string& formatted_value,
                         ConstElementPtr user_context) {
    return (boost::make_shared<OptionDescriptor>(opt, persist, cancel,
                                                 formatted_value,
                                                 user_context));
}

OptionDescriptorPtr
OptionDescriptor::create(bool persist, bool cancel) {
    return (boost::make_shared<OptionDescriptor>(persist, cancel));
}

OptionDescriptorPtr
OptionDescriptor::create(const OptionDescriptor& desc) {
    return (boost::make_shared<OptionDescriptor>(desc));
}

bool
OptionDescriptor::equals(const OptionDescriptor& other) const {
    return ((persistent_ == other.persistent_) &&
            (cancelled_ == other.cancelled_) &&
            (formatted_value_ == other.formatted_value_) &&
            (space_name_ == other.space_name_) &&
            option_->equals(other.option_));
}

CfgOption::CfgOption()
    : encapsulated_(false) {
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
CfgOption::add(const OptionPtr& option,
               const bool persistent,
               const bool cancelled,
               const std::string& option_space,
               const uint64_t id) {
    OptionDescriptor desc(option, persistent, cancelled);
    if (id > 0) {
        desc.setId(id);
    }
    add(desc, option_space);
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
    auto const& od_itr = idx.find(desc.option_->getType());
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
    for (auto const& id : ids) {
        std::ostringstream s;
        // Vendor space name is constructed as "vendor-XYZ" where XYZ is an
        // uint32_t value, without leading zeros.
        s << "vendor-" << id;
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

    // If we copied new options we may need to populate the
    // sub-options into the upper level options. The server
    // expects that the top-level options have suitable
    // suboptions appended.
    encapsulate();
}

void
CfgOption::createOptions(CfgOptionDefPtr cfg_def) {
    // Iterate over all the option descriptors in
    // all the spaces and instantiate the options
    // based on the given definitions.
    for (auto const& space : getOptionSpaceNames()) {
        for (auto opt_desc : *(getAll(space))) {
            if (createDescriptorOption(cfg_def, space, opt_desc)) {
                // Option was recreated, let's replace the descriptor.
                replace(opt_desc, space);
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

    // Finish with a last resort option definition.
    if (!def) {
        def = LibDHCP::getLastResortOptionDef(space, code);
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
    other.encapsulated_ = isEncapsulated();
}

void
CfgOption::encapsulate() {
    // Append sub-options to the top level "dhcp4" option space.
    encapsulateInternal(DHCP4_OPTION_SPACE);
    // Append sub-options to the top level "dhcp6" option space.
    encapsulateInternal(DHCP6_OPTION_SPACE);
    encapsulated_ = true;
}

void
CfgOption::encapsulateInternal(const std::string& option_space) {
    // Get all options for the particular option space.
    OptionContainerPtr options = getAll(option_space);
    // For each option in the option space we will append sub-options
    // from the option spaces they encapsulate.
    for (auto const& opt : *options) {
        encapsulateInternal(opt.option_);
    }
}

void
CfgOption::encapsulateInternal(const OptionPtr& option) {
    // Get encapsulated option space for the option.
    const std::string& encap_space = option->getEncapsulatedSpace();
    // Empty value means that no option space is encapsulated.
    if (!encap_space.empty()) {
        if (encap_space == DHCP4_OPTION_SPACE || encap_space == DHCP6_OPTION_SPACE) {
            return;
        }
        // Retrieve all options from the encapsulated option space.
        OptionContainerPtr encap_options = getAll(encap_space);
        for (auto const& encap_opt : *encap_options) {
            if (option.get() == encap_opt.option_.get()) {
                // Avoid recursion by not adding options to themselves.
                continue;
            }

            // Add sub-option if there isn't one added already.
            if (!option->getOption(encap_opt.option_->getType())) {
                option->addOption(encap_opt.option_);
            }
            encapsulateInternal(encap_opt.option_);
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
    for (auto const& it : selectors) {
        // Get all options in the destination container for the particular
        // option space.
        OptionContainerPtr dest_all = dest_container.getItems(it);
        OptionContainerPtr src_all = src_container.getItems(it);
        // For each option under this option space check if there is a
        // corresponding option in the destination container. If not,
        // add one.
        for (auto const& src_opt : *src_all) {
            const OptionContainerTypeIndex& idx = dest_all->get<1>();
            const OptionContainerTypeRange& range =
                idx.equal_range(src_opt.option_->getType());
            // If there is no such option in the destination container,
            // add one.
            if (std::distance(range.first, range.second) == 0) {
                dest_container.addItem(OptionDescriptor(src_opt), it);
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

OptionContainerPtr
CfgOption::getAllCombined(const std::string& option_space) const {
    auto vendor_id = LibDHCP::optionSpaceToVendorId(option_space);
    if (vendor_id > 0) {
        return (getAll(vendor_id));
    }
    return (getAll(option_space));
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
        for (auto const& option_space_from_list : option_space_names) {
            // Get all options within the particular option space.
            auto const& options_in_space = getAll(option_space_from_list);
            for (auto const& option_it : *options_in_space) {

                // Check if the option encapsulates our option space and
                // it does, try to delete our option.
                if (option_it.option_ &&
                    (option_it.option_->getEncapsulatedSpace() == option_space)) {
                    option_it.option_->delOption(option_code);
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

size_t
CfgOption::del(const uint64_t id) {
    // Hierarchical nature of the options configuration requires that
    // we go over all options and decapsulate them before removing
    // any of them. Let's walk over the existing option spaces.
    for (auto const& space_name : getOptionSpaceNames()) {
        // Get all options for the option space.
        auto const& options = getAll(space_name);
        for (auto const& option_it : *options) {
            if (!option_it.option_) {
                continue;
            }

            // For each option within the option space we need to dereference
            // any existing sub options.
            auto sub_options = option_it.option_->getOptions();
            for (auto const& sub : sub_options) {
                // Dereference sub option.
                option_it.option_->delOption(sub.second->getType());
            }
        }
    }

    // Now that we got rid of dependencies between the instances of the options
    // we can delete all options having a specified id.
    size_t num_deleted = options_.deleteItems(id) + vendor_options_.deleteItems(id);

    // Let's encapsulate those options that remain in the configuration.
    encapsulate();

    // Return the number of deleted options.
    return (num_deleted);
}

ElementPtr
CfgOption::toElement() const {
    return (toElementWithMetadata(false));
}

ElementPtr
CfgOption::toElementWithMetadata(const bool include_metadata) const {
    // option-data value is a list of maps
    ElementPtr result = Element::createList();
    // Iterate first on options using space names
    const std::list<std::string>& names = options_.getOptionSpaceNames();
    for (auto const& name : names) {
        OptionContainerPtr opts = getAll(name);
        for (auto const& opt : *opts) {
            // Get and fill the map for this option
            ElementPtr map = Element::createMap();
            // Set user context
            opt.contextToElement(map);
            // Set space from parent iterator
            map->set("space", Element::create(name));
            // Set the code
            uint16_t code = opt.option_->getType();
            map->set("code", Element::create(code));
            // Set the name (always for standard options else when asked for)
            OptionDefinitionPtr def = LibDHCP::getOptionDef(name, code);
            if (!def) {
                def = LibDHCP::getRuntimeOptionDef(name, code);
            }
            if (!def) {
                def = LibDHCP::getLastResortOptionDef(name, code);
            }
            if (def) {
                map->set("name", Element::create(def->getName()));
            }
            // Set the data item
            if (!opt.formatted_value_.empty()) {
                map->set("csv-format", Element::create(true));
                if (def && def->getType() == OPT_EMPTY_TYPE) {
                    map->set("data", Element::create(""));
                } else {
                    map->set("data", Element::create(opt.formatted_value_));
                }
            } else {
                std::vector<uint8_t> bin = opt.option_->toBinary();
                if (!opt.cancelled_ || !bin.empty()) {
                    map->set("csv-format", Element::create(false));
                    if (def && def->getType() == OPT_EMPTY_TYPE) {
                        map->set("data", Element::create(""));
                    } else {
                        std::string repr = util::encode::encodeHex(bin);
                        map->set("data", Element::create(repr));
                    }
                }
            }
            // Set the persistency flag
            map->set("always-send", Element::create(opt.persistent_));
            // Set the cancelled flag.
            map->set("never-send", Element::create(opt.cancelled_));
            // Include metadata if requested.
            if (include_metadata) {
                map->set("metadata", opt.getMetadata());
            }

            // Push on the list
            result->add(map);
        }
    }
    // Iterate first on vendor_options using vendor ids
    const std::list<uint32_t>& ids = vendor_options_.getOptionSpaceNames();
    for (auto const& id : ids) {
        OptionContainerPtr opts = getAll(id);
        for (auto const& opt : *opts) {
            // Get and fill the map for this option
            ElementPtr map = Element::createMap();
            // Set user context
            opt.contextToElement(map);
            // Set space from parent iterator
            std::ostringstream oss;
            oss << "vendor-" << id;
            map->set("space", Element::create(oss.str()));
            // Set the code
            uint16_t code = opt.option_->getType();
            map->set("code", Element::create(code));
            // Set the name
            Option::Universe universe = opt.option_->getUniverse();
            OptionDefinitionPtr def =
                LibDHCP::getVendorOptionDef(universe, id, code);
            if (!def) {
                // vendor-XXX space is in oss
                def = LibDHCP::getRuntimeOptionDef(oss.str(), code);
            }
            if (def) {
                map->set("name", Element::create(def->getName()));
            }
            // Set the data item
            if (!opt.formatted_value_.empty()) {
                map->set("csv-format", Element::create(true));
                if (def && def->getType() == OPT_EMPTY_TYPE) {
                    map->set("data", Element::create(""));
                } else {
                    map->set("data", Element::create(opt.formatted_value_));
                }
            } else {
                std::vector<uint8_t> bin = opt.option_->toBinary();
                if (!opt.cancelled_ || !bin.empty()) {
                    map->set("csv-format", Element::create(false));
                    if (def && def->getType() == OPT_EMPTY_TYPE) {
                        map->set("data", Element::create(""));
                    } else {
                        std::string repr = util::encode::encodeHex(bin);
                        map->set("data", Element::create(repr));
                    }
                }
            }
            // Set the persistency flag
            map->set("always-send", Element::create(opt.persistent_));
            // Set the cancellation flag
            map->set("never-send", Element::create(opt.cancelled_));
            // Push on the list
            result->add(map);
        }
    }
    return (result);
}

}  // namespace dhcp
}  // namespace isc
