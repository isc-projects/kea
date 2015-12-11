// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef CFG_OPTION_H
#define CFG_OPTION_H

#include <dhcp/option.h>
#include <dhcp/option_space_container.h>
#include <dhcpsrv/key_from_key.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <string>
#include <set>
#include <list>

namespace isc {
namespace dhcp {

/// @brief Option descriptor.
///
/// Option descriptor holds instance of an option and additional information
/// for this option. This information comprises whether this option is sent
/// to DHCP client only on request (persistent = false) or always
/// (persistent = true).
struct OptionDescriptor {
    /// Option instance.
    OptionPtr option_;
    /// Persistent flag, if true option is always sent to the client,
    /// if false option is sent to the client on request.
    bool persistent_;

    /// @brief Constructor.
    ///
    /// @param opt option
    /// @param persist if true option is always sent.
    OptionDescriptor(const OptionPtr& opt, bool persist)
        : option_(opt), persistent_(persist) {};

    /// @brief Constructor
    ///
    /// @param persist if true option is always sent.
    explicit OptionDescriptor(bool persist)
        : option_(OptionPtr()), persistent_(persist) {};

    /// @brief Checks if the one descriptor is equal to another.
    ///
    /// @param other Other option descriptor to compare to.
    ///
    /// @return true if descriptors equal, false otherwise.
    bool equals(const OptionDescriptor& other) const;

    /// @brief Equality operator.
    ///
    /// @param other Other option descriptor to compare to.
    ///
    /// @return true if descriptors equal, false otherwise.
    bool operator==(const OptionDescriptor& other) const {
        return (equals(other));
    }

    /// @brief Inequality operator.
    ///
    /// @param other Other option descriptor to compare to.
    ///
    /// @return true if descriptors unequal, false otherwise.
    bool operator!=(const OptionDescriptor& other) const {
        return (!equals(other));
    }
};

/// A pointer to option descriptor.
typedef boost::shared_ptr<OptionDescriptor> OptionDescriptorPtr;

/// @brief Multi index container for DHCP option descriptors.
///
/// This container comprises three indexes to access option
/// descriptors:
/// - sequenced index: used to access elements in the order they
/// have been added to the container,
/// - option type index: used to search option descriptors containing
/// options with specific option code (aka option type).
/// - persistency flag index: used to search option descriptors with
/// 'persistent' flag set to true.
///
/// This container is the equivalent of three separate STL containers:
/// - std::list of all options,
/// - std::multimap of options with option code used as a multimap key,
/// - std::multimap of option descriptors with option persistency flag
/// used as a multimap key.
/// The major advantage of this container over 3 separate STL containers
/// is automatic synchronization of all indexes when elements are added,
/// removed or modified in the container. With separate containers,
/// the synchronization would have to be guaranteed by the Subnet class
/// code. This would increase code complexity and presumably it would
/// be much harder to add new search criteria (indexes).
///
/// @todo we may want to search for options using option spaces when
/// they are implemented.
///
/// @see http://www.boost.org/doc/libs/1_51_0/libs/multi_index/doc/index.html
typedef boost::multi_index_container<
    // Container comprises elements of OptionDescriptor type.
    OptionDescriptor,
    // Here we start enumerating various indexes.
    boost::multi_index::indexed_by<
        // Sequenced index allows accessing elements in the same way
        // as elements in std::list.
        // Sequenced is an index #0.
        boost::multi_index::sequenced<>,
        // Start definition of index #1.
        boost::multi_index::hashed_non_unique<
            // KeyFromKeyExtractor is the index key extractor that allows
            // accessing option type being held by the OptionPtr through
            // OptionDescriptor structure.
            KeyFromKeyExtractor<
                // Use option type as the index key. The type is held
                // in OptionPtr object so we have to call Option::getType
                // to retrieve this key for each element.
                boost::multi_index::const_mem_fun<
                    Option,
                    uint16_t,
                    &Option::getType
                >,
                // Indicate that OptionPtr is a member of
                // OptionDescriptor structure.
                boost::multi_index::member<
                    OptionDescriptor,
                    OptionPtr,
                    &OptionDescriptor::option_
                 >
            >
        >,
        // Start definition of index #2.
        // Use 'persistent' struct member as a key.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::member<
                OptionDescriptor,
                bool,
                &OptionDescriptor::persistent_
            >
        >
    >
> OptionContainer;

/// Pointer to the OptionContainer object.
typedef boost::shared_ptr<OptionContainer> OptionContainerPtr;
/// Type of the index #1 - option type.
typedef OptionContainer::nth_index<1>::type OptionContainerTypeIndex;
/// Pair of iterators to represent the range of options having the
/// same option type value. The first element in this pair represents
/// the beginning of the range, the second element represents the end.
typedef std::pair<OptionContainerTypeIndex::const_iterator,
                  OptionContainerTypeIndex::const_iterator> OptionContainerTypeRange;
/// Type of the index #2 - option persistency flag.
typedef OptionContainer::nth_index<2>::type OptionContainerPersistIndex;

/// @brief Represents option data configuration for the DHCP server.
///
/// This class holds a collection of options to be sent to a DHCP client.
/// Options are grouped by the option space or vendor identifier (for
/// vendor options).
///
/// The server configuration allows for specifying two distinct collections
/// of options: global options and per-subnet options in which some options
/// may overlap.
///
/// The collection of global options specify options being sent to the client
/// belonging to any subnets, i.e. global options are "inherited" by all
/// subnets.
///
/// The per-subnet options are configured for a particular subnet and are sent
/// to clients which belong to this subnet. The values of the options specified
/// for a particular subnet override the values of the global options.
///
/// This class represents a single collection of options (either global or
/// per-subnet). Each subnet holds its own object of the @c CfgOption type. The
/// @c CfgMgr holds a @c CfgOption object representing global options.
///
/// Note that having a separate copy of the @c CfgOption to represent global
/// options is useful when the client requests stateless configuration from
/// the DHCP server and no subnet is selected for this client. This client
/// will only receive global options.
class CfgOption {
public:

    /// @brief default constructor
    CfgOption();

    /// @brief Indicates the object is empty
    ///
    /// @return true when the object is empty
    bool empty() const;

    /// @name Methods and operators used for comparing objects.
    ///
    //@{
    /// @brief Check if configuration is equal to other configuration.
    ///
    /// @param other An object holding configuration to compare to.
    ///
    /// @return true if configurations are equal, false otherwise.
    bool equals(const CfgOption& other) const;

    /// @brief Equality operator.
    ///
    /// @param other An object holding configuration to compare to.
    ///
    /// @return true if configurations are equal, false otherwise.
    bool operator==(const CfgOption& other) const {
        return (equals(other));
    }

    /// @brief Inequality operator.
    ///
    /// @param other An object holding configuration to compare to.
    ///
    /// @return true if configurations are unequal, false otherwise.
    bool operator!=(const CfgOption& other) const {
        return (!equals(other));
    }

    //@}

    /// @brief Adds instance of the option to the configuration.
    ///
    /// There are two types of options which may be passed to this method:
    /// - vendor options
    /// - non-vendor options
    ///
    /// The non-vendor options are grouped by the name of the option space
    /// (specified in textual format). The vendor options are grouped by the
    /// vendor identifier, which is a 32-bit unsigned integer value.
    ///
    /// In order to add new vendor option to the list the option space name
    /// (last argument of this method) should be specified as "vendor-X" where
    /// "X" is a 32-bit unsigned integer, e.g. "vendor-1234". Options for which
    /// the @c option_space argument doesn't follow this format are added as
    /// non-vendor options.
    ///
    /// @param option Pointer to the option being added.
    /// @param persistent Boolean value which specifies if the option should
    /// be sent to the client regardless if requested (true), or nor (false)
    /// @param option_space Option space name.
    ///
    /// @throw isc::BadValue if the option space is invalid.
    void add(const OptionPtr& option, const bool persistent,
             const std::string& option_space);

    /// @brief Merges this configuration to another configuration.
    ///
    /// This method iterates over the configuration items held in this
    /// configuration and copies them to the configuration specified
    /// as a parameter. If an item exists in the destination it is not
    /// copied.
    ///
    /// @note: this method is not longer used so should become private.
    ///
    /// @param [out] other Configuration object to merge to.
    void mergeTo(CfgOption& other) const;

    /// @brief Copies this configuration to another configuration.
    ///
    /// This method copies options configuration to another object.
    ///
    /// @param [out] other An object to copy the configuration to.
    void copyTo(CfgOption& other) const;

    /// @brief Appends encapsulated options to top-level options.
    ///
    /// This method iterates over the top-level options (from "dhcp4"
    /// and "dhcp6" option space) and checks which option spaces these
    /// options encapsulate. For each encapsulated option space, the
    /// options from this option space are appended to top-level options.
    void encapsulate();

    /// @brief Returns all options for the specified option space.
    ///
    /// This method will not return vendor options, i.e. having option space
    /// name in the format of "vendor-X" where X is 32-bit unsiged integer.
    /// See @c getAll(uint32_t) for vendor options.
    ///
    /// @param option_space Name of the option space.
    ///
    /// @return Pointer to the container holding returned options. This
    /// container is empty if no options have been found.
    OptionContainerPtr getAll(const std::string& option_space) const;

    /// @brief Returns vendor options for the specified vendor id.
    ///
    /// @param vendor_id Vendor id for which options are to be returned.
    ///
    /// @return Pointer to the container holding returned options. This
    /// container is empty if no options have been found.
    OptionContainerPtr getAll(const uint32_t vendor_id) const;

    /// @brief Returns option for the specified key and option code.
    ///
    /// The key should be a string, in which case it specifies an option space
    /// name, or an uint32_t value, in which case it specifies a vendor
    /// identifier.
    ///
    /// @note If there are multiple options with the same key, only one will
    /// be returned.  No indication will be given of the presence of others,
    /// and the instance returned is not determinable.
    ///
    /// @param key Option space name or vendor identifier.
    /// @param option_code Code of the option to be returned.
    /// @tparam Selector one of: @c std::string or @c uint32_t
    ///
    /// @return Descriptor of the option. If option hasn't been found, the
    /// descriptor holds NULL option.
    template<typename Selector>
    OptionDescriptor get(const Selector& key,
                         const uint16_t option_code) const {

        // Check for presence of options.
        OptionContainerPtr options = getAll(key);
        if (!options || options->empty()) {
            return (OptionDescriptor(false));
        }

        // Some options present, locate the one we are interested in.
        const OptionContainerTypeIndex& idx = options->get<1>();
        OptionContainerTypeIndex::const_iterator od_itr = idx.find(option_code);
        if (od_itr == idx.end()) {
            return (OptionDescriptor(false));
        }

        return (*od_itr);
    }

    /// @brief Converts option space name to vendor id.
    ///
    /// If the option space name is specified in the following format:
    /// "vendor-X" where X is an uint32_t number, it is assumed to be
    /// a vendor space and the uint32_t number is returned by this function.
    /// If the option space name is invalid this method will return 0, which
    /// is not a valid vendor-id, to signal an error.
    ///
    /// @todo remove this function once when the conversion is dealt by the
    /// appropriate functions returning options by option space names.
    ///
    /// @param option_space Option space name.
    /// @return vendor id.
    static uint32_t optionSpaceToVendorId(const std::string& option_space);

private:

    /// @brief Appends encapsulated options to the options in an option space.
    ///
    /// This method appends sub-options to the options belonging to the
    /// particular option space. For example: if the option space "foo"
    /// is specified, this function will go over all options belonging to
    /// "foo" and will check which option spaces they encapsulate. For each
    /// such option it will retrieve options for these option spaces and append
    /// as sub-options to options belonging to "foo".
    ///
    /// @param option_space Name of the option space containing option to
    /// which encapsulated options are appended.
    void encapsulateInternal(const std::string& option_space);

    /// @brief Merges data from two option containers.
    ///
    /// This method merges options from one option container to another
    /// option container. This function is templated because containers
    /// may use different type of selectors. For non-vendor options
    /// the selector is of the @c std::string type, for vendor options
    /// the selector is of the @c uint32_t type.
    ///
    /// @param src_container Reference to a container from which the data
    /// will be merged.
    /// @param [out] dest_container Reference to a container to which the
    /// data will be merged.
    /// @tparam Type of the selector: @c std::string or @c uint32_t.
    template <typename Selector>
    void mergeInternal(const OptionSpaceContainer<OptionContainer,
                       OptionDescriptor, Selector>& src_container,
                       OptionSpaceContainer<OptionContainer,
                       OptionDescriptor, Selector>& dest_container) const;

    /// @brief Type of the container holding options grouped by option space.
    typedef OptionSpaceContainer<OptionContainer, OptionDescriptor,
                                 std::string> OptionSpaceCollection;
    /// @brief Container holding options grouped by option space.
    OptionSpaceCollection options_;

    /// @brief Type of the container holding options grouped by vendor id.
    typedef OptionSpaceContainer<OptionContainer, OptionDescriptor,
                                 uint32_t> VendorOptionSpaceCollection;
    /// @brief Container holding options grouped by vendor id.
    VendorOptionSpaceCollection vendor_options_;
};

/// @name Pointers to the @c CfgOption objects.
//@{
/// @brief Non-const pointer.
typedef boost::shared_ptr<CfgOption> CfgOptionPtr;

/// @brief Const pointer.
typedef boost::shared_ptr<const CfgOption> ConstCfgOptionPtr;

/// @brief Const pointer list.
typedef std::list<ConstCfgOptionPtr> CfgOptionList;

//@}

}
}

#endif // CFG_OPTION_H
