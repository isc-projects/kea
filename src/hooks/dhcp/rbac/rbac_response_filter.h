// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RBAC_RESPONSE_FILTER_H
#define RBAC_RESPONSE_FILTER_H

#include <http/response_json.h>
#include <list>
#include <map>

namespace isc {
namespace rbac {

/// @brief Forward declaration of ResponseFilter.
class ResponseFilter;

/// @brief The type of shared pointers to response filters.
typedef boost::shared_ptr<ResponseFilter> ResponseFilterPtr;

/// @brief The type of list of shared pointers to response filters.
typedef std::list<ResponseFilterPtr> ResponseFilterList;

/// @brief The type of the response filter table.
typedef std::map<std::string, ResponseFilterPtr> ResponseFilterTable;

/// @brief Forward declaration of RoleConfig.
class RoleConfig;

/// @brief Response filter base class.
class ResponseFilter {
public:

    /// @brief Constructor.
    ///
    /// @param name Name of the response filter class.
    /// @throw Unexpected when name is empty.
    ResponseFilter(const std::string& name) : name_(name) {
        if (name.empty()) {
            isc_throw(Unexpected, "empty response filter name");
        }
    }

    /// @brief Destructor.
    virtual ~ResponseFilter() = default;

    /// @brief Returns the name.
    ///
    /// @return the name.
    std::string getName() const {
        return (name_);
    }

    /// @brief Filter a response.
    ///
    /// @param command The role command.
    /// @param role_config The role config.
    /// @param body The JSON response body.
    /// @return whether the body was modified.
    virtual bool filter(const std::string& command,
                        const RoleConfig& role_config,
                        data::ConstElementPtr body) = 0;

    /// @brief Initialize the response filter table.
    static void initResponseFilterTable();

    /// @brief Parse a response filter list.
    ///
    /// @param cfg Configuration of response filter list.
    static ResponseFilterList parse(data::ConstElementPtr cfg);

protected:
    /// @brief The class name.
    std::string name_;
};

/// @brief Noop response filter.
///
/// Removes not allowed commands from the response.
class NoopResponseFilter : public ResponseFilter {
public:

    /// @brief Constructor.
    NoopResponseFilter() : ResponseFilter("noop") {
    }

    /// @brief Filter a response (doing nothing).
    ///
    /// @return always false.
    virtual bool filter(const std::string&,
                        const RoleConfig&,
                        data::ConstElementPtr) final {
        return (false);
    }
};

/// @brief Response filter for list-commands.
///
/// Removes not allowed commands from the response.
class ListCommandsResponseFilter : public ResponseFilter {
public:

    /// @brief Constructor.
    ListCommandsResponseFilter() : ResponseFilter("list-commands") {
    }

    /// @brief Filter a response from list-commands.
    ///
    /// @param command The role command.
    /// @param role_config The role config.
    /// @param body The JSON response body.
    /// @return whether the body was modified.
    virtual bool filter(const std::string& command,
                        const RoleConfig& role_config,
                        data::ConstElementPtr body) final;
};

/// @brief The response filter table.
extern ResponseFilterTable responseFilterTable;

} // end of namespace rbac
} // end of namespace isc
#endif
