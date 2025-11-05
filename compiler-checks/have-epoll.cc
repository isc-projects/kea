#include <sys/epoll.h>
#include <unistd.h>

int main() {
    int epollfd = epoll_create1(0);
    close(epollfd);
    return 0;
}
