// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_ATTRIBUTE_H
#define CFG_ATTRIBUTE_H

#include <client_attribute.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <cc/cfg_to_element.h>
#include <dhcp/pkt.h>
#include <eval/token.h>
#include <util/buffer.h>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>

namespace isc {
namespace radius {

/// @brief Attribute data configuration.
///
/// It is used to store attribute types and values.
///
/// For example, it is able to store the following structure:
/// {
///     "name": "User-Name",
///     "type": 1,
///     "expr": "'foobar'"
/// }
class CfgAttributes : public data::CfgToElement {
public:

    /// @brief Constructor.
    CfgAttributes() : container_() {
    }

    // @brief Destructor.
    virtual ~CfgAttributes() {
        clear();
    }

    /// @brief Checks if the object is empty.
    ///
    /// @return true when the object is empty.
    bool empty() const {
        return (container_.empty());
    }

    /// @brief Returns the number of elements.
    ///
    /// @return the number of elements.
    size_t size() const {
        return (container_.size());
    }

    /// @brief Adds instance of the attribute to the configuration.
    ///
    /// @param def Pointer to the attribute definition.
    /// @param attr Pointer to the attribute being added.
    /// @param expr Expression to compute the value.
    /// @param test Original expression.
    void add(const AttrDefPtr& def,
             const ConstAttributePtr& attr,
             const dhcp::ExpressionPtr& expr,
             const std::string& test);

    /// @brief Adds instance of the attribute to the configuration.
    ///
    /// @param def Pointer to the attribute definition.
    /// @param attr Pointer to the attribute being added.
    void add(const AttrDefPtr& def, const ConstAttributePtr& attr) {
        add(def, attr, dhcp::ExpressionPtr(), "");
    }

    /// @brief Deletes an attribute from the configuration.
    ///
    /// Deletes only the first occurrence.
    ///
    /// @param type type of the attribute to delete.
    /// @return true if found.
    bool del(const uint8_t type);

    /// @brief Clear the container.
    void clear() {
        container_.clear();
    }

    /// @brief Counts instance of the attribute in the configuration.
    ///
    /// @param type type of the attribute to count.
    /// @return count of attributes with the given type in the configuration.
    size_t count(const uint8_t type) const {
        return (container_.count(type));
    }

    /// @brief Returns the definition of an attribute.
    ///
    /// @param type type of the attribute.
    /// @return the definition of the attribute.
    AttrDefPtr getDef(const uint8_t type) const;

    /// @brief Get instance of the attribute in the configuration.
    ///
    /// @param type type of the attribute to retrieve.
    /// @return the first instance if exists.
    ConstAttributePtr get(const uint8_t type) const;

    /// @brief Returns the expression of an attribute.
    ///
    /// @param type type of the attribute.
    /// @return the expression of the attribute.
    dhcp::ExpressionPtr getExpr(const uint8_t type) const;

    /// @brief Returns the text expression of an attribute.
    ///
    /// @param type type of the attribute.
    /// @return the text expression of the attribute.
    std::string getTest(const uint8_t type) const;

    /// @brief Get all attributes in the configuration.
    ///
    /// @return all attributes in the configuration.
    Attributes getAll() const;

    /// @brief Get all evaluated attributes in the configuration.
    ///
    /// When an attribute has an expression, evaluate the expression
    /// into a copy of the attribute. The attribute is skipped if
    /// the evaluation returns an empty string.
    ///
    /// @param pkt The v4 or v6 packet.
    /// @return all evaluated attributes in the configuration.
    Attributes getEvalAll(dhcp::Pkt& pkt);

    /// @brief Unparse configuration.
    ///
    /// @return a pointer to unparsed configuration.
    data::ElementPtr toElement() const override;

protected:
    /// @brief Container value class.
    class AttributeValue {
    public:
        /// @brief Constructor.
        ///
        /// @param def Pointer to the attribute definition.
        /// @param attr Pointer to the attribute.
        /// @param expr Expression to compute the value.
        /// @param test Original expression.
        AttributeValue(const AttrDefPtr& def,
                       const ConstAttributePtr& attr,
                       const dhcp::ExpressionPtr& expr,
                       const std::string& test)
            : def_(def), attr_(attr), expr_(expr), test_(test) {
            if (!def) {
                isc_throw(BadValue, "no attribute definition");
            }
            if (expr || !test.empty()) {
                if (attr) {
                    isc_throw(BadValue, "once of attribute or test");
                }
                if (!expr || test.empty()) {
                    isc_throw(BadValue, "missing expression or test");
                }
            } else if (!attr) {
                isc_throw(BadValue, "no attribute and test");
            }
        }

        /// @brief Pointer to the attribute definition (required).
        AttrDefPtr def_;

        /// @brief Pointer to the attribute.
        ConstAttributePtr attr_;

        /// @brief Expression to compute the value.
        dhcp::ExpressionPtr expr_;

        /// @brief Original expression.
        std::string test_;
    };

    /// @brief The container.
    std::multimap<uint8_t, AttributeValue> container_;
};

} // end of namespace isc::radius
} // end of namespace isc

#endif
