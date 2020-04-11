// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef USER_CONTEXT_H
#define USER_CONTEXT_H

#include <cc/data.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace data {

/// @brief Base class for user context
///
/// Many configuration structures allow attaching and storing arbitrary
/// user data that we call user context. Each of those configuration
/// structures need to derive from this class or include this class
/// to handle user context.
struct UserContext {
    /// @brief Returns const pointer to the user context.
    data::ConstElementPtr getContext() const {
        return (user_context_);
    }

    /// @brief Sets user context.
    /// @param ctx user context to be stored.
    void setContext(const data::ConstElementPtr& ctx) {
        user_context_ = ctx;
    }

    /// @brief Merge unparse a user_context object.
    ///
    /// Add user-context to map, but only if defined. Omit if it was not.
    ///
    /// @param map A pointer to map where the user context will be unparsed.
    void contextToElement(data::ElementPtr map) const;

    /// @brief Copy an Element map
    ///
    /// A previous version of this extracted comments.
    ///
    /// @param map A pointer to map.
    /// @return a copy of map
    static data::ElementPtr toElement(data::ConstElementPtr map);

protected:

    /// @brief Pointer to the user context (may be NULL)
    data::ConstElementPtr user_context_;
};

} // end of isc::dhcp namespace
} // end of isc namespace


#endif // USER_CONTEXT_H
