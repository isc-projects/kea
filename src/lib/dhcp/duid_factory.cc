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

#include <dhcp/duid_factory.h>
#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>
#include <util/range_utilities.h>
#include <util/strutil.h>
#include <boost/foreach.hpp>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace isc::util;
using namespace isc::util::str;

namespace {

/// @brief Length of the DUID type field.
const size_t DUID_TYPE_LEN = 2;

/// @brief Minimal length of the MAC address.
const size_t MIN_MAC_LEN = 6;

/// @brief Length of the enterprise if field.
const size_t ENTERPRISE_ID_LEN = 4;

/// @brief Default length of the variable length identifier in the DUID-EN.
const size_t DUID_EN_IDENTIFIER_LEN = 6;

}

namespace isc {
namespace dhcp {

DUIDFactory::DUIDFactory(const std::string& storage_location)
    : storage_location_(trim(storage_location)), duid_() {
}

bool
DUIDFactory::isStored() const {
    return (!storage_location_.empty());
}

void
DUIDFactory::createLLT(const uint16_t htype, const uint32_t time_in,
                       const std::vector<uint8_t>& ll_identifier) {
    // We'll need DUID stored in the file to compare it against the
    // new configuration. If the new configuration indicates that some
    // bits of the DUID should be generated we'll first try to use the
    // values stored in the file to prevent DUID from changing if possible.
    readFromFile();

    uint16_t htype_current = 0;
    uint32_t time_current = 0;
    std::vector<uint8_t> identifier_current;

    // If DUID exists in the file, try to use it as much as possible.
    if (duid_) {
        std::vector<uint8_t> duid_vec = duid_->getDuid();
        if ((duid_->getType() == DUID::DUID_LLT) && (duid_vec.size() > 8)) {
            htype_current = readUint16(&duid_vec[2], duid_vec.size() - 2);
            time_current = readUint32(&duid_vec[4], duid_vec.size() - 4);
            identifier_current.assign(duid_vec.begin() + 8, duid_vec.end());
        }
    }

    uint32_t time_out = time_in;
    // If time is unspecified (ANY), then use the time from current DUID or
    // set it to current time.
    if (time_out == 0) {
        time_out = (time_current != 0 ? time_current :
            static_cast<uint32_t>(time(NULL) - DUID_TIME_EPOCH));
    }

    std::vector<uint8_t> ll_identifier_out = ll_identifier;
    uint16_t htype_out = htype;

    // If link layer address unspecified, use address of one of the
    // interfaces present in the system. Also, update the link
    // layer type accordingly.
    if (ll_identifier_out.empty()) {
        // If DUID doesn't exist yet, generate a new identifier.
        if (identifier_current.empty()) {
            createLinkLayerId(ll_identifier_out, htype_out);
        } else {
            // Use current identifier and hardware type.
            ll_identifier_out = identifier_current;
            htype_out = htype_current;
        }

    } else if (htype_out == 0) {
        // If link layer type unspecified and link layer adddress
        // is specified, use current type or HTYPE_ETHER.
        htype_out = ((htype_current != 0) ? htype_current :
                     static_cast<uint16_t>(HTYPE_ETHER));

    }

    // Render DUID.
    std::vector<uint8_t> duid_out(DUID_TYPE_LEN + sizeof(time_out) +
                                  sizeof(htype_out));
    writeUint16(DUID::DUID_LLT, &duid_out[0], 2);
    writeUint16(htype_out, &duid_out[2], 2);
    writeUint32(time_out, &duid_out[4], 4);
    duid_out.insert(duid_out.end(), ll_identifier_out.begin(),
                    ll_identifier_out.end());

    // Set new DUID and persist in a file.
    set(duid_out);
}

void
DUIDFactory::createEN(const uint32_t enterprise_id,
                      const std::vector<uint8_t>& identifier) {
    // We'll need DUID stored in the file to compare it against the
    // new configuration. If the new configuration indicates that some
    // bits of the DUID should be generated we'll first try to use the
    // values stored in the file to prvent DUID from changing if possible.
    readFromFile();

    uint32_t enterprise_id_current = 0;
    std::vector<uint8_t> identifier_current;

    // If DUID exists in the file, try to use it as much as possible.
    if (duid_) {
        std::vector<uint8_t> duid_vec = duid_->getDuid();
        if ((duid_->getType() == DUID::DUID_EN) && (duid_vec.size() > 6)) {
            enterprise_id_current = readUint32(&duid_vec[2], duid_vec.size() - 2);
            identifier_current.assign(duid_vec.begin() + 6, duid_vec.end());
        }
    }

    // Enterprise id 0 means "unspecified". In this case, try to use existing
    // DUID's enterprise id, or use ISC enterprise id.
    uint32_t enterprise_id_out = enterprise_id;
    if (enterprise_id_out == 0) {
        if (enterprise_id_current != 0) {
            enterprise_id_out = enterprise_id_current;
        } else {
            enterprise_id_out = ENTERPRISE_ID_ISC;
        }
    }

    // Render DUID.
    std::vector<uint8_t> duid_out(DUID_TYPE_LEN + ENTERPRISE_ID_LEN);
    writeUint16(DUID::DUID_EN, &duid_out[0], 2);
    writeUint32(enterprise_id_out, &duid_out[2], ENTERPRISE_ID_LEN);

    // If no identifier specified, we'll have to use the one from the
    // DUID file or generate new.
    if (identifier.empty()) {
        // No DUID file, so generate new.
        if (identifier_current.empty()) {
            // Identifier is empty, so we have to extend the DUID by 6 bytes
            // to fit the random identifier.
            duid_out.resize(DUID_TYPE_LEN + ENTERPRISE_ID_LEN +
                            DUID_EN_IDENTIFIER_LEN);
            // Variable length identifier consists of random numbers. The generated
            // identifier is always 6 bytes long.
            ::srandom(time(NULL));
            fillRandom(&duid_out[DUID_TYPE_LEN + ENTERPRISE_ID_LEN],
                       &duid_out[DUID_TYPE_LEN + ENTERPRISE_ID_LEN +
                                 DUID_EN_IDENTIFIER_LEN]);
        } else {
            // Append existing identifier.
            duid_out.insert(duid_out.end(), identifier_current.begin(),
                            identifier_current.end());
        }

    } else {
        // Append the specified identifier to the end of DUID.
        duid_out.insert(duid_out.end(), identifier.begin(), identifier.end());
    }

    // Set new DUID and persist in a file.
    set(duid_out);
}

void
DUIDFactory::createLL(const uint16_t htype,
                      const std::vector<uint8_t>& ll_identifier) {
    // We'll need DUID stored in the file to compare it against the
    // new configuration. If the new configuration indicates that some
    // bits of the DUID should be generated we'll first try to use the
    // values stored in the file to prvent DUID from changing if possible.
    readFromFile();

    uint16_t htype_current = 0;
    std::vector<uint8_t> identifier_current;

    // If DUID exists in the file, try to use it as much as possible.
    if (duid_) {
        std::vector<uint8_t> duid_vec = duid_->getDuid();
        if ((duid_->getType() == DUID::DUID_LL) && (duid_vec.size() > 4)) {
            htype_current = readUint16(&duid_vec[2], duid_vec.size() - 2);
            identifier_current.assign(duid_vec.begin() + 4, duid_vec.end());
        }
    }

    std::vector<uint8_t> ll_identifier_out = ll_identifier;
    uint16_t htype_out = htype;

    // If link layer address unspecified, use address of one of the
    // interfaces present in the system. Also, update the link
    // layer type accordingly.
    if (ll_identifier_out.empty()) {
        // If DUID doesn't exist yet, generate a new identifier.
        if (identifier_current.empty()) {
            createLinkLayerId(ll_identifier_out, htype_out);
        } else {
            // Use current identifier and hardware type.
            ll_identifier_out = identifier_current;
            htype_out = htype_current;
        }

    } else if (htype_out == 0) {
        // If link layer type unspecified and link layer adddress
        // is specified, use current type or HTYPE_ETHER.
        htype_out = ((htype_current != 0) ? htype_current :
            static_cast<uint16_t>(HTYPE_ETHER));

    }

    // Render DUID.
    std::vector<uint8_t> duid_out(DUID_TYPE_LEN + sizeof(htype_out));
    writeUint16(DUID::DUID_LL, &duid_out[0], 2);
    writeUint16(htype_out, &duid_out[2], 2);
    duid_out.insert(duid_out.end(), ll_identifier_out.begin(),
                    ll_identifier_out.end());

    // Set new DUID and persist in a file.
    set(duid_out);
}

void
DUIDFactory::createLinkLayerId(std::vector<uint8_t>& identifier,
                               uint16_t& htype) const {
    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();

    // Let's find suitable interface.
    BOOST_FOREACH(IfacePtr iface, ifaces) {
        // All the following checks could be merged into one multi-condition
        // statement, but let's keep them separated as perhaps one day
        // we will grow knobs to selectively turn them on or off. Also,
        // this code is used only *once* during first start on a new machine
        // and then server-id is stored. (or at least it will be once
        // DUID storage is implemented)

        // I wish there was a this_is_a_real_physical_interface flag...

        // MAC address should be at least 6 bytes. Although there is no such
        // requirement in any RFC, all decent physical interfaces (Ethernet,
        // WiFi, InfiniBand, etc.) have at least 6 bytes long MAC address.
        // We want to/ base our DUID on real hardware address, rather than
        // virtual interface that pretends that underlying IP address is its
        // MAC.
        if (iface->getMacLen() < MIN_MAC_LEN) {
            continue;
        }

        // Let's don't use loopback.
        if (iface->flag_loopback_) {
            continue;
        }

        // Let's skip downed interfaces. It is better to use working ones.
        if (!iface->flag_up_) {
            continue;
        }

        // Some interfaces (like lo on Linux) report 6-bytes long
        // MAC address 00:00:00:00:00:00. Let's not use such weird interfaces
        // to generate DUID.
        if (isRangeZero(iface->getMac(), iface->getMac() + iface->getMacLen())) {
            continue;
        }

        // Assign link layer address and type.
        identifier.assign(iface->getMac(), iface->getMac() + iface->getMacLen());
        htype = iface->getHWType();
    }

    // We failed to find an interface which link layer address could be
    // used for generating DUID-LLT.
    if (identifier.empty()) {
        isc_throw(Unexpected, "unable to find suitable interface for "
                  " generating a DUID-LLT");
    }
}

void
DUIDFactory::set(const std::vector<uint8_t>& duid_vector) {
    // Check the minimal length.
    if (duid_vector.size() < DUID::MIN_DUID_LEN) {
        isc_throw(BadValue, "generated DUID must have at least "
                  << DUID::MIN_DUID_LEN << " bytes");
    }

    // Store DUID in a file if file location specified.
    if (isStored()) {
        std::ofstream ofs;
        try {
            ofs.open(storage_location_.c_str(), std::ofstream::out |
                     std::ofstream::trunc);
            if (!ofs.good()) {
                isc_throw(InvalidOperation, "unable to open DUID file "
                          << storage_location_ << " for writing");
            }

            // Create temporary DUID object.
            DUID duid(duid_vector);

            // Write DUID to file.
            ofs << duid.toText();
            if (!ofs.good()) {
                isc_throw(InvalidOperation, "unable to write to DUID file "
                          << storage_location_);
            }
        } catch (...) {
            // Close stream before leaving the function.
            ofs.close();
            throw;
        }
        ofs.close();
    }

    duid_.reset(new DUID(duid_vector));
}

DuidPtr
DUIDFactory::get() {
    // If DUID is initialized, return it.
    if (duid_) {
        return (duid_);
    }

    // Try to read DUID from file, if it exists.
    readFromFile();
    if (duid_) {
        return (duid_);
    }

    // DUID doesn't exist, so we need to create it.
    const std::vector<uint8_t> empty_vector;
    try {
        // There is no file with a DUID or the DUID stored in the file is
        // invalid. We need to generate a new DUID.
        createLLT(0, 0, empty_vector);

    } catch (...) {
        // It is possible that the creation of the DUID-LLT failed if there
        // are no suitable interfaces present in the system.
    }

    if (!duid_) {
        // Fall back to creation of DUID enterprise. If that fails we allow
        // for propagating exception to indicate a fatal error. This may
        // be the case if we failed to write it to a file.
        createEN(0, empty_vector);
    }

    return (duid_);
}

void
DUIDFactory::readFromFile() {
    duid_.reset();

    std::ostringstream duid_str;
   if (isStored()) {
        std::ifstream ifs;
        ifs.open(storage_location_.c_str(), std::ifstream::in);
        if (ifs.good()) {
            std::string read_contents;
            while (!ifs.eof() && ifs.good()) {
                ifs >> read_contents;
                duid_str << read_contents;
            }
        }
        ifs.close();

        // If we have read anything from the file, let's try to use it to
        // create a DUID.
        if (duid_str.tellp() != std::streampos(0)) {
            try {
                duid_.reset(new DUID(DUID::fromText(duid_str.str())));

            } catch (...) {
                // The contents of this file don't represent a valid DUID.
                // We'll need to generate it.
            }
        }
   }
}


}; // end of isc::dhcp namespace
}; // end of isc namespace
