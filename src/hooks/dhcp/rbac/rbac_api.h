// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RBAC_API_H
#define RBAC_API_H

#include <cc/data.h>
#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <set>
#include <string>

namespace isc {
namespace rbac {

/// @brief Forward declaration of the Api class.
class Api;

/// @brief Type of shared pointer to Api.
typedef boost::shared_ptr<Api> ApiPtr;

/// @brief Command from the API class.
class Api {
public:

    /// @brief Constructor.
    ///
    /// @param name The command name.
    /// @param access The access (read or write).
    /// @param hook The hook name (can be empty).
    Api(const std::string& name, const std::string& access,
        const std::string& hook) : name_(name), access_(access), hook_(hook) {
    }

    /// @brief Destructor.
    virtual ~Api() = default;

    /// @brief Returns the command name.
    ///
    /// @return the command name.
    std::string getName() const {
        return (name_);
    }

    /// @brief Returns the command access.
    ///
    /// @return the command access.
    std::string getAccess() const {
        return (access_);
    }

    /// @brief Set the command access.
    ///
    /// @param access The command access.
    void setAccess(const std::string& access) {
        access_ = access;
    }

    /// @brief Returns the command hook name.
    ///
    /// @return the command hook name.
    std::string getHook() const {
        return (hook_);
    }

    /// @brief Set the command hook name.
    ///
    /// @param hook The command hook name.
    void setHook(const std::string& hook) {
        hook_ = hook;
    }

    /// @brief Lookup in the table.
    ///
    /// @param name The command name.
    /// @return the pointer to the Api object with the specified name or null.
    static ApiPtr getApiByName(const std::string& name);

    /// @brief Fill the API command table.
    ///
    /// @param dirname The API directory name.
    static void fillApiTable(const std::string& dirname);

    /// @brief Parse a command config.
    ///
    /// @param cfg Configuration of a command.
    /// @param others Accept other keywords.
    static void parse(data::ConstElementPtr cfg, bool others = false);

protected:
    /// @brief The command name.
    std::string name_;

    /// @brief The command access (read or write).
    std::string access_;

    /// @brief The name of the hook which registers the command (may not be set).
    std::string hook_;
};

/// @brief A tag for accessing name index.
struct ApiNameIndexTag {};

/// @brief A tag for accessing access index.
struct ApiAccessIndexTag {};

/// @brief A tag for accessing hook index.
struct ApiHookIndexTag {};

/// @brief The type of the API command table.
typedef boost::multi_index_container<
    // Elements of shared pointer to Api objects.
    ApiPtr,
    boost::multi_index::indexed_by<
        // First index is by name.
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<ApiNameIndexTag>,
            boost::multi_index::const_mem_fun<Api, std::string, &Api::getName>
        >,
        // Second index is by access.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<ApiAccessIndexTag>,
            boost::multi_index::const_mem_fun<Api, std::string, &Api::getAccess>
        >,
        // Third index is by hook.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<ApiHookIndexTag>,
            boost::multi_index::const_mem_fun<Api, std::string, &Api::getHook>
        >
    >
> ApiTable;

/// @brief The API command table.
extern ApiTable apiTable;

/// @brief The API access list (should be "read" and "write").
extern std::set<std::string> apiAccesses;

/// @brief The API hook list.
extern std::set<std::string> apiHooks;

} // end of namespace rbac
} // end of namespace isc
#endif
