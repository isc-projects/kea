// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <cc/data.h>
#include <dhcp/duid.h>
#include <dhcpsrv/cfg_duid.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/duid_config_parser.h>
#include <exceptions/exceptions.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <limits>
#include <string>

using namespace isc::data;

namespace isc {
namespace dhcp {

DUIDConfigParser::DUIDConfigParser()
    : DhcpConfigParser() {
}

void
DUIDConfigParser::build(isc::data::ConstElementPtr duid_configuration) {
    bool type_present = false;
    BOOST_FOREACH(ConfigPair element, duid_configuration->mapValue()) {
        try {
            if (element.first == "type") {
                type_present = true;
                setType(element.second->stringValue());
            } else if (element.first == "identifier") {
                setIdentifier(element.second->stringValue());
            } else if (element.first == "htype") {
                setHType(element.second->intValue());
            } else if (element.first == "time") {
                setTime(element.second->intValue());
            } else if (element.first == "enterprise-id") {
                setEnterpriseId(element.second->intValue());
            } else {
                isc_throw(DhcpConfigError, "unsupported configuration "
                          "parameter '" << element.first << "'");
            }
        } catch (const std::exception& ex) {
            // Append position.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << element.second->getPosition() << ")");
        }
    }

    // "type" is mandatory
    if (!type_present) {
        isc_throw(DhcpConfigError, "mandatory parameter \"type\" not specified"
                  " for the DUID configuration ("
                  << duid_configuration->getPosition() << ")");
    }
}

void
DUIDConfigParser::setType(const std::string& duid_type) const {
    // Map DUID type represented as text into numeric value.
    DUID::DUIDType numeric_type = DUID::DUID_UNKNOWN;
    if (duid_type == "LLT") {
        numeric_type = DUID::DUID_LLT;
    } else if (duid_type == "EN") {
        numeric_type = DUID::DUID_EN;
    } else if (duid_type == "LL") {
        numeric_type = DUID::DUID_LL;
    } else {
        isc_throw(DhcpConfigError, "unsupported DUID type '"
                  << duid_type << "'. Expected: LLT, EN or LL");
    }

    const CfgDUIDPtr& cfg = CfgMgr::instance().getStagingCfg()->getCfgDUID();
    cfg->setType(static_cast<DUID::DUIDType>(numeric_type));
}

void
DUIDConfigParser::setIdentifier(const std::string& identifier) const {
    const CfgDUIDPtr& cfg = CfgMgr::instance().getStagingCfg()->getCfgDUID();
    cfg->setIdentifier(identifier);
}

void
DUIDConfigParser::setHType(const int64_t htype) const {
    const CfgDUIDPtr& cfg = CfgMgr::instance().getStagingCfg()->getCfgDUID();
    checkRange<uint16_t>("htype", htype);
    cfg->setHType(static_cast<uint16_t>(htype));

}

void
DUIDConfigParser::setTime(const int64_t new_time) const {
    const CfgDUIDPtr& cfg = CfgMgr::instance().getStagingCfg()->getCfgDUID();
    checkRange<uint32_t>("time", new_time);
    cfg->setTime(static_cast<uint32_t>(new_time));
}

void
DUIDConfigParser::setEnterpriseId(const int64_t enterprise_id) const {
    const CfgDUIDPtr& cfg = CfgMgr::instance().getStagingCfg()->getCfgDUID();
    checkRange<uint32_t>("enterprise-id", enterprise_id);
    cfg->setEnterpriseId(static_cast<uint32_t>(enterprise_id));
}

template<typename NumericType>
void
DUIDConfigParser::checkRange(const std::string& parameter_name,
                             const int64_t parameter_value) const {
    if ((parameter_value < 0) ||
        (parameter_value > std::numeric_limits<NumericType>::max())) {
        isc_throw(DhcpConfigError, "out of range value '" << parameter_value
                  << "' specified for parameter '" << parameter_name
                  << "'; expected value in range of [0.."
                  << std::numeric_limits<NumericType>::max() << "]");
    }
}


} // end of namespace isc::dhcp
} // end of namespace isc
