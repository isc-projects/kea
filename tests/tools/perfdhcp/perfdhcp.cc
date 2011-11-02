/*
 * Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <ifaddrs.h>
#include <strings.h>
#include <string.h>
#include <stdarg.h>
#include <netdb.h>
#include <errno.h>
#include <time.h>
#include "perfdhcp.h"
#include "cloptions.h"
#include "dkdebug.h"

struct duid {
    uint16_t duid_type;
    uint16_t htype;
    unsigned char hwaddr[6];
};

struct addrinfo *getaddr(int addr_fam, const char *hostname, const char *port);
char *addrName(const struct sockaddr_storage *addr, char *buf, size_t bufsize);
void add_option(int v6, unsigned optnum, unsigned count,
	size_t size, int direct, unsigned char options[], size_t *buffer_used,
	...);
int get_linklocal_addr(const char if_name[], struct sockaddr_storage *addr);
const char *optionName(int v6, unsigned optnum);
const unsigned char *find_option(const struct dhcp_packet *pkt, int search_opt);
int socket_setup(int addr_fam, const char *localAddr, const char *port,
	const char *type, struct sockaddr_storage *l_addr);
void gen_discover(struct dhcp_packet *discover_pkt, const struct in_addr *giaddr);
void gen_request(struct dhcp_packet *dhcp_pkt, const struct in_addr *giaddr,
	const struct in_addr *yiaddr, const unsigned char *server_id);
void dhcp_recv(int v6, void *msg, int recv_fd, const struct sockaddr_storage *recv_laddr);
void dora(const char *server, const char *localAddr);
void sarr(const char *server, const char *if_name);
void print_addrinfo(FILE *f, const struct addrinfo *addr);
void print_sa6_info(FILE *f, const struct sockaddr_in6 *sa);
void gen_solicit(struct dhcpv6_packet *dhcp_pkt, const struct duid *client_id);
void dhcp_send(int v6, const unsigned char *msg, int send_fd, const struct
	sockaddr *r_addr, const struct sockaddr_storage *send_laddr);

int v6 = 0;
int initialOnly = 0;
const char *localName = NULL;
unsigned rate = 0;
unsigned numRequest = 0;
const char *server = NULL;
const char *diagSelector = "";

static const struct dkdesc diagLetters[] = {
    { 's', DK_SOCK },
    { 'm', DK_MSG },
    { 'p', DK_PACKET },
    { 'a', DK_ALL },
    { '\0', 0 }
};

int
main(int argc, char *argv[])
{
    int ret;

    if ((ret = procArgs(argc, argv)) != 1)
	exit(ret);

    srand(time(NULL));
    if (v6)
	sarr(server, localName);
    else
	dora(server, localName);
    dk_setup(diagSelector, diagLetters);

    exit(0);
}

/*
 * Create a socket for communication with dhcp server:
 * - Create socket
 * - Bind it to given local address and port, UDP.
 *
 * Input variables:
 * addr_fam is the address family to use, e.g. AF_INET
 * localAddr is the local address to bind to.
 * port is the port to bind to.
 * type is a string giving the purpose of the socket, for verbose output.
 * If localAddr is null, the local address etc. is taken from l_addr.
 *
 * Output variables:
 * Socket details are stored in l_addr.
 *
 * Return value: The network fd.
 */
int
socket_setup(int addr_fam, const char *localAddr, const char *port,
	const char *type, struct sockaddr_storage *l_addr)
{
    char addrbuf[ADDR_NAME_BUFSIZE];
    int net_fd;
    struct addrinfo *addrs;

    if ((addrs = getaddr(addr_fam, localAddr, port)) == NULL) {
	fprintf(stderr, "No addresses for %s\n", localAddr);
	exit(1);
    }
    if (localAddr == NULL) {
	if (dk_set(DK_SOCK)) {
	    fprintf(stderr, "local address:\n");
	    print_sa6_info(stderr, (struct sockaddr_in6 *)l_addr);
	}
	memcpy(&((struct sockaddr_in6 *)addrs->ai_addr)->sin6_addr,
		&((struct sockaddr_in6 *)l_addr)->sin6_addr,
		sizeof(struct in6_addr));
	((struct sockaddr_in6 *)addrs->ai_addr)->sin6_flowinfo =
		((struct sockaddr_in6 *)l_addr)->sin6_flowinfo;
	((struct sockaddr_in6 *)addrs->ai_addr)->sin6_scope_id =
		((struct sockaddr_in6 *)l_addr)->sin6_scope_id;
    }
    if (dk_set(DK_SOCK)) {
	print_addrinfo(stderr, addrs);
	fprintf(stderr, "Creating socket from addrinfo:\n");
	print_addrinfo(stderr, addrs);
    }
    net_fd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
    if (net_fd < 0) {
        perror("socket");
        exit(1);
    }
    if (bind(net_fd, addrs->ai_addr, addrs->ai_addrlen) == -1) {
	int s_errno = errno;
	fprintf(stderr, "Could not bind to %s: %s\n",
		addrName((struct sockaddr_storage *)addrs->ai_addr, addrbuf,
			sizeof(addrbuf)), strerror(s_errno));
	exit(1);
    }
    dkprintf(DK_SOCK, "%s fd %d bound to %s\n", type, net_fd, addrName((struct sockaddr_storage *)addrs->ai_addr, addrbuf, sizeof(addrbuf)));
    memcpy(l_addr, addrs->ai_addr, sizeof(struct sockaddr_storage));
    freeaddrinfo(addrs);
    return net_fd;
}

/*
 * gen_discover: Generate a DHCP discover packet.
 *
 * Input variables:
 * giaddr is the address to be copied into the giaddr (gateway addr) element.
 *
 * Output variables:
 * discover_packet is a pointer to storage for the packet to be generated.
 */
void
gen_discover(struct dhcp_packet *discover_pkt, const struct in_addr *giaddr)
{
    size_t options_len;

    bzero((char *) discover_pkt, sizeof(struct dhcp_packet));
    discover_pkt->op = BOOTREQUEST;
    discover_pkt->htype = HTYPE_ETHER;
    discover_pkt->hlen = 6;
    discover_pkt->hops = 1;
    discover_pkt->xid = 0x12345678;	/* transaction id - fix */
    discover_pkt->secs = 0;
    discover_pkt->flags = 0;
    memcpy(&discover_pkt->giaddr, giaddr, sizeof((*discover_pkt).giaddr));
    strncpy((char *)discover_pkt->chaddr, "\x12\x34\x56\x78\x9a\xbc", 6);	/* client hardware addr - fix */
    memset(discover_pkt->options, DHO_PAD, DHCP_MAX_OPTION_LEN);
    strncpy((char *)discover_pkt->options, "\x63\x82\x53\x63", 4);		/* magic cookie */
    options_len = 4;
    add_option(0, DHO_DHCP_MESSAGE_TYPE, 1, 1, 1, discover_pkt->options, &options_len,
	    DHCPDISCOVER);
    add_option(0, DHO_DHCP_PARAMETER_REQUEST_LIST, 4, 1, 1, discover_pkt->options,
	    &options_len, DHO_SUBNET_MASK, DHO_ROUTERS, DHO_DOMAIN_NAME,
	    DHO_DOMAIN_NAME_SERVERS);
    add_option(0, DHO_DHCP_LEASE_TIME, 1, 4, 1, discover_pkt->options, &options_len,
	    htonl(60));

    if (options_len < DHCP_MAX_OPTION_LEN)
	discover_pkt->options[options_len++] = DHO_END;
}

/*
 * gen_request(): Generate a DHCPv4 request packet.
 * 
 * Input variables
 * giaddr is the address to copy into the giaddr element.
 * yiaddr is the address to store in the DHO_DHCP_REQUESTED_ADDRESS option.
 * server_id is the ID to store in the DHO_DHCP_SERVER_IDENTIFIER option.
 *
 * Output variables:
 * dhcp_pkt points to storage for the packet to be generated.
 */
void
gen_request(struct dhcp_packet *dhcp_pkt, const struct in_addr *giaddr,
	const struct in_addr *yiaddr, const unsigned char *server_id)
{
    size_t options_len;

    bzero((char *) dhcp_pkt, sizeof(struct dhcp_packet));
    dhcp_pkt->op = BOOTREQUEST;
    dhcp_pkt->htype = HTYPE_ETHER;
    dhcp_pkt->hlen = 6;
    dhcp_pkt->hops = 1;
    dhcp_pkt->xid = 0x12345678;	/* transaction id - fix */
    dhcp_pkt->secs = 0;
    dhcp_pkt->flags = 0;
    memcpy(&dhcp_pkt->giaddr, giaddr, sizeof((*dhcp_pkt).giaddr));
    /*memcpy(&dhcp_pkt->yiaddr, yiaddr, sizeof((*dhcp_pkt).yiaddr));*/
    strncpy((char *)dhcp_pkt->chaddr, "\x12\x34\x56\x78\x9a\xbc", 6);	/* client hardware addr - fix */
    memset(dhcp_pkt->options, DHO_PAD, DHCP_MAX_OPTION_LEN);
    strncpy((char *)dhcp_pkt->options, "\x63\x82\x53\x63", 4);		/* magic cookie */
    options_len = 4;
    add_option(0, DHO_DHCP_MESSAGE_TYPE, 1, 1, 1, dhcp_pkt->options, &options_len,
	    DHCPREQUEST);
    add_option(0, DHO_DHCP_SERVER_IDENTIFIER, 1, 4, 0, dhcp_pkt->options,
	    &options_len, server_id);
    add_option(0, DHO_DHCP_REQUESTED_ADDRESS, 1, 4, 1, dhcp_pkt->options,
	    &options_len, *yiaddr);
    add_option(0, DHO_DHCP_LEASE_TIME, 1, 4, 1, dhcp_pkt->options, &options_len,
	    htonl(60));

    if (options_len < DHCP_MAX_OPTION_LEN)
	dhcp_pkt->options[options_len++] = DHO_END;
}

/*
 * dhcp_send: Send a DHCP packet.
 * If the send fails, the program exits with an error message.
 *
 * Input variables:
 * dhcp_packet: DHCP message to send.
 * send_fd: Socket to send message on.
 * r_addr: Remote address to send message to.
 * send_laddr: Local address of socket, for informational messages only.
 */
void
dhcp_send(int v6, const unsigned char *msg, int send_fd, const struct sockaddr *r_addr,
	const struct sockaddr_storage *send_laddr) {
    
    size_t num_octets;
    ssize_t num_written;
    char addrbuf[ADDR_NAME_BUFSIZE];
    char addrbuf2[ADDR_NAME_BUFSIZE];

    num_octets = v6 ? sizeof(struct dhcpv6_packet) : sizeof(struct dhcp_packet);
    if (dk_set(DK_MSG)) {
	fprintf(stderr, "Sending %zu octets to socket fd %u, local %s remote %s",
		num_octets, send_fd,
		addrName((struct sockaddr_storage *)send_laddr, addrbuf, sizeof(addrbuf)),
		addrName((struct sockaddr_storage *)r_addr, addrbuf2, sizeof(addrbuf2)));
	fprintf(stderr, "Packet contents:\n");
	print_dhcp_packet(v6, msg, num_octets);
    }
    num_written = sendto(send_fd, msg, num_octets, 0,
	    r_addr, sizeof(struct sockaddr_storage));
    if (num_written < 0) {
	int s_errno = errno;
	fprintf(stderr, "Send failed: %s\n", strerror(s_errno));
	exit(1);
    }
    if ((size_t) num_written != num_octets) {
	fprintf(stderr, "Only %d of %u octets written\n", (int) num_written, (unsigned) num_octets);
    }
}

/*
 * dhcp_recv: Receive a DHCP packet.
 *
 * Input variables:
 * recv_fd is the socket to receive on.
 * recv_laddr is the socket's address, solely for informational messages.
 *
 * Output variables:
 * msg points to storage for the received message.
 */
void
dhcp_recv(int v6, void *msg, int recv_fd,
	const struct sockaddr_storage *recv_laddr) {
    
    ssize_t num_octets;
    struct sockaddr_storage sourceAddr;
    socklen_t addrSize;
    char addrbuf[ADDR_NAME_BUFSIZE];

    dkprintf(DK_SOCK, "Waiting for response on socket fd %u, %s",
	    recv_fd,
	    addrName(recv_laddr, addrbuf, sizeof(addrbuf)));
    addrSize = sizeof(sourceAddr);
    num_octets = recvfrom(recv_fd, msg, v6 ? sizeof(struct dhcpv6_packet) : sizeof(struct dhcp_packet), 0, (struct sockaddr *)&sourceAddr, &addrSize);
    /* TODO: check for recvfrom failure status here */
    if (dk_set(DK_MSG)) {
	fprintf(stderr, "Got %zd octets from fd %u, %s", num_octets, recv_fd,
		addrName(&sourceAddr, addrbuf, sizeof(addrbuf)));
	fprintf(stderr, "Received packet contents:\n");
	print_dhcp_packet(v6, msg, num_octets);
    }
}

void
dora(const char *server, const char *localAddr)
{
    struct sockaddr_storage send_laddr, recv_laddr;
    struct dhcp_packet discover_pkt, offer_pkt, request_pkt, ack_pkt;
    int send_fd, recv_fd;
    const unsigned char *type, *server_id;
    aaddr_buf a_yiaddr;
    struct addrinfo *remote;
    struct in_addr *local_address;

    send_fd = socket_setup(AF_INET, localAddr, "bootpc", "Send", &send_laddr);
    recv_fd = socket_setup(AF_INET, localAddr, "bootps", "Recv", &recv_laddr);

    if ((remote = getaddr(AF_INET, server, "bootps")) == NULL) {
	fprintf(stderr, "No addresses for %s\n", server);
	exit(1);
    }

    local_address = &((struct sockaddr_in *)&send_laddr)->sin_addr;
    gen_discover(&discover_pkt, local_address);

    dhcp_send(0, (unsigned char *)&discover_pkt, send_fd, remote->ai_addr, &send_laddr);
    dhcp_recv(0, &offer_pkt, recv_fd, &recv_laddr);
    type = find_option(&offer_pkt, DHO_DHCP_MESSAGE_TYPE);
    if (type == NULL) {
	fprintf(stderr, "DHCP reponse did not include message type option\n");
	exit(1);
    }
    if (type[2] != DHCPOFFER) {
	fprintf(stderr, "DHCP reponse had message type %d; expecting DHCPOFFER\n", type[2]);
	exit(1);
    }
    server_id = find_option(&offer_pkt, DHO_DHCP_SERVER_IDENTIFIER);
    if (type == NULL) {
	fprintf(stderr, "DHCP reponse did not include server identifier option\n");
	exit(1);
    }
    server_id += 2;
    printf("Server identifier: %08x\n", ntohl(*(int *)server_id));
    printf("Offered address: %s\n", addrtoa(AF_INET, &offer_pkt.yiaddr, a_yiaddr));
    gen_request(&request_pkt, local_address, &offer_pkt.yiaddr, server_id);
    dhcp_send(0, (unsigned char *)&request_pkt, send_fd, remote->ai_addr, &send_laddr);
    dhcp_recv(0, &ack_pkt, recv_fd, &recv_laddr);
}

/*
    client 546, server 547
    All_DHCP_Relay_Agents_and_Servers FF02::1:2
    DHCPV6_SOLICIT
    DHCPV6_ADVERTISE
    DHCPV6_REQUEST
    DHCPV6_REPLY

DUID option must be present
A client SHOULD generate a random number that cannot easily be guessed or
predicted to use as the transaction ID for each new message it sends
Discard ADVERTISE messages in which the Client Identifier option does not match the
      client's DUID, or in which the transaction ID does not match the SOLICIT transaction ID.
Discard REPLY messsages in whhich the "transaction-id" field in the message does not match the value
      used in the original message.
*/
void
sarr(const char *server, const char *if_name)
{
    struct sockaddr_storage send_laddr, recv_laddr;
    struct dhcpv6_packet solicit_pkt, advertise_pkt;
    int send_fd, recv_fd;
    struct in6_addr *local_address;
    struct addrinfo *remote;
    struct duid client_id;

    get_linklocal_addr(if_name, &send_laddr);
    memcpy(&recv_laddr, &send_laddr, sizeof(recv_laddr));
    send_fd = socket_setup(AF_INET6, NULL, "546", "Send", &send_laddr);
    /*
    recv_fd = socket_setup(AF_INET6, NULL, "547", "Recv", &recv_laddr);
    */
    recv_fd = send_fd;

    if (server != NULL) {
	if (strcmp(server, "all"))
	    server = All_DHCP_Relay_Agents_and_Servers;
	else if (strcmp(server, "server"))
	    server = All_DHCP_Servers;
    }
    if ((remote = getaddr(AF_INET6, server, "547")) == NULL) {
	fprintf(stderr, "Conversion failed for %s\n", server);
	exit(1);
    }

    local_address = &((struct sockaddr_in6 *)&send_laddr)->sin6_addr;

    client_id.duid_type = htons(DUID_LL);
    client_id.htype = htons(HTYPE_ETHER);
    memset(client_id.hwaddr, 0xA, 6);	/* TEMPORARY - FIX */

    gen_solicit(&solicit_pkt, &client_id);
    dhcp_send(1, (unsigned char *)&solicit_pkt, send_fd, remote->ai_addr, &send_laddr);
    dhcp_recv(1, &advertise_pkt, recv_fd, &recv_laddr);
/*
 *
 *    type = find_option(&offer_pkt, DHO_DHCP_MESSAGE_TYPE);
 *    if (type == NULL) {
 *	fprintf(stderr, "DHCP reponse did not include message type option\n");
 *	exit(1);
 *    }
 *    if (type[2] != DHCPOFFER) {
 *	fprintf(stderr, "DHCP reponse had message type %d; expecting DHCPOFFER\n", type[2]);
 *	exit(1);
 *    }
 *    server_id = find_option(&offer_pkt, DHO_DHCP_SERVER_IDENTIFIER);
 *    if (type == NULL) {
 *	fprintf(stderr, "DHCP reponse did not include server identifier option\n");
 *	exit(1);
 *    }
 *    server_id += 2;
 *    printf("Server identifier: %08x\n", ntohl(*(int *)server_id));
 *    printf("Offered address: %s\n", addrtoa(AF_INET, &offer_pkt.yiaddr, a_yiaddr));
 *    gen_request(&request_pkt, local_address, &offer_pkt.yiaddr, server_id);
 *    dhcp_send(&request_pkt, send_fd, remote->ai_addr, &send_laddr);
 *    dhcp_recv(&ack_pkt, recv_fd, &recv_laddr);
 */
}

/*
 * Must include client identifier, server identifier, IA, DUID?
 * Solitication: Create an IA.  Assign it an IAID.  Transmit a Solicit
 * message containing an IA option describing the IA.
 * Use IA_TA to request temporary addresses
 */
void
gen_solicit(struct dhcpv6_packet *dhcp_pkt, const struct duid *client_id)
{
    int tid;
    int i;
    size_t options_len = 0;

    bzero((char *) dhcp_pkt, sizeof(struct dhcpv6_packet));
    dhcp_pkt->msg_type = DHCPV6_SOLICIT;
    tid = rand();
    for (i = 0; i < 2; i++) {
	dhcp_pkt->transaction_id[i] = (unsigned char)tid;
	tid >>= 8;
    }
    add_option(1, D6O_CLIENTID, 1, sizeof(struct duid), 0, dhcp_pkt->options,
	    &options_len, client_id);
    add_option(1, D6O_IA_TA, 1, 4, 1, dhcp_pkt->options,
	    &options_len, "0xabcd");	/* Temporary - FIX */
    /* D60_ORO: Option Request Option */
    add_option(1, D6O_ORO, 1, 2, 1, dhcp_pkt->options,
	    &options_len, D6O_NAME_SERVERS);
}

/*
 * Add an option to a DHCP packet.
 *
 * Input variables:
 * If buffer_size is nonzero, options are added to a DHCP6 packet, and
 *     buffer_size specifies the size of the buffer.  If it is zero, options
 *     are added to a DHCP4 packet.
 * optnum is the option number.
 * count is the number of option parameters passed.
 * size is the size of each parameter, in bytes.
 * direct is true if the options are passed by value, false if they are passed
 * by address.
 *
 * Output variables:
 * options[] is the buffer in which to store the option.
 *
 * Input/output variables:
 * buffer_used is the amount of buffer space currently used.
 */
void
add_option(int v6, unsigned optnum, unsigned count, size_t size,
	int direct, unsigned char options[], size_t *buffer_used, ...)
{
    va_list ap;
    unsigned i;
    size_t buffer_size = v6 ? sizeof(struct dhcpv6_packet) : DHCP_MAX_OPTION_LEN;

    if ((*buffer_used + (v6 ? 4 : 2) + count * size) > buffer_size) {
	fprintf(stderr, "%s: Insufficient option space\n", progName);
	exit(1);
    }
    if (v6) {
	struct v6_option *opt = (struct v6_option *)&options[(*buffer_used)];
	opt->code = htons(optnum);
	opt->len = htons(count * size);
	*buffer_used += 4;
    }
    else {
	options[(*buffer_used)++] = optnum;
	options[(*buffer_used)++] = count * size;
    }
    va_start(ap,buffer_used);
    for (i = 1; i <= count; i++) {
	if (direct) {
	    int value = va_arg(ap, int);
	    memcpy(&options[*buffer_used], (char *)&value, size);
	}
	else {
	    char *p = va_arg(ap, char *);
	    memcpy(&options[*buffer_used], p, size);
	}
	(*buffer_used) += size;
    }
    /* ap */
    va_end(ap);
}

/*
 * Return value:
 * buf is returned.
 */
char *
addrtoa(int addr_fam, const struct in_addr *addr, aaddr_buf buf)
{
    if (inet_ntop(addr_fam, addr, buf, ADDR_NAME_BUFSIZE) == NULL)
	strcpy(buf, "untranslatable");
    return buf;
}

/*
 * getaddr: generate an addrinfo list for a given hostname and port, UDP.
 * If getaddrinfo() fails with the provided information, an error message
 * is printed and the program exits with status 2.
 *
 * Input variables:
 * hostname: The host name to look up.  This can be either a name or an IPv4 
 *     dotted-quad address, or null to not fill in the address.
 * port: The port to include in addrinfo.  This can be either a service name or
 *     an ASCII decimal number, or null to not fill in the port number.
 *
 * Globals:
 * progName, for error messages.
 *
 * Return value:
 * A pointer to the addrinfo list.  This must be freed by the caller with
 * freeaddrinfo().
 */
struct addrinfo *
getaddr(int addr_fam, const char *hostname, const char *port)
{
    struct addrinfo *ai;
    struct addrinfo hints;
    int ret;

    memset (&hints, '\0', sizeof(hints));
    hints.ai_family = addr_fam;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    if ((ret = getaddrinfo(hostname, port, &hints, &ai)) != 0) {
	fprintf(stderr, "%s: %s: getaddrinfo: %s/%s\n", progName,
		hostname == NULL ? "" : hostname, port == NULL ? "" : port, gai_strerror(ret));
	exit(2);
    }
    return ai;
}

/*
 * addrName(): Convert the address and port associated with a socket into an a
 * hostname and numeric string and store them in a buffer.
 *
 * Input variables:
 * addr is the socket to operate on.
 * bufsize is the size of the buffer.
 *
 * Output variables:
 * name is the buffer to store in.
 *
 * Return value:
 * buf is returned.
 */
char *
addrName(const struct sockaddr_storage *addr, char *name, size_t bufsize)
{
    char *buf = name;
    char servbuf[30];

    if (getnameinfo((struct sockaddr *)addr, sizeof(struct sockaddr_storage),
	  name, bufsize, servbuf, 30, 0) != 0)
	strncpy(buf, "untranslatable", bufsize-1);
    else {
	size_t len = strlen(buf);
	if (len < bufsize)
	    snprintf(name + len, bufsize - len, " port %s", servbuf);
    }
    return buf;
}

/*
 *
 * Input variables:
 * if_name is the name of the interface to search for.
 *
 * Output variables:
 * The link-local address for the interface is stored in addr.
 * 
 * Return value:
 * 1 on success, 0 if no link-local address is found.
 *
 * If retrieval of the interface address list fails, an error message is
 * printed and the program is exited with status 2.
 */
int
get_linklocal_addr(const char if_name[], struct sockaddr_storage *addr)
{

    struct ifaddrs *ifaddr, *ifa;
 
    if (getifaddrs(&ifaddr) == -1) {
	fprintf(stderr, "%s: Could not get interface addresses: %s\n",
		progName, strerror(errno));
        exit(2);
    }
 
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
	if (ifa->ifa_addr->sa_family == AF_INET6 && strcmp(ifa->ifa_name, if_name) == 0 &&
		(ntohs(((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr.__in6_u.__u6_addr16[0]) & 0xffc0) == 0xfe80)
	    break;
    }
    if (ifa != NULL)
	memcpy(addr, ifa->ifa_addr, sizeof(struct sockaddr_storage));
    freeifaddrs(ifaddr);
    return ifa != NULL;
}

void
print_addrinfo(FILE *f, const struct addrinfo *addr)
{
    fprintf(f, "Addrinfo:\n");
    fprintf(f, "flags: 0x%x;  family: %d;  socktype: %d;  proto: %d;\n",
	    addr->ai_flags, addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    fprintf(f, "addrlen: %u;  addr: %p;  canonname: %s;  next: %p\n",
	    addr->ai_addrlen, addr->ai_addr, addr->ai_canonname, addr->ai_next);
    if (addr->ai_family == AF_INET6)
	print_sa6_info(f, (struct sockaddr_in6 *)addr->ai_addr);
}

void
print_sa6_info(FILE *f, const struct sockaddr_in6 *sa)
{
    char addrbuf[ADDR_NAME_BUFSIZE];

    fprintf(f, "IPv6 sockaddr info:\n");
    fprintf(f, "family: %u;  flowinfo: 0x%x;  scope-id: %u  addr: %s\n",
	    sa->sin6_family, sa->sin6_flowinfo, sa->sin6_scope_id,
	    addrName((struct sockaddr_storage *)sa, addrbuf, sizeof(addrbuf)));
}

/*
 * Search for a specific option in the options stored in a DHCP packet.
 *
 * Input variables:
 * pkt is the packet to search.
 * search_opt is the option number to search for.
 *
 * Return value:
 * If the packet contains the option, a pointer to its start (the option
 * number) is returned.  If not, NULL is returned.
 */
const unsigned char *
find_option(const struct dhcp_packet *pkt, int search_opt)
{
    const unsigned char *p;

    p = &pkt->options[4];
    while ((p - pkt->options) < DHCP_MAX_OPTION_LEN && *p != DHO_END) {
	if (*p == search_opt)
	    return p;
	else if (*p == DHO_PAD)
	    p++;
	else {
	    size_t len = p[1];
	    p += 2 + len;
	}
    }
    return NULL;
}
