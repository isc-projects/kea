// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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

#if defined(OS_LINUX)
#include <net/if.h>
#include <linux/rtnetlink.h>
#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {
/// @brief Holds pointers to netlink messages.
///
/// netlink (a Linux interface for getting information about network
/// interfaces) uses memory aliasing. Linux kernel returns a memory
/// blob that should be interpreted as series of nlmessages. There
/// are different nlmsg structures defined with varying size. They
/// have one thing common - inital fields are laid out in the same
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
///
typedef boost::array<struct rtattr*, IFLA_MAX+1> RTattribPtrs;

BOOST_STATIC_ASSERT(IFLA_MAX>=IFA_MAX);

/// @brief This structure defines context for netlink connection.
struct rtnl_handle
{
    rtnl_handle() :fd(0), seq(0), dump(0) {
        memset(&local, 0, sizeof(struct sockaddr_nl));
        memset(&peer, 0, sizeof(struct sockaddr_nl));
    }
    int fd; // netlink file descriptor
    sockaddr_nl local; // local and remote addresses
    sockaddr_nl peer;
    __u32 seq; // counter used for generating unique sequence numbers
    __u32 dump; // number of expected message response
};

const size_t sndbuf = 32768;
const size_t rcvbuf = 32768;

/// @brief Opens netlink socket and initializes handle structure.
///
/// @exception Unexpected Thrown if socket configuration fails.
///
/// @param handle Context will be stored in this structure.
void rtnl_open_socket(struct rtnl_handle& handle) {
    // equivalent of rtnl_open
    handle.fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (handle.fd < 0) {
        isc_throw(Unexpected, "Failed to create NETLINK socket.");
    }

    if (setsockopt(handle.fd, SOL_SOCKET, SO_SNDBUF, &sndbuf, sizeof(sndbuf)) < 0) {
        isc_throw(Unexpected, "Failed to set send buffer in NETLINK socket.");
    }

    if (setsockopt(handle.fd, SOL_SOCKET, SO_RCVBUF, &sndbuf, sizeof(rcvbuf)) < 0) {
        isc_throw(Unexpected, "Failed to set receive buffer in NETLINK socket.");
    }

    memset(&handle.local, 0, sizeof(handle.local));
    handle.local.nl_family = AF_NETLINK;
    handle.local.nl_groups = 0;

    if (bind(handle.fd, (struct sockaddr*)&handle.local, sizeof(handle.local)) < 0) {
        isc_throw(Unexpected, "Failed to bind netlink socket.");
    }

    socklen_t addr_len = sizeof(handle.local);
    if (getsockname(handle.fd, (struct sockaddr*)&handle.local, &addr_len) < 0) {
        isc_throw(Unexpected, "Getsockname for netlink socket failed.");
    }

    // just 2 sanity checks and we are done
    if ( (addr_len != sizeof(handle.local)) ||
         (handle.local.nl_family != AF_NETLINK) ) {
        isc_throw(Unexpected, "getsockname() returned unexpected data for netlink socket.");
    }
}

/// @brief Sends request over NETLINK socket.
///
/// @param handle context structure
/// @param family requested information family
/// @param type request type (RTM_GETLINK or RTM_GETADDR)
void rtnl_send_request(rtnl_handle& handle, int family, int type) {
    struct {
        nlmsghdr netlink_header;
        rtgenmsg generic;
    } req;
    struct sockaddr_nl nladdr;

    // This doesn't work as gcc is confused with coma appearing in
    // the expression and thinks that there are 2 parameters passed to
    // BOOST_STATIC_ASSERT macro, while it only takes one.
    // BOOST_STATIC_ASSERT(sizeof(nlmsghdr) == offsetof(req,generic) );

    memset(&nladdr, 0, sizeof(nladdr));
    nladdr.nl_family = AF_NETLINK;

    // according to netlink(7) manpage, mlmsg_seq must be set to
    // sequence number and is used to track messages. That is just a
    // value that is opaque to kernel and user-space code is supposed
    // to use it to match incoming responses to sent requests. That is
    // not really useful, as we send a single request and get a single
    // response at a time, but still it better to obey man page suggestion
    // and just set this to monotonically increasing numbers.
    handle.seq++;

    // this will be used to finding correct response (responses
    // sent by kernel are supposed to have the same sequence number
    // as the request we sent)
    handle.dump = handle.seq;

    memset(&req, 0, sizeof(req));
    req.netlink_header.nlmsg_len = sizeof(req);
    req.netlink_header.nlmsg_type = type;
    req.netlink_header.nlmsg_flags = NLM_F_ROOT | NLM_F_MATCH | NLM_F_REQUEST;
    req.netlink_header.nlmsg_pid = 0;
    req.netlink_header.nlmsg_seq = handle.seq;
    req.generic.rtgen_family = family;

    int status =  sendto(handle.fd, static_cast<void*>(&req), sizeof(req), 0,
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
/// @param storage a vector that holds netlink messages
/// @param msg a netlink message to be added
void rtnl_store_reply(NetlinkMessages& storage, const struct nlmsghdr *msg)
{
    // we need to make a copy of this message. We really can't allocate
    // nlmsghdr directly as it is only part of the structure. There are
    // many message types with varying lengths and a common header.
    struct nlmsghdr* copy = reinterpret_cast<struct nlmsghdr*>(new char[msg->nlmsg_len]);
    memcpy(copy, msg, msg->nlmsg_len);

    // push_back copies only pointer content, not the pointed object
    storage.push_back(copy);
}

/// @brief Parses rtattr message.
///
/// Some netlink messages represent address information. Such messages
/// are concatenated collection of rtaddr structures. This function
/// iterates over that list and stores pointers to those messages in
/// flat array (table).
///
/// @param table rtattr messages will be stored here
/// @param rta pointer to first rtattr object
/// @param len length (in bytes) of concatenated rtattr list.
void parse_rtattr(RTattribPtrs& table, struct rtattr * rta, int len)
{
    std::fill(table.begin(), table.end(), static_cast<struct rtattr*>(NULL));
    // RTA_OK and RTA_NEXT() are macros defined in linux/rtnetlink.h
    // they are used to handle rtattributes. RTA_OK checks if the structure
    // pointed by rta is reasonable and passes all sanity checks.
    // RTA_NEXT() returns pointer to the next rtattr structure that
    // immediately follows pointed rta structure. See aforementioned
    // header for details.
    while (RTA_OK(rta, len)) {
        if (rta->rta_type <= table.size()-1) {
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
/// Netlink is a fine, but convoluted interface. It returns concatenated
/// collection of netlink messages. Some of those messages convey information
/// about addresses. Those messages are in fact appropriate header followed
/// by concatenated lists of rtattr structures that define various pieces
/// of address information.
///
/// @param iface interface representation (addresses will be added here)
/// @param addr_info collection of parsed netlink messages
void ipaddrs_get(IfaceMgr::Iface& iface, NetlinkMessages& addr_info) {
    uint8_t addr[V6ADDRESS_LEN];
    RTattribPtrs rta_tb;

    for (NetlinkMessages::const_iterator msg = addr_info.begin();
         msg != addr_info.end(); ++msg) {
        ifaddrmsg* ifa = static_cast<ifaddrmsg*>(NLMSG_DATA(*msg));

        // these are not the addresses you are looking for
        if (ifa->ifa_index != iface.getIndex()) {
            continue;
        }

        if (ifa->ifa_family == AF_INET6) {
            std::fill(rta_tb.begin(), rta_tb.end(), static_cast<rtattr*>(NULL));
            parse_rtattr(rta_tb, IFA_RTA(ifa), (*msg)->nlmsg_len - NLMSG_LENGTH(sizeof(*ifa)));
            if (!rta_tb[IFA_LOCAL]) {
                rta_tb[IFA_LOCAL] = rta_tb[IFA_ADDRESS];
            }
            if (!rta_tb[IFA_ADDRESS]) {
                rta_tb[IFA_ADDRESS] = rta_tb[IFA_LOCAL];
            }

            memcpy(addr,(char*)RTA_DATA(rta_tb[IFLA_ADDRESS]), V6ADDRESS_LEN);
            IOAddress a = IOAddress::from_bytes(AF_INET6, addr);
            iface.addAddress(a);

            /// TODO: Read lifetimes of configured addresses
        }

        if ( ifa->ifa_family == AF_INET ) {
            std::fill(rta_tb.begin(), rta_tb.end(), static_cast<struct rtattr*>(NULL));
            parse_rtattr(rta_tb, IFA_RTA(ifa), (*msg)->nlmsg_len - NLMSG_LENGTH(sizeof(*ifa)));
            if (!rta_tb[IFA_LOCAL])
                rta_tb[IFA_LOCAL]   = rta_tb[IFA_ADDRESS];
            if (!rta_tb[IFA_ADDRESS])
                rta_tb[IFA_ADDRESS] = rta_tb[IFA_LOCAL];

            memcpy(addr,(char*)RTA_DATA(rta_tb[IFLA_ADDRESS]),4);
            IOAddress a = IOAddress::from_bytes(AF_INET, addr);
            iface.addAddress(a);
        }
    }
}

/// @brief Processes reply received over netlink socket.
///
/// This method parses received buffer (a collection of concatenated
/// netlink messages), copies each received message to newly allocated
/// memory and stores pointers to it in info.
///
/// Make sure to release this memory, e.g. using release_info() function.
///
/// @param rth netlink parameters
/// @param info received netlink messages will be stored here
void rtnl_process_reply(const rtnl_handle& rth, NetlinkMessages& info) {

    struct sockaddr_nl nladdr;
    struct iovec iov;
    struct msghdr msg;
    memset(&msg, 0, sizeof(struct msghdr));
    msg.msg_name = &nladdr;
    msg.msg_namelen = sizeof(nladdr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    char buf[rcvbuf];

    iov.iov_base = buf;
    while (true) {
        int status;
        struct nlmsghdr* header;

        iov.iov_len = sizeof(buf);
        status = recvmsg(rth.fd, &msg, 0);

        if (status < 0) {
            if (errno == EINTR)
                continue;
            isc_throw(Unexpected, "Overrun while processing reply from netlink socket.");
        }

        if (status == 0) {
            isc_throw(Unexpected, "EOF while reading netlink socket.");
        }

        header = (struct nlmsghdr*)buf;
        while (NLMSG_OK(header, status)) {

            // why we received this anyway?
            if (nladdr.nl_pid != 0 ||
                header->nlmsg_pid != rth.local.nl_pid ||
                header->nlmsg_seq != rth.dump) {
                header = NLMSG_NEXT(header, status);
                continue;
            }

            if (header->nlmsg_type == NLMSG_DONE) {
                // end of message
                return;
            }

            if (header->nlmsg_type == NLMSG_ERROR) {
                struct nlmsgerr* err = (struct nlmsgerr*)NLMSG_DATA(header);
                if (header->nlmsg_len < NLMSG_LENGTH(sizeof(struct nlmsgerr))) {
                    // we are really out of luck here. We can't even say what is
                    // wrong as error message is truncated. D'oh.
                    isc_throw(Unexpected, "Netlink reply read failed.");
                } else {
                    isc_throw(Unexpected, "Netlink reply read error " << -err->error);
                }
                // never happens we throw before we reach here
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
/// @param messages first element of the list to be released
void release_list(NetlinkMessages& messages) {
    // let's free local copies of stored messages
    for (NetlinkMessages::iterator msg = messages.begin(); msg != messages.end(); ++msg) {
        delete (*msg);
    }

    // ang get rid of the message pointers as well
    messages.clear();
}

} // end of anonymous namespace

namespace isc {

namespace dhcp {

/// @brief Detect available interfaces on Linux systesm.
///
/// For detailed information about netlink interface, please refer to
/// http://en.wikipedia.org/wiki/Netlink and RFC3549.  Following
/// comments in the core is an overview on how netlink interface is
/// used here. Please note that this interface is very robust and
/// allows many operations: add/get/set/delete links, addresses,
/// routes, queuing, manipulate traffic classes, manipulate
/// neithborhood tables and even do something with address
/// labels. Getting list of interfaces with addresses configured on it
/// is just a small subset of all possible actions.
void IfaceMgr::detectIfaces() {
    cout << "Linux: detecting interfaces." << endl;

    // Copies of netlink messages about links will be stored here.
    NetlinkMessages link_info;

    // Copies of netlink messages about addresses will be stored here.
    NetlinkMessages addr_info;

    // socket descriptors other rtnl-related parameters
    struct rtnl_handle handle;

    RTattribPtrs attribs_table; // table with pointers to address attributes
    int len = 0;
    std::fill(attribs_table.begin(), attribs_table.end(),
              static_cast<struct rtattr*>(NULL));

    // open socket
    rtnl_open_socket(handle);

    // now we have open functional socket, let's use it!
    // ask for list of network interfaces...
    rtnl_send_request(handle, AF_PACKET, RTM_GETLINK);

    // Get reply and store it in link_info list:
    // response is received as with any other socket - just a series
    // of bytes. They are representing collection of netlink messages
    // concatenated together. rtnl_process_reply will parse this
    // buffer, copy each message to a newly allocated memory and
    // store pointers to it in link_info. This allocated memory will
    // be released later. See release_info(link_info) below.
    rtnl_process_reply(handle, link_info);

    // Now ask for list of addresses (AF_UNSPEC = of any family)
    // Let's repeat, but this time ask for any addresses.
    // That includes IPv4, IPv6 and any other address families that
    // are happen to be supported by this system.
    rtnl_send_request(handle, AF_UNSPEC, RTM_GETADDR);

    // Get reply and store it in addr_info list.
    // Again, we will allocate new memory and store messages in
    // addr_info. It will be released later using release_info(addr_info).
    rtnl_process_reply(handle, addr_info);

    // Now build list with interface names
    for (NetlinkMessages::iterator msg = link_info.begin(); msg != link_info.end(); ++msg) {
        // required to display information about interface
        struct ifinfomsg* interface_info = static_cast<ifinfomsg*>(NLMSG_DATA(*msg));
        len = (*msg)->nlmsg_len;
        len -= NLMSG_LENGTH(sizeof(*interface_info));
        parse_rtattr(attribs_table, IFLA_RTA(interface_info), len);

        // valgrind reports *possible* memory leak in the line below,
        // but I do believe that this report is bogus. Nevertheless,
        // I've split the whole interface definition into three
        // separate steps for easier debugging.
        const char* tmp = static_cast<const char*>(RTA_DATA(attribs_table[IFLA_IFNAME]));
        string iface_name(tmp); // <--- (probably bogus) valgrind warning here
        Iface iface = Iface(iface_name, interface_info->ifi_index);

        iface.hardware_type_ = interface_info->ifi_type;
        iface.setFlags(interface_info->ifi_flags);

        iface.mac_len_ = 0;
        memset(iface.mac_, 0, IfaceMgr::MAX_MAC_LEN);
        // Does inetface has LL_ADDR?
        if (attribs_table[IFLA_ADDRESS]) {
            iface.mac_len_ = RTA_PAYLOAD(attribs_table[IFLA_ADDRESS]);
            if (iface.mac_len_ > IfaceMgr::MAX_MAC_LEN) {
                iface.mac_len_ = 0;
                isc_throw(Unexpected, "Interface " << iface.getFullName()
                          << " was detected to have link address of length "
                          << RTA_PAYLOAD(attribs_table[IFLA_ADDRESS])
                          << ", but maximum supported length is " << IfaceMgr::MAX_MAC_LEN);
            }
            memcpy(iface.mac_, RTA_DATA(attribs_table[IFLA_ADDRESS]), iface.mac_len_);
        }
        else {
            // Tunnels can have no LL_ADDR. RTA_PAYLOAD doesn't check it and try to
            // dereference it in this manner
            // #define RTA_PAYLOAD(rta) ((int)((rta)->rta_len) - RTA_LENGTH(0))
            iface.mac_len_ = 0;
        }

        ipaddrs_get(iface, addr_info);
        ifaces_.push_back(iface);
    }

    release_list(link_info);
    release_list(addr_info);

    printIfaces();

    close(handle.fd);
}

/// @brief sets flag_*_ fields.
///
/// This implementation is OS-specific as bits have different meaning
/// on different OSes.
///
/// @param flags flags bitfield read from OS
void IfaceMgr::Iface::setFlags(uint32_t flags) {
    flags_ = flags;

    flag_loopback_ = flags & IFF_LOOPBACK;
    flag_up_ = flags & IFF_UP;
    flag_running_ = flags & IFF_RUNNING;
    flag_multicast_ = flags & IFF_MULTICAST;
    flag_broadcast_ = flags & IFF_BROADCAST;
}

} // end of isc::dhcp namespace

} // end of isc namespace

#endif // if defined(LINUX)
