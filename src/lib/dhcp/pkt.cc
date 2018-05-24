// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <utility>
#include <dhcp/pkt.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/hwaddr.h>
#include <vector>

namespace isc {
namespace dhcp {

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
     buffer_out_(0),
     copy_retrieved_options_(false)
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
     buffer_out_(0),
     copy_retrieved_options_(false)
{

    if (len != 0) {
        if (buf == NULL) {
            isc_throw(InvalidParameter, "data buffer passed to Pkt is NULL");
        }
        data_.resize(len);
        memcpy(&data_[0], buf, len);
    }
}

void
Pkt::addOption(const OptionPtr& opt) {
    options_.insert(std::pair<int, OptionPtr>(opt->getType(), opt));
}

OptionPtr
Pkt::getNonCopiedOption(const uint16_t type) const {
    OptionCollection::const_iterator x = options_.find(type);
    if (x != options_.end()) {
        return (x->second);
    }
    return (OptionPtr());
}

OptionPtr
Pkt::getOption(const uint16_t type) {
    OptionCollection::iterator x = options_.find(type);
    if (x != options_.end()) {
        if (copy_retrieved_options_) {
            OptionPtr option_copy = x->second->clone();
            x->second = option_copy;
        }
        return (x->second);
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
    return (classes_.contains(client_class));
}

void
Pkt::addClass(const std::string& client_class, bool required) {
    ClientClasses& classes = !required ? classes_ : required_classes_;
    if (!classes.contains(client_class)) {
        classes.insert(client_class);
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

    /// @todo: Implement an array of method pointers instead of set of ifs

    // Method 1: from raw sockets.
    if (hw_addr_src & HWAddr::HWADDR_SOURCE_RAW) {
        mac = getRemoteHWAddr();
        if (mac) {
            mac->source_ = HWAddr::HWADDR_SOURCE_RAW;
            return (mac);
        } else if (hw_addr_src == HWAddr::HWADDR_SOURCE_RAW) {
            // If we're interested only in RAW sockets as source of that info,
            // there's no point in trying other options.
            return (HWAddrPtr());
        }
    }

    // Method 2: From client link-layer address option inserted by a relay
    if (hw_addr_src & HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION) {
        mac = getMACFromIPv6RelayOpt();
        if (mac) {
            return (mac);
        } else if (hw_addr_src ==  HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION) {
            // If we're interested only in RFC6939 link layer address as source
            // of that info, there's no point in trying other options.
            return (HWAddrPtr());
        }
    }

    // Method 3: Extracted from DUID-LLT or DUID-LL
    if(hw_addr_src & HWAddr::HWADDR_SOURCE_DUID) {
        mac = getMACFromDUID();
        if (mac) {
            return (mac);
        } else if (hw_addr_src == HWAddr::HWADDR_SOURCE_DUID) {
            // If the only source allowed is DUID then we can skip the other
            // methods.
            return (HWAddrPtr());
        }
    }

    // Method 4: Extracted from source IPv6 link-local address
    if (hw_addr_src & HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL) {
        mac = getMACFromSrcLinkLocalAddr();
        if (mac) {
            return (mac);
        } else if (hw_addr_src ==  HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL) {
            // If we're interested only in link-local addr as source of that
            // info, there's no point in trying other options.
            return (HWAddrPtr());
        }
    }

    // Method 5: From remote-id option inserted by a relay
    if(hw_addr_src & HWAddr::HWADDR_SOURCE_REMOTE_ID) {
        mac = getMACFromRemoteIdRelayOption();
        if (mac) {
            return (mac);
        } else if (hw_addr_src == HWAddr::HWADDR_SOURCE_REMOTE_ID) {
            // If the only source allowed is remote-id option then we can skip
            // the other methods.
            return (HWAddrPtr());
        }
    }

    // Method 6: From subscriber-id option inserted by a relay

    // Method 7: From docsis options
    if (hw_addr_src & HWAddr::HWADDR_SOURCE_DOCSIS_CMTS) {
        mac = getMACFromDocsisCMTS();
        if (mac) {
            return (mac);
        } else if (hw_addr_src == HWAddr::HWADDR_SOURCE_DOCSIS_CMTS) {
            // If we're interested only in CMTS options as a source of that
            // info, there's no point in trying other options.
            return (HWAddrPtr());
        }
    }

    // Method 8: From docsis options
    if (hw_addr_src & HWAddr::HWADDR_SOURCE_DOCSIS_MODEM) {
        mac = getMACFromDocsisModem();
        if (mac) {
            return (mac);
        } else if (hw_addr_src == HWAddr::HWADDR_SOURCE_DOCSIS_MODEM) {
            // If we're interested only in CMTS options as a source of that
            // info, there's no point in trying other options.
            return (HWAddrPtr());
        }
    }

    // Ok, none of the methods were suitable. Return NULL.
    return (HWAddrPtr());
}

HWAddrPtr
Pkt::getMACFromIPv6(const isc::asiolink::IOAddress& addr) {
    HWAddrPtr mac;

    if (addr.isV6LinkLocal()) {
        std::vector<uint8_t> bin = addr.toBytes();

        // Double check that it's of appropriate size
        if ((bin.size() == isc::asiolink::V6ADDRESS_LEN) &&
            // Check that it's link-local (starts with fe80).
            (bin[0] == 0xfe) && (bin[1] == 0x80) &&
            // Check that u bit is set and g is clear.
            // See Section 2.5.1 of RFC2373 for details.
            ((bin[8] & 3) == 2) &&
            // And that the IID is of EUI-64 type.
            (bin[11] == 0xff) && (bin[12] == 0xfe)) {

                // Remove 8 most significant bytes
                bin.erase(bin.begin(), bin.begin() + 8);

                // Ok, we're down to EUI-64 only now: XX:XX:XX:ff:fe:XX:XX:XX
                bin.erase(bin.begin() + 3, bin.begin() + 5);

                // MAC-48 to EUI-64 involves inverting u bit (see explanation
                // in Section 2.5.1 of RFC2373). We need to revert that.
                bin[0] = bin[0] ^ 2;

                // Let's get the interface this packet was received on.
                // We need it to get hardware type
                IfacePtr iface = IfaceMgr::instance().getIface(iface_);
                uint16_t hwtype = 0; // not specified
                if (iface) {
                    hwtype = iface->getHWType();
                }

            mac.reset(new HWAddr(bin, hwtype));
            mac->source_ = HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL;
        }
    }

    return (mac);
}

};
};
