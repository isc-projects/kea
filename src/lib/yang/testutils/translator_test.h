// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_TEST_H
#define ISC_TRANSLATOR_TEST_H 1

#include <yang/translator.h>
#include <vector>
#include <iostream>

namespace isc {
namespace yang {
namespace test {

/// @brief Yang/sysrepo datastore textual representation class.
class YangRepr {
public:

    /// @brief Constructor.
    ///
    /// @param model The model name.
    YangRepr(const std::string& model) : model_(model) {
    }

    /// @brief The item class.
    struct YangReprItem {
        /// @brief Constructor with content.
        ///
        /// @param xpath The xpath.
        /// @param value The textual value.
        /// @param type The type of the value.
        /// @param settable The settable flag.
        YangReprItem(std::string xpath, std::string value,
                     sr_type_t type, bool settable)
            : xpath_(xpath), value_(value), type_(type), settable_(settable) {
        }

        /// @brief Factory from session.
        ///
        /// @param xpath The xpath.
        /// @param session Sysrepo session.
        static YangReprItem get(const std::string& xpath, S_Session session);

        /// @brief The xpath.
        std::string xpath_;

        /// @brief The textual value.
        std::string value_;

        /// @brief The type of the value.
        sr_type_t type_;

        /// @brief The settable flag.
        bool settable_;

        /// @brief The equal operator ignoring settable.
        bool operator==(const YangReprItem& other) const {
            return ((xpath_ == other.xpath_) &&
                    (value_ == other.value_) &&
                    (type_ == other.type_));
        }

        /// @brief The unequal operator ignoring settable.
        bool operator!=(const YangReprItem& other) const {
            return (!(*this == other));
        }
    };

    /// @brief Tree type.
    typedef std::vector<YangReprItem> Tree;

    /// @brief Get tree from session.
    ///
    /// @param session Sysrepo session.
    Tree get(S_Session session) const;

    /// @brief Verify tree.
    ///
    /// @param expected The expected value.
    /// @param session Sysrepo session.
    /// @param errs Error stream.
    /// @return True if verification succeeds, false with errors displayed
    /// on errs if it fails.
    bool verify(const Tree& expected, S_Session session,
                std::ostream& errs) const;

    /// @brief Set tree to session.
    ///
    /// @param tree The tree to install.
    /// @param session Sysrepo session.
    void set(const Tree& tree, S_Session session) const;

    /// @brief Validate.
    ///
    /// @param session Sysrepo session.
    /// @param errs Error stream.
    /// @return True if validation succeeds, false with errors displayed
    /// on errs if it fails.
    bool validate(S_Session session, std::ostream& errs) const;

    /// @brief The model name.
    std::string model_;
};

/// @brief Alias for Items.
typedef YangRepr::YangReprItem YRItem;

/// @brief Alias for Trees.
typedef YangRepr::Tree YRTree;

/// @brief Overrides standard output operator for sr_type_t.
std::ostream& operator<<(std::ostream& os, sr_type_t type);

/// @brief Overrides standard output operator for @c YangReprItem object.
std::ostream& operator<<(std::ostream& os, const YRItem& item);

/// @brief Overrides standard output operator for @c Tree object.
std::ostream& operator<<(std::ostream& os, const YRTree& tree);

}; // end of namespace isc::yang::test
}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_TRANSLATOR_TEST_H
