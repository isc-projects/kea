// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <utility>
#include <dhcp/pkt.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/hwaddr.h>
#include <boost/foreach.hpp>
#include <vector>

using namespace boost::posix_time;

namespace isc {
namespace dhcp {

const std::string PktEvent::SOCKET_RECEIVED("socket_received");
const std::string PktEvent::BUFFER_READ("buffer_read");
const std::string PktEvent::RESPONSE_SENT("response_sent");

Pkt::Pkt(uint32_t transid, const isc::asiolink::IOAddress& local_addr,
         const isc::asiolink::IOAddress& remote_addr, uint16_t local_port,
         uint16_t remote_port)
    : transid_(transid), iface_(""), ifindex_(UNSET_IFINDEX), local_addr_(local_addr),
      remote_addr_(remote_addr), local_port_(local_port),
      remote_port_(remote_port), buffer_out_(0), copy_retrieved_options_(false) {
}

Pkt::Pkt(const uint8_t* buf, uint32_t len, const isc::asiolink::IOAddress& local_addr,
         const isc::asiolink::IOAddress& remote_addr, uint16_t local_port,
         uint16_t remote_port)
    : transid_(0), iface_(""), ifindex_(UNSET_IFINDEX), local_addr_(local_addr),
      remote_addr_(remote_addr), local_port_(local_port),
      remote_port_(remote_port), buffer_out_(0), copy_retrieved_options_(false) {
    if (len != 0) {
        if (buf == NULL) {
            isc_throw(InvalidParameter, "data buffer passed to Pkt is NULL");
        }
        data_.resize(len);
        memcpy(&data_[0], buf, len);
    }
}

OptionCollection
Pkt::cloneOptions() {
    OptionCollection options;
    for (auto const& option : options_) {
        options.emplace(std::make_pair(option.second->getType(), option.second->clone()));
    }
    return (options);
}

void
Pkt::addOption(const OptionPtr& opt) {
    options_.insert(std::pair<int, OptionPtr>(opt->getType(), opt));
}

OptionPtr
Pkt::getNonCopiedOption(const uint16_t type) const {
    auto const& x = options_.find(type);
    if (x != options_.end()) {
        return (x->second);
    }
    return (OptionPtr());
}

OptionPtr
Pkt::getOption(const uint16_t type) {
    auto const& x = options_.find(type);
    if (x != options_.end()) {
        if (copy_retrieved_options_) {
            OptionPtr option_copy = x->second->clone();
            x->second = option_copy;
        }
        return (x->second);
    }
    return (OptionPtr()); // NULL
}

OptionCollection
Pkt::getNonCopiedOptions(const uint16_t opt_type) const {
    std::pair<OptionCollection::const_iterator,
              OptionCollection::const_iterator> range = options_.equal_range(opt_type);
    return (OptionCollection(range.first, range.second));
}

OptionCollection
Pkt::getOptions(const uint16_t opt_type) {
    OptionCollection options_copy;

    std::pair<OptionCollection::iterator,
              OptionCollection::iterator> range = options_.equal_range(opt_type);
    // If options should be copied on retrieval, we should now iterate over
    // matching options, copy them and replace the original ones with new
    // instances.
    if (copy_retrieved_options_) {
        BOOST_FOREACH(auto& opt_it, range) {
            OptionPtr option_copy = opt_it.second->clone();
            opt_it.second = option_copy;
        }
    }
    // Finally, return updated options. This can also be empty in some cases.
    return (OptionCollection(range.first, range.second));
}

bool
Pkt::delOption(uint16_t type) {
    auto const& x = options_.find(type);
    if (x != options_.end()) {
        options_.erase(x);
        return (true); // delete successful
    } else {
        return (false); // can't find option to be deleted
    }
}

bool
Pkt::inClass(const ClientClass& client_class) {
    return (classes_.contains(client_class));
}

void
Pkt::addClass(const ClientClass& client_class, bool required) {
    ClientClasses& classes = !required ? classes_ : required_classes_;
    if (!classes.contains(client_class)) {
        classes.insert(client_class);
        static_cast<void>(subclasses_.push_back(SubClassRelation(client_class, client_class)));
    }
}

void
Pkt::addSubClass(const ClientClass& class_def, const ClientClass& subclass) {
    if (!classes_.contains(class_def)) {
        classes_.insert(class_def);
        static_cast<void>(subclasses_.push_back(SubClassRelation(class_def, subclass)));
    }
    if (!classes_.contains(subclass)) {
        classes_.insert(subclass);
        static_cast<void>(subclasses_.push_back(SubClassRelation(subclass, subclass)));
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


void
Pkt::addPktEvent(const std::string& label, const boost::posix_time::ptime& timestamp) {
    events_.push_back(PktEvent(label, timestamp));
}

void
Pkt::setPktEvent(const std::string& label, const ptime& timestamp) {
    for (auto& event : events_) {
        if (event.label_ == label) {
            event.timestamp_ = timestamp;
            return;
        }
    }

    events_.push_back(PktEvent(label, timestamp));
}

void
Pkt::addPktEvent(const std::string& label, const struct timeval& tv) {
    time_t time_t_secs = tv.tv_sec;
    ptime timestamp = from_time_t(time_t_secs);
    time_duration usecs(0, 0, 0, tv.tv_usec);
    timestamp += usecs;
    addPktEvent(label, timestamp);
}

ptime
Pkt::getPktEventTime(const std::string& label) const {
    for (auto const& event : events_) {
        if (event.label_ == label) {
            return (event.timestamp_);
        }
    }

    return (PktEvent::EMPTY_TIME());
}

void
Pkt::clearPktEvents() {
    events_.clear();
}

std::string
Pkt::dumpPktEvents(bool verbose /* = false */) const {
    std::stringstream oss;
    if (verbose) {
        oss << "Event log: " << std::endl;
    }

    bool first_pass = true;
    boost::posix_time::ptime beg_time;
    boost::posix_time::ptime prev_time;
    for (auto const& event : events_) {
        if (!verbose) {
            oss << (first_pass ? "" : ", ") <<  event.timestamp_ << " : " << event.label_;
        } else {
            oss << event.timestamp_ << " : " << event.label_;
            if (first_pass) {
                oss << std::endl;
                beg_time = event.timestamp_;
            } else {
                oss << " elapsed: " << event.timestamp_ - prev_time << std::endl;
            }

            prev_time = event.timestamp_;
        }

        first_pass = false;
    }

    if (verbose) {
        oss << "total elapsed: " << prev_time - beg_time;
    }

    return (oss.str());
}

} // end of namespace isc::dhcp
} // end of namespace isc
