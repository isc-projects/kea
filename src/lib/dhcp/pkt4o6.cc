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

#include <dhcp/pkt4o6.h>
#include <dhcp/dhcp4.h>
#include <asiolink/io_address.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

using namespace std;

namespace isc {
namespace dhcp {

Pkt4o6Ptr Pkt4o6::fromPkt6(const Pkt6Ptr& pkt6) {
    if (pkt6->getType() != DHCPV4_QUERY && 
        pkt6->getType() != DHCPV4_RESPONSE) {
        isc_throw(Pkt4o6ConstructError,
                  "The DHCPv6 message is not DHCPV4_QUERY or DHCPV4_RESPONSE");
    }
    OptionPtr opt = pkt6->getOption(OPTION_DHCPV4_MSG);
    Pkt4o6Ptr pkt4o6;
    if (opt) {
        const OptionBuffer& data = opt->getData();
        pkt4o6 = Pkt4o6Ptr(new Pkt4o6(data.data(), data.size()));
        pkt4o6->setFlags(pkt6->getTransid());
        pkt4o6->setPkt6RemoteAddr(pkt6->getRemoteAddr());
        pkt4o6->setPkt6LocalAddr(pkt6->getLocalAddr());
        pkt4o6->setPkt6Index(pkt6->getIndex());
        pkt4o6->setPkt6Iface(pkt6->getIface());
    } else {
        isc_throw(Pkt4o6ConstructError,
                 "The DHCPv6 message doesn't contain a DHCPv4 Message Option");
    }
   return pkt4o6;
}

Pkt6Ptr Pkt4o6::toPkt6() {
    unpack();
    Pkt6Ptr pkt6 = Pkt6Ptr(new Pkt6(DHCPV4_QUERY, 0));
    pkt6->setRemoteAddr(getPkt6RemoteAddr());
    pkt6->setLocalAddr(getPkt6LocalAddr());
    pkt6->setIndex(getPkt6Index());
    pkt6->setIface(getPkt6Iface());
    
//    appendRequestedOptions(query, reply);//TODO: should we remove this?
        
    OptionPtr option(new Option(Option::V6,
                                OPTION_DHCPV4_MSG,
                                getDHCPv4MsgOption()));
    pkt6->addOption(option);

    //Add relay info
//    if (!query->relay_info_.empty()) {
//        reply->copyRelayInfo(query);
//    }
    return pkt6;
}

void Pkt4o6::pack() {
//    Pkt4::pack();
    Pkt4::repack();
    
    using boost::property_tree::ptree;
    ptree pt;

    pt.put("RemoteAddr", getPkt6RemoteAddr().toText());
    pt.put("LocalAddr", getPkt6LocalAddr().toText());
//    pt.put("RemotePort", pkt6_->getRemotePort());
//    pt.put("LocalPort", pkt6_->getLocalPort());
    pt.put("Index", getPkt6Index());
    pt.put("Iface", getPkt6Iface());
    
    pt.put("Flags", getFlags());
    std::stringstream sout;
    write_json(sout, pt);

    buffer_ancillary_ = sout.str();
}

void Pkt4o6::unpack() {
    Pkt4::unpack();
    
    using boost::property_tree::ptree;
    std::istringstream sin(buffer_ancillary_);
    ptree pt;
    read_json(sin, pt);

    try {
        setPkt6RemoteAddr(isc::asiolink::IOAddress(pt.get<std::string>("RemoteAddr")));
        setPkt6LocalAddr(isc::asiolink::IOAddress(pt.get<std::string>("LocalAddr")));
//        pkt6_->setRemotePort(pt.get<uint16_t>("RemotePort"));
//        pkt6_->setLocalPort(pt.get<uint16_t>("LocalPort"));
        setPkt6Index(pt.get<uint32_t>("Index"));
        setPkt6Iface(pt.get<std::string>("Iface"));
        setFlags(pt.get<uint32_t>("Flags"));
        setIface(getPkt6Iface());//Use Pkt6's Iface to find a subnet
    } catch (const std::exception& ex) {
        //TODO: logging
    }
    setPkt4LocalAddr();
}

/*
          
Pkt4o6::Pkt4o6(const uint8_t* data4, size_t len4,
               const uint8_t* data6, size_t len6)
       :pkt4_(new Pkt4(data4, len4)),
        pkt6_(new Pkt6(data6, len6))
{
    pkt6_->repack();//call repack() to generate outputBuffer
    pkt4_->repack();//call repack() to generate outputBuffer
}

Pkt4o6::Pkt4o6(const Pkt6Ptr& pkt6) {
    if (pkt6->getType() != DHCPV4_QUERY && 
        pkt6->getType() != DHCPV4_RESPONSE) {
        isc_throw(Pkt4o6ConstructError,
                  "The DHCPv6 packet is not DHCPV4_QUERY or DHCPV4_RESPONSE");
    }
    OptionPtr opt = pkt6->getOption(OPTION_DHCPV4_MSG);
    if (opt) {
        const OptionBuffer& data = opt->getData();
        pkt4_ = Pkt4Ptr(new Pkt4(data.data(), data.size()));
    } else {
        isc_throw(Pkt4o6ConstructError,
                 "The DHCPv6 message doesn't contain a DHCPv4 Message Option");
    }
    
    pkt6_ = pkt6;
    pkt6_->repack();//call repack() to generate outputBuffer
    pkt4_->repack();//call repack() to generate outputBuffer
}

Pkt4o6::Pkt4o6(const Pkt4o6Ptr& pkt4o6, const Pkt4Ptr& pkt4) {
    pkt4_ = pkt4;
    pkt6_ = pkt4o6->getPkt6();
}
*/
void
Pkt4o6::setPkt4LocalAddr() {
    if (getFlags() & 0x800000) {//U flag is 1, pkt4 was sent unicast
        setLocalAddr(isc::asiolink::IOAddress("8.8.8.8"));
    } else {//u flag is 0, pkt4 was sent to broadcast
        setLocalAddr(isc::asiolink::IOAddress("255.255.255.255"));
    }
}
/*
std::string
Pkt4o6::getJsonAttribute() {
    using boost::property_tree::ptree;
    ptree pt;
    pt.put("RemoteAddr", pkt6_->getRemoteAddr().toText());
    pt.put("LocalAddr", pkt6_->getLocalAddr().toText());
    pt.put("RemotePort", pkt6_->getRemotePort());
    pt.put("LocalPort", pkt6_->getLocalPort());
    pt.put("Index", pkt6_->getIndex());
    pt.put("Iface", pkt6_->getIface());
    std::stringstream sout;
    write_json(sout, pt);
    return (sout.str());
}

void
Pkt4o6::setJsonAttribute(std::string json) {
    using boost::property_tree::ptree;
    std::istringstream sin(json);
    ptree pt;
    read_json(sin, pt);
    try {
        pkt6_->setRemoteAddr(isc::asiolink::IOAddress(pt.get<std::string>("RemoteAddr")));
        pkt6_->setLocalAddr(isc::asiolink::IOAddress(pt.get<std::string>("LocalAddr")));
        pkt6_->setRemotePort(pt.get<uint16_t>("RemotePort"));
        pkt6_->setLocalPort(pt.get<uint16_t>("LocalPort"));
        pkt6_->setIndex(pt.get<uint32_t>("Index"));
        pkt6_->setIface(pt.get<std::string>("Iface"));
        
        pkt4_->setIface(pkt6_->getIface());
    } catch (const std::exception& ex) {
        //TODO: logging
    }
}
*/
OptionBuffer
Pkt4o6::getDHCPv4MsgOption() {
    Pkt4::pack();
    const isc::util::OutputBuffer &buf(Pkt4::getBuffer());
    uint8_t* head = (uint8_t*)buf.getData();
    OptionBuffer ret(head, head + buf.getLength());
    return ret;
}

}
}
