#ifdef __cplusplus
extern "C" {
#endif

#define FLEXIBLE_ARRAY_MEMBER 500
#define ADDR_NAME_BUFSIZE (NI_MAXHOST + 30)

#define DK_SOCK 1
#define DK_MSG 2
#define DK_PACKET 4

#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include "dhcp.h"
#include "dhcp6.h"

struct v6_option {
    uint16_t code;
    uint16_t len;
    unsigned char value;
};

typedef char aaddr_buf[ADDR_NAME_BUFSIZE];

char* addrtoa(int addr_fam, const struct in_addr* addr, aaddr_buf buf);
void print_dhcp_packet(int v6, const void* pkt, size_t len);

const char progName[] = "dhcpperf";

#ifdef __cplusplus
}
#endif
