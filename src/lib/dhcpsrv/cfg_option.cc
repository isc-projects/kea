// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/option_space.h>
#include <dhcpsrv/cfg_option.h>
#include <boost/lexical_cast.hpp>
#include <limits>
#include <string>

namespace {

uint32_t
optionSpaceToVendorId(const std::string& option_space) {
    if (option_space.size() < 8) {
        // 8 is a minimal length of "vendor-X" format
        return (0);
    }
    if (option_space.substr(0,7) != "vendor-") {
        return (0);
    }

    // text after "vendor-", supposedly numbers only
    std::string x = option_space.substr(7);

    int64_t check;
    try {
        check = boost::lexical_cast<int64_t>(x);
    } catch (const boost::bad_lexical_cast &) {
        /// @todo: Should we throw here?
        // isc_throw(BadValue, "Failed to parse vendor-X value (" << x
        //           << ") as unsigned 32-bit integer.");
        return (0);
    }
    if (check > std::numeric_limits<uint32_t>::max()) {
        /// @todo: Should we throw here?
        //isc_throw(BadValue, "Value " << x << "is too large"
        //          << " for unsigned 32-bit integer.");
        return (0);
    }
    if (check < 0) {
        /// @todo: Should we throw here?
        // isc_throw(BadValue, "Value " << x << "is negative."
        //       << " Only 0 or larger are allowed for unsigned 32-bit integer.");
        return (0);
    }

    // value is small enough to fit
    return (static_cast<uint32_t>(check));
}

}

namespace isc {
namespace dhcp {

bool
OptionDescriptor::equals(const OptionDescriptor& other) const {
    return (persistent == other.persistent &&
            option->equals(other.option));
}

bool
CfgOption::equals(const CfgOption& other) const {
    return (options_.equals(other.options_) &&
            vendor_options_.equals(other.vendor_options_));
}

void
CfgOption::add(const OptionPtr& option, const bool persistent,
               const std::string& option_space) {
    if (!option) {
        isc_throw(isc::BadValue, "option being configured must not be NULL");

    } else  if (!OptionSpace::validateName(option_space)) {
        isc_throw(isc::BadValue, "invalid option space name: '"
                  << option_space << "'");
    }

    const uint32_t vendor_id = optionSpaceToVendorId(option_space);
    if (vendor_id) {
        vendor_options_.addItem(OptionDescriptor(option, persistent),
                                vendor_id);
    } else {
        options_.addItem(OptionDescriptor(option, persistent), option_space);
    }
}

void
CfgOption::merge(CfgOption& other) const {
    // Merge non-vendor options.
    mergeInternal(options_, other.options_);
    // Merge vendor options.
    mergeInternal(vendor_options_, other.vendor_options_);
}

void
CfgOption::copy(CfgOption& other) const {
    // Create empty object and "merge" data to it.
    CfgOption new_cfg;
    merge(new_cfg);
    other = new_cfg;
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
                idx.equal_range(src_opt->option->getType());
            // If there is no such option in the destination container,
            // add one.
            if (std::distance(range.first, range.second) == 0) {
                dest_container.addItem(OptionDescriptor(src_opt->option,
                                                        src_opt->persistent),
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
