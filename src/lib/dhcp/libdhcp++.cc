// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/buffer.h>
#include <dhcp/option_definition.h>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace isc::dhcp;
using namespace isc::util;

// static array with factories for options
std::map<unsigned short, Option::Factory*> LibDHCP::v4factories_;

// static array with factories for options
std::map<unsigned short, Option::Factory*> LibDHCP::v6factories_;

// Static container with DHCPv4 option definitions.
OptionDefContainer LibDHCP::v4option_defs_;

// Static container with DHCPv6 option definitions.
OptionDefContainer LibDHCP::v6option_defs_;

VendorOptionDefContainers LibDHCP::vendor4_defs_;

VendorOptionDefContainers LibDHCP::vendor6_defs_;

// Those two vendor classes are used for cable modems:

/// DOCSIS3.0 compatible cable modem
const char* isc::dhcp::DOCSIS3_CLASS_MODEM = "docsis3.0";

/// DOCSIS3.0 cable modem that has router built-in
const char* isc::dhcp::DOCSIS3_CLASS_EROUTER = "eRouter1.0";

// Let's keep it in .cc file. Moving it to .h would require including optionDefParams
// definitions there
void initOptionSpace(OptionDefContainer& defs,
                     const OptionDefParams* params,
                     size_t params_size);

const OptionDefContainer&
LibDHCP::getOptionDefs(const Option::Universe u) {
    switch (u) {
    case Option::V4:
        if (v4option_defs_.empty()) {
            initStdOptionDefs4();
            initVendorOptsDocsis4();
        }
        return (v4option_defs_);
    case Option::V6:
        if (v6option_defs_.empty()) {
            initStdOptionDefs6();
            initVendorOptsDocsis6();
        }
        return (v6option_defs_);
    default:
        isc_throw(isc::BadValue, "invalid universe " << u << " specified");
    }
}

const OptionDefContainer*
LibDHCP::getVendorOption4Defs(const uint32_t vendor_id) {

    if (vendor_id == VENDOR_ID_CABLE_LABS &&
        vendor4_defs_.find(VENDOR_ID_CABLE_LABS) == vendor4_defs_.end()) {
        initVendorOptsDocsis4();
    }

    VendorOptionDefContainers::const_iterator def = vendor4_defs_.find(vendor_id);
    if (def == vendor4_defs_.end()) {
        // No such vendor-id space
        return (NULL);
    }
    return (&(def->second));
}

const OptionDefContainer*
LibDHCP::getVendorOption6Defs(const uint32_t vendor_id) {

    if (vendor_id == VENDOR_ID_CABLE_LABS &&
        vendor6_defs_.find(VENDOR_ID_CABLE_LABS) == vendor6_defs_.end()) {
        initVendorOptsDocsis6();
    }

    VendorOptionDefContainers::const_iterator def = vendor6_defs_.find(vendor_id);
    if (def == vendor6_defs_.end()) {
        // No such vendor-id space
        return (NULL);
    }
    return (&(def->second));
}

OptionDefinitionPtr
LibDHCP::getOptionDef(const Option::Universe u, const uint16_t code) {
    const OptionDefContainer& defs = getOptionDefs(u);
    const OptionDefContainerTypeIndex& idx = defs.get<1>();
    const OptionDefContainerTypeRange& range = idx.equal_range(code);
    if (range.first != range.second) {
        return (*range.first);
    }
    return (OptionDefinitionPtr());
}

OptionDefinitionPtr
LibDHCP::getOptionDef(const Option::Universe u, const std::string& name) {
    const OptionDefContainer& defs = getOptionDefs(u);
    const OptionDefContainerNameIndex& idx = defs.get<2>();
    const OptionDefContainerNameRange& range = idx.equal_range(name);
    if (range.first != range.second) {
        return (*range.first);
    }
    return (OptionDefinitionPtr());

}


OptionDefinitionPtr
LibDHCP::getVendorOptionDef(const Option::Universe u, const uint32_t vendor_id,
                            const std::string& name) {
    const OptionDefContainer* defs = NULL;
    if (u == Option::V4) {
        defs = getVendorOption4Defs(vendor_id);
    } else if (u == Option::V6) {
        defs = getVendorOption6Defs(vendor_id);
    }

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
    const OptionDefContainer* defs = NULL;
    if (u == Option::V4) {
        defs = getVendorOption4Defs(vendor_id);
    } else if (u == Option::V6) {
        defs = getVendorOption6Defs(vendor_id);
    }

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

bool
LibDHCP::isStandardOption(const Option::Universe u, const uint16_t code) {
    if (u == Option::V6) {
        if (code < 79 &&
            code != 10 &&
            code != 35) {
            return (true);
        }

    } else if (u == Option::V4) {
        if (!(code == 84 ||
              code == 96 ||
              (code > 101 && code < 112) ||
              code == 115 ||
              code == 126 ||
              code == 127 ||
              (code > 146 && code < 150) ||
              (code > 177 && code < 208) ||
              (code > 213 && code <  220) ||
              (code > 221 && code < 255))) {
                return (true);
            }

    }

    return (false);
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


size_t LibDHCP::unpackOptions6(const OptionBuffer& buf,
                               const std::string& option_space,
                               isc::dhcp::OptionCollection& options,
                               size_t* relay_msg_offset /* = 0 */,
                               size_t* relay_msg_len /* = 0 */,
			       size_t* signature_offset /* = 0 */) {
    size_t offset = 0;
    size_t length = buf.size();

    // Get the list of standard option definitions.
    OptionDefContainer option_defs;
    if (option_space == "dhcp6") {
        option_defs = LibDHCP::getOptionDefs(Option::V6);
    }
    // @todo Once we implement other option spaces we should add else clause
    // here and gather option definitions for them. For now leaving option_defs
    // empty will imply creation of generic Option.

    // Get the search index #1. It allows to search for option definitions
    // using option code.
    const OptionDefContainerTypeIndex& idx = option_defs.get<1>();

    // The buffer being read comprises a set of options, each starting with
    // a two-byte type code and a two-byte length field.
    while (offset + 4 <= length) {
        uint16_t opt_type = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        uint16_t opt_len = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        if (offset + opt_len > length) {
            // @todo: consider throwing exception here.

            // We peeked at the option header of the next option, but discovered
            // that it would end up beyond buffer end, so the option is
            // truncated. Hence we can't parse it. Therefore we revert
            // back by those four bytes (as if we never parsed them).
            return (offset - 4);
        }

        if (opt_type == D6O_RELAY_MSG && relay_msg_offset && relay_msg_len) {
            // remember offset of the beginning of the relay-msg option
            *relay_msg_offset = offset;
            *relay_msg_len = opt_len;

            // do not create that relay-msg option
            offset += opt_len;
            continue;
        }

	if (opt_type == D6O_SIGNATURE && signature_offset) {
	    // remember offset of the beginning of the (last) signature option
	    *signature_offset = offset;
	}

        if (opt_type == D6O_VENDOR_OPTS) {
            if (offset + 4 > length) {
                // Truncated vendor-option. There is expected at least 4 bytes
                // long enterprise-id field. Let's roll back option code + option
                // length (4 bytes) and return.
                return (offset - 4);
            }

            // Parse this as vendor option
            OptionPtr vendor_opt(new OptionVendor(Option::V6, buf.begin() + offset,
                                                  buf.begin() + offset + opt_len));
            options.insert(std::make_pair(opt_type, vendor_opt));

            offset += opt_len;
            continue;
        }


        // Get all definitions with the particular option code. Note that option
        // code is non-unique within this container however at this point we
        // expect to get one option definition with the particular code. If more
        // are returned we report an error.
        const OptionDefContainerTypeRange& range = idx.equal_range(opt_type);
        // Get the number of returned option definitions for the option code.
        size_t num_defs = distance(range.first, range.second);

        OptionPtr opt;
        if (num_defs > 1) {
            // Multiple options of the same code are not supported right now!
            isc_throw(isc::Unexpected, "Internal error: multiple option definitions"
                      " for option type " << opt_type << " returned. Currently it is not"
                      " supported to initialize multiple option definitions"
                      " for the same option code. This will be supported once"
                      " support for option spaces is implemented");
        } else if (num_defs == 0) {
            // @todo Don't crash if definition does not exist because only a few
            // option definitions are initialized right now. In the future
            // we will initialize definitions for all options and we will
            // remove this elseif. For now, return generic option.
            opt = OptionPtr(new Option(Option::V6, opt_type,
                                       buf.begin() + offset,
                                       buf.begin() + offset + opt_len));
        } else {
            // The option definition has been found. Use it to create
            // the option instance from the provided buffer chunk.
            const OptionDefinitionPtr& def = *(range.first);
            assert(def);
            opt = def->optionFactory(Option::V6, opt_type,
                                     buf.begin() + offset,
                                     buf.begin() + offset + opt_len);
        }
        // add option to options
        options.insert(std::make_pair(opt_type, opt));
        offset += opt_len;
    }

    return (offset);
}

size_t LibDHCP::unpackOptions4(const OptionBuffer& buf,
                               const std::string& option_space,
                               isc::dhcp::OptionCollection& options) {
    size_t offset = 0;

    // Get the list of stdandard option definitions.
    OptionDefContainer option_defs;
    if (option_space == "dhcp4") {
        option_defs = LibDHCP::getOptionDefs(Option::V4);
    }
    // @todo Once we implement other option spaces we should add else clause
    // here and gather option definitions for them. For now leaving option_defs
    // empty will imply creation of generic Option.

    // Get the search index #1. It allows to search for option definitions
    // using option code.
    const OptionDefContainerTypeIndex& idx = option_defs.get<1>();

    // The buffer being read comprises a set of options, each starting with
    // a one-byte type code and a one-byte length field.
    while (offset + 1 <= buf.size()) {
        uint8_t opt_type = buf[offset++];

        // DHO_END is a special, one octet long option
        if (opt_type == DHO_END)
            return (offset); // just return. Don't need to add DHO_END option

        // DHO_PAD is just a padding after DHO_END. Let's continue parsing
        // in case we receive a message without DHO_END.
        if (opt_type == DHO_PAD)
            continue;

        if (offset + 1 > buf.size()) {
            // opt_type must be cast to integer so as it is not treated as
            // unsigned char value (a number is presented in error message).
            isc_throw(OutOfRange, "Attempt to parse truncated option "
                      << static_cast<int>(opt_type));
        }

        uint8_t opt_len =  buf[offset++];
        if (offset + opt_len > buf.size()) {

            // We peeked at the option header of the next option, but discovered
            // that it would end up beyond buffer end, so the option is
            // truncated. Hence we can't parse it. Therefore we revert
            // back by two bytes (as if we never parsed them).
            return (offset - 2);

            // isc_throw(OutOfRange, "Option parse failed. Tried to parse "
            //          << offset + opt_len << " bytes from " << buf.size()
            //          << "-byte long buffer.");
        }

        // Get all definitions with the particular option code. Note that option code
        // is non-unique within this container however at this point we expect
        // to get one option definition with the particular code. If more are
        // returned we report an error.
        const OptionDefContainerTypeRange& range = idx.equal_range(opt_type);
        // Get the number of returned option definitions for the option code.
        size_t num_defs = distance(range.first, range.second);

        OptionPtr opt;
        if (num_defs > 1) {
            // Multiple options of the same code are not supported right now!
            isc_throw(isc::Unexpected, "Internal error: multiple option definitions"
                      " for option type " << static_cast<int>(opt_type)
                      << " returned. Currently it is not supported to initialize"
                      << " multiple option definitions for the same option code."
                      << " This will be supported once support for option spaces"
                      << " is implemented");
        } else if (num_defs == 0) {
            opt = OptionPtr(new Option(Option::V4, opt_type,
                                       buf.begin() + offset,
                                       buf.begin() + offset + opt_len));
        } else {
            // The option definition has been found. Use it to create
            // the option instance from the provided buffer chunk.
            const OptionDefinitionPtr& def = *(range.first);
            assert(def);
            opt = def->optionFactory(Option::V4, opt_type,
                                     buf.begin() + offset,
                                     buf.begin() + offset + opt_len);
        }

        options.insert(std::make_pair(opt_type, opt));
        offset += opt_len;
    }
    return (offset);
}

size_t LibDHCP::unpackVendorOptions6(const uint32_t vendor_id,
                                     const OptionBuffer& buf,
                                     isc::dhcp::OptionCollection& options) {
    size_t offset = 0;
    size_t length = buf.size();

    // Get the list of option definitions for this particular vendor-id
    const OptionDefContainer* option_defs = LibDHCP::getVendorOption6Defs(vendor_id);

    // Get the search index #1. It allows to search for option definitions
    // using option code. If there's no such vendor-id space, we're out of luck
    // anyway.
    const OptionDefContainerTypeIndex* idx = NULL;
    if (option_defs) {
        idx = &(option_defs->get<1>());
    }

    // The buffer being read comprises a set of options, each starting with
    // a two-byte type code and a two-byte length field.
    while (offset + 4 <= length) {
        uint16_t opt_type = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        uint16_t opt_len = isc::util::readUint16(&buf[offset], 2);
        offset += 2;

        if (offset + opt_len > length) {
            // @todo: consider throwing exception here.

            // We peeked at the option header of the next option, but discovered
            // that it would end up beyond buffer end, so the option is
            // truncated. Hence we can't parse it. Therefore we revert
            // back by those four bytes (as if we never parsed them).
            return (offset - 4);
        }

        OptionPtr opt;
        opt.reset();

        // If there is a definition for such a vendor option...
        if (idx) {
            // Get all definitions with the particular option code. Note that option
            // code is non-unique within this container however at this point we
            // expect to get one option definition with the particular code. If more
            // are returned we report an error.
            const OptionDefContainerTypeRange& range = idx->equal_range(opt_type);
            // Get the number of returned option definitions for the option code.
            size_t num_defs = distance(range.first, range.second);

            if (num_defs > 1) {
                // Multiple options of the same code are not supported right now!
                isc_throw(isc::Unexpected, "Internal error: multiple option definitions"
                          " for option type " << opt_type << " returned. Currently it is not"
                          " supported to initialize multiple option definitions"
                          " for the same option code. This will be supported once"
                          " support for option spaces is implemented");
            } else if (num_defs == 1) {
                // The option definition has been found. Use it to create
                // the option instance from the provided buffer chunk.
                const OptionDefinitionPtr& def = *(range.first);
                assert(def);
                opt = def->optionFactory(Option::V6, opt_type,
                                         buf.begin() + offset,
                                         buf.begin() + offset + opt_len);
            }
        }

        // This can happen in one of 2 cases:
        // 1. we do not have definitions for that vendor-space
        // 2. we do have definitions, but that particular option was not defined
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

size_t LibDHCP::unpackVendorOptions4(const uint32_t vendor_id, const OptionBuffer& buf,
                                     isc::dhcp::OptionCollection& options) {
    size_t offset = 0;

    // Get the list of stdandard option definitions.
    const OptionDefContainer* option_defs = LibDHCP::getVendorOption4Defs(vendor_id);
    // Get the search index #1. It allows to search for option definitions
    // using option code.
    const OptionDefContainerTypeIndex* idx = NULL;
    if (option_defs) {
        idx = &(option_defs->get<1>());
    }

    // The buffer being read comprises a set of options, each starting with
    // a one-byte type code and a one-byte length field.
    while (offset + 1 <= buf.size()) {

        // Note that Vendor-Specific info option (RFC3925) has a different option
        // format than Vendor-Spec info for DHCPv6. (there's additional layer of
        // data-length
        uint8_t data_len = buf[offset++];

        if (offset + data_len > buf.size()) {
            // The option is truncated.

            // We peeked at the data_len, but discovered that it would end up
            // beyond buffer end, so the data block is truncated. Hence we can't
            // parse it. Therefore we revert back by one byte (as if we never
            // parsed it).
            return (offset - 1);
        }

        uint8_t offset_end = offset + data_len;

        // beginning of data-chunk parser
        while (offset + 1 <= offset_end) {
            uint8_t opt_type = buf[offset++];

            // DHO_END is a special, one octet long option
            if (opt_type == DHO_END)
                return (offset); // just return. Don't need to add DHO_END option

            // DHO_PAD is just a padding after DHO_END. Let's continue parsing
            // in case we receive a message without DHO_END.
            if (opt_type == DHO_PAD)
                continue;

            if (offset + 1 > buf.size()) {
                // opt_type must be cast to integer so as it is not treated as
                // unsigned char value (a number is presented in error message).
                isc_throw(OutOfRange, "Attempt to parse truncated vendor option "
                          << static_cast<int>(opt_type));
            }

            uint8_t opt_len =  buf[offset++];
            if (offset + opt_len > buf.size()) {
                isc_throw(OutOfRange, "Option parse failed. Tried to parse "
                          << offset + opt_len << " bytes from " << buf.size()
                          << "-byte long buffer.");
            }

            OptionPtr opt;
            opt.reset();

            if (idx) {
                // Get all definitions with the particular option code. Note that option code
                // is non-unique within this container however at this point we expect
                // to get one option definition with the particular code. If more are
                // returned we report an error.
                const OptionDefContainerTypeRange& range = idx->equal_range(opt_type);
                // Get the number of returned option definitions for the option code.
                size_t num_defs = distance(range.first, range.second);

                if (num_defs > 1) {
                    // Multiple options of the same code are not supported right now!
                    isc_throw(isc::Unexpected, "Internal error: multiple option definitions"
                              " for option type " << static_cast<int>(opt_type)
                              << " returned. Currently it is not supported to initialize"
                              << " multiple option definitions for the same option code."
                              << " This will be supported once support for option spaces"
                              << " is implemented");
                } else if (num_defs == 1) {
                    // The option definition has been found. Use it to create
                    // the option instance from the provided buffer chunk.
                    const OptionDefinitionPtr& def = *(range.first);
                    assert(def);
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

    }
    return (offset);
}



void
LibDHCP::packOptions(isc::util::OutputBuffer& buf,
                     const OptionCollection& options) {
    for (OptionCollection::const_iterator it = options.begin();
         it != options.end(); ++it) {
        it->second->pack(buf);
    }
}

void LibDHCP::OptionFactoryRegister(Option::Universe u,
                                    uint16_t opt_type,
                                    Option::Factory* factory) {
    switch (u) {
    case Option::V6: {
        if (v6factories_.find(opt_type) != v6factories_.end()) {
            isc_throw(BadValue, "There is already DHCPv6 factory registered "
                     << "for option type "  << opt_type);
        }
        v6factories_[opt_type]=factory;
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
        if (v4factories_.find(opt_type)!=v4factories_.end()) {
            isc_throw(BadValue, "There is already DHCPv4 factory registered "
                     << "for option type "  << opt_type);
        }
        v4factories_[opt_type]=factory;
        return;
    }
    default:
        isc_throw(BadValue, "Invalid universe type specified.");
    }

    return;
}

void
LibDHCP::initStdOptionDefs4() {
    initOptionSpace(v4option_defs_, OPTION_DEF_PARAMS4, OPTION_DEF_PARAMS_SIZE4);
}

void
LibDHCP::initStdOptionDefs6() {
    initOptionSpace(v6option_defs_, OPTION_DEF_PARAMS6, OPTION_DEF_PARAMS_SIZE6);
}

void
LibDHCP::initVendorOptsDocsis4() {
    initOptionSpace(vendor4_defs_[VENDOR_ID_CABLE_LABS], DOCSIS3_V4_DEFS, DOCSIS3_V4_DEFS_SIZE);
}

void
LibDHCP::initVendorOptsDocsis6() {
    vendor6_defs_[VENDOR_ID_CABLE_LABS] = OptionDefContainer();
    initOptionSpace(vendor6_defs_[VENDOR_ID_CABLE_LABS], DOCSIS3_V6_DEFS, DOCSIS3_V6_DEFS_SIZE);
}

void initOptionSpace(OptionDefContainer& defs,
                     const OptionDefParams* params,
                     size_t params_size) {
    defs.clear();

    for (int i = 0; i < params_size; ++i) {
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
                                                  params[i].type,
                                                  params[i].array));
        } else {
            // Option does encapsulate an option space.
            definition.reset(new OptionDefinition(params[i].name,
                                                  params[i].code,
                                                  params[i].type,
                                                  params[i].encapsulates));

        }

        for (int rec = 0; rec < params[i].records_size; ++rec) {
            definition->addRecordField(params[i].records[rec]);
        }

        try {
            definition->validate();
        } catch (const isc::Exception& ex) {
            // This is unlikely event that validation fails and may
            // be only caused by programming error. To guarantee the
            // data consistency we clear all option definitions that
            // have been added so far and pass the exception forward.
            defs.clear();
            throw;
        }
        defs.push_back(definition);
    }
}
