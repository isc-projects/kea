// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_CLIENT_DICTIONARY_H
#define RADIUS_CLIENT_DICTIONARY_H

#include <exceptions/exceptions.h>
#include <client.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <istream>
#include <list>
#include <unordered_map>
#include <string>

namespace isc {
namespace radius {

/// @brief Attribute value types.
///
/// Removed PW_TYPE_DATE as it is not used.
enum AttrValueType {
    PW_TYPE_STRING,
    PW_TYPE_INTEGER,
    PW_TYPE_IPADDR,
    PW_TYPE_IPV6ADDR,
    PW_TYPE_IPV6PREFIX,
    PW_TYPE_VSA
};

/// @brief AttrValueType value -> name function.
///
/// @param value value to translate to name.
/// @return the name of the value.
std::string attrValueTypeToText(const AttrValueType value);

/// @brief AttrValueType name -> value function.
///
/// The date value type is mapped to the compatible integer one.
///
/// @param name name of the value.
/// @return the value with the given name.
AttrValueType textToAttrValueType(const std::string& name);

/// @brief RADIUS attribute definition.
class AttrDef {
public:

    /// @brief Constructor.
    ///
    /// @param type attribute type.
    /// @param name attribute name.
    /// @param value_type attribute value type.
    /// @param vendor vendor id (default 0).
    AttrDef(const uint8_t type, const std::string& name,
            const AttrValueType value_type, const uint32_t vendor = 0)
    : type_(type), name_(name), value_type_(value_type), vendor_(vendor) {
    }

    /// @brief type.
    const uint8_t type_;

    /// @brief name.
    const std::string name_;

    /// @brief value_type.
    const AttrValueType value_type_;

    /// @brief vendor id (default 0).
    const uint32_t vendor_;
};

/// @brief Shared pointers to Attribute definition.
typedef boost::shared_ptr<AttrDef> AttrDefPtr;

/// @brief List of Attribute definitions.
typedef std::list<AttrDef> AttrDefList;

/// @brief RADIUS attribute aliases.
class AttrDefAlias {
public:

    /// @brief Constructor.
    ///
    /// @param alias attribute alias name.
    /// @param name attribute name.
    /// @param vendor vendor id (default 0).
    AttrDefAlias(const std::string& alias, const std::string& name,
                 const uint32_t vendor = 0)
    : alias_(alias), name_(name), vendor_(vendor) {
    }

    /// @brief alias.
    const std::string alias_;

    /// @brief name.
    const std::string name_;

    /// @brief vendor id (default 0).
    const uint32_t vendor_;
};

/// @brief RADIUS integer constant definitions.
///
/// Include vendor ids with Vendor-Specific attribute.
class IntCstDef {
public:

    /// @brief Constructor.
    ///
    /// @param type attribute type.
    /// @param name integer constant name.
    /// @param value integer constant value.
    IntCstDef(const uint8_t type, const std::string& name,
              const uint32_t value)
        : type_(type), name_(name), value_(value) {
    }

    /// @brief attribute type.
    const uint8_t type_;

    /// @brief name.
    const std::string name_;

    /// @brief value.
    const uint32_t value_;
};

/// @brief Shared pointers to Integer constant definition.
typedef boost::shared_ptr<IntCstDef> IntCstDefPtr;

/// @brief RADIUS attribute definitions.
class AttrDefs : public boost::noncopyable {
public:

    /// @brief Type of the attribute definition container.
    typedef boost::multi_index_container<
        // This container stores pointers to attribute definitions.
        AttrDefPtr,
        // Start specification of indexes here.
        boost::multi_index::indexed_by<
            // Hash index for by vendor and type.
            boost::multi_index::hashed_unique<
                boost::multi_index::composite_key<
                    AttrDef,
                    boost::multi_index::member<
                        AttrDef, const uint32_t, &AttrDef::vendor_
                    >,
                    boost::multi_index::member<
                        AttrDef, const uint8_t, &AttrDef::type_
                    >
                >
            >,
            // Hash index for by vendor and name.
            boost::multi_index::hashed_unique<
                boost::multi_index::composite_key<
                    AttrDef,
                    boost::multi_index::member<
                        AttrDef, const uint32_t, &AttrDef::vendor_
                    >,
                    boost::multi_index::member<
                        AttrDef, const std::string, &AttrDef::name_
                    >
                >
            >
        >
    > AttrDefContainer;

    /// @brief Type of the alias table (alias -> standard name map).
    typedef boost::multi_index_container<
        // This container stores aliases.
        AttrDefAlias,
        // Start specification of indexes here.
        boost::multi_index::indexed_by<
            // Hash index for by vendor and alias.
            boost::multi_index::hashed_unique<
                boost::multi_index::composite_key<
                    AttrDefAlias,
                    boost::multi_index::member<
                        AttrDefAlias, const uint32_t, &AttrDefAlias::vendor_
                    >,
                    boost::multi_index::member<
                        AttrDefAlias, const std::string, &AttrDefAlias::alias_
                    >
                >
            >
        >
    > AttrDefAliases;

    /// @brief Type of the integer constant definition container.
    typedef boost::multi_index_container<
        // This container stores pointers to integer constant definitions.
        IntCstDefPtr,
        // Start specification of indexes here.
        boost::multi_index::indexed_by<
            // Hash index for by type and name.
            boost::multi_index::hashed_unique<
                boost::multi_index::composite_key<
                    IntCstDef,
                    boost::multi_index::member<
                        IntCstDef, const uint8_t, &IntCstDef::type_
                    >,
                    boost::multi_index::member<
                        IntCstDef, const std::string, &IntCstDef::name_
                    >
                >
            >,
            // Hash index for by type and value.
            boost::multi_index::hashed_unique<
                boost::multi_index::composite_key<
                    IntCstDef,
                    boost::multi_index::member<
                        IntCstDef, const uint8_t, &IntCstDef::type_
                    >,
                    boost::multi_index::member<
                        IntCstDef, const uint32_t, &IntCstDef::value_
                    >
                >
            >
        >
    > IntCstDefContainer;

    /// @brief Returns a single instance.
    ///
    /// AttrDefs is a singleton and this method is the only way of accessing it.
    ///
    /// @return the single instance.
    static AttrDefs& instance();

    /// @brief Get attribute definition by type and vendor.
    ///
    /// @param type type to look for.
    /// @param vendor vendor id to look for (default 0).
    /// @return pointer to the attribute definition or null.
    AttrDefPtr getByType(const uint8_t type, const uint32_t vendor = 0) const;

    /// @brief Get attribute definition by name and vendor.
    ///
    /// @param name name to look for.
    /// @param vendor vendor id to look for (default 0).
    /// @return pointer to the attribute definition or null.
    AttrDefPtr getByName(const std::string& name,
                         const uint32_t vendor = 0) const;

    /// @brief Add (or replace) an attribute definition.
    ///
    /// @param def attribute definition to add or replace.
    void add(AttrDefPtr def);

    /// @brief Clear definitions.
    void clear() {
        container_.clear();
        aliases_.clear();
        ic_container_.clear();
    }

    /// @brief Get attribute name.
    ///
    /// @param type type to look for.
    /// @param vendor vendor id to look for (default 0).
    std::string getName(const uint8_t type, const uint32_t vendor = 0) const;

    /// @brief Get integer constant definition by attribute type and name.
    ///
    /// @param type attribute type.
    /// @param name name to look for.
    /// @return pointer to the integer constant definition or null.
    IntCstDefPtr getByName(const uint8_t type, const std::string& name) const;

    /// @brief Get integer constant definition by attribute type and value.
    ///
    /// @param type attribute type.
    /// @param value value to look for.
    /// @return pointer to the integer constant definition or null.
    IntCstDefPtr getByValue(const uint8_t type, const uint32_t value) const;

    /// @brief Add (or replace) an integer constant definition.
    ///
    void add(IntCstDefPtr def);

    /// @brief Read a dictionary from a file.
    ///
    /// Fills attribute and integer constant definition tables from
    /// a dictionary file. Recursion depth is initialized to 0,
    /// incremented by includes and limited to 5.
    ///
    /// @param path dictionary file path.
    /// @param depth recursion depth.
    void readDictionary(const std::string& path, unsigned int depth = 0);

    /// @brief Read a dictionary from an input stream.
    ///
    /// Fills attribute and integer constant definition tables from
    /// a dictionary input stream. Recursion depth is initialized to 0,
    /// incremented by includes and limited to 5.
    ///
    /// @param is input stream.
    /// @param depth recursion depth.
    void readDictionary(std::istream& is, unsigned int depth = 0);

    /// @brief Check if a list of standard attribute definitions
    /// are available and correct.
    ///
    /// @param defs list of standard attribute definitions.
    void checkStandardDefs(const AttrDefList& defs) const;

protected:
    /// @brief Contructor.
    AttrDefs() : container_(), aliases_(), ic_container_() {
    }

    /// @brief Destructor.
    virtual ~AttrDefs() {
        clear();
    }

    /// @brief Parse a dictionary line.
    ///
    /// @param line line to parse.
    /// @param depth recursion depth.
    void parseLine(const std::string& line, unsigned int depth);

    /// @brief Attribute definition container.
    AttrDefContainer container_;

    /// @brief Attribute aliases.
    AttrDefAliases aliases_;

    /// @brief Integer constant definition container.
    IntCstDefContainer ic_container_;
};

} // end of namespace isc::radius
} // end of namespace isc

#endif
