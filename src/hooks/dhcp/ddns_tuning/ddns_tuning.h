// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DDNS_TUNING_H
#define DDNS_TUNING_H

#include <cc/data.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <eval/evaluate.h>
#include <eval/token.h>
#include <util/strutil.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <map>
#include <string>

namespace isc {
namespace ddns_tuning {

/// @brief DDNS Tuning implementation.
///
/// The implementation can be divided into two parts:
///  - the configuration parsed and stored by load()
///  - the response packet processing performed by the process method
///
class DdnsTuningImpl {
public:

    /// @brief Set textual expression.
    ///
    /// @param text the textual expression.
    void setText(const std::string& text) {
        text_ = text;
    };

    /// @brief Get textual expression.
    ///
    /// @return textual expression.
    const std::string& getText() const {
        return (text_);
    }

    /// @brief Set match expression.
    ///
    /// @param expr the match expression.
    void setExpr(const isc::dhcp::ExpressionPtr expr) {
        expr_ = expr;
    }

    /// @brief Get match expression.
    ///
    /// @return the match expression.
    const isc::dhcp::ExpressionPtr& getExpr() const {
        return (expr_);
    }

    /// @brief Constructor.
    DdnsTuningImpl();

    /// @brief Destructor.
    ~DdnsTuningImpl();

    /// @brief Configure the Ddns Tuning implementation.
    ///
    /// @param hostname The JSON element with the expression.
    /// @throw BadValue and similar exceptions on error.
    void configure(isc::data::ConstElementPtr hostname);

    /// @brief Process a query / response pair.
    ///
    /// @tparam PktType The type of pointers to packets: Pkt4Ptr or Pkt6Ptr.
    /// @param universe The option universe: Option::V4 or Option::V6.
    /// @param query The query packet.
    /// @param response The response packet.
    template <typename PktType>
    void process(isc::dhcp::Option::Universe universe,
                 PktType query, PktType /*response*/) {
        std::string value = isc::dhcp::evaluateString(*getExpr(), *query);
        if (value.empty()) {
            return;
        }
    }

private:
    /// @brief The textual expression.
    std::string text_;

    /// @brief The match expression.
    isc::dhcp::ExpressionPtr expr_;
};

/// @brief The type of shared pointers to DDNS Tuning implementations.
typedef boost::shared_ptr<DdnsTuningImpl> DdnsTuningImplPtr;

} // end of namespace ddns_tuning
} // end of namespace isc
#endif
