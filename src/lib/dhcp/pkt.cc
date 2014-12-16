// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <utility>
#include <dhcp/pkt.h>
#include <dhcp/iface_mgr.h>
#include <vector>

namespace isc {
namespace dhcp {

const uint32_t Pkt::HWADDR_SOURCE_ANY = 0xffffffff;
const uint32_t Pkt::HWADDR_SOURCE_UNKNOWN = 0x00000000;
const uint32_t Pkt::HWADDR_SOURCE_RAW = 0x00000001;
const uint32_t Pkt::HWADDR_SOURCE_DUID = 0x00000002;
const uint32_t Pkt::HWADDR_SOURCE_IPV6_LINK_LOCAL = 0x00000004;
const uint32_t Pkt::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION = 0x00000008;
const uint32_t Pkt::HWADDR_SOURCE_REMOTE_ID = 0x00000010;
const uint32_t Pkt::HWADDR_SOURCE_SUBSCRIBER_ID = 0x00000020;
const uint32_t Pkt::HWADDR_SOURCE_DOCSIS = 0x00000040;

Pkt::Pkt(uint32_t transid, const isc::asiolink::IOAddress& local_addr,
         const isc::asiolink::IOAddress& remote_addr, uint16_t local_port,
         uint16_t remote_port)
    :transid_(transid),
     iface_(""),
     ifindex_(-1),
     local_addr_(local_addr),
     remote_addr_(remote_addr),
     local_port_(local_port),
     remote_port_(remote_port),
     buffer_out_(0)
{
}

Pkt::Pkt(const uint8_t* buf, uint32_t len, const isc::asiolink::IOAddress& local_addr,
         const isc::asiolink::IOAddress& remote_addr, uint16_t local_port,
         uint16_t remote_port)
    :transid_(0),
     iface_(""),
     ifindex_(-1),
     local_addr_(local_addr),
     remote_addr_(remote_addr),
     local_port_(local_port),
     remote_port_(remote_port),
     buffer_out_(0)
{
    data_.resize(len);
    if (len) {
        memcpy(&data_[0], buf, len);
    }
}

void
Pkt::addOption(const OptionPtr& opt) {
    options_.insert(std::pair<int, OptionPtr>(opt->getType(), opt));
}

OptionPtr
Pkt::getOption(uint16_t type) const {
    OptionCollection::const_iterator x = options_.find(type);
    if (x != options_.end()) {
        return (*x).second;
    }
    return (OptionPtr()); // NULL
}

bool
Pkt::delOption(uint16_t type) {

    isc::dhcp::OptionCollection::iterator x = options_.find(type);
    if (x!=options_.end()) {
        options_.erase(x);
        return (true); // delete successful
    } else {
        return (false); // can't find option to be deleted
    }
}

bool
Pkt::inClass(const std::string& client_class) {
    return (classes_.find(client_class) != classes_.end());
}

void
Pkt::addClass(const std::string& client_class) {
    if (classes_.find(client_class) == classes_.end()) {
        classes_.insert(client_class);
    }
}

void
Pkt::updateTimestamp() {
    timestamp_ = boost::posix_time::microsec_clock::universal_time();
}

void Pkt::repack() {
    if (!data_.empty()) {
        buffer_out_.writeData(&data_[0], data_.size());
    }
}

void
Pkt::setRemoteHWAddr(const uint8_t htype, const uint8_t hlen,
                      const std::vector<uint8_t>& hw_addr) {
    setHWAddrMember(htype, hlen, hw_addr, remote_hwaddr_);
}

void
Pkt::setRemoteHWAddr(const HWAddrPtr& hw_addr) {
    if (!hw_addr) {
        isc_throw(BadValue, "Setting remote HW address to NULL is"
                  << " forbidden.");
    }
    remote_hwaddr_ = hw_addr;
}

void
Pkt::setHWAddrMember(const uint8_t htype, const uint8_t,
                      const std::vector<uint8_t>& hw_addr,
                      HWAddrPtr& storage) {

    storage.reset(new HWAddr(hw_addr, htype));
}

HWAddrPtr
Pkt::getMAC(uint32_t hw_addr_src) {
    HWAddrPtr mac;

    // Method 1: from raw sockets.
    if (hw_addr_src & HWADDR_SOURCE_RAW) {
        mac = getRemoteHWAddr();
        if (mac) {
            return (mac);
        } else if (hw_addr_src == HWADDR_SOURCE_RAW) {
            // If we're interested only in RAW sockets as source of that info,
            // there's no point in trying other options.
            return (HWAddrPtr());
        }
    }

    // Method 2: Extracted from DUID-LLT or DUID-LL

    // Method 3: Extracted from source IPv6 link-local address
    if (hw_addr_src & HWADDR_SOURCE_IPV6_LINK_LOCAL) {
        mac = getMACFromSrcLinkLocalAddr();
        if (mac) {
            return (mac);
        } else if (hw_addr_src ==  HWADDR_SOURCE_IPV6_LINK_LOCAL) {
            // If we're interested only in link-local addr as source of that
            // info, there's no point in trying other options.
            return (HWAddrPtr());
        }
    }

    // Method 4: From client link-layer address option inserted by a relay
    if (hw_addr_src & HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION) {
        mac = getMACFromIPv6RelayOpt();
        if (mac) {
            return (mac);
        } else if (hw_addr_src ==  HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION) {
            // If we're interested only in RFC6939 link layer address as source
            // of that info, there's no point in trying other options.
            return (HWAddrPtr());
        }
    }

    // Method 5: From remote-id option inserted by a relay

    // Method 6: From subscriber-id option inserted by a relay

    // Method 7: From docsis options

    /// @todo: add other MAC acquisition methods here

    // Ok, none of the methods were suitable. Return NULL.
    return (HWAddrPtr());
}

HWAddrPtr
Pkt::getMACFromIPv6(const isc::asiolink::IOAddress& addr) {

    if (!addr.isV6LinkLocal()) {
        return (HWAddrPtr());
    }

    std::vector<uint8_t> bin = addr.toBytes();

    // Double check that it's of appropriate size
    if ((bin.size() != isc::asiolink::V6ADDRESS_LEN) ||

        // Check that it's link-local (starts with fe80).
        (bin[0] != 0xfe) || (bin[1] != 0x80) ||

        // Check that u bit is set and g is clear. See Section 2.5.1 of RFC2373
        // for details.
        ((bin[8] & 3) != 2) ||

        // And that the IID is of EUI-64 type.
        (bin[11] != 0xff) || (bin[12] != 0xfe)) {
        return (HWAddrPtr());
    }

    // Remove 8 most significant bytes
    bin.erase(bin.begin(), bin.begin() + 8);

    // Ok, we're down to EUI-64 only now: XX:XX:XX:ff:fe:XX:XX:XX
    bin.erase(bin.begin() + 3, bin.begin() + 5);

    // MAC-48 to EUI-64 involves inverting u bit (see explanation in Section
    // 2.5.1 of RFC2373). We need to revert that.
    bin[0] = bin[0] ^ 2;

    // Let's get the interface this packet was received on. We need it to get
    // hardware type
    Iface* iface = IfaceMgr::instance().getIface(iface_);
    uint16_t hwtype = 0; // not specified
    if (iface) {
        hwtype = iface->getHWType();
    }

    return (HWAddrPtr(new HWAddr(bin, hwtype)));
}

uint16_t Pkt::MACSourceFromText(const std::string& name) {

    struct {
        const char * name;
        uint32_t type;
    } sources[] = {
        { "any", Pkt::HWADDR_SOURCE_ANY },
        { "raw", Pkt::HWADDR_SOURCE_RAW },
        { "duid", Pkt::HWADDR_SOURCE_DUID },
        { "ipv6-link-local", Pkt::HWADDR_SOURCE_IPV6_LINK_LOCAL },
        { "client-link-addr-option", Pkt::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION },
        { "rfc6939", Pkt::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION },
        { "remote-id", Pkt::HWADDR_SOURCE_REMOTE_ID },
        { "rfc4649", Pkt::HWADDR_SOURCE_REMOTE_ID },
        { "subscriber-id", Pkt::HWADDR_SOURCE_SUBSCRIBER_ID },
        { "rfc4580", Pkt::HWADDR_SOURCE_SUBSCRIBER_ID },
        { "docsis", Pkt::HWADDR_SOURCE_DOCSIS }
    };

    for (int i=0; i < sizeof(sources)/sizeof(sources[0]); ++i) {
        if (name.compare(sources[i].name)) {
            return (sources[i].type);
        }
    }

    isc_throw(BadValue, "Can't convert '" << name << "' to any known MAC source.");
}


};
};
