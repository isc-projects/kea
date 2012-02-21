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

#if defined(OS_LINUX)

#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>

#include <net/if.h>
#include <linux/rtnetlink.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {
/// @brief holds pointers to netlink messages
///
/// netlink (a Linux interface for getting information about network
/// interfaces) uses memory aliasing. There are many nlmsg structures
/// with varying size that all have the same nlmsghdr. The only
/// reasonable way to represent this in C++ is to use vector of
/// pointers to nlmsghdr (the common structure).
typedef vector<struct nlmsghdr*> NetlinkMessages;

/// This is a structure that defines context for netlink connection.
struct rtnl_handle
{
    int fd; // netlink file descriptor
    struct sockaddr_nl local;
    struct sockaddr_nl peer;
    __u32 seq;
    __u32 dump;
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
void rtnl_send_request(struct rtnl_handle& handle, int family, int type) {
    struct {
        struct nlmsghdr netlink_header;
        struct rtgenmsg generic;
    } req;
    struct sockaddr_nl nladdr;

    memset(&nladdr, 0, sizeof(nladdr));
    nladdr.nl_family = AF_NETLINK;

    memset(&req, 0, sizeof(req));
    req.netlink_header.nlmsg_len = sizeof(req);
    req.netlink_header.nlmsg_type = type;
    req.netlink_header.nlmsg_flags = NLM_F_ROOT|NLM_F_MATCH|NLM_F_REQUEST;
    req.netlink_header.nlmsg_pid = 0;
    req.netlink_header.nlmsg_seq = handle.dump = ++handle.seq;
    req.generic.rtgen_family = family;

    int status =  sendto(handle.fd, (void*)&req, sizeof(req), 0,
                         (struct sockaddr*)&nladdr, sizeof(nladdr));

    if (status<0) {
        isc_throw(Unexpected, "Failed to send " << sizeof(nladdr) << " bytes over netlink socket.");
    }
}

/// @brief Appends nlmsg to a storage.
///
/// @param storage a vector that holds netlink messages
/// @param msg a netlink message to be added
void rtnl_store_reply(NetlinkMessages& storage, const struct nlmsghdr *msg)
{
    // we need to make a copy of this message. We really can't allocate
    // nlmsghdr directly as it is only part of the structure. There are
    // many message types with varying lengths and a common header.
    struct nlmsghdr* copy = reinterpret_cast<struct nlmsghdr*>(new char[(msg->nlmsg_len)]);
    memcpy(copy, msg, msg->nlmsg_len);
    if (copy == NULL) {
        isc_throw(Unexpected, "Failed to allocate " << msg->nlmsg_len
                  << " bytes.");
    }

    // push_back copies only pointer content, not the pointed object
    storage.push_back(copy);
}

void parse_rtattr(struct rtattr *tb[], int max, struct rtattr *rta, int len)
{
    memset(tb, 0, sizeof(struct rtattr *) * (max + 1));
    while (RTA_OK(rta, len)) {
        if (rta->rta_type <= max)
            tb[rta->rta_type] = rta;
        rta = RTA_NEXT(rta,len);
    }
    if (len) {
        isc_throw(Unexpected, "Failed to parse RTATTR in netlink message.");
    }
}

void ipaddrs_get(IfaceMgr::Iface& iface, NetlinkMessages& addr_info) {
    uint8_t addr[16];
    struct rtattr * rta_tb[IFA_MAX+1];

    for (NetlinkMessages::const_iterator msg = addr_info.begin();
         msg != addr_info.end(); ++msg) {
        struct ifaddrmsg *ifa = (ifaddrmsg*)NLMSG_DATA(*msg);

        // these are not the addresses you are looking for
        if ( ifa->ifa_index != iface.getIndex()) {
            continue;
        }

        if ( ifa->ifa_family == AF_INET6 ) {
            memset(rta_tb, 0, sizeof(rta_tb));
            parse_rtattr(rta_tb, IFA_MAX, IFA_RTA(ifa), (*msg)->nlmsg_len - NLMSG_LENGTH(sizeof(*ifa)));
            if (!rta_tb[IFA_LOCAL])
                rta_tb[IFA_LOCAL]   = rta_tb[IFA_ADDRESS];
            if (!rta_tb[IFA_ADDRESS])
                rta_tb[IFA_ADDRESS] = rta_tb[IFA_LOCAL];

            memcpy(addr,(char*)RTA_DATA(rta_tb[IFLA_ADDRESS]),16);
            IOAddress a = IOAddress::from_bytes(AF_INET6, addr);
            iface.addAddress(a);

            /// TODO: Read lifetimes of configured addresses
        }

        if ( ifa->ifa_family == AF_INET ) {
            memset(rta_tb, 0, sizeof(rta_tb));
            parse_rtattr(rta_tb, IFA_MAX, IFA_RTA(ifa), (*msg)->nlmsg_len - NLMSG_LENGTH(sizeof(*ifa)));
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

void rtnl_process_reply(const struct rtnl_handle& rth, NetlinkMessages& info) {

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
                struct nlmsgerr *err = (struct nlmsgerr*)NLMSG_DATA(header);
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
    // let's free our copies of stored messages
    for (NetlinkMessages::iterator msg = messages.begin(); msg != messages.end(); ++msg) {
        delete(*msg);
    }
    messages.clear();
}

} // end of anonymous namespace

namespace isc {

namespace dhcp {

void IfaceMgr::detectIfaces() {
    cout << "Linux: detecting interfaces." << endl;

    NetlinkMessages link_info; // link info
    NetlinkMessages addr_info; // address info
    struct rtnl_handle handle;

    // required to display information about interface
    struct ifinfomsg* ifi = NULL;
    struct rtattr* tb[IFLA_MAX+1];
    int len = 0;
    memset(tb, 0, sizeof(tb));
    memset(&handle,0, sizeof(handle));

    // open socket
    rtnl_open_socket(handle);

    // now we have open functional socket, let's use it!
    // ask for list of interface...
    rtnl_send_request(handle, AF_PACKET, RTM_GETLINK);

    // Get reply and store it in link_info list.
    rtnl_process_reply(handle, link_info);

    // Now ask for list of addresses (AF_UNSPEC = of any family)
    rtnl_send_request(handle, AF_UNSPEC, RTM_GETADDR);

    // Get reply and store it in addr_info list.
    rtnl_process_reply(handle, addr_info);

    // Now build list with interface names
    for (NetlinkMessages::iterator msg = link_info.begin(); msg != link_info.end(); ++msg) {
        ifi = static_cast<ifinfomsg*>(NLMSG_DATA(*msg));
        len = (*msg)->nlmsg_len;
        len -= NLMSG_LENGTH(sizeof(*ifi));
        parse_rtattr(tb, IFLA_MAX, IFLA_RTA(ifi), len);

        // valgrind reports *possible* memory leak in the line below, but I do believe that this
        // report is bogus. Nevertheless, I've split the whole interface definition into
        // three separate steps for easier debugging.
        const char* tmp = static_cast<const char*>(RTA_DATA(tb[IFLA_IFNAME]));
        string iface_name(tmp); // <--- valgrind warning here
        Iface iface = Iface(iface_name, ifi->ifi_index);

        iface.hardware_type_ = ifi->ifi_type;
        iface.setFlags(ifi->ifi_flags);

        iface.mac_len_ = 0;
        memset(iface.mac_, 0, IfaceMgr::MAX_MAC_LEN);
        // Does inetface has LL_ADDR?
        if (tb[IFLA_ADDRESS]) {
            iface.mac_len_ = RTA_PAYLOAD(tb[IFLA_ADDRESS]);
            if (iface.mac_len_ > IfaceMgr::MAX_MAC_LEN) {
                iface.mac_len_ = 0;
                isc_throw(Unexpected, "Interface " << iface.getFullName()
                          << " was detected to have link address of length " << RTA_PAYLOAD(tb[IFLA_ADDRESS])
                          << ", but maximum supported length is " << IfaceMgr::MAX_MAC_LEN);
            }
            memcpy(iface.mac_, RTA_DATA(tb[IFLA_ADDRESS]), iface.mac_len_);
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
