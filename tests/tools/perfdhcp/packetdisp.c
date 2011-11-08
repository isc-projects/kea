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
#include <strings.h>
#include <string.h>
#include "perfdhcp.h"
#include "dkdebug.h"

static const char * enum_lookup(const char * const table[], size_t size, unsigned index);
static const char *optionName(int v6, unsigned optnum);
static void printOption(int v6, unsigned optnum, size_t len, const unsigned char *value);
static void print_dhcpv4_packet(const struct dhcp_packet *pkt, size_t len);
static void print_dhcpv6_packet(const struct dhcpv6_packet *pkt, size_t len);

typedef enum {
    T_UNK,
    T_STRING,
    T_PERIOD,
    T_IPADDR,
    T_MTYPE,
    T_STATUS
} opt_type;

struct dhcp_option_desc {
    char *name;
    opt_type type;
};

static struct dhcp_option_desc option_desc[] = {
[DHO_PAD] = { "PAD", T_UNK },
[DHO_SUBNET_MASK] = { "SUBNET_MASK", T_UNK },
[DHO_TIME_OFFSET] = { "TIME_OFFSET", T_PERIOD },
[DHO_ROUTERS] = { "ROUTERS", T_IPADDR },
[DHO_TIME_SERVERS] = { "TIME_SERVERS", T_UNK },
[DHO_NAME_SERVERS] = { "NAME_SERVERS", T_UNK },
[DHO_DOMAIN_NAME_SERVERS] = { "DOMAIN_NAME_SERVERS", T_IPADDR },
[DHO_LOG_SERVERS] = { "LOG_SERVERS", T_UNK },
[DHO_COOKIE_SERVERS] = { "COOKIE_SERVERS", T_UNK },
[DHO_LPR_SERVERS] = { "LPR_SERVERS", T_IPADDR },
[DHO_IMPRESS_SERVERS] = { "IMPRESS_SERVERS", T_UNK },
[DHO_RESOURCE_LOCATION_SERVERS] = { "RESOURCE_LOCATION_SERVERS", T_UNK },
[DHO_HOST_NAME] = { "HOST_NAME", T_UNK },
[DHO_BOOT_SIZE] = { "BOOT_SIZE", T_UNK },
[DHO_MERIT_DUMP] = { "MERIT_DUMP", T_UNK },
[DHO_DOMAIN_NAME] = { "DOMAIN_NAME", T_STRING },
[DHO_SWAP_SERVER] = { "SWAP_SERVER", T_UNK },
[DHO_ROOT_PATH] = { "ROOT_PATH", T_UNK },
[DHO_EXTENSIONS_PATH] = { "EXTENSIONS_PATH", T_UNK },
[DHO_IP_FORWARDING] = { "IP_FORWARDING", T_UNK },
[DHO_NON_LOCAL_SOURCE_ROUTING] = { "NON_LOCAL_SOURCE_ROUTING", T_UNK },
[DHO_POLICY_FILTER] = { "POLICY_FILTER", T_UNK },
[DHO_MAX_DGRAM_REASSEMBLY] = { "MAX_DGRAM_REASSEMBLY", T_UNK },
[DHO_DEFAULT_IP_TTL] = { "DEFAULT_IP_TTL", T_UNK },
[DHO_PATH_MTU_AGING_TIMEOUT] = { "PATH_MTU_AGING_TIMEOUT", T_UNK },
[DHO_PATH_MTU_PLATEAU_TABLE] = { "PATH_MTU_PLATEAU_TABLE", T_UNK },
[DHO_INTERFACE_MTU] = { "INTERFACE_MTU", T_UNK },
[DHO_ALL_SUBNETS_LOCAL] = { "ALL_SUBNETS_LOCAL", T_UNK },
[DHO_BROADCAST_ADDRESS] = { "BROADCAST_ADDRESS", T_UNK },
[DHO_PERFORM_MASK_DISCOVERY] = { "PERFORM_MASK_DISCOVERY", T_UNK },
[DHO_MASK_SUPPLIER] = { "MASK_SUPPLIER", T_UNK },
[DHO_ROUTER_DISCOVERY] = { "ROUTER_DISCOVERY", T_UNK },
[DHO_ROUTER_SOLICITATION_ADDRESS] = { "ROUTER_SOLICITATION_ADDRESS", T_UNK },
[DHO_STATIC_ROUTES] = { "STATIC_ROUTES", T_UNK },
[DHO_TRAILER_ENCAPSULATION] = { "TRAILER_ENCAPSULATION", T_UNK },
[DHO_ARP_CACHE_TIMEOUT] = { "ARP_CACHE_TIMEOUT", T_UNK },
[DHO_IEEE802_3_ENCAPSULATION] = { "IEEE802_3_ENCAPSULATION", T_UNK },
[DHO_DEFAULT_TCP_TTL] = { "DEFAULT_TCP_TTL", T_UNK },
[DHO_TCP_KEEPALIVE_INTERVAL] = { "TCP_KEEPALIVE_INTERVAL", T_UNK },
[DHO_TCP_KEEPALIVE_GARBAGE] = { "TCP_KEEPALIVE_GARBAGE", T_UNK },
[DHO_NIS_DOMAIN] = { "NIS_DOMAIN", T_UNK },
[DHO_NIS_SERVERS] = { "NIS_SERVERS", T_UNK },
[DHO_NTP_SERVERS] = { "NTP_SERVERS", T_IPADDR },
[DHO_VENDOR_ENCAPSULATED_OPTIONS] = { "VENDOR_ENCAPSULATED_OPTIONS", T_UNK },
[DHO_NETBIOS_NAME_SERVERS] = { "NETBIOS_NAME_SERVERS", T_UNK },
[DHO_NETBIOS_DD_SERVER] = { "NETBIOS_DD_SERVER", T_UNK },
[DHO_NETBIOS_NODE_TYPE] = { "NETBIOS_NODE_TYPE", T_UNK },
[DHO_NETBIOS_SCOPE] = { "NETBIOS_SCOPE", T_UNK },
[DHO_FONT_SERVERS] = { "FONT_SERVERS", T_UNK },
[DHO_X_DISPLAY_MANAGER] = { "X_DISPLAY_MANAGER", T_UNK },
[DHO_DHCP_REQUESTED_ADDRESS] = { "DHCP_REQUESTED_ADDRESS", T_IPADDR },
[DHO_DHCP_LEASE_TIME] = { "DHCP_LEASE_TIME", T_PERIOD },
[DHO_DHCP_OPTION_OVERLOAD] = { "DHCP_OPTION_OVERLOAD", T_UNK },
[DHO_DHCP_MESSAGE_TYPE] = { "DHCP_MESSAGE_TYPE", T_MTYPE },
[DHO_DHCP_SERVER_IDENTIFIER] = { "DHCP_SERVER_IDENTIFIER", T_UNK },
[DHO_DHCP_PARAMETER_REQUEST_LIST] = { "DHCP_PARAMETER_REQUEST_LIST", T_UNK },
[DHO_DHCP_MESSAGE] = { "DHCP_MESSAGE", T_UNK },
[DHO_DHCP_MAX_MESSAGE_SIZE] = { "DHCP_MAX_MESSAGE_SIZE", T_UNK },
[DHO_DHCP_RENEWAL_TIME] = { "DHCP_RENEWAL_TIME", T_UNK },
[DHO_DHCP_REBINDING_TIME] = { "DHCP_REBINDING_TIME", T_UNK },
[DHO_VENDOR_CLASS_IDENTIFIER] = { "VENDOR_CLASS_IDENTIFIER", T_UNK },
[DHO_DHCP_CLIENT_IDENTIFIER] = { "DHCP_CLIENT_IDENTIFIER", T_UNK },
[DHO_NWIP_DOMAIN_NAME] = { "NWIP_DOMAIN_NAME", T_UNK },
[DHO_NWIP_SUBOPTIONS] = { "NWIP_SUBOPTIONS", T_UNK },
[DHO_USER_CLASS] = { "USER_CLASS", T_UNK },
[DHO_USER_CLASS] = { "USER_CLASS", T_UNK },
[DHO_FQDN] = { "FQDN", T_UNK },
[DHO_DHCP_AGENT_OPTIONS] = { "DHCP_AGENT_OPTIONS", T_UNK },
[DHO_AUTHENTICATE] = { "AUTHENTICATE", T_UNK },
[DHO_CLIENT_LAST_TRANSACTION_TIME] = { "CLIENT_LAST_TRANSACTION_TIME", T_UNK },
[DHO_ASSOCIATED_IP] = { "ASSOCIATED_IP", T_UNK },
[DHO_SUBNET_SELECTION] = { "SUBNET_SELECTION", T_UNK },
[DHO_DOMAIN_SEARCH] = { "DOMAIN_SEARCH", T_UNK },
[DHO_VIVCO_SUBOPTIONS] = { "VIVCO_SUBOPTIONS", T_UNK },
[DHO_VIVSO_SUBOPTIONS] = { "VIVSO_SUBOPTIONS", T_UNK },
[DHO_END] = { "END", T_UNK },
[64] = { "NIS Domain", T_UNK },
[65] = { "NIS Servers", T_UNK },
[66] = { "TFTP Server", T_UNK },
[67] = { "Bootfile name", T_UNK },
[68] = { "Mobile IP Home Agent", T_UNK },
[69] = { "SMTP Server", T_IPADDR },
[70] = { "POP Server", T_IPADDR },
[71] = { "NNTP Server", T_IPADDR },
[72] = { "WWW Server", T_IPADDR },
[73] = { "Finger Server", T_IPADDR },
[74] = { "IRC Server", T_IPADDR },
[75] = { "StreetTalk Server", T_IPADDR },
[76] = { "StreetTalk Directory Assistance Server", T_IPADDR }
};

static const char * const message_types[] = {
    [DHCPDISCOVER] = "DHCPDISCOVER",
    [DHCPOFFER] = "DHCPOFFER",
    [DHCPREQUEST] = "DHCPREQUEST",
    [DHCPDECLINE] = "DHCPDECLINE",
    [DHCPACK] = "DHCPACK",
    [DHCPNAK] = "DHCPNAK",
    [DHCPRELEASE] = "DHCPRELEASE",
    [DHCPINFORM] = "DHCPINFORM",
    [DHCPLEASEQUERY] = "DHCPLEASEQUERY",
    [DHCPLEASEUNASSIGNED] = "DHCPLEASEUNASSIGNED",
    [DHCPLEASEUNKNOWN] = "DHCPLEASEUNKNOWN",
    [DHCPLEASEACTIVE] = "DHCPLEASEACTIVE"
};

static struct dhcp_option_desc option6_desc[] = {
    [D6O_CLIENTID] = { "D6O_CLIENTID", T_UNK },
    [D6O_SERVERID] = { "D6O_SERVERID", T_UNK },
    [D6O_IA_NA] = { "D6O_IA_NA", T_UNK },
    [D6O_IA_TA] = { "D6O_IA_TA", T_UNK },
    [D6O_IAADDR] = { "D6O_IAADDR", T_UNK },
    [D6O_ORO] = { "D6O_ORO", T_UNK },
    [D6O_PREFERENCE] = { "D6O_PREFERENCE", T_UNK },
    [D6O_ELAPSED_TIME] = { "D6O_ELAPSED_TIME", T_PERIOD },
    [D6O_RELAY_MSG] = { "D6O_RELAY_MSG", T_UNK },
    [D6O_AUTH] = { "D6O_AUTH", T_UNK },
    [D6O_UNICAST] = { "D6O_UNICAST", T_UNK },
    [D6O_STATUS_CODE] = { "D6O_STATUS_CODE", T_STATUS },
    [D6O_RAPID_COMMIT] = { "D6O_RAPID_COMMIT", T_UNK },
    [D6O_USER_CLASS] = { "D6O_USER_CLASS", T_UNK },
    [D6O_VENDOR_CLASS] = { "D6O_VENDOR_CLASS", T_UNK },
    [D6O_VENDOR_OPTS] = { "D6O_VENDOR_OPTS", T_UNK },
    [D6O_INTERFACE_ID] = { "D6O_INTERFACE_ID", T_UNK },
    [D6O_RECONF_MSG] = { "D6O_RECONF_MSG", T_UNK },
    [D6O_RECONF_ACCEPT] = { "D6O_RECONF_ACCEPT", T_UNK },
    [D6O_SIP_SERVERS_DNS] = { "D6O_SIP_SERVERS_DNS", T_UNK },
    [D6O_SIP_SERVERS_ADDR] = { "D6O_SIP_SERVERS_ADDR", T_UNK },
    [D6O_NAME_SERVERS] = { "D6O_NAME_SERVERS", T_IPADDR },
    [D6O_DOMAIN_SEARCH] = { "D6O_DOMAIN_SEARCH", T_UNK },
    [D6O_IA_PD] = { "D6O_IA_PD", T_UNK },
    [D6O_IAPREFIX] = { "D6O_IAPREFIX", T_UNK },
    [D6O_NIS_SERVERS] = { "D6O_NIS_SERVERS", T_UNK },
    [D6O_NISP_SERVERS] = { "D6O_NISP_SERVERS", T_UNK },
    [D6O_NIS_DOMAIN_NAME] = { "D6O_NIS_DOMAIN_NAME", T_UNK },
    [D6O_NISP_DOMAIN_NAME] = { "D6O_NISP_DOMAIN_NAME", T_UNK },
    [D6O_SNTP_SERVERS] = { "D6O_SNTP_SERVERS", T_UNK },
    [D6O_INFORMATION_REFRESH_TIME] = { "D6O_INFORMATION_REFRESH_TIME", T_UNK },
    [D6O_BCMCS_SERVER_D] = { "D6O_BCMCS_SERVER_D", T_UNK },
    [D6O_BCMCS_SERVER_A] = { "D6O_BCMCS_SERVER_A", T_UNK },
    [D6O_GEOCONF_CIVIC] = { "D6O_GEOCONF_CIVIC", T_UNK },
    [D6O_REMOTE_ID] = { "D6O_REMOTE_ID", T_UNK },
    [D6O_SUBSCRIBER_ID] = { "D6O_SUBSCRIBER_ID", T_UNK },
    [D6O_CLIENT_FQDN] = { "D6O_CLIENT_FQDN", T_UNK },
    [D6O_PANA_AGENT] = { "D6O_PANA_AGENT", T_UNK },
    [D6O_NEW_POSIX_TIMEZONE] = { "D6O_NEW_POSIX_TIMEZONE", T_UNK },
    [D6O_NEW_TZDB_TIMEZONE] = { "D6O_NEW_TZDB_TIMEZONE", T_UNK },
    [D6O_ERO] = { "D6O_ERO", T_UNK },
    [D6O_LQ_QUERY] = { "D6O_LQ_QUERY", T_UNK },
    [D6O_CLIENT_DATA] = { "D6O_CLIENT_DATA", T_UNK },
    [D6O_CLT_TIME] = { "D6O_CLT_TIME", T_UNK },
    [D6O_LQ_RELAY_DATA] = { "D6O_LQ_RELAY_DATA", T_UNK },
    [D6O_LQ_CLIENT_LINK] = { "D6O_LQ_CLIENT_LINK", T_UNK }
};

static const char * const message6_types[] = {
    [DHCPV6_SOLICIT] = "DHCPV6_SOLICIT",
    [DHCPV6_ADVERTISE] = "DHCPV6_ADVERTISE",
    [DHCPV6_REQUEST] = "DHCPV6_REQUEST",
    [DHCPV6_CONFIRM] = "DHCPV6_CONFIRM",
    [DHCPV6_RENEW] = "DHCPV6_RENEW",
    [DHCPV6_REBIND] = "DHCPV6_REBIND",
    [DHCPV6_REPLY] = "DHCPV6_REPLY",
    [DHCPV6_RELEASE] = "DHCPV6_RELEASE",
    [DHCPV6_DECLINE] = "DHCPV6_DECLINE",
    [DHCPV6_RECONFIGURE] = "DHCPV6_RECONFIGURE",
    [DHCPV6_INFORMATION_REQUEST] = "DHCPV6_INFORMATION_REQUEST",
    [DHCPV6_RELAY_FORW] = "DHCPV6_RELAY_FORW",
    [DHCPV6_RELAY_REPL] = "DHCPV6_RELAY_REPL",
    [DHCPV6_LEASEQUERY] = "DHCPV6_LEASEQUERY",
    [DHCPV6_LEASEQUERY_REPLY] = "DHCPV6_LEASEQUERY_REPLY"
};

static const char * const status_codes[] = {
    [STATUS_Success] = "Success",
    [STATUS_UnspecFail] = "UnspecFail",
    [STATUS_NoAddrsAvail] = "NoAddrsAvail",
    [STATUS_NoBinding] = "NoBinding",
    [STATUS_NotOnLink] = "NotOnLink",
    [STATUS_UseMulticast] = "UseMulticast",
    [STATUS_NoPrefixAvail] = "NoPrefixAvail",
    [STATUS_UnknownQueryType] = "UnknownQueryType",
    [STATUS_MalformedQuery] = "MalformedQuery",
    [STATUS_NotConfigured] = "NotConfigured",
    [STATUS_NotAllowed] = "NotAllowed",
};

void
print_dhcp_packet(int v6, const void *pkt, size_t len)
{
    if (v6)
	print_dhcpv6_packet((struct dhcpv6_packet *)pkt, len);
    else
	print_dhcpv4_packet((struct dhcp_packet *)pkt, len);

    if (dk_set(DK_PACKET)) {
	unsigned i;

	fprintf(stderr, "Raw packet contents (%zu bytes):\n", len);
	for (i = 0; i < len; i++)
	    fprintf(stderr, "%02x ", ((unsigned char *)pkt)[i]);
	fputc('\n', stderr);
    }
}

/*
 * Note: Not reentrant
 */
static const char *
enum_lookup(const char * const table[], size_t size, unsigned index)
{
    static char numbuf[10];

    if (index < (size / sizeof(char *)) && table[index] != NULL)
	return table[index];
    else {
	snprintf(numbuf, sizeof(numbuf), "%u", index);
	return numbuf;
    }
}

/*
 * Note: Not reentrant
 */
static const char *
optionName(int v6, unsigned optnum)
{
    static char numbuf[16];
    unsigned maxOpt = ((v6 ? sizeof(option6_desc) : sizeof(option_desc)) - 1) /
	    sizeof(struct dhcp_option_desc);
    struct dhcp_option_desc *descTable;

    if (optnum > maxOpt) {
	snprintf(numbuf, sizeof(numbuf), "invalid (%u)", optnum);
	return numbuf;
    }
    descTable = v6 ? option6_desc : option_desc;
    if (descTable[optnum].name == NULL) {
	snprintf(numbuf, sizeof(numbuf), "%u", optnum);
	return numbuf;
    }
    else
	return descTable[optnum].name;
}

/*
 *
 * Output variables: None
 */
static void
printOption(int v6, unsigned optnum, size_t len, const unsigned char *value)
{
    struct dhcp_option_desc *descTable = v6 ? option6_desc : option_desc;
    char buf[ADDR_NAME_BUFSIZE];
    unsigned i;
    unsigned maxOpt = ((v6 ? sizeof(option6_desc) : sizeof(option_desc)) - 1) / sizeof(struct dhcp_option_desc);
    unsigned statusCode;

    fprintf(stderr, "Option %s (%d) length %zu value ", optionName(v6, optnum), optnum, len);

    switch (optnum > maxOpt ? T_UNK : descTable[optnum].type) {
    case T_STRING:
	fprintf(stderr, "\"%.*s\"\n", (int) len, value);
	break;
    case T_PERIOD:
	fprintf(stderr, "%d seconds\n", ntohl(*(int *)value));
	break;
    case T_MTYPE:
	fprintf(stderr, "%s\n", enum_lookup(message_types, sizeof(message_types), *value));
	break;
    case T_IPADDR:
	for (i = 0; len - i >= 4; i += 4)
	    fprintf(stderr, "%s%s", addrtoa(AF_INET, (struct in_addr *)(value+i), buf), len - i > 4 ? ", " : "\n");
	break;
    case T_STATUS:
	statusCode = ntohs(*(uint16_t *)value);
	fprintf(stderr, "%s: %*.*s\n", 
		enum_lookup(status_codes, sizeof(status_codes), statusCode),
		(int)len - 2, (int)len - 2, value + 2);
	break;
    default:
	for (i = 0; i < len; i++)
	    fprintf(stderr, "%02x", value[i]);
	fputc('\n', stderr);
	break;
    }
}

static void
print_dhcpv4_packet(const struct dhcp_packet *pkt, size_t msglen)
{
    int i;
    const unsigned char *p;
    aaddr_buf buf1, buf2, buf3, buf4;

    fprintf(stderr, 
"opcode	%u\n\
htype	%u\n\
hlen	%u\n\
hops	%u\n\
xid	0x%0x\n\
secs	%u\n\
flags	0x%x\n\
ciaddr	%s\n\
yiaddr	%s\n\
siaddr	%s\n\
giaddr	%s\n\
chaddr	",
	pkt->op,
	pkt->htype,
	pkt->hlen,
	pkt->hops,
	pkt->xid,
	pkt->secs,
	pkt->flags,
	addrtoa(AF_INET, &pkt->ciaddr, buf1),
	addrtoa(AF_INET, &pkt->yiaddr, buf2),
	addrtoa(AF_INET, &pkt->siaddr, buf3),
	addrtoa(AF_INET, &pkt->giaddr, buf4));
    for (i = 0; i < pkt->hlen; i++)
	fprintf(stderr, "%02x", pkt->chaddr[i]);
    fputc('\n', stderr);
    fprintf(stderr, "magic	0x%x\n", *(unsigned int *)&pkt->options);
    p = &pkt->options[4];
    while ((unsigned) (p - (unsigned char *)pkt) < msglen && *p != DHO_END) {
	if (*p == DHO_PAD) {
	    fprintf(stderr, "Option PAD\n");
	    p++;
	}
	else {
	    unsigned optnum = *p++;
	    size_t len = *p++;

	    printOption(0, optnum, len, p);
	    p += len;
	}
    }
}

static void
print_dhcpv6_packet(const struct dhcpv6_packet *pkt, size_t msglen)
{
    int i;
    const unsigned char *p;
    struct v6_option *opt;

    fprintf(stderr, "msgtype\t%s\ntid\t", enum_lookup(message6_types, sizeof(message6_types), pkt->msg_type));
    for (i = 0; i <= 2; i++)
	fprintf(stderr, "%02x", pkt->transaction_id[i]);
    fputc('\n', stderr);

    p = pkt->options;
    opt = (struct v6_option *)p;
    while ((unsigned) (p - (unsigned char *)pkt) < msglen && opt->code != 0) {
	unsigned optlen = ntohs(opt->len);
	printOption(1, ntohs(opt->code), optlen, &opt->value);
	p += 4 + optlen;
	opt = (struct v6_option *)p;
    }
}
