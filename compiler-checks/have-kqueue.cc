#include <sys/event.h>
#include <unistd.h>

int main() {
    int kqueuefd = kqueue();
    close(kqueuefd);
    return 0;
}
