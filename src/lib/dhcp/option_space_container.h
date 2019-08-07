// Copyright (C) 2013-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_SPACE_CONTAINER_H
#define OPTION_SPACE_CONTAINER_H

#include <exceptions/exceptions.h>
#include <list>
#include <string>

namespace isc {
namespace dhcp {

/// @brief A tag for accessing DHCP options and definitions by id.
struct OptionIdIndexTag { };

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
    /// @return true when the container is empty
    bool empty() const {
        return (option_space_map_.empty());
    }

    /// @brief Adds a new item to the option_space.
    ///
    /// @param item reference to the item being added.
    /// @param option_space name or vendor-id of the option space
    void addItem(const ItemType& item, const Selector& option_space) {
        ItemsContainerPtr items = getItems(option_space);
        // Assume that the push_back() can't fail even when the
        // ContainerType is a multi index container, i.e., assume
        // there is no unique index which can raise a conflict.
        static_cast<void>(items->push_back(item));
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
    /// we create a structure of OptionSpaces defined
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

    /// @brief Remove all options or option definitions with a given
    /// database identifier.
    ///
    /// Note that there are cases when there will be multiple options
    /// or option definitions having the same id (typically id of 0).
    /// When configuration backend is in use it sets the unique ids
    /// from the database. In cases when the configuration backend is
    /// not used, the ids default to 0. Passing the id of 0 would
    /// result in deleting all options or option definitions that were
    /// not added via the database.
    ///
    /// @param id Identifier of the items to be deleted.
    ///
    /// @return Number of deleted options or option definitions.
    uint64_t deleteItems(const uint64_t id) {
        uint64_t num_deleted = 0;
        for (auto space : option_space_map_) {
            auto container = space.second;
            auto& index = container->template get<OptionIdIndexTag>();
            num_deleted += index.erase(id);
        }

        return (num_deleted);
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
