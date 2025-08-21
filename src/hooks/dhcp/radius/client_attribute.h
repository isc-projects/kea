// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_CLIENT_ATTRIBUTE_H
#define RADIUS_CLIENT_ATTRIBUTE_H

#include <exceptions/exceptions.h>
#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <asiolink/io_address.h>
#include <client_dictionary.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace isc {
namespace radius {

/// @brief Maximum string size.
static constexpr size_t MAX_STRING_LEN = 253;

/// @brief Maximum vsa data size.
static constexpr size_t MAX_VSA_DATA_LEN = MAX_STRING_LEN - 4;

/// @brief Type error.
using isc::data::TypeError;

/// @brief Shared pointers to Attribute object.
class Attribute;
typedef boost::shared_ptr<Attribute> AttributePtr;
typedef boost::shared_ptr<const Attribute> ConstAttributePtr;

/// @brief RADIUS attribute base class.
class Attribute : public data::CfgToElement {
protected:

    /// @brief Constructor.
    ///
    /// Called from derived classes.
    ///
    /// @param type attribute type.
    explicit Attribute(const uint8_t type) : type_(type) {
    }

public:
    /// @brief Virtual destructor.
    virtual ~Attribute() = default;

    /// @brief Get type.
    ///
    /// @return the type.
    uint8_t getType() const {
        return (type_);
    }

    /// @brief Get value type.
    ///
    /// @return the value type.
    virtual AttrValueType getValueType() const = 0;

    /// Generic factories.

    /// @brief From bytes (wire format).
    ///
    /// @param bytes binary attribute.
    /// @return pointer to the attribute or null.
    /// @throw BadValue on errors other than the definition can't be found.
    static AttributePtr fromBytes(const std::vector<uint8_t>& bytes);

    /// From definition generic factories.

    /// @brief From text with definition (handle vendor).
    ///
    /// Handle Vendor-Specific encapsulation.
    ///
    /// @param def pointer to attribute definition.
    /// @param value textual value.
    /// @return pointer to the attribute.
    /// @throw BadValue on errors.
    static AttributePtr fromText(const AttrDefPtr& def,
                                 const std::string& value);

    /// @brief From bytes with definition (handle vendor).
    ///
    /// Handle Vendor-Specific encapsulation.
    ///
    /// @param def pointer to attribute definition.
    /// @param value binary value.
    /// @return pointer to the attribute.
    /// @throw BadValue on errors.
    static AttributePtr fromBytes(const AttrDefPtr& def,
                                  const std::vector<uint8_t>& value);

    /// From type specific factories.
    ///
    /// @note: should be used only for internal create of standard attributes.

    /// @brief From string with type.
    ///
    /// @note Requires the type to be of a standard string attribute.
    ///
    /// @param type type of attribute.
    /// @param value string value.
    static AttributePtr fromString(const uint8_t type,
                                   const std::string& value);

    /// @brief From binary with type.
    ///
    /// @note Requires the type to be of a standard string attribute.
    ///
    /// @param type type of attribute.
    /// @param value binary value.
    static AttributePtr fromBinary(const uint8_t type,
                                   const std::vector<uint8_t>& value);

    /// @brief From integer with type.
    ///
    /// @note Requires the type to be of a standard integer attribute.
    ///
    /// @param type type of attribute.
    /// @param value integer value.
    static AttributePtr fromInt(const uint8_t type, const uint32_t value);

    /// @brief From IPv4 address with type.
    ///
    /// @note Requires the type to be of a standard ipaddr attribute.
    ///
    /// @param type type of attribute.
    /// @param value IPv4 address.
    static AttributePtr fromIpAddr(const uint8_t type,
                                   const asiolink::IOAddress& value);

    /// @brief From IPv6 address with type.
    ///
    /// @note Requires the type to be of a standard ipv6addr attribute.
    ///
    /// @param type type of attribute.
    /// @param value IPv6 address.
    static AttributePtr fromIpv6Addr(const uint8_t type,
                                     const asiolink::IOAddress& value);

    /// @brief From IPv6 prefix with type.
    ///
    /// @note Requires the type to be of a standard ipv6prefix attribute.
    ///
    /// @param type type of attribute.
    /// @param len prefix length.
    /// @param value IPv6 address.
    static AttributePtr fromIpv6Prefix(const uint8_t type,
                                       const uint8_t len,
                                       const asiolink::IOAddress& value);

    /// @brief From Vendor ID and string data with type.
    ///
    /// @note Requires the type to be of a standard vsa attribute.
    ///
    /// @param type type of attribute.
    /// @param vendor vendor id.
    /// @param value vsa data.
    static AttributePtr fromVsa(const uint8_t type,
                                const uint32_t vendor,
                                const std::string& value);

    /// @brief From Vendor ID and binary data with type.
    ///
    /// @note Requires the type to be of the Vendor Specific attribute (26).
    ///
    /// @param type type of attribute.
    /// @param vendor vendor id.
    /// @param value vsa data.
    static AttributePtr fromVsa(const uint8_t type,
                                const uint32_t vendor,
                                const std::vector<uint8_t>& value);

    /// Generic get methods.

    /// @brief Value length.
    ///
    /// @return Value length.
    virtual size_t getValueLen() const = 0;

    /// @brief Returns text representation of the attribute.
    ///
    /// @param indent number of spaces before printing text.
    /// @return string with text representation.
    virtual std::string toText(size_t indent = 0) const = 0;

    /// @brief To bytes (wire format).
    ///
    /// @return binary representation.
    virtual std::vector<uint8_t> toBytes() const = 0;

    /// Specific get methods.
    ///
    /// @note: should be used only for standard or type checked attributes.

    /// @brief To string.
    ///
    /// @return the string value.
    /// @throw TypeError if the attribute is not a string one.
    virtual std::string toString() const;

    /// @brief To binary.
    ///
    /// @return the string value as a binary.
    /// @throw TypeError if the attribute is not a string one.
    virtual std::vector<uint8_t> toBinary() const;

    /// @brief To integer.
    ///
    /// @return the integer value.
    /// @throw TypeError if the attribute is not an integer one.
    virtual uint32_t toInt() const;

    /// @brief To IPv4 address.
    ///
    /// @return the IPv4 address value.
    /// @throw TypeError if the attribute is not an ipaddr one.
    virtual asiolink::IOAddress toIpAddr() const;

    /// @brief To IPv6 address.
    ///
    /// @return the IPv6 address value.
    /// @throw TypeError if the attribute is not an ipv6addr one.
    virtual asiolink::IOAddress toIpv6Addr() const;

    /// @brief To IPv6 prefix.
    ///
    /// @return the IPv6 address value.
    /// @throw TypeError if the attribute is not an ipv6prefix one.
    virtual asiolink::IOAddress toIpv6Prefix() const;

    /// @brief To IPv6 prefix length.
    ///
    /// @return the IPv6 prefix length.
    /// @throw TypeError if the attribute is not an ipv6prefix one.
    virtual uint8_t toIpv6PrefixLen() const;

    /// @brief To vendor id.
    ///
    /// @return the vendor id.
    /// @throw TypeError if the attribute is not a vsa one.
    virtual uint32_t toVendorId() const;

    /// @brief To vsa data.
    ///
    /// @return the vsa data.
    /// @throw TypeError if the attribute is not a vsa one.
    virtual std::vector<uint8_t> toVsaData() const;

    /// @brief Type.
    const uint8_t type_;

private:

    /// @brief From text with definition.
    ///
    /// @param def pointer to attribute definition.
    /// @param value textual value.
    /// @return pointer to the attribute.
    /// @throw BadValue on errors.
    static AttributePtr fromText0(const AttrDefPtr& def,
                                  const std::string& value);

    /// @brief From bytes with definition.
    ///
    /// @param def pointer to attribute definition.
    /// @param value binary value.
    /// @return pointer to the attribute.
    /// @throw BadValue on errors.
    static AttributePtr fromBytes0(const AttrDefPtr& def,
                                   const std::vector<uint8_t>& value);
};

/// @brief RADIUS attribute derived classes: do not use them directly
/// outside unit tests, instead use Attribute class/static factory methods.

/// @brief RADIUS attribute holding strings.
class AttrString : public Attribute {
protected:

    /// @brief Constructor.
    ///
    /// @param type attribute type.
    /// @param value string value.
    AttrString(const uint8_t type, const std::string& value)
        : Attribute(type), value_(value) {
        if (value.empty()) {
            isc_throw(BadValue, "value is empty");
        }
        if (value.size() > MAX_STRING_LEN) {
            isc_throw(BadValue, "value is too large " << value.size()
                      << " > " << MAX_STRING_LEN);
        }
    }

    /// @brief Constructor.
    ///
    /// @param type attribute type.
    /// @param value binary value.
    AttrString(const uint8_t type, const std::vector<uint8_t>& value);

    /// @brief From text.
    ///
    /// @param type attribute type.
    /// @param repr value representation.
    /// @return pointer to the attribute or null.
    static AttributePtr fromText(const uint8_t type, const std::string& repr);

    /// @brief From bytes.
    ///
    /// @param type attribute type.
    /// @param bytes binary value.
    /// @return pointer to the attribute or null.
    static AttributePtr fromBytes(const uint8_t type,
                                  const std::vector<uint8_t>& bytes);

    /// Make Attribute a friend class.
    friend class Attribute;

public:
    /// @brief Get value type.
    ///
    /// @return the value type.
    virtual AttrValueType getValueType() const override {
        return (PW_TYPE_STRING);
    }

    /// @brief Value length.
    ///
    /// @return Value length.
    virtual size_t getValueLen() const override {
        return (value_.size());
    }

    /// @brief Returns text representation of the attribute.
    ///
    /// @param indent number of spaces before printing text.
    /// @return string with text representation.
    virtual std::string toText(size_t indent = 0) const override;

    /// @brief To bytes.
    ///
    /// @return binary representation.
    virtual std::vector<uint8_t> toBytes() const override;

    /// @brief To string.
    ///
    /// @return the string value.
    virtual std::string toString() const override {
        return (value_);
    }

    /// @brief To binary.
    ///
    /// @return the string value as a binary.
    virtual std::vector<uint8_t> toBinary() const override;

    /// @brief Unparse attribute.
    ///
    /// @return a pointer to unparsed attribute.
    virtual data::ElementPtr toElement() const override;

private:
    /// @brief Value.
    std::string value_;
};

/// @brief RADIUS attribute holding integers.
class AttrInt : public Attribute {
protected:

    /// @brief Constructor (signed).
    ///
    /// @param type attribute type.
    /// @param value integer value.
    AttrInt(const uint8_t type, const int32_t value)
        : Attribute(type), value_(static_cast<uint32_t>(value)) {
    }

    /// @brief Constructor (unsigned).
    ///
    /// @param type attribute type.
    /// @param value integer value.
    AttrInt(const uint8_t type, const uint32_t value)
        : Attribute(type), value_(value) {
    }

    /// @brief From text.
    ///
    /// @param type attribute type.
    /// @param repr value representation.
    /// @return pointer to the attribute or null.
    static AttributePtr fromText(const uint8_t type, const std::string& repr);

    /// @brief From bytes.
    ///
    /// @param type attribute type.
    /// @param bytes binary value.
    /// @return pointer to the attribute or null.
    static AttributePtr fromBytes(const uint8_t type,
                                  const std::vector<uint8_t>& bytes);

    /// Make Attribute a friend class.
    friend class Attribute;

public:

    /// @brief Get value type.
    ///
    /// @return the value type.
    virtual AttrValueType getValueType() const override {
        return (PW_TYPE_INTEGER);
    }

    /// @brief Value length.
    ///
    /// @return Value length.
    virtual size_t getValueLen() const override {
        return (4);
    }

    /// @brief Returns text representation of the attribute.
    ///
    /// @param indent number of spaces before printing text.
    /// @return string with text representation.
    virtual std::string toText(size_t indent = 0) const override;

    /// @brief To bytes.
    ///
    /// @return binary representation.
    virtual std::vector<uint8_t> toBytes() const override;

    /// @brief To integer.
    ///
    /// @return the integer value.
    virtual uint32_t toInt() const override {
        return (value_);
    }

    /// @brief Unparse attribute.
    ///
    /// @return a pointer to unparsed attribute.
    virtual data::ElementPtr toElement() const override;

private:
    /// @brief Value.
    const uint32_t value_;
};

/// @brief RADIUS attribute holding IPv4 addresses.
class AttrIpAddr : public Attribute {
protected:

    /// @brief Constructor.
    ///
    /// @param type attribute type.
    /// @param value IP address value.
    AttrIpAddr(const uint8_t type, const asiolink::IOAddress& value)
        : Attribute(type), value_(value) {
        if (!value.isV4()) {
            isc_throw(BadValue, "not v4 address " << value);
        }
    }

    /// @brief From text.
    ///
    /// @param type attribute type.
    /// @param repr value representation.
    /// @return pointer to the attribute or null.
    static AttributePtr fromText(const uint8_t type, const std::string& repr);

    /// @brief From bytes.
    ///
    /// @param type attribute type.
    /// @param bytes binary value.
    /// @return pointer to the attribute or null.
    static AttributePtr fromBytes(const uint8_t type,
                                  const std::vector<uint8_t>& bytes);

    /// Make Attribute a friend class.
    friend class Attribute;

public:
    /// @brief Get value type.
    ///
    /// @return the value type.
    virtual AttrValueType getValueType() const override {
        return (PW_TYPE_IPADDR);
    }

    /// @brief Value length.
    ///
    /// @return Value length.
    virtual size_t getValueLen() const override {
        return (4);
    }

    /// @brief Returns text representation of the attribute.
    ///
    /// @param indent number of spaces before printing text.
    /// @return string with text representation.
    virtual std::string toText(size_t indent = 0) const override;

    /// @brief To bytes.
    ///
    /// @return binary representation.
    virtual std::vector<uint8_t> toBytes() const override;

    /// @brief To IPv4 address.
    ///
    /// @return the IPv4 address value.
    virtual asiolink::IOAddress toIpAddr() const override {
        return (value_);
    }

    /// @brief Unparse attribute.
    ///
    /// @return a pointer to unparsed attribute.
    virtual data::ElementPtr toElement() const override;

private:
    /// @brief Value.
    asiolink::IOAddress value_;
};

/// @brief RADIUS attribute holding IPv6 addresses.
class AttrIpv6Addr : public Attribute {
protected:

    /// @brief Constructor.
    ///
    /// @param type attribute type.
    /// @param value IPv6 address value.
    AttrIpv6Addr(const uint8_t type, const asiolink::IOAddress& value)
        : Attribute(type), value_(value) {
        if (!value.isV6()) {
            isc_throw(BadValue, "not v6 address " << value);
        }
    }

    /// @brief From text.
    ///
    /// @param type attribute type.
    /// @param repr value representation.
    /// @return pointer to the attribute or null.
    static AttributePtr fromText(const uint8_t type, const std::string& repr);

    /// @brief From bytes.
    ///
    /// @param type attribute type.
    /// @param bytes binary value.
    /// @return pointer to the attribute or null.
    static AttributePtr fromBytes(const uint8_t type,
                                  const std::vector<uint8_t>& bytes);

    /// Make Attribute a friend class.
    friend class Attribute;

public:

    /// @brief Get value type.
    ///
    /// @return the value type.
    virtual AttrValueType getValueType() const override {
        return (PW_TYPE_IPV6ADDR);
    }

    /// @brief Value length.
    ///
    /// @return Value length.
    virtual size_t getValueLen() const override {
        return (16);
    }

    /// @brief Returns text representation of the attribute.
    ///
    /// @param indent number of spaces before printing text.
    /// @return string with text representation.
    virtual std::string toText(size_t indent = 0) const override;

    /// @brief To bytes.
    ///
    /// @return binary representation.
    virtual std::vector<uint8_t> toBytes() const override;

    /// @brief To IPv6 address.
    ///
    /// @return the IPv6 address value.
    virtual asiolink::IOAddress toIpv6Addr() const override {
        return (value_);
    }

    /// @brief Unparse attribute.
    ///
    /// @return a pointer to unparsed attribute.
    virtual data::ElementPtr toElement() const override;

private:
    /// @brief Value.
    asiolink::IOAddress value_;
};

/// @brief RADIUS attribute holding IPv6 prefixes.
class AttrIpv6Prefix : public Attribute {
protected:

    /// @brief Constructor.
    ///
    /// @param type attribute type.
    /// @param len prefix length.
    /// @param value IPv6 address value.
    AttrIpv6Prefix(const uint8_t type, const uint8_t len,
                   const asiolink::IOAddress& value)
        : Attribute(type), len_(len), value_(value) {
        if (!value.isV6()) {
            isc_throw(BadValue, "not v6 address " << value);
        }
        if (len > 128) {
            isc_throw(BadValue, "too long prefix "
                      << static_cast<unsigned>(len));
        }
    }

    /// @brief From text.
    ///
    /// @param type attribute type.
    /// @param repr value representation.
    /// @return pointer to the attribute or null.
    static AttributePtr fromText(const uint8_t type, const std::string& repr);

    /// @brief From bytes.
    ///
    /// @param type attribute type.
    /// @param bytes binary value.
    /// @return pointer to the attribute or null.
    static AttributePtr fromBytes(const uint8_t type,
                                  const std::vector<uint8_t>& bytes);

    /// Make Attribute a friend class.
    friend class Attribute;

public:

    /// @brief Get value type.
    ///
    /// @return the value type.
    virtual AttrValueType getValueType() const override {
        return (PW_TYPE_IPV6PREFIX);
    }

    /// @brief Value length.
    ///
    /// @return Value length.
    virtual size_t getValueLen() const override {
        return (17);
    }

    /// @brief Returns text representation of the attribute.
    ///
    /// @param indent number of spaces before printing text.
    /// @return string with text representation.
    virtual std::string toText(size_t indent = 0) const override;

    /// @brief To bytes.
    ///
    /// @return binary representation.
    virtual std::vector<uint8_t> toBytes() const override;

    /// @brief To IPv6 prefix.
    ///
    /// @return the IPv6 address value.
    virtual asiolink::IOAddress toIpv6Prefix() const override {
        return (value_);
    }

    /// @brief To IPv6 prefix length.
    ///
    /// @return the IPv6 prefix length.
    virtual uint8_t toIpv6PrefixLen() const override {
        return (len_);
    }

    /// @brief Unparse attribute.
    ///
    /// @return a pointer to unparsed attribute.
    virtual data::ElementPtr toElement() const override;

private:
    /// @brief Prefix length.
    const uint8_t len_;

    /// @brief Value.
    asiolink::IOAddress value_;
};

/// @brief RADIUS attribute holding vsa.
class AttrVsa : public Attribute {
protected:

    /// @brief Constructor.
    ///
    /// @param type attribute type.
    /// @param vendor vendor id.
    /// @param value string vsa data.
    AttrVsa(const uint8_t type, const uint32_t vendor,
            const std::string& value)
        : Attribute(type), vendor_(vendor), value_(value) {
        if (value.empty()) {
            isc_throw(BadValue, "value is empty");
        }
        if (value.size() > MAX_VSA_DATA_LEN) {
            isc_throw(BadValue, "value is too large " << value.size()
                      << " > " << MAX_VSA_DATA_LEN);
        }
    }

    /// @brief Constructor.
    ///
    /// @param type attribute type.
    /// @param vendor vendor id.
    /// @param value binary vsa data.
    AttrVsa(const uint8_t type, const uint32_t vendor,
            const std::vector<uint8_t>& value);

    /// @brief From text.
    ///
    /// @param type attribute type.
    /// @param repr value representation.
    /// @return pointer to the attribute or null.
    /// @throw NotImplemented
    static AttributePtr fromText(const uint8_t type, const std::string& repr);

    /// @brief From bytes.
    ///
    /// @param type attribute type.
    /// @param bytes binary value.
    /// @return pointer to the attribute or null.
    static AttributePtr fromBytes(const uint8_t type,
                                  const std::vector<uint8_t>& bytes);

    /// Make Attribute a friend class.
    friend class Attribute;

public:

    /// @brief Get value type.
    ///
    /// @return the value type.
    virtual AttrValueType getValueType() const override {
        return (PW_TYPE_VSA);
    }

    /// @brief Value length.
    ///
    /// @return Value length.
    virtual size_t getValueLen() const override {
        return (4 + value_.size());
    }

    /// @brief Returns text representation of the attribute.
    ///
    /// @param indent number of spaces before printing text.
    /// @return string with text representation.
    virtual std::string toText(size_t indent = 0) const override;

    /// @brief To bytes.
    ///
    /// @return binary representation.
    virtual std::vector<uint8_t> toBytes() const override;

    /// @brief To vendor id.
    ///
    /// @return the vendor id.
    virtual uint32_t toVendorId() const override {
        return (vendor_);
    }

    /// @brief To vsa data.
    ///
    /// @return the vsa data.
    virtual std::vector<uint8_t> toVsaData() const override;

    /// @brief Unparse attribute.
    ///
    /// @return a pointer to unparsed attribute.
    virtual data::ElementPtr toElement() const override;

private:
    /// @brief Vendor id.
    uint32_t vendor_;

    /// @brief Value.
    std::string value_;
};


/// @brief Collection of attributes.
class Attributes : public data::CfgToElement {
public:

    /// @brief Type of the container.
    typedef boost::multi_index_container<
        // This container stores pointers to attributes.
        ConstAttributePtr,
        // Start specification of indexes here.
        boost::multi_index::indexed_by<
            // Sequenced index to keep insert order.
            boost::multi_index::sequenced<>,
            // Hash index for direct retrieval.
            boost::multi_index::hashed_non_unique<
                boost::multi_index::member<
                    Attribute, const uint8_t, &Attribute::type_
                >
            >
        >
    > AttributeContainer;

    /// @brief constructor.
    Attributes() : container_() {
    }

    /// @brief Copy constructor.
    ///
    /// @param other source attributes.
    Attributes(const Attributes& other) : container_(other.container_) {
    }

    /// @brief Destructor.
    virtual ~Attributes() {
        clear();
    }

    /// @brief Indicates the object is empty.
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

    /// @brief Adds instance of the attribute to the collection.
    ///
    /// @param attr Pointer to the attribute being added (can be null).
    void add(const ConstAttributePtr& attr);

    /// @brief Deletes an attribute from the collection.
    ///
    /// Delete only the first occurrence.
    ///
    /// @param type type of the attribute to delete.
    /// @return true if found.
    bool del(const uint8_t type);

    /// @brief Clear the collection.
    void clear() {
        container_.clear();
    }

    /// @brief Append another collection.
    ///
    /// @param other The other collection to be appended to this one.
    void append(const Attributes& other);

    /// @brief Counts instance of the attribute in the collection.
    ///
    /// @param type type of the attribute to count.
    /// @return count of attributes with the given type in the collection.
    size_t count(const uint8_t type) const;

    /// @brief Get instance of the attribute in the collection.
    ///
    /// @param type type of the attribute to retrieve.
    /// @return the first instance if exists.
    ConstAttributePtr get(const uint8_t type) const;

    /// @brief Returns text representation of the collection.
    ///
    /// @param indent number of spaces before printing text.
    /// @return string with text representation.
    std::string toText(size_t indent = 0) const;

    /// @brief Unparse collection.
    ///
    /// @return a pointer to unparsed collection.
    data::ElementPtr toElement() const override;

    /// @brief Parse collection.
    ///
    /// @brief attr_list the attribute list to parse.
    /// @return parsed collection.
    static Attributes fromElement(const data::ConstElementPtr& attr_list);

    /// @brief Get the iterator to the beginning.
    ///
    /// @return the iterator to the beginning.
    AttributeContainer::iterator begin() {
        return (container_.begin());
    }

    /// @brief Get the iterator to the beginning.
    ///
    /// @return the iterator to the beginning.
    AttributeContainer::const_iterator begin() const {
        return (container_.begin());
    }

    /// @brief Get the const iterator to the beginning.
    ///
    /// @return the const iterator to the beginning.
    AttributeContainer::const_iterator cbegin() const {
        return (container_.cbegin());
    }

    /// @brief Get the iterator to the past-the-end.
    ///
    /// @return the iterator to the past-the-end.
    AttributeContainer::iterator end() {
        return (container_.end());
    }

    /// @brief Get the iterator to the past-the-end.
    ///
    /// @return the iterator to the past-the-end.
    AttributeContainer::const_iterator end() const {
        return (container_.end());
    }

    /// @brief Get the const iterator to the past-the-end.
    AttributeContainer::const_iterator cend() const {
        return (container_.cend());
    }

protected:
    /// @brief The container.
    AttributeContainer container_;
};

/// @brief Shared pointers to attribute collection.
typedef boost::shared_ptr<Attributes> AttributesPtr;

} // end of namespace isc::radius
} // end of namespace isc

#endif
