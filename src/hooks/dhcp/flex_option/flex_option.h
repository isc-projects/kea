// Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FLEX_OPTION_H
#define FLEX_OPTION_H

#include <cc/data.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcp/std_option_defs.h>
#include <eval/evaluate.h>
#include <eval/token.h>
#include <util/strutil.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <map>
#include <string>

namespace isc {
namespace flex_option {

/// @brief Flex Option implementation.
///
/// The implementation can be divided into two parts:
///  - the configuration parsed and stored by load()
///  - the response packet processing performed by the process method
///
class FlexOptionImpl {
public:

    /// @brief Action.
    ///
    /// Currently supported actions are:
    ///  - add (if not already existing)
    ///  - supersede (as add but also when already existing)
    ///  - remove
    enum Action {
        NONE,
        ADD,
        SUPERSEDE,
        REMOVE
    };

    /// @brief Option configuration.
    ///
    /// Per option configuration.
    class OptionConfig {
    public:
        /// @brief Constructor.
        ///
        /// @param code the option code.
        /// @param def the option definition.
        OptionConfig(uint16_t code, isc::dhcp::OptionDefinitionPtr def);

        /// @brief Destructor.
        virtual ~OptionConfig();

        /// @brief Return option code.
        ///
        /// @return option code.
        uint16_t getCode() const {
            return (code_);
        }

        /// @brief Return option definition.
        ///
        /// @return option definition.
        isc::dhcp::OptionDefinitionPtr getOptionDef() const {
            return (def_);
        }

        /// @brief Set action.
        ///
        /// @param action the action.
        void setAction(Action action) {
            action_ = action;
        }

        /// @brief Return action.
        ///
        /// @return action.
        Action getAction() const {
            return (action_);
        }

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
        void setExpr(const isc::dhcp::ExpressionPtr& expr) {
            expr_ = expr;
        }

        /// @brief Get match expression.
        ///
        /// @return the match expression.
        const isc::dhcp::ExpressionPtr& getExpr() const {
            return (expr_);
        }

    private:
        /// @brief The code.
        uint16_t code_;

        /// @brief The option definition.
        /// @note This value is set only when csv-format is true.
        isc::dhcp::OptionDefinitionPtr def_;

        /// @brief The action.
        Action action_;

        /// @brief The textual expression.
        std::string text_;

        /// @brief The match expression.
        isc::dhcp::ExpressionPtr expr_;
    };

    /// @brief The type of shared pointers to option config.
    typedef boost::shared_ptr<OptionConfig> OptionConfigPtr;

    /// @brief The type of the option config map.
    typedef std::map<uint16_t, OptionConfigPtr> OptionConfigMap;

    /// @brief Constructor.
    FlexOptionImpl();

    /// @brief Destructor.
    ~FlexOptionImpl();

    /// @brief Get the option config map.
    ///
    /// @return The option config map.
    const OptionConfigMap& getOptionConfigMap() const {
        return (option_config_map_);
    }

    /// @brief Configure the Flex Option implementation.
    ///
    /// @param options The element with option config list.
    /// @throw BadValue and similar exceptions on error.
    void configure(isc::data::ConstElementPtr options);

    /// @brief Process a query / response pair.
    ///
    /// @tparam PktType The type of pointers to packets: Pkt4Ptr or Pkt6Ptr.
    /// @param universe The option universe: Option::V4 or Option::V6.
    /// @param query The query packet.
    /// @param response The response packet.
    template <typename PktType>
    void process(isc::dhcp::Option::Universe universe,
                 PktType query, PktType response) {
        for (auto pair : getOptionConfigMap()) {
            const OptionConfigPtr& opt_cfg = pair.second;
            std::string value;
            isc::dhcp::OptionBuffer buffer;
            isc::dhcp::OptionPtr opt = response->getOption(opt_cfg->getCode());
            isc::dhcp::OptionDefinitionPtr def = opt_cfg->getOptionDef();
            switch (opt_cfg->getAction()) {
            case NONE:
                break;
            case ADD:
                // Don't add if option is already there.
                if (opt) {
                    break;
                }
                value = isc::dhcp::evaluateString(*opt_cfg->getExpr(), *query);
                // Do nothing is the expression evaluates to empty.
                if (value.empty()) {
                    break;
                }
                // Set the value.
                if (def) {
                    std::vector<std::string> split_vec =
                            isc::util::str::tokens(value, ",", true);
                    opt = def->optionFactory(universe, opt_cfg->getCode(),
                                             split_vec);
                } else {
                    buffer.assign(value.begin(), value.end());
                    opt.reset(new isc::dhcp::Option(universe,
                                                    opt_cfg->getCode(),
                                                    buffer));
                }
                // Add the option.
                response->addOption(opt);
                logAction(ADD, opt_cfg->getCode(), value);
                break;
            case SUPERSEDE:
                // Do nothing is the expression evaluates to empty.
                value = isc::dhcp::evaluateString(*opt_cfg->getExpr(), *query);
                if (value.empty()) {
                    break;
                }
                // Remove the option if already there.
                while (opt) {
                    response->delOption(opt_cfg->getCode());
                    opt = response->getOption(opt_cfg->getCode());
                }
                // Set the value.
                if (def) {
                    std::vector<std::string> split_vec =
                            isc::util::str::tokens(value, ",", true);
                    opt = def->optionFactory(universe, opt_cfg->getCode(),
                                             split_vec);
                } else {
                    buffer.assign(value.begin(), value.end());
                    opt.reset(new isc::dhcp::Option(universe,
                                                    opt_cfg->getCode(),
                                                    buffer));
                }
                // Add the option.
                response->addOption(opt);
                logAction(SUPERSEDE, opt_cfg->getCode(), value);
                break;
            case REMOVE:
                // Nothing to remove if option is not present.
                if (!opt) {
                    break;
                }
                // Do nothing is the expression evaluates to false.
                if (!isc::dhcp::evaluateBool(*opt_cfg->getExpr(), *query)) {
                    break;
                }
                // Remove the option.
                while (opt) {
                    response->delOption(opt_cfg->getCode());
                    opt = response->getOption(opt_cfg->getCode());
                }
                logAction(REMOVE, opt_cfg->getCode(), "");
                break;
            }
        }
    }

    /// @brief Log the action.
    ///
    /// @param action The action.
    /// @param code The option code.
    /// @param value The option value ("" for remove).
    void logAction(Action action, uint16_t code, const std::string& value) const;

protected:
    /// @brief Get a mutable reference to the option config map
    ///
    /// @return The option config map.
    OptionConfigMap& getMutableOptionConfigMap() {
        return (option_config_map_);
    }

private:
    /// @brief The option config map (code and pointer to option config).
    OptionConfigMap option_config_map_;

    /// @brief Parse an option config.
    ///
    /// @param option The element with option config.
    /// @throw BadValue and similar exceptions on error.
    void parseOptionConfig(isc::data::ConstElementPtr option);

};

/// @brief The type of shared pointers to Flex Option implementations.
typedef boost::shared_ptr<FlexOptionImpl> FlexOptionImplPtr;

} // end of namespace flex_option
} // end of namespace isc
#endif
