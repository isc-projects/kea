// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_RELATIONSHIP_MAPPER_H
#define HA_RELATIONSHIP_MAPPER_H

#include <config.h>

#include <exceptions/exceptions.h>
#include <boost/shared_ptr.hpp>
#include <unordered_map>
#include <vector>

namespace isc {
namespace ha {

/// @brief Holds associations between objects and HA relationships.
///
/// There are at least two classes that require associations with the
/// HA relationships: @c HAService and @c HAConfig. The @c HAImpl class
/// may hold one or more instances of these classes. The library must be
/// able to select appropriate instances depending on the partner name.
/// This class associates partners with the relationships. Each partner
/// may be associated with only one relationship. One relationship may
/// be associated with many partners (e.g., primary and standby).
///
/// @tparam MappedType type of a mapped object (i.e., @c HAService or
/// @c HAConfig).
template<typename MappedType>
class HARelationshipMapper {
public:

    /// @brief A pointer to the held object type.
    typedef boost::shared_ptr<MappedType> MappedTypePtr;

    /// @brief Associates a key with the object.
    ///
    /// @param key typically a name of a partner belonging to a relationship.
    /// @param obj mapped object.
    void map(const std::string& key, MappedTypePtr obj) {
        if (mapping_.count(key) > 0) {
            isc_throw(InvalidOperation, "a relationship '" << key << "' already exists");
        }
        mapping_[key] = obj;

        auto found = false;
        for (auto o : vector_) {
            if (o == obj) {
                found = true;
                break;
            }
        }
        if (!found) {
            vector_.push_back(obj);
        }
    }

    /// @brief Retrieves mapped object by a key (e.g., partner name).
    ///
    /// @param key typically a name of the partner belonging to a relationship.
    /// @return Mapped object or null pointer if the object was not found.
    MappedTypePtr get(const std::string& key) const {
        auto obj = mapping_.find(key);
        if (obj == mapping_.end()) {
            return (MappedTypePtr());
        }
        return (obj->second);
    }

    /// @brief Returns the sole mapped object.
    ///
    /// @return Mapped object.
    /// @throw InvalidOperation when there is no mapped object or if there
    /// are multiple mapped objects.
    MappedTypePtr get() const {
        if (vector_.empty() || vector_.size() > 1) {
            isc_throw(InvalidOperation, "expected one relationship to be configured");
        }
        return (vector_[0]);
    }

    /// @brief Returns all mapped objects.
    ///
    /// @return A reference to a vector of mapped objects.
    const std::vector<MappedTypePtr>& getAll() const {
        return (vector_);
    }

private:

    /// Key-to-object mappings.
    std::unordered_map<std::string, MappedTypePtr> mapping_;

    /// A vector of unique objects in the order in which they were mapped.
    std::vector<MappedTypePtr> vector_;
};

} // end of namespace isc::ha
} // end of namespace isc

#endif // HA_RELATIONSHIP_MAPPER_H
