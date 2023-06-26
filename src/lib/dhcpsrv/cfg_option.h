// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_OPTION_H
#define CFG_OPTION_H

#include <dhcp/option.h>
#include <dhcp/option_space_container.h>
#include <cc/cfg_to_element.h>
#include <cc/stamped_element.h>
#include <cc/user_context.h>
#include <dhcpsrv/cfg_option_def.h>
#include <dhcpsrv/key_from_key.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <list>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

class OptionDescriptor;

/// A pointer to option descriptor.
typedef boost::shared_ptr<OptionDescriptor> OptionDescriptorPtr;

/// A list of option descriptors.
typedef std::vector<OptionDescriptor> OptionDescriptorList;

/// @brief Option descriptor.
///
/// Option descriptor holds instance of an option and additional information
/// for this option. This information comprises whether this option is sent
/// to DHCP client only on request (persistent = false) or always
/// (persistent = true), or must never send (cancelled = true).
class OptionDescriptor : public data::StampedElement, public data::UserContext {
public:
    /// @brief Option instance.
    OptionPtr option_;

    /// @brief Persistence flag.
    ///
    /// If true, option is always sent to the client. If false, option is
    /// sent to the client when requested using ORO or PRL option.
    bool persistent_;

    /// @brief Cancelled flag.
    ///
    /// If true, option is never sent to the client. If false, option is
    /// sent when it should.
    /// @note: When true the action of this flag is final i.e. it can't be
    /// overridden at a more specific level and has precedence over persist.
    bool cancelled_;

    /// @brief Option value in textual (CSV) format.
    ///
    /// This field is used to convey option value in human readable format,
    /// the same as used to specify option value in the server configuration.
    /// This value is optional and can be held in the host reservations
    /// database instead of the binary format.
    ///
    /// Note that this value is carried in the option descriptor, rather than
    /// @c Option instance because it is a server specific value (same as
    /// persistence flag).
    ///
    /// An example of the formatted value is: "2001:db8:1::1, 23, some text"
    /// for the option which carries IPv6 address, a number and a text.
    std::string formatted_value_;

    /// @brief Option space name.
    ///
    /// Options are associated with option spaces. Typically, such association
    /// is made when the option is stored in the @c OptionContainer. However,
    /// in some cases it is also required to associate option with the particular
    /// option space outside of the container. In particular, when the option
    /// is fetched from a database. The database configuration backend will
    /// set option space upon return of the option. In other cases this value
    /// won't be set.
    std::string space_name_;

    /// @brief Constructor.
    ///
    /// @param opt option instance.
    /// @param persist if true, option is always sent.
    /// @param cancel if true, option is never sent.
    /// @param formatted_value option value in the textual format (optional).
    /// @param user_context user context (optional).
    OptionDescriptor(const OptionPtr& opt, bool persist, bool cancel,
                     const std::string& formatted_value = "",
                     data::ConstElementPtr user_context = data::ConstElementPtr())
        : data::StampedElement(), option_(opt), persistent_(persist),
          cancelled_(cancel), formatted_value_(formatted_value),
          space_name_() {
        setContext(user_context);
    };

    /// @brief Constructor.
    ///
    /// @param persist if true option is always sent.
    /// @param cancel if true, option is never sent.
    OptionDescriptor(bool persist, bool cancel)
        : data::StampedElement(), option_(OptionPtr()), persistent_(persist),
          cancelled_(cancel), formatted_value_(), space_name_() {};

    /// @brief Copy constructor.
    ///
    /// @param desc option descriptor to be copied.
    OptionDescriptor(const OptionDescriptor& desc)
        : data::StampedElement(desc),
          option_(desc.option_),
          persistent_(desc.persistent_),
          cancelled_(desc.cancelled_),
          formatted_value_(desc.formatted_value_),
          space_name_(desc.space_name_) {
        setContext(desc.getContext());
    };

    /// @brief Assignment operator.
    ///
    /// @param other option descriptor to be assigned from.
    OptionDescriptor& operator=(const OptionDescriptor& other) {
        if (this != &other) {
            // Not self-assignment.
            data::StampedElement::operator=(other);
            option_ = other.option_;
            persistent_ = other.persistent_;
            cancelled_ = other.cancelled_;
            formatted_value_ = other.formatted_value_;
            space_name_ = other.space_name_;
            setContext(other.getContext());
        }
        return (*this);
    }

    /// @brief Factory function creating an instance of the @c OptionDescriptor.
    ///
    /// @param opt option instance.
    /// @param persist if true, option is always sent.
    /// @param cancel if true, option is never sent.
    /// @param formatted_value option value in the textual format (optional).
    /// @param user_context user context (optional).
    ///
    /// @return Pointer to the @c OptionDescriptor instance.
    static OptionDescriptorPtr create(const OptionPtr& opt,
                                      bool persist,
                                      bool cancel,
                                      const std::string& formatted_value = "",
                                      data::ConstElementPtr user_context =
                                      data::ConstElementPtr());

    /// @brief Factory function creating an instance of the @c OptionDescriptor.
    ///
    /// @param persist if true option is always sent.
    /// @param cancel if true, option is never sent.
    ///
    /// @return Pointer to the @c OptionDescriptor instance.
    static OptionDescriptorPtr create(bool persist, bool cancel);

    /// @brief Factory function creating an instance of the @c OptionDescriptor.
    ///
    /// @param desc option descriptor to be copied.
    ///
    /// @return Pointer to the @c OptionDescriptor instance.
    static OptionDescriptorPtr create(const OptionDescriptor& desc);

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
/// This container is the equivalent of four separate STL containers:
/// - std::list of all options,
/// - std::multimap of options with option code used as a multimap key,
/// - std::multimap of option descriptors with option persistency flag
/// used as a multimap key.
/// - std::multimap of option descriptors with option cancellation flag
/// used as a multimap key.
/// The major advantage of this container over 4 separate STL containers
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
        >,
        // Start definition of index #3.
        // Use BaseStampedElement::getModificationTime as a key.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::const_mem_fun<
                data::BaseStampedElement,
                boost::posix_time::ptime,
                &data::BaseStampedElement::getModificationTime
            >
        >,

        // Start definition of index #4.
        // Use BaseStampedElement::getId as a key.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<OptionIdIndexTag>,
            boost::multi_index::const_mem_fun<data::BaseStampedElement, uint64_t,
                                              &data::BaseStampedElement::getId>
        >,
        // Start definition of index #5.
        // Use 'cancelled' struct member as a key.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::member<
                OptionDescriptor,
                bool,
                &OptionDescriptor::cancelled_
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
/// Pair of iterators to represent the range of options having the
/// same persistency flag. The first element in this pair represents
/// the beginning of the range, the second element represents the end.
typedef std::pair<OptionContainerPersistIndex::const_iterator,
                  OptionContainerPersistIndex::const_iterator> OptionContainerPersistRange;
/// Type of the index #5 - option cancellation flag.
typedef OptionContainer::nth_index<5>::type OptionContainerCancelIndex;
/// Pair of iterators to represent the range of options having the
/// same cancellation flag. The first element in this pair represents
/// the beginning of the range, the second element represents the end.
typedef std::pair<OptionContainerCancelIndex::const_iterator,
                  OptionContainerCancelIndex::const_iterator> OptionContainerCancelRange;

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
class CfgOption : public isc::data::CfgToElement {
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
    /// @param cancelled Boolean value which specifies if the option must
    /// never be sent to the client.
    /// @param option_space Option space name.
    /// @param id Optional database id to be associated with the option.
    ///
    /// @throw isc::BadValue if the option space is invalid.
    void add(const OptionPtr& option, const bool persistent,
             const bool cancelled, const std::string& option_space,
             const uint64_t id = 0);

    /// @brief A variant of the @ref CfgOption::add method which takes option
    /// descriptor as an argument.
    ///
    /// @param desc Option descriptor holding option instance and other
    /// parameters pertaining to the option.
    /// @param option_space Option space name.
    ///
    /// @throw isc::BadValue if the option space is invalid.
    void add(const OptionDescriptor& desc, const std::string& option_space);

    /// @brief Replaces the instance of an option within this collection
    ///
    /// This method locates the option within the given space and replaces
    /// it with a copy of the given descriptor.  This effectively updates
    /// the contents without altering the container indexing.
    ///
    /// @param desc Option descriptor holding option instance and other
    /// parameters pertaining to the option.
    /// @param option_space Option space name.
    ///
    /// @throw isc::BadValue if the descriptor's option instance is null,
    /// if  space is invalid, or if the option does not already exist
    /// in the given space.
    void replace(const OptionDescriptor& desc, const std::string& option_space);

    /// @brief Merges another option configuration into this one.
    ///
    /// This method calls @c mergeTo() to add this configuration's
    /// options into @c other (skipping any duplicates).  Next it calls
    /// @c createDescriptorOption() for each option descriptor in the
    /// merged set.  This (re)-creates each descriptor's option based on
    /// the merged set of opt definitions. Finally, it calls
    /// @c copyTo() to overwrite this configuration's options with
    /// the merged set in @c other.
    ///
    /// @warning The merge operation will affect the @c other configuration.
    /// Therefore, the caller must not rely on the data held in the @c other
    /// object after the call to @c merge. Also, the data held in @c other must
    /// not be modified after the call to @c merge because it may affect the
    /// merged configuration.
    ///
    /// @param cfg_def set of of user-defined option definitions to use
    /// when merging.
    /// @param other option configuration to merge in.
    void merge(CfgOptionDefPtr cfg_def, CfgOption& other);

    /// @brief Re-create the option in each descriptor based on given definitions
    ///
    /// Invokes @c createDescriptorOption() on each option descriptor in
    /// each option space, passing in the given dictionary of option
    /// definitions.  If the descriptor's option is re-created, then the
    /// descriptor is updated by calling @c replace().
    ///
    /// @param cfg_def set of of user-defined option definitions to use
    /// when creating option instances.
    void createOptions(CfgOptionDefPtr cfg_def);

    /// @brief Creates an option descriptor's option based on a set of option defs
    ///
    /// This function's primary use is to create definition specific options for
    /// option descriptors fetched from a configuration backend, as part of a
    /// configuration merge.
    ///
    /// Given an OptionDescriptor whose option_ member contains a generic option
    /// (i.e has a code and/or data), this function will attempt to find a matching
    /// definition and then use that definition's factory to create an option
    /// instance specific to that definition.   It will then replace the descriptor's
    /// generic option with the specific option.
    ///
    /// Three sources of definitions are searched, in the following order:
    ///
    /// 1. Standard option definitions (@c LIBDHCP::getOptionDef))
    /// 2. Vendor option definitions (@c LIBDHCP::getVendorOptionDef))
    /// 3. User specified definitions passed in via cfg_def parameter.
    ///
    /// The code will use the first matching definition found.  It then applies
    /// the following rules:
    ///
    /// -# If no definition is found but the descriptor conveys a non-empty
    /// formatted value, throw an error.
    /// -# If not definition is found and there is no formatted value, return
    /// This leaves intact the generic option in the descriptor.
    /// -# If a definition is found and there is no formatted value, pass the
    /// descriptor's generic option's data into the definition's factory. Replace
    /// the descriptor's option with the newly created option.
    /// -# If a definition is found and there is a formatted value, split
    /// the value into vector of values and pass that into the definition's
    /// factory. Replace the descriptor's option with the newly created option.
    ///
    /// @param cfg_def the user specified definitions to use
    /// @param space the option space name of the option
    /// @param opt_desc OptionDescriptor describing the option.
    ///
    /// @return True if the descriptor's option instance was replaced.
    /// @throw InvalidOperation if the descriptor conveys a formatted value and
    /// there is no definition matching the option code in the given space, or
    /// if the definition factory invocation fails.
    static bool createDescriptorOption(CfgOptionDefPtr cfg_def, const std::string& space,
                             OptionDescriptor& opt_desc);

    /// @brief Merges this configuration to another configuration.
    ///
    /// This method iterates over the configuration items held in this
    /// configuration and copies them to the configuration specified
    /// as a parameter. If an item exists in the destination it is not
    /// copied.
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

    /// @brief Checks if options have been encapsulated.
    ///
    /// @return true if options have been encapsulated, false otherwise.
    bool isEncapsulated() const {
        return (encapsulated_);
    }

    /// @brief Returns all options for the specified option space.
    ///
    /// This method will not return vendor options, i.e. having option space
    /// name in the format of "vendor-X" where X is 32-bit unsigned integer.
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

    /// @brief Returns all non-vendor or vendor options for the specified
    /// option space.
    ///
    /// It combines the output of the @c getAll function variants. When
    /// option space has the format of "vendor-X", it retrieves the vendor
    /// options by vendor id, where X must be a 32-bit unsigned integer.
    /// Otherwise, it fetches non-vendor options.
    ///
    /// @param option_space Name of the option space.
    /// @return Pointer to the container holding returned options. This
    /// container is empty if no options have been found.
    OptionContainerPtr getAllCombined(const std::string& option_space) const;

    /// @brief Returns option for the specified key and option code.
    ///
    /// The key should be a string, in which case it specifies an option space
    /// name, or an uint32_t value, in which case it specifies a vendor
    /// identifier.
    ///
    /// @note If there are multiple options with the same key, only one will
    /// be returned.  No indication will be given of the presence of others,
    /// and the instance returned is not determinable. So please use
    /// the next method when multiple instances of the option are expected.
    ///
    /// @param key Option space name or vendor identifier.
    /// @param option_code Code of the option to be returned.
    /// @tparam Selector one of: @c std::string or @c uint32_t
    ///
    /// @return Descriptor of the option. If option hasn't been found, the
    /// descriptor holds null option.
    template<typename Selector>
    OptionDescriptor get(const Selector& key,
                         const uint16_t option_code) const {

        // Check for presence of options.
        OptionContainerPtr options = getAll(key);
        if (!options || options->empty()) {
            return (OptionDescriptor(false, false));
        }

        // Some options present, locate the one we are interested in.
        const OptionContainerTypeIndex& idx = options->get<1>();
        OptionContainerTypeIndex::const_iterator od_itr = idx.find(option_code);
        if (od_itr == idx.end()) {
            return (OptionDescriptor(false, false));
        }

        return (*od_itr);
    }

    /// @brief Returns options for the specified key and option code.
    ///
    /// The key should be a string, in which case it specifies an option space
    /// name, or an uint32_t value, in which case it specifies a vendor
    /// identifier.
    ///
    /// @param key Option space name or vendor identifier.
    /// @param option_code Code of the option to be returned.
    /// @tparam Selector one of: @c std::string or @c uint32_t
    ///
    /// @return List of Descriptors of the option.
    template<typename Selector>
    OptionDescriptorList getList(const Selector& key,
                                 const uint16_t option_code) const {

        OptionDescriptorList list;
        // Check for presence of options.
        OptionContainerPtr options = getAll(key);
        if (!options || options->empty()) {
            return (list);
        }

        // Some options present, locate the one we are interested in.
        const OptionContainerTypeIndex& idx = options->get<1>();
        OptionContainerTypeRange range = idx.equal_range(option_code);
        // This code copies descriptors and can be optimized not doing this.
        for (OptionContainerTypeIndex::const_iterator od_itr = range.first;
             od_itr != range.second; ++od_itr) {
            list.push_back(*od_itr);
        }

        return (list);
    }

    /// @brief Deletes option for the specified option space and option code.
    ///
    /// If the option is encapsulated within some non top level option space,
    /// it is also deleted from all option instances encapsulating this
    /// option space.
    ///
    /// @param option_space Option space name.
    /// @param option_code Code of the option to be returned.
    ///
    /// @return Number of deleted options.
    size_t del(const std::string& option_space, const uint16_t option_code);

    /// @brief Deletes vendor option for the specified vendor id.
    ///
    /// @param vendor_id Vendor identifier.
    /// @param option_code Option code.
    ///
    /// @return Number of deleted options.
    size_t del(const uint32_t vendor_id, const uint16_t option_code);

    /// @brief Deletes all options having a given database id.
    ///
    /// Note that there are cases when there will be multiple options
    /// having the same id (typically id of 0). When configuration backend
    /// is in use it sets the unique ids from the database. In cases when
    /// the configuration backend is not used, the ids default to 0.
    /// Passing the id of 0 would result in deleting all options that were
    /// not added via the database.
    ///
    /// Both regular and vendor specific options are deleted with this
    /// method.
    ///
    /// This method internally calls @c encapsulate() after deleting
    /// options having the given id.
    ///
    /// @param id Identifier of the options to be deleted.
    ///
    /// @return Number of deleted options. Note that if a single option
    /// instance is encapsulated by multiple options it adds 1 to the
    /// number of deleted options even though the same instance is
    /// deleted from multiple higher level options.
    size_t del(const uint64_t id);

    /// @brief Returns a list of configured option space names.
    ///
    /// The returned option space names exclude vendor option spaces,
    /// such as "vendor-1234". These are returned by the
    /// @ref getVendorIdsSpaceNames.
    ///
    /// @return List comprising option space names.
    std::list<std::string> getOptionSpaceNames() const {
        return (options_.getOptionSpaceNames());
    }

    /// @brief Returns a list of all configured  vendor identifiers.
    std::list<uint32_t> getVendorIds() const {
        return (vendor_options_.getOptionSpaceNames());
    }

    /// @brief Returns a list of option space names for configured vendor ids.
    ///
    /// For each vendor-id the option space name returned is constructed
    /// as "vendor-XYZ" where XYZ is a @c uint32_t value without leading
    /// zeros.
    ///
    /// @return List comprising option space names for vendor options.
    std::list<std::string> getVendorIdsSpaceNames() const;

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Unparse a configuration object with optionally including
    /// the metadata.
    ///
    /// @param include_metadata boolean value indicating if the metadata
    /// should be included (if true) or not (if false).
    ///
    /// @return A pointer to the unparsed configuration.
    isc::data::ElementPtr
    toElementWithMetadata(const bool include_metadata) const;

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

    /// @brief Appends encapsulated options from the option space encapsulated
    /// by the specified option.
    ///
    /// This method will go over all options belonging to the encapsulated space
    /// and will check which option spaces they encapsulate recursively,
    /// adding these options to the current option
    ///
    /// @param option which encapsulated options.
    void encapsulateInternal(const OptionPtr& option);

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

    /// @brief A flag indicating if options have been encapsulated.
    bool encapsulated_;

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
