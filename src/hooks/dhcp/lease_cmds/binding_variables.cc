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

    /// @todo If we add scopes we may wish to allow higher order
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

const data::SimpleKeywords
BindingVariable::CONFIG_KEYWORDS =
{
    { "name",        Element::string },
    { "expression",  Element::string },
    { "source",      Element::string }
};

BindingVariablePtr
BindingVariable::parse(data::ConstElementPtr config, uint16_t family) {
    // Note checkKeywords() will throw DhcpConfigError if there is a problem.
    SimpleParser::checkKeywords(CONFIG_KEYWORDS, config);

    // Parse members.
    std::string name = SimpleParser::getString(config, "name");;
    std::string expression = SimpleParser::getString(config, "expression");;
    std::string source_str = SimpleParser::getString(config, "source");;

    try {
        Source source;
        if (source_str == "query") {
            source = QUERY;
        } else if (source_str == "response") {
            source = RESPONSE;
        } else {
            isc_throw(BadValue, "invalid source '" << source_str
                      << "', must be either 'query' or 'response'");
        }

        // Attempt to create the variable.
        return (BindingVariablePtr(new BindingVariable(name, expression, source, family)));
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, "invalid config: " << ex.what());
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
    map->set("expression", Element::create(expression_str_));
    map->set("source", Element::create((source_ == QUERY ? "query" : "response")));
    return (map);
}

BindingVariableCache::BindingVariableCache()
    : variables_(), mutex_(new std::mutex) {
}

bool
BindingVariableCache::add(BindingVariablePtr variable) {
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

BindingVariableListPtr
BindingVariableCache::getAll() {
    util::MultiThreadingLock lock(*mutex_);

    BindingVariableListPtr var_list(new BindingVariableList());
    const auto& index = variables_.get<VariableSequenceTag>();
    for (auto const& variable : index) {
        /// For now we'll return the pointer, w/o making a copy
        /// of the  variable itself.  We never updates variables
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

BindingVariableMgr::BindingVariableMgr(uint32_t family)
    : family_(family) {
    if (family_ != AF_INET && family_ != AF_INET6) {
        isc_throw (BadValue, "BindingVariableMgr - invalid family: " << family_);
    }

    cache_.reset(new BindingVariableCache());
}

void
BindingVariableMgr::configure(data::ConstElementPtr config) {
    //  Always wipe the cache.
    cache_->clear();

    ConstElementPtr elem = config->get("binding-variables");
    if (!elem) {
        // Nothing to do.
        return;
    }

    // binding-variables should be a list.
    if (elem->getType() != Element::list) {
        isc_throw(DhcpConfigError, "'binding-variables' must be a list");
    }

    // iterate over the list adding variables to the cache
    for (auto const& var_elem : elem->listValue()) {
        try {
            BindingVariablePtr variable = BindingVariable::parse(var_elem, family_);
            cache_->add(variable);
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "cannot add BindingVariable to cache: " << ex.what());
        }
    }
}

bool
BindingVariableMgr::evaluateVariables(PktPtr query, PktPtr response, LeasePtr lease) {
    if (!query || !response || !lease) {
        isc_throw(BadValue, "evaluateVariables - missing query, response, and/or lease");
    }

    if (!cache_->size()) {
        /// @todo If the lease has binding-variables in its context from a prior
        /// update, but config changed and now there are none defined, should we
        /// removed them from the lease? For now, we'll leave them.
        return(false);
    }

    auto const variables = cache_->getAll();
    ElementPtr values = Element::createMap();
    for (auto const& variable : *variables) {
        try {
            auto value = evaluateString(*(variable->getExpression()),
                                        (variable->getSource() == BindingVariable::QUERY ?
                                         *query : *response));
            values->set(variable->getName(), Element::create(value));
        } catch (const std::exception& ex) {
            isc_throw(Unexpected, "expression blew up: " << ex.what());
        }
    }

    return (lease->updateUserContextISC("binding-variables", values));
}

} // end of namespace lease_cmds
} // end of namespace isc
