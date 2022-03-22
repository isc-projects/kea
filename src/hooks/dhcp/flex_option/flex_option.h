// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FLEX_OPTION_H
#define FLEX_OPTION_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcp/classify.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_vendor.h>
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

    /// @brief Base option configuration.
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

        /// @brief Set client class.
        ///
        /// @param class_name the client class aka guard name.
        void setClass(const isc::dhcp::ClientClass& class_name) {
            class_ = class_name;
        }

        /// @brief Get client class.
        ///
        /// @return client class aka guard name.
        const isc::dhcp::ClientClass& getClass() const {
            return (class_);
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

        /// @brief The client class aka guard name.
        isc::dhcp::ClientClass class_;
    };

    /// @brief The type of shared pointers to option config.
    typedef boost::shared_ptr<OptionConfig> OptionConfigPtr;

    /// @brief The type of lists of shared pointers to option config.
    typedef std::list<OptionConfigPtr> OptionConfigList;

    /// @brief The type of the option config map.
    typedef std::map<uint16_t, OptionConfigList> OptionConfigMap;

    /// @brief Sub-option configuration.
    ///
    /// Per sub-option configuration.
    class SubOptionConfig : public OptionConfig {
    public:
        /// @brief Constructor.
        ///
        /// @param code the sub-option code.
        /// @param def the sub-option definition.
        /// @param container pointer to the container option.
        SubOptionConfig(uint16_t code, isc::dhcp::OptionDefinitionPtr def,
                        OptionConfigPtr container);

        /// @brief Destructor.
        virtual ~SubOptionConfig();

        /// @brief Set vendor id.
        ///
        /// @param vendor_id the vendor id.
        void setVendorId(uint32_t vendor_id) {
            vendor_id_ = vendor_id;
        }

        /// @brief Return vendor id.
        ///
        /// @return vendor id.
        uint32_t getVendorId() const {
            return (vendor_id_);
        }

        /// @brief Return container code.
        ///
        /// @return container code.
        uint16_t getContainerCode() const {
            return (container_->getCode());
        }

        /// @brief Return container definition.
        ///
        /// @return container definition.
        isc::dhcp::OptionDefinitionPtr getContainerDef() const {
            return (container_->getOptionDef());
        }

        /// @brief Return container client class.
        ///
        /// @return container client class name.
        const isc::dhcp::ClientClass& getContainerClass() const {
            return (container_->getClass());
        }

        /// @brief Set action on the container.
        ///
        /// @param action the action.
        void setContainerAction(Action action) {
            container_action_ = action;
        }

        /// @brief Return action on the container.
        ///
        /// @return action on the container.
        Action getContainerAction() const {
            return (container_action_);
        }

    private:
        /// @brief Pointer to the container option configuration.
        OptionConfigPtr container_;

        /// @brief Vendor id (0 when the container is not a vendor one).
        uint32_t vendor_id_;

        /// @brief The action on the container.
        Action container_action_;
    };

    /// @brief The type of shared pointers to sub-option config.
    typedef boost::shared_ptr<SubOptionConfig> SubOptionConfigPtr;

    /// @brief The type of the sub-option config map.
    /// @note the index is the sub-option code.
    typedef std::map<uint16_t, SubOptionConfigPtr> SubOptionConfigMap;

    /// @brief The type of the map of sub-option config maps.
    /// @note the index is the container option code.
    typedef std::map<uint16_t, SubOptionConfigMap> SubOptionConfigMapMap;

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

    /// @brief Get the sub-option config map of maps.
    ///
    /// @return The sub-option config map of maps.
    const SubOptionConfigMapMap& getSubOptionConfigMap() const {
        return (sub_option_config_map_);
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
            for (const OptionConfigPtr& opt_cfg : pair.second) {
                const isc::dhcp::ClientClass& client_class =
                    opt_cfg->getClass();
                if (!client_class.empty()) {
                    if (!query->inClass(client_class)) {
                        logClass(client_class, opt_cfg->getCode());
                        continue;
                    }
                }
                std::string value;
                isc::dhcp::OptionBuffer buffer;
                uint16_t code = opt_cfg->getCode();
                isc::dhcp::OptionPtr opt = response->getOption(code);
                isc::dhcp::OptionDefinitionPtr def = opt_cfg->getOptionDef();
                switch (opt_cfg->getAction()) {
                case NONE:
                    break;
                case ADD:
                    // Don't add if option is already there.
                    if (opt) {
                        break;
                    }
                    // Do nothing is the expression evaluates to empty.
                    value = isc::dhcp::evaluateString(*opt_cfg->getExpr(),
                                                      *query);
                    if (value.empty()) {
                        break;
                    }
                    // Set the value.
                    if (def) {
                        std::vector<std::string> split_vec =
                            isc::util::str::tokens(value, ",", true);
                        opt = def->optionFactory(universe, code, split_vec);
                    } else {
                        buffer.assign(value.begin(), value.end());
                        opt.reset(new isc::dhcp::Option(universe, code,
                                                        buffer));
                    }
                    // Add the option.
                    response->addOption(opt);
                    logAction(ADD, code, value);
                    break;
                case SUPERSEDE:
                    // Do nothing is the expression evaluates to empty.
                    value = isc::dhcp::evaluateString(*opt_cfg->getExpr(),
                                                      *query);
                    if (value.empty()) {
                        break;
                    }
                    // Set the value.
                    if (def) {
                        std::vector<std::string> split_vec =
                            isc::util::str::tokens(value, ",", true);
                        opt = def->optionFactory(universe, code,
                                                 split_vec);
                    } else {
                        buffer.assign(value.begin(), value.end());
                        opt.reset(new isc::dhcp::Option(universe,
                                                        code,
                                                        buffer));
                    }
                    // Remove the option if already there.
                    while (response->getOption(code)) {
                        response->delOption(code);
                    }
                    // Add the option.
                    response->addOption(opt);
                    logAction(SUPERSEDE, code, value);
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
                    while (response->getOption(code)) {
                        response->delOption(code);
                    }
                    logAction(REMOVE, code, "");
                    break;
                }
            }
        }
        for (auto pair : getSubOptionConfigMap()) {
            for (auto sub_pair : pair.second) {
                const SubOptionConfigPtr& sub_cfg = sub_pair.second;
                uint16_t sub_code = sub_cfg->getCode();
                uint16_t opt_code = sub_cfg->getContainerCode();
                const isc::dhcp::ClientClass& opt_class =
                    sub_cfg->getContainerClass();
                if (!opt_class.empty()) {
                    if (!query->inClass(opt_class)) {
                        logClass(opt_class, opt_code);
                        continue;
                    }
                }
                const isc::dhcp::ClientClass& sub_class =
                    sub_cfg->getClass();
                if (!sub_class.empty()) {
                    if (!query->inClass(sub_class)) {
                        logSubClass(sub_class, sub_code, opt_code);
                        continue;
                    }
                }
                std::string value;
                isc::dhcp::OptionBuffer buffer;
                isc::dhcp::OptionPtr opt = response->getOption(opt_code);
                isc::dhcp::OptionPtr sub;
                isc::dhcp::OptionDefinitionPtr def = sub_cfg->getOptionDef();
                uint32_t vendor_id = sub_cfg->getVendorId();
                switch (sub_cfg->getAction()) {
                case NONE:
                    break;
                case ADD:
                    // If no container and no magic add return
                    if (!opt && (sub_cfg->getContainerAction() != ADD)) {
                        break;
                    }
                    // Do nothing is the expression evaluates to empty.
                    value = isc::dhcp::evaluateString(*sub_cfg->getExpr(),
                                                      *query);
                    if (value.empty()) {
                        break;
                    }
                    // Check vendor id mismatch.
                    if (opt && vendor_id && !checkVendor(opt, vendor_id)) {
                        break;
                    }
                    // Don't add if sub-option is already there.
                    if (opt && opt->getOption(sub_code)) {
                        break;
                    }
                    // Set the value.
                    if (def) {
                        std::vector<std::string> split_vec =
                            isc::util::str::tokens(value, ",", true);
                        sub = def->optionFactory(universe, sub_code,
                                                 split_vec);
                    } else {
                        buffer.assign(value.begin(), value.end());
                        sub.reset(new isc::dhcp::Option(universe, sub_code,
                                                        buffer));
                    }
                    // If the container does not exist add it.
                    if (!opt) {
                        if (!vendor_id) {
                            opt.reset(new isc::dhcp::Option(universe,
                                                            opt_code));
                        } else {
                            opt.reset(new isc::dhcp::OptionVendor(universe,
                                                                  vendor_id));
                        }
                        response->addOption(opt);
                        if (vendor_id) {
                            logAction(ADD, opt_code, vendor_id);
                        } else {
                            logAction(ADD, opt_code, "");
                        }
                    }
                    // Add the sub-option.
                    opt->addOption(sub);
                    logSubAction(ADD, sub_code, opt_code, value);
                    break;
                case SUPERSEDE:
                    // If no container and no magic add return
                    if (!opt && (sub_cfg->getContainerAction() != ADD)) {
                        break;
                    }
                    // Do nothing is the expression evaluates to empty.
                    value = isc::dhcp::evaluateString(*sub_cfg->getExpr(),
                                                      *query);
                    if (value.empty()) {
                        break;
                    }
                    // Check vendor id mismatch.
                    if (opt && vendor_id && !checkVendor(opt, vendor_id)) {
                        break;
                    }
                    // Set the value.
                    if (def) {
                        std::vector<std::string> split_vec =
                            isc::util::str::tokens(value, ",", true);
                        sub = def->optionFactory(universe, sub_code,
                                                 split_vec);
                    } else {
                        buffer.assign(value.begin(), value.end());
                        sub.reset(new isc::dhcp::Option(universe, sub_code,
                                                        buffer));
                    }
                    // Remove the sub-option if already there.
                    if (opt) {
                        while (opt->getOption(sub_code)) {
                            opt->delOption(sub_code);
                        }
                    }
                    // If the container does not exist add it.
                    if (!opt) {
                        if (!vendor_id) {
                            opt.reset(new isc::dhcp::Option(universe,
                                                            opt_code));
                        } else {
                            opt.reset(new isc::dhcp::OptionVendor(universe,
                                                                  vendor_id));
                        }
                        response->addOption(opt);
                        if (vendor_id) {
                            logAction(ADD, opt_code, vendor_id);
                        } else {
                            logAction(ADD, opt_code, "");
                        }
                    }
                    // Add the sub-option.
                    opt->addOption(sub);
                    logSubAction(SUPERSEDE, sub_code, opt_code, value);
                    break;
                case REMOVE:
                    // Nothing to remove if container is not present.
                    if (!opt) {
                        break;
                    }
                    sub = opt->getOption(sub_code);
                    // Nothing to remove if sub-option is not present.
                    if (!sub) {
                        break;
                    }
                    // Do nothing is the expression evaluates to false.
                    if (!isc::dhcp::evaluateBool(*sub_cfg->getExpr(), *query)) {
                        break;
                    }
                    // Check vendor id mismatch.
                    if (opt && vendor_id && !checkVendor(opt, vendor_id)) {
                        break;
                    }
                    // Remove the sub-option.
                    while (opt->getOption(sub_code)) {
                        opt->delOption(sub_code);
                    }
                    logSubAction(REMOVE, sub_code, opt_code, "");
                    // Remove the empty container when wanted.
                    if ((sub_cfg->getContainerAction() == REMOVE) &&
                        opt->getOptions().empty()) {
                        response->delOption(opt_code);
                        logAction(REMOVE, opt_code, "");
                    }
                    break;
                }
            }
        }
    }


    /// @brief Log the client class for option.
    ///
    /// @param client_class The client class aka guard name.
    /// @param code The option code.
    static void logClass(const isc::dhcp::ClientClass &client_class,
                         uint16_t code);

    /// @brief Log the action for option.
    ///
    /// @param action The action.
    /// @param code The option code.
    /// @param value The option value ("" for remove).
    static void logAction(Action action, uint16_t code,
                          const std::string& value);

    /// @brief Log the action for option.
    ///
    /// @param action The action.
    /// @param code The option code.
    /// @param vendor_id The vendor option vendor id.
    static void logAction(Action action, uint16_t code, uint32_t vendor_id);

    /// @brief Log the client class for sub-option.
    ///
    /// @param client_class The client class aka guard name.
    /// @param code The sub-option code.
    /// @param container_code The container option code.
    static void logSubClass(const isc::dhcp::ClientClass &client_class,
                            uint16_t code, uint16_t container_code);

    /// @brief Log the action for sub-option.
    ///
    /// @param action The action.
    /// @param code The sub-option code.
    /// @param container_code The container option code.
    /// @param value The option value ("" for remove).
    static void logSubAction(Action action, uint16_t code,
                             uint16_t container_code,
                             const std::string& value);

    /// @brief Check vendor option vendor id mismatch.
    ///
    /// @param opt The pointer to the option.
    /// @param vendor_id The vendor option vendor id.
    static bool checkVendor(isc::dhcp::OptionPtr opt, uint32_t vendor_id);

protected:
    /// @brief Get a mutable reference to the option config map
    ///
    /// @return The option config map.
    OptionConfigMap& getMutableOptionConfigMap() {
        return (option_config_map_);
    }

    /// @brief Get a mutable reference to the sub-option config map of maps.
    ///
    /// @return The sub-option config map of maps.
    SubOptionConfigMapMap& getMutableSubOptionConfigMap() {
        return (sub_option_config_map_);
    }

private:
    /// @brief Option parameters.
    static const data::SimpleKeywords OPTION_PARAMETERS;

    /// @brief Sub-option parameters.
    static const data::SimpleKeywords SUB_OPTION_PARAMETERS;

    /// @brief The option config map (code and pointer to option config).
    OptionConfigMap option_config_map_;

    /// @brief The sub-option config map of maps.
    SubOptionConfigMapMap sub_option_config_map_;

    /// @brief Parse an option config.
    ///
    /// @param option The element with option config.
    /// @throw BadValue and similar exceptions on error.
    void parseOptionConfig(isc::data::ConstElementPtr option);

    /// @brief Parse a sub-option.
    ///
    /// @param sub_option The sub-option element.
    /// @param opt_cfg The container option configuration.
    /// @param universe The universe.
    void parseSubOption(isc::data::ConstElementPtr sub_option,
                        OptionConfigPtr opt_cfg,
                        isc::dhcp::Option::Universe universe);

    /// @brief Parse sub-options.
    ///
    /// @param sub_options The sub-option list.
    /// @param opt_cfg The container option configuration.
    /// @param universe The universe.
    void parseSubOptions(isc::data::ConstElementPtr sub_options,
                         OptionConfigPtr opt_cfg,
                         isc::dhcp::Option::Universe universe);
};

/// @brief The type of shared pointers to Flex Option implementations.
typedef boost::shared_ptr<FlexOptionImpl> FlexOptionImplPtr;

} // end of namespace flex_option
} // end of namespace isc
#endif
