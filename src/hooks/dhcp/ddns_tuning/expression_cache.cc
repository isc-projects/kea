// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <expression_cache.h>
#include <eval/token.h>
#include <eval/eval_context.h>
#include <util/multi_threading_mgr.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace std;

namespace isc {
namespace ddns_tuning {

bool
ExpressionCache::findExpression(const SubnetID& subnet_id, ExpressionPtr& expression) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        return (findExpressionInternal(subnet_id, expression));
    } else {
        return (findExpressionInternal(subnet_id, expression));
    }
}

bool
ExpressionCache::findExpressionInternal(const SubnetID& subnet_id, ExpressionPtr& expression) const {
    auto it = expressions_.find(subnet_id);
    if (it != expressions_.end()) {
        expression = it->second;
        return (true);
    }

    expression = ExpressionPtr();
    return (false);
}

ExpressionPtr
ExpressionCache::parseAndCacheExpression(const SubnetID& subnet_id, const string& expression_str,
                                 uint32_t family) {
    ExpressionPtr expression;
    try {
        // We allow empty expressions so higher precedence scopes may
        // override lower precedence scopes.
        if (expression_str.empty()) {
            expression.reset(new Expression());
        } else {
            EvalContext eval_ctx(family == AF_INET ? Option::V4 : Option::V6);
            eval_ctx.parseString(expression_str, EvalContext::PARSER_STRING);
            expression.reset(new Expression(eval_ctx.expression_));
        }
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "error parsing expression: ["
                  << expression_str << "] : " << ex.what());
    }

    cacheExpression(subnet_id, expression);
    return (expression);
}

void
ExpressionCache::cacheExpression(const SubnetID& subnet_id, ExpressionPtr& expression) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        expressions_[subnet_id] = expression;
    } else {
        expressions_[subnet_id] = expression;
    }
}

void
ExpressionCache::clear() {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        // Discard the contents.
        expressions_.clear();

        // We use modification time to remember the last time we flushed.
        updateModificationTime();
    } else {
        // Discard the contents.
        expressions_.clear();

        // We use modification time to remember the last time we flushed.
        updateModificationTime();
    }
}

size_t
ExpressionCache::size() {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        return (expressions_.size());
    } else {
        return (expressions_.size());
    }
}

boost::posix_time::ptime
ExpressionCache::getLastFlushTime() {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lk(mutex_);
        return (BaseStampedElement::getModificationTime());
    } else {
        return (BaseStampedElement::getModificationTime());
    }
}

} // end of namespace ddns_tuning
} // end of namespace isc
