#include <sys/event.h>
#include <unistd.h>

int main() {
    int kq = kqueue();
    close(kq);
    return 0;
}
