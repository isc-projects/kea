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

#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_vendor_class.h>
#include <dhcp/option_vendor.h>
#include <dhcp/pkt6.h>
#include <dhcp/docsis3_option_defs.h>
#include <util/io_utilities.h>
#include <exceptions/exceptions.h>
#include <dhcp/duid.h>
#include <dhcp/iface_mgr.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc::asiolink;

/// @brief Default address used in Pkt6 constructor
const IOAddress DEFAULT_ADDRESS6("::");

namespace isc {
namespace dhcp {

Pkt6::RelayInfo::RelayInfo()
    :msg_type_(0), hop_count_(0), linkaddr_(DEFAULT_ADDRESS6),
    peeraddr_(DEFAULT_ADDRESS6), relay_msg_len_(0) {
}

Pkt6::Pkt6(const uint8_t* buf, uint32_t buf_len, DHCPv6Proto proto /* = UDP */)
   :Pkt(buf, buf_len, DEFAULT_ADDRESS6, DEFAULT_ADDRESS6, 0, 0),
    proto_(proto), msg_type_(0) {
}

Pkt6::Pkt6(uint8_t msg_type, uint32_t transid, DHCPv6Proto proto /*= UDP*/)
:Pkt(transid, DEFAULT_ADDRESS6, DEFAULT_ADDRESS6, 0, 0), proto_(proto),
    msg_type_(msg_type) {
}

size_t Pkt6::len() {
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
        LibDHCP::packOptions6(buffer_out_, options_);
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
              " not implemented yet.");
}

void
Pkt6::unpack() {
    switch (proto_) {
    case UDP:
        return unpackUDP();
    case TCP:
        return unpackTCP();
    default:
        isc_throw(BadValue, "Invalid protocol specified (non-TCP, non-UDP)");
    }
}

void
Pkt6::unpackUDP() {
    if (data_.size() < 4) {
        isc_throw(BadValue, "Received truncated UDP DHCPv6 packet of size "
                  << data_.size() << ", DHCPv6 header alone has 4 bytes.");
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
    case DHCPV6_DHCPV4_QUERY:
    case DHCPV6_DHCPV4_RESPONSE:
    default: // assume that uknown messages are not using relay format
        {
            return (unpackMsg(data_.begin(), data_.end()));
        }
    case DHCPV6_RELAY_FORW:
    case DHCPV6_RELAY_REPL:
        return (unpackRelayMsg());
    }
}

void
Pkt6::unpackMsg(OptionBuffer::const_iterator begin,
                OptionBuffer::const_iterator end) {
    size_t size = std::distance(begin, end);
    if (size < 4) {
        // truncated message (less than 4 bytes)
        isc_throw(BadValue, "Received truncated UDP DHCPv6 packet of size "
                  << data_.size() << ", DHCPv6 header alone has 4 bytes.");
    }

    msg_type_ = *begin++;

    transid_ = ( (*begin++) << 16 ) +
        ((*begin++) << 8) + (*begin++);
    transid_ = transid_ & 0xffffff;

    // See below about invoking Postel's law, as we aren't using
    // size we don't need to update it.  If we do so in the future
    // perhaps for stats gathering we can uncomment this.
    //    size -= sizeof(uint32_t); // We just parsed 4 bytes header

    OptionBuffer opt_buffer(begin, end);

    // If custom option parsing function has been set, use this function
    // to parse options. Otherwise, use standard function from libdhcp.
    size_t offset;
    if (callback_.empty()) {
        offset = LibDHCP::unpackOptions6(opt_buffer, "dhcp6", options_);
    } else {
        // The last two arguments hold the DHCPv6 Relay message offset and
        // length. Setting them to NULL because we are dealing with the
        // not-relayed message.
        offset = callback_(opt_buffer, "dhcp6", options_, NULL, NULL);
    }

    // If offset is not equal to the size, then something is wrong here. We
    // either parsed past input buffer (bug in our code) or we haven't parsed
    // everything (received trailing garbage or truncated option).
    //
    // Invoking Jon Postel's law here: be conservative in what you send, and be
    // liberal in what you accept. There's no easy way to log something from
    // libdhcp++ library, so we just choose to be silent about remaining
    // bytes. We also need to quell compiler warning about unused offset
    // variable.
    //
    // if (offset != size) {
    //        isc_throw(BadValue, "Received DHCPv6 buffer of size " << size
    //                  << ", were able to parse " << offset << " bytes.");
    // }
    (void)offset;
}

void
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

        // parse the rest as options
        OptionBuffer opt_buffer(&data_[offset], &data_[offset] + bufsize);

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

        /// @todo: implement ERO (Echo Request Option, RFC 4994) here

        if (relay_msg_len >= bufsize) {
            // length of the relay_msg option extends beyond end of the message
            isc_throw(Unexpected, "Relay-msg option is truncated.");
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
    }

    if ( (offset == data_.size()) && (bufsize == 0) ) {
        // message has been parsed completely
        return;
    }

    /// @todo: log here that there are additional unparsed bytes
}

void
Pkt6::addRelayInfo(const RelayInfo& relay) {
    if (relay_info_.size() > 32) {
        isc_throw(BadValue, "Massage cannot be encapsulated more than 32 times");
    }

    /// @todo: Implement type checks here (e.g. we could receive relay-forw in relay-repl)
    relay_info_.push_back(relay);
}

void
Pkt6::unpackTCP() {
    isc_throw(Unexpected, "DHCPv6 over TCP (bulk leasequery and failover) "
              "not implemented yet.");
}

HWAddrPtr
Pkt6::getMACFromDUID() {
    HWAddrPtr mac;
    OptionPtr opt_duid = getOption(D6O_CLIENTID);
    if (!opt_duid) {
        return (mac);
    }

    uint8_t hlen = opt_duid->getData().size();
    vector<uint8_t> hw_addr(hlen, 0);
    std::vector<unsigned char> duid_data = opt_duid->getData();

    // Read the first two bytes. That duid type.
    uint16_t duid_type = util::readUint16(&duid_data[0], duid_data.size());

    switch (duid_type) {
    case DUID::DUID_LL:
    {
        // 2 bytes of duid type, 2 bytes of hardware type and at least
        // 1 byte of actual identification
        if (duid_data.size() >= 5) {
            uint16_t hwtype = util::readUint16(&duid_data[2],
                                               duid_data.size() - 2);
            mac.reset(new HWAddr(&duid_data[4], duid_data.size() - 4, hwtype));
        }
        break;
    }
    case DUID::DUID_LLT:
    {
        // 2 bytes of duid type, 2 bytes of hardware, 4 bytes for timestamp,
        // and at least 1 byte of actual identification
        if (duid_data.size() >= 9) {
            uint16_t hwtype = util::readUint16(&duid_data[2],
                                               duid_data.size() - 2);
            mac.reset(new HWAddr(&duid_data[8], duid_data.size() - 8, hwtype));
        }
        break;
    }
    default:
        break;
    }

    if (mac) {
        mac->source_ = HWAddr::HWADDR_SOURCE_DUID;
    }

    return (mac);
}

std::string
Pkt6::makeLabel(const DuidPtr duid, const uint32_t transid,
                const HWAddrPtr& hwaddr) {
    // Create label with DUID and HW address.
    std::stringstream label;
    label << makeLabel(duid, hwaddr);

    // Append transaction id.
    label << ", tid=0x" << std::hex << transid << std::dec;

    return (label.str());
}

std::string
Pkt6::makeLabel(const DuidPtr duid, const HWAddrPtr& hwaddr) {
    std::stringstream label;
    // DUID should be present at all times, so explicitly inform when
    // it is no present (no info).
    label << "duid=[" << (duid ? duid->toText() : "no info")
          << "]";

    // HW address is typically not carried in the DHCPv6 mmessages
    // and can be extracted using various, but not fully reliable,
    // techniques. If it is not present, don't print anything.
    if (hwaddr) {
        label << ", [" << hwaddr->toText() << "]";
    }

    return (label.str());
}

std::string
Pkt6::getLabel() const {
    /// @todo Do not print HW address as it is unclear how it should
    /// be retrieved if there is no access to user configuration which
    /// specifies the order of various techniques to be used to retrieve
    /// it.
    return (makeLabel(getClientId(), getTransid(), HWAddrPtr()));}

std::string
Pkt6::toText() const {
    stringstream tmp;
    tmp << "localAddr=[" << local_addr_ << "]:" << local_port_
        << " remoteAddr=[" << remote_addr_
        << "]:" << remote_port_ << endl;
    tmp << "msgtype=" << static_cast<int>(msg_type_) << ", transid=0x" <<
        hex << transid_ << dec << endl;
    for (isc::dhcp::OptionCollection::const_iterator opt=options_.begin();
         opt != options_.end();
         ++opt) {
        tmp << opt->second->toText() << std::endl;
    }
    return tmp.str();
}

DuidPtr
Pkt6::getClientId() const {
    OptionPtr opt_duid = getOption(D6O_CLIENTID);
    try {
        // This will throw if the DUID length is larger than 128 bytes
        // or is too short.
        return (opt_duid ? DuidPtr(new DUID(opt_duid->getData())) : DuidPtr());
    } catch (...) {
        // Do nothing. This method is used only by getLabel(), which is
        // used for logging purposes. We should not throw, but rather
        // report no DUID. We should not log anything, as we're in the
        // process of logging something for this packet. So the only
        // choice left is to return an empty pointer.
    }
    return (DuidPtr());
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

const char*
Pkt6::getName(const uint8_t type) {
    static const char* ADVERTISE = "ADVERTISE";
    static const char* CONFIRM = "CONFIRM";
    static const char* DECLINE = "DECLINE";
    static const char* INFORMATION_REQUEST = "INFORMATION_REQUEST";
    static const char* LEASEQUERY = "LEASEQUERY";
    static const char* LEASEQUERY_REPLY = "LEASEQUERY_REPLY";
    static const char* REBIND = "REBIND";
    static const char* RECONFIGURE = "RECONFIGURE";
    static const char* RELAY_FORW = "RELAY_FORWARD";
    static const char* RELAY_REPL = "RELAY_REPLY";
    static const char* RELEASE = "RELEASE";
    static const char* RENEW = "RENEW";
    static const char* REPLY = "REPLY";
    static const char* REQUEST = "REQUEST";
    static const char* SOLICIT = "SOLICIT";
    static const char* DHCPV4_QUERY = "DHCPV4_QUERY";
    static const char* DHCPV4_RESPONSE = "DHCPV4_RESPONSE";
    static const char* UNKNOWN = "UNKNOWN";

    switch (type) {
    case DHCPV6_ADVERTISE:
        return (ADVERTISE);

    case DHCPV6_CONFIRM:
        return (CONFIRM);

    case DHCPV6_DECLINE:
        return (DECLINE);

    case DHCPV6_INFORMATION_REQUEST:
        return (INFORMATION_REQUEST);

    case DHCPV6_LEASEQUERY:
        return (LEASEQUERY);

    case DHCPV6_LEASEQUERY_REPLY:
        return (LEASEQUERY_REPLY);

    case DHCPV6_REBIND:
        return (REBIND);

    case DHCPV6_RECONFIGURE:
        return (RECONFIGURE);

    case DHCPV6_RELAY_FORW:
        return (RELAY_FORW);

    case DHCPV6_RELAY_REPL:
        return (RELAY_REPL);

    case DHCPV6_RELEASE:
        return (RELEASE);

    case DHCPV6_RENEW:
        return (RENEW);

    case DHCPV6_REPLY:
        return (REPLY);

    case DHCPV6_REQUEST:
        return (REQUEST);

    case DHCPV6_SOLICIT:
        return (SOLICIT);

    case DHCPV6_DHCPV4_QUERY:
        return (DHCPV4_QUERY);

    case DHCPV6_DHCPV4_RESPONSE:
        return (DHCPV4_RESPONSE);

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
    for (size_t i = 0; i < question->relay_info_.size(); ++i) {
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

HWAddrPtr
Pkt6::getMACFromSrcLinkLocalAddr() {
    if (relay_info_.empty()) {
        // This is a direct message, use source address
        return (getMACFromIPv6(remote_addr_));
    }

    // This is a relayed message, get the peer-addr from the first relay-forw
    return (getMACFromIPv6(relay_info_[relay_info_.size() - 1].peeraddr_));
}

HWAddrPtr
Pkt6::getMACFromIPv6RelayOpt() {
    HWAddrPtr mac;

    // This is not a direct message
    if (!relay_info_.empty()) {
        // RFC6969 Section 6: Look for the client_linklayer_addr option on the
        // relay agent closest to the client
        OptionPtr opt = getAnyRelayOption(D6O_CLIENT_LINKLAYER_ADDR,
                                          RELAY_GET_FIRST);
        if (opt) {
            const OptionBuffer data = opt->getData();
            // This client link address option is supposed to be
            // 2 bytes of link-layer type followed by link-layer address.
            if (data.size() >= 3) {
                // +2, -2 means to skip the initial 2 bytes which are
                // hwaddress type
                mac.reset(new HWAddr(&data[0] + 2, data.size() - 2,
                          opt->getUint16()));

                mac->source_ = HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION;
            }
        }
    }

    return mac;
}

HWAddrPtr
Pkt6::getMACFromDocsisModem() {
    HWAddrPtr mac;
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<
        OptionVendor>(getOption(D6O_VENDOR_OPTS));

    // Check if this is indeed DOCSIS3 environment
    if (vendor && vendor->getVendorId() == VENDOR_ID_CABLE_LABS) {
        // If it is, try to get device-id option
        OptionPtr device_id = vendor->getOption(DOCSIS3_V6_DEVICE_ID);
        if (device_id) {
            // If the option contains any data, use it as MAC address
            if (!device_id->getData().empty()) {
                mac.reset(new HWAddr(device_id->getData(), HTYPE_DOCSIS));
                mac->source_ = HWAddr::HWADDR_SOURCE_DOCSIS_MODEM;
            }
        }
    }

    return mac;
}

HWAddrPtr
Pkt6::getMACFromDocsisCMTS() {
    HWAddrPtr mac;

    // If the message passed through a CMTS, there'll
    // CMTS-specific options in it.
    if (!relay_info_.empty()) {
        OptionVendorPtr vendor = boost::dynamic_pointer_cast<
            OptionVendor>(getAnyRelayOption(D6O_VENDOR_OPTS,
                                            RELAY_SEARCH_FROM_CLIENT));

        // Check if this is indeed DOCSIS3 environment
        if (vendor && vendor->getVendorId() == VENDOR_ID_CABLE_LABS) {
            // Try to get cable modem mac
            OptionPtr cm_mac = vendor->getOption(DOCSIS3_V6_CMTS_CM_MAC);

            // If the option contains any data, use it as MAC address
            if (cm_mac && !cm_mac->getData().empty()) {
                mac.reset(new HWAddr(cm_mac->getData(), HTYPE_DOCSIS));
                mac->source_ = HWAddr::HWADDR_SOURCE_DOCSIS_CMTS;
            }
        }
    }

    return (mac);
}

HWAddrPtr
Pkt6::getMACFromRemoteIdRelayOption() {
    HWAddrPtr mac;

    // If this is relayed message
    if (!relay_info_.empty()) {
        // Get remote-id option from a relay agent closest to the client
        OptionPtr opt = getAnyRelayOption(D6O_REMOTE_ID, RELAY_GET_FIRST);
        if (opt) {
            const OptionBuffer data = opt->getData();
            // This remote-id option is supposed to be 4 bytes of
            // of enterprise-number followed by remote-id.
            if (data.size() >= 5) {
                // Let's get the interface this packet was received on.
                // We need it to get the hardware type.
                IfacePtr iface = IfaceMgr::instance().getIface(iface_);
                uint16_t hwtype = 0; // not specified

                // If we get the interface HW type, great! If not,
                // let's not panic.
                if (iface) {
                    hwtype = iface->getHWType();
                }

                // Skip the initial 4 bytes which are enterprise-number.
                mac.reset(new HWAddr(&data[0] + 4, data.size() - 4, hwtype));
                mac->source_ = HWAddr::HWADDR_SOURCE_REMOTE_ID;
            }
        }
    }

    return (mac);
}

} // end of isc::dhcp namespace
} // end of isc namespace
