// Copyright (C) 2011-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_int_array.h>
#include <dhcp/std_option_defs.h>
#include <dhcp/docsis3_option_defs.h>
#include <exceptions/exceptions.h>
#include <exceptions/isc_assert.h>
#include <util/buffer.h>

#include <boost/lexical_cast.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <limits>
#include <list>

using namespace std;
using namespace isc::dhcp;
using namespace isc::util;

namespace isc {
namespace dhcp {

namespace {

/// @brief the option definitions and the respective space mapping
///
/// used for easier initialization of option definitions by space name
const OptionDefParamsEncapsulation OPTION_DEF_PARAMS[] = {
    { STANDARD_V4_OPTION_DEFINITIONS,       STANDARD_V4_OPTION_DEFINITIONS_SIZE,     DHCP4_OPTION_SPACE          },
    { STANDARD_V6_OPTION_DEFINITIONS,       STANDARD_V6_OPTION_DEFINITIONS_SIZE,     DHCP6_OPTION_SPACE          },
    { DOCSIS3_V4_OPTION_DEFINITIONS,        DOCSIS3_V4_OPTION_DEFINITIONS_SIZE,      DOCSIS3_V4_OPTION_SPACE     },
    { DOCSIS3_V6_OPTION_DEFINITIONS,        DOCSIS3_V6_OPTION_DEFINITIONS_SIZE,      DOCSIS3_V6_OPTION_SPACE     },
    { ISC_V6_OPTION_DEFINITIONS,            ISC_V6_OPTION_DEFINITIONS_SIZE,          ISC_V6_OPTION_SPACE         },
    { MAPE_V6_OPTION_DEFINITIONS,           MAPE_V6_OPTION_DEFINITIONS_SIZE,         MAPE_V6_OPTION_SPACE        },
    { MAPT_V6_OPTION_DEFINITIONS,           MAPT_V6_OPTION_DEFINITIONS_SIZE,         MAPT_V6_OPTION_SPACE        },
    { LW_V6_OPTION_DEFINITIONS,             LW_V6_OPTION_DEFINITIONS_SIZE,           LW_V6_OPTION_SPACE          },
    { V4V6_RULE_OPTION_DEFINITIONS,         V4V6_RULE_OPTION_DEFINITIONS_SIZE,       V4V6_RULE_OPTION_SPACE      },
    { V4V6_BIND_OPTION_DEFINITIONS,         V4V6_BIND_OPTION_DEFINITIONS_SIZE,       V4V6_BIND_OPTION_SPACE      },
    { LAST_RESORT_V4_OPTION_DEFINITIONS,    LAST_RESORT_V4_OPTION_DEFINITIONS_SIZE,  LAST_RESORT_V4_OPTION_SPACE },
    { NULL,                                 0,                                       ""                          }
};

}  // namespace

}  // namespace dhcp
}  // namespace isc

// static array with factories for options
std::map<unsigned short, Option::Factory*> LibDHCP::v4factories_;

// static array with factories for options
std::map<unsigned short, Option::Factory*> LibDHCP::v6factories_;

// Static container with option definitions grouped by option space.
OptionDefContainers LibDHCP::option_defs_;

// Static container with option definitions created in runtime.
StagedValue<OptionDefSpaceContainer> LibDHCP::runtime_option_defs_;

// Null container.
const OptionDefContainerPtr null_option_def_container_(new OptionDefContainer());

// Those two vendor classes are used for cable modems:

/// DOCSIS3.0 compatible cable modem
const char* isc::dhcp::DOCSIS3_CLASS_MODEM = "docsis3.0";

/// DOCSIS3.0 cable modem that has router built-in
const char* isc::dhcp::DOCSIS3_CLASS_EROUTER = "eRouter1.0";

// Let's keep it in .cc file. Moving it to .h would require including optionDefParams
// definitions there
void initOptionSpace(OptionDefContainerPtr& defs,
                     const OptionDefParams* params,
                     size_t params_size);

bool LibDHCP::initialized_ = LibDHCP::initOptionDefs();

const OptionDefContainerPtr
LibDHCP::getOptionDefs(const std::string& space) {
    OptionDefContainers::const_iterator container = option_defs_.find(space);
    if (container != option_defs_.end()) {
        return (container->second);
    }

    return (null_option_def_container_);
}

const OptionDefContainerPtr
LibDHCP::getVendorOptionDefs(const Option::Universe u, const uint32_t vendor_id) {
    if (Option::V4 == u) {
        if (VENDOR_ID_CABLE_LABS == vendor_id) {
            return getOptionDefs(DOCSIS3_V4_OPTION_SPACE);
        }
    } else if (Option::V6 == u) {
        if (VENDOR_ID_CABLE_LABS == vendor_id) {
            return getOptionDefs(DOCSIS3_V6_OPTION_SPACE);
        } else if (ENTERPRISE_ID_ISC == vendor_id) {
            return getOptionDefs(ISC_V6_OPTION_SPACE);
        }
    }

    return (null_option_def_container_);
}

OptionDefinitionPtr
LibDHCP::getOptionDef(const std::string& space, const uint16_t code) {
    const OptionDefContainerPtr& defs = getOptionDefs(space);
    const OptionDefContainerTypeIndex& idx = defs->get<1>();
    const OptionDefContainerTypeRange& range = idx.equal_range(code);
    if (range.first != range.second) {
        return (*range.first);
    }

    return (OptionDefinitionPtr());
}

OptionDefinitionPtr
LibDHCP::getOptionDef(const std::string& space, const std::string& name) {
    const OptionDefContainerPtr& defs = getOptionDefs(space);
    const OptionDefContainerNameIndex& idx = defs->get<2>();
    const OptionDefContainerNameRange& range = idx.equal_range(name);
    if (range.first != range.second) {
        return (*range.first);
    }

    return (OptionDefinitionPtr());
}

OptionDefinitionPtr
LibDHCP::getVendorOptionDef(const Option::Universe u, const uint32_t vendor_id,
                            const std::string& name) {
    const OptionDefContainerPtr& defs = getVendorOptionDefs(u, vendor_id);

    if (!defs) {
        return (OptionDefinitionPtr());
    }

    const OptionDefContainerNameIndex& idx = defs->get<2>();
    const OptionDefContainerNameRange& range = idx.equal_range(name);
    if (range.first != range.second) {
        return (*range.first);
    }

    return (OptionDefinitionPtr());
}

OptionDefinitionPtr
LibDHCP::getVendorOptionDef(const Option::Universe u, const uint32_t vendor_id,
                            const uint16_t code) {
    const OptionDefContainerPtr& defs = getVendorOptionDefs(u, vendor_id);

    if (!defs) {
        // Weird universe or unknown vendor_id. We don't care. No definitions
        // one way or another
        // What is it anyway?
        return (OptionDefinitionPtr());
    }

    const OptionDefContainerTypeIndex& idx = defs->get<1>();
    const OptionDefContainerTypeRange& range = idx.equal_range(code);
    if (range.first != range.second) {
        return (*range.first);
    }

    return (OptionDefinitionPtr());
}

OptionDefinitionPtr
LibDHCP::getRuntimeOptionDef(const std::string& space, const uint16_t code) {
    OptionDefContainerPtr container = runtime_option_defs_.getValue().getItems(space);
    const OptionDefContainerTypeIndex& index = container->get<1>();
    const OptionDefContainerTypeRange& range = index.equal_range(code);
    if (range.first != range.second) {
        return (*range.first);
    }

    return (OptionDefinitionPtr());
}

OptionDefinitionPtr
LibDHCP::getRuntimeOptionDef(const std::string& space, const std::string& name) {
    OptionDefContainerPtr container = runtime_option_defs_.getValue().getItems(space);
    const OptionDefContainerNameIndex& index = container->get<2>();
    const OptionDefContainerNameRange& range = index.equal_range(name);
    if (range.first != range.second) {
        return (*range.first);
    }

    return (OptionDefinitionPtr());
}

OptionDefContainerPtr
LibDHCP::getRuntimeOptionDefs(const std::string& space) {
    return (runtime_option_defs_.getValue().getItems(space));
}

void
LibDHCP::setRuntimeOptionDefs(const OptionDefSpaceContainer& defs) {
    OptionDefSpaceContainer defs_copy;
    std::list<std::string> option_space_names = defs.getOptionSpaceNames();
    for (std::list<std::string>::const_iterator name = option_space_names.begin();
         name != option_space_names.end(); ++name) {
        OptionDefContainerPtr container = defs.getItems(*name);
        for (OptionDefContainer::const_iterator def = container->begin();
             def != container->end(); ++def) {
            OptionDefinitionPtr def_copy(new OptionDefinition(**def));
            defs_copy.addItem(def_copy);
        }
    }
    runtime_option_defs_ = defs_copy;
}

void
LibDHCP::clearRuntimeOptionDefs() {
    runtime_option_defs_.reset();
}

void
LibDHCP::revertRuntimeOptionDefs() {
    runtime_option_defs_.revert();
}

void
LibDHCP::commitRuntimeOptionDefs() {
    runtime_option_defs_.commit();
}

OptionDefinitionPtr
LibDHCP::getLastResortOptionDef(const std::string& space, const uint16_t code) {
    OptionDefContainerPtr container = getLastResortOptionDefs(space);
    const OptionDefContainerTypeIndex& index = container->get<1>();
    const OptionDefContainerTypeRange& range = index.equal_range(code);
    if (range.first != range.second) {
        return (*range.first);
    }

    return (OptionDefinitionPtr());
}

OptionDefinitionPtr
LibDHCP::getLastResortOptionDef(const std::string& space, const std::string& name) {
    OptionDefContainerPtr container = getLastResortOptionDefs(space);
    const OptionDefContainerNameIndex& index = container->get<2>();
    const OptionDefContainerNameRange& range = index.equal_range(name);
    if (range.first != range.second) {
        return (*range.first);
    }

    return (OptionDefinitionPtr());
}

OptionDefContainerPtr
LibDHCP::getLastResortOptionDefs(const std::string& space) {
    if (space == DHCP4_OPTION_SPACE) {
        return getOptionDefs(LAST_RESORT_V4_OPTION_SPACE);
    }

    return (null_option_def_container_);
}

bool
LibDHCP::shouldDeferOptionUnpack(const std::string& space, const uint16_t code) {
    return ((space == DHCP4_OPTION_SPACE) &&
            ((code == DHO_VENDOR_ENCAPSULATED_OPTIONS) ||
             ((code >= 224) && (code <= 254))));
}

OptionPtr
LibDHCP::optionFactory(Option::Universe u,
                       uint16_t type,
                       const OptionBuffer& buf) {
    FactoryMap::iterator it;
    if (u == Option::V4) {
        it = v4factories_.find(type);
        if (it == v4factories_.end()) {
            isc_throw(BadValue, "factory function not registered "
            "for DHCP v4 option type " << type);
        }
    } else if (u == Option::V6) {
        it = v6factories_.find(type);
        if (it == v6factories_.end()) {
            isc_throw(BadValue, "factory function not registered "
                      "for DHCPv6 option type " << type);
        }
    } else {
        isc_throw(BadValue, "invalid universe specified (expected "
                  "Option::V4 or Option::V6");
    }
    return (it->second(u, type, buf));
}


size_t
LibDHCP::unpackOptions6(const OptionBuffer& buf,
                        const std::string& option_space,
                        isc::dhcp::OptionCollection& options,
                        size_t* relay_msg_offset /* = 0 */,
                        size_t* relay_msg_len /* = 0 */) {
    size_t offset = 0;
    size_t length = buf.size();
    size_t last_offset = 0;

    // Get the list of standard option definitions.
    const OptionDefContainerPtr& option_defs = LibDHCP::getOptionDefs(option_space);
    // Runtime option definitions for non standard option space and if
    // the definition doesn't exist within the standard option definitions.
    const OptionDefContainerPtr& runtime_option_defs = LibDHCP::getRuntimeOptionDefs(option_space);

    // @todo Once we implement other option spaces we should add else clause
    // here and gather option definitions for them. For now leaving option_defs
    // empty will imply creation of generic Option.

    // Get the search indexes #1. It allows to search for option definitions
    // using option code.
    const OptionDefContainerTypeIndex& idx = option_defs->get<1>();
    const OptionDefContainerTypeIndex& runtime_idx = runtime_option_defs->get<1>();

    // The buffer being read comprises a set of options, each starting with
    // a two-byte type code and a two-byte length field.
    while (offset < length) {
        // Save the current offset for backtracking
        last_offset = offset;

        // Check if there is room for another option
        if (offset + 4 > length) {
            // Still something but smaller than an option
            return (last_offset);
        }

        // Parse the option header
        uint16_t opt_type = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        uint16_t opt_len = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        if (offset + opt_len > length) {
            // We peeked at the option header of the next option, but
            // discovered that it would end up beyond buffer end, so
            // the option is truncated. Hence we can't parse
            // it. Therefore we revert back by those bytes (as if
            // we never parsed them).
            //
            // @note it is the responsibility of the caller to throw
            // an exception on partial parsing
            return (last_offset);
        }

        if (opt_type == D6O_RELAY_MSG && relay_msg_offset && relay_msg_len) {
            // remember offset of the beginning of the relay-msg option
            *relay_msg_offset = offset;
            *relay_msg_len = opt_len;

            // do not create that relay-msg option
            offset += opt_len;
            continue;
        }

        if (opt_type == D6O_VENDOR_OPTS) {
            if (offset + 4 > length) {
                // Truncated vendor-option. We expect at least
                // 4 bytes for the enterprise-id field. Let's roll back
                // option code + option length (4 bytes) and return.
                return (last_offset);
            }

            // Parse this as vendor option
            OptionPtr vendor_opt(new OptionVendor(Option::V6, buf.begin() + offset,
                                                  buf.begin() + offset + opt_len));
            options.insert(std::make_pair(opt_type, vendor_opt));

            offset += opt_len;
            continue;
        }

        // Get all definitions with the particular option code. Note
        // that option code is non-unique within this container
        // however at this point we expect to get one option
        // definition with the particular code. If more are returned
        // we report an error.
        OptionDefContainerTypeRange range;
        // Number of option definitions returned.
        size_t num_defs = 0;

        // We previously did the lookup only for dhcp6 option space, but with the
        // addition of S46 options, we now do it for every space.
        range = idx.equal_range(opt_type);
        num_defs = std::distance(range.first, range.second);

        // Standard option definitions do not include the definition for
        // our option or we're searching for non-standard option. Try to
        // find the definition among runtime option definitions.
        if (num_defs == 0) {
            range = runtime_idx.equal_range(opt_type);
            num_defs = std::distance(range.first, range.second);
        }

        OptionPtr opt;
        if (num_defs > 1) {
            // Multiple options of the same code are not supported right now!
            isc_throw(isc::Unexpected, "Internal error: multiple option"
                      " definitions for option type " << opt_type <<
                      " returned. Currently it is not supported to initialize"
                      " multiple option definitions for the same option code."
                      " This will be supported once support for option spaces"
                      " is implemented");
        } else if (num_defs == 0) {
            // @todo Don't crash if definition does not exist because
            // only a few option definitions are initialized right
            // now. In the future we will initialize definitions for
            // all options and we will remove this elseif. For now,
            // return generic option.
            opt = OptionPtr(new Option(Option::V6, opt_type,
                                       buf.begin() + offset,
                                       buf.begin() + offset + opt_len));
        } else {
            try {
                // The option definition has been found. Use it to create
                // the option instance from the provided buffer chunk.
                const OptionDefinitionPtr& def = *(range.first);
                isc_throw_assert(def);
                opt = def->optionFactory(Option::V6, opt_type,
                                         buf.begin() + offset,
                                         buf.begin() + offset + opt_len);
            } catch (const SkipThisOptionError&)  {
                opt.reset();
            }
        }

        // add option to options
        if (opt) {
            options.insert(std::make_pair(opt_type, opt));
        }

        offset += opt_len;
    }

    last_offset = offset;
    return (last_offset);
}

size_t
LibDHCP::unpackOptions4(const OptionBuffer& buf,
                        const std::string& option_space,
                        isc::dhcp::OptionCollection& options,
                        std::list<uint16_t>& deferred,
                        bool flexible_pad_end) {
    size_t offset = 0;
    size_t last_offset = 0;

    // Special case when option_space is dhcp4.
    bool space_is_dhcp4 = (option_space == DHCP4_OPTION_SPACE);

    // Get the list of standard option definitions.
    const OptionDefContainerPtr& option_defs = LibDHCP::getOptionDefs(option_space);
    // Runtime option definitions for non standard option space and if
    // the definition doesn't exist within the standard option definitions.
    const OptionDefContainerPtr& runtime_option_defs = LibDHCP::getRuntimeOptionDefs(option_space);

    // Get the search indexes #1. It allows to search for option definitions
    // using option code.
    const OptionDefContainerTypeIndex& idx = option_defs->get<1>();
    const OptionDefContainerTypeIndex& runtime_idx = runtime_option_defs->get<1>();

    // Flexible PAD and END parsing.
    bool flex_pad = (flexible_pad_end && (runtime_idx.count(DHO_PAD) == 0));
    bool flex_end = (flexible_pad_end && (runtime_idx.count(DHO_END) == 0));

    // The buffer being read comprises a set of options, each starting with
    // a one-byte type code and a one-byte length field.
    while (offset < buf.size()) {
        // Save the current offset for backtracking
        last_offset = offset;

        // Get the option type
        uint8_t opt_type = buf[offset++];

        // DHO_END is a special, one octet long option
        // Valid in dhcp4 space or when flexible_pad_end is true and
        // there is a sub-option configured for this code.
        if ((opt_type == DHO_END) && (space_is_dhcp4 || flex_end)) {
            // just return. Don't need to add DHO_END option
            // Don't return offset because it makes this condition
            // and partial parsing impossible to recognize.
            return (last_offset);
        }

        // DHO_PAD is just a padding after DHO_END. Let's continue parsing
        // in case we receive a message without DHO_END.
        // Valid in dhcp4 space or when flexible_pad_end is true and
        // there is a sub-option configured for this code.
        if ((opt_type == DHO_PAD) && (space_is_dhcp4 || flex_pad)) {
            continue;
        }

        if (offset + 1 > buf.size()) {
            // We peeked at the option header of the next option, but
            // discovered that it would end up beyond buffer end, so
            // the option is truncated. Hence we can't parse
            // it. Therefore we revert back (as if we never parsed it).
            //
            // @note it is the responsibility of the caller to throw
            // an exception on partial parsing
            return (last_offset);
        }

        uint8_t opt_len =  buf[offset++];
        if (offset + opt_len > buf.size()) {
            // We peeked at the option header of the next option, but
            // discovered that it would end up beyond buffer end, so
            // the option is truncated. Hence we can't parse
            // it. Therefore we revert back (as if we never parsed it).
            return (last_offset);
        }

        // While an empty Host Name option is non-RFC compliant, some clients
        // do send it.  In the spirit of being liberal, we'll just drop it,
        // rather than the dropping the whole packet.  We do not have a
        // way to log this from here but meh...  a PCAP will show it arriving,
        // and we know we drop it.
        if (space_is_dhcp4 && opt_len == 0 && opt_type == DHO_HOST_NAME) {
            continue;
        }

        // Get all definitions with the particular option code. Note
        // that option code is non-unique within this container
        // however at this point we expect to get one option
        // definition with the particular code. If more are returned
        // we report an error.
        OptionDefContainerTypeRange range;
        // Number of option definitions returned.
        size_t num_defs = 0;

        // Previously we did the lookup only for "dhcp4" option space, but there
        // may be standard options in other spaces (e.g. radius). So we now do
        // the lookup for every space.
        range = idx.equal_range(opt_type);
        num_defs = std::distance(range.first, range.second);

        // Standard option definitions do not include the definition for
        // our option or we're searching for non-standard option. Try to
        // find the definition among runtime option definitions.
        if (num_defs == 0) {
            range = runtime_idx.equal_range(opt_type);
            num_defs = std::distance(range.first, range.second);
        }

        // Check if option unpacking must be deferred
        if (shouldDeferOptionUnpack(option_space, opt_type)) {
            num_defs = 0;
            deferred.push_back(opt_type);
        }

        OptionPtr opt;
        if (num_defs > 1) {
            // Multiple options of the same code are not supported right now!
            isc_throw(isc::Unexpected, "Internal error: multiple option"
                      " definitions for option type " <<
                      static_cast<int>(opt_type) <<
                      " returned. Currently it is not supported to initialize"
                      " multiple option definitions for the same option code."
                      " This will be supported once support for option spaces"
                      " is implemented");
        } else if (num_defs == 0) {
            opt = OptionPtr(new Option(Option::V4, opt_type,
                                       buf.begin() + offset,
                                       buf.begin() + offset + opt_len));
            opt->setEncapsulatedSpace(DHCP4_OPTION_SPACE);
        } else {
            try {
                // The option definition has been found. Use it to create
                // the option instance from the provided buffer chunk.
                const OptionDefinitionPtr& def = *(range.first);
                isc_throw_assert(def);
                opt = def->optionFactory(Option::V4, opt_type,
                                         buf.begin() + offset,
                                         buf.begin() + offset + opt_len);
            } catch (const SkipThisOptionError&)  {
                opt.reset();
            }
        }

        // If we have the option, insert it
        if (opt) {
            options.insert(std::make_pair(opt_type, opt));
        }

        offset += opt_len;
    }
    last_offset = offset;
    return (last_offset);
}

size_t
LibDHCP::unpackVendorOptions6(const uint32_t vendor_id,
                              const OptionBuffer& buf,
                              isc::dhcp::OptionCollection& options) {
    size_t offset = 0;
    size_t length = buf.size();

    // Get the list of option definitions for this particular vendor-id
    const OptionDefContainerPtr& option_defs =
        LibDHCP::getVendorOptionDefs(Option::V6, vendor_id);

    // Get the search index #1. It allows to search for option definitions
    // using option code. If there's no such vendor-id space, we're out of luck
    // anyway.
    const OptionDefContainerTypeIndex* idx = NULL;
    if (option_defs) {
        idx = &(option_defs->get<1>());
    }

    // The buffer being read comprises a set of options, each starting with
    // a two-byte type code and a two-byte length field.
    while (offset < length) {
        if (offset + 4 > length) {
            isc_throw(SkipRemainingOptionsError,
                      "Vendor option parse failed: truncated header");
        }

        uint16_t opt_type = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        uint16_t opt_len = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        if (offset + opt_len > length) {
            isc_throw(SkipRemainingOptionsError,
                      "Vendor option parse failed. Tried to parse "
                      << offset + opt_len << " bytes from " << length
                      << "-byte long buffer.");
        }

        OptionPtr opt;
        opt.reset();

        // If there is a definition for such a vendor option...
        if (idx) {
            // Get all definitions with the particular option
            // code. Note that option code is non-unique within this
            // container however at this point we expect to get one
            // option definition with the particular code. If more are
            // returned we report an error.
            const OptionDefContainerTypeRange& range =
                idx->equal_range(opt_type);
            // Get the number of returned option definitions for the
            // option code.
            size_t num_defs = std::distance(range.first, range.second);

            if (num_defs > 1) {
                // Multiple options of the same code are not supported
                // right now!
                isc_throw(isc::Unexpected, "Internal error: multiple option"
                          " definitions for option type " << opt_type <<
                          " returned. Currently it is not supported to"
                          " initialize multiple option definitions for the"
                          " same option code. This will be supported once"
                          " support for option spaces is implemented");
            } else if (num_defs == 1) {
                // The option definition has been found. Use it to create
                // the option instance from the provided buffer chunk.
                const OptionDefinitionPtr& def = *(range.first);
                isc_throw_assert(def);
                opt = def->optionFactory(Option::V6, opt_type,
                                         buf.begin() + offset,
                                         buf.begin() + offset + opt_len);
            }
        }

        // This can happen in one of 2 cases:
        // 1. we do not have definitions for that vendor-space
        // 2. we do have definitions, but that particular option was
        //    not defined

        if (!opt) {
            opt = OptionPtr(new Option(Option::V6, opt_type,
                                       buf.begin() + offset,
                                       buf.begin() + offset + opt_len));
        }

        // add option to options
        if (opt) {
            options.insert(std::make_pair(opt_type, opt));
        }
        offset += opt_len;
    }

    return (offset);
}

size_t
LibDHCP::unpackVendorOptions4(const uint32_t vendor_id, const OptionBuffer& buf,
                              isc::dhcp::OptionCollection& options) {
    size_t offset = 0;

    // Get the list of standard option definitions.
    const OptionDefContainerPtr& option_defs =
        LibDHCP::getVendorOptionDefs(Option::V4, vendor_id);
    // Get the search index #1. It allows to search for option definitions
    // using option code.
    const OptionDefContainerTypeIndex* idx = NULL;
    if (option_defs) {
        idx = &(option_defs->get<1>());
    }

    // The buffer being read comprises a set of options, each starting with
    // a one-byte type code and a one-byte length field.
    while (offset < buf.size()) {
        // Note that Vendor-Specific info option (RFC3925) has a
        // different option format than Vendor-Spec info for
        // DHCPv6. (there's additional layer of data-length)
        uint8_t data_len = buf[offset++];

        if (offset + data_len > buf.size()) {
            // The option is truncated.
            isc_throw(SkipRemainingOptionsError,
                      "Attempt to parse truncated vendor option");
        }

        uint8_t offset_end = offset + data_len;

        // beginning of data-chunk parser
        while (offset < offset_end) {
            uint8_t opt_type = buf[offset++];

            // No DHO_END or DHO_PAD in vendor options

            if (offset + 1 > offset_end) {
                // opt_type must be cast to integer so as it is not
                // treated as unsigned char value (a number is
                // presented in error message).
                isc_throw(SkipRemainingOptionsError,
                          "Attempt to parse truncated vendor option "
                          << static_cast<int>(opt_type));
            }

            uint8_t opt_len =  buf[offset++];
            if (offset + opt_len > offset_end) {
                isc_throw(SkipRemainingOptionsError,
                          "Option parse failed. Tried to parse "
                          << offset + opt_len << " bytes from " << buf.size()
                          << "-byte long buffer.");
            }

            OptionPtr opt;
            opt.reset();

            if (idx) {
                // Get all definitions with the particular option
                // code. Note that option code is non-unique within
                // this container however at this point we expect to
                // get one option definition with the particular
                // code. If more are returned we report an error.
                const OptionDefContainerTypeRange& range =
                    idx->equal_range(opt_type);
                // Get the number of returned option definitions for
                // the option code.
                size_t num_defs = std::distance(range.first, range.second);

                if (num_defs > 1) {
                    // Multiple options of the same code are not
                    // supported right now!
                    isc_throw(isc::Unexpected, "Internal error: multiple"
                              " option definitions for option type "
                              << opt_type << " returned. Currently it is"
                              " not supported to initialize multiple option"
                              " definitions for the same option code."
                              " This will be supported once support for"
                              " option spaces is implemented");
                } else if (num_defs == 1) {
                    // The option definition has been found. Use it to create
                    // the option instance from the provided buffer chunk.
                    const OptionDefinitionPtr& def = *(range.first);
                    isc_throw_assert(def);
                    opt = def->optionFactory(Option::V4, opt_type,
                                             buf.begin() + offset,
                                             buf.begin() + offset + opt_len);
                }
            }

            if (!opt) {
                opt = OptionPtr(new Option(Option::V4, opt_type,
                                           buf.begin() + offset,
                                           buf.begin() + offset + opt_len));
            }

            options.insert(std::make_pair(opt_type, opt));
            offset += opt_len;

        } // end of data-chunk

        break; // end of the vendor block.
    }
    return (offset);
}

void
LibDHCP::packOptions4(isc::util::OutputBuffer& buf,
                     const OptionCollection& options,
                     bool top /* = false */) {
    OptionPtr agent;
    OptionPtr end;

    // We only look for type when we're the top level
    // call that starts packing for options for a packet.
    // This way we avoid doing type logic in all ensuing
    // recursive calls.
    if (top) {
        auto x = options.find(DHO_DHCP_MESSAGE_TYPE);
        if (x != options.end()) {
            x->second->pack(buf);
        }
    }

    for (OptionCollection::const_iterator it = options.begin();
         it != options.end(); ++it) {

        // TYPE is already done, RAI and END options must be last.
        switch (it->first) {
            case DHO_DHCP_MESSAGE_TYPE:
                break;
            case DHO_DHCP_AGENT_OPTIONS:
                agent = it->second;
                break;
            case DHO_END:
                end = it->second;
                break;
            default:
                it->second->pack(buf);
                break;
        }
    }

    // Add the RAI option if it exists.
    if (agent) {
       agent->pack(buf);
    }

    // And at the end the END option.
    if (end)  {
       end->pack(buf);
    }
}

void
LibDHCP::packOptions6(isc::util::OutputBuffer& buf,
                      const OptionCollection& options) {
    for (OptionCollection::const_iterator it = options.begin();
         it != options.end(); ++it) {
        it->second->pack(buf);
    }
}

void
LibDHCP::OptionFactoryRegister(Option::Universe u,
                               uint16_t opt_type,
                               Option::Factory* factory) {
    switch (u) {
    case Option::V6:
    {
        if (v6factories_.find(opt_type) != v6factories_.end()) {
            isc_throw(BadValue, "There is already DHCPv6 factory registered "
                     << "for option type "  << opt_type);
        }
        v6factories_[opt_type] = factory;
        return;
    }
    case Option::V4:
    {
        // Option 0 is special (a one octet-long, equal 0) PAD option. It is never
        // instantiated as an Option object, but rather consumed during packet parsing.
        if (opt_type == 0) {
            isc_throw(BadValue, "Cannot redefine PAD option (code=0)");
        }
        // Option 255 is never instantiated as an option object. It is special
        // (a one-octet equal 255) option that is added at the end of all options
        // during packet assembly. It is also silently consumed during packet parsing.
        if (opt_type > 254) {
            isc_throw(BadValue, "Too big option type for DHCPv4, only 0-254 allowed.");
        }
        if (v4factories_.find(opt_type) != v4factories_.end()) {
            isc_throw(BadValue, "There is already DHCPv4 factory registered "
                     << "for option type "  << opt_type);
        }
        v4factories_[opt_type] = factory;
        return;
    }
    default:
        isc_throw(BadValue, "Invalid universe type specified.");
    }

    return;
}

bool
LibDHCP::initOptionDefs() {
    for (uint32_t i = 0; OPTION_DEF_PARAMS[i].optionDefParams; ++i) {
        std::string space = OPTION_DEF_PARAMS[i].space;
        option_defs_[space] = OptionDefContainerPtr(new OptionDefContainer);
        initOptionSpace(option_defs_[space],
                        OPTION_DEF_PARAMS[i].optionDefParams,
                        OPTION_DEF_PARAMS[i].size);
    }

    return (true);
}

uint32_t
LibDHCP::optionSpaceToVendorId(const std::string& option_space) {
    // 8 is a minimal length of "vendor-X" format
    if ((option_space.size() < 8) || (option_space.substr(0,7) != "vendor-")) {
        return (0);
    }

    int64_t check;
    try {
        // text after "vendor-", supposedly numbers only
        std::string x = option_space.substr(7);

        check = boost::lexical_cast<int64_t>(x);
    } catch (const boost::bad_lexical_cast &) {
        return (0);
    }

    if ((check < 0) || (check > std::numeric_limits<uint32_t>::max())) {
        return (0);
    }

    // value is small enough to fit
    return (static_cast<uint32_t>(check));
}

void
initOptionSpace(OptionDefContainerPtr& defs,
                const OptionDefParams* params,
                size_t params_size) {
    // Container holding vendor options is typically not initialized, as it
    // is held in map of null pointers. We need to initialize here in this
    // case.
    if (!defs) {
        defs.reset(new OptionDefContainer());
    } else {
        defs->clear();
    }

    for (size_t i = 0; i < params_size; ++i) {
        std::string encapsulates(params[i].encapsulates);
        if (!encapsulates.empty() && params[i].array) {
            isc_throw(isc::BadValue, "invalid standard option definition: "
                      << "option with code '" << params[i].code
                      << "' may not encapsulate option space '"
                      << encapsulates << "' because the definition"
                      << " indicates that this option comprises an array"
                      << " of values");
        }

        // Depending whether an option encapsulates an option space or not
        // we pick different constructor to create an instance of the option
        // definition.
        OptionDefinitionPtr definition;
        if (encapsulates.empty()) {
            // Option does not encapsulate any option space.
            definition.reset(new OptionDefinition(params[i].name,
                                                  params[i].code,
                                                  params[i].space,
                                                  params[i].type,
                                                  params[i].array));
        } else {
            // Option does encapsulate an option space.
            definition.reset(new OptionDefinition(params[i].name,
                                                  params[i].code,
                                                  params[i].space,
                                                  params[i].type,
                                                  params[i].encapsulates));

        }

        for (size_t rec = 0; rec < params[i].records_size; ++rec) {
            definition->addRecordField(params[i].records[rec]);
        }

        try {
            definition->validate();
        } catch (const isc::Exception&) {
            // This is unlikely event that validation fails and may
            // be only caused by programming error. To guarantee the
            // data consistency we clear all option definitions that
            // have been added so far and pass the exception forward.
            defs->clear();
            throw;
        }

        // option_defs is a multi-index container with no unique indexes
        // so push_back can't fail).
        static_cast<void>(defs->push_back(definition));
    }
}
