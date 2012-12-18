// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_int_array.h>
#include <dhcp/std_option_defs.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>

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

const OptionDefContainer&
LibDHCP::getOptionDefs(const Option::Universe u) {
    switch (u) {
    case Option::V4:
        if (v4option_defs_.empty()) {
            initStdOptionDefs4();
        }
        return (v4option_defs_);
    case Option::V6:
        if (v6option_defs_.empty()) {
            initStdOptionDefs6();
        }
        return (v6option_defs_);
    default:
        isc_throw(isc::BadValue, "invalid universe " << u << " specified");
    }
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
                               isc::dhcp::Option::OptionCollection& options) {
    size_t offset = 0;
    size_t length = buf.size();

    // Get the list of stdandard option definitions.
    const OptionDefContainer& option_defs = LibDHCP::getOptionDefs(Option::V6);
    // Get the search index #1. It allows to search for option definitions
    // using option code.
    const OptionDefContainerTypeIndex& idx = option_defs.get<1>();

    // The buffer being read comprises a set of options, each starting with
    // a two-byte type code and a two-byte length field.
    while (offset + 4 <= length) {
        uint16_t opt_type = isc::util::readUint16(&buf[offset]);
        offset += 2;
        uint16_t opt_len = isc::util::readUint16(&buf[offset]);
        offset += 2;

        if (offset + opt_len > length) {
            // @todo: consider throwing exception here.
            return (offset);
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
                                 isc::dhcp::Option::OptionCollection& options) {
    size_t offset = 0;

    // Get the list of stdandard option definitions.
    const OptionDefContainer& option_defs = LibDHCP::getOptionDefs(Option::V4);
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

        if (offset + 1 >= buf.size()) {
            // opt_type must be cast to integer so as it is not treated as
            // unsigned char value (a number is presented in error message).
            isc_throw(OutOfRange, "Attempt to parse truncated option "
                      << static_cast<int>(opt_type));
        }

        uint8_t opt_len =  buf[offset++];
        if (offset + opt_len > buf.size()) {
            isc_throw(OutOfRange, "Option parse failed. Tried to parse "
                      << offset + opt_len << " bytes from " << buf.size()
                      << "-byte long buffer.");
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

void LibDHCP::packOptions6(isc::util::OutputBuffer &buf,
                           const isc::dhcp::Option::OptionCollection& options) {
    for (Option::OptionCollection::const_iterator it = options.begin();
         it != options.end(); ++it) {
        it->second->pack(buf);
    }
}

void
LibDHCP::packOptions(isc::util::OutputBuffer& buf,
                     const Option::OptionCollection& options) {
    for (Option::OptionCollection::const_iterator it = options.begin();
         it != options.end(); ++it) {
        it->second->pack4(buf);
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
    v4option_defs_.clear();

    // Now let's add all option definitions.
    for (int i = 0; i < OPTION_DEF_PARAMS_SIZE4; ++i) {
        OptionDefinitionPtr definition(new OptionDefinition(OPTION_DEF_PARAMS4[i].name,
                                                            OPTION_DEF_PARAMS4[i].code,
                                                            OPTION_DEF_PARAMS4[i].type,
                                                            OPTION_DEF_PARAMS4[i].array));

        for (int rec = 0; rec < OPTION_DEF_PARAMS4[i].records_size; ++rec) {
            definition->addRecordField(OPTION_DEF_PARAMS4[i].records[rec]);
        }

        // Sanity check if the option is valid.
        try {
            definition->validate();
        } catch (const Exception& ex) {
            // This is unlikely event that validation fails and may
            // be only caused by programming error. To guarantee the
            // data consistency we clear all option definitions that
            // have been added so far and pass the exception forward.
            v4option_defs_.clear();
            throw;
        }
        v4option_defs_.push_back(definition);
    }
}

void
LibDHCP::initStdOptionDefs6() {
    v6option_defs_.clear();

    for (int i = 0; i < OPTION_DEF_PARAMS_SIZE6; ++i) {
        OptionDefinitionPtr definition(new OptionDefinition(OPTION_DEF_PARAMS6[i].name,
                                                            OPTION_DEF_PARAMS6[i].code,
                                                            OPTION_DEF_PARAMS6[i].type,
                                                            OPTION_DEF_PARAMS6[i].array));

        for (int rec = 0; rec < OPTION_DEF_PARAMS6[i].records_size; ++rec) {
            definition->addRecordField(OPTION_DEF_PARAMS6[i].records[rec]);
        }

        try {
            definition->validate();
        } catch (const Exception& ex) {
            // This is unlikely event that validation fails and may
            // be only caused by programming error. To guarantee the
            // data consistency we clear all option definitions that
            // have been added so far and pass the exception forward.
            v6option_defs_.clear();
            throw;
        }
        v6option_defs_.push_back(definition);
    }
}
