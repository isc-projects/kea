// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION_SPACE_CONTAINER_H
#define OPTION_SPACE_CONTAINER_H

#include <list>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Simple container for option spaces holding various items.
///
/// This helper class is used to store items of various types in
/// that are grouped by option space names. Each option space is
/// mapped to a container that holds items which specifically can
/// be OptionDefinition objects or Subnet::OptionDescriptor structures.
///
/// @tparam ContainerType of the container holding items within
/// option space.
/// @tparam ItemType type of the item being held by the container.
/// @tparam Selector a string (for option spaces) or uint32_t (for vendor options)
template<typename ContainerType, typename ItemType, typename Selector>
class OptionSpaceContainer {
public:

    /// Pointer to the container.
    typedef boost::shared_ptr<ContainerType> ItemsContainerPtr;

    /// @brief Adds a new item to the option_space.
    ///
    /// @param item reference to the item being added.
    /// @param option_space name of the option space.
    void addItem(const ItemType& item, const Selector& option_space) {
        ItemsContainerPtr items = getItems(option_space);
        items->push_back(item);
        option_space_map_[option_space] = items;
    }

    /// @brief Get all items for the particular option space.
    ///
    /// @warning when there are no items for the specified option
    /// space an empty container is created and returned. However
    /// this container is not added to the list of option spaces.
    ///
    /// @param option_space name of the option space.
    ///
    /// @return pointer to the container holding items.
    ItemsContainerPtr getItems(const Selector& option_space) const {
        const typename OptionSpaceMap::const_iterator& items =
            option_space_map_.find(option_space);
        if (items == option_space_map_.end()) {
            return (ItemsContainerPtr(new ContainerType()));
        }
        return (items->second);
    }

    /// @brief Get a list of existing option spaces.
    ///
    /// @return a list of option spaces.
    ///
    /// @todo This function is likely to be removed once
    /// we create a structore of OptionSpaces defined
    /// through the configuration manager.
    std::list<Selector> getOptionSpaceNames() {
        std::list<Selector> names;
        for (typename OptionSpaceMap::const_iterator space =
                 option_space_map_.begin();
             space != option_space_map_.end(); ++space) {
            names.push_back(space->first);
        }
        return (names);
    }

    /// @brief Remove all items from the container.
    void clearItems() {
        option_space_map_.clear();
    }

private:

    /// A map holding container (option space name is the key).
    typedef std::map<Selector, ItemsContainerPtr> OptionSpaceMap;
    OptionSpaceMap option_space_map_;
};


} // end of isc::dhcp namespace
} // end of isc namespace

#endif // OPTION_SPACE_CONTAINER_H
