#include <sys/types.h>
#include <sys/socket.h>

int main() {
    struct sockaddr sa;
    sa.sa_len = 0;
    return 0;
}
