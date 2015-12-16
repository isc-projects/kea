// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// Access to interface information on Linux is via netlink, a socket-based
/// method for transferring information between the kernel and user processes.
///
/// For detailed information about netlink interface, please refer to
/// http://en.wikipedia.org/wiki/Netlink and RFC3549.  Comments in the
/// detectIfaces() method (towards the end of this file) provide an overview
/// on how the netlink interface is used here.
///
/// Note that this interface is very robust and allows many operations:
/// add/get/set/delete links, addresses, routes, queuing, manipulation of
/// traffic classes, manipulation of neighbourhood tables and even the ability
/// to do something with address labels. Getting a list of interfaces with
/// addresses configured on it is just a small subset of all possible actions.

#include <config.h>

#if defined(OS_LINUX)

#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/iface_mgr_error_handler.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcp/pkt_filter_lpf.h>
#include <exceptions/exceptions.h>
#include <util/io/sockaddr_util.h>

#include <boost/array.hpp>
#include <boost/static_assert.hpp>

#include <fcntl.h>
#include <stdint.h>
#include <net/if.h>
#include <linux/rtnetlink.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util::io::internal;

BOOST_STATIC_ASSERT(IFLA_MAX>=IFA_MAX);

namespace {

/// @brief This class offers utility methods for netlink connection.
///
/// See IfaceMgr::detectIfaces() (Linux implementation, towards the end of this
/// file) for example usage.
class Netlink
{
public:

/// @brief Holds pointers to netlink messages.
///
/// netlink (a Linux interface for getting information about network
/// interfaces) uses memory aliasing. Linux kernel returns a memory
/// blob that should be interpreted as series of nlmessages. There
/// are different nlmsg structures defined with varying size. They
/// have one thing common - initial fields are laid out in the same
/// way as nlmsghdr. Therefore different messages can be represented
/// as nlmsghdr with followed variable number of bytes that are
/// message-specific. The only reasonable way to represent this in
/// C++ is to use vector of pointers to nlmsghdr (the common structure).
    typedef vector<nlmsghdr*> NetlinkMessages;

/// @brief Holds pointers to interface or address attributes.
///
/// Note that to get address info, a shorter (IFA_MAX rather than IFLA_MAX)
/// table could be used, but we will use the bigger one anyway to
/// make the code reusable.
///
/// rtattr is a generic structure, similar to sockaddr. It is defined
/// in linux/rtnetlink.h and shown here for documentation purposes only:
///
/// struct rtattr {
///     unsigned short<>rta_len;
///     unsigned short<>rta_type;
/// };
    typedef boost::array<struct rtattr*, IFLA_MAX + 1> RTattribPtrs;

    Netlink() : fd_(-1), seq_(0), dump_(0) {
        memset(&local_, 0, sizeof(struct sockaddr_nl));
        memset(&peer_, 0, sizeof(struct sockaddr_nl));
    }

    ~Netlink() {
        rtnl_close_socket();
    }


    void rtnl_open_socket();
    void rtnl_send_request(int family, int type);
    void rtnl_store_reply(NetlinkMessages& storage, const nlmsghdr* msg);
    void parse_rtattr(RTattribPtrs& table, rtattr* rta, int len);
    void ipaddrs_get(Iface& iface, NetlinkMessages& addr_info);
    void rtnl_process_reply(NetlinkMessages& info);
    void release_list(NetlinkMessages& messages);
    void rtnl_close_socket();

private:
    int fd_;            // Netlink file descriptor
    sockaddr_nl local_; // Local addresses
    sockaddr_nl peer_;  // Remote address
    uint32_t seq_;      // Counter used for generating unique sequence numbers
    uint32_t dump_;     // Number of expected message response
};

/// @brief defines a size of a sent netlink buffer
const static size_t SNDBUF_SIZE = 32768;

/// @brief defines a size of a received netlink buffer
const static size_t RCVBUF_SIZE = 32768;

/// @brief Opens netlink socket and initializes handle structure.
///
/// @throw isc::Unexpected Thrown if socket configuration fails.
void Netlink::rtnl_open_socket() {

    fd_ = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (fd_ < 0) {
        isc_throw(Unexpected, "Failed to create NETLINK socket.");
    }

    if (fcntl(fd_, F_SETFD, FD_CLOEXEC) < 0) {
        isc_throw(Unexpected, "Failed to set close-on-exec in NETLINK socket.");
    }

    if (setsockopt(fd_, SOL_SOCKET, SO_SNDBUF, &SNDBUF_SIZE, sizeof(SNDBUF_SIZE)) < 0) {
        isc_throw(Unexpected, "Failed to set send buffer in NETLINK socket.");
    }

    if (setsockopt(fd_, SOL_SOCKET, SO_RCVBUF, &RCVBUF_SIZE, sizeof(RCVBUF_SIZE)) < 0) {
        isc_throw(Unexpected, "Failed to set receive buffer in NETLINK socket.");
    }

    local_.nl_family = AF_NETLINK;
    local_.nl_groups = 0;

    if (bind(fd_, convertSockAddr(&local_), sizeof(local_)) < 0) {
        isc_throw(Unexpected, "Failed to bind netlink socket.");
    }

    socklen_t addr_len = sizeof(local_);
    if (getsockname(fd_, convertSockAddr(&local_), &addr_len) < 0) {
        isc_throw(Unexpected, "Getsockname for netlink socket failed.");
    }

    // just 2 sanity checks and we are done
    if ( (addr_len != sizeof(local_)) ||
         (local_.nl_family != AF_NETLINK) ) {
        isc_throw(Unexpected, "getsockname() returned unexpected data for netlink socket.");
    }
}

/// @brief Closes netlink communication socket
void Netlink::rtnl_close_socket() {
    if (fd_ != -1) {
        close(fd_);
    }
    fd_ = -1;
}

/// @brief Sends request over NETLINK socket.
///
/// @param family requested information family.
/// @param type request type (RTM_GETLINK or RTM_GETADDR).
void Netlink::rtnl_send_request(int family, int type) {
    struct Req {
        nlmsghdr netlink_header;
        rtgenmsg generic;
    };
    Req req; // we need this type named for offsetof() used in assert
    struct sockaddr_nl nladdr;

    // do a sanity check. Verify that Req structure is aligned properly
    BOOST_STATIC_ASSERT(sizeof(nlmsghdr) == offsetof(Req, generic));

    memset(&nladdr, 0, sizeof(nladdr));
    nladdr.nl_family = AF_NETLINK;

    // According to netlink(7) manpage, mlmsg_seq must be set to a sequence
    // number and is used to track messages. That is just a value that is
    // opaque to kernel, and user-space code is supposed to use it to match
    // incoming responses to sent requests. That is not really useful as we
    // send a single request and get a single response at a time. However, we
    // obey the man page suggestion and just set this to monotonically
    // increasing numbers.
    seq_++;

    // This will be used to finding correct response (responses
    // sent by kernel are supposed to have the same sequence number
    // as the request we sent).
    dump_ = seq_;

    memset(&req, 0, sizeof(req));
    req.netlink_header.nlmsg_len = sizeof(req);
    req.netlink_header.nlmsg_type = type;
    req.netlink_header.nlmsg_flags = NLM_F_ROOT | NLM_F_MATCH | NLM_F_REQUEST;
    req.netlink_header.nlmsg_pid = 0;
    req.netlink_header.nlmsg_seq = seq_;
    req.generic.rtgen_family = family;

    int status =  sendto(fd_, static_cast<void*>(&req), sizeof(req), 0,
                         static_cast<struct sockaddr*>(static_cast<void*>(&nladdr)),
                         sizeof(nladdr));

    if (status<0) {
        isc_throw(Unexpected, "Failed to send " << sizeof(nladdr)
                  << " bytes over netlink socket.");
    }
}

/// @brief Appends nlmsg to a storage.
///
/// This method copies pointed nlmsg to a newly allocated memory
/// and adds it to storage.
///
/// @param storage A vector that holds pointers to netlink messages. The caller
///        is responsible for freeing the pointed-to messages.
/// @param msg A netlink message to be added.
void Netlink::rtnl_store_reply(NetlinkMessages& storage, const struct nlmsghdr *msg)
{
    // we need to make a copy of this message. We really can't allocate
    // nlmsghdr directly as it is only part of the structure. There are
    // many message types with varying lengths and a common header.
    struct nlmsghdr* copy = reinterpret_cast<struct nlmsghdr*>(new char[msg->nlmsg_len]);
    memcpy(copy, msg, msg->nlmsg_len);

    // push_back copies only pointer content, not the pointed-to object.
    storage.push_back(copy);
}

/// @brief Parses rtattr message.
///
/// Some netlink messages represent address information. Such messages
/// are concatenated collection of rtaddr structures. This function
/// iterates over that list and stores pointers to those messages in
/// flat array (table).
///
/// @param table rtattr Messages will be stored here
/// @param rta Pointer to first rtattr object
/// @param len Length (in bytes) of concatenated rtattr list.
void Netlink::parse_rtattr(RTattribPtrs& table, struct rtattr* rta, int len)
{
    std::fill(table.begin(), table.end(), static_cast<struct rtattr*>(NULL));
    // RTA_OK and RTA_NEXT() are macros defined in linux/rtnetlink.h
    // they are used to handle rtattributes. RTA_OK checks if the structure
    // pointed by rta is reasonable and passes all sanity checks.
    // RTA_NEXT() returns pointer to the next rtattr structure that
    // immediately follows pointed rta structure. See aforementioned
    // header for details.
    while (RTA_OK(rta, len)) {
        if (rta->rta_type < table.size()) {
            table[rta->rta_type] = rta;
        }
        rta = RTA_NEXT(rta,len);
    }
    if (len) {
        isc_throw(Unexpected, "Failed to parse RTATTR in netlink message.");
    }
}

/// @brief Parses addr_info and appends appropriate addresses to Iface object.
///
/// Netlink is a fine, but convoluted interface. It returns a concatenated
/// collection of netlink messages. Some of those messages convey information
/// about addresses. Those messages are in fact appropriate header followed
/// by concatenated lists of rtattr structures that define various pieces
/// of address information.
///
/// @param iface interface representation (addresses will be added here)
/// @param addr_info collection of parsed netlink messages
void Netlink::ipaddrs_get(Iface& iface, NetlinkMessages& addr_info) {
    uint8_t addr[V6ADDRESS_LEN];
    RTattribPtrs rta_tb;

    for (NetlinkMessages::const_iterator msg = addr_info.begin();
         msg != addr_info.end(); ++msg) {
        ifaddrmsg* ifa = static_cast<ifaddrmsg*>(NLMSG_DATA(*msg));

        // These are not the addresses you are looking for
        if (ifa->ifa_index != iface.getIndex()) {
            continue;
        }

        if ((ifa->ifa_family == AF_INET6) || (ifa->ifa_family == AF_INET)) {
            std::fill(rta_tb.begin(), rta_tb.end(), static_cast<rtattr*>(NULL));
            parse_rtattr(rta_tb, IFA_RTA(ifa), (*msg)->nlmsg_len - NLMSG_LENGTH(sizeof(*ifa)));
            if (!rta_tb[IFA_LOCAL]) {
                rta_tb[IFA_LOCAL] = rta_tb[IFA_ADDRESS];
            }
            if (!rta_tb[IFA_ADDRESS]) {
                rta_tb[IFA_ADDRESS] = rta_tb[IFA_LOCAL];
            }

            memcpy(addr, RTA_DATA(rta_tb[IFLA_ADDRESS]),
                   ifa->ifa_family==AF_INET?V4ADDRESS_LEN:V6ADDRESS_LEN);
            IOAddress a = IOAddress::fromBytes(ifa->ifa_family, addr);
            iface.addAddress(a);

            /// TODO: Read lifetimes of configured IPv6 addresses
        }
    }
}

/// @brief Processes reply received over netlink socket.
///
/// This method parses the received buffer (a collection of concatenated
/// netlink messages), copies each received message to newly allocated
/// memory and stores pointers to it in the "info" container.
///
/// @param info received netlink messages will be stored here.  It is the
///        caller's responsibility to release the memory associated with the
///        messages by calling the release_list() method.
void Netlink::rtnl_process_reply(NetlinkMessages& info) {
    sockaddr_nl nladdr;
    iovec iov;
    msghdr msg;
    memset(&msg, 0, sizeof(msghdr));
    msg.msg_name = &nladdr;
    msg.msg_namelen = sizeof(nladdr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    char buf[RCVBUF_SIZE];

    iov.iov_base = buf;
    iov.iov_len = sizeof(buf);
    while (true) {
        int status = recvmsg(fd_, &msg, 0);

        if (status < 0) {
            if (errno == EINTR) {
                continue;
            }
            isc_throw(Unexpected, "Error " << errno
                      << " while processing reply from netlink socket.");
        }

        if (status == 0) {
            isc_throw(Unexpected, "EOF while reading netlink socket.");
        }

        nlmsghdr* header = static_cast<nlmsghdr*>(static_cast<void*>(buf));
        while (NLMSG_OK(header, status)) {

            // Received a message not addressed to our process, or not
            // with a sequence number we are expecting.  Ignore, and
            // look at the next one.
            if (nladdr.nl_pid != 0 ||
                header->nlmsg_pid != local_.nl_pid ||
                header->nlmsg_seq != dump_) {
                header = NLMSG_NEXT(header, status);
                continue;
            }

            if (header->nlmsg_type == NLMSG_DONE) {
                // End of message.
                return;
            }

            if (header->nlmsg_type == NLMSG_ERROR) {
                nlmsgerr* err = static_cast<nlmsgerr*>(NLMSG_DATA(header));
                if (header->nlmsg_len < NLMSG_LENGTH(sizeof(struct nlmsgerr))) {
                    // We are really out of luck here. We can't even say what is
                    // wrong as error message is truncated. D'oh.
                    isc_throw(Unexpected, "Netlink reply read failed.");
                } else {
                    isc_throw(Unexpected, "Netlink reply read error " << -err->error);
                }
                // Never happens we throw before we reach here
                return;
            }

            // store the data
            rtnl_store_reply(info, header);

            header = NLMSG_NEXT(header, status);
        }
        if (msg.msg_flags & MSG_TRUNC) {
            isc_throw(Unexpected, "Message received over netlink truncated.");
        }
        if (status) {
            isc_throw(Unexpected, "Trailing garbage of " << status << " bytes received over netlink.");
        }
    }
}

/// @brief releases nlmsg structure
///
/// @param messages Set of messages to be freed.
void Netlink::release_list(NetlinkMessages& messages) {
    // let's free local copies of stored messages
    for (NetlinkMessages::iterator msg = messages.begin(); msg != messages.end(); ++msg) {
        delete[] (*msg);
    }

    // ang get rid of the message pointers as well
    messages.clear();
}

} // end of anonymous namespace

namespace isc {
namespace dhcp {

/// @brief Detect available interfaces on Linux systems.
///
/// Uses the socket-based netlink protocol to retrieve the list of interfaces
/// from the Linux kernel.
void IfaceMgr::detectIfaces() {
    // Copies of netlink messages about links will be stored here.
    Netlink::NetlinkMessages link_info;

    // Copies of netlink messages about addresses will be stored here.
    Netlink::NetlinkMessages addr_info;

    // Socket descriptors and other rtnl-related parameters.
    Netlink nl;

    // Table with pointers to address attributes.
    Netlink::RTattribPtrs attribs_table;
    std::fill(attribs_table.begin(), attribs_table.end(),
              static_cast<struct rtattr*>(NULL));

    // Open socket
    nl.rtnl_open_socket();

    // Now we have open functional socket, let's use it!
    // Ask for list of network interfaces...
    nl.rtnl_send_request(AF_PACKET, RTM_GETLINK);

    // Get reply and store it in link_info list:
    // response is received as with any other socket - just a series
    // of bytes. They are representing collection of netlink messages
    // concatenated together. rtnl_process_reply will parse this
    // buffer, copy each message to a newly allocated memory and
    // store pointers to it in link_info. This allocated memory will
    // be released later. See release_info(link_info) below.
    nl.rtnl_process_reply(link_info);

    // Now ask for list of addresses (AF_UNSPEC = of any family)
    // Let's repeat, but this time ask for any addresses.
    // That includes IPv4, IPv6 and any other address families that
    // are happen to be supported by this system.
    nl.rtnl_send_request(AF_UNSPEC, RTM_GETADDR);

    // Get reply and store it in addr_info list.
    // Again, we will allocate new memory and store messages in
    // addr_info. It will be released later using release_info(addr_info).
    nl.rtnl_process_reply(addr_info);

    // Now build list with interface names
    for (Netlink::NetlinkMessages::iterator msg = link_info.begin();
         msg != link_info.end(); ++msg) {
        // Required to display information about interface
        struct ifinfomsg* interface_info = static_cast<ifinfomsg*>(NLMSG_DATA(*msg));
        int len = (*msg)->nlmsg_len;
        len -= NLMSG_LENGTH(sizeof(*interface_info));
        nl.parse_rtattr(attribs_table, IFLA_RTA(interface_info), len);

        // valgrind reports *possible* memory leak in the line below, but it is
        // bogus. Nevertheless, the whole interface definition has been split
        // into three separate steps for easier debugging.
        const char* tmp = static_cast<const char*>(RTA_DATA(attribs_table[IFLA_IFNAME]));
        string iface_name(tmp); // <--- bogus valgrind warning here
        IfacePtr iface(new Iface(iface_name, interface_info->ifi_index));

        iface->setHWType(interface_info->ifi_type);
        iface->setFlags(interface_info->ifi_flags);

        // Does interface have LL_ADDR?
        if (attribs_table[IFLA_ADDRESS]) {
            iface->setMac(static_cast<const uint8_t*>(RTA_DATA(attribs_table[IFLA_ADDRESS])),
                          RTA_PAYLOAD(attribs_table[IFLA_ADDRESS]));
        }
        else {
            // Tunnels can have no LL_ADDR. RTA_PAYLOAD doesn't check it and
            // try to dereference it in this manner
        }

        nl.ipaddrs_get(*iface, addr_info);
        ifaces_.push_back(iface);
    }

    nl.release_list(link_info);
    nl.release_list(addr_info);
}

/// @brief sets flag_*_ fields.
///
/// This implementation is OS-specific as bits have different meaning
/// on different OSes.
///
/// @param flags flags bitfield read from OS
void Iface::setFlags(uint64_t flags) {
    flags_ = flags;

    flag_loopback_ = flags & IFF_LOOPBACK;
    flag_up_ = flags & IFF_UP;
    flag_running_ = flags & IFF_RUNNING;
    flag_multicast_ = flags & IFF_MULTICAST;
    flag_broadcast_ = flags & IFF_BROADCAST;
}

void
IfaceMgr::setMatchingPacketFilter(const bool direct_response_desired) {
    if (direct_response_desired) {
        setPacketFilter(PktFilterPtr(new PktFilterLPF()));

    } else {
        setPacketFilter(PktFilterPtr(new PktFilterInet()));

    }
}

bool
IfaceMgr::openMulticastSocket(Iface& iface,
                              const isc::asiolink::IOAddress& addr,
                              const uint16_t port,
                              IfaceMgrErrorMsgCallback error_handler) {
    // This variable will hold a descriptor of the socket bound to
    // link-local address. It may be required for us to close this
    // socket if an attempt to open and bind a socket to multicast
    // address fails.
    int sock;
    try {
        sock = openSocket(iface.getName(), addr, port,
                          iface.flag_multicast_);

    } catch (const Exception& ex) {
        IFACEMGR_ERROR(SocketConfigError, error_handler,
                       "Failed to open link-local socket on "
                       " interface " << iface.getName() << ": "
                       << ex.what());
        return (false);

    }

    // In order to receive multicast traffic another socket is opened
    // and bound to the multicast address.

    /// @todo The DHCPv6 requires multicast so we may want to think
    /// whether we want to open the socket on a multicast-incapable
    /// interface or not. For now, we prefer to be liberal and allow
    /// it for some odd use cases which may utilize non-multicast
    /// interfaces. Perhaps a warning should be emitted if the
    /// interface is not a multicast one.
    if (iface.flag_multicast_) {
        try {
            openSocket(iface.getName(),
                       IOAddress(ALL_DHCP_RELAY_AGENTS_AND_SERVERS),
                       port);
        } catch (const Exception& ex) {
            // An attempt to open and bind a socket to multicast addres
            // has failed. We have to close the socket we previously
            // bound to link-local address - this is everything or
            // nothing strategy.
            iface.delSocket(sock);
            IFACEMGR_ERROR(SocketConfigError, error_handler,
                           "Failed to open multicast socket on"
                           " interface " << iface.getName()
                           << ", reason: " << ex.what());
            return (false);
        }
    }
    // Both sockets have opened successfully.
    return (true);
}

int
IfaceMgr::openSocket6(Iface& iface, const IOAddress& addr, uint16_t port,
                      const bool join_multicast) {
    // Assuming that packet filter is not NULL, because its modifier checks it.
    SocketInfo info = packet_filter6_->openSocket(iface, addr, port,
                                                  join_multicast);
    iface.addSocket(info);

    return (info.sockfd_);
}

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // if defined(LINUX)
