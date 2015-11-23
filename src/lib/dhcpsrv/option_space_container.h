// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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
/// This helper class is used to store items of various types
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

    /// @brief Indicates the container is empty
    ///
    /// @return true when the confainer is empty
    bool empty() const {
        return (option_space_map_.empty());
    }

    /// @brief Adds a new item to the option_space.
    ///
    /// @param item reference to the item being added.
    /// @param option_space name or vendor-id of the option space
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
    /// @param option_space name or vendor-id of the option space.
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
    std::list<Selector> getOptionSpaceNames() const {
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

    /// @brief Check if two containers are equal.
    ///
    /// This method checks if option space container contains exactly
    /// the same selectors and that there are exactly the same items
    /// added for each selector. The order of items doesn't matter.
    ///
    /// @param other Other container to compare to.
    ///
    /// @return true if containers are equal, false otherwise.
    bool equals(const OptionSpaceContainer& other) const {
        for (typename OptionSpaceMap::const_iterator it =
                 option_space_map_.begin(); it != option_space_map_.end();
             ++it) {

            typename OptionSpaceMap::const_iterator other_it =
                other.option_space_map_.find(it->first);
            if (other_it == other.option_space_map_.end()) {
                return (false);
            }

            // If containers have different sizes it is an indication that
            // they are unequal.
            if (it->second->size() != other_it->second->size()) {
                return (false);
            }

            // If they have the same sizes, we have to compare each element.
            for (typename ContainerType::const_iterator items_it =
                     it->second->begin();
                 items_it != it->second->end(); ++items_it) {

                bool match_found = false;
                for (typename ContainerType::const_iterator other_items_it =
                         other_it->second->begin();
                     other_items_it != other_it->second->end();
                     ++other_items_it) {
                    if (items_it->equals(*other_items_it)) {
                        match_found = true;
                        break;
                    }
                }

                if (!match_found) {
                    return (false);
                }
            }
        }
        return (true);
    }

private:

    /// A map holding container (option space name or vendor-id is the key).
    typedef std::map<Selector, ItemsContainerPtr> OptionSpaceMap;
    OptionSpaceMap option_space_map_;
};


} // end of isc::dhcp namespace
} // end of isc namespace

#endif // OPTION_SPACE_CONTAINER_H
