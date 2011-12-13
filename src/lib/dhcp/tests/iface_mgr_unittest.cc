// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <fstream>
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <asiolink/io_address.h>
#include <dhcp/pkt6.h>
#include <dhcp/iface_mgr.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

// name of loopback interface detection
char LOOPBACK[32] = "lo";

namespace {
const char* const INTERFACE_FILE = TEST_DATA_BUILDDIR "/interfaces.txt";

class NakedIfaceMgr: public IfaceMgr {
    // "naked" Interface Manager, exposes internal fields
public:
    NakedIfaceMgr() { }
    IfaceLst & getIfacesLst() { return ifaces_; }
    void setSendSock(int sock) { sendsock_ = sock; }
    void setRecvSock(int sock) { recvsock_ = sock; }

    int openSocket(const std::string& ifname,
                   const isc::asiolink::IOAddress& addr,
                   int port) {
        return IfaceMgr::openSocket(ifname, addr, port);
    }

};

// dummy class for now, but this will be expanded when needed
class IfaceMgrTest : public ::testing::Test {
public:
    IfaceMgrTest() {
    }
};

// We need some known interface to work reliably. Loopback interface
// is named lo on Linux and lo0 on BSD boxes. We need to find out
// which is available. This is not a real test, but rather a workaround
// that will go away when interface detection is implemented.

// NOTE: At this stage of development, write access to current directory
// during running tests is required.
TEST_F(IfaceMgrTest, loDetect) {

    // poor man's interface detection
    // it will go away as soon as proper interface detection
    // is implemented
    if (if_nametoindex("lo")>0) {
        cout << "This is Linux, using lo as loopback." << endl;
        sprintf(LOOPBACK, "lo");
    } else if (if_nametoindex("lo0")>0) {
        cout << "This is BSD, using lo0 as loopback." << endl;
        sprintf(LOOPBACK, "lo0");
    } else {
        cout << "Failed to detect loopback interface. Neither "
             << "lo or lo0 worked. I give up." << endl;
        ASSERT_TRUE(false);
    }
}

// uncomment this test to create packet writer. It will
// write incoming DHCPv6 packets as C arrays. That is useful
// for generating test sequences based on actual traffic
//
// TODO: this potentially should be moved to a separate tool
//

#if 0
TEST_F(IfaceMgrTest, dhcp6Sniffer) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    unlink("interfaces.txt");

    ofstream interfaces("interfaces.txt", ios::ate);
    interfaces << "eth0 fe80::21e:8cff:fe9b:7349";
    interfaces.close();

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    Pkt6 * pkt = 0;
    int cnt = 0;
    cout << "---8X-----------------------------------------" << endl;
    while (true) {
        pkt = ifacemgr->receive();

        cout << "// Received " << pkt->data_len_ << " bytes packet:" << endl;
        cout << "Pkt6 *capture" << cnt++ << "() {" << endl;
        cout << "    Pkt6* pkt;" << endl;
        cout << "    pkt = new Pkt6(" << pkt->data_len_ << ");" << endl;
        cout << "    pkt->remote_port_ = " << pkt-> remote_port_ << ";" << endl;
        cout << "    pkt->remote_addr_ = IOAddress(\""
             << pkt->remote_addr_.toText() << "\");" << endl;
        cout << "    pkt->local_port_ = " << pkt-> local_port_ << ";" << endl;
        cout << "    pkt->local_addr_ = IOAddress(\""
             << pkt->local_addr_.toText() << "\");" << endl;
        cout << "    pkt->ifindex_ = " << pkt->ifindex_ << ";" << endl;
        cout << "    pkt->iface_ = \"" << pkt->iface_ << "\";" << endl;

        // TODO it is better to declare an array and then memcpy it to
        // packet.
        for (int i=0; i< pkt->data_len_; i++) {
            cout << "    pkt->data_[" << i << "]="
                 << (int)(unsigned char)pkt->data_[i] << "; ";
            if (!(i%4))
                cout << endl;
        }
        cout << endl;
        cout << "    return (pkt);" << endl;
        cout << "}" << endl << endl;

        delete pkt;
    }
    cout << "---8X-----------------------------------------" << endl;

    // never happens. Infinite loop is infinite
    delete pkt;
    delete ifacemgr;
}
#endif

TEST_F(IfaceMgrTest, basic) {
    // checks that IfaceManager can be instantiated

    IfaceMgr & ifacemgr = IfaceMgr::instance();
    ASSERT_TRUE(&ifacemgr != 0);
}

TEST_F(IfaceMgrTest, ifaceClass) {
    // basic tests for Iface inner class

    IfaceMgr::Iface * iface = new IfaceMgr::Iface("eth5", 7);

    EXPECT_STREQ("eth5/7", iface->getFullName().c_str());

    delete iface;

}

// TODO: Implement getPlainMac() test as soon as interface detection
// is implemented.
TEST_F(IfaceMgrTest, getIface) {

    cout << "Interface checks. Please ignore socket binding errors." << endl;
    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    // interface name, ifindex
    IfaceMgr::Iface iface1("lo1", 1);
    IfaceMgr::Iface iface2("eth5", 2);
    IfaceMgr::Iface iface3("en3", 5);
    IfaceMgr::Iface iface4("e1000g0", 3);

    // note: real interfaces may be detected as well
    ifacemgr->getIfacesLst().push_back(iface1);
    ifacemgr->getIfacesLst().push_back(iface2);
    ifacemgr->getIfacesLst().push_back(iface3);
    ifacemgr->getIfacesLst().push_back(iface4);

    cout << "There are " << ifacemgr->getIfacesLst().size()
         << " interfaces." << endl;
    for (IfaceMgr::IfaceLst::iterator iface=ifacemgr->getIfacesLst().begin();
         iface != ifacemgr->getIfacesLst().end();
         ++iface) {
        cout << "  " << iface->name_ << "/" << iface->ifindex_ << endl;
    }


    // check that interface can be retrieved by ifindex
    IfaceMgr::Iface * tmp = ifacemgr->getIface(5);
    // ASSERT_NE(NULL, tmp); is not supported. hmmmm.
    ASSERT_TRUE( tmp != NULL );

    EXPECT_STREQ( "en3", tmp->name_.c_str() );
    EXPECT_EQ(5, tmp->ifindex_);

    // check that interface can be retrieved by name
    tmp = ifacemgr->getIface("lo1");
    ASSERT_TRUE( tmp != NULL );

    EXPECT_STREQ( "lo1", tmp->name_.c_str() );
    EXPECT_EQ(1, tmp->ifindex_);

    // check that non-existing interfaces are not returned
    EXPECT_EQ(static_cast<void*>(NULL), ifacemgr->getIface("wifi0") );

    delete ifacemgr;
}

#if !defined(OS_LINUX)
TEST_F(IfaceMgrTest, detectIfaces_stub) {

    // test detects that interfaces can be detected
    // there is no code for that now, but interfaces are
    // read from file
    fstream fakeifaces(INTERFACE_FILE, ios::out|ios::trunc);
    fakeifaces << "eth0 fe80::1234";
    fakeifaces.close();

    // this is not usable on systems that don't have eth0
    // interfaces. Nevertheless, this fake interface should
    // be on list, but if_nametoindex() will fail.

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    ASSERT_TRUE( ifacemgr->getIface("eth0") != NULL );

    IfaceMgr::Iface * eth0 = ifacemgr->getIface("eth0");

    // there should be one address
    EXPECT_EQ(1, eth0->addrs_.size());

    IOAddress * addr = &(*eth0->addrs_.begin());
    ASSERT_TRUE( addr != NULL );

    EXPECT_STREQ( "fe80::1234", addr->toText().c_str() );

    delete ifacemgr;
}
#endif

// TODO: disabled due to other naming on various systems
// (lo in Linux, lo0 in BSD systems)
// Fix for this is available on 1186 branch, will reenable
// this test once 1186 is merged
TEST_F(IfaceMgrTest, DISABLED_sockets) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    IOAddress loAddr("::1");

    // bind multicast socket to port 10547
    int socket1 = ifacemgr->openSocket(LOOPBACK, loAddr, 10547);
    EXPECT_GT(socket1, 0); // socket > 0

    // bind unicast socket to port 10548
    int socket2 = ifacemgr->openSocket(LOOPBACK, loAddr, 10548);
    EXPECT_GT(socket2, 0);

    // expect success. This address/port is already bound, but
    // we are using SO_REUSEADDR, so we can bind it twice
    int socket3 = ifacemgr->openSocket(LOOPBACK, loAddr, 10547);

    // rebinding succeeds on Linux, fails on BSD
    // TODO: add OS-specific defines here (or modify code to
    // behave the same way on all OSes, but that may not be
    // possible
    // EXPECT_GT(socket3, 0); // socket > 0

    // we now have 3 sockets open at the same time. Looks good.

    close(socket1);
    close(socket2);
    close(socket3);

    delete ifacemgr;
}

// TODO: disabled due to other naming on various systems
// (lo in Linux, lo0 in BSD systems)
TEST_F(IfaceMgrTest, DISABLED_socketsMcast) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    IOAddress loAddr("::1");
    IOAddress mcastAddr("ff02::1:2");

    // bind multicast socket to port 10547
    int socket1 = ifacemgr->openSocket(LOOPBACK, mcastAddr, 10547);
    EXPECT_GT(socket1, 0); // socket > 0

    // expect success. This address/port is already bound, but
    // we are using SO_REUSEADDR, so we can bind it twice
    int socket2 = ifacemgr->openSocket(LOOPBACK, mcastAddr, 10547);
    EXPECT_GT(socket2, 0);

    // there's no good way to test negative case here.
    // we would need non-multicast interface. We will be able
    // to iterate thru available interfaces and check if there
    // are interfaces without multicast-capable flag.

    close(socket1);
    close(socket2);

    delete ifacemgr;
}

// TODO: disabled due to other naming on various systems
// (lo in Linux, lo0 in BSD systems)
// Fix for this is available on 1186 branch, will reenable
// this test once 1186 is merged
TEST_F(IfaceMgrTest, DISABLED_sendReceive) {
    // testing socket operation in a portable way is tricky
    // without interface detection implemented

    fstream fakeifaces(INTERFACE_FILE, ios::out|ios::trunc);
    fakeifaces << LOOPBACK << " ::1";
    fakeifaces.close();

    NakedIfaceMgr * ifacemgr = new NakedIfaceMgr();

    // let's assume that every supported OS have lo interface
    IOAddress loAddr("::1");
    int socket1 = ifacemgr->openSocket(LOOPBACK, loAddr, 10547);
    int socket2 = ifacemgr->openSocket(LOOPBACK, loAddr, 10546);

    ifacemgr->setSendSock(socket2);
    ifacemgr->setRecvSock(socket1);

    boost::shared_ptr<Pkt6> sendPkt(new Pkt6(128) );

    // prepare dummy payload
    for (int i=0;i<128; i++) {
        sendPkt->data_[i] = i;
    }

    sendPkt->remote_port_ = 10547;
    sendPkt->remote_addr_ = IOAddress("::1");
    sendPkt->ifindex_ = 1;
    sendPkt->iface_ = LOOPBACK;

    boost::shared_ptr<Pkt6> rcvPkt;

    EXPECT_EQ(true, ifacemgr->send(sendPkt));

    rcvPkt = ifacemgr->receive();

    ASSERT_TRUE( rcvPkt ); // received our own packet

    // let's check that we received what was sent
    EXPECT_EQ(sendPkt->data_len_, rcvPkt->data_len_);
    EXPECT_EQ(0, memcmp(&sendPkt->data_[0], &rcvPkt->data_[0],
                        rcvPkt->data_len_) );

    EXPECT_EQ(sendPkt->remote_addr_.toText(), rcvPkt->remote_addr_.toText());
    EXPECT_EQ(rcvPkt->remote_port_, 10546);

    delete ifacemgr;
}

/// @brief parses text representation of MAC address
///
/// This function parses text representation of a MAC address and stores
/// it in binary format. Text format is expecte to be separate with
/// semicolons, e.g. f4:6d:04:96:58:f2
///
/// TODO: IfaceMgr::Iface::mac_ uses uint8_t* type, should be vector<uint8_t>
///
/// @param textMac string with MAC address to parse
/// @param mac pointer to output buffer
/// @param macLen length of output buffer
///
/// @return number of bytes filled in output buffer
size_t parse_mac(const std::string& textMac, uint8_t* mac, size_t macLen) {
    stringstream tmp(textMac);
    tmp.flags(ios::hex);
    int i = 0;
    uint8_t octet = 0; // output octet
    uint8_t byte;  // parsed charater from text representation
    while (!tmp.eof()) {

        tmp >> byte; // hex value
        if (byte == ':') {
            mac[i++] = octet;

            if (i == macLen) {
                // parsing aborted. We hit output buffer size
                return(i);
            }
            octet = 0;
            continue;
        }
        if (isalpha(byte)) {
            byte = toupper(byte) - 'A' + 10;
        } else if (isdigit(byte)) {
            byte -= '0';
        } else {
            // parse error. Let's return what we were able to parse so far
            break;
        }
        octet <<= 4;
        octet += byte;
    }
    mac[i++] = octet;

    return (i);
}

#if defined(OS_LINUX)

/// @brief Parses 'ifconfig -a' output and creates list of interfaces
///
/// This method tries to parse ifconfig output. Note that there are some
/// oddities in recent versions of ifconfig, like putting extra spaces
/// after MAC address, inconsistent naming and spacing between inet and inet6.
/// This is an attempt to find a balance between tight parsing of every piece
/// of text that ifconfig prints and robustness to handle slight differences
/// in ifconfig output.
///
/// @param textFile name of a text file that holds output of ifconfig -a
/// @param ifaces empty list of interfaces to be filled
void parse_ifconfig(const std::string textFile, IfaceMgr::IfaceLst& ifaces) {
    fstream f(textFile.c_str());

    bool first_line = true;
    IfaceMgr::IfaceLst::iterator iface;
    while (!f.eof()) {
        string line;
        getline(f, line);

        // interfaces are separated by empty line
        if (line.length() == 0) {
            first_line = true;
            continue;
        }

        // uncomment this for ifconfig output debug
        // cout << "line[" << line << "]" << endl;

        // this is first line of a new interface
        if (first_line) {
            first_line = false;

            size_t offset;
            offset = line.find_first_of(" ");
            if (offset == string::npos) {
                isc_throw(BadValue, "Malformed output of ifconfig");
            }
            string name = line.substr(0, offset);

            // sadly, ifconfig does not return ifindex
            ifaces.push_back(IfaceMgr::Iface(name, 0));
            iface = ifaces.end();
            --iface; // points to the last element

            offset = line.find(string("HWaddr"));

            string mac = "";
            if (offset != string::npos) { // some interfaces don't have MAC (e.g. lo)
                offset += 7;
                mac = line.substr(offset, string::npos);
                mac = mac.substr(0, mac.find_first_of(" "));

                iface->mac_len_ = parse_mac(mac, iface->mac_, IfaceMgr::MAX_MAC_LEN);
            }
        }

        if (line.find("inet6") != string::npos) {
            // IPv6 address
            string addr = line.substr(line.find("inet6")+12, string::npos);
            addr = addr.substr(0, addr.find("/"));
            IOAddress a(addr);
            iface->addrs_.push_back(a);
        } else if(line.find("inet") != string::npos) {
            // IPv4 address
            string addr = line.substr(line.find("inet")+10, string::npos);
            addr = addr.substr(0, addr.find_first_of(" "));
            IOAddress a(addr);
            iface->addrs_.push_back(a);
        } else if(line.find("Metric")) {
            // flags
            if (line.find("UP") != string::npos) {
                iface->flag_up_ = true;
            }
            if (line.find("LOOPBACK") != string::npos) {
                iface->flag_loopback_ = true;
            }
            if (line.find("RUNNING") != string::npos) {
                iface->flag_running_ = true;
            }
            if (line.find("BROADCAST") != string::npos) {
                iface->flag_broadcast_ = true;
            }
            if (line.find("MULTICAST") != string::npos) {
                iface->flag_multicast_ = true;
            }
        }
    }
}


// This test compares implemented detection routines to output of "ifconfig -a" command.
// It is far from perfect, but it is able to verify that interface names, flags,
// MAC address, IPv4 and IPv6 addresses are detected properly. Interface list completeness
// (check that each interface is reported, i.e. no missing or extra interfaces) and
// address completeness is verified.
//
// Things that are not tested: 
// - ifindex (ifconfig does not print it out)
// - address scopes and lifetimes (we don't need it, so it is not implemented in IfaceMgr)
TEST_F(IfaceMgrTest, detectIfaces_linux) {

    NakedIfaceMgr* ifacemgr = new NakedIfaceMgr();
    IfaceMgr::IfaceLst& detectedIfaces = ifacemgr->getIfacesLst();

    const std::string textFile = "ifconfig.txt";

    unlink(textFile.c_str());
    int result = system( ("/sbin/ifconfig -a > " + textFile).c_str());

    ASSERT_EQ(0, result);

    // list of interfaces parsed from ifconfig
    IfaceMgr::IfaceLst parsedIfaces;

    EXPECT_NO_THROW(
        parse_ifconfig(textFile, parsedIfaces);
    );
    unlink(textFile.c_str());

    cout << "------Parsed interfaces---" << endl;
    for (IfaceMgr::IfaceLst::iterator i = parsedIfaces.begin();
         i != parsedIfaces.end(); ++i) {
        cout << i->name_ << ": ifindex=" << i->ifindex_ << ", mac=" << i->getPlainMac();
        cout << ", flags:";
        if (i->flag_up_) {
            cout << " UP";
        }
        if (i->flag_running_) {
            cout << " RUNNING";
        }
        if (i->flag_multicast_) {
            cout << " MULTICAST";
        }
        if (i->flag_broadcast_) {
            cout << " BROADCAST";
        }
        cout << ", addrs:";
        for (IfaceMgr::Addr6Lst::iterator a= i->addrs_.begin();
             a != i->addrs_.end(); ++a) {
            cout << a->toText() << " ";
        }
        cout << endl;
    }

    // Ok, now we have 2 lists of interfaces. Need to compare them
    ASSERT_EQ(detectedIfaces.size(), parsedIfaces.size());

    // TODO: This could could probably be written simple with find()
    for (IfaceMgr::IfaceLst::iterator detected = detectedIfaces.begin();
         detected != detectedIfaces.end(); ++detected) {
        // let's find out if this interface is

        bool found = false;
        for (IfaceMgr::IfaceLst::iterator i = parsedIfaces.begin();
             i != parsedIfaces.end(); ++i) {
            if (detected->name_ != i->name_) {
                continue;
            }
            found = true;

            cout << "Checking interface " << detected->name_ << endl;

            // start with checking flags
            EXPECT_EQ(detected->flag_loopback_, i->flag_loopback_);
            EXPECT_EQ(detected->flag_up_, i->flag_up_);
            EXPECT_EQ(detected->flag_running_, i->flag_running_);
            EXPECT_EQ(detected->flag_multicast_, i->flag_multicast_);
            EXPECT_EQ(detected->flag_broadcast_, i->flag_broadcast_);

            // skip MAC comparison for loopback as netlink returns MAC
            // 00:00:00:00:00:00 for lo
            if (!detected->flag_loopback_) {
                ASSERT_EQ(detected->mac_len_, i->mac_len_);
                EXPECT_EQ(0, memcmp(detected->mac_, i->mac_, i->mac_len_));
            }

            EXPECT_EQ(detected->addrs_.size(), i->addrs_.size());

            // now compare addresses
            for (IfaceMgr::Addr6Lst::iterator addr = detected->addrs_.begin();
                 addr != detected->addrs_.end(); ++addr) {
                bool addr_found = false;

                for (IfaceMgr::Addr6Lst::iterator a = i->addrs_.begin();
                     a != i->addrs_.end(); ++a) {
                    if (*addr != *a) {
                        continue;
                    }
                    addr_found = true;
                }
                if (!addr_found) {
                    cout << "ifconfig does not seem to report " << addr->toText()
                         << " address on " << detected->getFullName() << " interface." << endl;
                    FAIL();
                }
                cout << "Address " << addr->toText() << " on iterface " << detected->getFullName()
                     << " matched with 'ifconfig -a' output." << endl;
            }

        }


    }




    delete ifacemgr;
}
#endif

}
