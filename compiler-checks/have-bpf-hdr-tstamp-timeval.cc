#include <sys/types.h>
#include <sys/time.h>
#include <net/bpf.h>

void test() {
    struct bpf_hdr hdr;
    struct timeval *tv = &hdr.bh_tstamp;
}

int main() {
    return 0;
}
