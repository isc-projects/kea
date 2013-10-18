// Copyright (C) 2011-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/pkt6.h>
#include <exceptions/exceptions.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {

Pkt6::RelayInfo::RelayInfo()
    :msg_type_(0), hop_count_(0), linkaddr_("::"), peeraddr_("::"), relay_msg_len_(0) {
    // interface_id_, subscriber_id_, remote_id_ initialized to NULL
    // echo_options_ initialized to empty collection
}

Pkt6::Pkt6(const uint8_t* buf, uint32_t buf_len, DHCPv6Proto proto /* = UDP */) :
    proto_(proto),
    msg_type_(0),
    transid_(rand()%0xffffff),
    iface_(""),
    ifindex_(-1),
    local_addr_("::"),
    remote_addr_("::"),
    local_port_(0),
    remote_port_(0),
    buffer_out_(0) {
    data_.resize(buf_len);
    memcpy(&data_[0], buf, buf_len);
}

Pkt6::Pkt6(uint8_t msg_type, uint32_t transid, DHCPv6Proto proto /*= UDP*/) :
    proto_(proto),
    msg_type_(msg_type),
    transid_(transid),
    iface_(""),
    ifindex_(-1),
    local_addr_("::"),
    remote_addr_("::"),
    local_port_(0),
    remote_port_(0),
    buffer_out_(0) {
}

uint16_t Pkt6::len() {
    if (relay_info_.empty()) {
        return (directLen());
    } else {
        // Unfortunately we need to re-calculate relay size every time, because
        // we need to make sure that once a new option is added, its extra size
        // is reflected in Pkt6::len().
        calculateRelaySizes();
        return (relay_info_[0].relay_msg_len_ + getRelayOverhead(relay_info_[0]));
    }
}

OptionPtr Pkt6::getAnyRelayOption(uint16_t opt_type, RelaySearchOrder order) {

    if (relay_info_.empty()) {
        // There's no relay info, this is a direct message
        return (OptionPtr());
    }

    int start = 0; // First relay to check
    int end = 0;   // Last relay to check
    int direction = 0; // How we going to iterate: forward or backward?

    switch (order) {
    case RELAY_SEARCH_FROM_CLIENT:
        // Search backwards
        start = relay_info_.size() - 1;
        end = 0;
        direction = -1;
        break;
    case RELAY_SEARCH_FROM_SERVER:
        // Search forward
        start = 0;
        end = relay_info_.size() - 1;
        direction = 1;
        break;
    case RELAY_GET_FIRST:
        // Look at the innermost relay only
        start = relay_info_.size() - 1;
        end = start;
        direction = 1;
        break;
    case RELAY_GET_LAST:
        // Look at the outermost relay only
        start = 0;
        end = 0;
        direction = 1;
    }

    // This is a tricky loop. It must go from start to end, but it must work in
    // both directions (start > end; or start < end). We can't use regular
    // exit condition, because we don't know whether to use i <= end or i >= end.
    // That's why we check if in the next iteration we would go past the
    // list (end + direction). It is similar to STL concept of end pointing
    // to a place after the last element
    for (int i = start; i != end + direction; i += direction) {
        OptionPtr opt = getRelayOption(opt_type, i);
        if (opt) {
            return (opt);
        }
    }

    // We iterated over specified relays and haven't found what we were
    // looking for
    return (OptionPtr());
}


OptionPtr Pkt6::getRelayOption(uint16_t opt_type, uint8_t relay_level) {
    if (relay_level >= relay_info_.size()) {
        isc_throw(OutOfRange, "This message was relayed " << relay_info_.size() << " time(s)."
                  << " There is no info about " << relay_level + 1 << " relay.");
    }

    for (OptionCollection::iterator it = relay_info_[relay_level].options_.begin();
         it != relay_info_[relay_level].options_.end(); ++it) {
        if ((*it).second->getType() == opt_type) {
            return (it->second);
        }
    }

    return (OptionPtr());
}

uint16_t Pkt6::getRelayOverhead(const RelayInfo& relay) const {
    uint16_t len = DHCPV6_RELAY_HDR_LEN // fixed header
        + Option::OPTION6_HDR_LEN; // header of the relay-msg option

    for (OptionCollection::const_iterator opt = relay.options_.begin();
         opt != relay.options_.end(); ++opt) {
        len += (opt->second)->len();
    }

    return (len);
}

uint16_t Pkt6::calculateRelaySizes() {

    uint16_t len = directLen(); // start with length of all options

    for (int relay_index = relay_info_.size(); relay_index > 0; --relay_index) {
        relay_info_[relay_index - 1].relay_msg_len_ = len;
        len += getRelayOverhead(relay_info_[relay_index - 1]);
    }

    return (len);
}

uint16_t Pkt6::directLen() const {
    uint16_t length = DHCPV6_PKT_HDR_LEN; // DHCPv6 header

    for (OptionCollection::const_iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }

    return (length);
}


void
Pkt6::pack() {
    switch (proto_) {
    case UDP:
        packUDP();
        break;
    case TCP:
        packTCP();
        break;
    default:
        isc_throw(BadValue, "Invalid protocol specified (non-TCP, non-UDP)");
    }
}

void
Pkt6::packUDP() {
    try {
        // Make sure that the buffer is empty before we start writting to it.
        buffer_out_.clear();

        // is this a relayed packet?
        if (!relay_info_.empty()) {

            // calculate size needed for each relay (if there is only one relay,
            // then it will be equal to "regular" length + relay-forw header +
            // size of relay-msg option header + possibly size of interface-id
            // option (if present). If there is more than one relay, the whole
            // process is called iteratively for each relay.
            calculateRelaySizes();

            // Now for each relay, we need to...
            for (vector<RelayInfo>::iterator relay = relay_info_.begin();
                 relay != relay_info_.end(); ++relay) {

                // build relay-forw/relay-repl header (see RFC3315, section 7)
                buffer_out_.writeUint8(relay->msg_type_);
                buffer_out_.writeUint8(relay->hop_count_);
                buffer_out_.writeData(&(relay->linkaddr_.toBytes()[0]),
                                     isc::asiolink::V6ADDRESS_LEN);
                buffer_out_.writeData(&relay->peeraddr_.toBytes()[0],
                                     isc::asiolink::V6ADDRESS_LEN);

                // store every option in this relay scope. Usually that will be
                // only interface-id, but occasionally other options may be
                // present here as well (vendor-opts for Cable modems,
                // subscriber-id, remote-id, options echoed back from Echo
                // Request Option, etc.)
                for (OptionCollection::const_iterator opt =
                         relay->options_.begin();
                     opt != relay->options_.end(); ++opt) {
                    (opt->second)->pack(buffer_out_);
                }

                // and include header relay-msg option. Its payload will be
                // generated in the next iteration (if there are more relays)
                // or outside the loop (if there are no more relays and the
                // payload is a direct message)
                buffer_out_.writeUint16(D6O_RELAY_MSG);
                buffer_out_.writeUint16(relay->relay_msg_len_);
            }

        }

        // DHCPv6 header: message-type (1 octect) + transaction id (3 octets)
        buffer_out_.writeUint8(msg_type_);
        // store 3-octet transaction-id
        buffer_out_.writeUint8( (transid_ >> 16) & 0xff );
        buffer_out_.writeUint8( (transid_ >> 8) & 0xff );
        buffer_out_.writeUint8( (transid_) & 0xff );

        // the rest are options
        LibDHCP::packOptions(buffer_out_, options_);
    }
    catch (const Exception& e) {
       // An exception is thrown and message will be written to Logger
       isc_throw(InvalidOperation, e.what());
    }
}

void
Pkt6::packTCP() {
    /// TODO Implement this function.
    isc_throw(NotImplemented, "DHCPv6 over TCP (bulk leasequery and failover)"
              "not implemented yet.");
}

bool
Pkt6::unpack() {
    switch (proto_) {
    case UDP:
        return unpackUDP();
    case TCP:
        return unpackTCP();
    default:
        isc_throw(BadValue, "Invalid protocol specified (non-TCP, non-UDP)");
    }
    return (false); // never happens
}

bool
Pkt6::unpackUDP() {
    if (data_.size() < 4) {
        // @todo: throw exception here informing that packet is truncated
        // once we turn this function to void.
        return (false);
    }
    msg_type_ = data_[0];
    switch (msg_type_) {
    case DHCPV6_SOLICIT:
    case DHCPV6_ADVERTISE:
    case DHCPV6_REQUEST:
    case DHCPV6_CONFIRM:
    case DHCPV6_RENEW:
    case DHCPV6_REBIND:
    case DHCPV6_REPLY:
    case DHCPV6_DECLINE:
    case DHCPV6_RECONFIGURE:
    case DHCPV6_INFORMATION_REQUEST:
    default: // assume that uknown messages are not using relay format
        {
            return (unpackMsg(data_.begin(), data_.end()));
        }
    case DHCPV6_RELAY_FORW:
    case DHCPV6_RELAY_REPL:
        return (unpackRelayMsg());
    }
}

bool
Pkt6::unpackMsg(OptionBuffer::const_iterator begin,
                OptionBuffer::const_iterator end) {
    if (std::distance(begin, end) < 4) {
        // truncated message (less than 4 bytes)
        return (false);
    }

    msg_type_ = *begin++;

    transid_ = ( (*begin++) << 16 ) +
        ((*begin++) << 8) + (*begin++);
    transid_ = transid_ & 0xffffff;

    try {
        OptionBuffer opt_buffer(begin, end);

        // If custom option parsing function has been set, use this function
        // to parse options. Otherwise, use standard function from libdhcp.
        if (callback_.empty()) {
            LibDHCP::unpackOptions6(opt_buffer, "dhcp6", options_);
        } else {
            // The last two arguments hold the DHCPv6 Relay message offset and
            // length. Setting them to NULL because we are dealing with the
            // not-relayed message.
            callback_(opt_buffer, "dhcp6", options_, NULL, NULL);
        }
    } catch (const Exception& e) {
        // @todo: throw exception here once we turn this function to void.
        return (false);
    }
    return (true);
}

bool
Pkt6::unpackRelayMsg() {

    // we use offset + bufsize, because we want to avoid creating unnecessary
    // copies. There may be up to 32 relays. While using InputBuffer would
    // be probably a bit cleaner, copying data up to 32 times is unacceptable
    // price here. Hence a single buffer with offets and lengths.
    size_t bufsize = data_.size();
    size_t offset = 0;

    while (bufsize >= DHCPV6_RELAY_HDR_LEN) {

        RelayInfo relay;

        size_t relay_msg_offset = 0;
        size_t relay_msg_len = 0;

        // parse fixed header first (first 34 bytes)
        relay.msg_type_ = data_[offset++];
        relay.hop_count_ = data_[offset++];
        relay.linkaddr_ = IOAddress::fromBytes(AF_INET6, &data_[offset]);
        offset += isc::asiolink::V6ADDRESS_LEN;
        relay.peeraddr_ = IOAddress::fromBytes(AF_INET6, &data_[offset]);
        offset += isc::asiolink::V6ADDRESS_LEN;
        bufsize -= DHCPV6_RELAY_HDR_LEN; // 34 bytes (1+1+16+16)

        try {
            // parse the rest as options
            OptionBuffer opt_buffer(&data_[offset], &data_[offset+bufsize]);

            // If custom option parsing function has been set, use this function
            // to parse options. Otherwise, use standard function from libdhcp.
            if (callback_.empty()) {
                LibDHCP::unpackOptions6(opt_buffer, "dhcp6", relay.options_,
                                        &relay_msg_offset, &relay_msg_len);
            } else {
                callback_(opt_buffer, "dhcp6", relay.options_,
                          &relay_msg_offset, &relay_msg_len);
            }

            /// @todo: check that each option appears at most once
            //relay.interface_id_ = options->getOption(D6O_INTERFACE_ID);
            //relay.subscriber_id_ = options->getOption(D6O_SUBSCRIBER_ID);
            //relay.remote_id_ = options->getOption(D6O_REMOTE_ID);

            if (relay_msg_offset == 0 || relay_msg_len == 0) {
                isc_throw(BadValue, "Mandatory relay-msg option missing");
            }

            // store relay information parsed so far
            addRelayInfo(relay);

            /// @todo: implement ERO here

            if (relay_msg_len >= bufsize) {
                // length of the relay_msg option extends beyond end of the message
                isc_throw(Unexpected, "Relay-msg option is truncated.");
                return false;
            }
            uint8_t inner_type = data_[offset + relay_msg_offset];
            offset += relay_msg_offset; // offset is relative
            bufsize = relay_msg_len;    // length is absolute

            if ( (inner_type != DHCPV6_RELAY_FORW) &&
                 (inner_type != DHCPV6_RELAY_REPL)) {
                // Ok, the inner message is not encapsulated, let's decode it
                // directly
                return (unpackMsg(data_.begin() + offset, data_.begin() + offset
                                  + relay_msg_len));
            }

            // Oh well, there's inner relay-forw or relay-repl inside. Let's
            // unpack it as well. The next loop iteration will take care
            // of that.
        } catch (const Exception& e) {
            /// @todo: throw exception here once we turn this function to void.
            return (false);
        }
    }

    if ( (offset == data_.size()) && (bufsize == 0) ) {
        // message has been parsed completely
        return (true);
    }

    /// @todo: log here that there are additional unparsed bytes
    return (true);
}

void
Pkt6::addRelayInfo(const RelayInfo& relay) {
    if (relay_info_.size() > 32) {
        isc_throw(BadValue, "Massage cannot be encapsulated more than 32 times");
    }

    /// @todo: Implement type checks here (e.g. we could receive relay-forw in relay-repl)
    relay_info_.push_back(relay);
}

bool
Pkt6::unpackTCP() {
    isc_throw(Unexpected, "DHCPv6 over TCP (bulk leasequery and failover) "
              "not implemented yet.");
}


std::string
Pkt6::toText() {
    stringstream tmp;
    tmp << "localAddr=[" << local_addr_.toText() << "]:" << local_port_
        << " remoteAddr=[" << remote_addr_.toText()
        << "]:" << remote_port_ << endl;
    tmp << "msgtype=" << static_cast<int>(msg_type_) << ", transid=0x" <<
        hex << transid_ << dec << endl;
    for (isc::dhcp::OptionCollection::iterator opt=options_.begin();
         opt != options_.end();
         ++opt) {
        tmp << opt->second->toText() << std::endl;
    }
    return tmp.str();
}

OptionPtr
Pkt6::getOption(uint16_t opt_type) {
    isc::dhcp::OptionCollection::const_iterator x = options_.find(opt_type);
    if (x!=options_.end()) {
        return (*x).second;
    }
    return OptionPtr(); // NULL
}

isc::dhcp::OptionCollection
Pkt6::getOptions(uint16_t opt_type) {
    isc::dhcp::OptionCollection found;

    for (OptionCollection::const_iterator x = options_.begin();
         x != options_.end(); ++x) {
        if (x->first == opt_type) {
            found.insert(make_pair(opt_type, x->second));
        }
    }
    return (found);
}

void
Pkt6::addOption(const OptionPtr& opt) {
    options_.insert(pair<int, boost::shared_ptr<Option> >(opt->getType(), opt));
}

bool
Pkt6::delOption(uint16_t type) {
    isc::dhcp::OptionCollection::iterator x = options_.find(type);
    if (x!=options_.end()) {
        options_.erase(x);
        return (true); // delete successful
    }
    return (false); // can't find option to be deleted
}

void Pkt6::repack() {
    buffer_out_.writeData(&data_[0], data_.size());
}

void
Pkt6::updateTimestamp() {
    timestamp_ = boost::posix_time::microsec_clock::universal_time();
}

const char*
Pkt6::getName(uint8_t type) {
    static const char* CONFIRM = "CONFIRM";
    static const char* DECLINE = "DECLINE";
    static const char* INFORMATION_REQUEST = "INFORMATION_REQUEST";
    static const char* REBIND = "REBIND";
    static const char* RELEASE = "RELEASE";
    static const char* RENEW = "RENEW";
    static const char* REQUEST = "REQUEST";
    static const char* SOLICIT = "SOLICIT";
    static const char* UNKNOWN = "UNKNOWN";

    switch (type) {
    case DHCPV6_CONFIRM:
        return (CONFIRM);

    case DHCPV6_DECLINE:
        return (DECLINE);

    case DHCPV6_INFORMATION_REQUEST:
        return (INFORMATION_REQUEST);

    case DHCPV6_REBIND:
        return (REBIND);

    case DHCPV6_RELEASE:
        return (RELEASE);

    case DHCPV6_RENEW:
        return (RENEW);

    case DHCPV6_REQUEST:
        return (REQUEST);

    case DHCPV6_SOLICIT:
        return (SOLICIT);

    default:
        ;
    }
    return (UNKNOWN);
}

const char* Pkt6::getName() const {
    return (getName(getType()));
}

void Pkt6::copyRelayInfo(const Pkt6Ptr& question) {

    // We use index rather than iterator, because we need that as a parameter
    // passed to getRelayOption()
    for (int i = 0; i < question->relay_info_.size(); ++i) {
        RelayInfo info;
        info.msg_type_ = DHCPV6_RELAY_REPL;
        info.hop_count_ = question->relay_info_[i].hop_count_;
        info.linkaddr_ = question->relay_info_[i].linkaddr_;
        info.peeraddr_ = question->relay_info_[i].peeraddr_;

        // Is there an interface-id option in this nesting level?
        // If there is, we need to echo it back
        OptionPtr opt = question->getRelayOption(D6O_INTERFACE_ID, i);
        // taken from question->RelayInfo_[i].options_
        if (opt) {
            info.options_.insert(make_pair(opt->getType(), opt));
        }

        /// @todo: Implement support for ERO (Echo Request Option, RFC4994)

        // Add this relay-forw info (client's message) to our relay-repl
        // message (server's response)
        relay_info_.push_back(info);
    }
}

bool
Pkt6::inClass(const std::string& client_class) {
    return (classes_.find(client_class) != classes_.end());
}

void
Pkt6::addClass(const std::string& client_class) {
    if (classes_.find(client_class) == classes_.end()) {
        classes_.insert(client_class);
    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
