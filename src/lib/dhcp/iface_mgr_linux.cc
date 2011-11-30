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

#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>

#include <net/if.h>
#include <linux/if_link.h>
#include <linux/rtnetlink.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

#if !defined(OS_LINUX)
/// There are several detectIfaces() implementations for specific
/// Operating Systems. This one is specific to Linux. It works on
/// Linux only, so it does not make sense to try to compile it somewhere
/// else. In particular, Makefile.am includes only one iface_mgr_{OS_TYPE}.cc
/// file.

#error "Attempt to compile iface_mgr_linux.cc on non-Linux system!"
#endif

struct rtnl_handle
{
	int			fd;
	struct sockaddr_nl	local;
	struct sockaddr_nl	peer;
	__u32			seq;
	__u32			dump;
};

struct nlmsg_list
{
	struct nlmsg_list *next;
	struct nlmsghdr	  h;
};

const int sndbuf = 32768;
const int rcvbuf = 32768;

namespace isc {


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

// sends request over NETLINK socket
void rtnl_send_request(struct rtnl_handle& handle,
		       int family, int type) {
    struct {
	struct nlmsghdr nlh;
	struct rtgenmsg g;
    } req;
    struct sockaddr_nl nladdr;
    
    memset(&nladdr, 0, sizeof(nladdr));
    nladdr.nl_family = AF_NETLINK;
    
    memset(&req, 0, sizeof(req));
    req.nlh.nlmsg_len = sizeof(req);
    req.nlh.nlmsg_type = type;
    req.nlh.nlmsg_flags = NLM_F_ROOT|NLM_F_MATCH|NLM_F_REQUEST;
    req.nlh.nlmsg_pid = 0;
    req.nlh.nlmsg_seq = handle.dump = ++handle.seq;
    req.g.rtgen_family = family;
    
    int status =  sendto(handle.fd, (void*)&req, sizeof(req), 0,
			 (struct sockaddr*)&nladdr, sizeof(nladdr));

    if (status<0) {
	isc_throw(Unexpected, "Failed to send " << sizeof(nladdr) << " bytes over netlink socket.");
    }
}

void rtnl_store_reply(/*const struct sockaddr_nl *who,*/ struct nlmsghdr *n, struct nlmsg_list** linfo)
{
    struct nlmsg_list *h;
    struct nlmsg_list **lp;
    
    h = (nlmsg_list*)malloc(n->nlmsg_len+sizeof(void*));
    if (h == NULL) {
	isc_throw(Unexpected, "Failed to allocate " << n->nlmsg_len+sizeof(void*)
		  << " bytes.");
    }
    
    memcpy(&h->h, n, n->nlmsg_len);
    h->next = NULL;
    
    for (lp = linfo; *lp; lp = &(*lp)->next) /* NOTHING */;
    *lp = h;
    
    // ll_remember_index(who, n, NULL);
    // return 0;
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


 void ipaddrs_get(IfaceMgr::Iface& iface, struct nlmsg_list *ainfo) {
    uint8_t addr[16];
    struct rtattr * rta_tb[IFA_MAX+1];

    for ( ;ainfo ;  ainfo = ainfo->next) {
	struct nlmsghdr *n = &ainfo->h;
	struct ifaddrmsg *ifa = (ifaddrmsg*)NLMSG_DATA(n);

	// these are not the addresses you are looking for
	if ( ifa->ifa_index != iface.ifindex_) {
	    continue;
	}

	if ( ifa->ifa_family == AF_INET6 ) {
	    memset(rta_tb, 0, sizeof(rta_tb));
	    parse_rtattr(rta_tb, IFA_MAX, IFA_RTA(ifa), n->nlmsg_len - NLMSG_LENGTH(sizeof(*ifa)));
	    if (!rta_tb[IFA_LOCAL])   
		rta_tb[IFA_LOCAL]   = rta_tb[IFA_ADDRESS];
	    if (!rta_tb[IFA_ADDRESS]) 
		rta_tb[IFA_ADDRESS] = rta_tb[IFA_LOCAL];
	    
	    memcpy(addr,(char*)RTA_DATA(rta_tb[IFLA_ADDRESS]),16);
	    IOAddress a = IOAddress::from_bytes(AF_INET6, addr);
	    iface.addrs_.push_back(a);

	    /// TODO: Read lifetimes of configured addresses
	}

	if ( ifa->ifa_family == AF_INET ) {
	    memset(rta_tb, 0, sizeof(rta_tb));
	    parse_rtattr(rta_tb, IFA_MAX, IFA_RTA(ifa), n->nlmsg_len - NLMSG_LENGTH(sizeof(*ifa)));
	    if (!rta_tb[IFA_LOCAL])   
		rta_tb[IFA_LOCAL]   = rta_tb[IFA_ADDRESS];
	    if (!rta_tb[IFA_ADDRESS]) 
		rta_tb[IFA_ADDRESS] = rta_tb[IFA_LOCAL];
	    
	    memcpy(addr,(char*)RTA_DATA(rta_tb[IFLA_ADDRESS]),4);
	    IOAddress a = IOAddress::from_bytes(AF_INET, addr);
	    iface.addrs_.push_back(a);
	}


    }
}


void rtnl_process_reply(struct rtnl_handle &rth,
		       struct nlmsg_list *&info) {

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
    while (1) {
	int status;
	struct nlmsghdr *h;
	
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
	
	h = (struct nlmsghdr*)buf;
	while (NLMSG_OK(h, status)) {

	    // why we received this anyway?
	    if (nladdr.nl_pid != 0 ||
		h->nlmsg_pid != rth.local.nl_pid ||
		h->nlmsg_seq != rth.dump) {
		h = NLMSG_NEXT(h, status);
		continue;
	    }
		    
	    if (h->nlmsg_type == NLMSG_DONE) {
		// end of message
		return;
	    }

	    if (h->nlmsg_type == NLMSG_ERROR) {
		struct nlmsgerr *err = (struct nlmsgerr*)NLMSG_DATA(h);
		if (h->nlmsg_len < NLMSG_LENGTH(sizeof(struct nlmsgerr))) {
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
	    rtnl_store_reply(/*&nladdr,*/ h, &info);
	    
	    h = NLMSG_NEXT(h, status);
	}
	if (msg.msg_flags & MSG_TRUNC) {
	    isc_throw(Unexpected, "Message received over netlink truncated.");
	}
	if (status) {
	    isc_throw(Unexpected, "Trailing garbage of " << status << " bytes received over netlink.");
	}
    }
}

void release_list(struct nlmsg_list *n) {
    struct nlmsg_list *tmp;
    while (n) {
	tmp = n->next;
	free(n);
	n = tmp;
    }
}

    
void
IfaceMgr::detectIfaces() {

    cout << "Linux: detecting interfaces." << endl;

    struct nlmsg_list *linfo = NULL;
    struct nlmsg_list *ainfo = NULL;
    struct nlmsg_list *l = NULL;
    struct rtnl_handle rth;

    /* required to display information about interface */
    struct ifinfomsg *ifi = NULL;
    struct rtattr * tb[IFLA_MAX+1];
    int len = 0;
    memset(tb, 0, sizeof(tb));
    memset(&rth,0, sizeof(rth));

    // open socket
    rtnl_open_socket(rth);

    // now we have open functional socket, let's use it!
    rtnl_send_request(rth, AF_PACKET, RTM_GETLINK);

    // process reply
    rtnl_process_reply(rth, linfo);
    //rtnl_dump_filter(&rth, store_nlmsg, &linfo, NULL, NULL);
    
    /* 2nd attribute: AF_UNSPEC, AF_INET, AF_INET6 */
    rtnl_send_request(rth, AF_UNSPEC, RTM_GETADDR);
    rtnl_process_reply(rth, ainfo);

    /* build list with interface names */
    for (l=linfo; l; l = l->next) {
	ifi = (ifinfomsg*)NLMSG_DATA(&l->h);
	len = (&l->h)->nlmsg_len;
	len -= NLMSG_LENGTH(sizeof(*ifi));
	parse_rtattr(tb, IFLA_MAX, IFLA_RTA(ifi), len);

	Iface* iface = new Iface(string( (char*)RTA_DATA(tb[IFLA_IFNAME])), ifi->ifi_index);

	iface->hardware_type_ = ifi->ifi_type;
	iface->setFlags(ifi->ifi_flags);

	iface->mac_len_ = 0;
	memset(iface->mac_, 0, IfaceMgr::MAX_MAC_LEN);
	/* Does inetface has LL_ADDR? */
	if (tb[IFLA_ADDRESS]) {
  	    iface->mac_len_ = RTA_PAYLOAD(tb[IFLA_ADDRESS]);
	    if (iface->mac_len_ > IfaceMgr::MAX_MAC_LEN) {
		iface->mac_len_ = 0;
		isc_throw(Unexpected, "Interface " << iface->getFullName() 
			  << " was detected to have link address of length " << RTA_PAYLOAD(tb[IFLA_ADDRESS])
			  << ", but maximum supported length is " << IfaceMgr::MAX_MAC_LEN);
	    }
	    memcpy(iface->mac_, RTA_DATA(tb[IFLA_ADDRESS]), iface->mac_len_);
	}
	else {
	    /* Tunnels can have no LL_ADDR. RTA_PAYLOAD doesn't check it and try to
	     * dereference it in this manner
	     * #define RTA_PAYLOAD(rta) ((int)((rta)->rta_len) - RTA_LENGTH(0))
	     */
	    iface->mac_len_ = 0;
	}

	ipaddrs_get(*iface, ainfo);
	ifaces_.push_back(*iface);
    }


    release_list(linfo);
    release_list(ainfo);

    printIfaces();
}

void IfaceMgr::Iface::setFlags(uint32_t flags) {
    flags_ = flags;

    flag_loopback_ = flags & IFF_LOOPBACK;
    flag_up_ = flags & IFF_UP;
    flag_running_ = flags & IFF_RUNNING;
    flag_multicast_ = flags & IFF_MULTICAST;
    flag_broadcast_ = flags & IFF_BROADCAST;
}

}
