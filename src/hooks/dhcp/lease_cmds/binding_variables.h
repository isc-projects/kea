// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BINDING_VARIABLES_H
#define BINDING_VARIABLES_H

#include <cc/base_stamped_element.h>
#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcp/pkt.h>
#include <dhcpsrv/lease.h>
#include <eval/evaluate.h>
#include <eval/token.h>

#include <boost/scoped_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>

namespace isc {
namespace lease_cmds {

// Forward declaration for pointer.
class BindingVariable;

/// @brief Defines a shared pointer to a BindingVariable.
typedef boost::shared_ptr<BindingVariable> BindingVariablePtr;

/// @brief Embodies a named expression, whose output when
/// evaluated can be stored in a lease's user-context.
class BindingVariable : public isc::data::CfgToElement {
public:
    /// @brief Specifies the packet that the expression should be
    /// evaluated against.
    enum Source {
        QUERY,
        RESPONSE
    };

    /// @brief List of valid configurable parameters for a BindingVariable.
    static const data::SimpleKeywords CONFIG_KEYWORDS;

    /// @brief Constructor
    ///
    /// @param name name of the variable, must be unique. Used
    /// both as the key and as the label for the value in the output.
    /// @param expression_str Evaluation expression text.
    /// @param source Source packet the expression should be
    /// evaluated against, either QUERY or RESPONSE.
    /// @param family Protocol family of the expression, either
    /// AF_INET or AF_INET6.
    ///
    /// During construction the expression string is parsed for the
    /// protocol family.
    /// @throw BadValue if name if empty, or expression string fails
    /// to parse.
    BindingVariable(const std::string& name,
                    const std::string& expression_str,
                    const Source& source,
                    uint32_t family);

    /// @brief Destructor
    virtual ~BindingVariable() = default;

    /// @brief Parses configuration elements into a BindingVarable instance.
    ///
    /// @param config Map Element containing parameters for a single binding variable.
    /// @param family Protocol family of the variable, either AF_INET or AF_INET6.
    /// @return Pointer to the newly created BindingVariable instance.
    /// @throw DhcpConfigError if configuration parameters are invalid.
    static BindingVariablePtr parse(data::ConstElementPtr config, uint16_t family);

    /// @brief Evaluate the variable against the given packet.
    ///
    /// @param packet Pointer to the target packet.
    /// @return string result of the evaluation.
    /// @throw BadValue if an evaluation error occurs.
    std::string evaluate(dhcp::PktPtr packet) const;

    /// @brief Fetches the variable's name.
    ///
    /// @return string containing the name.
    std::string getName() const {
        return (name_);
    }

    /// @brief Fetches the variable's pre-parsed expression string.
    ///
    /// @return string containing the expression.
    std::string getExpressionStr() const {
        return (expression_str_);
    }

    /// @brief Fetches the variable's parsed expression.
    ///
    /// @return pointer to the expression.
    dhcp::ExpressionPtr getExpression() const {
        return (expression_);
    }

    /// @brief Fetches the variable's packet source.
    ///
    /// @return Source of the packet.
    Source getSource() const {
        return (source_);
    }

    /// @brief Fetches the variable's protocol family.
    ///
    /// @return Family of the packet i.e AF_INET or AF_INET6.
    uint32_t getFamily() const {
        return (family_);
    }

    /// @brief Creates an Element tree for the variable's configurable
    /// members.
    ///
    /// @return ElementPtr containing the configurable members.
    virtual data::ElementPtr toElement() const;

private:
    /// @param source Source packet the expression should be
    /// evaluated against, either QUERY or RESPONSE.
    /// @param family Protocol family of the expression, either

    /// @brief name of the variable.
    std::string name_;

    /// @brief Evaluation expression text.
    std::string expression_str_;

    /// @brief Source packet the expression should be evaluated against.
    Source source_;

    /// @brief Protocol family AF_INET or AF_INET6.
    uint32_t family_;

    /// @brief Parsed evaluation expression.
    dhcp::ExpressionPtr expression_;
};

/// @brief Defines a list of BindingVariablePtr instances.
typedef std::list<BindingVariablePtr> BindingVariableList;

/// @brief Defines a pointer to a list of BindingVariablePtrs.
typedef boost::shared_ptr<BindingVariableList> BindingVariableListPtr;

/// @brief Tag for the sequence index.
struct VariableSequenceTag { };

/// @brief Tag for the name index.
struct VariableNameTag { };

/// @brief Tag for the source index.
struct VariableSourceTag { };

/// @brief the client class multi-index.
typedef boost::multi_index_container<
    BindingVariablePtr,
    boost::multi_index::indexed_by<
        // First index is by sequence. -- Do we need this one?
        boost::multi_index::sequenced<
            boost::multi_index::tag<VariableSequenceTag>
        >,
        // Second index is by name.
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<VariableNameTag>,
            boost::multi_index::const_mem_fun<BindingVariable,
                                              std::string,
                                              &BindingVariable::getName>
        >,
        // Third index is by source.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<VariableSourceTag>,
            boost::multi_index::const_mem_fun<BindingVariable,
                                              BindingVariable::Source,
                                              &BindingVariable::getSource>
        >
    >
> BindingVariableContainer;

/// @brief BindingVariableCache stores binding variables.
///
/// Wrapper around the variable container that provides
/// thread-safe access and time-stamped management.  The
/// later is available if/when supported scopes beyond
/// global are added.
class BindingVariableCache : public data::BaseStampedElement {
public:
    /// @brief Constructor
    BindingVariableCache();

    /// @brief Destructor
    virtual ~BindingVariableCache() = default;

    /// @brief Adds (or replaces) the variable in the cache.
    ///
    /// Variables must be unique by name. If the variable to
    /// be added is a duplicate, the add fails and the function
    /// returns false.
    ///
    /// @param variable pointer to the variable to store.
    /// @return true if the variable was added, false otherwise.
    bool add(BindingVariablePtr variable);

    /// @brief Delete all the entries in the cache.
    void clear();

    /// @brief Returns number of entries in the cache.
    size_t size();

    /// @brief Returns the last time the cache was flushed (or
    /// the time it was created if it has never been flushed).
    boost::posix_time::ptime getLastFlushTime();

    /// @brief Fetches all of the binding variables in the order
    /// they were added to the cache.
    ///
    /// @return Pointer to a list of the BindingVariables.
    BindingVariableListPtr getAll();

    /// @brief Fetches a binding variable by name
    ///
    /// @return A pointer to the variable or an empty pointer
    /// if no match is found.
    BindingVariablePtr getByName(const std::string& name);

    /// @brief Fetches all of the binding variables in the order
    /// they were added to the cache that use a specific source.
    ///
    /// @return Pointer to a list of the BindingVariables.
    BindingVariableListPtr getBySource(const BindingVariable::Source& source);

private:
    /// @brief Variable storage container.
    BindingVariableContainer variables_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;

};

/// @brief Defines a shared pointer to a BindingVariableCache.
typedef boost::shared_ptr<BindingVariableCache> BindingVariableCachePtr;

/// @brief Singleton which warehouses the configured binding variables,
/// and evaluation of variables for a given lease and packet pair.
class BindingVariableMgr {
public:
    /// @brief Constructor
    ///
    /// @param family Protocol family of the expression, either
    /// AF_INET or AF_INET6.
    explicit BindingVariableMgr(uint32_t family);

    /// @brief Destructor;
    ~BindingVariableMgr() = default;

    /// @brief Configures the manager based on the given configuration.
    ///
    /// This will clear the binding variable cache and then repopulate it
    /// by parsing the configuration.  It expects to see a list of one or
    /// more binding variable maps similar to the following:
    ///
    /// @code
    /// "binding-variables": [{
    ///     "name": "domain-name",
    ///     "expression": "option[15].text",
    ///      "source": "response"
    ///  },{
    ///     "name": "opt-222",
    ///     "expression": "hexstring(option[222].hex, ':')"
    ///     "source": "query"
    ///  ..
    ///  }]
    ///
    /// @endcode
    /// @param config JSON element tree containing the binding-variable list.
    /// @throw DhcpConfigError if the configuration is invalid.
    void configure(data::ConstElementPtr config);

    /// @brief Evaluates the binding variables for a given lease and packet pair.
    ///
    /// Iterates over the variables in the cache evaluating each on and added its
    /// name and value to the context.
    ///
    /// @param query Client packet which produced the lease. Variables whose source
    /// is "query" will be evaluated against this packet.
    /// @param response Server response conveying the lease. Variables whose source
    /// is "response" will be evaluated against this packet.
    /// @param lease Lease whose use-context will be updated with the evaluation
    /// results.  If the results of the evaluation are identical the the lease's
    /// existing binding-variables value, the lease is not altered. This allows
    /// a subsequent lease store update to only occur when needed.
    /// @return True if the lease's user-context was updated, false otherwise.
    bool evaluateVariables(dhcp::PktPtr query, dhcp::PktPtr response,
                           dhcp::LeasePtr lease);

    /// @brief Fetches the current variables cache.
    ///
    /// @return Pointer to BindingVariableCache.
    BindingVariableCachePtr getCache() {
        return(cache_);
    }

private:
    /// @brief Protocol family AF_INET or AF_INET6.
    uint32_t family_;

    /// @brief Currently configured set of binding variables.
    BindingVariableCachePtr cache_;
};

/// @brief Defines a shared pointer to a BindingVariableMgr.
typedef boost::shared_ptr<BindingVariableMgr> BindingVariableMgrPtr;


} // end of namespace lease_cmds
} // end of namespace isc
#endif
