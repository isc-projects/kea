// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Kea Hooks Basic
// Commercial End User License Agreement v2.0. See COPYING file in the premium/
// directory.

#include <config.h>

#include <binding_variables.h>
#include <iostream>

#include <cc/data.h>
#include <eval/eval_context.h>
#include <util/multi_threading_mgr.h>

using namespace isc::dhcp;
using namespace isc::data;

namespace isc {
namespace lease_cmds {

BindingVariable::BindingVariable(const std::string& name,
                                 const std::string& expression_str,
                                 const Source& source,
                                 uint32_t family)
    : name_(name), expression_str_(expression_str), source_(source),
      family_(family) {
    if (name_.empty()) {
        isc_throw(BadValue, "BindingVariable - name cannot be empty");
    }

    /// @todo If we add socpes we may wish to allow higher order
    /// scopes to override lower scopes with empty expressions.
    if (expression_str_.empty()) {
        isc_throw(BadValue, "BindingVariable - '" << name_ 
                  << "' expression_str cannot be empty");
    }

    if (family_ != AF_INET && family_ != AF_INET6) {
        isc_throw(BadValue, "BindingVariable - '" << name_ 
                  << "', invalid family: " << family_);
    }

    try {
        EvalContext eval_ctx(family_ == AF_INET ? Option::V4 : Option::V6);
        eval_ctx.parseString(expression_str_, EvalContext::PARSER_STRING);
        expression_.reset(new Expression(eval_ctx.expression_));
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "BindingVariable - '" << name_ << "', error parsing expression: '"
                  << expression_str_ << "' : " << ex.what());
    }
}

std::string
BindingVariable::evaluate(PktPtr packet) const {
    try {
        return (evaluateString(*expression_, *packet));
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "BindingVariable - " << name_ << ", error evaluating expression: ["
                  << expression_str_ << "] : " << ex.what());
    } 
}

ElementPtr
BindingVariable::toElement() const {
    ElementPtr map = Element::createMap();
    map->set("name", Element::create(name_));
    map->set("expression_str", Element::create(expression_str_));
    map->set("source", Element::create((source_ == QUERY ? "query" : "response")));
    return (map);
}

BindingVariableCache::BindingVariableCache() 
    : variables_(), mutex_(new std::mutex) {
}

bool
BindingVariableCache::cacheVariable(BindingVariablePtr variable) {
    util::MultiThreadingLock lock(*mutex_);
    auto retpair = variables_.push_back(variable);
    return(retpair.second);
}

void 
BindingVariableCache::clear() {
    util::MultiThreadingLock lock(*mutex_);
    // Discard contents.
    // We use modification time to remember the last time we flushed.
    variables_.clear();
    updateModificationTime();
}

size_t
BindingVariableCache::size() {
    util::MultiThreadingLock lock(*mutex_);
    return (variables_.size());
}

boost::posix_time::ptime
BindingVariableCache::getLastFlushTime() {
    util::MultiThreadingLock lock(*mutex_);
    return (BaseStampedElement::getModificationTime());
}

/// @brief Tag for the name index.
//struct VariableNameTag { };

/// @brief Tag for the source index.
//struct VariableSourceTag { };


BindingVariableListPtr
BindingVariableCache::getAll() {
    util::MultiThreadingLock lock(*mutex_);

    BindingVariableListPtr var_list(new BindingVariableList());
    const auto& index = variables_.get<VariableSequenceTag>();
    for (auto const& variable : index) {
        /// For now we'll return the pointer, w/o making a copy
        /// of the  varaiable itself.  We never updates variables
        /// so we should be OK.
        var_list->push_back(variable);
    }

    return (var_list);
}

BindingVariablePtr
BindingVariableCache::getByName(const std::string& name) {
    util::MultiThreadingLock lock(*mutex_);

    const auto& index = variables_.get<VariableNameTag>();
    auto var_iter = index.find(name);
    return (var_iter == index.end() ? BindingVariablePtr() : *var_iter);
}

BindingVariableListPtr
BindingVariableCache::getBySource(const BindingVariable::Source& source) {
    util::MultiThreadingLock lock(*mutex_);

    BindingVariableListPtr var_list(new BindingVariableList());
    const auto& index = variables_.get<VariableSourceTag>();
    auto lower_limit = index.lower_bound(source);
    auto upper_limit = index.upper_bound(source);
    for (auto var_iter = lower_limit; var_iter != upper_limit; ++var_iter) {
        var_list->push_back(*var_iter);
    }

    return (var_list);
}
    
} // end of namespace lease_cmds
} // end of namespace isc
