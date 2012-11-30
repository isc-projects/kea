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
#include <dhcp/option6_int_array.h>
#include <dhcp/option_definition.h>
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
        initStdOptionDefs4();
        return (v4option_defs_);
    case Option::V6:
        if (v6option_defs_.size() == 0) {
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
    size_t end = buf.size();

    while (offset +4 <= end) {
        uint16_t opt_type = buf[offset] * 256 + buf[offset + 1];
        offset += 2;
        uint16_t opt_len = buf[offset] * 256 + buf[offset + 1];
        offset += 2;

        if (offset + opt_len > end) {
            // @todo: consider throwing exception here.
            return (offset);
        }

        // Get the list of stdandard option definitions.
        OptionDefContainer option_defs = LibDHCP::getOptionDefs(Option::V6);
        // Get the search index #1. It allows to search for option definitions
        // using option code.
        const OptionDefContainerTypeIndex& idx = option_defs.get<1>();
        // Get all options with the particular option code. Note that option code
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

    // 2 byte - header of DHCPv4 option
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
            isc_throw(OutOfRange, "Attempt to parse truncated option "
                      << opt_type);
        }

        uint8_t opt_len =  buf[offset++];
        if (offset + opt_len > buf.size()) {
            isc_throw(OutOfRange, "Option parse failed. Tried to parse "
                      << offset + opt_len << " bytes from " << buf.size()
                      << "-byte long buffer.");
        }

        OptionPtr opt;
        switch(opt_type) {
        default:
            opt = OptionPtr(new Option(Option::V4, opt_type,
                                       buf.begin()+offset,
                                       buf.begin()+offset+opt_len));
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
    isc_throw(isc::NotImplemented, "initStdOptionDefs4 is not implemented");
}

void
LibDHCP::initStdOptionDefs6() {
    v6option_defs_.clear();

    struct OptionParams {
        std::string name;
        uint16_t code;
        OptionDataType type;
        bool array;
    };
    OptionParams params[] = {
        { "clientid", D6O_CLIENTID, OPT_BINARY_TYPE, false },
        { "serverid", D6O_SERVERID, OPT_BINARY_TYPE, false },
        { "ia-na", D6O_IA_NA, OPT_RECORD_TYPE, false },
        { "ia-ta", D6O_IA_TA, OPT_UINT32_TYPE, false },
        { "iaaddr", D6O_IAADDR, OPT_RECORD_TYPE, false },
        { "oro", D6O_ORO, OPT_UINT16_TYPE, true },
        { "preference", D6O_PREFERENCE, OPT_UINT8_TYPE, false },
        { "elapsed-time", D6O_ELAPSED_TIME, OPT_UINT16_TYPE, false },
        { "relay-msg", D6O_RELAY_MSG, OPT_BINARY_TYPE, false },
        //        { "AUTH", D6O_AUTH, D6O_AUTH, OPT_RECORD_TYPE, false },
        { "unicast", D6O_UNICAST, OPT_IPV6_ADDRESS_TYPE, false },
        { "status-code", D6O_STATUS_CODE, OPT_RECORD_TYPE, false },
        { "rapid-commit", D6O_RAPID_COMMIT, OPT_EMPTY_TYPE, false },
        { "user-class", D6O_USER_CLASS, OPT_BINARY_TYPE, false },
        { "vendor-class", D6O_VENDOR_CLASS, OPT_RECORD_TYPE, false },
        { "vendor-opts", D6O_VENDOR_OPTS, OPT_RECORD_TYPE, false },
        { "interface-id", D6O_INTERFACE_ID, OPT_BINARY_TYPE, false },
        { "reconf-msg", D6O_RECONF_MSG, OPT_UINT8_TYPE, false },
        { "reconf-accept", D6O_RECONF_ACCEPT, OPT_EMPTY_TYPE, false },
        { "sip-server-dns", D6O_SIP_SERVERS_DNS, OPT_FQDN_TYPE, true },
        { "sip-server-addr", D6O_SIP_SERVERS_ADDR, OPT_IPV6_ADDRESS_TYPE, true },
        { "dns-servers", D6O_NAME_SERVERS, OPT_IPV6_ADDRESS_TYPE, true },
        { "domain-search", D6O_DOMAIN_SEARCH, OPT_FQDN_TYPE, true },
        { "ia-pd", D6O_IA_PD, OPT_RECORD_TYPE, false },
        { "iaprefix", D6O_IAPREFIX, OPT_RECORD_TYPE, false },
        { "nis-servers", D6O_NIS_SERVERS, OPT_IPV6_ADDRESS_TYPE, true },
        { "nisp-servers", D6O_NISP_SERVERS, OPT_IPV6_ADDRESS_TYPE, true },
        { "nis-domain-name", D6O_NIS_DOMAIN_NAME, OPT_FQDN_TYPE, true },
        { "nisp-domain-name", D6O_NISP_DOMAIN_NAME, OPT_FQDN_TYPE, true },
        { "sntp-servers", D6O_SNTP_SERVERS, OPT_IPV6_ADDRESS_TYPE, true },
        { "information-refresh-time", D6O_INFORMATION_REFRESH_TIME,
          OPT_UINT32_TYPE, false },
        { "bcmcs-server-dns", D6O_BCMCS_SERVER_D, OPT_FQDN_TYPE, true },
        { "bcmcs-server-addr", D6O_BCMCS_SERVER_A, OPT_IPV6_ADDRESS_TYPE, true },
        { "geoconf-civic", D6O_GEOCONF_CIVIC, OPT_RECORD_TYPE, false },
        { "remote-id", D6O_REMOTE_ID, OPT_RECORD_TYPE, false },
        { "subscriber-id", D6O_SUBSCRIBER_ID, OPT_BINARY_TYPE, false },
        { "client-fqdn", D6O_CLIENT_FQDN, OPT_RECORD_TYPE, false },
        { "pana-agent", D6O_PANA_AGENT, OPT_IPV6_ADDRESS_TYPE, true },
        { "new-posix-timezone", D6O_NEW_POSIX_TIMEZONE, OPT_STRING_TYPE, false },
        { "new-tzdb-timezone", D6O_NEW_TZDB_TIMEZONE, OPT_STRING_TYPE, false },
        { "ero", D6O_ERO, OPT_UINT16_TYPE, true },
        { "lq-query", D6O_LQ_QUERY, OPT_RECORD_TYPE, false },
        { "client-data", D6O_CLIENT_DATA, OPT_EMPTY_TYPE, false },
        { "clt-time", D6O_CLT_TIME, OPT_UINT32_TYPE, false },
        { "lq-relay-data", D6O_LQ_RELAY_DATA, OPT_RECORD_TYPE, false },
        { "lq-client-link", D6O_LQ_CLIENT_LINK, OPT_IPV6_ADDRESS_TYPE, true },
        /*        { "MIP6_HNIDF", D6O_MIP6_HNIDF, OPT_FQDN_TYPE, false },
        { "MIP6_VDINF", D6O_MIP6_VDINF, OPT_EMPTY_TYPE, false },
        { "V6_LOST", D6O_V6_LOST, OPT_FQDN_TYPE, false },
        { "CAPWAP_AC_V6", D6O_CAPWAP_AC_V6, OPT_IPV6_ADDRESS_TYPE, true },
        { "RELAY_ID", D6O_RELAY_ID, OPT_BINARY_TYPE, false },
        { "IPV6_ADDRESS_MOS", */

    };
    const int params_size = sizeof(params) / sizeof(params[0]);

    for (int i = 0; i < params_size; ++i) {
        OptionDefinitionPtr definition(new OptionDefinition(params[i].name,
                                                            params[i].code,
                                                            params[i].type,
                                                            params[i].array));
        switch(params[i].code) {
        case D6O_IA_NA:
        case D6O_IA_PD:
            for (int j = 0; j < 3; ++j) {
                definition->addRecordField(OPT_UINT32_TYPE);
            }
            break;
        case D6O_IAADDR:
            definition->addRecordField(OPT_IPV6_ADDRESS_TYPE);
            definition->addRecordField(OPT_UINT32_TYPE);
            definition->addRecordField(OPT_UINT32_TYPE);
            break;
        case D6O_STATUS_CODE:
            definition->addRecordField(OPT_UINT16_TYPE);
            definition->addRecordField(OPT_STRING_TYPE);
            break;
        case D6O_VENDOR_CLASS:
            definition->addRecordField(OPT_UINT32_TYPE);
            definition->addRecordField(OPT_BINARY_TYPE);
            break;
        case D6O_VENDOR_OPTS:
            definition->addRecordField(OPT_UINT32_TYPE);
            definition->addRecordField(OPT_BINARY_TYPE);
            break;
        case D6O_IAPREFIX:
            definition->addRecordField(OPT_UINT32_TYPE);
            definition->addRecordField(OPT_UINT32_TYPE);
            definition->addRecordField(OPT_UINT8_TYPE);
            definition->addRecordField(OPT_BINARY_TYPE);
            break;
        case D6O_GEOCONF_CIVIC:
            definition->addRecordField(OPT_UINT8_TYPE);
            definition->addRecordField(OPT_UINT16_TYPE);
            definition->addRecordField(OPT_BINARY_TYPE);
            break;
        case D6O_REMOTE_ID:
            definition->addRecordField(OPT_UINT32_TYPE);
            definition->addRecordField(OPT_BINARY_TYPE);
            break;
        case D6O_CLIENT_FQDN:
            definition->addRecordField(OPT_UINT8_TYPE);
            definition->addRecordField(OPT_FQDN_TYPE);
            break;
        case D6O_LQ_QUERY:
            definition->addRecordField(OPT_UINT8_TYPE);
            definition->addRecordField(OPT_IPV6_ADDRESS_TYPE);
            break;
        case D6O_LQ_RELAY_DATA:
            definition->addRecordField(OPT_IPV6_ADDRESS_TYPE);
            definition->addRecordField(OPT_BINARY_TYPE);
            break;
        default:
            // The default case is intentionally left empty
            // as it does not need any processing.
            ;
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
